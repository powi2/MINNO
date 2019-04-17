//==============================================================================
// Fosc_Trim_S.cpp (User function)
// 
//    void Fosc_Trim_S_user_init(test_function& func)
//    void Fosc_Trim_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_Trim_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_Trim_S_user_init(test_function& func)
{
	Fosc_Trim_S_params *ours;
    ours = (Fosc_Trim_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_Trim_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_Trim_S_params *ours;
    ours = (Fosc_Trim_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	//set_fail_bin = 11;

	Func_name = "Fosc_Trim_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Fosc_Trim_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

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

	float	IZtr_F1_S =0.0,
			IZtr_F2_S =0.0,
			IZtr_F3_S =0.0,
			IZtr_F4_S =0.0;

	float trim_weight[32]={0};		// Double of what's needed
	float trim_target=0.0,trim_exp=0.0;
	float trim_needed =0.0, trim_result =0.0;
	float delta;
	int	  trim_code=0, plot_code;
	int	  Force_Trim =0;

	int   previous_addr, trim_addr, clks;
	int	  i;

	//if(gSiliconRev_S >= revB2_S)	//F4 bit added in revB2 silicon and stay for future silicon
	//{
	//		//		(17.7%, -8.8%, -4%, -2.2%) => (F3,F2,F1) 	Trim Code	Plot Code
	//		trim_weight[0] = 0.0;		// Code: 0000			0			 0
	//		trim_weight[1] = -2.2;		// Code: 0001			1			-1
	//		trim_weight[2] = -4.0;		// Code: 0010			2			-2
	//		trim_weight[3] = -6.2;		// Code: 0011			3			-3
	//		trim_weight[4] = -8.8;		// Code: 0100			4			-4
	//		trim_weight[5] = -11.0;		// Code: 0101			5			-5
	//		trim_weight[6] = -12.8;		// Code: 0110			6			-6
	//		trim_weight[7] = -15.0;		// Code: 0111			7			-7
	//		trim_weight[8]  = 2.7;		// Code: 1000			8			 1
	//		trim_weight[9]  = 4.9;		// Code: 1001			9			 2
	//		trim_weight[10] = 6.7;		// Code: 1010			10			 3
	//		trim_weight[11] = 8.9;		// Code: 1011			11			 4
	//		trim_weight[12] = 11.5;		// Code: 1100			12			 5
	//		trim_weight[13] = 13.7;		// Code: 1101			13			 6
	//		trim_weight[14] = 15.5;		// Code: 1110			14			 7
	//		trim_weight[15] = 17.7;		// Code: 1111			15			 8
	//}
	//else	//revB_S silicon F1,F2,F3
	//{
	//		//			(+20%, -10%, -5%) => (F3,F2,F1) 	Trim Code	Plot Code
	//		trim_weight[0] = 0.0;		// Code: 000		0			 0
	//		trim_weight[1] = -3.0;		// Code: 001		1			-1
	//		trim_weight[2] = -6;		// Code: 010		2			-2
	//		trim_weight[3] = -9;		// Code: 011		3			-3
	//		trim_weight[4] = 3.0;		// Code: 100		4			+1
	//		trim_weight[5] = 6.67;		// Code: 101		5			+2
	//		trim_weight[6] = 10.8;		// Code: 110		6			+3
	//		trim_weight[7] = 13.5;		// Code: 111		7			+4
	//}
	//if(gSiliconRev_S == revA1_S)	//F4 bit added in revB2 silicon and stay for future silicon
	//{
			//		(17.7%, -8.8%, -4%, -2.2%) => (F3,F2,F1) 	Trim Code	Plot Code
			trim_weight[0] = 0.0;		// Code: 0000			0			 0
			trim_weight[1] = -2.2;		// Code: 0001			1			-1
			trim_weight[2] = -4.4;		// Code: 0010			2			-2
			trim_weight[3] = -6.6;		// Code: 0011			3			-3
			trim_weight[4] = -8.8;		// Code: 0100			4			-4
			trim_weight[5] = -11.0;		// Code: 0101			5			-5
			trim_weight[6] = -13.2;		// Code: 0110			6			-6
			trim_weight[7] = -15.4;		// Code: 0111			7			-7
			trim_weight[8]  = 2.2;		// Code: 1000			8			 1
			trim_weight[9]  = 4.4;		// Code: 1001			9			 2
			trim_weight[10] = 6.6;		// Code: 1010			10			 3
			trim_weight[11] = 8.8;		// Code: 1011			11			 4
			trim_weight[12] = 11.0;		// Code: 1100			12			 5
			trim_weight[13] = 13.2;		// Code: 1101			13			 6
			trim_weight[14] = 15.4;		// Code: 1110			14			 7
			trim_weight[15] = 17.6;		// Code: 1111			15			 8
	//}
	//Pass FS trim_weights Globally
//	for(i=0; i<8; i++)
//	{
//		gFS_trim_weight[i] = trim_weight[i];
//	}

	trim_target = gFOSC_TARGET_S;

	if(ours->force_code == -99)							
	{													
		if(gFOSC_pt_S >50e3)	//must be within trim range
			trim_needed = 100.0 * (1- gFOSC_pt_S/trim_target);	
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
	for(i =0; i<=15 ;i++)			// i< 2^(#of bits)
	{
		trim_result =  gFOSC_pt_S*(trim_weight[i]/100.0 +1);
		if(fabs(trim_result - trim_target) < delta)
		{
			trim_code = i;
			delta = fabs(trim_result - trim_target);
		}
	}


	//if(gSiliconRev_S >= revB2_S)	//F4 bit added in revB2 silicon
	//{
	//	if(ours->force_code >-7 && ours->force_code <=0)	// Allow force code from -3 to 0
	//	{
	//		Force_Trim =1;
	//		trim_code = -ours->force_code;				// Force code -7 to 0; 
	//	}
	//	else if (ours->force_code >0 && ours->force_code <=4)	// +1 to +8
	//	{
	//		Force_Trim =1;
	//		trim_code = ours->force_code+7;					// Force code  +1 to +8
	//	}
	//	else if (ours->force_code != -99)
	//	{
	//		mdb.SetStatusDialogHasOKButton(TRUE);
	//		mdb.SetDialogTopMessage("** FOSC_S Force Code is outside of Range ****");
	//		mdb.SetDialogBottomMessage("**** Force a valid trim code or set it to -99 for auto trim ****");
	//		RunModalDialog(&mdb);	//Output error message
	//		return;			// Force trim code outside of Range. Disable trimming 
	//	}
	//}
	//else	//revB silicon with F1,F2,F3 bits 
	//{
	//	if(ours->force_code >-4 && ours->force_code <=0)	// Allow force code from -3 to 0
	//	{
	//		Force_Trim =1;
	//		trim_code = -ours->force_code;				// Force code -3 to 0; 
	//	}
	//	else if (ours->force_code >0 && ours->force_code <=4)	// +1 to +4
	//	{
	//		Force_Trim =1;
	//		trim_code = ours->force_code+3;					// Force code  +1 to +4
	//	}
	//	else if (ours->force_code != -99)
	//	{
	//		mdb.SetStatusDialogHasOKButton(TRUE);
	//		mdb.SetDialogTopMessage("** FOSC_S Force Code is outside of Range ****");
	//		mdb.SetDialogBottomMessage("**** Force a valid trim code or set it to -99 for auto trim ****");
	//		RunModalDialog(&mdb);	//Output error message
	//		return;			// Force trim code outside of Range. Disable trimming 
	//	}
	//}
	if(gSiliconRev_S >= revA1_S)	//F4 bit added in revB2 silicon
	{
		if(ours->force_code >-7 && ours->force_code <=0)	// Allow force code from -3 to 0
		{
			Force_Trim =1;
			trim_code = -ours->force_code;				// Force code -7 to 0; 
		}
		else if (ours->force_code >0 && ours->force_code <=4)	// +1 to +8
		{
			Force_Trim =1;
			trim_code = ours->force_code+7;					// Force code  +1 to +8
		}
		else if (ours->force_code != -99)
		{
			mdb.SetStatusDialogHasOKButton(TRUE);
			mdb.SetDialogTopMessage("** FOSC_S Force Code is outside of Range ****");
			mdb.SetDialogBottomMessage("**** Force a valid trim code or set it to -99 for auto trim ****");
			RunModalDialog(&mdb);	//Output error message
			return;			// Force trim code outside of Range. Disable trimming 
		}
	}
	if (!TRIM_ENABLE && !Force_Trim)
		return;

// ********** Trim Anti-fuses **************//
	Powerup_to_trim_secondary();

	previous_addr =0;
	trim_addr     =0;
	if(trim_code & 1)
	{
		trim_addr = gFosc_AF_Addr_Start;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_F1_S,gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms),IZrd, Vread(on FW pin)
		// Datalog			
		PiDatalog(func, A_IZtr_F1_S,	IZtr_F1_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;

	}
	if(trim_code & 2)
	{
		trim_addr = gFosc_AF_Addr_Start + 1;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_F2_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms),IZrd, Vread(on FW pin));	
		// Datalog
		PiDatalog(func, A_IZtr_F2_S,	IZtr_F2_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;
	}
	if(trim_code & 4)
	{
		trim_addr = gFosc_AF_Addr_Start + 2;
		clks = trim_addr - previous_addr;
		DDD_Clock_Vout_Antifuse(clks);

		Trim_Anti_fuse_secondary(&IZtr_F3_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms),IZrd, Vread(on FW pin));	
		// Datalog
		PiDatalog(func, A_IZtr_F3_S,	IZtr_F3_S,		set_fail_bin,	POWER_MILLI);	

		previous_addr =  trim_addr;

	}

	////F4 bit exist in revB2 silicon
	//if(gSiliconRev_S >= revB2_S)
	//{
	//	if(trim_code & 8)
	//	{
	//		trim_addr = gFosc4_AF_Addr;
	//		clks = trim_addr - previous_addr;
	//		DDD_Clock_Vout_Antifuse(clks);

	//		Trim_Anti_fuse_secondary(&IZtr_F4_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms),IZrd, Vread(on FW pin));	
	//		// Datalog
	//		PiDatalog(func, A_IZtr_F4_S,	IZtr_F4_S,		set_fail_bin,	POWER_MILLI);	

	//		previous_addr =  trim_addr;

	//	}	
	//}
	//if(gSiliconRev_S >= revA1_S)
	//{
		if(trim_code & 8)
		{
			trim_addr = gFosc_AF_Addr_Start + 3;
			clks = trim_addr - previous_addr;
			DDD_Clock_Vout_Antifuse(clks);

			Trim_Anti_fuse_secondary(&IZtr_F4_S, gAF_1ST_TRIM_DELAY);// IZtr, Zap time(in ms),IZrd, Vread(on FW pin));	
			// Datalog
			PiDatalog(func, A_IZtr_F4_S,	IZtr_F4_S,		set_fail_bin,	POWER_MILLI);	

			previous_addr =  trim_addr;

		}	
	//}

	////if(trim_code >= 4)
	////	plot_code = trim_code -8;
	////else 
	////	plot_code = trim_code;
	//if(gSiliconRev_S >= revB2_S)
	//{
	//	if(trim_code >= 8)
	//		plot_code = trim_code - 7;
	//	else 
	//		plot_code = -trim_code;
	//}
	//else
	//{
	//	if(trim_code >= 4)
	//		plot_code = trim_code - 3;
	//	else 
	//		plot_code = -trim_code;
	//}
	if(gSiliconRev_S >= revA1_S)
	{
		if(trim_code >= 8)
			plot_code = trim_code - 7;
		else 
			plot_code = -trim_code;
	}

	gFOSC_exp_S = trim_weight[trim_code];	// Save value for post-trim change calculation 

	// Power down from trim
	Powerdown_from_trim_secondary();

	//Datalog
	PiDatalog(func, A_gFOSC_TARGET_S,trim_target,			set_fail_bin,	POWER_KILO);	
	PiDatalog(func, A_Fosc_code_S,	plot_code,				set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Fosc_table_S,	trim_weight[trim_code],	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Fosc_needed_S,trim_needed,			set_fail_bin,	POWER_UNIT);	

	if(gDEBUG)
	printf("Function Fosc_Trim_S Done\n");

}
