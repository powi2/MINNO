//==============================================================================
// SR_Trim_S.cpp (User function)
// 
//    void SR_Trim_S_user_init(test_function& func)
//    void SR_Trim_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "SR_Trim_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void SR_Trim_S_user_init(test_function& func)
{
	SR_Trim_S_params *ours;
    ours = (SR_Trim_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void SR_Trim_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    SR_Trim_S_params *ours;
    ours = (SR_Trim_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	//set_fail_bin = 11;

	Func_name = "SR_Trim_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_SR_Trim_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

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

	float	IZtr_SR1_S =0.0,
			IZtr_SR2_S =0.0,
			IZtr_SR3_S =0.0,
			IZtr_SR4_S =0.0;

	float trim_weight[32]={0};		// Double of what's needed
	float trim_target=0.0,trim_exp=0.0;
	float trim_needed =0.0, trim_result =0.0;
	float delta;
	int	  trim_code=0, plot_code;
	int	  Force_Trim =0;

	int   previous_addr, trim_addr, clks;
	int	  i;

	//if(gSiliconRev_S == revA1_S)
	//{
		//trim_weight in mV
		//											Trim Code	Plot Code
		//trim_weight[0] = 0;		// Code: 0000			0			 0
		//trim_weight[1] = 1;		// Code: 0001			1			 1
		//trim_weight[2] = 2;		// Code: 0010			2			 2
		//trim_weight[3] = 3;		// Code: 0011			3			 3
		//trim_weight[4] = 4;		// Code: 0100			4			 4
		//trim_weight[5] = 5;		// Code: 0101			5			 5
		//trim_weight[6] = 6;		// Code: 0110			6			 6
		//trim_weight[7] = 7;		// Code: 0111			7			 7
		//trim_weight[8]  = -1;	// Code: 1000			8			-1
		//trim_weight[9]  = -2;	// Code: 1001			9			-2
		//trim_weight[10] = -3;	// Code: 1010			10			-3
		//trim_weight[11] = -4;	// Code: 1011			11			-4
		//trim_weight[12] = -5;	// Code: 1100			12			-5
		//trim_weight[13] = -6;	// Code: 1101			13			-6
		//trim_weight[14] = -7;	// Code: 1110			14			-7
		//trim_weight[15] = -8;	// Code: 1111			15			-8
		//											Trim Code	Plot Code
		trim_weight[0] = 0;			// Code: 0000			0			 0
		trim_weight[1] = 1.5;		// Code: 0001			1			 1
		trim_weight[2] = 3.0;		// Code: 0010			2			 2
		trim_weight[3] = 4.5;		// Code: 0011			3			 3
		trim_weight[4] = 6.0;		// Code: 0100			4			 4
		trim_weight[5] = 7.5;		// Code: 0101			5			 5
		trim_weight[6] = 9.0;		// Code: 0110			6			 6
		trim_weight[7] = 10.5;		// Code: 0111			7			 7
		trim_weight[8]  = -1.5;		// Code: 1000			8			-1
		trim_weight[9]  = -3.0;		// Code: 1001			9			-2
		trim_weight[10] = -4.5;		// Code: 1010			10			-3
		trim_weight[11] = -6.0;		// Code: 1011			11			-4
		trim_weight[12] = -7.5;		// Code: 1100			12			-5
		trim_weight[13] = -9.0;		// Code: 1101			13			-6
		trim_weight[14] = -10.5;	// Code: 1110			14			-7
		trim_weight[15] = -11.5;	// Code: 1111			15			-8
	//}

	trim_target = gSRth_TARGET;

	if(ours->force_code == -99)							
	{													
		if(gSRth_pt_S > -12e-3 && gSRth_pt_S < 5e-3)	//must be within trim range
			trim_needed = (gSRth_pt_S/1e-3) - trim_target;	
		else
		{
			trim_needed = 999.0;
			return;
		}
	}

	// ********** Determine Trim Code ****** //
	trim_code = 0;
	delta = 9.99e6; 

	// Auto Trim Code
	for (i = 0; i <= 15; i++)			// i< 2^(#of bits)
	{
		trim_result = (gSRth_pt_S/1e-3) + trim_weight[i];
		if ((fabs(trim_result - trim_target) < delta) && (trim_result < 0))
		{
			trim_code = i;
			delta = fabs(trim_result - trim_target);
		}
	}

	if (gSiliconRev_S >= revA1_S)
	{
		if (ours->force_code >= -8 && ours->force_code < 0)	// Allow force code from -8 to -1
		{
			Force_Trim = 1;
			trim_code = -ours->force_code + 7;
		}
		else if (ours->force_code >= 0 && ours->force_code <= 7)	// 0 to +7
		{
			Force_Trim = 1;
			trim_code = ours->force_code;
		}
		else if (ours->force_code != -99)
		{
			mdb.SetStatusDialogHasOKButton(TRUE);
			mdb.SetDialogTopMessage("**** SR_Trim_S Force Code is outside of Range ****");
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
		trim_addr = gSRth_AF_Addr_Start;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_SR1_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_SR1_S,	IZtr_SR1_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	if(trim_code & 2)
	{
		trim_addr = gSRth_AF_Addr_Start + 1;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_SR2_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_SR2_S,	IZtr_SR2_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	if(trim_code & 4)
	{
		trim_addr = gSRth_AF_Addr_Start + 2;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_SR3_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_SR3_S,	IZtr_SR3_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	if(trim_code & 8)
	{
		trim_addr = gSRth_AF_Addr_Start + 3;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_SR4_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms)
		// Datalog			
		PiDatalog(func, A_IZtr_SR4_S,	IZtr_SR4_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}

	plot_code = (int)trim_weight[trim_code];

	gSRth_exp_S = trim_weight[trim_code];	// Save value for post-trim change calculation

	// Power down from trim
	Powerdown_from_trim_secondary();

	//Datalog
	PiDatalog(func, A_gSR_TARGET_S,	trim_target * 1e-3,		set_fail_bin,	POWER_MILLI);	
	PiDatalog(func, A_SR_code_S,	plot_code,				set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_SR_table_S,	trim_weight[trim_code],	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_SR_needed_S,	trim_needed,			set_fail_bin,	POWER_UNIT);	

	if(gDEBUG)
	printf("Function SR_Trim_S Done\n");

}
