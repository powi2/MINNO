//==============================================================================
// Fosc_Trim_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Fosc_Trim_S_user_init(test_function& func);

// ***********************************************************

void initialize_Fosc_Trim_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Fosc_Trim_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Fosc_Trim_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Fosc_Trim_S{

	A_Func_Num_Fosc_Trim_S,
	A_gFOSC_TARGET_S,
	A_Fosc_code_S,
	A_Fosc_table_S,
	A_Fosc_needed_S,
	A_IZtr_F1_S,
	A_IZtr_F2_S,
	A_IZtr_F3_S,
	A_IZtr_F4_S,

};