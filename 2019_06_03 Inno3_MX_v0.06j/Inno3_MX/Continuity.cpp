//==============================================================================
// Continuity.cpp (User function)
// 
//    void Continuity_user_init(test_function& func)
//    void Continuity(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "Continuity.h"
#include "PIserial.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Continuity_user_init(test_function& func)
{
	Continuity_params *ours;
    ours = (Continuity_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Continuity(test_function& func)
{
    // The two lines below must be the first two in the function.
    Continuity_params *ours;
    ours = (Continuity_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "Continuity";

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Continuity,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	float VcontD=0, VcontBPP=0, VcontUV=0, VcontFWC=0, VcontREQ=0, VcontBPS=0, VcontSR=0, VcontVO=0, VcontFW=0, VcontACK=0;
	float VcontD_p=0, VcontBPP_p=0, VcontUV_p=0, VcontFWC_p=0, VcontREQ_p=0, VcontBPS_p=0, VcontSR_p=0, VcontVO_p=0, VcontFW_p=0, VcontACK_p=0;
	float IcontD=0, IcontBPP=0, IcontUV=0, IcontFWC=0, IcontREQ=0, IcontBPS=0, IcontSR=0, IcontVO=0, IcontFW=0, IcontACK=0;
	////float ILL_D=0, ILL_BPP=0, ILL_UV=0, ILL_IS=0, ILL_FB=0, ILL_BPS=0, ILL_SR=0, ILL_VO=0, ILL_FW=0;
	////float ILH_D=0, ILH_BPP=0, ILH_UV=0, ILH_IS=0, ILH_FB=0, ILH_BPS=0, ILH_SR=0, ILH_VO=0, ILH_FW=0;
	float GNDRes_Sec=0, GNDRes_Pri=0;
	float VcontD_1mA=0, VcontBPP_1mA=0, VcontUV_1mA=0, VcontFWC_1mA=0, VcontREQ_1mA=0, VcontBPS_1mA=0, VcontSR_1mA=0, 
		VcontVO_1mA=0, VcontFW_1mA=0, VcontACK_1mA=0;
	float VcontD_Rat=0, VcontBPP_Rat=0, VcontUV_Rat=0, VcontFWC_Rat=0, VcontREQ_Rat=0, VcontBPS_Rat=0, VcontSR_Rat=0, 
		VcontVO_Rat=0, VcontFW_Rat=0, VcontACK_Rat=0;
	float vmeas=0, imeas=0;
	float Icont6mA_IS=0;
	float VcontBPP_cap=0;


/****************************************************************************
 *								Vcont test									*
 ****************************************************************************/
	Power_Down_Everything();
	Open_All_Relays();
	tmu_6->open_relay(TMU_HIZ_DUT1);			
	tmu_6->open_relay(TMU_HIZ_DUT2);			
	tmu_6->open_relay(TMU_HIZ_DUT3);			
	tmu_6->open_relay(TMU_HIZ_DUT4);			
	tmu_6->open_relay(TMU_CHAN_A_DUT1);			
	tmu_6->open_relay(TMU_CHAN_A_DUT2);			
	tmu_6->open_relay(TMU_CHAN_B_DUT1);			
	tmu_6->open_relay(TMU_CHAN_B_DUT2);			
	delay(1);
	//dvi_9->init();
	//dvi_11->init();
	//dvi_13->open_relay(BUS_SENSE1);
	//dvi_13->open_relay(BUS_FORCE1);
	//mux_14->open_relay(MUX_3_BUS3);
	//dvi_11->open_relay(BUS_SENSE1);
	//dvi_11->close_relay(CONN_SENSE1);
	//dvi_11->close_relay(CONN_FORCE1);
	//Open_relay(K8);
	//Open_relay(K19);

	ovi_1->connect(OVI_CHANNEL_0);
	ovi_1->connect(OVI_CHANNEL_1);
	ovi_1->connect(OVI_CHANNEL_2);
	ovi_1->connect(OVI_CHANNEL_3);
	ovi_1->connect(OVI_CHANNEL_4);
	ovi_1->connect(OVI_CHANNEL_5);
	ovi_1->connect(OVI_CHANNEL_6);
	ovi_1->connect(OVI_CHANNEL_7);

	dvi_9->close_relay(CONN_SENSE0);
	dvi_9->close_relay(CONN_FORCE0);
	dvi_9->close_relay(CONN_SENSE1);
	dvi_9->close_relay(CONN_FORCE1);
	dvi_11->close_relay(CONN_SENSE0);
	dvi_11->close_relay(CONN_FORCE0);
	dvi_11->close_relay(CONN_SENSE1);
	dvi_11->close_relay(CONN_FORCE1);
	dvi_13->close_relay(CONN_SENSE0);
	dvi_13->close_relay(CONN_FORCE0);
	dvi_13->close_relay(CONN_SENSE1);
	dvi_13->close_relay(CONN_FORCE1);


	//Connect Relays
	Close_relay(K2);	//Connects Drain to DVI_11_0
	Close_relay(K18);	//Connects FW to DVI_11_1


	// ***** Start Temperature Settle*****//
	if (gTEC_enable == 1)
	{
		REQ_ovi->set_voltage(REQ_ch, -2.0, 		RANGE_2_V);	// OVI_1_2
		REQ_ovi->set_current(REQ_ch, -100e-6,		RANGE_300_UA);
		REQ_ovi->set_meas_mode(REQ_ch,			OVI_MEASURE_VOLTAGE);

		delay(2);
		
		double set_T[] = {25, -25, -15, 0, 125, 100, 75, 50};
		//double set_T[] = {27.1, -29.0, -17.8, -0.9, 139.4, 111.3, 83.3, 55.2};   //adjusted to match oven temperature

		double VREQ_array[16] = {0.0};
		double VREQ_sum;
		double VREQ_ave;
		double VREQ_prev = 999.0;
		BOOL t_settle = false;
		int i = 0;
		int j = 0;
		long timeout = 0;
		int ret;

		if (SERIAL_NUM <= sizeof(set_T)/sizeof(set_T[0]))
		{
			ret = LHC_Set_Temp(set_T[SERIAL_NUM - 1]);
			if (ret == 0) ret = LHC_Enable();
			
			if (ret == 0)
			{
				while ((!t_settle) && (timeout < 30))   // 5 minute timeout
				{
					if (i > 15) i = 0;

					VREQ_array[i++] = REQ_ovi->measure_average(5);
					VREQ_sum = 0.0;
					VREQ_ave = 0.0;
					for (j = 0; j < 16; j++)
					{
						VREQ_sum += VREQ_array[j];
					}
					VREQ_ave = VREQ_sum / 16;

					if (fabs(VREQ_ave - VREQ_prev) < 100e-6) t_settle = true;

					VREQ_prev = VREQ_ave;
					
					for (j = 0; j < 1000; j++)   // a measurement every 10 seconds
					{
						delay(10);
					}

					timeout++;
				}
				timeout = 0;
				while (timeout < 600)   // 1 minute soak
				{
					delay(100);
					timeout++;
				}
			}
		}
		else
		{
			LHC_Disable();
		}
	}
	// ***** End Temperature Settle *****//


	/** 1st Vcont Group: D, BPP, FW, SR, REQ, FWC, ACK **/
	//		UV, VO, BPS to 0V, 20mA
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, 		RANGE_2_V);	// OVI_1_1
	VPIN_ovi->set_current(VPIN_ch, 20.0e-3,		RANGE_30_MA);	

	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_2_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, 20.0e-3,		RANGE_30_MA);	

	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_2_RANGE);	// DVI_9_1
	BPS_dvi->set_current(BPS_ch, 20.0e-3,	RANGE_30_MA);	
	
	//		D, BPP, FW, SR, REQ, FWC, ACK to -2V, -100uA
	D_dvi->set_voltage(D_ch, -2.0, 			VOLT_2_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, -100e-6,		RANGE_300_UA);
	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_VOLTAGE);

	BPP_ovi->set_voltage(BPP_ch, -2.0, 		RANGE_2_V);	// OVI_1_0
	BPP_ovi->set_current(BPP_ch, -0.5e-3,	RANGE_3_MA);			//BPP with 4.7uF
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_VOLTAGE);
	
	// No ESD diode. Expect to read 0V. 
	FWC_dvi2k->set_voltage(FWC_ch, -2.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, -100e-6,	RANGE_200_UA);
	FWC_dvi2k->set_meas_mode(FWC_ch,			DVI_MEASURE_VOLTAGE);

	delay(4);
	VcontD   = D_dvi->measure_average(5);
	VcontBPP = BPP_ovi->measure_average(5);
	VcontFWC  = FWC_dvi2k->measure_average(5);
	
	// JD added 1mA and ratio tests
	D_dvi->set_current(D_ch, -1.0e-3,		RANGE_3_MA);
	BPP_ovi->set_current(BPP_ch, -1.0e-3,	RANGE_3_MA);			//BPP with 4.7uF
	FWC_dvi2k->set_current(FWC_ch, -1.0e-3,	RANGE_2_MA);
	delay(2);

	VcontD_1mA   = D_dvi->measure_average(5);
	VcontBPP_1mA = BPP_ovi->measure_average(5);
	VcontFWC_1mA  = FWC_dvi2k->measure_average(5);

	VcontD_Rat	=	VcontD_1mA  / VcontD;
	VcontBPP_Rat=	VcontBPP_1mA / VcontBPP;
	VcontFWC_Rat	=	VcontFWC_1mA / VcontFWC;

	//	JD Added pos continuity tests
	D_dvi->set_voltage(D_ch, 2.0, 			VOLT_2_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 100e-6,		RANGE_300_UA);
	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_VOLTAGE);

	BPP_ovi->set_voltage(BPP_ch, 2.0, 		RANGE_2_V);	// OVI_1_0
	BPP_ovi->set_current(BPP_ch, 0.5e-3,	RANGE_3_MA);			//BPP with 4.7uF
	//BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_VOLTAGE);
	
	// No ESD diode. Expect to read 0V. 
	FWC_dvi2k->set_voltage(FWC_ch, 2.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 100e-6,	RANGE_200_UA);
	//FWC_dvi2k->set_meas_mode(FWC_ch,			DVI_MEASURE_VOLTAGE);

	delay(4);
	VcontD_p   = D_dvi->measure_average(5);
	VcontBPP_p = BPP_ovi->measure_average(5);
	VcontFWC_p  = FWC_dvi2k->measure_average(5);

	FW_dvi->set_voltage(FW_ch, -2.0, 		VOLT_2_RANGE);	// DVI_11_1
	FW_dvi->set_current(FW_ch, -100e-6,	RANGE_300_UA);
	FW_dvi->set_meas_mode(FW_ch,			DVI_MEASURE_VOLTAGE);

	SR_dvi2k->set_voltage(SR_ch, -2.0, 		VOLT_2_RANGE);	// DVI_21_1
	SR_dvi2k->set_current(SR_ch, -100e-6,	RANGE_200_UA);
	SR_dvi2k->set_meas_mode(SR_ch,			DVI_MEASURE_VOLTAGE);

	REQ_ovi->set_voltage(REQ_ch, -2.0, 		RANGE_2_V);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, -100e-6,		RANGE_300_UA);
	REQ_ovi->set_meas_mode(REQ_ch,			OVI_MEASURE_VOLTAGE);

	ACK_ovi->set_voltage(ACK_ch, -2.0, 		RANGE_2_V);	// OVI_1_5
	ACK_ovi->set_current(ACK_ch, -100e-6,		RANGE_300_UA);
	ACK_ovi->set_meas_mode(ACK_ch,			OVI_MEASURE_VOLTAGE);

	delay(2);
	VcontFW = FW_dvi->measure_average(5);
	VcontSR = SR_dvi2k->measure_average(5);
	VcontREQ = REQ_ovi->measure_average(5);
	VcontACK = ACK_ovi->measure_average(5);

	// JD added 1mA and ratio tests
	FW_dvi->set_current(FW_ch, -1.0e-3,	RANGE_3_MA);
	SR_dvi2k->set_current(SR_ch, -1.0e-3,	RANGE_2_MA);
	REQ_ovi->set_current(REQ_ch, -1.0e-3,		RANGE_3_MA);
	ACK_ovi->set_current(ACK_ch, -1.0e-3,		RANGE_3_MA);

	VcontFW_1mA   = FW_dvi->measure_average(5);
	VcontSR_1mA = SR_dvi2k->measure_average(5);
	VcontREQ_1mA  = REQ_ovi->measure_average(5);
	VcontACK_1mA  = ACK_ovi->measure_average(5);

	VcontFW_Rat	=	VcontFW_1mA  / VcontFW;
	VcontSR_Rat=	VcontSR_1mA / VcontSR;
	VcontREQ_Rat	=	VcontREQ_1mA / VcontREQ;
	VcontACK_Rat	=	VcontACK_1mA / VcontACK;

	FW_dvi->set_voltage(FW_ch, 2.0, 		VOLT_2_RANGE);	// DVI_11_1
	FW_dvi->set_current(FW_ch, 100e-6,	RANGE_300_UA);
	//FW_dvi->set_meas_mode(FW_ch,			DVI_MEASURE_VOLTAGE);

	SR_dvi2k->set_voltage(SR_ch, 2.0, 		VOLT_2_RANGE);	// DVI_21_1
	SR_dvi2k->set_current(SR_ch, 100e-6,	RANGE_200_UA);
	//SR_dvi2k->set_meas_mode(SR_ch,			DVI_MEASURE_VOLTAGE);

	REQ_ovi->set_voltage(REQ_ch, 2.0, 		RANGE_2_V);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, 100e-6,		RANGE_300_UA);
	//REQ_ovi->set_meas_mode(REQ_ch,			OVI_MEASURE_VOLTAGE);

	ACK_ovi->set_voltage(ACK_ch, 2.0, 		RANGE_2_V);	// OVI_1_5
	ACK_ovi->set_current(ACK_ch, 100e-6,		RANGE_300_UA);
	//ACK_ovi->set_meas_mode(ACK_ch,			OVI_MEASURE_VOLTAGE);

	delay(2);
	VcontFW_p = FW_dvi->measure_average(5);
	VcontSR_p = SR_dvi2k->measure_average(5);
	VcontREQ_p = REQ_ovi->measure_average(5);
	VcontACK_p = ACK_ovi->measure_average(5);

	//Power down first group of pins: D, BPP, FW, SR, REQ, FWC
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_2_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 20.0e-3,		RANGE_30_MA);

	BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_2_V);	// OVI_1_0
	BPP_ovi->set_current(BPP_ch, 20.0e-3,	RANGE_30_MA);

	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);

	FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_2_RANGE);	// DVI_11_1
	FW_dvi->set_current(FW_ch, 20.0e-3,		RANGE_30_MA);

	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	SR_dvi2k->set_current(SR_ch, 20.0e-3,	RANGE_20_MA);

	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_2_V);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, 20.0e-3,		RANGE_30_MA);

	ACK_ovi->set_voltage(ACK_ch, 0.0, 		RANGE_2_V);	// OVI_1_2
	ACK_ovi->set_current(ACK_ch, 20.0e-3,		RANGE_30_MA);

	D_dvi->set_current(D_ch, 100e-6,		RANGE_300_UA);
	D_dvi->set_voltage(D_ch, 0.0,			VOLT_2_RANGE); 
	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_CURRENT);
	delay(1);

	// Added ILL and ILH tests	
	//////ILL_D  = FW_dvi->measure_average(15);		// Check current from D dvi  to FW dvi
	//////D_dvi->set_current(D_ch, 3e-3,		RANGE_3_MA);
	//////D_dvi->set_voltage(D_ch, 2.0,			VOLT_5_RANGE); 
	//////delay(5);
	//////ILH_D  = FW_dvi->measure_average(15);		// Check current from D dvi  to FW dvi

	//////BPP_DVI->set_current(BPP_ch, 100e-6,		RANGE_300_UA); 
	//////BPP_DVI->set_voltage(BPP_ch, 0.0,		VOLT_2_RANGE); 
	//////BPP_DVI->set_meas_mode(BPP_ch,			DVI_MEASURE_CURRENT);
	//////delay(1);
	//////ILL_BPP= FW_dvi->measure_average(15);	// Check current from BPP dvi to FW dvi

	//////BPP_DVI->set_current(BPP_ch, 3e-3,		RANGE_3_MA); 
	//////BPP_DVI->set_voltage(BPP_ch, 2.0,		VOLT_2_RANGE); 
	//////delay(4);
	//////ILH_BPP= FW_dvi->measure_average(15);	// Check current from BPP dvi to FW dvi
	//////
	//////FW_dvi->set_current(FW_ch, 100.0e-6,	RANGE_300_UA);
	//////FW_dvi->set_voltage(FW_ch, 0.0,		VOLT_2_RANGE); 
	//////FW_dvi->set_meas_mode(FW_ch,			DVI_MEASURE_CURRENT);
	//////delay(1);
	//////ILL_FW  = FW_dvi->measure_average(15);		// Check current from FW dvi to D dvi

	//////FW_dvi->set_current(FW_ch, 3e-3,	RANGE_3_MA);
	//////FW_dvi->set_voltage(FW_ch, 2.0,		VOLT_2_RANGE); 
	//////delay(1);
	//////ILH_FW  = FW_dvi->measure_average(15);		// Check current from FW dvi to D dvi

	// SR internally shorted to ground
	/*SR_dvi2k->set_current(SR_ch, 100.0e-6,	RANGE_200_UA);
	SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE); 
	SR_dvi2k->set_meas_mode(SR_ch,			DVI_MEASURE_CURRENT);
	delay(1);
	ILL_SR  = SR_dvi2k->measure_average(15);		// Check current from FW dvi to D dvi

	SR_dvi2k->set_current(SR_ch, 3e-3,	RANGE_20_MA);
	SR_dvi2k->set_voltage(SR_ch, 2.0,		VOLT_2_RANGE); 
	delay(1);
	ILH_SR  = SR_dvi2k->measure_average(15);		// Check current from FW dvi to D dvi*/
	
	//////REQ_ovi->set_current(REQ_ch, 100e-6,	RANGE_300_UA); 
	//////REQ_ovi->set_voltage(REQ_ch, 0,	RANGE_2_V); // Use -5V pull down through 2V range on DVI
	//////REQ_ovi->set_meas_mode(REQ_ch,			DVI_MEASURE_CURRENT);
	//////wait.delay_10_us(500);
	//////ILL_FB = REQ_ovi->measure_average(15); // Check current from FB ovi  to UV ovi

	//////REQ_ovi->set_current(REQ_ch, 3e-3,	RANGE_3_MA); 
	//////REQ_ovi->set_voltage(REQ_ch, 2.0,	RANGE_2_V); // Use -5V pull down through 2V range on DVI
	//////wait.delay_10_us(500);
	//////ILH_FB = REQ_ovi->measure_average(15); // Check current from FB ovi  to UV ovi
	//////
	/** 2nd Vcont Group: UV, VO, BPS **/

	//		UV, VO, BPS to -2.0V, -5.0mA
	VPIN_ovi->set_voltage(VPIN_ch, -2.0, 		RANGE_2_V);	// OVI_1_1
	VPIN_ovi->set_current(VPIN_ch, -100e-6,		RANGE_300_UA);
	VPIN_ovi->set_meas_mode(VPIN_ch,			OVI_MEASURE_VOLTAGE);

	VO_dvi->set_voltage(VO_ch, -2.0, 		VOLT_2_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, -100e-6,		RANGE_300_UA);
	VO_dvi->set_meas_mode(VO_ch,			OVI_MEASURE_VOLTAGE);
	delay(2);
	VcontUV = VPIN_ovi->measure_average(5);					// Expect -2V , Test die, UV is not define
	VcontVO = VO_dvi->measure_average(5);

	// JD added 1mA Vcont tests
	VPIN_ovi->set_current(VPIN_ch, -1.0e-3,		RANGE_3_MA);
	VO_dvi->set_current(VO_ch, -1.0e-3,		RANGE_3_MA);
	delay(2);

	VcontUV_1mA = VPIN_ovi->measure_average(5);					// Expect -2V , Test die, UV is not define
	VcontVO_1mA = VO_dvi->measure_average(5);

	BPS_dvi->set_voltage(BPS_ch, -2.0, 		VOLT_2_RANGE);	// DVI_9_1
	BPS_dvi->set_current(BPS_ch, -100e-6,	RANGE_300_UA);
	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_VOLTAGE);
	delay(2);
	VcontBPS = BPS_dvi->measure_average(5);

	// JD added 1mA Vcont tests
	BPS_dvi->set_current(BPS_ch, -1.0e-3,	RANGE_3_MA);
	delay(2);
	VcontBPS_1mA = BPS_dvi->measure_average(5);

	VcontUV_Rat	=	VcontUV_1mA  / VcontUV;
	VcontVO_Rat=	VcontVO_1mA / VcontVO;
	VcontBPS_Rat	=	VcontBPS_1mA / VcontBPS;

	// JD added vcont pos tests
	/*VPIN_ovi->set_voltage(VPIN_ch, 2.0, 		RANGE_2_V);	// OVI_1_1
	VPIN_ovi->set_current(VPIN_ch, 100e-6,		RANGE_300_UA);
	//VPIN_ovi->set_meas_mode(VPIN_ch,			OVI_MEASURE_VOLTAGE);

	VO_dvi->set_voltage(VO_ch, 2.0, 		VOLT_2_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, 100e-6,		RANGE_300_UA);
	//VO_dvi->set_meas_mode(VO_ch,			OVI_MEASURE_VOLTAGE);
	
	delay(2);
	VcontUV_p = VPIN_ovi->measure_average(5);					// Expect -2V , Test die, UV is not define
	VcontVO_p = VO_dvi->measure_average(5);

	BPS_dvi->set_voltage(BPS_ch, 2.0, 		VOLT_2_RANGE);	// DVI_9_1
	BPS_dvi->set_current(BPS_ch, 100e-6,	RANGE_300_UA);
	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_VOLTAGE);
	delay(2);
	VcontBPS_p = BPS_dvi->measure_average(5);*/

	// Power down second group of pins: UV, VO, BPS 
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, 	RANGE_2_V);	// OVI_1_1
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_2_RANGE);	// DVI_9_0
	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_2_RANGE);	// DVI_9_1
	
	//////// Added IIL and IIH tests
	//////VO_dvi->set_current(VO_ch, 100e-6,	RANGE_300_UA);
	//////VO_dvi->set_voltage(VO_ch, 0.0,		VOLT_2_RANGE);  
	//////VO_dvi->set_meas_mode(VO_ch,		DVI_MEASURE_CURRENT);
	//////delay(1);
	//////ILL_VO = VO_dvi->measure_average(15);		// Check current from VO dvi to BPS dvi

	//////VO_dvi->set_current(VO_ch, 3e-3,	RANGE_3_MA);
	//////VO_dvi->set_voltage(VO_ch, 2.0,		VOLT_2_RANGE);  
	//////delay(1);
	//////ILH_VO = VO_dvi->measure_average(15);		// Check current from VO dvi to BPS dvi

	//////SR_dvi2k->set_current(SR_ch, 100.0e-6,	RANGE_200_UA);  // DVI2K
	//////SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);
	//////SR_dvi2k->set_meas_mode(SR_ch,			DVI_MEASURE_CURRENT);
	////////delay(2);
	//////ILL_SR	 = FWC_dvi2k->measure_average(15);	// Check current from SR dvi to IS dvi

	// Short to ground
	//SR_dvi2k->set_current(SR_ch, 2e-3,	RANGE_2_MA);  // DVI2K
	//SR_dvi2k->set_voltage(SR_ch, 2.0,		VOLT_2_RANGE); 
	//delay(10);
	//ILH_SR	 = FWC_dvi2k->measure_average(15);	// Check current from SR dvi to IS dvi
	
	// BPS done in ICH tests
	//BPS_dvi->set_current(BPS_ch, 3.0e-3,	RANGE_3_MA);
	//BPS_dvi->set_voltage(BPS_ch, 2.0,		VOLT_5_RANGE);
	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//delay(1);
	//ILH_BPS = BPS_dvi->measure_average(15);		// Check current from BPS dvi to VO dvi

	//BPS_dvi->set_current(BPS_ch, 300.0e-6,	RANGE_300_UA);
	//BPS_dvi->set_voltage(BPS_ch, 0.0,		VOLT_5_RANGE);
	//delay(7);
	//ILL_BPS = BPS_dvi->measure_average(15);		// Check current from BPS dvi to VO dvi

	//////REQ_ovi->set_current(REQ_ch, 100e-6,	RANGE_300_UA); 
	//////REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_2_V); // Use -5V pull down through 2V range on DVI
	//////REQ_ovi->set_meas_mode(REQ_ch,			DVI_MEASURE_CURRENT);
	//////wait.delay_10_us(30);
	//////ILL_UV = REQ_ovi->measure_average(15);		// Check current from FB ovi  to UV ovi

	//////REQ_ovi->set_voltage(REQ_ch, 2.0,	RANGE_2_V); // Use -5V pull down through 2V range on DVI
	//////wait.delay_10_us(30);
	//////ILH_UV = REQ_ovi->measure_average(15);		// Check current from FB ovi  to UV ovi

/****************************************************************************
 *								Icont test									*
 * Note1: IS pin is connected to GND internally through bondwire			*
 * Note2: Connect CONN_FORCE and CONN_SENSE relay instead of BUS_FORCE and  *
 * BUS_SENSE relay as 3 DVI channel ICONT are test in parallel and BUS2 and *
 * BUS3 are all tied together												*
 ****************************************************************************/

//************** check Icont on DVI Channel 1: FW, BPS, SR pins **********************
	//   FW:  DVI_11_1  D: DVI_11_0
	//	 BPS: DVI_9_1   VO:DVI_9_0
	//	 SR:  DVI_21_1 FWC:DVI_21_0

	//** Setup FW pin Icont test DVI_11_1
	FW_dvi->close_relay(CHANNEL_SHORT);
	// Source current
	FW_dvi->set_voltage(FW_ch, -1.5,		VOLT_2_RANGE);  
	FW_dvi->set_current(FW_ch, -6.0e-3,		RANGE_30_MA);		
	// Sink Current to check Force and Sense connectivity
	D_dvi->set_voltage(D_ch, 0.0,			VOLT_2_RANGE); // Use -5V pull down through 2V range on DVI
	D_dvi->set_current(D_ch, 20e-3,			RANGE_30_MA); 
	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_CURRENT);

	//** Setup BPS pin Icont test DVI_9_1
	BPS_dvi->close_relay(CHANNEL_SHORT);
	// Source current
	BPS_dvi->set_voltage(BPS_ch, -1.5,		VOLT_2_RANGE);  
	BPS_dvi->set_current(BPS_ch, -6.0e-3,	RANGE_30_MA);		
	// Sink Current to check Force and Sense connectivity
	VO_dvi->set_voltage(VO_ch, 0.0,			VOLT_2_RANGE); // Use -5V pull down through 2V range on DVI
	VO_dvi->set_current(VO_ch, 20e-3,		RANGE_30_MA); 
	VO_dvi->set_meas_mode(VO_ch,			DVI_MEASURE_CURRENT);

	if(g_TurretCB)
	{
		delay(3);
		IcontBPS = VO_dvi->measure_average(5);		// Check current from BPS dvi to VO dvi
	}

	//** Setup SR pin Icont test DVI_21_1
	SR_dvi2k->close_relay(CHANNEL_SHORT);
	// Source current
	SR_dvi2k->set_voltage(SR_ch, -1.5,		VOLT_2_RANGE);  
	SR_dvi2k->set_current(SR_ch, -6.0e-3,	RANGE_20_MA);  // DVI2K	
	// Sink Current to check Force and Sense connectivity
	FWC_dvi2k->set_voltage(FWC_ch, 0.0,		VOLT_2_RANGE); // Use -5V pull down through 2V range on DVI
	FWC_dvi2k->set_current(FWC_ch, 20e-3,		RANGE_20_MA); 
	FWC_dvi2k->set_meas_mode(FWC_ch,			DVI_MEASURE_CURRENT);

	delay(2);
	//** Take measurements from the 20mA current channel
	D_dvi->close_relay(BUS_SENSE0);		// Need to close BUS_SENSE and BUS_FORCE to avoid failing the ICont on the wrong pin
	D_dvi->close_relay(BUS_FORCE0);
	delay(1);
	IcontFW  = D_dvi->measure_average(5);		// Check current from FW dvi to D dvi

	D_dvi->open_relay(BUS_SENSE0);
	D_dvi->open_relay(BUS_FORCE0);
	//VO_dvi->close_relay(BUS_SENSE0);
	//VO_dvi->close_relay(BUS_FORCE0);
	if(!g_TurretCB)
	{
		delay(3);
		IcontBPS = VO_dvi->measure_average(5);		// Check current from BPS dvi to VO dvi
	}

	VO_dvi->open_relay(BUS_SENSE0);
	VO_dvi->open_relay(BUS_FORCE0);

	IcontSR	 = FWC_dvi2k->measure_average(5);	// Check current from SR dvi to FWC dvi

	//** Power down FW, BPS, SR pins and open CONN BUS relays, Leave CHANNEL_SHORT relay close
	FW_dvi->set_voltage(FW_ch, 0.0,			VOLT_2_RANGE);  
	FW_dvi->set_current(FW_ch, 20.0e-3,		RANGE_30_MA);		
	BPS_dvi->set_voltage(BPS_ch, 0.0,		VOLT_2_RANGE);  
	BPS_dvi->set_current(BPS_ch, 20.0e-3,	RANGE_30_MA);		
	SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);  
	SR_dvi2k->set_current(SR_ch, 20.0e-3,	RANGE_20_MA);		
	wait.delay_10_us(10);

//************** check Icont on DVI Channel 0 : D, VO, FWC pins **********************
	//   FW:  DVI_11_1  D: DVI_11_0
	//	 BPS: DVI_9_1   VO:DVI_9_0
	//	 SR:  DVI_21_1 FWC:DVI_21_0
	//** Setup FW pin Icont test DVI_11_1

	// CHANNEL SHORT Relays were closed previously

	//** Setup D pin Icont test DVI_11_0
	// FW pin was set up above to 0V, 20mA to sink current from D pin
	FW_dvi->set_meas_mode(FW_ch,				DVI_MEASURE_CURRENT);
	// Source current
	D_dvi->set_voltage(D_ch, -1.5,			VOLT_2_RANGE);  
	D_dvi->set_current(D_ch, -6.0e-3,		RANGE_30_MA);		

	//** Setup VO pin Icont test DVI_9_0
	// BPS pin was set up above to 0V, 20mA to sink current from D pin
	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	// Source current
	VO_dvi->set_voltage(VO_ch, -1.5,		VOLT_2_RANGE);  
	VO_dvi->set_current(VO_ch, -6.0e-3,		RANGE_30_MA);	

	//** Setup VO pin Icont test DVI_9_0
	//SR pin was set up above to 0V, 20mA to sink current from FWC pin
	SR_dvi2k->set_meas_mode(SR_ch,			DVI_MEASURE_CURRENT);
	// Source current
	FWC_dvi2k->set_voltage(FWC_ch, -1.5,		VOLT_2_RANGE);  
	FWC_dvi2k->set_current(FWC_ch, -6.0e-3,	RANGE_20_MA);	
	delay(2);
	//** Take measurements
	//FW_dvi->close_relay(BUS_SENSE1);
	//FW_dvi->close_relay(BUS_FORCE1);
	//delay(1);
	IcontD  = FW_dvi->measure_average(5);		// Check current from D dvi  to FW dvi

	FW_dvi->open_relay(BUS_SENSE1);
	FW_dvi->open_relay(BUS_FORCE1);
	//BPS_dvi->close_relay(BUS_SENSE1);
	//BPS_dvi->close_relay(BUS_FORCE1);
	delay(3);
	IcontVO = BPS_dvi->measure_average(5);		// Check current from VO dvi to BPS dvi

	BPS_dvi->open_relay(BUS_SENSE1);
	BPS_dvi->open_relay(BUS_FORCE1);

	IcontFWC = SR_dvi2k->measure_average(5);		// Check current from FWC dvi to SR dvi

	D_dvi->set_voltage(D_ch, 0,			VOLT_2_RANGE);  
	D_dvi->set_current(D_ch, 100e-6,		RANGE_300_UA);		
	VO_dvi->set_voltage(VO_ch, 0,		VOLT_2_RANGE);  
	VO_dvi->set_current(VO_ch, 100e-6,		RANGE_300_UA);	
	FWC_dvi2k->set_voltage(FWC_ch, 0,		VOLT_2_RANGE);  
	FWC_dvi2k->set_current(FWC_ch, 100e-6,	RANGE_200_UA);	

//************** check BPP Icont with DVI_11_0 **********************
	//FW pin was set up above to 0V, 20mA to sink current from DVI_11_0	BPP_DVI->set_voltage(BPP_ch, 0.0,		VOLT_2_RANGE);  wait.delay_10_us(10);
	Close_relay(K11);
	Close_relay(K3);	delay(2);			// Disconnect Drain from DVI_11_0

	// Source current
	BPP_DVI->set_voltage(BPP_ch, -1.5,		VOLT_2_RANGE);  wait.delay_10_us(10);
	BPP_DVI->set_current(BPP_ch, -6.0e-3,		RANGE_30_MA); 
	FW_dvi->set_meas_mode(FW_ch,			DVI_MEASURE_CURRENT);
	delay(2);

	//** Take measurements
	//FW_dvi->close_relay(BUS_SENSE1);
	//FW_dvi->close_relay(BUS_FORCE1);
	//delay(1);
	IcontBPP= FW_dvi->measure_average(5);	// Check current from BPP dvi to FW dvi

	FW_dvi->open_relay(BUS_SENSE1);
	FW_dvi->open_relay(BUS_FORCE1);

	//** Power down D, VO, FWC pins and open CONN BUS relays
	Open_relay(K11);
	Open_relay(K3);			
	BPP_DVI->set_voltage(BPP_ch, 0.0,		VOLT_2_RANGE);  
	VO_dvi->set_voltage(VO_ch, 0.0,			VOLT_2_RANGE);  
	FWC_dvi2k->set_voltage(FWC_ch, 0.0,		VOLT_2_RANGE);  
	wait.delay_10_us(10);
	
	FW_dvi->open_relay(CHANNEL_SHORT);
	BPS_dvi->open_relay(CHANNEL_SHORT);
	SR_dvi2k->open_relay(CHANNEL_SHORT);

//************** check REQ and UV Icont with OVI **********************
	Close_relay(MUX_1_1);
	Close_relay(MUX_1_2);
	Close_relay(MUX_1_3); // Added for connecting F and S of VPIN_ovi - HQL
	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT);
	delay(2);

	// REQ Source current
	REQ_ovi->set_voltage(REQ_ch, -1.5,		RANGE_2_V); // Use -5V pull down through 2V range on DVI
	REQ_ovi->set_current(REQ_ch, -6.0e-3,		RANGE_30_MA); 
	// Sink Current to check Force and Sense connectivity
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_2_V);  
	VPIN_ovi->set_current(VPIN_ch, 20e-3,	RANGE_30_MA);		
	
	wait.delay_10_us(500);
	IcontREQ = VPIN_ovi->measure_average(5); // Check current from REQ ovi  to UV ovi

	/******************************** Notes for v1.5-2.0 silicon**************************
	/ UV Sense can't be checked on v1.5-2.0 silicon due to lack of ESD diode on UV pin.
	/ As long as both force and sense make connections, IcontUV will still read -6.0mA. 
	/ If only force is broken, this test will failed reading around -0.2mA				*/
	// UV Source current
	Open_relay(MUX_1_3);
	Close_relay(MUX_1_4); // Added for connecting F and S of REQ_ovi - HQL
	wait.delay_10_us(100);
	REQ_ovi->set_meas_mode(REQ_ch, OVI_MEASURE_CURRENT);
	VPIN_ovi->set_voltage(VPIN_ch, -1.5,	RANGE_2_V);  
	VPIN_ovi->set_current(VPIN_ch, -6.0e-3,	RANGE_30_MA);		
	// Sink Current to check Force and Sense connectivity
	REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_2_V); // Use -5V pull down through 2V range on DVI
	REQ_ovi->set_current(REQ_ch, 20e-3,	RANGE_30_MA); 
	
	wait.delay_10_us(500);
	IcontUV = REQ_ovi->measure_average(5);		// Check current from REQ ovi  to UV ovi

	// Power down Icont OVI circuit on UV and REQ
	REQ_ovi->set_voltage(REQ_ch, 0.0,		RANGE_2_V); // Use -5V pull down through 2V range on DVI
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,	RANGE_2_V);  wait.delay_10_us(10);
	Open_relay(MUX_1_1);	
	Open_relay(MUX_1_2);
	Open_relay(MUX_1_4);

/****************************************************************************
 *							Secondary SRC-S Gnd Res check					*
 ****************************************************************************/
	// Connect DVI9_0 to GND through BUS lines
	VO_dvi->close_relay(BUS_SENSE0);
	VO_dvi->open_relay(BUS_FORCE0);
	VO_dvi->open_relay(CONN_FORCE0);
	VO_dvi->open_relay(CONN_SENSE0);
	mux_14->close_relay(MUX_2_BUS2);
	Close_relay(MUX_2_1);	// Connect DVI9_0 BUS_SENSE to GND 
	delay(4);

	VO_dvi->set_meas_mode(VO_ch, DVI_MEASURE_VOLTAGE);
	// Force -2V, 100mA through BPS pin
	BPS_dvi->set_voltage(BPS_ch, -1.5,		VOLT_2_RANGE);  
	BPS_dvi->set_current(BPS_ch, -100.0e-3,	RANGE_300_MA);		
	wait.delay_10_us(50);
	vmeas = VO_dvi->measure_average(25);
	BPS_dvi->set_meas_mode(BPS_ch, DVI_MEASURE_CURRENT); wait.delay_10_us(50);
	imeas = BPS_dvi->measure_average(25);
	GNDRes_Sec = -vmeas/(imeas + 1e-23);
	gGNDRes_Se = GNDRes_Sec;		//Pass it to global variable for CB_adj calculation


	// Power down GNDRes 
	BPS_dvi->set_voltage(BPS_ch, 0.0,		VOLT_2_RANGE);  
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	VO_dvi->open_relay(BUS_FORCE0);
	VO_dvi->open_relay(BUS_SENSE0);

	Open_relay(MUX_2_BUS2);
	Open_relay(MUX_2_1);	// Disconnect DVI9_0 BUS_SENSE from GND 

	// Power down and Open relays
	Open_relay(K2);
	Open_relay(K18);

/****************************************************************************
*                                        Primary SRC-P Gnd Res check                           *
****************************************************************************/
	Open_relay(MUX_BANK_3_4);

	// Connect DVI11_1 to GND through BUS lines
	FW_dvi->close_relay(BUS_SENSE1);
	FW_dvi->open_relay(BUS_FORCE1);
	FW_dvi->open_relay(CONN_FORCE1);
	FW_dvi->open_relay(CONN_SENSE1);
	mux_14->close_relay(MUX_BANK_2_3);
	mux_14->close_relay(MUX_3_BUS3);
	Close_relay(MUX_2_1);   // Connect DVI11_1 BUS_SENSE to GND 
	Close_relay(K11); // Connect DVI11_0 to BPP
	delay(5);

	FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_VOLTAGE);
	// Force -2V, 100mA through BPS pin
	BPP_DVI->set_voltage(BPP_ch, -1.5,        VOLT_2_RANGE);  
	BPP_DVI->set_current(BPP_ch, -100.0e-3,   RANGE_300_MA);          
	wait.delay_10_us(50);
	vmeas = FW_dvi->measure_average(25);
	BPP_DVI->set_meas_mode(BPP_ch, DVI_MEASURE_CURRENT); wait.delay_10_us(50);
	imeas = BPP_DVI->measure_average(25);
	GNDRes_Pri = -vmeas/(imeas + 1e-23);


	// Power down GNDRes 
	BPP_DVI->set_voltage(BPP_ch, 0.0,		VOLT_2_RANGE);  
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	VO_dvi->open_relay(BUS_FORCE0);
	VO_dvi->open_relay(BUS_SENSE0);
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	FW_dvi->open_relay(BUS_SENSE1);
	FW_dvi->close_relay(CONN_FORCE1);
	FW_dvi->close_relay(CONN_SENSE1);

	mux_14->open_relay(MUX_BANK_2_3);
	Open_relay(MUX_3_BUS3);
	Open_relay(MUX_2_1);	// Disconnect DVI9_0 BUS_SENSE from GND 
	Open_relay(K11);
	Close_relay(MUX_BANK_3_4);

	// Power down and Open relays
	Open_relay(K2);
	Open_relay(K8);
	Open_relay(K18);
	Open_relay(K19);


	// VcontBPP_cap.
	// Continuity check for ground connection of BPP pin capacitor.
	// Force 100uA to BPP.  If BPP capacitor ground is NOT connected, BPP voltage will 
	// rise up very quickly.  If BPP capacitor ground is connected properly, the BPP 
	// voltage rises up more slowly.  Datalog BPP voltage, 350usec after 100uA forced to BPP.  //
	wait.delay_10_us(300); // Wait for relays //
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	BPP_ovi->set_current(BPP_ch, 100e-6, RANGE_300_UA); // OVI_1_0 //
	BPP_ovi->set_meas_mode(BPP_ch, OVI_MEASURE_VOLTAGE); // OVI_1_0 //
	wait.delay_10_us(150);
	BPP_ovi->set_voltage(BPP_ch, 5, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(35); // 350usec.  Don't change //
	VcontBPP_cap = BPP_ovi->measure();
	BPP_ovi->set_voltage(BPP_ch, 0.1, RANGE_10_V); // OVI_1_0, prevent undershoot. //
	BPP_ovi->set_current(BPP_ch, 30e-3, RANGE_30_MA); // OVI_1_0 //
	wait.delay_10_us(15);
	BPP_ovi->set_voltage(BPP_ch, 0.0, RANGE_10_V); // OVI_1_0 //
	wait.delay_10_us(20);
	//VcontBPP_capGNG = 1; // Default is pass //
	if (VcontBPP_cap > 0.9) // Fail //
	{
		//g_Error_Flag = -225;
		VcontBPP = -99;		// Using VcontBPP to datalog to indicate the Cap on BPP is not connected properly.
	}
	

// Datalog 
	
	PiDatalog(func, A_VcontD,	VcontD, set_fail_bin,		POWER_UNIT);
	//PiDatalog(func, A_VcontD_p,	VcontD_p, set_fail_bin,		POWER_UNIT);
	PiDatalog(func, A_VcontD_1mA,	VcontD_1mA, set_fail_bin,		POWER_UNIT);
	PiDatalog(func, A_VcontD_Rat,	VcontD_Rat, set_fail_bin,		POWER_UNIT);
	PiDatalog(func, A_IcontD,	IcontD, set_fail_bin,		POWER_MILLI);	
	//////PiDatalog(func, A_ILL_D,	ILL_D, set_fail_bin,		POWER_MICRO);
	//////PiDatalog(func, A_ILH_D,	ILH_D, set_fail_bin,		POWER_MILLI);

	PiDatalog(func, A_VcontBPP, VcontBPP, set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_VcontBPP_p, VcontBPP_p, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontBPP_1mA, VcontBPP_1mA, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontBPP_Rat, VcontBPP_Rat, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IcontBPP, IcontBPP, set_fail_bin,	POWER_MILLI);	
	//PiDatalog(func, A_ILL_BPP, ILL_BPP, set_fail_bin,	POWER_MICRO);
	//PiDatalog(func, A_ILH_BPP, ILH_BPP, set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_VcontUV,	VcontUV, set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_VcontUV_p,	VcontUV_p, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontUV_1mA,	VcontUV_1mA, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontUV_Rat,	VcontUV_Rat, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IcontUV,	IcontUV, set_fail_bin,	POWER_MILLI);	
	//////PiDatalog(func, A_ILL_UV,	ILL_UV, set_fail_bin,	POWER_MICRO);
	//////PiDatalog(func, A_ILH_UV,	ILH_UV, set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_VcontFW,	VcontFW, set_fail_bin,	POWER_UNIT);	
	//PiDatalog(func, A_VcontFW_p,	VcontFW_p, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontFW_1mA,	VcontFW_1mA, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontFW_Rat,	VcontFW_Rat, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IcontFW,	IcontFW, set_fail_bin,	POWER_MILLI);
	//////PiDatalog(func, A_ILL_FW,	ILL_FW, set_fail_bin,	POWER_MICRO);
	//////PiDatalog(func, A_ILH_FW,	ILH_FW, set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_VcontVO,	VcontVO, set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_VcontVO_p,	VcontVO_p, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontVO_1mA,	VcontVO_1mA, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontVO_Rat,	VcontVO_Rat, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IcontVO,	IcontVO, set_fail_bin,	POWER_MILLI);	
	//////PiDatalog(func, A_ILL_VO,	ILL_VO, set_fail_bin,	POWER_MICRO);
	//////PiDatalog(func, A_ILH_VO,	ILH_VO, set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_VcontSR,	VcontSR, set_fail_bin,	POWER_UNIT);	
	//PiDatalog(func, A_VcontSR_p,	VcontSR_p, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontSR_1mA,	VcontSR_1mA, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontSR_Rat,	VcontSR_Rat, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IcontSR,	IcontSR, set_fail_bin,	POWER_MILLI);	
	//////PiDatalog(func, A_ILL_SR,	ILL_SR, set_fail_bin,	POWER_MICRO);
	//////PiDatalog(func, A_ILH_SR,	ILH_SR, set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_VcontBPS, VcontBPS,set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_VcontBPS_p, VcontBPS_p,set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontBPS_1mA, VcontBPS_1mA,set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontBPS_Rat, VcontBPS_Rat,set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IcontBPS, IcontBPS,set_fail_bin,	POWER_MILLI);	
	//PiDatalog(func, A_ILL_BPS, ILL_BPS,set_fail_bin,	POWER_MICRO);
	//PiDatalog(func, A_ILH_BPS, ILH_BPS,set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_VcontREQ,	VcontREQ, set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_VcontREQ_p,	VcontREQ_p, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontREQ_1mA,	VcontREQ_1mA, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontREQ_Rat,	VcontREQ_Rat, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IcontREQ,	IcontREQ, set_fail_bin,	POWER_MILLI);	
	//////PiDatalog(func, A_ILL_FB,	ILL_FB, set_fail_bin,	POWER_MICRO);
	//////PiDatalog(func, A_ILH_FB,	ILH_FB, set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_VcontFWC,	VcontFWC, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontFWC_1mA,	VcontFWC_1mA, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontFWC_Rat,	VcontFWC_Rat, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_IcontFWC,	IcontFWC, set_fail_bin,	POWER_MILLI);

	PiDatalog(func, A_VcontACK,	VcontACK, set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_VcontACK_p,	VcontACK_p, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontACK_1mA,	VcontACK_1mA, set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_VcontACK_Rat,	VcontACK_Rat, set_fail_bin,	POWER_UNIT);
	//PiDatalog(func, A_IcontACK,	IcontACK, set_fail_bin,	POWER_MILLI);	/****** No capability on LB rev 6 *****/

	PiDatalog(func, A_GNDRes_Sec,GNDRes_Sec,set_fail_bin,	POWER_MILLI);	
	PiDatalog(func, A_GNDRes_Pri,GNDRes_Pri,set_fail_bin,	POWER_MILLI);

//Retrieve initial Capture Status.


	if (PiGetAnyFailStatus())
	{
		AbortTest = true;
		delay(50);	// Wait 50ms if failing continuity for Handler to respond properly
	}

	if(gDEBUG)
	printf("Continuity_Done\n");


//*********************************************************************************************************
//*********************************************************************************************************
//*********************************************************************************************************
	//Temporary code for Primary Controller die on PDIP package
	if (0)
	{
		float	vDrain_Trim		=0,
				vDrain_Read		=0,
				vDrain_Read_AF	=0,
				vDeviceID		=0;
		int		i			=0,
				trimTime	=0,
				readTime	=0,
				deviceID	=0,
				addr		=0;
		float	Iz_meas_p[60]	={0},
				Iztr_meas_p[60] ={0},
				Iz_meas_s[60]	={0};
		bool	Write_Trim_Mode	=false,
				Write_Read_Mode =false,
				Observe_Mode	=false;

		vDrain_Trim		= 40;
		vDrain_Read		= 15;
		vDrain_Read_AF	= 7;
		trimTime	= 5;	//ms
		readTime	= 10;	//x*10us => 200us if readTime = 20
	
		if(0)	//READ mode
		{
			Write_Trim_Mode	= false;
			Write_Read_Mode	= true;
		}
		else	//WRITE and TRIM mode
		{
			Write_Trim_Mode	= true;
			Write_Read_Mode	= false;
		}
		Observe_Mode	= true;
		wait.delay_10_us(100);  
		ddd_7->ddd_set_hi_level(5);							// Will immediately change to this level upon execution
		ddd_7->ddd_set_lo_level(0);							// Will immediately change to this level upon execution
		wait.delay_10_us(100);								//HL Do not remove. Else, DDD will be corrupted.; 
		ovi_1->disconnect(OVI_CHANNEL_1);

		Close_relay(K12);	//Vpin (UV) to DDD-7-1
		Close_relay(K2);	//Tap (Drain) to DVI-11-0
		delay(3);

			////Setup to connect 5kohm between Vpin and DDD
			//Open_relay(K12);	//Vpin (UV) to DDD-7-1
			//Close_relay(K16);	//5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
			//delay(4);

		//Vpin to start out LOW
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(10);

		//BPP set 0V
		ovi_1->set_voltage(OVI_CHANNEL_0, 0.0, RANGE_10_V);
		ovi_1->set_current(OVI_CHANNEL_0, 30e-3, RANGE_30_MA);
		wait.delay_10_us(10);

		//Tap set 0V (similar to Drain set 0V)
		dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
		dvi_11->set_current(DVI_CHANNEL_0, 10e-3, RANGE_30_MA);
		dvi_11->set_meas_mode(DVI_CHANNEL_0, DVI_MEASURE_CURRENT);


		//Bpp set 5V for 100us
		VBPP_ramp_up(0.0, 5.0, 200e-3); //BPP ramp up from 0 to 5V with 100mV step

		if(Write_Trim_Mode || Write_Read_Mode)
		{
			//Vpin clock 3 pulses (10us positive) to enter write mode
			Force_Vpin_Pulses_nTimes(3);
		}
		else	//Program Mode
		{
			//Vpin clock 2 pulses (10us positive) to enter program mode
			Force_Vpin_Pulses_nTimes(2);
		}

		if(Write_Trim_Mode)
		{
			dvi_11->set_voltage(DVI_CHANNEL_0, vDrain_Trim, VOLT_50_RANGE);
			wait.delay_10_us(50);
		}
		else
		{
			dvi_11->set_voltage(DVI_CHANNEL_0, vDrain_Read, VOLT_50_RANGE);
			wait.delay_10_us(50);
		}

		//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
		VBPP_ramp_up(5.0, 5.5, 50e-3);		
		VBPP_ramp_down(5.5, 5, 50e-3);	

		if(Write_Read_Mode)
		{
			//Release Drain(Tap) to 
			dvi_11->set_voltage(DVI_CHANNEL_0, vDrain_Read_AF, VOLT_50_RANGE);
			wait.delay_10_us(50);
		}

		//Trim everything
		for(i=1; i<=54; i++)
		{
			ddd_7->ddd_run_pattern(AF_Vpin_Clk_pulse_start, AF_Vpin_Clk_pulse_stop);	//Clk into next AF link
			wait.delay_10_us(4);

			//Trim anti-fuse link

			//Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
			ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
			wait.delay_10_us(4);
			if(Write_Trim_Mode)
				delay(trimTime);				//3ms similar to Inno2 Primary
			else
				wait.delay_10_us(readTime);		
			Iztr_meas_p[i] = dvi_11->measure_average(5);
			ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
			wait.delay_10_us(4);
		}

		//Have Vpin toggle back to stay at LOW
		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		wait.delay_10_us(3);

		dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
		wait.delay_10_us(3);
		Open_relay(K12);	//Vpin (UV) to DDD-7-1
		Open_relay(K2);		//Tap (Drain) to DVI-11-0
		Open_relay(K16);	//5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
		ovi_1->set_voltage(OVI_CHANNEL_0, 0.0, RANGE_10_V);
		ovi_1->connect(OVI_CHANNEL_1);
		delay(3);

	}


}
