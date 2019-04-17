//==============================================================================
// Feature_Trim_S.cpp (User function)
// 
//    void Feature_Trim_S_user_init(test_function& func)
//    void Feature_Trim_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "Feature_Trim_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Feature_Trim_S_user_init(test_function& func)
{
	Feature_Trim_S_params *ours;
    ours = (Feature_Trim_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Feature_Trim_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    Feature_Trim_S_params *ours;
    ours = (Feature_Trim_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 11;

	Func_name = "Feature_Trim_S";
	gFuncNum++;
	if (gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Feature_Trim_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (ours->force_code == -99)						//REMARK AT PRODUCTION
	{													//REMARK AT PRODUCTION
		if (OPCODE != 4200 || TRIM_ENABLE == 0)
			return;
	}													//REMARK AT PRODUCTION

	double	Feature_Code_S		= 0;
	float	IZtr_S[100]			= {-999.0};
	bool	Trim_S[100]			= {false};
	int		A_IZtr_S[100]		= {1};

	int previous_addr = 0, trim_addr = 0, clks = 0;

	//Determine what feature to trim based on given info from DE
	//Determine PK trim bits,			3 bits
	if ((gTrim_PK_S & 1) == 1)	Trim_S[gPK_ssSpeed_AF_Addr_Start]		= true;
	if ((gTrim_PK_S & 2) == 2)	Trim_S[gPK_ssSpeed_AF_Addr_Start + 1]	= true;
	if ((gTrim_PK_S & 4) == 4)	Trim_S[gPK_ssSpeed_AF_Addr_Start + 2]	= true;

	//Determine Rnw coarse trim bits,	2 bits
	if ((gTrim_Rnw_S & 1) == 1)	Trim_S[gRnw_AF_Addr_Start]		= true;
	if ((gTrim_Rnw_S & 2) == 2)	Trim_S[gRnw_AF_Addr_Start + 1]	= true;

	//Determine Rnw fine trim bits,		4 bits
	if ((gTrim_RnwFine_S & 1) == 1)	Trim_S[gRnwFine_AF_Addr_Start]		= true;
	if ((gTrim_RnwFine_S & 2) == 2)	Trim_S[gRnwFine_AF_Addr_Start + 1]	= true;
	if ((gTrim_RnwFine_S & 4) == 4)	Trim_S[gRnwFine_AF_Addr_Start + 2]	= true;
	if ((gTrim_RnwFine_S & 8) == 8)	Trim_S[gRnwFine_AF_Addr_Start + 3]	= true;

	Trim_S[gFWC2_AF_Addr_Start]			= gTrim_FWC2_S;
	Trim_S[gNoFWC100mV_AF_Addr_Start]	= gTrim_NoFWC100mV_S;

	//Determine Cap trim bits,			3 bits
	if ((gTrim_Cap_S & 1) == 1)		Trim_S[gCap_AF_Addr_Start]		= true;
	if ((gTrim_Cap_S & 2) == 2)		Trim_S[gCap_AF_Addr_Start + 1]	= true;
	if ((gTrim_Cap_S & 4) == 4)		Trim_S[gCap_AF_Addr_Start + 2]	= true;

	//Determine PKdig trim bits,		4 bits
	if ((gTrim_PKdig_S & 1) == 1)	Trim_S[gPKdig_AF_Addr_Start]		= true;
	if ((gTrim_PKdig_S & 2) == 2)	Trim_S[gPKdig_AF_Addr_Start + 1]	= true;
	if ((gTrim_PKdig_S & 4) == 4)	Trim_S[gPKdig_AF_Addr_Start + 2]	= true;
	if ((gTrim_PKdig_S & 8) == 8)	Trim_S[gPKdig_AF_Addr_Start + 3]	= true;

	if (g_Stress_passed == 1)	//Only trim Vshunt bit if Stress test passed
	{
		Trim_S[gVshunt_AF_Addr_Start] = gTrim_Vshunt_S;
	}

	//Determine IintTC trim bits,		4 bits
	if ((gTrim_IintTC_S & 1) == 1)	Trim_S[gIintTC_AF_Addr_Start]		= true;
	if ((gTrim_IintTC_S & 2) == 2)	Trim_S[gIintTC_AF_Addr_Start + 1]	= true;
	if ((gTrim_IintTC_S & 4) == 4)	Trim_S[gIintTC_AF_Addr_Start + 2]	= true;
	if ((gTrim_IintTC_S & 8) == 8)	Trim_S[gIintTC_AF_Addr_Start + 3]	= true;

	Trim_S[gDOPL_AF_Addr_Start]		= gTrim_DOPL_S;
	Trim_S[gREQlow_AF_Addr_Start]	= gTrim_REQlow_S;
	Trim_S[gXFWPK_AF_Addr_Start]	= gTrim_XFWPK_S;
	Trim_S[gLO_dis_AF_Addr_Start]	= gTrim_LO_dis_S;

	//Map to VATE subtest number
	A_IZtr_S[gPK_ssSpeed_AF_Addr_Start]		= A_IZtr_PK1spdLd_S;
	A_IZtr_S[gPK_ssSpeed_AF_Addr_Start + 1]	= A_IZtr_PK2_S;
	A_IZtr_S[gPK_ssSpeed_AF_Addr_Start + 2]	= A_IZtr_PK3_S;
	A_IZtr_S[gRnw_AF_Addr_Start]			= A_IZtr_Rnw5_S;
	A_IZtr_S[gRnw_AF_Addr_Start + 1]		= A_IZtr_Rnw6_S;
	A_IZtr_S[gRnwFine_AF_Addr_Start]		= A_IZtr_Rnw1_S;
	A_IZtr_S[gRnwFine_AF_Addr_Start + 1]	= A_IZtr_Rnw2_S;
	A_IZtr_S[gRnwFine_AF_Addr_Start + 2]	= A_IZtr_Rnw3_S;
	A_IZtr_S[gRnwFine_AF_Addr_Start + 3]	= A_IZtr_Rnw4_S;
	A_IZtr_S[gFWC2_AF_Addr_Start]			= A_IZtr_FWC2_S;
	A_IZtr_S[gNoFWC100mV_AF_Addr_Start]		= A_IZtr_NoFWC100mV_S;
	A_IZtr_S[gCap_AF_Addr_Start]			= A_IZtr_Cap1_S;
	A_IZtr_S[gCap_AF_Addr_Start + 1]		= A_IZtr_Cap2_S;
	A_IZtr_S[gCap_AF_Addr_Start + 2]		= A_IZtr_Cap3_S;
	A_IZtr_S[gPKdig_AF_Addr_Start]			= A_IZtr_PKdig1_S;
	A_IZtr_S[gPKdig_AF_Addr_Start + 1]		= A_IZtr_PKdig2_S;
	A_IZtr_S[gPKdig_AF_Addr_Start + 2]		= A_IZtr_PKdig3_S;
	A_IZtr_S[gPKdig_AF_Addr_Start + 3]		= A_IZtr_PKdig4_S;
	A_IZtr_S[gVshunt_AF_Addr_Start]			= A_IZtr_Vshunt_S;
	A_IZtr_S[gIintTC_AF_Addr_Start]			= A_IZtr_IintTC1_S;
	A_IZtr_S[gIintTC_AF_Addr_Start + 1]		= A_IZtr_IintTC2_S;
	A_IZtr_S[gIintTC_AF_Addr_Start + 2]		= A_IZtr_IintTC3_S;
	A_IZtr_S[gIintTC_AF_Addr_Start + 3]		= A_IZtr_IintTC4_S;
	A_IZtr_S[gDOPL_AF_Addr_Start]			= A_IZtr_DOPL_S;
	A_IZtr_S[gREQlow_AF_Addr_Start]			= A_IZtr_REQlow_S;
	A_IZtr_S[gXFWPK_AF_Addr_Start]			= A_IZtr_XFWPK_S;
	A_IZtr_S[gLO_dis_AF_Addr_Start]			= A_IZtr_LO_dis_S;

	//Power Up to Trim Features for Secondary (See OTS/TestPlan)
	Powerup_to_trim_secondary();

	previous_addr =	0;
	trim_addr     =	0;

	//Forced trim code
	if (ours->force_code != -99)
	{
		if (ours->force_code == 0)
		{
			Powerdown_from_trim_secondary();
			return;
		}

		trim_addr = ours->force_code;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_S[trim_addr], gAF_1ST_TRIM_DELAY);   // IZtr, Zap time(in ms)
		PiDatalog(func, A_IZtr_S[trim_addr], IZtr_S[trim_addr], set_fail_bin, POWER_MILLI);

		Powerdown_from_trim_secondary();
		return;
	}

	//Feature Bits trimmed
	for (trim_addr = 1; trim_addr <= gTotal_Addr_Count_S; trim_addr++)
	{
		if (Trim_S[trim_addr])
		{
			clks = trim_addr - previous_addr;
			DDD_Clock_Vout_Antifuse(clks);
			Trim_Anti_fuse_secondary(&IZtr_S[trim_addr], gAF_1ST_TRIM_DELAY);   // IZtr, Zap time(in ms)
			PiDatalog(func, A_IZtr_S[trim_addr], IZtr_S[trim_addr], set_fail_bin, POWER_MILLI);
			previous_addr =  trim_addr;
		}
	}

	//Trim all bits and observe IZtr
	if (0)
	{
		printf("\nTrim All Secondary bits with trim time of %.2f ms\n", gAF_1ST_TRIM_DELAY);
		previous_addr = 0;
		for(trim_addr = 1; trim_addr <= gTotal_Addr_Count_S; trim_addr++)
		{
			clks = trim_addr - previous_addr;
			DDD_Clock_Vout_Antifuse(clks);
			Trim_Anti_fuse_secondary(&IZtr_S[trim_addr], gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
			printf("Addr = %i, Iztr = %.2f mA\n", trim_addr, IZtr_S[trim_addr]*1e3);
			previous_addr = trim_addr;
		}
	}

	// Power down from trim
	Powerdown_from_trim_secondary();

	if (gDEBUG)
	printf("Function Feature_Trim_S Done\n");
}
