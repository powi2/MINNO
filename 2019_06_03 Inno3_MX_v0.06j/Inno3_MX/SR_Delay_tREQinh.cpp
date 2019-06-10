//==============================================================================
// SR_Delay_tREQinh.cpp (User function)
// 
//    void SR_Delay_tREQinh_user_init(test_function& func)
//    void SR_Delay_tREQinh(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "SR_Delay_tREQinh.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void SR_Delay_tREQinh_user_init(test_function& func)
{
	SR_Delay_tREQinh_params *ours;
    ours = (SR_Delay_tREQinh_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void SR_Delay_tREQinh(test_function& func)
{
    // The two lines below must be the first two in the function.
    SR_Delay_tREQinh_params *ours;
    ours = (SR_Delay_tREQinh_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "SR_Delay";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_SR_Delay,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	float	ISR_Pulldown=0.0,
			VSR_Pulldown = 0.0,
			SR_delay=0.0,
			ISR_Pullup=0,
			VSR_Pullup = 0.0,
			Rpd = 0.0,
			Rpu = 0.0,
			vbps = 0.0,
			SR_threshold=0.0,
			vSR_high=0.0,
			tmeas =0.0, 
			iBPS=0.0, 
			vset=0.0,
			TREQ_INH=0.0,
			TON_P=0.0,
			TOFF_P=0.0,
			Num_Cycles=0.0,
			tHS=0.0,
			Freq_P_tHS=0.0,
			Freq_S_tHS=0.0,
			Soft_time_S=0.0,
			Soft_FrqStart_S=0.0;

	int		i=0,
			Unwanted_pulses=0;

	bool  SR_debug			=0;
	
	// Added SR:Gnd test
	int		j=0;
	float	SR_freq[20]={0};
	float	SR_Ton[20]={0};
	bool	Switching = false;
	float	SRfrequency = 0, 
			SRCkOpen=0, 
			SRCkCap=0,
			SRGdFrequency=0;
	int		num_pulse = 0, 
			Cknum_pulse=0, 
			Gdnum_pulse=0;
	float 	Pulse_dly_HS = 0, 
			Pulse_dly_0V = 0;
	float	FWFlate_filter_NM = 0, 
			FWFlate_dly_0V = 0, 
			Delta_dly_0V = 0;

	int     num_loop = 0;

	float	tmeas_SRopen_vFBlow		=0,
			tmeas_SRopen_vFBhigh	=0;

	float	SR_DuringSSpass	=0,
			SR_AfterSSpass =0,
			SR_10pctClampOff =0,
			tmeas_DuringSSpass =0,
			tmeas_AfterSSpass  =0,
			tmeas_10pctClampOff=0;

	//SR_debug = 1;
	
	//if(SR_debug)
	//	DEBUG = 1;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
//	////////

	// Charge up PV3 for SOA test
	pv3_4->normal_comp();
	pv3_4->set_voltage(0, RANGE_3_V);
	pv3_4->set_current(0);
	pv3_4->set_meas_mode(PV3_CHARGE_S);			// Monitor storage cap DEBUG_MODEge_mode
	pv3_4->drive_off();
	pv3_4->charge_on();							// Requires a 15ms wait
	// Charge up PV3 for SOA test

/*************************************************************************************
 *						RSR_Clamp: BPS3V							 				 *
 *************************************************************************************/
	float VSR_Clamp;
	float ISR_Clamp;
	float RSR_Clamp_BPS3V;

	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	delay(1);

	Close_relay(K18);
	FWC_dvi2k->open_relay(CONN_FORCE0);
	FWC_dvi2k->open_relay(CONN_SENSE0);
	ACK_ovi->disconnect(ACK_ch);
	delay(3);

	FW_dvi->set_current(FW_ch, 30e-3,	RANGE_30_MA);	
	FW_dvi->set_voltage(FW_ch, 11.0,	RANGE_20_V);		// DVI11-1
	wait.delay_10_us(10);

	BPS_dvi->set_current(BPS_ch, 5e-3,	RANGE_300_MA);	 
	BPS_dvi->set_voltage(BPS_ch, 3.0,	RANGE_10_V);		// DVI_9_1
	wait.delay_10_us(10);	
	
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	REQ_ovi->set_voltage(REQ_ch, 0.0,	RANGE_2_V);			// OVI_1_2	
	wait.delay_10_us(10);	

	SR_dvi2k->set_current(SR_ch, 10e-3,	RANGE_200_MA);
	SR_dvi2k->set_voltage(SR_ch, 5.0, 	RANGE_10_V);		// DVI_21_0
	wait.delay_10_us(10);	

	SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(10);	
	VSR_Clamp = SR_dvi2k->measure_average(5);

	SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);	
	ISR_Clamp = SR_dvi2k->measure_average(5);
	
	RSR_Clamp_BPS3V = VSR_Clamp / ISR_Clamp;

/*************************************************************************************
 *						ISR_Pulldown: Only power up Secondary		 				 *
 *************************************************************************************/
	BPS_dvi->set_current(BPS_ch, 300e-3,	RANGE_300_MA);	 
	BPS_dvi->set_voltage(BPS_ch, 0.0,		RANGE_10_V);		// DVI_9_1

	// Set VO and FW to zero to limit influence on BPS
	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
	FW_dvi->set_current(FW_ch, 30e-3,		RANGE_30_MA);	
	FW_dvi->set_voltage(FW_ch, 0.0,			VOLT_5_RANGE);		// DVI11-1

	SR_dvi2k->open_relay(BUS_SENSE1);
	SR_dvi2k->open_relay(BUS_FORCE1);
	mux_14->open_relay(MUX_3_BUS3);

	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);	
	REQ_ovi->set_voltage(REQ_ch, gREQ_2V,	RANGE_2_V);			// OVI_1_2	

	//BPS_dvi->set_current(BPS_ch, 300e-3,	RANGE_300_MA);	 
	BPS_dvi->set_voltage(BPS_ch, 5.0,		RANGE_10_V);		// DVI_9_1
	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_VOLTAGE);

	// First do Rpd measurement at 10mA to avoid device heating
	SR_dvi2k->set_meas_mode(SR_ch,			DVI_MEASURE_VOLTAGE);
	SR_dvi2k->set_current(SR_ch, 10e-3,		RANGE_200_MA);
	SR_dvi2k->set_voltage(SR_ch, 5.0,		RANGE_5_V);	// DVI_21_0
	wait.delay_10_us(10);

	VSR_Pulldown = SR_dvi2k->measure_average(8);

	SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);	

	ISR_Pulldown = SR_dvi2k->measure_average(8);

	//vbps = BPS_dvi->measure_average(10);

	Rpd = VSR_Pulldown / ISR_Pulldown;

	// Now measure full pull down current
	SR_dvi2k->set_current(SR_ch, 2.0,		RANGE_2_A);
	//SR_dvi2k->set_voltage(SR_ch, 5.0, 	RANGE_5_V);	// DVI_21_0
	wait.delay_10_us(20);	

	// If trap and measure here, the current will be about 40mA smaller than running full speed. Device
	// can get heat up with constant 300mA on RDSON from the driver 
	ISR_Pulldown = SR_dvi2k->measure_average(8);
	
	SR_dvi2k->set_voltage(SR_ch, 0.0, 	VOLT_5_RANGE);	// DVI_21_0
	//SR_dvi2k->set_current(SR_ch, 2.0e-6, RANGE_2_MA);	
	BPS_dvi->set_current(BPS_ch, 300e-3, RANGE_300_MA);	 
	BPS_dvi->set_voltage(BPS_ch, 0.0, 	VOLT_10_RANGE);	// DVI_9_1

///////////****************************************************************************************
//////////*					SR:GdCheck-															*
//////////*		With SR grounded the part should continue to switch and to save test time the	*
//////////*		the SR threshold test will be done immediately afterwards.						*											   *
////////// ***************************************************************************************/
//////////	Open_relay(K21);		// FW		to	DDD
//////////	Close_relay(K3);		// Drain	to	50 ohm 
//////////
//////////	//SECTION DEBUG FOR tHANDSHAKE
//////////	Close_relay(K10);		//Drain to RDS_BUF_IN
//////////	SAMPLE_SIZE = GAGE_POST_16K;
//////////
//////////	INNO_Gage_ChanAB_setup(0.22);	// Only do it when SAMPLE_SIZE is diff from previous. 
//////////	delay(3);
//////////
//////////	//tHANDSHAKE does a manual HS powerup here so gage digitizer can be program to start capture right before BPS reach vPlus
//////////	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
//////////	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
//////////	// Hard ground SR throught the MUX
//////////	if(g_TurretCB)
//////////	{
//////////		//HL needs to change to 20mA or Turret CB won't work.
//////////		SR_dvi2k->set_current(SR_ch, 20e-3,			RANGE_2_A);	
//////////		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
//////////	}
//////////	else
//////////	{
//////////		SR_dvi2k->set_current(SR_ch, 20e-6,			RANGE_20_UA);	
//////////		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
//////////	}
//////////
//////////	SR_dvi2k->close_relay(BUS_SENSE1);
//////////	SR_dvi2k->close_relay(BUS_FORCE1);
//////////	mux_14->close_relay(MUX_3_BUS3);
//////////
//////////	//Close_relay(K21);		// FW		to	DDD
//////////	delay(6);
//////////	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//This could cause a 1V glitch at BPS for 50us
//////////	wait.delay_10_us(10);
//////////
//////////	//Vpin (0V)
//////////	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
//////////	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
//////////	//Vout (3V)
//////////	VO_dvi->set_current(VO_ch, 30.0e-3,		RANGE_30_MA);	
//////////	VO_dvi->set_voltage(VO_ch, 3.0, 		VOLT_5_RANGE);	// DVI_9_0
//////////	//FB (1V)
//////////	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
//////////	REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
//////////	//IS (0V)
//////////	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
//////////	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
//////////	wait.delay_10_us(50);
////////////////////
//////////
////////////	Connect_InvSyn_IM(Low_Vd_Input);
//////////	Connect_InvSyn_IM(Low_Load_Vd_Input);
//////////	
//////////	// Connect TMU CHA to SR 
//////////	tmu_6->reset_holdoff();
//////////	tmu_6->close_relay(TMU_CHAN_A_DUT2);	// Connect TMU_CHAN_A2 to SR pin
//////////	//tmu_6->close_relay(TMU_HIZ_DUT1);		// Connect TMU HIZ to Drain 
//////////	tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);
//////////	tmu_6->stop_trigger_setup(3.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
//////////	delay(3);
//////////
//////////	VBPP_Negative_Cycle();
//////////	VBPP_Power_Up_w_Test_Mode(gTM1_p, ILIM_NORM);	//
//////////	//Power_Up_Primary_Normal_Mode();
//////////	//BPS (vPlus - 300mV)
//////////	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
//////////	VBPS_Power_Up(gVBPS_P_Init-0.3);			// vfinal
//////////	wait.delay_10_us(gDly_Wait_and_Listen_Test_Mode);	//wait and listen time
//////////
//////////	//////////
//////////	Gage_Start_Capture( );
//////////	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
//////////	//wait.delay_10_us(5);
//////////	CsDo(hSystem, ACTION_FORCE);	//Force capture.
//////////		
//////////	Gage_Wait_For_Capture_Complete();
//////////
//////////	WAVE_NAME =  "t_HandShake";
//////////	Gage_Find_tHandshake(&tHS, &Freq_P_tHS, &Freq_S_tHS);
//////////	Open_relay(K10);		//Drain to RDS_BUF_IN
//////////	Open_relay(K21);
//////////
//////////	//////////
	Disconnect_InvSyn_IM();
	Power_Down_Primary();
	Power_Down_Secondary();
//////////
	//Power_Down_Everything();
	Open_All_Relays();

/***************************************************************************************
 *					SR_delay: Secondary controlled primary Switching				   *
 *Measure delay time from the falling edge of SR to the falling edge of Drain		   *
 *NOTE1: Ton has to be trimmed before measuring SR_Delay. Otherwise, primary will      *
 *ignore a cycle from secondary and continue to stay off when secondary sends a pulse  *
 *NOTE2: The waveform after the first 64ms on is no longer reliable as both primary    *
 * and secondary are trying to stay in control due to BPS being held up by DVI resource*
 * In application, this will never be the case. When device gets in autorestart, BPS   *
 * will be discharged, secondary will give up control. It will re-synchronized by the  *
 * FW pulses and re-seize control.													   *
 ***************************************************************************************/
	Close_relay(K3);		// Drain	to	50 ohm 

	// Connect TMU CHA to SR 
	tmu_6->reset_holdoff();
	tmu_6->close_relay(TMU_CHAN_A_DUT2);	// Connect TMU_CHAN_A2 to SR pin
	tmu_6->close_relay(TMU_HIZ_DUT1);		// Connect TMU HIZ to Drain 
	if(LB_Rev>=5 )
	{
		tmu_6->start_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
		tmu_6->stop_trigger_setup(5.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	}
	else
	{
		if(g_TurretCB)
		{
			tmu_6->start_trigger_setup(1.8, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
			tmu_6->stop_trigger_setup(3.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);

		}
		else
		{
			tmu_6->start_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
			tmu_6->stop_trigger_setup(3.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		}
	}
	delay(4);

	////// Secondary send 2 negative FW pulses to cause Primary to see request so Primary will be switching		//why?  zcx for JD
	////Force_Neg_Pulses_FW_DDD(4.0, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.		//why?  zcx for JD
	////wait.delay_10_us(10);  //more than 30us quiet time on FW signal		
	//why?  zcx for JD

	//float start=0, stop=0, time=0;

//
//
	if(0)	//B2 material 
	{
		Open_relay(K18);	// FW to TMU
		Open_relay(K27);	// VO disconnect from ddd
		Close_relay(K3);	// Connect drain fast edge ckt
		Close_relay(K21);	// Connect FW to DDD
		VBPP_Negative_Cycle();
		delay(3);

		tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
		tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->stop_trigger_setup(3.0,	POS_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);
		delay(3);

		//Vpin (0V)
		VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
		VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
		//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
		//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
		if(g_TurretCB)
		{
			//HL needs to change to 20mA or Turret CB won't work.
			SR_dvi2k->set_current(SR_ch, 20e-3,			RANGE_2_A);	
			SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		}
		else
		{
			SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
			SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		}
	
		dvi_13->close_relay(BUS_SENSE1);
		dvi_13->close_relay(BUS_FORCE1);
		mux_14->close_relay(MUX_3_BUS3);
		wait.delay_10_us(20);
		delay(3);
		//mux_14->close_relay(MUX_BANK_3_4);
		//mux_14->close_relay(MUX_4_GND);

		//Vout (Will charge BPS if @5V)
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
		//FB (1V)
		REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 200mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	

		//Make sure vBPS less than 5.5V
		if(gVBPS_M_Init < 5.5)
			VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal  
		else
			VBPS_Power_Up(4.5);			

		//Connect_InvSyn_IM(Low_Vd_Input);

		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
		wait.delay_10_us(100); 
		ddd_7->ddd_set_hi_level(5.0);				// Will immediately change to this level upon execution
		delay(1);
		ddd_7->ddd_run_pattern(High_pat_start,High_pat_stop);
		wait.delay_10_us(14);

		//Make sure vBPS less than 5.5V
		if(gVBPS_P_Init < 5.5)
	//	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init + 0.05, 	VOLT_10_RANGE);	// DVI_9_1
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// DVI_9_1  (8" EPSON require higher)
		wait.delay_10_us(100); 

		ddd_7->ddd_set_lo_level(-0.5);				// Will immediately change to this level upon execution
		delay(1);
		ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_3rd_pulse_stop-1);
		wait.delay_10_us(100);	
	}
	else
	{
		// For SR pulses to appear, must do the power up with tmu disconnected										//why?  zcx for JD
		Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
		//Secondary_Vout_Clock_to_Testmode(gProgReadTestModeTFB1_S);
		Secondary_Vout_Clock_to_Testmode(gProgReadTestMode3_S);

		Power_Up_Primary_Normal_Mode(ILIM_NORM);

		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
		wait.delay_10_us(10);

		Close_relay(K21);		// FW to DDD
		delay(4);
		// Secondary send 2 negative FW pulses to cause Primary to see request so Primary will be switching
		Force_Neg_Pulses_FW_DDD(4.0, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
		if(g_TurretCB)
		{
			wait.delay_10_us(150);  //more than 30us quiet time on FW signal
			//HL changed the timing.
		}
		else
		{
			wait.delay_10_us(10);  //more than 30us quiet time on FW signal
		}

		D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0		
		wait.delay_10_us(5);

		Connect_InvSyn_IM_New(High_Vd_Input);		
		Open_relay(K21);		// FW must float 
		wait.delay_10_us(350);

		//FB (1V) force Switching
		D_dvi->set_voltage(D_ch, 5.0, 			VOLT_50_RANGE);	// DVI_11_0		
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(50);
		//int start = mytimer.GetElapsedTime();

		// Float FW pin to prevent tester fighting it, FW forced to 0V in prog read powerup
		// If FW rises above ground, SR will go low
		FW_dvi->open_relay(CONN_FORCE1);
		FW_dvi->open_relay(CONN_SENSE1);
		delay(7);	// Takes ~12ms for drain to switch 
	}

	//start = mytimer.GetElapsedTime();
	//////////
	for (i=0; i<10; i++)
	{
		// SR to Drain prop delay 
		tmu_6->arm(); 
		wait.delay_10_us(4);
		SR_delay += tmu_6->read(400e-6);	//See ~100ns from scope for INNO 3x
	}
	//int stop = mytimer.GetElapsedTime();
	SR_delay /= 10;

	if(g_TurretCB)
	{

		float UpperLimit = (func.dlog->tests[A_SR_delay].f_max_limit_val[0]); // Get upper test limit //
		float LowerLimit = (func.dlog->tests[A_SR_delay].f_min_limit_val[0]); // Get upper test limit //
		int   correction = 0;


		if(SR_delay >= UpperLimit)
		{
			tmu_6->start_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
			tmu_6->stop_trigger_setup(3.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			wait.delay_10_us(10);
			SR_delay = 0;
			for (i=0; i<10; i++)
			{
				// SR to Drain prop delay 
				tmu_6->arm(); 
				wait.delay_10_us(40);
				SR_delay += tmu_6->read(400e-6);	//See ~100ns from scope for INNO 3x
			}
			//int stop = mytimer.GetElapsedTime();
			SR_delay /= 10;
			correction = 1;
		}


		if(SR_delay <= LowerLimit)
		{
			if(correction == 1)
			{
				tmu_6->start_trigger_setup(1.9, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
				tmu_6->stop_trigger_setup(3.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			}
			else
			{
				tmu_6->start_trigger_setup(1.6, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
				tmu_6->stop_trigger_setup(3.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			}
			wait.delay_10_us(10);
			SR_delay = 0;
			for (i=0; i<10; i++)
			{
				// SR to Drain prop delay 
				tmu_6->arm(); 
				wait.delay_10_us(40);
				SR_delay += tmu_6->read(400e-6);	//See ~100ns from scope for INNO 3x
			}
			//int stop = mytimer.GetElapsedTime();
			SR_delay /= 10;
		}

	}

	//float time = (stop-start)/1e6;

	tmu_6->open_relay(TMU_HIZ_DUT1);		 // Connect TMU HIZ to Drain 
	tmu_6->open_relay(TMU_CHAN_A_DUT2);	 // Connect TMU CHA to SR 
	wait.delay_10_us(50);	

	SAMPLE_SIZE = GAGE_POST_32K;
//	INNO_Gage_ChanAB_setup(0.15);	// Only do it when SAMPLE_SIZE is diff from previous. 
//	wait.delay_10_us(10);
	// Channel B setup //
	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,SAMPLE_SIZE); 
	//delay(2);

	gage_input_control_xp (GAGE_CHAN_B,		// channel
			GAGE_INPUT_ENABLE,					// enable / disable
			GAGE_DC,							// coupling
			GAGE_PM_5_V|GAGE_1_MOHM_INPUT);			// range, impedance
	//delay(2);
	
	gage_trigger_control_xp (GAGE_CHAN_B,		// trigger source
			GAGE_DC,							// coupling for ext trig
			GAGE_PM_5_V,								// range for CHA trigger
			GAGE_POSITIVE,						// slope
			0.15,								// 1.0V trigger level 
	   		SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE
	//	Set up Buffer Clamp
	BC_ovi->set_current(BC_ch, 30e-3,		RANGE_30_MA);
	BC_ovi->set_voltage(BC_ch, (5.0-0.6),VOLT_10_RANGE);	// OVI_1_3 Account for one diode drop
	delay(1);

	Power_Down_Everything();
	Disconnect_InvSyn_IM();	// Disconnect FW pin
	Open_All_Relays();

/****************************************************************************************
 *				 tREQ-INH:																*
*****************************************************************************************/

	{
		Open_relay(K18);	// FW to TMU
		Open_relay(K27);	// VO disconnect from ddd
		Close_relay(K3);	// Connect drain fast edge ckt
		//Close_relay(K21);	// Connect FW to DDD
		VBPP_Negative_Cycle();
		delay(3);

		//Vpin (0V)
		VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
		VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
		//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
		//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
	    if(g_TurretCB)
		{
			SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
			SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);	// DVI_21_1
			delay(2);
			mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
			delay(2);
		}
		else
		{
			SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
			SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
			dvi_13->close_relay(BUS_SENSE1);
			dvi_13->close_relay(BUS_FORCE1);
			mux_14->close_relay(MUX_3_BUS3);
			wait.delay_10_us(20);
			delay(3);
		}
		

		//Vout (Will charge BPS if @5V)
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
		//FB (1V)
		REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	

		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 200mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	

		//Make sure vBPS less than 5.5V
		if(gVBPS_M_Init < 5.5)
			VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal  
		else
			VBPS_Power_Up(4.5);			

		Connect_InvSyn_IM(Low_Load_Vd_Input);
		VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
		// Close K12 to connect DDD to VPIN
		Close_relay(K12);
		delay(4);
//
		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// DVI_9_1  (8" EPSON require higher)
		wait.delay_10_us(30);
		//BPP set to lower voltage after Secondary power-up for B3 silicon an later material
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
		wait.delay_10_us(10);

		//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_3rd_pulse_stop-1);
		//wait.delay_10_us(20);

		REQ_ovi->set_voltage(REQ_ch, gREQ_V_Req,		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(50);
		Disconnect_InvSyn_IM();	// Disconnect FW pin
		Close_relay(K10);		//Drain to	RDS_BUF_IN
		delay(5);				//Required for INH: timing measurements

		Gage_Start_Capture();
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
		wait.delay_10_us(20);
		// Open K12 
		Open_relay(K12);
		//Bring Vpin OVI back
		VPIN_ovi->connect(1);				// Reconnect OVI from UV
		VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);  
		VPIN_ovi->set_current(VPIN_ch, 1e-3,		RANGE_30_MA);

		//ddd_7->ddd_set_lo_level(-0.5);				// Will immediately change to this level upon execution
		//delay(1);
////		Close_relay(K10);		//Drain to	RDS_BUF_IN
////		delay(5);	
//////
////		Gage_Start_Capture();
////		//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_3rd_pulse_stop-1);
////		//wait.delay_10_us(200);
////		delay(5);
////		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
		Gage_Wait_For_Capture_Complete();
		WAVE_NAME =  "tREQ";
		//DEBUG=1;
		Gage_Find_tReqInhibit(&TREQ_INH, &TON_P, &TOFF_P, &Num_Cycles, &Unwanted_pulses);
		//DEBUG=0;
		//time = (stop - start)/1e6;

	}

	Power_Down_Everything();
	Disconnect_InvSyn_IM();	// Disconnect FW pin
	Open_All_Relays();

/********************************************************************************************
 *					Rpu, ISR_Pullup-s: Secondary TM5										*
 ********************************************************************************************/
	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
	Secondary_Vout_Clock_to_Testmode(gProgReadTestMode5_S);

	FWC_dvi2k->open_relay(CONN_FORCE0);
	FWC_dvi2k->open_relay(CONN_SENSE0);
	ACK_ovi->disconnect(ACK_ch);
	SR_dvi2k->open_relay(BUS_SENSE1);
	SR_dvi2k->open_relay(BUS_FORCE1);
	mux_14->open_relay(MUX_3_BUS3);
	Open_relay(K5);			// Disconnect 5nF Cap from SR

	// measure Rpu at 10mA forcing current
	// Step VSR to 0V to avoid voltage spike on VBPS
	SR_dvi2k->set_current(SR_ch, 10e-3,		RANGE_200_MA);
	SR_dvi2k->set_voltage(SR_ch, gVBPS_final+100e-3, 		RANGE_5_V);		// DVI_21_0
	wait.delay_10_us(100);
	SR_dvi2k->set_voltage(SR_ch, 4.0, 		RANGE_5_V);		// DVI_21_0
	wait.delay_10_us(20);
	SR_dvi2k->set_voltage(SR_ch, 3.0, 		RANGE_5_V);		// DVI_21_0
	wait.delay_10_us(20);
	SR_dvi2k->set_voltage(SR_ch, 2.0, 		RANGE_5_V);		// DVI_21_0
	wait.delay_10_us(20);
	SR_dvi2k->set_voltage(SR_ch, 1.0, 		RANGE_5_V);		// DVI_21_0
	wait.delay_10_us(20);
	SR_dvi2k->set_voltage(SR_ch, 0.0, 		RANGE_5_V);		// DVI_21_0
	SR_dvi2k->set_meas_mode(SR_ch,			DVI_MEASURE_VOLTAGE);

	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_VOLTAGE);
	BPS_dvi->set_current(BPS_ch, 300 mA,	RANGE_300_MA);	
	BPS_dvi->set_voltage(BPS_ch, 5.0,		RANGE_5_V);		// DVI_9_1

	FW_dvi->set_current(FW_ch, 30e-3,		RANGE_30_MA);	
	FW_dvi->set_voltage(FW_ch, 5.0,			RANGE_5_V);		// DVI11-1

	VO_dvi->set_current(VO_ch, 20.0e-3,		RANGE_30_MA);	
	VO_dvi->set_voltage(VO_ch, 0.0, 		RANGE_5_V);		// DVI_9_0

	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);	
	REQ_ovi->set_voltage(REQ_ch, gREQ_2V,	RANGE_2_V);		// OVI_1_2
	delay(1);

	vbps = BPS_dvi->measure_average(10);

	VSR_Pullup = SR_dvi2k->measure_average(10);

	SR_dvi2k->set_meas_mode(SR_ch,			DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	float isr = SR_dvi2k->measure_average(10);

	// Calculate Rpu
	Rpu = -(vbps - VSR_Pullup) / isr;
	
	// Now measure full pull up current
	// Gradually increase SR current limit to avoid BPS collapse
	for (i=2; i<=80; i++)
	{
		SR_dvi2k->set_current(SR_ch, i*5e-3,		RANGE_2_A);
		wait.delay_10_us(1);
	}
	wait.delay_10_us(20);

	ISR_Pullup = SR_dvi2k->measure_average(10);

	// Slowly decrease SR current limit to avoid big spike on VBPS
	for (i=20; i>=1; i--)
	{
		SR_dvi2k->set_current(SR_ch, i*10e-3,		RANGE_2_A);
		wait.delay_10_us(5);
	}

	//Disconnect_InvSyn_IM();
	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();

/*******************************************************************************************
 *				SR:Threshold: Secondary controlled primary Switching (3 NEG pulses method) *
 * Step 1. Power up secondary from BPS with 3 negative pulses on FW pin. Use 3.0V on DDD_Hi*
 *          to avoid glitch when connecting DVI to FW pin.								   *
 * 		   Make sure DVI is connected to FW pin before step 2. After step 2, only the first*
 *		   FW falling edge can bring up SR voltage. If DVI was connected after step 2,     *
 *		   glitches will bring SR back to low. The test condition would be wrong.          *
 * Step 2. Stop secondary from switching by rising FB pin voltage					       *
 * Step 3. Drop FW pin to -0.5V(below FW threshold). SR pin will rise at the FW falling    *
 *			edge.																		   *
 * Step 4. Slowly bring up FW pin voltage by changing DDD_lo_lev. When the FW threshold is *
 *         crossed, SR pin will drop. Record FW pin threshold.							   *
 ******************************************************************************************/
	////////
	// Set ddd high level to 4.4V, same as VBPS
	wait.delay_10_us(100); 
	ddd_7->ddd_set_hi_level(4.4);
	delay(1);

	if(g_TurretCB)
	{
		//HL added more current to BPS.  Else, SRth-S failed in Turret CB.
		BPS_dvi->set_current(BPS_ch, 300.0e-3,					RANGE_300_MA);
	}
	VBPP_Negative_Cycle();
	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);

	int TM = 11;
	SR_threshold = DEFAULT_VALUE;

	if (TM == 11)
	{
		Secondary_Vout_Clock_to_Testmode(gProgReadTestMode11_S);

		Open_relay(K26);	//Disconnect SR from DDD-7-5
		SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE, VOLT_5_RANGE);
		SR_dvi2k->close_relay(CONN_SENSE1);
		wait.delay_10_us(50);

		//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
		FW_dvi->set_current(FW_ch, 1e-3, RANGE_30_MA);		// Float FW pin for SR:Threshold test
		FW_dvi->set_voltage(FW_ch, -1, VOLT_10_RANGE);		// Same voltage as FW in Sync
		delay(1); //needed 1ms here 

		search_SR_th(&SR_threshold);
	}

	if (TM == 1)
	{
		Secondary_Vout_Clock_to_Testmode(gProgReadTestMode1_FB_S);

		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, RANGE_10_V);
		SR_dvi2k->close_relay(CONN_SENSE1);

		REQ_ovi->set_voltage(REQ_ch, gREQ_2V, VOLT_5_RANGE);
		wait.delay_10_us(10);

		//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
		FW_dvi->set_current(FW_ch, 1e-3, RANGE_300_MA);

		for (i = 0; i < 3; i++)
		{
			FW_dvi->set_voltage(FW_ch, -1.0, VOLT_10_RANGE);
			wait.delay_10_us(10);
			FW_dvi->set_voltage(FW_ch, 5.0, VOLT_10_RANGE);
			wait.delay_10_us(10);
		}
		REQ_ovi->set_voltage(REQ_ch, 1.0, VOLT_5_RANGE);
		FW_dvi->set_voltage(FW_ch, -0.5, VOLT_10_RANGE);
		
		//Ramp up FW so SR will toggle
		search_SR_th_TM1(&SR_threshold);
	}
	
	Power_Down_Secondary();


	if(gSiliconRev_S<3)
	{
	   /************************************************************************************************************
		***************** SR_Chk_Open-S, SR_Chk_5nF-S **************************************************************
		************************************************************************************************************
		SR_Chk_Open-S Test Procedure:
			1.	power up VBPS into Normal mode                        
			2.	Power up Primary in Normal mode. Secondary should take over control.              
			4.  Observe SR:CkOpen check on SR pin. Only one SR switching cycle for 1us. Secondary gives up control 
				and stops requesting pulses.
		***********************************************************************************************************/
		Open_relay(K21);		// FW		to	DDD
		Close_relay(K3);		// Drain	to	50 ohm 
		tmu_6->close_relay(TMU_EXT_DRV3);	// Floating SR pin on the contactor board
	 
		tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
		tmu_6->start_trigger_setup(1.2, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->stop_trigger_setup(1.4,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);
		
		Connect_InvSyn_IM(High_Vd_Input);	// Must use Vd high input for tester to tester correlation JD 7/28

		// Float SR pin, SR:CKopen test
		// DUT should give one 1us pulse and then turn off
		dvi_13->open_relay(CONN_SENSE1);
		dvi_13->open_relay(CONN_FORCE1);
		Open_relay(K18);		//FW		float
		delay(3);

		VBPP_Power_Up_w_Test_Mode(gTM1_p, ILIM_NORM);	//

		//Vout (Will charge BPS if @5V)
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 300mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
		VBPS_Power_Up(gVBPS_P_Init-0.3);			// vfinal
		wait.delay_10_us(gDly_Wait_and_Listen_Test_Mode);	//wait and listen time

		// Test will not work without higher than 2-3V on the drain, FW and Drain get out of phase and the 
		// part continues to swtich with SR pin floating
		D_dvi->set_voltage(D_ch, 5.0, 		VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(10);
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
		wait.delay_10_us(50);

		// FB (1V) force Switching
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
		wait.delay_10_us(10);		
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas = tmu_6->read(50e-6);

		if(tmeas < 1e-9)	// No Switching
			SRCkOpen = 1;
		else
			SRCkOpen = 0;

		tmu_6->open_relay(TMU_EXT_DRV3);	// SR pin w/ 1K to ground

		//Disconnect_InvSyn_IM();
		Power_Down_Primary();
		Power_Down_Secondary();
		Disconnect_InvSyn_IM();
		delay(1);

		Close_relay(K5);	// Connect 5nF Cap to SR
		delay(5);
		Connect_InvSyn_IM(High_Vd_Input);	// Must use Vd high input for tester to tester correlation JD 7/28

		// DUT should give one 1us pulse and then turn off
		dvi_13->open_relay(CONN_SENSE1);
		dvi_13->open_relay(CONN_FORCE1);
		Open_relay(K18);		//FW		float
		delay(3);
	
		//Power_Up_Primary_Normal_Mode();
		VBPP_Power_Up_w_Test_Mode(gTM1_p, ILIM_NORM);	//

		//Vout (Will charge BPS if @5V)
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 300mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
		VBPS_Power_Up(gVBPS_P_Init-0.3);			// vfinal
		wait.delay_10_us(gDly_Wait_and_Listen_Test_Mode);	//wait and listen time

		// Test will not work without higher than 2-3V on the drain, FW and Drain get out of phase and the 
		// part continues to swtich with SR pin floating
		D_dvi->set_voltage(D_ch, 5.0, 		VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(10);
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
		wait.delay_10_us(50);		
		// FB (1V) force Switching
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
		wait.delay_10_us(10);		
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas = tmu_6->read(50e-6);

		if(tmeas > 0)	// Switching
			SRCkCap = 1;
		else
			SRCkCap = 0;

		Open_relay(K5);
		//////////
		tmu_6->open_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
		//Disconnect_InvSyn_IM();
		Power_Down_Primary();
		Power_Down_Secondary();
		Disconnect_InvSyn_IM();
		delay(1);

		dvi_13->close_relay(CONN_SENSE1);
		dvi_13->close_relay(CONN_FORCE1);
		delay(3);

		if(g_TurretCB)
		{
			tmu_6->close_relay(TMU_EXT_DRV3); //Disconnect DVI_13 from SR pin.
			delay(3);
		}
	}
	else //Secondary B3 and later silicon revisions
	{
	   /************************************************************************************************************
		***************** SR_Chk_Open-S, SR_DuringSSpass, SR_AfterSSPass, SR_10pctClmpOff **************************
		************************************************************************************************************
		Test Procedure:
			1.  power up VBPS into Normal mode with SR open                   
			2.  Power up Primary in Normal mode TM5 to skip wait and listen timer. 
			    Secondary should take over control and give up control immediately after the first SR cycle check.
			    Expect no switching after 1st SR cycle.
			3.  Terminate softstart ramp by increasing FB above CV, SR shouldn't turn on after that. 
				Expect no switching after FB go above CVth.
		***********************************************************************************************************/
		Open_relay(K21);		// FW		to	DDD
		Close_relay(K3);		// Drain	to	50 ohm 
		tmu_6->close_relay(TMU_EXT_DRV3);	// Floating SR pin on the contactor board
	 
		tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
		tmu_6->start_trigger_setup(1.2, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->stop_trigger_setup(1.4,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);
		
		Connect_InvSyn_IM(Low_Load_Vd_Input);	

		// Float SR pin, SR:CKopen test
		// DUT should give one 1us pulse and then turn off (Because we want SR to be 
		dvi_13->open_relay(CONN_SENSE1);
		dvi_13->open_relay(CONN_FORCE1);
		Open_relay(K18);		//FW		float
		delay(3);

		// Setup Vpin for digital clocking with DDD //
		ovi_1->disconnect(OVI_CHANNEL_1);	
		wait.delay_10_us(100); 
		ddd_7->ddd_set_lo_level(0.1);
		ddd_7->ddd_set_hi_level(4.0);
		delay(1);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(10);
		Close_relay(K12); // Connect DDD7_1 to Vpin(UV) //
		delay(4);
		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);

		//Vout (Will charge BPS if @5V)
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 300mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
		VBPS_Power_Up(gVBPS_P_Init-0.3);			// vfinal

		// Test will not work without higher than 2-3V on the drain, FW and Drain get out of phase and the 
		// part continues to swtich with SR pin floating
		D_dvi->set_voltage(D_ch, 5.0, 		VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(10);
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
		wait.delay_10_us(50);

		// Secondary should now have control. //
		if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
		{
			BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
			wait.delay_10_us(10);
		}

		// FB (1V) force Switching
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
		wait.delay_10_us(10);		
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas_SRopen_vFBlow = tmu_6->read(50e-6);

		// FB set 5% above CVth to terminate tSoft.  (SR switch from Low to High if SR connect to 5nF, SR stay Low if SR open)
		REQ_ovi->set_voltage(REQ_ch, gCV_FB_S*1.05,		RANGE_2_V);	// OVI_1_2	
		wait.delay_10_us(10);		
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas_SRopen_vFBhigh = tmu_6->read(50e-6);

		if(tmeas_SRopen_vFBlow < 1e-9 && tmeas_SRopen_vFBhigh < 1e-9)	// No Switching and SR stay low
			SRCkOpen = 1;
		else
			SRCkOpen = 0;


		tmu_6->open_relay(TMU_EXT_DRV3);	// SR pin w/ 1K to ground
		tmu_6->open_relay(TMU_HIZ_DUT1);    // Disconnect TMU HIZ to Drain 
		Open_relay(K12);					// Disconnect DDD7_1 from Vpin

		//Disconnect_InvSyn_IM();
		Power_Down_Primary();
		Power_Down_Secondary();
		Disconnect_InvSyn_IM();
		delay(1);

		/*****************************************************************************************************
		 ************************* SR checks with 5nF connected to SR pin ************************************
		 *****************************************************************************************************
		 Test(s): SR_DuringSSpass, SR_AfterSSpass, SR_10pctClampOff

		 Procedure:
			1.  Power up Secondary in Normal mode                              
			2.  Power up Primary in Normal mode. Secondary should take over control.       
			3.  Observe SR turn on for one cycle  (1us width) and stop until after tSoft then SR switch for another cycle.
				If SR stop switching during tSoft, datalog "1" to SR_DuringSSpass.
			4.  Terminate Softstart ramp by taking FB or Vout (internal FB res) above regulation (above CVth).
			4a. Bring FB below CVth to observe normal switching.
			5.  Observe SR switching continuously.  If SR switches, datalog "1" to SR:AfterSSpass. 
			6.  Bring FB above CVth to stop switching.  Power-Down Primary so device will stay in control by 2ndary only.
			6a. SR should stay low.  Set FW high
			6b. Send 1 request by FB (FB => below CVth and then above CVth)
			6c. Set FW low below GND and make sure no bounce back so SR will go high as FW go low
			6d. Set FB 15% above CVth so SR will go low as FB go 15% above CVth.  
				If SR stay high at 6c and low at 6d then datalog "1" to SR_10pctClampOff

			Note:
				SR_10pctClampOff can also be done with powerup into Testmode9.  Since we already power up,
				we do not need to have another power-up to testmode 9, so step 6 from above replace the testmode9.
				Below is the waveform given from DE, Qing

				FW -----| |---------| |--| |--------------------|							-- FW high
						|_|			|_|  |_|					|______________________		__ FW Low

																		
																|-------|					-- SR High (~vBPS_plus)
				SR _____________________________________________|		|______________		__ SR Low  (~0V)


																		 ______________		__ FB 15% above CVth
																		|
				FB ---------------------------------| |------------------					-- FB 5%  above CVth
													|_|										__ FB     below CVth
									 _	  _			 _
				Comm Pulse___________||___||_________||________________________________		xx Internal signal
													 |<-------->|
													     <30us

		*****************************************************************************************************************/

		Close_relay(K5);	// Connect 5nF Cap to SR
		Connect_InvSyn_IM(Low_Load_Vd_Input);
		dvi_13->open_relay(CONN_SENSE1);
		dvi_13->open_relay(CONN_FORCE1);
		Open_relay(K18);		//FW		float
		delay(5);

		// Setup Vpin for digital clocking with DDD //
		ovi_1->disconnect(OVI_CHANNEL_1);
		wait.delay_10_us(100); 
		ddd_7->ddd_set_lo_level(0.1);
		ddd_7->ddd_set_hi_level(4.0);
		delay(1);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(10);
		Close_relay(K12); // Connect DDD7_1 to Vpin(UV) //
		delay(4);
		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);

		//FB set Low for Secondary to request switching continuously before PU
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	
		wait.delay_10_us(10);
		//Vout (Will charge BPS if @5V)
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 300mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
		VBPS_Power_Up(gVBPS_P_Init-0.3);			// vfinal
		wait.delay_10_us(20);

		// Test will not work without higher than 2-3V on the drain, FW and Drain get out of phase and the 
		// part continues to swtich with SR pin floating
		D_dvi->set_voltage(D_ch, 5.0, 		VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(10);

		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
		wait.delay_10_us(10);	
		// Secondary should now have control. //
		if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
		{
			BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
			wait.delay_10_us(10);
		}

		//Setup TMU ChanB Dut2 to measure SR signal
		tmu_6->close_relay(TMU_CHAN_B_DUT2);
		tmu_6->start_trigger_setup(3, NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);
		tmu_6->stop_trigger_setup( 3.5, NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);

		//*********************
		//** SR_DuringSSpass **
		//*********************
		//3.	Observe SR turn on for one cycle  (1us width) and stop until after tSoft then SR switch for another cycle.
		//		If SR stop switching during tSoft, datalog "1" to SR_DuringSSpass.
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	//tSoft will stay because it's still below CVth
		wait.delay_10_us(10);
		//Observe SR switching or not during tSoft (No Switch => pass => SR_DurringSSpass = 1)   tSoft LL=8.1ms, HL=16ms
		tmu_6->arm();
		delay(7);
		tmeas_DuringSSpass = tmu_6->read(7e-3);	//expect no switching in 7ms which ~1ms lower than LL of tSoft
		if(tmeas_DuringSSpass==0)	SR_DuringSSpass = 1;
		else						SR_DuringSSpass = 0;


		//*********************
		//** SR_AfterSSpass ***
		//*********************
		//4.  Terminate Softstart ramp by taking FB or Vout (internal FB res) above regulation (above CVth).
		//4a. Bring FB below CVth to observe normal switching.
		//5.  Observe SR switching continuously.  If SR switches, datalog "1" to SR_AfterSSpass. 
		REQ_ovi->set_voltage(REQ_ch, gCV_FB_S*1.05,		RANGE_2_V);	// OVI_1_2	
		wait.delay_10_us(10);
		//Bring FB below CVth and expect SR to be switching
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2		
		wait.delay_10_us(20);		
		//Observe SR switching or not (Switching => pass => SR_AfterSSpass = 1)
		tmu_6->arm(); 
		wait.delay_10_us(50);
		tmeas_AfterSSpass = tmu_6->read(500e-6);	//expect no switching in 7ms which ~1ms lower than LL of tSoft
		if(tmeas_AfterSSpass>0 && tmeas_AfterSSpass<99)		SR_AfterSSpass = 1;
		else												SR_AfterSSpass = 0;

		//**********************
		//** SR_10pctClampOff **
		//**********************
		//6.  Bring FB above CVth to stop switching.  Power-Down Primary so device will stay in control by 2ndary only.
		//6a. SR should stay low.  Set FW high
		//6b. Send 1 request by FB (FB => below CVth and then above CVth)
		//6c. Set FW low below GND and make sure no bounce back so SR will go high as FW go low
		//6d. Set FB 15% above CVth so SR will go low as FB go 15% above CVth.  
		//	  If SR stay high at 6c and low at 6d then datalog "1" to SR_10pctClampOff

		tmu_6->start_trigger_setup(3.5, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
		tmu_6->stop_trigger_setup( 2.5, NEG_SLOPE, TMU_CHAN_B, TMU_IN_10V);
		wait.delay_10_us(100); 
		ddd_7->ddd_set_lo_level(0.1);
		ddd_7->ddd_set_hi_level(gCV_FB_S*1.05);	
		wait.delay_10_us(100);                 //HL Do not remove. Else, DDD will be corrupted.
		REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_2_V);	// OVI_1_2		
		wait.delay_10_us(10);		
		Open_relay(K18);	//FW disconnect from dvi-11-1
		Open_relay(K19);	//FW disconnect from InvSync_IM_OUT
		Open_relay(K8);		//D  disconnect from InvSync_IM_IN
		wait.delay_10_us(20);		
		Close_relay(K21);	//FW connect to DDD-7-3
		Close_relay(K17);	//FB connect to DDD-7-2
		delay(4);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);
		wait.delay_10_us(100); 
		ddd_7->ddd_set_lo_level(-0.7);
		delay(1);

		BPP_ovi->set_voltage(BPP_ch, 0.0,	RANGE_2_V);	//BPP power-down primary
		wait.delay_10_us(100);		
		tmu_6->arm(); 
		wait.delay_10_us(5);
		ddd_7->ddd_run_pattern(SR_10pctClampOff_start,	SR_10pctClampOff_end);
		wait.delay_10_us(100); 

		ddd_7->ddd_set_hi_level(gCV_FB_S*1.15);		
		delay(1);
		tmeas_10pctClampOff = tmu_6->read(2e-3);	
		if(tmeas_10pctClampOff>100e-6 && tmeas_10pctClampOff<200e-6)		SR_10pctClampOff = 1;
		else																SR_10pctClampOff = 0;

		//Temporary use the SRCkcap as consolidating datalog for 3 of the new test for B3 and later silicon
		if(SR_DuringSSpass && SR_AfterSSpass && SR_10pctClampOff)
		{
			SRCkCap	= 1;
		}
		else
		{
			if		(SR_DuringSSpass==0)	SRCkCap = 11;
			else if (SR_AfterSSpass==0)		SRCkCap = 12;
			else if (SR_10pctClampOff==0)	SRCkCap = 13;
		}

		Open_relay(K21);	//FW disconnect from DDD-7-3
		Open_relay(K17);	//FB disconnect from DDD-7-2
		wait.delay_10_us(100); 
		ddd_7->ddd_set_lo_level(0.1);
		wait.delay_10_us(100);                           // HL do not remove delay.  Else, it will corrupt the DDD pattern.
		tmu_6->open_relay(TMU_CHAN_B_DUT2);
		Open_relay(K5);
		tmu_6->open_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
		//Disconnect_InvSyn_IM();
		Power_Down_Primary();
		Power_Down_Secondary();
		Disconnect_InvSyn_IM();
		wait.delay_10_us(20);

		dvi_13->close_relay(CONN_SENSE1);
		dvi_13->close_relay(CONN_FORCE1);
		delay(3);

		if(g_TurretCB)
		{
			tmu_6->close_relay(TMU_EXT_DRV3); //Disconnect DVI_13 from SR pin.
			delay(3);
		}
	}
	//************************************************************************************************************
	//******* Pulse_dly_HS, Pulse_dly_0V, FWFlate_filter_NM, FWFlate_dly_0V, Delta_dly_0V ************************
	//************************************************************************************************************
	tmu_6->init();
	//Close_relay(K3);						// tmu to drain
 	tmu_6->close_relay(TMU_CHAN_A_DUT1);	// Connect TMU HIZ to FW 
	tmu_6->close_relay(TMU_CHAN_B_DUT2);	// tmu to SR pin
	if(g_TurretCB)
	{
		//Turret RevB
		tmu_6->start_trigger_setup(0.15, NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);
		tmu_6->stop_trigger_setup(0.25,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// SR pulse request is a glitch and sensitive to trigger level
	}
	else
	{
		tmu_6->start_trigger_setup(0.45, NEG_SLOPE, TMU_CHAN_A, TMU_IN_2_5V);
		tmu_6->stop_trigger_setup(0.1,	POS_SLOPE, TMU_CHAN_B, TMU_IN_2_5V);	// SR pulse request is a glitch and sensitive to trigger level
	}
	delay(5);	// TMT43 use 0.0 Pos, TMT20 0.14

	//FB (2V)  pull FB above CVth to force No Switching
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);
	if (fabs(gCV_FB_S) >2.0) gCV_FB_S = 2.0;  //RLB prevent OVI over range
	if(g_TurretCB)
	{
		REQ_ovi->set_voltage(REQ_ch, gCV_FB_S-0.05,	RANGE_2_V);	// OVI_1_2
	}
	else
	{
		REQ_ovi->set_voltage(REQ_ch, gCV_FB_S-0.05,	RANGE_2_V);	// OVI_1_2	
	}
	//IS (0V)
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	wait.delay_10_us(10);

	//Pulse_dly_HS
	//////////
	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
	Secondary_Vout_Clock_to_Testmode(gProgReadTestMode3_S);

	if(g_TurretCB)
	{
		BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	
	}

	//HL added for LB Rev E
	if(1)//!g_TurretCB)
	{
		//Need to keep both FW & SR at 0V first before switching DDD to these 2 pins.
		FW_dvi->set_current(FW_ch, 0.1e-3,		RANGE_30_MA);
		FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1

		//Float SR pin
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);
		delay(3);   //HL needed or glitch on SR pin to cause repeatability on RevE LB
	
	}

	// Hot switching to cause a glitch on FW & SR pin, leading to repeatability issue.
	// HL moved it to inside the "Force_Neg_Pulses_FW_DDD_continuously(") function
	// Disconnect FW from DVI
	//dvi_11->open_relay(CONN_FORCE1);
	//dvi_11->open_relay(CONN_SENSE1);
	

	// After clocking, force VO=0V to avoid interaction with VBPS
	Open_relay(K27);	//Connect Vout to DVI
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	delay(3);



	// Needed to allow SR pulse request
	VO_dvi->set_voltage(VO_ch, 0, 	VOLT_5_RANGE);	// DVI_9_0
	if(g_TurretCB)
	{
		BPS_dvi->set_current(BPS_ch, 290e-3,	RANGE_300_MA);
	}
	BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS+0.2,	VOLT_10_RANGE);			
	wait.delay_10_us(50);

	if(g_TurretCB)
	{ 
		delay(2);
	}

	Force_Neg_Pulses_FW_DDD_continuously();


	num_loop = 50;

	if(g_TurretCB)
	{
		num_loop = 100;
	}

	if(g_TurretCB)
	{
		Pulse_dly_HS = 0.0; //HL re-initialized variables.
	}
	for (i=0; i<num_loop; i++)	// SR pin cannot drive stray capacitance
	{
		// measure time
		tmu_6->arm(); 	
		wait.delay_10_us(40);
		tmeas = tmu_6->read(100e-6);
		wait.delay_10_us(5);
		if (tmeas > 0.7e-6 && tmeas < 2e-6) break;
	}
	Pulse_dly_HS = tmeas;

	

	

	//Pulse_dly_0V
	if(g_TurretCB)
	{
		REQ_ovi->set_voltage(REQ_ch, gCV_FB_S+0.05, 	RANGE_2_V);	// Above CV threshold
	}
	else
	{
		REQ_ovi->set_voltage(REQ_ch, gCV_FB_S+0.05, 	RANGE_2_V);	// Above CV threshold
	}
	wait.delay_10_us(10);
	BPS_dvi->set_current(BPS_ch, gISD+2e-3, 	RANGE_30_MA);	// Secondary vBPS_plus
	wait.delay_10_us(40);
//
if(g_TurretCB)
	{
		//Turret RevB
		tmu_6->start_trigger_setup(0.15, NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);
		tmu_6->stop_trigger_setup(0.25,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// SR pulse request is a glitch and sensitive to trigger level
	}

	num_loop = 10;
	if(g_TurretCB)
	{
		wait.delay_10_us(50);
		num_loop = 50;
	}

	for (i=0; i<num_loop; i++)	// SR pin cannot drive stray capacitance
	{
		// measure time
		tmu_6->arm(); 
		wait.delay_10_us(14);
		tmeas = tmu_6->read(100e-6);
		wait.delay_10_us(5);
		if (tmeas > 0.7e-6 && tmeas < 2e-6) break;
	}
	Pulse_dly_0V = tmeas;

	Power_Down_Primary();
	Power_Down_Secondary();

if(g_TurretCB)
	{
		//Turret RevB
		tmu_6->start_trigger_setup(0.15, NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);
		tmu_6->stop_trigger_setup(0.25,	POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);	// SR pulse request is a glitch and sensitive to trigger level
	}

	//FWFlate_filter_NM
	//FB (2V)  pull FB above CVth to force No Switching
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	REQ_ovi->set_voltage(REQ_ch, gCV_FB_S-0.05,	RANGE_2_V);	// OVI_1_2	
	//IS (0V)
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	wait.delay_10_us(10);

	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
	Secondary_Vout_Clock_to_Testmode(gProgReadTestMode12_S);

	if(g_TurretCB)
	{
		BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);
		delay(1);
	}

	//HL added for LB Rev E
	if(1)
	{
		//Need to keep both FW & SR at 0V first before switching DDD to these 2 pins.
		FW_dvi->set_current(FW_ch, 0.1e-3,		RANGE_30_MA);
		FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1

		//Float SR pin
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);
		delay(3);   //HL needed or glitch on SR pin to cause repeatability on RevE LB
	
	}



	// Hot switching to cause a glitch on FW & SR pin, leading to repeatability issue.
	// HL moved it to inside the "Force_Neg_Pulses_FW_DDD_continuously(") function
	// Disconnect FW from DVI
	//dvi_11->open_relay(CONN_FORCE1);
	//dvi_11->open_relay(CONN_SENSE1);

	// After clocking, force VO=0V to avoid interaction with VBPS
	Open_relay(K27);	//Connect Vout to DVI
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	delay(3);

	// Needed to allow SR pulse request
	VO_dvi->set_voltage(VO_ch, 0, 	VOLT_5_RANGE);	// DVI_9_0
	BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS+0.2,	VOLT_10_RANGE);			
	wait.delay_10_us(50);

	Force_Neg_Pulses_FW_DDD_continuously();
		//////////
//
	num_loop = 10;
	if(g_TurretCB)
	{
		num_loop = 50;
	}
	for (i=0; i<num_loop; i++)	// SR pin cannot drive stray capacitance
	{
		// measure time

		tmu_6->arm(); 
		wait.delay_10_us(14);
		tmeas = tmu_6->read(100e-6);
		wait.delay_10_us(5);
		if (tmeas > 0.7e-6 && tmeas < 2e-6) break;
	}
	FWFlate_filter_NM = tmeas;

	if(g_TurretCB)
	{
		//FWFlate_filter_NM = 0.94*FWFlate_filter_NM;
	}

	//FWFlate_dly_OV
	REQ_ovi->set_voltage(REQ_ch, gCV_FB_S+0.05, 	RANGE_2_V);	// OVI_1_2
	wait.delay_10_us(10);
	BPS_dvi->set_current(BPS_ch, gISD+2e-3, 	RANGE_30_MA);	// Secondary vBPS_plus
	wait.delay_10_us(40);
		
	num_loop = 10;
	if(g_TurretCB)
	{
		num_loop = 50;
	}
	for (i=0; i<num_loop; i++)
	{
		// measure time
		tmu_6->arm(); 
		wait.delay_10_us(14);
		tmeas = tmu_6->read(100e-6);
		wait.delay_10_us(5);
		if (tmeas > 0.7e-6 && tmeas < 2e-6) break;
	}
	FWFlate_dly_0V = tmeas;

	//Calfactor for Turret CB
	if(g_TurretCB)
	{
		//FWFlate_dly_0V = 0.94*FWFlate_dly_0V;
	}
	
	Power_Down_Primary();
	Power_Down_Secondary();

	Open_relay(K3);
	Open_relay(K21);		// FW		to	DDD
	wait.delay_10_us(10);

	dvi_13->close_relay(CONN_SENSE1);
	dvi_13->close_relay(CONN_FORCE1);
	delay(3);

	//Delta_dly_OV
	Delta_dly_0V = Pulse_dly_0V - FWFlate_dly_0V;

	// Power down
	if(0)
	{
		ddd_7->ddd_set_clock_period(250e-9);		// Set DDD vector time back to 250ns
	}
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	wait.delay_10_us(100);                           // HL do not remove delay.  Else, it will corrupt the DDD pattern.

	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	Power_Down_Primary();
	Power_Down_Secondary();

	dvi_11->close_relay(CONN_SENSE1);
	dvi_11->close_relay(CONN_FORCE1);
	Open_relay(K3);
	Open_relay(K18);
	Open_relay(K27);
	Open_relay(K21);		// Connect FW pin to DDD, DDD is at 0V
	Open_relay(K10);		// Drain to RDS_BUF_IN
 	tmu_6->open_relay(TMU_CHAN_A_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->open_relay(TMU_CHAN_A_DUT2);	// Connect TMU CHA to SR 
	if(g_TurretCB)
	{
		tmu_6->open_relay(TMU_EXT_DRV3); //Reconnect DVI_13 from SR pin.
		delay(3);
	}
	delay(3);

	// Datalog
	PiDatalog(func, A_ISR_Pulldown,		ISR_Pulldown,		set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_Rpd,				Rpd,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_SR_delay,			SR_delay,			set_fail_bin,	POWER_NANO);
	PiDatalog(func, A_ISR_Pullup,		ISR_Pullup,			set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_Rpu,				Rpu,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_SR_threshold,		SR_threshold,		set_fail_bin,	POWER_MILLI);
	//PiDatalog(func, A_SR_chk_Open,		SRCkOpen,			set_fail_bin,	POWER_UNIT);   // EEFU 20180208
	//PiDatalog(func, A_SR_chk_5nF,		SRCkCap,			set_fail_bin,	POWER_UNIT);   // EEFU 20180911
	//PiDatalog(func, A_Soft_time_S,		Soft_time_S,		set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_Soft_FrqStart_S,	Soft_FrqStart_S,	set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_tHandShake,		tHS,				set_fail_bin,	POWER_MICRO);
	//PiDatalog(func, A_tREQ_Inhibit,		TREQ_INH,			set_fail_bin,	POWER_MICRO);   // EEFU 20180208
	//PiDatalog(func, A_nCycles_Inhibit,	Num_Cycles,			set_fail_bin,	POWER_UNIT);   // EEFU 20180208
	//PiDatalog(func, A_Unwanted_pulses,	Unwanted_pulses,	set_fail_bin,	POWER_UNIT);   // EEFU 20180208
	//PiDatalog(func, A_Pulse_dly_HS,	Pulse_dly_HS,	set_fail_bin,	POWER_MICRO);   // EEFU 20180208
	//PiDatalog(func, A_Pulse_dly_0V,	Pulse_dly_0V,	set_fail_bin,	POWER_MICRO);   // EEFU 20180208
	//PiDatalog(func, A_FWFlate_filter_NM,	FWFlate_filter_NM,	set_fail_bin,	POWER_MICRO);   // EEFU 20180208
	//PiDatalog(func, A_FWFlate_dly_0V,	FWFlate_dly_0V,	set_fail_bin,	POWER_MICRO);   // EEFU 20180208
	//PiDatalog(func, A_Delta_dly_0V,	Delta_dly_0V,	set_fail_bin,	POWER_NANO);   // EEFU 20180208
	PiDatalog(func, A_RSR_Clamp_BPS3V,		RSR_Clamp_BPS3V,		set_fail_bin,	POWER_UNIT);

	if(gDEBUG==1)
	printf("Function SR_Delay_tREQinh Done\n");

	//if (gCHAR_FLOW)
#define CODE_SIZE 16
	if(0)
	{
		long	trim_code;
		int		r_AF[100] = {0};
		float	SRth[CODE_SIZE]		= {-999.0};

		Power_Down_Primary();
		Power_Down_Secondary();
		Disconnect_InvSyn_IM();

		for (trim_code = 0; trim_code < CODE_SIZE; trim_code++)
		{
			FillMemory(&r_AF, sizeof(r_AF), -1);
			printf("trim_code = %d\n", trim_code);

			Powerup_Secondary_in_Testmode(gProgRead_AFreg_S, 0, 0);
		
			Read_Secondary_AF_Reg(r_AF);	//must be followed by write

			// MINNO_S feature trim code
			//r_AF[11] = 1;
			////r_AF[12] = 0;
			//r_AF[13] = 1;
			////r_AF[14] = 0;
			//r_AF[15] = 1;
			//r_AF[16] = 1;
			//r_AF[38] = 1;
			//r_AF[39] = 0;
			//r_AF[40] = 0;
			//r_AF[41] = 0;

			// SR trim bits
			r_AF[26] = (trim_code & 1);
			r_AF[27] = (trim_code & 2) >> 1;
			r_AF[28] = (trim_code & 4) >> 2;
			r_AF[29] = (trim_code & 8) >> 3;

			Write_Secondary_AF_Reg(r_AF);

			VO_dvi->set_voltage(VO_ch, 0.0,		VOLT_5_RANGE);	// DVI_9_0
			wait.delay_10_us(10);

			//7. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
			FW_dvi->set_voltage(FW_ch, -0.3,	VOLT_50_RANGE);	// DVI_11_1
			wait.delay_10_us(10);
			FW_dvi->set_voltage(FW_ch, 1.0,		VOLT_50_RANGE);	// DVI_11_1
			wait.delay_10_us(10);

			//8. Clock VOUT to TestMode#
			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode11_S);

			//Open_relay(K21);	//Disconnect FW from DDD7-3
			// SR disconnected in Powerup, need to connect sense to act as DVM
			Open_relay(K26);	//Disconnect SR from DDD-7-5
			SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE, VOLT_5_RANGE);
			SR_dvi2k->close_relay(CONN_SENSE1);
			wait.delay_10_us(50);

			//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
			FW_dvi->set_current(FW_ch, 1e-3, RANGE_30_MA);		// Float FW pin for SR:Threshold test
			FW_dvi->set_voltage(FW_ch, gVshunt_BPS+0.2, VOLT_10_RANGE);		// Same voltage as FW in Sync
			delay(1); //needed 1ms here 

			//Ramp up FW so SR will toggle from Low to High
			search_SR_th(&SRth[trim_code]);	//Note: if BPS_plus is marginally passing, SR will fail.  Might need higher BPS voltage

			Power_Down_Secondary();

		}

		// Write to debug file
		time_t rawtime;
		struct tm * timeinfo;
		char timestamp[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timestamp, 80, "%y%m%d%H%M%S", timeinfo);

		char file_name_Id[200] ="e:\\dl4\\SRth_";
		strcat (file_name_Id, timestamp);
		strcat (file_name_Id, ".csv");
		FILE * fpr = fopen(file_name_Id, "w");
		if (! fpr) return;
		
		fprintf(fpr, "DUT,trim_code,SRth(V)\n");

		for (trim_code = 0; trim_code < CODE_SIZE; trim_code++)
		{
				fprintf(fpr, "%d,%d,%8.4f\n", SERIAL_NUM, trim_code, SRth[trim_code] * 1e3);
		}
		fprintf(fpr,"\n" );

		fclose(fpr);
		delay(10);
	}


	// SR threshold using TM1
	if (0)
	{
		Power_Down_Primary();
		Power_Down_Secondary();
		Disconnect_InvSyn_IM();

		Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
		Secondary_Vout_Clock_to_Testmode(gProgReadTestMode1_FB_S);

		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, RANGE_10_V);
		SR_dvi2k->close_relay(CONN_SENSE1);

		REQ_ovi->set_voltage(REQ_ch, 2.0, VOLT_5_RANGE);
		wait.delay_10_us(10);

		//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
		FW_dvi->set_current(FW_ch, 1e-3, RANGE_300_MA);

		for (i = 0; i < 3; i++)
		{
			FW_dvi->set_voltage(FW_ch, -1.0, VOLT_10_RANGE);
			wait.delay_10_us(10);
			FW_dvi->set_voltage(FW_ch, 5.0, VOLT_10_RANGE);
			wait.delay_10_us(10);
		}
		REQ_ovi->set_voltage(REQ_ch, 1.0, VOLT_5_RANGE);
		FW_dvi->set_voltage(FW_ch, -0.5, VOLT_10_RANGE);
		
		//Ramp up FW so SR will toggle from High to Low
		SR_threshold = 999.0;
		search_SR_th_TM1(&SR_threshold);
		
		printf("V_SRth_TM1 = %8.2f mV\n", SR_threshold * 1e3);
		Power_Down_Secondary();
	}

	// Characterise SR threshold using TM1
	if(0)
	{
//#define CODE_SIZE 16
		long	trim_code;
		int		r_AF[100] = {0};
		float	SRth[CODE_SIZE]		= {-999.0};

		Power_Down_Primary();
		Power_Down_Secondary();
		Disconnect_InvSyn_IM();

		for (trim_code = 0; trim_code < CODE_SIZE; trim_code++)
		{
			FillMemory(&r_AF, sizeof(r_AF), -1);
			printf("trim_code = %d\n", trim_code);

			Powerup_Secondary_in_Testmode(gProgRead_AFreg_S, 0, 0);
		
			Read_Secondary_AF_Reg(r_AF);	//must be followed by write

			// MINNO_S feature trim code
			//r_AF[11] = 1;
			////r_AF[12] = 0;
			//r_AF[13] = 1;
			////r_AF[14] = 0;
			//r_AF[15] = 1;
			//r_AF[16] = 1;
			//r_AF[38] = 1;
			//r_AF[39] = 0;
			//r_AF[40] = 0;
			//r_AF[41] = 0;

			// SR trim bits
			r_AF[26] = (trim_code & 1);
			r_AF[27] = (trim_code & 2) >> 1;
			r_AF[28] = (trim_code & 4) >> 2;
			r_AF[29] = (trim_code & 8) >> 3;

			Write_Secondary_AF_Reg(r_AF);

			VO_dvi->set_voltage(VO_ch, 0.0,		VOLT_5_RANGE);	// DVI_9_0
			wait.delay_10_us(10);

			//7. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
			FW_dvi->set_voltage(FW_ch, -0.3,	VOLT_50_RANGE);	// DVI_11_1
			wait.delay_10_us(10);
			FW_dvi->set_voltage(FW_ch, 1.0,		VOLT_50_RANGE);	// DVI_11_1
			wait.delay_10_us(10);

			//8. Clock VOUT to TestMode#
			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode1_FB_S);

			SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, RANGE_10_V);
			SR_dvi2k->close_relay(CONN_SENSE1);

			REQ_ovi->set_voltage(REQ_ch, 2.0, VOLT_5_RANGE);
			wait.delay_10_us(10);

			//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
			FW_dvi->set_current(FW_ch, 1e-3, RANGE_300_MA);

			for (i = 0; i < 3; i++)
			{
				FW_dvi->set_voltage(FW_ch, -1.0, VOLT_10_RANGE);
				wait.delay_10_us(20);
				FW_dvi->set_voltage(FW_ch, 6.0, VOLT_10_RANGE);
				wait.delay_10_us(20);
			}
			REQ_ovi->set_voltage(REQ_ch, 1.0, VOLT_5_RANGE);
			FW_dvi->set_voltage(FW_ch, -0.5, VOLT_10_RANGE);

			//Ramp up FW so SR will toggle from Low to High
			search_SR_th_TM1(&SRth[trim_code]);

			Power_Down_Secondary();
		}

		// Write to debug file
		time_t rawtime;
		struct tm * timeinfo;
		char timestamp[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timestamp, 80, "%y%m%d%H%M%S", timeinfo);

		char file_name_Id1[200] ="e:\\dl4\\SRth_TM1";
		strcat (file_name_Id1, timestamp);
		strcat (file_name_Id1, ".csv");
		FILE * fpr1 = fopen(file_name_Id1, "w");
		if (! fpr1) return;
		
		fprintf(fpr1, "DUT,trim_code,SRth(V)\n");

		for (trim_code = 0; trim_code < CODE_SIZE; trim_code++)
		{
				fprintf(fpr1, "%d,%d,%8.4f\n", SERIAL_NUM, trim_code, SRth[trim_code] * 1e3);
		}
		fprintf(fpr1,"\n" );

		fclose(fpr1);
		delay(10);
	}
}
