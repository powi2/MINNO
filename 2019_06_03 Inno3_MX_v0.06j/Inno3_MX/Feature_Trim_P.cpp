//==============================================================================
// Feature_Trim_P.cpp (User function)
// 
//    void Feature_Trim_P_user_init(test_function& func)
//    void Feature_Trim_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "Feature_Trim_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Feature_Trim_P_user_init(test_function& func)
{
	Feature_Trim_P_params *ours;
    ours = (Feature_Trim_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Feature_Trim_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Feature_Trim_P_params *ours;
    ours = (Feature_Trim_P_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 11;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	Func_name = "Fosc_Trim_P";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Feature_Trim_P,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if(ours->force_code == -99)							//REMARK AT PRODUCTION
	{													//REMARK AT PRODUCTION
		if (OPCODE != 4200 || TRIM_ENABLE == 0)
			return;
	}													//REMARK AT PRODUCTION

	double	Feature_Code_P		= 0;
	float	IZtr_P[100]			= {};
	bool	Trim_P[100]			= {};
	int		A_IZtr_P[100]		= {};

	int previous_addr = 0, trim_addr = 0, clks = 0;

	for (int i = 0; i < 100; i++)
	{
		IZtr_P[i]	= -999.0;
		Trim_P[i]	= false;
		A_IZtr_P[i]	= 3;
	}

	if (gGaN)
	{
		//Individual Feature Bits
		Trim_P[gP_AF_Start_Addr_IuvIov_Disable]			= gTrim_iov_Off_P;
		Trim_P[gP_AF_Start_Addr_Iuv_10uA]				= gTrim_iuvMinus_P;
		Trim_P[gP_AF_Start_Addr_UV_400ms_dly]			= gTrim_uvDelay_P;
		Trim_P[gP_AF_Start_Addr_LatchOFF_aft_AR]		= gTrim_Loff_AR_P;
		Trim_P[gP_AF_Start_Addr_LatchOFF_w_OT]			= gTrim_LoffwOT_P;
		Trim_P[gP_AF_Start_Addr_Disable_ILIM_Select]	= gTrim_iLselOff_P;
		Trim_P[gP_AF_Start_Addr_Select_ILIM_Incr]		= gTrim_iLStdIcr_P;
		Trim_P[gP_AF_Start_Addr_OT_Hys_30C]				= gTrim_OT_Hys_P;
		Trim_P[gP_AF_Start_Addr_Disable_AR]				= gTrim_DisablAR_P;
		Trim_P[gP_AF_Start_Addr_Samsung_Mode]			= gTrim_SAM_P;
		Trim_P[gP_AF_Start_Addr_ZVSon]					= gTrim_ZVSon_p;
		Trim_P[gP_AF_Start_Addr_UV]						= gTrim_UV1_P;
		Trim_P[gP_AF_Start_Addr_UV + 1]					= gTrim_UV2_P;
		Trim_P[gP_AF_Start_Addr_ZVSdelaym20]			= gTrim_ZVSdlym20_P;
		Trim_P[gP_AF_Start_Addr_IlimLEB]				= gTrim_IlimLEB_P;
		Trim_P[gP_AF_Start_Addr_VpinCTRL_iREF20pct]		= gTrim_VpinIref20pct_P;
		Trim_P[gP_AF_Start_Addr_SDSpct]					= gTrim_SDS30pct_P;
		Trim_P[gP_AF_Start_Addr_SDSpct + 1]				= gTrim_SDS60pct_P;
		Trim_P[gP_AF_Start_Addr_AR_Request]				= gTrim_AR_req_P;

		//Determine OTP trim bits,			3 bits
		if((gTrim_OTP_P & 1) == 1)			Trim_P[gP_AF_Start_Addr_OTP]			= true;
		if((gTrim_OTP_P & 2) == 2)			Trim_P[gP_AF_Start_Addr_OTP + 1]		= true;
		if((gTrim_OTP_P & 4) == 4)			Trim_P[gP_AF_Start_Addr_OTP + 2]		= true;
		//Determine ZVS Ton Sel trim bits,	2 bits
		if((gTrim_ZVS_Ton_sel_P & 1) == 1)	Trim_P[gP_AF_Start_Addr_ZVS_Ton]		= true;
		if((gTrim_ZVS_Ton_sel_P & 2) == 2)	Trim_P[gP_AF_Start_Addr_ZVS_Ton + 1]	= true;
		//Determine ZVS_Ton Trim trim bits,	2 bits
		if((gTrim_ZVS_Ton_Trm_P & 1) == 1)	Trim_P[gP_AF_Start_Addr_ZVS_Trim]		= true;
		if((gTrim_ZVS_Ton_Trm_P & 2) == 2)	Trim_P[gP_AF_Start_Addr_ZVS_Trim + 1]	= true;
		//Determine Rcv trim bits,			3 bits
		if((gTrim_Rcv_P & 1) == 1)			Trim_P[gP_AF_Start_Addr_Rcv]			= true;
		if((gTrim_Rcv_P & 2) == 2)			Trim_P[gP_AF_Start_Addr_Rcv + 1]		= true;
		if((gTrim_Rcv_P & 4) == 4)			Trim_P[gP_AF_Start_Addr_Rcv + 2]		= true;
		//Determine ZVS delay trim bits,	4 bits
		if((gTrim_ZVS_dly_P & 1) == 1)		Trim_P[gP_AF_Start_Addr_ZVS_Delay]		= true;
		if((gTrim_ZVS_dly_P & 2) == 2)		Trim_P[gP_AF_Start_Addr_ZVS_Delay + 1]	= true;
		if((gTrim_ZVS_dly_P & 4) == 4)		Trim_P[gP_AF_Start_Addr_ZVS_Delay + 2]	= true;
		if((gTrim_ZVS_dly_P & 8) == 8)		Trim_P[gP_AF_Start_Addr_ZVS_Delay + 3]	= true;
		//Determine ILIM Ratio trim bits,	2 bits
		if((gTrim_iLRatio_P & 1) == 1)		Trim_P[gP_AF_Start_Addr_ILIM_Ratio]		= true;
		if((gTrim_iLRatio_P & 2) == 2)		Trim_P[gP_AF_Start_Addr_ILIM_Ratio + 1]	= true;
		//Determine ILIM TC trim bits,		4 bits
		if((gTrim_iLTC_P & 1) == 1)			Trim_P[gP_AF_Start_Addr_ILIM_TC]		= true;
		if((gTrim_iLTC_P & 2) == 2)			Trim_P[gP_AF_Start_Addr_ILIM_TC + 1]	= true;
		if((gTrim_iLTC_P & 4) == 4)			Trim_P[gP_AF_Start_Addr_ILIM_TC + 2]	= true;
		if((gTrim_iLTC_P & 8) == 8)			Trim_P[gP_AF_Start_Addr_ILIM_TC + 3]	= true;

		//Map to VATE subtest number
		A_IZtr_P[gP_AF_Start_Addr_IuvIov_Disable]		= 	A_IZtr_iov_Off_P;
		A_IZtr_P[gP_AF_Start_Addr_Iuv_10uA]				= 	A_IZtr_iuvMinus_P;
		A_IZtr_P[gP_AF_Start_Addr_UV_400ms_dly]			= 	A_IZtr_uvDelay_P;
		A_IZtr_P[gP_AF_Start_Addr_LatchOFF_aft_AR]		= 	A_IZtr_Loff_AR_P;
		A_IZtr_P[gP_AF_Start_Addr_OTP]					= 	A_IZtr_OTP1_P;
		A_IZtr_P[gP_AF_Start_Addr_OTP + 1]				= 	A_IZtr_OTP2_P;
		A_IZtr_P[gP_AF_Start_Addr_OTP + 2]				= 	A_IZtr_OTP3_P;
		A_IZtr_P[gP_AF_Start_Addr_LatchOFF_w_OT]		= 	A_IZtr_LoffwOT_P;
		A_IZtr_P[gP_AF_Start_Addr_Disable_ILIM_Select]	= 	A_IZtr_iLselOff_P;
		A_IZtr_P[gP_AF_Start_Addr_Select_ILIM_Incr]		= 	A_IZtr_iLStdIcr_P;
		A_IZtr_P[gP_AF_Start_Addr_OT_Hys_30C]			= 	A_IZtr_OT_Hys_P;
		A_IZtr_P[gP_AF_Start_Addr_Disable_AR]			= 	A_IZtr_DisablAR_P;
		A_IZtr_P[gP_AF_Start_Addr_Samsung_Mode]			= 	A_IZtr_SAM_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVS_Ton]				= 	A_IZtr_ZvsTonSel1_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVS_Ton + 1]			= 	A_IZtr_ZvsTonSel2_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVS_Trim]				= 	A_IZtr_ZvsTonTrm1_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVS_Trim + 1]			= 	A_IZtr_ZvsTonTrm2_P;
		A_IZtr_P[gP_AF_Start_Addr_Rcv]					= 	A_IZtr_Rcv1_P;
		A_IZtr_P[gP_AF_Start_Addr_Rcv + 1]				= 	A_IZtr_Rcv2_P;
		A_IZtr_P[gP_AF_Start_Addr_Rcv + 2]				= 	A_IZtr_RcvSign_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVSon]				= 	A_IZtr_ZVSon_p;
		A_IZtr_P[gP_AF_Start_Addr_UV]					= 	A_IZtr_UV1_P;
		A_IZtr_P[gP_AF_Start_Addr_UV + 1]				= 	A_IZtr_UV2_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVSdelaym20]			= 	A_IZtr_ZVSdlym20_p;
		A_IZtr_P[gP_AF_Start_Addr_IlimLEB]				= 	A_IZtr_IlimLEB_P;
		A_IZtr_P[gP_AF_Start_Addr_VpinCTRL_iREF20pct]	= 	A_IZtr_Vpin_ctrl_iREF_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVS_Delay]			= 	A_IZtr_ZVS_dly1_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVS_Delay + 1]		= 	A_IZtr_ZVS_dly2_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVS_Delay + 2]		= 	A_IZtr_ZVS_dly3_P;
		A_IZtr_P[gP_AF_Start_Addr_ZVS_Delay + 3]		= 	A_IZtr_ZVS_dly4_P;
		A_IZtr_P[gP_AF_Start_Addr_SDSpct]				= 	A_IZtr_SDS_30pct_P;
		A_IZtr_P[gP_AF_Start_Addr_SDSpct + 1]			= 	A_IZtr_SDS_60pct_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_Ratio]			= 	A_IZtr_iLRatio1_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_Ratio + 1]		= 	A_IZtr_iLRatio2_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_TC]				= 	A_IZtr_iLTC1_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_TC + 1]			= 	A_IZtr_iLTC2_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_TC + 2]			= 	A_IZtr_iLTC3_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_TC + 3]			= 	A_IZtr_iLTC4_P;
		A_IZtr_P[gP_AF_Start_Addr_AR_Request]			= 	A_IZtr_AR_req_P;

	}
	else
	{
		//Individual Feature Bits
		Trim_P[gP_AF_Start_Addr_IuvIov_Disable]			= gTrim_iov_Off_P;
		Trim_P[gP_AF_Start_Addr_Iuv_10uA]				= gTrim_iuvMinus_P;
		Trim_P[gP_AF_Start_Addr_UV_400ms_dly]			= gTrim_uvDelay_P;
		Trim_P[gP_AF_Start_Addr_LatchOFF_aft_AR]		= gTrim_Loff_AR_P;
		Trim_P[gP_AF_Start_Addr_Disable_AR]				= gTrim_DisablAR_P;
		Trim_P[gP_AF_Start_Addr_didt_comp]				= gTrim_didtComp_P;
		Trim_P[gP_AF_Start_Addr_OT_Hys_30C]				= gTrim_OT_Hys_P;
		Trim_P[gP_AF_Start_Addr_LatchOFF_w_OT]			= gTrim_LoffwOT_P;
		Trim_P[gP_AF_Start_Addr_Disable_ILIM_Select]	= gTrim_iLselOff_P;
		Trim_P[gP_AF_Start_Addr_Select_ILIM_Incr]		= gTrim_iLStdIcr_P;
		Trim_P[gP_AF_Start_Addr_minus_20pct_ILIM]		= gTrim_iL20dn_P;
		Trim_P[gP_AF_Start_Addr_plus_20pct_ILIM]		= gTrim_iL20up_P;
		Trim_P[gP_AF_Start_Addr_Samsung_Mode]			= gTrim_SAM_P;
		Trim_P[gP_AF_Start_Addr_SDS_OFF]				= gTrim_SDS_OFF_P;
		Trim_P[gP_AF_Start_Addr_Rsense_up]				= gTrim_RsenseUp_P;
		Trim_P[gP_AF_Start_Addr_AR_Request]				= gTrim_AR_req_P;

		//Determine OTP trim bits,			3 bits
		if((gTrim_OTP_P & 1) == 1)			Trim_P[gP_AF_Start_Addr_OTP]				= true;
		if((gTrim_OTP_P & 2) == 2)			Trim_P[gP_AF_Start_Addr_OTP + 1]			= true;
		if((gTrim_OTP_P & 4) == 4)			Trim_P[gP_AF_Start_Addr_OTP + 2]			= true;
		//Determine Rcv trim bits,			3 bits
		if((gTrim_Rcv_P & 1) == 1)			Trim_P[gP_AF_Start_Addr_Rcv]				= true;
		if((gTrim_Rcv_P & 2) == 2)			Trim_P[gP_AF_Start_Addr_Rcv + 1]			= true;
		if((gTrim_Rcv_P & 4) == 4)			Trim_P[gP_AF_Start_Addr_Rcv + 2]			= true;
		//Determine Driver Size trim bits,	4 bits
		if((gTrim_drvSize_P & 1) == 1)		Trim_P[gP_AF_Start_Addr_Driver_Size]		= true;
		if((gTrim_drvSize_P & 2) == 2)		Trim_P[gP_AF_Start_Addr_Driver_Size + 1]	= true;
		if((gTrim_drvSize_P & 4) == 4)		Trim_P[gP_AF_Start_Addr_Driver_Size + 2]	= true;
		if((gTrim_drvSize_P & 8) == 8)		Trim_P[gP_AF_Start_Addr_Driver_Size + 3]	= true;
		//Determine vxAdj trim bits,		5 bits
		if((gTrim_vxAdj_P & 1) == 1)		Trim_P[gP_AF_Start_Addr_Vx_adjust]			= true;
		if((gTrim_vxAdj_P & 2) == 2)		Trim_P[gP_AF_Start_Addr_Vx_adjust + 1]		= true;
		if((gTrim_vxAdj_P & 4) == 4)		Trim_P[gP_AF_Start_Addr_Vx_adjust + 2]		= true;
		if((gTrim_vxAdj_P & 8) == 8)		Trim_P[gP_AF_Start_Addr_Vx_adjust + 3]		= true;
		if((gTrim_vxAdj_P & 16) == 16)		Trim_P[gP_AF_Start_Addr_Vx_adjust + 4]		= true;
		//Determine ILIM Ratio trim bits,	4 bits
		if((gTrim_iLRatio_P & 1) == 1)		Trim_P[gP_AF_Start_Addr_ILIM_Ratio]			= true;
		if((gTrim_iLRatio_P & 2) == 2)		Trim_P[gP_AF_Start_Addr_ILIM_Ratio + 1]		= true;
		if((gTrim_iLRatio_P & 4) == 4)		Trim_P[gP_AF_Start_Addr_ILIM_Ratio + 2]		= true;
		if((gTrim_iLRatio_P & 8) == 8)		Trim_P[gP_AF_Start_Addr_ILIM_Ratio + 3]		= true;
		//Determine ILIM TC trim bits,		4 bits
		if((gTrim_iLTC_P & 1) == 1)			Trim_P[gP_AF_Start_Addr_ILIM_TC]			= true;
		if((gTrim_iLTC_P & 2) == 2)			Trim_P[gP_AF_Start_Addr_ILIM_TC + 1]		= true;
		if((gTrim_iLTC_P & 4) == 4)			Trim_P[gP_AF_Start_Addr_ILIM_TC + 2]		= true;
		if((gTrim_iLTC_P & 8) == 8)			Trim_P[gP_AF_Start_Addr_ILIM_TC + 3]		= true;

		//Map to VATE subtest number
		A_IZtr_P[gP_AF_Start_Addr_IuvIov_Disable]		= 	A_IZtr_iov_Off_P;
		A_IZtr_P[gP_AF_Start_Addr_Iuv_10uA]				= 	A_IZtr_iuvMinus_P;
		A_IZtr_P[gP_AF_Start_Addr_UV_400ms_dly]			= 	A_IZtr_uvDelay_P;
		A_IZtr_P[gP_AF_Start_Addr_LatchOFF_aft_AR]		= 	A_IZtr_Loff_AR_P;
		A_IZtr_P[gP_AF_Start_Addr_Disable_AR]			= 	A_IZtr_DisablAR_P;
		A_IZtr_P[gP_AF_Start_Addr_didt_comp]			= 	A_IZtr_didtComp_P;
		A_IZtr_P[gP_AF_Start_Addr_OT_Hys_30C]			= 	A_IZtr_OT_Hys_P;
		A_IZtr_P[gP_AF_Start_Addr_LatchOFF_w_OT]		= 	A_IZtr_LoffwOT_P;
		A_IZtr_P[gP_AF_Start_Addr_Disable_ILIM_Select]	= 	A_IZtr_iLselOff_P;
		A_IZtr_P[gP_AF_Start_Addr_Select_ILIM_Incr]		= 	A_IZtr_iLStdIcr_P;
		A_IZtr_P[gP_AF_Start_Addr_minus_20pct_ILIM]		= 	A_IZtr_iL20dn_P;
		A_IZtr_P[gP_AF_Start_Addr_plus_20pct_ILIM]		= 	A_IZtr_iL20up_P;
		A_IZtr_P[gP_AF_Start_Addr_Samsung_Mode]			= 	A_IZtr_SAM_P;
		A_IZtr_P[gP_AF_Start_Addr_OTP]					= 	A_IZtr_OTP1_P;
		A_IZtr_P[gP_AF_Start_Addr_OTP + 1]				= 	A_IZtr_OTP2_P;
		A_IZtr_P[gP_AF_Start_Addr_OTP + 2]				= 	A_IZtr_OTP3_P;
		A_IZtr_P[gP_AF_Start_Addr_SDS_OFF]				= 	A_IZtr_SDS_OFF_P;
		A_IZtr_P[gP_AF_Start_Addr_Rcv]					= 	A_IZtr_Rcv1_P;
		A_IZtr_P[gP_AF_Start_Addr_Rcv + 1]				= 	A_IZtr_Rcv2_P;
		A_IZtr_P[gP_AF_Start_Addr_Rcv + 2]				= 	A_IZtr_RcvSign_P;
		A_IZtr_P[gP_AF_Start_Addr_Driver_Size]			= 	A_IZtr_drvSize1_P;
		A_IZtr_P[gP_AF_Start_Addr_Driver_Size + 1]		= 	A_IZtr_drvSize2_P;
		A_IZtr_P[gP_AF_Start_Addr_Driver_Size + 2]		= 	A_IZtr_drvSize3_P;
		A_IZtr_P[gP_AF_Start_Addr_Driver_Size + 3]		= 	A_IZtr_drvSize4_P;
		A_IZtr_P[gP_AF_Start_Addr_Rsense_up]			= 	A_IZtr_RsenseUp_P;
		A_IZtr_P[gP_AF_Start_Addr_Vx_adjust]			= 	A_IZtr_vxAdj1_P;
		A_IZtr_P[gP_AF_Start_Addr_Vx_adjust + 1]		= 	A_IZtr_vxAdj2_P;
		A_IZtr_P[gP_AF_Start_Addr_Vx_adjust + 2]		= 	A_IZtr_vxAdj3_P;
		A_IZtr_P[gP_AF_Start_Addr_Vx_adjust + 3]		= 	A_IZtr_vxAdj4_P;
		A_IZtr_P[gP_AF_Start_Addr_Vx_adjust + 4]		= 	A_IZtr_vxAdj5_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_Ratio]			= 	A_IZtr_iLRatio1_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_Ratio + 1]		= 	A_IZtr_iLRatio2_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_Ratio + 2]		= 	A_IZtr_iLRatio3_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_Ratio + 3]		= 	A_IZtr_iLRatio4_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_TC]				= 	A_IZtr_iLTC1_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_TC + 1]			= 	A_IZtr_iLTC2_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_TC + 2]			= 	A_IZtr_iLTC3_P;
		A_IZtr_P[gP_AF_Start_Addr_ILIM_TC + 3]			= 	A_IZtr_iLTC4_P;
		A_IZtr_P[gP_AF_Start_Addr_AR_Request]			= 	A_IZtr_AR_req_P;
	}

	//Trim Features for Primary (See OTS/TestPlan)
	Powerup_to_trim_primary();

	previous_addr =0;
	trim_addr     =0;

	//Forced trim: Clock through Primary and trim anti-fuses
	if(ours->force_code != -99)
	{
		if(ours->force_code != 0)
		{
			trim_addr = ours->force_code;
			clks = trim_addr - previous_addr;
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary(&IZtr_P[trim_addr]);
			previous_addr =  trim_addr;

			// Datalog
			PiDatalog(func,		A_IZtr_P[trim_addr],	IZtr_P[trim_addr],	set_fail_bin,	POWER_MILLI);
		}

		// Power down from trim
		Powerdown_from_trim_primary();
		VPIN_ovi->set_voltage(VPIN_ch,	0.0, 		RANGE_2_V);	// OVI_1_1
		REQ_ovi->set_voltage(REQ_ch,	0.0, 		RANGE_2_V);	// OVI_1_2
		return;
	}

	//Feature Bits trimmed
	for (trim_addr = 1; trim_addr <= gTotal_Addr_Count_P; trim_addr++)
	{
		if (Trim_P[trim_addr])
		{
			clks = trim_addr - previous_addr;
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary(&IZtr_P[trim_addr]);
			PiDatalog(func,		A_IZtr_P[trim_addr],	IZtr_P[trim_addr],	set_fail_bin,	POWER_MILLI);
			previous_addr =  trim_addr;
		}
	}

	// Power down from trim
	Powerdown_from_trim_primary();
	VPIN_ovi->set_voltage(VPIN_ch,	0.0, 		RANGE_2_V);	// OVI_1_1
	REQ_ovi->set_voltage(REQ_ch,	0.0, 		RANGE_2_V);	// OVI_1_2

	if (gDEBUG)
	printf("Function Feature_Trim_P Done\n");
}
