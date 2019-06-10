//==============================================================================
// ILIM_Trim.cpp (User function)
// 
//    void ILIM_Trim_user_init(test_function& func)
//    void ILIM_Trim(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "ILIM_Trim.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ILIM_Trim_user_init(test_function& func)
{
	ILIM_Trim_params *ours;
    ours = (ILIM_Trim_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ILIM_Trim(test_function& func)
{
    // The two lines below must be the first two in the function.
    ILIM_Trim_params *ours;
    ours = (ILIM_Trim_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 11;
	Func_name = "ILIM_Trim";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_ILIM_Trim,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if(ours->force_code == -99)							//REMARK AT PRODUCTION
	{													//REMARK AT PRODUCTION
		if (OPCODE != 4200 || TRIM_ENABLE == 0)
			return;
	}													//REMARK AT PRODUCTION

	//Temporary set to 1
	gHandShake_PASS = 1;
	// If Handshake wasn't done properly, I2f calculation will be base on primary fosc, which is wrong. 
	if (!gHandShake_PASS)
		return;

	//float ILIM_target_adj_P=0.0,
	float IZtr_L1_P=0.0,
		  IZtr_L2_P=0.0,
		  IZtr_L3_P=0.0,
		  IZtr_L4_P=0.0,
		  IZtr_ZF_P=0.0,
		  IZtr_ILIM_Plus30pct_P=0.0;

	float trim_weight[16]={0};		// Double of what's needed
	float trim_target=0.0,trim_exp=0.0;
	float trim_needed =0.0, trim_result =0.0;
	float delta=0;
	int	  trim_code=0, plot_code;
	int	  Force_Trim =0;

	int   previous_addr=0, trim_addr=0, clks=0;
	int	  i=0;

	////OLD Trim Weights
	////						 DN   ,   UP,   UP,    UP
	//// L4,L3,L2,L1		-40.0%, +20.0%, +10%, +5%		Trim Code	Plot Code
	//trim_weight[0] = 0.0;		// Code: 0000					0			 0
	//trim_weight[1] = 5.0;		// Code: 0001					1			+1
	//trim_weight[2] = 10.0;		// Code: 0010					2			+2
	//trim_weight[3] = 15.0;		// Code: 0011					3			+3
	//trim_weight[4] = 20.0;		// Code: 0100					4			+4
	//trim_weight[5] = 25.0;		// Code: 0101					5			+5
	//trim_weight[6] = 30.0;		// Code: 0110					6			+6
	//trim_weight[7] = 35.0;		// Code: 0111					7			+7
	//trim_weight[8] = -5.0;		// Code: 1000					8			-1
	//trim_weight[9] = -10.0;		// Code: 1001					9			-2
	//trim_weight[10] = -15.0;	// Code: 1010					10			-3
	//trim_weight[11] = -20.0;	// Code: 1011					11			-4
	//trim_weight[12] = -25.0;	// Code: 1100					12			-5
	//trim_weight[13] = -30.0;	// Code: 1101					13			-6
	//trim_weight[14] = -35.0;	// Code: 1110					14			-7
	//trim_weight[15] = -40.0;	// Code: 1111					15			-8

	//New Trim Weights

	//						 DN   ,   UP,   UP,    UP
		// L4,L3,L2,L1		-40.0%, +20.0%, +10%, +5%		Trim Code	Plot Code
		trim_weight[0] = 0.0;		// Code: 0000					0			 0
		trim_weight[1] = 4.87;		// Code: 0001					1			+1
		trim_weight[2] = 9.57;		// Code: 0010					2			+2
		trim_weight[3] = 13.47;		// Code: 0011					3			+3
		trim_weight[4] = 17.82;		// Code: 0100					4			+4
		trim_weight[5] = 25.0;		// Code: 0101					5			+5
		trim_weight[6] = 30.0;		// Code: 0110					6			+6
		trim_weight[7] = 35.0;		// Code: 0111					7			+7
		trim_weight[8] = -4.65;		// Code: 1000					8			-1
		trim_weight[9] = -9.29;		// Code: 1001					9			-2
		trim_weight[10] = -13.88;	// Code: 1010					10			-3
		trim_weight[11] = -18.34;	// Code: 1011					11			-4
		trim_weight[12] = -22.90;	// Code: 1100					12			-5
		trim_weight[13] = -28.34;	// Code: 1101					13			-6
		trim_weight[14] = -35.0;	// Code: 1110					14			-7
		trim_weight[15] = -40.0;	// Code: 1111					15			-8

	//Below table is based on a few devices
	//////						 DN   ,   UP,   UP,    UP
	////// L4,L3,L2,L1		-40.0%, +20.0%, +10%, +5%		Trim Code	Plot Code
	////trim_weight[0] = 0.0;		// Code: 0000					0			 0
	////trim_weight[1] = 5.0;		// Code: 0001					1			+1
	////trim_weight[2] = 10.0;		// Code: 0010					2			+2
	////trim_weight[3] = 15.0;		// Code: 0011					3			+3
	////trim_weight[4] = 20.0;		// Code: 0100					4			+4
	////trim_weight[5] = 25.0;		// Code: 0101					5			+5
	////trim_weight[6] = 30.0;		// Code: 0110					6			+6
	////trim_weight[7] = 35.0;		// Code: 0111					7			+7
	////trim_weight[8] = -3.2;		// Code: 1000					8			-1
	////trim_weight[9] = -10.0;		// Code: 1001					9			-2
	////trim_weight[10] = -15.0;	// Code: 1010					10			-3
	////trim_weight[11] = -20.0;	// Code: 1011					11			-4
	////trim_weight[12] = -22.0;	// Code: 1100					12			-5
	////trim_weight[13] = -30.0;	// Code: 1101					13			-6
	////trim_weight[14] = -35.0;	// Code: 1110					14			-7
	////trim_weight[15] = -40.0;	// Code: 1111					15			-8

	//Require Fosc_post_S and ILIM_pt_P to determine target and how much we want to trim.
	if (ours->force_code == -99 || ours->force_ZF_P_code == -99)
	{
		if(gFOSC_pt_S !=0)//Correct statemnet, Uncomment this statment for final release
		//if(gFOSC_pt_S ==0)//Temporary- Remove this statement after secondary frequency code is merged
			trim_target = gILIM_TARGET_S;	
		else
		{
			trim_target = 999.0;
			PiDatalog(func, A_gILIM_TARGET_S,gILIM_TARGET_S,			set_fail_bin,	POWER_MILLI);	
			return;
		}

		if(gILIM_pt_S !=0 && gILIM_pt_S < 990.0)
			trim_needed = 100.0 * ((trim_target / gILIM_pt_S) -1);	
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
	for(i =0; i<16 ;i++)			// i< 2^(#of bits)
	{
		trim_result =  gILIM_pt_S*(trim_weight[i]/100.0 +1);
		if(fabs(trim_result - trim_target) < delta)
		{
			trim_code = i;
			delta = fabs(trim_result - trim_target);
		}
	}
	
	// Force Trim Code
	//////if(ours->force_code >-8 && ours->force_code <=7)	//-8 to +7
	//////{
	//////	Force_Trim =1;
	//////	if(ours->force_code < 8)
	//////		trim_code = ours->force_code;
	//////	else
	//////		trim_code = (ours->force_code -7)*-1;				
	//////}
	if(ours->force_code >=-8 && ours->force_code <=7)	//-8 to +7
	{
		Force_Trim =1;
		if(ours->force_code >= 0)
			trim_code = ours->force_code;		//force_code is positive
		else
			trim_code = (ours->force_code -7)*-1;				
	}
	else if (ours->force_code != -99)
	{
		mdb.SetStatusDialogHasOKButton(TRUE);
		mdb.SetDialogTopMessage("** ILIM Force Code is outside of Range ****");
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
	if(trim_code & 1)		//L1
	{
		trim_addr = gP_AF_Start_Addr_ILIM; //12
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		////////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		//////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		//////wait.delay_10_us(g_readTime_p);		
		//////IZtr_L1_P = D_dvi->measure_average(5);
		//////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		//////wait.delay_10_us(3);
		Trim_Anti_fuse_primary(&IZtr_L1_P);
		if(g_ReTrim_P && IZtr_L1_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_L1_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_L1_P,	IZtr_L1_P,		set_fail_bin,	POWER_MILLI);	
	}
	if(trim_code & 2)		//L2
	{
		trim_addr = gP_AF_Start_Addr_ILIM + 1; 
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_L2_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);
		Trim_Anti_fuse_primary(&IZtr_L2_P);
		if(g_ReTrim_P && IZtr_L2_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_L2_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_L2_P,	IZtr_L2_P,		set_fail_bin,	POWER_MILLI);	
	}
	if(trim_code & 4)		//L3
	{
		trim_addr = gP_AF_Start_Addr_ILIM + 2; 
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_L3_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);
		Trim_Anti_fuse_primary(&IZtr_L3_P);
		if(g_ReTrim_P && IZtr_L3_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_L3_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_L3_P,	IZtr_L3_P,		set_fail_bin,	POWER_MILLI);	
	}
	if(trim_code & 8)		//C4, ILIM4
	{
		trim_addr = gP_AF_Start_Addr_ILIM + 3; 
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_L4_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);
		Trim_Anti_fuse_primary(&IZtr_L4_P);
		if(g_ReTrim_P && IZtr_L4_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_L4_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_L4_P,	IZtr_L4_P,		set_fail_bin,	POWER_MILLI);	
	}

	// Trim Primary Zfinal 	
	if(ours->force_ZF_P_code == -99 || ours->force_ZF_P_code == 1)
	{
		trim_addr = gP_AF_Start_Addr_ZF; //48
//		trim_addr = 50;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_ZF_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);
		Trim_Anti_fuse_primary(&IZtr_ZF_P);
		if(g_ReTrim_P && IZtr_ZF_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_ZF_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_ZF_P,	IZtr_ZF_P,			set_fail_bin,	POWER_MILLI);	
	}

	if(trim_code >= 8)
		plot_code = (trim_code -7)*-1;
	else 
		plot_code = trim_code;

	gILIM_exp_S = trim_weight[trim_code];	// Save value for post-trim change calculation 

	// Power down from trim
	Powerdown_from_trim_primary();
	Power_Down_Everything();
	Open_All_Relays();

	//Datalog
	float LSL = gILIM_TARGET_S * 0.9;
	float USL = gILIM_TARGET_S * 1.1;
	func.dlog->set_test_no(A_gILIM_TARGET_S + 1);
	func.dlog->set_min_limit_value(LSL);
	func.dlog->set_max_limit_value(USL);
	PiDatalog(func, A_gILIM_TARGET_S,gILIM_TARGET_S,			set_fail_bin,	POWER_MILLI);	
	//PiDatalog(func, A_ILIM_target_adj_P,trim_target,		set_fail_bin,	POWER_MILLI);	

	PiDatalog(func, A_ILIM_code_P,	plot_code,				set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_ILIM_table_P,	trim_weight[trim_code],	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_ILIM_needed_P,trim_needed,			set_fail_bin,	POWER_UNIT);	

	if(gDEBUG==1)
	printf("Function ILIM_Trim Done\n");

}
