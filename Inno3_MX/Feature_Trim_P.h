//==============================================================================
// Feature_Trim_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Feature_Trim_P_user_init(test_function& func);

// ***********************************************************

void initialize_Feature_Trim_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Feature_Trim_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Feature_Trim_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Feature_Trim_P{

	A_Func_Num_Feature_Trim_P,
	A_Feature_Code_P,
	//A_IZtr_iov_Off_P,
	A_IZtr_iuvMinus_P,
	A_IZtr_uvDelay_P,
	A_IZtr_Loff_AR_P,
	A_IZtr_DisablAR_P,
	A_IZtr_didtComp_P,
	A_IZtr_OT_Hys_P,
	A_IZtr_LoffwOT_P,
	A_IZtr_iLselOff_P,
	A_IZtr_iLStdIcr_P,
	A_IZtr_iL20dn_P,
	A_IZtr_iL20up_P,
	A_IZtr_SAM_P,
	A_IZtr_OTP1_P,
	A_IZtr_OTP2_P,
	A_IZtr_OTP3_P,
	A_IZtr_VpinCtri_P,
	A_IZtr_SDS_OFF_P,
	A_IZtr_Rcv1_P,
	A_IZtr_Rcv2_P,
	A_IZtr_RcvSign_P,
	A_IZtr_drvSize1_P,
	A_IZtr_drvSize2_P,
	A_IZtr_drvSize3_P,
	A_IZtr_drvSize4_P,
	A_IZtr_RsenseUp_P,
	A_IZtr_vxAdj1_P,
	A_IZtr_vxAdj2_P,
	A_IZtr_vxAdj3_P,
	A_IZtr_vxAdj4_P,
	A_IZtr_vxAdj5_P,
	A_IZtr_iLRatio1_P,
	A_IZtr_iLRatio2_P,
	A_IZtr_iLRatio3_P,
	A_IZtr_iLRatio4_P,
	A_IZtr_iLTC1_P,
	A_IZtr_iLTC2_P,
	A_IZtr_iLTC3_P,
	A_IZtr_iLTC4_P,
	A_IZtr_AR_req_P,
};