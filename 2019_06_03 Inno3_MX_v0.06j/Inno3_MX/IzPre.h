//==============================================================================
// IzPre.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IzPre_user_init(test_function& func);

// ***********************************************************

void initialize_IzPre(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IzPre_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IzPre(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum enum_IzPre{
	A_Func_Num_IZpre,
	//Primary
	A_Izpt_iov1_p,
	A_Izpt_iov2_p,
	A_Izpt_iov3_p,
	A_Izpt_iov4_p,
	A_Izpt_iovSign_p,
	A_Izpt_iL1_p,
	A_Izpt_iL2_p,
	A_Izpt_iL3_p,
	A_Izpt_iLsign_p,
	A_Izpt_tOVL1_p,
	A_Izpt_tOVL2_p,
	A_Izpt_tOVLSign_p,
	A_Izpt_f1_p,
	A_Izpt_f2_p,
	A_Izpt_fSign_p,
	A_Izpt_iov_Off_p,
	A_Izpt_iuvMinus_p,
	A_Izpt_uvDelay_p,
	A_Izpt_Loff_AR_p,
	A_Izpt_DisablAR_p,
	A_Izpt_didtComp_p,
	A_Izpt_OT_Hys_p,
	A_Izpt_LoffwOT_p,
	A_Izpt_iLselOff_p,
	A_Izpt_iLStdIcr_p,
	A_Izpt_iL20dn_p,
	A_Izpt_iL20up_p,
	A_Izpt_SAM_p,
	A_Izpt_OTP1_p,
	A_Izpt_OTP2_p,
	A_Izpt_OTP3_p,
	A_Izpt_VpinCtri_p,
	A_Izpt_SDS_OFF_p,
	A_Izpt_ZVSTSel1_p,		// GaN
	A_Izpt_ZVSTSel2_p,		// GaN
	A_Izpt_ZVSTtr1_p,		// GaN
	A_Izpt_ZVSTtr2_p,		// GaN
	A_Izpt_Rcv1_p,
	A_Izpt_Rcv2_p,
	A_Izpt_RcvSign_p,
	A_Izpt_drvSize1_p,
	A_Izpt_drvSize2_p,
	A_Izpt_drvSize3_p,
	A_Izpt_drvSize4_p,
	A_Izpt_RsenseUp_p,
	A_Izpt_vxAdj1_p,
	A_Izpt_vxAdj2_p,
	A_Izpt_vxAdj3_p,
	A_Izpt_vxAdj4_p,
	A_Izpt_vxAdj5_p,
	A_Izpt_ZVSon_p,			// GaN
	A_Izpt_UV1_p,			// GaN
	A_Izpt_UV2_p,			// GaN
	A_Izpt_ZVSdlm20_p,		// GaN
	A_Izpt_IlimLEB_p,		// GaN
	A_Izpt_vpinIref_p,		// GaN
	A_Izpt_ZVSDly1_p,		// GaN
	A_Izpt_ZVSDly2_p,		// GaN
	A_Izpt_ZVSDly3_p,		// GaN
	A_Izpt_ZVSDly14_p,		// GaN
	A_Izpt_SDS30pct_p,		// GaN
	A_Izpt_SDS60pct_p,		// GaN
	A_Izpt_iLRatio1_p,
	A_Izpt_iLRatio2_p,
	A_Izpt_iLRatio3_p,
	A_Izpt_iLRatio4_p,
	A_Izpt_iLTC1_p,
	A_Izpt_iLTC2_p,
	A_Izpt_iLTC3_p,
	A_Izpt_iLTC4_p,
	A_Izpt_ARreq_p,
	A_Izpt_ZF_p,

	//Secondary
	A_Izpt_NoZ_s,
	A_Izpt_F1_s,
	A_Izpt_F2_s,
	A_Izpt_F3_s,
	A_Izpt_F4_s,
	A_Izpt_PKspdLd_s,
	A_Izpt_PK2_s,
	A_Izpt_PK3_s,
	A_Izpt_Rnw5_s,
	A_Izpt_Rnw6_s,
	A_Izpt_Rnw1_s,
	A_Izpt_Rnw2_s,
	A_Izpt_Rnw3_s,
	A_Izpt_Rnw4_s,
	A_Izpt_FWC2_s,
	A_Izpt_NoFWC_s,
	A_Izpt_Cap1_s,
	A_Izpt_Cap2_s,
	A_Izpt_Cap3_s,
	A_Izpt_PKdig1_s,
	A_Izpt_PKdig2_s,
	A_Izpt_PKdig3_s,
	A_Izpt_PKdig4_s,
	A_Izpt_SRth1_s,
	A_Izpt_SRth2_s,
	A_Izpt_SRth3_s,
	A_Izpt_SRth4_s,
	A_Izpt_Vshunt_s,
	A_Izpt_V1_s,
	A_Izpt_V2_s,
	A_Izpt_V3_s,
	A_Izpt_V4_s,
	A_Izpt_V5_s,
	A_Izpt_V6_s,
	A_Izpt_IintTC1_s,
	A_Izpt_IintTC2_s,
	A_Izpt_IintTC3_s,
	A_Izpt_IintTC4_s,
	A_Izpt_DOPL_s,
	A_Izpt_REQlow_s,
	A_Izpt_XFWPK_s,
	A_Izpt_LO_dis_s,

	A_Izpt_Trimmed,
	A_Izpt_Iplus_p,
	A_Izpt_ID0_p,
	A_Izpt_ID1_p,
	A_Izpt_SiRev3_s,
	A_Izpt_SiRev2_s,
	A_Izpt_SiRev1_s,
	A_Izpt_FabID2_s,
	A_Izpt_FabID1_s,
	A_SiOption_p, 
	A_SiOption_s,
	A_Izpt_Sil_Match_p,
	A_Izpt_Sil_Match_s,
};
