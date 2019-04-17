//==============================================================================
// tOVL_Trim.cpp (User function)
// 
//    void tOVL_Trim_user_init(test_function& func)
//    void tOVL_Trim(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "tOVL_Trim.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void tOVL_Trim_user_init(test_function& func)
{
	tOVL_Trim_params *ours;
    ours = (tOVL_Trim_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void tOVL_Trim(test_function& func)
{
    // The two lines below must be the first two in the function.
    tOVL_Trim_params *ours;
    ours = (tOVL_Trim_params *)func.params;


	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 11;

	Func_name = "tOVL_Trim";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_tOVL_Trim,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if(ours->force_code == -99)							//REMARK AT PRODUCTION
	{													//REMARK AT PRODUCTION
		if (OPCODE != 4200 || TRIM_ENABLE == 0)
			return;
	}													//REMARK AT PRODUCTION

	// If Handshake wasn't done properly, Ton measurement will be primary Ton, which is wrong to use for trimming. 
	//if (!gHandShake_PASS)
	//	return;

	float 	IZtr_tOVL1=0.0,
			IZtr_tOVL2=0.0,
			IZtr_tOVLsign=0.0;

	float trim_weight[16]={0};		// Double of what's needed
	float trim_target=0.0,trim_exp=0.0;
	float trim_needed =0.0, trim_result =0.0;
	float delta;
	int	  trim_code=0, plot_code;
	int	  Force_Trim =0;

	int   previous_addr, trim_addr, clks;
	int	  i;					

	////////////************************************************************************
	////////////*** Table for tOVL_needed = [(Pre/Target)-1]*100% ********************
	////////////************************************************************************
	//////////							// L3, L2, L1		Trim Code	Plot Code
	//////////trim_weight[0] = 0.0;		// Code: 000			0			 0
	//////////trim_weight[1] = -4.0;		// Code: 001			1			 1	 
	//////////trim_weight[2] = -8.0;		// Code: 010			2			 2
	//////////trim_weight[3] = -12.0;		// Code: 011			3			 3   
	//////////trim_weight[4] = 4.0;		// Code: 100			4			-1
	//////////trim_weight[5] = 8.0;		// Code: 101			5			-2
	//////////trim_weight[6] = 12.0;		// Code: 110			6			-3
	//////////trim_weight[7] = 16.0;		// Code: 111			7			-4

	//************************************************************************
	//*** Table for tOVL_needed = -1*[(Pre/Target)-1]*100% *****************
	//************************************************************************
								// L3, L2, L1		Trim Code	Plot Code
	trim_weight[0] = 0.0;		// Code: 000			0			  0
	trim_weight[1] = -3.15;		//-4.0;		// Code: 001			1			 -1	 
	trim_weight[2] = -6.84;		//-8.0;		// Code: 010			2			 -2
	trim_weight[3] = -10.09;	//-12;		// Code: 011			3			 -3   
	trim_weight[4] = 4.64;		//4.0;		// Code: 100			4			  1
	trim_weight[5] = 8.88;		//8.0;		// Code: 101			5			  2
	trim_weight[6] = 13.38;		//12.0;		// Code: 110			6			  3
	trim_weight[7] = 18.0;		//16.0;		// Code: 111			7			  4

	//Below table is based on couple units
	////							// L3, L2, L1		Trim Code	Plot Code
	////trim_weight[0] = 0.0;		// Code: 000			0			  0
	////trim_weight[1] = -3.7;		// Code: 001			1			 -1	 
	////trim_weight[2] = -7.0;		// Code: 010			2			 -2
	////trim_weight[3] = -10.1;		// Code: 011			3			 -3   
	////trim_weight[4] = 3.8;		// Code: 100			4			  1
	////trim_weight[5] = 7.6;		// Code: 101			5			  2
	////trim_weight[6] = 11.0;		// Code: 110			6			  3
	////trim_weight[7] = 17.0;		// Code: 111			7			  4

	trim_target = g_tOVL_TARGET;

	if(g_tOVL_Pt !=0 && g_tOVL_Pt < 15e-6)
//		trim_needed = 100.0 * ((trim_target /gtOVL_Pt) -1);	
		trim_needed = -100.0 * ((g_tOVL_Pt / trim_target) -1);	
	else
		trim_needed = 999.0;

// ********** Determine Trim Code ****** //
	trim_code = 0;
	delta = 9.99e6; 

	// Auto Trim Code
	for(i =0; i<8 ;i++)			// i< 2^(#of bits)
	{
		trim_result =  g_tOVL_Pt*(trim_weight[i]/100.0 +1);
		if(fabs(trim_result - trim_target) < delta)
		{
			trim_code = i;
			delta = fabs(trim_result - trim_target);
		}
	}
	
	// Force Trim Code
	if(ours->force_code>= -3 && ours->force_code <=4)	// Allow force code from -3 to 4
	{
		Force_Trim =1;
		if(ours->force_code <= 0)			
			trim_code = -ours->force_code;			//-3 to 0
		else
			trim_code = ours->force_code + 3;		//1 to 4			
	}
	else if (ours->force_code != -99)
	{
		mdb.SetStatusDialogHasOKButton(TRUE);
		mdb.SetDialogTopMessage("** tOVL Force Code is outside of Range ****");
		mdb.SetDialogBottomMessage("**** Force a valid trim code or set it to -99 for auto trim ****");
		RunModalDialog(&mdb);	//Output error message
		return;			// Force trim code outside of Range. Disable trimming 
	}
	
	////if (!TRIM_ENABLE && !Force_Trim)
	////	return;

// ********** Trim Anti-fuses **************//
	Powerup_to_trim_primary();

	previous_addr =0;
	trim_addr     =0;

	if(trim_code & 1)		//L1 
	{
		trim_addr = gP_AF_Start_Addr_tOVL;		
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		//ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		//wait.delay_10_us(g_readTime_p);		
		//IZtr_tOVL1 = D_dvi->measure_average(5);
		//ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		//wait.delay_10_us(3);

		Trim_Anti_fuse_primary(&IZtr_tOVL1);
		if(g_ReTrim_P && IZtr_tOVL1 < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_tOVL1);		
		}

		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_tOVL1,	IZtr_tOVL1,		set_fail_bin,	POWER_MILLI);	

	}
	if(trim_code & 2)		//L2
	{
		trim_addr = gP_AF_Start_Addr_tOVL + 1;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		//ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		//wait.delay_10_us(g_readTime_p);		
		//IZtr_tOVL2 = D_dvi->measure_average(5);
		//ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		//wait.delay_10_us(3);

		Trim_Anti_fuse_primary(&IZtr_tOVL2);
		if(g_ReTrim_P && IZtr_tOVL2 < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_tOVL2);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_tOVL2,	IZtr_tOVL2,		set_fail_bin,	POWER_MILLI);	
	}
	if(trim_code & 4)		//L3
	{
		trim_addr = gP_AF_Start_Addr_tOVL + 2;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		//ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		//wait.delay_10_us(g_readTime_p);		
		//IZtr_tOVLsign = D_dvi->measure_average(5);
		//ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		//wait.delay_10_us(3);

		Trim_Anti_fuse_primary(&IZtr_tOVLsign);
		if(g_ReTrim_P && IZtr_tOVLsign < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_tOVLsign);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_tOVLsign,	IZtr_tOVLsign,		set_fail_bin,	POWER_MILLI);	
	}
	
	////if(trim_code >= 4)
	////	plot_code = (trim_code -3)*-1;
	////else 
	////	plot_code = trim_code;
	if(trim_code >= 4)
		plot_code = (trim_code -3);
	else 
		plot_code = -trim_code;

	g_tOVL_exp = trim_weight[trim_code];	// Save value for post-trim change calculation 

	// Power down from trim
	Powerdown_from_trim_primary();


	//Datalog
	PiDatalog(func, A_gtOVL_TARGET,trim_target,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_tOVL_code,	plot_code,				set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_tOVL_table,	trim_weight[trim_code],	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_tOVL_needed,trim_needed,			set_fail_bin,	POWER_UNIT);	

	if(gDEBUG==1)
	printf("Function tOVL_Trim Done\n");

}
