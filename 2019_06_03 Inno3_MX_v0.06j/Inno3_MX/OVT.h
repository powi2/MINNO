//==============================================================================
// OVT.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void OVT_user_init(test_function& func);

// ***********************************************************

void initialize_OVT(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	OVT_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_OVT(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum OVT {
	A_Func_Num_OVT,
	A_OVT_OFF,
	A_OVT_ON,

};