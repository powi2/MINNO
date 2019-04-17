//==============================================================================
// Iz_xChk_Reg_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Iz_xChk_Reg_S_user_init(test_function& func);

// ***********************************************************

void initialize_Iz_xChk_Reg_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Iz_xChk_Reg_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Iz_xChk_Reg_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Iz_xChk_Reg_S{
	A_Func_Num_Iz_xChk_Reg_S,
};