//==============================================================================
// Fosc_post_S.cpp (User function)
// 
//    void Fosc_post_S_user_init(test_function& func)
//    void Fosc_post_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_post_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_post_S_user_init(test_function& func)
{
	Fosc_post_S_params *ours;
    ours = (Fosc_post_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_post_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_post_S_params *ours;
    ours = (Fosc_post_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "Fosc_post_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Fosc_post_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	////skip this function if it's not for characterization
	//if(gCHAR_FLOW == false)
	//	return;

	float Fosc_post_S =0.0,
		  FOSC_act_S=0.0,
		  Fosc_WeakBPS=0.0,
		  Fosc_SMwin=0.0,
		  Fosc_SMwin_Err=0.0,
		  Fosc_SMamp=0.0;
	float TonMax_Pt =0.0;
	float tmeas =0.0, toff =0.0;
	float tHandShake =0.0;
	float vfrc  =0.0;
	int   lcnt  =0;

	float WAIT_n_LISTEN_TM_starttime=0,
		  WAIT_n_LISTEN_TM_stoptime=0, 
		  WAIT_n_LISTEN_TM_time=0,
		  tElapse=0;
	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//////////
/****************************************************************************
 *					Fosc_post_S: Secondary Frequency Post trim				*
 * Note: Secondary frequency has Jitter									    *
 ****************************************************************************/
	VBPP_Negative_Cycle();
//	tmu_6->init();
	Close_relay(K3);
 	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 

	if(g_TurretCB)
	{
		tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.3,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	}
	else
	{
		tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
		tmu_6->stop_trigger_setup(1.2,	NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	}
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	delay(3);
	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA);	
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);

//#define PU_2ndary_Prog_AF_REG
#ifndef PU_2ndary_Prog_AF_REG
	SyncHS_PowerUp_Secondary_in_Test_Mode_MINNO(gTM1_p,ILIM_NORM);	//Expect device to switch ON ~2.2ms, OFF ~62ms
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF

	delay(2);
	//if(LB_Rev >= 5)		REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	
	//else				REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	
	//wait.delay_10_us(50);
	//REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2		Try for low CV_init
	//REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(20);
#endif

#ifdef PU_2ndary_Prog_AF_REG
	int		SR_AF_temp[100]={0};
	//PROG mode to program out XFWPK bit to disable FWPK switching.
	// Also Program out the External FB option
	Powerup_Secondary_in_Testmode(gProgRead_AFreg_S, 0, 0);

	Read_Secondary_AF_Reg (SR_AF_temp);	//must be followed by write
	//set CB and CS bits to 0 to disable cable comp
	//AF_Zero_Out_CS_and_CB_bits (SR_AF_temp);
	//Write corrected bits into AF register
	SR_AF_temp[4]=0;	// Programming out PK1&Xspeedload
	SR_AF_temp[6]=0;	// Programming out DVserSlpAdj
	SR_AF_temp[38]=1;	// Programming in  AR1
	SR_AF_temp[39]=1;	// Programming in  AR2
	SR_AF_temp[42]=1;	// Programming in  DOPL
	SR_AF_temp[43]=0;	// Programming out OVLO
	SR_AF_temp[44]=0;	// Programming out VR1
	SR_AF_temp[45]=0;	// Programming out VR2
	SR_AF_temp[46]=1;	// Programming in  FWPK
	SR_AF_temp[47]=0;	// Programming out SCEN
	SR_AF_temp[49]=0;	// Programming out CCAR
	SR_AF_temp[50]=0;	// Programming out ESRsel
	SR_AF_temp[51]=0;	// Programming out DdampEn
	Write_Secondary_AF_Reg (SR_AF_temp);
	wait.delay_10_us(20);

	Open_relay(K18);
	Open_relay(K21);
	delay(1);

	REQ_ovi->set_voltage(REQ_ch, gCV_Low,	RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(5);
	Connect_InvSyn_IM(Low_Load_Vd_Input);		//FB (2V)  pull FB above CVth to force No Switching

	if(LB_Rev >= 5)			ddd_7->ddd_set_hi_level(5.0);
	else					ddd_7->ddd_set_hi_level(gCVth_15pct_Higher);
	ddd_7->ddd_set_lo_level(gCV_Low);								// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);
	wait.delay_10_us(5);
	//Setup FB to connect to DDD
	Close_relay(K17);	//FB   to   DDD
	delay(4);
	VBPP_Power_Up_w_Test_Mode(gTM1_p,ILIM_NORM);

	if(gSiliconRev_P>=3)
	{
		BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);		//						B3 material
		VBPP_ramp_down(gVBPP_P_final, gVBPP_P_s_final, 10e-3);	// vstart, vstop, vstep	B3 material
		wait.delay_10_us(10);
	}
	else
		delay(3);	// Wait and Listen time in TM1

#endif
 

//**** Fosc_post_S 
	tmu_6->start_holdoff(5,TRUE);
	tmu_6->stop_holdoff(64,TRUE);
	tmu_6->arm();						// Note that device will do auto-restart in testmode1
	wait.delay_10_us(60);				// Wait for TMU to trigger and to capture 64 cycles (need at least 600us wait if 10us period)
	
	tmeas = tmu_6->read(600e-6);	 
	tmeas/=64;


	//Setup to measure IS2-S
	// Needs to move the current of Sec here to catch the full switching freq.
	/*BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);
	gIBPS_sw = 0;
	gIBPS_sw = BPS_dvi->measure_average(10);*/

	////tmu_6->start_holdoff(10,TRUE);
	////tmu_6->stop_holdoff(50,TRUE);
	////tmu_6->arm();						// Note that device will do auto-restart in testmode1
	////wait.delay_10_us(60);				// Wait for TMU to trigger and to capture 128 cycles (need at least 1280us wait if 10us period)
	////tmeas = tmu_6->read(600e-6);	 
	////tmeas/=50;
	if (tmeas != 0)
			Fosc_post_S = 1/tmeas;
		else
			Fosc_post_S = 0.0;	

	gFOSC_post_S = Fosc_post_S;			// Pass to global variable

// Datalog Fosc_act_S here before secondary Zfinal is trimmed and jitter is enabled to removed the 
// delta created by jitter. 
//** FOSC_act_S
	if( gFOSC_pt_S !=0)
		FOSC_act_S = (1- gFOSC_pt_S/Fosc_post_S)*100;
	else 
		FOSC_act_S = 999.0;

	//////////Measure ISS2-S here to save test time (Make sure SR is switching to get maximum IS2-S current)
	////////	//FB set to 15% above CV target to have part stop switching
	////////	REQ_ovi->set_voltage(REQ_ch, gCVtgt_15pct_Higher,		RANGE_2_V);	// OVI_1_2	
	////////	wait.delay_10_us(10);
	////////	//SR not shorted so it could be switching
	////////	dvi_13->open_relay(BUS_SENSE1);
	////////	dvi_13->open_relay(BUS_FORCE1);
	////////	mux_14->open_relay(MUX_3_BUS3);
	////////	wait.delay_10_us(10);
	////////	//FB set to 1V to have device switching
	////////	REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	////////	wait.delay_10_us(10);
	////////	//Setup to measure IS2-S
	////////	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	////////	wait.delay_10_us(5);
	////////	gIBPS_sw = 0;
	////////	gIBPS_sw = BPS_dvi->measure_average(25);
	float BPP_IS2_VBPP_p= 0.0;
	gBPP_IS2_VBPP_p = 0.0;


	//Measure IS2-VBPP_p here to save test time.
		//if(gSiliconRev_P >= 3)		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
		//else						BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
		//BPP_ovi->set_current(BPP_ch, 3e-3, RANGE_3_MA);
		//BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
		//wait.delay_10_us(5);
		BPP_IS2_VBPP_p = BPP_ovi->measure_average(5);
		gBPP_IS2_VBPP_p = BPP_IS2_VBPP_p;

/****************************************************************************************
 *					Fosc_WeakBPS: Functionality test									*
 * Note: Lower BPS voltage to vBPS_minus+250mV and make sure communication between      *
 * primary and secondary doesn't get weak. If communication gets weak,					*
 * switching cycles can be missed and caused Fosc to drop.								*
 ****************************************************************************/
	tmu_6->start_holdoff(5,TRUE);
	tmu_6->stop_holdoff(5,TRUE);


	VBPS_ramp_down(gVBPS_P_Init, gVBPS_M_Init+250e-3, 50e-3);
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init+250e-3, 	VOLT_10_RANGE);	// DVI_9_1
	wait.delay_10_us(10);

	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(15);				// Wait for TMU to trigger and to capture 10 cycles 
	tmeas = tmu_6->read(150e-6);	 
	tmeas/=5;

		if (tmeas != 0)
			Fosc_WeakBPS = 1/tmeas;
		else
			Fosc_WeakBPS = 0.0;	

	    //Added per Hiep's recommendation.
		BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init+50e-3, 	VOLT_10_RANGE);	// DVI_9_1
		wait.delay_10_us(10);

//		////Measure IS2-VBPP_p here to save test time.
//		//if(gSiliconRev_P >= 3)		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
//		//else						BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
//		BPP_ovi->set_current(BPP_ch, 3e-3, RANGE_3_MA);
//		BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
//		wait.delay_10_us(25);
//		gBPP_IS2_VBPP_p = 0;
////
//		gBPP_IS2_VBPP_p = BPP_ovi->measure_average(5);



/*****************************************************************************
 *					gHandShake_PASS											 *
 * Note: Verify handshake is done properly under normal operating condition. *
 * Normal operating condition:VBPS= VBPS_P+0.05V, Itag is pulled up to VBPS_P*							*
 * switching cycles can be missed and caused Fosc to drop.					 *
 *****************************************************************************/
	//if(DEBUG ==1)
	//{
	//	tmu_6->start_trigger_setup(0.5,			POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	//	tmu_6->stop_trigger_setup(HANDSHAKE_Vd_TM,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	//	tmu_6->start_holdoff(0,TRUE);
	//	tmu_6->stop_holdoff(0,TRUE);
	//	tmu_6->arm();						// Device doing auto-restart
	//	wait.delay_10_us(10);				//Wait for TMU

	//	tHandShake = tmu_6->read();	 
	//}

	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	// Go above secondary OVP, device should stop switching if it is trully secondary control
#ifndef PU_2ndary_Prog_AF_REG
	//REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	
	REQ_ovi->set_voltage(REQ_ch, 0.9,		RANGE_2_V);	// OVI_1_2	
#endif
#ifdef PU_2ndary_Prog_AF_REG
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
#endif

	wait.delay_10_us(10);
	tmu_6->arm(); 
	wait.delay_10_us(10);
	toff = tmu_6->read(100e-6); 

	//******************** BPP:IS1_6p2-P & BPP:IS1_VBPP-P ***********************************************
	//* These two test are tested here because primary side turns on an internal Isource after 5ms		*
	//* Originally, these two test are done in VBP_Supply function, but it takes >5ms to test			*
	//* So, moving these two test here will not require ramp to save test time and IS1 meas within 5ms	*
	//* These two test will be datalog in VBP_Supply function since datalog already exist there			*
	//***************************************************************************************************
	float BPP_IS1_VBPP_p;
	gBPP_IS1_VBPP_p = 0.0;

	if(gSiliconRev_P >= 3)		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
	else						BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);

	BPP_ovi->set_current(BPP_ch, 0.001, RANGE_3_MA);
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
	wait.delay_10_us(40);
	BPP_IS1_VBPP_p = BPP_ovi->measure_average(10);
	gBPP_IS1_VBPP_p = BPP_IS1_VBPP_p;

	// 80kHz => 12.5us period ->toff  [8.5us - 14.5us]
	// 132kHz => 7.5us period ->toff  [3.5us - 9.5us]
	if (OPCODE==4200 ||OPCODE==4250)
	{
		if( (Fosc_post_S - Fosc_WeakBPS)  >3.0e3 )	// If Fosc drops more than 3kHz, fail Handshake
				gHandShake_PASS = 999;
		else if( (tmeas < 1e-6  || tmeas > 999) ||	// HandShake fail if primary doesn't stop switching when FB is raised above CV
				(toff > (1/gFOSC_TARGET_S - 4e-6) && toff < (1/gFOSC_TARGET_S + 2.0e-6)))	
				gHandShake_PASS = 0;
		else
				gHandShake_PASS =1;
	}
	else 
	{
		if(toff > (1/gFOSC_TARGET_S - 4e-6) && toff < (1/gFOSC_TARGET_S + 2.0e-6))
			gHandShake_PASS = 0;
		else
			gHandShake_PASS =1;
		
	}
	//Power down
	dvi_13->open_relay(BUS_SENSE1);
	dvi_13->open_relay(BUS_FORCE1);
	mux_14->open_relay(MUX_3_BUS3);

	REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_2_V);	// OVI_1_2 Stop device from switching	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_10_V);
	wait.delay_10_us(30);
	D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);	// OVI_1_0
	BPP_ovi->set_current(BPP_ch, 0.03, RANGE_30_MA);
	BPS_dvi->set_voltage(BPS_ch, 0.0, 	VOLT_10_RANGE);	// DVI_9_1

	//Disconnect_InvSyn_IM();  //HL Do not disconnect Inv ckt before powerdown other resources.
	//tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain 
	//Open_relay(K3);
	//Power_Down_Secondary();
	//Power_Down_Primary();
	//wait.delay_10_us(5);
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain 
	Open_relay(K3);

//	delay(2);

	// Datalog
	PiDatalog(func, A_Fosc_post_S,	Fosc_post_S,	set_fail_bin,	POWER_KILO);	
	if(TRIM_ENABLE)
	{
		PiDatalog(func, A_FOSC_exp_S,	gFOSC_exp_S,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_FOSC_act_S,	FOSC_act_S,			set_fail_bin,	POWER_UNIT);
	}
	if (OPCODE==4200 ||OPCODE==4250)
	{
		PiDatalog(func, A_Fosc_WeakBPS,		Fosc_WeakBPS,	set_fail_bin,	POWER_KILO);	
	}
	//PiDatalog(func, A_HS_FAIL_post,	gHandShake_PASS,set_fail_bin,	POWER_UNIT); // EEFU 20180208
	
	//commented out datalog because code measuring tHandShake has been commented out, 11/11/16, pm
	//if(DEBUG==1)
	//	PiDatalog(func, A_tHandShake,	tHandShake,		set_fail_bin,	POWER_NANO);	
 


	if(gDEBUG)
	printf("Function Fosc_post_S Done\n");

	
	//NWell jfet TempCo Adjust
	if (0)
	{
#define RNW_CODE_SIZE 1024
		int trim_code;
		int r_AF[100] = {0};
		int i, n;

		float SRth[RNW_CODE_SIZE] = {0.0};
		float VFWC_M[RNW_CODE_SIZE] = {0.0};
		float VFWC_P[RNW_CODE_SIZE] = {0.0};
		
		Power_Down_Primary();
		Power_Down_Secondary();
		Disconnect_InvSyn_IM();
		
		for (trim_code = 0; trim_code < RNW_CODE_SIZE; trim_code++)
		{
			//pulse.do_pulse();//********************************************************
			FillMemory(&r_AF, sizeof(r_AF), 0);
			Powerup_Secondary_in_Testmode(gProgRead_AFreg_S, 0, 0);

			Read_Secondary_AF_Reg(r_AF);	//must be followed by write

			//Rnw(4:1)
			r_AF[13] = (trim_code & 1);
			r_AF[14] = (trim_code & 2) >> 1;
			r_AF[15] = (trim_code & 4) >> 2;
			r_AF[16] = (trim_code & 8) >> 3;
			//Rnw(6:5)
			r_AF[11] = (trim_code & 16) >> 4;
			r_AF[12] = (trim_code & 32) >> 5;
			//IintTC(4:1)
			r_AF[38] = (trim_code & 64) >> 6;
			r_AF[39] = (trim_code & 128) >> 7;
			r_AF[40] = (trim_code & 256) >> 8;
			r_AF[41] = (trim_code & 512) >> 9;
			// SR trim bits
			r_AF[26] = 0;
			r_AF[27] = 0;
			r_AF[28] = 0;
			r_AF[29] = 0;

			Write_Secondary_AF_Reg(r_AF);

			VO_dvi->set_voltage(VO_ch, 0.0,		RANGE_5_V);	// DVI_9_0
			wait.delay_10_us(10);

			//7. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
			FW_dvi->set_voltage(FW_ch, -0.5,	RANGE_10_V);	// DVI_11_1
			wait.delay_10_us(10);
			FW_dvi->set_voltage(FW_ch, 5.0,		RANGE_10_V);	// DVI_11_1
			wait.delay_10_us(10);

			//8. Clock VOUT to TestMode#
			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode1_FB_S);

			SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, RANGE_10_V);
			SR_dvi2k->close_relay(CONN_SENSE1);

			REQ_ovi->set_voltage(REQ_ch, gREQ_2V, RANGE_5_V);
			//wait.delay_10_us(10);

			Close_relay(K5);		//Connect SR to 5nF
			delay(3);

			//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
			FW_dvi->set_current(FW_ch, 1e-3, RANGE_300_MA);

			for (i = 0; i < 2; i++)
			{
				FW_dvi->set_voltage(FW_ch, -1.0, RANGE_10_V);
				wait.delay_10_us(10);
				FW_dvi->set_voltage(FW_ch, 5.0, RANGE_10_V);
				wait.delay_10_us(10);
			}
			REQ_ovi->set_voltage(REQ_ch, gREQ_V_Idle, RANGE_5_V);
			FW_dvi->set_voltage(FW_ch, -0.5, RANGE_10_V);

			//Ramp up FW so SR will toggle from Low to High
			search_SR_th_TM1(&SRth[trim_code]);
			printf("trim_code = %d; SRth = %.2f\n", trim_code, SRth[trim_code] * 1000);

			Power_Down_Secondary();
			Open_relay(K5);		//Disconnect SR from 5nF
			delay(5);
		}

		////Write to debug file
		time_t rawtime;
		struct tm * timeinfo;
		char timestamp[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timestamp, 80, "%y%m%d%H%M", timeinfo);

		char file_name_Id[200] ="e:\\dl4\\MINNO_S_SR_TC_";
		strcat (file_name_Id, timestamp);
		strcat (file_name_Id, ".csv");
		FILE * fpr = fopen(file_name_Id, "w");
		if (! fpr) return;
		
		fprintf(fpr, "Serial number,%d\n", SERIAL_NUM);
		fprintf(fpr, "n,VSR_th(mV)\n");

		for (n = 0; n < RNW_CODE_SIZE; n++)
		{
				fprintf(fpr, "%d,%.3f\n", n, SRth[n] * 1000);
		}
		fprintf(fpr,"\n" );

		fclose(fpr);
	}
}
