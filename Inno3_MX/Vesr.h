//==============================================================================
// Vesr.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Vesr_user_init(test_function& func);

// ***********************************************************

void initialize_Vesr(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Vesr_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Vesr(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum Vesr
{
	A_Func_Num_Vesr,
	A_VFB1,
	A_DeltaT1,
	A_VFB2,
	A_DeltaT2,
	A_VFB3,
	A_DeltaT3,
	A_VFB4,
	A_DeltaT4,
	A_Vesr_slope1,
	A_Vesr_int1,
	A_Vesr_slope2,
	A_Vesr_int2,
	A_Vesr_knee,
	A_Vesr_peak,
};
