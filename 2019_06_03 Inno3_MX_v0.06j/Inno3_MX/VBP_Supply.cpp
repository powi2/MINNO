//==============================================================================
// VBP_Supply.cpp (User function)
// 
//    void VBP_Supply_user_init(test_function& func)
//    void VBP_Supply(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "VBP_Supply.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VBP_Supply_user_init(test_function& func)
{
	VBP_Supply_params *ours;
    ours = (VBP_Supply_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VBP_Supply(test_function& func)
{
    // The two lines below must be the first two in the function.
    VBP_Supply_params *ours;
    ours = (VBP_Supply_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "VBP_Supply";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_VBP_Supply,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//float Vshunt_2mA_p=0.0,  Vshunt_2mA_s=0.0;
	float Ishunt_p=0.0,	Ishunt_s=0.0, Vshunt_12mA_p=0.0;
	float BPS_ISS1_s=0.0,	 BPS_ISS2_s=0.0,	BPP_IS2_6p2_p=0.0,	BPP_IS2_5p8_p=0.0;
	float VBPP_P=0,			 VBPP_M=0.0,		VBPP_HYS=0.0,		VBPP_PV=0.0,		VBPP_P_S=0.0,
		  VBPS_P=0.0, 		 VBPS_M=0.0,		VBPS_HYS=0.0,		VBPP_P_iHVoff=0.0,	VBPP_Vshunt_PUseq=0.0;
	float VBPP_Reset_p=0.0,  VBPS_Reset_s=0.0, VBPS_Reset_Delta_s=0.0;
	float BPP_IS1_6p2_p=0.0, BPP_IS1_VBPP_p=0.0;
	float tLOff_Filter_S = 0.0;
	float i_bpp=0.0;

	float start_trig=0.0, stop_trig=0.0;
	float vfrc =0.0, ifrc=0.0, vstep =0.0, istep=0.0, vramp =0.0;
	float tmeas =0.0,tmeas1 =0.0,tmeas2 =0.0,tmeas3 =0.0;
	int	  lcnt  =0, cnt = 0;
	bool  FINE_SEARCH=0;

	float ISD_p = 0, ISD_s = 0, VBPP_Reset_s = 0, VBPS_OV=0;
	int	  ISD_func_p =false;

	float LO_Expect_Time = 0;
	float HI_Expect_Time = 0;

	int	   VBP_Supply_debug=0;

	//VBP_Supply_debug = 0;
	//if(VBP_Supply_debug)
	//	DEBUG = 1;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//									ISD-P									    //
// Ramp IBPP until device latches off (stops switching).					    //
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//								ISD:func-P										//
// Go/No go functional test.  Make sure device can be brought out of			//
// latchoff after ISD has occured.												//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	Power_Down_Everything();
	Open_All_Relays();
	Close_relay(K3);

	// Setup TMU //
	tmu_6->init();
	Close_relay(K3); // Drain to dvi though pullup resistor.  Drain to TMU. //
 	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain //
	tmu_6->start_trigger_setup(1.0,	NEG_SLOPE, TMU_HIZ,  TMU_IN_10V);
	tmu_6->stop_trigger_setup(1.2,	NEG_SLOPE, TMU_HIZ,  TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	wait.delay_10_us(100); 

	// Setup DDD //
	ddd_7->ddd_set_hi_level(4);
	ddd_7->ddd_set_lo_level(0);
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);
	delay(4);

	//if (gTrim_AR_req)
	//{
	//	//////UV pin (Vpin) set to 6V/80uA before PU
	//	////VPIN_ovi->set_voltage(VPIN_ch, 6.0,			VOLT_10_RANGE);  
	//	////VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	
	//	VBPP_Negative_Cycle();
	//	SyncHS_PowerUp_Secondary_in_Normal_Mode_Primary_TM5(Low_Vd_Input);

	//	if(g_TurretCB&&MOSFET_SIZE==5)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.5,		VOLT_20_RANGE);	// OVI_1_4	

	//	delay(5);

	//	// Get ready for search. //
	//	// Check to make sure drain is initially switching. //
	//	vfrc = 5.45;
	//	ifrc = 4.0e-3;
	//	BPP_ovi->set_voltage(BPP_ch, vfrc, RANGE_10_V); 
	//	BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
	//	wait.delay_10_us(10);
	//	tmu_6->arm();
	//	wait.delay_10_us(15);				
	//	tmeas = tmu_6->read(1e-3);
	//	istep = 0.2e-3;
	//	if(g_TurretCB)
	//	{
	//		LO_Expect_Time = 1.0e-9; //HL changed from 1us to 1ns.  This is the threshold to ensure Drain is switching.
	//	}
	//	else
	//	{
	//		LO_Expect_Time = 1.0e-6;
	//	}
	//	HI_Expect_Time = 100e-6;
	//	if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) ) // Make sure drain is switching. //
	//	{
	//		// Rough search for ISD-P threshold. //
	//		while(tmeas > LO_Expect_Time && tmeas < HI_Expect_Time && ifrc < .01)
	//		{
	//				ifrc +=istep;
	//				BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
	//				wait.delay_10_us(10);	// Provide enough time for device to stop switching
	//				tmu_6->arm();	
	//				wait.delay_10_us(10);				
	//				tmeas = tmu_6->read(1e-3);
	//		}

	//		////// Functional check.  Make sure latchoff can be removed by bring BP below VBP-. // 
	//		////VBPP_ramp_down(vfrc, gVBPP_M_Init-200e-3, 0.05); // Bring below VBP- to reset latch-off. //
	//		//////VBPP_ramp_down(vfrc, 3.0, 0.05); // Bring below VBP- to reset latch-off. //
	//		////wait.delay_10_us(50); // Wait for BPP voltage to come down. //
	//		////BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	//		////VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_Init+50e-3, 0.05); // Bring back up to make sure part switches (i.e. make sure latchoff is removed). //
	//		////tmu_6->arm();	
	//		////wait.delay_10_us(10);				
	//		////tmeas = tmu_6->read(100e-6);
	//		////if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) )
	//		////	ISD_func_p = true; // Pass.  Latchoff is removed- drain switching. //
	//		////else
	//		////	ISD_func_p = 999.0; // Fail.  Latchoff not removed- drain not switching. //

	//		////// Fine search for ISD-P threshold. //
	//		////ifrc -= 1e-3;
	//		////istep = 0.02e-3;	
	//		////BPP_ovi->set_voltage(BPP_ch, vfrc, RANGE_10_V); 
	//		////BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
	//		////wait.delay_10_us(10);
	//		////VBPP_ramp_up(gVBPP_P_Init+50e-3, vfrc, 0.05);	// vstart, vstop, vstep - To reduce overshoot //
	//		////wait.delay_10_us(10);
	//		////tmu_6->arm();
	//		////wait.delay_10_us(15);				
	//		////tmeas = tmu_6->read(1e-3);
	//		////if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) ) // Make sure drain is switching. //
	//		////{
	//		////	while(tmeas > LO_Expect_Time && tmeas < HI_Expect_Time && ifrc < .01)
	//		////	{
	//		////		ifrc +=istep;
	//		////		BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
	//		////		wait.delay_10_us(15);	// Provide enough time for device to stop switching
	//		////		tmu_6->arm();	
	//		////		wait.delay_10_us(15);				
	//		////		tmeas = tmu_6->read(200e-6);
	//		////	}
	//		////}
	//		////else
	//		////{		
	//		////	ISD_p =999.0e-6; // Device not switching. FAIL. //
	//		////}
	//		ISD_p = ifrc;
	//	}
	//	else
	//		ISD_p =999.0e-6; // Device not switching. FAIL. //

	//	gISD = ISD_p;	// Save for later SR tests
	//}
	//else
	{
		//// Vpin connect to DDD. //
		//VPIN_ovi->set_current(VPIN_ch, 0.1e-9, RANGE_30_UA); // Float.  Let DDD control. //	
		//ovi_1->disconnect(1);
		//Close_relay(K12); // Connect DDD7_1 to V pin //
		//wait.delay_10_us(300);

		// Powerup Primary in Normal Mode, Test Mode 5, to bypass wait and listen //
		VBPP_ramp_up(0, 5.0, 0.2);	// vstart, vstop, vstep	//

		//// Vpin clock 5 pulses (10us positive) to enter test mode 5. //
		//Force_Vpin_Pulses_5_Times(5.0, 0.0);	
		//wait.delay_10_us(5);

		// Setup Vpin for digital clocking with DDD //
		ovi_1->disconnect(OVI_CHANNEL_1);	
		ddd_7->ddd_set_lo_level(0.1);
		ddd_7->ddd_set_hi_level(4.0);
		//delay(1);
		wait.delay_10_us(10);
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(10);
		Close_relay(K12); // Connect DDD7_1 to Vpin(UV) //
		delay(4);
		// Vpin clock 5 pulses (10us positive) to enter test mode 5. //
		Force_Vpin_Pulses_5_Times(5.0, 0.0);	
		wait.delay_10_us(5);

		// Set drain voltage. //
		D_dvi->set_voltage(D_ch, 5.0, VOLT_5_RANGE);
		wait.delay_10_us(50);

		// BPP ramp up //
		VBPP_ramp_up(5.0, gVBPP_PV_Init+.05, 50e-3);		

		// BPP ramp down //
		VBPP_ramp_down(gVBPP_PV_Init+.05, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	//
		
		// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
		int ILIM_Select = ILIM_NORM;
		if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
		else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

		// BPP set below VBP-, then back above VBP+ to complete the powerup. //
		BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
		wait.delay_10_us(50);
		//BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init+50e-3, RANGE_10_V); 
		//wait.delay_10_us(100);
		if(gSiliconRev_P>=3)
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
		// Wait and listen is skipped, drain should now be switching. //

		// Get ready for search. //
		// Check to make sure drain is initially switching. //
		vfrc = 5.54;
		ifrc = 1.0e-3;
		BPP_ovi->set_voltage(BPP_ch, vfrc, RANGE_10_V);
		BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
		wait.delay_10_us(10);
		VBPP_ramp_up(gVBPP_P_Init+50e-3, vfrc, 0.05);	// vstart, vstop, vstep //
		wait.delay_10_us(10);
		tmu_6->arm();
		wait.delay_10_us(15);				
		tmeas = tmu_6->read(1e-3);
		istep = 0.5e-3;
			if(g_TurretCB)
		{
			LO_Expect_Time = 1.0e-9; //HL changed from 1us to 1ns.  This is the threshold to ensure Drain is switching.
		}
		else
		{
			LO_Expect_Time = 1.0e-6;
		}
	
		HI_Expect_Time = 100e-6;
		if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) ) // Make sure drain is switching. //
		{
			// Rough search for ISD-P threshold. //
			while(tmeas > LO_Expect_Time && tmeas < HI_Expect_Time && ifrc < .01)
			{
					ifrc +=istep;
					BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
					wait.delay_10_us(10);	// Provide enough time for device to stop switching
					tmu_6->arm();	
					wait.delay_10_us(10);				
					tmeas = tmu_6->read();
			}

			// Functional check.  Make sure latchoff can be removed by bring BP below VBP-. // 
			BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
			VBPP_ramp_down(vfrc, gVBPP_M_Init-200e-3, 0.05); // Bring below VBP- to reset latch-off. //
			wait.delay_10_us(50); // Wait for BPP voltage to come down. //
			BPP_ovi->set_current(BPP_ch, 5e-3, RANGE_30_MA);
			VBPP_ramp_up(gVBPP_M_Init-200e-3, gVBPP_P_Init+50e-3, 0.05); // Bring back up to make sure part switches (i.e. make sure latchoff is removed). //
			tmu_6->arm();	
			wait.delay_10_us(10);				
			tmeas = tmu_6->read(100e-6);
			if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) )
				ISD_func_p = true; // Pass.  Latchoff is removed- drain switching. //
			else
				ISD_func_p = 999.0; // Fail.  Latchoff not removed- drain not switching. //

			// Fine search for ISD-P threshold. //
			ifrc -= 1e-3;
			istep = 0.02e-3;	
			BPP_ovi->set_voltage(BPP_ch, vfrc, RANGE_10_V);
			BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
			wait.delay_10_us(10);
			VBPP_ramp_up(gVBPP_P_Init+50e-3, vfrc, 0.05);	// vstart, vstop, vstep - To reduce overshoot //
			wait.delay_10_us(10);
			tmu_6->arm();
			wait.delay_10_us(15);				
			tmeas = tmu_6->read(1e-3);
			if ( (tmeas > LO_Expect_Time) && (tmeas < HI_Expect_Time) ) // Make sure drain is switching. //
			{
				while(tmeas > LO_Expect_Time && tmeas < HI_Expect_Time && ifrc < .01)
				{
					ifrc +=istep;
					BPP_ovi->set_current(BPP_ch, ifrc, RANGE_30_MA);
					wait.delay_10_us(15);	// Provide enough time for device to stop switching
					tmu_6->arm();	
					wait.delay_10_us(15);				
					tmeas = tmu_6->read(200e-6);
				}
			}
			else
			{		
				ISD_p =999.0e-6; // Device not switching. FAIL. //
			}
			ISD_p = ifrc;
		}
		else
			ISD_p =999.0e-6; // Device not switching. FAIL. //

		gISD = ISD_p;	// Save for later SR tests
	}

	// JD separate powerup to reduce test time
	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();


	VBPP_Negative_Cycle();

	/************************************************
	 ** Ishunt_5.5V & Vshunt_12mA *******************
	 ************************************************
		Ishunt_5.5V Test Condition: 
		o BPP pin set vClamp to 5.6V and allow shunt current max out to 18.5mA
		o Note that there should be only two places where in the program vBPP is higher than 5.5V
		  Ishunt_5.5V and Vshunt_12mA

	    Vshunt_12mA Test Condition:
		o BPP pin set iClamp to 12mA and allow shunt voltage up to 5.7V								*/


	SyncHS_PowerUp_Secondary_in_Normal_Mode_Primary_TM5(Low_Vd_Input);
	delay(5);

	//Ishunt_5.5V
	if(LB_Rev>=5||g_TurretCB)
	{
		BPP_ovi->set_voltage(BPP_ch, 5.60, RANGE_10_V); 
		BPP_ovi->set_current(BPP_ch, 18.5e-3, RANGE_30_MA);
	}
	else
	{
		BPP_ovi->set_voltage(BPP_ch, 5.60, RANGE_10_V); 
		BPP_ovi->set_current(BPP_ch, 18.5e-3, RANGE_30_MA);
	}
	wait.delay_10_us(10);
	BPP_ovi->set_meas_mode(BPP_ch,		OVI_MEASURE_CURRENT);
	delay(5);

	Ishunt_p = BPP_ovi->measure_average(10);	

	//Vshunt_12mA
	BPP_ovi->set_meas_mode(BPP_ch,		OVI_MEASURE_VOLTAGE);
	BPP_ovi->set_current(BPP_ch, 12e-3, RANGE_30_MA);
	wait.delay_10_us(5);
	BPP_ovi->set_voltage(BPP_ch, 5.70,	RANGE_10_V); 
	wait.delay_10_us(20);
	Vshunt_12mA_p = BPP_ovi->measure_average(10);	


	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();

	// Reset //
	Power_Down_Everything();
	Open_All_Relays();
	wait.delay_10_us(200);

	BPS_dvi->set_voltage(BPS_ch, 0.0, 					VOLT_10_RANGE);	// DVI_9_1
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
	wait.delay_10_us(10); 
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//This could cause a 1V glitch at BPS for 50us initially
	wait.delay_10_us(10); 
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//							VShunt and IShunt								//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	Close_relay(K2);			//Drain to dvi-11-0
	Close_relay(K18);			//FW to dvi-11-1
	//////////ovi_1->disconnect(VPIN_ch);	//Vpin
	delay(2);
// VShunt
	//////////D_dvi->set_voltage(D_ch,	 0.0,	VOLT_2_RANGE);  
	//////////FW_dvi->set_voltage(FW_ch,	 0.0,	VOLT_2_RANGE);  wait.delay_10_us(10);

	//////////VPIN_ovi->set_voltage(VPIN_ch,	 0.0, 	RANGE_2_V);			// OVI_1_1
	//////////VPIN_ovi->set_current(VPIN_ch,	 30.0e-3,RANGE_30_MA);	

	//////////BPP_ovi->set_voltage(BPP_ch, gVshunt_BPP, RANGE_10_V);	// OVI_1_0
	//////////BPP_ovi->set_current(BPP_ch, 2.0e-3,RANGE_3_MA);
	//////////BPP_ovi->set_meas_mode(BPP_ch,		OVI_MEASURE_VOLTAGE);

	//////////BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS, VOLT_10_RANGE);  
	//////////BPS_dvi->set_current(BPS_ch, 300e-3,RANGE_300_MA);			
	////////////wait.delay_10_us(20);
	//////////delay(2);
	//////////BPS_dvi->set_meas_mode(BPS_ch,		DVI_MEASURE_VOLTAGE);
	//////////BPS_dvi->set_current(BPS_ch, 2e-3,	RANGE_300_MA);		
	//////////delay(20);

	//////////Vshunt_2mA_p = BPP_ovi->measure_average(10);
	//////////Vshunt_2mA_s = BPS_dvi->measure_average(10);

	//BPP_ovi->set_current(BPP_ch, 30e-3,RANGE_30_MA);
	//VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);	// OVI_1_0

	REQ_ovi->set_voltage(REQ_ch, 2.0, RANGE_5_V);
	REQ_ovi->set_current(REQ_ch, 10e-3,		RANGE_30_MA);
	//Float FWC
	FWC_dvi2k->open_relay(CONN_FORCE0);
	FWC_dvi2k->open_relay(CONN_SENSE0);
	//delay(1);
	
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF

	BPS_dvi->set_current(BPS_ch, 300e-3,RANGE_300_MA);		
	BPS_dvi->set_voltage(BPS_ch, 0.0,	VOLT_10_RANGE);  
	wait.delay_10_us(50);
// IShunt: Need DVI to meas Ishunt_p. OVI doesn't have enough current
	Close_relay(K3);	//Float Drain
	//Close_relay(K11);	//Connect DVI to BPP
	delay(4);

	//BPP_DVI->set_current(BPP_ch, 300e-3,RANGE_300_MA);	
//	Change Vshunt from 12V to 8V per Sheng
	//BPP_DVI->set_voltage(BPP_ch, gVshunt_BPP,	VOLT_20_RANGE);	
	//BPP_ovi->set_voltage(BPP_ch, gVshunt_BPP,	RANGE_10_V);			// OVI_1_0
	BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS,	VOLT_20_RANGE);  
	//BPS_dvi->set_voltage(BPS_ch, 5.5,	VOLT_20_RANGE);  
	wait.delay_10_us(50);


//	wait.delay_10_us(20);
	//BPP_ovi->set_meas_mode(BPP_ch,		OVI_MEASURE_CURRENT);
	BPS_dvi->set_meas_mode(BPS_ch,		DVI_MEASURE_CURRENT);
	delay(5);

	//Ishunt_p = BPP_ovi->measure_average(10);	
	Ishunt_s = BPS_dvi->measure_average(10);
	
	//BPP_DVI->set_voltage(BPP_ch, 0.0, VOLT_20_RANGE);
	//VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		RANGE_10_V);	// OVI_1_0
	BPS_dvi->set_voltage(BPS_ch, 0.0,	VOLT_10_RANGE);  
	//D_dvi->set_voltage(D_ch,	 0.0,		VOLT_50_RANGE);  
	Open_relay(K2);
	//Open_relay(K11);	//Disconnect DVI from BPP and Connect OVI-1-0 to BPP
	delay(3);

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//					Primary: VBPP_Init_P, VBPP_Init_M, VBPP_Init_HYS				    //
//																					    //
// Src VBPP threshold by checking chip consumption at different state without involving //
// Drain pin.																		    //
//             /\    /\																    //
//       0.3 /  3 0.3 0.8 mA														    //	
//	BPP Pin	 /	  \/    \                                                               //
//	   	    /                                                                           //
// CAUTION: "OVI" has major overshoot when forcing voltage on BPP pin                   //
//          (0-5V signal, 20% overshoot - 1V). DVI doesn't have a problem.              //
//			Without parts, OVI doesn't have overshoot.                                  //
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//K2, K3, and K11 was closed above
	//UV pin has to be grounded.  Otherwise, BPP will not operate.
	//////////ovi_1->connect(VPIN_ch);
	tmu_6->open_relay(TMU_HIZ_DUT1);

	VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_2_V);  
	VPIN_ovi->set_current(VPIN_ch, 10e-3,		RANGE_30_MA);		
	wait.delay_10_us(30);
	
	VBPP_P = 0.0;
	VBPP_M = 0.0;
	
if(gSiliconRev_P<=2)
	search_VBPP_th   (&VBPP_PV, &VBPP_M, &VBPP_P, &VBPP_P_iHVoff, &VBPP_Vshunt_PUseq			);
else
	search_VBPP_th_B3(&VBPP_PV, &VBPP_M, &VBPP_P, &VBPP_P_iHVoff, &VBPP_Vshunt_PUseq, &VBPP_P_S	);

	if(gSiliconRev_P >=3)
	{
		VBPP_HYS = (gVBPP_P_s_final-50e-3) - VBPP_M;	//Don't want to search for BPP_P_s again
		gVBPP_VCEN = (VBPP_P + VBPP_M)/2;	
	}
	else
	{
		VBPP_HYS = VBPP_P - VBPP_M;
		gVBPP_VCEN = (VBPP_P + VBPP_M)/2;	
	}

	// Power down VBPP test
	BPP_DVI->set_voltage(BPP_ch, 0.0,	VOLT_10_RANGE);	wait.delay_10_us(10);
	Open_relay(K3);			   

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//					Secondary: VBPS_Init_P, VBPS_Init_M, VBPS_Init_HYS				  //
//VBPS_Init_P:																		  //
// Chip consumption is the same at different states for secondary when device is not  //
// switching. Power up FW pin to see state transition by checking charge current. 	  //
// NOTE: CURRENT from FW to BPS guide line: (Vfw - Vbps - Vdiode)/200ohm			  //
//                           +200uA													  //			
//				 -20mA /----------------											  //
//					  /											            		  //	
//	BPS Pin			 /	                                                              //
//	FW =9.5V   	    /                                                                 //
//																				      //
//VBPS_Init_M:																		  //
//	In order to find VBPS_Init_M, allow device to switch, chip consumption should drop//
//  when VBPS_Init_M threshold is reached and switching is off.						  //
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//pulse.do_pulse();
//Setting to be the same as VBP_Init function
tmu_6->open_relay(TMU_HIZ_DUT1);
mux_14->open_relay(MUX_4_4);	//InvSync forgot somewhere before this func
mux_14->open_relay(MUX_7_3);	//InvSync forgot somewhere before this func

// VBPS_Init_P
	// K18 was closed above
	BPS_dvi->set_current(BPS_ch, 100e-3,	RANGE_300_MA);	 
	FW_dvi->set_current(FW_ch,   30e-3,		RANGE_30_MA);	 
	FW_dvi->set_voltage(FW_ch,	 5.0,		VOLT_10_RANGE);	 
	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//delay(2);
	REQ_ovi->set_voltage(REQ_ch, 2.0, RANGE_5_V);
	REQ_ovi->set_current(REQ_ch, 10e-3,		RANGE_30_MA);
	//Float FWC
	FWC_dvi2k->open_relay(CONN_FORCE0);
	FWC_dvi2k->open_relay(CONN_SENSE0);
	//delay(1);
	
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF
	delay(2);
	/*ovi_1->set_meas_mode(OVI_CHANNEL_5, OVI_MEASURE_VOLTAGE);
	delay(2);*/

	VBPS_P = 0.0;
	VBPS_M = 0.0;

	Open_relay(K18);   // FW_dvi
	Close_relay(K21);
	delay(1);

	search_VBPS_P_th(&VBPS_P);

//DEBUG=1;
	search_VBPS_M_th(&VBPS_M);
//DEBUG=0;
	
	VBPS_HYS = VBPS_P - VBPS_M;
	gVBPS_VCEN = (VBPS_P + VBPS_M)/2;

	gVBPS_M = VBPS_M;	//save for later

	// Power down
	Power_Down_Everything();
	Open_All_Relays();


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//							Secondary: VBPS:Reset-S								        //
//VBPS:Reset-S:																		    //
// VBPS:Reset-S measures the secondary BPS reset voltage.							    //
// After secondary is powered up in test mode, VBPS is ramp down toward VBPS:Reset.     //
// After each ramp down step, two negative pulses is applied on the FW pin.             //
// If VBPS:Reset hasn't been reached, secondary will come back switching. Vice versa,   //
// if VBPS:Reset is reached, secondary would not come back switching with 2 negative    //
// pulses. 3 negative pulses on FW pin is required to switch secondary.This difference  //
// is used as a criteria to search VBPS:Reset.										    //
// Again, when secondary is switching, secondary chip consumption on BPS is 2.0mA, vs   //
// 0.2mA while secondary is not switching.											    //
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
////	dvi_13->open_relay(BUS_SENSE1);
////	dvi_13->open_relay(BUS_FORCE1);
////	mux_14->open_relay(MUX_3_BUS3);
////	tmu_6->open_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
////
////	Disconnect_InvSyn_IM();
////	delay(1);
////
	
#if 0
	BPS_dvi->set_current(BPS_ch, 30.0e-3,					RANGE_30_MA);	
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 100e-3, 	VOLT_10_RANGE);	// DVI_9_1
	VBPS_ramp_up(0, gVBPS_M_Init - 100e-3, 100e-3);	//BPS ramp up from 0 to VBPS-M minus 200mV with 100mV step.
	wait.delay_10_us(5);

	//Float SR pin
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);

	//2. Set FB to 5V
	//REQ_ovi->set_voltage(REQ_ch, 5.0, 		VOLT_5_RANGE);	// OVI_1_2
	REQ_ovi->set_voltage(REQ_ch, 4.4, 		VOLT_5_RANGE);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);
	wait.delay_10_us(10);

	//3. Set Vout to 0V
	VO_dvi->set_current(VO_ch, 5e-3,		RANGE_30_MA);
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0

	ddd_7->ddd_set_lo_level(0.1);				// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(14);
	Open_relay(K18);	
	Close_relay(K21);	
	delay(4);	
	//Float SR pin
	//SR_dvi2k->open_relay(CONN_FORCE1);
	//SR_dvi2k->open_relay(CONN_SENSE1);
	//4. Set VFW to 1V
	ddd_7->ddd_set_hi_level(1.0);				// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(High_pat_start,High_pat_stop);
	wait.delay_10_us(14);
	delay(1);	//Minimum wait time is 700us in order for AF reading to work properly
	//5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
	//VBPS_ramp_up(0, gVBPS_M_Init - 100e-3, 100e-3);	//BPS ramp up from 0 to VBPS-M minus 100mV with 100mV step.
	//wait.delay_10_us(5);
	//VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVshunt_Init_Se - 100e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
	VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVBPS_final+100e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
	delay(1);
	wait.delay_10_us(40);
	//6. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
	ddd_7->ddd_set_lo_level(-0.5);				// Will immediately change to this level upon execution
	ddd_7->ddd_set_hi_level(5.0);				// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_1st_pulse_stop-1);
	wait.delay_10_us(15);	
	//7. Set FB back to 1V
	REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		VOLT_5_RANGE);	// OVI_1_2
	wait.delay_10_us(40);

	//// Provide 2 negative pulses on FW to give Secondary control.  (FW go below -100mV)
	ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_2nd_pulse_stop-1);
	wait.delay_10_us(15);	

//	Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
//	wait.delay_10_us(100);  //more than 30us quiet time on FW signal
	//Close_relay(K18);
	//Open_relay(K21);
	//delay(4);
	//// Clock VOUT to Test Mode
	ddd_7->ddd_set_hi_level(4.0);				// Will immediately change to this level upon execution
	ddd_7->ddd_set_lo_level(0.1);				// Will immediately change to this level upon execution
	delay(1);
	Close_relay(K27);
	dvi_9->open_relay(CONN_SENSE0);
	dvi_9->open_relay(CONN_FORCE0);
	delay(4);
	DDD_Clock_Vout_Antifuse(12);	// Register Address 36 is TM18, CV Comparator output.
									// Only clock to address 35 because need to set Vout at 5V after power up. Thats consider 1 more clock.
	delay(1);
	dvi_9->close_relay(CONN_SENSE0);
	dvi_9->close_relay(CONN_FORCE0);
	Open_relay(K27);
	delay(5);
#endif

	//pulse.do_pulse();
	//Open_relay(K18);	// FW to TMU
	//Open_relay(K27);	// VO disconnect from ddd
	//Close_relay(K3);	// Connect drain fast edge ckt
	//VBPP_Negative_Cycle();
	
	//delay(3);
//
	////tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	////tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	////tmu_6->stop_trigger_setup(3.0,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	////tmu_6->start_holdoff(0,FALSE);
	////tmu_6->stop_holdoff(0,FALSE);
	////delay(1);
	//pulse.do_pulse();
	//Power_Up_Primary_BypassWL_TM5(ILIM_NORM);
	//Power_Up_Primary_Normal_Mode(ILIM_NORM) ;
	//Vpin (0V)
	//VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	//VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
	//if(g_TurretCB)
	//{
	//	//HL needs to change to 20mA or Turret CB won't work.
	//	SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
	//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	//	delay(2);
	//	mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
	//}
	//else
	//{
	//	SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
	//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	//	dvi_13->close_relay(BUS_SENSE1);
	//	dvi_13->close_relay(BUS_FORCE1);
	//	mux_14->close_relay(MUX_3_BUS3);
	//	wait.delay_10_us(20);
	//}
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	
	REQ_ovi->set_voltage(REQ_ch, 2,		RANGE_2_V);	// OVI_1_2	
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	

	//Float FWC
	FWC_dvi2k->open_relay(CONN_FORCE0);
	FWC_dvi2k->open_relay(CONN_SENSE0);
	//delay(5);
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF
	Close_relay(K21);	// Connect FW to DDD
	delay(4);
	
	//delay(3);
	//mux_14->close_relay(MUX_BANK_3_4);
	//mux_14->close_relay(MUX_4_GND);

	//Vout (Will charge BPS if @5V)
	//VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
//	VO_dvi->set_voltage(VO_ch, 0, 		VOLT_5_RANGE);	// DVI_9_0
	//VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
	//FB (1V)
	//pulse.do_pulse();
	//REQ_ovi->set_voltage(REQ_ch, 2,		RANGE_2_V);	// OVI_1_2	
	//REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	//IS (0V)
	//FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	//FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	//wait.delay_10_us(10);
	//BPS (vPlus - 200mV)
	

	////Make sure vBPS less than 5.5V
	//if(gVBPS_M_Init < 5.5)
	//	VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal  
	//else
	//	VBPS_Power_Up(4.5);		
	//pulse.do_pulse();
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init-0.1, 	VOLT_10_RANGE);	// MINNO
	wait.delay_10_us(50);
	//Connect_InvSyn_IM(Low_Vd_Input);
	//wait.delay_10_us(100); 
	ddd_7->ddd_set_hi_level(5.0);				// Will immediately change to this level upon execution
	//delay(1);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(High_pat_start,High_pat_stop);
	wait.delay_10_us(14);

	//Make sure vBPS less than 5.5V
	if(gVBPS_P_Init < 5.5)
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init + 0.05, 	VOLT_10_RANGE);	// DVI_9_1
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// DVI_9_1  (8" EPSON require higher)
	BPS_dvi->set_voltage(BPS_ch, 5.0, 	VOLT_10_RANGE);	// MINNO
	wait.delay_10_us(100);

	if(gSiliconRev_P >= 3)		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
	else						BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);

	ddd_7->ddd_set_lo_level(-0.5);				// Will immediately change to this level upon execution
	//delay(1);
	ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_3rd_pulse_stop-1);
	wait.delay_10_us(10);	

	//tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	//tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	//tmu_6->stop_trigger_setup(3.0,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	//tmu_6->start_holdoff(0,FALSE);
	//tmu_6->stop_holdoff(0,FALSE);
	//delay(1);

   //MINNO- Use ACK pin TMU
	tmu_6->init();
	tmu_6->close_relay(TMU_CHAN_B_DUT1);//Connect TMU on ACK
	tmu_6->start_trigger_setup(2.1, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
	tmu_6-> stop_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
	delay(1);

//
//	DEBUG=1;
	WAVE_NAME = "VBPS_Reset_s";
	search_VBPS_Reset (&VBPS_Reset_s);
//	DEBUG=0;

	//VBPS_vs_VOcurrent();

	//Power Down
	//wait.delay_10_us(100); 
	ddd_7->ddd_set_lo_level(0.1);		 // Will immediately change to this level upon execution 
	wait.delay_10_us(10);                           // HL do not remove delay.  Else, it will corrupt the DDD pattern.

	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10); 
 	tmu_6->open_relay(TMU_HIZ_DUT1);
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();

//IBPS and VBPS_OV tests are removed from MINNO-S as they are included in MINNO Master 
/*  
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//						IBPS_SD, and VBPS_OV								//
// Power up secondary in Normal Mode, set VFB>CVth, Power up primary in		//
// Normal Mode. Increase IBPS units primary switches once and gives up control//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	float vforce = 0, ibps_delta = 0, ibps = 0, ibps_last = 0;
	int start=0, stop=0, i=0, j=0, num_pulse=0;
	float tOV_filter = 0.0;
	bool Switching=false;
	pulse.do_pulse();
	Close_relay(K3);
	delay(5);
	VBPP_Negative_Cycle();
	delay(1);
	SyncHS_PowerUp_Secondary_in_Normal_Mode_Primary_TM5(Low_Vd_Input);
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0  "Stop device from switching"
	wait.delay_10_us(10);
	//HL added. 6/20/17
	//if(MOSFET_SIZE==5)		
	//{
	//	if(OPCODE==4300 ||OPCODE==4500)
	//	{
	//		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4	
	//	}
	//}

	delay(3);
	// Step up to see ISD latchoff on oscilloscope
	//BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS, 	VOLT_10_RANGE);	// DVI_9_1
	//wait.delay_10_us(100);
	tmu_6->close_relay(TMU_HIZ_DUT1);	 // Connect TMU HIZ to Drain
	tmu_6->start_trigger_setup(1.8, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);	//FW	Channel_A_DUT1	to start trigger NEG
	tmu_6->stop_trigger_setup(2.0,	POS_SLOPE, TMU_HIZ, TMU_IN_5V);	//FW	Channel_A_DUT1	to start trigger NEG
	delay(4);

	//Find_Vbps_vs_Ibps();	// Make VI curve
	if(LB_Rev >= 5)		REQ_ovi->set_voltage(REQ_ch, 0.9,		RANGE_2_V);	// OVI_1_2	
	else				REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(10);
	//// Loop to find the approx trip point, current increases from uA at 5.25V to 13mA at 5.25V
	//vforce = gVshunt_BPS-0.5;
	////vforce = 5.25;
	//vstep = 5e-3;
	////
	//for (i=0; i<100; i++)	// Limit forcing volatge to 5.5V, abs max of process
	//{	// Loop to see switching start
	//	vforce += vstep;
	//	tmu_6->arm();
	//	wait.delay_10_us(10);
	//	BPS_dvi->set_voltage(BPS_ch, vforce,	VOLT_10_RANGE);
	//	wait.delay_10_us(50);		// > 120us timer on BPS latchoff, per DE
	//	////tmu_6->arm();
	//	////wait.delay_10_us(10);
	//	tmeas = tmu_6->read(150e-6);
	//	if (tmeas > 0) break;
	//}
	//vstep = 2.5e-3;
	//if(g_TurretCB)
	//{
	//	while( (vforce < 5.5) && (tmeas > 2e-9) )	//HL changed from 50ns to 2ns.  This is to make sure Drain is switching.
	//	{
	//		vforce += vstep;
	//		////start = mytimer.GetElapsedTime();
	//		////tmu_6->arm();
	//		////wait.delay_10_us(5);
	//		BPS_dvi->set_voltage(BPS_ch, vforce,	VOLT_10_RANGE);
	//		wait.delay_10_us(50);		// > 120us timer on BPS latchoff, per DE
	//		tmu_6->arm();
	//		wait.delay_10_us(5);
	//		tmeas = tmu_6->read(150e-6);
	//		////stop = mytimer.GetElapsedTime();
	//	}
	//	VBPS_OV = vforce-vstep;	// Measure Isd just before threshold
	//}
	//else
	//{
	//	while( (vforce < 5.5) && (tmeas > 2e-9) )	
	//	{
	//		vforce += vstep;
	//		////tmu_6->arm();
	//		////wait.delay_10_us(5);
	//		BPS_dvi->set_voltage(BPS_ch, vforce,	VOLT_10_RANGE);
	//		wait.delay_10_us(50);		// > 120us timer on BPS latchoff, per DE
	//		tmu_6->arm();
	//		wait.delay_10_us(5);
	//		tmeas = tmu_6->read(150e-6);
	//	}
	//	VBPS_OV = vforce-vstep;	// Measure Isd just before threshold
	//	//VBPS_OV = vforce;	// Measure Isd just before threshold
	//}
	//
	//// Disconnect the Sync Circuit to make sure FWD is not below GND when measuring ISD.
	//Disconnect_InvSyn_IM();
	//delay(3);

	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//wait.delay_10_us(10);
	//BPS_dvi->set_current(BPS_ch, 20e-3, 	RANGE_300_MA);	// DVI_9_1
	//wait.delay_10_us(20);
	//BPS_dvi->set_current(BPS_ch, 20e-3, 	RANGE_30_MA);	// DVI_9_1
	//wait.delay_10_us(20);
	//// Make sure it is off
	////BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS,	VOLT_10_RANGE);
	////wait.delay_10_us(50);		// > 120us timer on BPS latchoff, per DE
	//REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	//wait.delay_10_us(10);
	//
	//BPS_dvi->set_voltage(BPS_ch, VBPS_OV,	VOLT_10_RANGE);
	//wait.delay_10_us(100);		// > 100us
	//ISD_s = BPS_dvi->measure_average(10);

	//// Go down to VBPS+50mV and verify no switching
	//REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	//wait.delay_10_us(20);
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init+0.05, 	VOLT_10_RANGE);	// DVI_9_1 
	//wait.delay_10_us(50);

	//// Verify no switching
	//tmu_6->arm(); 
	//wait.delay_10_us(10);
	//tmeas = tmu_6->read();
	//if (tmeas > 0)
	//{
	//	VBPS_OV = 0.0;
	//	ISD_s = 0.0;
	//}
	ifrc = 5.5e-3;
	//vforce = 5.25;
	istep = 0.25e-3;
	BPS_dvi->set_current(BPS_ch, 5.5e-3, 	RANGE_30_MA);	// DVI_9_1
	BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS,	VOLT_10_RANGE);
	//BPS_dvi->set_voltage(BPS_ch, 5.0,	VOLT_10_RANGE);
	wait.delay_10_us(10);
	//for (i=0; i<150; i++)	// Limit forcing current to 20mA
	for (i=0; i<80; i++)	// HQL 1/8/2018
	{	// Loop to see switching start
		ifrc += istep;
		tmu_6->arm();
		wait.delay_10_us(10);
		BPS_dvi->set_current(BPS_ch, ifrc, 	RANGE_30_MA);
		wait.delay_10_us(50);		// > 120us timer on BPS latchoff, per DE
		tmeas = tmu_6->read(150e-6);
		if (tmeas > 0) break;
	}
	//ifrc -= istep;
	//////istep = 0.1e-3;
	//////if(g_TurretCB)
	//////{
	//////	while( (ifrc < 20.5e-3) && (tmeas > 2e-9) )	//HL changed from 50ns to 2ns.  This is to make sure Drain is switching.
	//////	{
	//////		ifrc += istep;
	//////		tmu_6->arm();
	//////		wait.delay_10_us(10);
	//////		BPS_dvi->set_current(BPS_ch, ifrc, 	RANGE_30_MA);
	//////		wait.delay_10_us(50);		// > 120us timer on BPS latchoff, per DE
	//////		tmeas = tmu_6->read(150e-6);
	//////	}
	//////	ISD_s = ifrc-istep;	// Measure Isd just before threshold
	//////}
	//////else
	//////{
	//////	while( (ifrc < 20.5e-3) && (tmeas > 2e-9) )	
	//////	{
	//////		ifrc += istep;
	//////		tmu_6->arm();
	//////		wait.delay_10_us(15);
	//////		BPS_dvi->set_current(BPS_ch, ifrc, 	RANGE_30_MA);
	//////		wait.delay_10_us(50);		// > 120us timer on BPS latchoff, per DE
	//////		tmeas = tmu_6->read(150e-6);
	//////	}
	//////	ISD_s = ifrc-istep;	// Measure Isd just before threshold
	//////}
	//ISD_s = ifrc-istep;
	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);
	ISD_s = BPS_dvi->measure_average(10);
	// Disconnect the Sync Circuit to make sure FWD is not below GND when measuring ISD.
	////////Disconnect_InvSyn_IM();
	////////delay(3);

	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(50);
	////////////// Make sure it is off
	////////FB_ovi->set_voltage(FB_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	////////wait.delay_10_us(10);
	////////
	BPS_dvi->set_current(BPS_ch, ISD_s, 	RANGE_30_MA);
	wait.delay_10_us(100);		// > 100us
	VBPS_OV = BPS_dvi->measure_average(10);

	////////// Go down to VBPS+50mV and verify no switching
	////////FB_ovi->set_voltage(FB_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	////////wait.delay_10_us(20);
	////////BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init+0.05, 	VOLT_10_RANGE);	// DVI_9_1 
	////////wait.delay_10_us(50);

	////////// Verify no switching
	////////tmu_6->arm(); 
	////////wait.delay_10_us(10);
	////////tmeas = tmu_6->read();
	////////if (tmeas > 0)
	////////{
	////////	VBPS_OV = 0.0;
	////////	ISD_s = 0.0;
	////////}

	gVSD_s = VBPS_OV;
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();*/

	// +++++++++++++++++ tLOff_Filter_S +++++++++++++++++++//
	//if(g_TurretCB)
	//{

	//
	//		Close_relay(K3);
	//		delay(5);
	//		VBPP_Negative_Cycle();
	//	
	//		SyncHS_PowerUp_Secondary_in_Normal_Mode_Primary_TM5(Low_Vd_Input);

	//		if(MOSFET_SIZE==5)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.5,		VOLT_20_RANGE);	// OVI_1_4	

	//		delay(3);
	//		tmu_6->close_relay(TMU_HIZ_DUT1);	 // Connect TMU HIZ to Drain
	//		tmu_6->start_trigger_setup(5.2, POS_SLOPE, TMU_HIZ, TMU_IN_10V);	//FW	Channel_A_DUT1	to start trigger NEG
	//		tmu_6->stop_trigger_setup(4.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);	//FW	Channel_A_DUT1	to start trigger NEG
	//		delay(4);

	//		REQ_ovi->set_voltage(REQ_ch, gCVth_15pct_Higher,		RANGE_2_V);	// OVI_1_2	
	//		wait.delay_10_us(50);
	//		VO_dvi->set_voltage(VO_ch, 10.0, 		VOLT_10_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
	//		wait.delay_10_us(50);
	//		tmu_6->arm();
	//		wait.delay_10_us(50);
	//		BPS_dvi->set_voltage(BPS_ch, 5.5,	VOLT_10_RANGE);
	//		D_dvi->set_voltage(D_ch, 10.0,	VOLT_50_RANGE);  
	//		
	//		wait.delay_10_us(10); //100us delay only. Else, wrong measurement
	//		tmeas = 0.0;
	//	
	//		tmeas = tmu_6->read(500e-6);
	//	
	//		tLOff_Filter_S = tmeas;
	//		tmu_6->arm();
	//		wait.delay_10_us(10);
	//		tmeas = tmu_6->read(50e-6);
	//		if (tmeas > 0)
	//			tLOff_Filter_S = 0;

	//		


	//		
	//		if(tmeas > 290e-6)
	//		{
	//			delay(2);
	//		}
	//
	//}
	//else
	{

		Close_relay(K3);
		delay(5);
		VBPP_Negative_Cycle();
	//();
		SyncHS_PowerUp_Secondary_in_Normal_Mode_Primary_TM5(Low_Vd_Input);

		//if(MOSFET_SIZE==5)		
		//{
		//	if(OPCODE==4300 ||OPCODE==4500)
		//	{
		//		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4	used to be 6

		//	}
		//	else
		//	{
		//		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.5,		VOLT_20_RANGE);	// OVI_1_4	used to be 6
		//	}
		//}
		delay(3);
		tmu_6->close_relay(TMU_HIZ_DUT1);	 // Connect TMU HIZ to Drain
		tmu_6->start_trigger_setup(5.5, POS_SLOPE, TMU_HIZ, TMU_IN_10V);	//FW	Channel_A_DUT1	to start trigger NEG
		tmu_6->stop_trigger_setup(2.0,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);	//FW	Channel_A_DUT1	to start trigger NEG
		delay(4);

		if(OPCODE==4200 || OPCODE==4250)		REQ_ovi->set_voltage(REQ_ch, 5.0,		RANGE_10_V);	// OVI_1_2	
		else				                    REQ_ovi->set_voltage(REQ_ch, 5.0,		RANGE_10_V);	// OVI_1_2	
		//VO_dvi->set_voltage(VO_ch, 10.0, 		VOLT_10_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
		wait.delay_10_us(50);
		tmu_6->arm();
		wait.delay_10_us(50);
		BPS_dvi->set_voltage(BPS_ch, 5.5,	VOLT_10_RANGE);
		D_dvi->set_voltage(D_ch, 10.0,	VOLT_50_RANGE);  
			
		wait.delay_10_us(50); //100us delay only. Else, wrong measurement
		tmeas = 0.0;

		tmeas = tmu_6->read(500e-6);
	
		tLOff_Filter_S = tmeas;
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas = tmu_6->read(50e-6);
		if (tmeas > 0)
			tLOff_Filter_S = 0;
	}
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	if(g_TurretCB)
	{
		mux_20->open_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
		delay(2);
	}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  //
//							VBPP_Reset_p								     //
//		Ramp down VBPP pin and monitor Vpin current to find the threshold.	 //
//		When Vbp rest is reached, POR will change currents on feature pins.	 //
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//Vpin (300uA)
	VPIN_ovi->set_voltage(VPIN_ch, 6.0,			RANGE_10_V);
	VPIN_ovi->set_current(VPIN_ch, 300e-6,		RANGE_300_UA);
	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(30);

	VBPP_Power_Up_w_Test_Mode(gTM1_UVOV_NoDelay, ILIM_NORM);

//	DEBUG=1;
	//////////
	search_VBPP_Reset (&VBPP_Reset_p);
//	DEBUG=0;

	//Find_VBP_vs_DrainCurrent();	// Char loop for debug
	Power_Down_Primary();


	// JD separate powerup to reduce test time
	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();




	//if(DEBUG==1)
	//{
	//	printf("\nSerial_NUM = %i", SERIAL_NUM);
	//	printf("\nVBP_Supply: ISD (vBPP = 6.8V, Ramp iBPP 1mA to 10mA, expect no switching after threshold found");
	//}
			//if(DEBUG==1)
			//	printf("\nvBPP= %.2f V, iBPP_frc= %.2f mA, lcnt= %i, tmeas= %.2f us, FINE_SEARCH= %i", vfrc, ifrc*1000, lcnt, tmeas*1e6, FINE_SEARCH);
				//if(DEBUG==1)
				//	printf("\nvBPP= %.2f V, iBPP_frc= %.2f mA, lcnt= %i, tmeas= %.2f us, FINE_SEARCH= %i", vfrc, ifrc*1000, lcnt, tmeas*1e6, FINE_SEARCH);

//These two test are done at the end of Fosc_Post_S() function and datalog in this function
/****************************************************************************
 *						BPP_IS1_6p2_p, BPP_IS1_5p8_p						*
 *After ISD is found, primary stops switching, increase drain voltage to 15V*
 *and BPS voltage to 6.2V, meas BPP_IS1_6p2_p. Drop BPS voltage to 5.8V     *
 *meas BPP_IS1_5p8_p.														*	
 *Test IS1 in ILIM_RED state (See BPP_Power_Up above), to avoid the marginal*
 *discharge delay problem in ILIM_NORM powerup. If the Discharge time is    *
 *less than 3 cycles, tap will stay on for the rest of the operation, and   *
 *IS1 will be negative.													    *
 ****************************************************************************/	
//	ovi_1->disconnect(VPIN_ch);
//	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA);		
//	D_dvi->set_voltage(D_ch, 15.0,	VOLT_50_RANGE);  
//	wait.delay_10_us(50);
//	VBPP_Power_Up(ILIM_RED);
//	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
//
//	// Shut down device with ISD shutdown function
//	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);	// OVI_1_0
////	VBPP_ramp_up(gVBPP_P_Init+0.2, 6.8, 0.2);			 // vstart, vstop, vstep - To reduce undershoot
//	// 6.8V can't shutdown some devices
//	VBPP_ramp_up(gVBPP_P_Init+0.2, 7.5, 0.2);			 // vstart, vstop, vstep - To reduce undershoot
//
//	// More than 300uA for some of the 1.8 primary silicon options
//	BPP_ovi->set_current(BPP_ch, 3.0e-3, RANGE_3_MA);	// OVI_1_0
//	delay(2);
////	VBPP_ramp_down(6.8, 6.2, 0.1);						// vstart, vstop, vstep - To reduce undershoot
//	VBPP_ramp_down(7.5, 6.2, 0.1);	
//	wait.delay_10_us(400);
//
//	BPP_IS1_6p2_p = BPP_ovi->measure_average(5);
//
////	BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init+0.1, RANGE_10_V);//8.0V// DVI_9_1
//	VBPP_ramp_down(6.2, gVBPP_P_Init+0.1, 0.1);			// vstart, vstop, vstep - To reduce undershoot
//	wait.delay_10_us(500);
//
//	BPP_IS1_VBPP_p = BPP_ovi->measure_average(5);

	
	Power_Down_Everything();	//Need this power-down here else tWL_NM-P and tAR_On_NM_P will fail
	Open_All_Relays();			//Need this power-down here else tWL_NM-P and tAR_On_NM_P will fail

////		// Power down
////		Power_Down_Primary();
////		Power_Down_Secondary();
////
////	D_dvi->set_voltage(D_ch,	 0.0,	VOLT_50_RANGE);  
////	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
////	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);	// OVI_1_0
////	wait.delay_10_us(10);
////
////	Open_relay(K2);
////	Open_relay(K18);
////	Open_relay(K3);
////	tmu_6->open_relay(TMU_HIZ_DUT1);
//////	delay(2);
////	ovi_1->connect(VPIN_ch);
////	delay(2);
/****************************************************************************
 *								VBPS_Reset_s								*
 ****************************************************************************/
	//PiDatalog(func, A_VBPS_Reset_s,	VBPS_Reset_s,	set_fail_bin,	POWER_UNIT);

	//Datalog
	////PiDatalog(func, A_Vshunt_2mA_p, Vshunt_2mA_p,	set_fail_bin,	POWER_UNIT);	//Done in VBP_Init func
	////PiDatalog(func, A_Vshunt_2mA_s, Vshunt_2mA_s,	set_fail_bin,	POWER_UNIT);	//Done in VBP_Init func	

	PiDatalog(func, A_Ishunt_p,			Ishunt_p,		set_fail_bin,	POWER_MILLI);	
	PiDatalog(func, A_Vshunt_12mA_p,	Vshunt_12mA_p,	set_fail_bin,	POWER_UNIT);	//Bring alive when datalog created from PM
	PiDatalog(func, A_Ishunt_s,			Ishunt_s,		set_fail_bin,	POWER_MILLI);	

	PiDatalog(func, A_VBPP_P,			VBPP_P,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_VBPP_M,			VBPP_M,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_VBPP_HYS,			VBPP_HYS,		set_fail_bin,	POWER_UNIT);

	PiDatalog(func, A_VBPS_P,			VBPS_P,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_VBPS_M,			VBPS_M,			set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_VBPS_HYS,			VBPS_HYS,		set_fail_bin,	POWER_UNIT);

	//Temporary using VBPS_Reset_s datalog for VBPS_Reset_Delta (update CREATE for additional datalog)
	VBPS_Reset_Delta_s = VBPS_M - VBPS_Reset_s;
	//PiDatalog(func, A_VBPS_Reset_s,		VBPS_Reset_s,	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VBPS_Reset_s,		VBPS_Reset_s,	    set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VBPS_Reset_delt,	VBPS_Reset_Delta_s,	set_fail_bin,	POWER_UNIT);

	//PiDatalog(func, A_ISD_S,			ISD_s,			set_fail_bin,	POWER_MILLI);
	//gISD_s = ISD_s; // Save for later. //
	//PiDatalog(func, A_VSD_S,			VBPS_OV,		set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_tLOff_Filter_S,	tLOff_Filter_S, set_fail_bin,	POWER_MICRO);//Commented out temporary
	//PiDatalog(func, A_tOVP_S,			tOV_filter,		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_VBPP_Reset_p,		VBPP_Reset_p,	set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_ISD_p,			ISD_p,			set_fail_bin,	POWER_MILLI);
	//if (!gTrim_AR_req)
		PiDatalog(func, A_ISD_func_p,		ISD_func_p,		set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_BPP_IS1_6p2_p,	BPP_IS1_6p2_p,	set_fail_bin,	POWER_MICRO);
	//PiDatalog(func, A_BPP_IS1_VBPP_p,	BPP_IS1_VBPP_p,set_fail_bin,	POWER_MICRO);
	//--------------------------------------------------------------------
	// BPP_IS1_6p2_p is removed per Shreyas  --  05/16/14  HQL
	//--------------------------------------------------------------------
	//PiDatalog(func, A_BPP_IS1_6p2_p,gBPP_IS1_6p2_p,	set_fail_bin,	POWER_MICRO); 
	//PiDatalog(func, A_BPP_IS1_VBPP_p,gBPP_IS1_VBPP_p,set_fail_bin,	POWER_MICRO);

	if(gDEBUG==1)
	printf("Function VBP_Supply Done\n");

}
