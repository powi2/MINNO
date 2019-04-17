
//==============================================================================
// Setup.cpp (User function)
// 
//    void Setup_user_init(test_function& func)
//    void Setup(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "Setup.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Setup_user_init(test_function& func)
{
	Setup_params *ours;
    ours = (Setup_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Setup(test_function& func)
{
    // The two lines below must be the first two in the function.
    Setup_params *ours;
    ours = (Setup_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	int Setup =0;
	int BUFRes_Div_ratio =0.0;
	float vfrc =0.0, ical_frc =0.0;
	float DVI2K_ch0_Temp =0.0, DVI2K_ch1_Temp =0.0;
	float hvs_relay_chk=0;

	gDisplay_FuncNum=1;	//must turn on for Production use
	gDisplay_ErrDlog=1; //Error datalog flag to turn on/off 

	hvs_15->init();	
	
	gFuncNum=1;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Setup,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest && !g_Setup_OK)//Don't continue if Invsync check fails
		return;

int InvSync_pass = 0;

//************************Initialize global variable**********************************
//************************************************************************************
/*=======================   Turn ON/OFF Stress of Pri and Secondary =================*/
	gStress_ON = 1;
	g_Stress_passed = 0;

/*=======================   Program flow Variables    ===============================*/
	gRemove_Test_from_all_Devices	=true;	
	gRemove_Test_per_Device_option	=true;
	Program_load *p = (Program_load*) g_program;
	gStoponfail = !(p->operator_setup.cont_on_fail); //reverse logic of continue_on_fail

/*============================    Characterization Variables    =================================*/
	gCHAR_FLOW		= ours->CHAR_FLOW;
/*============================    VBP Variables    =================================*/
	gVBPS_P_Init=0.0; gVBPP_P_Init=0.0; gVBPP_M_Init= 0.0; gVBPS_M_Init=0.0; 
	gVBPP_VCEN =0.0; gVBPS_VCEN=0.0;
	//gVBPP_Low_Voltage_PU = 1.5;
	gVBPP_Low_Voltage_PU = 0.0;

 /*=======================    IzPre Function Variables    ===============================*/
	gIzpt_NoZ_s=0.0;
	gIZ_NoZ_s=0.0;
    gVread_AF_primary =0.0; gVread_AF_secondary=0.0;
    gSec_tr1_ZapTime  =0.0;
    gSec_tr2_AFtrhd   =0.0;
	gTrimmed_Device	  =0;

/*====================    Fosc Function Variables    ===============================*/
	gFosc_pt_P =0.0;    gFOSC_pt_S =0.0;
    gFOSC_exp_P =0.0;   gFOSC_exp_S =0.0;
    gFOSC_post_S =0.0;

/*======================    TonMax replace by tOVL Variables    ====================================*/
    gTonMax_Pt  =0.0;
    gTonMax_exp =0.0;
	g_tOVL_Pt	=0;
	g_tOVL_exp	=0;
    gHandShake_PASS =0;

/*======================    CV Variables    ====================================*/
	gCV_FB_pt_S  =0.0;
	gCV_VO_pt_S  =0.0;
	gCV_exp_S =0.0;
	gCV_S =0.0;
    gVclamp_2pct_S=0.0; gVclamp_10pct_S=0.0;
	g_vFBth_SC_S =0.0;
	gARSTth_S =0.0;

/*======================    CC Variables    ====================================*/
	gCC_pt_S =0.0;
	gCC_exp_S =0.0;
 
/*======================    CB Variables    ====================================*/
	gCB_pt_S =0.0;
    gCB_exp_S =0.0;

/*======================    ILIM Variables    ====================================*/
    gILIM_pt_S  =0.0;
    gILIM_exp_S =0.0;
	gILIM_I2f_pt_S =0.0;

/*=======================    CV_CC_CB_Vout Function Variables    ===============================*/
	gISvth =0.0;
	MEAS_Isvth_FLAG =0;

/*=======================    VBP_Supply Function Variables    ===============================*/
    gVshunt_Init_Pr =0.0;
    gVshunt_Init_Se =0.0;

/*=======================    BPS STRESS Variables    ===============================*/
	gILL_D_pre		= 99 mA; 
	gILL_UV_pre		= 99 mA; 
	gILL_REQ_pre	= 99 mA; 
	gILL_BPS_pre	= 99 mA; 
	gILL_SR_pre		= 99 mA; 
	gILL_VO_pre		= 99 mA; 
	gILL_FW_pre		= 99 mA;
	gILH_D_pre		= 99 mA; 
	gILH_UV_pre		= 99 mA; 
	gILH_REQ_pre	= 99 mA; 
	gILH_BPS_pre	= 99 mA; 
	gILH_SR_pre		= 99 mA; 
	gILH_VO_pre		= 99 mA; 
	gILH_FW_pre		= 99 mA;
	gIDS_FW_pre		= 99 mA;

//****************************    Setup Resources  **********************************
//************************************************************************************
	Func_name = "Setup";

	delay(ours->Wait);		//User forced wait
	TRIM_ENABLE		 = ours->TRIM_ENABLE;
	gTrim_Voltage	 = ours->Trim_Voltage;
	gDEBUG			 = ours->Debug;	//global gDEBUG, set to 0 to turn of all debugging code
	gREL_FLOW		 = ours->REL_FLOW;
	if(gTrim_DOPL_S) 
		gREL_FLOW = 1;
	else
		gREL_FLOW = 0;

	//Primary_Si_Rev   = ours->Primary_Si_Rev;
	//Secondary_Si_Rev = ours->Secondary_Si_Rev;
	ours_ENG_Option  = ours->ENG_Option;
	ours_v_debug	 = ours->v_debug;
	ours_i_debug	 = ours->i_debug;
	ours_ms_debug	 = ours->ms_debug;
	ours_SiliconRev_S= ours->SiliconRev_S;
	ours_SiliconRev_P= ours->SiliconRev_P;
	g_GRR            = ours->GRR;

	g_DDD_Reload     = 0;
	gCV_VO_S		 = 0;
	gCV_FB_S		 = 0;
	g_ReTrim_P       = 1; //Turn on retrim primary in case of trimming issue.

	///////////////////////////////////////////////////////////////////////////////////////
	//HL added here.
	g_Original_ISVth_Search = 0;
	//g_LB_RevE = 1;
	//////////////////////////////////////////////////////////////////////////////////////////
	if(g_GRR)		//Disable trimming when GRR mode is ON
	{
		TRIM_ENABLE =0;			//Disable Trim while running GRR
	}
	//if(ours_ENG_Option==98)		//Remove this once CREATE updates a gGRR parameter
	//{
	//	g_TurretCB =1;
	//	g_GRR =1;
	//	TRIM_ENABLE =0;			//Disable Trim while running GRR
	//}

	BPP_4p7uF = false;
	BPP_p47uF = false;

//	gSEC_8in	= true;
	gSEC_8in	= false;

//	gDly_Wait_and_Listen_Test_Mode		= 600;	//Test   Mode delay for "Wait and Listen" 2.5ms (250 x 10us)
	gDly_Wait_and_Listen_Test_Mode		= 260;	//Test   Mode delay for "Wait and Listen" 2.5ms (250 x 10us)
	gDly_Wait_and_Listen_Normal_Mode	= 90;	//Normal Mode delay for "Wait and Listen" 90 ms
	g_readTime_p						= 10;	//x*10us => 100us 
	g_readTime_s						= 10;	//x*10us => 100us 
	g_trimTime_p						= 500;	//x*10us =>   5ms 
	g_trimTime_s						= 500;	//x*10us =>   5ms 

	g_ILIM_dly							= 95;
	g_REL_dly							= 100;
	//g_ILIM_dly							= 1;
	//g_REL_dly							= 1;

	GetSerialNum(CURRENT_SERIAL_NUM);
	SERIAL_NUM= atoi(CURRENT_SERIAL_NUM);

	if (First_Time_Run || SERIAL_NUM <2)
		mode_change();

	//Reset CV 10% above after mode change
	gCV_FB_Init_pt_S	= gCV_FB_TARGET;
	gCVth_5pct_Lower	= gCV_FB_TARGET * 0.95;	//Above highest AR 90% threshold
	gCVth_5pct_Higher	= gCV_FB_TARGET * 1.05;	//
	gCVth_8pct_Higher	= gCV_FB_TARGET * 1.08;	//
	gCVth_10pct_Higher	= gCV_FB_TARGET * 1.10;
	gCVth_15pct_Higher	= gCV_FB_TARGET * 1.15;

	//Determine what's the lowest vFB voltage we want to use to have device switching for different options.
	//if(gTrim_AR_S==3)				//Fixed ARth Vout=3.45V
	//	gCV_Low = 0.8;				//This will be lower than the lowest acceptable CVpre 
	//else
	//	gCV_Low = gCVth_5pct_Lower;	//
	//gCV_Low = 0.8;
	gCV_Low = 1.7;

	gAF_1ST_TRIM_DELAY = ours->AF_1ST_TRIM_DELAY;
	gAF_2ND_TRIM_DELAY = ours->AF_2ND_TRIM_DELAY;
	gAF_2ND_TRIM_TRHD  = ours->AF_2ND_TRIM_TRHD;
	gVread_AF_secondary = ours->VFW_Read_AF;
	gVread_AF_primary	=5.5;	//lower to 5.5V and expect post trim to be around 200uA to 300uA instead of 600uA to 800uA)
//	gVread_AF_primary	=7.0;
//	gVread_AF_primary	=10.0;

	// Check DVI2K ch0 temperature
	FWC_dvi2k->set_meas_mode(FWC_ch,DVI_MEASURE_TEMP);
	wait.delay_10_us(10);
	DVI2K_ch0_Temp =  FWC_dvi2k->measure();	// If it is greater than 140F, DVI is overheat

	// Check DVI2K ch1 temperature
	SR_dvi2k->set_meas_mode(SR_ch,DVI_MEASURE_TEMP);
	wait.delay_10_us(10);
	DVI2K_ch1_Temp =  FWC_dvi2k->measure(); // If it is greater than 140F, DVI is overheat


	// Set up test flow
	if (OPCODE==4250 || OPCODE==4300 ||OPCODE==4500)	// Disable trimming for temperature
		TRIM_ENABLE =0;

	AbortTest =0;
	Setup     =0;
	

	if( !HardwareList.VerifyRequiredBoardList() || (g_Setup_OK == FALSE))	//xie 6/29/2017  (if wrong IM used, will catch it)
	//if(g_Setup_OK == FALSE)
	{
		Setup	= 999;				// Failed setup	
	}

	if (First_Time_Run)
	{

		//////Determine if InvSyn Circuit is working properly
		////Check_InvSync_Circuit(&InvSync_pass);
		////if(!g_TurretCB && InvSync_pass == false)
		////{
		////	MessageBox(NULL,"InvSyn Circuit is bad!","SETUP ERROR", MB_OK);
		////	Setup = 999;
		////}
		//Determine what digitizer we have on PC
		//////if (CsSysInfo.u32BoardType == 35)
		//////	gDig_Type = 1422;	//Razor 1422
		//////else if (CsSysInfo.u32BoardType == 33)
		//////	gDig_Type = 1622;	//Razor 1622
		//////else if (CsSysInfo.u32BoardType == 7)
		//////	gDig_Type = 14100;	//Older 14100

		if (   !strnicmp( CsSysInfo.strBoardName, "CS1422", 6 )// PCI 14bits
			|| !strnicmp( CsSysInfo.strBoardName, "CSE1422", 7 ))// PCI 14bits
		{
			gDig_Type = 1422;	//Razor 1422
		}
		else if (!strnicmp( CsSysInfo.strBoardName, "CS1622", 6 )//PCIex 16bits
			|| !strnicmp( CsSysInfo.strBoardName, "CSE1622", 7 ))//PCIex 16bits
		{
			gDig_Type = 1622;	//Razor 1422
		}


		SAMPLE_SIZE = GAGE_POST_4K;
		BUFRes_Div_ratio = 1.0;
		BUFgain = Rdson_Buffer_Cal(BUFRes_Div_ratio);

		vfrc = 2.0;

		if(gCC_Amp_TARGET > 0)
		{
			// Use 90%CC to measure CB
			ical_frc = gCC_Amp_TARGET * 0.9;
			iPV3_Cal_CC90 = iPV3_CC80_Cal(vfrc, ical_frc);
			iPV3_CC90 = gCC_Amp_TARGET * 0.9* iPV3_Cal_CC90;	// Force 90% of target CC from PV3. Include cal factor to get the exact 80%
		
			// Start CC search from 80% of target
			ical_frc = gCC_Amp_TARGET * 0.8;
			iPV3_Cal_CC80 = iPV3_CC80_Cal(vfrc, ical_frc);
			iPV3_CC80 = gCC_Amp_TARGET * 0.8* iPV3_Cal_CC80;	// Force 80% of target CC from PV3. Include cal factor to get the exact 80%


			ical_frc = gCC_Amp_TARGET * 0.65;
			iPV3_Cal_CC65 = iPV3_CC80_Cal(vfrc, ical_frc);
			iPV3_CC65 = gCC_Amp_TARGET * 0.65* iPV3_Cal_CC65;	// Force 65% of target CC from PV3. Include cal factor to get the exact 80%

			ical_frc = gCC_Amp_TARGET * 0.55;
			iPV3_Cal_CC55 = iPV3_CC80_Cal(vfrc, ical_frc);
			iPV3_CC55 = gCC_Amp_TARGET * 0.55* iPV3_Cal_CC55;	// Force 55% of target CC from PV3. Include cal factor to get the exact 80%
			
		}
	}
	if(gCC_Amp_TARGET > 0)
	{
		PiDatalog(func, A_iPV3_Cal_CC90,	iPV3_Cal_CC90,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_iPV3_Cal_CC80,	iPV3_Cal_CC80,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_iPV3_Cal_CC65,	iPV3_Cal_CC65,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_iPV3_Cal_CC55,	iPV3_Cal_CC55,		set_fail_bin,	POWER_UNIT);
	}
	PiDatalog(func, A_Setup,			Setup,				set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_BUFgain,			BUFgain,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_DVI2K_ch0_Temp,	DVI2K_ch0_Temp,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_DVI2K_ch1_Temp,	DVI2K_ch1_Temp,		set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_Primary_Si_Rev,		Primary_Si_Rev,		set_fail_bin,	POWER_UNIT);	
	//PiDatalog(func, A_Secondary_Si_Rev,	Secondary_Si_Rev,	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_gDevNum,			gDevNum,				set_fail_bin,	POWER_UNIT);

	//printf debug, add datalogs later
	if (gDEBUG && gHcode) printf("H_code = %.0f\n", gHcode );
	if (gDEBUG && gHcode) printf("HC_code = %.0f\n", gHcode );
	if (gDEBUG) printf("H_code_6dig = %.0f\n", gH_code_AN );
	if (gDEBUG) printf("HZ_code_6dig = %.0f\n", gHZ_code_AN );
	

	if (gDEBUG) printf("Trimops_Table_Rev = %.2f\n", gTrimops_Table_Rev_float );

	if (gHcode == 0)
	{
		if (gHZ_code_AN > 0 ) gHcode = gHZ_code_AN;
	}

	PiDatalog(func, A_Hcode,			gHcode,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Dig_Type,			gDig_Type,			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_LB_ID,			gLB_ID,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_CB_ID,			gCB_ID,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IB_ID,			gIB_ID,				set_fail_bin,	POWER_UNIT);
	
/*========================  HVS RELAY CHECK (RL9) ====================================*/
	//hvs_relay_chk is sampling test 1/25, when failed will perform 100%.

	skiphvs++; // counter for sampling hvs_relay_chk test 1/25
	//printf("\nskiphvs---->%d x",skiphvs);

	if (skiphvs == 1 || hvsflag == 1)  // if hvs_relay_chk fail, hvsflag=1 to enable 100% test
	{

	//close hvs relay force pos and neg
	hvs_15->set_current(2e-06);
	hvs_15->set_voltage(0);
	hvs_15->close_relay(HVS_FORCE_POS);
	hvs_15->close_relay(HVS_SHORT_POS_FS);
	hvs_15->close_relay(HVS_NEG_FORCE);
	hvs_15->close_relay(HVS_SHORT_NEG_FS);

	wait.delay_10_us(200);
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT); 

	wait.delay_10_us(500);
	hvs_15->set_current(3e-3,RANGE_10_MA);
	hvs_15->set_voltage(600,RANGE_1_KV); // 600V to 1Mohm resistor

	wait.delay_10_us(1500);
	hvs_relay_chk=hvs_15->measure_average(30);
	//printf("\nhvs_relay_check---->%f A",hvs_relay_chk);
	PiDatalog(func,A_HVS_RELAY_CHK,hvs_relay_chk,31,POWER_MILLI);

	//hvs power down
	wait.delay_10_us(200);
	hvs_15->set_voltage(0);
	wait.delay_10_us(200); 

	hvs_15->init();	

	if (hvs_relay_chk < 0.00045 || hvs_relay_chk > 0.00075)
	{
		hvsflag = 1; // trigger hvsflag to 1 when failed limit
	}
	else
		hvsflag = hvsflag;
	}
	if (skiphvs==25)//reset sampling counter for every 25 counts.
	{
		skiphvs=0;
	}
	else
	{
		skiphvs=skiphvs;
	}

/*=====================================================================================*/



	if (PiGetAnyFailStatus())		
	{
		if(g_Setup_OK == FALSE)
		{
			MessageBox(NULL,"WRONG COMBINATION OF HW. MAKE SURE LB, CB & IM ARE USED PROPERLY!","SETUP ERROR", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		}
		else
		{
			MessageBox(NULL,"IF fail Setup and/or BUFgain, first check if your ID cable is connected, then if your unit is loaded backwards!!","SETUP ERROR", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		}
		First_Time_Run = true;			// Re-run calibration if setup fails
		AbortTest	= true ;
	}
	else
		First_Time_Run = false;	
	
	// If Setup passes, check R8_4wire. If R8_4wire is not programmed, run All calibration again on next run
	if (Setup!= 999 && R8_4wire ==0.0)
	{
		MessageBox(NULL,"LoadBoard Cal Factor for is not programmed","R8_4wire", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		First_Time_Run = true;			// Re-run calibration if setup fails
		AbortTest	= true ;
	}

	//DDD_Load_Patterns();
	

	if(gDEBUG==1)
	printf("\nFunction Setup Done\n");
}
