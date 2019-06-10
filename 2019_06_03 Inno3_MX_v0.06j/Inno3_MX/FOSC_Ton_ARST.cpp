//==============================================================================
// FOSC_Ton_ARST.cpp (User function)
// 
//    void FOSC_Ton_ARST_user_init(test_function& func)
//    void FOSC_Ton_ARST(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "FOSC_Ton_ARST.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void FOSC_Ton_ARST_user_init(test_function& func)
{
	FOSC_Ton_ARST_params *ours;
    ours = (FOSC_Ton_ARST_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void FOSC_Ton_ARST(test_function& func)
{
    // The two lines below must be the first two in the function.
    FOSC_Ton_ARST_params *ours;
    ours = (FOSC_Ton_ARST_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "FOSC_Ton_ARST";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_FOSC_Ton_ARST,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	float   ToffMin_s=0.0;	
	float	FOSC_P=0.0,
			FOSC_P_Err=0.0,
			FOSC_act_P=0.0,
			TonMax_P=0.0,
			TonMax_P_Err=0.0,
			FOSC_S=0.0,
			FOSC_S_Err=0.0,
			FOSC_Min_S=0.0,
			FOSC_Min_S_Err=0.0,
			FOSC_Max_S=0.0,
			FOSC_Max_S_Err=0.0,
			FOSC_Jitter_S=0.0,
			DCmax_P=0,
			DCmax_S=0,
			tAR_On_NM_P=0.0,
			tAR_On_TM_P=0.0,
			tAR_Off_TM_P=0.0,
			fModulation_P=0.0,
			fOVL_P=0.0,
			fLB_audible_P=0.0, 
			fUB_audible_P=0.0,
			iBPS_SD=0,
			Result=0,
			tOVP  =0,
			TonMax1us_s	=0.0,	
			ToffMax1us_s	=0.0,
			TonMax1us_frq_s	=0.0,
			TonMax18us_frq_s	=0.0;

	float Fosc_ss_min_S=0,
		  Fosc_ss_Start_S=0,
		  Fosc_Start_S=0,
		  tSoft_S=0,
		  AR_disable_S=0,
		  TonMax_S=0;

	float tOVL_S=0,
		  tOVL_exp=0,
		  tOVL_act=0,
		  tOVL_Err_S=0,
		  tblock_S=0,
		  tDelta=0;
	int	  tOVL_cnt=0,
		  Rep_cnt=0;

	float tmeas=0.0, 
		  tmeas_min=0.0, 
		  tmeas_max=0.0, 
		  tmeas_Sum=0.0, 
		  tmeas_db[100]={0}, 
		  Fosc_S_Pre_calc=0.0, 
		  Good_Sample=0.0;
	float Freq_at_TonMax_s = 0;
	int   lcnt =0, 
		  lcnt_offtime=0, 
		  maxcnt =0, 
		  i=0;
	int   lcnt_ON=0, 
		  lcnt_OFF=0;
	float Freq_ON[500]={0.0}, 
		  Freq_OFF[500]={0.0}, 
		  Time_Stamp_ON[500]={0}, 
		  Time_Stamp_OFF[500]={0};

	int	  cycles=0, 
		  avg_cycle=0, 
		  Latch_Off_Pass=0,
		  Loff_aft_AR_P=0,
		  ARoff_P=0,
		  ARreq_P=0,
		  Loff_w_OT_P=0;

	float starttime=0, 
		  starttime1=0, 
		  stoptime=0, 
		  stoptime1=0;
	float ARST_NM_starttime=0, 
		  ARST_NM_stoptime=0;
	float ARST_On_TM_starttime=0, 
		  ARST_On_TM_stoptime=0, 
		  ARST_On_TM_time=0;
	float ARST_Off_TM_starttime=0, 
		  ARST_Off_TM_stoptime=0, 
		  ARST_Off_TM_time=0;
	float WAIT_n_LISTEN_NM_starttime=0, 
		  WAIT_n_LISTEN_NM_stoptime=0, 
		  tWL_NM_P=0, 
		  tElapse=0;
	float WAIT_n_LISTEN_TM_starttime=0, 
		  WAIT_n_LISTEN_TM_stoptime=0, 
		  tWL_TM_P=0;
	float tOV_filter_starttime=0, 
		  tOV_filter_stoptime=0, 
		  tOV_filter=0;
	float tDZwindow_90us=0, 
		  tDZwindow_55us=0,
		  tDZwindow_145us=0;
	float imeas=0;
	float TimeStart = 0;	
	float TimeStop = 0;
	float TimeDelta = 0;
	int FlagError = 0;
	int	count = 0;
	int MaxCount = 0;
	float iforce = 0;
	// Setup Digitizer //
	float	ChB_vrng=0.0;
	int		vrng_b	=0.0;

//	float starttime_sw=0, starttime1_sw=0, stoptime_sw=0, stoptime1_sw=0, ARST_NM_starttime_sw=0, ARST_NM_stoptime_sw=0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	Close_relay(K3);
 	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 

	//tmu_6->start_trigger_setup(2.4, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	//tmu_6->stop_trigger_setup(2.6,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);

	//HL needed to change TMU range to 10V because D = 5V or slightly higher.
	//Else, this will cause system to system failure.
	if(g_TurretCB)
	{
		tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		delay(2);
	}
	else
	{
		//tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);	//change from 0.5 to 1.0  xie 5/19/2017  (4300 low ~0.6V)
		tmu_6->stop_trigger_setup(1.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	}
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(10);			
	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA);	
	delay(1);
	VBPP_Negative_Cycle();

	//***********************************************************************************************
	//*			Wait and Listen Time (Primary)														*
	//***********************************************************************************************
	Power_Up_Primary_Normal_Mode(ILIM_NORM); //Vpin(GND), Drain(6V), BPP(0V ramp to 5V w/ 200mV step, then vPlus+200mV, -400mV, vPlus)

	D_dvi->set_voltage(D_ch, 2.0, 		VOLT_10_RANGE);	// DVI_11_0	(needed to reduce noise)
	wait.delay_10_us(10);

	WAIT_n_LISTEN_NM_starttime = mytimer.GetElapsedTime();
	tElapse = 0;
	tmeas	= 0;
	while(tElapse<120e-3 && tmeas < 1e-6)
	{
		tmu_6->arm();					
		wait.delay_10_us(10);			
		tmeas = tmu_6->read(30e-6);
		tElapse += 100e-6; //Estimated time per loop without the arm() and read() in account.
	}
	WAIT_n_LISTEN_NM_stoptime = mytimer.GetElapsedTime();
	tWL_NM_P = (WAIT_n_LISTEN_NM_stoptime - WAIT_n_LISTEN_NM_starttime)*1e-6;

	ARST_NM_starttime = WAIT_n_LISTEN_NM_stoptime;

	lcnt =0;
	maxcnt = 700;
	while (	tmeas	> 1.0e-6					&& 
			//tmeas	< 1/(0.9*gFOSC_TARGET_P)	&& 
			lcnt	< maxcnt						)
	{
		tmu_6->arm();					// Device doing auto-restart
		wait.delay_10_us(15);			// Wait for TMU
		tmeas = tmu_6->read(30e-6);	 
		lcnt ++;
	}
	ARST_NM_stoptime = mytimer.GetElapsedTime();

	if (ARST_NM_starttime <= 199 || ARST_NM_stoptime <= -199)
		tAR_On_NM_P =999.0 *1e-3;
	else
		tAR_On_NM_P = (ARST_NM_stoptime - ARST_NM_starttime) * 1e-6;

	//Power down
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(20);
	BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);		// OVI_1_0
	wait.delay_10_us(20);


	/****************************************************************************
	 *					Fosc_P: Primary Frequency Post Trim						*
	 * Note: Primay frequency doesn't have Jitter							    *
	 ****************************************************************************/
////
	VBPP_Negative_Cycle();

		//update TMU setting to have better Freq measurement
		tmu_6->start_holdoff(5,TRUE);
		tmu_6->stop_holdoff(128,TRUE);
		wait.delay_10_us(10);			

		////Setup Vpin for digital clocking
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
//
		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);

		tmu_6->arm();					
		delay(6);			// Wait for TMU to trigger and to capture 128 cycles
		//delay(8);			// JD cold debug Wait for TMU to trigger and to capture 128 cycles, JD was 6, cold test debug
		
		tmeas = tmu_6->read(6e-3);	 
		tmeas/=128;

	if	   (tmeas>99)	FOSC_P=999e3;
	else if(tmeas==0)	FOSC_P=-999e3;	
	else				FOSC_P=1/tmeas;

	FOSC_P_Err = (FOSC_P/gFOSC_TARGET_P - 1.0) * 100.0;

	if( gFosc_pt_P !=0)
		FOSC_act_P = (FOSC_P/gFosc_pt_P -1)*100;
	else 
		FOSC_act_P = 999.0;


	//***************************************************************************
	//*						TonMax_P: Primary Control 							
	//***************************************************************************
	if(g_TurretCB)
	{
		//HL needs to change TMU Range to 10V due to D = 5V or slightly higher.
		//Else, this will cause system to system failure.
		tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);	
		tmu_6->stop_trigger_setup(1.8,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);
		delay(2);
	}
	else
	{
		tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);	
		tmu_6->stop_trigger_setup(1.8,	POS_SLOPE, TMU_HIZ, TMU_IN_5V);	
	}
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(5);
	tmeas =0.0;
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(5);				// Wait for TMU
	tmeas+= tmu_6->read();	
	TonMax_P = tmeas;

	DCmax_P = (TonMax_P / (1/FOSC_P))*100.0; //datalog in percentage

	// Power down primary switching
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0	
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);		// OVI_1_0
	REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_2_V);		// OVI_1_2 Stop device from switching	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_10_V);
	BPS_dvi->set_voltage(BPS_ch, 0.0, 	VOLT_10_RANGE);		// DVI_9_1
	//VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);		// OVI_1_0
	wait.delay_10_us(50);

//
	/******************************************************************************************************************
	***				TonMax_1us with secondary in control															***
	***  - Devices with the FW_peak_20us_timer feature will require trimming DOPL bit.								***
	***  - If DOPL bit is not trimmed, Toff will be ~22us.															***
	***  - Modify Hardware to keep FW stay below GND so FW_Peak_20us_timer feature will not be triggered.			***
	******************************************************************************************************************/

	/****************************************************************************
	 *					Fosc_S: Secondary Frequency	Post Trim					*
	 * Note: Secondary frequency has Jitter									    *
	 ****************************************************************************/
	Power_Down_Everything();	
	Open_All_Relays();
	Close_relay(K3);
	delay(4);

	//pulse.do_pulse();

	VBPP_Negative_Cycle();

	if(g_TurretCB)
	{
		tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->stop_trigger_setup(1.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		delay(2);
	}
	else
	{
		tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
		tmu_6->stop_trigger_setup(1.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	}
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

		SyncHS_PowerUp_Secondary_in_Test_Mode_MINNO(gTM1_p,ILIM_NORM);	//Expect device to switch ON ~2.2ms, OFF ~62ms
		//delay(3);
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);
		Close_relay(K5);//Connect SR to 5nF
		delay(2);

		if(OPCODE==4400)
			{
				tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
				tmu_6->stop_trigger_setup(0.8,	POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);

					tmeas		= 0.0;
					tmeas_Sum	= 0.0;
				//for(lcnt=0;lcnt<2;lcnt++)
				//{
					tmu_6->arm();						// Device doing auto-restart
					wait.delay_10_us(5);				// Wait for TMU
					//pulse.do_pulse();
					tmeas = tmu_6->read(50e-6);
					tmeas_Sum += tmeas;

					tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
					tmu_6->stop_trigger_setup(1.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);

			}

		//Measure FOSC_S averaged over 128 cycles
		tmu_6->start_holdoff(5,TRUE);
		tmu_6->stop_holdoff(128,TRUE);
		tmu_6->arm();						// Note that device will do auto-restart in testmode1
		wait.delay_10_us(150);				// Wait for TMU to trigger and to capture 128 cycles (need at least 1280us wait if 10us period)
		tmeas = tmu_6->read(1.5e-3);
		//pulse.do_pulse();
		tmeas/=128;

		if (tmeas != 0)
				FOSC_S = 1/tmeas;
			else
				FOSC_S = -999e3;	

		FOSC_S_Err = (FOSC_S/gFOSC_TARGET_S - 1.0) * 100.0;
	
		if(g_TurretCB)
		{
			//For TurretRevB
			//Ton setup for TMU
			tmu_6->start_trigger_setup(1.00, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
			tmu_6->stop_trigger_setup(0.58,	POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);
			tmu_6->start_holdoff(0,FALSE);
			tmu_6->stop_holdoff(0,FALSE);
			wait.delay_10_us(5);
		}
		else if (OPCODE!=4400)
		{
			//Ton setup for TMU
			//pulse.do_pulse();
			/*if(OPCODE==4400)
			{
				tmu_6->start_trigger_setup(0.8, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
				tmu_6->stop_trigger_setup(0.9,	POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);
			}*/

			
				tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
				tmu_6->stop_trigger_setup(0.6,	POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);

			/*if(OPCODE==4400)
				tmu_6->stop_trigger_setup(0.9,	POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);*/
			tmu_6->start_holdoff(0,FALSE);
			tmu_6->stop_holdoff(0,FALSE);
			wait.delay_10_us(5);				// Wait for TMU
		

		//Measure TonMax1us_s (on time)
		tmeas		= 0.0;
		tmeas_Sum	= 0.0;
		//for(lcnt=0;lcnt<2;lcnt++)
		//{
			tmu_6->arm();						// Device doing auto-restart
			//pulse.do_pulse();
			wait.delay_10_us(50);				// Wait for TMU
			//pulse.do_pulse();
			tmeas = tmu_6->read(50e-6);
			//pulse.do_pulse();
			tmeas_Sum += tmeas;
		//}
		}
		//TonMax1us_s = tmeas_Sum/2.0;
		TonMax1us_s = tmeas_Sum;
	//}

	/******************************************************************************
	 *					TonMax: Secondary Control Post Trim						  *
	 *					DCMax : Secondary Control Maximum duty cycle			  *	
	 *					ToffMax-S:	   Secondary Control Max off time			  *
	 *					tAR_On_NM_P: Secondary controlled 64ms ARST on time.	  *
	 ******************************************************************************/
	if(g_TurretCB)
	{
		tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_100V);	// JD was 2.0
		tmu_6->stop_trigger_setup(5.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_100V);	// JD was 3.0

	}
	else
	{
		tmu_6->start_trigger_setup(3.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);	// JD was 2.0
		tmu_6->stop_trigger_setup(4.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);	// JD was 3.0
	}
		tmu_6->start_holdoff(10,TRUE);
		tmu_6->stop_holdoff(128,TRUE);
		wait.delay_10_us(5);

		if(1)		//Primary TM1_TM5, Secondary Normal Mode
		{
				Power_Down_Everything();
				Open_All_Relays();
				VBPP_Negative_Cycle();

				Close_relay(K3);
 				tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 

				//*******************************************************
				//Power up Primary TM1(32x faster) with TM5(Bypass WL)
				//*******************************************************
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
				//delay(3);
				SR_dvi2k->open_relay(CONN_FORCE1);
				SR_dvi2k->open_relay(CONN_SENSE1);
				Close_relay(K5);//Connect SR to 5nF
				delay(2);
			//Setup FB to connect to DDD
				REQ_ovi->set_voltage(REQ_ch, 0.0,	RANGE_2_V);	// OVI_1_2	
				wait.delay_10_us(5);
				Close_relay(K17);
				delay(5);
			//Have InvSync circuit ready for communication
				Connect_InvSyn_IM_New(Low_Vd_Input);
				Power_Up_Primary_BypassWL_TM5 (ILIM_NORM);
				if(g_TurretCB)
				{
						//HL changed to 10V for Turret CB
					dvi_11->set_voltage(DVI_CHANNEL_0, 10.0, VOLT_50_RANGE);
				}
				else
				{
					dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
				}
				//Bring Vpin OVI back
				//ovi_1->connect(OVI_CHANNEL_1);	
				//VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);  
				//VPIN_ovi->set_current(VPIN_ch, 1e-3,		RANGE_30_MA); 
				//delay(1);
				//Open_relay(K12);	//disconnect DDD7_1	from Vpin(UV)	pin
				//delay(1);

				//*******************************************************************
				//Power up Secondary Normal Mode FB Hi then Lo to bypass tSoft time
				//*******************************************************************
				ddd_7->ddd_set_voltage_ref(0.0);
				//delay(1);
				wait.delay_10_us(10);
				//Setup FB High/Low switching thresholds
				ddd_7->ddd_set_hi_level(1.7);				// Will immediately change to this level upon execution
				//ddd_7->ddd_set_hi_level(1.5);				// Will immediately change to this level upon execution
				//ddd_7->ddd_set_lo_level(gCV_Low);								// Will immediately change to this level upon execution
				ddd_7->ddd_set_lo_level(0.9);								// Will immediately change to this level upon execution
				wait.delay_10_us(10); 
				ddd_7->ddd_run_pattern(Low_FB_pat_start,Low_FB_pat_stop);			//Run Low pattern first then High to prevent overshoot
				wait.delay_10_us(50);
			//Setup to have Secondary power up to VBPS minus
				//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
				//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
				//if(g_TurretCB)
				//{
				//	//HL needs to change to 20mA or Turret CB won't work.
				//	SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
				//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
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
				//	delay(2);
				//}
				
				//wait.delay_10_us(20);
				//Vout (Will charge BPS if @5V)
				VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
				VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
				////FB (1V)
				//REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
				//REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
				//IS (0V)
				FWC_dvi2k->set_voltage(FWC_ch, 15e-3, 		VOLT_2_RANGE);	// DVI_21_0
				FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
				wait.delay_10_us(10);
				//BPS (vPlus - 200mV)
				BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	
				VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal  

				//Bring BPS to vPlus (Note: if BPS not power up fully, Vpin will be switching at Fosc Modulation)
				BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
				delay(2);
				
				//VPIN_ovi->set_voltage(VPIN_ch, 5.0,			RANGE_10_V);  
			
				//if(!g_TurretCB || (g_TurretCB && gSiliconRev_P < 3))
				//{
				//	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);			//Run Low pattern first then High to prevent overshoot
				//	wait.delay_10_us(5);
				//	ddd_7->ddd_run_pattern(High_pat_FB_start,High_pat_FB_stop);
				//	wait.delay_10_us(50);
				//	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
				//	wait.delay_10_us(5);

				//}
			}
			else
				SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);
if(g_TurretCB)
{
	delay(2);
}

	//Debug=1;
	if (DEBUG && gDEBUG) 
		
	DEBUG=0;

	tmeas_Sum	= 0.0;
	tmeas		= 0.0;
	//measure Freq_at_TonMax_s over 128 cycles
	tmu_6->arm();						// Device doing auto-restart				
	if(g_TurretCB)
	{
		delay(10);
		tmeas = tmu_6->read(10e-3);
	}
	else
	{
		delay(3);  // Wait for TMU to capture all 128 cycles
		tmeas = tmu_6->read(5e-3);	//128 cycles ~ 4.7ms
	}
	tmeas/=128;		//stop_holdoff=128
	Freq_at_TonMax_s = 1/tmeas;


	//setup TMU for Toff_min pulse width
	if(g_TurretCB)
	{
		//Change Pos slope from 0.5V to 1.0V to improve repeatability across system.
		tmu_6->start_trigger_setup(2.5, POS_SLOPE, TMU_HIZ, TMU_IN_10V);	
		tmu_6->stop_trigger_setup(8.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V); 
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);
		wait.delay_10_us(500);
		
	}
	else
	{
		tmu_6->start_trigger_setup(2.5, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(5.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);
		wait.delay_10_us(500);
	}
	
		//Too much repeatability issue.  HL added into average 5 times to improve repeatability on Turret handler.
	
		int loop = 0;
		tmeas		= 0.0;
		tmeas_Sum	= 0.0;
		while(loop <10)
		{
			tmu_6->arm();						
			wait.delay_10_us(50);				
			tmeas = tmu_6->read(500e-6);
			tmeas_Sum = tmeas_Sum+tmeas;
			loop++;
		}
		ToffMin_s = tmeas_Sum;
		ToffMin_s = ToffMin_s/10; 
		TonMax_S = 1/Freq_at_TonMax_s - ToffMin_s;

		if(ToffMin_s < 1e-6)	printf("Freq_at_TonMax_s =  %.2f Hz\n", Freq_at_TonMax_s);

		gTonMax_S = TonMax_S;	// Save for later use
		//ToffMin_s = 1/Freq_at_TonMax_s - TonMax_S;

		DCmax_S = 100 * TonMax_S/(1/Freq_at_TonMax_s);
		wait.delay_10_us(100);  				

	//**********************************************
	//*********** tOVP *****************************
	//**********************************************
	//Setup DDD Low/High (1.0V/1.3V)
	//ddd_7->ddd_set_lo_level(gCV_Low);
	ddd_7->ddd_set_lo_level(0.9);
	ddd_7->ddd_set_hi_level(1.7);
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);
	wait.delay_10_us(10);
	//Close relay K17 to use DDD-7-2 for FB
	Close_relay(K17);
	//VO_dvi set to 0V and open conn_Force/Sense
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);
	wait.delay_10_us(3);
	VO_dvi->open_relay(CONN_FORCE0);
	VO_dvi->open_relay(CONN_SENSE0);
	//ovi-1-7 disconnect
	ovi_1->disconnect(OVI_CHANNEL_7);
	//Close_relay(K27) to connect VO to 1kohm to ovi-1-5
	Close_relay(K27);
	delay(4);
	//ovi-1-5 set to 4V in series with 1kohm  (4V to be lower than vBPS so Vout will not supply any current to BPS)
	ovi_1->set_current(OVI_CHANNEL_5, 30e-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_5, 4.00,   RANGE_5_V);
	wait.delay_10_us(100);  

	//Setup DDD compare threshold 
	ddd_7->ddd_set_voltage_ref(3.5);
	wait.delay_10_us(100);  

	//FB set 1V to 1.3V using DDD
	ddd_7->ddd_run_pattern(FB_positive_edge_start, FB_positive_edge_stop);
	wait.delay_10_us(10);

	//Read out compare results
	for(i=FB_positive_edge_start+4; i<FB_positive_edge_stop; i++)
	{
		Result = ddd_7->ddd_read_pattern(i);	//Read VO result during FB high vectors
		Result = Result/8;						//VO pin connects to DDD7_4.  X000 => bit4 divided by 8 to get 1/0.
		if(Result == 0)
		{
//			tOVP = (i - (FB_positive_edge_start+4)) * 0.25e-6;
			tOVP = (i - (FB_positive_edge_start+4+2)) * 0.25e-6; //minus two additional vector to match scope
			break;
		}
	}

	Open_relay(K17);	//Disconnect DDD-7-2 from FB
	Open_relay(K27);	//Disconnect Vout from "1kohm to ovi-1-5"
	ovi_1->set_current(OVI_CHANNEL_5, 0.0,	RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_5, 0.0,  RANGE_5_V);
	wait.delay_10_us(100);  
	ddd_7->ddd_set_lo_level(0.1);
	ddd_7->ddd_set_hi_level(4.0);
	ddd_7->ddd_set_voltage_ref(0.0);
	delay(1);
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);
	wait.delay_10_us(3);


	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();

	tmu_6->start_trigger_setup(3.5, POS_SLOPE, TMU_HIZ, TMU_IN_5V);	
	tmu_6->stop_trigger_setup(3.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V); 
	//****************************************
	//************ iBPS_SD, Latch_OFF ********
	//****************************************
	SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);

	imeas = BPS_dvi->measure_average(25);
	BPS_dvi->set_voltage(BPS_ch, 5.3, 	VOLT_10_RANGE);	// Secondary vBPS_plus

	lcnt = 0;
	while(imeas < 7e-3 && lcnt < 20)
	{
		imeas = BPS_dvi->measure_average(25);
		lcnt++;
	}

	//Timer start for tOV_filter or tLatchOff_filter
	mytimer.Start();
	////////////
	tOV_filter_starttime = mytimer.GetElapsedTime();

	tmeas = 555;
	lcnt  = 0;

	while(tmeas > 0.1e-9 && tmeas < 999 && lcnt<10)
	{
		tmu_6->arm();				
		wait.delay_10_us(3);				
		tmeas = tmu_6->read(30e-6);		
		lcnt++;
	}

	//Timer stop for tOV_filter or tLatchOff_filter
	tOV_filter_stoptime = mytimer.GetElapsedTime();

	tOV_filter = (tOV_filter_stoptime - tOV_filter_starttime)*1e-6 ;

	iBPS_SD = BPS_dvi->measure_average(25);
	
	//Expect device go into latchoff and lower vBPS to vPlus+50mV will not bring it back to switching
	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init+50e-3, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	wait.delay_10_us(10);

	imeas = BPS_dvi->measure_average(25);	//Expect less than 1.5mA (~300uA expected)
	if(imeas < 1.5e-3)
		Latch_Off_Pass = 1;


	//Power down
	Power_Down_Everything();
	Open_All_Relays();

	//Open_relay(K9);
	//REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_2_V);		// OVI_1_2 Stop device from switching	
	//VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_10_V);
	//D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0	
	//wait.delay_10_us(30);
	//BPS_dvi->set_voltage(BPS_ch, 0.0, 	VOLT_10_RANGE);		// DVI_9_1
	//BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);		// OVI_1_0
	Disconnect_InvSyn_IM();	//ARST_Testmode also use the InvSyncCircuit
	VBPP_Negative_Cycle();

	/******************************* TESTMODE PRIMARY *******************************
	 *					ARST_On_Tmode:  Secondary controlled 2ms ARST on time.		*
	 *					tAR_Off_TM_P: Secondary controlled 64ms ARST on time.		*
	 *  Timing: TM1 gives 32x faster												*
	 *			- Wait and Listen after power-up.	(~2.7ms)						*
	 *			- Switching On Time.				(~2.7ms)						*
	 *			- Switching Off Time.				(~64.ms)						*
	 ********************************************************************************/
	Close_relay(K3);
 	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	tmu_6->start_trigger_setup(1.2, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->stop_trigger_setup(1.4,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	delay(3);
	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA);	

	if(1)	//Primary power up with TM1 
	{
			//Drain = 0V
			D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
			D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
			wait.delay_10_us(5);
			//UV pin (Vpin) set to 0V before PU
			VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_10_V);  
			VPIN_ovi->set_current(VPIN_ch, 20e-3,		RANGE_30_MA);	
			//BPP set 0V
			BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
			BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);	// OVI_1_0
			wait.delay_10_us(5);
			//////Try Cycle BPP to see if it helps
			////BPP_ovi->set_voltage(BPP_ch, 5.3, 	RANGE_10_V);	// OVI_1_0
			////wait.delay_10_us(10);
			////BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);	// OVI_1_0
			////wait.delay_10_us(10);

			VBPP_ramp_up(0, gVBPP_PV_final, 0.2);	// This ramp seems important to start from 0V, else not repeatable.
			
			VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
			wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
			wait.delay_10_us(1);	//Delay is critical for 1.8A device.  w/o 10us, ILIM read 70mA lower and not as repeatable.
			VBPP_ramp_down(gVBPP_M_Init +0.25, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
			wait.delay_10_us(10);
			if(gSiliconRev_P>=3)
			{
				BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
				VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	B3 material
			}
			else
			{
				VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
			}
			D_dvi->set_voltage(D_ch, HANDSHAKE_Vd_TM, 	VOLT_5_RANGE);	// DVI_11_0	
	}
	//else
	//		VBPP_Power_Up_w_Test_Mode(gTM_Fast_Counter_32x, ILIM_NORM);	//

	mytimer.Start();
	WAIT_n_LISTEN_TM_starttime = mytimer.GetElapsedTime();
	tElapse = 0;
	tmeas = 0;
	while(tElapse<5e-3 && tmeas < 4e-6)
	{
		tmu_6->arm();					
		wait.delay_10_us(8);			
		tmeas = tmu_6->read(80e-6);
		tElapse += 80e-6; //Estimated time per loop without the arm() and read() in account.
	}
	WAIT_n_LISTEN_TM_stoptime = mytimer.GetElapsedTime();
	tWL_TM_P = (WAIT_n_LISTEN_TM_stoptime - WAIT_n_LISTEN_TM_starttime)*1e-6;

	ARST_On_TM_starttime = WAIT_n_LISTEN_TM_stoptime;
	tElapse = 0;
	while(tElapse<4e-3 && tmeas > 1e-6)
	{
		tmu_6->arm();					
		wait.delay_10_us(8);	//Require minimum 80us for SAM,DSOFT bits trimmed device else 40us wait is enough
		tmeas = tmu_6->read(80e-6);
		tElapse += 80e-6; //Estimated time per loop without the arm() and read() in account.
	}
	ARST_On_TM_stoptime = mytimer.GetElapsedTime();
	tAR_On_TM_P = (ARST_On_TM_stoptime - ARST_On_TM_starttime)*1e-6;

	
	//HL 08/02/17.  HL added to check for latch up if Loff_AR_P bit is trimmed.
	if(gTrim_Loff_AR_P)
	{
		delay(45);
		tElapse = 0;
		FlagError = 0;
		while(tElapse<30e-3 && (tmeas <=0 || tmeas >= 99))
		{
			tmu_6->arm();					
			wait.delay_10_us(8);			
			tmeas = tmu_6->read(80e-6);
			tElapse += 80e-6; //Estimated time per loop without the arm() and read() in account.
			if(tmeas >0.1e-9 && tmeas < 1)
			{
				FlagError = 1;
				break;			
			}
		}
		// Final result //
		if (FlagError)
			Loff_aft_AR_P = -999; // Fail. //
		else
			Loff_aft_AR_P = 1; // Pass. //

	}
	else
	{
	
		ARST_Off_TM_starttime = ARST_On_TM_stoptime;
		tElapse = 0;
		while(tElapse<80e-3 && tmeas < 1e-6)
		{
			tmu_6->arm();					
			wait.delay_10_us(8);			
			tmeas = tmu_6->read(80e-6);
			tElapse += 80e-6; //Estimated time per loop without the arm() and read() in account.
		}
		ARST_Off_TM_stoptime = mytimer.GetElapsedTime();
		tAR_Off_TM_P = (ARST_Off_TM_stoptime - ARST_Off_TM_starttime)*1e-6;
	}
	//Disconnect_InvSyn_IM();  //HL Do not disconnect Inv ckt before powerdown other resources.
	// Power down
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0	
	BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);		// OVI_1_0
	wait.delay_10_us(10);
	
//
//
//

		//////////	/****************************************************************************
		//////////	 *					FOSC MODULATION											*
		//////////	 ****************************************************************************/
		//////////	tmu_6->start_trigger_setup(4.2, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		//////////	tmu_6->stop_trigger_setup(4.8,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		//////////	tmu_6->open_relay(TMU_HIZ_DUT1);	// HIZ1 to Drain
		//////////	tmu_6->close_relay(TMU_HIZ_DUT3);	// HIZ3 to Drain
		//////////	Close_relay(KC5);	//VPIN_OVI to 15Kohm to UV pin
		//////////	Close_relay(KC6);	//UV pin to 330ohm to TMU_HIZ_DUT3
		//////////	delay(3);
		//////////
		//////////////////////
		//////////	VBPP_Power_Up_w_Test_Mode(gTM2_p, ILIM_NORM);	//
		//////////	//UV pin (Vpin) set to 5V/3mA after PU
		//////////	VPIN_ovi->set_voltage(VPIN_ch, 5.0,			RANGE_10_V);  
		//////////	VPIN_ovi->set_current(VPIN_ch, 3e-3,		RANGE_30_MA);	
		//////////	delay(2);			//Require minimum 2ms before arm
		//////////
		//////////	tmu_6->arm();			
		//////////	delay(3);
		//////////	tmeas = tmu_6->read(1e-3);	 
		//////////	fModulation_P = 1/tmeas;

	/****************************************************************************
	 *					tOVL or fOVL (Fosc_Overload)							*
	 ****************************************************************************/

	//tOVL_cnt = 1;
	//while(tOVL_S < 3e-6 && tOVL_cnt <=3)	//tOVL-S has repeatability issue at HOT
	//{
		// Power down
		Power_Down_Everything();
		Open_All_Relays();

		Disconnect_InvSyn_IM();

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
				//4.0,								// 1.0V trigger level 
				4.5,								// 1.0V trigger level 
	   			SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE
		//delay(2);

		VBPP_Negative_Cycle();
		Close_relay(K3);
		delay(4);

		//HL Set SR to Direct GND based on JD input. 6/8/17
		//if(1)//g_TurretCB)
		//{
		//	SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
		//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		//	delay(2);
		//	mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
		//	delay(2);
		//		
		//}
		Close_relay(K5);//Connect SR to 5nF
		delay(5);
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);

	//Setup Vpin for digital clocking
		//ovi_1->disconnect(OVI_CHANNEL_1);	
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
		delay(2);
	//Have InvSync circuit ready for communication
		Connect_InvSyn_IM_New(Low_Vd_Input);
		//Primary TM5 bypass Wait and Listen power up
		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);

	//Setup to have Secondary power up to VBPS minus
		//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
		//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
		//if(0)//!g_TurretCB)
		//{

		//	SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
		//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		//
		//	dvi_13->close_relay(BUS_SENSE1);
		//	dvi_13->close_relay(BUS_FORCE1);
		//	mux_14->close_relay(MUX_3_BUS3);
		//	delay(5);	
		//}
		//Vout (Will charge BPS if @5V)
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
		////FB (1V)
		//REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
		//REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
		//IS (0V)
		//Setup FB High/Low switching thresholds
		ddd_7->ddd_set_hi_level(gREQ_V_Req);				// Will immediately change to this level upon execution
		ddd_7->ddd_set_lo_level(gREQ_V_Idle);				// Will immediately change to this level upon execution
		wait.delay_10_us(10);

		//ddd_7->ddd_run_pattern(FB_tOVL_start, FB_tOVL_stop);
		//wait.delay_10_us(5);
		ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
		wait.delay_10_us(5);
		
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 200mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	
		VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal  

		//Bring BPS to vPlus (Note: if BPS not power up fully, Vpin will be switching at Fosc Modulation)
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus

		// Secondary should now have control. //
		if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
		{
			BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
			wait.delay_10_us(10);
		}

		//Bring Vpin OVI back
		/*ovi_1->connect(OVI_CHANNEL_1);
		delay(1);
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
		//ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		//wait.delay_10_us(50);
	//
		Gage_Start_Capture(  );
		//Initiate the first pattern of tOVL to get rid of all of the noise before tmu arm()
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
		////VPIN_ovi->set_voltage(VPIN_ch, 5.0,			RANGE_10_V);  
		////wait.delay_10_us(10);

		////Open_relay(K17);
		////Open_relay(KC5);	//VPIN_OVI to 15Kohm to UV pin
		////Open_relay(KC6);	//UV pin to 330ohm to TMU_HIZ_DUT3
		//////tmu_6->open_relay(TMU_HIZ_DUT3);	
		////tmu_6->open_relay(TMU_EXT_DRV2);

		// Power down
		//Disconnect_InvSyn_IM();  //HL Do not disconnect Inv ckt before powerdown other resources.
		Power_Down_Everything();
		Disconnect_InvSyn_IM();
		if(g_TurretCB)
		{
			mux_20->open_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
			delay(2);
		}
		tmu_6->open_relay(TMU_EXT_DRV2);
		//Open_All_Relays();

		//DEBUG=1;
		// Search result //
		if(1)//g_TurretCB)
		{
			Gage_Find_tOVL_Turret(&tOVL_S);
		}
		else
		{
			Gage_Find_tOVL(&tOVL_S);
		}
		//DEBUG=0;

			tOVL_S += 1e-9;
			tOVL_Err_S = ( g_tOVL_TARGET/tOVL_S - 1 ) * 100.0;
		//	tOVL_cnt++;
		//}

	//** tOVL_act
		if(tOVL_S > 99.0)
			tOVL_S/=1e6;	

		if( g_tOVL_Pt !=0 )
			tOVL_act = (tOVL_S/g_tOVL_Pt -1)*100;
		else 
			tOVL_act = 999.0;

		Gage_pretrig_samples=64;	// Reset the Pre_Trigger Samples back to defaul at 64.
		Gage_init() ;

////////////


	//----------------------------------------------------------------------------


	/****************************************************************************
	 *					Audible Noise START										*
	 ****************************************************************************
	
	Prevent switching at frequencies from 7khz to 11khz.  This is to suppress noise resulting from the cavity resonant frequency 
	of the transformer.  If any switching request comes 90us to 145us after 1 switching request, all of these requests will be denied.
	After this "deadzone" window has elapsed, pulses outside of this window will be honored, but RTM will be frozen (meaning ILIM fixed) 
	until after 2 switching pulses.

	The deadzone window has been brought out and observable on VPIN.  See ObserveMode for the addressing.  
	A straight forward way to test this would be to also do this during the ILIM test, so we are in 2ndary control.  
	Fire a pulse and keep quiet for about 200us to window on VPIN.

	Simplified test procedure:
	- Get into ObserveMode
	- Get into 2ndary control
	- fire a request pulse
	- measure Dzwindow to be from 90us to 145us
																															*/
	
	wait.delay_10_us(10);  	
	ddd_7->ddd_set_clock_period(0.25e-6);	
	wait.delay_10_us(5);

	Rep_cnt = 1;
	while( (fLB_audible_P<6e3 || fLB_audible_P>100e3) && Rep_cnt<=2)  //has repeatability issue (take care later)
	{

		//Power_Down_Everything();
		//Open_All_Relays();
		Power_Down_Secondary();
		Power_Down_Primary();
		Disconnect_InvSyn_IM();
		Open_relay(K17);//Important for MINNO, else secondary won't switch
		Open_relay(K36);//Required for MINNO, FWD connected to TMU_CHA_DUT1

		tmu_6->open_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
		wait.delay_10_us(10);
		tmu_6->close_relay(TMU_HIZ_DUT3);
		wait.delay_10_us(10);

		//Setup to measure 55us, Vpin stay high for 55us after the 90us
		tmu_6->start_trigger_setup(4.8, POS_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(4.2,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);
		wait.delay_10_us(10);

		Close_relay(K3);	
		delay(4);

		VBPP_Negative_Cycle();
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
		wait.delay_10_us(20);
		//Close_relay(KC6);	//UV pin to 330ohm to TMU_HIZ_DUT3  (Needs to close before PU.  Some charge left over at TMU require discharge)
		//if(g_TurretCB)
		//{
		//	mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
		//	
		//}
		//delay(4);


		//SyncHS_PowerUp_SkipWaitNListen(gObserve_Mode_DZwindow, gNM_SkipWaitNListen_S); //Powerup Modes:  (Primary, Secondary)
		if(Rep_cnt==1)		SyncHS_PowerUp_SkipWaitNListen(gObserve_Mode_DZwindow,  gNM_SkipWaitNListen_S); //(Primary, Secondary) Vpin 3 clocks
		else				SyncHS_PowerUp_SkipWaitNListen(gObserve_Mode_DZwindow2, gNM_SkipWaitNListen_S); //(Primary, Secondary) Vpin 2 clocks
		wait.delay_10_us(10);
		/*VPIN_ovi->connect(VPIN_ch);	
		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
		VPIN_ovi->set_voltage(VPIN_ch, 0.0,   RANGE_5_V);*/
		//wait.delay_10_us(5);
		Close_relay(KC5);	//VPIN_OVI to 5Kohm to UV pin
		Close_relay(KC6);	//UV pin to 330ohm to TMU_HIZ_DUT3
		delay(5);
		//VPIN_ovi->set_voltage(VPIN_ch, 5.0,   RANGE_5_V);
	//	wait.delay_10_us(5);
		wait.delay_10_us(20);  	

		if(1)
		{
			VPIN_ovi->set_voltage(VPIN_ch, 5.0,   RANGE_5_V);
			wait.delay_10_us(20);  
			ddd_7->ddd_set_hi_level(1.7);	//07-18-17. HL changed from 10% increase to 15% increase to fix repeatability on TMT57
			ddd_7->ddd_set_lo_level(0.9);		
			//delay(1);
			wait.delay_10_us(10);

			ddd_7->ddd_run_pattern(High_pat_FB_start,High_pat_FB_stop);//Stop Drain from switching, This step required for MINNO
			//ddd_7->ddd_run_pattern(High_pat_start,High_pat_stop);
			wait.delay_10_us(5);

			REQ_ovi->set_current(REQ_ch, 0.1e-9,	RANGE_30_MA);	//float FB pin
			wait.delay_10_us(10);
			//FB_ovi->set_voltage(FB_ch, gCV_FB_S*1.1,	RANGE_2_V);	// OVI_1_2	"Force device to stop switching while 2ndary in control"
			//wait.delay_10_us(20);

			//Setup for FB pin
			Close_relay(K17);										// FB to DDD7_2
			delay(4);
			//ddd_7->ddd_set_hi_level(gCV_FB_S*1.1);		// 10pct above CV to avoid parts with OVLO bit trimmed will force Pri into latchoff/AR.
			//delay(1);

			//Require 10 pulses in order for dead zone signals to come up for revB2 and later silicons

			for(i=1; i<=15; i++)
			{
				ddd_7->ddd_run_pattern(0, 40);
//				wait.delay_10_us(30);	//Outside the 145us dead zone window
				wait.delay_10_us(50);	//Outside the 145us dead zone window
			}

			//tDZwindow_55us tmeas
			tmu_6->arm();			
			wait.delay_10_us(10);
			ddd_7->ddd_run_pattern(0, 40);
			wait.delay_10_us(30);	//Outside the 145us dead zone window
			tDZwindow_55us =  tmu_6->read(200e-6);		//expect ~55us

			//Close_relay(K36);//Required for MINNO, FWD connected to TMU_CHA_DUT1
			//wait.delay_10_us(50);

			//Setup to measure 90us, Time between device start switching (Drain High to Low) to Vpin toggle from Low to High (4V to 5V)
			tmu_6->close_relay(TMU_CHAN_A_DUT1);	 // Connect TMU CHA to FW
			tmu_6->start_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);	//FW	Channel_A_DUT1	to start trigger NEG
			tmu_6->stop_trigger_setup(4.5,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);		//Vpin	HIZ-DUT-3		to stop  trigger POS
			wait.delay_10_us(50);
			//tDZwindow_90us tmeas
			tmu_6->arm();			
			wait.delay_10_us(10);

			ddd_7->ddd_run_pattern(0, 40);
			wait.delay_10_us(50);
			tDZwindow_90us = tmu_6->read(300e-6);		//expect ~90us
		}

		//For Debug purpose only
		//if(tDZwindow_90us<0.1e-6)		
		//if(0)

		//Audible Lower Bound
		if(tDZwindow_90us == 0)		fLB_audible_P = 999e3;
		else						fLB_audible_P = 1/tDZwindow_90us;		//Audible noise frequency Lower Bound

		//Audible Upper Bound
		tDZwindow_145us = tDZwindow_90us + tDZwindow_55us;
		if(tDZwindow_145us == 0)	fUB_audible_P = 999e3;
		else						fUB_audible_P = 1/tDZwindow_145us;		//Audible noise frequency Upper Bound

		Rep_cnt++;

	}

	//STOP and START ILIM for a better view of ILIM from scope
	ddd_7->ddd_stop_pattern();								//Need to do a stop pattern when you don't want ddd looping
//	wait.delay_10_us(100);  	
	wait.delay_10_us(10);
	ddd_7->ddd_set_clock_period(0.25e-6);		
//	wait.delay_10_us(100);  	
	wait.delay_10_us(10);

	Open_relay(K17);										// FB to DDD7_2
	Open_relay(KC5);
	Open_relay(KC6);
	tmu_6->open_relay(TMU_CHAN_A_DUT1);	 // Connect TMU CHA to FW
	tmu_6->open_relay(TMU_HIZ_DUT3);	// HIZ3 to Drain

	//--------------------Audible Noise END-------------------------




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

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tblock-S //
	// After the drain turns off, secondary requests are ignored for tblock (~2usec).
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Power Down from previous //
	Power_Down_Everything_Except_Buf_Clamp();
	Open_All_Relays();

	/********************************************************************************************************
	Procedure:
		1.  Primary power-up with normal mode and TM6 (Vpin = receiver input at TM6)
		2.  Drain set to 10V after TM6 power-up
		3.  Send two pulses of 30us apart at Vpin to give control to secondary
		4.  Send one Vpin clock and observe Drain signal for tblock.
			Drain turns on (switch from high to low) when Vpin goes high.  After 15us tonMax, drain turns off
			then turns on again after tblock has ended.
			
						 _______
			Vpin _______|		|_________
			
			Drain_______					 		____
						|__________________________|	|_____________
						<------ tonmax (15us)------><--->
													 tblock (~2.4us)
	 ************************************************************************************************************/

	// Drain //
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	Close_relay(K3); // Drain to dvi through pullup resistor. //
	
	// TMU setup, off-time //
	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
	tmu_6->start_trigger_setup(1.0, POS_SLOPE, TMU_HIZ, TMU_IN_25V);
	tmu_6->stop_trigger_setup(9.0, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	// SR //
	if(g_TurretCB)
	{
		//HL needs to change to 20mA or Turret CB won't work.
		SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
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
		delay(2);
	}
	

	// BPS //
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);

	// IS //
	if(g_TurretCB)
	{
		FWC_dvi2k->set_voltage(FWC_ch, 0, VOLT_2_RANGE);
		FWC_dvi2k->set_current(FWC_ch, 200e-3, RANGE_2_A);

	}
	else
	{
		FWC_dvi2k->set_voltage(FWC_ch, 0, VOLT_50_RANGE);
		FWC_dvi2k->set_current(FWC_ch, 200e-3, RANGE_200_MA);
	}

	// Setup Vpin for DDD clocking //
	ovi_1->disconnect(OVI_CHANNEL_1);
	wait.delay_10_us(100);  	
	// Setup DDD //
	ddd_7->ddd_set_lo_level(0.1);
	ddd_7->ddd_set_hi_level(4.0);
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);
	Close_relay(K12); // Connect DDD7_1	to Vpin //
	wait.delay_10_us(300); // Wait for all relays //

	// Remove latchoff problem. //
	VBPP_Negative_Cycle();
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	wait.delay_10_us(10);

	// Primary Power up with normal mode and TM6 //
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2); // vstart, vstop, vstep //	
	wait.delay_10_us(2);
	
	// Vpin pulse 6 times for test mode 6. //
	// In test mode 6 the Vpin becomes the receiver input. //
	ddd_7->ddd_run_pattern(Vpin_6clocks_start,Vpin_6clocks_stop);	
	wait.delay_10_us(5);

	// Drain to 40V, for normal mode. //	
	D_dvi->set_voltage(D_ch, 40, VOLT_50_RANGE);
	wait.delay_10_us(60);

	// Set BPP //
	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);	
	wait.delay_10_us(5);

	// Set BPP //
	VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

	// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
	int ILIM_Select = ILIM_NORM;
	if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
	else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

	// Set BPP below VBP- //
	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
	wait.delay_10_us(30);

	// Set BPP above VBP+ // 
	if(gSiliconRev_P>=3)
	{
		BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
		VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
		wait.delay_10_us(10);
	}
	else
	{
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
		wait.delay_10_us(30);
	}

	// Set drain to observe switching. //
	D_dvi->set_voltage(D_ch, 10, VOLT_10_RANGE);
	wait.delay_10_us(40);

	// Two pulses 30usec apart to give control to secondary. //
	ddd_7->ddd_run_pattern(Vpin_30usec_start,Vpin_30usec_stop);	
	wait.delay_10_us(10);
		
	// Setup TMU //
	tmu_6->arm();					
	wait.delay_10_us(10);	

	// One Vpin clock.  Drain turns on when Vpin goes high.  After 15usec tonMax, drain turns off, 
	// then turns on again after tblock has ended. //
	ddd_7->ddd_run_pattern(Vpin_one_30us_clock_start,Vpin_one_30us_clock_stop);
	wait.delay_10_us(10);
	tmeas = tmu_6->read();	
	tblock_S = tmeas;

	// Power Down //
	tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Loff_aft_AR-P //
	// Feature Trim#19: Latch off after any AR.
	//
	// When this bit trimmed, any fault that causes AR will cause latchoff.  
	// Powerup in TM1 for faster test time.  Prevent secondary from taking control by keeping BPS < 4.4V.
	// After wait&listen (2.56ms), there will be switching for tAR (another 2.56msec).  
	// Without bit#19 trimmed, the part will then stop switching for tAROff (62msec) and then will start 
	// switching in tAR again.  But, with bit#19 trimmed, the part will stop switching and stay latched 
	// off and should never switch again.  So, in this test we just need to monitor switching to ensure 
	// that after the 62msec of tARoff, that switching does not start again. Check all the way out to 
	// 100msec.  The is a functional test.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (0)//(gTrim_Loff_AR_P)//HL 08/02/17 disabled and moved the test to after AR
	{
		// Initialize //
		Loff_aft_AR_P = -999;
		FlagError = 0;
		
		// Power Down from previous //
		Power_Down_Everything_Except_Buf_Clamp();
		Open_All_Relays();

		// Drain to 0V, for test mode 1. //
		D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE);
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
		Close_relay(K3); // Drain to dvi through pullup resistor. //
		
		// TMU setup //
		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
		tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);

		// SR //
		if(g_TurretCB)
		{
			//HL needs to change to 20mA or Turret CB won't work.
			SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
			SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
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
			delay(2);

		}
		
		// IS //
		FWC_dvi2k->set_voltage(FWC_ch, 0, VOLT_50_RANGE);
		FWC_dvi2k->set_current(FWC_ch, 200e-3, RANGE_200_MA);
		wait.delay_10_us(300); // Wait for all relays //

		// Remove latchoff problem. //
		VBPP_Negative_Cycle();
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		wait.delay_10_us(10);

		// Primary Power up test mode 1. //
		VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2); // vstart, vstop, vstep //	
		wait.delay_10_us(7);

		// Set BPP //
		VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);	
		wait.delay_10_us(5);

		// Set BPP //
		VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

		// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
		ILIM_Select = ILIM_NORM;
		if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
		else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

		// Set BPP below VBP- //
		BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
		wait.delay_10_us(30);

		// Set BPP above VBP+ // 
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
		wait.delay_10_us(30);

		// Set Drain //
		D_dvi->set_voltage(D_ch, 1.5, VOLT_10_RANGE); // Keep below 3V to stay in test mode 1. //
		wait.delay_10_us(20);

		// Wait for wait&isten to expire and drain will start switching (~2.5msec). //
		TimeStart = mytimer.GetElapsedTime();
		count = 0;
		while (count < 10000)
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Part started switching. //
				break;
			count++;
		}
		TimeStop = mytimer.GetElapsedTime();
		TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
		if(TimeDelta > .005) // Wait&Listen was too long. //
			FlagError = 1;

		// Wait for tAR to expire and drain will stop switching (~2.5msec). //
		TimeStart = mytimer.GetElapsedTime();
		count = 0;
		while (count < 10000)
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas < 0.1e-9) // Part stopped switching. //
				break;
			count++;
		}
		TimeStop = mytimer.GetElapsedTime();
		TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
		if(TimeDelta > .005) // tAR was too long. //
			FlagError = 1;

		// Make sure drain has latched off. Check for 100msec to make sure it does not start switching again. //
		// 100msec is a long test time.  Maybe for characterizaiton only. //
		TimeStart = mytimer.GetElapsedTime();
		count = 0;
		while (count < 10000)
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			TimeStop = mytimer.GetElapsedTime();
			TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
			if (tmeas > 0.1e-9) // Error. Part started switching.  Should have stayed latched off. //
			{
				FlagError = 1;
				break;
			}
			if (TimeDelta > 0.1) // Wait for 100msec. //
				break;
			count++;
		}
		TimeStop = mytimer.GetElapsedTime();
		TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //

		// Final result //
		if (FlagError)
			Loff_aft_AR_P = -999; // Fail. //
		else
			Loff_aft_AR_P = 1; // Pass. //

		tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// AR_disable-S //
	// Feature Trim#20: Disable AR if not switching. //
	//
	// Bit#20 disables the AR function that transfers control to primary when secondary stops requesting 
	// for > tARSK (1.3s).  Note, secondary can still give up control with latchoff request.  
	// Powerup in TM1 to save test time.  With seconary control, stop making requests for more than 
	// tARSK (tARST = 1.3/32 = 40.6ms).  Use 62msec.  After waiting for 62msec, make sure the primary 
	// still responds to secondary requests (making sure secondary still has control).  This 
	// is a functional test.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (gTrim_DisablAR_P)
	{
		// Initialize //
		AR_disable_S = -999;
		FlagError = 0;
		
		// Power Down from previous //
		Power_Down_Everything_Except_Buf_Clamp();
		Open_All_Relays();	

		// Drain //
		D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
		Close_relay(K3); // Drain to dvi through pullup resistor. //
		
		// TMU setup //
		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
		tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);

		// SR //
		if(g_TurretCB)
		{
			//HL needs to change to 20mA or Turret CB won't work.
			SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
			SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
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
			delay(2);
		}
		

		// IS //
		FWC_dvi2k->set_voltage(FWC_ch, 0, VOLT_50_RANGE);
		FWC_dvi2k->set_current(FWC_ch, 200e-3, RANGE_200_MA);

		//Setup Vpin for digital clocking
		ovi_1->disconnect(OVI_CHANNEL_1);
		wait.delay_10_us(100);  	
		// Initialize DDD
		ddd_7->ddd_set_lo_level(0.1);
		ddd_7->ddd_set_hi_level(4.0);
		delay(1);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(10);
		Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
		
		//Setup FB to connect to DDD //
		Close_relay(K17); // Connect FB to DD //	

		//Have InvSync circuit ready for communication
		Connect_InvSyn_IM(Low_Vd_Input);
		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1, VOLT_20_RANGE);	// OVI_1_4	
		wait.delay_10_us(300); // Wait for all relays //

		// Remove latchoff problem. //
		VBPP_Negative_Cycle();
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		wait.delay_10_us(10);

		// Primary Power up with TM1 and TM5 in same power up //
		VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(20);
		Force_Vpin_Pulses_5_Times(5.0, 0.0);	
		wait.delay_10_us(10);
		VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);
		wait.delay_10_us(5);
		VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

		// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
		ILIM_Select = ILIM_NORM;
		if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
		else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

		// Set BPP below VBP- //
		BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
		wait.delay_10_us(50);

		// Reconnect Vpin OVI //
		VPIN_ovi->set_current(VPIN_ch, 1e-3, RANGE_30_MA);
		ovi_1->connect(OVI_CHANNEL_1);
		delay(1);
		Open_relay(K12);
		delay(2);
		VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
		VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
		wait.delay_10_us(50);

		// Drain set to 1.5V for switching.  Do not exceed 3V or will exit TM1. //
		D_dvi->set_voltage(D_ch, 1.5, VOLT_10_RANGE);
		wait.delay_10_us(30);

		// Set BPP above VBP+ // 
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
		wait.delay_10_us(30);
		// Wait and listen should be skipped, and device should switching immediatly under primary control. //

		// Get FB ready for clocking. //
		wait.delay_10_us(100);  	
		ddd_7->ddd_set_hi_level(gCV_FB_S*1.1);
		ddd_7->ddd_set_lo_level(gCV_Low);
		delay(1);
		ddd_7->ddd_run_pattern(High_pat_FB_start,High_pat_FB_stop);
		wait.delay_10_us(5);		

		// Vout at 5V. // 	
		VO_dvi->set_voltage(VO_ch, 5, VOLT_5_RANGE);
		wait.delay_10_us(50);

		// BPS powerup //
		// When BPS is powered up, secondary will immediately handshake and take control. //
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE);
		wait.delay_10_us(100);
		// Secondary should now have control. //
		if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
		{
			BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
			wait.delay_10_us(10);
		}

		// Issue FB pulses.  Make sure secondary has control. //
		wait.delay_10_us(350); // Must wait to make sure tAR time is finished, in case secondary failed to take control. //
		tmu_6->arm();
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(FB_100kHz_pulse_start_5X, FB_100kHz_pulse_stop_5X);
		wait.delay_10_us(10);
		tmeas = tmu_6->read(100e-6);
		if (tmeas < 0.1e-9) // No switching detected, secondary does not have control. //
			FlagError  = 1; // Error. //

		// Wait for longer than tARSK (wait for 62msec).
		TimeStart = mytimer.GetElapsedTime();
		wait.delay_10_us(6200);
		TimeStop = mytimer.GetElapsedTime();
		TimeDelta = (TimeStop - TimeStart)*1e-3;

		// Issue FB pulses.  Make sure secondary still has control. //
		tmu_6->arm();
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(FB_100kHz_pulse_start_5X, FB_100kHz_pulse_stop_5X);
		wait.delay_10_us(10);
		tmeas = tmu_6->read(100e-6);
		if (tmeas < 0.1e-9) // No switching detected, secondary does not have control. //
			FlagError  = 1; // Error. //

		// Final result //
		if (FlagError)
			AR_disable_S = -999; // Fail //
		else
			AR_disable_S = TimeDelta; // Pass.  Datalog the wait time. //

		tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Loff_w_OT-P //
	// Feature Trim#23: Latch off with OT. //
	//
	// Normally, when a part heat ups above the thermal shutdown threshold it stops switching, 
	// and it will start switching again when the temperature falls below the thermal shutdown 
	// threshold.  However, with bit#23 trimmed, when a part heats up above the thermal shutdown 
	// threshold it latches off and does not start switching again when the temperature falls 
	// below the thermal shutdown threshold.  To test this, go into OT (i.e.OVT) test mode and 
	// when Vpin is brought up to 5V (i.e. thermal shutdown is reduced to 19C) the part should 
	// latch off and stop switching, then when Vpin is set to 0V (i.e. thermal shutdown set to 
	// 60C) it should stay latched off.  Then, can make sure the latch off can be removed by 
	// either pulling VBPP below undervoltage then back above VBP+.  This is a functional test.
	//
	// OT test mode will only work at room temp. Cannot test this at hot.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (gTrim_LoffwOT_P)
	{
		if (OPCODE==4250 || OPCODE==4200)
		{
			// Initialize //
			Loff_w_OT_P = -999;
			FlagError = 0;

			//BELOW CODING IS TAKEN FROM OVT FUNCTION.  COULD BE A POTENTIAL TEST TIME SAVER FOR POWER-UP FOR LATER
			// Power Down from previous //
			Power_Down_Everything_Except_Buf_Clamp();
			Open_All_Relays();	

			// Drain low for test mode 1. //
			D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);
			D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
			Close_relay(K3); // Drain to dvi through pullup resistor. //
			
			// TMU setup //
			tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
			tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			tmu_6->start_holdoff(0,FALSE);
			tmu_6->stop_holdoff(0,FALSE);

			//Setup Vpin for digital clocking
			ovi_1->disconnect(OVI_CHANNEL_1);
			//wait.delay_10_us(100);  	
			// Initialize DDD
			ddd_7->ddd_set_lo_level(0.1);
			ddd_7->ddd_set_hi_level(4.0);
			//delay(1);
			wait.delay_10_us(10);
			ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
			wait.delay_10_us(10);
			Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
			wait.delay_10_us(300); // Wait for all relays //

			// Remove latchoff problem. //
			VBPP_Negative_Cycle();
			BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
			wait.delay_10_us(10);

			ovi_1->disconnect(OVI_CHANNEL_1);	// Vpin does not use ovi-1-1 for Iz function
			//delay(1);                           // HL: Do not remove this delay.  Without it, DDD pattern seems to be corrupted after less than 100 runs.
			wait.delay_10_us(10);
			// Initialize DDD
			ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
			ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
			//delay(1);
			wait.delay_10_us(10);
			ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
			wait.delay_10_us(10);

			Close_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
			Close_relay(K3);					// Connect Drain	to R1 and L1 Load
 			tmu_6->close_relay(TMU_HIZ_DUT1);   // Connect TMU HIZ	to Drain 

			if(g_TurretCB)
			{
				tmu_6->start_trigger_setup(0.4, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
				tmu_6->stop_trigger_setup(0.6,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			}
			else
			{
				tmu_6->start_trigger_setup(0.4, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
				tmu_6->stop_trigger_setup(0.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			}
			tmu_6->start_holdoff(0,FALSE);
			tmu_6->stop_holdoff(0,FALSE);
			VBPP_Negative_Cycle();
			delay(4);

			Powerup_Primary_in_Testmode(gOT_Mode);
			wait.delay_10_us(300);	// TM1 wait n listen = 2.5ms

			// Bring Vpin back to 0V to increase OT theshold to 60C. //
			VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);
			wait.delay_10_us(15);
			
			// Wait for wait&listen to finish and drain will start switching (~2.5msec). //
			count = 0;
			MaxCount = 50;
			while (count < MaxCount) // About 100usec per loop //
			{
				tmu_6->arm();
				wait.delay_10_us(100);
				tmeas = tmu_6->read(500e-6);
				if (tmeas > 0.1e-9) // Part started switching. //
					break;
				count++;
			}
			if(count > (MaxCount-1))
				FlagError = 1; // Part did not start switching. //

			// Raise Vpin to 5V to reduce OT threshold to 19C. //
			VPIN_ovi->set_voltage(VPIN_ch, 5, RANGE_10_V);
			wait.delay_10_us(110);		// Takes a long time to stop switching, min argument 75

			// Make sure part stopped switching //
			count = 0;
			MaxCount = 10;
			while (count < MaxCount) // About 100usec per loop //
			{
				tmu_6->arm();
				wait.delay_10_us(10);
				tmeas = tmu_6->read(100e-6);
				if (tmeas > 0.1e-9) // Error. Part still switching. //
				{
					FlagError = 1;
					break;
				}
				count++;
			}
			
			// Bring Vpin back to 0V to increase OT theshold back to 60C. //
			VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);
			wait.delay_10_us(15);

			// Make sure part is still NOT switching //
			count = 0;
			MaxCount = 10;
			while (count < MaxCount) // About 100usec per loop //
			{
				tmu_6->arm();
				wait.delay_10_us(10);
				tmeas = tmu_6->read(100e-6);
				if (tmeas > 0.1e-9) // Error. Part still switching. //
				{
					FlagError = 1;
					break;
				}
				count++;
			}

			// Reset latch-off condition to make sure part start switching again. //
			VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init - 0.200, 0.1);
			VBPP_ramp_up(gVBPP_M_Init - 0.200, gVBPP_P_final, 0.1);
			wait.delay_10_us(15);

			// Make sure part is now switching //
			// After part comes out of latch-off, it goes into wait&listen for ~2.5msec and then starts switching. //
			count = 0;
			MaxCount = 500;
			while (count < MaxCount) // About 100usec per loop //
			{
				tmu_6->arm();
				wait.delay_10_us(10);
				tmeas = tmu_6->read(100e-6);
				if (tmeas > 0.1e-9) // Part started switching. //
					break;
				count++;
			}
			if(count > (MaxCount-1))
				FlagError = 1; // Part did not start switching. //

			// Final result //
			if (FlagError)
				Loff_w_OT_P = -999; // Fail //
			else
				Loff_w_OT_P = 1; // Pass //

			tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 
		}
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// ARoff-P //
	// Feature Trim#54: request AR //
	//
	// Bit#54 changes secondary triggered primary latchoff into auto-restart instead.  The part
	// should go into auto-restart instead of latchoff. 
	// Powerup in test mode 1.  Create an ISD BPS fault.  Make sure device starts switching again 
	// after auto-restart time (2s/32 = 62msec in test mode 1) making sure the part 
	// goes into auto-restart instead of staying in latchoff.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (gTrim_AR_req_P)
	{
		// Initialize //
		ARoff_P = -999;
		FlagError = 0;

		// Power Down from previous //
		Power_Down_Everything_Except_Buf_Clamp();
		Open_All_Relays();	

		// Drain to 0V, for test mode 1. //
		D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE);
		D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
		Close_relay(K3); // Drain to dvi through pullup resistor. //
		
		// TMU setup //
		tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
		tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);

		//Setup Vpin for digital clocking
		ovi_1->disconnect(OVI_CHANNEL_1);
		//wait.delay_10_us(100);  	
		// Initialize DDD
		ddd_7->ddd_set_lo_level(0.1);
		ddd_7->ddd_set_hi_level(4.0);
		//delay(1);
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(10);
		Close_relay(K12); // Connect DDD7_1	to Vpin(UV)	pin
		wait.delay_10_us(300); // Wait for all relays //

		// Remove latchoff problem. //
		VBPP_Negative_Cycle();
		BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
		wait.delay_10_us(10);

		ovi_1->disconnect(OVI_CHANNEL_1);	// Vpin does not use ovi-1-1 for Iz function
		//delay(1);                           // HL: Do not remove this delay.  Without it, DDD pattern seems to be corrupted after less than 100 runs.
		// Initialize DDD
		ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
		//delay(1);
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(10);

		Close_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
		Close_relay(K3);					// Connect Drain	to R1 and L1 Load
		tmu_6->close_relay(TMU_HIZ_DUT1);   // Connect TMU HIZ	to Drain 

		if(g_TurretCB)
		{
			tmu_6->start_trigger_setup(0.4, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			tmu_6->stop_trigger_setup(0.6,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		}
		else
		{
			tmu_6->start_trigger_setup(0.4, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
			tmu_6->stop_trigger_setup(0.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		}
		tmu_6->start_holdoff(0,FALSE);
		tmu_6->stop_holdoff(0,FALSE);
		VBPP_Negative_Cycle();
		delay(4);

		Powerup_Primary_in_Testmode(gOT_Mode);
		wait.delay_10_us(300);	// TM1 wait n listen = 2.5ms

		// Vpin to 0V to increase OT theshold to 60C. //
		VPIN_ovi->set_voltage(VPIN_ch, 0, RANGE_10_V);
		wait.delay_10_us(15);

		// Make sure drain starts switching. //
		count = 0;
		MaxCount = 10;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Part started switching. //
				break;
			count++;
		}
		if(count > (MaxCount-1))
			FlagError = 1; // Part did not start switching. //

		// Force BPS ISD fault to trigger primary latchoff. //
		BPS_dvi->set_voltage(BPS_ch, 5.5, VOLT_10_RANGE);  // abs max 5.5V //

		// Wait until drain stops switching //
		count = 0;
		MaxCount = 100;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas < 0.1e-9) // Part stopped switching. //
			{
				break;
			}
			count++;
		}
		if(count > (MaxCount-1))
			FlagError = 1; // Part did not stop switching. //

		// Power down BPS //
		BPS_dvi->set_voltage(BPS_ch, 0, VOLT_10_RANGE);
		//wait.delay_10_us(100);  	
		ddd_7->ddd_set_lo_level(0);
		//wait.delay_10_us(100);                           // HL do not remove delay.  Else, it will corrupt the DDD pattern.
		wait.delay_10_us(10);
		VO_dvi->set_voltage(VO_ch, 0, VOLT_5_RANGE);

		// Make sure drain starts switching again after auto-restart offtime (~62msec). //
		count = 0;
		MaxCount = 1000;
		while (count < MaxCount) // About 100usec per loop //
		{
			tmu_6->arm();
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			if (tmeas > 0.1e-9) // Part started switching. //
				break;
			count++;
		}
		if(count > (MaxCount-1))
			FlagError = 1; // Part did not start switching. //

		// Final result //
		if (FlagError)
			ARreq_P = -999; // Fail //
		else
			ARreq_P = 1; // Pass //

		tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 
	}

		
	//Power Down
	Power_Down_Everything();
	Open_All_Relays();
	tmu_6->open_relay(TMU_HIZ_DUT1);			
	tmu_6->open_relay(TMU_HIZ_DUT2);			
	tmu_6->open_relay(TMU_HIZ_DUT3);			
	tmu_6->open_relay(TMU_HIZ_DUT4);			
	tmu_6->open_relay(TMU_CHAN_A_DUT1);			
	tmu_6->open_relay(TMU_CHAN_A_DUT2);			
	tmu_6->open_relay(TMU_CHAN_B_DUT1);			
	tmu_6->open_relay(TMU_CHAN_B_DUT2);			
	Disconnect_InvSyn_IM();
	delay(4);

	//Datalog
	PiDatalog(func, A_FOSC_P,				FOSC_P,				set_fail_bin,	POWER_KILO);	
	PiDatalog(func, A_FOSC_P_Err,			FOSC_P_Err,			set_fail_bin,	POWER_UNIT);	
	if(TRIM_ENABLE)
	{
		PiDatalog(func, A_FOSC_exp_P,		gFOSC_exp_P,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_FOSC_act_P,		FOSC_act_P,			set_fail_bin,	POWER_UNIT);
	}
	PiDatalog(func, A_TonMax_P,				TonMax_P,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_TonMax_P_Err,			TonMax_P_Err,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_DCmax_P,				DCmax_P,			set_fail_bin,	POWER_UNIT);
	if (gTrim_Loff_AR_P)
	{
		PiDatalog(func, A_Loff_aft_AR_P,		Loff_aft_AR_P,		set_fail_bin,	POWER_UNIT);
	}
	if (gTrim_AR_req_P && (OPCODE==4200 || OPCODE==4250))	// Per JD, this test is not working at HOT, we need to fix this at HOT
	{
		PiDatalog(func, A_AR_req_P,				ARreq_P,			set_fail_bin,	POWER_UNIT);
	}
	if (gTrim_LoffwOT_P)
	{
		if (OPCODE==4250 || OPCODE==4200)
		PiDatalog(func, A_Loff_w_OT_P,			Loff_w_OT_P,		set_fail_bin,	POWER_UNIT);
	}
	//PiDatalog(func, A_Fosc_ss_min_S,		Fosc_ss_min_S,		set_fail_bin,	POWER_KILO);	
	//PiDatalog(func, A_Fosc_ss_Start_S,		Fosc_ss_Start_S,	set_fail_bin,	POWER_KILO);	
	//PiDatalog(func, A_Fosc_Start_S,			Fosc_Start_S,		set_fail_bin,	POWER_KILO);	
	//PiDatalog(func, A_tSoft_S,				tSoft_S,			set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_FOSC_S,				FOSC_S,				set_fail_bin,	POWER_KILO);	
	PiDatalog(func, A_FOSC_S_Err,			FOSC_S_Err,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_DCmax_S,				DCmax_S,			set_fail_bin,	POWER_UNIT);
	if (gTrim_DisablAR_P)
	{
		PiDatalog(func, A_AR_disable_S,			AR_disable_S,		set_fail_bin,	POWER_UNIT);
	}
	PiDatalog(func, A_TonMax_S,				TonMax_S,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_ToffMin_s,			ToffMin_s,			set_fail_bin,	POWER_MICRO);

	PiDatalog(func, A_TonMax1us_s,			TonMax1us_s,		set_fail_bin,	POWER_MICRO);
	////PiDatalog(func, A_ToffMax1us_s,			ToffMax1us_s,		set_fail_bin,	POWER_MICRO);
	////PiDatalog(func, A_TonMax1us_frq_s,		TonMax1us_frq_s,	set_fail_bin,	POWER_KILO);


	PiDatalog(func, A_tAR_On_NM_P,				tAR_On_NM_P,			set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_tAR_On_TM_P,				tAR_On_TM_P,			set_fail_bin,	POWER_MILLI);
	if(!gTrim_Loff_AR_P)
		PiDatalog(func, A_tAR_Off_TM_P,				tAR_Off_TM_P,			set_fail_bin,	POWER_MILLI);

	//PiDatalog(func, A_fModulation_P,			fModulation_P,			set_fail_bin,	POWER_KILO);
	PiDatalog(func, A_tOVL_S,					tOVL_S,					set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_tOVL_Err_S,				tOVL_Err_S,				set_fail_bin,	POWER_UNIT);	

////// Temporary use this datalog to datalog out the Toffmin_s - tblock. Need to add in create later. HQL 11/21/16
////	PiDatalog(func, A_tOVL_Err_S,				ToffMin_s-tblock_S,		set_fail_bin,	POWER_MICRO);	

	if(TRIM_ENABLE)
	{
		PiDatalog(func, A_tOVL_exp,			g_tOVL_exp,			set_fail_bin,	POWER_UNIT);
		PiDatalog(func, A_tOVL_act,			tOVL_act,				set_fail_bin,	POWER_UNIT);
	}

	PiDatalog(func, A_tWL_NM_P,					tWL_NM_P,				set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_tWL_TM_P,					tWL_TM_P,				set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_fLB_audible_P,			fLB_audible_P,			set_fail_bin,	POWER_KILO);
	PiDatalog(func, A_fUB_audible_P,			fUB_audible_P,			set_fail_bin,	POWER_KILO);
	PiDatalog(func, A_tblock_S,					tblock_S,				set_fail_bin,	POWER_MICRO);

	tDelta = ToffMin_s-tblock_S;
	if(tDelta > 0)	tDelta = 1;
	else			tDelta = 0;
	PiDatalog(func, A_tOffm_block_dif,			tDelta,		set_fail_bin,	POWER_UNIT);	

	//PiDatalog(func, A_iBPS_SD_S,				iBPS_SD,				set_fail_bin,	POWER_MILLI);
	//PiDatalog(func, A_tOV_filter_S,				tOV_filter,				set_fail_bin,	POWER_MICRO);
	//PiDatalog(func, A_LatchOff_Pass_S,			Latch_Off_Pass,			set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_tOVP_S,					tOVP,					set_fail_bin,	POWER_MICRO);

	if(gDEBUG)
	printf("\nFunction FOSC_Ton_ARST Done\n");

}
