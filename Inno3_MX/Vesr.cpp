//==============================================================================
// Vesr.cpp (User function)
// 
//    void Vesr_user_init(test_function& func)
//    void Vesr(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "Vesr.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Vesr_user_init(test_function& func)
{
	Vesr_params *ours;
    ours = (Vesr_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Vesr(test_function& func)
{
    // The two lines below must be the first two in the function.
    Vesr_params *ours;
    ours = (Vesr_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 30;

	Func_name = "Vesr";

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Vesr,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//************************************************************************************************************
	//***************** Vesr Ramp Tests **************
	//************************************************************************************************************
	//
	//	Frequency reduces as FB rises and approaches VFB threshold
	//	Measure slope and intercept of the Frequency reduction
	//	Method:	Reduce VFB to below threshold
	//			Measure T1 period
	//			Reduce VFB further
	//			Measure T2 period
	//			Calculate slope and intercept
	//
	//////////////////////////////////////////////////////////////

	float 	DeltaT1=0, DeltaT2=0, DeltaT3=0, DeltaT4=0, DeltaT5=0;
	float	VFB=0, VFB1=0, VFB2=0, VFB3=0, VFB4=0, VFB5=0;
	float	Vesr_slope1=0, Vesr_slope2=0, Vesr_int1=0, Vesr_int2=0, Vesr_knee=0, Vesr_peak=0;
	float	VFBknee = 0, VFBpeak =0;
	float	tmeas = 0;
	int		count=0;
	float	CV=0;
	float	step = 0;
	int		i = 0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//////////

	//Problem with Turret Board until all resources are reset.
	if(g_TurretCB)
	{
		//Disconnect_InvSyn_IM();
		Power_Down_Everything();
		Disconnect_InvSyn_IM();
		Open_All_Relays();
		delay(2);
	}

	tmu_6->init();
	Close_relay(K3);

 	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 
	if(g_TurretCB)
	{
		tmu_6->start_trigger_setup(1.9, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(2.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	}
	else
	{
		tmu_6->start_trigger_setup(1.9, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->stop_trigger_setup(2.2,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	}
	tmu_6->start_holdoff(20,true);		// Use holdoff to average 128 cycles, remove jitter 
	tmu_6->stop_holdoff(128,true);
	wait.delay_10_us(50);

	if(g_TurretCB)
	{
		//HL Added.
		VBPP_Negative_Cycle();
		delay(4);
	}


	//Power_Up_Secondary(Normal_Mode_with_FW, gVBPS_P_Init+50e-3);
	SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(Low_Vd_Input);

	if(g_TurretCB)
	{
		REQ_ovi->set_current(REQ_ch, 29.9e-3,		RANGE_30_MA);
	}
	else
	{
		REQ_ovi->set_current(REQ_ch, 2.99e-3,		RANGE_3_MA);//RLB prevent overrange on OVI
	}
	wait.delay_10_us(20);

	//////////

	//Find_Vfb_vs_Drain_Toff();

	//gCV_post_S = 1.3;	// For debug only

	// Single line slope 
	// First point is below CV threshold
	VFB1 = gCV_FB_S - 25e-3;
	if (fabs(VFB1) > 2.0) VFB1 = 2.0;  //RLB prevent overrange on OVI
    
	REQ_ovi->set_voltage(REQ_ch, VFB1, 		RANGE_2_V);	// OVI_1_2	

	if (gTrim_VR_S == 1) 	//internal fb resistors, set Vout to center DeltaT1
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_10_RANGE);	// DVI_9_0

	if(g_TurretCB)
	{
		wait.delay_10_us(500);//HL changed timing due to repeatability faiflure on Turret CB
	}
	else
	{
		wait.delay_10_us(40);
	}
	//Use hold off feature to average jitter out
	tmu_6->arm(128e-3); 
	wait.delay_10_us(200);
	if(g_TurretCB)
	{
		wait.delay_10_us(100);  //HL added 1ms due to 128x20us = 2.560ms.
	}
	tmeas = tmu_6->read();
	//calculate average period, T1
	tmeas = tmeas/128;
	//DeltaT1 = tmeas - gTonMax_Pt; // FW Ton = Drain Toff
	DeltaT1 = tmeas - gTonMax_S; // FW Ton = Drain Toff
	
	// Second point
	VFB2 = VFB1 - 10e-3;
	if(fabs(VFB2) > 2) VFB2 = 0;  //This is to prevent Over Range pop-up error
	REQ_ovi->set_voltage(REQ_ch, VFB2, 		RANGE_2_V);	// OVI_1_2	
	if (gTrim_VR_S == 1) 	//internal fb resistors, set Vout to center DeltaT2
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_10_RANGE);	// DVI_9_0
	if(g_TurretCB)
	{
		wait.delay_10_us(500);//HL changed timing due to repeatability faiflure on Turret CB
	}
	else
	{
		wait.delay_10_us(40);
	}
	//Use hold off feature to average jitter out
	tmu_6->arm(128e-3); 
	if(g_TurretCB)
	{
		wait.delay_10_us(500);//HL changed timing due to repeatability faiflure on Turret CB
	}
	else
	{
		wait.delay_10_us(200);
	}
	tmeas = tmu_6->read();
	//calculate average period, T2
	tmeas = tmeas/128;
	//DeltaT2 = tmeas - gTonMax_Pt; // FW Ton = Drain Toff
	DeltaT2 = tmeas - gTonMax_S; // FW Ton = Drain Toff

	// Use math to find slope and peak compensation point
	if((DeltaT1-DeltaT2)!=0)		
		Vesr_slope1 = (VFB1-VFB2)/((DeltaT1-DeltaT2)*1e6);
	else
		Vesr_slope1 = 999.0;	// Prevent Display error
	Vesr_int1 = VFB2-(Vesr_slope1*DeltaT2*1e6);

	// Calculate Vesr knee and Vesr peak
	Vesr_peak = gCV_FB_S - Vesr_int1;

	//Characterize VESR
//	DEBUG=1;
	if(gTrim_DVesrSlpAdj)	//Adaptive VESR
	{
			float VFB_thrsh, VFB_force;
			int data_cnt=0;
			double fb_val[100]={0.0};
			double Toff_val[100]={0.0};
			double t_meas, avg_per;

			VFB_thrsh = gCV_FB_S;
			data_cnt=0; t_meas=0;
			if (VFB_thrsh > 2.0) VFB_force = 1.625;  //RLB prevent overrange on OVI

			//small step loop
			for ( VFB_force =VFB_thrsh-40e-3 ;(t_meas < 10e-3) &&  (VFB_force < (VFB_thrsh)) && (data_cnt<100) ; VFB_force += 0.5e-3, data_cnt++)
			{
				REQ_ovi->set_voltage(REQ_ch, VFB_force, 		RANGE_2_V);	// OVI_1_2	

				//Use hold off feature to average jitter out
				tmu_6->arm(10e-3); 
				delay(3);	//time to count cycles
				t_meas = tmu_6->read();
				//calculate average period
				avg_per = t_meas/128;
				Toff_val[data_cnt] = avg_per - gTonMax_S; // FW Ton = Drain Toff
				fb_val[data_cnt] = VFB_force;
			}
			//data_cnt--;
			//DEBUG text File
			if(DEBUG==1 && gDEBUG)
			{
				int i=0;
				char debug_file_name[150] ="/0"; 

				strcpy (debug_file_name, "e:\\DL4\\"); 
				strcat (debug_file_name, DevName); 
				strcat (debug_file_name, "_VESR_debug.txt");

				//open file
				FILE * fpr = fopen(debug_file_name, "w");
				if (! fpr)
					return;

				//print to file
				fprintf (fpr, "\nTrim_DVesrSlpAdj bit = %i\n\n",gTrim_DVesrSlpAdj);
				for (i=0; i<=data_cnt;i++)
				{
					fprintf(fpr,"VFB= %.4f V, Toff_val = %.3f us\n",fb_val[i],Toff_val[i]*1e6);
				}
				fprintf (fpr, "End of VESR Measurements\n");
				fclose(fpr);

			}
	}	//end of Characterize VESR
//	DEBUG=0;


	REQ_ovi->set_voltage(REQ_ch, 0, 		RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(20);

	//////////
	//Disconnect_InvSyn_IM();
	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();
	delay(1);

	tmu_6->open_relay(TMU_HIZ_DUT1); // Connect TMU HIZ to Drain // 
	dvi_13->close_relay(CONN_SENSE1);
	dvi_13->close_relay(CONN_FORCE1);
	delay(3);
	
	Open_relay(K12);
	Open_relay(K21);

	// Data log results
	PiDatalog(func, A_VFB1,			VFB1,			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_DeltaT1,		DeltaT1,		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_VFB2,			VFB2,			set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_DeltaT2,		DeltaT2,		set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_Vesr_slope1,	Vesr_slope1,	set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_Vesr_int1,	Vesr_int1,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_Vesr_peak,	Vesr_peak,		set_fail_bin,	POWER_MILLI);
	

}
