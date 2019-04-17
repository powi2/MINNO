//==============================================================================
// FWC_ACK_S.cpp (User function)
// 
//    void FWC_ACK_S_user_init(test_function& func)
//    void FWC_ACK_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "FWC_ACK_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void FWC_ACK_S_user_init(test_function& func)
{
	FWC_ACK_S_params *ours;
    ours = (FWC_ACK_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void FWC_ACK_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    FWC_ACK_S_params *ours;
    ours = (FWC_ACK_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "FWC_ACK_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_FWC_ACK,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	int		i					= 0;
	float	VFWC_M_S			= -999.0;
	float	VFWC_P_S			= -999.0;
	float	FWC_width_S			= -999.0;
	float	tFWC_rise_S			= -999.0;
	float	tFWC_fall_S			= -999.0;
	float	ACK_width_S			= -999.0;
	float	tACK_rise_S			= -999.0;
	float	tACK_fall_S			= -999.0;
	float	tdly_REQ_to_pulse	= -999.0;
	int		hold_off_test_S		= 0;
	int		no_pulse_test_S		= 0;
	int		latch_off_test_S	= 0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//pulse.do_pulse();//********************************************************

	//tmu_6->init();
	//tmu_6->reset_holdoff();
	//tmu_6->close_relay(TMU_CHAN_A_DUT1);	// Connect TMU_CHAN_A1 to FW pin
	////tmu_6->close_relay(TMU_CHAN_B_DUT2);	// Connect TMU_CHAN_B2 to SR pin
	//// 330R in series to TMU input A & B low impedance of 2k (1k5 + 500R divider) (ratio = 0.8584)
	//tmu_6->start_trigger_setup(1.72,	NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);	// Rising edge of FW pulse
	//tmu_6->stop_trigger_setup( 1.72,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// Rising edge of SR pulse

	tmu_6->init();
	tmu_6->reset_holdoff();
	tmu_6->close_relay(TMU_CHAN_B_DUT1);	// Connect TMU_CHAN_B1 to ACK pin
	// 330R in series to TMU input A & B low impedance of 2k (1k5 + 500R divider) (ratio = 0.8584)
	tmu_6->start_trigger_setup(1.71,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// Rising edge of ACK pulse
	tmu_6->stop_trigger_setup( 1.72,	NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// Falling edge of ACK pulse

	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();

	//pulse.do_pulse();//********************************************************
	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);

	Secondary_Vout_Clock_to_Testmode(gProgReadTestMode3_S);

	REQ_ovi->set_voltage(REQ_ch, gREQ_V_Req, RANGE_5_V);		// OVI_1_2

	Close_relay(K5);		//Connect SR to 5nF
	Close_relay(K26);		//SR to DDD-7-5

	FW_dvi->set_voltage(FW_ch, 5.0, RANGE_50_V);		// DVI_11_1
	
	ddd_7->ddd_set_voltage_ref(2.5);
	wait.delay_10_us(10);
	ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
	wait.delay_10_us(10);
	ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_FW_pat_start,Low_FW_pat_stop);
	DDD_Wait_Pattern_End(Low_FW_pat_start,Low_FW_pat_stop);
	ddd_7->ddd_run_pattern(High_pat_FW_start,High_pat_FW_stop);
	DDD_Wait_Pattern_End(High_pat_FW_start,High_pat_FW_stop);

	Close_relay(K21);		// Connect FW to DDD7_3
	delay(1);				// IMPORTANT - make before break
	Open_relay(K18);		// Disconnect FW from DVI11_1
	Open_relay(K36);		// Connect FW  to TMU

	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	delay(4);

	//pulse.do_pulse();//********************************************************

	//Secondary send 2 negative FW pulses to cause Primary to see request so Primary will be switching
	//Force_Neg_Pulses_FW_DDD(5.0, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
	ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_4th_pulse_stop);
	DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_4th_pulse_stop);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_4th_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_4th_pulse_stop);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_4th_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_4th_pulse_stop);

	//REQ_ovi->set_voltage(REQ_ch, gREQ_V_Idle, 		VOLT_5_RANGE);	// OVI_1_2
	//delay(1);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_2nd_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_2nd_pulse_stop);
	//
	//REQ_ovi->set_voltage(REQ_ch, gREQ_V_LatchOff, 		VOLT_5_RANGE);	// OVI_1_2
	//delay(1);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_3rd_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_3rd_pulse_stop);

	//REQ_ovi->set_voltage(REQ_ch, gREQ_V_Idle, 		VOLT_5_RANGE);	// OVI_1_2
	//delay(1);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_2nd_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_2nd_pulse_stop);

	//REQ_ovi->set_voltage(REQ_ch, gREQ_V_Req, 		VOLT_5_RANGE);	// OVI_1_2
	//delay(1);
	//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_2nd_pulse_stop);
	//DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_2nd_pulse_stop);

	//Open_relay(K36);	// Connect REQ to TMU
	delay(1);

	ACK_width_S = 0;
	for (i = 0; i < 10; i++)
	{
		tmu_6->reset();
		tmu_6->arm();
		wait.delay_10_us(4);
		ACK_width_S += tmu_6->read(100e-6);
	}
	ACK_width_S /= 10;

	tmu_6->start_trigger_setup(0.35,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// 10% of ACK pulse
	tmu_6->stop_trigger_setup( 3.09,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// 90% of ACK pulse
	wait.delay_10_us(10);

	tACK_rise_S = 0;
	for (i = 0; i < 10; i++)
	{
		tmu_6->reset();
		tmu_6->arm();
		wait.delay_10_us(4);
		tACK_rise_S += tmu_6->read(100e-6);
	}
	tACK_rise_S /= 10;

	tmu_6->start_trigger_setup(3.09,	NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// 90% of ACK pulse
	tmu_6->stop_trigger_setup( 0.35,	NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// 10% of ACK pulse
	wait.delay_10_us(10);

	tACK_fall_S = 0 ;
	for (i = 0; i < 10; i++)
	{
		tmu_6->reset();
		tmu_6->arm();
		wait.delay_10_us(4);
		tACK_fall_S += tmu_6->read(100e-6);
	}
	tACK_fall_S /= 10;

	Open_relay(K5);		// Disconnect SR from 5nF
	Close_relay(K17);	// Connect REQ to DDD7_2
	Close_relay(K36);	// Connect REQ to TMU
	ddd_7->ddd_set_hi_level(gREQ_2V);
	wait.delay_10_us(50);
	ddd_7->ddd_set_lo_level(-0.5);
	wait.delay_10_us(50);

	tmu_6->init();
	tmu_6->reset_holdoff();
	tmu_6->close_relay(TMU_CHAN_A_DUT1);	// Connect TMU CHAN_A1 to REQ pin
	tmu_6->close_relay(TMU_CHAN_B_DUT2);	// Connect TMU_CHAN_B2 to SR  pin
	tmu_6->start_trigger_setup(1.00,	POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);	// REQ rising edge
	tmu_6->stop_trigger_setup( 1.71,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// SR  rising edge
	delay(2);

	ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	wait.delay_10_us(2);
	ddd_7->ddd_run_pattern(FW_Neg_pulse_3us_Req_start, FW_Neg_pulse_3us_Req_stop);
	wait.delay_10_us(2);
	ddd_7->ddd_run_pattern(FW_Neg_pulse_3us_Req_start, FW_Neg_pulse_3us_Req_stop);
	wait.delay_10_us(2);
	ddd_7->ddd_set_lo_level(gREQ_V_Idle);
	wait.delay_10_us(50);
	ddd_7->ddd_run_pattern(Low_pat_REQ_start, Low_pat_REQ_stop);
	wait.delay_10_us(2);
	//pulse.do_pulse();//********************************************************

	tdly_REQ_to_pulse = 0;
	for (i = 0; i < 10; i++)
	{
		ddd_7->ddd_run_pattern(Low_pat_REQ_start, Low_pat_REQ_stop);
		wait.delay_10_us(1);
		tmu_6->reset();
		tmu_6->arm();
		wait.delay_10_us(4);
		ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
		wait.delay_10_us(2);
		tdly_REQ_to_pulse += tmu_6->read(100e-6);
		//wait.delay_10_us(4);
	}
	tdly_REQ_to_pulse /= 10;

	FWC_dvi2k->open_relay(CONN_FORCE0);
	FWC_dvi2k->open_relay(CONN_SENSE0);

	ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution
	wait.delay_10_us(50);
	ddd_7->ddd_run_pattern(FW_Neg_pulse_3us_Req_start, FW_Neg_pulse_3us_Req_stop);

	Close_relay(K38);	// Connect FWC to TMU
	//Close_relay(K5);		//Connect SR to 5nF

	tmu_6->init();
	tmu_6->reset_holdoff();
	tmu_6->close_relay(TMU_CHAN_B_DUT1);	// Connect TMU_CHAN_B1 to FWC pin
	tmu_6->start_trigger_setup(1.71,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// Rising edge of FWC pulse
	tmu_6->stop_trigger_setup( 1.72,	NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// Falling edge of FWC pulse
	delay(4);
	
	FWC_width_S = 0;
	for (i = 0; i < 10; i++)
	{
		tmu_6->reset();
		tmu_6->arm();
		wait.delay_10_us(4);
		ddd_7->ddd_run_pattern(FW_Neg_pulse_3us_Req_start, FW_Neg_pulse_3us_Req_stop);
		wait.delay_10_us(4);
		FWC_width_S += tmu_6->read(100e-6);
		//wait.delay_10_us(4);
	}
	FWC_width_S /= 10;

	tmu_6->start_trigger_setup(0.35,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// 10% of FWC pulse
	tmu_6->stop_trigger_setup( 3.09,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// 90% of FWC pulse
	wait.delay_10_us(10);

	tFWC_rise_S = 0;
	for (i = 0; i < 10; i++)
	{
		tmu_6->reset();
		tmu_6->arm();
		wait.delay_10_us(4);
		ddd_7->ddd_run_pattern(FW_Neg_pulse_3us_Req_start, FW_Neg_pulse_3us_Req_stop);
		wait.delay_10_us(4);
		tFWC_rise_S += tmu_6->read(100e-6);
		//wait.delay_10_us(4);
	}
	tFWC_rise_S /= 10;

	tmu_6->start_trigger_setup(3.09,	NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// 10% of FWC pulse
	tmu_6->stop_trigger_setup( 0.35,	NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// 90% of FWC pulse
	wait.delay_10_us(10);

	tFWC_fall_S = 0;
	for (i = 0; i < 10; i++)
	{
		tmu_6->reset();
		tmu_6->arm();
		wait.delay_10_us(4);
		ddd_7->ddd_run_pattern(FW_Neg_pulse_3us_Req_start, FW_Neg_pulse_3us_Req_stop);
		wait.delay_10_us(4);
		tFWC_fall_S += tmu_6->read(100e-6);
		//wait.delay_10_us(4);
	}
	tFWC_fall_S /= 10;

	Open_relay(K36);	// Connect FW  to TMU

	tmu_6->init();
	tmu_6->reset_holdoff();
	tmu_6->close_relay(TMU_CHAN_A_DUT1);	// Connect TMU_CHAN_A1 to FW  pin
	tmu_6->close_relay(TMU_CHAN_B_DUT1);	// Connect TMU_CHAN_B1 to FWC pin
	tmu_6->start_trigger_setup(0.09,	POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);	// Rising edge of FW pulse at +100mV
	tmu_6->stop_trigger_setup( 1.71,	NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// Falling edge of FWC pulse at 50%
	delay(4);

	//pulse.do_pulse();//********************************************************
	float FWC_delay_S = 0;
	for (i = 0; i < 10; i++)
	{
		tmu_6->reset();
		tmu_6->arm();
		wait.delay_10_us(4);
		ddd_7->ddd_run_pattern(FW_Neg_pulse_3us_Req_start, FW_Neg_pulse_3us_Req_stop);
		wait.delay_10_us(4);
		FWC_delay_S += tmu_6->read(100e-6);
		wait.delay_10_us(4);
	}
	FWC_delay_S /= 10;

	Power_Down_Secondary();
	Close_relay(K18);	// Connect FW  to DVI11_1
	Open_relay(K26);	// Disconnect SR  from DDD7_5
	Open_relay(K21);	// Disconnect FW  from DDD7_3
	Open_relay(K17);	// Disconnect REQ from DDD7_2
	Open_relay(K36);	// Disconnect FW  from TMU
	Open_relay(K38);	// Disconnect FWC from TMU
	delay(4);

	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
	Secondary_Vout_Clock_to_Testmode(gProgReadTestMode13_S);

	// FWC connect sense to act as DVM
	FWC_dvi2k->set_meas_mode(FWC_ch,		DVI_MEASURE_VOLTAGE, VOLT_5_RANGE);
	FWC_dvi2k->open_relay(CONN_FORCE0);
	FWC_dvi2k->close_relay(CONN_SENSE0);
	SR_dvi2k->open_relay(CONN_SENSE1);
	FW_dvi->set_voltage(FW_ch, 0.0e-3, VOLT_1_RANGE);
	delay(4);

	search_FWC_th(&VFWC_M_S, &VFWC_P_S);

	Power_Down_Secondary();
	
	// Datalog
	PiDatalog(func, A_VFWC_M_S,			VFWC_M_S,			set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_VFWC_P_S,			VFWC_P_S,			set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_FWC_width_S,		FWC_width_S,		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_tFWC_rise_S,		tFWC_rise_S,		set_fail_bin,	POWER_NANO);
	PiDatalog(func, A_tFWC_fall_S,		tFWC_fall_S,		set_fail_bin,	POWER_NANO);
	PiDatalog(func, A_FWC_delay_S,		FWC_delay_S,		set_fail_bin,	POWER_NANO);
	PiDatalog(func, A_ACK_width_S,		ACK_width_S,		set_fail_bin,	POWER_NANO);
	PiDatalog(func, A_tACK_rise_S,		tACK_rise_S,		set_fail_bin,	POWER_NANO);
	PiDatalog(func, A_tACK_fall_S,		tACK_fall_S,		set_fail_bin,	POWER_NANO);
	//PiDatalog(func, A_tdly_REQtoPulse,	tdly_REQ_to_pulse,	set_fail_bin,	POWER_NANO);
	//PiDatalog(func, A_hold_off_test_S,	hold_off_test_S,	set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_no_pulse_test_S,	no_pulse_test_S,	set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_latch_off_test_S,	latch_off_test_S,	set_fail_bin,	POWER_UNIT);

	if (gDEBUG)
	printf("Function REQ_post_S Done\n");
}
