//==============================================================================
// REQ_Pre_S.cpp (User function)
// 
//    void REQ_Pre_S_user_init(test_function& func)
//    void REQ_Pre_S(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "REQ_Pre_S.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void REQ_Pre_S_user_init(test_function& func)
{
	REQ_Pre_S_params *ours;
    ours = (REQ_Pre_S_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void REQ_Pre_S(test_function& func)
{
    // The two lines below must be the first two in the function.
    REQ_Pre_S_params *ours;
    ours = (REQ_Pre_S_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "REQ_Pre_S";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_REQ_Pre,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	// Skip Test if AbortTest set 
	if (AbortTest)
		return;

	if (g_GRR == 0 && (OPCODE != 4200 || TRIM_ENABLE == 0))
		return;

	float	REQqtrVref_M_pt_S		= -999.0;
	float	REQqtrVref_P_pt_S		= -999.0;
	float	REQqtrVref_HYS_pt_S		= -999.0;
	float	REQhalfVref_M_pt_S		= -999.0;
	float	REQhalfVref_P_pt_S		= -999.0;
	float	REQhalfVref_HYS_pt_S	= -999.0;
	float	REQ_Vref_M_pt_S			= -999.0;
	float	REQ_Vref_P_pt_S			= -999.0;
	float	REQ_Vref_HYS_pt_S		= -999.0;
	float	REQ_2Vref_M_pt_S		= -999.0;
	float	REQ_2Vref_P_pt_S		= -999.0;
	float	REQ_2Vref_HYS_pt_S		= -999.0;

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
	search_REQ_Vref_th(0.29, 0.0001, &REQqtrVref_M_pt_S, &REQqtrVref_P_pt_S);	//search_REQ_Vref_th(float V_start, float V_step, float *REQ_Vref_M, float *REQ_Vref_P)
	REQqtrVref_HYS_pt_S = REQqtrVref_P_pt_S - REQqtrVref_M_pt_S;

	Close_relay(K27);
	VO_dvi->open_relay(CONN_SENSE0);
	VO_dvi->open_relay(CONN_FORCE0);
	delay(5);

	DDD_Clock_Vout_Antifuse(2);		//gProgReadTestMode20_S	
	delay(1);
	search_REQ_Vref_th(0.60, 0.0001, &REQhalfVref_M_pt_S, &REQhalfVref_P_pt_S);
	REQhalfVref_HYS_pt_S = REQhalfVref_P_pt_S - REQhalfVref_M_pt_S;

	DDD_Clock_Vout_Antifuse(2);		//gProgReadTestMode21_S	
	delay(1);
	search_REQ_Vref_th(1.23, 0.0001, &REQ_Vref_M_pt_S, &REQ_Vref_P_pt_S);
	REQ_Vref_HYS_pt_S = REQ_Vref_P_pt_S - REQ_Vref_M_pt_S;

	DDD_Clock_Vout_Antifuse(2);		//gProgReadTestMode22_S	
	delay(1);
	search_REQ_Vref_th(2.50, 0.0001, &REQ_2Vref_M_pt_S, &REQ_2Vref_P_pt_S);
	REQ_2Vref_HYS_pt_S = REQ_2Vref_P_pt_S - REQ_2Vref_M_pt_S;

	Power_Down_Secondary();
	
	// Datalog
	PiDatalog(func, A_REQqtrVref_M_pt_S,	REQqtrVref_M_pt_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQqtrVref_P_pt_S,	REQqtrVref_P_pt_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQqtrVref_HYS_pt_S,	REQqtrVref_HYS_pt_S,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQhalfVref_M_pt_S,	REQhalfVref_M_pt_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQhalfVref_P_pt_S,	REQhalfVref_P_pt_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQhalfVref_HYS_pt_S,	REQhalfVref_HYS_pt_S,	set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_Vref_M_pt_S,		REQ_Vref_M_pt_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_Vref_P_pt_S,		REQ_Vref_P_pt_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_Vref_HYS_pt_S,	REQ_Vref_HYS_pt_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_2Vref_M_pt_S,		REQ_2Vref_M_pt_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_2Vref_P_pt_S,		REQ_2Vref_P_pt_S,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_REQ_2Vref_HYS_pt_S,	REQ_2Vref_HYS_pt_S,		set_fail_bin,	POWER_UNIT);	

	gREQ_Vref_pt_S = REQ_Vref_P_pt_S;

	if (gDEBUG)
	printf("Function REQ_Pre_S Done\n");

	//if (gCHAR_FLOW)
	if(0)
	{
#define CODE_SIZE 64
		long	n;
		int		i;
		int		r_AF[100] = {0};
		float	REQqtrVref_M[CODE_SIZE]		= {-999.0};
		float	REQqtrVref_P[CODE_SIZE]		= {-999.0};
		float	REQqtrVref_Hys[CODE_SIZE]	= {-999.0};
		float	REQhalfVref_M[CODE_SIZE]	= {-999.0};
		float	REQhalfVref_P[CODE_SIZE]	= {-999.0};
		float	REQhalfVref_Hys[CODE_SIZE]	= {-999.0};
		float	REQ_Vref_M[CODE_SIZE]		= {-999.0};
		float	REQ_Vref_P[CODE_SIZE]		= {-999.0};
		float	REQ_Vref_Hys[CODE_SIZE]		= {-999.0};
		float	REQ_2Vref_M[CODE_SIZE]		= {-999.0};
		float	REQ_2Vref_P[CODE_SIZE]		= {-999.0};
		float	REQ_2Vref_Hys[CODE_SIZE]	= {-999.0};

		Power_Down_Primary();
		Power_Down_Secondary();
		Disconnect_InvSyn_IM();

		for (n = 0; n < CODE_SIZE; n++)
		{
			FillMemory(&r_AF, sizeof(r_AF), 0);
			printf("n = %d\n", n);

			// MINNO_S feature trim code
			r_AF[11] = 1;
			//r_AF[12] = 0;
			r_AF[13] = 1;
			//r_AF[14] = 0;
			r_AF[15] = 1;
			r_AF[16] = 1;
			r_AF[38] = 1;
			//r_AF[39] = 0;
			//r_AF[40] = 0;
			//r_AF[41] = 0;

			// REQ_Vref trim bits
			r_AF[32] = (n & 1);
			r_AF[33] = (n & 2) >> 1;
			r_AF[34] = (n & 4) >> 2;
			r_AF[35] = (n & 8) >> 3;
			r_AF[36] = (n & 16) >> 4;
			r_AF[37] = (n & 32) >> 5;

			Powerup_Secondary_in_Testmode(gProgSim, 0, 0);
			VO_dvi->set_current(VO_ch, 200e-3, RANGE_300_MA);	// increase Vout current limit to enable AF register programming
			wait.delay_10_us(30);

			for (i = 52; i >= 1; i--)
			{
				REQ_ovi->set_voltage(REQ_ch, 5.0*r_AF[i],	VOLT_5_RANGE);	// OVI_1_2
				wait.delay_10_us(10);
				//Vout to clock to AF link
				VO_dvi->set_voltage(VO_ch, 0.0,		VOLT_5_RANGE);	// DVI_9_0
				wait.delay_10_us(15);
				VO_dvi->set_voltage(VO_ch, 5.0,		VOLT_5_RANGE);	// DVI_9_0
				wait.delay_10_us(10);
				REQ_ovi->set_voltage(REQ_ch, 0.0,	VOLT_5_RANGE);	// OVI_1_2
				wait.delay_10_us(10);
			}
			VO_dvi->set_voltage(VO_ch, 0.0,		VOLT_5_RANGE);	// DVI_9_0
			wait.delay_10_us(10);

			//7. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
			FW_dvi->set_voltage(FW_ch, -0.3,	VOLT_50_RANGE);	// DVI_11_1
			wait.delay_10_us(50);
			FW_dvi->set_voltage(FW_ch, 0.0,		VOLT_50_RANGE);	// DVI_11_1
			delay(1);

			//8. Clock VOUT to TestMode#
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
			search_REQ_Vref_th(0.29, 0.0001, &REQqtrVref_M_pt_S, &REQqtrVref_P_pt_S);	//search_REQ_Vref_th(float V_start, float V_step, float *REQ_Vref_M, float *REQ_Vref_P)
			REQqtrVref_HYS_pt_S = REQqtrVref_P_pt_S - REQqtrVref_M_pt_S;

			Close_relay(K27);
			VO_dvi->open_relay(CONN_SENSE0);
			VO_dvi->open_relay(CONN_FORCE0);
			delay(5);

			DDD_Clock_Vout_Antifuse(2);		//gProgReadTestMode20_S	
			delay(1);
			search_REQ_Vref_th(0.60, 0.0001, &REQhalfVref_M_pt_S, &REQhalfVref_P_pt_S);
			REQhalfVref_HYS_pt_S = REQhalfVref_P_pt_S - REQhalfVref_M_pt_S;

			DDD_Clock_Vout_Antifuse(2);		//gProgReadTestMode21_S	
			delay(1);
			search_REQ_Vref_th(1.23, 0.0001, &REQ_Vref_M_pt_S, &REQ_Vref_P_pt_S);
			REQ_Vref_HYS_pt_S = REQ_Vref_P_pt_S - REQ_Vref_M_pt_S;

			DDD_Clock_Vout_Antifuse(2);		//gProgReadTestMode22_S	
			delay(1);
			search_REQ_Vref_th(2.50, 0.0001, &REQ_2Vref_M_pt_S, &REQ_2Vref_P_pt_S);
			REQ_2Vref_HYS_pt_S = REQ_2Vref_P_pt_S - REQ_2Vref_M_pt_S;

			REQqtrVref_M[n]		= REQqtrVref_M_pt_S;
			REQqtrVref_P[n]		= REQqtrVref_P_pt_S;
			REQqtrVref_Hys[n]	= REQqtrVref_HYS_pt_S;
			REQhalfVref_M[n]	= REQhalfVref_M_pt_S;
			REQhalfVref_P[n]	= REQhalfVref_P_pt_S;
			REQhalfVref_Hys[n]	= REQhalfVref_HYS_pt_S;
			REQ_Vref_M[n]		= REQ_Vref_M_pt_S;
			REQ_Vref_P[n]		= REQ_Vref_P_pt_S;
			REQ_Vref_Hys[n]		= REQ_Vref_HYS_pt_S;
			REQ_2Vref_M[n]		= REQ_2Vref_M_pt_S;
			REQ_2Vref_P[n]		= REQ_2Vref_P_pt_S;
			REQ_2Vref_Hys[n]	= REQ_2Vref_HYS_pt_S;

			Power_Down_Secondary();
		}

		// Write to debug file
		time_t rawtime;
		struct tm * timeinfo;
		char timestamp[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timestamp, 80, "%y%m%d%H%M%S", timeinfo);

		char file_name_Id[200] ="e:\\dl4\\VREF_";
		strcat (file_name_Id, timestamp);
		strcat (file_name_Id, ".csv");
		FILE * fpr = fopen(file_name_Id, "w");
		if (! fpr) return;
		
		fprintf(fpr, "Serial number,%d\n", SERIAL_NUM);
		fprintf(fpr, "n,REQqtrVref_M(V),REQqtrVref_P(V),REQqtrVref_Hys(V),REQhalfVref_M(V),REQhalfVref_P(V),REQhalfVref_Hys(V),REQ_Vref_M(V),REQ_Vref_P(V),REQ_Vref_Hys(V),REQ_2Vref_M(V),REQ_2Vref_P(V),REQ_2Vref_Hys(V)\n");

		for (n = 0; n < CODE_SIZE; n++)
		{
				fprintf(fpr, "%d,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f,%8.4f\n", n, REQqtrVref_M[n],
																												REQqtrVref_P[n],
																												REQqtrVref_Hys[n],
																												REQhalfVref_M[n],
																												REQhalfVref_P[n],
																												REQhalfVref_Hys[n],
																												REQ_Vref_M[n],
																												REQ_Vref_P[n],
																												REQ_Vref_Hys[n],
																												REQ_2Vref_M[n],
																												REQ_2Vref_P[n],
																												REQ_2Vref_Hys[n]);
		}
		fprintf(fpr,"\n" );

		fclose(fpr);
		delay(10);
	}
}
