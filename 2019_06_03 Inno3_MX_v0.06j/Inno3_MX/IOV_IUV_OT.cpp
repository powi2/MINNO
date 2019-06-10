//==============================================================================
// IOV_IUV_OT.cpp (User function)
// 
//    void IOV_IUV_OT_user_init(test_function& func)
//    void IOV_IUV_OT(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IOV_IUV_OT.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IOV_IUV_OT_user_init(test_function& func)
{
	IOV_IUV_OT_params *ours;
    ours = (IOV_IUV_OT_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IOV_IUV_OT(test_function& func)
{
    // The two lines below must be the first two in the function.
    IOV_IUV_OT_params *ours;
    ours = (IOV_IUV_OT_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 24;

	Func_name = "IOV_IUV_OT";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IOV_IUV_OT,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	float	iOVp	= 0, 
			iOVm	= 0, 
			iUVp	= 0, 
			iUVm	= 0;
	float	iOV_plus		=0, 
			iOV_minus		=0, 
			iOVplus_start	=0,
			iOV_Hys			=0,
			tOV_minus		=0,
			iUV_minus		=0,
			iBPP_bled_S		=0,
			iBPP_bledOff_S	=0,
			iUV_plus		=0,
			iUV_Hys			=0,
			tUV_minus		=0,
			iOV_plus_err	=0,
			iOV_plus_exp	=0,
			iOV_plus_act	=0;
	float	i_start			=0,
			i_stop			=0,
			i_step			=0,
			i_VPIN			=0,
			i_Hys			=0,
			i_force			=0,
			tmeas			=0;
	float	LoopTime[100]	={0},
			ifrc_UV[100]	={0},
			ifrc_UVm_Time	=0,
			UVm_TimeTrack	=0;
	//float	OT_Vpin0V		=0,
	//		OT_Vpin6V		=0;
	float tUV_400ms_S = 0;
	float tUV_M_counter_S = 0;
	bool	SWITCHING		=false,
			NO_SWITCHING	=false;
	int		count			=0,
			i				=0;
	float TimeStart = 0;	
	float TimeStop = 0;
	float TimeDelta = 0;
	float ExitTime = 0;
	bool  IOV_debug			=0;
	float stepDown = 0;
	int loopCount = 0;
	float BPPcurrent1 = 0;
	float BPPcurrent2 = 0;
	int ILIM_Select = ILIM_NORM;
	float tLineOVfast=0.0;
	
	if(IOV_debug)
		DEBUG = 1;

	/******************************************************************************************************
	***					IUV, IOV test(s)																***
	***																									***
	***  Notes:  Both Testmode 1 & 2 enables "No Delay" response time for UV/OV test.					***
	***          Since TM1 is 32x faster, we want to do this in TM2.									***
	***																									***
	***  Test Procedure:																				***
	***  -	Primary TestMode2 power-up with VPIN set to 6V/80uA.										***
	***		Expect Drain to be switching (Drain can set to 100mV like the PH device to lower the noise).***
	***	 -	Ramp up iVPIN until Drain stop switching to find iOV-										***
	***	 -  Ramp down iVPIN from iOV- until Drain start switching to find iOV+							***
	***	 -  Ramp down further from iOV+ until Drain stop switching to find iUV-							***
	***		Note: Require confirmation from design that TM2 did not disable UV delay (35ms)				***
	***	 -  Ramp up from iUV- until Drain start switching to find iUV+									***
	***																									***
	***  Attention:																						***
	***		If Primary in control, test has to be done within 64ms (switching ON time).					***
	***		Otherwise, it will go into ARST.															***
	*******************************************************************************************************/

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
//	//////

	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
//	tmu_6->start_trigger_setup(0.30, POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);
//	tmu_6->stop_trigger_setup(0.25,	POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(3.0,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);
	wait.delay_10_us(10);

	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	Close_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
	VBPP_Negative_Cycle();
	delay(4);

	gIOV = true;	// Used in "Power_Up_Primary_Normal_Mode" sequence
	//////Different power-up of testing iOV/iUV for different silicon Revs 
	////if(gSiliconRev_P == revB_P)
	////	SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);
	////else	//revB2 and later silicons
	////{
		VBPP_Power_Up_w_Test_Mode(gTM2_UVOV_NoDelay, ILIM_NORM);	// TM2 requires the normal wait and listen 85ms
		D_dvi->set_voltage(D_ch, 5.0, 		VOLT_50_RANGE);			// Bring Drain higher to TMU measurement during iVpin test

		Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);
		Close_relay(K5);//Connect SR to 5nF
		delay(2);

		VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0

		if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
		{
			BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
			wait.delay_10_us(10);
			BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
			wait.delay_10_us(10);
		}

		if(g_TurretCB)
		{
			D_dvi->set_voltage(D_ch, 25, 		VOLT_50_RANGE);			// Bring Drain higher to TMU measurement during iVpin test
		}
		else
		{
			D_dvi->set_voltage(D_ch, 5.0, 		VOLT_50_RANGE);			// Bring Drain higher to TMU measurement during iVpin test

		}
		
		Open_relay(K27); //Disconnect Vout from DDD7-4
		//// Provide 2 negative pulses on FW to give Secondary control.  (FW go below -100mV)
		Open_relay(K18);
		Close_relay(K21);
		Close_relay(KC5);	//improve repeatability purpose
		delay(4);
		Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
		if(g_TurretCB)
		{
			wait.delay_10_us(150);  //more than 30us quiet time on FW signal
		}
		else
		{
			wait.delay_10_us(100);  //more than 30us quiet time on FW signal
		}
		Open_relay(K21);
		Close_relay(K18);
		//Close_relay(KC5);	//improve repeatability purpose
		delay(4);
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
		wait.delay_10_us(50);
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		wait.delay_10_us(100);
		wait.delay_10_us(50);
	////}
	gIOV = false;	// Used in "Power_Up_Primary_Normal_Mode" sequence

	VPIN_ovi->set_voltage(VPIN_ch, 5.0,		RANGE_5_V);	//Can't go down to 2V.  3V is about 0.3uA lower than original
	if(gTrim_Loff_AR_P)
	{
		VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	//expect stop switching
		wait.delay_10_us(10);
		VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(10);
		VBPP_ramp_up(gVBPP_M_Init -0.25, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(10);
	}
////
////	VPIN_ovi->set_current(VPIN_ch, 160e-6,		RANGE_300_UA);	//expect stop switching
////	delay(6);
////
////
////	VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	//expect stop switching
////	delay(1);
////
////
////	VPIN_ovi->set_current(VPIN_ch, 10e-6,		RANGE_300_UA);	//expect stop switching
////	delay(1);
////
////
////	VPIN_ovi->set_current(VPIN_ch, 40e-6,		RANGE_300_UA);	//expect stop switching
////	delay(1);
////
////
////	VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	//expect stop switching
////	delay(1);
////
////


	if(1)
	{
		//*********************************************************
		//** IOV+
		//*********************************************************
		if(!gTrim_iov_Off_P)
		{
			//DEBUG = 1;
			if(g_TurretCB)
			{
				search_IOVp_Binary_TurretCB(&iOV_plus);
			}
			else
			{
				search_IOVp_Binary(&iOV_plus);
			}
			//DEBUG = 0;

			//*********************************************************
			//** IOV-
			//*********************************************************
			//Found IOV+ and step down 4uA to start searching for IOV-.
			if (fabs(iOV_plus) > 300e-6)		// to prevent range error when bad part encountered
			{
				i_VPIN	= giOV_plus_TARGET;
				//i_force = giOV_plus_TARGET + 10e-6;
			}
			else
			{
				//i_VPIN	= iOV_plus - 4e-6;
				i_VPIN	= iOV_plus;
				//i_force = iOV_plus;
			}

			//Make sure device stop switching
			i_force = 125e-6;
			VPIN_ovi->set_current(VPIN_ch, i_force,		RANGE_300_UA);	//expect no switching
			wait.delay_10_us(20);

			/*
			 This loop is not used- Commented to improve test time
			//Ramp down iVpin to be closer to iOV- threshold
			while( i_force > (i_VPIN-4e-6) )
			{
				VPIN_ovi->set_current(VPIN_ch, i_force,		RANGE_300_UA);	//expect no switching
				wait.delay_10_us(5);
				i_force -= 0.5e-6;
			}*/
			
			//step down with i_step to roughly find IOV- threshold 
			i_step = 0.25e-6;
			i_VPIN = i_VPIN - 3e-6;	// start 3uA below iOV_Plus
//			for(i=1; i<=20; i++)
			//printf("\n");
			//printf("IOV- Search\n");
			for(i=1; i<=50; i++)
			{
				
				//i_VPIN = i_VPIN - 5e-6 - i*i_step;
//				i_VPIN = i_VPIN - i*i_step;
				i_VPIN = i_VPIN - i_step;
				VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	//expect no switching
				wait.delay_10_us(20);
				if(gTrim_Loff_AR_P)
				{
					VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
					wait.delay_10_us(10);
					VBPP_ramp_up(gVBPP_M_Init -0.25, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
					wait.delay_10_us(100);
				}
				if(g_TurretCB)
				{
					wait.delay_10_us(30);   //HL added to prevent repeatability problem on Turret CB
				}
				tmu_6->arm();						
				wait.delay_10_us(20);	//Need minimum 100us for device to react to new current from nsw to sw
				tmeas = tmu_6->read(200e-6);
				/*if(DEBUG==1)
				{
					printf("i_VPIN = %.2f uA, tmeas = %.2f us\n", i_VPIN*1e6, tmeas*1e6);
				}*/
				if(tmeas > 10e-6 && tmeas < 999)	//Device switching
					break;
			}
			iOV_minus = i_VPIN;
			//Fine tune with 0.1uA step (need this???)

			iOV_Hys = iOV_plus - iOV_minus;
		}

		//*********************************************************
		//** iUV+
		//*********************************************************
		//Device is in non-switching state from tUV
		//Ramp up from 15uA to 40uA with i_step (Note that iUV+ might need to be found in less than 4ms else device stays OFF)
		//Note if above iUV+ is appllied you will see device switch for more than 100ms

		////if(gSiliconRev_P == revB_P)
		////{
		////	//*********************************************************
		////	//** iUV+
		////	//*********************************************************
		////	//Device is in non-switching state from tUV
		////	//Ramp up from 15uA to 40uA with i_step (Note that iUV+ might need to be found in less than 4ms else device stays OFF)
		////	//Note if above iUV+ is appllied you will see device switch for more than 100ms
		////	i_step	= 1e-6;
		////	i_start = 15e-6;
		////	for(i=1; i<=20; i++)
		////	{
		////		i_VPIN = i_start + i*i_step;
		////		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	//require minimum 100us for device change from nsw to sw
		////		tmu_6->arm(); 
		////		wait.delay_10_us(20);		//needed for device to go from nsw to sw
		////		tmeas = tmu_6->read(200e-6); 
		////		if(tmeas > 10e-6 && tmeas < 999)
		////		{
		////			SWITCHING = true;
		////			break;
		////		}
		////		else
		////			SWITCHING = false;
		////	}
		////	iUV_plus = i_VPIN;

		////	//*********************************************************
		////	//** iUV- 
		////	//*********************************************************
		////	//Device is in switching state from iUV+
		////	//Ramp down from IUV+ - 3uA with i_step down until device stop switching
		////	stepDown = 3e-6;
		////	loopCount = 20;
		////	if(gTrim_iuvMinus_P)
		////	{
		////		stepDown = 9e-6;
		////		loopCount = 48;
		////	}
		////	starttime	= mytimer.GetElapsedTime();
		////	LoopTime[0]	= starttime;
		////	i_step = 0.25e-6;
		////	for(i=1; i<=loopCount; i++)
		////	{
		////		LoopTime[0]	= mytimer.GetElapsedTime();
		////		ifrc_UV[i] = iUV_plus - stepDown - i*i_step;
		////		VPIN_ovi->set_current(VPIN_ch, ifrc_UV[i],		RANGE_300_UA);	
		////		wait.delay_10_us(20);
		////		LoopTime[i] = mytimer.GetElapsedTime() - LoopTime[0];
		////	}

		////	count = 0;
		////	while(SWITCHING == true && count < 1000) //40ms takes about 800 counts of 50us.  1000 is plenty
		////	{
		////		tmu_6->arm(); 
		////		wait.delay_10_us(5);
		////		tmeas = tmu_6->read(50e-6); 
		////		if(tmeas > 10e-6 && tmeas < 999)
		////		{
		////			SWITCHING = true;
		////		}
		////		else
		////		{
		////			SWITCHING = false;
		////			break;
		////		}
		////		count++;
		////	}
		////	stoptime = mytimer.GetElapsedTime();

		////	//Back track where IUV- happen with timing
		////	UVm_TimeTrack =0;
		////	ifrc_UVm_Time =0;
		////	ifrc_UVm_Time = (stoptime-starttime)*1e-6 - tUV_minus;
		////	for(i=loopCount; i>=1; i--)
		////	{
		////		UVm_TimeTrack += LoopTime[i]*1e-6;
		////		if( (ifrc_UVm_Time - UVm_TimeTrack) < 0 )
		////		{
		////			iUV_minus = ifrc_UV[i];
		////			break;
		////		}
		////	}
		////	iUV_Hys = iUV_plus - iUV_minus;
		////}
		////else	//revB2 and later silicons
		////{
			
			if(LB_Rev>=5  || g_TurretCB)
			{
				if(g_TurretCB)
				{
					D_dvi->set_voltage(D_ch, 13.0, 		VOLT_50_RANGE);			// Bring Drain higher to TMU measurement during iVpin test
				}
				else
				{
					D_dvi->set_voltage(D_ch, 4.0, 		VOLT_50_RANGE);			// Bring Drain higher to TMU measurement during iVpin test

				}

				//HL set the current 10uA to prevent repeatability failure on Turret CB
				VPIN_ovi->set_current(VPIN_ch, 10e-6,		RANGE_300_UA);	
				wait.delay_10_us(50);
			}
			else
			{
				//HL set the current 10uA to prevent repeatability failure on Turret CB  (cx copy from above)
				VPIN_ovi->set_current(VPIN_ch, 10e-6,		RANGE_300_UA);	
				wait.delay_10_us(50);
			}
			
			i_step	= 0.25e-6;
			//i_start = 15e-6;
			i_VPIN = 15e-6;
			for(i=1; i<=80; i++)
			{
				i_VPIN = i_VPIN + i_step;
				VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	//require minimum 100us for device change from nsw to sw
				if(gTrim_Loff_AR_P)
				{
					VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
					wait.delay_10_us(10);
					VBPP_ramp_up(gVBPP_M_Init -0.25, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
					wait.delay_10_us(50);
					//delay(1);
				}
				tmu_6->arm(); 
				wait.delay_10_us(20);		// ~100us needed for device to go from nsw to sw
				tmeas = tmu_6->read(100e-6); 
				if(tmeas > 10e-6 && tmeas < 999)
				{
					SWITCHING = true;
					break;
				}
				else
					SWITCHING = false;
			}
			//iUV_plus = i_VPIN+i_step;
			iUV_plus = i_VPIN;

			//*********************************************************
			//** iUV- 
			//*********************************************************
			//Device is in switching state from iUV+
			//Ramp down from IUV+ - 3uA with i_step down until device stop switching
			if(g_TurretCB)
			{
				float drain_V = 20.0;
				int exit_loop = 0;
				while(exit_loop < 2)
				{
					D_dvi->set_voltage(D_ch, drain_V, 		VOLT_50_RANGE);			// Bring Drain higher to TMU measurement during iVpin test
					wait.delay_10_us(50);
					VPIN_ovi->set_current(VPIN_ch, 30e-6,		RANGE_300_UA);	//require minimum 100us for device change from nsw to sw
					wait.delay_10_us(50);
										i_step = 0.25e-6;
					loopCount = 20;
					if(gTrim_iuvMinus_P)
					{
						stepDown = 9e-6;
						loopCount = 48;
					}
					i_VPIN = iUV_plus;
					for(i=1; i<=loopCount; i++)
					{
						i_VPIN -= i_step;
						VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
						wait.delay_10_us(20);

						tmu_6->arm(); 
						wait.delay_10_us(20);
						tmeas = tmu_6->read(100e-6); 

						if(tmeas > 10e-6 && tmeas < 999)
							SWITCHING = true;
						else
						{
							SWITCHING = false;
							break;
						}
					}
				
					iUV_minus = i_VPIN;

					iUV_Hys = iUV_plus - iUV_minus;

					if(iUV_Hys <= 1.5e-6)
					{
						drain_V = 15;
						exit_loop++;
					}
					else
					{
						exit_loop = 10;
						
					}

				}			}
			else
			{
					i_step = 0.25e-6;
					loopCount = 20;
					if(gTrim_iuvMinus_P)
					{
						stepDown = 9e-6;
						loopCount = 48;
					}
					i_VPIN = iUV_plus - stepDown;
					for(i=1; i<=loopCount; i++)
					{
						i_VPIN -= i_step;
						VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
						wait.delay_10_us(20);

						tmu_6->arm(); 
						wait.delay_10_us(20);
						tmeas = tmu_6->read(100e-6); 

						if(tmeas > 10e-6 && tmeas < 999)
							SWITCHING = true;
						else
						{
							SWITCHING = false;
							break;
						}
					}
					//iUV_minus = i_VPIN-i_step;
					iUV_minus = i_VPIN;

					iUV_Hys = iUV_plus - iUV_minus;
			}

			if (!gTrim_iov_Off_P)	// Dont do this test when OV function is disabled.
			{
				//pulse.do_pulse();

				if(g_TurretCB)
				{
					VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_5_V);	//Can't go down to 2V.  3V is about 0.3uA lower than original
					VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	//expect stop switching
					wait.delay_10_us(50);
					Close_relay(KC5);	

					tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
					tmu_6->stop_trigger_setup(1.0,	POS_SLOPE, TMU_HIZ, TMU_IN_10V);
					wait.delay_10_us(200);

					D_dvi->set_voltage(D_ch, 5, 		VOLT_50_RANGE);			// Bring Drain higher to TMU measurement during iVpin test
					wait.delay_10_us(50);

					VPIN_ovi->set_voltage(VPIN_ch, 5.0,		RANGE_5_V);	//Can't go down to 2V.  3V is about 0.3uA lower than original
					
				}
				//HL 8/1/17.  Need to bring DUT back to OV region instead of IUV region
				VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	//expect stop switching
				wait.delay_10_us(10);
				// tLine OV fast test	--------------------------------------------
				// JD moved tLine OV fast test here to prevent Latch off for AR condition when bit 19 (Latching AR) is trimmed
				ddd_7->ddd_set_voltage_ref(-2.0);	// In order to have DDD on Vpin to go tri-state
				//delay(1);
				wait.delay_10_us(10);
				//FB (2V)  pull FB above CVth to force No Switching
				ddd_7->ddd_set_hi_level(5.0);
				ddd_7->ddd_set_lo_level(0.9);								// Will immediately change to this level upon execution
				//delay(1);
				wait.delay_10_us(10);
				Close_relay(K40);		// Clamp REQ pin to 2.4V
				delay(3);
			//	REQ_ovi->set_voltage(REQ_ch, 2.0, 	RANGE_2_V);
				ddd_7->ddd_run_pattern(Low_FB_pat_start,Low_FB_pat_stop);
				wait.delay_10_us(5);
				Close_relay(K17);	//Setup FB to connect to DDD
				delay(5);
				ddd_7->ddd_run_pattern(Low_FB_pat_start,Low_FB_pat_stop);
				wait.delay_10_us(20);
				Close_relay(K12);	//Setup VPIN to connect to DDD
				delay(5);

				//Stop Drain from switching
				ddd_7->ddd_run_pattern(High_pat_FB_start,High_pat_FB_stop);
				wait.delay_10_us(5); //HL 07-13-17: changed from 200us to 50us.
				tmu_6->arm();	
				// Set FB back to Low to resume switching, also VPIN goes high to activate OV fast
				// When Vpin goes high (crossing the OV_P threshold (120uA), drain will turn off within 3us (actuall measurement around 1.8us instead)
				ddd_7->ddd_run_pattern(Low_FB_pat_start_with_Vpin,Low_FB_pat_stop_with_Vpin);
				wait.delay_10_us(10);				
				tmeas = tmu_6->read();
				tLineOVfast = tmeas - 250e-9;	// DO NOT CHANGE THIS NUMBER AS THE TIMING SUPPOSED TO BE FROM RISING VPIN TO RISING DRAIN, 
												// BUT TMU CAN ONLY MEASURE FROM DRAIN, SO MEASURE TON OF DRAIN AND SUBTRACT THIS 250ns TO GET
												// tLineOVfast.
				delay(1);
				Open_relay(K17);	//Setup FB to connect to DDD
				Open_relay(K12);	//Setup VPIN to connect to DDD
				Open_relay(K40);	//Release 2.4V clamp on REQ

				//delay(1);
				ddd_7->ddd_set_voltage_ref(0.0);	// Reset the ddd_voltage ref
				//delay(1);
				wait.delay_10_us(10);
			}


	}
//	Power_Down_Secondary();
//	Power_Down_Primary();
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();

	//*********************************************************
	//** tOV
	//*********************************************************
	if(!gTrim_iov_Off_P)
	{
		if(g_TurretCB)
		{
			//HL added to fix repeatability issue on Turret CB.  Short term solution only.
			int exit_loop = 0;
			i = 0;
			while( i < 2 && exit_loop < 1)
			{
					//HL added for Turret CB
					VBPP_Negative_Cycle();
					delay(4);
					gIOV = true;
					Close_relay(K3);	//Connect Drain to DVI
					SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);

					//HL added due to repeatability failure on Turret CB
					D_dvi->set_voltage(D_ch, 5.0, 			VOLT_50_RANGE);	// DVI_11_0		
					wait.delay_10_us(30);
					REQ_ovi->set_voltage(REQ_ch, gCV_Low, 	RANGE_2_V);	// OVI_1_2
					wait.delay_10_us(10);

					Open_relay(K18);	//FW to dvi-11-1
					delay(gDly_Wait_and_Listen_Normal_Mode);	// Skip wait n listen doesn't work
					gIOV = false;
					//HL increased the Vpin current to ensure no switching on Turret CB.
					VPIN_ovi->set_current(VPIN_ch, 200e-6,		RANGE_300_UA);	//expect no switching immediately
					wait.delay_10_us(2);
					SWITCHING = false;

					//HL added to smooth out the current on Vpin.
					VPIN_ovi->set_current(VPIN_ch, 100e-6,		RANGE_300_UA);	
					VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	//expect switching in ~100us tOV
					starttime = mytimer.GetElapsedTime();
					count = 0;
					while(SWITCHING == false && count < 10)
					{
						tmu_6->arm(); 
						wait.delay_10_us(5);
						tmeas = tmu_6->read(50e-6); 
						if(tmeas > 10e-6 && tmeas < 999)
						{
							SWITCHING = true;
							break;
						}
						count++;
					}
					stoptime = mytimer.GetElapsedTime();
					tOV_minus = (stoptime - starttime)/1e6;

					if(tOV_minus < 120e-6)
					{
						exit_loop = 2;
						i = 10;
					}
					else
					{
						i++;
					}

			//		Power_Down_Primary();
			//		Power_Down_Secondary();
					Power_Down_Everything();
					Open_All_Relays();
					Disconnect_InvSyn_IM();

			}
		}
		else
		{
			//HL added to fix repeatability issue on RS on TMT92.  Short term solution only.
			int exit_loop = 0;
			i = 0;
			while( i < 2 && exit_loop < 1)
			{
				gIOV = true;
				Close_relay(K3);	//Connect Drain to DVI
				SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);

				REQ_ovi->set_voltage(REQ_ch, gCV_Low, 	RANGE_2_V);	// OVI_1_2
				wait.delay_10_us(10);

				Open_relay(K18);	//FW to dvi-11-1
				delay(gDly_Wait_and_Listen_Normal_Mode);	// Skip wait n listen doesn't work
				gIOV = false;
				VPIN_ovi->set_current(VPIN_ch, 150e-6,		RANGE_300_UA);	//expect no switching immediately
				wait.delay_10_us(5);
				SWITCHING = false;

				VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	//expect switching in ~100us tOV
				starttime = mytimer.GetElapsedTime();
				count = 0;
				while(SWITCHING == false && count < 50)
				{
					tmu_6->arm(); 
					wait.delay_10_us(5);
					tmeas = tmu_6->read(50e-6); 
					if(tmeas > 10e-6 && tmeas < 999)
					{
						SWITCHING = true;
						break;
					}
					count++;
				}
				stoptime = mytimer.GetElapsedTime();
				tOV_minus = (stoptime - starttime)/1e6;

				if(tOV_minus < 120e-6)
				{
					exit_loop = 2;
					i = 10;
				}
				else
				{
					i++;
				}

				//Power_Down_Primary();
				//Power_Down_Secondary();
				Power_Down_Everything();
				Open_All_Relays();
				Disconnect_InvSyn_IM();

			}

	


		}
	}
	if(!gTrim_uvDelay_P)
	{
		//*********************************************************
		//** tUV
		//*********************************************************
		//Note: Above searching for IOV+, IOV- must be short (less than 10ms)
		//Set iVpin to be 10uA so it goes below iUV- and expect device will switch for ~35ms then OFF
		VBPP_Negative_Cycle();
		gIOV = true;
		Close_relay(K3);	//Connect Drain to DVI	
		SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);
		//SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Load_Vd_Input);

		REQ_ovi->set_voltage(REQ_ch, gCV_Low, 	RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(10);

		Open_relay(K18);	//FW to dvi-11-1
		//delay(2);	// Skip wait n listen doesn't work
		gIOV = false;
		VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	//expect no switching immediately
		wait.delay_10_us(5);

		SWITCHING = true;
		VPIN_ovi->set_current(VPIN_ch, 10e-6,		RANGE_300_UA);	//expect switching for 35ms then OFF 
		delay(1);
		if(gTrim_iuvMinus_P)
			VPIN_ovi->set_current(VPIN_ch, 1e-6, RANGE_300_UA);
		starttime = mytimer.GetElapsedTime();
		count = 0;
		while(SWITCHING == true && count < 1000) //40ms takes about 800 counts of 50us.  1000 is plenty
		{
			tmu_6->arm(); 
			wait.delay_10_us(5);
			tmeas = tmu_6->read(50e-6); 
			if(tmeas > 10e-6 && tmeas < 999)
			{
				SWITCHING = true;
			}
			else
			{
				SWITCHING = false;
				break;
			}
			count++;
		}
		stoptime = mytimer.GetElapsedTime();
		tUV_minus = (stoptime - starttime)/1e6;

		if(tUV_minus > 50e-3) tUV_minus = 49.99e-3; //Below use tUV_minus for delay so need to make sure this is low
	}

	//Power Down
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	wait.delay_10_us(1);

	//////////else
	//////////{

	//////////			if(DEBUG==1)
	//////////			{
	//////////				printf("\nIUV_IOV:\n");
	//////////				printf("\TESTMODE/Program Mode PowerUp\n");
	//////////			}

	//////////			//Ramp up iVpin until device stop switching (iOV- ~=110uA)
	//////////			i_start		= 80e-6;
	//////////			i_stop		= 140e-6;
	//////////			i_step		= 100e-9;	// Min forcing step size of OVI, 12 bits, 300uA range (3e-4/4096=70nA)
	//////////			i_VPIN		= i_start;
	//////////			i_Hys		= 20e-6;	// Larger than actual hysteresis
	//////////			count		= 0;

	//////////			starttime = mytimer.GetElapsedTime();

	//////////			VPIN_ovi->set_voltage(VPIN_ch, 2.0,		RANGE_2_V);	
	//////////			VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	
	//////////			wait.delay_10_us(300);

	//////////			// IOV+ binary search to find threshold where switching stops
	//////////			while ((i_stop - i_start) > i_step && count < 20)
	//////////			{
	//////////				count += 1;
	//////////				i_VPIN = i_start + (i_stop - i_start)/2;
	//////////				VPIN_ovi->set_current(VPIN_ch, i_VPIN-i_Hys,		RANGE_300_UA);	
	//////////				wait.delay_10_us(25);
	//////////				VPIN_ovi->set_current(VPIN_ch, 0.94*i_VPIN,		RANGE_300_UA);	
	//////////				wait.delay_10_us(25);
	//////////				VPIN_ovi->set_current(VPIN_ch, 0.99*i_VPIN,		RANGE_300_UA);	
	//////////				wait.delay_10_us(25);
	//////////				VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
	//////////				wait.delay_10_us(30);
	//////////				//exit while loop if device stop switching
	//////////				tmu_6->arm(); 
	//////////				wait.delay_10_us(50);
	//////////				tmeas = tmu_6->read(50e-6); 
	//////////				stoptime = mytimer.GetElapsedTime();
	//////////				if(DEBUG==1)
	//////////					printf("(iOV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
	//////////				if(tmeas < 10e-6)
	//////////				{
	//////////					//SWITCHING = false;
	//////////					i_stop = i_VPIN+3*i_step;
	//////////				}
	//////////				else if(tmeas > 10e-6)
	//////////				{
	//////////					//SWITCHING = true;
	//////////					i_start = i_VPIN-3*i_step;
	//////////				}
	//////////			}
	//////////			if(DEBUG)
	//////////				printf("\n");

	//////////			//Power Down
	//////////			Power_Down_Secondary();
	//////////			Power_Down_Primary();
	//////////			wait.delay_10_us(50);

	//////////			iOV_plus = i_VPIN;

	//////////			gIOV = true;	// Used in "Power_Up_Primary_Normal_Mode" sequence
	//////////			//Power_Up_Secondary(Normal_Mode_with_FW, gVBPS_P_Init+50e-3);
	//////////			VBPP_Negative_Cycle();
	//////////			SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);
	//////////			//REQ_ovi->set_voltage(REQ_ch, gCV_FB_TARGET - 0.05, 	RANGE_2_V);	// OVI_1_2
	//////////			REQ_ovi->set_voltage(REQ_ch, gCV_Low, 	RANGE_2_V);	// OVI_1_2
	//////////			wait.delay_10_us(50);
	//////////			gIOV = false;	// Used in "Power_Up_Primary_Normal_Mode" sequence

	//////////			// iVpin, binary search to find the start switching threshold (iOV+ ~=100uA)	iOV_Hys ~=10uA
	//////////			i_start		= iOV_plus;
	//////////			i_stop		= iOV_plus - 25e-6;
	//////////			i_step		= 250e-9;	// Min forcing step size of OVI, 12 bits, 300uA range (3e-4/4096=70nA)
	//////////			i_VPIN		= i_start;
	//////////			count		= 0;
	//////////			starttime = mytimer.GetElapsedTime();

	//////////			VPIN_ovi->set_voltage(VPIN_ch, 2.0,		RANGE_2_V);	
	//////////			wait.delay_10_us(30);

	//////////			//Binary search to save test time
	//////////			while((i_start - i_stop) > i_step && count < 25)
	//////////			{
	//////////				count += 1;
	//////////				i_VPIN = i_stop + (i_start - i_stop)/2;
	//////////				VPIN_ovi->set_current(VPIN_ch, i_VPIN+i_Hys,		RANGE_300_UA);	
	//////////				wait.delay_10_us(15);
	//////////				VPIN_ovi->set_current(VPIN_ch, 1.02*i_VPIN,		RANGE_300_UA);	
	//////////				wait.delay_10_us(20);
	//////////				VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
	//////////				wait.delay_10_us(25);
	//////////				//exit while loop if device stop switching
	//////////				tmu_6->arm(); 
	//////////				wait.delay_10_us(500);	// Long delay so intermittent switching at threshold has no effect 
	//////////				tmeas = tmu_6->read(50e-6); 
	//////////				stoptime = mytimer.GetElapsedTime();
	//////////				if(DEBUG)
	//////////					printf("(iOV+)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
	//////////				if(tmeas < 10e-6)
	//////////				{
	//////////					//SWITCHING = false;
	//////////					i_start = i_VPIN + 2*i_step;
	//////////				}
	//////////				else if(tmeas > 10e-6)
	//////////				{
	//////////					//SWITCHING = true;
	//////////					i_stop = i_VPIN - 2*i_step;
	//////////				}
	//////////			}
	//////////			iOV_minus = i_VPIN;
	//////////			if(DEBUG)
	//////////				printf("\n");

	//////////				//Power Down
	//////////			Power_Down_Secondary();
	//////////			Power_Down_Primary();
	//////////			wait.delay_10_us(10);

	//////////			gIOV = true;	// Used in "Power_Up_Primary_Normal_Mode" sequence
	//////////			//Power_Up_Secondary(Normal_Mode_with_FW, gVBPS_P_Init+50e-3);
	//////////			VBPP_Negative_Cycle();
	//////////			SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);
	//////////			REQ_ovi->set_voltage(REQ_ch, gCV_Low, 	RANGE_2_V);	// OVI_1_2
	//////////			//REQ_ovi->set_voltage(REQ_ch, gCV_FB_TARGET - 0.05, 	RANGE_2_V);	// OVI_1_2
	//////////			wait.delay_10_us(50);
	//////////			gIOV = false;	// Used in "Power_Up_Primary_Normal_Mode" sequence

	//////////			VPIN_ovi->set_voltage(VPIN_ch, 2.0,		RANGE_2_V);	
	//////////			wait.delay_10_us(30);

	//////////			//Ramp dn from iOV- until device stop switching (iUV- ~=15uA.  Acutal = 17uA)
	//////////			//Manually ramp down iVpin with 10uA per step to be 10uA above iUV_plus ~30uA
	//////////			i_VPIN		= 111e-6;
	//////////			count		= 0;
	//////////			while (i_VPIN > 30e-6 && count < 50)
	//////////			{
	//////////				i_VPIN = i_VPIN - 5e-6;
	//////////				VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
	//////////				wait.delay_10_us(15);
	//////////				count++;
	//////////			}
	//////////			
	//////////			// IUV, ~20uA, 
	//////////			i_start		= i_VPIN;
	//////////			i_stop		= i_start - 15e-6;
	//////////			i_VPIN		= i_start;
	//////////			i_step		= 250e-9;
	//////////			i_Hys		= 8e-6;	// Larger than actual hysteresis
	//////////			//count		= 0;
	//////////			starttime = mytimer.GetElapsedTime();

	//////////			//Ramp down with 1uA step until device stop switching
	//////////			for (i=0; i<40; i++)
	//////////			{
	//////////				i_VPIN -= i_step;
	//////////				if ((i_VPIN+i_Hys) <= 30e-6)
	//////////				{
	//////////					VPIN_ovi->set_current(VPIN_ch, i_VPIN+i_Hys, RANGE_30_UA);	
	//////////					wait.delay_10_us(15);
	//////////					VPIN_ovi->set_current(VPIN_ch, 1.05*i_VPIN,	RANGE_30_UA);	
	//////////					wait.delay_10_us(20);
	//////////					VPIN_ovi->set_current(VPIN_ch, 1.02*i_VPIN,	RANGE_30_UA);	
	//////////					wait.delay_10_us(20);
	//////////					VPIN_ovi->set_current(VPIN_ch, i_VPIN,	RANGE_30_UA);	
	//////////					wait.delay_10_us(25);
	//////////				}
	//////////				else
	//////////				{
	//////////					VPIN_ovi->set_current(VPIN_ch, i_VPIN+i_Hys, RANGE_300_UA);	
	//////////					wait.delay_10_us(15);
	//////////					VPIN_ovi->set_current(VPIN_ch, 1.02*i_VPIN,	RANGE_300_UA);	
	//////////					wait.delay_10_us(20);
	//////////					VPIN_ovi->set_current(VPIN_ch, i_VPIN,	RANGE_300_UA);	
	//////////					wait.delay_10_us(25);
	//////////				}
	//////////				//exit while loop if device stop switching
	//////////				tmu_6->arm(); 
	//////////				delay(20);		// Long tUV delay for device to stop switching
	//////////				tmeas = tmu_6->read(500e-6); 
	//////////				stoptime = mytimer.GetElapsedTime();
	//////////				if(DEBUG)
	//////////					printf("(iUV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
	//////////				if (tmeas < 0.1e-6) break;
	//////////			}
	//////////			iUV_minus = i_VPIN - 2*i_step;
	//////////			////////

	//////////				//Power Down
	//////////			Power_Down_Secondary();
	//////////			Power_Down_Primary();
	//////////			wait.delay_10_us(10);

	//////////			gIOV = true;	// Used in "Power_Up_Primary_Normal_Mode" sequence
	//////////			//Power_Up_Secondary(Normal_Mode_with_FW, gVBPS_P_Init+50e-3);
	//////////			VBPP_Negative_Cycle();
	//////////			SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);
	//////////			REQ_ovi->set_voltage(REQ_ch, gCV_Low, 	RANGE_2_V);	// OVI_1_2
	//////////			//REQ_ovi->set_voltage(REQ_ch, gCV_FB_TARGET - 0.05, 	RANGE_2_V);	// OVI_1_2
	//////////			wait.delay_10_us(50);
	//////////			gIOV = false;	// Used in "Power_Up_Primary_Normal_Mode" sequence
	//////////			
	//////////			VPIN_ovi->set_voltage(VPIN_ch, 2.0,		RANGE_2_V);	
	//////////			wait.delay_10_us(30);

	//////////			//Binary search from iUV- until device start switching (iUV+ ~=25uA. Actual = 24uA)	iUV_Hys ~=10uA
	//////////			i_start		= iUV_minus - 3e-6;
	//////////			i_stop		= 30e-6;	// max of 30uA range
	//////////			i_VPIN		= i_start;
	//////////			i_step		= 250e-9;
	//////////			SWITCHING	= false;
	//////////			starttime = mytimer.GetElapsedTime();
	//////////			count		= 0;

	//////////			while ((i_stop - i_start) > i_step && count < 15)
	//////////			{
	//////////				count += 1;
	//////////				i_VPIN = i_start + (i_stop - i_start)/2;
	//////////				VPIN_ovi->set_current(VPIN_ch, i_VPIN-i_Hys,		RANGE_30_UA);	
	//////////				wait.delay_10_us(15);
	//////////				VPIN_ovi->set_current(VPIN_ch, 0.94*i_VPIN,		RANGE_30_UA);	
	//////////				wait.delay_10_us(10);
	//////////				VPIN_ovi->set_current(VPIN_ch, 0.99*i_VPIN,		RANGE_30_UA);	
	//////////				wait.delay_10_us(10);
	//////////				VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_30_UA);	
	//////////				wait.delay_10_us(20);
	//////////				//exit while loop if device stop switching
	//////////				tmu_6->arm(); 
	//////////				delay(40);
	//////////				tmeas = tmu_6->read(500e-6); 
	//////////				stoptime = mytimer.GetElapsedTime();
	//////////				if(DEBUG)
	//////////					printf("(iUV+)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
	//////////				if(tmeas < 0.1e-6)
	//////////				{
	//////////					//SWITCHING = false;
	//////////					i_stop = i_VPIN+2*i_step;
	//////////				}
	//////////				else if(tmeas > 0.1e-6)
	//////////				{
	//////////					//SWITCHING = true;
	//////////					i_start = i_VPIN-2*i_step;
	//////////				}
	//////////			}
	//////////			iUV_plus = i_VPIN-2*i_step;
	//////////			////////

	//////////			//Power Down
	//////////			Power_Down_Secondary();
	//////////			Power_Down_Primary();
	//////////			wait.delay_10_us(50);

	//////////			iOV_Hys = iOV_plus - iOV_minus;
	//////////			iUV_Hys = iUV_plus  - iUV_minus;

	//////////			// Calculate error and actual
	//////////			iOV_plus_err	= (iOV_plus/giOV_plus_TARGET - 1.0)*100.0;
	//////////			iOV_plus_act	= (iOV_plus/giOV_plus_Pt_P - 1.0)*100.0;

	//////////			/******************************************************************************************************
	//////////			***					tUV-, tOV- test(s)																***
	//////////			***																									***
	//////////			***  Test Procedure:																				***
	//////////			***  -	Normal mode power-up with VPIN set to 6V/50uA.  (Expect Drain to be switching)				***
	//////////			***	 -	step iVpin below iUV- and expect device to stop switching after 35ms  (tUV-)				***
	//////////			***	 -  step iVpin above iOV- and expect device to      switch    after 100us (tOV-)				***
	//////////			*******************************************************************************************************/
	//////////			tmu_6->start_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	//////////			tmu_6->stop_trigger_setup (1.1,	NEG_SLOPE, TMU_HIZ, TMU_IN_2_5V);

	//////////			gIOV = true; // to enable Vpin on power up
	//////////			VBPP_Negative_Cycle();
	//////////			Power_Up_Primary_Normal_Mode(ILIM_NORM);
	//////////			delay(gDly_Wait_and_Listen_Normal_Mode+10);

	//////////			if(DEBUG)
	//////////				printf("\nPrimary Normal Mode PowerUp\n");
	//////////				tmu_6->arm(); 
	//////////			wait.delay_10_us(5);
	//////////			tmeas = tmu_6->read(50e-6); 
	//////////			if(tmeas > 0.1e-6)
	//////////				SWITCHING = true;
	//////////			else
	//////////			{
	//////////				SWITCHING = false;
	//////////				tUV_minus = 999;
	//////////			}

	//////////			if(SWITCHING)	// saw switching for 42ms, starts up and runs before we step Vpin current 
	//////////			{
	//////////				//tUV- (step iVpin below iUV- and expect device to stop switching after 35ms)
	//////////				i_VPIN = iUV_minus - 5e-6; //iVpin below iUV-

	//////////				starttime = mytimer.GetElapsedTime();
	//////////				VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
	//////////				wait.delay_10_us(20);

	//////////				count = 0;
	//////////				while(SWITCHING == true && count < 100)	// 35ms count ~= 63
	//////////				{
	//////////					tmu_6->arm(); 
	//////////					wait.delay_10_us(50);
	//////////					tmeas = tmu_6->read(20e-6); 
	//////////					stoptime = mytimer.GetElapsedTime();
	//////////					if(DEBUG)
	//////////						printf("(tUV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms, count = %i\n", i_VPIN*1e6, tmeas*1e6, (stoptime-starttime)/1e3, count);
	//////////					if(tmeas < 10e-6)
	//////////					{
	//////////						SWITCHING = false;
	//////////						if(DEBUG)
	//////////							printf("\n");
	//////////					}
	//////////					count++;
	//////////				}
	//////////			}
	//////////			tUV_minus = (stoptime - starttime)/1e6;

	//////////			//Power Down
	//////////			Power_Down_Primary();
	//////////			wait.delay_10_us(50);

	//////////			VBPP_Negative_Cycle();
	//////////			Power_Up_Primary_Normal_Mode(ILIM_NORM);
	//////////			delay(gDly_Wait_and_Listen_Normal_Mode+10);	// make sure wait n listen has expired
	//////////			gIOV = false; // to enable Vpin on power up

	//////////			//tOV- (step iVpin above iOV- and expect device to switch after 100us)
	//////////			if(DEBUG)
	//////////				printf("(tOV-)iVPIN = 50 uA, tmeas = %.2f us\n", tmeas*1e6);
	//////////			i_VPIN = iOV_minus+5e-6; //iVpin above iOV-
	//////////			VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);

	//////////			starttime = mytimer.GetElapsedTime();
	//////////			count = 0;
	//////////			while(SWITCHING == false && count < 100)
	//////////			{
	//////////				tmu_6->arm(); 
	//////////				wait.delay_10_us(5);
	//////////				tmeas = tmu_6->read(50e-6); 
	//////////				stoptime = mytimer.GetElapsedTime();
	//////////				if(tmeas > 0.1e-6)
	//////////				{
	//////////					SWITCHING = true;
	//////////					if(DEBUG)
	//////////						printf("\n");
	//////////				}
	//////////				count++;
	//////////			}
	//////////			tOV_minus = (stoptime - starttime)/1e6;
	//////////}

	//Open Relays
	Open_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
	wait.delay_10_us(5);

	//Power Down
	Power_Down_Secondary();
	Power_Down_Primary();
	wait.delay_10_us(10);
#if	0
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// iBPP_bled-S //
	// iBPP_bledOff-S //
	// When Vpin current falls below IUV-, the 1mA BPP bleeder current turns on.  
	// When Vpin is brought back above IUV+, the BPP bleeder current should turn off again.  
	// Without the bleeder on, the BPP current should be about 200uA. Be sure to subtract 
	// the 200uA from the bleeder current measurement. 
	// iBPP_bled-S is the bleeder current.
	// iBPP_bledOff-S is a functional go/no test to make sure the bleeder turns off.
	// Test with primary in TM1 to reduce the amount of time it takes bleeder to turn on.
	// Seconary does not need to be powered up. //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	//float DGtempAR[2000] = {0};
	//int DGcount = 0;
	float BPPcurrent1 = 0;
	float BPPcurrent2 = 0;
	//for (DGcount = 0; DGcount< 2000; DGcount++)
	//{
	//	DGtempAR[DGcount] = BPP_ovi->measure_average(5);
	//	wait.delay_10_us(100);
	//}
	
	// Setup Instruments //
	Open_relay(K1);
	Close_relay(K2);
	Open_relay(K3);
	Open_relay(K12);
	D_dvi->set_voltage(D_ch, 0, VOLT_50_RANGE);
	D_dvi->set_current(D_ch, 30e-3, RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, 0, RANGE_10_V);
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	VPIN_ovi->set_voltage(VPIN_ch, 2.0, RANGE_2_V);	
	VPIN_ovi->set_current(VPIN_ch, 35e-6, RANGE_300_UA); // Force Vpin current at powerup to enable Vpin functionality. //
	wait.delay_10_us(200); // Wait for relays. //
	
	// Powerup Primary in TM1. //
	//BPP ramp from 0V to 5V with 200mV step. //
	VBPP_ramp_up(0, 5.0, 0.2);	// vstart, vstop, vstep //

	//BPP ramp from 5V to gVBPP_PV_Init+.05 with 50mV step. //
	VBPP_ramp_up(5.0, gVBPP_PV_Init+.05, 50e-3); // vstart, vstop, vstep //			

	//BPP ramp from gVBPP_PV_Init+.05 to gVBPP_M_Init +0.25 with 100mV step. //
	VBPP_ramp_down(gVBPP_PV_Init+.05, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep //	

	// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
	int ILIM_Select = ILIM_NORM;
	if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
	else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

	// BPP set below VBP-, then back above VBP+ to complete the powerup. //
	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
	wait.delay_10_us(50);
	BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init+50e-3, RANGE_10_V); 
	wait.delay_10_us(30);
	// Primary now powered up in TM1. //

	// Raise Vpin current above IUV+ to make sure bleeder is off. //
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
	VPIN_ovi->set_current(VPIN_ch, 50e-6, RANGE_300_UA);
	wait.delay_10_us(50);
	BPPcurrent1 = BPP_ovi->measure_average(5); // Measure BPP current without bleeder. //

	// Drop VPin current below IUV- to turn bleeder on. //
	VPIN_ovi->set_current(VPIN_ch, 5e-6, RANGE_300_UA);
	wait.delay_10_us(1200); // Takes at least 8ms for bleeder to turn on. //
	iBPP_bled_S = BPP_ovi->measure_average(5); // Measure bleeder current. //
	iBPP_bled_S = iBPP_bled_S - BPPcurrent1; // Subtract off BPP current without bleeder to get actual bleeder value. //

	// Raise Vpin current above IUV+ and make sure bleeder turns back off. //
	VPIN_ovi->set_current(VPIN_ch, 50e-6, RANGE_300_UA);
	wait.delay_10_us(50);
	wait.delay_10_us(50);
	BPPcurrent2 = BPP_ovi->measure_average(5); // Measure BPP current to make sure bleeder turns off. //
	if(BPPcurrent1 < 0.5e-3 && iBPP_bled_S > 0.5e-3 && BPPcurrent2 < 0.5e-3) // Functional check, make sure bleeder turns on, then back off. //
		iBPP_bledOff_S = 1e-6; // Pass //
	else
		iBPP_bledOff_S = -999; // Fail //
#endif	
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tUV_M_counter-S
	// The tUV time measured in test mode 1. //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// Power Down //
	Power_Down_Everything_Except_Buf_Clamp();
	Open_All_Relays();
	Close_relay(K3); // Drain to dvi through pullup resistor. //
	delay(5);
//	
	// TMU setup //
	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
	tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	VBPP_Negative_Cycle();
	delay(3);
	//Power_Up_Secondary(Normal_Mode_S, gVBPS_final);
	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF
	delay(2);
	//Negative pulses on FW
	//if(g_TurretCB)
	////if(1)
	////{
	////	Open_relay(K18);
	////	Close_relay(K21);
	////	Open_relay(K27);    //HL disconnect DDD from VO
	////	delay(4);
	////	Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
	////	wait.delay_10_us(150);  //more than 30us quiet time on FW signal
	////							//HL changed to 1.5ms to prevent repeatability on Turret CB
	////	Open_relay(K21);
	////	Close_relay(K18);
	////	delay(4);
	////}
	////else
	////{
	////	Open_relay(K18);
	////	Close_relay(K21);
	////	delay(4);
	////	Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
	////	wait.delay_10_us(100);  //more than 30us quiet time on FW signal
	////	Open_relay(K21);
	////	Close_relay(K18);
	////	delay(4);
	////}
	Open_relay(K18);
	wait.delay_10_us(20);
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_10_RANGE);	// DVI_9_0
	wait.delay_10_us(50);
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	Open_relay(K27);
	wait.delay_10_us(20);
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_10_RANGE);	// DVI_9_0
	wait.delay_10_us(50);
	Connect_InvSyn_IM(Low_Vd_Input);
	delay(1);
	//if((LB_Rev >= 5||g_TurretCB) && (OPCODE==4200||OPCODE== 4250))
	//{
	//	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2.5,		VOLT_20_RANGE);	// OVI_1_4	
	//}
	if(LB_Rev==7)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2.5,		VOLT_20_RANGE);	// OVI_1_4	
	else				InvSyn_REF_ovi->set_voltage(InvSyn_ch, -4,		VOLT_20_RANGE);	// OVI_1_4	
	//InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2.5,		VOLT_20_RANGE);	// OVI_1_4	
	if(LB_Rev >= 9)	
	{
		if((OPCODE==4300 || OPCODE==4500)&& gILIM_TARGET_S > 2.2)
		{
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, -4,		VOLT_20_RANGE);	// OVI_1_4	
		}
	}
	
	VBPP_Power_Up_w_Test_Mode(gTM1_UVOV_NoDelay, ILIM_NORM);	// TM2 requires the normal wait and listen 85ms
	delay(5);
	if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
	{
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
		wait.delay_10_us(10);
	}

	// Force IUV fault //
	VPIN_ovi->set_current(VPIN_ch, 5e-6, RANGE_300_UA);
	wait.delay_10_us(1);
	// Wait for drain to stop switching //
	TimeStart = mytimer.GetElapsedTime();
//
	count = 0;
	while (count < 10000)
	{
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas = tmu_6->read(60e-6);
		if (tmeas < 0.1e-9)
			break;
		count++;
	}
//
	TimeStop = mytimer.GetElapsedTime();
	tUV_M_counter_S = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// iBPP_bled-S		(expect ~1.2mA)
	// iBPP_bledOff-S	(Functional check to make sure bleeder is off)
	// When Vpin current falls below IUV-, the 1mA BPP bleeder current turns on.  
	// When Vpin is brought back above IUV+, the BPP bleeder current should turn off again.  
	// Without the bleeder on, the BPP current should be about 200uA. Be sure to subtract 
	// the 200uA from the bleeder current measurement. 
	// iBPP_bled-S is the bleeder current.
	// iBPP_bledOff-S is a functional go/no test to make sure the bleeder turns off.
	// Test with primary in TM1 to reduce the amount of time it takes bleeder to turn on.
	// Seconary does not need to be powered up. //
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(50);
	iBPP_bled_S = BPP_ovi->measure_average(5); // Measure BPP current without bleeder. //
	// Raise Vpin current above IUV+ and make sure bleeder turns back off. //
	VPIN_ovi->set_current(VPIN_ch, 60e-6, RANGE_300_UA);
	if(g_TurretCB || LB_Rev >= 5)
	{
		wait.delay_10_us(500); //HL increased delay time due to repeatability on Turret CB
	}
	else
	{
		wait.delay_10_us(50);
	}

	BPPcurrent2 = BPP_ovi->measure_average(5); // Measure BPP current to make sure bleeder turns off. //
	if(iBPP_bled_S > 0.5e-3 && (iBPP_bled_S - BPPcurrent2) > 150e-6) // Functional check, make sure bleeder turns on, then back off. //
		iBPP_bledOff_S = 1e-6; // Pass //
	else
		iBPP_bledOff_S = -999; // Fail //
			
	delay(20);
	ddd_7->ddd_stop_pattern();
	wait.delay_10_us(10);

#if 0
	// Drain to 0V, for test mode 1. //
	D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE);
	D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
	Close_relay(K3); // Drain to dvi through pullup resistor. //
	
	// TMU setup //
	tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
	tmu_6->start_trigger_setup(0.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(1.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	// Vpin high to enable OV/UV //
	VPIN_ovi->set_current(VPIN_ch, 80e-6, RANGE_300_UA);  // Do not exceed IOV. //	
	VPIN_ovi->set_voltage(VPIN_ch, 6, RANGE_10_V); 

	// FW //
	Close_relay(K21); // Connect FW to DDD Ch3 // 

	// SR //
	SR_dvi2k->set_current(SR_ch, 0, RANGE_2_UA);	
	SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE);
	dvi_13->close_relay(BUS_SENSE1);
	dvi_13->close_relay(BUS_FORCE1);
	mux_14->close_relay(MUX_3_BUS3);

	// BPS //
	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);

	// IS //
	FWC_dvi2k->set_voltage(FWC_ch, 0, VOLT_50_RANGE);
	FWC_dvi2k->set_current(FWC_ch, 200e-3, RANGE_200_MA);

	// Vout //
	VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 5, VOLT_5_RANGE);
	
	// FB //
	REQ_ovi->set_current(REQ_ch, 30e-3, RANGE_30_MA);
	REQ_ovi->set_voltage(REQ_ch, gCV_FB_S*1.1, RANGE_2_V);

	//BPS (vPlus - 200mV)
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	

	//Make sure vBPS less than 5.5V
	if(gVBPS_M_Init < 5.5)
		VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal  
	else
		VBPS_Power_Up(4.5);			
	
	// Setup DDD //
	ddd_7->ddd_set_lo_level(0);
	ddd_7->ddd_set_hi_level(5);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(300); // Wait for all relays //

	// Remove latchoff problem. //
	VBPP_Negative_Cycle();
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
	wait.delay_10_us(10);

	// Primary Power up with TM1 //
	VBPP_ramp_up(0.0, 5.0, 0.2); // vstart, vstop, vstep //	
	wait.delay_10_us(7);

	// Set BPP //
	VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);	
	wait.delay_10_us(5);

	// Set BPP //
	VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

	// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
	ILIM_Select = ILIM_NORM;
	if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
	else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

	// Set BPP below VBP- //
	BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
	wait.delay_10_us(30);

	// Set BPP above VBP+ // 
	BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
	wait.delay_10_us(30);

	// BPS powerup //
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE);
	wait.delay_10_us(50);

	// FW pin //
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);

	// Secondary send 3 negative FW pulses. //
	Force_Neg_Pulses_FW_DDD(5, -0.5);
	wait.delay_10_us(30);
	// Secondary now has control. //
	
	// Set drain to 0V to connnect InvSync circuit //
	D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE);
	wait.delay_10_us(20);

	// FW pin //
	ddd_7->ddd_set_lo_level(0);
	wait.delay_10_us(10);

	// Connect InvSync circuit //
	Connect_InvSyn_IM(Low_Vd_Input);
	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0.5, VOLT_5_RANGE);
	Open_relay(K21); // Disconnect FW from DDD Ch3 //
	wait.delay_10_us(200);

	// FB pin //
	ddd_7->ddd_set_hi_level(gCV_FB_S*1.1);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
	wait.delay_10_us(10);
	Close_relay(K17); // Connect DDD Ch2 to FB pin //
	ddd_7->ddd_set_lo_level(0.9);
	wait.delay_10_us(200);
	REQ_ovi->set_voltage(REQ_ch, 0, RANGE_2_V);

	// Set drain.  Keep below 3V to stay in test mode 1. //
	D_dvi->set_voltage(D_ch, 2.0, VOLT_10_RANGE);
	wait.delay_10_us(50);
	
	// Start drain switching //
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop); // Bring FB low to start switching. //
	//REQ_ovi->set_voltage(REQ_ch, gCV_Low, RANGE_2_V);
	wait.delay_10_us(20);

	// Force IUV fault //
	VPIN_ovi->set_current(VPIN_ch, 10e-6, RANGE_300_UA);
	wait.delay_10_us(1);
	// Wait for drain to stop switching //
	TimeStart = mytimer.GetElapsedTime();
//
	count = 0;
	while (count < 10000)
	{
		tmu_6->arm();
		wait.delay_10_us(10);
		tmeas = tmu_6->read(100e-6);
		if (tmeas < 0.1e-9)
			break;
		count++;
	}
//
	TimeStop = mytimer.GetElapsedTime();
	tUV_M_counter_S = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
#endif
	// Power Down //
	Power_Down_Everything_Except_Buf_Clamp();
	Open_All_Relays();
	tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	// tUV_400ms-S
	// When bit#18 (UV 400ms delay) is trimmed the tUV time increaes to 400msec. //
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
	if (gTrim_uvDelay_P)
	{
		//if(gCHAR_FLOW == false)
		//	ExitTime = .05; // If production test, only wait 50msec max. //
		//else
			ExitTime = 0.6; // If characterization, expect longest UV timer ~600ms //
		
		if(g_TurretCB)
		{
					//HL added the while loop to fix the repeatability issue.  Short term solution only.
				i = 0;
				int exit_loop = 0;
				while(i < 2 && exit_loop < 1)
				{
						// Drain to 40V, for normal mode. //
						D_dvi->set_voltage(D_ch, 40.0, VOLT_50_RANGE);
						D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
						Close_relay(K3); // Drain to dvi through pullup resistor. //
						
						// TMU setup //
						tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
						tmu_6->start_trigger_setup(1.9, NEG_SLOPE, TMU_HIZ, TMU_IN_100V);
						tmu_6->stop_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_100V);
						tmu_6->start_holdoff(0,FALSE);
						tmu_6->stop_holdoff(0,FALSE);

						// Vpin high to enable OV/UV //
						VPIN_ovi->set_current(VPIN_ch, 80e-6, RANGE_300_UA);  // Do not exceed IOV. //	
						VPIN_ovi->set_voltage(VPIN_ch, 6, RANGE_10_V); 

						// FW //
						Close_relay(K21); // Connect FW to DDD Ch3 // 

						// SR //
						//SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
						//SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);	// DVI_21_1
						//delay(2);
						//mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
						//delay(2);
						Close_relay(K5);//Connect SR to 5nF
						delay(5);
						SR_dvi2k->open_relay(CONN_FORCE1);
						SR_dvi2k->open_relay(CONN_SENSE1);
						// BPS //
						BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);

						// IS //
						FWC_dvi2k->set_voltage(FWC_ch, 0, VOLT_50_RANGE);
						FWC_dvi2k->set_current(FWC_ch, 200e-3, RANGE_200_MA);

						// Vout //
						VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA);	
						VO_dvi->set_voltage(VO_ch, 5, VOLT_5_RANGE);
						
						// FB //
						REQ_ovi->set_current(REQ_ch, 30e-3, RANGE_30_MA);
						REQ_ovi->set_voltage(REQ_ch, gCV_FB_S*1.1, RANGE_2_V);
						delay(1);
						// Setup DDD //
						ddd_7->ddd_set_lo_level(0);
						ddd_7->ddd_set_hi_level(5);
						delay(1);
						ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
						delay(2);; // Wait for all relays //

						// Remove latchoff problem. //
						VBPP_Negative_Cycle();
						BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
						wait.delay_10_us(10);

						// Primary Power up with normal mode //
						VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2); // vstart, vstop, vstep //	
						wait.delay_10_us(7);

						// Set BPP //
						VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);	
						wait.delay_10_us(5);

						// Set BPP //
						VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

						// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
						ILIM_Select = ILIM_NORM;
						if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
						else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

						// Set BPP below VBP- //
						BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
						wait.delay_10_us(30);

						// Set BPP above VBP+ // 
						if(gSiliconRev_P>=3)
						{
							BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
							VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
							wait.delay_10_us(10);
						}
						else
						{
							BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
							wait.delay_10_us(30);
						}

						// Set drain //
						D_dvi->set_voltage(D_ch, 5, VOLT_10_RANGE);
						wait.delay_10_us(40);

						// BPS powerup //
						BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE);
						wait.delay_10_us(50);

						if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
						{
							BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
							wait.delay_10_us(10);
							BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
							wait.delay_10_us(10);
						}

						// FW pin //
						ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);

						// Secondary send 3 negative FW pulses. //
						Force_Neg_Pulses_FW_DDD(5, -0.5);
						wait.delay_10_us(30);
						// Secondary now has control. //
						
						// Set drain to 0V to connnect InvSync circuit //
						D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE);
						delay(1);;

						// FW pin //
						ddd_7->ddd_set_lo_level(0);
						delay(1);

						// Connect InvSync circuit //
						Connect_InvSyn_IM(Low_Vd_Input);
						Open_relay(K21); // Disconnect FW from DDD Ch3 //
						wait.delay_10_us(200);

						// FB pin //
						ddd_7->ddd_set_hi_level(gCV_FB_S*1.05);
						delay(1);
						ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
						wait.delay_10_us(50);
						Close_relay(K17); // Connect DDD Ch2 to FB pin //
						delay(4);
						//wait.delay_10_us(200);
						REQ_ovi->set_voltage(REQ_ch, 0, RANGE_2_V);

						// Set drain //
						D_dvi->set_voltage(D_ch, 5, VOLT_10_RANGE);
						wait.delay_10_us(50);
						
						// Start drain switching //
						ddd_7->ddd_end_pattern(FB_100kHz_loop_pulse_stop);
						delay(1); //HL added.
						ddd_7->ddd_run_pattern(); // Need to do a stop pattern when you don't want ddd looping //
						wait.delay_10_us(50);

						// Force IUV fault //
						VPIN_ovi->set_current(VPIN_ch, 10e-6, RANGE_300_UA);
						wait.delay_10_us(50);
						
						// Wait for drain to stop switching //
						TimeStart = mytimer.GetElapsedTime();
						count = 0;
						while (count < 10000)
						{
							tmu_6->arm();
							wait.delay_10_us(20);
							tmeas = tmu_6->read(200e-6);

							TimeStop = mytimer.GetElapsedTime();
							TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
							if (tmeas < 0.1e-9 || (TimeDelta > ExitTime))
								break;
							count++;
						}
						TimeStop = mytimer.GetElapsedTime();
						tUV_400ms_S = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
						ddd_7->ddd_stop_pattern();

						if(tUV_400ms_S < 300e-3||tUV_400ms_S > 600e-3 )
						{
							i++;
						}
						else
						{
							i = 10;
							exit_loop = 10;
						}

						// Power Down //
						Power_Down_Everything_Except_Buf_Clamp();
						Open_All_Relays();
						tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 
				}
		}
		else
		{
				// Drain to 40V, for normal mode. //
				D_dvi->set_voltage(D_ch, 40.0, VOLT_50_RANGE);
				D_dvi->set_current(D_ch, 300e-3, RANGE_300_MA);
				Close_relay(K3); // Drain to dvi through pullup resistor. //
				
				// TMU setup //
				tmu_6->close_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
				tmu_6->start_trigger_setup(1.9, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
				tmu_6->stop_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_25V);
				tmu_6->start_holdoff(0,FALSE);
				tmu_6->stop_holdoff(0,FALSE);

				// Vpin high to enable OV/UV //
				VPIN_ovi->set_current(VPIN_ch, 80e-6, RANGE_300_UA);  // Do not exceed IOV. //	
				VPIN_ovi->set_voltage(VPIN_ch, 6, RANGE_10_V); 

				// FW //
				Close_relay(K21); // Connect FW to DDD Ch3 // 

				// SR //
				/*SR_dvi2k->set_current(SR_ch, 0, RANGE_2_UA);	
				SR_dvi2k->set_voltage(SR_ch, 0.0, VOLT_2_RANGE);
				dvi_13->close_relay(BUS_SENSE1);
				dvi_13->close_relay(BUS_FORCE1);
				mux_14->close_relay(MUX_3_BUS3);*/

				SR_dvi2k->open_relay(CONN_FORCE1);
				SR_dvi2k->open_relay(CONN_SENSE1);
				Close_relay(K5);//Connect SR to 5nF
				delay(2);

				// BPS //
				BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);

				// IS //
				FWC_dvi2k->set_voltage(FWC_ch, 0, VOLT_50_RANGE);
				FWC_dvi2k->set_current(FWC_ch, 200e-3, RANGE_200_MA);

				// Vout //
				VO_dvi->set_current(VO_ch, 300e-3, RANGE_300_MA);	
				VO_dvi->set_voltage(VO_ch, 5, VOLT_5_RANGE);
				
				// FB //
				REQ_ovi->set_current(REQ_ch, 30e-3, RANGE_30_MA);
				REQ_ovi->set_voltage(REQ_ch, 0.9, RANGE_2_V);
				delay(1);
				// Setup DDD //
				ddd_7->ddd_set_lo_level(0);
				ddd_7->ddd_set_hi_level(5);
				delay(1);
				ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
				delay(2);; // Wait for all relays //

				// Remove latchoff problem. //
				VBPP_Negative_Cycle();
				BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA);
				wait.delay_10_us(10);

				// Primary Power up with normal mode //
				VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2); // vstart, vstop, vstep //	
				wait.delay_10_us(7);

				// Set BPP //
				VBPP_ramp_up(5.0, gVBPP_PV_final, 50e-3);	
				wait.delay_10_us(5);

				// Set BPP //
				VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

				// Determine what ILIM mode we want to power-up in (IMPORTANT: ZF-P MUST BE TRIMMED TO RECOGNIZE) //
				ILIM_Select = ILIM_NORM;
				if (ILIM_Select == ILIM_NORM) wait.delay_10_us(3);	// 1.0 uF (ILIM) 30us //
				else if(ILIM_Select == ILIM_INCR) wait.delay_10_us(150); // 10 uF (ILIM+1) 1.2ms //

				// Set BPP below VBP- //
				BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init-200e-3, RANGE_10_V);
				wait.delay_10_us(30);

				// Set BPP above VBP+ // 
				if(gSiliconRev_P>=3)
				{
					BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
					VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
					wait.delay_10_us(10);
				}
				else
				{
					BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, RANGE_10_V);
					wait.delay_10_us(30);
				}

				// Set drain //
				D_dvi->set_voltage(D_ch, 5, VOLT_10_RANGE);
				wait.delay_10_us(40);

				// BPS powerup //
				BPS_dvi->set_voltage(BPS_ch, gVBPS_final, VOLT_10_RANGE);
				wait.delay_10_us(50);

				if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
				{
					BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
					wait.delay_10_us(10);
					BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
					wait.delay_10_us(10);
				}

				// FW pin //
				ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
				wait.delay_10_us(10); 
				// Secondary send 3 negative FW pulses. //
				Force_Neg_Pulses_FW_DDD(5, -0.5);
				wait.delay_10_us(30);
				// Secondary now has control. //
				
				// Set drain to 0V to connnect InvSync circuit //
				D_dvi->set_voltage(D_ch, 0, VOLT_10_RANGE);
				delay(1);

				// FW pin //
				ddd_7->ddd_set_lo_level(0);
				//delay(1);
				wait.delay_10_us(10);

				// Connect InvSync circuit //
				Connect_InvSyn_IM(Low_Vd_Input);
				Open_relay(K21); // Disconnect FW from DDD Ch3 //
				wait.delay_10_us(200);

				// FB pin //
				if(LB_Rev>=5 )
					ddd_7->ddd_set_hi_level(0.9);  //RevE LB required to subtract 50mV from VFB.
				else
					ddd_7->ddd_set_hi_level(gCV_FB_S*1.05);
				//delay(1);
				wait.delay_10_us(10);
				ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);
				wait.delay_10_us(50);
				Close_relay(K17); // Connect DDD Ch2 to FB pin //
				delay(4);
				//wait.delay_10_us(200);
				REQ_ovi->set_voltage(REQ_ch, 0, RANGE_2_V);

				// Set drain //
				D_dvi->set_voltage(D_ch, 5, VOLT_10_RANGE);
				wait.delay_10_us(50);  
				
				// Start drain switching //
				ddd_7->ddd_end_pattern(FB_100kHz_loop_pulse_stop);
				ddd_7->ddd_run_pattern(); // Need to do a stop pattern when you don't want ddd looping //
				wait.delay_10_us(50);

				// Force IUV fault //
				VPIN_ovi->set_current(VPIN_ch, 10e-6, RANGE_300_UA);
				wait.delay_10_us(50);  //Fixed repeatability issue with Rasco LB Rev E
				
				// Wait for drain to stop switching //
				TimeStart = mytimer.GetElapsedTime();
				count = 0;
				while (count < 10000)
				{
					tmu_6->arm();
					wait.delay_10_us(20);
					tmeas = tmu_6->read(200e-6);

					TimeStop = mytimer.GetElapsedTime();
					TimeDelta = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
					if (tmeas < 0.1e-9 || (TimeDelta > ExitTime))
						break;
					count++;
				}
				TimeStop = mytimer.GetElapsedTime();
				tUV_400ms_S = (TimeStop - TimeStart)*1e-6; // Convert from usec to seconds //
				ddd_7->ddd_stop_pattern();

				// Power Down //
				Power_Down_Everything_Except_Buf_Clamp();
				Open_All_Relays();
				tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain // 
		}
	}

	iOV_plus_err	= (iOV_plus/giOV_plus_TARGET - 1.0)*100.0;
	// Datalog
	if(!gTrim_iov_Off_P)
	{
		PiDatalog(func, A_iOV_plus,		iOV_plus,		set_fail_bin,	POWER_MICRO);	
		PiDatalog(func, A_iOV_plus_err,	iOV_plus_err,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_iOV_minus,	iOV_minus,		set_fail_bin,	POWER_MICRO);	
		PiDatalog(func, A_iOV_Hys,		iOV_Hys,		set_fail_bin,	POWER_MICRO);	
		PiDatalog(func, A_tOV_minus,	tOV_minus,		set_fail_bin,	POWER_MICRO);	
		//A_iOV_plus_err,

		if(TRIM_ENABLE)
		{
			//** iOV_plus_act
			//if( giOV_plus_Pt_P !=0)		iOV_plus_act = (giOV_plus_Pt_P/iOV_plus -1)*100;
			if( giOV_plus_Pt_P !=0)		iOV_plus_act = (1 - giOV_plus_Pt_P/iOV_plus)*100;	
			else 						iOV_plus_act = 999.0;

			PiDatalog(func, A_iOV_plus_exp,		giOV_plus_exp,	set_fail_bin,	POWER_UNIT);	
			PiDatalog(func, A_iOV_plus_act,		iOV_plus_act,	set_fail_bin,	POWER_UNIT);	
		}		
	}
	PiDatalog(func, A_iUV_minus,	iUV_minus,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_iUV_plus,		iUV_plus,		set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_iUV_Hys,		iUV_Hys,		set_fail_bin,	POWER_MICRO);

	PiDatalog(func, A_iBPP_bled, iBPP_bled_S, set_fail_bin, POWER_MICRO);
	PiDatalog(func, A_iBPP_bledOff, iBPP_bledOff_S, set_fail_bin, POWER_MICRO);
	if(!gTrim_uvDelay_P)
		PiDatalog(func, A_tUV_minus,	tUV_minus,		set_fail_bin,	POWER_MILLI);	
//	PiDatalog(func, A_OT_Vpin6V,	OT_Vpin6V,		set_fail_bin,	POWER_UNIT);	
//	PiDatalog(func, A_OT_Vpin0V,	OT_Vpin0V,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_tUV_M_counter, tUV_M_counter_S, set_fail_bin, POWER_MILLI);	
	if (gTrim_uvDelay_P)
		PiDatalog(func, A_tUV_400ms, tUV_400ms_S, set_fail_bin, POWER_MILLI);
	if (!gTrim_iov_Off_P)	// This test is disabled when iOV_Off bit trimmed.
		PiDatalog(func, A_tLineOVfast, tLineOVfast, set_fail_bin, POWER_MICRO);



	if(gDEBUG==1)
		printf("Function IOV_IUV_OT Done\n");

}
