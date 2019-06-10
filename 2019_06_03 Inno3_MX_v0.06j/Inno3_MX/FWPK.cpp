//==============================================================================
// FWPK.cpp (User function)
// 
//    void FWPK_user_init(test_function& func)
//    void FWPK(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "FWPK.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void FWPK_user_init(test_function& func)
{
	FWPK_params *ours;
    ours = (FWPK_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void FWPK(test_function& func)
{
    // The two lines below must be the first two in the function.
    FWPK_params *ours;
    ours = (FWPK_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 20;

	Func_name = "FWPK";

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_FWPK,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//return;	//*********** EEFU - to be remove ***********//

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//Trimming DOPL bit will disable FWPK
	if(!gTrim_DOPL_S && gSR_AF_post[gDOPL_AF_Addr_Start]==0)
	{
		float 	tDableOn_300kHz=0.0,
				tDableOn_300kHz_1stR=0.0,
				tDableOn_1MHz=0.0,
				tDableOn_1MHz_1stR=0.0,
				tDableOn_1MHz_1stR_2nd=0.0,
				FWPK_tDableOntime=0.0, 
				FWPK_Timer=0.0, 
				FWPK_4Ring=0.0, 
				FWPK_DableOnHi4Ring=0.0,
				FWPK_tVOxDble=0.0,
				HS_Ring1V_FaultP=0.0,
				MaxF_FaultP=0.0,
				MinF_FaultP=0.0;
		int		i=0;

		Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug  rlb

		//------------------------------------------------------------------------------------------------------------------------
		//--------------------FWPK Switching START -------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------------------------
		// FWPK with gage digitizer capture takes ~50ms test time.  PU + capture
		float ddd_clock_freq = ddd_7->ddd_get_clock_freq();
		
		if (ddd_clock_freq != 4.0e6)
		{
			ddd_7->ddd_set_clock_period(0.25e-6);		//
			wait.delay_10_us(250);						// Delay helps tDbleOn300kHz
		}
		//SAMPLE_SIZE = GAGE_POST_8K;
		//INNO_Gage_ChanAB_setup(0.15);	// Only do it when SAMPLE_SIZE is diff from previous. 


		//***************************
		//** 300kHz Half Ring Test **
		//***************************
		Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);

		Secondary_Vout_Clock_to_Testmode(gProgReadTestMode2_S);
		
		//setup to measure signal come out of SR
		tmu_6->close_relay(TMU_CHAN_A_DUT2);	// Connect TMU_CHAN_A2 to SR pin
		tmu_6->start_trigger_setup( 2.4,	POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);	// Rising edge of SR pulse
		tmu_6->stop_trigger_setup(  2.2,	NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);	// Rising edge of SR pulse

		//REQ 5V -> 1V
		REQ_ovi->set_voltage(REQ_ch, 5.0, 		RANGE_5_V);	// OVI_1_2
		wait.delay_10_us(10);
		REQ_ovi->set_voltage(REQ_ch, 1.0, 		RANGE_5_V);	// OVI_1_2
		//wait.delay_10_us(10);
		
		//Provide 3 negative 1.67us pulses on FW to allow handshake
		ddd_7->ddd_set_hi_level(1.0);
		ddd_7->ddd_set_lo_level(-1.0);
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
		DDD_Wait_Pattern_End(High_pat_FW_start, High_pat_FW_stop);
		Close_relay(K21);		// Connect FW to DDD7_3
		delay(1);				// IMPORTANT - make before break
		Open_relay(K18);		// Disconnect FW from DVI11_1
		delay(3);
		ddd_7->ddd_set_hi_level(5.0);
		wait.delay_10_us(4);
		ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_3rd_pulse_stop-1); //make sure 1.67us pulses
		DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start,FW_Neg_3rd_pulse_stop-1);

		//3a. FW 5V -> -1V
		ddd_7->ddd_run_pattern(Low_FW_pat_start,Low_FW_pat_stop-1);
		DDD_Wait_Pattern_End(Low_FW_pat_start,Low_FW_pat_stop-1);

		//3b. REQ 1V -> 0.5V
		REQ_ovi->set_voltage(REQ_ch, 0.5, 		RANGE_5_V);	// OVI_1_2
		wait.delay_10_us(10);

		//3c. FW Send one -1V to 5V (1.67us for 300KHz) / (500ns for 1MHz) positive pulse for FWPK programming
		ddd_7->ddd_run_pattern(FWPK_pos_1p75us_pulse_start,FWPK_pos_1p75us_pulse_stop); 
		wait.delay_10_us(2);

		//4a. REQ 0.5V -> 2V
		REQ_ovi->set_voltage(REQ_ch, 2.0, 		RANGE_5_V);	// OVI_1_2

		//4b. FW -1V -> 5V
		tmu_6->reset();
		tmu_6->arm();
		ddd_7->ddd_run_pattern(High_pat_FW_start,High_pat_FW_stop-1); 
		DDD_Wait_Pattern_End(High_pat_FW_start,High_pat_FW_stop-1);

		//4c. FW Send 1us negative pulse && Measure SR positive pulse width as tDableOn 300kHz (expect ~500ns)
		ddd_7->ddd_run_pattern(FWPK_300kHz_Ring_pulse_start, (FWPK_300kHz_Ring_pulse_start+1/(Dclk_period*1e6))+1);
		DDD_Wait_Pattern_End(FWPK_300kHz_Ring_pulse_start, (FWPK_300kHz_Ring_pulse_start+1/(Dclk_period*1e6))+1);

		tDableOn_300kHz = tmu_6->read(50e-6);

		//5. Switch 2ndary into Prog.Read TestMode4 by 4 VOUT positive pulses.  Check SR pin status, should be LOW
		//Observe SR status here (save this for EeFu/Kaumudi)

		//----------------------------------
		//-- DableOn_300kHz_1stR	Start --
		//----------------------------------
		////2. Switch 2ndary into Prog.Read TestMode7 by another 6 VOUT positive pulses
		ddd_7->ddd_set_lo_level(0.1);				
		SR_dvi2k->close_relay(CONN_SENSE1);	//SR
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, RANGE_10_V);	//SR

		Close_relay(K27);	//Vout to DDD
		delay(3);
		VO_dvi->open_relay(CONN_SENSE0);
		VO_dvi->open_relay(CONN_FORCE0);
		delay(1);

		//Make sure SR stays high before issuing the VOUT pulse
		float dummy_vSR = -99.0;
		dummy_vSR = SR_dvi2k->measure_average(25);

		if(dummy_vSR < 0.01)	//Vout glitch once exist
		{
			DDD_Clock_Vout_Antifuse(9);		//extra # of vout pulses	including the 4 from step 5. above
		}
		else if(dummy_vSR < 0.05)	//Vout glitch twice exist
		{
			DDD_Clock_Vout_Antifuse(8);		//extra # of vout pulses	including the 4 from step 5. above
		}
		else
		{
			DDD_Clock_Vout_Antifuse(10);		//extra # of vout pulses	including the 4 from step 5. above
		}

		// These will get close/open after done with the tests that needs VO clocking to get into TEST MODES
		VO_dvi->close_relay(CONN_SENSE0);
		VO_dvi->close_relay(CONN_FORCE0);
		Open_relay(K27);
		delay(3);

		//3. FW Send 1us negative pulse && Measure SR positive pulse width as tDableOn 300kHz (expect ~500ns)
		ddd_7->ddd_set_lo_level(-1.0);	//for FW negative pulse
		wait.delay_10_us(10);

		for (i = 0; i < 3; i++)
		{
			tmu_6->reset();
			tmu_6->arm();
			wait.delay_10_us(4);
			ddd_7->ddd_run_pattern(FWPK_300kHz_Ring_pulse_start, FWPK_300kHz_Ring_pulse_start+5);
			wait.delay_10_us(10);
			tDableOn_300kHz_1stR = tmu_6->read(50e-6);
			if(tDableOn_300kHz_1stR > 900e-9 && tDableOn_300kHz_1stR < 1300e-9)
			{
				break;
			}
		}

		//4d. Measure FW rising to SR falling delay as tdly_CCMwin_1stR.  

		//----------------------------------
		//-- DableOn_300kHz_1stR	Stop  --
		//----------------------------------

		//Power down for tDable 300kHz
		Power_Down_Secondary();
		Open_relay(K21);		// Disconnect FW to DDD7_3
		delay(1);				// IMPORTANT - make before break
		tmu_6->open_relay(TMU_CHAN_A_DUT2);	// disConnect TMU_CHAN_B2 to SR pin
		delay(3);

		//****************************
		//** tDable 1MHz	Start	**
		//****************************
		Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);

		Secondary_Vout_Clock_to_Testmode(gProgReadTestMode2_S);

		tmu_6->close_relay(TMU_CHAN_A_DUT2);	// Connect TMU_CHAN_A2 to SR pin
		//tmu_6->start_trigger_setup( 1.8,	POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);	// Rising edge of SR pulse
		//tmu_6->stop_trigger_setup(  1.5,	NEG_SLOPE, TMU_CHAN_A, TMU_IN_10V);	// Rising edge of SR pulse

		//REQ 5V -> 1V
		REQ_ovi->set_voltage(REQ_ch, 5.0, 		RANGE_5_V);	// OVI_1_2
		wait.delay_10_us(10);
		REQ_ovi->set_voltage(REQ_ch, 1.0, 		RANGE_5_V);	// OVI_1_2
		//wait.delay_10_us(10);

		//Provide 3 negative 1.67us pulses on FW to allow handshake
		ddd_7->ddd_set_hi_level(1.0);
		ddd_7->ddd_set_lo_level(-1.0);
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
		DDD_Wait_Pattern_End(High_pat_FW_start, High_pat_FW_stop);
		Close_relay(K21);		// Connect FW to DDD7_3
		delay(1);				// IMPORTANT - make before break
		Open_relay(K18);		// Disconnect FW from DVI11_1
		delay(3);
		ddd_7->ddd_set_hi_level(5.0);
		wait.delay_10_us(4);
		ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_3rd_pulse_stop-1); //make sure 1.67us pulses
		DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start,FW_Neg_3rd_pulse_stop-1);

		//3a. FW 5V -> -1V
		ddd_7->ddd_run_pattern(Low_FW_pat_start,Low_FW_pat_stop-1);
		DDD_Wait_Pattern_End(Low_FW_pat_start,Low_FW_pat_stop-1);

		//3b. REQ 1V -> 0.5V
		REQ_ovi->set_voltage(REQ_ch, 0.5, 		RANGE_5_V);	// OVI_1_2
		wait.delay_10_us(10);

		//3c. FW Send one -1V to 5V (1.67us for 300KHz) / (500ns for 1MHz) positive pulse for FWPK programming
		ddd_7->ddd_run_pattern(FWPK_pos_0p50us_pulse_start,FWPK_pos_0p50us_pulse_stop); 
		wait.delay_10_us(2);

		//4a. REQ 0.5V -> 2V
		REQ_ovi->set_voltage(REQ_ch, 2.0, 		RANGE_5_V);	// OVI_1_2
		wait.delay_10_us(10);

		//4b. FW -1V -> 5V
		tmu_6->reset();
		tmu_6->arm();
		ddd_7->ddd_run_pattern(High_pat_FW_start,High_pat_FW_stop-1); 
		DDD_Wait_Pattern_End(High_pat_FW_start,High_pat_FW_stop-1);

		//4c. FW Send 500ns negative pulse && Measure SR positive pulse width as tDableOn 1MHz (expect ~150ns)
		ddd_7->ddd_run_pattern(FWPK_neg_0p50us_pulse_start,FWPK_neg_0p50us_pulse_stop-1);
		DDD_Wait_Pattern_End(FWPK_neg_0p50us_pulse_start,FWPK_neg_0p50us_pulse_stop-1);

		tDableOn_1MHz = tmu_6->read(50e-6);

		//5. Switch 2ndary into Prog.Read TestMode4 by 4 VOUT positive pulses.  Check SR pin status, should be LOW
		//Observe SR status here (save this for EeFu/Kaumudi)

		//----------------------------------
		//-- DableOn_1MHz_1stR	Start --
		//----------------------------------
		//2. Switch 2ndary into Prog.Read TestMode7 by another 6 VOUT positive pulses
		ddd_7->ddd_set_lo_level(0.1);				
		SR_dvi2k->close_relay(CONN_SENSE1);	//SR
		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, RANGE_10_V);	//SR

		Close_relay(K27);	//Vout to DDD
		delay(3);
		VO_dvi->open_relay(CONN_SENSE0);
		VO_dvi->open_relay(CONN_FORCE0);
		delay(1);

		//Make sure SR stays high before issuing the VOUT pulse
		dummy_vSR = -99.0;
		dummy_vSR = SR_dvi2k->measure_average(25);

		if(dummy_vSR < 0.01)	//Vout glitch once exist
		{
			DDD_Clock_Vout_Antifuse(9);		//extra # of vout pulses	including the 4 from step 5. above
		}
		else if(dummy_vSR < 0.05)	//Vout glitch twice exist
		{
			DDD_Clock_Vout_Antifuse(8);		//extra # of vout pulses	including the 4 from step 5. above
		}
		else
		{
			DDD_Clock_Vout_Antifuse(10);		//extra # of vout pulses	including the 4 from step 5. above
		}

		// These will get close/open after done with the tests that needs VO clocking to get into TEST MODES
		VO_dvi->close_relay(CONN_SENSE0);
		VO_dvi->close_relay(CONN_FORCE0);
		Open_relay(K27);
		delay(3);

		//3. FW Send 1us negative pulse && Measure SR positive pulse width as tDableOn 300kHz (expect ~500ns)
		ddd_7->ddd_set_lo_level(-1.0);	//for FW negative pulse
		wait.delay_10_us(10);

		for(i=1; i<=3; i++)
		{
			tmu_6->reset();
			tmu_6->arm();
			ddd_7->ddd_run_pattern(FWPK_neg_0p50us_pulse_start,FWPK_neg_0p50us_pulse_stop); 
			wait.delay_10_us(5);
			tDableOn_1MHz_1stR = tmu_6->read(50e-6);//if no Vout glitch it would fail.  if there's vout glitch, it would pass
			if(tDableOn_1MHz_1stR > 250e-9 && tDableOn_1MHz_1stR < 350e-9)
			{
				break;
			}
		}

		//----------------------------------
		//-- DableOn_1MHz_1stR	Stop  --
		//----------------------------------

		//Power down for tDable 300kHz
		Power_Down_Secondary();
		Open_relay(K21);		// Disconnect FW to DDD7_3
		delay(1);				// IMPORTANT - make before break
		tmu_6->open_relay(TMU_CHAN_A_DUT2);	// disConnect TMU_CHAN_B2 to SR pin
		delay(3);

		//****************************
		//** tDable 1MHz	Stop	**
		//****************************
		

		Open_relay(K5);			//Disconnect SR from 5nF
		Open_relay(K26);		//Disconnect SR from DDD-7-5


		////ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
		////wait.delay_10_us(10);
		////ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
		////wait.delay_10_us(10);
		////ddd_7->ddd_run_pattern(Low_FW_pat_start, Low_FW_pat_stop);
		////wait.delay_10_us(4);
		////ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
		////wait.delay_10_us(4);

		////Close_relay(K21);		// Connect FW to DDD7_3
		////delay(1);
		////Open_relay(K18);		// Disconnect FW from DVI11_1

		////SR_dvi2k->open_relay(CONN_FORCE1);
		////SR_dvi2k->open_relay(CONN_SENSE1);
		////delay(3);

		////ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_3rd_pulse_stop);
		////DDD_Wait_Pattern_End(FW_Neg_1st_pulse_start, FW_Neg_3rd_pulse_stop);
		////
		////ddd_7->ddd_run_pattern(Low_FW_pat_start, Low_FW_pat_stop);

		////REQ_ovi->set_voltage(REQ_ch, gREQ_V_RingDet, 		RANGE_5_V);	// OVI_1_2
		////wait.delay_10_us(4);

		////ddd_7->ddd_run_pattern(FWPK_pos_1p75us_pulse_start, FWPK_pos_1p75us_pulse_stop);
		////DDD_Wait_Pattern_End(FWPK_pos_1p75us_pulse_start, FWPK_pos_1p75us_pulse_stop);
		//////ddd_7->ddd_run_pattern(FWPK_pos_0p50us_pulse_start, FWPK_pos_0p50us_pulse_stop);
		//////DDD_Wait_Pattern_End(FWPK_pos_0p50us_pulse_start, FWPK_pos_0p50us_pulse_stop);

		////REQ_ovi->set_voltage(REQ_ch, gREQ_2V, 		RANGE_5_V);	// OVI_1_2
		////ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
		////wait.delay_10_us(4);

		////tmu_6->arm();
		////wait.delay_10_us(4);

		////ddd_7->ddd_run_pattern(FWPK_neg_1p75us_pulse_start, FWPK_neg_1p75us_pulse_stop);
		////DDD_Wait_Pattern_End(FWPK_neg_1p75us_pulse_start, FWPK_neg_1p75us_pulse_stop);

		//////Measure tDableOn_300kHz
		////tDableOn_300kHz =  tmu_6->read(100e-6);		
		////if (tDableOn_300kHz > 1) tDableOn_300kHz = 0.999;	// Prevent display error.

		//////***************************************************************************
		////REQ_ovi->set_voltage(REQ_ch, gREQ_V_Idle, 		RANGE_5_V);	// OVI_1_2
		////Close_relay(K18);		// Connect FW to DVI11_1
		////delay(1);
		////Open_relay(K21);		// Disconnect FW from DDD7_3
		////delay(3);

////		Secondary_Vout_Clock_to_Testmode(gProgReadTestMode5_S);		// 10 VO pulses to TestMode7
////
////		ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
////		wait.delay_10_us(10);
////		ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
////		wait.delay_10_us(10);
////		ddd_7->ddd_run_pattern(Low_FW_pat_start, Low_FW_pat_stop);
////		wait.delay_10_us(4);
////		ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
////		wait.delay_10_us(4);
////
////		Close_relay(K21);		// Connect FW to DDD7_3
////		delay(1);
////		Open_relay(K18);		// Disconnect FW from DVI11_1
////		delay(3);
////
////		REQ_ovi->set_voltage(REQ_ch, gREQ_2V, 		RANGE_5_V);	// OVI_1_2
////		ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
////		wait.delay_10_us(4);
////
////		tmu_6->arm();
////		wait.delay_10_us(4);
////
////		ddd_7->ddd_run_pattern(FWPK_neg_1p75us_pulse_start, FWPK_neg_1p75us_pulse_stop);
////
////		//pulse.do_pulse();//********************************************************
////
////		DDD_Wait_Pattern_End(FWPK_neg_1p75us_pulse_start, FWPK_neg_1p75us_pulse_stop);
////
////		//Measure tDableOn_300kHz
////		tDableOn_300kHz =  tmu_6->read(100e-6);		
////		if (tDableOn_300kHz > 1) tDableOn_300kHz = 0.999;	// Prevent display error.
////
////			//*****
////			Open_relay(K21);	//FW to DDD-7-3
////			Close_relay(K18);	//FW to dvi-11-1
////			Open_relay(K17);	//FB to DDD-7-2
////			delay(4);
////			Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
////
////			//HL removed due to cause of repeatability for both RS and Turret.
////			//VO_dvi->set_voltage(VO_ch, 0.0, 		RANGE_5_V);	// DVI_9_0  RLB
////
////			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode2_S);
////
////			if(g_TurretCB || LB_Rev>=5 )		BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	
////			else								BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	
////
////			VO_dvi->set_current(VO_ch, 200.0e-3,		RANGE_300_MA);	
////			VO_dvi->set_voltage(VO_ch, 1, 		RANGE_5_V);	// DVI_9_0  RLB
////
////			//Secondary_Vout_Clock_to_Testmode(gProgReadTestMode4_S);
////			//Open_relay(K27);	//Disconnect Vout from DDD-7-4 (Testmode used)
////			//Setup FW to clock 1 FW pulse to latch, then 1 double FWPK pulses.  Note the 1 double FWPK pulses is to have device learn the pulses
////			if((LB_Rev >= 5||g_TurretCB) && (OPCODE==4200||OPCODE== 4250))
////			{
////				VO_dvi->set_voltage(VO_ch, 1.15, 		RANGE_5_V);	
////			}
////			else if(LB_Rev >= 5 && (OPCODE==4300||OPCODE== 4500))
////			{
////				VO_dvi->set_voltage(VO_ch, 1.05, 		RANGE_5_V);	
////			}
////			else
////			{
////				if(OPCODE==4300||OPCODE== 4500)		VO_dvi->set_voltage(VO_ch, 1.05, 	RANGE_5_V);
////				else								VO_dvi->set_voltage(VO_ch, 1.15, 	RANGE_5_V);
////			}
////
////			FW_dvi->set_voltage(FW_ch, 0.1, 		VOLT_50_RANGE);	// DVI_11_1
////			delay(1);
////			ddd_7->ddd_set_lo_level(-0.1);
////			ddd_7->ddd_set_hi_level(4.0);		// FW toggle high to 4V  (per Qing 10/17/2016)
////			delay(1);
////			if(g_TurretCB)
////			{
////				//Strange, same pattern at different location, causing FW to drop below GND.
////				//ddd_7->ddd_run_pattern(Low_FW_pat_start,	Low_FW_pat_stop);
////				//ddd_7->ddd_run_pattern(Low_pat_start,	Low_pat_stop);
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);
////			}
////			else
////			{
////					ddd_7->ddd_run_pattern(Low_pat_start,	Low_pat_stop);
////			}
////			
////			wait.delay_10_us(100);
////			Close_relay(K21);	//FW to DDD-7-3 (HOT SWAP)
////			if(g_TurretCB)  
////			{
////				FW_dvi->set_current(FW_ch, 0.0e-3,		RANGE_30_MA);
////				FW_dvi->set_voltage(FW_ch, 0.1, 		VOLT_50_RANGE);	// DVI_11_1
////				delay(1);			
////			}
////			Open_relay(K18);   // FW disconnect from DVI-11-1 for RS setup.
////			delay(4);
////			ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
////			wait.delay_10_us(10);
//////pulse.do_pulse();
////			//Setup for FB connects to DDD-7-2
////			REQ_ovi->set_current(REQ_ch, 0,						RANGE_30_MA);
////			wait.delay_10_us(10);
////			Close_relay(K17);	//FB connect to DDD-7-2 in parallel with 1kohm in series with ovi-1-2
////			delay(4);
////			//Setup to have FW do request and FW learn pulse then DableON pulse
////			ddd_7->ddd_set_lo_level(-0.7);		
////			delay(1);
////
////			ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
////			wait.delay_10_us(g_tHandshake_SSS+5);
////			if(!g_TurretCB)
////			{
////				tmu_6->arm();	
////			}
////
////
////
////			ddd_7->ddd_run_pattern(FWPK_300kHz_Ring_pulse_start, FWPK_300kHz_Ring_pulse1_stop);
////			
////			if(LB_Rev>=5 )		
////			{	
////				wait.delay_10_us(g_tHandshake_SSS+1);
////			}
////			else if(g_TurretCB)
////			{
////				wait.delay_10_us(g_tHandshake_SSS+3);
////			}
////			else							
////			{
////				wait.delay_10_us(g_tHandshake_SSS+1);
////			}
////		
////			if(g_TurretCB)
////			{
////				//HL moved it here.  Invalid measurement due to the above DDD run to cause wrong pulse.
////				tmu_6->arm();
////			}
////			ddd_7->ddd_run_pattern(FWPK_300kHz_Ring_pulse_start_FB, FWPK_300kHz_Ring_pulse1_stop_FB);
////			wait.delay_10_us(10);
////			//Measure tDableOn_300kHz
////			tDableOn_300kHz =  tmu_6->read(100e-6);		
////			if (tDableOn_300kHz > 1)
////				tDableOn_300kHz = 0.999;	// Prevent display error.
////			Open_relay(K17);	//Disconnect FB from DDD
		
////		//******************************************************************************************
////		//** 1MHz Half Ring Test (tDable_ON_1MHz, FWPK_Timer_us, FWPK_4Ring, FWPK_DableOnHi4Ring) **
////		//******************************************************************************************
////
////		//============== tDable_ON_1MHZ and FWPK_Timer_us
////			VBPP_Negative_Cycle();
////			Power_Down_Secondary();
////			Open_relay(K21);	//FW to DDD-7-3
////			Close_relay(K18);	//FW to dvi-11-1	
////	
////			SAMPLE_SIZE = GAGE_POST_8K;
////			INNO_Gage_ChanAB_setup(0.15);	// Only do it when SAMPLE_SIZE is diff from previous. 
////
////			Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
////			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode2_S);
////
////			if(g_TurretCB || LB_Rev>=5 )
////			{
////				BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	
////			}
////
////			//Setup FW to clock 1 FW pulse to latch, then 1 double FWPK pulses.  Note the 1 double FWPK pulses is to have device learn the pulses
////			VO_dvi->set_current(VO_ch, 200.0e-3,		RANGE_300_MA);	
////			VO_dvi->set_voltage(VO_ch, 1, 		RANGE_5_V);	// DVI_9_0  RLB
////			delay(2); //HL added due to Turret CB repeatability issue.
////			ddd_7->ddd_set_lo_level(0.1);
////			ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
////			delay(1);
////		    if(g_TurretCB)
////			{
////				//Strange, same pattern at different location, causing FW to drop below GND.
////				//ddd_7->ddd_run_pattern(Low_FW_pat_start,	Low_FW_pat_stop);
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);
////			}
////			else
////			{
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);		
////			}
////		
////			
////			wait.delay_10_us(10);
////			Close_relay(K21);	//FW to DDD-7-3 (HOT SWAP)
////			Close_relay(K26);	//SR to SR_Buf_In for digitizer capture
////	
////			if(g_TurretCB)     
////			{          
////				FW_dvi->set_current(FW_ch, 0.0e-3,		RANGE_30_MA);
////				FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
////				delay(1);	
////			}
////			Open_relay(K18);   // FW disconnect from DVI-11-1 for RS setup.
////			delay(4);
////
////			ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
////			wait.delay_10_us(10);
////			ddd_7->ddd_set_lo_level(-0.7);		
////			delay(2);
////
////			//Setup for FB connects to DDD-7-2
////			REQ_ovi->set_current(REQ_ch, 0,						RANGE_30_MA);
////			wait.delay_10_us(20);
////			Close_relay(K17);	//FB connect to DDD-7-2 in parallel with 1kohm in series with ovi-1-2
////			delay(4);
////			Gage_Start_Capture(  );	//takes ~100us to run
////			if(g_TurretCB)
////			{
////
////				ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
////				wait.delay_10_us(g_tHandshake_SSS+2);
////				ddd_7->ddd_run_pattern(FWPK_1MHz_Ring_learn_pulse_start, FWPK_1MHz_Ring_learn_pulse_stop);
////				wait.delay_10_us(g_tHandshake_SSS+1);
////			}
////			else
////			{
////				ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
////				wait.delay_10_us(g_tHandshake_SSS+2);
////				ddd_7->ddd_run_pattern(FWPK_1MHz_Ring_learn_pulse_start, FWPK_1MHz_Ring_learn_pulse_stop);
////				wait.delay_10_us(g_tHandshake_SSS+1);	//delay of +1 is to compensate for the CsDo command timing.
////			}
////
////			//Gage_Start_Capture(  );
////			ddd_7->ddd_run_pattern(FWPK_1MHz_Ring_Dable_pulse_start_FB, FWPK_1MHz_Ring_Dable_pulse_stop_FB);
////			CsDo(hSystem, ACTION_FORCE);	//Force capture.  (Captures about 120us in total.  Takes ~6k samples)
////			wait.delay_10_us(10);
////
////			Gage_Wait_For_Capture_Complete();
////	
////			//DEBUG=1;
////			WAVE_NAME =  "FWPK_Timer";
////			Gage_Find_FWPK_DableON_Timer(&FWPK_tDableOntime, &FWPK_Timer);
////			//DEBUG=0;
////			if(FWPK_tDableOntime > 150e-9)
////				tDableOn_1MHz =  999e-9;	//prevent display error.  (999 would cause a display error)	
////			else
////				tDableOn_1MHz =  FWPK_tDableOntime;		
////
////			Open_relay(K17);	//Disconnect FB from DDD
////
////
////		//============== FWPK_4Ring, FWPK_DableOnHi4Ring
////			VBPP_Negative_Cycle();
////			Power_Down_Secondary();
////			Open_relay(K21);	//FW to DDD-7-3
////			Close_relay(K18);	//FW to dvi-11-1
////		
////		
////			//SAMPLE_SIZE = GAGE_POST_8K;
////			//INNO_Gage_ChanAB_setup(0.15);	// Only do it when SAMPLE_SIZE is diff from previous. 
////
////			Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
////			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode2_S);
////
////			if(g_TurretCB || LB_Rev>=5 )
////			{
////				BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	
////			}
////
////			//Setup FW to clock 1 FW pulse to latch, then 1 double FWPK pulses.  Note the 1 double FWPK pulses is to have device learn the pulses
////			VO_dvi->set_current(VO_ch, 200.0e-3,		RANGE_300_MA);	
////			VO_dvi->set_voltage(VO_ch, 1, 		RANGE_5_V);	// DVI_9_0  RLB
////			delay(2); //HL added due to Turret CB repeatability issue.
////			ddd_7->ddd_set_lo_level(0.1);
////			ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
////			delay(1);
////
////
////			if(g_TurretCB)
////			{
////				//Strange, same pattern at different location, causing FW to drop below GND.
////				//ddd_7->ddd_run_pattern(Low_FW_pat_start,	Low_FW_pat_stop);
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);
////			}
////			else
////			{
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);		
////			}
////		
////
////			wait.delay_10_us(100);
////			Close_relay(K21);	//FW to DDD-7-3 (HOT SWAP)
////			Close_relay(K26);	//SR to SR_Buf_In for digitizer capture
////			//Open_relay(K18);	//FW disconnect from DVI-11-1
////			if(g_TurretCB)     
////			{       
////				FW_dvi->set_current(FW_ch, 0.0e-3,		RANGE_30_MA);
////				FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
////				delay(1);
////			}
////				
////		
////			Open_relay(K18);   // FW disconnect from DVI-11-1 for RS setup.
////			delay(4);
////
////			ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
////			wait.delay_10_us(10);
////			ddd_7->ddd_set_lo_level(-0.7);		
////			delay(2);
////
////			//Setup for FB connects to DDD-7-2
////			REQ_ovi->set_current(REQ_ch, 0,						RANGE_30_MA);
////			wait.delay_10_us(20);
////			Close_relay(K17);	//FB connect to DDD-7-2 in parallel with 1kohm in series with ovi-1-2
////			delay(4);
//////
////			Gage_Start_Capture(  );
////			ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
////			wait.delay_10_us(g_tHandshake_SSS+2);
////			ddd_7->ddd_run_pattern(FWPK_1MHz_Ring_learn_pulse_start, FWPK_1MHz_Ring_learn_pulse_stop);	
////			wait.delay_10_us(g_tHandshake_SSS+1);
////			
////			//Gage_Start_Capture(  );
////			ddd_7->ddd_run_pattern(FWPK_1MHz_Ring_pulse1_start_FB, FWPK_1MHz_Ring_pulse4_stop_FB);
////			CsDo(hSystem, ACTION_FORCE);	//Force capture.  (Captures about 120us in total.  Takes ~6k samples)
////			wait.delay_10_us(5);//USED TO BE 10
////
////			Gage_Wait_For_Capture_Complete();
////	
////			//DEBUG=1;
////			WAVE_NAME =  "FWPK_4Rings";
////			if(gSiliconRev_P>=3) //This fix is for both RS and Turret. Qing confirmed 7 rings are correct.
////			{
////				Gage_Find_FWPK_4Rings_Turret(&FWPK_4Ring, &FWPK_DableOnHi4Ring);
////			}
////			else
////			{
////				Gage_Find_FWPK_4Rings(&FWPK_4Ring, &FWPK_DableOnHi4Ring);
////			}
////			//DEBUG=0;
////			if(FWPK_tDableOntime > 150e-9)
////				tDableOn_1MHz =  999e-9;	//prevent display error.  (999 would cause a display error)	
////			else
////				tDableOn_1MHz =  FWPK_tDableOntime;		
////			Open_relay(K26);	//Disconnect SR from SR_Buf_In 
////			Open_relay(K17);	//Disconnect FB from DDD
////
////		//******************************************************************************************
////		//** HS_Ring1V_FaultP **
////		//******************************************************************************************
////			Power_Down_Secondary();
////			Open_relay(K21);	//FW to DDD-7-3
////			Close_relay(K18);	//FW to dvi-11-1
////			Open_relay(K17);	//Disconnect FB from DDD
////			tmu_6->open_relay(TMU_EXT_DRV3); //DVI_13 to SR pin.
////			delay(3);
////
////			Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
////			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode4_S);
////			//Setup FW to clock 1 FW pulse to latch, then 1 double FWPK pulses.  Note the 1 double FWPK pulses is to have device learn the pulses
////			//HL added for Turret CB.
////			BPS_dvi->set_current(BPS_ch, 290e-3, RANGE_300_MA);
////
////			//HL changed from 1.0V to 0.5V.  Will need to check with Charles on the proper test condition.
////			VO_dvi->set_voltage(VO_ch, 0.5, 		RANGE_5_V);	// DVI_9_0  RLB
////			FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
////			wait.delay_10_us(100);  	
////			ddd_7->ddd_set_lo_level(0.1);
////			ddd_7->ddd_set_hi_level(0.5);		// Will immediately change to this level upon execution
////			delay(1);
////			if(g_TurretCB)
////			{
////				//Strange, same pattern at different location, causing FW to drop below GND.
////				//ddd_7->ddd_run_pattern(Low_FW_pat_start,	Low_FW_pat_stop);
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);
////			}
////			else
////			{
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);		
////			}
////		
////			wait.delay_10_us(10);
////			Close_relay(K21);	//FW to DDD-7-3 (HOT SWAP)
////			if(g_TurretCB)     
////			{       
////				FW_dvi->set_current(FW_ch, 0.0e-3,		RANGE_30_MA);
////				FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
////				delay(1);
////			}	
////			Open_relay(K18);   // FW disconnect from DVI-11-1 for RS setup.
////			delay(4);
////			ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
////			wait.delay_10_us(10);
////			ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
////			ddd_7->ddd_set_hi_level(0.5);		// Will immediately change to this level upon execution
////			delay(1);
////	//////////
////
////			//Setup to measure SR signal
////			SR_dvi2k->close_relay(CONN_SENSE1);
////			SR_dvi2k->open_relay(CONN_FORCE1);
////			tmu_6->open_relay(TMU_CHAN_B_DUT2);  //HL disconnected TMU from SR pin.
////			SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, VOLT_10_RANGE);
////
////			//Provide 3 negative pulses on FW to allow handshake and FWPK programming. Pulse width is 1.6us 
////			ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
////			wait.delay_10_us(20); 
////			ddd_7->ddd_run_pattern(FWPK_300kHz_Ring_pulse_start, FWPK_300kHz_Ring_pulse1_stop);
////			wait.delay_10_us(20);
////			//If SR pin output is high, datalog HS_Ring1V_FaultP to be 1  
////			HS_Ring1V_FaultP = SR_dvi2k->measure_average(5);
////			if(HS_Ring1V_FaultP > 4)	HS_Ring1V_FaultP = 1;
////			else						HS_Ring1V_FaultP = 0;
////
////		//******************************************************************************************
////		//** MaxF_FaultP
////		//******************************************************************************************
////			Power_Down_Secondary();
////			wait.delay_10_us(100);  	
////	//		ddd_7->ddd_set_lo_level(0.1);
////			ddd_7->ddd_set_hi_level(2.0);		// Will immediately change to this level upon execution
////			wait.delay_10_us(100); 
////			Open_relay(K21);	//FW to DDD-7-3
////			Close_relay(K18);	//FW to dvi-11-1
////			delay(3);
////	//////////
////			Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
////			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode4_S);
////
////			if(g_TurretCB || LB_Rev>=5 )
////			{
////				BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	
////			}
////			//Setup FW to clock 1 FW pulse to latch, then 1 double FWPK pulses.  Note the 1 double FWPK pulses is to have device learn the pulses
////			FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
////			wait.delay_10_us(100);  	
////			ddd_7->ddd_set_lo_level(0.1);
////			ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
////			delay(1);
////			if(g_TurretCB)
////			{
////				//Strange, same pattern at different location, causing FW to drop below GND.
////				//ddd_7->ddd_run_pattern(Low_FW_pat_start,	Low_FW_pat_stop);
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);
////			}
////			else
////			{
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);		
////			}
////		
////			
////
////			wait.delay_10_us(10);
////			Close_relay(K21);	//FW to DDD-7-3 (HOT SWAP)
////			if(g_TurretCB)     
////			{       
////				FW_dvi->set_current(FW_ch, 0.0e-3,		RANGE_30_MA);
////				FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
////				delay(1);
////			}	
////			Open_relay(K18);	//FW disconnect from DVI-11-1
////			delay(4);
////			ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
////			wait.delay_10_us(10);
////			ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
////			ddd_7->ddd_set_hi_level(4.0);		// FW (2V)
////			delay(1);
////
////			////Setup to measure SR signal
////			SR_dvi2k->close_relay(CONN_SENSE1);
////			SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, VOLT_10_RANGE);
////
////			//Provide 3 negative pulses on FW to allow handshake and FWPK programming. Pulse width is 0.5us 
////			ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
////			wait.delay_10_us(5);
////			ddd_7->ddd_run_pattern(FWPK_p5us_Ring_pulse_start, FWPK_p5us_Ring_pulse_stop);
////			wait.delay_10_us(20);
////
////			//If SR pin output is high, datalog HS_Ring1V_FaultP to be 1  
////			MaxF_FaultP = SR_dvi2k->measure_average(5);
////			if(MaxF_FaultP > 4)			MaxF_FaultP = 1;
////			else						MaxF_FaultP = 0;
////
////		//******************************************************************************************
////		//** MinF_FaultP
////		//******************************************************************************************
////			Power_Down_Secondary();
////			Open_relay(K21);	//FW to DDD-7-3
////			Close_relay(K18);	//FW to dvi-11-1
////			delay(3);
////	//////////
////			Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
////			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode4_S);
////
////			if(g_TurretCB || LB_Rev>=5 )
////			{
////				BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	
////			}
////
////			//Setup FW to clock 1 FW pulse to latch, then 1 double FWPK pulses.  Note the 1 double FWPK pulses is to have device learn the pulses
////			FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
////			wait.delay_10_us(100);  	
////			ddd_7->ddd_set_lo_level(0.1);
////			ddd_7->ddd_set_hi_level(2.0);		// Will immediately change to this level upon execution
////			delay(1);
////			if(g_TurretCB)
////			{
////				//Strange, same pattern at different location, causing FW to drop below GND.
////				//ddd_7->ddd_run_pattern(Low_FW_pat_start,	Low_FW_pat_stop);
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);
////			}
////			else
////			{
////				ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);		
////			}
////		
////			wait.delay_10_us(10);
////			Close_relay(K21);	//FW to DDD-7-3 (HOT SWAP)
////			if(g_TurretCB)     
////			{       
////				FW_dvi->set_current(FW_ch, 0.0e-3,		RANGE_30_MA);
////				FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
////				delay(1);
////			}	
////			Open_relay(K18);	//FW disconnect from DVI-11-1
////			delay(4);
////			ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
////			wait.delay_10_us(10);
////			ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
////			ddd_7->ddd_set_hi_level(2.0);		// FW (2V)
////			delay(1);
////
////			//Setup to measure SR signal
////			SR_dvi2k->close_relay(CONN_SENSE1);
////			SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, VOLT_10_RANGE);
////
////			//Provide 3 negative pulses on FW to allow handshake and FWPK programming. Pulse width is 0.5us 
////			ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop);
////			wait.delay_10_us(5);
////
////			ddd_7->ddd_run_pattern(FWPK_4us_Ring_pulse_start, FWPK_4us_Ring_pulse_stop);
////			wait.delay_10_us(20);
////	//////Try faster pulse and see if SR go from low to high
////	////ddd_7->ddd_set_clock_period(80e-9);		
////	////wait.delay_10_us(5);
////	////ddd_7->ddd_run_pattern(FWPK_p5us_Ring_pulse_start, FWPK_p5us_Ring_pulse_stop);
////	////wait.delay_10_us(20);
////
////			//If SR pin output is high, datalog HS_Ring1V_FaultP to be 1  
////			MinF_FaultP = SR_dvi2k->measure_average(5);
////			if(MinF_FaultP > 4)			MinF_FaultP = 1;
////			else						MinF_FaultP = 0;
////
////		//Power-down and reset relays
////		FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
////		wait.delay_10_us(100);  	
////		ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
////		ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
////		delay(1);
////		ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);
////		wait.delay_10_us(10);
////		Open_relay(K21);	//FW to DDD-7-3
////		Open_relay(K26);	//SR to DDD-7-5
////		Open_relay(K27);	//Disconnect Vout from DDD-7-4 (Testmode used)
////		tmu_6->open_relay(TMU_CHAN_B_DUT2);	 // TMU CHB to SR
////
////		//--------------------FWPK Switching END ---------------------------------------------------------------------------------

		// Power down
		dvi_13->open_relay(BUS_SENSE1);
		dvi_13->open_relay(BUS_FORCE1);
		mux_14->open_relay(MUX_3_BUS3);
		Power_Down_Secondary();
		Power_Down_Primary();
		Disconnect_InvSyn_IM();

		D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0	
		VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
		//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);		// OVI_1_0
		wait.delay_10_us(10);
 		tmu_6->open_relay(TMU_HIZ_DUT1);	// Disconnect TMU HIZ from Drain 
 		tmu_6->open_relay(TMU_HIZ_DUT3);	// Disconnect TMU HIZ from Vpin
		tmu_6->open_relay(TMU_CHAN_A_DUT1);	// Disconnect TMU CHA from FW
		Open_relay(K3);
		Open_relay(KC5);
		Open_relay(KC6);
		Open_relay(K2);
		Open_relay(K16);
		Open_All_Relays();


		PiDatalog(func, A_tDableOn_300kHz_S,		tDableOn_300kHz,		set_fail_bin,	POWER_NANO);
		PiDatalog(func, A_tDableOn_1MHz_S,			tDableOn_1MHz,			set_fail_bin,	POWER_NANO);
		//PiDatalog(func, A_FWPK_Timer_S,				FWPK_Timer,				set_fail_bin,	POWER_MICRO);
		//PiDatalog(func, A_FWPK_4Rings_S,			FWPK_4Ring,				set_fail_bin,	POWER_UNIT);
		//PiDatalog(func, A_DableOnHi4Ring_S,			FWPK_DableOnHi4Ring,	set_fail_bin,	POWER_UNIT);
		//PiDatalog(func, A_FWPK_tVOxDble_S,			FWPK_tVOxDble,			set_fail_bin,	POWER_MICRO);
		//PiDatalog(func, A_HS_Ring1V_FaultP_S,		HS_Ring1V_FaultP,		set_fail_bin,	POWER_UNIT);
		//PiDatalog(func, A_MaxF_FaultP_S,			MaxF_FaultP,			set_fail_bin,	POWER_UNIT);
		//PiDatalog(func, A_MinF_FaultP_S,			MinF_FaultP,			set_fail_bin,	POWER_UNIT);
		PiDatalog(func, A_tDableOn_300kHz_1stR_S,		tDableOn_300kHz_1stR,		set_fail_bin,	POWER_NANO);
		PiDatalog(func, A_tDableOn_1MHz_1stR_S,			tDableOn_1MHz_1stR,		set_fail_bin,	POWER_NANO);

	}

	if(gDEBUG)
	printf("\nFunction FWPK Done\n");

}
