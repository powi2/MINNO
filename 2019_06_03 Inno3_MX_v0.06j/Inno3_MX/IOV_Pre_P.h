//==============================================================================
// IOV_Pre_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IOV_Pre_P_user_init(test_function& func);

// ***********************************************************

void initialize_IOV_Pre_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IOV_Pre_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IOV_Pre_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IOV_pre_P
{
	A_Func_Num_IOV_Pre_P,
	A_iOV_plus_pre,
	A_CV_init_S,
	A_CV_init_ddd_lo,
	A_CV_init_ddd_hi
};