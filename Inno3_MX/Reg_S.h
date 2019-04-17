//==============================================================================
// Reg_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Reg_S_user_init(test_function& func);

// ***********************************************************

void initialize_Reg_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Reg_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Reg_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Reg_S{		
	A_Func_Num_Reg_S	,
	A_Reg_F1_S	,
	A_Reg_F2_S	,
	A_Reg_F3_S	,
	A_Reg_F4_S	,
	A_Reg_PK1spdLd_S	,
	A_Reg_PK2_S	,
	A_Reg_PK3_S	,
	A_Reg_Rnw5_S	,
	A_Reg_Rnw6_S	,
	A_Reg_Rnw1_S	,
	A_Reg_Rnw2_S	,
	A_Reg_Rnw3_S	,
	A_Reg_Rnw4_S	,
	A_Reg_FWC2_S	,
	A_Reg_NoFWC100mV_S	,
	A_Reg_Cap1_S	,
	A_Reg_Cap2_S	,
	A_Reg_Cap3_S	,
	A_Reg_PKdig1_S	,
	A_Reg_PKdig2_S	,
	A_Reg_PKdig3_S	,
	A_Reg_PKdig4_S	,
	A_Reg_SRth1_S	,
	A_Reg_SRth2_S	,
	A_Reg_SRth3_S	,
	A_Reg_SRth4_S	,
	A_Reg_Vshunt_S	,
	A_Reg_V1_S	,
	A_Reg_V2_S	,
	A_Reg_V3_S	,
	A_Reg_V4_S	,
	A_Reg_V5_S	,
	A_Reg_V6_S	,
	A_Reg_IintTC1_S	,
	A_Reg_IintTC2_S	,
	A_Reg_IintTC3_S	,
	A_Reg_IintTC4_S	,
	A_Reg_DOPL_S	,
	A_Reg_REQlow_S	,
	A_Reg_XFWPK_S	,
	A_Reg_LO_dis_S	,
};
