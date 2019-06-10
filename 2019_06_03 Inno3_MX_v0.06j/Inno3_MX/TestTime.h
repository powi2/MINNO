//==============================================================================
// TestTime.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void TestTime_user_init(test_function& func);

// ***********************************************************

void initialize_TestTime(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	TestTime_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_TestTime(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum TestTime{

	A_Func_Num_TestTime,
	A_TestTime,
	A_TestTime_PP,
};