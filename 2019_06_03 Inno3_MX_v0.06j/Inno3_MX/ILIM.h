//==============================================================================
// ILIM.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void ILIM_user_init(test_function& func);

// ***********************************************************

void initialize_ILIM(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	ILIM_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_ILIM(test_function &func,char **function_name,char *heading_line,unsigned short *want_Srint,char manual_setup)
{
}

// ***********************************************************
enum ILIM{
	A_Func_Num_ILIM,
	A_IlimHigh_JitterLow_S,
	A_IlimLow_JitterHigh_S,
	A_ILIM_Jit132K_S,
	A_ILIM_Jit18K_S,
	A_IlimHigh_JitterLow_18kHz_S,
	A_IlimLow_JitterHigh_18kHz_S,
	A_Fosc_Mod_18kHz_S,
	A_ILIM_S,
	A_ILIM_Err_S,
	A_ILIM_exp_S,
	A_ILIM_act_S,
	A_DIDT_S,
	A_DIDT_Err_S,
	A_TON_S,
	A_I2F_S,
	A_I2F_Err_S,
	A_ILIM_Low_S,
	A_ILIM_Low_Err_S,
	A_ILIM_Med_S,
	A_ILIM_Med_Err_S,
	A_ILIM_High_S,
	A_ILIM_High_Err_S,
	A_ILIM_RTM_Slope,
	A_tDelta_RTM_Slope_30us_S,
	A_i_pct_drop_RTM,
	A_tDelta_RTM_Slope_200us_S,
	A_ILIM_200us_S,
	A_ILIM_200us_pct_S,
	A_RxTx_CycReq_cnt,
	A_RxTx_Hi_BPS_Low_Rcv,
	A_RxTx_Lo_BPS_Low_Rcv,
	A_RxTx_Hi_BPS_High_Rcv,	//char only
	A_RxTx_Lo_BPS_High_Rcv,	//char only
	A_ILIM_P1_S,
	A_ILIM_P1_Err_S,
	A_DIDT_P1_S,
	A_TON_P1_S,
	A_RDSON_P1_S,
	A_Fosc_Sss_P,
	A_ILIM_70pct_mA_P,
	A_ILIM_70pct_P,
	A_tsoft_SSS,
	A_tHandshake_SSS,
	A_Fosc_min_SSS,
	A_Fosc_max_SSS,
	A_Fosc_Mod_S,
	A_tRTMrelease,
	A_tChUp_RTM_P,

};