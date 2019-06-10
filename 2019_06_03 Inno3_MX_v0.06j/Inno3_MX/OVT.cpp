//==============================================================================
// OVT.cpp (User function)
// 
//    void OVT_user_init(test_function& func)
//    void OVT(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "OVT.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void OVT_user_init(test_function& func)
{
	OVT_params *ours;
    ours = (OVT_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void OVT(test_function& func)
{
    // The two lines below must be the first two in the function.
    OVT_params *ours;
    ours = (OVT_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "OVT";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_OVT,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (OPCODE==4300 ||OPCODE==4500)
		return;

	int   OVT_OFF= 0,
		  OVT_ON =0;
	float tmeas=0.0, 
		  tElapse=0.0,
		  WAIT_n_LISTEN_TM_starttime=0,
		  WAIT_n_LISTEN_TM_stoptime=0, 
		  WAIT_n_LISTEN_TM_time=0;
	float	t_hi=0.0, t_lo=0.0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	ovi_1->disconnect(OVI_CHANNEL_1);	// Vpin does not use ovi-1-1 for Iz function
	//delay(1);                           // HL: Do not remove this delay.  Without it, DDD pattern seems to be corrupted after less than 100 runs.
	// Initialize DDD
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	//wait.delay_10_us(10);

	Close_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
	Close_relay(K3);					// Connect Drain	to R1 and L1 Load
	tmu_6->close_relay(TMU_HIZ_DUT1);   // Connect TMU HIZ	to Drain 

	tmu_6->start_trigger_setup(0.4, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
	tmu_6->stop_trigger_setup(0.5,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);

	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);
	VBPP_Negative_Cycle();
	
	delay(4);
	



/*
	**************************************  OVER TEMPERATURE	*********************************************************
	* Description:																										*
	*	The OT test is no longer tested under testmode1.  This allows all tests that are done under testmode1			*
	*	to be run under all temperatures without interference from the OT test.											*
	*																													*
	*	Entry into OT mode follows a similar sequence as that for Write and Program; the difference is that we clock in *
	*	4 posedges on VPIN.  Once that is done, we keep drain low, so it stays in testmode1 (like Inno3).  Finish the	*
	*	zig-zag on BP and the primary will start switching.  With VPIN at 0, the OT threshold will be around ~60C; VPIN *
	*	at 1, threshold drops to ~19C, so at room temp of 25C, it should stop switching.								*
	*********************************************************************************************************************
*/


	Powerup_Primary_in_Testmode(gOT_Mode);



	WAIT_n_LISTEN_TM_starttime = mytimer.GetElapsedTime();
	tElapse = 0;
	tmeas = 0;
	while(tElapse<7e-3 && tmeas < 0.1e-9)
	{
		tmu_6->arm();					
		wait.delay_10_us(10);
		if(g_TurretCB)
		{
			wait.delay_10_us(20);
		}
		tmeas = tmu_6->read(40e-6);
		tElapse += 40e-6; //Estimated time per loop without the arm() and read() in account.
	}
	WAIT_n_LISTEN_TM_stoptime = mytimer.GetElapsedTime();
	WAIT_n_LISTEN_TM_time = (WAIT_n_LISTEN_TM_stoptime - WAIT_n_LISTEN_TM_starttime)*1e-6;

	if(WAIT_n_LISTEN_TM_time < 7e-3) // Possible test time saving here //
	{
		gDly_Wait_and_Listen_Test_Mode	 = WAIT_n_LISTEN_TM_time*1e5 + 10;	//add another 100us so we are sure in switching state
		gDly_Wait_and_Listen_Normal_Mode = WAIT_n_LISTEN_TM_time*1e3*32 + 15; //add another 10ms to ensure switching
	}
	else
	{
		gDly_Wait_and_Listen_Test_Mode		= 300;	//Test   Mode delay for "Wait and Listen" 2.5ms (250 x 10us)
		gDly_Wait_and_Listen_Normal_Mode	= 90;	//Normal Mode delay for "Wait and Listen" 90 ms
	}

	DEBUG=0;
	if(DEBUG==1 && gDEBUG)
	{
		printf("\nOVT function: TestMode OT power-up.  SN=%i\n", SERIAL_NUM);
		printf("UV@0V(OVT_ON) => \tperiod = %.2f us\n", tmeas*1e6);
	}

	// With Vpin low, OT is 60C.  At room temp(25C), expect device to be switching. //
	if (tmeas > 0.1e-9)	
		OVT_ON = 1; // Switching //
	else 
		OVT_ON = -99; // Not switching //


	// Raise Vpin to change OT to 19C.  At room temp(25C), expect device to stop switching. //
	ddd_7->ddd_run_pattern(High_pat_start,High_pat_stop);
	wait.delay_10_us(20);
	if(g_TurretCB)
	{
		wait.delay_10_us(100);
	}
	tmu_6->arm();						
	wait.delay_10_us(20);					
	tmeas = tmu_6->read(1e-3);
	if(DEBUG==1 && gDEBUG)
	{
		printf("UV@6V(OVT_OFF) => \tperiod = %.2f us\n", tmeas*1e6);
	}
	if (tmeas < 0.1e-9)
		OVT_OFF = 1; // Not switching //
	else 
		OVT_OFF = -99; // Switching //




	// Power down
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0	
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, 	RANGE_10_V);	// OVI_1_1
	VPIN_ovi->connect(VPIN_ch);								// OVI_1_1
 	tmu_6->open_relay(TMU_HIZ_DUT1);	// Disconnect TMU HIZ from Drain 
	Open_relay(K3);
	Open_relay(K12);					// DDD7_1	to Vpin(UV)	pin
	REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_2_V);	// OVI_1_2	
	delay(1);



	//Datalog
	PiDatalog(func, A_OVT_OFF,	OVT_OFF,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_OVT_ON,	OVT_ON,		set_fail_bin,	POWER_UNIT);	

	DEBUG=0;
	if(gDEBUG==1)
	printf("Function OVT Done\n");

	
}
