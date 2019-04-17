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

	ovi_1->disconnect(OVI_CHANNEL_1);	//Vpin does not use ovi-1-1 for Iz function
	delay(3);

	// Initialize DDD
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);
	//BPP_ovi->disconnect(1);
	Close_relay(K2);	// Primary:		Connect DVI11_0 to Drain	pin
	Close_relay(K12);	// Primary:		Connect DDD7_1	to Vpin(UV)	pin
	Close_relay(K18);	// Secondary:	Connect DVI11_1 to FB		pin
//	Close_relay(K17);	// Secondary:	Connect DDD7_2	to FB		pin
	Close_relay(K27);	// Secondary:	Connect DDD7_4	to Vout		pin (Inno4)
	delay(4);			// 4 ms delay is necessary to wait for DDD to settle down before powering up BPP pin to avoid mis-clocking




	Powerup_Primary_in_Testmode(gWrite_Mode_ReadAF);
	D_dvi->set_meas_mode(D_ch,			DVI_MEASURE_CURRENT);
	delay(5);
	if(gSiliconRev_P == revA_P)		Total_Addr_Count_p = 54;
	if(gSiliconRev_P >= revB_P)		Total_Addr_Count_p = 55;

	for (i = 1; i<=Total_Addr_Count_p; i++)		
	{
		addr=i;
		DDD_Clock_UV_Antifuse(1);		// Vpin(UV) clock through all AF links one by one
				//Require more wait time for the first AF link
				if(i==1)	
				{
					if(LB_Rev>=5 || g_TurretCB)
					{
						wait.delay_10_us(200);
					}
					else
					{
						wait.delay_10_us(70);//70
					}
				}

		//Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
		wait.delay_10_us(readTime);		
		iAF_array_p[addr] = D_dvi->measure_average(5);
		gIZ_AF_post_P[addr] = iAF_array_p[addr];

		ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		//wait.delay_10_us(3);
		wait.delay_10_us(100);  //HL : 1ms seems to reduce the repeatability issue.
	}


	//Secondary AF currents
	if(g_TurretCB)
	{
		tmu_6->close_relay(TMU_EXT_DRV3);
		delay(2);
	}



	Powerup_Secondary_in_Testmode(gWrite_Mode_ReadAF, gTrim_Voltage, gVread_AF_secondary);

	//BPS stay at 4V for reading AF links
	//BPS_dvi->set_voltage(BPS_ch, 4.4,	VOLT_10_RANGE);	//4.4V to match Bench measurement.
	//MUST USE VPLUS + 50mV, else read negative current on devices with vPlus higher than 4.4V
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final,	VOLT_10_RANGE);	//DE complain vBPS(4V)_120uA iAF_NoZF is too high (suspect Bench vBPS=4.4V_88uA)
	wait.delay_10_us(5);

	if(gSiliconRev_S == revA_S)		Total_Addr_Count_s = 48;
	if(gSiliconRev_S >= revB_S)		Total_Addr_Count_s = 52;

	//FW_dvi->set_voltage(FW_ch, 0, 	VOLT_5_RANGE);	// DVI_11_1
	//FW_dvi->set_current(FW_ch, 300e-6,					RANGE_3_MA);
	//delay(1);

	for (i = 1; i<=Total_Addr_Count_s; i++)  //Secondary: First clock count at address 3 for 1.6 silicon, and address 8 for 1.5 silicon
	{
		addr = i;
		DDD_Clock_Vout_Antifuse(1);		// Vout clk

		//Quiescent current 
		if(i==1)
		{
			FW_dvi->set_voltage(FW_ch, gVread_AF_secondary, 	VOLT_10_RANGE);	// DVI_11_1
			FW_dvi->set_current(FW_ch, 300e-6,					RANGE_300_UA);
			FW_dvi->set_meas_mode(FW_ch,						DVI_MEASURE_CURRENT);
			wait.delay_10_us(50);
			iAF_array_s[0] = FW_dvi->measure_average(5);

				
		}

		//Raise FB voltage to 5V for duration of anti-fuse reading
//		REQ_ovi->set_voltage(REQ_ch, 5.0, 		VOLT_5_RANGE);	// OVI_1_2
		REQ_ovi->set_voltage(REQ_ch, 4.0, 		VOLT_5_RANGE);	// OVI_1_2 (revB silicon)
		wait.delay_10_us(15);	

		iAF_array_s[addr] = FW_dvi->measure_average(5);

		//if(gSiliconRev_S==revA_S)
		//{
			//Bring FB voltage back down to 0 after reading
			REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
			wait.delay_10_us(10);	 //HL changed from 50us to 100us.
		//}

		// Secondary Anti-fuses are read from BPS pin. BPS voltage is about 4.V. Some antifuses can't be read properly
		// at this voltage. Subtract out Quiescent current from the anti-fuse current to make sure anti-fuses are trimmed properly
		iAF_array_s[addr]  -=iAF_array_s[0];
		gIZ_AF_post_S[addr] = iAF_array_s[addr];
	}

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
		if(((IZ_ARreq_p>iAFp_th && gTrim_AR_req) || (IZ_ARreq_p<iAFp_th && !gTrim_AR_req)))
			Feature_Check_Pri = 1;
		else
			Feature_Check_Pri = 54;	// bit 54.




	// Secondary
	////if(gSiliconRev_S == revA_S)
	////{
	////	IZ_NoZ_s		=iAF_array_s[0]; 
	////	IZ_F1_s			=iAF_array_s[1];
	////	IZ_F2_s			=iAF_array_s[2];
	////	IZ_F3_s			=iAF_array_s[3];
	////	IZ_PK1_s		=iAF_array_s[4];
	////	//IZ_PK2_s		=iAF_array_s[5];
	////	//IZ_PK3_s		=iAF_array_s[6];
	////	IZ_CV1_s			=iAF_array_s[33];	//addr moved and replaced PK2 addr
	////	IZ_DVesrSlpAdj_s	=iAF_array_s[6];	//new		 and replaced PK3 addr
	////	IZ_CP1_s		=iAF_array_s[7];
	////	IZ_CP2_s		=iAF_array_s[8];
	////	IZ_CP3_s		=iAF_array_s[9];
	////	IZ_PS1_s		=iAF_array_s[10];
	////	IZ_PS2_s		=iAF_array_s[11];
	////	IZ_T1_s			=iAF_array_s[12];
	////	IZ_T2_s			=iAF_array_s[13];
	////	IZ_CC1_s		=iAF_array_s[14];
	////	IZ_CC2_s		=iAF_array_s[15];
	////	IZ_CC3_s		=iAF_array_s[16];
	////	IZ_CC4_s		=iAF_array_s[17];
	////	IZ_CC5_s		=iAF_array_s[18];
	////	IZ_CC6_s		=iAF_array_s[19];
	////	IZ_KP1_s		=iAF_array_s[20];
	////	IZ_KP2_s		=iAF_array_s[21];
	////	IZ_KP3_s		=iAF_array_s[22];
	////	IZ_SL1_s		=iAF_array_s[23];
	////	IZ_SL2_s		=iAF_array_s[24];
	////	IZ_SL3_s		=iAF_array_s[25];
	////	IZ_CS1_s		=iAF_array_s[26];
	////	IZ_CS2_s		=iAF_array_s[27];
	////	IZ_CS3_s		=iAF_array_s[28];
	////	IZ_CS4_s		=iAF_array_s[29];
	////	IZ_CB1_s		=iAF_array_s[30];
	////	IZ_CB2_s		=iAF_array_s[31];
	////	IZ_CB3_s		=iAF_array_s[32];
	////	//IZ_CV1_s		=iAF_array_s[33];
	////	IZ_CV2_s		=iAF_array_s[34];
	////	IZ_CV3_s		=iAF_array_s[35];
	////	IZ_CV4_s		=iAF_array_s[36];
	////	IZ_AR1_s		=iAF_array_s[37];
	////	IZ_AR2_s		=iAF_array_s[38];
	////	IZ_SCEN_s		=iAF_array_s[39];
	////	IZ_CBEN_s		=iAF_array_s[40];
	////	IZ_DsoftEn_s	=iAF_array_s[41];
	////	IZ_DOPL_s		=iAF_array_s[42];
	////	IZ_OVLO_s		=iAF_array_s[43];
	////	IZ_VR1_s		=iAF_array_s[44];
	////	IZ_CR_s			=iAF_array_s[45];
	////	IZ_XFWPK_s		=iAF_array_s[46];
	////	IZ_Spare_s		=iAF_array_s[47];
	////	IZ_ZF_s			=iAF_array_s[48];
	////}
	////else 
	if(gSiliconRev_S >= revB_S)
	{
		IZ_F1_S			= iAF_array_s[1];
		IZ_F2_S			= iAF_array_s[2];
		IZ_F3_S			= iAF_array_s[3];
		IZ_F4_S			= iAF_array_s[4];
		IZ_PK1spdLd_S	= iAF_array_s[5];
		IZ_PK2_S		= iAF_array_s[6];
		IZ_PK3_S		= iAF_array_s[7];
		IZ_Rnw5_S		= iAF_array_s[11];
		IZ_Rnw6_S		= iAF_array_s[12];
		IZ_Rnw1_S		= iAF_array_s[13];
		IZ_Rnw2_S		= iAF_array_s[14];
		IZ_Rnw3_S		= iAF_array_s[15];
		IZ_Rnw4_S		= iAF_array_s[16];
		IZ_FWC2_S		= iAF_array_s[17];
		IZ_NoFWC100mV_S	= iAF_array_s[18];
		IZ_Cap1_S		= iAF_array_s[19];
		IZ_Cap2_S		= iAF_array_s[20];
		IZ_Cap3_S		= iAF_array_s[21];
		IZ_PKdig1_S		= iAF_array_s[22];
		IZ_PKdig2_S		= iAF_array_s[23];
		IZ_PKdig3_S		= iAF_array_s[24];
		IZ_PKdig4_S		= iAF_array_s[25];
		IZ_SRth1_S		= iAF_array_s[26];
		IZ_SRth2_S		= iAF_array_s[27];
		IZ_SRth3_S		= iAF_array_s[28];
		IZ_SRth4_S		= iAF_array_s[29];
		IZ_V1_S			= iAF_array_s[32];
		IZ_V2_S			= iAF_array_s[33];
		IZ_V3_S			= iAF_array_s[34];
		IZ_V4_S			= iAF_array_s[35];
		IZ_V5_S			= iAF_array_s[36];
		IZ_V6_S			= iAF_array_s[37];
		IZ_IintTC1_S	= iAF_array_s[38];
		IZ_IintTC2_S	= iAF_array_s[39];
		IZ_IintTC3_S	= iAF_array_s[40];
		IZ_IintTC4_S	= iAF_array_s[41];
		IZ_DOPL_S		= iAF_array_s[42];
		IZ_REQlow_S		= iAF_array_s[43];
		IZ_XFWPK_S		= iAF_array_s[44];
	}

	//Power down
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(20);
	D_dvi->set_voltage(D_ch, 0.0, 		VOLT_10_RANGE);	// DVI_11_0
	FW_dvi->set_voltage(FW_ch, 0.0, 	VOLT_10_RANGE);	// DVI_11_1
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU,	RANGE_10_V);
	BPS_dvi->set_voltage(BPS_ch, 0.0,	VOLT_10_RANGE);	
	wait.delay_10_us(20);

	BPP_ovi->connect(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(20);
	Open_relay(K2);
	Open_relay(K18);
	Open_relay(K12);
//	Open_relay(K17);
	Open_relay(K27);

	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);

	Power_Down_Everything();
	Open_All_Relays();

//** Datalog
	// Primary
	PiDatalog(func, A_IZ_iov1_p,		IZ_iov1_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iov2_p,		IZ_iov2_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iov3_p,		IZ_iov3_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iov4_p,		IZ_iov4_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iovSign_p,		IZ_iovSign_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iL1_p,			IZ_iL1_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iL2_p,			IZ_iL2_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iL3_p,			IZ_iL3_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLsign_p,		IZ_iLsign_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_tmax1_p,		IZ_tmax1_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_tmax2_p,		IZ_tmax2_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_tmaxSign_p,	IZ_tmaxSign_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_f1_p,			IZ_f1_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_f2_p,			IZ_f2_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_fSign_p,		IZ_fSign_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iov_Off_p,		IZ_iov_Off_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iuvMinus_p,	IZ_iuvMinus_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_uvDelay_p,		IZ_uvDelay_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_Loff_AR_p,		IZ_Loff_AR_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_DisablAR_p,	IZ_DisablAR_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_didtComp_p,	IZ_didtComp_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_OT_Hys_p,		IZ_OT_Hys_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_LoffwOT_p,		IZ_LoffwOT_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLselOff_p,	IZ_iLselOff_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLStdIcr_p,	IZ_iLStdIcr_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iL20dn_p,		IZ_iL20dn_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iL20up_p,		IZ_iL20up_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_SAM_p,			IZ_SAM_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_OTP1_p,		IZ_OTP1_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_OTP2_p,		IZ_OTP2_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_OTP3_p,		IZ_OTP3_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_VpinCtri_p,	IZ_VpinCtri_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_Rcv1_p,		IZ_Rcv1_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_Rcv2_p,		IZ_Rcv2_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_RcvSign_p,		IZ_RcvSign_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_drvSize1_p,	IZ_drvSize1_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_drvSize2_p,	IZ_drvSize2_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_drvSize3_p,	IZ_drvSize3_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_drvSize4_p,	IZ_drvSize4_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_RsenseUp_p,	IZ_RsenseUp_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_vxAdj1_p,		IZ_vxAdj1_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_vxAdj2_p,		IZ_vxAdj2_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_vxAdj3_p,		IZ_vxAdj3_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_vxAdj4_p,		IZ_vxAdj4_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_vxAdj5_p,		IZ_vxAdj5_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLRatio1_p,	IZ_iLRatio1_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLRatio2_p,	IZ_iLRatio2_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLRatio3_p,	IZ_iLRatio3_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLRatio4_p,	IZ_iLRatio4_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLTC1_p,		IZ_iLTC1_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLTC2_p,		IZ_iLTC2_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLTC3_p,		IZ_iLTC3_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_iLTC4_p,		IZ_iLTC4_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_IZ_ZF_p,			IZ_ZF_p,			set_fail_bin,	POWER_MICRO);	
	if(gSiliconRev_P >= revB_P)
		PiDatalog(func, A_IZ_ARreq_p,		IZ_ARreq_p,		set_fail_bin,	POWER_MICRO);	



////	if(gSiliconRev_S == revA_S)
////	{
////		PiDatalog(func, A_IZ_NoZ_s,		IZ_NoZ_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_F1_s,		IZ_F1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_F2_s,		IZ_F2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_F3_s,		IZ_F3_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_PK1_s,		IZ_PK1_s,		set_fail_bin,	POWER_MICRO);	
//////		PiDatalog(func, A_IZ_PK2_s,		IZ_PK2_s,		set_fail_bin,	POWER_MICRO);	
//////		PiDatalog(func, A_IZ_PK3_s,		IZ_PK3_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CV1_s,			IZ_PK2_s,			set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_DVesrSlpAdj_s,	IZ_PK3_s,			set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CP1_s,		IZ_CP1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CP2_s,		IZ_CP2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CP3_s,		IZ_CP3_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_PS1_s,		IZ_PS1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_PS2_s,		IZ_PS2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_T1_s,		IZ_T1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_T2_s,		IZ_T2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CC1_s,		IZ_CC1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CC2_s,		IZ_CC2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CC3_s,		IZ_CC3_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CC4_s,		IZ_CC4_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CC5_s,		IZ_CC5_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CC6_s,		IZ_CC6_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_KP1_s,		IZ_KP1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_KP2_s,		IZ_KP2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_KP3_s,		IZ_KP3_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_SL1_s,		IZ_SL1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_SL2_s,		IZ_SL2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_SL3_s,		IZ_SL3_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CS1_s,		IZ_CS1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CS2_s,		IZ_CS2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CS3_s,		IZ_CS3_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CS4_s,		IZ_CS4_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CB1_s,		IZ_CB1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CB2_s,		IZ_CB2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CB3_s,		IZ_CB3_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CV1_s,		IZ_CV1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CV2_s,		IZ_CV2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CV3_s,		IZ_CV3_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CV4_s,		IZ_CV4_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_AR1_s,		IZ_AR1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_AR2_s,		IZ_AR2_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_SCEN_s,		IZ_SCEN_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CBEN_s,		IZ_CBEN_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_DsoftEn_s,		IZ_DsoftEn_s,	set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_DOPL_s,		IZ_DOPL_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_OVLO_s,		IZ_OVLO_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_VR1_s,			IZ_VR1_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_CR_s,			IZ_CR_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_XFWPK_s,		IZ_XFWPK_s,		set_fail_bin,	POWER_MICRO);	
//////		PiDatalog(func, A_IZ_Spare_s,		IZ_Spare_s,		set_fail_bin,	POWER_MICRO);	
////		PiDatalog(func, A_IZ_ZF_s,			IZ_ZF_s,		set_fail_bin,	POWER_MICRO);	
////	}
////	else 
	if(gSiliconRev_S >= revB_S)
	{
		PiDatalog(func,	A_IZ_F1_S,			IZ_F1_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_F2_S,			IZ_F2_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_F3_S,			IZ_F3_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_F4_S,			IZ_F4_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_PK1spdLd_S,	IZ_PK1spdLd_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_PK2_S,			IZ_PK2_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_PK3_S,			IZ_PK3_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_Rnw5_S,		IZ_Rnw5_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_Rnw6_S,		IZ_Rnw6_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_Rnw1_S,		IZ_Rnw1_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_Rnw2_S,		IZ_Rnw2_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_Rnw3_S,		IZ_Rnw3_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_Rnw4_S,		IZ_Rnw4_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_FWC2_S,		IZ_FWC2_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_NoFWC100mV_S,	IZ_NoFWC100mV_S,	set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_Cap1_S,		IZ_Cap1_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_Cap2_S,		IZ_Cap2_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_Cap3_S,		IZ_Cap3_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_PKdig1_S,		IZ_PKdig1_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_PKdig2_S,		IZ_PKdig2_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_PKdig3_S,		IZ_PKdig3_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_PKdig4_S,		IZ_PKdig4_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_SRth1_S,		IZ_SRth1_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_SRth2_S,		IZ_SRth2_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_SRth3_S,		IZ_SRth3_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_SRth4_S,		IZ_SRth4_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_V1_S,			IZ_V1_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_V2_S,			IZ_V2_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_V3_S,			IZ_V3_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_V4_S,			IZ_V4_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_V5_S,			IZ_V5_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_V6_S,			IZ_V6_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_IintTC1_S,		IZ_IintTC1_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_IintTC2_S,		IZ_IintTC2_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_IintTC3_S,		IZ_IintTC3_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_IintTC4_S,		IZ_IintTC4_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_DOPL_S,		IZ_DOPL_S,			set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_REQlow_S,		IZ_REQlow_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func,	A_IZ_XFWPK_S,		IZ_XFWPK_S,			set_fail_bin,	POWER_MICRO);

	}



	//////// Secondary
	//////PiDatalog(func, A_IZ_NoZ_s,		IZ_NoZ_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_F1_s,		IZ_F1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_F2_s,		IZ_F2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_F3_s,		IZ_F3_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_PK1_s,		IZ_PK1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_PK2_s,		IZ_PK2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_PK3_s,		IZ_PK3_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CP1_s,		IZ_CP1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CP2_s,		IZ_CP2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CP3_s,		IZ_CP3_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_PS1_s,		IZ_PS1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_PS2_s,		IZ_PS2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_T1_s,		IZ_T1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_T2_s,		IZ_T2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CC1_s,		IZ_CC1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CC2_s,		IZ_CC2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CC3_s,		IZ_CC3_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CC4_s,		IZ_CC4_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CC5_s,		IZ_CC5_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CC6_s,		IZ_CC6_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_KP1_s,		IZ_KP1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_KP2_s,		IZ_KP2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_KP3_s,		IZ_KP3_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_SL1_s,		IZ_SL1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_SL2_s,		IZ_SL2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_SL3_s,		IZ_SL3_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CS1_s,		IZ_CS1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CS2_s,		IZ_CS2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CS3_s,		IZ_CS3_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CS4_s,		IZ_CS4_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CB1_s,		IZ_CB1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CB2_s,		IZ_CB2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CB3_s,		IZ_CB3_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CV1_s,		IZ_CV1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CV2_s,		IZ_CV2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CV3_s,		IZ_CV3_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CV4_s,		IZ_CV4_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_AR1_s,		IZ_AR1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_AR2_s,		IZ_AR2_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_SCEN_s,	IZ_SCEN_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CBEN_s,	IZ_CBEN_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_DsoftEn_s,	IZ_DsoftEn_s,	set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_DOPL_s,	IZ_DOPL_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_OVLO_s,	IZ_OVLO_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_VR1_s,		IZ_VR1_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_CR_s,		IZ_CR_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_XFWPK_s,	IZ_XFWPK_s,		set_fail_bin,	POWER_MICRO);	
	//////PiDatalog(func, A_IZ_Spare_s,	IZ_Spare_s,		set_fail_bin,	POWER_MICRO);	

	////Pass read back info to Secondary global Feature trim variables
	//if(IZ_PK1_s > iAFs_th)	gRead_PK_S	+=1;
	//if(IZ_CP1_s > iAFs_th)	gRead_CP_S	+=1;
	//if(IZ_CP2_s > iAFs_th)	gRead_CP_S	+=2;
	//if(IZ_CP3_s > iAFs_th)	gRead_CP_S	+=4;
	//if(IZ_PS1_s > iAFs_th)	gRead_PS_S	+=1;
	//if(IZ_PS2_s > iAFs_th)	gRead_PS_S	+=2;
	//if(IZ_T1_s > iAFs_th)	gRead_TF_S	+=1;
	//if(IZ_T2_s > iAFs_th)	gRead_TF_S	+=2;
	//if(IZ_AR1_s > iAFs_th)	gRead_AR_S	+=1;
	//if(IZ_AR2_s > iAFs_th)	gRead_AR_S	+=2;
	//if(IZ_SCEN_s > iAFs_th)		gRead_SCEN_S	+=1;
	//if(IZ_CBEN_s > iAFs_th)		gRead_CBEN_S	+=1;
	//if(IZ_DsoftEn_s > iAFs_th)	gRead_DsoftEn_S	+=1;
	//if(IZ_DOPL_s > iAFs_th)		gRead_DOPL_S	+=1;
	//if(IZ_OVLO_s > iAFs_th)		gRead_OVLO_S	+=1;
	//if(IZ_VR1_s > iAFs_th)		gRead_VR_S		+=1;
	//if(IZ_CR_s > iAFs_th)		gRead_CR_S		+=1;
	//if(IZ_XFWPK_s > iAFs_th)	gRead_XFWPK_S	+=1;
	//if(IZ_Spare_s > iAFs_th)	gRead_Spare_S	+=1;


	//if(gSiliconRev_S <= revB_S)
	//{
	//	//ZF test escape
	//	if(IZ_ZF_s < 3e-6)
	//	{
	//		PiDatalog(func, A_IZ_ZF_s,	IZ_ZF_s,			   6,	POWER_MICRO); //Test Escape	
	//		Test_Escape += 1;
	//	}
	//	else
	//		PiDatalog(func, A_IZ_ZF_s,	IZ_ZF_s, set_fail_bin,	POWER_MICRO);	
	//}

	//PiDatalog(func, A_IZ_Test_Escape,	Test_Escape, 6,	POWER_UNIT);	

	//////Decode CC trimcode
	////gCC_trimcode = 0;
	////if(IZ_CC5_s > 3e-6)	gCC_trimcode += 16;
	////if(IZ_CC4_s > 3e-6)	gCC_trimcode += 8;
	////if(IZ_CC3_s > 3e-6)	gCC_trimcode += 4;
	////if(IZ_CC2_s > 3e-6)	gCC_trimcode += 2;
	////if(IZ_CC1_s > 3e-6)	gCC_trimcode += 1;

	//////Decode F trimcode
	////gFS_trimcode = 0;
	////if(IZ_F3_s > 3e-6) gFS_trimcode += 4;
	////if(IZ_F2_s > 3e-6) gFS_trimcode += 2;
	////if(IZ_F1_s > 3e-6) gFS_trimcode += 1;

	if(gDEBUG==1)
	printf("Function IZPost Done\n");

}
