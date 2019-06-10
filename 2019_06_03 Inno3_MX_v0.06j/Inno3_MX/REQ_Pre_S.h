//==============================================================================
// REQ_Pre_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void REQ_Pre_S_user_init(test_function& func);

// ***********************************************************

void initialize_REQ_Pre_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	REQ_Pre_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_REQ_Pre_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum REQ_Pre_S{

	A_Func_Num_REQ_Pre,
	A_REQqtrVref_M_pt_S,
	A_REQqtrVref_P_pt_S,
	A_REQqtrVref_HYS_pt_S,
	A_REQhalfVref_M_pt_S,
	A_REQhalfVref_P_pt_S,
	A_REQhalfVref_HYS_pt_S,
	A_REQ_Vref_M_pt_S,
	A_REQ_Vref_P_pt_S,
	A_REQ_Vref_HYS_pt_S,
	A_REQ_2Vref_M_pt_S,
	A_REQ_2Vref_P_pt_S,
	A_REQ_2Vref_HYS_pt_S,

};
