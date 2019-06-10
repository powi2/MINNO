//==============================================================================
// BV_Drain_900V.cpp (User function)
// 
//    void BV_Drain_900V_user_init(test_function& func)
//    void BV_Drain_900V(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "BV_Drain_900V.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void BV_Drain_900V_user_init(test_function& func)
{
	BV_Drain_900V_params *ours;
    ours = (BV_Drain_900V_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void BV_Drain_900V(test_function& func)
{
    // The two lines below must be the first two in the function.
    BV_Drain_900V_params *ours;
    ours = (BV_Drain_900V_params *)func.params;
	Func_name = "BV_Drain";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_BV_Drain_900V,		gFuncNum,		ours->fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (OPCODE != 4200)
		return;

	// 900V only on untrimmed parts
	if ( TRIM_ENABLE == 0 || gTrimmed_Device	== 1 )
		return;

	//disable900V = 1;
	if (disable900V == 1)
	{
		MessageBox(NULL,"HVS19 IS REQUIRED FOR OPCODE4200","SETUP ERROR", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		return;
	}

	double	ifrc_str_init=0,
			ifrc_str=0,
			ifrc=0;
	int		INIT_STRESS_FLAG =0;
	int		Stress_time = 0;
		

	float	vfrc_init=0,
			vfrc=0,
			BVDSS_STR1=0,
			BVDSS_STR2=0,
			BVDSS_STR1_15=0,
			BVDSS_STR1_19=0,
			BVDSS_STR2_15=0,
			BVDSS_STR2_19=0,
			BVDSS_ISTR=0,
			BVDSS_WALK=0,
			BVD_100UA=0,
			BVD_100UA_15=0,
			BVD_100UA_19=0,
			IDS_BVD_10V=0,
			IDS_80BVD=0,
			IDS_650V=0,
			IDS_325V=0,
			IDS_150V=0,
			IDS_30V=0;

	float	Imeas=0.0, ton =0.0, toff =0.0;
	int		BVD_stress_time =0;
	bool	LowBV_PowerDown =0;

	float	iAF_Zf = 0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	//////// First check Zf bit trimming to see if it was already trimmed.
	//////ovi_1->disconnect(OVI_CHANNEL_1);	// Vpin does not use ovi-1-1 for Iz function

	//////// Initialize DDD
	//////ddd_7->ddd_set_lo_level(0.0);		// Will immediately change to this level upon execution 
	//////delay(1);
	//////ddd_7->ddd_set_hi_level(4.4);		// Will immediately change to this level upon execution
	//////delay(1);
	//////ddd_7->ddd_run_pattern(Low_pat_start,Low_pat_stop);
	//////wait.delay_10_us(10);
	////////BPP_ovi->disconnect(1);
	//////Close_relay(K2);	// Primary:		Connect DVI11_0 to Drain	pin
	//////Close_relay(K12);	// Primary:		Connect DDD7_1	to Vpin(UV)	pin
	//////delay(4);			// 4 ms delay is necessary to wait for DDD to settle down before powering up BPP pin to avoid mis-clocking

	//////Powerup_Primary_in_Testmode(gWrite_Mode_ReadAF);
	//////D_dvi->set_meas_mode(D_ch,			DVI_MEASURE_CURRENT);

	////////addr=gZF_S_Addr;
	//////DDD_Clock_UV_Antifuse(55);		// Vpin(UV) clock through all AF links one by one
	//////wait.delay_10_us(100);

	////////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
	//////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
	//////wait.delay_10_us(g_readTime_p);		
	//////iAF_Zf = D_dvi->measure_average(5);
	//////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
	//////wait.delay_10_us(3);

	//////if (iAF_Zf > 300e-6)		// Trimmed if > 0.1mA
	//////	gTrimmed_Device = 1;

	////////Observe mode to identify device ID and other features that designers are interested in for Primary Controller
	//////Observe_Vpin_Internal_Signals();

	//////Power_Down_Everything();	// JD helps trimming issue
	//////Open_All_Relays();

	//////if (iAF_Zf > 300e-6)		// Trimmed if > 0.1mA
	//////{
	//////	printf("Zf_p bit is trimmed, 900V BV not done");
	//////	return;
	//////}
	//////// End of Zf bit check

// Instrument protection
	ovi_1->disconnect(0);
	ovi_1->disconnect(1);
	ovi_1->disconnect(2);
	ovi_1->disconnect(5);
	tmu_6->open_relay(TMU_HIZ_DUT1);			// protect TMU
	tmu_6->open_relay(TMU_HIZ_DUT2);			// protect TMU
	tmu_6->open_relay(TMU_CHAN_A_DUT2);			// protect TMU
	dvi_11->close_relay(CONN_FORCE0);
	dvi_11->close_relay(CONN_SENSE0);

//****************************************************************************
//*						High Voltage MOSFET BVD								*
//****************************************************************************/
	//Short UV pin to GND by MUX (UV PIN MUST BE GROUNDED IN ORDER FOR DEVICE TO POWER-UP PROPERLY)
	//We do not want to burn any OVI card so risk mux card here or connect the un-used relay of the K12B to GND for HW mod.
	mux_14->close_relay(MUX_BANK_8_1);	
	mux_14->close_relay(MUX_1_1);
	//mux_14->close_relay(MUX_1_4); //Ground FB thru Mux
	//mux_14->close_relay(MUX_1_2);
	mux_14->close_relay(MUX_2_GND);	//for K23

	tmu_6->open_relay(TMU_EXT_DRV1); // Make sure DVI 11 CH1 is disconnected
	Open_relay(K5);			// Connect HVS to drain, not FWD
	Close_relay(K23);		// Connect HVS to Drain --> HVS-19 stack over HVS-15
	Close_relay(K11);		// Connect BPP to DVI. Avoid using OVI, which can be damaged by 
	delay(4);				// avalanche breakdown from bad units. 

	if (OPCODE==4300 || OPCODE==4500)
	{
		ifrc_str = 1e-3;						// stress current clamp at hot
		ifrc = 100e-6;							// current clamp at hot
		vfrc = 905;			
	}
	else
	{
		ifrc_str = 1e-3;					// stress current clamp at room per device
		ifrc = 100e-6;						// current clamp at room
		vfrc = 900;	
	}

	// Power up from 0V to 5.25V
	BPP_DVI->set_current(BPP_ch, 300e-3,			RANGE_300_MA);	// found lower clamp causes apparent short in data
	wait.delay_10_us(50);

	// Set up HVS
	hvs_15->set_current		(100e-9,	RANGE_1_MA);
	hvs_15->set_voltage		(0.0,		RANGE_1_KV);
	hvs_15->set_meas_mode	(HVS_MEASURE_CURRENT);		
	delay(2);

	hvs_15->close_relay(HVS_NEG_FORCE);		// Connect Source to Gnd
	hvs_15->close_relay(HVS_SHORT_NEG_FS);
	delay(1);
	hvs_15->close_relay(HVS_GND_NEG_SENSE);
	delay(1);
	hvs_15->close_relay(HVS_FORCE_POS);		// Connect Force to HVS15 Neg F
	hvs_15->close_relay(HVS_SHORT_POS_FS);
	delay(1);

	hvs_19->set_current		(100e-9,	RANGE_1_MA);
	hvs_19->set_voltage		(0.0,		RANGE_1_KV);
	hvs_19->set_meas_mode	(HVS_MEASURE_CURRENT);				
	delay(1);
	hvs_19->close_relay(HVS_NEG_FORCE);		// Connect Source to HVS19 Pos F
	hvs_19->close_relay(HVS_SHORT_NEG_FS);
	hvs_19->close_relay(HVS_SHORT_POS_FS);
	delay(1);
	hvs_19->close_relay(HVS_FORCE_POS);		//  Connect Pos Force
	delay(5);

//Power-up after HVS setup
//*******************************************************************************************
	//Powerup BPP zigzag. I_BPP ~ 15mA, using DVI, not OVI
	int lcnt=0;
	float vstart = 0;
	while( vstart < 5.5 && lcnt <500)			// Ramp up VBPP to reduce overshoot
	{	
		vstart +=50e-3;
		BPP_DVI->set_voltage(BPP_ch, vstart,	VOLT_20_RANGE);			// OVI_1_0
		wait.delay_10_us(25);
	}	
	BPP_DVI->set_voltage(BPP_ch, 5.5,	VOLT_20_RANGE);
	wait.delay_10_us(25);

	lcnt=0;
	vstart = 5.5;
	while( vstart > (4.3) && lcnt <500)			// Ramp down VBPP to reduce undershoot
	{	
		vstart -=50e-3;
		BPP_DVI->set_voltage(BPP_ch, vstart,	VOLT_20_RANGE);
		wait.delay_10_us(25);
	}	
	BPP_DVI->set_voltage(BPP_ch, 4.3,	VOLT_20_RANGE);			// OVI_1_0
	wait.delay_10_us(25);

	lcnt=0;
	vstart = 4.3;
	while( vstart < 5.5 && lcnt <500)			// Ramp up VBPP to reduce overshoot
	{	
		vstart +=50e-3;
		BPP_DVI->set_voltage(BPP_ch, vstart,	VOLT_20_RANGE);			// OVI_1_0
		wait.delay_10_us(25);
	}	
	BPP_DVI->set_voltage(BPP_ch, 5.5,	VOLT_20_RANGE);
	wait.delay_10_us(250);
//*******************************************************************************************
	//*** Production Stress the High Voltage MOSFET STARTS ***
	hvs_19->set_meas_mode(HVS_MEASURE_CURRENT);	
	hvs_19->set_current(ifrc_str-10e-6,	RANGE_1_MA);
	hvs_15->set_current(ifrc_str,		RANGE_1_MA);
	delay(5);
	hvs_15->set_voltage(500,		RANGE_1_KV);	
	hvs_19->set_voltage(vfrc - 500,	RANGE_1_KV);
	delay(12);					// Give HVS time for the voltage to come up	(DOES THIS REALLY NEEDED???  ZCX)
								// Some testers require 10ms to come up all the way
								// HL Turret CB requires at least 15ms.

	//*** Production Stress the High Voltage MOSFET STARTS ***
	//Measure ISTR
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);	
	hvs_19->set_meas_mode(HVS_MEASURE_CURRENT);	
	delay(5);
	BVDSS_ISTR = hvs_19->measure_average(25);// measure avalanche current

	//BVD at ISTR before WALK
	hvs_15->set_meas_mode(HVS_MEASURE_VOLTAGE); 
	hvs_19->set_meas_mode(HVS_MEASURE_VOLTAGE); 
	delay(2);
	BVDSS_STR1_15 = hvs_15->measure_average(5);		
	BVDSS_STR1_19 = hvs_19->measure_average(5);		
	BVDSS_STR1 = BVDSS_STR1_15 + BVDSS_STR1_19;
	BVDSS_STR1 = BVDSS_STR1 - BVDSS_ISTR*47e3;		// subtract 47k vdrop

	//Prevent bad device from damaging tester.  Go to LowBV Powerdown
	if(BVDSS_STR1 < 450)
	{
		LowBV_PowerDown = true;
		goto Run_LowBV_PowerDown;
	}

	//WALK
	delay(7);	//WALK Time 20ms
	BVDSS_STR2_15 = hvs_15->measure_average(5);		
	BVDSS_STR2_19 = hvs_19->measure_average(5);		
	BVDSS_STR2 = BVDSS_STR2_15 + BVDSS_STR2_19 - BVDSS_ISTR*47e3;
	//BVDSS_WALK = BVDSS_STR2 - BVDSS_STR1;			// BVDSS:WALK

	//// For now 900V 1s
	//////Experimental Stress time request from Kamal
	////if ((!strnicmp(Dev_id, "INN3678C_REL", 12))||
	////(!strnicmp(Dev_id, "INN3679C_REL", 12)))
		delay(1000);	// 1s for REL programs per technology 10/2
	////else
	////	delay(90);	// 90ms for FT programs per technology 10/2

	//***	After stress reduce current or at hot leave it the same
	hvs_19->set_current(ifrc,	RANGE_1_MA);
	hvs_19->set_meas_mode(HVS_MEASURE_CURRENT);
	wait.delay_10_us(240);							
	Imeas = hvs_19->measure_average(5);				// no avalanche current for GaN

	hvs_19->set_meas_mode(HVS_MEASURE_VOLTAGE); 
	wait.delay_10_us(200);						

	//** BVD_100UA
	BVD_100UA_15 = hvs_15->measure_average(5);
	BVD_100UA_19 = hvs_19->measure_average(5);
	BVD_100UA = BVD_100UA_15 + BVD_100UA_19;	
	BVD_100UA -= Imeas * 47e3;						// subtract 47k vdrop 
	
	hvs_19->set_meas_mode(HVS_MEASURE_CURRENT);
	wait.delay_10_us(200);

	//** BVD-10V
	hvs_19->set_voltage(BVD_100UA - 10 - 500,	RANGE_1_KV);
	wait.delay_10_us(400);		
	IDS_BVD_10V = hvs_19->measure_average(25);		// IDSS:BVD-10V

	//** 80%BVD
	hvs_19->set_voltage(BVD_100UA*0.8  - 500,	RANGE_1_KV);
	wait.delay_10_us(350);
	IDS_80BVD = hvs_19->measure_average(25);		// IDSS:80%BVD 

	//** 650V
	hvs_15->set_voltage(450 ,RANGE_1_KV);
	wait.delay_10_us(400);
	hvs_19->set_voltage(650 - 450 ,RANGE_1_KV);
	wait.delay_10_us(400);
	IDS_650V = hvs_19->measure_average(10);			// IDSS:650V

	//** 325V BVD
	hvs_15->set_voltage(225 ,RANGE_1_KV);
	wait.delay_10_us(400);
	hvs_19->set_voltage(325 - 225 ,RANGE_1_KV);
	wait.delay_10_us(700);
	IDS_325V = hvs_19->measure_average(10);			// IDSS:325V

	//** 150V
	hvs_15->set_voltage(100, RANGE_1_KV); 
	wait.delay_10_us(400);
	hvs_19->set_voltage(150 - 100, RANGE_1_KV); 
	wait.delay_10_us(700);
	IDS_150V = hvs_19->measure_average(10);			// IDSS:150V
	
	//** 30V
	hvs_15->set_voltage(20, RANGE_1_KV); 
	wait.delay_10_us(700);
	hvs_19->set_voltage(10, RANGE_1_KV); 
	wait.delay_10_us(700);
	IDS_30V = hvs_19->measure_average(10);			// IDSS:30V 98.7ms

	hvs_15->set_voltage(0.0, RANGE_1_KV);
	wait.delay_10_us(200);
	hvs_19->set_voltage(0.0, RANGE_1_KV);
	wait.delay_10_us(200);

	BPP_DVI->set_voltage(BPP_ch, 0.0, 		VOLT_10_RANGE); 	// DVI_11_0 
	wait.delay_10_us(20);

	Open_relay(K23);		// Disconnect HVS from Drain
	Open_relay(K11);		// Disconnect BPP from DVI
	delay(2);

	hvs_15->open_relay(HVS_NEG_FORCE);		// NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->open_relay(HVS_SHORT_NEG_FS);	
	hvs_15->open_relay(HVS_GND_NEG_SENSE);	
	hvs_15->open_relay(HVS_SHORT_POS_FS);
	hvs_15->open_relay(HVS_FORCE_POS);		// POS_FORCE (J6,B9) to drain	

	hvs_19->open_relay(HVS_NEG_FORCE);		// Connect Source to HVS19 Pos F
	hvs_19->open_relay(HVS_SHORT_NEG_FS);
	hvs_19->open_relay(HVS_SHORT_POS_FS);
	hvs_19->open_relay(HVS_FORCE_POS);		//  Connect Pos Force
	delay(2);

	ovi_1->connect(0);
	ovi_1->connect(1);
	ovi_1->connect(2);

	// Data log here to prevent 0 leakage readings when BV is low	
	PiDatalog(func, A_9x_IDS_BVD_10V,		IDS_BVD_10V,	 ours->fail_bin,	POWER_MICRO);		
	PiDatalog(func, A_9x_IDS_80BVD,			IDS_80BVD,		 ours->fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_9x_IDS_650V,			IDS_650V,		 ours->fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_9x_IDS_325V,			IDS_325V,		 ours->fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_9x_IDS_150V,			IDS_150V,		 ours->fail_bin,	POWER_MICRO);		
	PiDatalog(func, A_9x_IDS_30V,			IDS_30V,		 ours->fail_bin,	POWER_MICRO);	

Run_LowBV_PowerDown:

if(LowBV_PowerDown == true)
{
	hvs_15->set_voltage(0.0, RANGE_1_KV);
	hvs_19->set_voltage(0.0, RANGE_1_KV);
	delay(2);

	VBPP_ramp_down(3, 0.0, 0.05);

	Open_relay(K23);			// Disconnect HVS from Drain
	Open_relay(K11);			// Disconnect BPP from DVI
	delay(2);

	hvs_15->open_relay(HVS_NEG_FORCE);		// NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->open_relay(HVS_SHORT_NEG_FS);	
	hvs_15->open_relay(HVS_GND_NEG_SENSE);	
	hvs_15->open_relay(HVS_SHORT_POS_FS);
	hvs_15->open_relay(HVS_FORCE_POS);		// POS_FORCE (J6,B9) to drain	
	hvs_19->open_relay(HVS_NEG_FORCE);		// Connect Source to HVS19 Pos F
	hvs_19->open_relay(HVS_SHORT_NEG_FS);
	hvs_19->open_relay(HVS_SHORT_POS_FS);
	hvs_19->open_relay(HVS_FORCE_POS);		//  Connect Pos Force
	delay(2);

	// Power down
	D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_2_RANGE);	// DVI_11_0
	wait.delay_10_us(10);
	VBPP_ramp_down(3, 0.0, 0.05);

	Power_Down_Everything();
	Open_All_Relays();

	Open_relay(K2);
	hvs_15->init();	
	delay(1);
	ovi_1->connect(0);
	ovi_1->connect(1);
	ovi_1->connect(2);
	delay(1);

	//AbortTest = true;
}

	//Disconnect UV pin from GND by MUX
	mux_14->open_relay(MUX_BANK_8_1);	
	mux_14->open_relay(MUX_1_1);
	mux_14->open_relay(MUX_2_GND);	//for K23

	//DEBUG = 1;
	if (DEBUG==1)
		BVDSS_STR1 = 151;

	if (BVDSS_STR1 < 40.0)
		AbortTest =true;		// Don't continue on if BVD is too low
	//DEBUG = 0;

// Datalog
	PiDatalog(func, A_9x_BVDSS_STR,			BVDSS_STR1,		 ours->fail_bin,	POWER_UNIT);		
	PiDatalog(func, A_9x_BVDSS_ISTR,		BVDSS_ISTR,		 ours->fail_bin,	POWER_MICRO);		
	//PiDatalog(func, A_9x_BVDSS_WALK,		BVDSS_WALK,		 ours->fail_bin,	POWER_UNIT);		
	PiDatalog(func, A_9x_BVD_100UA,			BVD_100UA,		 ours->fail_bin,	POWER_UNIT);	
	//PiDatalog(func, A_9x_IDS_BVD_10V,		IDS_BVD_10V,	 ours->fail_bin,	POWER_MICRO);		
	//PiDatalog(func, A_9x_IDS_80BVD,			IDS_80BVD,		 ours->fail_bin,	POWER_MICRO);	
	//PiDatalog(func, A_9x_IDS_650V,			IDS_650V,		 ours->fail_bin,	POWER_MICRO);		
	//PiDatalog(func, A_9x_IDS_325V,			IDS_325V,		 ours->fail_bin,	POWER_MICRO);	
	//PiDatalog(func, A_9x_IDS_150V,			IDS_150V,		 ours->fail_bin,	POWER_MICRO);		
	//PiDatalog(func, A_9x_IDS_30V,			IDS_30V,		 ours->fail_bin,	POWER_MICRO);	

	if (PiGetAnyFailStatus())	// Do not continue program if 900V BV test 
		AbortTest = true;

	if (BVD_100UA <= 400)
		AbortTest = true;

	if(DEBUG==1)
		printf("Function_BV_Drain_Done\n");

}
