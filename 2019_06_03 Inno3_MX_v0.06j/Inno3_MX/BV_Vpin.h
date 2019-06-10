//==============================================================================
// BV_Vpin.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void BV_Vpin_user_init(test_function& func);

// ***********************************************************

void initialize_BV_Vpin(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	BV_Vpin_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_BV_Vpin(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************

enum BV_Vpin{
	A_Func_Num_BV_Vpin,
	A_BVD_Vpin,
	A_IDS_750V_Vpin,
	A_IDS_700V_Vpin,
	A_IDS_650V_Vpin,
	A_IDS_500V_Vpin,
};
