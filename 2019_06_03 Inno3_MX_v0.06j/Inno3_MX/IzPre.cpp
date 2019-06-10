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

	float iAFp_th =0.0; 

	float iAF_array_p[100] = {0};
	float iAF_array_s[100] = {0};
	float iAF_min_p = 999,
		  iAF_max_p = -99;

	//Primary Vpin Internal register variables
	int Izpt_Iplus_p	= 0,
		Izpt_ID0_p		= 0,
		Izpt_ID1_p		= 0;

	//Secondary SR Internal register variables
	int Izpt_SiRev3_s	= 0,
		Izpt_SiRev2_s	= 0,
		Izpt_SiRev1_s	= 0,
		Izpt_FabID2_s	= 0,
		Izpt_FabID1_s	= 0;

	int i = 0,
		Trimmed  = 0,
		readTime = 0;

	readTime	= 10;		//x*10us => 200us if readTime = 10
	
	iAFp_th		= 200e-6;	//Threshold use to determine if Primary   is trimmed or not.  If trimmed, iAFp ~= 300uA

	// Setup Vout to connect to DDD7_4 and have DDD7_4 toggle to stay LOW to start with
	VO_dvi->open_relay(CONN_FORCE0);
	VO_dvi->open_relay(CONN_SENSE0);

	VPIN_ovi->disconnect(VPIN_ch);	// Vpin does not use ovi-1-1 for Iz function
	//delay(1);

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

	//** Power Up Primary
	Powerup_Primary_in_Testmode(gWrite_Mode_ReadAF);
	D_dvi->set_meas_mode(D_ch,			DVI_MEASURE_CURRENT);
	delay(5);			// Critical do not remove!

	// Read Primary
	for (i = 1; i <= gTotal_Addr_Count_P; i++)
	{
		DDD_Clock_UV_Antifuse(1);		// Vpin(UV) clock through all AF links one by one
		//Require more wait time for the first AF link		// ET - questionable?? - 20190508
		//if(i==1)	
		//{
		//	wait.delay_10_us(200);
		//}

		// Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
		ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse
		DDD_Wait_Pattern_End(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);
		//wait.delay_10_us(readTime);

		// measure anti-fuse curent
		iAF_array_p[i] = D_dvi->measure_average(5);

		ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse
		DDD_Wait_Pattern_End(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);

		if (iAF_array_p[i] > iAFp_th)
			Trimmed += 1;
	}

	// Observe mode to identify device ID and other features that designers are interested in for Primary Controller
	Observe_Vpin_Internal_Signals();

	// Measure secondary AF currents
	//if(gRemove_Test_from_all_Devices==false)
	if (1)
	{
		//** Power Up Secondary
		Powerup_Secondary_in_Testmode(gWrite_Mode_ReadAF, gTrim_Voltage, gVread_AF_secondary);

		ddd_7->ddd_set_lo_level(0.1);		
		ddd_7->ddd_set_hi_level(4.0);		// This is to make sure Vout is not higher than VBPS
		wait.delay_10_us(10);

		//BPS stay at 4V for reading AF links
		//BPS_dvi->set_voltage(BPS_ch, 4.4,	VOLT_10_RANGE);	//DE complain vBPS(4V)_120uA iAF_NoZF is too high (suspect Bench vBPS=4.4V_88uA)
		//MUST USE VPLUS + 50mV, else read negative current on devices with vPlus higher than 4.4V
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final,	VOLT_10_RANGE);	//DE complain vBPS(4V)_120uA iAF_NoZF is too high (suspect Bench vBPS=4.4V_88uA)
		wait.delay_10_us(5);

		// Read Secondary
		for (i = 1; i <= gTotal_Addr_Count_S; i++)	// Secondary: First clock count at address 3 for 1.6 silicon, and address 8 for 1.5 silicon
		{
			// Clock
			DDD_Clock_Vout_Antifuse(1);		// Vout clk

			// Quiescent current 
			if(i==1)
			{
				FW_dvi->set_voltage(FW_ch, gVread_AF_secondary, 	RANGE_5_V);	// DVI_11_1
				FW_dvi->set_current(FW_ch, 300e-6,					RANGE_300_UA);
				FW_dvi->set_meas_mode(FW_ch,						DVI_MEASURE_CURRENT);
				wait.delay_10_us(100);
				iAF_array_s[0] = FW_dvi->measure_average(5);
			}

			// Raise REQ voltage to 4V for duration of anti-fuse reading
			REQ_ovi->set_voltage(REQ_ch, 4.0, 		VOLT_5_RANGE);	// OVI_1_2 (revB silicon use 4V)
			wait.delay_10_us(15);	

			// Save FW current into array
			iAF_array_s[i] = FW_dvi->measure_average(5);

			// Bring REQ voltage back down to 0 after reading
			REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
			wait.delay_10_us(51);

			// subtract quiescent current
			// Secondary Anti-fuses are read from BPS pin. BPS voltage is about 4.V. Some antifuses can't be read properly
			// at this voltage. Subtract out Quiescent current from the anti-fuse current to make sure anti-fuses are trimmed properly
			iAF_array_s[i] -=iAF_array_s[0];

			//Use the SR registers instead of the iAF to keep track of number of secondary bits trimmed.
			//if (iAF_array_s[addr] > iAFs_th)
			//	Trimmed += 1;			
		}

		// Read out Silicon Rev of Secondary from Program Mode
		BPS_dvi->set_current(BPS_ch, 0.0e-3,	RANGE_300_MA);
		BPS_dvi->set_voltage(BPS_ch, 0.0, 		RANGE_5_V);	// DVI_9_1
		wait.delay_10_us(5);
		FW_dvi->set_current(FW_ch, 0.0e-3,		RANGE_30_MA);	
		FW_dvi->set_voltage(FW_ch, 0.0,			VOLT_5_RANGE);		// DVI11-1
		REQ_ovi->set_current(REQ_ch, 0.0e-3,	RANGE_30_MA);
		REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_5_V);	// OVI_1_2
		FWC_dvi2k->set_current(FWC_ch, 0.0,		RANGE_2_A);
		FWC_dvi2k->set_voltage(FWC_ch, 0.0,		RANGE_2_V);	// DVI-13-0
	}
	//ends if(gRemove_Test_from_all_Devices==false)

	// Requires the following setting if we do not test AF current of Secondary
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	//delay(1);
	ddd_7->ddd_set_voltage_ref(2.5);
	//delay(1);
	wait.delay_10_us(5);

	int Result = 0;

	Close_relay(K26);
	Powerup_Secondary_in_Testmode(gProgRead_S, gTrim_Voltage, gVread_AF_secondary);

	// Clock Vout through Register addresses (2 to 52)
	// Read zener trim data on SR pin using DDD
	for (i = 1; i <= gTotal_Addr_Count_S; i++)  //Secondary: First clock count at address 3 for 1.6 silicon, and address 8 for 1.5 silicon
	{
		//DDD_Clock_Vout_Antifuse(1);		
		DDD_Clock_Vout_Antifuse(2);		// Vout clk twice
		i++;
		
		// Reset SR Internal signal array
		gSR_Internal_Signal[i] = 0;

		Result = ddd_7->ddd_read_pattern(AF_Vout_pulse_start + 22); // Read SR result during Vout high vectors
		gSR_Internal_Signal[i] = Result / 16;		// SR pin connects to DDD7_5.  x0000 => bit5 divided by 16 to get 1/0.
	}

	// Keep track of min/max and delta to make sure DDD card is good
	for (i = 1; i<= gTotal_Addr_Count_P; i++)
	{
		if(iAF_array_p[i] < iAF_min_p)		iAF_min_p = iAF_array_p[i];
		if(iAF_array_p[i] > iAF_max_p)		iAF_max_p = iAF_array_p[i];
	}
	// Purposely datalog out -999 to fail ZF-P so we know DDD or DVI is bad and "Disable Trim"  (TMT26 shows this symptom)
	if(iAF_max_p > 150e-6 && iAF_max_p < 200e-6 ) // virgin device but iAF is measured incorrectly
	{
		iAF_array_p[gP_AF_Start_Addr_ZF] = -999;
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
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(3);
	D_dvi->set_voltage(D_ch,		0.0, 		RANGE_10_V);	// DVI_11_0
	FW_dvi->set_voltage(FW_ch,		0.0, 		RANGE_10_V);	// DVI_11_1
	VPIN_ovi->set_current(VPIN_ch,	1e-3,		RANGE_30_MA);	// HL new added to prevent hot switching in Feature trim function.
	VPIN_ovi->set_voltage(VPIN_ch,	0.0,		RANGE_10_V);
	delay(1);

	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	BPS_dvi->set_voltage(BPS_ch, 0.0, 	VOLT_10_RANGE);	// DVI_9_1
	wait.delay_10_us(20);

	BPP_ovi->connect(1);
	SR_dvi2k->close_relay(CONN_FORCE1);
	SR_dvi2k->close_relay(CONN_SENSE1);
	delay(1);
	ddd_7->ddd_set_voltage_ref(0.0);
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
	gIzpt_iov_Off_p = iAF_array_p[gP_AF_Start_Addr_IuvIov_Disable];

	//** Datalog
	// Primary
	if (gGaN)
	{
		// GaN
		PiDatalog(func, A_Izpt_iov1_p,		iAF_array_p[gP_AF_Start_Addr_IOV],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iov2_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iov3_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iov4_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 3],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iovSign_p,	iAF_array_p[gP_AF_Start_Addr_IOV + 4],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iL1_p,		iAF_array_p[gP_AF_Start_Addr_ILIM],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iL2_p,		iAF_array_p[gP_AF_Start_Addr_ILIM + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iL3_p,		iAF_array_p[gP_AF_Start_Addr_ILIM + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLsign_p,	iAF_array_p[gP_AF_Start_Addr_ILIM + 3],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_tOVL1_p,		iAF_array_p[gP_AF_Start_Addr_tOVL],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_tOVL2_p,		iAF_array_p[gP_AF_Start_Addr_tOVL + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_tOVLSign_p,	iAF_array_p[gP_AF_Start_Addr_tOVL + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_f1_p,		iAF_array_p[gP_AF_Start_Addr_Freq],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_f2_p,		iAF_array_p[gP_AF_Start_Addr_Freq + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_fSign_p,		iAF_array_p[gP_AF_Start_Addr_Freq + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iov_Off_p,	iAF_array_p[gP_AF_Start_Addr_IuvIov_Disable],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iuvMinus_p,	iAF_array_p[gP_AF_Start_Addr_Iuv_10uA],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_uvDelay_p,	iAF_array_p[gP_AF_Start_Addr_UV_400ms_dly],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_Loff_AR_p,	iAF_array_p[gP_AF_Start_Addr_LatchOFF_aft_AR],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_OTP1_p,		iAF_array_p[gP_AF_Start_Addr_OTP],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_OTP2_p,		iAF_array_p[gP_AF_Start_Addr_OTP + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_OTP3_p,		iAF_array_p[gP_AF_Start_Addr_OTP + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_LoffwOT_p,	iAF_array_p[gP_AF_Start_Addr_LatchOFF_w_OT],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLselOff_p,	iAF_array_p[gP_AF_Start_Addr_Disable_ILIM_Select],	set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLStdIcr_p,	iAF_array_p[gP_AF_Start_Addr_Select_ILIM_Incr],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_OT_Hys_p,	iAF_array_p[gP_AF_Start_Addr_OT_Hys_30C],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_DisablAR_p,	iAF_array_p[gP_AF_Start_Addr_Disable_AR],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_SAM_p,		iAF_array_p[gP_AF_Start_Addr_Samsung_Mode],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSTSel1_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Ton],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSTSel2_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Ton + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSTtr1_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Trim],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSTtr2_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Trim + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_Rcv1_p,		iAF_array_p[gP_AF_Start_Addr_Rcv],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_Rcv2_p,		iAF_array_p[gP_AF_Start_Addr_Rcv + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_RcvSign_p,	iAF_array_p[gP_AF_Start_Addr_Rcv + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSon_p,		iAF_array_p[gP_AF_Start_Addr_ZVSon],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_UV1_p,		iAF_array_p[gP_AF_Start_Addr_UV],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_UV2_p,		iAF_array_p[gP_AF_Start_Addr_UV + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSdlm20_p,	iAF_array_p[gP_AF_Start_Addr_ZVSdelaym20],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_IlimLEB_p,	iAF_array_p[gP_AF_Start_Addr_IlimLEB],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_vpinIref_p,	iAF_array_p[gP_AF_Start_Addr_VpinCTRL_iREF20pct],	set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSDly1_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Delay],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSDly2_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Delay + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSDly3_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Delay + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZVSDly14_p,	iAF_array_p[gP_AF_Start_Addr_ZVS_Delay + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_SDS30pct_p,	iAF_array_p[gP_AF_Start_Addr_SDSpct],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_SDS60pct_p,	iAF_array_p[gP_AF_Start_Addr_SDSpct + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLRatio1_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLRatio2_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLTC1_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLTC2_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLTC3_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 2],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLTC4_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 3],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ARreq_p,		iAF_array_p[gP_AF_Start_Addr_AR_Request],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZF_p,		iAF_array_p[gP_AF_Start_Addr_ZF],					set_fail_bin,	POWER_MICRO);
	}
	else
	{
		// DLM
		PiDatalog(func, A_Izpt_iov1_p,		iAF_array_p[gP_AF_Start_Addr_IOV],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iov2_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iov3_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iov4_p,		iAF_array_p[gP_AF_Start_Addr_IOV + 3],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iovSign_p,	iAF_array_p[gP_AF_Start_Addr_IOV + 4],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iL1_p,		iAF_array_p[gP_AF_Start_Addr_ILIM],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iL2_p,		iAF_array_p[gP_AF_Start_Addr_ILIM + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iL3_p,		iAF_array_p[gP_AF_Start_Addr_ILIM + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLsign_p,	iAF_array_p[gP_AF_Start_Addr_ILIM + 3],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_tOVL1_p,		iAF_array_p[gP_AF_Start_Addr_tOVL],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_tOVL2_p,		iAF_array_p[gP_AF_Start_Addr_tOVL + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_tOVLSign_p,	iAF_array_p[gP_AF_Start_Addr_tOVL + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_f1_p,		iAF_array_p[gP_AF_Start_Addr_Freq],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_f2_p,		iAF_array_p[gP_AF_Start_Addr_Freq + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_fSign_p,		iAF_array_p[gP_AF_Start_Addr_Freq + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iov_Off_p,	iAF_array_p[gP_AF_Start_Addr_IuvIov_Disable],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iuvMinus_p,	iAF_array_p[gP_AF_Start_Addr_Iuv_10uA],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_uvDelay_p,	iAF_array_p[gP_AF_Start_Addr_UV_400ms_dly],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_Loff_AR_p,	iAF_array_p[gP_AF_Start_Addr_LatchOFF_aft_AR],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_DisablAR_p,	iAF_array_p[gP_AF_Start_Addr_Disable_AR],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_didtComp_p,	iAF_array_p[gP_AF_Start_Addr_didt_comp],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_OT_Hys_p,	iAF_array_p[gP_AF_Start_Addr_OT_Hys_30C],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_LoffwOT_p,	iAF_array_p[gP_AF_Start_Addr_LatchOFF_w_OT],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLselOff_p,	iAF_array_p[gP_AF_Start_Addr_Disable_ILIM_Select],	set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLStdIcr_p,	iAF_array_p[gP_AF_Start_Addr_Select_ILIM_Incr],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iL20dn_p,	iAF_array_p[gP_AF_Start_Addr_minus_20pct_ILIM],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iL20up_p,	iAF_array_p[gP_AF_Start_Addr_plus_20pct_ILIM],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_SAM_p,		iAF_array_p[gP_AF_Start_Addr_Samsung_Mode],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_OTP1_p,		iAF_array_p[gP_AF_Start_Addr_OTP],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_OTP2_p,		iAF_array_p[gP_AF_Start_Addr_OTP + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_OTP3_p,		iAF_array_p[gP_AF_Start_Addr_OTP + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_SDS_OFF_p,	iAF_array_p[gP_AF_Start_Addr_SDS_OFF],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_Rcv1_p,		iAF_array_p[gP_AF_Start_Addr_Rcv],					set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_Rcv2_p,		iAF_array_p[gP_AF_Start_Addr_Rcv + 1],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_RcvSign_p,	iAF_array_p[gP_AF_Start_Addr_Rcv + 2],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_drvSize1_p,	iAF_array_p[gP_AF_Start_Addr_Driver_Size],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_drvSize2_p,	iAF_array_p[gP_AF_Start_Addr_Driver_Size + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_drvSize3_p,	iAF_array_p[gP_AF_Start_Addr_Driver_Size + 2],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_drvSize4_p,	iAF_array_p[gP_AF_Start_Addr_Driver_Size + 3],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_RsenseUp_p,	iAF_array_p[gP_AF_Start_Addr_Rsense_up],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_vxAdj1_p,	iAF_array_p[gP_AF_Start_Addr_Vx_adjust],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_vxAdj2_p,	iAF_array_p[gP_AF_Start_Addr_Vx_adjust + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_vxAdj3_p,	iAF_array_p[gP_AF_Start_Addr_Vx_adjust + 2],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_vxAdj4_p,	iAF_array_p[gP_AF_Start_Addr_Vx_adjust + 3],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_vxAdj5_p,	iAF_array_p[gP_AF_Start_Addr_Vx_adjust + 4],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLRatio1_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLRatio2_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio + 1],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLRatio3_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio + 2],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLRatio4_p,	iAF_array_p[gP_AF_Start_Addr_ILIM_Ratio + 3],		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLTC1_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC],				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLTC2_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 1],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLTC3_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 2],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_iLTC4_p,		iAF_array_p[gP_AF_Start_Addr_ILIM_TC + 3],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ARreq_p,		iAF_array_p[gP_AF_Start_Addr_AR_Request],			set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Izpt_ZF_p,		iAF_array_p[gP_AF_Start_Addr_ZF],					set_fail_bin,	POWER_MICRO);
	}

	// Secondary
	PiDatalog(func, A_Izpt_NoZ_s,		iAF_array_s[0],								set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_F1_s,		iAF_array_s[gFosc_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_F2_s,		iAF_array_s[gFosc_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_F3_s,		iAF_array_s[gFosc_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_F4_s,		iAF_array_s[gFosc_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_PKspdLd_s,	iAF_array_s[gPK_ssSpeed_AF_Addr_Start],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_PK2_s,		iAF_array_s[gPK_ssSpeed_AF_Addr_Start + 1],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_PK3_s,		iAF_array_s[gPK_ssSpeed_AF_Addr_Start + 2],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Rnw5_s,		iAF_array_s[gRnw_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Rnw6_s,		iAF_array_s[gRnw_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Rnw1_s,		iAF_array_s[gRnwFine_AF_Addr_Start],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Rnw2_s,		iAF_array_s[gRnwFine_AF_Addr_Start + 1],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Rnw3_s,		iAF_array_s[gRnwFine_AF_Addr_Start + 2],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Rnw4_s,		iAF_array_s[gRnwFine_AF_Addr_Start + 3],	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_FWC2_s,		iAF_array_s[gFWC2_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_NoFWC_s,		iAF_array_s[gNoFWC100mV_AF_Addr_Start],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Cap1_s,		iAF_array_s[gCap_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Cap2_s,		iAF_array_s[gCap_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Cap3_s,		iAF_array_s[gCap_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_PKdig1_s,	iAF_array_s[gPKdig_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_PKdig2_s,	iAF_array_s[gPKdig_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_PKdig3_s,	iAF_array_s[gPKdig_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_PKdig4_s,	iAF_array_s[gPKdig_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_SRth1_s,		iAF_array_s[gSRth_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_SRth2_s,		iAF_array_s[gSRth_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_SRth3_s,		iAF_array_s[gSRth_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_SRth4_s,		iAF_array_s[gSRth_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_Vshunt_s,	iAF_array_s[gVshunt_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_V1_s,		iAF_array_s[gVref_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_V2_s,		iAF_array_s[gVref_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_V3_s,		iAF_array_s[gVref_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_V4_s,		iAF_array_s[gVref_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_V5_s,		iAF_array_s[gVref_AF_Addr_Start + 4],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_V6_s,		iAF_array_s[gVref_AF_Addr_Start + 5],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_IintTC1_s,	iAF_array_s[gIintTC_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_IintTC2_s,	iAF_array_s[gIintTC_AF_Addr_Start + 1],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_IintTC3_s,	iAF_array_s[gIintTC_AF_Addr_Start + 2],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_IintTC4_s,	iAF_array_s[gIintTC_AF_Addr_Start + 3],		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_DOPL_s,		iAF_array_s[gDOPL_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_REQlow_s,	iAF_array_s[gREQlow_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_XFWPK_s,		iAF_array_s[gXFWPK_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Izpt_LO_dis_s,	iAF_array_s[gLO_dis_AF_Addr_Start],			set_fail_bin,	POWER_MICRO);

	// Keep track of secondary trimmed links  CX 8/30/2017
	for (i = 1; i <= 52; i++)
	{
		if (gSR_AF[i] > 0)	Trimmed += 1;	// use SR Registers instead of iAF_s
	}

	PiDatalog(func, A_Izpt_Trimmed,		Trimmed,		set_fail_bin,	POWER_UNIT);

	PiDatalog(func, A_Izpt_Iplus_p,			Izpt_Iplus_p,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Izpt_ID0_p,			Izpt_ID0_p,			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Izpt_ID1_p,			Izpt_ID1_p,			set_fail_bin,	POWER_UNIT);

	PiDatalog(func, A_Izpt_SiRev3_s,		Izpt_SiRev3_s,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Izpt_SiRev2_s,		Izpt_SiRev2_s,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Izpt_SiRev1_s,		Izpt_SiRev1_s,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Izpt_FabID2_s,		Izpt_FabID2_s,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Izpt_FabID1_s,		Izpt_FabID1_s,		set_fail_bin,	POWER_UNIT);

	// Determine Primary and Secondary Silicon Option based on ID0,ID1 for Primary and SiRev3,2,1 for Secondary
	gSiOption_p = Izpt_ID1_p	* 2 + Izpt_ID0_p;
	gSiOption_s = Izpt_SiRev3_s	* 4 + Izpt_SiRev2_s * 2 + Izpt_SiRev1_s;

	PiDatalog(func, A_SiOption_p,			gSiOption_p,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_SiOption_s,			gSiOption_s,		set_fail_bin,	POWER_UNIT);

	// Check silicon rev matches what is in TrimOptions table
	int rev_correct_p, rev_correct_s;
	rev_correct_p = 0;	//fail
	rev_correct_s = 0;	//fail

	if (gGaN)
	{
		// Check for correct DX121C Primary silicon
		if ((gSiliconRev_P == 7) && (gSiOption_p == 0) )	//TrimOps table vs silicon
			rev_correct_p=1;	//Correct Rev B2 silicon
	}
	else
	{
		// Check for correct DX001B5 Primary silicon
		if ((gSiliconRev_P == 5) && (gSiOption_p == 3) )	//TrimOps table vs silicon
			rev_correct_p=1;	//Correct Rev B2 silicon
	}

	// Check for correct DX112B1 Secondary silicon
	if ( (gSiliconRev_S == 3) && (gSiOption_s == 3) )
		rev_correct_s=1;	//Correct Rev B2 silicon

	// Check for correct DX112B2 Secondary silicon
	if ( (gSiliconRev_S == 4) && (gSiOption_s == 4) )
		rev_correct_s=1;	//Correct Rev B2 silicon

	// datalog, 1 if correct match, 0 if not correct
	PiDatalog(func, A_Izpt_Sil_Match_p,		rev_correct_p,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Izpt_Sil_Match_s,		rev_correct_s,		set_fail_bin,	POWER_UNIT);


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
