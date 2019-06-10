//==============================================================================
// Continuity.h 
//==============================================================================

#include "asl.h"
#include "function.h"

void Continuity_user_init(test_function& func);

// ***********************************************************

void initialize_Continuity(short test_entry,test_function& func,char **function_name)
{
	func.dlog->set_datalog_inactive();

	Continuity_user_init(func);

	func.dlog->test_offset = test_entry + 1;
}

// ***********************************************************

void setup_Continuity(test_function &func,char **function_name,char *heading_line,unsigned short *want_print,char manual_setup)
{
}



// ***********************************************************
enum enum_continuity{
	A_Func_Num_Continuity,
	A_VcontD,
	A_VcontD_p,
	A_VcontD_1mA,
	A_VcontD_Rat,
	A_IcontD,
	////A_ILL_D,
	////A_ILH_D,
	A_VcontBPP,
	A_VcontBPP_p,
	A_VcontBPP_1mA,
	A_VcontBPP_Rat,
	A_IcontBPP,
	////A_ILL_BPP,
	////A_ILH_BPP,
	A_VcontUV,
	A_VcontUV_p,
	A_VcontUV_1mA,
	A_VcontUV_Rat,
	A_IcontUV,
	////A_ILL_UV,
	////A_ILH_UV,
	A_VcontFW,
	A_VcontFW_p,
	A_VcontFW_1mA,
	A_VcontFW_Rat,
	A_IcontFW,
	////A_ILL_FW,
	////A_ILH_FW,
	A_VcontVO,
	A_VcontVO_p,
	A_VcontVO_1mA,
	A_VcontVO_Rat,
	A_IcontVO,
	////A_ILL_VO,
	////A_ILH_VO,
	A_VcontSR,
	A_VcontSR_p,
	A_VcontSR_1mA,
	A_VcontSR_Rat,
	A_IcontSR,
	////A_ILL_SR,
	////A_ILH_SR,
	A_VcontBPS,
	A_VcontBPS_p,
	A_VcontBPS_1mA,
	A_VcontBPS_Rat,
	A_IcontBPS,
	////A_ILL_BPS,
	////A_ILH_BPS,
	A_VcontREQ,
	A_VcontREQ_p,
	A_VcontREQ_1mA,
	A_VcontREQ_Rat,
	A_IcontREQ,
	////A_ILL_REQ,
	////A_ILH_REQ,
	A_VcontFWC,
	A_VcontFWC_p,
	A_VcontFWC_1mA,
	A_VcontFWC_Rat,
	A_IcontFWC,
	////A_ILL_FWC,
	////A_ILH_FWC,
	A_VcontACK,
	A_VcontACK_p,
	A_VcontACK_1mA,
	A_VcontACK_Rat,
	A_IcontACK,
	A_GNDRes_Sec,
	A_GNDRes_Pri,
};