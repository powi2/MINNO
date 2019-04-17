//==============================================================================
// IBP_Supply.cpp (User function)
// 
//    void IBP_Supply_user_init(test_function& func)
//    void IBP_Supply(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "IBP_Supply.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IBP_Supply_user_init(test_function& func)
{
	IBP_Supply_params *ours;
    ours = (IBP_Supply_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IBP_Supply(test_function& func)
{
    // The two lines below must be the first two in the function.
    IBP_Supply_params *ours;
    ours = (IBP_Supply_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "IBP_Supply";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IBP_Supply,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	float BPP_ICH1_0V_p			=0, 
		  BPS_ICH1_3V_s			=0, 
		  BPP_ICH2_4V_p			=0, 
		  BPS_ICH2_4V_s			=0;
	float BPP_ICH3_CEN_p		=0,
		  BPS_ICH3_VO_s			=0, 
		  BPP_ICH4_D_p			=0,  
		  BPP_ICH5_CEN_p		=0;
	float BPS_IS1_nsw_s			=0,    
		  BPS_IS2_sw_s			=0,    
		  BPP_IS2_6p2_p			=0, 
		  BPP_IS2_VBPP_p		=0;
	float BPS_ICH3_VO_5v_S		=0, 
		  BPS_ICH3_4V_VO_5v_S	=0, 
		  BPS_ICH3_4V_VO20v_S	=0, 
		  BPS_ICH2_4V_FW11V_s	=0;
	float VO_S					=0, 
		  VBPS_S				=0;
	float Delta_VO_minus_VBPS_S	=0;
	float Vsr_clamp				=0.0,
		  Isr_clamp				=0.0,
		  Rsr_clamp				=0.0,
		  ISRclamp_S			=0.0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//
/*
****************************************************************************
 *						BPP and BPS Charge Current							*
 ****************************************************************************/
	
	Open_relay(K3);
	Open_relay(K27);	// Make sure DDD-7-4 disconnect from Vout pin
	Close_relay(K2);	// Connect DVI11_0 to Drain
	Close_relay(K18);	// Connect DVI11_1 to FW pin
	delay(4);

	//------------------------------------------------------------------------------------------------------------------
	//---------------- ICH1_0V_D-P (Drain=45V, BPP=0V)
	//------------------------------------------------------------------------------------------------------------------
	/* Because Secondary get damaged easily with high current coming from FW, Secondary is not testing at vBPS=0V.
	   Temporary set vBPS=3V so the potential difference between FW and BPS is less and current would be less so 
	   device won't be damaged.  Current is also limited from FW source from 300mA to 190mA to prevent device damage. */

	//VO 
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_10_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, 100e-3,		RANGE_300_MA);
	//Vpin set to 0V/30mA
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
	//Drain set to 45V/300mA
	D_dvi->set_current(D_ch, 300.0e-3,		RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 45.0, 			VOLT_50_RANGE);	// DVI_11_0
	wait.delay_10_us(20);
	//BPP set to 0V/30mA with current_meas_mode
	BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
	wait.delay_10_us(20);
	BPP_ICH1_0V_p = BPP_ovi->measure_average(25);
	
	/*------------------------------------------------------------------------------------------------------------------
	//---------------- BPP_ICH2_4V_D-P (FW=0V, BPS=0V, Drain=45V, BPP=4V)
	//---------------- BPP_ICH3_CEN-P  (FW=0V, BPS=0V, Drain=45V, BPP=(VBPP_P + VBPP_M)/2)
	//---------------- BPP_ICH4_4V_D-P (FW=0V, BPS=0V, Drain=45V, BPP=> PV_final then 4V)
	//---------------- BPP_ICH5_CEN-P  (FW=0V, BPS=0V, Drain=45V, BPP=(VBPP_P + VBPP_M)/2)

									_______ BPP_PV_final
						   /\	   /
					  (3)_/  \_(4)/_(5)
						 /    \  /
						/	   \/__________ gVBPP_M_Init-0.2
				   (2)_/		
					  /
				 (1)_/

				 (1) BPP_ICH1_0V_p
				 (2) BPP_ICH2_4V_D-P
				 (3) BPP_ICH3_CEN-P
				 (4) BPP_ICH4_4V_D-P
				 (5) BPP_ICH5_CEN-P
	  ------------------------------------------------------------------------------------------------------------------*/
	//FW	=0V
	//BPS	=0V
	//Drain	=45V 
	//BPP	=4V (new)
	//Vout = 0V/100mA, 10Vrange/300mARange
	BPP_ovi->set_voltage(BPP_ch, 4.0, 		RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(20);
	BPP_ICH2_4V_p = BPP_ovi->measure_average(15);	

	//** BPP_ICH3_CEN_p
	VBPP_ramp_up(gVBPP_VCEN-0.5, gVBPP_VCEN, 100e-3);
	BPP_ICH3_CEN_p = BPP_ovi->measure_average(25);	

	//Require BPP power down here TMT91 else ICH4 measure -6mA
	//BPP_ovi->set_voltage(BPP_ch, 0.0,	RANGE_10_V);	// OVI_1_0
	//wait.delay_10_us(50);

	//** BPP_ICH4_D_p
	//FW_dvi->set_current(FW_ch, 30.0e-3,	RANGE_30_MA);
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_PV_final,	RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(150);

	BPP_ovi->set_voltage(BPP_ch, gVBPP_VCEN,		RANGE_10_V);	// OVI_1_0
	delay(1);
	delay(2);	// JD Longer delay for smaller devices, was 1
	BPP_ICH4_D_p = BPP_ovi->measure_average(25);	

	//** BPP_ICH5_CEN_p
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-0.2,	RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(50);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_VCEN,		RANGE_10_V);	// OVI_1_0
	if(gSiliconRev_P <=2 && (OPCODE==4300 || OPCODE==4500))
		wait.delay_10_us(150);
	else
		wait.delay_10_us(50);

	BPP_ICH5_CEN_p = BPP_ovi->measure_average(25);	

	BPP_ovi->set_voltage(BPP_ch, 0.0,		RANGE_10_V);	// OVI_1_0
	
	//------------------------------------------------------------------------------------------------------------------
	//---------------- ICH1_3V_FW-S (FW=45V, BPS=3V, Drain=45V, BPP=0V)
	//------------------------------------------------------------------------------------------------------------------
	//FW	=45V
	//BPS	=3V
	//Drain	=45V 
	//BPP	=0V
	//Vout = 0V/100mA, 10Vrange/300mARange
//	BPS_dvi->set_current(BPS_ch, 300e-3,	RANGE_300_MA);	
//	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
////	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_10_RANGE);	// DVI_9_1	
//	BPS_dvi->set_voltage(BPS_ch, 3.0, 		VOLT_10_RANGE);	// Set   to 3V    to reduce device damage
//	FW_dvi->set_current(FW_ch, 190.0e-3,	RANGE_300_MA);	// Clamp to 190mA to reduce device damage
//	FW_dvi->set_voltage(FW_ch, 45.0, 		VOLT_50_RANGE);	// DVI_11_1
//	//delay(gDly_Wait_and_Listen_Normal_Mode_P);	// Long delay (Maybe this is where it kills the device with high current)
//	delay(1);	// See if shorter helps.
//	BPS_ICH1_3V_s = BPS_dvi->measure_average(25);


	
	//------------------------------------------------------------------------------------------------------------------
	//---------------- ICH2_4V_FW-S,  ICH2_4V_FW11v-S
	////------------------------------------------------------------------------------------------------------------------
	////FW	=45V
	////BPS	=vPlus+150mV->4V "2ndary PU and back down to 4V"  (new)
	////Drain	=45V 
	////BPP	=4V
	////Vout = 0V/100mA, 10Vrange/300mARange
	//BPP_ovi->set_voltage(BPP_ch, 4.0, 		RANGE_10_V);	// OVI_1_0
	//wait.delay_10_us(50);

	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 		VOLT_10_RANGE);	// DVI_9_1
	//wait.delay_10_us(20);
	//BPS_dvi->set_voltage(BPS_ch, 4.0, 		VOLT_10_RANGE);	// DVI_9_1
	//wait.delay_10_us(20);
	//delay(1);
	//BPS_ICH2_4V_s = BPS_dvi->measure_average(15);
	//
	////FW	=11V
	//FW_dvi->set_voltage(FW_ch, 11.0, 		VOLT_50_RANGE);	// DVI_11_1
	//wait.delay_10_us(20);
	//delay(1);
	//BPS_ICH2_4V_FW11V_s = BPS_dvi->measure_average(25);

	//FW	=45V/120mA  (As long as current is above the min limit, we know the ICH between FW and BPS is good.  Use 100mA instead)
		//BPS	=vPlus+150mV->4V "2ndary PU and back down to 4V"  (new)
		//Drain	=45V 
		//BPP	=0V
		//Vout = 0V/100mA, 10Vrange/300mARange
	//pulse.do_pulse();
	//	BPS_dvi->set_current(BPS_ch, 300e-3,	RANGE_300_MA);	
	//	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//	FW_dvi->set_current(FW_ch, 100.0e-3,	RANGE_300_MA);	// Clamp to 100mA to reduce stress (max current could go up to 115mA)
	//	VBPS_ramp_up(3, gVBPS_final, 50e-3);			// vfinal
	////pulse.do_pulse();
	//	wait.delay_10_us(5);
	//	FW_dvi->set_voltage(FW_ch, 45.0, 		VOLT_50_RANGE);	// DVI_11_1
	////pulse.do_pulse();
	//	BPS_dvi->set_voltage(BPS_ch, 4.0, 		VOLT_10_RANGE);	// DVI_9_1
	//	wait.delay_10_us(35);
	////pulse.do_pulse();
	//	BPS_ICH2_4V_s = BPS_dvi->measure_average(5);	//Accuracy not needed.  As long as it's sink more than upper limit (-44mA)
	//	
	//	//FW	=11V
	////pulse.do_pulse();
	//	FW_dvi->set_voltage(FW_ch, 11.0, 		VOLT_50_RANGE);	// DVI_11_1
	//	wait.delay_10_us(15);
	////pulse.do_pulse();
	//	BPS_ICH2_4V_FW11V_s = BPS_dvi->measure_average(5);  //Accuracy not needed.  As long as it's sink more than upper limit (-47mA)


	//------------------------------------------------------------------------------------------------------------------
	//---------------- ICH3_CEN-P (First ramp of power-up sequence) "vCEN = (vPlus + vMinus)/2" -------------------------
	//------------------------------------------------------------------------------------------------------------------
	//FW	=0V								(new)
	//BPS	=4V
	//Drain	=45V 
	//BPP	=4V
	//Vout = 5V/100mA, 10Vrange/300mARange	(new)
	//Measure Current from Vout.
	//---------------------------------------------------------------------------
	// Set VO clamp current
	//FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
	//wait.delay_10_us(10);
	////VO_dvi->set_voltage(VO_ch, 3.5, 		VOLT_10_RANGE);	// DVI_9_0
	////VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_10_RANGE);	// DVI_9_0
	////VO_dvi->set_voltage(VO_ch, 4.5, 		VOLT_10_RANGE);	// DVI_9_0
	//VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_10_RANGE);	// DVI_9_0
	//wait.delay_10_us(20);
	//VO_dvi->set_meas_mode(VO_ch,			DVI_MEASURE_CURRENT);
	//wait.delay_10_us(10);
	//BPS_ICH3_VO_s = VO_dvi->measure_average(25);

	//------------------------------------------------------------------------------------------------------------------
	//---------------- ICH3_4V_VO_5v-S
	//---------------- ICH3_3V_VO_5v-S
	//---------------- ICH3_4V_VO_20v-S
	//------------------------------------------------------------------------------------------------------------------
	//FW	=0V
	//Drain	=45V 
	//BPP	=4V
	//Vout = 5V/100mA, 10Vrange/300mARange	(measure current from Vout)

		//TMT43 require Secondary to bring BPS up to vPlus + 50mV because the first power-up has a big dip due to FW high.
		//Here is with FW at 0V and it's able to bring BPS high without dip so it's really PU.
	//	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 		VOLT_10_RANGE);	// DVI_9_1
	//	wait.delay_10_us(10);

	////BPS	=4V								(new)
	//BPS_dvi->set_voltage(BPS_ch, 4.0, 		VOLT_10_RANGE);	// DVI_9_1
	//wait.delay_10_us(50);
	//BPS_ICH3_4V_VO_5v_S = VO_dvi->measure_average(25);

	////Vout = 20V
	//VO_dvi->set_voltage(VO_ch, 20.0, 		VOLT_50_RANGE);	// DVI_9_0
	//delay(1);
	//BPS_ICH3_4V_VO20v_S = VO_dvi->measure_average(25);

	//if(1)
	//{
	//	//Vout = 20V
	//	VO_dvi->set_voltage(VO_ch, 20.0, 		VOLT_50_RANGE);	// DVI_9_0
	//	delay(1);
	//	BPS_ICH3_4V_VO20v_S = VO_dvi->measure_average(25);
	//}
	////Vout = 5V/100mA, 10Vrange/300mARange	(measure current from Vout)
	////BPS	=3V								(new)
	//VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_10_RANGE);	// DVI_9_0
	//wait.delay_10_us(20);
	//BPS_dvi->set_voltage(BPS_ch, 3.0, 		VOLT_10_RANGE);	// DVI_9_1
	//delay(1);
	//BPS_ICH3_VO_5v_S = VO_dvi->measure_average(25);


	////------------------------------------------------------------------------------------------------------------------
	////---------------- R_SRclamp-S
	////------------------------------------------------------------------------------------------------------------------
	////BPS	= vPlus + 50mV
	////SR	= 5V/10mA
	//// Power down secondary.
	//BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_10_RANGE);	// DVI_9_1
	//VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	//FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
	//wait.delay_10_us(10);

	//BPS_dvi->set_current(BPS_ch, 5.0e-3,		RANGE_300_MA);
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// DVI_9_1
	//SR_dvi2k->set_voltage(SR_ch, 5.0, 	VOLT_5_RANGE);	// -.3 DVI_21_0
	//SR_dvi2k->set_current(SR_ch, 10e-3,	RANGE_200_MA);			// -1.0
	//wait.delay_10_us(10);
	//SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE);
	//wait.delay_10_us(25);
	//Vsr_clamp = SR_dvi2k->measure_average(15);
	//SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_CURRENT);
	//wait.delay_10_us(25);
	//Isr_clamp = SR_dvi2k->measure_average(25);
	//Rsr_clamp = Vsr_clamp / Isr_clamp;


	//// Power down secondary.
	//SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_5_RANGE);	
	//BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_10_RANGE);	// DVI_9_1
	//wait.delay_10_us(5);
#if 0
	//** BPP_ICH3_CEN_p
	VBPP_ramp_up(gVBPP_VCEN-0.5, gVBPP_VCEN, 100e-3);
	BPP_ICH3_CEN_p = BPP_ovi->measure_average(25);	

	//Require BPP power down here TMT91 else ICH4 measure -6mA
	//BPP_ovi->set_voltage(BPP_ch, 0.0,	RANGE_10_V);	// OVI_1_0
	//wait.delay_10_us(50);

	//** BPP_ICH4_D_p
	//FW_dvi->set_current(FW_ch, 30.0e-3,	RANGE_30_MA);
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_PV_final,	RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(50);
	//wait.delay_10_us(90);	// JD Longer delay for smaller devices, was 50

	BPP_ovi->set_voltage(BPP_ch, gVBPP_VCEN,		RANGE_10_V);	// OVI_1_0
	delay(1);
	delay(2);	// JD Longer delay for smaller devices, was 1
	BPP_ICH4_D_p = BPP_ovi->measure_average(25);	

	//** BPP_ICH5_CEN_p
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-0.2,	RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(50);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_VCEN,		RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(50);
	BPP_ICH5_CEN_p = BPP_ovi->measure_average(25);	
#endif
/*****************************************************************************
 *						BPP and BPS Supply Current				 			 *
 *BPP_IS2_6p2_p was done before BPP_IS2_5p8_p due to the overshoot above 6.2V*
 *when setting BPP to 5.8V. Coming down from 6.2 to 5.8, no undershoot.		 *
 *****************************************************************************/

/************************************************************************************************************
 *					IS2_VBPP_p: Secondary in control for Primary to be switching at 132kHz					*
 *	IS2_VBPP_p is measured in Fosc_post_S function because test condition is for FET switching at 132kHz	*
 *	Since 1.92P silicon require secondary control to be switching at 132kHz, this test will be test for all	*
 *	silicon reivisons inside Fosc_post_S function and datalog at IBP_Supply function.						*
 ************************************************************************************************************/
	//ovi_1->disconnect(VPIN_ch);


//@@ BPP_IS2_6p2_p: Device is switching: Autorestart 
	D_dvi->set_voltage(D_ch, 15.0, 		VOLT_50_RANGE);	// DVI_11_0
	//************************************
	// This test is removed per Shreyas
	//************************************
	//VBPP_Power_Up(ILIM_RED);	
	//BPP_ovi->set_voltage(BPP_ch, 6.2,	RANGE_10_V);	// OVI_1_0
	//wait.delay_10_us(80);
	//BPP_IS2_6p2_p = BPP_ovi->measure_average(100); //!!!Can't stop and meas here. Device autorestart	

	// Dump to file
	if(DEBUG==1)
	{
		float imeas_debug = 0;
		float tDelay = 800e-6; //Delay before BPP_IS2_6p2_p measurement.
		float delay_step = 5;
		char *Title ="\0";
		Title = "cnt	Time	iBPP_IS2_6p2_p";
		for(int i=0; i< 500; i++)
		{
			wait.delay_10_us(delay_step);
			tDelay += delay_step * 10e-6;
			imeas_debug = BPP_ovi->measure_average(100);
			Dump_IS_Data(Title, i, tDelay,	imeas_debug);
		}
		WAVE_NAME = "NoWaveName";
	}

//@@ BPP_IS2_5p8_p: Device is switching 

	VBPP_Power_Up(ILIM_RED);	
	BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init+0.1,	RANGE_10_V);	// OVI_1_0
	delay(1);
	BPP_IS2_VBPP_p = BPP_ovi->measure_average(100);//!!!Can't stop and meas here. Device autorestart		


	//Power Down
	Power_Down_Secondary();
	Power_Down_Primary();
	wait.delay_10_us(50);
	


/****************************************************************************
 *						BPP and BPS Supply Current							*
 ****************************************************************************/
	
	//IS1_S (Not Switching)
	BPS_IS1_nsw_s = gIBPS_nsw;	//This test is done twice.  Once in VBP_Init searching vPlus and VBP_Supply searching vPlus as well

	//////////************************************************************
	//////////** IS2_S (Switching and should be done with SR switching) **
	//////////************************************************************
	////////// Note: This test couldn't be done from Fosc-S because SR pin has to be shorted to see 132kHz.  If SR not shorted, it's 126kHz

	//////////Connect SR pin to 5nf to allow switching
	//pulse.do_pulse();


	//Open_relay(K2);		// disconnect DVI11_0 from Drain
	//Open_relay(K18);	// disconnect DVI11_1 from FW pin
	//Close_relay(K3);	// Connect dvi-11-0 to R1(50ohm),L1(82uH) to Drain
	//delay(4);
	//
	//VBPP_Negative_Cycle();
	//if(1)
	//{
	//	//Vpin (0V)
	//	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	//	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//	//SR require floating for IS2_S test so SR will be switching 
	//	//SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
	//	//SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	//	//SR_dvi2k->open_relay(CONN_FORCE1);
	//	//SR_dvi2k->open_relay(CONN_SENSE1);
	//	REQ_ovi->set_voltage(REQ_ch, 0.0,	RANGE_2_V);	// OVI_1_2	
	//	wait.delay_10_us(5);

	//	

	//	SR_dvi2k->open_relay(CONN_FORCE1);
	//	SR_dvi2k->open_relay(CONN_SENSE1);
	//	Close_relay(K5);//Connect SR to 5nF
	//	delay(2);

	//	Close_relay(K17);
	//	delay(3);

	//	
	//	//ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//This could cause a 1V glitch at BPS for 50us
	//	//wait.delay_10_us(10);

	//	//Vout (0V)
	//	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	//	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
	//	//FB (2V)  pull FB above CVth to force No Switching
	//	//REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	//	//if(LB_Rev >= 5)		REQ_ovi->set_voltage(REQ_ch, 0.9,		RANGE_2_V);	// OVI_1_2	
	//	//else				REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	

	//	//IS (0V)
	//	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	//	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	//	wait.delay_10_us(10);
	//	//BPS (vPlus - 300mV)
	//		// vfinal
	//	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
	//	VBPS_Power_Up(gVBPS_M_Init-0.2);

	//	//Drain (0V/3mA)
	//	D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
	//	D_dvi->set_voltage(D_ch, 0, 		VOLT_50_RANGE);	// DVI_11_0	
	//	//D_dvi->set_voltage(D_ch, 45.0, 		VOLT_50_RANGE);	// DVI_11_0	
	//	wait.delay_10_us(20);

	//	VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_10_V);  
	//	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);

	//	//BPP set 0V
	//	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	//	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2);	// vstart, vstop, vstep	
	//	// Initialize DDD
	//	wait.delay_10_us(100);  	
	//	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	//	ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	//	delay(1);
	//	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	//	wait.delay_10_us(50);

	//	VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
	//	// Close K12 to connect DDD to VPIN
	//	Close_relay(K12);
	//	delay(4);
	//	Force_Vpin_Pulses_5_Times(5.0, 0.0);	
	//	wait.delay_10_us(10);
	//	D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
	//	D_dvi->set_voltage(D_ch, 45.0, 			VOLT_50_RANGE);	// DVI_11_0

	//	//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	//	VBPP_ramp_up(5.0, gVBPP_PV_Init, 50e-3);		
	//	//Drain stays at 0V so BPP signal will be cleaner
	//	dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
	//	wait.delay_10_us(10);
	//	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
	//	wait.delay_10_us(5);

	//	//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
	//	ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-200e-3, RANGE_10_V);
	//	wait.delay_10_us(50);
	//	if(gSiliconRev_P >= 3)
	//	{
	//		BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
	//		VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
	//		wait.delay_10_us(10);
	//	}
	//	else
	//	{
	//		ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+50e-3, RANGE_10_V);
	//		wait.delay_10_us(30);
	//	}
	//	dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
	//	wait.delay_10_us(10);
	//	Connect_InvSyn_IM(Low_Vd_Input);

	//	//BPS_dvi->set_voltage(BPS_ch, 5.0, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	//	//wait.delay_10_us(10);
	//	//FB (1V) force Switching
	//	//REQ_ovi->set_voltage(REQ_ch, 2.0,		RANGE_2_V);	// OVI_1_2	
	//	//wait.delay_10_us(10);
	//	// Open K12 
	//	Open_relay(K12);
	//	VPIN_ovi->connect(1);// Reconnect OVI from UV
	//	wait.delay_10_us(100);  	
	//	ddd_7->ddd_set_hi_level(0.0);		// Will immediately change to this level upon execution
	//	delay(1);
	//}

	//	

	//	ddd_7->ddd_set_hi_level(2);				// Will immediately change to this level upon execution
	//	ddd_7->ddd_set_lo_level(1);				// Will immediately change to this level upon execution
	//	delay(1);

	//	BPS_dvi->set_voltage(BPS_ch, 5.0, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	//	wait.delay_10_us(10);

	//	ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	//	wait.delay_10_us(5);
	//
	//
	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//wait.delay_10_us(10);
	//ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	//wait.delay_10_us(30);
	//BPS_IS2_sw_s = BPS_dvi->measure_average(25); //expect ~10mA with SR switching.
	//gIBPS_sw = BPS_IS2_sw_s;
	//pulse.do_pulse();
	//wait.delay_10_us(100);





//Original Code
pulse.do_pulse();

	Open_relay(K2);		// disconnect DVI11_0 from Drain
	Open_relay(K18);	// disconnect DVI11_1 from FW pin
	Close_relay(K3);	// Connect dvi-11-0 to R1(50ohm),L1(82uH) to Drain
	delay(4);
	
	VBPP_Negative_Cycle();
	if(1)
	{
		//Vpin (0V)
		VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
		VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
		//SR require floating for IS2_S test so SR will be switching 
		//SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
		//SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		//SR_dvi2k->open_relay(CONN_FORCE1);
		//SR_dvi2k->open_relay(CONN_SENSE1);
		//Drain (0V/3mA)
		D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
		D_dvi->set_voltage(D_ch, 0, 		VOLT_50_RANGE);	// DVI_11_0	
		//D_dvi->set_voltage(D_ch, 45.0, 		VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(20);
		

		VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_10_V);  
		VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);

		//BPP set 0V
		BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
		VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2);	// vstart, vstop, vstep	
		// Initialize DDD
		wait.delay_10_us(100);  	
		ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
		delay(1);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(50);

		VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
		// Close K12 to connect DDD to VPIN
		Close_relay(K12);
		delay(4);
		Force_Vpin_Pulses_5_Times(5.0, 0.0);	
		wait.delay_10_us(10);

		D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
		D_dvi->set_voltage(D_ch, 45.0, 			VOLT_50_RANGE);	// DVI_11_0
		wait.delay_10_us(50);

		Connect_InvSyn_IM(Low_Vd_Input);// Connect the Sync Circuit while the device is quiet to help with the glitch on drain.
										// This glitch was much noticible and much worse on Turret setup.

		//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
		VBPP_ramp_up(5.0, gVBPP_PV_Init, 50e-3);		
		//Drain stays at 0V so BPP signal will be cleaner
		//dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
		//wait.delay_10_us(10);
		wait.delay_10_us(50);
		VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(5);

		//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
		ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-200e-3, RANGE_10_V);
		wait.delay_10_us(50);
		if(gSiliconRev_P >= 3)
		{
			BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
			VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
			wait.delay_10_us(10);
		}
		else
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+50e-3, RANGE_10_V);
			wait.delay_10_us(30);
		}
		/*dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
		wait.delay_10_us(10);*/
		// Open K12 
		Open_relay(K12);
		VPIN_ovi->connect(1);// Reconnect OVI from UV
		ddd_7->ddd_set_hi_level(0.0);		// Will immediately change to this level upon execution
		wait.delay_10_us(100);
		
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);
		Close_relay(K5);//Connect SR to 5nF
		delay(2);

		//ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//This could cause a 1V glitch at BPS for 50us
		//wait.delay_10_us(10);

		//Vout (0V)
		VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
		//FB (2V)  pull FB above CVth to force No Switching
		REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
		//REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	

		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 300mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
		//VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal
		VBPS_Power_Up(gVBPS_P_Init-0.3);	
		if(LB_Rev >= 5)		ddd_7->ddd_set_hi_level(1.7);
		else				ddd_7->ddd_set_hi_level(gCVth_15pct_Higher);	
		ddd_7->ddd_set_lo_level(0.9);
		wait.delay_10_us(100);
		
		ddd_7->ddd_run_pattern(Low_FB_pat_start, Low_FB_pat_stop);
		wait.delay_10_us(10);
		VO_dvi->set_voltage(VO_ch, 3.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
		wait.delay_10_us(10);
		 
		Close_relay(K17);	//FB   to   DDD
			//Must leave 2ms here for the SSS 70pct ILIM-P to capture at least 40 cycles (1/25kHz =~40us. 40x40us = 1600us = 1.6ms)
		delay(5);
	//Gage_Start_Capture(  );
		BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
		wait.delay_10_us(5);
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);
		//BPS_dvi->set_voltage(BPS_ch, 5, 	VOLT_10_RANGE);
	// Secondary vBPS_plus	//Connect REQ pin to DDD to run 100KHz pulses
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(Low_FB_pat_start, Low_FB_pat_stop);
		wait.delay_10_us(10);
		
		ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
		wait.delay_10_us(30);
		BPS_IS2_sw_s = BPS_dvi->measure_average(25); //expect ~10mA with SR switching.
		gIBPS_sw = BPS_IS2_sw_s;
		pulse.do_pulse();
		wait.delay_10_us(100);
		
		
	}


	//ddd_7->ddd_set_hi_level(2);				// Will immediately change to this level upon execution
	//ddd_7->ddd_set_lo_level(1);				// Will immediately change to this level upon execution
	//delay(1);

	//ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	//wait.delay_10_us(5);

	//Close_relay(K17);
	//delay(4);

	/*ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	wait.delay_10_us(5);

	ddd_7->ddd_run_pattern(High_pat_FB_start,High_pat_FB_stop);
	wait.delay_10_us(5);*/

	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//wait.delay_10_us(5);
	//ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	//wait.delay_10_us(30);
	//BPS_IS2_sw_s = BPS_dvi->measure_average(25); //expect ~10mA with SR switching.
	//gIBPS_sw = BPS_IS2_sw_s;
	//pulse.do_pulse();
	//wait.delay_10_us(100);
	
	//Power down
 	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	wait.delay_10_us(100);                           // HL do not remove delay.  Else, it will corrupt the DDD pattern.
	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_2_V);	// OVI_1_2
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	wait.delay_10_us(5);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);	
	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_2_RANGE);	// DVI_9_1
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	wait.delay_10_us(5);
	Open_relay(K17);
	delay(4);

	//Removed from MINNO-S, Done in MINNO Master
	// Added Delta(VO-VBPS)
	//VBPS_ramp_up(0, gVBPS_P_Init+50e-3, 50e-3);			// vfinal
	//BPS_dvi->set_voltage(BPS_ch, 4.0, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	//wait.delay_10_us(20);

	//VO_dvi->set_voltage(VO_ch, 5.2, 		VOLT_10_RANGE);	// DVI_9_0
	//VO_dvi->set_current(VO_ch, 5e-3,		RANGE_300_MA);
	//wait.delay_10_us(20);
	//VO_dvi->set_meas_mode(VO_ch,			DVI_MEASURE_VOLTAGE);
	//wait.delay_10_us(20);
	//VO_S = VO_dvi->measure_average(5);
	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_VOLTAGE);
	//wait.delay_10_us(20);
	//VBPS_S = BPS_dvi->measure_average(5);
	//Delta_VO_minus_VBPS_S = (VO_S - VBPS_S);

	//Power Down
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	delay(1);


	// Power down
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0	
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, 	RANGE_10_V);	// OVI_1_1
	VPIN_ovi->connect(VPIN_ch);								// OVI_1_1
 	tmu_6->open_relay(TMU_HIZ_DUT1);	// Disconnect TMU HIZ from Drain 
	Open_relay(K3);
	Open_relay(K12);	// DDD7_1	to Vpin(UV)	pin
	delay(1);
	REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_2_V);	// OVI_1_2	
	delay(1);

	//Datalog
	// Charge Current
	PiDatalog(func, A_BPP_ICH1_0V_p,			BPP_ICH1_0V_p,			set_fail_bin,	POWER_MILLI);	
	//PiDatalog(func, A_BPS_ICH1_3V_s,			BPS_ICH1_3V_s,			set_fail_bin,	POWER_MILLI);	
	PiDatalog(func, A_BPP_ICH2_4V_p,			BPP_ICH2_4V_p,			set_fail_bin,	POWER_MILLI);	
	//PiDatalog(func, A_BPS_ICH2_4V_s,			BPS_ICH2_4V_s,			set_fail_bin,	POWER_MILLI);	
	//PiDatalog(func, A_BPS_ICH2_4V_FW11V_s,		BPS_ICH2_4V_FW11V_s,	set_fail_bin,	POWER_MILLI);
	//PiDatalog(func, A_R_SRclamp_S,				Rsr_clamp,				set_fail_bin,	POWER_UNIT);

	PiDatalog(func, A_BPP_ICH3_CEN_p,			BPP_ICH3_CEN_p,				set_fail_bin,	POWER_MILLI);	
//	PiDatalog(func, A_BPS_ICH3_VO_5v_S,			BPS_ICH3_VO_5v_S,			set_fail_bin,	POWER_MILLI); // Added per Sheng 05/16/14  HQL
	//PiDatalog(func, A_BPS_ICH3_4V_VO_5v_S,		BPS_ICH3_4V_VO_5v_S,		set_fail_bin,	POWER_MILLI); 
	//PiDatalog(func, A_BPS_ICH3_4V_VO20v_S,		BPS_ICH3_4V_VO20v_S,		set_fail_bin,	POWER_MILLI);
	//PiDatalog(func, A_Delta_VO_minus_VBPS_S,	Delta_VO_minus_VBPS_S,		set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_BPP_ICH4_D_p,		BPP_ICH4_D_p,		set_fail_bin,	POWER_MILLI);	
	PiDatalog(func, A_BPP_ICH5_CEN_p,	BPP_ICH5_CEN_p,		set_fail_bin,	POWER_MILLI);	

	PiDatalog(func, A_BPS_IS1_nsw_s,	BPS_IS1_nsw_s,		set_fail_bin,	POWER_MICRO);	

	// Move the BPS_sw test to Fosc_Post-S func to save test time as well for better measurement since Freq needs to be
	// at 132kHz... In this func, when we do the Power, the device switches at Low Freq because of Low Load on Primary.
//	PiDatalog(func, A_BPS_IS2_sw_s,		BPS_IS2_sw_s,		set_fail_bin,	POWER_MILLI);	
	PiDatalog(func, A_BPS_IS2_sw_s,		gIBPS_sw,			set_fail_bin,	POWER_MILLI);	
	PiDatalog(func, A_BPP_IS1_nsw_s,	gBPP_IS1_VBPP_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_BPP_IS2_sw_s,		gBPP_IS2_VBPP_p,	set_fail_bin,	POWER_MILLI);	


	if(gDEBUG)
	printf("Function IBP_Supply Done\n");

}
