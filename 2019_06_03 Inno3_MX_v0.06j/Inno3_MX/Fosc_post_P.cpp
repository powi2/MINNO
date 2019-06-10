//==============================================================================
// Fosc_post_P.cpp (User function)
// 
//    void Fosc_post_P_user_init(test_function& func)
//    void Fosc_post_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_post_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_post_P_user_init(test_function& func)
{
	Fosc_post_P_params *ours;
    ours = (Fosc_post_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_post_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_post_P_params *ours;
    ours = (Fosc_post_P_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "Fosc_Pre_P";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Fosc_post_P,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//skip this function if it's not for characterization
	/*if(gCHAR_FLOW == false)
		return;*/

	float Fosc_post_P=0.0;
	float tmeas=0.0,
		  tElapse=0.0;
	int   lcnt =0;
	int WaitTime = 0;
	int NumPulses = 0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

/****************************************************************************
 *					Fosc_post_P: Primary Frequency							*
 * Note: Primay frequency doesn't have Jitter							    *
 ****************************************************************************/

	// Power Down from previous //
	Power_Down_Everything_Except_Buf_Clamp();
	Open_All_Relays();
	delay(3);

	VBPP_Negative_Cycle();
	// Setup TMU //
	Close_relay(K3);
	delay(3);
 	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	//if(OPCODE==4300 || OPCODE==4500)
	//{
	//	tmu_6->start_trigger_setup(10, NEG_SLOPE, TMU_HIZ, TMU_IN_100V);
	//	tmu_6->stop_trigger_setup(15, NEG_SLOPE, TMU_HIZ, TMU_IN_100V);
	//	WaitTime = 700;
	//	NumPulses = 128;
	//}
	//else
	//{

	if(g_TurretCB)
	{
		tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		delay(2);
	}
	else
	{
		tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->stop_trigger_setup(1.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	}
		
	//WaitTime = 300;
	//NumPulses = 50;
	//}

	// TMU settings //
	tmu_6->start_holdoff(5,TRUE);
	tmu_6->stop_holdoff(128,TRUE);
	//tmu_6->stop_holdoff(NumPulses,TRUE);
	wait.delay_10_us(10);			

	//// Setup Vpin for digital clocking with DDD //
	//ovi_1->disconnect(OVI_CHANNEL_1);	
	//wait.delay_10_us(100);  
	//ddd_7->ddd_set_lo_level(0.1);
	//ddd_7->ddd_set_hi_level(4.0);
	//delay(1);
	//ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	//wait.delay_10_us(10);
	//Close_relay(K12); // Connect DDD7_1 to Vpin(UV) //
	//delay(4);
	Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
#if 0	
	// Drain //
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);	// DVI_11_0

	// SR //
	SR_dvi2k->set_current(SR_ch, 0, RANGE_2_UA);	
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE);
	dvi_13->close_relay(BUS_SENSE1);
	dvi_13->close_relay(BUS_FORCE1);
	mux_14->close_relay(MUX_3_BUS3);

	// BPS //
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);

	// IS //
	FWC_dvi2k->set_voltage(FWC_ch, 0, VOLT_50_RANGE);
	FWC_dvi2k->set_current(FWC_ch, 200e-3, RANGE_200_MA);

	// Setup FB to connect to DDD //
	Close_relay(K17); // Connect FB to DDD //	

	//Have InvSync circuit ready for communication
	Connect_InvSyn_IM(Low_Vd_Input);
	wait.delay_10_us(300); // Wait for all relays //

	// Remove latchoff problem. //
	//VBPP_Negative_Cycle();
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);

	// Primary Powerup //
	// Powerup in normal mode when testing at hot.  Powerup in test mode 1 when testing at room. //
	if(OPCODE==4300 || OPCODE==4500)
	{
		D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE);
		wait.delay_10_us(100);
	}
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.1);	// vstart, vstop, vstep	
	wait.delay_10_us(20);
	Force_Vpin_Pulses_5_Times (5.0, 0.0);
	wait.delay_10_us(10);
	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);		
	VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

	// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
	int ILIM_Select = ILIM_NORM;
	if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
	else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

	// Set BPP below VBP- //
	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
	wait.delay_10_us(50);

	// Reconnect Vpin OVI //
	VPIN_ovi->set_current(VPIN_ch, 1e-3, RANGE_30_MA);
	ovi_1->connect(OVI_CHANNEL_1);
	Open_relay(K12);
	delay(2);
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
	wait.delay_10_us(50);

	// Test mode 1. Drain set to 1.5V for switching.  Do not exceed 3V or will exit Test mode 1. //
	if(OPCODE == 4200 || OPCODE == 4250 || OPCODE == 4400)
	{
		D_dvi->set_voltage(D_ch, 1.5, VOLT_10_RANGE);
		wait.delay_10_us(30);
	}

	// Set BPP above VBP+ // 
	BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
	wait.delay_10_us(30);
	
	// Foor room temp. In test mode 1, wait-and-listen will be skipped. //
	// Foor hot temp. In normal mode, must wait for wait-and-listen to finish (~85msec). //
	if(OPCODE==4300 || OPCODE==4500)
	{
		wait.delay_10_us(10000); // 100 msec.  Can add a loop to check for switching to save test time. //
	}
#endif
	tmu_6->arm();					
	delay(8);			// Wait for TMU to trigger and to capture 128 cycles (25kHz norm.  20kHz min require min 7ms wait)
	//wait.delay_10_us(WaitTime);
	//tmeas = tmu_6->read(WaitTime*10e-6);	 
	tmeas = tmu_6->read(8e-3);	 
	tmeas/=128;
	//tmeas/=NumPulses;
	
	if (tmeas>99)	Fosc_post_P=999e3;
	else if(tmeas==0) Fosc_post_P=-999e3;
	else Fosc_post_P=1/(tmeas);

	//Power down
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(20);
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
 	tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain 
	Open_relay(K3);
	Open_relay(K21);

	//Datalog
	PiDatalog(func, A_Fosc_post_P,	Fosc_post_P,		set_fail_bin,	POWER_KILO);	

	if(gDEBUG)
	printf("Function_Fosc_post_P_Done\n");
}
