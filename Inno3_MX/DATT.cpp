//==============================================================================
// DATT.cpp (User function)
// 
//    void DATT_user_init(test_function& func)
//    void DATT(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "DATT.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void DATT_user_init(test_function& func)
{
	DATT_params *ours;
    ours = (DATT_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void DATT(test_function& func)
{
    // The two lines below must be the first two in the function.
    DATT_params *ours;
    ours = (DATT_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "DATT";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_DATT,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (OPCODE==4300 ||OPCODE==4500)	// Disable DATT for temperature
		return;

	float DATT_VD_BEF=0, DATT_VD_AFT=0, DATT_DIFF=0, DATT_NORM=0, DATT_POWER=0;
	float DATT_VD_AFT_start=0, vDelta=0;
	float Norm_inter=0.0, Datt_slope=0.0;
	float	datt_test_norm=0,
			datt_test_b15=0,
			datt_test_fail=0,
			bin15_lim=0,
			Norm_lim=0,
			PV3_Charge=0;

	float	Drain_current=0.0, iD_ESD_DVI=0.0, iD_ESD_PVI=0.0;
	int		Pulse_time;
	int		lcnt, i;	

	float	pvi_vmeas=0.0, Time_diff=0.0, Heating_Time=0.0, After_Heating_Time=0.0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//////////

//NOTE: Do Not use OVI for the Vd_BEF and Vd_AFT measurement. 
//		OVI current overshoots which cause Vd_AFT to be more negative than Vd_BEF.
//      Hence, Vd_DIFF will always come out to be positive when using OVI for meas. 
//e.g.  OVI on BPP (-1V, 1mA)   Vd_BPP = -5.138V
//		OVI on BPP (-1V, 1.5mA) Vd_BPP = -5.344V

	Pulse_time		= DATT_pulse_time;
	Drain_current	= DATT_drain_current;

	//Pulse_time		= 100;
	//Drain_current	= 1.8;

	Close_relay(K11); // Connect BPP to DVI //
	Close_relay(K2); // Disconnect Drain from DVI_11_0
	Close_relay(K3); // Disconnect Drain from DVI_11_0

	//delay(2);

	pv3_4->normal_comp();
	pv3_4->set_voltage(0, RANGE_3_V);
	pv3_4->set_current(0);
	pv3_4->set_meas_mode(PV3_CHARGE_S);			// Monitor storage cap DEBUG_MODEge_mode
	pv3_4->drive_off();
	pv3_4->charge_on();							// Requires a 15ms wait
	PV3_Charge = pv3_4->measure();				// What is the charge now?

	lcnt = 0;
	while ( (PV3_Charge < 63.0)
		&&  (lcnt < 2000) )	
	{
		delay(1);
		lcnt++;
		PV3_Charge = pv3_4->measure();
	}

	bin15_lim=-0.5e-3;						// Minimum DATT_DIFF for all


//** DATT_VD_BEF
	//D_dvi->set_voltage(D_ch, -2.0, 			VOLT_2_RANGE);	// DVI_11_0
	//D_dvi->set_current(D_ch, -1e-3,			RANGE_3_MA);
	//D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_VOLTAGE);
	//delay(2);
	//DATT_VD_BEF = D_dvi->measure_average(5);

	BPP_DVI->set_voltage(BPP_ch, -2.0, VOLT_2_RANGE);	
	BPP_DVI->set_current(BPP_ch, -1e-3, RANGE_3_MA);	
	BPP_DVI->set_meas_mode(BPP_ch, DVI_MEASURE_VOLTAGE);
	delay(2);
	DATT_VD_BEF = BPP_DVI->measure_average(5);

	pv3_4->charge_off();
	wait.delay_10_us(1500);		// Get ready to use. Requires a 15ms wait
	//	connect PV3 to drain DATT
	pv3_4->close_switch(PV3_LOW_FORCE_3);
	pv3_4->close_switch(PV3_LOW_SENSE_3);
	pv3_4->close_switch(PV3_HIGH_FORCE_2);
	pv3_4->close_switch(PV3_HIGH_SENSE_2);
	Close_relay(K6);			// Connect PVI to Drain
	delay(2);

	pv3_4->set_meas_mode(PV3_MEASURE_VOLTAGE);
	pv3_4->set_current(Drain_current);			// auto range
	pv3_4->set_voltage(2.0, RANGE_3_V);
	wait.delay_10_us(100);

	DEBUG=0;
	if(DEBUG==1 && gDEBUG)
	{
		printf("\nDATT: ( Heatup Darin current = %.2f A )\n", Drain_current);
		printf("PV3_vfrc \tcnt \tTime(ms) \tDrain_vESD_at_Heat \tvDelta\n");
		starttime = mytimer.GetElapsedTime();
		delay(1);
		stoptime = mytimer.GetElapsedTime();
		pv3_4->drive_on();
		for(i=0; i<18; i++)
		{
			delay(10);
			pvi_vmeas = pv3_4->measure();				// voltage when PV3 is forcing
			delay(1);
			//DATT_VD_AFT = D_dvi->measure_average(5);
			DATT_VD_AFT = BPP_DVI->measure_average(5);
			if(i==0)
			{
				DATT_VD_AFT_start = DATT_VD_AFT;
			}
			stoptime = mytimer.GetElapsedTime();
			Time_diff = stoptime - starttime;
			vDelta = DATT_VD_AFT - DATT_VD_AFT_start;
			printf("%.4f V \t\t%i \t%.2f ms \t%.4f V\t\t%.2f mV\n", pvi_vmeas, i, Time_diff/1e3, DATT_VD_AFT, vDelta*1e3);
		}
		//D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_CURRENT);
		BPP_DVI->set_meas_mode(BPP_ch, DVI_MEASURE_CURRENT);
		pv3_4->set_meas_mode(PV3_MEASURE_CURRENT);
		wait.delay_10_us(10);
		//iD_ESD_DVI = D_dvi->measure_average(5);
		iD_ESD_DVI = BPP_DVI->measure_average(5);
		printf("iD_ESD = %.4f A dvi_meas\n", iD_ESD_DVI);
		iD_ESD_PVI = pv3_4->measure();
		printf("iD_ESD = %.4f A pvi_meas\n", iD_ESD_PVI);
		//D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_VOLTAGE);
		BPP_DVI->set_meas_mode(BPP_ch, DVI_MEASURE_VOLTAGE);
		pv3_4->set_meas_mode(PV3_MEASURE_VOLTAGE);
	}
	else
	{
		starttime = mytimer.GetElapsedTime();
		pv3_4->drive_on();							// turns on in 50-100us
		delay(Pulse_time / 2);
		pvi_vmeas = pv3_4->measure();				// voltage when PV3 is forcing
		delay(Pulse_time / 2);
	}

	//////////
	pv3_4->set_current(0);						// 590us for both
	pv3_4->set_voltage(0, RANGE_3_V);
	stoptime = mytimer.GetElapsedTime();
	wait.delay_10_us(20);
	Heating_Time = stoptime - starttime;
	//////////

	//	disconnect PV3 from drain DATT
	pv3_4->open_switch(PV3_LOW_FORCE_3);		// 240us for all 4
	pv3_4->open_switch(PV3_LOW_SENSE_3);
	pv3_4->open_switch(PV3_HIGH_FORCE_2);
	pv3_4->open_switch(PV3_HIGH_SENSE_2);
	//////////
	wait.delay_10_us(40);						// 1.42ms from turn off
	stoptime = mytimer.GetElapsedTime();

	//////////
	//DATT_VD_AFT = D_dvi->measure_average(5);
	DATT_VD_AFT = BPP_DVI->measure_average(5);
	//D_dvi->set_voltage(D_ch, 0.0, 		VOLT_2_RANGE);	// OVI_1_0
	BPP_DVI->set_voltage(BPP_ch, 0.0, VOLT_2_RANGE);	
	After_Heating_Time = stoptime - starttime - Heating_Time;

	if(DEBUG==1 && gDEBUG)
	{
		printf("Drain_vESD before heat = %.4f V without connecting PV3\n", DATT_VD_BEF);
		printf("Drain_vESD after_ heat = %.4f V without connecting PV3 after Heating_Time\n", DATT_VD_AFT);
		printf("Heating time = %.2f ms, After_Heating_Time = %.2f ms\n", Heating_Time/1e3, After_Heating_Time/1e3);
	}

	Open_relay(K6);			// PVI to Drain
	Open_relay(K11);
	Open_relay(K2);			// Drain to DVI_11_0
	Open_relay(K3);
	delay(1);
	DATT_DIFF = DATT_VD_BEF - DATT_VD_AFT;

	if (Norm_x_lim != Norm_n_lim)
		Norm_lim = (Datt_slope * DATT_VD_BEF) + Norm_inter; // has slope
	else
		Norm_lim = Norm_n_lim;

	if (DATT_DIFF > bin15_lim)	// > -0.5mV
		Norm_lim = bin15_lim;
	else
	if (DATT_DIFF < Norm_n_lim)	// > fixed min limit
	{
		datt_test_fail = 1;
		Norm_lim = Norm_n_lim;
	}
	else
	if ( (DATT_DIFF < Norm_x_lim)	// on the slope between max and min
	  && (DATT_DIFF > Norm_n_lim)
	  && (DATT_DIFF < Norm_lim))
	{
		if(Norm_x_lim < Norm_lim) Norm_lim = Norm_x_lim;
		if(Norm_n_lim > Norm_lim) Norm_lim = Norm_n_lim;
		datt_test_fail = 1;
	}	

	datt_test_norm	 = Norm_lim;
	datt_test_b15	 = bin15_lim;

	DATT_POWER		 = pvi_vmeas* Drain_current * Pulse_time *1e-3;	//[Ws]
	DATT_NORM		 = DATT_DIFF / (DATT_POWER+1e-23);

	pv3_4->drive_off();
	delay(1);		
	pv3_4->charge_on();			
	//Datalog
	PiDatalog(func, A_DATT_VD_BEF,		DATT_VD_BEF,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_DATT_VD_AFT,		DATT_VD_AFT,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_DATT_DIFF,		DATT_DIFF,		set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_DATT_NORM,		DATT_NORM,		set_fail_bin,	POWER_MILLI);	
	PiDatalog(func, A_DATT_POWER,		DATT_POWER,		set_fail_bin,	POWER_UNIT);

	if(gDEBUG)
	printf("Function DATT Done\n");

}
