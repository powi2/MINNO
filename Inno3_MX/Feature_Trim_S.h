//==============================================================================
// Feature_Trim_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Feature_Trim_S_user_init(test_function& func);

// ***********************************************************

void initialize_Feature_Trim_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Feature_Trim_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Feature_Trim_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Feature_Trim_S{
	A_Func_Num_Feature_Trim_S,
	A_Feature_Code_S,
	A_IZtr_PK1spdLd_S,
	A_IZtr_PK2_S,
	A_IZtr_PK3_S,
	A_IZtr_Rnw5_S,
	A_IZtr_Rnw6_S,
	A_IZtr_Rnw1_S,
	A_IZtr_Rnw2_S,
	A_IZtr_Rnw3_S,
	A_IZtr_Rnw4_S,
	A_IZtr_FWC2_S,
	A_IZtr_NoFWC100mV_S,
	A_IZtr_Cap1_S,
	A_IZtr_Cap2_S,
	A_IZtr_Cap3_S,
	A_IZtr_PKdig1_S,
	A_IZtr_PKdig2_S,
	A_IZtr_PKdig3_S,
	A_IZtr_PKdig4_S,
	A_IZtr_Vshunt_S,
	A_IZtr_IintTC1_S,
	A_IZtr_IintTC2_S,
	A_IZtr_IintTC3_S,
	A_IZtr_IintTC4_S,
	A_IZtr_DOPL_S,
	A_IZtr_REQlow_S,
	A_IZtr_XFWPK_S,
	A_IZtr_LO_dis_S,
};