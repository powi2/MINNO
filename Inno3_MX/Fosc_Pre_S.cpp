//==============================================================================
// Fosc_Pre_S.cpp (User function)
// 
//    void Fosc_Pre_S_user_init(test_function& func)
//    void Fosc_Pre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_Pre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_Pre_S_user_init(test_function& func)
{
	Fosc_Pre_S_params *ours;
    ours = (Fosc_Pre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_Pre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_Pre_S_params *ours;
    ours = (Fosc_Pre_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	Func_name = "Fosc_Pre_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Fosc_Pre_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_GRR == 0 && (OPCODE != 4200 || TRIM_ENABLE == 0))
		return;

	float Fosc_pt_S		=0.0;
		  ////Fosc_pt_Min_S =0.0,
		  ////Fosc_pt_Max_S =0.0;

	float iBPS =0.0;
	float tmeas =0.0, tmeas_min=0.0, tmeas_max=0.0;
	float dummy[100] = {0};
	int	  lcnt =0;
	int	  avg_cycle =0;

	float WAIT_n_LISTEN_TM_starttime=0,
		  WAIT_n_LISTEN_TM_stoptime=0, 
		  WAIT_n_LISTEN_TM_time=0,
		  tElapse=0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//////////

/****************************************************************************
 *					Fosc_pt_S: Secondary Frequency							*
 * Note: Secondary frequency has Jitter									    *
 ****************************************************************************/

//Temporary variable for sampling test purpose
	//int i=0, n_loop=5;
	//for(i=1; i<n_loop; i++)  //This for loop is added for sample testing only.  Remove for production
	//{

		Close_relay(K3);
 		tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 

	if(g_TurretCB)
	{
		tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->stop_trigger_setup(1.2,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	}
	else
	{
		tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
		tmu_6->stop_trigger_setup(1.2,	NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	}

	
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	delay(2);
	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA);	

//#define PU_2ndary_Prog_AF_REG
#ifndef PU_2ndary_Prog_AF_REG
//#if 0
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
	wait.delay_10_us(50);
#endif

#ifdef PU_2ndary_Prog_AF_REG
//#if 1
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

//**** Fosc_post_S Pre
	tmu_6->start_holdoff(5,TRUE);
	tmu_6->stop_holdoff(128,TRUE);
	tmu_6->arm();						// Note that device will do auto-restart in testmode1
	wait.delay_10_us(150);				// Wait for TMU to trigger and to capture 128 cycles (need at least 1280us wait if 10us period)
	tmeas = tmu_6->read(1.5e-3);	 
	tmeas/=128;

	if (tmeas != 0)
		Fosc_pt_S = 1/tmeas;
	else
		Fosc_pt_S = 0.0;	

	gFOSC_pt_S = Fosc_pt_S;				// Pass to global variable

	//Power down
	dvi_13->open_relay(BUS_SENSE1);
	dvi_13->open_relay(BUS_FORCE1);
	mux_14->open_relay(MUX_3_BUS3);

	REQ_ovi->set_voltage(REQ_ch, 0.0,		VOLT_2_RANGE);	// OVI_1_2 Stop device from switching	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,		VOLT_10_RANGE);
	wait.delay_10_us(30);
	D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	VOLT_10_RANGE);	// OVI_1_0
	BPS_dvi->set_voltage(BPS_ch, 0.0, 	VOLT_10_RANGE);	// DVI_9_1

	////Disconnect_InvSyn_IM();  //HL Do not disconnect Inv ckt before powerdown other resources.
	////tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain 
	////Open_relay(K3);
	////Open_relay(K12);					// disconnect DDD7_1	from Vpin(UV)	pin

	Power_Down_Everything();
	Open_All_Relays();

	Disconnect_InvSyn_IM();
	tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain 
	Open_relay(K3);
	Open_relay(K12);	

	//	if(Fosc_pt_S > 15e3 && Fosc_pt_S < 30e3)
	//		break;
	//}

	// Datalog
	PiDatalog(func, A_Fosc_pt_S,	Fosc_pt_S,		set_fail_bin,	POWER_KILO);	
	//PiDatalog(func, A_Fosc_pt_Min_S,Fosc_pt_Min_S,	set_fail_bin,	POWER_KILO);	
	//PiDatalog(func, A_Fosc_pt_Max_S,Fosc_pt_Max_S,	set_fail_bin,	POWER_KILO);	

	if(gDEBUG)
	printf("Function Fosc_Pre_S Done\n");
}
