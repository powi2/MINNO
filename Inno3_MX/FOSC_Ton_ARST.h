//==============================================================================
// FOSC_Ton_ARST.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void FOSC_Ton_ARST_user_init(test_function& func);

// ***********************************************************

void initialize_FOSC_Ton_ARST(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	FOSC_Ton_ARST_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_FOSC_Ton_ARST(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum FOSC_Ton_ARST{

	A_Func_Num_FOSC_Ton_ARST,	
	A_FOSC_P,	
	A_FOSC_P_Err,
	A_FOSC_exp_P,
	A_FOSC_act_P,
	A_TonMax_P,	
	A_TonMax_P_Err,	
	A_DCmax_P,
	A_Loff_aft_AR_P,
	A_ARoff_P,
	A_AR_req_P,
	A_Loff_w_OT_P,
	A_FOSC_S,	
	A_FOSC_S_Err,
	A_DCmax_S,
	A_AR_disable_S,
	A_TonMax_S,	
	A_ToffMin_s,	
	A_TonMax1us_s,
	A_ToffMax1us_s,
	A_TonMax1us_frq_s,
	A_tAR_On_NM_P,	
	A_tAR_On_TM_P,	
	A_tAR_Off_TM_P,	
	A_tARskip_S,
	A_fModulation_P,
	A_tOVL_S,	
	A_tOVL_exp,	
	A_tOVL_act,	
	A_tOVL_Err_S,	
	A_tWL_NM_P,
	A_tWL_TM_P,
	A_fLB_audible_P,
	A_fUB_audible_P,
	A_tblock_S,
	A_tOffm_block_dif,
};