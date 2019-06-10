//==============================================================================
// Iz_xChk_Reg_S.cpp (User function)
// 
//    void Iz_xChk_Reg_S_user_init(test_function& func)
//    void Iz_xChk_Reg_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Iz_xChk_Reg_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Iz_xChk_Reg_S_user_init(test_function& func)
{
	Iz_xChk_Reg_S_params *ours;
    ours = (Iz_xChk_Reg_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Iz_xChk_Reg_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    Iz_xChk_Reg_S_params *ours;
    ours = (Iz_xChk_Reg_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "Iz_xChk_Reg_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Iz_xChk_Reg_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	int		i=0, 
			Reg_IZ=0,
			Reg_Diff[53]={0};
	float	iAFs_th =0.0; 
	
//	iAFs_th = 40e-6;
	iAFs_th = 20e-6;	// Per Qing and Shreyas.

	////Compare SR register result against AF current result
	//for(i=1; i<=52; i++)
	//{
	//	if(gIZ_AF_post_S[i] > iAFs_th)
	//		Reg_IZ=1;
	//	else
	//		Reg_IZ=0;

	//	Reg_Diff[i] = 0;
	//	Reg_Diff[i] = Reg_IZ - gSR_AF_post[i];
	//	if(i==52)
	//	{
	//		if(gSiliconRev_S >= revB2_S)
	//			PiDatalog(func, i,		Reg_Diff[i],			set_fail_bin,	POWER_UNIT);	//F4
	//		else
	//			PiDatalog(func, i+1,	Reg_Diff[i],			set_fail_bin,	POWER_UNIT);	//ZF
	//	}
	//	else
	//			PiDatalog(func, i,		Reg_Diff[i],			set_fail_bin,	POWER_UNIT);
	//}
	if(gDEBUG)
	printf("Function Iz_xChk_Reg_S Done\n");

//	if (PiGetAnyFailStatus())
//	{
//		delay(2);
//	}

}
