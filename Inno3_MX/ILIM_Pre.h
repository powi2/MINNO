//==============================================================================
// ILIM_Pre.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ILIM_Pre_user_init(test_function& func);

// ***********************************************************

void initialize_ILIM_Pre(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ILIM_Pre_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ILIM_Pre(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum ILIM_Pre{

	A_Func_Num_ILIM_Pre,
	A_ILIM_Pt_P,
	A_ILIM_Pt_didt_P,
	A_ILIM_Pt_ton_P,
	A_ILIM_I2f_pt_P,


};