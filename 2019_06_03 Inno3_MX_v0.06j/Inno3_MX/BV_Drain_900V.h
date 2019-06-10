//==============================================================================
// BV_Drain_900V.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void BV_Drain_900V_user_init(test_function& func);

// ***********************************************************

void initialize_BV_Drain_900V(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	BV_Drain_900V_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_BV_Drain_900V(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

enum enum_BVD_900V{
	A_Func_Num_BV_Drain_900V,
	A_9x_BVDSS_ISTR,
	A_9x_BVDSS_STR,
	A_9x_BVDSS_WALK,
	A_9x_BVD_100UA,
	A_9x_IDS_BVD_10V,
	A_9x_IDS_80BVD,
	A_9x_IDS_650V,
	A_9x_IDS_325V,
	A_9x_IDS_150V,
	A_9x_IDS_30V,
};
// ***********************************************************
