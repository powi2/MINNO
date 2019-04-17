//==============================================================================
// DATT.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void DATT_user_init(test_function& func);

// ***********************************************************

void initialize_DATT(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	DATT_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_DATT(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum DATT{
	A_Func_Num_DATT,
	A_DATT_VD_BEF,
	A_DATT_VD_AFT,
	A_DATT_DIFF,
	A_DATT_NORM,
	A_DATT_POWER,
};