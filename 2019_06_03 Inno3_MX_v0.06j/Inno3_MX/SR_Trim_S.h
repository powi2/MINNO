//==============================================================================
// SR_Trim_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void SR_Trim_S_user_init(test_function& func);

// ***********************************************************

void initialize_SR_Trim_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	SR_Trim_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_SR_Trim_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum SR_Trim_S{

	A_Func_Num_SR_Trim_S,
	A_gSR_TARGET_S,
	A_SR_code_S,
	A_SR_table_S,
	A_SR_needed_S,
	A_IZtr_SR1_S,
	A_IZtr_SR2_S,
	A_IZtr_SR3_S,
	A_IZtr_SR4_S,

};
