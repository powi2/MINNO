//==============================================================================
// STRESS.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void STRESS_user_init(test_function& func);

// ***********************************************************

void initialize_STRESS(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	STRESS_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_STRESS(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum STRESS{

	A_Func_Num_STRESS,
	A_STRESS_Voltage,

	A_ILL_D_post,
	A_ILL_D_delta,
	A_ILH_D_post,
	A_ILH_D_delta,
	A_ILL_UV_post,
	A_ILL_UV_delta,
	A_ILH_UV_post,
	A_ILH_UV_delta,
	A_ILL_FW_post,
	A_ILL_FW_delta,
	A_ILH_FW_post,
	A_ILH_FW_delta,
	A_ILL_VO_post,
	A_ILL_VO_delta,
	A_ILH_VO_post,
	A_ILH_VO_delta,
	A_ILL_SR_post,
	A_ILL_SR_delta,
	A_ILH_SR_post,
	A_ILH_SR_delta,
	A_ILL_REQ_post,
	A_ILL_REQ_delta,
	A_ILH_REQ_post,
	A_ILH_REQ_delta,
	A_ILL_FWC_post,
	A_ILL_FWC_delta,
	A_ILH_FWC_post,
	A_ILH_FWC_delta,
	A_ILL_ACK_post,
	A_ILL_ACK_delta,
	A_ILH_ACK_post,
	A_ILH_ACK_delta,
	A_BPS_IS1_pre,
	A_BPS_IS1_post,
	A_BPS_IS1_delta,
	A_BPS_IS2_pre,
	A_BPS_IS2_post,
	A_BPS_IS2_delta,
	A_BPP_IS1_pre,
	A_BPP_IS1_post,
	A_BPP_IS1_delta,
	A_BPP_IS2_pre,
	A_BPP_IS2_post,
	A_BPP_IS2_delta,

};