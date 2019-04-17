//==============================================================================
// Lekage.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Leakage_user_init(test_function& func);

// ***********************************************************

void initialize_Leakage(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Leakage_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Leakage(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum enum_Leakage{
	A_Func_Num_Leakage,
	A_ILL_D,
	A_ILH_D,
	A_ILL_BPP,
	A_ILH_BPP,
	A_ILL_UV,
	A_ILH_UV,
	A_ILL_FW,
	A_ILH_FW,
	A_ILL_VO,
	A_ILH_VO,
	A_ILL_SR,
	A_ILH_SR,
	A_ILL_BPS,
	A_ILH_BPS,
	A_ILL_REQ,
	A_ILH_REQ,
	A_ILL_FWC,
	A_ILH_FWC,
	A_ILL_ACK,
	A_ILH_ACK,
};