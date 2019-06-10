//==============================================================================
// IBP_Supply.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void IBP_Supply_user_init(test_function& func);

// ***********************************************************

void initialize_IBP_Supply(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	IBP_Supply_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_IBP_Supply(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum IBP_Supply{
	A_Func_Num_IBP_Supply,
	A_BPP_ICH1_0V_p,
	A_BPS_ICH1_3V_s,
	A_BPP_ICH2_4V_p,
	A_BPS_ICH2_4V_s,
	A_BPS_ICH2_4V_FW11V_s,
	A_R_SRclamp_S,
	A_BPP_ICH3_CEN_p,
	A_BPS_ICH3_VO_5v_S,
	A_BPS_ICH3_4V_VO_5v_S,
	A_BPS_ICH3_4V_VO20v_S,
	A_Delta_VO_minus_VBPS_S,
	A_BPP_ICH4_D_p,
	A_BPP_ICH5_CEN_p,
	A_BPS_IS1_nsw_s,
	A_BPS_IS2_sw_s,
	A_BPP_IS1_nsw_s,
	A_BPP_IS2_sw_s,
};