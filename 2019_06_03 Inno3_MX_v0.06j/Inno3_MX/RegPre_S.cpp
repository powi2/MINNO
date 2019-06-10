//==============================================================================
// RegPre_S.cpp (User function)
// 
//    void RegPre_S_user_init(test_function& func)
//    void RegPre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "RegPre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void RegPre_S_user_init(test_function& func)
{
	RegPre_S_params *ours;
    ours = (RegPre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void RegPre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    RegPre_S_params *ours;
    ours = (RegPre_S_params *)func.params;


	int set_fail_bin = ours->fail_bin;

	Func_name = "RegPre_S";

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_RegPre_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;


	FillMemory(&gSR_AF, sizeof(gSR_AF), -1);
	Powerup_Secondary_in_Testmode(gProgRead_AFreg_S, 0, 0);

	Read_Secondary_AF_Reg(gSR_AF);

	if(LB_Rev>=5||g_TurretCB)
	{
		//Do not remove this power down sequence.  Glitches will cause repeatability on the next IZpost test.
		ddd_7->ddd_set_voltage_ref(0.0);
		ddd_7->ddd_set_lo_level(0.1);							// Will immediately change to this level upon execution 
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(5);
		FW_dvi->set_voltage(FW_ch, 0.0, 	RANGE_50_V);	// DVI_11_1
		REQ_ovi->set_voltage(REQ_ch, 0.0, 	RANGE_5_V);	// OVI_1_2
		BPS_dvi->set_voltage(BPS_ch, 2.0,	RANGE_5_V);	// DVI_9_1
		wait.delay_10_us(50);
		BPS_dvi->set_voltage(BPS_ch, 1.0,	RANGE_5_V);	// DVI_9_1
		wait.delay_10_us(50);
		BPS_dvi->set_voltage(BPS_ch, 0.5,	RANGE_5_V);	// DVI_9_1
		wait.delay_10_us(50);
		BPS_dvi->set_voltage(BPS_ch, 0.0,	RANGE_5_V);	// DVI_9_1

		Open_relay(K18);	//FW to DVI-11-1
		Open_relay(K26);	//SR to DDD-7-5
		Open_relay(K27);	//VO to DDD-7-4
		delay(4);
	}
	else
	{
		Power_Down_Secondary();

		Open_relay(K18);	//FW to DVI-11-1
		Open_relay(K26);	//SR to DDD-7-5
		Open_relay(K27);	//VO to DDD-7-4
		delay(4);
	}

	//Datalog
	PiDatalog(func, A_RegPt_F1_S,			gSR_AF[gFosc_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_F2_S,			gSR_AF[gFosc_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_F3_S,			gSR_AF[gFosc_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_F4_S,			gSR_AF[gFosc_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_PK1spdLd_S,		gSR_AF[gPK_ssSpeed_AF_Addr_Start],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_PK2_S,			gSR_AF[gPK_ssSpeed_AF_Addr_Start + 1],	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_PK3_S,			gSR_AF[gPK_ssSpeed_AF_Addr_Start + 2],	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Rnw5_S,			gSR_AF[gRnw_AF_Addr_Start],				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Rnw6_S,			gSR_AF[gRnw_AF_Addr_Start + 1],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Rnw1_S,			gSR_AF[gRnwFine_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Rnw2_S,			gSR_AF[gRnwFine_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Rnw3_S,			gSR_AF[gRnwFine_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Rnw4_S,			gSR_AF[gRnwFine_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_FWC2_S,			gSR_AF[gFWC2_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_NoFWC100mV_S,	gSR_AF[gNoFWC100mV_AF_Addr_Start],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Cap1_S,			gSR_AF[gCap_AF_Addr_Start],				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Cap2_S,			gSR_AF[gCap_AF_Addr_Start + 1],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Cap3_S,			gSR_AF[gCap_AF_Addr_Start + 2],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_PKdig1_S,		gSR_AF[gPKdig_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_PKdig2_S,		gSR_AF[gPKdig_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_PKdig3_S,		gSR_AF[gPKdig_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_PKdig4_S,		gSR_AF[gPKdig_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_SRth1_S,		gSR_AF[gSRth_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_SRth2_S,		gSR_AF[gSRth_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_SRth3_S,		gSR_AF[gSRth_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_SRth4_S,		gSR_AF[gSRth_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_Vshunt_S,		gSR_AF[gVshunt_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_V1_S,			gSR_AF[gVref_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_V2_S,			gSR_AF[gVref_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_V3_S,			gSR_AF[gVref_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_V4_S,			gSR_AF[gVref_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_V5_S,			gSR_AF[gVref_AF_Addr_Start + 4],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_V6_S,			gSR_AF[gVref_AF_Addr_Start + 5],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_IintTC1_S,		gSR_AF[gIintTC_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_IintTC2_S,		gSR_AF[gIintTC_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_IintTC3_S,		gSR_AF[gIintTC_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_IintTC4_S,		gSR_AF[gIintTC_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_DOPL_S,			gSR_AF[gDOPL_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_REQlow_S,		gSR_AF[gREQlow_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_XFWPK_S,		gSR_AF[gXFWPK_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RegPt_LO_dis_S,		gSR_AF[gLO_dis_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);

	if(gDEBUG)
	printf("Function RegPre_S Done\n");
}
