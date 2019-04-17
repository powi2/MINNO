//==============================================================================
// SR_post_S.cpp (User function)
// 
//    void SR_post_S_user_init(test_function& func)
//    void SR_post_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "SR_post_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void SR_post_S_user_init(test_function& func)
{
	SR_post_S_params *ours;
    ours = (SR_post_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void SR_post_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    SR_post_S_params *ours;
    ours = (SR_post_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "SR_post_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_SR_post_S,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	int		i;
	float 	SRth_post_S = -999.0;

	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();

	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
	Secondary_Vout_Clock_to_Testmode(gProgReadTestMode1_FB_S);

	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE, RANGE_10_V);
	SR_dvi2k->close_relay(CONN_SENSE1);

	REQ_ovi->set_voltage(REQ_ch, gREQ_2V, VOLT_5_RANGE);
	wait.delay_10_us(10);

	//FW set to -0.3V/1mA to be the condition similar to FW in Sync at Low
	FW_dvi->set_current(FW_ch, 1e-3, RANGE_300_MA);

	for (i = 0; i < 3; i++)
	{
		FW_dvi->set_voltage(FW_ch, -1.0, VOLT_10_RANGE);
		wait.delay_10_us(10);
		FW_dvi->set_voltage(FW_ch, 5.0, VOLT_10_RANGE);
		wait.delay_10_us(10);
	}
	REQ_ovi->set_voltage(REQ_ch, 1.0, VOLT_5_RANGE);
	FW_dvi->set_voltage(FW_ch, -0.5, VOLT_10_RANGE);
	
	//Ramp up FW so SR will toggle from High to Low
	SRth_post_S = 999.0;
	search_SR_th_TM1(&SRth_post_S);
	
	Power_Down_Secondary();
	
	// Datalog
	PiDatalog(func, A_SR_post_S,	SRth_post_S,	set_fail_bin,	POWER_MILLI);	

	if(gDEBUG)
	printf("Function SR_post_S Done\n");
}
