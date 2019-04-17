//==============================================================================
// Fosc_Trim_P.cpp (User function)
// 
//    void Fosc_Trim_P_user_init(test_function& func)
//    void Fosc_Trim_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_Trim_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_Trim_P_user_init(test_function& func)
{
	Fosc_Trim_P_params *ours;
    ours = (Fosc_Trim_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_Trim_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_Trim_P_params *ours;
    ours = (Fosc_Trim_P_params *)func.params;
	
	int set_fail_bin = ours->fail_bin;

	set_fail_bin = 11;

	Func_name = "Fosc_Trim_P";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Fosc_Trim_P,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if(ours->force_code == -99)							//REMARK AT PRODUCTION
	{													//REMARK AT PRODUCTION
		if (OPCODE != 4200 || TRIM_ENABLE == 0)
			return;
	}													//REMARK AT PRODUCTION

	float	IZtr_F1_P1_P =0.0,
			IZtr_F2_P2_P =0.0,
			IZtr_F3_M4_P =0.0;

	float trim_weight[8]={0};
	float trim_target=0.0,trim_exp=0.0;
	float trim_needed =0.0, trim_result =0.0;
	float delta;
	int	  trim_code=0, plot_code;
	int	  Force_Trim = 0;
	int   previous_addr, trim_addr, clks;
	int	  i;
	//							   DN, UP, UP	
								// F3, F2, F1		Trim Code	Plot Code
	trim_weight[0] = 0.0;		// Code: 000			0			 0
	trim_weight[1] = 4.84;		// Code: 001			1			+1
	trim_weight[2] = 9.61;		// Code: 010			2			+2	
	trim_weight[3] = 14.56;		// Code: 011			3			+3
	trim_weight[4] = -4.77;		// Code: 100			4			-1
	trim_weight[5] = -9.6;		// Code: 101			5			-2
	trim_weight[6] = -15;		// Code: 110			6			-3
	trim_weight[7] = -20; 		// Code: 111			7			-4

	trim_target = gFOSC_TARGET_P;

	if(gFosc_pt_P >10e3 && gFosc_pt_P < 200e3)	//only allow trimming if primary switching at greater than 10kHz
		trim_needed = 100.0 * ((trim_target / gFosc_pt_P) -1);	
	else
	{
		trim_needed = 999.0;
		return;
	}


// ********** Determine Trim Code ****** //
	trim_code = 0;
	delta = 9.99e6; 

	// Auto Trim Code
	for(i =0; i<8 ;i++)			// i< 2^(#of bits)
	{
		trim_result =  gFosc_pt_P*(trim_weight[i]/100.0 +1);
		if(fabs(trim_result - trim_target) < delta)
		{
			trim_code = i;
			delta = fabs(trim_result - trim_target);
		}
	}
	
	// Force Trim Code
	if(ours->force_code >=-4 && ours->force_code <=3)	// Allow force code from -4 to +3
	{
		Force_Trim = 1;
		////if(ours->force_code < 4)
		////	trim_code = ours->force_code;
		////else
		////	trim_code = (ours->force_code -3)*-1;				
		if(ours->force_code >=0)
			trim_code = ours->force_code;
		else
			trim_code = (ours->force_code -3)*-1;				
	}
	else if (ours->force_code != -99)
	{
		mdb.SetStatusDialogHasOKButton(TRUE);
		mdb.SetDialogTopMessage("** FOSC_P Force Code is outside of Range ****");
		mdb.SetDialogBottomMessage("**** Force a valid trim code or set it to -99 for auto trim ****");
		RunModalDialog(&mdb);	//Output error message
		return;			// Force trim code outside of Range. Disable trimming 
	}

	if (!TRIM_ENABLE && !Force_Trim)
		return;

// ********** Trim Anti-fuses **************//
	Powerup_to_trim_primary();

	previous_addr =0;
	trim_addr     =0;
	if(trim_code & 1)
	{
		trim_addr = gP_AF_Start_Addr_Freq;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_F1_P1_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);
		Trim_Anti_fuse_primary(&IZtr_F1_P1_P);
		wait.delay_10_us(10);
		if(g_ReTrim_P && IZtr_F1_P1_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			wait.delay_10_us(10);
			Trim_Anti_fuse_primary_Retrim(&IZtr_F1_P1_P);		
		}

		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_F1_P1_P,	IZtr_F1_P1_P,		set_fail_bin,	POWER_MILLI);	
	}
	if(trim_code & 2)
	{
		trim_addr = gP_AF_Start_Addr_Freq + 1;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_F2_P2_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);
		Trim_Anti_fuse_primary(&IZtr_F2_P2_P);
		if(g_ReTrim_P && IZtr_F2_P2_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			wait.delay_10_us(10);
			Trim_Anti_fuse_primary_Retrim(&IZtr_F2_P2_P);		
		}

		previous_addr =  trim_addr;
		
		// Datalog
		PiDatalog(func, A_IZtr_F2_P2_P,	IZtr_F2_P2_P,		set_fail_bin,	POWER_MILLI);	
	}
	if(trim_code & 4)
	{
		trim_addr = gP_AF_Start_Addr_Freq + 2;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_F3_M4_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);
		Trim_Anti_fuse_primary(&IZtr_F3_M4_P);
		if(g_ReTrim_P && IZtr_F3_M4_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			wait.delay_10_us(10);
			Trim_Anti_fuse_primary_Retrim(&IZtr_F3_M4_P);		
		}

		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_F3_M4_P,	IZtr_F3_M4_P,		set_fail_bin,	POWER_MILLI);	
	}
	

	if(trim_code >= 4)
		plot_code = (trim_code -3)*-1;
	else 
		plot_code = trim_code;

	gFOSC_exp_P = trim_weight[trim_code];	// Save value for post-trim change calculation 

	// Power down from trim
	Powerdown_from_trim_primary();


	//Datalog
	PiDatalog(func, A_gFOSC_TARGET_P,trim_target,			set_fail_bin,	POWER_KILO);	
	PiDatalog(func, A_Fosc_code_P,	plot_code,				set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Fosc_table_P,	trim_weight[trim_code],	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Fosc_needed_P,trim_needed,			set_fail_bin,	POWER_UNIT);	

	if(gDEBUG)
	printf("Function Fosc_Trim_PDone\n");

}
