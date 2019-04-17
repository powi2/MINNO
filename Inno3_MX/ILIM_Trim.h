//==============================================================================
// ILIM_Trim.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ILIM_Trim_user_init(test_function& func);

// ***********************************************************

void initialize_ILIM_Trim(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ILIM_Trim_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ILIM_Trim(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum ILIM_Trim{

	A_Func_Num_ILIM_Trim,
	A_gILIM_TARGET_S,
	//A_ILIM_target_adj_P,
	A_ILIM_code_P,
	A_ILIM_table_P,
	A_ILIM_needed_P,
	A_IZtr_L1_P,
	A_IZtr_L2_P,
	A_IZtr_L3_P,
	A_IZtr_L4_P,
	A_IZtr_ZF_P,

};