//==============================================================================
// IOV_Trim.cpp (User function)
// 
//    void IOV_Trim_user_init(test_function& func)
//    void IOV_Trim(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IOV_Trim.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IOV_Trim_user_init(test_function& func)
{
	IOV_Trim_params *ours;
    ours = (IOV_Trim_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IOV_Trim(test_function& func)
{
    // The two lines below must be the first two in the function.
    IOV_Trim_params *ours;
    ours = (IOV_Trim_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 11;

	Func_name = "IOV_Trim";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IOV_Trim,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if(ours->force_code == -99)							//REMARK AT PRODUCTION
	{													//REMARK AT PRODUCTION
		if (OPCODE != 4200 || TRIM_ENABLE == 0)
		return;
	}													//REMARK AT PRODUCTION

	float IZtr_IOV1_P		=0.0,
		  IZtr_IOV2_P		=0.0,
		  IZtr_IOV3_P		=0.0,
		  IZtr_IOV4_P		=0.0,
		  IZtr_IOV5_P		=0.0,
		  IZtr_iov_Off_P	=0.0;

	float trim_weight[32]={0};		
	float trim_target=0.0,trim_exp=0.0;
	float trim_needed =0.0, trim_result =0.0;
	float delta=0;
	int	  trim_code=0, plot_code;
	int	  Force_Trim =0;

	int   previous_addr=0, trim_addr=0, clks=0;
	int	  i=0;
Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
//	//////
	//pulse.do_pulse();
/*****************************************************************************
/*************************** Bitweight Table *********************************
/*****************************************************************************
		(Active)										(Don't use)
	IOV5, IOV4, IOV3, IOV2, IOV1				IOV5, IOV4, IOV3, IOV2, IOV1				
	----------------------------				----------------------------
	sign  -8%	-4%	  -2%   -1%					sign  +8%	+4%	  +2%   +1%	
	----------------------------				----------------------------

	Code(Bin)	Code(Int)	Bitweight(%)		Code(Bin)	Code(Int)	Bitweight(%)		
							Plot_code(ForceCode)						Plot_code
	------------------------------------		------------------------------------		
	00000		=0			=0					00000		=0			=0					
	00001		=1			=-1					00001		=1			=1					
	00010		=2			=-2					00010		=2			=2					
	00011		=3			=-3					00011		=3			=3					
	00100		=4			=-4					00100		=4			=4					
	00101		=5			=-5					00101		=5			=5					
	00110		=6			=-6					00110		=6			=6					
	00111		=7			=-7					00111		=7			=7					
	01000		=8			=-8					01000		=8			=8					
	01001		=9			=-9					01001		=9			=9					
	01010		=10			=-10				01010		=10			=10					
	01011		=11			=-11				01011		=11			=11					
	01100		=12			=-12				01100		=12			=12					
	01101		=13			=-13				01101		=13			=13					
	01110		=14			=-14				01110		=14			=14					
	01111		=15			=-15				01111		=15			=15					
	10000		=16			=1					10000		=16			=-1					
	10001		=17			=2					10001		=17			=-2					
	10010		=18			=3					10010		=18			=-3					
	10011		=19			=4					10011		=19			=-4					
	10100		=20			=5					10100		=20			=-5					
	10101		=21			=6					10101		=21			=-6					
	10110		=22			=7					10110		=22			=-7					
	10111		=23			=8					10111		=23			=-8					
	11000		=24			=9					11000		=24			=-9					
	11001		=25			=10					11001		=25			=-10					
	11010		=26			=11					11010		=26			=-11						
	11011		=27			=12					11011		=27			=-12				
	11100		=28			=13					11100		=28			=-13			
	11101		=29			=14					11101		=29			=-14				
	11110		=30			=15					11110		=30			=-15				
	11111		=31			=16					11111		=31			=-16				
*****************************************************************************/
	trim_weight[0] = 0;	
	trim_weight[1] = -1.38;		//-1;	
	trim_weight[2] = -2.56;		//-2;	
	trim_weight[3] = -3.65;		//-3;	
	trim_weight[4] = -4.58;		//-4;	
	trim_weight[5] = -5.66;		//-5;	
	trim_weight[6] = -6.8;		//-6;	
	trim_weight[7] = -7.87;		//-7;	
	trim_weight[8] = -8.88;		//-8;	
	trim_weight[9] = -9.94;		//-9;	
	trim_weight[10] = -11.09;	//-10;
	trim_weight[11] = -12.14;	//-11;
	trim_weight[12] = -13.04;	//-12;
	trim_weight[13] = -14.09;	//-13;
	trim_weight[14] = -15.24;	//-14;
	trim_weight[15] = -16.31;	//-15;
	trim_weight[16] = 0.43;		//1;
	trim_weight[17] = 1.54;		//2;
	trim_weight[18] = 2.73;		//3;
	trim_weight[19] = 3.86;		//4;
	trim_weight[20] = 4.84;		//5;
	trim_weight[21] = 5.99;		//6;
	trim_weight[22] = 7.13;		//7;
	trim_weight[23] = 8.28;		//8;
	trim_weight[24] = 9.42;		//9;
	trim_weight[25] = 10.47;	//10;
	trim_weight[26] = 11.57;	//11;
	trim_weight[27] = 12.97;	//12;
	trim_weight[28] = 13.85;	//13;
	trim_weight[29] = 14.9;		//14;
	trim_weight[30] = 16.02;	//15;
	trim_weight[31] = 16;
	//trim_weight[30] = 16;
	//trim_weight[31] = 18;
	

	trim_target = giOV_plus_TARGET;

	/***************************************************************************************************************
	******************	Equation to use for calcuating iOV trim_needed => [(Pre/tgt) - 1] * 100				********
	****************************************************************************************************************
	Note that fabs[(tgt/Pre-1)*100] does not equal to fabs[(Pre/tgt-1)*100]
	
	i.e.  Pre = 124uA		Target = 115uA
	(tgt/Pre-1)*100 => -7.258%
	(Pre/tgt-1)*100 => +7.826%	(They are not equal to each other)

	iOV is design to work with (Pre/tgt -1)*100 formula 
	(It is the only parameter does this.  To make the trimweight make sense when we look at datalog, define the 
	 trimweight inversely instead so there won't be confusion.  Pre=124uA trim to Tgt=115 require -7.826% trim down)
	 So, trim_needed function will be [(Pre/tgt-1) * 100]*-1
	***************************************************************************************************************/

	if(giOV_plus_Pt_P >50e-6 && giOV_plus_Pt_P < 200e-6)	//only allow trim for iOV_pre in range from 50uA to 200uA
		trim_needed = ((giOV_plus_Pt_P / trim_target) -1)*100*-1;	
	else
	{
		trim_needed = 999.0;
		return;
	}

// ********** Determine Trim Code ****** //
	trim_code = 0;
	delta = 9.99e6; 

	// Auto Trim Code
	for(i =0; i<32 ;i++)			// i< 2^(#of bits)
	{
		trim_result =  giOV_plus_Pt_P / (1 - trim_weight[i]/100.0);
		//trim_result =  giOV_plus_Pt_P*(trim_weight[i]/100.0 +1);
		if(fabs(trim_result - trim_target) < delta)
		{
			trim_code = i;
			delta = fabs(trim_result - trim_target);
		}
	}
	
	// Force Trim Code
	if (ours->force_code >=-15 && ours->force_code <=16) //-15 to 16
	{
		Force_Trim =1;
		if(ours->force_code > 0)
			trim_code = ours->force_code + 15;
		else if(ours->force_code < 0)
			trim_code = ours->force_code * -1;				
		else
			trim_code = 0;
	}
	else if (ours->force_code != -99)
	{
		mdb.SetStatusDialogHasOKButton(TRUE);
		mdb.SetDialogTopMessage("** IOV- Force Code is outside of Range ****");
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
	if(trim_code & 1)		//IOV1
	{
		trim_addr = gP_AF_Start_Addr_IOV; //12
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_IOV1_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);

		Trim_Anti_fuse_primary(&IZtr_IOV1_P);
		if(g_ReTrim_P && IZtr_IOV1_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_IOV1_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_IOV1_P,	IZtr_IOV1_P,		set_fail_bin,	POWER_MILLI);	
	}
	if(trim_code & 2)		//IOV2
	{
		trim_addr = gP_AF_Start_Addr_IOV + 1; 
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_IOV2_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);

		Trim_Anti_fuse_primary(&IZtr_IOV2_P);
		if(g_ReTrim_P && IZtr_IOV2_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_IOV2_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_IOV2_P,	IZtr_IOV2_P,		set_fail_bin,	POWER_MILLI);	
	}
	if(trim_code & 4)		//IOV3
	{
		trim_addr = gP_AF_Start_Addr_IOV + 2; 
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_IOV3_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);

		Trim_Anti_fuse_primary(&IZtr_IOV3_P);
		if(g_ReTrim_P && IZtr_IOV3_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_IOV3_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_IOV3_P,	IZtr_IOV3_P,		set_fail_bin,	POWER_MILLI);	
	}
	if(trim_code & 8)		//IOV4
	{
		trim_addr = gP_AF_Start_Addr_IOV + 3; 
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_IOV4_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);

		Trim_Anti_fuse_primary(&IZtr_IOV4_P);
		if(g_ReTrim_P && IZtr_IOV4_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_IOV4_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_IOV4_P,	IZtr_IOV4_P,		set_fail_bin,	POWER_MILLI);	
	}	
	if(trim_code & 16)		//IOV5
	{
		trim_addr = gP_AF_Start_Addr_IOV + 4; 
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		//////Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		////wait.delay_10_us(g_readTime_p);		
		////IZtr_IOV5_P = D_dvi->measure_average(5);
		////ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		////wait.delay_10_us(3);

		Trim_Anti_fuse_primary(&IZtr_IOV5_P);
		if(g_ReTrim_P && IZtr_IOV5_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_IOV5_P);		
		}
		previous_addr =  trim_addr;

		//Datalog
		PiDatalog(func, A_IZtr_IOV5_P,	IZtr_IOV5_P,		set_fail_bin,	POWER_MILLI);	
	}

	////if(trim_code >= 16)
	////	plot_code = (trim_code -15)*-1;
	////else 
	////	plot_code = trim_code;
	if(trim_code >= 16)
		plot_code = (trim_code -15);
	else 
		plot_code = -trim_code;

	giOV_plus_exp = trim_weight[trim_code];	// Save value for post-trim change calculation 


	if(gTrim_iov_Off_P)
	{
		trim_addr = gP_AF_Start_Addr_IuvIov_Disable;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);

		Trim_Anti_fuse_primary(&IZtr_iov_Off_P);
		if(g_ReTrim_P && IZtr_iov_Off_P < 1e-3 )
		{
			Powerdown_from_trim_primary();
			VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
			REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

			Powerup_to_trim_primary_Retrim();
			DDD_Clock_UV_Antifuse(clks);
			Trim_Anti_fuse_primary_Retrim(&IZtr_iov_Off_P);		
		}
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, A_IZtr_iov_Off_P,	IZtr_iov_Off_P,		set_fail_bin,	POWER_MILLI);	
	}

	// Power down from trim
	Powerdown_from_trim_primary();
	Power_Down_Everything();
	Open_All_Relays();


	//Datalog
	PiDatalog(func, A_giOV_plus_TARGET,			trim_target,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_iOV_plus_code_P,		plot_code,				set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_iOV_plus_table_P,	trim_weight[trim_code],	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_iOV_plus_needed_P,	trim_needed,			set_fail_bin,	POWER_UNIT);	

	if(gDEBUG==1)
	printf("Function IOV_Trim Done\n");

}
