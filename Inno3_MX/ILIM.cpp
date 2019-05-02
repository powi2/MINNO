//==============================================================================
// ILIM.cpp (User function)
// 
//    void ILIM_user_init(test_function& func)
//    void ILIM(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "ILIM.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ILIM_user_init(test_function& func)
{
	ILIM_params *ours;
    ours = (ILIM_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ILIM(test_function& func)
{
    // The two lines below must be the first two in the function.
    ILIM_params *ours;
    ours = (ILIM_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "ILIM";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_ILIM,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	float	ILIM_S=0.0,
			ILIM_S_Err=0.0,
			DIDT_S=0.0,
			DIDT_S_Err=0.0,
			TON_S=0.0,
			ILIM_70pct_mA_P=0.0,
			ILIM_70pct_P=0.0,
			I2F_S=0.0,
			I2F_S_Err=0.0,
			ILIM_act_S=0.0,
			ILIM_P1_S=0.0,
			ILIM_P1_S_Err=0.0,
			DIDT_P1_S=0.0,
			TON_P1_S=0.0,
			RDSON_P1_S=0.0,
			ILIM_LO_Err_S=0.0,
			ILIM_Med_Err_S=0.0,
			ILIM_High_Err_S=0.0,
			ILIM_Reduce_w_Jitter_132kHz=0.0,
			RxTx_CycReq_cnt			= 0.0,
			RxTx_Hi_BPS_Low_Rcv		= 0.0,
			RxTx_Lo_BPS_Low_Rcv		= 0.0,
			RxTx_Hi_BPS_High_Rcv	= 0.0,
			RxTx_Lo_BPS_High_Rcv	= 0.0,
			Fosc_Sss_P			=0.0,
			tsoft_SSS			=0.0,
			tHandshake_SSS		=0.0,
			Fosc_min_SSS		=0.0,
			Fosc_max_SSS		=0.0,
			fModulation_P		=0.0,
			tRTM				=0.0,
			ILIM_Jit18K_S		=0.0,
			ILIMhi_Jit18K_S		=0.0,
			ILIMLo_Jit18K_S		=0.0,
			Fosc_Mod_18K_S		=0.0,
			tChUp_RTM_P			=0.0;

	float	Dummy_didt=0.0, Dummy_ton=0.0;
	float   Dummy_rdson_peak = 0.0, Dummy_rdson_spec =0.0;
	float	Rdson_peak_rslt =0.0;		// RDSON_P1_S, Rdson_Spec_P
	float   ILIM_peak_rslt = 0.0;

	float	ChB_vrng=0.0;
	int		vrng_b	=0.0;
	int		SR_AF_temp[100]={0};

	float	InvSync_vREF = 0;

	if(OPCODE==4300 || OPCODE==4500) 
	{
		if(MOSFET_SIZE == 2)		InvSync_vREF = 4.5;
		if(MOSFET_SIZE == 3)		InvSync_vREF = 4.5;
		if(MOSFET_SIZE == 4)		InvSync_vREF = 4.0;
		if(MOSFET_SIZE == 5)		InvSync_vREF = 3.0;
		if(MOSFET_SIZE == 6)		InvSync_vREF = 3.0;
		if(MOSFET_SIZE == 7)		InvSync_vREF = 3.0;
		if(MOSFET_SIZE == 8)		
			if (gSiliconRev_P == 3)
				InvSync_vREF = 0.0;	// HQL 3/19/2018 For INN3168C-H106 B3p/B4s ONLY at HOT. This is for RDSON_P1 @ HOT
			else
				InvSync_vREF = 4.0;	// CX 2/15/17
	}
	else if(OPCODE==4400) 
	{
		if(MOSFET_SIZE == 2)		InvSync_vREF = 3.0;
		if(MOSFET_SIZE == 3)		InvSync_vREF = 3.0;
		if(MOSFET_SIZE == 4)		InvSync_vREF = 3.0;
		if(MOSFET_SIZE == 5)		InvSync_vREF = 5.5;
		if(MOSFET_SIZE == 6)		InvSync_vREF = 5.5;
		if(MOSFET_SIZE == 7)		InvSync_vREF = 5.5;
		if(MOSFET_SIZE == 8)		InvSync_vREF = 5.5;
	}
	else ////4200 & 4250
	{
		if(MOSFET_SIZE == 2)		InvSync_vREF = 1.0;//was 3.0
		if(MOSFET_SIZE == 3)		InvSync_vREF = 1.0;//was 3.0
		if(MOSFET_SIZE == 4)		InvSync_vREF = 1.0;//was 3.0
		if(MOSFET_SIZE == 5)		InvSync_vREF = 1.0;//was 3.0
		if(MOSFET_SIZE == 6)		InvSync_vREF = 1.0;//was 3.0
		if(MOSFET_SIZE == 7)		InvSync_vREF = 1.0;//was 3.0
		if(MOSFET_SIZE == 8)		InvSync_vREF = 1.0;//was 3.0
	}

	gFind_ILIM_Jitter	= 0;
	FIND_RDSON_Peak_FLAG = 0;		// Will be reset at the end of  Gage_Find_Ilim func

	//Reset Jitter ILIM variables
	gIdmax_Jitter_132kHz = DEFAULT_VALUE;
	gIdmin_Jitter_132kHz = DEFAULT_VALUE;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//pulse.do_pulse();

	/********************************************************************************
	 *					ILIM Post trim:												*
	 * Note: If ILIM measure from testmode, ILIM should shows flat from scope.		*
	 *		 In normal-mode, ILIM will show Jitter from scope.						*
	 ********************************************************************************/

	PV3_Charge_On(RANGE_100_V);	//Prepare PV3 before power-up

	//************************************************************************************************************************
	//************************* ILIM_NORM  && RDSON_SPEC START ***************************************************************
	//************************************************************************************************************************
	// Setup Digitizer //
	SAMPLE_SIZE = GAGE_POST_32K;
	INNO_Gage_ChanAB_setup(0.07);	// Only do it if SAMPLE_SIZE is diff from previous. (Each input/trig control function takes 4ms)
	//pulse.do_pulse();
	Gage_Capture_Ilim(ILIM_NORM, InvSync_vREF);

	// Process data
	WAVE_NAME =  "ILIM_NORM";
	Gage_Find_Ilim_MINNO(&ILIM_S, &DIDT_S, &TON_S, &Dummy_rdson_peak, &Dummy_rdson_spec);

	I2F_S = ILIM_S *ILIM_S * 100e3 * 1e-3;	//FB clocking request at 100kHz hence multiply by 100e3
	// Calculate ILIM_act trim
	if( gILIM_pt_S !=0)
		ILIM_act_S = (ILIM_S/gILIM_pt_S -1)*100;
	else 
		ILIM_act_S = 999.0;

	ILIM_S_Err = (ILIM_S/gILIM_TARGET_S - 1.0)*100.0;
	DIDT_S_Err = (DIDT_S/gDIDT_TARGET - 1.0)*100.0;
	I2F_S_Err = (I2F_S/gI2F_S_TARGET - 1.0)*100.0;

	ILIM_LO_Err_S = gILIM_pct_1stP-(gILIM_LO_TARGET/gILIM_TARGET_S)*100;
	ILIM_Med_Err_S = gILIM_pct_2ndP-(gILIM_LO_Med_TARGET/gILIM_TARGET_S)*100;
	ILIM_High_Err_S = gILIM_pct_3rdP-(gILIM_UP_Med_TARGET/gILIM_TARGET_S)*100;

	Power_Down_Everything_Except_Buf_Clamp();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	delay(4);

	/********************************************************************************
	 *				ILIM_P1: Secondary Control (ZF-P MUST TRIMMED)					*
	 ********************************************************************************/
	if (gTrim_iLselOff_P == 0)
	{
		//pulse.do_pulse();
		Gage_Capture_Ilim(ILIM_INCR, InvSync_vREF);

		// Process data
		WAVE_NAME =  "ILIM_P1";
		FIND_RDSON_Peak_FLAG = 0;
		Gage_Find_Ilim_MINNO(&ILIM_P1_S, &DIDT_P1_S, &TON_P1_S, &Dummy_rdson_peak, &Dummy_rdson_spec);

		if(gTrim_iLselOff_P)
		{
			gIlim_Incr_max = gILIM_TARGET_S;
		}
		else
		{
			gIlim_Incr_max = gILIM_TARGET_S * ( 1 + (2 * (float)(gTrim_iLRatio_P ^ 13) / 100));
		}

		ILIM_P1_S_Err = (ILIM_P1_S/gIlim_Incr_max -1.0) * 100.0;

	/********************************************************************************
	 *				Rdson at ILIM_P1 peak:	Secondary control						*
	 ********************************************************************************/
		Close_relay(K10);			// Drain to Rdson Buffer
		delay(4);

		PV3_Check_Charge(RANGE_100_V);
		pv3_4->charge_off();

		if(OPCODE==4300 ||OPCODE==4500)
		{
			PV3_Connect_Drain_and_DriveON(Vind_RM+1.5); //Drive Voltage
		}
		else
		{
			PV3_Connect_Drain_and_DriveON(Vind_RM); //Drive Voltage
		}

		// Enable RTM by switch >110kHz for >200usec. //
		//ddd_7->ddd_run_pattern(FB_125kHz_pulse_start_X,FB_125kHz_pulse_stop_X);
		//DDD_Wait_Pattern_End(FB_125kHz_pulse_start_X,FB_125kHz_pulse_stop_X);
		ddd_7->ddd_run_pattern(FB_125kHz_pulse_start_X,FB_125kHz_pulse_stop_X);
		DDD_Wait_Pattern_End(FB_125kHz_pulse_start_X,FB_125kHz_pulse_stop_X);

		Gage_Start_Capture();

		ddd_7->ddd_run_pattern(FB_100kHz_ILIM_pulse_start_X,FB_100kHz_ILIM_pulse_stop_X);
		DDD_Wait_Pattern_End(FB_100kHz_ILIM_pulse_start_X,FB_100kHz_ILIM_pulse_stop_X);

		Gage_Wait_For_Capture_Complete();

		PV3_Disconnect_Drain_and_DriveOFF();

		// Process data
		WAVE_NAME =  "ILIM_P1_RDSON_PEAK";
		FIND_RDSON_Peak_FLAG = 1;		// Will be reset at the end of  Gage_Find_Ilim func
		Gage_Find_Ilim(&ILIM_peak_rslt, &Dummy_didt, &Dummy_ton, &Rdson_peak_rslt, &Dummy_rdson_spec);

		// Use ILIM_P1_S without Rdson buffer connected for more accurate measurement. 
		if (ILIM_P1_S !=0)
			RDSON_P1_S = (Rdson_peak_rslt * ILIM_peak_rslt) /ILIM_P1_S;
		else
			RDSON_P1_S = 999.0;

		Power_Down_Everything_Except_Buf_Clamp();
		Open_All_Relays();
		Disconnect_InvSyn_IM();
		delay(4);
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tChUp_RTM-P //
	// Measures how accurate the 1us RTM charge up time is.  Goto observe mode address 3 (DchUp).
	// 1usec pulse should show up on Vpin when gate turns off.
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	Close_relay(K3); // Drain to dvi through pullup resistor. //

	// Drain (0V/3mA)
	D_dvi->set_voltage(D_ch, 0.0,		VOLT_50_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);
	//wait.delay_10_us(20);

	//// UV pin (Vpin) set to 0V before PU
	VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_10_V);
	VPIN_ovi->set_current(VPIN_ch, 20e-3,		RANGE_30_MA);

	// BPP set 0V
	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	//wait.delay_10_us(5);
	delay(4);

	// BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2);	// vstart, vstop, vstep	

	// Initialize DDD
	ddd_7->ddd_set_lo_level(0.0);
	wait.delay_10_us(10);
	ddd_7->ddd_set_hi_level(5.0);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	//DDD_Wait_Pattern_End(Low_XXX_pat_start,Low_XXX_pat_stop);
	Close_relay(K12);						// Connect DDD7_1	to Vpin(UV)	pin
	
	// Setup Vpin for digital clocking
	VPIN_ovi->disconnect(VPIN_ch);
	delay(4);

	// Vpin pulse 2 times for Program mode. Then wiggle BPP pin to get into Observe mode. //
	ddd_7->ddd_run_pattern(Vpin_2clocks_start, Vpin_2clocks_stop);
	DDD_Wait_Pattern_End(Vpin_2clocks_start, Vpin_2clocks_stop);

	// Set BPP //
	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);
	wait.delay_10_us(5);
	VBPP_ramp_down(gVBPP_PV_final, 5.0, 50e-3);	// vstart, vstop, vstep
	wait.delay_10_us(20);
	VBPP_ramp_down(5.0, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

	// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
	int ILIM_Select = ILIM_NORM;
	if     (ILIM_Select == ILIM_NORM)	wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
	else if(ILIM_Select == ILIM_INCR)	wait.delay_10_us(150);	// 10 uF (ILIM+1) 1.2ms //

	// Set BPP below VBP- //
	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
	wait.delay_10_us(10);

	// Lower Vpin voltage because max RDSon buffer input is clamped to 4.4V. //
	ddd_7->ddd_set_hi_level(4.0);
	wait.delay_10_us(10);                 //HL Do not remove. Else, DDD will be corrupted.
	// Connect Vpin to 5kohm pullup resistor. //
	Open_relay(K12);
	Close_relay(K16);
	Close_relay(KC6);
	Open_relay(KC5);

	// Connect Vpin to RDSon buffer circuit. //
	tmu_6->close_relay(TMU_EXT_DRV2);
	delay(4);

	// Vpin //
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
	DDD_Wait_Pattern_End(High_pat_start, High_pat_stop);

	// Set BPP above VBP+ // 
	BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
	VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final+20e-3, 10e-3);	// vstart, vstop, vstep	B3 material
	wait.delay_10_us(10);

	// Part should now be in Observe mode. //

	// Clock Vpin three times to look at DChUp observe signal. //
	ddd_7->ddd_run_pattern(Vpin_3NegClocks_start, Vpin_3NegClocks_stop);
	wait.delay_10_us(350);	// use fixed delay here!!!
	Gage_Start_Capture();
	CsDo(hSystem, ACTION_FORCE); // Force capture. //
	Gage_Wait_For_Capture_Complete();

	// Search result //
	Gage_Find_DChUp(&tChUp_RTM_P);

	Power_Down_Everything_Except_Buf_Clamp();
	Open_All_Relays();
	delay(4);

	//************************************************************************************************************************
	//************************* ILIM Jitter 18kHz  ***************************************************************************
	//************************************************************************************************************************
	SAMPLE_SIZE = GAGE_POST_512K;
	INNO_Gage_ChanAB_setup(0.1);	// Only do it when SAMPLE_SIZE is diff from previous. Each input control and trig control function takes 4ms.

	Gage_Capture_Ilim(ILIM_Jit18K, InvSync_vREF);

	// Process data
	WAVE_NAME =  "ILIM_18kHz";
	Gage_Find_Ilim_18kHz(&ILIM_Jit18K_S, &ILIMhi_Jit18K_S, &ILIMLo_Jit18K_S, &Fosc_Mod_18K_S);

	Power_Down_Everything_Except_Buf_Clamp();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	delay(4);

	//Samsung bit trimmed
	if(gTrim_SAM_P)
	{
		//********************************************************************************************/
		//******************** ILIM - 70% - Samsung Soft Start****************************************/
		//********************************************************************************************/
		SAMPLE_SIZE = GAGE_POST_256K;
		INNO_Gage_ChanAB_setup(0.1);	// Only do it if SAMPLE_SIZE is diff from previous. (Each input/trig control function takes 4ms)

		Gage_Capture_Ilim_SSS(ILIM_SSS, InvSync_vREF);

		//** Process SoftStart data:  Find all parameters **	
		WAVE_NAME =  "ILIM_tSoftRamp";
		//Gage_Find_Ilim_SSS(&ILIM_70pct_mA_P, &tsoft_SSS, &tHandshake_SSS, &Fosc_min_SSS, &Fosc_max_SSS, &gIdmax_Jitter_132kHz, &gIdmin_Jitter_132kHz, &fModulation_P, &Fosc_Sss_P, &tRTM);
		Gage_Find_Ilim_SSS_MINNO(&ILIM_70pct_mA_P, &tsoft_SSS, &tHandshake_SSS, &Fosc_min_SSS, &Fosc_max_SSS, &gIdmax_Jitter_132kHz, &gIdmin_Jitter_132kHz, &fModulation_P, &Fosc_Sss_P, &tRTM);

		ILIM_Reduce_w_Jitter_132kHz = (1 - gIdmax_Jitter_132kHz / gIdmin_Jitter_132kHz) * 100;
	//	ILIM_70pct_P = (ILIM_70pct_mA_P / ILIM_S)*100.0;
		ILIM_70pct_P = (ILIM_70pct_mA_P / gIdmin_Jitter_132kHz)*100.0;
		g_tHandshake_SSS = int(tHandshake_SSS*1e6/10);
		if(g_tHandshake_SSS<5 || g_tHandshake_SSS>99)	g_tHandshake_SSS=6;	//FWPK use this variable.  Could not be < 6

		// Power down
		Power_Down_Everything_Except_Buf_Clamp();
		Open_All_Relays();
		Disconnect_InvSyn_IM();
		delay(4);
	}

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//  RxTx_HiBPS_Lorcv-  With High BPS at 4.4V.
	// 
	// In test mode 1, the receiver threshold can be changed by changing the Vpin level. 
	// With Vpin low, the receiver threshold is standard.
	// With Vpin high, the receiver threshold is increased by 5mV. //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	SAMPLE_SIZE = GAGE_POST_64K;
	RxTx_CycReq_cnt = 100;	//Total number of requested counts from FB on secondary side

	//	Set up Buffer Clamp
	//ChB_vrng = 5.0;
	//BC_ovi->set_current(BC_ch, 30e-3,		RANGE_30_MA);
	//BC_ovi->set_voltage(BC_ch, (ChB_vrng-0.6),VOLT_5_RANGE);	// OVI_1_3 Account for one diode drop
	//wait.delay_10_us(10);

	// Channel B setup //
	INNO_Gage_ChanB_setup(1.0);

	Close_relay(K3);	// Drain to dvi through pullup resistor. //
	Close_relay(K10);	// Connect drain to RDS buffer circuit to digitize drain waveform. //

	// Drain //
	D_dvi->set_voltage(D_ch, 0.0, VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);	// DVI_11_0
	delay(4);
	
	//PROG mode to program out XFWPK bit to disable FWPK switching.
	// Also Program out the External FB option

	Powerup_Secondary_in_Testmode(gProgRead_AFreg_S, 0, 0);
	//wait.delay_10_us(20);

	if(OPCODE==4200 || OPCODE==4250)
	{
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final,	VOLT_10_RANGE);
	}
	else //HOT temperature 125C
	{
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final+50e-3,	VOLT_10_RANGE);	
	}
	wait.delay_10_us(10);

	// Read/write AF register
	Read_Secondary_AF_Reg (SR_AF_temp);	// must be followed by write
	// MINNO Trim bits
	// PROG mode to program out XFWPK bit to disable FWPK switching
	// Also Program out the External REQ option
	// Write corrected bits into AF register
	SR_AF_temp[5]=0;				// Programming out PK1&Xspeedload
	SR_AF_temp[6]=0;				// Programming out PK2
	SR_AF_temp[7]=0;				// Programming out PK3
	SR_AF_temp[22]=0;				// Programming out PKdig<1>
	SR_AF_temp[23]=0;				// Programming out PKdig<2>
	SR_AF_temp[24]=0;				// Programming out PKdig<3>
	SR_AF_temp[25]=0;				// Programming out PKdig<4>
	SR_AF_temp[42]=1;				// Programming in  DOPL
	SR_AF_temp[44]=1;				// Programming in  FWPK
	Write_Secondary_AF_Reg (SR_AF_temp);

	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);				// Connect SR to 5nF
	Open_relay(K18);				// Disconnect FW from DVI
	Open_relay(K21);				// Disconnect FW from DDD
	delay(4);

	REQ_ovi->set_voltage(REQ_ch, gREQ_2V, 		RANGE_5_V);
	//wait.delay_10_us(10);
	
	Connect_InvSyn_IM(Low_Load_Vd_Input);

	//VBPP_ramp_down(gVBPP_P_final, gVBPP_P_s_final, 10e-3);	// vstart, vstop, vstep	B3 material
	//wait.delay_10_us(10);

	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 10.0,	RANGE_20_V);	// Avoid noise coupling over to InvSynCircuit to FW
	wait.delay_10_us(10); 

	ddd_7->ddd_set_hi_level(gREQ_2V);
	wait.delay_10_us(10);
	ddd_7->ddd_set_lo_level(gREQ_V_Idle);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	DDD_Wait_Pattern_End(High_pat_REQ_start, High_pat_REQ_stop);
	Close_relay(K17);				// Connect REQ to DDD

	VBPP_Power_Up_w_Test_Mode(gTM1_p,ILIM_NORM);
	D_dvi->set_voltage(D_ch, 1.5, 		VOLT_50_RANGE);	// DVI_11_0	
	InvSyn_REF_ovi->set_voltage(InvSyn_ch, -5.0,		VOLT_20_RANGE);//Added on 11/02/18 to improve stability

	delay(4);	// Wait and Listen time in TM1. Hiep adjusted from 3ms to 4ms.

	// Run 100kHz clocks to avoid the Primary going into Overload Freq.
	ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	DDD_Wait_Pattern_End(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);

	BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
	VBPP_ramp_down(gVBPP_P_final, gVBPP_P_s_final, 50e-3);	// vstart, vstop, vstep	B3 material
	wait.delay_10_us(20);

	Gage_Start_Capture();
	//Issue 100 FB pulses with Normal VBPP requesting primary to switch 100 times and expect 100 ILIM pulses
	ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	DDD_Wait_Pattern_End(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	Gage_Wait_For_Capture_Complete();

	VBPP_ramp_down(gVBPP_P_s_final, 3.5, 50e-3);

	WAVE_NAME =  "RxTx_Hi_BPS_Low_Rcv_cnt";
	Gage_Count_Cycles_CHB(&RxTx_Hi_BPS_Low_Rcv);

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//  RxTx_LoBPS_Lorcv-  With Low BPS at VBPS_M+100mV
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
	VBPP_ramp_up(gVBPP_P_s_final, 5.0, 50e-3); //BPP ramp up from 0 to 5V with 100mV step

	VBPP_ramp_down(gVBPP_P_final, gVBPP_P_s_final, 50e-3);	// vstart, vstop, vstep	B3 material
	//wait.delay_10_us(20);

	VBPS_ramp_down(gVBPS_final, gVBPS_M_Init + 100e-3, 50e-3);
	wait.delay_10_us(10);	// Dont wait for too long here, secondary might loose control
	
	ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	DDD_Wait_Pattern_End(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);

	Gage_Start_Capture();
	//Issue 100 FB pulses with Normal VBPP requesting primary to switch 100 times and expect 100 ILIM pulses
	ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	DDD_Wait_Pattern_End(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	Gage_Wait_For_Capture_Complete();

	VBPP_ramp_down(gVBPP_P_s_final, 3.5, 50e-3);

	//Count Cycles (process gage data)
	WAVE_NAME =  "RxTx_Lo_BPS_Low_Rcv_cnt";
	Gage_Count_Cycles_CHB(&RxTx_Lo_BPS_Low_Rcv);

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//  RxTx_HiBPS_Hircv-  With High BPS at 4.4
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
	VBPP_ramp_up(gVBPP_P_s_final, 5.0, 50e-3); //BPP ramp up from 0 to 5V with 100mV step

	VBPP_ramp_down(gVBPP_P_final, gVBPP_P_s_final, 50e-3);	// vstart, vstop, vstep	B3 material
	//wait.delay_10_us(20);

	if(OPCODE==4200 || OPCODE==4250)
		VBPS_ramp_up(gVBPS_M_Init + 100e-3, gVBPS_final, 50e-3);        //HL changed the stepsize from 20mV to 50mV
	else
		VBPS_ramp_up(gVBPS_M_Init + 100e-3, gVBPS_final+100e-3, 50e-3); //HL added 100mV due to hot failure.

	wait.delay_10_us(10);	// Dont wait for too long here, secondary might loose control

	// Bring up Vpin. //
	// Vpin must be high to enable the elevated receiver threshold.  With Vpin 
	// low, the receiver threshold is standard.  With Vpin high, the receiver 
	// threshold is increased by 5mV. // 
	VPIN_ovi->set_voltage(VPIN_ch, 5.0, RANGE_10_V);
	wait.delay_10_us(10);	// Dont wait for too long here, secondary might loose control

	ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	DDD_Wait_Pattern_End(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);

	Gage_Start_Capture();
	//Issue 100 FB pulses with Normal VBPP requesting primary to switch 100 times and expect 100 ILIM pulses
	ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	DDD_Wait_Pattern_End(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	Gage_Wait_For_Capture_Complete();

	VBPP_ramp_down(gVBPP_P_s_final, 3.5, 50e-3);

	WAVE_NAME =  "RxTx_Hi_BPS_High_Rcv_cnt";
	Gage_Count_Cycles_CHB(&RxTx_Hi_BPS_High_Rcv);

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//  RxTx_LoBPS_Hircv-  With Low BPS at VBPS_M+100mV
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
	VBPP_ramp_up(gVBPP_P_s_final, 5.0, 50e-3); //BPP ramp up from 0 to 5V with 100mV step

	VBPP_ramp_down(gVBPP_P_final, gVBPP_P_s_final, 50e-3);	// vstart, vstop, vstep	B3 material
	//wait.delay_10_us(20);

	VBPS_ramp_down(gVBPS_final, gVBPS_M_Init + 100e-3, 50e-3);
	wait.delay_10_us(10);	// Dont wait for too long here, secondary might loose control

	ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	DDD_Wait_Pattern_End(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);

	Gage_Start_Capture();
	//Issue 100 FB pulses with Normal VBPP requesting primary to switch 100 times and expect 100 ILIM pulses
	ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	DDD_Wait_Pattern_End(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	Gage_Wait_For_Capture_Complete();

	VBPP_ramp_down(gVBPP_P_s_final, 3.5, 50e-3);

	WAVE_NAME =  "RxTx_Lo_BPS_High_Rcv_cnt";
	Gage_Count_Cycles_CHB(&RxTx_Lo_BPS_High_Rcv);

	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	delay(4);

	// Datalog
	PiDatalog(func, A_IlimHigh_JitterLow_S,			gIdmax_Jitter_132kHz,			set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_IlimLow_JitterHigh_S,			gIdmin_Jitter_132kHz,			set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_ILIM_Jit132K_S,				ILIM_Reduce_w_Jitter_132kHz,	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_ILIM_Jit18K_S,				ILIM_Jit18K_S,					set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IlimHigh_JitterLow_18kHz_S,	ILIMhi_Jit18K_S,				set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_IlimLow_JitterHigh_18kHz_S,	ILIMLo_Jit18K_S,				set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_Fosc_Mod_18kHz_S,				Fosc_Mod_18K_S,					set_fail_bin,	POWER_KILO);

	if (strcmp("INN3468C-HR09", Dev_id) == 0 || strcmp("INN3468C-HY11", Dev_id) == 0 || strcmp("INN3468C-HZ12", Dev_id) == 0)
	{
		float LSL = gILIM_TARGET_S * 0.93;
		float USL = gILIM_TARGET_S * 1.07;
		func.dlog->set_test_no(A_ILIM_S + 1);
		func.dlog->set_min_limit_value(LSL);
		func.dlog->set_max_limit_value(USL);
	}
	PiDatalog(func, A_ILIM_S,			ILIM_S,				set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_DIDT_S,			DIDT_S,				set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_TON_S,			TON_S,				set_fail_bin,	POWER_MICRO);

	PiDatalog(func, A_I2F_S,			I2F_S,				set_fail_bin,	POWER_UNIT);

	PiDatalog(func, A_ILIM_Low_S,				gILIM_pct_1stP,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_ILIM_Med_S,				gILIM_pct_2ndP,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_ILIM_High_S,				gILIM_pct_3rdP,				set_fail_bin,	POWER_UNIT);

	if(TRIM_ENABLE)
	{
		PiDatalog(func, A_ILIM_exp_S,	gILIM_exp_S,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_ILIM_act_S,	ILIM_act_S,			set_fail_bin,	POWER_UNIT);
	}

	//PiDatalog(func, A_ILIM_Low_S,				gILIM_pct_1stP,				set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_ILIM_Med_S,				gILIM_pct_2ndP,				set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_ILIM_High_S,				gILIM_pct_3rdP,				set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_ILIM_RTM_Slope,			gRTM_Slope,					set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_tDelta_RTM_Slope_30us_S,	gtDelta_RTM_Slope,			set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_i_pct_drop_RTM,			-gi_pct_drop_RTM,			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_tDelta_RTM_Slope_200us_S,	gtDelta_RTM_Slope_200us,	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_ILIM_200us_S,				gILIM_200us_S,				set_fail_bin, POWER_MILLI);
	PiDatalog(func, A_ILIM_200us_pct_S,			-gILIM_200us_pct_S,			set_fail_bin, POWER_UNIT);

	PiDatalog(func, A_RxTx_CycReq_cnt,		RxTx_CycReq_cnt,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RxTx_Hi_BPS_Low_Rcv,	RxTx_Hi_BPS_Low_Rcv-6,	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RxTx_Lo_BPS_Low_Rcv,	RxTx_Lo_BPS_Low_Rcv-6,	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RxTx_Hi_BPS_High_Rcv,	RxTx_Hi_BPS_High_Rcv-6,	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_RxTx_Lo_BPS_High_Rcv,	RxTx_Lo_BPS_High_Rcv-6,	set_fail_bin,	POWER_UNIT);
	
	if(gTrim_iLselOff_P==0)
	{
		int result = 99;
		char *ptr_Dev_id = Dev_id;
		while (*ptr_Dev_id != '\0')
		{
			*ptr_Dev_id = toupper((unsigned char)*ptr_Dev_id);
			++ptr_Dev_id;
		}
		if (strcmp("INN3468C-HR09", Dev_id) == 0 || strcmp("INN3468C-HY11", Dev_id) == 0 || strcmp("INN3468C-HZ12", Dev_id) == 0)
		{
			float LSL = 2.6 * 0.93;
			float USL = 2.6 * 1.07;
			func.dlog->set_test_no(A_ILIM_P1_S + 1);
			func.dlog->set_min_limit_value(LSL);
			func.dlog->set_max_limit_value(USL);
		}

		PiDatalog(func, A_ILIM_P1_S,		ILIM_P1_S,		set_fail_bin,	POWER_MILLI);
		PiDatalog(func, A_DIDT_P1_S,		DIDT_P1_S,		set_fail_bin,	POWER_MILLI);
		PiDatalog(func, A_TON_P1_S,			TON_P1_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_RDSON_P1_S,		RDSON_P1_S,		set_fail_bin,	POWER_UNIT);
	}
	

	if(gDisplay_ErrDlog)
	{
		PiDatalog(func, A_ILIM_Err_S,		ILIM_S_Err,			set_fail_bin,	POWER_UNIT);
		/*PiDatalog(func, A_DIDT_Err_S,		DIDT_S_Err,			set_fail_bin,	POWER_UNIT);
		PiDatalog(func, A_I2F_Err_S,		I2F_S_Err,			set_fail_bin,	POWER_UNIT);
		PiDatalog(func, A_ILIM_Low_Err_S,			ILIM_LO_Err_S,				set_fail_bin,	POWER_UNIT);
		PiDatalog(func, A_ILIM_Med_Err_S,			ILIM_Med_Err_S,				set_fail_bin,	POWER_UNIT);
		PiDatalog(func, A_ILIM_High_Err_S,			ILIM_High_Err_S,*/			/*set_fail_bin,	POWER_UNIT);*/
		if(gTrim_iLselOff_P==0)
		PiDatalog(func, A_ILIM_P1_Err_S,	ILIM_P1_S_Err,	set_fail_bin,	POWER_UNIT);
	}

	if(gTrim_SAM_P || gTrim_DsoftEn_S)
	{
		PiDatalog(func, A_Fosc_Sss_P,			Fosc_Sss_P,					set_fail_bin,	POWER_KILO);
		PiDatalog(func, A_Fosc_Mod_S,			fModulation_P,				set_fail_bin,	POWER_KILO);

		if (strcmp("INN3468C-HR09", Dev_id) == 0 || strcmp("INN3468C-HY11", Dev_id) == 0 || strcmp("INN3468C-HZ12", Dev_id) == 0)
		{
			float LSL = (gILIM_TARGET_S * 0.8) * 0.93;
			float USL = (gILIM_TARGET_S * 0.8) * 1.07;
			func.dlog->set_test_no(A_ILIM_70pct_mA_P + 1);
			func.dlog->set_min_limit_value(LSL);
			func.dlog->set_max_limit_value(USL);
		}
		PiDatalog(func, A_ILIM_70pct_mA_P,		ILIM_70pct_mA_P,			set_fail_bin,	POWER_MILLI);
		PiDatalog(func, A_ILIM_70pct_P,			ILIM_70pct_P,				set_fail_bin,	POWER_UNIT);
		PiDatalog(func, A_tsoft_SSS,			tsoft_SSS,					set_fail_bin,	POWER_MILLI);
		PiDatalog(func, A_tHandshake_SSS,		tHandshake_SSS,				set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_Fosc_min_SSS,			Fosc_min_SSS,				set_fail_bin,	POWER_KILO);
		PiDatalog(func, A_Fosc_max_SSS,			Fosc_max_SSS,				set_fail_bin,	POWER_KILO);
		if(gSiliconRev_P>=3)
			PiDatalog(func, A_tRTMrelease,			tRTM,						set_fail_bin,	POWER_MICRO);
	}

		PiDatalog(func, A_tChUp_RTM_P,			tChUp_RTM_P,				set_fail_bin,	POWER_MICRO);

	if(gDEBUG)
	printf("Function ILIM Done\n");
}
