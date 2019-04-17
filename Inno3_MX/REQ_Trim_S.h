//==============================================================================
// REQ_Trim_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void REQ_Trim_S_user_init(test_function& func);

// ***********************************************************

void initialize_REQ_Trim_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	REQ_Trim_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_REQ_Trim_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum REQ_Trim_S{

	A_Func_Num_REQ_Trim_S,
	A_gVref_TARGET_S,
	A_REQ_code_S,
	A_REQ_table_S,
	A_REQ_needed_S,
	A_IZtr_V1_S,
	A_IZtr_V2_S,
	A_IZtr_V3_S,
	A_IZtr_V4_S,
	A_IZtr_V5_S,
	A_IZtr_V6_S,

};
