//==============================================================================
// TestTime.cpp (User function)
// 
//    void TestTime_user_init(test_function& func)
//    void TestTime(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "TestTime.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void TestTime_user_init(test_function& func)
{
	TestTime_params *ours;
    ours = (TestTime_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void TestTime(test_function& func)
{
    // The two lines below must be the first two in the function.
    TestTime_params *ours;
    ours = (TestTime_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_TestTime,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	PiDatalog(func, A_TestTime,		PiGetTestTime(),	  set_fail_bin, POWER_UNIT);
	PiDatalog(func, A_TestTime_PP,	PiGetPart2PartTime(), set_fail_bin, POWER_UNIT);

	if ((OPCODE == 4200||OPCODE == 4300) && !Golden_Unit_Prg)
			PiQcSampleSelect( );

//	PiQcSampleSelect();

	if(gDEBUG==1)
	printf("Function TestTime Done\n");

}
