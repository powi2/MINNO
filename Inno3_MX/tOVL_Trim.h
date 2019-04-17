//==============================================================================
// tOVL_Trim.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void tOVL_Trim_user_init(test_function& func);

// ***********************************************************

void initialize_tOVL_Trim(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	tOVL_Trim_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_tOVL_Trim(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum tOVL_Trim{

	A_Func_Num_tOVL_Trim,
	A_gtOVL_TARGET,
	A_tOVL_code,
	A_tOVL_table,
	A_tOVL_needed,
	A_IZtr_tOVL1,
	A_IZtr_tOVL2,
	A_IZtr_tOVLsign,

};