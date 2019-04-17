//==============================================================================
// SOA_SDS_TW50.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void SOA_SDS_TW50_user_init(test_function& func);

// ***********************************************************

void initialize_SOA_SDS_TW50(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	SOA_SDS_TW50_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_SOA_SDS_TW50(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum SOA_SDS_TW50{

	A_Func_Num_SOA_SDS_TW50,
	A_vSOA,
	A_vSDS,
	A_SOA_S,
	A_TW50_S,
	A_SDS_S,
	A_SDS_TW50_S,
	A_SDS_S_sw,		//Only datalog in REL_Flow
	A_SDS_S_nsw,
	A_SOA_P,
	A_TW50_P,
	A_didt_comp_P,
	A_SDS_P,
	A_SDS_TW50_P,
	A_SDS_P_sw,		//Only datalog in REL_Flow
	A_SDS_P_nsw,
	A_tARoffShort_P,
};