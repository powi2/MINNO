//==============================================================================
// IOV_post_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IOV_post_P_user_init(test_function& func);

// ***********************************************************

void initialize_IOV_post_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IOV_post_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IOV_post_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IOV_post_P
{
	A_Func_Num_IOV_post_P,
	A_iOV_plus_post,
	A_iOV_P_err_P,
	A_iOV_P_P_gng
};