//==============================================================================
// IzPre.cpp (User function)
// 
//    void IzPre_user_init(test_function& func)
//    void IzPre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "IzPre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IzPre_user_init(test_function& func)
{
	IzPre_params *ours;
    ours = (IzPre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IzPre(test_function& func)
{
    // The two lines below must be the first two in the function.
    IzPre_params *ours;
    ours = (IzPre_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "IzPre";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IZpre,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (OPCODE==4300 ||OPCODE==4500)
		return;

	float	    Izpt_iov1_p=0.0,		Izpt_iov2_p=0.0,		Izpt_iov3_p=0.0,		Izpt_iov4_p=0.0,
				Izpt_iovSign_p=0.0,
				Izpt_iL1_p=0.0,			Izpt_iL2_p=0.0,			Izpt_iL3_p=0.0,			Izpt_iLsign_p=0.0,
				Izpt_tmax1_p=0.0,		Izpt_tmax2_p=0.0,		Izpt_tmaxSign_p=0.0,
				Izpt_f1_p=0.0,			Izpt_f2_p=0.0,			Izpt_fSign_p=0.0,
				Izpt_iov_Off_p=0.0, 
				Izpt_iuvMinus_p=0.0,
				Izpt_uvDelay_p=0.0,
				Izpt_Loff_AR_p=0.0,
				Izpt_DisablAR_p=0.0,
				Izpt_didtComp_p=0.0,
				Izpt_OT_Hys_p=0.0,
				Izpt_LoffwOT_p=0.0,
				Izpt_iLselOff_p=0.0,	Izpt_iLStdIcr_p=0.0,
				Izpt_iL20dn_p=0.0,		Izpt_iL20up_p=0.0,
				Izpt_SAM_p=0.0,
				Izpt_OTP1_p=0.0,		Izpt_OTP2_p=0.0,		Izpt_OTP3_p=0.0,
				Izpt_VpinCtri_p=0.0,	Izpt_SDS_OFF_p=0.0,
				Izpt_Rcv1_p=0.0,		Izpt_Rcv2_p=0.0,		Izpt_RcvSign_p=0.0,
				Izpt_drvSize1_p=0.0,	Izpt_drvSize2_p=0.0,	Izpt_drvSize3_p=0.0,	Izpt_drvSize4_p=0.0,
				Izpt_RsenseUp_p=0.0,
				Izpt_vxAdj1_p=0.0,		Izpt_vxAdj2_p=0.0,		Izpt_vxAdj3_p=0.0,		Izpt_vxAdj4_p=0.0,		Izpt_vxAdj5_p=0.0,
				Izpt_iLRatio1_p=0.0,	Izpt_iLRatio2_p=0.0,	Izpt_iLRatio3_p=0.0,	Izpt_iLRatio4_p=0.0,
				Izpt_iLTC1_p=0.0,		Izpt_iLTC2_p=0.0,		Izpt_iLTC3_p=0.0,		Izpt_iLTC4_p=0.0,
				Izpt_ARreq_p=0.0,
				Izpt_ZF_p=0.0;


	float iAFp_th =0.0; 

	float iAF_array_p[100] = {0};
	float iAF_array_s[100] = {0};
	float iAF_min_p = 999,
		  iAF_max_p = -99;

	//Primary Vpin Internal register variables
	int	Izpt_Iplus_p=0,
		Izpt_ID0_p=0, 		
		Izpt_ID1_p=0;

	//Secondary SR Internal register variables
	int Izpt_SiRev3_s=0, 	
		Izpt_SiRev2_s=0,	
		Izpt_SiRev1_s=0,
		Izpt_FabID2_s=0,
		Izpt_FabID1_s=0;

	int addr =0, 
		Total_Addr_Count_p=0, 
		Total_Addr_Count_s=0, 
		Total_SR_Addr_Count_s=0;

	int i=0, 
		Trimmed=0, 
		readTime=0;


	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//////////

	if(LB_Rev >= 5||g_TurretCB)
	{
		readTime	= 10;		//x*10us => 200us if readTime = 20
	}
	else
	{
		readTime	= 5;		//x*10us => 100us if readTime = 10
	}
	
	if(gSiliconRev_P<=2)	
		iAFp_th		= 300e-6;	//Threshold use to determine if Primary   is trimmed or not.  If trimmed, iAFp ~= 500uA
	else						//B3 material threshold temporary set for 
		iAFp_th		= 200e-6;	//Threshold use to determine if Primary   is trimmed or not.  If trimmed, iAFp ~= 300uA

	//Setup Vout to connect to DDD7_4 and have DDD7_4 toggle to stay LOW to start with
	VO_dvi->open_relay(CONN_FORCE0);
	VO_dvi->open_relay(CONN_SENSE0);

	ovi_1->disconnect(OVI_CHANNEL_1);	// Vpin does not use ovi-1-1 for Iz function
	//delay(1);
	// Initialize DDD
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(4.4);		// Will immediately change to this level upon execution
	//delay(1);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);
	//BPP_ovi->disconnect(1);
	Close_relay(K2);	// Primary:		Connect DVI11_0 to Drain	pin
	Close_relay(K12);	// Primary:		Connect DDD7_1	to Vpin(UV)	pin
	Close_relay(K18);	// Secondary:	Connect DVI11_1 to FB		pin
//	Close_relay(K17);	// Secondary:	Connect DDD7_2	to FB		pin
	Close_relay(K27);	// Secondary:	Connect DDD7_4	to Vout		pin (Inno4)
	delay(4);			// 4 ms delay is necessary to wait for DDD to settle down before powering up BPP pin to avoid mis-clocking

	//** Power Up Primary
	Powerup_Primary_in_Testmode(gWrite_Mode_ReadAF);
	D_dvi->set_meas_mode(D_ch,			DVI_MEASURE_CURRENT);
	delay(5);

	if(gSiliconRev_P == revA_P)		Total_Addr_Count_p = 54;
	if(gSiliconRev_P >= revB_P)		Total_Addr_Count_p = 55;

	//Read Primary
	for (i = 1; i<=Total_Addr_Count_p; i++)			//Primary: First clock count at address 4
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
	//delay(1);
		//measure anti-fuse curent
		iAF_array_p[addr] = D_dvi->measure_average(5);
		ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
		wait.delay_10_us(3);

		if (iAF_array_p[addr] > iAFp_th)		// Trimmed if > 0.1mA
			Trimmed += 1;
	}


	//Observe mode to identify device ID and other features that designers are interested in for Primary Controller
	Observe_Vpin_Internal_Signals();

	//Requires the following setting if we do not test AF current of Secondary
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	//delay(1);
	ddd_7->ddd_set_voltage_ref(2.5);
	//delay(1);
	wait.delay_10_us(5);


	int Result=0, SR_Registers=0;
	int g_Read_SR_Addr[52] = {AF_Vout_pulse_start+20};

	Close_relay(K26);
	Powerup_Secondary_in_Testmode(gProgRead_S, gTrim_Voltage, gVread_AF_secondary);

	//Clock Vout through Register addresses (2 to 52)
	//Read zener trim data on SR pin using DDD
	Total_SR_Addr_Count_s = 52;
	for (i = 1; i<=Total_SR_Addr_Count_s; i++)  //Secondary: First clock count at address 3 for 1.6 silicon, and address 8 for 1.5 silicon
	{
		//DDD_Clock_Vout_Antifuse(1);		
		DDD_Clock_Vout_Antifuse(2);		// Vout clk twice
		i++;
		
		//Reset SR Internal signal array
		gSR_Internal_Signal[i] = 0;

		Result = ddd_7->ddd_read_pattern(g_Read_SR_Addr[0]+2); //Read SR result during Vout high vectors
		gSR_Internal_Signal[i] = Result/16;		//SR pin connects to DDD7_5.  x0000 => bit5 divided by 16 to get 1/0.
	}

	//for (i = 1; i <= 55; i++)
	//{
	//	if (iAF_array_p[i] > 200e-6)
	//		gVpin_AF[i] = 1;
	//	else
	//		gVpin_AF[i] = 0;
	//}

//** Antifuse current results
	// Primary
    Izpt_iov1_p		=iAF_array_p[1];
	Izpt_iov2_p		=iAF_array_p[2];
	Izpt_iov3_p		=iAF_array_p[3]; 
	Izpt_iov4_p		=iAF_array_p[4]; 
	Izpt_iovSign_p	=iAF_array_p[5]; 
	Izpt_iL1_p		=iAF_array_p[6];
	Izpt_iL2_p		=iAF_array_p[7];
	Izpt_iL3_p		=iAF_array_p[8]; 
	Izpt_iLsign_p	=iAF_array_p[9]; 
	Izpt_tmax1_p	=iAF_array_p[10];
	Izpt_tmax2_p	=iAF_array_p[11];
	Izpt_tmaxSign_p	=iAF_array_p[12]; 
	Izpt_f1_p		=iAF_array_p[13];  
	Izpt_f2_p		=iAF_array_p[14];
	Izpt_fSign_p	=iAF_array_p[15];
	Izpt_iov_Off_p	=iAF_array_p[16];
	Izpt_iuvMinus_p	=iAF_array_p[17];
	Izpt_uvDelay_p	=iAF_array_p[18];
	Izpt_Loff_AR_p	=iAF_array_p[19];
	Izpt_DisablAR_p	=iAF_array_p[20];
	Izpt_didtComp_p	=iAF_array_p[21];
	Izpt_OT_Hys_p	=iAF_array_p[22];
	Izpt_LoffwOT_p	=iAF_array_p[23];
	Izpt_iLselOff_p	=iAF_array_p[24];
	Izpt_iLStdIcr_p	=iAF_array_p[25];
	Izpt_iL20dn_p	=iAF_array_p[26];
	Izpt_iL20up_p	=iAF_array_p[27];
	Izpt_SAM_p		=iAF_array_p[28];	//Samsung
	Izpt_OTP1_p		=iAF_array_p[29];
	Izpt_OTP2_p		=iAF_array_p[30];
	Izpt_OTP3_p		=iAF_array_p[31];
	Izpt_VpinCtri_p	=iAF_array_p[32];	//B2p silicon
	Izpt_SDS_OFF_p	=iAF_array_p[32];	//B3p silicon
	Izpt_Rcv1_p		=iAF_array_p[33];
	Izpt_Rcv2_p		=iAF_array_p[34];
	Izpt_RcvSign_p	=iAF_array_p[35];
	Izpt_drvSize1_p	=iAF_array_p[36];
	Izpt_drvSize2_p	=iAF_array_p[37];
	Izpt_drvSize3_p	=iAF_array_p[38];
	Izpt_drvSize4_p	=iAF_array_p[39];
	Izpt_RsenseUp_p	=iAF_array_p[40];
	Izpt_vxAdj1_p	=iAF_array_p[41];
	Izpt_vxAdj2_p	=iAF_array_p[42];
	Izpt_vxAdj3_p	=iAF_array_p[43];
	Izpt_vxAdj4_p	=iAF_array_p[44];
	Izpt_vxAdj5_p	=iAF_array_p[45];
	Izpt_iLRatio1_p	=iAF_array_p[46];
	Izpt_iLRatio2_p	=iAF_array_p[47];
	Izpt_iLRatio3_p	=iAF_array_p[48];
	Izpt_iLRatio4_p	=iAF_array_p[49];
	Izpt_iLTC1_p	=iAF_array_p[50];
	Izpt_iLTC2_p	=iAF_array_p[51];
	Izpt_iLTC3_p	=iAF_array_p[52];
	Izpt_iLTC4_p	=iAF_array_p[53];

	if(gSiliconRev_P == revA_P)
		Izpt_ZF_p		=iAF_array_p[54];
	if(gSiliconRev_P >= revB_P)
	{
		Izpt_ARreq_p	=iAF_array_p[54];
		Izpt_ZF_p		=iAF_array_p[55];
	}
		//Keep track of min/max and delta to make sure DDD card is good
		for(i=1; i<=54; i++)
		{
			if(iAF_array_p[i] < iAF_min_p)		iAF_min_p = iAF_array_p[i];
			if(iAF_array_p[i] > iAF_max_p)		iAF_max_p = iAF_array_p[i];
		}
		//Purposely datalog out -999 to fail ZF-P so we know DDD or DVI is bad and "Disable Trim"  (TMT26 shows this symptom)
		if(iAF_max_p > 150e-6 && iAF_max_p < 200e-6 ) //virgin device but iAF is measured incorrectly
		{
			Izpt_ZF_p = -999;
			TRIM_ENABLE = 0;	//DISABLE TRIM
		}

//** Primary Vpin Internal Signal results
	Izpt_Iplus_p	=gVpin_Internal_Signal[13];
	Izpt_ID0_p		=gVpin_Internal_Signal[14];
	Izpt_ID1_p		=gVpin_Internal_Signal[15];

//** Secondary SR Internal Signal results
	Izpt_SiRev3_s	=gSR_Internal_Signal[30];
	Izpt_SiRev2_s	=gSR_Internal_Signal[32];
	Izpt_SiRev1_s	=gSR_Internal_Signal[34];
	Izpt_FabID2_s	=gSR_Internal_Signal[28];
	Izpt_FabID1_s	=gSR_Internal_Signal[36];


	//Power down
	wait.delay_10_us(10); 
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(3);
	D_dvi->set_voltage(D_ch, 0.0, 		VOLT_10_RANGE);	// DVI_11_0
	FW_dvi->set_voltage(FW_ch, 0.0, 	VOLT_10_RANGE);	// DVI_11_1
	VPIN_ovi->set_current(VPIN_ch, 1e-3,		RANGE_30_MA);  //HL new added to prevent hot switching in Feature trim function.
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);  
	
	delay(1);
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU,	RANGE_10_V);
	BPS_dvi->set_voltage(BPS_ch, 0.0, 	VOLT_10_RANGE);	// DVI_9_1
	wait.delay_10_us(20);

	BPP_ovi->connect(1);
	SR_dvi2k->close_relay(CONN_FORCE1);
	SR_dvi2k->close_relay(CONN_SENSE1);
	delay(1);
	ddd_7->ddd_set_voltage_ref(0.0);
//	delay(1);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	Open_relay(K2);
	Open_relay(K18);
	Open_relay(K12);
	Open_relay(K16);
	Open_relay(K27);
	Open_relay(K26);
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);

	//Store Izpt_iov_Off_p globally
	gIzpt_iov_Off_p = Izpt_iov_Off_p;

//** Datalog
	// Primary
	PiDatalog(func, A_Izpt_iov1_p,		Izpt_iov1_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iov2_p,		Izpt_iov2_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iov3_p,		Izpt_iov3_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iov4_p,		Izpt_iov4_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iovSign_p,	Izpt_iovSign_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iL1_p,		Izpt_iL1_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iL2_p,		Izpt_iL2_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iL3_p,		Izpt_iL3_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLsign_p,	Izpt_iLsign_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_tmax1_p,		Izpt_tmax1_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_tmax2_p,		Izpt_tmax2_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_tmaxSign_p,	Izpt_tmaxSign_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_f1_p,		Izpt_f1_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_f2_p,		Izpt_f2_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_fSign_p,		Izpt_fSign_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iov_Off_p,	Izpt_iov_Off_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iuvMinus_p,	Izpt_iuvMinus_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_uvDelay_p,	Izpt_uvDelay_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_Loff_AR_p,	Izpt_Loff_AR_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_DisablAR_p,	Izpt_DisablAR_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_didtComp_p,	Izpt_didtComp_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_OT_Hys_p,	Izpt_OT_Hys_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_LoffwOT_p,	Izpt_LoffwOT_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLselOff_p,	Izpt_iLselOff_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLStdIcr_p,	Izpt_iLStdIcr_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iL20dn_p,	Izpt_iL20dn_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iL20up_p,	Izpt_iL20up_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_SAM_p,		Izpt_SAM_p,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_OTP1_p,		Izpt_OTP1_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_OTP2_p,		Izpt_OTP2_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_OTP3_p,		Izpt_OTP3_p,		set_fail_bin,	POWER_MICRO);	
	if(gSiliconRev_P>=3)	PiDatalog(func, A_Izpt_SDS_OFF_p,	Izpt_SDS_OFF_p,		set_fail_bin,	POWER_MICRO);	
	else					PiDatalog(func, A_Izpt_VpinCtri_p,	Izpt_VpinCtri_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_Rcv1_p,		Izpt_Rcv1_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_Rcv2_p,		Izpt_Rcv2_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_RcvSign_p,	Izpt_RcvSign_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_drvSize1_p,	Izpt_drvSize1_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_drvSize2_p,	Izpt_drvSize2_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_drvSize3_p,	Izpt_drvSize3_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_drvSize4_p,	Izpt_drvSize4_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_RsenseUp_p,	Izpt_RsenseUp_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_vxAdj1_p,	Izpt_vxAdj1_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_vxAdj2_p,	Izpt_vxAdj2_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_vxAdj3_p,	Izpt_vxAdj3_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_vxAdj4_p,	Izpt_vxAdj4_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_vxAdj5_p,	Izpt_vxAdj5_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLRatio1_p,	Izpt_iLRatio1_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLRatio2_p,	Izpt_iLRatio2_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLRatio3_p,	Izpt_iLRatio3_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLRatio4_p,	Izpt_iLRatio4_p,	set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLTC1_p,		Izpt_iLTC1_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLTC2_p,		Izpt_iLTC2_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLTC3_p,		Izpt_iLTC3_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_iLTC4_p,		Izpt_iLTC4_p,		set_fail_bin,	POWER_MICRO);	
	if(gSiliconRev_P >= revB_P)
		PiDatalog(func, A_Izpt_ARreq_p,		Izpt_ARreq_p,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Izpt_ZF_p,		Izpt_ZF_p,			set_fail_bin,	POWER_MICRO);	

	//Keep track of secondary trimmed links  CX 8/30/2017
	for(i=1; i<=52; i++)
	{
		if(gSR_AF[i] > 0)
			Trimmed += 1;	//use SR Registers instead of iAF_s
	}

	PiDatalog(func, A_Izpt_Trimmed,		Trimmed,		set_fail_bin,	POWER_UNIT);	

	////PiDatalog(func, A_Izpt_Xcontrol_p,		Izpt_Xcontrol_p,	set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_Xlisten_p,		Izpt_Xlisten_p,		set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_XVTurnOn_p,		Izpt_XVTurnOn_p,	set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_XRestart_p,		Izpt_XRestart_p,	set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_rcv_p,			Izpt_rcv_p,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_Pause_p,			Izpt_Pause_p,		set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_DSDS_p,			Izpt_DSDS_p,		set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_OT_p,			Izpt_OT_p,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_LatchOff_p,		Izpt_LatchOff_p,	set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_Xoc_p,			Izpt_Xoc_p,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_DZwindow_p,		Izpt_DZwindow_p,	set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_XZF_Q_p,			Izpt_XZF_Q_p,		set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_XTest2_p,		Izpt_XTest2_p,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Izpt_Iplus_p,			Izpt_Iplus_p,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Izpt_ID0_p,			Izpt_ID0_p,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Izpt_ID1_p,			Izpt_ID1_p,			set_fail_bin,	POWER_UNIT);	

	////PiDatalog(func, A_Izpt_TM1_s,			Izpt_TM1_s,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TM2_s,			Izpt_TM2_s,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TM3_s,			Izpt_TM3_s,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TM4_s,			Izpt_TM4_s,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TM5_s,			Izpt_TM5_s,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TM6_s,			Izpt_TM6_s,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TMTFB1_s,		Izpt_TMTFB1_s,		set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TMTFB2_s,		Izpt_TMTFB2_s,		set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_R18_s,			Izpt_R18_s,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_R20_s,			Izpt_R20_s,			set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TM11_s,			Izpt_TM11_s,		set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TM12_s,			Izpt_TM12_s,		set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TM13_s,			Izpt_TM13_s,		set_fail_bin,	POWER_UNIT);	
	////PiDatalog(func, A_Izpt_TM14_s,			Izpt_TM14_s,		set_fail_bin,	POWER_UNIT);	


	PiDatalog(func, A_Izpt_SiRev3_s,		Izpt_SiRev3_s,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Izpt_SiRev2_s,		Izpt_SiRev2_s,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Izpt_SiRev1_s,		Izpt_SiRev1_s,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Izpt_FabID2_s,		Izpt_FabID2_s,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Izpt_FabID1_s,		Izpt_FabID1_s,		set_fail_bin,	POWER_UNIT);	

	//Determine Primary and Secondary Silicon Option based on ID0,ID1 for Primary and SiRev3,2,1 for Secondary
	gSiOption_p = Izpt_ID1_p	* 2 + Izpt_ID0_p;
	gSiOption_s	= Izpt_SiRev3_s	* 4 + Izpt_SiRev2_s * 2 + Izpt_SiRev1_s;

	PiDatalog(func, A_SiOption_p,		gSiOption_p,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_SiOption_s,		gSiOption_s,		set_fail_bin,	POWER_UNIT);	

	//Determine what Silicon Revision it is by combining Primary and Secondary SiOption data
	if(gSiOption_p==0 && gSiOption_s==1)	g_Silicon_Rev = 2;	//B2 silicon device
	if(gSiOption_p==1 && gSiOption_s==2)	g_Silicon_Rev = 3;	//B3 silicon device

	//Check silicon rev matches what is in TrimOptions table
	int rev_correct_p,rev_correct_s;
	rev_correct_p=0;	//fail
	rev_correct_s=0;	//fail

		//Check for correct rev B2 Primary silicon, 
		if ((gSiliconRev_P == 2) && (gSiOption_p == 0) )	//TrimOps table vs silicon
			rev_correct_p=1;	//Correct Rev B2 silicon

		//Check for correct rev B2 Secondary silicon
		if ( (gSiliconRev_S == 2) && (gSiOption_s == 1) )
			rev_correct_s=1;	//Correct Rev B2 silicon

		//Check for correct rev B3(P) silicon
		if ((gSiliconRev_P == 3) && (gSiOption_p == 1) )
			rev_correct_p=1;	//Correct Rev B2 silicon

		//Check for correct B4(S) silicon
		if ((gSiliconRev_S == 4) && (gSiOption_s == 2) )
			rev_correct_s=1;	//Correct Rev B2 silicon

		//datalog, 1 if correct match, 0 if not correct
		PiDatalog(func, A_Izpt_Sil_Match_p,		rev_correct_p,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_Izpt_Sil_Match_s,		rev_correct_s,		set_fail_bin,	POWER_UNIT);	



	//Power_Down_Everything();
	//Open_All_Relays();

	if(Trimmed > 1)
	{
		TRIM_ENABLE		= 0;	//DISABLE TRIM
		gTrimmed_Device	= 1;
		gStress_ON		= 0;
	}
	else
	{
		gTrimmed_Device	= 0;
	}

	if(gDEBUG==1)
	printf("Function IZPre Done\n");

}
