//==============================================================================
// FWC_ACK_S.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void FWC_ACK_S_user_init(test_function& func);

// ***********************************************************

void initialize_FWC_ACK_S(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	FWC_ACK_S_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_FWC_ACK_S(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum FWC_ACK{

	A_Func_Num_FWC_ACK,
	A_VFWC_M_S,
	A_VFWC_P_S,
	A_FWC_width_S,
	A_tFWC_rise_S,
	A_tFWC_fall_S,
	A_FWC_delay_S,
	A_ACK_width_S,
	A_tACK_rise_S,
	A_tACK_fall_S,
	A_tdly_REQtoPulse,
	A_hold_off_test_S,
	A_no_pulse_test_S,
	A_latch_off_test_S,

};
