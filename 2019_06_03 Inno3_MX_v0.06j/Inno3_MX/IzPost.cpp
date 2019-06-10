//==============================================================================
// IzPost.cpp (User function)
// 
//    void IzPost_user_init(test_function& func)
//    void IzPost(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "IzPost.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IzPost_user_init(test_function& func)
{
	IzPost_params *ours;
    ours = (IzPost_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IzPost(test_function& func)
{
    // The two lines below must be the first two in the function.
    IzPost_params *ours;
    ours = (IzPost_params *)func.params;

	int set_fail_bin = ours->fail_bin;


	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug  rlb


	Func_name = "IzPost";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IzPost,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	float	IZ_iov1_p=0.0,		IZ_iov2_p=0.0,		IZ_iov3_p=0.0,		IZ_iov4_p=0.0,
			IZ_iovSign_p=0.0,
			IZ_iL1_p=0.0,		IZ_iL2_p=0.0,		IZ_iL3_p=0.0,		IZ_iLsign_p=0.0,
			IZ_tmax1_p=0.0,		IZ_tmax2_p=0.0,		IZ_tmaxSign_p=0.0,
			IZ_f1_p=0.0,		IZ_f2_p=0.0,		IZ_fSign_p=0.0,
			IZ_iov_Off_p=0.0, 
			IZ_iuvMinus_p=0.0,
			IZ_uvDelay_p=0.0,
			IZ_Loff_AR_p=0.0,
			IZ_DisablAR_p=0.0,
			IZ_didtComp_p=0.0,
			IZ_OT_Hys_p=0.0,
			IZ_LoffwOT_p=0.0,
			IZ_iLselOff_p=0.0,	IZ_iLStdIcr_p=0.0,
			IZ_iL20dn_p=0.0,	IZ_iL20up_p=0.0,
			IZ_SAM_p=0.0,
			IZ_OTP1_p=0.0,		IZ_OTP2_p=0.0,		IZ_OTP3_p=0.0,
			IZ_VpinCtri_p=0.0,	IZ_SDS_OFF_p=0.0,
			IZ_Rcv1_p=0.0,		IZ_Rcv2_p=0.0,		IZ_RcvSign_p=0.0,
			IZ_drvSize1_p=0.0,	IZ_drvSize2_p=0.0,	IZ_drvSize3_p=0.0,	IZ_drvSize4_p=0.0,
			IZ_RsenseUp_p=0.0,
			IZ_vxAdj1_p=0.0,	IZ_vxAdj2_p=0.0,	IZ_vxAdj3_p=0.0,	IZ_vxAdj4_p=0.0,		IZ_vxAdj5_p=0.0,
			IZ_iLRatio1_p=0.0,	IZ_iLRatio2_p=0.0,	IZ_iLRatio3_p=0.0,	IZ_iLRatio4_p=0.0,
			IZ_iLTC1_p=0.0,		IZ_iLTC2_p=0.0,		IZ_iLTC3_p=0.0,		IZ_iLTC4_p=0.0,
			IZ_ARreq_p=0.0,
			IZ_ZF_p=0.0;


	float	IZ_F1_S=0.0,		IZ_F2_S=0.0,		IZ_F3_S=0.0,		IZ_F4_S=0.0,
			IZ_PK1spdLd_S=0.0,	IZ_PK2_S=0.0,		IZ_PK3_S=0.0,
			IZ_Rnw5_S=0.0,		IZ_Rnw6_S=0.0,
			IZ_Rnw1_S=0.0,		IZ_Rnw2_S=0.0,		IZ_Rnw3_S=0.0,		IZ_Rnw4_S=0.0,
			IZ_FWC2_S=0.0,		IZ_NoFWC100mV_S=0.0,
			IZ_Cap1_S=0.0,		IZ_Cap2_S=0.0,		IZ_Cap3_S=0.0,
			IZ_PKdig1_S=0.0,	IZ_PKdig2_S=0.0,	IZ_PKdig3_S=0.0,	IZ_PKdig4_S=0.0,
			IZ_SRth1_S=0.0,		IZ_SRth2_S=0.0,		IZ_SRth3_S=0.0,		IZ_SRth4_S=0.0,
			IZ_V1_S=0.0,		IZ_V2_S=0.0,		IZ_V3_S=0.0,		IZ_V4_S=0.0,		IZ_V5_S=0.0,		IZ_V6_S=0.0,
			IZ_IintTC1_S=0.0,	IZ_IintTC2_S=0.0,	IZ_IintTC3_S=0.0,	IZ_IintTC4_S=0.0,
			IZ_DOPL_S=0.0,
			IZ_REQlow_S=0.0,
			IZ_XFWPK_S=0.0;

	float iAFp_th =0.0,
		  iAFs_th =0.0; 

	float iAF_array_p[100] = {0};
	float iAF_array_s[100] = {0};

	int addr =0, Total_Addr_Count_p=0, Total_Addr_Count_s=0;
	int i=0, Trimmed=0, readTime=0;

	int	  Feature_Check_Pri=0, Feature_Check_Sec=0;
	int	  Test_Escape =0;

	
	//Reinit global variable
	for(i=0; i<100; i++)
	{
		gIZ_AF_post_P[i] = 0;
		gIZ_AF_post_S[i] = 0;
	}

	//Initialize read global variables
	gRead_PK_S		=0;
	gRead_CP_S		=0;
	gRead_PS_S		=0;
	gRead_TF_S		=0;
	gRead_AR_S		=0;
	gRead_SCEN_S	=0;
	gRead_CBEN_S	=0;
	gRead_DsoftEn_S	=0;
	gRead_DOPL_S	=0;
	gRead_OVLO_S	=0;
	gRead_VR_S		=0;
	gRead_CR_S		=0;
	gRead_XFWPK_S	=0;
	gRead_Spare_S	=0;


	if(LB_Rev >= 5||g_TurretCB)
	{
		readTime	= 10;		//x*10us => 200us if readTime = 20
	}
	else
	{
		readTime	= 3;		//x*10us => 200us if readTime = 20
	}
	iAFp_th		= 200e-6;	//Threshold use to determine if Primary   is trimmed or not.  If trimmed, iAFp ~= 600uA
	iAFs_th		= 30e-6;	//Threshold use to determine if Secondary is trimmed or not.  If trimmed, iAFs ~= 180uA

	dvi_13->open_relay(BUS_SENSE1);
	dvi_13->open_relay(BUS_FORCE1);
	mux_14->open_relay(MUX_3_BUS3);

	//Setup Vout to connect to DDD7_4 and have DDD7_4 toggle to stay LOW to start with
	VO_dvi->open_relay(CONN_FORCE0);
	VO_dvi->open_relay(CONN_SENSE0);

	VPIN_ovi->disconnect(VPIN_ch);	// Vpin does not use ovi-1-1 for Iz function
	//delay(3);

	// Initialize DDD
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(4.4);		// Will immediately change to this level upon execution
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);

	Close_relay(K2);	// Primary:		Connect DVI11_0 to Drain	pin
	Close_relay(K12);	// Primary:		Connect DDD7_1	to Vpin(UV)	pin
	Close_relay(K18);	// Secondary:	Connect DVI11_1 to FW		pin
	Close_relay(K27);	// Secondary:	Connect DDD7_4	to Vout		pin (Inno4)
	delay(4);			// 4 ms delay is necessary to wait for relays to settle down before powering up BPP pin to avoid mis-clocking

	// Primary AF currents
	Powerup_Primary_in_Testmode(gWrite_Mode_ReadAF);
	D_dvi->set_meas_mode(D_ch,			DVI_MEASURE_CURRENT);
	delay(5);			// Critical do not remove!

	for (i = 1; i <= gTotal_Addr_Count_P; i++)
	{
		DDD_Clock_UV_Antifuse(1);		// Vpin(UV) clock through all AF links one by one
		////Require more wait time for the first AF link
		//if(i==1)	
		//{
		//	if(LB_Rev>=5 || g_TurretCB)
		//	{
		//		wait.delay_10_us(200);
		//	}
		//	else
		//	{
		//		wait.delay_10_us(70);//70
		//	}
		//}

		//Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		DDD_Wait_Pattern_End(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);
		//wait.delay_10_us(readTime);

		iAF_array_p[i] = D_dvi->measure_average(5);
		gIZ_AF_post_P[i] = iAF_array_p[i];

		ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		DDD_Wait_Pattern_End(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);
		//wait.delay_10_us(100);  //HL : 1ms seems to reduce the repeatability issue.
	}

	//Secondary AF currents
	Powerup_Secondary_in_Testmode(gWrite_Mode_ReadAF, gTrim_Voltage, gVread_AF_secondary);

	ddd_7->ddd_set_lo_level(0.1);		
	ddd_7->ddd_set_hi_level(4.0);		// This is to make sure Vout is not higher than VBPS
	wait.delay_10_us(10);

	//BPS stay at 4V for reading AF links
	//BPS_dvi->set_voltage(BPS_ch, 4.4,	VOLT_10_RANGE);	//4.4V to match Bench measurement.
	//MUST USE VPLUS + 50mV, else read negative current on devices with vPlus higher than 4.4V
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final,	VOLT_10_RANGE);	//DE complain vBPS(4V)_120uA iAF_NoZF is too high (suspect Bench vBPS=4.4V_88uA)
	wait.delay_10_us(5);

	for (i = 1; i <= gTotal_Addr_Count_S; i++)	// Secondary: First clock count at address 3 for 1.6 silicon, and address 8 for 1.5 silicon
	{
		// Clock
		DDD_Clock_Vout_Antifuse(1);		// Vout clk

		//Quiescent current 
		if (i == 1)
		{
			FW_dvi->set_voltage(FW_ch, gVread_AF_secondary, 	RANGE_5_V);	// DVI_11_1
			FW_dvi->set_current(FW_ch, 300e-6,					RANGE_300_UA);
			FW_dvi->set_meas_mode(FW_ch,						DVI_MEASURE_CURRENT);
			wait.delay_10_us(100);
			iAF_array_s[0] = FW_dvi->measure_average(5);
		}

		//Raise REQ voltage to 4V for duration of anti-fuse reading
		REQ_ovi->set_voltage(REQ_ch, 4.0, 		VOLT_5_RANGE);	// OVI_1_2 (revB silicon)
		wait.delay_10_us(15);	

		iAF_array_s[i] = FW_dvi->measure_average(5);

		//Bring REQ voltage back down to 0 after reading
		REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
		wait.delay_10_us(15);

		// Secondary Anti-fuses are read from BPS pin. BPS voltage is about 4.V. Some antifuses can't be read properly
		// at this voltage. Subtract out Quiescent current from the anti-fuse current to make sure anti-fuses are trimmed properly
		iAF_array_s[i]  -=iAF_array_s[0];
		gIZ_AF_post_S[i] = iAF_array_s[i];
	}

	//Power down
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(3);
	D_dvi->set_voltage(D_ch, 0.0, 		VOLT_10_RANGE);	// DVI_11_0
	FW_dvi->set_voltage(FW_ch, 0.0, 	VOLT_10_RANGE);	// DVI_11_1
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	BPS_dvi->set_voltage(BPS_ch, 0.0,	VOLT_10_RANGE);	
	wait.delay_10_us(20);

	BPP_ovi->connect(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	Open_relay(K2);
	Open_relay(K18);
	Open_relay(K12);
	Open_relay(K27);
	Open_relay(K26);

	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);

	Power_Down_Everything();
	Open_All_Relays();

	// Feature Checks
	//** Antifuse current results
	// Primary
    IZ_iov1_p		=iAF_array_p[1];
	IZ_iov2_p		=iAF_array_p[2];
	IZ_iov3_p		=iAF_array_p[3]; 
	IZ_iov4_p		=iAF_array_p[4]; 
	IZ_iovSign_p	=iAF_array_p[5]; 
	IZ_iL1_p		=iAF_array_p[6];
	IZ_iL2_p		=iAF_array_p[7];
	IZ_iL3_p		=iAF_array_p[8]; 
	IZ_iLsign_p		=iAF_array_p[9]; 
	IZ_tmax1_p		=iAF_array_p[10];
	IZ_tmax2_p		=iAF_array_p[11];
	IZ_tmaxSign_p	=iAF_array_p[12]; 
	IZ_f1_p			=iAF_array_p[13];  
	IZ_f2_p			=iAF_array_p[14];
	IZ_fSign_p		=iAF_array_p[15];
	IZ_iov_Off_p	=iAF_array_p[16];
	IZ_iuvMinus_p	=iAF_array_p[17];
	IZ_uvDelay_p	=iAF_array_p[18];
	IZ_Loff_AR_p	=iAF_array_p[19];
	IZ_DisablAR_p	=iAF_array_p[20];
	IZ_didtComp_p	=iAF_array_p[21];
	IZ_OT_Hys_p		=iAF_array_p[22];
	IZ_LoffwOT_p	=iAF_array_p[23];
	IZ_iLselOff_p	=iAF_array_p[24];
	IZ_iLStdIcr_p	=iAF_array_p[25];
	IZ_iL20dn_p		=iAF_array_p[26];
	IZ_iL20up_p		=iAF_array_p[27];
	IZ_SAM_p		=iAF_array_p[28];	//Samsung
	IZ_OTP1_p		=iAF_array_p[29];
	IZ_OTP2_p		=iAF_array_p[30];
	IZ_OTP3_p		=iAF_array_p[31];
	IZ_VpinCtri_p	=iAF_array_p[32];
	IZ_Rcv1_p		=iAF_array_p[33];
	IZ_Rcv2_p		=iAF_array_p[34];
	IZ_RcvSign_p	=iAF_array_p[35];
	IZ_drvSize1_p	=iAF_array_p[36];
	IZ_drvSize2_p	=iAF_array_p[37];
	IZ_drvSize3_p	=iAF_array_p[38];
	IZ_drvSize4_p	=iAF_array_p[39];
	IZ_RsenseUp_p	=iAF_array_p[40];
	IZ_vxAdj1_p		=iAF_array_p[41];
	IZ_vxAdj2_p		=iAF_array_p[42];
	IZ_vxAdj3_p		=iAF_array_p[43];
	IZ_vxAdj4_p		=iAF_array_p[44];
	IZ_vxAdj5_p		=iAF_array_p[45];
	IZ_iLRatio1_p	=iAF_array_p[46];
	IZ_iLRatio2_p	=iAF_array_p[47];
	IZ_iLRatio3_p	=iAF_array_p[48];
	IZ_iLRatio4_p	=iAF_array_p[49];
	IZ_iLTC1_p		=iAF_array_p[50];
	IZ_iLTC2_p		=iAF_array_p[51];
	IZ_iLTC3_p		=iAF_array_p[52];
	IZ_iLTC4_p		=iAF_array_p[53];
	//IZ_ZF_p			=iAF_array_p[54];

	if(gSiliconRev_P == revA_P)
		IZ_ZF_p		=iAF_array_p[54];
	if(gSiliconRev_P >= revB_P)
	{
		IZ_ARreq_p	=iAF_array_p[54];
		IZ_ZF_p		=iAF_array_p[55];
	}

	/*************************************************************************************************/
	// Primary Feature Checks
	/*************************************************************************************************/
	if((IZ_iov_Off_p>iAFp_th && gTrim_iov_Off_P) || (IZ_iov_Off_p<iAFp_th && !gTrim_iov_Off_P))
		Feature_Check_Pri = 1;
	else
		Feature_Check_Pri = 16;	// bit 16.
	if(Feature_Check_Pri == 1) 
		if(((IZ_iuvMinus_p>iAFp_th && gTrim_iuvMinus_P) || (IZ_iuvMinus_p<iAFp_th && !gTrim_iuvMinus_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 17;	// bit 17.
	if(Feature_Check_Pri == 1) 
		if(((IZ_uvDelay_p>iAFp_th && gTrim_uvDelay_P) || (IZ_uvDelay_p<iAFp_th && !gTrim_uvDelay_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 18;	// bit 18.
	if(Feature_Check_Pri == 1) 
		if(((IZ_Loff_AR_p>iAFp_th && gTrim_Loff_AR_P) || (IZ_Loff_AR_p<iAFp_th && !gTrim_Loff_AR_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 19;	// bit 19.
	if(Feature_Check_Pri == 1) 
		if(((IZ_DisablAR_p>iAFp_th && gTrim_DisablAR_P) || (IZ_DisablAR_p<iAFp_th && !gTrim_DisablAR_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 20;	// bit 20.
	if(Feature_Check_Pri == 1) 
		if(((IZ_didtComp_p>iAFp_th && gTrim_didtComp_P) || (IZ_didtComp_p<iAFp_th && !gTrim_didtComp_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 21;	// bit 21.
	if(Feature_Check_Pri == 1) 
		if(((IZ_OT_Hys_p>iAFp_th && gTrim_OT_Hys_P) ||(IZ_OT_Hys_p<iAFp_th && !gTrim_OT_Hys_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 22;	// bit 22.
	if(Feature_Check_Pri == 1) 
		if(((IZ_LoffwOT_p>iAFp_th && gTrim_LoffwOT_P) || (IZ_LoffwOT_p<iAFp_th && !gTrim_LoffwOT_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 23;	// bit 23.
	if(Feature_Check_Pri == 1) 
		if(((IZ_iLselOff_p>iAFp_th && gTrim_iLselOff_P) || (IZ_iLselOff_p<iAFp_th && !gTrim_iLselOff_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 24;	// bit 24.
	if(Feature_Check_Pri == 1) 
		if(((IZ_iLStdIcr_p>iAFp_th && gTrim_iLStdIcr_P) || (IZ_iLStdIcr_p<iAFp_th && !gTrim_iLStdIcr_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 25;	// bit 25.
	if(Feature_Check_Pri == 1) 
		if(((IZ_iL20dn_p>iAFp_th && gTrim_iL20dn_P) || (IZ_iL20dn_p<iAFp_th && !gTrim_iL20dn_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 26;	// bit 26.
	if(Feature_Check_Pri == 1) 
		if(((IZ_iL20up_p>iAFp_th && gTrim_iL20up_P) || (IZ_iL20up_p<iAFp_th && !gTrim_iL20up_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 27;	// bit 27.
	if(Feature_Check_Pri == 1) 
		if(((IZ_SAM_p>iAFp_th && gTrim_SAM_P) || (IZ_SAM_p<iAFp_th && !gTrim_SAM_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 28;	// bit 28.
	if(Feature_Check_Pri == 1) 
		if(((IZ_SDS_OFF_p>iAFp_th && gTrim_SDS_OFF_P) || (IZ_SDS_OFF_p<iAFp_th && !gTrim_SDS_OFF_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 32;	// bit 32.
	if(Feature_Check_Pri == 1) 
		if(((IZ_ARreq_p>iAFp_th && gTrim_AR_req_P) || (IZ_ARreq_p<iAFp_th && !gTrim_AR_req_P)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 54;	// bit 54.


	//** Datalog
	// Primary
	if (gGaN)
	{
		// GaN
		PiDatalog(func, A_IZ_iov1_p,		iAF_array_p[gP_AF_Start_Addr_IOV],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iov2_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iov3_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iov4_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 3],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iovSign_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 4],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iL1_p,			iAF_array_p[gP_AF_Start_Addr_ILIM],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iL2_p,			iAF_array_p[gP_AF_Start_Addr_ILIM + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iL3_p,			iAF_array_p[gP_AF_Start_Addr_ILIM + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLsign_p,		iAF_array_p[gP_AF_Start_Addr_ILIM + 3],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_tOVL1_p,		iAF_array_p[gP_AF_Start_Addr_tOVL],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_tOVL2_p,		iAF_array_p[gP_AF_Start_Addr_tOVL + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_tOVLSign_p,	iAF_array_p[gP_AF_Start_Addr_tOVL + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_f1_p,			iAF_array_p[gP_AF_Start_Addr_Freq],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_f2_p,			iAF_array_p[gP_AF_Start_Addr_Freq + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_fSign_p,		iAF_array_p[gP_AF_Start_Addr_Freq + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iov_Off_p,		iAF_array_p[gP_AF_Start_Addr_IuvIov_Disable],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iuvMinus_p,	iAF_array_p[gP_AF_Start_Addr_Iuv_10uA],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_uvDelay_p,		iAF_array_p[gP_AF_Start_Addr_UV_400ms_dly],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_Loff_AR_p,		iAF_array_p[gP_AF_Start_Addr_LatchOFF_aft_AR],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_OTP1_p,		iAF_array_p[gP_AF_Start_Addr_OTP],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_OTP2_p,		iAF_array_p[gP_AF_Start_Addr_OTP + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_OTP3_p,		iAF_array_p[gP_AF_Start_Addr_OTP + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_LoffwOT_p,		iAF_array_p[gP_AF_Start_Addr_LatchOFF_w_OT],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLselOff_p,	iAF_array_p[gP_AF_Start_Addr_Disable_ILIM_Select],	set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLStdIcr_p,	iAF_array_p[gP_AF_Start_Addr_Select_ILIM_Incr],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_OT_Hys_p,		iAF_array_p[gP_AF_Start_Addr_OT_Hys_30C],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_DisablAR_p,	iAF_array_p[gP_AF_Start_Addr_Disable_AR],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_SAM_p,			iAF_array_p[gP_AF_Start_Addr_Samsung_Mode],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSTSel1_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Ton],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSTSel2_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Ton + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSTtr1_p,		iAF_array_p[gP_AF_Start_Addr_ZVS_Trim],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSTtr2_p,		iAF_array_p[gP_AF_Start_Addr_ZVS_Trim + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_Rcv1_p,		iAF_array_p[gP_AF_Start_Addr_Rcv],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_Rcv2_p,		iAF_array_p[gP_AF_Start_Addr_Rcv + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_RcvSign_p,		iAF_array_p[gP_AF_Start_Addr_Rcv + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSon_p,		iAF_array_p[gP_AF_Start_Addr_ZVSon],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_UV1_p,			iAF_array_p[gP_AF_Start_Addr_UV],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_UV2_p,			iAF_array_p[gP_AF_Start_Addr_UV + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSdlm20_p,	iAF_array_p[gP_AF_Start_Addr_ZVSdelaym20],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_IlimLEB_p,		iAF_array_p[gP_AF_Start_Addr_IlimLEB],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_vpinIref_p,	iAF_array_p[gP_AF_Start_Addr_VpinCTRL_iREF20pct],	set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSDly1_p,		iAF_array_p[gP_AF_Start_Addr_ZVS_Delay],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSDly2_p,		iAF_array_p[gP_AF_Start_Addr_ZVS_Delay + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSDly3_p,		iAF_array_p[gP_AF_Start_Addr_ZVS_Delay + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZVSDly14_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Delay + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_SDS30pct_p,	iAF_array_p[gP_AF_Start_Addr_SDSpct],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_SDS60pct_p,	iAF_array_p[gP_AF_Start_Addr_SDSpct + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLRatio1_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLRatio2_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLTC1_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLTC2_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLTC3_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 2],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLTC4_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 3],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ARreq_p,		iAF_array_p[gP_AF_Start_Addr_AR_Request],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZF_p,			iAF_array_p[gP_AF_Start_Addr_ZF],					set_fail_bin,	POWER_MICRO);
	}
	else
	{
		// DLM
		PiDatalog(func, A_IZ_iov1_p,		iAF_array_p[gP_AF_Start_Addr_IOV],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iov2_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iov3_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iov4_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 3],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iovSign_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 4],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iL1_p,			iAF_array_p[gP_AF_Start_Addr_ILIM],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iL2_p,			iAF_array_p[gP_AF_Start_Addr_ILIM + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iL3_p,			iAF_array_p[gP_AF_Start_Addr_ILIM + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLsign_p,		iAF_array_p[gP_AF_Start_Addr_ILIM + 3],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_tOVL1_p,		iAF_array_p[gP_AF_Start_Addr_tOVL],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_tOVL2_p,		iAF_array_p[gP_AF_Start_Addr_tOVL + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_tOVLSign_p,	iAF_array_p[gP_AF_Start_Addr_tOVL + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_f1_p,			iAF_array_p[gP_AF_Start_Addr_Freq],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_f2_p,			iAF_array_p[gP_AF_Start_Addr_Freq + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_fSign_p,		iAF_array_p[gP_AF_Start_Addr_Freq + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iov_Off_p,		iAF_array_p[gP_AF_Start_Addr_IuvIov_Disable],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iuvMinus_p,	iAF_array_p[gP_AF_Start_Addr_Iuv_10uA],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_uvDelay_p,		iAF_array_p[gP_AF_Start_Addr_UV_400ms_dly],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_Loff_AR_p,		iAF_array_p[gP_AF_Start_Addr_LatchOFF_aft_AR],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_DisablAR_p,	iAF_array_p[gP_AF_Start_Addr_Disable_AR],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_didtComp_p,	iAF_array_p[gP_AF_Start_Addr_didt_comp],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_OT_Hys_p,		iAF_array_p[gP_AF_Start_Addr_OT_Hys_30C],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_LoffwOT_p,		iAF_array_p[gP_AF_Start_Addr_LatchOFF_w_OT],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLselOff_p,	iAF_array_p[gP_AF_Start_Addr_Disable_ILIM_Select],	set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLStdIcr_p,	iAF_array_p[gP_AF_Start_Addr_Select_ILIM_Incr],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iL20dn_p,		iAF_array_p[gP_AF_Start_Addr_minus_20pct_ILIM],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iL20up_p,		iAF_array_p[gP_AF_Start_Addr_plus_20pct_ILIM],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_SAM_p,			iAF_array_p[gP_AF_Start_Addr_Samsung_Mode],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_OTP1_p,		iAF_array_p[gP_AF_Start_Addr_OTP],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_OTP2_p,		iAF_array_p[gP_AF_Start_Addr_OTP + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_OTP3_p,		iAF_array_p[gP_AF_Start_Addr_OTP + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_SDS_OFF_p,		iAF_array_p[gP_AF_Start_Addr_SDS_OFF],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_Rcv1_p,		iAF_array_p[gP_AF_Start_Addr_Rcv],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_Rcv2_p,		iAF_array_p[gP_AF_Start_Addr_Rcv + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_RcvSign_p,		iAF_array_p[gP_AF_Start_Addr_Rcv + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_drvSize1_p,	iAF_array_p[gP_AF_Start_Addr_Driver_Size],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_drvSize2_p,	iAF_array_p[gP_AF_Start_Addr_Driver_Size + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_drvSize3_p,	iAF_array_p[gP_AF_Start_Addr_Driver_Size + 2],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_drvSize4_p,	iAF_array_p[gP_AF_Start_Addr_Driver_Size + 3],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_RsenseUp_p,	iAF_array_p[gP_AF_Start_Addr_Rsense_up],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_vxAdj1_p,		iAF_array_p[gP_AF_Start_Addr_Vx_adjust],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_vxAdj2_p,		iAF_array_p[gP_AF_Start_Addr_Vx_adjust + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_vxAdj3_p,		iAF_array_p[gP_AF_Start_Addr_Vx_adjust + 2],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_vxAdj4_p,		iAF_array_p[gP_AF_Start_Addr_Vx_adjust + 3],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_vxAdj5_p,		iAF_array_p[gP_AF_Start_Addr_Vx_adjust + 4],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLRatio1_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLRatio2_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLRatio3_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio + 2],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLRatio4_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio + 3],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLTC1_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLTC2_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLTC3_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 2],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_iLTC4_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 3],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ARreq_p,		iAF_array_p[gP_AF_Start_Addr_AR_Request],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_IZ_ZF_p,			iAF_array_p[gP_AF_Start_Addr_ZF],					set_fail_bin,	POWER_MICRO);
	}

	// Secondary
	PiDatalog(func, A_IZ_NoZ_s,			iAF_array_s[0],								set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_F1_s,			iAF_array_s[gFosc_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_F2_s,			iAF_array_s[gFosc_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_F3_s,			iAF_array_s[gFosc_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_F4_s,			iAF_array_s[gFosc_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_PK1spdLd_s,	iAF_array_s[gPK_ssSpeed_AF_Addr_Start],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_PK2_s,			iAF_array_s[gPK_ssSpeed_AF_Addr_Start + 1],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_PK3_s,			iAF_array_s[gPK_ssSpeed_AF_Addr_Start + 2],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Rnw5_s,		iAF_array_s[gRnw_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Rnw6_s,		iAF_array_s[gRnw_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Rnw1_s,		iAF_array_s[gRnwFine_AF_Addr_Start],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Rnw2_s,		iAF_array_s[gRnwFine_AF_Addr_Start + 1],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Rnw3_s,		iAF_array_s[gRnwFine_AF_Addr_Start + 2],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Rnw4_s,		iAF_array_s[gRnwFine_AF_Addr_Start + 3],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_FWC2_s,		iAF_array_s[gFWC2_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_NoFWC_s,		iAF_array_s[gNoFWC100mV_AF_Addr_Start],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Cap1_s,		iAF_array_s[gCap_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Cap2_s,		iAF_array_s[gCap_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Cap3_s,		iAF_array_s[gCap_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_PKdig1_s,		iAF_array_s[gPKdig_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_PKdig2_s,		iAF_array_s[gPKdig_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_PKdig3_s,		iAF_array_s[gPKdig_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_PKdig4_s,		iAF_array_s[gPKdig_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_SRth1_s,		iAF_array_s[gSRth_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_SRth2_s,		iAF_array_s[gSRth_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_SRth3_s,		iAF_array_s[gSRth_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_SRth4_s,		iAF_array_s[gSRth_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_Vshunt_s,		iAF_array_s[gVshunt_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_V1_s,			iAF_array_s[gVref_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_V2_s,			iAF_array_s[gVref_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_V3_s,			iAF_array_s[gVref_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_V4_s,			iAF_array_s[gVref_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_V5_s,			iAF_array_s[gVref_AF_Addr_Start + 4],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_V6_s,			iAF_array_s[gVref_AF_Addr_Start + 5],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_IintTC1_s,		iAF_array_s[gIintTC_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_IintTC2_s,		iAF_array_s[gIintTC_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_IintTC3_s,		iAF_array_s[gIintTC_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_IintTC4_s,		iAF_array_s[gIintTC_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_DOPL_s,		iAF_array_s[gDOPL_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_REQlow_s,		iAF_array_s[gREQlow_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_XFWPK_s,		iAF_array_s[gXFWPK_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_IZ_LO_dis_s,		iAF_array_s[gLO_dis_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);

	//PiDatalog(func, A_FeatureT_Chk_p,	Feature_Check_Pri,							set_fail_bin,	POWER_UNIT);	
	//PiDatalog(func, A_FeatureT_Chk_s,	Feature_Check_Sec,							set_fail_bin,	POWER_UNIT);	

	if(gDEBUG==1)
	printf("Function IZPost Done\n");
}
