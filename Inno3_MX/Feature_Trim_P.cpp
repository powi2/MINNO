//==============================================================================
// Feature_Trim_P.cpp (User function)
// 
//    void Feature_Trim_P_user_init(test_function& func)
//    void Feature_Trim_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)

#include "Feature_Trim_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Feature_Trim_P_user_init(test_function& func)
{
	Feature_Trim_P_params *ours;
    ours = (Feature_Trim_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Feature_Trim_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Feature_Trim_P_params *ours;
    ours = (Feature_Trim_P_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 11;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	Func_name = "Fosc_Trim_P";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Feature_Trim_P,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if(ours->force_code == -99)							//REMARK AT PRODUCTION
	{													//REMARK AT PRODUCTION
		if (OPCODE != 4200 || TRIM_ENABLE == 0)
			return;
	}													//REMARK AT PRODUCTION

	double	Feature_Code_P	=0;
	//float	IZtr_iov_Off_P	=0,

	float	IZtr_iuvMinus_P	=0,	//iUV+ @10uA
			IZtr_uvDelay_P	=0,
			IZtr_Loff_AR_P	=0,
			IZtr_DisablAR_P	=0,
			IZtr_didtComp_P	=0,
			IZtr_OT_Hys_P	=0,
			IZtr_LoffwOT_P	=0,
			IZtr_iLselOff_P	=0,
			IZtr_iLStdIcr_P	=0,
			IZtr_iL20dn_P	=0,
			IZtr_iL20up_P	=0,
			IZtr_SAM_P		=0,
			IZtr_OTP1_P		=0,
			IZtr_OTP2_P		=0,
			IZtr_OTP3_P		=0,
			IZtr_SDS_OFF_P	=0,
			IZtr_Rcv1_P		=0,
			IZtr_Rcv2_P		=0,
			IZtr_RcvSign_P	=0,
			IZtr_drvSize1_P	=0,
			IZtr_drvSize2_P	=0,
			IZtr_drvSize3_P	=0,
			IZtr_drvSize4_P	=0,
			IZtr_RsenseUp_P	=0,
			IZtr_vxAdj1_P	=0,
			IZtr_vxAdj2_P	=0,
			IZtr_vxAdj3_P	=0,
			IZtr_vxAdj4_P	=0,
			IZtr_vxAdj5_P	=0,
			IZtr_iLRatio1_P	=0,
			IZtr_iLRatio2_P	=0,
			IZtr_iLRatio3_P	=0,
			IZtr_iLRatio4_P	=0,
			IZtr_iLTC1_P	=0,
			IZtr_iLTC2_P	=0,
			IZtr_iLTC3_P	=0,
			IZtr_iLTC4_P	=0,
			IZtr_AR_req_P	=0;

	//bool	Trim_iov_Off_P	=false,
	bool	Trim_iuvMinus_P	=false,
			Trim_uvDelay_P	=false,
			Trim_Loff_AR_P	=false,
			Trim_DisablAR_P	=false,
			Trim_didtComp_P	=false,
			Trim_OT_Hys_P	=false,
			Trim_LoffwOT_P	=false,
			Trim_iLselOff_P	=false,
			Trim_iLStdIcr_P	=false,
			Trim_iL20dn_P	=false,
			Trim_iL20up_P	=false,
			Trim_SAM_P		=false,
			Trim_OTP1_P		=false,
			Trim_OTP2_P		=false,
			Trim_OTP3_P		=false,
			Trim_SDS_OFF_P	=false,
			Trim_Rcv1_P		=false,
			Trim_Rcv2_P		=false,
			Trim_RcvSign_P	=false,
			Trim_drvSize1_P	=false,
			Trim_drvSize2_P	=false,
			Trim_drvSize3_P	=false,
			Trim_drvSize4_P	=false,
			Trim_RsenseUp_P	=false,
			Trim_vxAdj1_P	=false,
			Trim_vxAdj2_P	=false,
			Trim_vxAdj3_P	=false,
			Trim_vxAdj4_P	=false,
			Trim_vxAdj5_P	=false,
			Trim_iLRatio1_P	=false,
			Trim_iLRatio2_P	=false,
			Trim_iLRatio3_P	=false,
			Trim_iLRatio4_P	=false,
			Trim_iLTC1_P	=false,
			Trim_iLTC2_P	=false,
			Trim_iLTC3_P	=false,
			Trim_iLTC4_P	=false,
			Trim_AR_req_P	=false;

	//Trim_iov_Off_P	=gTrim_iov_Off_P;
	Trim_iuvMinus_P	=gTrim_iuvMinus_P;
	Trim_uvDelay_P	=gTrim_uvDelay_P;
	Trim_Loff_AR_P	=gTrim_Loff_AR_P;
	Trim_DisablAR_P	=gTrim_DisablAR_P;
	Trim_didtComp_P	=gTrim_didtComp_P;
	Trim_OT_Hys_P	=gTrim_OT_Hys_P;
	Trim_LoffwOT_P	=gTrim_LoffwOT_P;
	Trim_iLselOff_P	=gTrim_iLselOff_P;
	Trim_iLStdIcr_P	=gTrim_iLStdIcr_P;
	Trim_iL20dn_P	=gTrim_iL20dn_P;
	Trim_iL20up_P	=gTrim_iL20up_P;
	Trim_SAM_P		=gTrim_SAM_P;
	//Trim_SDS_OFF_P	=1;					//	temporary
	Trim_SDS_OFF_P	=gTrim_SDS_OFF_P;
	Trim_RsenseUp_P	=gTrim_RsenseUp_P;
	Trim_AR_req_P	=gTrim_AR_req;


	//Determine OTP trim bits,			3 bits
	if((gTrim_OTP_P & 1) == 1)		Trim_OTP1_P = 1;
	if((gTrim_OTP_P & 2) == 2)		Trim_OTP2_P = 1;
	if((gTrim_OTP_P & 4) == 4)		Trim_OTP3_P = 1;
	//Determine Rcv trim bits,			2 bits
	if((gTrim_Rcv_P & 1) == 1)		Trim_Rcv1_P = 1;
	if((gTrim_Rcv_P & 2) == 2)		Trim_Rcv2_P = 1;
	//Determine Driver Size trim bits,	4 bits
	if((gTrim_drvSize_P & 1) == 1)	Trim_drvSize1_P = 1;
	if((gTrim_drvSize_P & 2) == 2)	Trim_drvSize2_P = 1;
	if((gTrim_drvSize_P & 4) == 4)	Trim_drvSize3_P = 1;
	if((gTrim_drvSize_P & 8) == 8)	Trim_drvSize4_P = 1;
	//Trim_drvSize1_P = 1;	//bit36
	//Trim_drvSize2_P = 0;
	//Trim_drvSize3_P = 0;
	//Trim_drvSize4_P = 0;
	//Determine vxAdj trim bits,		5 bits
	if((gTrim_vxAdj_P & 1) == 1)	Trim_vxAdj1_P = 1;
	if((gTrim_vxAdj_P & 2) == 2)	Trim_vxAdj2_P = 1;
	if((gTrim_vxAdj_P & 4) == 4)	Trim_vxAdj3_P = 1;
	if((gTrim_vxAdj_P & 8) == 8)	Trim_vxAdj4_P = 1;
	if((gTrim_vxAdj_P & 16) == 16)	Trim_vxAdj5_P = 1;
			
	//Determine ILIM Ratio trim bits,	4 bits
	if((gTrim_iLRatio_P & 1) == 1)	Trim_iLRatio1_P = 1;
	if((gTrim_iLRatio_P & 2) == 2)	Trim_iLRatio2_P = 1;
	if((gTrim_iLRatio_P & 4) == 4)	Trim_iLRatio3_P = 1;
	if((gTrim_iLRatio_P & 8) == 8)	Trim_iLRatio4_P = 1;
			
	//Determine ILIM TC trim bits,		4 bits
	if((gTrim_iLTC_P & 1) == 1)		Trim_iLTC1_P = 1;
	if((gTrim_iLTC_P & 2) == 2)		Trim_iLTC2_P = 1;
	if((gTrim_iLTC_P & 4) == 4)		Trim_iLTC3_P = 1;
	if((gTrim_iLTC_P & 8) == 8)		Trim_iLTC4_P = 1;
				

	int	  trim_code=0, plot_code=0;
	int	  Force_Trim = 0;
	int   previous_addr=0, trim_addr=0, clks=0;
	int	  i=0;

	//Trim Features for Primary (See OTS/TestPlan)
	Powerup_to_trim_primary();

	previous_addr =0;
	trim_addr     =0;

	//Forced trim: Clock through Primary and trim anti-fuses
	if(ours->force_code != -99)
	{
		if(ours->force_code == 0)
			goto END_OF_FUNC;

		trim_addr = ours->force_code;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iuvMinus_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iuvMinus_P,	IZtr_iuvMinus_P,		set_fail_bin,	POWER_MILLI);

		goto END_OF_FUNC;
	}

	//////if(Trim_iov_Off_P)
	//////{
	//////	trim_addr = gP_AF_Start_Addr_IuvIov_Disable;
	//////	clks = trim_addr - previous_addr;
	//////	DDD_Clock_UV_Antifuse(clks);
	//////	Trim_Anti_fuse_primary(&IZtr_iov_Off_P);
	//////	previous_addr =  trim_addr;

	//////	// Datalog
	//////	PiDatalog(func, A_IZtr_iov_Off_P,	IZtr_iov_Off_P,		set_fail_bin,	POWER_MILLI);	
	//////}

	//Individual Feature Bits
	if(Trim_iuvMinus_P)
	{
		trim_addr = gP_AF_Start_Addr_Iuv_10uA;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iuvMinus_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iuvMinus_P,	IZtr_iuvMinus_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_uvDelay_P)
	{
		trim_addr = gP_AF_Start_Addr_UV_400ms_dly;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_uvDelay_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_uvDelay_P,	IZtr_uvDelay_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_Loff_AR_P)
	{
		trim_addr = gP_AF_Start_Addr_LatchOFF_aft_AR;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_Loff_AR_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_Loff_AR_P,	IZtr_Loff_AR_P,		set_fail_bin,	POWER_MILLI);

	}
	if(Trim_DisablAR_P)
	{
		trim_addr = gP_AF_Start_Addr_Disable_AR;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_DisablAR_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_DisablAR_P,	IZtr_DisablAR_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_didtComp_P)
	{
		trim_addr = gP_AF_Start_Addr_didt_comp;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_didtComp_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_didtComp_P,	IZtr_didtComp_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_OT_Hys_P)
	{
		trim_addr = gP_AF_Start_Addr_OT_Hys_30C;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_OT_Hys_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_OT_Hys_P,	IZtr_OT_Hys_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_LoffwOT_P)
	{
		trim_addr = gP_AF_Start_Addr_LatchOFF_w_OT;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_LoffwOT_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_LoffwOT_P,	IZtr_LoffwOT_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_iLselOff_P)
	{
//		trim_addr = 4;
		trim_addr = gP_AF_Start_Addr_Disable_ILIM_Select;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLselOff_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLselOff_P,	IZtr_iLselOff_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_iLStdIcr_P)
	{
		trim_addr = gP_AF_Start_Addr_Select_ILIM_Incr;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLStdIcr_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLStdIcr_P,	IZtr_iLStdIcr_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_iL20dn_P)
	{
		trim_addr = gP_AF_Start_Addr_minus_20pct_ILIM;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iL20dn_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iL20dn_P,	IZtr_iL20dn_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_iL20up_P)
	{
		trim_addr = gP_AF_Start_Addr_plus_20pct_ILIM;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iL20up_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iL20up_P,	IZtr_iL20up_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_SAM_P)
	{
		trim_addr = gP_AF_Start_Addr_Samsung_Mode;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_SAM_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_SAM_P,	IZtr_SAM_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_OTP1_P)
	{
		trim_addr = gP_AF_Start_Addr_OTP;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_OTP1_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_OTP1_P,	IZtr_OTP1_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_OTP2_P)
	{
		trim_addr = gP_AF_Start_Addr_OTP +1;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_OTP2_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_OTP2_P,	IZtr_OTP2_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_OTP3_P)
	{
		trim_addr = gP_AF_Start_Addr_OTP +2;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_OTP3_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_OTP3_P,	IZtr_OTP3_P,		set_fail_bin,	POWER_MILLI);
	}	
	if(Trim_SDS_OFF_P)
	{
		trim_addr = gP_AF_Start_Addr_SDS_OFF;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_SDS_OFF_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_SDS_OFF_P,	IZtr_SDS_OFF_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_Rcv1_P)
	{
		trim_addr = gP_AF_Start_Addr_Rcv;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_Rcv1_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_Rcv1_P,	IZtr_Rcv1_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_Rcv2_P)
	{
		trim_addr = gP_AF_Start_Addr_Rcv +1;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_Rcv2_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_Rcv2_P,	IZtr_Rcv2_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_RcvSign_P)
	{
		trim_addr = gP_AF_Start_Addr_Rcv +2;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_RcvSign_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_RcvSign_P,	IZtr_RcvSign_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_drvSize1_P)
	{
		trim_addr = gP_AF_Start_Addr_Driver_Size;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_drvSize1_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_drvSize1_P,	IZtr_drvSize1_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_drvSize2_P)
	{
		trim_addr = gP_AF_Start_Addr_Driver_Size +1;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_drvSize2_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_drvSize2_P,	IZtr_drvSize2_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_drvSize3_P)
	{
		trim_addr = gP_AF_Start_Addr_Driver_Size +2;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_drvSize3_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_drvSize3_P,	IZtr_drvSize3_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_drvSize4_P)
	{
		trim_addr = gP_AF_Start_Addr_Driver_Size +3;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_drvSize4_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_drvSize4_P,	IZtr_drvSize4_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_RsenseUp_P)
	{
		trim_addr = gP_AF_Start_Addr_Rsense_up;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_RsenseUp_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_RsenseUp_P,	IZtr_RsenseUp_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_vxAdj1_P)
	{
		trim_addr = gP_AF_Start_Addr_Vx_adjust;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_vxAdj1_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_vxAdj1_P,	IZtr_vxAdj1_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_vxAdj2_P)
	{
		trim_addr = gP_AF_Start_Addr_Vx_adjust+1;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_vxAdj2_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_vxAdj2_P,	IZtr_vxAdj2_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_vxAdj3_P)
	{
		trim_addr = gP_AF_Start_Addr_Vx_adjust+2;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_vxAdj3_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_vxAdj3_P,	IZtr_vxAdj3_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_vxAdj4_P)
	{
		trim_addr = gP_AF_Start_Addr_Vx_adjust+3;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_vxAdj4_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_vxAdj4_P,	IZtr_vxAdj4_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_vxAdj5_P)
	{
		trim_addr = gP_AF_Start_Addr_Vx_adjust+4;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_vxAdj5_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_vxAdj5_P,	IZtr_vxAdj5_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_iLRatio1_P)
	{
		trim_addr = gP_AF_Start_Addr_ILIM_Ratio;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLRatio1_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLRatio1_P,	IZtr_iLRatio1_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_iLRatio2_P)
	{
		trim_addr = gP_AF_Start_Addr_ILIM_Ratio+1;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLRatio2_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLRatio2_P,	IZtr_iLRatio2_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_iLRatio3_P)
	{
		trim_addr = gP_AF_Start_Addr_ILIM_Ratio+2;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLRatio3_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLRatio3_P,	IZtr_iLRatio3_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_iLRatio4_P)
	{
		trim_addr = gP_AF_Start_Addr_ILIM_Ratio+3;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLRatio4_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLRatio4_P,	IZtr_iLRatio4_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_iLTC1_P)
	//if(1)
	{
		trim_addr = gP_AF_Start_Addr_ILIM_TC;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLTC1_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLTC1_P,	IZtr_iLTC1_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_iLTC2_P)
	{
		trim_addr = gP_AF_Start_Addr_ILIM_TC+1;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLTC2_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLTC2_P,	IZtr_iLTC2_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_iLTC3_P)
	//if(1)
	{
		trim_addr = gP_AF_Start_Addr_ILIM_TC+2;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLTC3_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLTC3_P,	IZtr_iLTC3_P,		set_fail_bin,	POWER_MILLI);
	}
	if(Trim_iLTC4_P)
	//if(1)
	{
		trim_addr = gP_AF_Start_Addr_ILIM_TC+3;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_iLTC4_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_iLTC4_P,	IZtr_iLTC4_P,		set_fail_bin,	POWER_MILLI);
	}

	if(Trim_AR_req_P)
	//if(1)
	{
		trim_addr = gP_AF_Start_Addr_AR_Request;
		clks = trim_addr - previous_addr;
		DDD_Clock_UV_Antifuse(clks);
		Trim_Anti_fuse_primary(&IZtr_AR_req_P);
		previous_addr =  trim_addr;

		// Datalog
		PiDatalog(func, 	A_IZtr_AR_req_P,	IZtr_AR_req_P,		set_fail_bin,	POWER_MILLI);
	}

END_OF_FUNC:;

	// Power down from trim
	Powerdown_from_trim_primary();
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
	REQ_ovi->set_voltage(REQ_ch,     0.0, 		RANGE_2_V);	// OVI_1_2

}
