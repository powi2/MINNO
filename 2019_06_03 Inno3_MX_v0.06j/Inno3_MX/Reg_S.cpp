//==============================================================================
// Reg_S.cpp (User function)
// 
//    void Reg_S_user_init(test_function& func)
//    void Reg_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Reg_S.h"

#include <strstream>
#include <fstream>	// for offstream to work

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Reg_S_user_init(test_function& func)
{
	Reg_S_params *ours;
    ours = (Reg_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Reg_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    Reg_S_params *ours;
    ours = (Reg_S_params *)func.params;


	int set_fail_bin = ours->fail_bin;

	Func_name = "Reg_S";

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Reg_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;


	FillMemory(&gSR_AF_post, sizeof(gSR_AF_post), -1);
	Powerup_Secondary_in_Testmode(gProgRead_AFreg_S, 0, 0);

	Read_Secondary_AF_Reg(gSR_AF_post);

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
	PiDatalog(func, A_Reg_F1_S,			gSR_AF_post[gFosc_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_F2_S,			gSR_AF_post[gFosc_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_F3_S,			gSR_AF_post[gFosc_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_F4_S,			gSR_AF_post[gFosc_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_PK1spdLd_S,	gSR_AF_post[gPK_ssSpeed_AF_Addr_Start],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_PK2_S,		gSR_AF_post[gPK_ssSpeed_AF_Addr_Start + 1],	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_PK3_S,		gSR_AF_post[gPK_ssSpeed_AF_Addr_Start + 2],	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Rnw5_S,		gSR_AF_post[gRnw_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Rnw6_S,		gSR_AF_post[gRnw_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Rnw1_S,		gSR_AF_post[gRnwFine_AF_Addr_Start],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Rnw2_S,		gSR_AF_post[gRnwFine_AF_Addr_Start + 1],	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Rnw3_S,		gSR_AF_post[gRnwFine_AF_Addr_Start + 2],	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Rnw4_S,		gSR_AF_post[gRnwFine_AF_Addr_Start + 3],	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_FWC2_S,		gSR_AF_post[gFWC2_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_NoFWC100mV_S,	gSR_AF_post[gNoFWC100mV_AF_Addr_Start],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Cap1_S,		gSR_AF_post[gCap_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Cap2_S,		gSR_AF_post[gCap_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Cap3_S,		gSR_AF_post[gCap_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_PKdig1_S,		gSR_AF_post[gPKdig_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_PKdig2_S,		gSR_AF_post[gPKdig_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_PKdig3_S,		gSR_AF_post[gPKdig_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_PKdig4_S,		gSR_AF_post[gPKdig_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_SRth1_S,		gSR_AF_post[gSRth_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_SRth2_S,		gSR_AF_post[gSRth_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_SRth3_S,		gSR_AF_post[gSRth_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_SRth4_S,		gSR_AF_post[gSRth_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_Vshunt_S,		gSR_AF_post[gVshunt_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_V1_S,			gSR_AF_post[gVref_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_V2_S,			gSR_AF_post[gVref_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_V3_S,			gSR_AF_post[gVref_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_V4_S,			gSR_AF_post[gVref_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_V5_S,			gSR_AF_post[gVref_AF_Addr_Start + 4],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_V6_S,			gSR_AF_post[gVref_AF_Addr_Start + 5],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_IintTC1_S,	gSR_AF_post[gIintTC_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_IintTC2_S,	gSR_AF_post[gIintTC_AF_Addr_Start + 1],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_IintTC3_S,	gSR_AF_post[gIintTC_AF_Addr_Start + 2],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_IintTC4_S,	gSR_AF_post[gIintTC_AF_Addr_Start + 3],		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_DOPL_S,		gSR_AF_post[gDOPL_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_REQlow_S,		gSR_AF_post[gREQlow_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_XFWPK_S,		gSR_AF_post[gXFWPK_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Reg_LO_dis_S,		gSR_AF_post[gLO_dis_AF_Addr_Start],			set_fail_bin,	POWER_UNIT);

	if(gDEBUG)
	printf("Function Reg_S Done\n");
}
