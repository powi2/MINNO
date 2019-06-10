//==============================================================================
// BV_FW.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void BV_FW_user_init(test_function& func);

// ***********************************************************

void initialize_BV_FW(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	BV_FW_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_BV_FW(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum BV_FW{
	A_Func_Num_BV_FW,
	A_BVD_FW_25UA,
	A_IDS_FW_25UA,
};