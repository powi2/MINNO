//==============================================================================
// Setup.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Setup_user_init(test_function& func);

// ***********************************************************

void initialize_Setup(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Setup_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Setup(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum enum_Setup{

	A_Func_Num_Setup,
	A_Setup,
	A_BUFgain,
	A_iPV3_Cal_CC90,
	A_iPV3_Cal_CC80,
	A_iPV3_Cal_CC65,
	A_iPV3_Cal_CC55,
	A_DVI2K_ch0_Temp,
	A_DVI2K_ch1_Temp,
	A_Primary_Si_Rev,
	A_Secondary_Si_Rev,
	A_gDevNum,
	A_Hcode,
	A_Dig_Type,
	A_HVS_RELAY_CHK,
	A_LB_ID,
	A_CB_ID,
	A_IB_ID,
	A_TB_ID,
};