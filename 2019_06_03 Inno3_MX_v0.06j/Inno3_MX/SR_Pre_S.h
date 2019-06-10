//==============================================================================
// SR_Pre_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void SR_Pre_S_user_init(test_function& func);

// ***********************************************************

void initialize_SR_Pre_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	SR_Pre_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_SR_Pre_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum SR_Pre{

	A_Func_Num_SR_Pre,
	A_SRth_pt_S,

};
