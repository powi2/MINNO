//==============================================================================
// FWPK.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void FWPK_user_init(test_function& func);

// ***********************************************************

void initialize_FWPK(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	FWPK_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_FWPK(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum FWPK
{
	A_Func_Num_FWPK,
	A_tDableOn_300kHz_S,
	A_tDableOn_1MHz_S,
	A_FWPK_Timer_S,
	A_FWPK_4Rings_S,
	A_DableOnHi4Ring_S,
	A_FWPK_tVOxDble_S,
	A_HS_Ring1V_FaultP_S,
	A_MaxF_FaultP_S,
	A_MinF_FaultP_S,
};