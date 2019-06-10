//==============================================================================
// ILIM_Pre.cpp (User function)
// 
//    void ILIM_Pre_user_init(test_function& func)
//    void ILIM_Pre(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "ILIM_Pre.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void ILIM_Pre_user_init(test_function& func)
{
	ILIM_Pre_params *ours;
    ours = (ILIM_Pre_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void ILIM_Pre(test_function& func)
{
    // The two lines below must be the first two in the function.
    ILIM_Pre_params *ours;
    ours = (ILIM_Pre_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "ILIM_Pre";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_ILIM_Pre,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_GRR == 0 && (OPCODE != 4200 || TRIM_ENABLE == 0))
		return;

	float	ILIM_Pt_P		 = 0.0,
			ILIM_Pt_didt_P	 = 0.0,
			ILIM_Pt_ton_P	 = 0.0,
			ILIM_I2f_pt_P	 = 0.0;
	float	Dummy_rdson_peak = 0.0,
			Dummy_rdson_spec = 0.0;

	int		cnt		= 0,
			retest	= 3;

	float	InvSync_vREF	 = 0.0;

	if(MOSFET_SIZE == 2)		InvSync_vREF = 1.0;
	if(MOSFET_SIZE == 3)		InvSync_vREF = 1.0;
	if(MOSFET_SIZE == 4)		InvSync_vREF = 1.0;
	if(MOSFET_SIZE == 5)		InvSync_vREF = 1.0;
	if(MOSFET_SIZE == 6)		InvSync_vREF = 1.0;
	if(MOSFET_SIZE == 7)		InvSync_vREF = 1.0;
	if(MOSFET_SIZE == 8)		InvSync_vREF = 1.0;

	//Pulse pulse(PULSE_RISING_EDGE,10e-6);		//external trigger pulse from dvi for debug
	//pulse.do_pulse();

	PV3_Charge_On(RANGE_100_V);	//Prepare PV3 before power-up

	//************************************************************************************************************************
	//************************* ILIM_Pre *************************************************************************************
	//************************************************************************************************************************
	SAMPLE_SIZE = GAGE_POST_32K;
	INNO_Gage_ChanAB_setup(0.07);	// Only do it when SAMPLE_SIZE is diff from previous. Each input control and trig control function takes 4ms. 		

	while (cnt++ < retest && ILIM_Pt_P < 100e-3)
	{
		ILIM_Pt_P		 = 0.0;
		ILIM_Pt_didt_P	 = 0.0;
		ILIM_Pt_ton_P	 = 0.0;
		ILIM_I2f_pt_P	 = 0.0;
		Dummy_rdson_peak = 0.0;
		Dummy_rdson_spec = 0.0;

		Gage_Capture_Ilim(ILIM_NORM, InvSync_vREF);

		// Process data
		WAVE_NAME =  "ILIM_Pre";
		FIND_RDSON_Peak_FLAG = 0;
		//Gage_Find_Ilim(&ILIM_Pt_P, &ILIM_Pt_didt_P, &ILIM_Pt_ton_P, &Dummy_rdson_peak, &Dummy_rdson_spec);
		Gage_Find_Ilim_MINNO(&ILIM_Pt_P, &ILIM_Pt_didt_P, &ILIM_Pt_ton_P, &Dummy_rdson_peak, &Dummy_rdson_spec);

		gILIM_I2f_pt_S = ILIM_Pt_P *ILIM_Pt_P * gFOSC_post_S * 1e-3;	// Pass to global variable
		gILIM_pt_S = ILIM_Pt_P;											// Pass to global variable

		// Power down
		Power_Down_Everything();
		Open_All_Relays();
		delay(4);
		Disconnect_InvSyn_IM();
	}

	// Datalog
	PiDatalog(func, A_ILIM_Pt_P,		ILIM_Pt_P,		set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_ILIM_Pt_didt_P,	ILIM_Pt_didt_P,	set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_ILIM_Pt_ton_P,	ILIM_Pt_ton_P,	set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_ILIM_I2f_pt_P,	gILIM_I2f_pt_S,	set_fail_bin,	POWER_UNIT);

	if(gDEBUG)
	printf("Function ILIM_Pre Done\n");
}
