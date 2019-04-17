//==============================================================================
// BV_Drain.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void BV_Drain_user_init(test_function& func);

// ***********************************************************

void initialize_BV_Drain(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	BV_Drain_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_BV_Drain(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum enum_BV_Drain{
	A_Func_Num_BV_Drain,
	//A_BVDSS_STR_50UA,
	//A_BVDSS_ISTR_50UA,
	//A_BVDSS_WALK_50UA,
	A_BVDSS_ISTR,
	A_BVDSS_STR1,
	A_BVDSS_STR2,
	A_BVDSS_7x_STR1,
	A_BVDSS_7x_STR2,
	A_BVDSS_WALK,
	A_BVD_100UA,
	A_BVD_7x_100UA,
	A_IDS_BVD_10V,
	A_IDS_80BVD,
	A_IDS_325V,
	A_IDS_150V,
	A_IDS_30V,
	//A_IDS_50V_TAPoff, // Done with DVI for bettter accuracy
	//A_IDS_325V_TAPon,
	//A_HandShake_PASS,
	//A_tHS_BV,
};