//==============================================================================
// SR_Pre_S.cpp (User function)
// 
//    void SR_Pre_S_user_init(test_function& func)
//    void SR_Pre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "SR_Pre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void SR_Pre_S_user_init(test_function& func)
{
	SR_Pre_S_params *ours;
    ours = (SR_Pre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void SR_Pre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    SR_Pre_S_params *ours;
    ours = (SR_Pre_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "SR_Pre_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_SR_Pre,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_GRR == 0 && (OPCODE != 4200 || TRIM_ENABLE == 0))
		return;

	int		i;
	int		TM = 11;
	float 	SRth_pt_S = DEFAULT_VALUE;

	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();

	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);

	if (TM == 11)
	{
		Secondary_Vout_Clock_to_Testmode(gProgReadTestMode11_S);

		Open_relay(K26);	//Disconnect SR from DDD-7-5
		SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE, VOLT_5_RANGE);
		SR_dvi2k->close_relay(CONN_SENSE1);
		wait.delay_10_us(50);

		//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
		FW_dvi->set_current(FW_ch, 1e-3, RANGE_30_MA);		// Float FW pin for SR:Threshold test
		FW_dvi->set_voltage(FW_ch, -1, VOLT_10_RANGE);		// Same voltage as FW in Sync
		delay(1); //needed 1ms here 

		search_SR_th(&SRth_pt_S);
	}

	if (TM == 1)
	{
		Secondary_Vout_Clock_to_Testmode(gProgReadTestMode1_FB_S);

		SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, RANGE_10_V);
		SR_dvi2k->close_relay(CONN_SENSE1);

		REQ_ovi->set_voltage(REQ_ch, gREQ_2V, VOLT_5_RANGE);
		wait.delay_10_us(10);

		//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
		FW_dvi->set_current(FW_ch, 1e-3, RANGE_300_MA);

		// Three FW pulses
		for (i = 0; i < 3; i++)
		{
			FW_dvi->set_voltage(FW_ch, -1.0, VOLT_10_RANGE);
			wait.delay_10_us(10);
			FW_dvi->set_voltage(FW_ch, 5.0, VOLT_10_RANGE);
			wait.delay_10_us(10);
		}
		REQ_ovi->set_voltage(REQ_ch, 1.0, VOLT_5_RANGE);
		FW_dvi->set_voltage(FW_ch, -0.5, VOLT_10_RANGE);
		
		//Ramp up FW so SR will toggle
		search_SR_th_TM1(&SRth_pt_S);
	}

	Power_Down_Secondary();

	// Datalog
	PiDatalog(func, A_SRth_pt_S,	SRth_pt_S,	set_fail_bin,	POWER_MILLI);	

	gSRth_pt_S = SRth_pt_S;

	if(gDEBUG)
	printf("Function SR_Pre_S Done\n");
}
