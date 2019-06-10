
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

	Func_name = "Setup";

	int Setup = 0;
	float BUFRes_Div_ratio = 0.0;
	float vfrc = 0.0, ifrc = 0.0;
	float DVI2K_ch0_Temp = 0.0, DVI2K_ch1_Temp = 0.0;
	float hvs15_relay_chk = 0.0, hvs19_relay_chk = 0.0;

	hvs_15->init();
	if (disable900V == 0) hvs_19->init();

	gDisplay_FuncNum = 1;	//must turn on for Production use
	gDisplay_ErrDlog = 1;	//Error datalog flag to turn on/off 

	gFuncNum = 1;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Setup,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest && !g_Setup_OK)//Don't continue if Invsync check fails
		return;

//************************Initialize global variable**********************************
//************************************************************************************
/*=====================   Turn ON/OFF Stress of Pri and Secondary   =================*/
	gStress_ON = 1;
	g_Stress_passed = 0;

/*=====================   Program flow Variables   ==================================*/

/*=====================   Characterization Variables   ==============================*/
	gCHAR_FLOW = ours->CHAR_FLOW;

/*=====================   VBP Variables   ===========================================*/
	gVBPP_P_Init = 0.0;
	gVBPP_M_Init = 0.0;
	gVBPP_VCEN = 0.0;
	gVBPP_Low_Voltage_PU = 0.0;
	gVBPS_P_Init = 0.0;
	gVBPS_M_Init = 0.0;
	gVBPS_VCEN = 0.0;

/*=====================   IzPre Function Variables   ================================*/
	gIzpt_NoZ_s = 0.0;
	gIZ_NoZ_s = 0.0;
	gVread_AF_primary = 0.0;
	gVread_AF_secondary = 0.0;
	gTrimmed_Device = 0;

/*=====================   Fosc Function Variables   =================================*/
	gFosc_pt_P = 0.0;
	gFOSC_exp_P = 0.0;
	gFOSC_pt_S = 0.0;
	gFOSC_exp_S = 0.0;
	gFOSC_post_S = 0.0;

/*=====================   tOVL Variables   ==========================================*/
	g_tOVL_Pt	= 0;
	g_tOVL_exp	= 0;


	gHandShake_PASS = 0;


/*=====================   ILIM Variables   ==========================================*/
	gILIM_pt_S  = 0.0;
	gILIM_exp_S = 0.0;
	gILIM_I2f_pt_S = 0.0;

/*=====================   VBP_Supply Function Variables   ===========================*/
	gVshunt_Init_Pr = 0.0;
	gVshunt_Init_Se = 0.0;

/*=====================   BPS STRESS Variables   ====================================*/
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

//****************************   Setup Resources   ***********************************
//************************************************************************************
	delay(ours->Wait);		//User forced wait
	TRIM_ENABLE			= ours->TRIM_ENABLE;
	gTrim_Voltage		= ours->Trim_Voltage;
	gDEBUG				= ours->Debug;	// global gDEBUG, set to 0 to turn of all debugging code
	gREL_FLOW			= ours->REL_FLOW;

	ours_ENG_Option		= ours->ENG_Option;
	ours_v_debug		= ours->v_debug;
	ours_i_debug		= ours->i_debug;
	ours_ms_debug		= ours->ms_debug;
	ours_SiliconRev_S	= ours->SiliconRev_S;
	ours_SiliconRev_P	= ours->SiliconRev_P;
	g_GRR				= ours->GRR;

	gCV_FB_S			= 0;	// TODO: remove this variable, not use in MINNO-PS
	g_ReTrim_P			= 1;	// Turn on retrim primary in case of trimming issue.

	if (g_GRR)		//Disable trimming when GRR mode is ON
	{
		TRIM_ENABLE = 0;			//Disable Trim while running GRR
	}

	BPP_4p7uF = false;	// TODO: remove this variable, not very useful
	BPP_p47uF = false;	// TODO: remove this variable, not very useful

	gDly_Wait_and_Listen_Test_Mode		= 260;	//Test   Mode delay for "Wait and Listen" 2.5ms (250 x 10us)
	gDly_Wait_and_Listen_Normal_Mode	= 90;	//Normal Mode delay for "Wait and Listen" 90 ms

	g_readTime_p						= 10;	//x*10us => 100us // TODO: remove this variable
	g_readTime_s						= 10;	//x*10us => 100us // TODO: remove this variable
	g_trimTime_p						= 500;	//x*10us =>   5ms 
	g_trimTime_s						= 500;	//x*10us =>   5ms // TODO: remove this variable

	GetSerialNum(CURRENT_SERIAL_NUM);
	SERIAL_NUM = atoi(CURRENT_SERIAL_NUM);

	if (First_Time_Run || SERIAL_NUM < 2)
		mode_change();

	if (gTrim_DOPL_S)
		gREL_FLOW = 1;
	else
		gREL_FLOW = 0;

	gCV_Low = gREQ_2V;	// TODO: replace all gCV_Low with gREQ

	gAF_1ST_TRIM_DELAY	= ours->AF_1ST_TRIM_DELAY;
	gAF_2ND_TRIM_DELAY	= ours->AF_2ND_TRIM_DELAY;
	gAF_2ND_TRIM_TRHD	= ours->AF_2ND_TRIM_TRHD;
	gVread_AF_secondary	= ours->VFW_Read_AF;
	gVread_AF_primary	= 5.5;	//lower to 5.5V and expect post trim to be around 200uA to 300uA instead of 600uA to 800uA)

	// Check DVI2K ch0 temperature
	FWC_dvi2k->set_meas_mode(FWC_ch, DVI_MEASURE_TEMP);
	wait.delay_10_us(10);
	DVI2K_ch0_Temp = FWC_dvi2k->measure();	// If it is greater than 140F, DVI is overheat

	// Check DVI2K ch1 temperature
	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_TEMP);
	wait.delay_10_us(10);
	DVI2K_ch1_Temp = SR_dvi2k->measure();	// If it is greater than 140F, DVI is overheat

	// Set up test flow
	if (OPCODE==4250 || OPCODE==4300 ||OPCODE==4500)	// Disable trimming for temperature
		TRIM_ENABLE = 0;

	AbortTest	= false;
	Setup		= 0;
	if (!HardwareList.VerifyRequiredBoardList() || (g_Setup_OK == FALSE))	//xie 6/29/2017  (if wrong IM used, will catch it)
	{
		Setup	= 999;				// Failed setup
	}

	if (First_Time_Run)
	{
		if (OPCODE == 4200 && gGaN == true)
		{
			if (disable900V == 1)
			{
				MessageBox(NULL,"HVS19 IS REQUIRED FOR OPCODE4200","SETUP ERROR", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
				g_Setup_OK	= 0;
				Setup		= 999;				// Failed setup
				AbortTest	= true ;
			}
		}
		else
		{
			disable900V = 1;
		}

		if (   !strnicmp(CsSysInfo.strBoardName, "CS1422",  6)		// PCI 14bits
			|| !strnicmp(CsSysInfo.strBoardName, "CSE1422", 7))		// PCI 14bits
		{
			gDig_Type = 1422;	//Razor 1422
		}
		else if (!strnicmp(CsSysInfo.strBoardName, "CS1622",  6)	//PCIex 16bits
			  || !strnicmp(CsSysInfo.strBoardName, "CSE1622", 7))	//PCIex 16bits
		{
			gDig_Type = 1622;	//Razor 1422
		}

		SAMPLE_SIZE = GAGE_POST_4K;
		BUFRes_Div_ratio = 1.0;
		BUFgain = Rdson_Buffer_Cal(BUFRes_Div_ratio);
	}

	PiDatalog(func, A_Setup,			Setup,				set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_BUFgain,			BUFgain,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_DVI2K_ch0_Temp,	DVI2K_ch0_Temp,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_DVI2K_ch1_Temp,	DVI2K_ch1_Temp,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_gDevNum,			gDevNum,				set_fail_bin,	POWER_UNIT);

	//printf debug, add datalogs later
	if (gDEBUG && gHcode) printf("H_code = %.0f\n", gHcode );
	if (gDEBUG && gHcode) printf("HC_code = %.0f\n", gHcode );
	if (gDEBUG) printf("H_code_6dig = %.0f\n", gH_code_AN );
	if (gDEBUG) printf("HZ_code_6dig = %.0f\n", gHZ_code_AN );
	
	if (gHZ_code_AN > 0 ) gHcode = gHZ_code_AN;

	PiDatalog(func, A_Hcode,			gHcode,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Dig_Type,			gDig_Type,			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_LB_ID,			gLB_ID,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_LB_Type_Rev,		gLB_Type_Rev,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_CB_ID,			gCB_ID,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_CB_Type_Rev,		gCB_Type_Rev,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IB_ID,			gIB_ID,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IB_Type_Rev,		gIB_Type_Rev,		set_fail_bin,	POWER_UNIT);
	
	/*========================  HVS RELAY CHECK (RL9) ====================================*/
	//hvs_relay_chk is sampling test 1/25, when failed will perform 100%.
	skiphvs++; // counter for sampling hvs_relay_chk test 1/25

	if (skiphvs == 1 || hvsflag == 1)  // if hvs_relay_chk fail, hvsflag=1 to enable 100% test
	{
		vfrc = 600.0;			// 600V to 1Mohm resistor
		ifrc = 1e-3;

		// Instrument protection
		OVI_disconnect_all();
		TMU_disconnect_all();
		Open_relay(K1);			// Disconnect DVI_11_0 from Drain directly (Kelvin connection)
		Open_relay(K2);
		Open_relay(K4);			// Disconnect HVS from Drain
		Open_relay(K11);		// Disconnect BPP from DVI
		Open_relay(K5);			// Disconnect HVS from FW pin
		Open_relay(K18);		// Disconnect FW  from DVI-11-1
		mux_14->open_relay(MUX_BANK_8_1);	
		mux_14->open_relay(MUX_1_1);
		tmu_6->open_relay(TMU_EXT_DRV1);
		wait.delay_10_us(250);

		// close hvs relay force pos and neg
		hvs_15->set_voltage(0.0,		RANGE_1_KV);
		hvs_15->set_current(2e-6,		RANGE_1_MA);
		hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
		wait.delay_10_us(20);

		hvs_15->close_relay(HVS_NEG_FORCE);
		hvs_15->close_relay(HVS_SHORT_NEG_FS);
		hvs_15->close_relay(HVS_FORCE_POS);
		hvs_15->close_relay(HVS_SHORT_POS_FS);
		delay(2);

		hvs_15->set_current(ifrc,		RANGE_1_MA);
		hvs_15->set_voltage(vfrc,		RANGE_1_KV);	// 600V to 1Mohm resistor
		delay(10);										// Give HVS time for the voltage to come up
														// Some testers require 10ms to come up all the way

		hvs15_relay_chk = hvs_15->measure_average(5);
		PiDatalog(func, A_HVS15_RELAY_CHK,	hvs15_relay_chk,	31,		POWER_MILLI);

		// hvs power down
		hvs_15->set_voltage(0.0,		RANGE_1_KV);
		wait.delay_10_us(20);
		hvs_15->open_relay(HVS_NEG_FORCE);
		hvs_15->open_relay(HVS_SHORT_NEG_FS);
		hvs_15->open_relay(HVS_SHORT_POS_FS);
		hvs_15->open_relay(HVS_FORCE_POS);
		delay(2);

		hvs_15->init();

		if (hvs15_relay_chk < 0.00045 || hvs15_relay_chk > 0.00075)
		{
			hvsflag = 1;	// trigger hvsflag to 1 when failed limit
		}

		if (disable900V == 0)
		{
			// close hvs relay force pos and neg
			hvs_19->set_voltage(0.0,		RANGE_1_KV);
			hvs_19->set_current(2e-6,		RANGE_1_MA);
			hvs_19->set_meas_mode(HVS_MEASURE_CURRENT);
			wait.delay_10_us(20);

			hvs_19->close_relay(HVS_NEG_FORCE);
			hvs_19->close_relay(HVS_SHORT_NEG_FS);
			hvs_19->close_relay(HVS_FORCE_POS);
			hvs_19->close_relay(HVS_SHORT_POS_FS);
			delay(2);

			hvs_19->set_current(ifrc,		RANGE_1_MA);
			hvs_19->set_voltage(vfrc,		RANGE_1_KV);	// 600V to 1Mohm resistor
			delay(10);										// Give HVS time for the voltage to come up
															// Some testers require 10ms to come up all the way

			hvs19_relay_chk = hvs_19->measure_average(5);
			PiDatalog(func, A_HVS19_RELAY_CHK,	hvs19_relay_chk,	31,		POWER_MILLI);

			// hvs power down
			hvs_19->set_voltage(0.0,		RANGE_1_KV);
			wait.delay_10_us(20);
			hvs_19->open_relay(HVS_NEG_FORCE);
			hvs_19->open_relay(HVS_SHORT_NEG_FS);
			hvs_19->open_relay(HVS_SHORT_POS_FS);
			hvs_19->open_relay(HVS_FORCE_POS);
			delay(2);

			hvs_19->init();	

			if (hvs19_relay_chk < 0.00045 || hvs19_relay_chk > 0.00075)
			{
				hvsflag = 1;	// trigger hvsflag to 1 when failed limit
			}
		}
		OVI_connect_all();
	}

	if (skiphvs == 25)//reset sampling counter for every 25 counts.
	{
		skiphvs = 0;
	}
	else
	{
		skiphvs = skiphvs;
	}

	/*=====================================================================================*/
	if (PiGetAnyFailStatus())		
	{
		if (g_Setup_OK == FALSE)
		{
			MessageBox(NULL,"WRONG COMBINATION OF HW. MAKE SURE LB, CB & IM ARE USED PROPERLY!","SETUP ERROR", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		}
		else
		{
			MessageBox(NULL,"IF fail Setup and/or BUFgain, first check if your ID cable is connected, then if your unit is loaded backwards!!","SETUP ERROR", MB_OK | MB_ICONERROR | MB_TOPMOST | MB_SYSTEMMODAL);
		}
		First_Time_Run = true;			// Re-run calibration if setup fails
		AbortTest = true ;
	}
	else
		First_Time_Run = false;	

	if (gDEBUG == 1)
		printf("\nFunction Setup Done\n");
}
