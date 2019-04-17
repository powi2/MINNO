//==============================================================================
// REQ_post_S.cpp (User function)
// 
//    void REQ_post_S_user_init(test_function& func)
//    void REQ_post_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "REQ_post_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void REQ_post_S_user_init(test_function& func)
{
	REQ_post_S_params *ours;
    ours = (REQ_post_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void REQ_post_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    REQ_post_S_params *ours;
    ours = (REQ_post_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "REQ_post_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_REQ_post,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	float	REQqtrVref_M_post_S		= -999.0;
	float	REQqtrVref_P_post_S		= -999.0;
	float	REQqtrVref_HYS_post_S	= -999.0;
	float	REQhalfVref_M_post_S	= -999.0;
	float	REQhalfVref_P_post_S	= -999.0;
	float	REQhalfVref_HYS_post_S	= -999.0;
	float	REQ_Vref_M_post_S		= -999.0;
	float	REQ_Vref_P_post_S		= -999.0;
	float	REQ_Vref_HYS_post_S		= -999.0;
	float	REQ_2Vref_M_post_S		= -999.0;
	float	REQ_2Vref_P_post_S		= -999.0;
	float	REQ_2Vref_HYS_post_S	= -999.0;

	Power_Down_Primary();
	Power_Down_Secondary();
	Disconnect_InvSyn_IM();

	Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
	Secondary_Vout_Clock_to_Testmode(gProgReadTestMode19_S);

	Open_relay(K21);	// Disconnect FW from DDD7-3
	// SR disconnected in Powerup, need to connect sense to act as DVM
	SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE, VOLT_5_RANGE);
	SR_dvi2k->close_relay(CONN_SENSE1);
	wait.delay_10_us(50);

	// FW set to 5V/1mA
	FW_dvi->set_current(FW_ch, 1e-3, RANGE_30_MA);
	FW_dvi->set_voltage(FW_ch, gVshunt_BPS+0.2, VOLT_10_RANGE);
	delay(1);	// needed 1ms here 
	
	// Ramp up REQ so SR will toggle from Low to High
	search_REQ_Vref_th(0.29, 0.0001, &REQqtrVref_M_post_S, &REQqtrVref_P_post_S);	//search_REQ_Vref_th(float V_start, float V_step, float *REQ_Vref_M, float *REQ_Vref_P)
	REQqtrVref_HYS_post_S = REQqtrVref_P_post_S - REQqtrVref_M_post_S;

	Close_relay(K27);
	VO_dvi->open_relay(CONN_SENSE0);
	VO_dvi->open_relay(CONN_FORCE0);
	delay(5);

	DDD_Clock_Vout_Antifuse(2);		//gProgReadTestMode20_S	
	delay(1);
	search_REQ_Vref_th(0.60, 0.0001, &REQhalfVref_M_post_S, &REQhalfVref_P_post_S);
	REQhalfVref_HYS_post_S = REQhalfVref_P_post_S - REQhalfVref_M_post_S;

	DDD_Clock_Vout_Antifuse(2);		//gProgReadTestMode21_S	
	delay(1);
	search_REQ_Vref_th(1.23, 0.0001, &REQ_Vref_M_post_S, &REQ_Vref_P_post_S);
	REQ_Vref_HYS_post_S = REQ_Vref_P_post_S - REQ_Vref_M_post_S;

	DDD_Clock_Vout_Antifuse(2);		//gProgReadTestMode22_S	
	delay(1);
	search_REQ_Vref_th(2.50, 0.0001, &REQ_2Vref_M_post_S, &REQ_2Vref_P_post_S);
	REQ_2Vref_HYS_post_S = REQ_2Vref_P_post_S - REQ_2Vref_M_post_S;

	Power_Down_Secondary();
	
	// Datalog
	PiDatalog(func, A_REQqtrVref_M_post_S,		REQqtrVref_M_post_S,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQqtrVref_P_post_S,		REQqtrVref_P_post_S,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQqtrVref_HYS_post_S,	REQqtrVref_HYS_post_S,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQhalfVref_M_post_S,		REQhalfVref_M_post_S,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQhalfVref_P_post_S,		REQhalfVref_P_post_S,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQhalfVref_HYS_post_S,	REQhalfVref_HYS_post_S,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_Vref_M_post_S,		REQ_Vref_M_post_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_Vref_P_post_S,		REQ_Vref_P_post_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_Vref_HYS_post_S,		REQ_Vref_HYS_post_S,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_2Vref_M_post_S,		REQ_2Vref_M_post_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_2Vref_P_post_S,		REQ_2Vref_P_post_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_2Vref_HYS_post_S,		REQ_2Vref_HYS_post_S,	set_fail_bin,	POWER_UNIT);	

	if (gDEBUG)
	printf("Function REQ_post_S Done\n");
}
