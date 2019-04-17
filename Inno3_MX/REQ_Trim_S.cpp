//==============================================================================
// REQ_Trim_S.cpp (User function)
// 
//    void REQ_Trim_S_user_init(test_function& func)
//    void REQ_Trim_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "REQ_Trim_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void REQ_Trim_S_user_init(test_function& func)
{
	REQ_Trim_S_params *ours;
    ours = (REQ_Trim_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void REQ_Trim_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    REQ_Trim_S_params *ours;
    ours = (REQ_Trim_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	//set_fail_bin = 11;

	Func_name = "REQ_Trim_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_REQ_Trim_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if(ours->force_code == -99)							//REMARK AT PRODUCTION
	{													//REMARK AT PRODUCTION
		if (OPCODE != 4200 || TRIM_ENABLE == 0)
			return;
	}													//REMARK AT PRODUCTION
	//if (!gHandShake_PASS)
	//	return;

	float	IZtr_V1_S =0.0,
			IZtr_V2_S =0.0,
			IZtr_V3_S =0.0,
			IZtr_V4_S =0.0,
			IZtr_V5_S =0.0,
			IZtr_V6_S =0.0;

	float trim_weight[128]={0};		// Double of what's needed
	float trim_target=0.0,trim_exp=0.0;
	float trim_needed =0.0, trim_result =0.0;
	float trim_plotcode = 0.0;
	float delta;
	int	  trim_code=0, plot_code;
	int	  Force_Trim =0;

	int   previous_addr, trim_addr, clks;
	
	//if(gSiliconRev_S == revA1_S)
	//{
	//	//trim_weight in %
	//														Trim Code	Plot Code
	//	trim_weight[0]  =   0.00;		// Code: 000000			0			 0
	//	trim_weight[1]  =  -0.85;		// Code: 000001			1			-1
	//	trim_weight[2]  =  -1.70;		// Code: 000010			2			-2
	//	trim_weight[3]  =  -2.55;		// Code: 000011			3			-3
	//	
	//	trim_weight[30] = -24.60;		// Code: 011110			30			-30
	//	trim_weight[31] = -25.45;		// Code: 011111			31			-31
	//	trim_weight[32] =   0.85;		// Code: 100000			32			 1
	//	trim_weight[33] =   1.70;		// Code: 100001			33			 2
	//	
	//	trim_weight[63] =  26.35;		// Code: 111111			63			 63
	//}

	trim_target = gVref_TARGET;
	//possible trim range 0.975V to 1.547V

	if(ours->force_code == -99)							
	{													
		if(gREQ_Vref_pt_S > 1 && gREQ_Vref_pt_S < 1.53)	//must be within trim range
			trim_needed = (trim_target / gREQ_Vref_pt_S) - 1;
		else
		{
			trim_needed = 999.0;
			return;
		}
	}

	// ********** Determine Trim Code ****** //
	trim_code = 0;
	delta = 9.99e6; 

	trim_plotcode = (trim_needed + 0.0004454) / 0.007178;	// obtained from measurements

	plot_code = (int)(trim_plotcode > 0.0) ? (trim_plotcode + 0.5) : (trim_plotcode - 0.5); 

	trim_code = (plot_code <= 0) ? (-plot_code) : (plot_code + 31);

	if (gSiliconRev_S >= revA1_S)
	{
		if (ours->force_code >= 0 && ours->force_code < 64)	// Allow force code from 0 to 63
		{
			Force_Trim = 1;
			trim_code = ours->force_code;
		}
		else if (ours->force_code != -99)
		{
			mdb.SetStatusDialogHasOKButton(TRUE);
			mdb.SetDialogTopMessage("**** REQ_Trim_S Force Code is outside of Range ****");
			mdb.SetDialogBottomMessage("**** Force a valid trim code or set it to -99 for auto trim ****");
			RunModalDialog(&mdb);	//Output error message
			return;			// Force trim code outside of Range. Disable trimming 
		}
	}
	if (!TRIM_ENABLE && !Force_Trim)
		return;

	// ********** Trim Anti-fuses **************//
	Powerup_to_trim_secondary();

	previous_addr = 0;
	trim_addr     = 0;
	if(trim_code & 1)
	{
		trim_addr = gVref_AF_Addr_Start;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_V1_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_V1_S,	IZtr_V1_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	if(trim_code & 2)
	{
		trim_addr = gVref_AF_Addr_Start + 1;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_V2_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_V2_S,	IZtr_V2_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	if(trim_code & 4)
	{
		trim_addr = gVref_AF_Addr_Start + 2;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_V3_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_V3_S,	IZtr_V3_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	if(trim_code & 8)
	{
		trim_addr = gVref_AF_Addr_Start + 3;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_V4_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_V4_S,	IZtr_V4_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	if(trim_code & 16)
	{
		trim_addr = gVref_AF_Addr_Start + 4;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_V5_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_V5_S,	IZtr_V5_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	if(trim_code & 32)
	{
		trim_addr = gVref_AF_Addr_Start + 5;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_V6_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_V6_S,	IZtr_V6_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	gVref_exp_S = trim_needed;	// Save value for post-trim change calculation

	// Power down from trim
	Powerdown_from_trim_secondary();

	//Datalog
	PiDatalog(func, A_gVref_TARGET_S,	trim_target,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_code_S,		plot_code,				set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_table_S,		trim_plotcode,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_needed_S,		trim_needed,			set_fail_bin,	POWER_UNIT);	

	if(gDEBUG)
	printf("Function REQ_Trim_S Done\n");

}
