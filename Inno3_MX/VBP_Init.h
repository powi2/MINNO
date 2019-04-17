//==============================================================================
// VBP_Init.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void VBP_Init_user_init(test_function& func);

// ***********************************************************

void initialize_VBP_Init(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	VBP_Init_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_VBP_Init(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}

// ***********************************************************
enum VBP_init{

	A_Func_Num_VBP_init,
	A_ID_1V_2V,				//1
	A_Vshunt_Init_Pr,		//2
	A_Vshunt_Init_Se,		//3
	A_VBPP_PV_Init,			//4
	A_VBPP_M_Init,			//5
	A_VBPP_P_Init,			//6
	A_VBPP_P_S_Init_P,
	A_VBPP_P_iHVoff,		//7
	A_VBPP_Vshunt_PUseq,	//8
	A_VBPP_HYS_Init,		//9
	A_VBPS_P_Init,			//10
	A_VBPS_M_Init,			//11
	A_VBPS_HYS_Init,		//12

};
