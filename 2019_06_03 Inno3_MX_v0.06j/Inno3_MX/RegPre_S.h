//==============================================================================
// RegPre_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void RegPre_S_user_init(test_function& func);

// ***********************************************************

void initialize_RegPre_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	RegPre_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_RegPre_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum RegPre_S{		
	A_Func_Num_RegPre_S	,
	A_RegPt_F1_S	,
	A_RegPt_F2_S	,
	A_RegPt_F3_S	,
	A_RegPt_F4_S	,
	A_RegPt_PK1spdLd_S	,
	A_RegPt_PK2_S	,
	A_RegPt_PK3_S	,
	A_RegPt_Rnw5_S	,
	A_RegPt_Rnw6_S	,
	A_RegPt_Rnw1_S	,
	A_RegPt_Rnw2_S	,
	A_RegPt_Rnw3_S	,
	A_RegPt_Rnw4_S	,
	A_RegPt_FWC2_S	,
	A_RegPt_NoFWC100mV_S	,
	A_RegPt_Cap1_S	,
	A_RegPt_Cap2_S	,
	A_RegPt_Cap3_S	,
	A_RegPt_PKdig1_S	,
	A_RegPt_PKdig2_S	,
	A_RegPt_PKdig3_S	,
	A_RegPt_PKdig4_S	,
	A_RegPt_SRth1_S	,
	A_RegPt_SRth2_S	,
	A_RegPt_SRth3_S	,
	A_RegPt_SRth4_S	,
	A_RegPt_Vshunt_S	,
	A_RegPt_V1_S	,
	A_RegPt_V2_S	,
	A_RegPt_V3_S	,
	A_RegPt_V4_S	,
	A_RegPt_V5_S	,
	A_RegPt_V6_S	,
	A_RegPt_IintTC1_S	,
	A_RegPt_IintTC2_S	,
	A_RegPt_IintTC3_S	,
	A_RegPt_IintTC4_S	,
	A_RegPt_DOPL_S	,
	A_RegPt_REQlow_S	,
	A_RegPt_XFWPK_S	,
	A_RegPt_LO_dis_S	,
};
