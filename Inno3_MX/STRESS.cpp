//==============================================================================
// STRESS.cpp (User function)
// 
//    void STRESS_user_init(test_function& func)
//    void STRESS(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "STRESS.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void STRESS_user_init(test_function& func)
{
	STRESS_params *ours;
    ours = (STRESS_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void STRESS(test_function& func)
{
    // The two lines below must be the first two in the function.
    STRESS_params *ours;
    ours = (STRESS_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	Func_name = "STRESS";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_STRESS,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//char *ptr_Dev_id = Dev_id;
	//while (*ptr_Dev_id != '\0')
	//{
	//	*ptr_Dev_id = toupper((unsigned char)*ptr_Dev_id);
	//	++ptr_Dev_id;
	//}
	//if ((strcmp("INN3468C-HZ12", Dev_id) == 0) || (strcmp("INN3468C-HR09", Dev_id) == 0))
	//	gStress_ON = 1;		// STRESS evaluation
	return;// STRESS test disabled temporarily
	// Not stressing at 4250/4300/4500.
	//if(OPCODE==4250 || OPCODE==4300 || OPCODE==4500 || gStress_ON==0)
	if((OPCODE != 4200) || (gStress_ON == 0) || (gTrimmed_Device == 1)) // && (strcmp("INN3468C-HZ12", Dev_id) != 0)))
	{
		g_Stress_passed = 1;
		return;
	}

	float	BPS_IS1_pre=0.0, BPS_IS1_post=0.0, BPS_IS1_delta=0.0;
	float	BPS_IS2_pre=0.0, BPS_IS2_post=0.0, BPS_IS2_delta=0.0;
	float	BPP_IS1_pre=0.0, BPP_IS1_post=0.0, BPP_IS1_delta=0.0;
	float	BPP_IS2_pre=0.0, BPP_IS2_post=0.0, BPP_IS2_delta=0.0;
	float	ILL_REQ_post	= 99 uA,
			ILL_D_post		= 99 uA,
			ILL_UV_post		= 99 uA,
			ILL_VO_post		= 99 uA,
			ILL_FW_post		= 99 uA;
	float	ILH_REQ_post	= 99 uA,
			ILH_D_post		= 99 uA,
			ILH_UV_post		= 99 uA,
			ILH_VO_post		= 99 uA,
			ILH_FW_post		= 99 uA;
	float	ILL_REQ_delta	= 99 uA,
			ILL_D_delta		= 99 uA,
			ILL_UV_delta	= 99 uA,
			ILL_VO_delta	= 99 uA,
			ILL_FW_delta	= 99 uA;
	float	ILH_REQ_delta	= 99 uA,
			ILH_D_delta		= 99 uA,
			ILH_UV_delta	= 99 uA,
			ILH_VO_delta	= 99 uA,
			ILH_FW_delta	= 99 uA;
	float	Vstress_frc = 0;
	int		i;
	int		test_fail = 0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	
	Vstress_frc = ours->vStress;
	if(Vstress_frc == -99)
		Vstress_frc = 8.0;
	else if(Vstress_frc == 0)
		return;

	PiDatalog(func, A_STRESS_Voltage,		Vstress_frc,		set_fail_bin,	POWER_UNIT);

	Set_Default_VIrange();
	Reset_VI();
/****************************************************************************
 *	BPS_IS1 and BPS_IS2 Pre Stress											*
 ****************************************************************************/
	VBPP_Negative_Cycle();
//	tmu_6->init();
	Close_relay(K3);

	//Rasco Note: Vin_Minus varies from -1.8V to -3.2V.
    //			  Vin_plus sets to -2.5V (OVI_1_4 sets to -5V), which is good for all devices.

	//ET Note:    Vin_Minus varies from -1.9V to -3.6V.
    //			  Vin_plus sets to -2.5V (OVI_1_4 sets to -5V), which is good for all devices.

    //=======> Both RS & ET can share the same setting for Vinplus.

	SyncHS_PowerUp_Secondary_in_Test_Mode_MINNO(gTM1_p,ILIM_NORM);	//Expect device to switch ON ~2.2ms, OFF ~62ms
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF
	BPP_ovi->set_current(BPP_ch, 3e-3, RANGE_3_MA);	//lower the BPP current range.
	delay(3);
	//FB_ovi->set_voltage(FB_ch, gCVth_15pct_Higher,		RANGE_2_V);	// OVI_1_2	
	//wait.delay_10_us(50);
	//FB_ovi->set_voltage(FB_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2		Try for low CV_init
	//wait.delay_10_us(10);

	//Setup to measure IS2-S
	// Needs to move the current of Sec here to catch the full switching freq.
	/*BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);
	BPS_IS2_pre = BPS_dvi->measure_average(10);*/

	//IS1_S (Not Switching)
	BPS_IS1_pre = gIBPS_nsw;	//This test is done twice.  Once in VBP_Init searching vPlus and VBP_Supply searching vPlus as well

	// BPP_IS2
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
	wait.delay_10_us(8);
	BPP_IS2_pre = BPP_ovi->measure_average(10);

	// BPP IS1
	REQ_ovi->set_voltage(REQ_ch, 0.9,		RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(50);
	if(gSiliconRev_P >= 3)		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
	else						BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);

	//BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);

	BPP_ovi->set_current(BPP_ch, 0.001, RANGE_3_MA);
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
	wait.delay_10_us(40);
	//delay(2);
	BPP_IS1_pre = BPP_ovi->measure_average(10);

	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();

	
	//

	//Open_relay(K2);		// disconnect DVI11_0 from Drain
	//Open_relay(K18);	// disconnect DVI11_1 from FW pin
	//Close_relay(K3);	// Connect dvi-11-0 to R1(50ohm),L1(82uH) to Drain
	//// Close K12 to connect DDD to VPIN
	////SR_dvi2k->open_relay(CONN_FORCE1);
	////SR_dvi2k->open_relay(CONN_SENSE1);
	////Close_relay(K5);//Connect SR to 5nF
	//delay(1);
	////Connect_InvSyn_IM(Low_Vd_Input);// Connect the Sync Circuit while the device is quiet to help with the glitch on drain.

	//Set_VI(res_VPIN_ovi, 0.0 V, 30 mA);
	////VPIN_ovi->disconnect(VPIN_ch);				// Disconnect OVI from UV
	//Set_Vrange(res_D_dvi, RANGE_50_V);
	//Set_VI(res_D_dvi, 0.0 V, 300 mA);
	//Set_I(res_BPP_ovi, 30 mA);
	//VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2);	// vstart, vstop, vstep	
	//
	//wait.delay_10_us(100);  
	//// Initialize DDD
	//ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	//wait.delay_10_us(10);
	//ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	//wait.delay_10_us(10);
	//ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	//wait.delay_10_us(50);

	//VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
	//Close_relay(K12);// Close K12 to connect DDD to VPIN
	//delay(4);
	//
	//Force_Vpin_Pulses_5_Times(5.0, 0.0);
	//wait.delay_10_us(10);

	//Set_VI(res_D_dvi, 45.0 V, 300 mA);
	//wait.delay_10_us(50);

	//Connect_InvSyn_IM(Low_Vd_Input);
	//
	////Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	//VBPP_ramp_up(5.0 V, gVBPP_PV_Init, 50 mV);
	//wait.delay_10_us(50);
	//VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init + 250 mV, 100 mV);	// vstart, vstop, vstep
	//wait.delay_10_us(5);

	////BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
	//Set_V(res_BPP_ovi, gVBPP_M_Init - 200 mV);
	//wait.delay_10_us(50);
	//Set_I(res_BPP_ovi, 3 mA);
	//VBPP_ramp_up(gVBPP_M_Init - 200 mV, gVBPP_P_final, 10 mV);	// vstart, vstop, vstep	B3 material
	//wait.delay_10_us(10);
	//
	//Open_relay(K12);
	//VPIN_ovi->connect(VPIN_ch);// Reconnect OVI from UV
	//ddd_7->ddd_set_hi_level(0.0);		// Will immediately change to this level upon execution
	//wait.delay_10_us(100);
	//
	//SR_dvi2k->open_relay(CONN_FORCE1);
	//SR_dvi2k->open_relay(CONN_SENSE1);
	//Close_relay(K5);//Connect SR to 5nF
	//delay(2);
	//
	//Set_VI(res_VO_dvi, 5.0 V, 300 mA);
	//REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	////Close_relay(K17);	//REQ   to   DDD
	//FWC_dvi2k->open_relay(CONN_FORCE0);
	//FWC_dvi2k->open_relay(CONN_SENSE0);
	//ACK_ovi->disconnect(ACK_ch);
	//delay(4);


 //   Set_I(res_BPS_dvi, 300 mA);
	//VBPS_Power_Up(gVBPS_P_Init - 300 mV);	
	////Set_VI(res_BPS_dvi, gVBPS_final, 300 mA);

	//ddd_7->ddd_set_hi_level(gREQ_2V);
	//wait.delay_10_us(10);
	//ddd_7->ddd_set_lo_level(gREQ_V_Idle);
	//wait.delay_10_us(10);

	//ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	//wait.delay_10_us(10);
	//VO_dvi->set_voltage(VO_ch, 3.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
	//wait.delay_10_us(10);
	//	 
	//Close_relay(K17);	//FB   to   DDD
	//		//Must leave 2ms here for the SSS 70pct ILIM-P to capture at least 40 cycles (1/25kHz =~40us. 40x40us = 1600us = 1.6ms)
	//delay(5);
	////ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	////DDD_Wait_Pattern_End(High_pat_REQ_start, High_pat_REQ_stop);
	////
	////BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);
	//	//BPS_dvi->set_voltage(BPS_ch, 5, 	VOLT_10_RANGE);
	//// Secondary vBPS_plus	//Connect REQ pin to DDD to run 100KHz pulses
	//	//wait.delay_10_us(10);
	////// Secondary vBPS_plus	//Connect REQ pin to DDD to run 100KHz pulses
	////wait.delay_10_us(10);
	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//wait.delay_10_us(5);
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);
	//	//BPS_dvi->set_voltage(BPS_ch, 5, 	VOLT_10_RANGE);
	//// Secondary vBPS_plus	//Connect REQ pin to DDD to run 100KHz pulses
	//	wait.delay_10_us(10);
	//	
	//ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	//wait.delay_10_us(10);
	////DDD_Wait_Pattern_End(High_pat_REQ_start, High_pat_REQ_stop);
	//
	//ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	//wait.delay_10_us(30);

	// BPS_IS2_pre = BPS_dvi->measure_average(25); //expect ~10mA with SR switching.
	////IS2 (Switching)
	////BPS_IS2_pre = Meas_VIaverage(res_BPS_dvi, MEASURE_CURRENT, 25);
	////BPP_IS2_pre = Meas_VIaverage(res_BPP_ovi, MEASURE_CURRENT, 10);

	////Set_VI(res_D_dvi, 2.0 V, 300 mA);
	////Set_V(res_BPP_ovi, gVBPP_P_s_final);
	//wait.delay_10_us(100);
	// //delay(1);
	////IS1 (Not Switching)
	//BPS_IS1_pre = gIBPS_nsw;	//This test is done in VBP_Init searching vPlus
	////BPP_IS1_pre = Meas_VIaverage(res_BPP_ovi, MEASURE_CURRENT, 10);

	//Power_Down_Everything();
	//Open_All_Relays();
	//Disconnect_InvSyn_IM();



    Open_relay(K2);		// disconnect DVI11_0 from Drain
	Open_relay(K18);	// disconnect DVI11_1 from FW pin
	Close_relay(K3);	// Connect dvi-11-0 to R1(50ohm),L1(82uH) to Drain
	delay(4);
	
	VBPP_Negative_Cycle();
	if(1)
	{
		//Vpin (0V)
		VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
		VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
		
		//Drain (0V/3mA)
		D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
		D_dvi->set_voltage(D_ch, 0, 		VOLT_50_RANGE);	// DVI_11_0	
		//D_dvi->set_voltage(D_ch, 45.0, 		VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(20);

		//BPP set 0V
		BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
		VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2);	// vstart, vstop, vstep	
		// Initialize DDD
		wait.delay_10_us(100);  	
		ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
		delay(1);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(50);

		VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
		// Close K12 to connect DDD to VPIN
		Close_relay(K12);
		delay(4);
		Force_Vpin_Pulses_5_Times(5.0, 0.0);	
		wait.delay_10_us(10);

		D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
		D_dvi->set_voltage(D_ch, 45.0, 			VOLT_50_RANGE);	// DVI_11_0
		wait.delay_10_us(50);

		Connect_InvSyn_IM(Low_Vd_Input);// Connect the Sync Circuit while the device is quiet to help with the glitch on drain.
										// This glitch was much noticible and much worse on Turret setup.

		//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
		VBPP_ramp_up(5.0, gVBPP_PV_Init, 50e-3);		
		//Drain stays at 0V so BPP signal will be cleaner
		//dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
		//wait.delay_10_us(10);
		wait.delay_10_us(50);
		VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(5);

		//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
		ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-200e-3, RANGE_10_V);
		wait.delay_10_us(50);
		if(gSiliconRev_P >= 3)
		{
			BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
			VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
			wait.delay_10_us(10);
		}
		else
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+50e-3, RANGE_10_V);
			wait.delay_10_us(30);
		}
		/*dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
		wait.delay_10_us(10);*/
		// Open K12 
		Open_relay(K12);
		VPIN_ovi->connect(1);// Reconnect OVI from UV
		ddd_7->ddd_set_hi_level(0.0);		// Will immediately change to this level upon execution
		wait.delay_10_us(100);
		
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);
		Close_relay(K5);//Connect SR to 5nF
		delay(2);

		//ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//This could cause a 1V glitch at BPS for 50us
		//wait.delay_10_us(10);

		//Vout (0V)
		VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
		//FB (2V)  pull FB above CVth to force No Switching
		REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
		//REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	

		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 300mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
		//VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal
		VBPS_Power_Up(gVBPS_P_Init-0.3);	
		if(LB_Rev >= 5)		ddd_7->ddd_set_hi_level(1.7);
		else				ddd_7->ddd_set_hi_level(gCVth_15pct_Higher);	
		ddd_7->ddd_set_lo_level(0.9);
		wait.delay_10_us(100);
		
		ddd_7->ddd_run_pattern(Low_FB_pat_start, Low_FB_pat_stop);
		wait.delay_10_us(10);
		VO_dvi->set_voltage(VO_ch, 3.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
		wait.delay_10_us(10);
		 
		Close_relay(K17);	//FB   to   DDD
			//Must leave 2ms here for the SSS 70pct ILIM-P to capture at least 40 cycles (1/25kHz =~40us. 40x40us = 1600us = 1.6ms)
		delay(5);
	//Gage_Start_Capture(  );
		BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
		wait.delay_10_us(5);
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);
		//BPS_dvi->set_voltage(BPS_ch, 5, 	VOLT_10_RANGE);
	// Secondary vBPS_plus	//Connect REQ pin to DDD to run 100KHz pulses
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(Low_FB_pat_start, Low_FB_pat_stop);
		wait.delay_10_us(10);
		
		ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
		wait.delay_10_us(30);
		BPS_IS2_pre = BPS_dvi->measure_average(25); //expect ~10mA with SR switching.
		gIBPS_sw = BPS_IS2_pre;
		//pulse.do_pulse();
		wait.delay_10_us(100);
		
		
	}

	//Power down
 	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	wait.delay_10_us(100);                           // HL do not remove delay.  Else, it will corrupt the DDD pattern.
	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_2_V);	// OVI_1_2
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	wait.delay_10_us(5);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);	
	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_2_RANGE);	// DVI_9_1
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	wait.delay_10_us(5);
	Open_relay(K17);
	delay(4);

	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();

/****************************************************************************
 *								BPS and VOUT stress							*
 *	BPS to Vstress_frc (Setup func pass para) for 100ms					*
 *  Then Vout to 48V while BPS at 4.5V for 100ms							*
 ****************************************************************************/

	/*******************************************************************************/
	// Primary stress
	/*******************************************************************************/
	Close_relay(K2);
	delay(5);
	VPIN_ovi->set_current(VPIN_ch, 1e-3, RANGE_3_MA);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
	wait.delay_10_us(10);
	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	VBPP_ramp_up(0.0, Vstress_frc, 1.0);
	wait.delay_10_us(10);
	D_dvi->set_current(D_ch, 10e-3, 		RANGE_30_MA);	// DVI_11_0
	D_dvi->set_voltage(D_ch, 50.0, 			VOLT_50_RANGE);	// DVI_11_0
	wait.delay_10_us(10);

	/*******************************************************************************/
	// Secondary stress
	/*******************************************************************************/
	//PROG mode
	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);	//BPS bleeder disabled in PROG mode
	//FW_dvi->set_voltage(FW_ch, -0.5, 		VOLT_50_RANGE);	// DVI_11_1
	//wait.delay_10_us(10);
	FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
	wait.delay_10_us(10);
	Open_relay(K27);
	delay(1);
	VO_dvi->set_current(VO_ch, 30.0e-3,		RANGE_30_MA);	
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_50_RANGE);	// DVI_9_0
	delay(1);
	Close_relay(K18);
	delay(1);
	REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
	wait.delay_10_us(10);
	ddd_7->ddd_set_hi_level(Vstress_frc);				// Will immediately change to this level upon execution
	ddd_7->ddd_set_lo_level(0.1);				// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(Low_pat_REQ_start, Low_pat_REQ_stop);
	wait.delay_10_us(50);
	Close_relay(K17);
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);
	delay(5);
	BPS_dvi->set_current(BPS_ch, 30.0e-3,	RANGE_30_MA);	
	BPS_dvi->set_voltage(BPS_ch, Vstress_frc-1, 		VOLT_10_RANGE);	// DVI_9_1
	wait.delay_10_us(10);
	BPS_dvi->set_voltage(BPS_ch, Vstress_frc, 		VOLT_10_RANGE);	// DVI_9_1
	delay(2);
	VO_dvi->set_current(VO_ch, 30.0e-3,		RANGE_30_MA);	
	VO_dvi->set_voltage(VO_ch, 45.0, 		VOLT_50_RANGE);	// DVI_9_0
	delay(1);
	FW_dvi->set_voltage(FW_ch, 45.0, 		VOLT_50_RANGE);	// DVI_11_1
	delay(1);
	ddd_7->ddd_end_pattern(FB_100kHz_loop_pulse_stop);
	//ddd_7->ddd_end_pattern(FW_Neg_loop_pulse_start);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern();
	wait.delay_10_us(10);
	for (i=0;i<1000;i++)
	{
		wait.delay_10_us(10);
	}
	//delay(100);

	delay(2);
	ddd_7->ddd_stop_pattern();
	wait.delay_10_us(50);
	ddd_7->ddd_set_hi_level(0.1);				// Will immediately change to this level upon execution
	ddd_7->ddd_run_pattern(Low_pat_REQ_start, Low_pat_REQ_stop);
	wait.delay_10_us(10);
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0
	FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
	wait.delay_10_us(50);
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_50_RANGE);	// DVI_9_0
	wait.delay_10_us(50);
	BPP_ovi->set_voltage(BPP_ch, 4.5, 		RANGE_10_V);	// OVI_1_0
	BPS_dvi->set_voltage(BPS_ch, 4.5, 		VOLT_10_RANGE);	// DVI_9_1
	delay(1);
	BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0
	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_10_RANGE);	// DVI_9_1
	delay(1);

	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();

	/*************************************************************************************************************
	*	Leakages After Stress
	*************************************************************************************************************/
	//Connect Relays
	Close_relay(K2);	//Connects Drain to DVI_11_0
	Close_relay(K18);	//Connects FW to DVI_11_1

	//Vpin, VO, BPS to 0V
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_20_V);	// OVI_1_1
	VPIN_ovi->set_current(VPIN_ch, 300.0e-6,		RANGE_300_UA);	

	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, 30.0e-6,		RANGE_30_UA);

	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_1
	BPS_dvi->set_current(BPS_ch, 30.0e-3,	RANGE_30_MA);
	
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 300.0e-3,		RANGE_300_MA);

	BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0
	BPP_ovi->set_current(BPP_ch, 30.0e-6,	RANGE_30_UA);

	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_10_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 200.0e-6,	RANGE_200_UA);

	FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_5_RANGE);	// DVI_11_1
	FW_dvi->set_current(FW_ch, 20.0e-6,		RANGE_30_UA);

	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_10_RANGE);	// DVI_21_1
	SR_dvi2k->set_current(SR_ch, 200.0e-6,	RANGE_200_UA);

	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_10_V);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, 30.0e-6,		RANGE_30_UA);

	//**********************************
	//** Primary Leakages
	//**********************************

	//Drain Low Leakage test only (High leakage is already in BV_Drain function)
	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_CURRENT);
	D_dvi->set_voltage(D_ch, 0.0,			VOLT_10_RANGE); 
	D_dvi->set_current(D_ch, 3e-3,		RANGE_3_MA);		//Use 3mA to bring it to GND faster then smaller Range to 
	wait.delay_10_us(50);
	D_dvi->set_current(D_ch, 300.0e-6,		RANGE_300_UA);		//Use 3mA to bring it to GND faster then smaller Range to 
	wait.delay_10_us(50);
	if(LB_Rev >= 5)
	{
		wait.delay_10_us(450);
	}
	ILL_D_post  = D_dvi->measure_average(15);
	ILL_D_delta = ILL_D_post - gILL_D_pre;

	D_dvi->set_voltage(D_ch, 5.5,			VOLT_10_RANGE); 
	wait.delay_10_us(50);
	//If BPP is set to 5.5V, Vpin at 20V will fail (It has to go through the BPP power cycle)
	BPP_ovi->set_current(BPP_ch, 30.0e-3,	RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, 5.5,		VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)
	wait.delay_10_us(20);
	BPP_ovi->set_voltage(BPP_ch, 4.5,		VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)
	wait.delay_10_us(20);
	BPP_ovi->set_voltage(BPP_ch, 5.1,		VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)


	VPIN_ovi->set_meas_mode(VPIN_ch,		OVI_MEASURE_CURRENT);
	VPIN_ovi->set_voltage(VPIN_ch, 5.5,		RANGE_10_V);		//Bring this back after Vpin BV circuit in place
	wait.delay_10_us(50);
	ILH_UV_post = VPIN_ovi->measure_average(5);		
	ILH_UV_delta = ILH_UV_post - gILH_UV_pre;

	VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_2_V); 
	//wait.delay_10_us(200);
	wait.delay_10_us(50);
	ILL_UV_post = VPIN_ovi->measure_average(5);		
	ILL_UV_delta = ILL_UV_post - gILL_UV_pre;

	//Primary pins set to 0V
	BPP_ovi->set_voltage(BPP_ch, 0.0,		VOLT_10_RANGE); 
	D_dvi->set_voltage(D_ch, 0.0,			VOLT_10_RANGE); 

	//**********************************
	//** Secondary Leakages
	//**********************************

	BPS_dvi->set_current(BPS_ch,	10.0e-3,	RANGE_30_MA);
	BPS_dvi->set_voltage(BPS_ch,	4.5, 		VOLT_5_RANGE);
	wait.delay_10_us(50);
	//ILH_BPS = BPS_dvi->measure_average(5);

	//FW leakage (Make sure it's less than vBPS else it could provide charge to BPS easily)
	FW_dvi->set_meas_mode(FW_ch,				DVI_MEASURE_CURRENT);
	FW_dvi->set_current(FW_ch,		30.0e-6,	RANGE_30_UA);
	FW_dvi->set_voltage(FW_ch,		0.0,		VOLT_5_RANGE);
	wait.delay_10_us(5);
	ILL_FW_post  = FW_dvi->measure_average(5);
	ILL_FW_delta = ILL_FW_post - gILL_FW_pre;

	//REQ leakage
	REQ_ovi->set_meas_mode(REQ_ch,				OVI_MEASURE_CURRENT);
	REQ_ovi->set_voltage(REQ_ch, 0.0,				RANGE_10_V); 
	wait.delay_10_us(5);
	ILL_REQ_post = REQ_ovi->measure_average(5); 
	ILL_REQ_delta = ILL_REQ_post - gILL_REQ_pre;

	//REQ_ovi->set_voltage(REQ_ch, 5.5,				RANGE_10_V); 
	//wait.delay_10_us(50);
	//ILH_REQ_post = REQ_ovi->measure_average(5); 
	//ILH_REQ_delta = ILH_REQ_post - gILH_REQ_pre;
	//REQ_ovi->set_voltage(REQ_ch, 0.0,				RANGE_10_V); 
	
	//Vout Leakage	(Low Leakage test only.  Vout can provide charge to BPS)
	VO_dvi->set_meas_mode(VO_ch,				DVI_MEASURE_CURRENT);
	wait.delay_10_us(50);
	ILL_VO_post = VO_dvi->measure_average(5);		
	ILL_VO_delta = ILL_VO_post - gILL_VO_pre;
	
	Power_Down_Everything();
	Open_All_Relays();

/****************************************************************************
 *	BPS_IS1 and BPS_IS2 Post Stress											*
 ****************************************************************************/
	VBPP_Negative_Cycle();
//	tmu_6->init();
	Close_relay(K3);

	//Rasco Note: Vin_Minus varies from -1.8V to -3.2V.
    //			  Vin_plus sets to -2.5V (OVI_1_4 sets to -5V), which is good for all devices.

	//ET Note:    Vin_Minus varies from -1.9V to -3.6V.
    //			  Vin_plus sets to -2.5V (OVI_1_4 sets to -5V), which is good for all devices.

    //=======> Both RS & ET can share the same setting for Vinplus.
	SyncHS_PowerUp_Secondary_in_Test_Mode_MINNO(gTM1_p,ILIM_NORM);	//Expect device to switch ON ~2.2ms, OFF ~62ms
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF
	BPP_ovi->set_current(BPP_ch, 3e-3, RANGE_3_MA);	//lower the BPP current range.
	delay(3);
	
	//Setup to measure IS2-S
	// Needs to move the current of Sec here to catch the full switching freq.
	/*BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);
	BPS_IS2_post = BPS_dvi->measure_average(10);
	BPS_IS2_delta = BPS_IS2_post - BPS_IS2_pre;*/

	// BPP_IS2
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
	wait.delay_10_us(8);
	BPP_IS2_post = BPP_ovi->measure_average(10);
	BPP_IS2_delta = BPP_IS2_post - BPP_IS2_pre;

	// BPP IS1
	REQ_ovi->set_voltage(REQ_ch, 0.9,		RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(50);
	if(gSiliconRev_P >= 3)		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
	else						BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);

	//BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);

	BPP_ovi->set_current(BPP_ch, 0.001, RANGE_3_MA);
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
	wait.delay_10_us(40);
	//delay(2);
	BPP_IS1_post = BPP_ovi->measure_average(10);
	BPP_IS1_delta = BPP_IS1_post - BPP_IS1_pre;

	 //   BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
		//wait.delay_10_us(5);
		//
		//BPS_IS1_post = BPS_dvi->measure_average(25); //expect ~10mA with SR switching.
		////gIBPS_sw = BPS_IS2_pre;
		////pulse.do_pulse();
		//wait.delay_10_us(100);

	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();


	Open_relay(K2);		// disconnect DVI11_0 from Drain
	Open_relay(K18);	// disconnect DVI11_1 from FW pin
	Close_relay(K3);	// Connect dvi-11-0 to R1(50ohm),L1(82uH) to Drain
	delay(4);
	
	VBPP_Negative_Cycle();
	if(1)
	{
		//Vpin (0V)
		VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
		VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
		
		//Drain (0V/3mA)
		D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
		D_dvi->set_voltage(D_ch, 0, 		VOLT_50_RANGE);	// DVI_11_0	
		//D_dvi->set_voltage(D_ch, 45.0, 		VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(20);

		//BPP set 0V
		BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
		VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2);	// vstart, vstop, vstep	
		// Initialize DDD
		wait.delay_10_us(100);  	
		ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
		delay(1);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(50);

		VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
		// Close K12 to connect DDD to VPIN
		Close_relay(K12);
		delay(4);
		Force_Vpin_Pulses_5_Times(5.0, 0.0);	
		wait.delay_10_us(10);

		D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
		D_dvi->set_voltage(D_ch, 45.0, 			VOLT_50_RANGE);	// DVI_11_0
		wait.delay_10_us(50);

		Connect_InvSyn_IM(Low_Vd_Input);// Connect the Sync Circuit while the device is quiet to help with the glitch on drain.
										// This glitch was much noticible and much worse on Turret setup.

		//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
		VBPP_ramp_up(5.0, gVBPP_PV_Init, 50e-3);		
		//Drain stays at 0V so BPP signal will be cleaner
		//dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
		//wait.delay_10_us(10);
		wait.delay_10_us(50);
		VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(5);

		//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
		ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-200e-3, RANGE_10_V);
		wait.delay_10_us(50);
		if(gSiliconRev_P >= 3)
		{
			BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
			VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
			wait.delay_10_us(10);
		}
		else
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+50e-3, RANGE_10_V);
			wait.delay_10_us(30);
		}
		/*dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
		wait.delay_10_us(10);*/
		// Open K12 
		Open_relay(K12);
		VPIN_ovi->connect(1);// Reconnect OVI from UV
		ddd_7->ddd_set_hi_level(0.0);		// Will immediately change to this level upon execution
		wait.delay_10_us(100);
		
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);
		Close_relay(K5);//Connect SR to 5nF
		delay(2);

		//ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//This could cause a 1V glitch at BPS for 50us
		//wait.delay_10_us(10);

		//Vout (0V)
		VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
		//FB (2V)  pull FB above CVth to force No Switching
		REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
		//REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	

		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 300mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
		//VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal
		VBPS_Power_Up(gVBPS_P_Init-0.3);	
		if(LB_Rev >= 5)		ddd_7->ddd_set_hi_level(1.7);
		else				ddd_7->ddd_set_hi_level(gCVth_15pct_Higher);	
		ddd_7->ddd_set_lo_level(0.9);
		wait.delay_10_us(100);
		
		ddd_7->ddd_run_pattern(Low_FB_pat_start, Low_FB_pat_stop);
		wait.delay_10_us(10);
		VO_dvi->set_voltage(VO_ch, 3.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
		wait.delay_10_us(10);
		 
		Close_relay(K17);	//FB   to   DDD
			//Must leave 2ms here for the SSS 70pct ILIM-P to capture at least 40 cycles (1/25kHz =~40us. 40x40us = 1600us = 1.6ms)
		delay(5);
	//Gage_Start_Capture(  );
		BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
		wait.delay_10_us(5);
		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);
		//BPS_dvi->set_voltage(BPS_ch, 5, 	VOLT_10_RANGE);
	// Secondary vBPS_plus	//Connect REQ pin to DDD to run 100KHz pulses
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(Low_FB_pat_start, Low_FB_pat_stop);
		wait.delay_10_us(10);
		
		ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
		wait.delay_10_us(30);
		BPS_IS2_post = BPS_dvi->measure_average(25); //expect ~10mA with SR switching.
		
		//gIBPS_sw = BPS_IS2_pre;
		//pulse.do_pulse();
		wait.delay_10_us(100);
		BPS_IS2_delta = BPS_IS2_post - BPS_IS2_pre;
		
	}

	//Power down
 	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	wait.delay_10_us(100);                           // HL do not remove delay.  Else, it will corrupt the DDD pattern.
	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_2_V);	// OVI_1_2
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	wait.delay_10_us(5);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);	
	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_2_RANGE);	// DVI_9_1
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	wait.delay_10_us(5);
	Open_relay(K17);
	delay(4);

	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();


	//IS1_S (Not Switching)
	Close_relay(K18);
	delay(5);
	BPS_dvi->set_current(BPS_ch, 100e-3,	RANGE_300_MA);	 
	FW_dvi->set_current(FW_ch,   30e-3,	RANGE_30_MA);	 
	FW_dvi->set_voltage(FW_ch,	 6.0,		VOLT_10_RANGE);	 
	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	delay(1);
	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init+50e-3,	VOLT_10_RANGE);	// Starting search point
	delay(2);
	BPS_dvi->set_current(BPS_ch, 3e-3,	RANGE_3_MA);	
	delay(2);

	BPS_IS1_post = BPS_dvi->measure_average(10);
	BPS_IS1_delta = BPS_IS1_post - BPS_IS1_pre;

	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();

	/*
	
	Set_Default_VIrange();
	Reset_VI();
	// Initialize DDD
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	wait.delay_10_us(10);
	ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);

	Open_relay(K2);		// disconnect DVI11_0 from Drain
	Open_relay(K18);	// disconnect DVI11_1 from FW pin
	Close_relay(K3);	// Connect dvi-11-0 to R1(50ohm),L1(82uH) to Drain
	Close_relay(K12);	// Close K12 to connect DDD to VPIN
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF

	Connect_InvSyn_IM(Low_Vd_Input);// Connect the Sync Circuit while the device is quiet to help with the glitch on drain.

	Set_VI(res_VPIN_ovi, 0.0 V, 30 mA);
	VPIN_ovi->disconnect(VPIN_ch);				// Disconnect OVI from UV
	Set_Vrange(res_D_dvi, RANGE_50_V);
	Set_VI(res_D_dvi, 0.0 V, 300 mA);
	Set_I(res_BPP_ovi, 30 mA);
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2);	// vstart, vstop, vstep	
	
	Force_Vpin_Pulses_5_Times(5.0, 0.1);
	wait.delay_10_us(10);

	Set_VI(res_D_dvi, 45.0 V, 300 mA);

	//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	VBPP_ramp_up(5.0 V, gVBPP_PV_Init, 50 mV);
	wait.delay_10_us(50);
	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init + 250 mV, 100 mV);	// vstart, vstop, vstep
	wait.delay_10_us(5);

	//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
	Set_V(res_BPP_ovi, gVBPP_M_Init - 200 mV);
	wait.delay_10_us(50);
	VBPP_ramp_up(gVBPP_M_Init - 200 mV, gVBPP_P_final, 100 mV);	// vstart, vstop, vstep	B3 material

	VPIN_ovi->connect(VPIN_ch);// Reconnect OVI from UV
	ddd_7->ddd_set_hi_level(0.0);		// Will immediately change to this level upon execution
	wait.delay_10_us(10);
	Open_relay(K12);
	Set_I(res_BPP_ovi, 3 mA);
	Set_I(res_BPS_dvi, 300 mA);
	Set_VI(res_VO_dvi, 5.0 V, 300 mA);
	Close_relay(K17);	//REQ   to   DDD
	FWC_dvi2k->open_relay(CONN_FORCE0);
	FWC_dvi2k->open_relay(CONN_SENSE0);
	ACK_ovi->disconnect(ACK_ch);
	delay(4);

	ddd_7->ddd_set_hi_level(gREQ_2V);
	wait.delay_10_us(10);
	ddd_7->ddd_set_lo_level(gREQ_V_Idle);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	DDD_Wait_Pattern_End(High_pat_REQ_start, High_pat_REQ_stop);
	VBPS_Power_Up(gVBPS_P_Init - 300 mV);	
	Set_VI(res_BPS_dvi, gVBPS_final, 300 mA);

	// Secondary vBPS_plus	//Connect REQ pin to DDD to run 100KHz pulses
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	DDD_Wait_Pattern_End(High_pat_REQ_start, High_pat_REQ_stop);
	
	ddd_7->ddd_run_pattern(FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop);
	wait.delay_10_us(30);

	//IS2 (Switching)
	BPS_IS2_post = Meas_VIaverage(res_BPS_dvi, MEASURE_CURRENT, 25);
	BPS_IS2_delta = BPS_IS2_post - BPS_IS2_pre;
	BPP_IS2_post = Meas_VIaverage(res_BPP_ovi, MEASURE_CURRENT, 10);
	BPP_IS2_delta = BPP_IS2_post - BPP_IS2_pre;

	Set_VI(res_D_dvi, 2.0 V, 300 mA);
	Set_V(res_BPP_ovi, gVBPP_P_s_final);
	delay(1);
	//IS1 (Not Switching)
	BPP_IS1_post = Meas_VIaverage(res_BPP_ovi, MEASURE_CURRENT, 10);
	BPP_IS1_delta = BPP_IS1_post - BPP_IS1_pre;
	BPS_IS1_post = Meas_VIaverage(res_BPS_dvi, MEASURE_CURRENT, 10);
	BPS_IS1_delta = BPS_IS1_post - BPS_IS1_pre;

	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	*/

/****************************************************************************
 *	Datalog																	*
 ****************************************************************************/
	int failed = 0;

	PiDatalog(func, A_ILL_D_post,		ILL_D_post,		set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_D_post].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILL_UV_post,		ILL_UV_post,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_UV_post].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILH_UV_post,		ILH_UV_post,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILH_UV_post].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILL_FW_post,		ILL_FW_post,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_FW_post].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILL_VO_post,		ILL_VO_post,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_VO_post].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILL_REQ_post,		ILL_REQ_post,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_REQ_post].passed_fail == FAILED_TEST) failed++;
	//PiDatalog(func, A_ILH_REQ_post,		ILH_REQ_post,	set_fail_bin,	POWER_MICRO);
	//if (func.dlog->tests[A_ILH_REQ_post].passed_fail == FAILED_TEST) failed++;

	PiDatalog(func, A_ILL_D_delta,		ILL_D_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_D_delta].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILL_UV_delta,		ILL_UV_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_UV_delta].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILH_UV_delta,		ILH_UV_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILH_UV_delta].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILL_FW_delta,		ILL_FW_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_FW_delta].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILL_VO_delta,		ILL_VO_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_VO_delta].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_ILL_REQ_delta,	ILL_REQ_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_ILL_REQ_delta].passed_fail == FAILED_TEST) failed++;
	//PiDatalog(func, A_ILH_REQ_delta,	ILH_REQ_delta,	set_fail_bin,	POWER_MICRO);
	//if (func.dlog->tests[A_ILH_REQ_delta].passed_fail == FAILED_TEST) failed++;

	PiDatalog(func, A_BPS_IS1_pre,		BPS_IS1_pre,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_BPS_IS1_pre].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_BPS_IS2_pre,		BPS_IS2_pre,	set_fail_bin,	POWER_MILLI);
	if (func.dlog->tests[A_BPS_IS2_pre].passed_fail == FAILED_TEST) failed++;

	PiDatalog(func, A_BPS_IS1_post,		BPS_IS1_post,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_BPS_IS1_post].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_BPS_IS2_post,		BPS_IS2_post,	set_fail_bin,	POWER_MILLI);
	if (func.dlog->tests[A_BPS_IS2_post].passed_fail == FAILED_TEST) failed++;

	PiDatalog(func, A_BPS_IS1_delta,	BPS_IS1_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_BPS_IS1_delta].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_BPS_IS2_delta,	BPS_IS2_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_BPS_IS2_delta].passed_fail == FAILED_TEST) failed++;

	PiDatalog(func, A_BPP_IS1_pre,		BPP_IS1_pre,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_BPP_IS1_pre].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_BPP_IS2_pre,		BPP_IS2_pre,	set_fail_bin,	POWER_MILLI);
	if (func.dlog->tests[A_BPP_IS2_pre].passed_fail == FAILED_TEST) failed++;

	PiDatalog(func, A_BPP_IS1_post,		BPP_IS1_post,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_BPP_IS1_post].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_BPP_IS2_post,		BPP_IS2_post,	set_fail_bin,	POWER_MILLI);
	if (func.dlog->tests[A_BPP_IS2_post].passed_fail == FAILED_TEST) failed++;

	PiDatalog(func, A_BPP_IS1_delta,	BPP_IS1_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_BPP_IS1_delta].passed_fail == FAILED_TEST) failed++;
	PiDatalog(func, A_BPP_IS2_delta,	BPP_IS2_delta,	set_fail_bin,	POWER_MICRO);
	if (func.dlog->tests[A_BPP_IS2_delta].passed_fail == FAILED_TEST) failed++;

	if (failed == 0)
	{
		g_Stress_passed = 1;	//Only trim Vshunt bit if Stress test passed
	}

	if(gDEBUG==1)
	printf("STRESS_Done\n");
}
