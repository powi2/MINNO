//==============================================================================
// Fosc_Trim_P.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Fosc_Trim_P_user_init(test_function& func);

// ***********************************************************

void initialize_Fosc_Trim_P(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Fosc_Trim_P_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Fosc_Trim_P(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Fosc_Trim_P{

	A_Func_Num_Fosc_Trim_P,
	A_gFOSC_TARGET_P,
	A_Fosc_code_P,
	A_Fosc_table_P,
	A_Fosc_needed_P,
	A_IZtr_F1_P1_P,
	A_IZtr_F2_P2_P,
	A_IZtr_F3_M4_P,
};