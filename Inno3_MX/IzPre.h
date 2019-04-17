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
	A_Izpt_tmax1_p,
	A_Izpt_tmax2_p,
	A_Izpt_tmaxSign_p,
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