//==============================================================================
// IzPost.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IzPost_user_init(test_function& func);

// ***********************************************************

void initialize_IzPost(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IzPost_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IzPost(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IzPost{
	A_Func_Num_IzPost,
	//Primary
	A_IZ_iov1_p,
	A_IZ_iov2_p,
	A_IZ_iov3_p,
	A_IZ_iov4_p,
	A_IZ_iovSign_p,
	A_IZ_iL1_p,
	A_IZ_iL2_p,
	A_IZ_iL3_p,
	A_IZ_iLsign_p,
	A_IZ_tmax1_p,
	A_IZ_tmax2_p,
	A_IZ_tmaxSign_p,
	A_IZ_f1_p,
	A_IZ_f2_p,
	A_IZ_fSign_p,
	A_IZ_iov_Off_p,
	A_IZ_iuvMinus_p,
	A_IZ_uvDelay_p,
	A_IZ_Loff_AR_p,
	A_IZ_DisablAR_p,
	A_IZ_didtComp_p,
	A_IZ_OT_Hys_p,
	A_IZ_LoffwOT_p,
	A_IZ_iLselOff_p,
	A_IZ_iLStdIcr_p,
	A_IZ_iL20dn_p,
	A_IZ_iL20up_p,
	A_IZ_SAM_p,
	A_IZ_OTP1_p,
	A_IZ_OTP2_p,
	A_IZ_OTP3_p,
	A_IZ_VpinCtri_p,
	A_IZ_SDS_OFF_p,
	A_IZ_Rcv1_p,
	A_IZ_Rcv2_p,
	A_IZ_RcvSign_p,
	A_IZ_drvSize1_p,
	A_IZ_drvSize2_p,
	A_IZ_drvSize3_p,
	A_IZ_drvSize4_p,
	A_IZ_RsenseUp_p,
	A_IZ_vxAdj1_p,
	A_IZ_vxAdj2_p,
	A_IZ_vxAdj3_p,
	A_IZ_vxAdj4_p,
	A_IZ_vxAdj5_p,
	A_IZ_iLRatio1_p,
	A_IZ_iLRatio2_p,
	A_IZ_iLRatio3_p,
	A_IZ_iLRatio4_p,
	A_IZ_iLTC1_p,
	A_IZ_iLTC2_p,
	A_IZ_iLTC3_p,
	A_IZ_iLTC4_p,
	A_IZ_ARreq_p,
	A_IZ_ZF_p,

	//Secondary
	A_IZ_F1_S,
	A_IZ_F2_S,
	A_IZ_F3_S,
	A_IZ_F4_S,
	A_IZ_PK1spdLd_S,
	A_IZ_PK2_S,
	A_IZ_PK3_S,
	A_IZ_Rnw5_S,
	A_IZ_Rnw6_S,
	A_IZ_Rnw1_S,
	A_IZ_Rnw2_S,
	A_IZ_Rnw3_S,
	A_IZ_Rnw4_S,
	A_IZ_FWC2_S,
	A_IZ_NoFWC100mV_S,
	A_IZ_Cap1_S,
	A_IZ_Cap2_S,
	A_IZ_Cap3_S,
	A_IZ_PKdig1_S,
	A_IZ_PKdig2_S,
	A_IZ_PKdig3_S,
	A_IZ_PKdig4_S,
	A_IZ_SRth1_S,
	A_IZ_SRth2_S,
	A_IZ_SRth3_S,
	A_IZ_SRth4_S,
	A_IZ_V1_S,
	A_IZ_V2_S,
	A_IZ_V3_S,
	A_IZ_V4_S,
	A_IZ_V5_S,
	A_IZ_V6_S,
	A_IZ_IintTC1_S,
	A_IZ_IintTC2_S,
	A_IZ_IintTC3_S,
	A_IZ_IintTC4_S,
	A_IZ_DOPL_S,
	A_IZ_REQlow_S,
	A_IZ_XFWPK_S,
	A_FeatureT_Chk_p,
	A_FeatureT_Chk_s,
	A_IZ_Test_Escape,
};