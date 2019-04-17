//==============================================================================
// IOV_Trim.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IOV_Trim_user_init(test_function& func);

// ***********************************************************

void initialize_IOV_Trim(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IOV_Trim_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IOV_Trim(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IOV_Trim
{
	A_Func_Num_IOV_Trim,
	A_giOV_plus_TARGET,
	A_iOV_plus_code_P,
	A_iOV_plus_table_P,
	A_iOV_plus_needed_P,
	A_IZtr_IOV1_P,
	A_IZtr_IOV2_P,
	A_IZtr_IOV3_P,
	A_IZtr_IOV4_P,
	A_IZtr_IOV5_P,
	A_IZtr_iov_Off_P,

};