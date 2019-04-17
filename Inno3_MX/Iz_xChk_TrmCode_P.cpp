//==============================================================================
// Iz_xChk_TrmCode_P.cpp (User function)
// 
//    void Iz_xChk_TrmCode_P_user_init(test_function& func)
//    void Iz_xChk_TrmCode_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "Iz_xChk_TrmCode_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Iz_xChk_TrmCode_P_user_init(test_function& func)
{
	Iz_xChk_TrmCode_P_params *ours;
    ours = (Iz_xChk_TrmCode_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Iz_xChk_TrmCode_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Iz_xChk_TrmCode_P_params *ours;
    ours = (Iz_xChk_TrmCode_P_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 11;

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Iz_xChk_TrmCode_P,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;


}
