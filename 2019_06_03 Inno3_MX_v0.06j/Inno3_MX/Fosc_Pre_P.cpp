//==============================================================================
// Fosc_Pre_P.cpp (User function)
// 
//    void Fosc_Pre_P_user_init(test_function& func)
//    void Fosc_Pre_P(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Fosc_Pre_P.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Fosc_Pre_P_user_init(test_function& func)
{
	Fosc_Pre_P_params *ours;
    ours = (Fosc_Pre_P_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Fosc_Pre_P(test_function& func)
{
    // The two lines below must be the first two in the function.
    Fosc_Pre_P_params *ours;
    ours = (Fosc_Pre_P_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	Func_name = "Fosc_Pre_P";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Fosc_Pre_P,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_GRR == 0 && (OPCODE != 4200 || TRIM_ENABLE == 0))
		return;

	float Fosc_pt_P=0.0;
	float tmeas=0.0,
		  tElapse=0.0;
	int   lcnt =0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//////////
	
/****************************************************************************
 *					Fosc_pt_P: Primary Frequency							*
 * Note: Primay frequency doesn't have Jitter							    *
 ****************************************************************************/

	Close_relay(K3);
 	tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 

	//tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	//tmu_6->stop_trigger_setup(2.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	if(g_TurretCB)
	{
		tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(1.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	}
	else
	{
		tmu_6->start_trigger_setup(0.5, NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
		tmu_6->stop_trigger_setup(1.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_5V);
	}
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	delay(4);
////	D_dvi->set_current(D_ch, 300e-3,RANGE_300_MA);	
////
////	VBPP_Power_Up_w_Test_Mode(gTM1_p, ILIM_NORM);	//
////
////	//Wait and Listen time
////	tmeas	= 0.0;
////	tElapse = 0;
////	while(tElapse<5e-3 && tmeas < 1e-6)
////	{
////		tmu_6->arm();					
////		wait.delay_10_us(10);			
////		tmeas = tmu_6->read(100e-6);
////		tElapse += 100e-6; //Estimated time per loop without the arm() and read() in account.
////	}
////
////	tmu_6->start_holdoff(10,TRUE);
////	tmu_6->stop_holdoff(10,TRUE);
//////	tmu_6->stop_holdoff(50,TRUE);
//////	tmu_6->stop_holdoff(128,TRUE);
////	wait.delay_10_us(5);
////
////	tmu_6->arm();						// Device doing auto-restart
////	wait.delay_10_us(150);				// Wait for TMU to trigger and to capture 128 cycles (require minimum 1280us wait if 10us period)
////	tmeas = tmu_6->read(1.5e-3);	 

		//update TMU setting to have better Freq measurement
		tmu_6->start_holdoff(5,TRUE);
		tmu_6->stop_holdoff(128,TRUE);
		wait.delay_10_us(10);			

		////Setup Vpin for digital clocking
		//ovi_1->disconnect(OVI_CHANNEL_1);
		//wait.delay_10_us(100);  
		//// Initialize DDD
		//ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
		//ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
		//delay(1);
		//ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		//wait.delay_10_us(10);
		//Close_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
		//delay(3);

		Power_Up_Primary_BypassWL_TM5(ILIM_NORM);

		tmu_6->arm();					
		delay(6);			// Wait for TMU to trigger and to capture 128 cycles
		tmeas = tmu_6->read(6e-3);	 
		tmeas/=128;

	if	   (tmeas>99)	Fosc_pt_P=999e3;
	else if(tmeas==0)	Fosc_pt_P=-999e3;
	else				Fosc_pt_P=1/(tmeas);
//	else				Fosc_pt_P=1/(tmeas/50);
//	else				Fosc_pt_P=tmeas/128;

	//if (tmeas != 0 && tmeas != 999)
	//		Fosc_pt_P = 1/tmeas;
	//	else
	//		Fosc_pt_P = 0.0;	

	gFosc_pt_P = Fosc_pt_P;	// Pass to global variable

	//Power down
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	////D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0	
	////wait.delay_10_us(20);
	////VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//////BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);		// OVI_1_0
 	tmu_6->open_relay(TMU_HIZ_DUT1); // Disconnect TMU HIZ from Drain 
	////Open_relay(K3);
	////Open_relay(K12);

	//Datalog
	PiDatalog(func, A_Fosc_pt_P,	Fosc_pt_P,		set_fail_bin,	POWER_KILO);	

	if(gDEBUG)
	printf("Function_Fosc_Pre_P_Done\n");

}
