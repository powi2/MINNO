//==============================================================================
// BV_Drain.cpp (User function)
// 
//    void BV_Drain_user_init(test_function& func)
//    void BV_Drain(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "BV_Drain.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void BV_Drain_user_init(test_function& func)
{
	BV_Drain_params *ours;
    ours = (BV_Drain_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void BV_Drain(test_function& func)
{
    // The two lines below must be the first two in the function.
    BV_Drain_params *ours;
    ours = (BV_Drain_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "BV_Drain";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_BV_Drain,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	//if (AbortTest || MOSFET_SIZE==8)	//The 1st SilRev of sizex8 fail BV
	if (AbortTest)
		return;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	double	ifrc_str_init=0,
			ifrc_str=0,
			ifrc=0;
	int		INIT_STRESS_FLAG =0;
		

	float	vfrc_init=0,
			//bvdss_str1_init=0,
			//bvdss_str2_init=0,
			vfrc=0,
			//bvdss_str1=0,
			//bvdss_str2=0,
			BVDSS_STR1=0,
			BVDSS_STR2=0,
			BVDSS_ISTR=0,
			BVDSS_WALK=0,
			BVD_100UA=0,
			//BVD_High=0,
			//BVD_Low=0,
			IDS_BVD_10V=0,
			IDS_80BVD=0,
			IDS_325V=0,
			IDS_150V=0,
			IDS_30V=0;
			//IDS_50V_TAPoff=0,		// Done with DVI for bettter accuracy
			//ifrc_FW_str=0,
			//ifrc_FW=0,
			//vfrc_FW=0,
			//bvdss_FW_str1=0,
			//bvdss_FW_str2=0,
			//BVDSS_FW_ISTR=0,
			//BVDSS_FW_STR=0,
			//BVDSS_FW_WALK=0,
			//BVD_FW_25UA=0,
			//IDS_FW_25UA=0;
	float	Imeas=0.0, ton =0.0, toff =0.0;
	float   j = 0.0;
	//float	tHS_BV =0.0;
	int		BVD_stress_time =0;
	bool	LowBV_PowerDown =0;


	//gHandShake_PASS = 0;

// Instrument protection
	ovi_1->disconnect(0); //BPP.  Do not use OVI for BV testing.
	ovi_1->disconnect(1); //UV 
	ovi_1->disconnect(2); //FB.   Why not ground FB through MUX14_1_4 & MUX14_1_2 to protect OVI1_1. ???
	ovi_1->disconnect(5); //NC.   Need to add relay to isolate OVI1_5 from NC.
	tmu_6->open_relay(TMU_HIZ_DUT1);			// protect TMU
	tmu_6->open_relay(TMU_HIZ_DUT2);			// protect TMU
	tmu_6->open_relay(TMU_CHAN_A_DUT2);			// protect TMU

/****************************************************************************
 *						High Voltage MOSFET BVD								*
 ****************************************************************************/
	//Short UV pin to GND by MUX (UV PIN MUST BE GROUNDED IN ORDER FOR DEVICE TO POWER-UP PROPERLY)
	//We do not want to burn any OVI card so risk mux card here or connect the un-used relay of the K12B to GND for HW mod.
	mux_14->close_relay(MUX_BANK_8_1);	
	mux_14->close_relay(MUX_1_1);
	mux_14->close_relay(MUX_1_4); //Ground FB thru Mux
	mux_14->close_relay(MUX_1_2);


	Close_relay(K4);		// Connect HVS to Drain
	Close_relay(K11);		// Connect BPP to DVI. Avoid using OVI, which can be damaged by 
							// avalanche breakdown from bad units. 
	delay(4);
	if (OPCODE==4300 || OPCODE==4500)
	{
		ifrc_str = 300e-6;						// stress current clamp at hot
		ifrc = 100e-6;							// current clamp at hot
		vfrc = gBVD_Hot;			
	}
	else if (OPCODE==4400)
	{
		ifrc_str = scaled_ifrc;					// stress current clamp at cold
		ifrc = 100e-6;							// current clamp at cold	// Per Shreyas 11/21/16
		vfrc = 600;			
	}
	else
	{
		ifrc_str = scaled_ifrc;					// stress current clamp at room per device
		ifrc = 100e-6;							// current clamp at room
		vfrc = gBVD_Room;			
	}

	//Important Note: Add condition for char programs later,clamp voltage is much higher 

	BVD_stress_time = ours->BVD_stress_time * 1000;	// In ms

	// Power up from 0V 6.3V->4.4V->6.8V above Vshunt to stop device from switching
	//HL changed back to 5mA before ramping up BPP pin.
	BPP_DVI->set_current(BPP_ch, 5e-3,					RANGE_30_MA);  //used to be at 5mA
	//BPP_DVI->set_current(BPP_ch, 30e-3,					RANGE_30_MA);		//require > Ishunt to hit Vshunt_BPP  zcx 12/28/16
	BPP_DVI->set_voltage(BPP_ch, 0.0, 					VOLT_10_RANGE); 	wait.delay_10_us(10);	// DVI_11_0 
	BPP_DVI->set_voltage(BPP_ch, 3.0, 					VOLT_10_RANGE); 	wait.delay_10_us(50);
//	BPP_DVI->set_voltage(BPP_ch, gVshunt_BPP-50e-3, 	VOLT_10_RANGE); 	wait.delay_10_us(10);	
//	BPP_DVI->set_voltage(BPP_ch, 4.4, 					VOLT_10_RANGE); 	wait.delay_10_us(10);
	int i_set = 0;
	j = 3.0;
	while(j < gVshunt_BPP)
	{
		if(j > 5.4 && i_set < 1)
		{
			BPP_DVI->set_current(BPP_ch, 18e-3,					RANGE_30_MA);  //used to be at 5mA
			i_set = 1;
		}
		BPP_DVI->set_voltage(BPP_ch, j,	VOLT_10_RANGE); 	wait.delay_10_us(10);	
		j = j + 0.1;
	}
	BPP_DVI->set_voltage(BPP_ch, gVshunt_BPP+100e-6,	VOLT_10_RANGE); 	wait.delay_10_us(10);	

	//Randy's recommendation to use 18mA to prevent the DUT going into Shutdown mode.
	BPP_DVI->set_current(BPP_ch, 18e-3,					RANGE_30_MA);		//require > Ishunt to hit Vshunt_BPP  zcx 12/28/16
	wait.delay_10_us(500);	


//	hvs_15->set_current		(ifrc_str,	RANGE_1_MA);
	hvs_15->set_current		(100e-9,	RANGE_1_MA);
	hvs_15->set_voltage		(0.0,		RANGE_1_KV);
	hvs_15->set_meas_mode	(HVS_MEASURE_CURRENT);				
	delay(1);
			
	hvs_15->close_relay(HVS_NEG_FORCE);		// NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->close_relay(HVS_SHORT_NEG_FS);	
	hvs_15->close_relay(HVS_GND_NEG_SENSE);	
	hvs_15->close_relay(HVS_SHORT_POS_FS);
	hvs_15->close_relay(HVS_FORCE_POS);		// POS_FORCE (J6,B9) to drain	
	wait.delay_10_us(250);	

if(OPCODE==4200)//Stress and walk only at room
{
//*** Production Stress the High Voltage MOSFET STARTS ***
	//hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
	hvs_15->set_meas_mode(HVS_MEASURE_VOLTAGE);	
	hvs_15->set_current(ifrc_str,	RANGE_1_MA);
	hvs_15->set_voltage(vfrc,		RANGE_1_KV);	
	delay(15);					// Give HVS time for the voltage to come up	(DOES THIS REALLY NEEDED???  ZCX)
								// Some testers require 10ms to come up all the way
								// HL Turret CB requires at least 15ms.
	//////////

	//Measure ISTR
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);	
	delay(5);
	BVDSS_ISTR = hvs_15->measure_average(5);// measure avalanche current

	//Measure BVDSS at ISTR before WALK
	hvs_15->set_meas_mode(HVS_MEASURE_VOLTAGE); 
	delay(5);
	BVDSS_STR1 = hvs_15->measure_average(5);		// measure BVD @ stress				
	BVDSS_STR1 = BVDSS_STR1 - BVDSS_ISTR*47e3;		// subtract 47k vdrop

	//Prevent bad device from damaging tester.  Go to LowBV Powerdown
	if(BVDSS_STR1 < 450)
	{
		LowBV_PowerDown = true;
		goto Run_LowBV_PowerDown;
	}

	delay(BVD_stress_time);	// Make it a variable to PE for different stress experiment. Default is 20ms for production.
	
	BVDSS_STR2 = hvs_15->measure_average(5);
	BVDSS_STR2 = BVDSS_STR2 - BVDSS_ISTR*47e3;		// subtract 47k vdrop
	BVDSS_WALK = BVDSS_STR2 - BVDSS_STR1;									// BVDSS:WALK
}
//*** Production Stress the High Voltage MOSFET ENDS ***

	//***	After stress reduce current or at hot leave it the same
	//if(ifrc<=100e-6)	hvs_15->set_current(ifrc, RANGE_100_UA);		// 100uA or 300uA at hot 			
	//else				hvs_15->set_current(ifrc, RANGE_1_MA);			// 100uA or 300uA at hot 			
	
	hvs_15->set_current(100e-6, RANGE_1_MA);//New DLM stress conditions 

	//hvs_15->set_current(ifrc, RANGE_100_UA);		// 100uA or 300uA at hot 			
	//hvs_15->set_current(ifrc, RANGE_1_MA);			// 100uA or 300uA at hot 
	
	if((OPCODE==4300)||(OPCODE==4500)||(OPCODE==4501))//Hot,REL,Production programs measures BVD_100UA (clamp set to limit + 5V), need to add production condition later
		hvs_15->set_voltage(vfrc+5,		RANGE_1_KV);
	else if(OPCODE==4400)//Temporary add this condition for cold
		hvs_15->set_voltage(vfrc,		RANGE_1_KV);

	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
	delay(5);
	Imeas = hvs_15->measure_average(5);				// measure avalanche current

	hvs_15->set_meas_mode(HVS_MEASURE_VOLTAGE); 
	delay(10); //KJ, As per new stress conditions, 15 ms delay before calculate BV@(100uA)
	//** BVD_100UA
	BVD_100UA = hvs_15->measure_average(5);
	BVD_100UA -= Imeas * 47e3;						// subtract 47k vdrop 

	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
	delay(5); //HL changed from 2ms to 5ms.
	
	//** BVD-10V
	hvs_15->set_voltage(BVD_100UA - 10, RANGE_1_KV); 
	delay(5); //HL changed from 2ms to 5ms
	IDS_BVD_10V = hvs_15->measure_average(5);		// IDSS:BVD-10V

	//** 80%BVD
	hvs_15->set_voltage(BVD_100UA * 0.8 ,RANGE_1_KV);
	delay(5);
	IDS_80BVD = hvs_15->measure_average(10);		// IDSS:80%BVD 78.7ms
 
	if(OPCODE==4200)// Leakage current at 325V only at room
	{
		//** 325V BVD
		hvs_15->set_voltage(325 ,RANGE_1_KV);
		delay(5);
		IDS_325V = hvs_15->measure_average(10);	// IDSS:325 BVD
	}

	//** 150V
	hvs_15->set_voltage(150, RANGE_1_KV); 
	delay(5);
	IDS_150V = hvs_15->measure_average(10);			// IDSS:150V 88.5ms
	
	if(OPCODE==4200)// Leakage current at 30V only at room
	{
		//** 30V
		//hvs_15->set_current(ifrc, RANGE_100_UA);
		hvs_15->set_voltage(30, RANGE_1_KV); 
		delay(15);
		IDS_30V = hvs_15->measure_average(10);			// IDSS:30V 98.7ms
	}

	// Power down HVS before connecting it to FW pin
	hvs_15->set_voltage(0.0, RANGE_1_KV);	
	delay(5);
	BPP_DVI->set_voltage(BPP_ch, 0.0, 		VOLT_10_RANGE); 	// DVI_11_0 
	BPP_DVI->set_current(BPP_ch, 5e-3,					RANGE_30_MA); //HL changed BPP current back to 5mA.

	Open_relay(K4);			// Disconnect HVS from Drain
	Open_relay(K11);		// Disconnect BPP from DVI

	ovi_1->connect(0);
	ovi_1->connect(1);
	ovi_1->connect(2);

	hvs_15->open_relay(HVS_NEG_FORCE);		// NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->open_relay(HVS_SHORT_NEG_FS);	
	hvs_15->open_relay(HVS_GND_NEG_SENSE);	
	hvs_15->open_relay(HVS_SHORT_POS_FS);
	hvs_15->open_relay(HVS_FORCE_POS);		// POS_FORCE (J6,B9) to drain	
	delay(2);

///////****************************************************************************
////// *						750V MOSFET: IDS:50V_TAPoff							*
////// * NOTE: Measure with DVI to get best accuracy								*
////// ****************************************************************************/
//////	Close_relay(K2);
//////	delay(2);
//////	// Power up from 0V 6.3V->4.4V->6.8V to stop device from switching
//////	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);
//////	BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		RANGE_10_V); 	wait.delay_10_us(10);
//////// Keep initial BPP voltage low. Bandgap needs time to power up properly before VBPP raise up too high.
//////// Problem gets worse at hot temp (125C). 1.8 Primary silicon needs more delay for proper power up.
//////	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 6.3, 0.5);
//////	BPP_ovi->set_voltage(BPP_ch, 4.4, 		RANGE_10_V); 	wait.delay_10_us(10);	
//////	BPP_ovi->set_voltage(BPP_ch, gVshunt_BPP, 		RANGE_10_V); 	wait.delay_10_us(10);	// Above Vshunt to stop device from switching
//////
//////	D_dvi->set_voltage(D_ch, 50.0, 			VOLT_50_RANGE);	// DVI_11_0
//////	D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
//////	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_CURRENT);
//////	wait.delay_10_us(50);									// Wait for Drain to charge up to 50V
//////
//////	D_dvi->set_current(D_ch, 30e-6,		RANGE_30_UA);		// Meas current in a lower range. DVI voltage drops to 48V at this range
//////	wait.delay_10_us(50);	
//////	IDS_50V_TAPoff = D_dvi->measure_average(5);
//////
//////	// Power down
//////	D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
//////	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_2_RANGE);	// DVI_11_0
//////	wait.delay_10_us(10);
//////	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
//////	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		RANGE_10_V); // DVI_9_1 
//////	Open_relay(K2);
//////	hvs_15->init();	
//////	delay(2);

	if (BVD_100UA < 150.0)
		AbortTest =true;		// Don't continue on if BVD is too low


Run_LowBV_PowerDown:

if(LowBV_PowerDown == true)
{
	hvs_15->set_voltage(0.0, RANGE_1_KV);
	wait.delay_10_us(200);

	// Power down HVS before connecting it to FW pin
	hvs_15->set_voltage(0.0, RANGE_1_KV);	
	delay(2);
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_DVI->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		VOLT_10_RANGE); 	// DVI_11_0 	

	Open_relay(K4);			// Disconnect HVS from Drain
	Open_relay(K11);		// Disconnect BPP from DVI

	hvs_15->open_relay(HVS_NEG_FORCE);		// NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->open_relay(HVS_SHORT_NEG_FS);	
	hvs_15->open_relay(HVS_GND_NEG_SENSE);	
	hvs_15->open_relay(HVS_SHORT_POS_FS);
	hvs_15->open_relay(HVS_FORCE_POS);		// POS_FORCE (J6,B9) to drain	
	delay(2);

	// Power down
	D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_2_RANGE);	// DVI_11_0
	wait.delay_10_us(10);
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		RANGE_10_V); // DVI_9_1 

	Open_relay(K2);
	hvs_15->init();	
	delay(1);
	ovi_1->connect(0);
	ovi_1->connect(1);
	ovi_1->connect(2);
	delay(1);

	AbortTest = true;
}

	//Disconnect UV pin from GND by MUX
	mux_14->open_relay(MUX_BANK_8_1);	
	mux_14->open_relay(MUX_1_1);
	delay(1);

// Datalog
	if(OPCODE==4200)
	{
		PiDatalog(func, A_BVDSS_ISTR,		BVDSS_ISTR,		 set_fail_bin,	POWER_MICRO);		
		PiDatalog(func, A_BVDSS_STR1,		BVDSS_STR1,		 set_fail_bin,	POWER_UNIT);		
		PiDatalog(func, A_BVDSS_STR2,		BVDSS_STR2,		 set_fail_bin,	POWER_UNIT);		
		PiDatalog(func, A_BVDSS_WALK,		BVDSS_WALK,		 set_fail_bin,	POWER_UNIT);	
	}
		PiDatalog(func, A_BVD_100UA,		BVD_100UA,		 set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_IDS_BVD_10V,		IDS_BVD_10V,	 set_fail_bin,	POWER_MICRO);		
		PiDatalog(func, A_IDS_80BVD,		IDS_80BVD,		 set_fail_bin,	POWER_MICRO);	
	if(OPCODE==4200)
		PiDatalog(func, A_IDS_325V,			IDS_325V,		 set_fail_bin,	POWER_MICRO);	
		PiDatalog(func, A_IDS_150V,			IDS_150V,		 set_fail_bin,	POWER_MICRO);
	if(OPCODE==4200)
		PiDatalog(func, A_IDS_30V,			IDS_30V,		 set_fail_bin,	POWER_MICRO);	
 

	if(gDEBUG)
		printf("Function_BV_Drain_Done\n");

}
