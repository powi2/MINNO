//==============================================================================
// IOV_Pre_P.cpp (User function)
// 
//    void IOV_Pre_P_user_init(test_function& func)
//    void IOV_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "IOV_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void IOV_Pre_P_user_init(test_function& func)
{
	IOV_Pre_P_params *ours;
    ours = (IOV_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void IOV_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    IOV_Pre_P_params *ours;
    ours = (IOV_Pre_P_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 24;

	Func_name = "IOV_Pre";

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_IOV_Pre_P,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//if (g_GRR == 0 && (OPCODE != 4200 || TRIM_ENABLE == 0))
	//	return;

	float	iOV_plus_pre	=0;
	float	i_start			=0,
			i_stop			=0,
			i_step			=0,
			i_VPIN			=0,
			i_Hys			=0,
			tmeas			=0;
	bool	SWITCHING		=false;
	int		count			=0;
	float	vfrc = 0.0, vstep = 0.0;
	int		cnt=0;
	bool  IOV_Pre_debug =0;
	float	Lo_CVpre		=0,
			Hi_CVpre		=0;
	IOV_Pre_debug = 0;

	if(g_GRR == 1)
	{
		IOV_Pre_debug = 1;
	
	}

	if(IOV_Pre_debug)
		DEBUG = 1;

	/******************************************************************************************************
	***					IUV, IOV test(s)																***
	***																									***
	***  Notes:  Both Testmode 1 & 2 enables "No Delay" response time for UV/OV test.					***
	***          Since TM1 is 32x faster, we want to do this in TM2										***
	***																									***
	***  Test Procedure:																				***
	***  -	Primary TestMode2 power-up with VPIN set to 6V/80uA.										***
	***		Expect Drain to be switching (Drain can set to 100mV like the PH device to lower the noise).***
	***	 -	Ramp up iVPIN until Drainstop switching to find iOV-										***
	***																									***
	***  Attention:																						***
	***		If Primary in control, test has to be done within 64ms (switching ON time).					***
	***		Otherwise, it will go into ARST.															***
	*******************************************************************************************************/
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
//	//////
	//pulse.do_pulse();
	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
//	tmu_6->start_trigger_setup(0.30, POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);
//	tmu_6->stop_trigger_setup(0.25,	POS_SLOPE, TMU_HIZ, TMU_IN_2_5V);
	tmu_6->start_trigger_setup(2.0, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	tmu_6->stop_trigger_setup(3.0,	POS_SLOPE, TMU_HIZ, TMU_IN_5V);
	wait.delay_10_us(10);

	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	Close_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
	VBPP_Negative_Cycle();
	delay(4);

//pulse.do_pulse();

	//Power Up
	gIOV = true;	// Used in "Power_Up_Primary_Normal_Mode" sequence
	//Different power-up of testing iOV/iUV for different silicon Revs 
	////if(gSiliconRev_P == revB_P)
	////	SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);
	////else	//revB2 and later silicons
	{

		//HL Repeatability failure.  Possible SR pin glitch related ==> Need solid GND on SR pin.
		//SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
		//SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);	// DVI_21_1
		//delay(2);
		//mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
		//delay(2);
		//pulse.do_pulse();
		VBPP_Power_Up_w_Test_Mode(gTM2_UVOV_NoDelay, ILIM_NORM);	// TM2 requires the normal wait and listen 85ms
		//pulse.do_pulse();
		D_dvi->set_voltage(D_ch, 5.0, 		VOLT_50_RANGE);			// Bring Drain higher to TMU measurement during iVpin test
		//wait.delay_10_us(10);//Added by KJ
		////B3 material debug
		//BPP_ovi->set_current(BPP_ch, 10e-3,	RANGE_30_MA);
		//wait.delay_10_us(10);
		//BPP_ovi->set_voltage(BPP_ch, gVBPP_P_final, 	RANGE_10_V);	// OVI_1_0
		//wait.delay_10_us(10);
//pulse.do_pulse();
		//delay(90);
		Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);

	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF

	delay(2);

		//HL added to fix glitch on VO pin. 06/19/17
		VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
		//pulse.do_pulse();
		//if(g_TurretCB)
		if(1)
		{
			BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	
			wait.delay_10_us(20);
			Force_Neg_Pulses_FW_DDD(0, 0);	//Force FW to GND to prevent glitch on SR pin.
		}
		if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
		{
			BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
			wait.delay_10_us(10);
			BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
			wait.delay_10_us(10);
		}

		REQ_ovi->set_voltage(REQ_ch, gCV_Low, 	RANGE_2_V);
		wait.delay_10_us(10);

		Open_relay(K27); //Disconnect Vout from DDD7-4
		//// Provide 2 negative pulses on FW to give Secondary control.  (FW go below -100mV)
		Open_relay(K18);
		Close_relay(K21);
		delay(4);
		Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
		//wait.delay_10_us(10);
		//Force_Neg_Pulses_FW_DDD(5, -0.5);
		//wait.delay_10_us(10);
		//Force_Neg_Pulses_FW_DDD(5, -0.5);

		if(g_TurretCB)			wait.delay_10_us(150);  //more than 30us quiet time on FW signal
		else					wait.delay_10_us(100);  //more than 30us quiet time on FW signal

		Open_relay(K21);
		Close_relay(K18);
		Close_relay(KC5);	//improve repeatability purpose
		delay(4);
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
		wait.delay_10_us(50);
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		wait.delay_10_us(100);
		//wait.delay_10_us(50);
	}
	gIOV = false;	// Used in "Power_Up_Primary_Normal_Mode" sequence

	if (g_GRR == 1 || (OPCODE == 4200 && TRIM_ENABLE == 1))
	{
		if(1)
		{
			if(g_TurretCB)
			{
				//Drain requires to be set at 20V to correlate with Rasco LB.
				//Somehow, IOV is a function of Drain voltage.  Need to inform Charles.
				D_dvi->set_voltage(D_ch, 20, 		VOLT_50_RANGE);			// Bring Drain higher to TMU measurement during iVpin test
			}
			REQ_ovi->set_voltage(REQ_ch, 1.7, 	RANGE_2_V);	// OVI_1_2
			wait.delay_10_us(50);
			//pulse.do_pulse();
			VPIN_ovi->set_voltage(VPIN_ch, 5.0,		RANGE_5_V);	//Can't go down to 2V.  3V is about 0.3uA lower than original
			wait.delay_10_us(20);
			if(gTrim_Loff_AR_P)
			{
				VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	//expect stop switching
				wait.delay_10_us(10);
				VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
				wait.delay_10_us(10);
				VBPP_ramp_up(gVBPP_M_Init -0.25, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
				wait.delay_10_us(10);
			}
			if(g_TurretCB)
			{
				search_IOVp_Binary_TurretCB(&iOV_plus_pre);
			}
			else
			{
				//pulse.do_pulse();
				search_IOVp_Binary(&iOV_plus_pre);
			}
			

			giOV_plus_Pt_P = iOV_plus_pre;
		}
		else
		{
			REQ_ovi->set_voltage(REQ_ch, gCV_Low, 	RANGE_2_V);	// OVI_1_2
			wait.delay_10_us(50);
			if(DEBUG==1 && gDEBUG)
			{
				printf("\nIUV_IOV:\n");
				printf("TESTMODE/Program Mode PowerUp\n");
			}

			//Ramp up iVpin until device stop switching (iOV- ~=110uA)
			i_start		= 80e-6;
			i_stop		= 140e-6;
			i_step		= 100e-9;	// Min forcing step size of OVI, 12 bits, 300uA range (3e-4/4096=70nA)
			i_VPIN		= i_start;
			i_Hys		= 20e-6;	// Larger than actual hysteresis
			count		= 0;

			starttime = mytimer.GetElapsedTime();

			VPIN_ovi->set_voltage(VPIN_ch, 5.0,		RANGE_5_V);	
			VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	
			wait.delay_10_us(300);

			// IOV+ binary search to find threshold where switching stops
			while ((i_stop - i_start) > i_step && count < 20)
			{
				count += 1;
				i_VPIN = i_start + (i_stop - i_start)/2;
				VPIN_ovi->set_current(VPIN_ch, i_VPIN-i_Hys,		RANGE_300_UA);	
				wait.delay_10_us(25);
				VPIN_ovi->set_current(VPIN_ch, 0.94*i_VPIN,		RANGE_300_UA);	
				wait.delay_10_us(25);
				VPIN_ovi->set_current(VPIN_ch, 0.99*i_VPIN,		RANGE_300_UA);	
				wait.delay_10_us(25);
				VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
				wait.delay_10_us(30);
				//exit while loop if device stop switching
				tmu_6->arm(); 
				wait.delay_10_us(50);
				tmeas = tmu_6->read(50e-6); 
				stoptime = mytimer.GetElapsedTime();
				if(DEBUG==1 && gDEBUG)
					printf("(iOV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
				if(tmeas < 10e-6)
				{
					//SWITCHING = false;
					i_stop = i_VPIN+3*i_step;
				}
				else if(tmeas > 10e-6)
				{
					//SWITCHING = true;
					i_start = i_VPIN-3*i_step;
				}
			}
			if(DEBUG && gDEBUG)
				printf("\n");

			iOV_plus_pre = i_VPIN + i_step; 
			giOV_plus_Pt_P = iOV_plus_pre;

		}
	}

	
	//Power Down
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();

	//gCV_Low = 1.7;

	// Datalog iOV_plus_pre
	if (g_GRR == 1 || (OPCODE == 4200 && TRIM_ENABLE == 1))
		PiDatalog(func, A_iOV_plus_pre,	iOV_plus_pre,		set_fail_bin,	POWER_MICRO);


	if(gDEBUG==1)
	printf("IOV_Pre_P done\n");

	if(IOV_Pre_debug)
		DEBUG = 0;

}
