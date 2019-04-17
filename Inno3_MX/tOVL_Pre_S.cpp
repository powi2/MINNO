//==============================================================================
// tOVL_Pre_S.cpp (User function)
// 
//    void tOVL_Pre_S_user_init(test_function& func)
//    void tOVL_Pre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "tOVL_Pre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void tOVL_Pre_S_user_init(test_function& func)
{
	tOVL_Pre_S_params *ours;
    ours = (tOVL_Pre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void tOVL_Pre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    tOVL_Pre_S_params *ours;
    ours = (tOVL_Pre_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "tOVL_Pre_S";

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_tOVL_Pre_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_GRR == 0 && (OPCODE != 4200 || TRIM_ENABLE == 0))
		return;


	float tOVL_Pt_S=0,
		  tmeas=0;

	bool  HS_PASS_pt=true;

	// Setup Digitizer //
	float	ChB_vrng=0.0;
	int		i = 0, vrng_b	=0.0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	// Setup Digitizer //
//	float	ChB_vrng=0.0;
//	int		vrng_b	=0.0;
	Gage_pretrig_samples=1024;	//Set up the Pre_Trigger sample to be 1024 for better trigger point.
	Gage_init() ;
	//SAMPLE_SIZE = GAGE_POST_4K;
	SAMPLE_SIZE = GAGE_POST_256K;
	vrng_b = GAGE_PM_10_V;
	ChB_vrng = 5.6;
	//	Set up Buffer Clamp
	BC_ovi->set_current(BC_ch, 30e-3,		RANGE_30_MA);
	BC_ovi->set_voltage(BC_ch, (ChB_vrng-0.6),VOLT_10_RANGE);	// OVI_1_3 Account for one diode drop
	delay(1);

	// Channel B setup //
	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,SAMPLE_SIZE); 
	//delay(2);

	gage_input_control_xp (GAGE_CHAN_B,		// channel
			GAGE_INPUT_ENABLE,					// enable / disable
			GAGE_DC,							// coupling
			vrng_b|GAGE_1_MOHM_INPUT);			// range, impedance
	//delay(2);
	
	gage_trigger_control_xp (GAGE_CHAN_B,		// trigger source
			GAGE_DC,							// coupling for ext trig
			vrng_b,								// range for CHA trigger
			GAGE_NEGATIVE,						// slope
//			4.0,								// 1.0V trigger level 
			4.5,								// 1.0V trigger level 
	   		SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE
	//delay(2);

	/****************************************************************************
	 *					tOVL or fOVL (Fosc_Overload)							*
	 ****************************************************************************/
	Close_relay(K3);
	VBPP_Negative_Cycle();
	delay(4);

//Setup Vpin for digital clocking
	//ovi_1->disconnect(OVI_CHANNEL_1);	
	//wait.delay_10_us(100); 
	//// Initialize DDD
	//ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	//ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
	//delay(1);
	//ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	//wait.delay_10_us(10);
	//Close_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
	//delay(4);

//Setup FB to connect to DDD
	REQ_ovi->set_voltage(REQ_ch, 0.0,	RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(5);

	Close_relay(K17);	
	Open_relay(K27);
//Have InvSync circuit ready for communication
	
	Close_relay(K5);//Connect SR to 5nF
	//delay(5);
	delay(2);
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	//Have InvSync circuit ready for communication
	Connect_InvSyn_IM_New(Low_Vd_Input);
	//Primary TM5 bypass Wait and Listen power up
	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);

//Setup to have Secondary power up to VBPS minus
	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)

	//if(1)//g_TurretCB)
	//{
	//	//HL needs to change to 20mA or Turret CB won't work.
	//	SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
	//	SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);	// DVI_21_1
	//	delay(2);
	//	mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
	//	delay(2);
	//}
	//else
	//{
	//	SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
	//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	//	dvi_13->close_relay(BUS_SENSE1);
	//	dvi_13->close_relay(BUS_FORCE1);
	//	mux_14->close_relay(MUX_3_BUS3);
	//	delay(5);
	//}

	//Vout (Will charge BPS if @5V)
	VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
	////FB (1V)
	//REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	//REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	

	//Setup FB High/Low switching thresholds
	//ddd_7->ddd_set_hi_level(gREQ_V_Req);				// Will immediately change to this level upon execution
	//ddd_7->ddd_set_lo_level(gREQ_V_Idle);				// Will immediately change to this level upon execution
	//delay(1);

	//ddd_7->ddd_run_pattern(FB_tOVL_start, FB_tOVL_stop);
	//wait.delay_10_us(5);
	//ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	//wait.delay_10_us(5);

	//Close_relay(K17);
	//delay(4);

	ddd_7->ddd_set_hi_level(gREQ_V_Req);				// Will immediately change to this level upon execution
	ddd_7->ddd_set_lo_level(gREQ_V_Idle);				// Will immediately change to this level upon execution
	wait.delay_10_us(10);

	//ddd_7->ddd_run_pattern(FB_tOVL_start, FB_tOVL_stop);
	//wait.delay_10_us(5);
	ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	wait.delay_10_us(5);

	//IS (0V)
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	wait.delay_10_us(10);
	//BPS (vPlus - 200mV)
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	
	VBPS_Power_Up(gVBPS_M_Init-0.1);			// vfinal  

	//Bring BPS to vPlus (Note: if BPS not power up fully, Vpin will be switching at Fosc Modulation)
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	BPS_dvi->set_voltage(BPS_ch, 5, 	VOLT_10_RANGE);	// Secondary vBPS_plus

	//Bring Vpin OVI back
	/*ovi_1->connect(OVI_CHANNEL_1);	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);  
	VPIN_ovi->set_current(VPIN_ch, 1e-3,		RANGE_30_MA);  */
	// Connect Vpin to RDSon buffer circuit. //
	tmu_6->close_relay(TMU_EXT_DRV2);
	wait.delay_10_us(100);

	//Setup to measure tOVL from Vpin
	Open_relay(K12);	//disconnect DDD7_1	from Vpin(UV)	pin
	Close_relay(KC5);	//VPIN_OVI to 15Kohm to UV pin
	Close_relay(KC6);	//UV pin to 330ohm to TMU_HIZ_DUT3
	delay(5);
	VPIN_ovi->set_voltage(VPIN_ch, 5.0,			RANGE_10_V);  
	wait.delay_10_us(100); 

	ddd_7->ddd_run_pattern(High_pat_FB_start,High_pat_FB_stop);
	wait.delay_10_us(50);


	/*ddd_7->ddd_run_pattern(FB_tOVL_start,FB_tOVL_stop);
	wait.delay_10_us(5);*/

	Gage_Start_Capture(  );

	//Initiate the first pattern of tOVL to get rid of all of the noise before tmu arm()
	//ddd_7->ddd_run_pattern(FB_tOVL_start,FB_tOVL_stop);
	//wait.delay_10_us(25);	//HOT debug

	i = 0;
	while(i<10)
	{
		ddd_7->ddd_run_pattern(FB_tOVL_start,FB_tOVL_stop);
		wait.delay_10_us(5);	//used to be 25
		i++;
	}

	Gage_Wait_For_Capture_Complete();

	//HL removed this section because of hot switching on Vpin. 06/08/17.
	//Disable Vpin
	//VPIN_ovi->set_voltage(VPIN_ch, 5.0,			RANGE_10_V);  
	//wait.delay_10_us(10);

	//Open_relay(K17);
	//Open_relay(KC5);	//VPIN_OVI to 15Kohm to UV pin
	//Open_relay(KC6);	//UV pin to 330ohm to TMU_HIZ_DUT3
	//tmu_6->open_relay(TMU_HIZ_DUT3);	
	//tmu_6->open_relay(TMU_EXT_DRV2);

	// Power down
	//Disconnect_InvSyn_IM();  //HL Do not disconnect Inv ckt before powerdown other resources.
	Power_Down_Everything();
	Disconnect_InvSyn_IM();
	Open_All_Relays();
	tmu_6->open_relay(TMU_HIZ_DUT3);	

	//DEBUG=1;
	// Search result //

	if(g_TurretCB)
	{
		Gage_Find_tOVL_Turret(&tOVL_Pt_S);
	}
	else
	{
		Gage_Find_tOVL(&tOVL_Pt_S);
	}
	//DEBUG=0;
	g_tOVL_Pt = tOVL_Pt_S;
	Gage_pretrig_samples=64;	// Reset the Pre_Trigger Samples back to defaul at 64.
	Gage_init() ;

	//Datalog
	PiDatalog(func, A_tOVL_Pt_S,		tOVL_Pt_S,			set_fail_bin,	POWER_MICRO);
	////PiDatalog(func, A_HS_PASS_pt,		HS_PASS_pt,			set_fail_bin,	POWER_UNIT);

}
