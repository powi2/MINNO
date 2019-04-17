//==============================================================================
// VBP_Init.cpp (User function)
// 
//    void VBP_Init_user_init(test_function& func)
//    void VBP_Init(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#include "VBP_Init.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void VBP_Init_user_init(test_function& func)
{
	VBP_Init_params *ours;
    ours = (VBP_Init_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void VBP_Init(test_function& func)
{
    // The two lines below must be the first two in the function.
    VBP_Init_params *ours;
    ours = (VBP_Init_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "VBP_Init";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_VBP_init,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	double ID_1V_2V=0;
	float  Vshunt_Init_Pr=0;
	float  Vshunt_Init_Se=0;
	float  VBPP_P_Init=0, VBPP_M_Init=0, VBPP_HYS_Init=0, VBPP_PV_Init=0, VBPP_P_iHVoff=0, VBPP_Vshunt_PUseq=0;
	float  VBPS_P_Init=0, VBPS_M_Init=0, VBPS_HYS_Init=0;
	int	   VBP_Init_debug=0;

	//B3 Material variables added
	float  VBPP_P_Init_P=0, VBPP_P_Init_S=0;

	DEBUG=0;
	//VBP_Init_debug = 0;
	//if(VBP_Init_debug)
	//	DEBUG = 1;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

/****************************************************************************
 *							1V 2V tests										*
 ****************************************************************************/
	Close_relay(K2);	//Drain
	Close_relay(K18);	//FW
	// Disconnect UV(Itag) pin to stop it from pulling 0.5mA from device in normal mode. 
	VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_2_V);  
	VPIN_ovi->set_current(VPIN_ch, 10e-3,		RANGE_30_MA);		
	delay(2);

	D_dvi->set_voltage(D_ch, 2.0,			VOLT_2_RANGE);  
	D_dvi->set_current(D_ch, 200e-3,		RANGE_300_MA);		
	VBPP_ramp_down(3, 1.0, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		RANGE_10_V);	// OVI_1_0
	BPP_ovi->set_current(BPP_ch, 3e-3,						RANGE_3_MA);
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_CURRENT);
	delay(5);

	D_dvi->set_current(D_ch, 29e-6, RANGE_30_UA);wait.delay_10_us(10);
	delay(8);
//	ID_1V_2V = BPP_ovi->measure_average(10);
	ID_1V_2V = D_dvi->measure_average(10);

//	D_dvi->set_voltage(D_ch,	 0.0,		VOLT_10_RANGE);  
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		RANGE_10_V);	// OVI_1_0
	

	/****************************************************************************
	 *								VShunt										*
	 ****************************************************************************/
	
	//BPP_ICH ~1.5mA.  0.2mA set here to have device power-up at 45V through normal power-up seq & apply 2mA later for Vshunt
	BPP_ovi->set_current(BPP_ch, 0.2e-3,		RANGE_3_MA);	//B2 silicon is about ~1.1mA

	FW_dvi->set_voltage(FW_ch,	 0.0,		VOLT_2_RANGE);  //Redue noise for secondary

	Open_relay(K2);
	Close_relay(K3);			// Drain to L1,R1 pullup from dvi-11-0
	delay(3);

	D_dvi->set_voltage(D_ch, 0.0,			VOLT_10_RANGE);  
	D_dvi->set_current(D_ch, 30e-3,			RANGE_300_MA);	

	VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_2_V);  
	VPIN_ovi->set_current(VPIN_ch, 10e-3,		RANGE_30_MA);		
	wait.delay_10_us(50);

	BPP_ovi->set_current(BPP_ch, 20.0e-3,		RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, 0,	RANGE_10_V);	// OVI_1_0
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_VOLTAGE);
	wait.delay_10_us(50);

	D_dvi->set_voltage(D_ch,	 5,		VOLT_10_RANGE);  
	delay(1);

	//Powerup BPP zigzag. I_BPP ~ 15mA
	VBPP_ramp_up(0, 5.5, 100e-3);
	VBPP_ramp_down(5.5, 4.3, 50e-3);
	VBPP_ramp_up(4.3, 5.5, 50e-3);
	wait.delay_10_us(50);

	BPP_ovi->set_current(BPP_ch, 2.0e-3,		RANGE_30_MA);
	wait.delay_10_us(200);
	if(BPP_4p7uF) delay(22);

	Vshunt_Init_Pr = BPP_ovi->measure_average(10);

	//D_dvi->set_voltage(D_ch,	 5,		VOLT_50_RANGE);  
	//D_dvi->set_current(D_ch,   10e-3,		RANGE_30_MA);
	//delay(3);
	
//	BPP_ovi->set_current(BPP_ch, 2.0e-3,		RANGE_3_MA);
//	BPP_ovi->set_voltage(BPP_ch, gVshunt_BPP,	RANGE_10_V);	// OVI_1_0
//	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_VOLTAGE);
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF
	delay(1);
	
	REQ_ovi->set_voltage(REQ_ch, 2.0, RANGE_5_V);
	REQ_ovi->set_current(REQ_ch, 10e-3,		RANGE_30_MA);

	VBPS_ramp_up(0, gVshunt_BPS, 200e-3);
	BPS_dvi->set_voltage(BPS_ch, gVshunt_BPS, VOLT_10_RANGE);  
	//BPS_dvi->set_current(BPS_ch, 300e-3,	RANGE_300_MA);			wait.delay_10_us(20);
	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_VOLTAGE);
	BPS_dvi->set_current(BPS_ch, 2e-3,	RANGE_300_MA);	
	wait.delay_10_us(50);

	D_dvi->set_voltage(D_ch,	 0.0,		VOLT_50_RANGE);  //Reduce noise for Primary
	wait.delay_10_us(50);

	//BPP_ovi->set_current(BPP_ch, 2.0e-3,		RANGE_30_MA);
	//wait.delay_10_us(50);
	//if(BPP_4p7uF) delay(22);

	//Vshunt_Init_Pr = BPP_ovi->measure_average(10);
	pulse.do_pulse();
	Vshunt_Init_Se = BPS_dvi->measure_average(10);
	gVshunt_Init_Pr = Vshunt_Init_Pr;
	gVshunt_Init_Se = Vshunt_Init_Se;

	//VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		RANGE_10_V);	// OVI_1_0
	BPS_dvi->set_voltage(BPS_ch, 0.0,		VOLT_10_RANGE);  
	D_dvi->set_voltage(D_ch,	 0.0,		VOLT_50_RANGE);  
	wait.delay_10_us(10);

/**************************************************************************************
 *					Primary: VBPP_Init_P, VBPP_Init_M, VBPP_Init_HYS				  *
 **************************************************************************************/
	
	VBPP_P_Init = 0.0;
	VBPP_M_Init = 0.0;
	
	//DEBUG=1;	
	if(gSiliconRev_P>=3)
	{
		search_VBPP_th_B3(&VBPP_PV_Init, &VBPP_M_Init, &VBPP_P_Init_P, &VBPP_P_iHVoff, &VBPP_Vshunt_PUseq, &VBPP_P_Init_S);
		gVBPP_P_Init	= VBPP_P_Init_P;	
	}
	else
	{
		search_VBPP_th(&VBPP_PV_Init, &VBPP_M_Init, &VBPP_P_Init, &VBPP_P_iHVoff, &VBPP_Vshunt_PUseq);
		gVBPP_P_Init	= VBPP_P_Init;		
	}
	//DEBUG=0;

	gVBPP_PV_Init	= VBPP_PV_Init;
	gVBPP_M_Init	= VBPP_M_Init;

	// Power down VBPP test
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_DVI->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU,	VOLT_10_RANGE);	wait.delay_10_us(10);	
	//Drain = 0V
	D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
	D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(5);
	Open_relay(K3);			   

/**************************************************************************************
 *					Secondary: VBPS_Init_P, VBPS_Init_M, VBPS_Init_HYS				  *
 *VBPS_Init_P:																		  *
 * Apply 60us period negative square wave on FW pin                                   *                  
 * Gradually increasing BPS voltage before powering up secondary into Normal Mode     * 
 * until pulses show up on ACK pin. Record the BPS voltage as VBPS_P 	              *
 * REQ=2V                                                                             *
 * SR= 5nf                                                                            *	                                                                  	                                                                    *
 *																				      *
 *VBPS_Init_M:																		  *
 * REQ=2V                                                                             *                  
 * Gradually decreasing BPS voltage before powering up secondary into Normal Mode     * 
 * until pulses disappear on ACK pin. Record the BPS voltage as VBPS_M                *												  *
 **************************************************************************************/

//** VBPS_P_Init & VBPS_M_Init
	// K18 was closed above
	BPS_dvi->set_current(BPS_ch, 100e-3,	RANGE_300_MA);	 
	FW_dvi->set_current(FW_ch,   30e-3,	RANGE_30_MA);	 
	FW_dvi->set_voltage(FW_ch,	 5.0,		VOLT_10_RANGE);	 
	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	/*BPS_dvi->set_voltage(BPS_ch, 3.5, VOLT_10_RANGE);
	delay(1);*/
	REQ_ovi->set_voltage(REQ_ch, 2.0, RANGE_5_V);
	REQ_ovi->set_current(REQ_ch, 10e-3,		RANGE_30_MA);
	//Float FWC
	FWC_dvi2k->open_relay(CONN_FORCE0);
	FWC_dvi2k->open_relay(CONN_SENSE0);

	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);//Connect SR to 5nF
	Open_relay(K18);   // FW_dvi
	Close_relay(K21);
	delay(4);
	
	VBPS_P_Init = 0.0;
	VBPS_M_Init = 0.0;
	gVBPS_P_Init =0.0;
	gVBPS_M_Init =0.0;
	
	search_VBPS_P_th(&VBPS_P_Init);
	gVBPS_P_Init = VBPS_P_Init;

	search_VBPS_M_th(&VBPS_M_Init);
	//search_VBPS_M_th_Inno4(&VBPS_M_Init);
	gVBPS_M_Init = VBPS_M_Init;
	

	VBPS_HYS_Init = VBPS_P_Init - VBPS_M_Init;

	//Reset BPS, FW, Vout to 0V
	BPS_dvi->set_voltage(BPS_ch, 0.0,		VOLT_10_RANGE);  
	FW_dvi->set_voltage(FW_ch,	 0.0,		VOLT_10_RANGE);	 
	VO_dvi->set_voltage(VO_ch,	 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	REQ_ovi->set_voltage(REQ_ch, 0.0, RANGE_5_V);
	wait.delay_10_us(5);



	//B3 silicon vBPP_plus-S with 2ndary in control
	//iBPP change current from plus to minus.
	//void SyncHS_PowerUp_Secondary_in_Test_Mode(int TestModeSelect=0, int ILIM_Mode=0)

//pulse.do_pulse();

	if(gSiliconRev_P>=3)
	{	
		float bpp_current[300] = {0};
		int k=0;
		float vstep=5e-3;
		float vBPP_start=0;

		#define TM6p_PU_find_vBPP_Ps

		#ifdef TM6p_PU_find_vBPP_Ps
			wait.delay_10_us(100); 
			ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
			wait.delay_10_us(100);
			ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
			wait.delay_10_us(100);                           // HL do not remove delay.  Else, it will corrupt the DDD pattern.
			Close_relay(K3);
			Close_relay(K12);
			delay(4);
			ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);	//FW will start with High
			wait.delay_10_us(10);

			Power_Up_Primary_TM6(ILIM_NORM);
	
			wait.delay_10_us(10);
			ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);	//FW will start with High
			wait.delay_10_us(10);
			ddd_7->ddd_end_pattern(Vpin_loop_pulse_stop);	//K12 needs to be closed for DDD connect to Vpin
			wait.delay_10_us(10);
			ddd_7->ddd_run_pattern();
			delay(5);

			////////////// Experiment only. Awaiting for design approval.  Vpin = 0V after test mode 6.
			////ddd_7->ddd_stop_pattern();
			////delay(1);	
			////VPIN_ovi->connect(1);
			////delay(3);
			////VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_5_V);  
			////VPIN_ovi->set_current(VPIN_ch, 10e-3,		RANGE_30_MA);		
			////delay(1);
			////Open_relay(K12);
			////delay(3);
			
			BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
			k=0;
			bpp_current[1]=0;
			vstep		= 5e-3;
			vBPP_start = 5.15; 
			while(k<300)
			{
				k++;
				BPP_ovi->set_voltage(BPP_ch, vBPP_start-k*vstep,		RANGE_10_V);	// Starting search point
				wait.delay_10_us(5);
				bpp_current[k] = BPP_ovi->measure_average(5);
				if(bpp_current[k]<-0.6e-3)
				{
					VBPP_P_Init_S = vBPP_start-k*vstep;
					break;
				}
				//k++;
			}
			wait.delay_10_us(10);

			ddd_7->ddd_stop_pattern();
			wait.delay_10_us(10);
		#endif

		#ifndef TM6p_PU_find_vBPP_Ps
			Close_relay(K3);
			//Vpin (0V)
			VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
			VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
			//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
			//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
			SR_dvi2k->set_current(SR_ch, 20e-3,			RANGE_2_A);	
			SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
			dvi_13->close_relay(BUS_SENSE1);
			dvi_13->close_relay(BUS_FORCE1);
			mux_14->close_relay(MUX_3_BUS3);
			wait.delay_10_us(20);
			delay(3);

		//Vout (Will charge BPS if @5V)
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
		//FB (1V)
		REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
		REQ_ovi->set_voltage(REQ_ch, 0.8,		RANGE_2_V);	// OVI_1_2		//Try for low CVinit devices
		//REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 200mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	

		//Make sure vBPS less than 5.5V
		if(gVBPS_M_Init < 5.5)		VBPS_Power_Up(gVBPS_M_Init-0.2);			
		else						VBPS_Power_Up(4.5);			

		Connect_InvSyn_IM(Low_Load_Vd_Input);

				//VBPP_Power_Up_w_Test_Mode(gTM1_p, ILIM_Mode);	//
				//Drain = 0V
				D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
				D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
				//UV pin (Vpin) set to 0V before PU
				VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_10_V);  
				VPIN_ovi->set_current(VPIN_ch, 20e-3,		RANGE_30_MA);	
				//BPP set 0V
				BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);	// Set 2mA here to prevent BPP go into Vshunt for B3 silicon
				BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);	// OVI_1_0
				wait.delay_10_us(5);
				VBPP_ramp_up(3.5, 5.5, 0.2);	// vstart, vstop, vstep		
				VBPP_ramp_down(5.5, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
				BPP_ovi->set_current(BPP_ch,  15e-3,	RANGE_30_MA);	// 15mA here so iBPP_minus won't clamp at 2mA from above for B3 silicon
				wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
				VBPP_ramp_down(gVBPP_M_Init +0.25, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
				wait.delay_10_us(10);
				BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);	// Set 2mA here to prevent BPP go into Vshunt for B3 silicon
				wait.delay_10_us(10);
				VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_Init+100e-3, 10e-3);	// vstart, vstop, vstep	B3 material

			D_dvi->set_voltage(D_ch, HANDSHAKE_Vd_TM, 	VOLT_50_RANGE);	// DVI_11_0	

		//Make sure vBPS less than 5.5V
		if(gVBPS_P_Init < 5.5)		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	
		else						BPS_dvi->set_voltage(BPS_ch, 4.5, 			VOLT_10_RANGE);	
		delay(3);
		//Disable SoftStart with FB toggle high/low
		if(LB_Rev >= 5)		REQ_ovi->set_voltage(REQ_ch, gCVth_15pct_Higher,		RANGE_2_V);	// OVI_1_2	
		else				REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	
							wait.delay_10_us(20);
							REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2		Try for low CV_init
							wait.delay_10_us(10);
		//Exit primary testmode 1 so device will be switching continuously at low load
		D_dvi->set_voltage(D_ch, 40.0, 	VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(10);


			vBPP_start = 5.45;
			BPP_ovi->set_voltage(BPP_ch, vBPP_start,		RANGE_10_V);	// Starting search point

			BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
			wait.delay_10_us(20);
			//BPP_ovi->set_current(BPP_ch, 10e-3,		RANGE_30_MA);   
			//wait.delay_10_us(20);
			REQ_ovi->set_voltage(REQ_ch, 1.3,		RANGE_2_V);	// OVI_1_2	

			k=0;
			bpp_current[1]=0;
			while(k<300)
			{
				k++;
				BPP_ovi->set_voltage(BPP_ch, vBPP_start-k*vstep,		RANGE_10_V);	// Starting search point
				wait.delay_10_us(5);
				bpp_current[k] = BPP_ovi->measure_average(5);
				if(bpp_current[k]<-0.6e-3)
				{
					VBPP_P_Init_S = vBPP_start-k*vstep;
					break;
				}
				//k++;
			}
			wait.delay_10_us(10);
			Open_relay(K3);
		#endif
	}


	//Calculate Hysteresis 
	if(gSiliconRev_P>=3)		VBPP_HYS_Init	= VBPP_P_Init_S - gVBPP_M_Init;
	else						VBPP_HYS_Init	= VBPP_P_Init - gVBPP_M_Init;


	//Power Down
	//Disconnect_InvSyn_IM();
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();

	//#define CHAR_ON
	#ifdef CHAR_ON
		//*********************************************************************************
		//** Characterized BPPth
		//*********************************************************************************

		float bpp_current[300] = {0};
		int k=0, pv_count=0, m_count=0, p_count=0, Ps_count=0;
		float vstep=5e-3;
		float vBPP_start=0, vBPP=0;
		float vBPP_pv[300]={0}, iBPP_pv[300]={0},
			  vBPP_p[300]={0},  iBPP_p[300]={0},
			  vBPP_m[300]={0},  iBPP_m[300]={0},
			  vBPP_Ps[300]={0}, iBPP_Ps[300]={0};

		//initialize all array variables
		for(k=0; k<300; k++)
		{
			vBPP_pv[k]=0;
			vBPP_p[k]=0;  
			vBPP_m[k]=0;  
			vBPP_Ps[k]=0; 
			iBPP_pv[k]=0;
			iBPP_p[k]=0;
			iBPP_m[k]=0;
			iBPP_Ps[k]=0;
			bpp_current[k]=0;
		}

		if(gSiliconRev_P>=3)
		{	
			Close_relay(K3);
			//Vpin (0V)
			VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
			VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
			//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
			//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
			SR_dvi2k->set_current(SR_ch, 20e-3,			RANGE_2_A);	
			SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
			dvi_13->close_relay(BUS_SENSE1);
			dvi_13->close_relay(BUS_FORCE1);
			mux_14->close_relay(MUX_3_BUS3);
			wait.delay_10_us(20);
			delay(3);

			//Vout (Will charge BPS if @5V)
			VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
			VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
			//FB (1V)
			REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
			//REQ_ovi->set_voltage(REQ_ch, 0.8,		RANGE_2_V);	// OVI_1_2		//Try for low CVinit devices
			REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
			//IS (0V)
			FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
			FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
			wait.delay_10_us(10);
			//BPS (vPlus - 200mV)
			BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	

			//Make sure vBPS less than 5.5V
			if(gVBPS_M_Init < 5.5)		VBPS_Power_Up(gVBPS_M_Init-0.2);			
			else						VBPS_Power_Up(4.5);			

			Connect_InvSyn_IM(Low_Load_Vd_Input);

			//VBPP_Power_Up_w_Test_Mode(gTM1_p, ILIM_Mode);	//
			//Drain = 0V
			D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
			D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
			//UV pin (Vpin) set to 0V before PU
			VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_10_V);  
			VPIN_ovi->set_current(VPIN_ch, 20e-3,		RANGE_30_MA);	
			//BPP set 0V
			BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);	// Set 2mA here to prevent BPP go into Vshunt for B3 silicon
			BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);	// OVI_1_0
			BPP_ovi->set_meas_mode(BPP_ch,		OVI_MEASURE_CURRENT);
			wait.delay_10_us(5);
			
			//Characterize vBPP_PV threshold
			BPP_ovi->set_current(BPP_ch,  15e-3,	RANGE_30_MA);	// 15mA here so iBPP_minus won't clamp at 2mA from above for B3 silicon
			wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
			k=0;
			vstep=25e-3;
			vBPP=0;
			while(vBPP<=5.5)
			{
				BPP_ovi->set_voltage(BPP_ch, vBPP, 	RANGE_10_V);	// OVI_1_0
				wait.delay_10_us(5);
				vBPP_pv[k] = vBPP;
				iBPP_pv[k] = BPP_ovi->measure_average(5);
				vBPP = vBPP+vstep;
				k++;
			}
			pv_count = k-1;


			//Characterize vBPP_M threshold
			D_dvi->set_voltage(D_ch,	 45,		VOLT_50_RANGE);  
			BPP_ovi->set_current(BPP_ch, 8e-3,	RANGE_30_MA);	// Set 8mA here to prevent BPP go into Vshunt for B3 silicon
			wait.delay_10_us(10);
			k=0;
			while(vBPP>=4.3)
			{
				BPP_ovi->set_voltage(BPP_ch, vBPP, 	RANGE_10_V);	// OVI_1_0
				wait.delay_10_us(5);
				vBPP_m[k] = vBPP;
				iBPP_m[k] = BPP_ovi->measure_average(5);
				vBPP = vBPP-vstep;
				k++;
			}
			m_count = k-1;


			//Characterize vBPP_P threshold
			BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);	// Set 2mA here to prevent BPP go into Vshunt for B3 silicon
			wait.delay_10_us(50);
			k=0;
			while(vBPP<=5.5)
			{
				BPP_ovi->set_voltage(BPP_ch, vBPP, 	RANGE_10_V);	// OVI_1_0
				wait.delay_10_us(5);
				vBPP_p[k] = vBPP;
				iBPP_p[k] = BPP_ovi->measure_average(5);
				vBPP = vBPP+vstep;
				k++;
			}
			p_count = k-1;


			D_dvi->set_voltage(D_ch, HANDSHAKE_Vd_TM, 	VOLT_50_RANGE);	// DVI_11_0	

			//Make sure vBPS less than 5.5V
			if(gVBPS_P_Init < 5.5)		BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	
			else						BPS_dvi->set_voltage(BPS_ch, 4.5, 			VOLT_10_RANGE);	
			delay(3);
			//Disable SoftStart with FB toggle high/low
			if(LB_Rev >= 5)		REQ_ovi->set_voltage(REQ_ch, gCVth_15pct_Higher,		RANGE_2_V);	// OVI_1_2	
			else				REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	
								wait.delay_10_us(20);
								REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2		Try for low CV_init
								wait.delay_10_us(10);
			//Exit primary testmode 1 so device will be switching continuously at low load
			D_dvi->set_voltage(D_ch, 40.0, 	VOLT_50_RANGE);	// DVI_11_0	
			wait.delay_10_us(10);


			//Characterize vBPP_P_s threshold (vPlus of BPP with Secondary in control)
			k=0;
			while(vBPP>=4.0)
			{
				BPP_ovi->set_voltage(BPP_ch, vBPP, 	RANGE_10_V);	// OVI_1_0
				wait.delay_10_us(5);
				vBPP_Ps[k] = vBPP;
				iBPP_Ps[k] = BPP_ovi->measure_average(5);
				vBPP = vBPP-vstep;
				k++;
			}
			Ps_count = k-1;


			Open_relay(K3);
		}

		int i=0;
		char debug_file_name[150] ="/0"; 

		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, DevName); 
		strcat (debug_file_name, "_BPPth_debug.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print to file
		fprintf (fpr, "\nCharacterize BPPth vs iBPP \n\n");

		//print vBPP_pv
		fprintf(fpr,"VPIN=0V, SR=GND, Vout=4V, FB=0.8V, IS=0V, BPS=vMinus, InvSync connected, D=0V\n");
		fprintf(fpr,"BPP set 15mA clamp and Ramp up voltage from 0V to 5.5V measure iBPP\n");
		for (i=0; i<=pv_count;i++)
		{
			fprintf(fpr,"vBPP_pv= %.4f V, iBPP_pv = %.3f mA\n",vBPP_pv[i],iBPP_pv[i]*1e3);
		}
		fprintf(fpr,"\n");

		//print vBPP_m
		fprintf(fpr,"Drain set to 45V and BPP change current clamp to 8mA then ramp BPP from 5.5V to 4.3V and measure iBPP\n");
		for (i=0; i<=m_count;i++)
		{
			fprintf(fpr,"vBPP_m= %.4f V, iBPP_m = %.3f mA\n",vBPP_m[i],iBPP_m[i]*1e3);
		}
		fprintf(fpr,"\n");

		//print vBPP_p
		fprintf(fpr,"BPP set current clamp to 2mA and ramp up voltage from 4.3V to 5.5V and measure iBPP\n");
		for (i=0; i<=p_count;i++)
		{
			fprintf(fpr,"vBPP_p= %.4f V, iBPP_p = %.3f mA\n",vBPP_p[i],iBPP_p[i]*1e3);
		}
		fprintf(fpr,"\n");

		//print vBPP_Ps
		fprintf(fpr,"Drain set to HANDSHAKE_Vd_TM then power-up BPS to vPlus + 50mV. \n");
		fprintf(fpr,"FB set 15pct higher than CVth then FB set to 0.8V to request switching.\n");  
		fprintf(fpr,"Drain set to 40V.  Ramp down vBPP from 5.5V to 4V and measure iBPP\n");
		for (i=0; i<=Ps_count;i++)
		{
			fprintf(fpr,"vBPP_Ps= %.4f V, iBPP_Ps = %.3f mA\n",vBPP_Ps[i],iBPP_Ps[i]*1e3);
		}
		fprintf(fpr,"\n");

		fprintf (fpr, "End of BPPth vs. iBPP Measurements\n");
		fclose(fpr);

		//Power Down
		//Disconnect_InvSyn_IM();
		Power_Down_Everything();
		Open_All_Relays();
		Disconnect_InvSyn_IM();

#endif

	//ddd_7->ddd_stop_pattern();								// Stop the DDD loop pattern
	//ddd_7->ddd_set_lo_level(0.1);							// Will immediately change to this level upon execution 
	//ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);

	////FW_dvi->set_voltage(FW_ch,	 0.01,		VOLT_10_RANGE);	

	////D_dvi->set_voltage(D_ch,	 0.01,		VOLT_50_RANGE);  
	////BPP_DVI->set_voltage(BPP_ch, 0.01, 		VOLT_10_RANGE);	// OVI_1_0

	////REQ_ovi->set_voltage(REQ_ch,   0.01, 		RANGE_2_V);	// OVI_1_2
	////VO_dvi->set_voltage(VO_ch, 0.01, 		VOLT_5_RANGE);	// DVI_9_0

	////BPS_dvi->set_voltage(BPS_ch, 0.01,		VOLT_10_RANGE);  
	////wait.delay_10_us(20);

	////Open_relay(K21);
	////Open_relay(K18);
	////Open_relay(K3);
	////VO_dvi->close_relay(CONN_FORCE0);
	////VO_dvi->close_relay(CONN_SENSE0);
	////wait.delay_10_us(10);

	//Datalog
	PiDatalog(func, A_ID_1V_2V,				ID_1V_2V,			set_fail_bin,	POWER_MICRO);	
	PiDatalog(func, A_Vshunt_Init_Pr,		Vshunt_Init_Pr,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_Vshunt_Init_Se,		Vshunt_Init_Se,		set_fail_bin,	POWER_UNIT);	

	PiDatalog(func, A_VBPP_PV_Init,			VBPP_PV_Init,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_VBPP_M_Init,			VBPP_M_Init,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_VBPP_HYS_Init,		VBPP_HYS_Init,		set_fail_bin,	POWER_UNIT);
if(gSiliconRev_P<=2)
{
	PiDatalog(func, A_VBPP_P_Init,			VBPP_P_Init,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_VBPP_P_iHVoff,		VBPP_P_iHVoff,		set_fail_bin,	POWER_UNIT);	
}
else
{
	//B3 material datalog
	PiDatalog(func, A_VBPP_P_Init,			VBPP_P_Init_P,				set_fail_bin,	POWER_UNIT);	
	//iHVoff does not need for B3 silicon from Lance
	PiDatalog(func, A_VBPP_P_S_Init_P,		VBPP_P_Init_S,				set_fail_bin,	POWER_UNIT);	//temp use for vBPP_2ndary Control threshold
}
	//PiDatalog(func, A_VBPP_Vshunt_PUseq,	VBPP_Vshunt_PUseq,	set_fail_bin,	POWER_UNIT);	

	PiDatalog(func, A_VBPS_P_Init,			VBPS_P_Init,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_VBPS_M_Init,			VBPS_M_Init,		set_fail_bin,	POWER_UNIT);	
	PiDatalog(func, A_VBPS_HYS_Init,		VBPS_HYS_Init,		set_fail_bin,	POWER_UNIT);

	if(gDEBUG==1)
	printf("Function VBP_Init Done\n");


	if(gSiliconRev_P<=2)
	{
			gVBPP_P_final   = VBPP_P_Init	+0.05;
			if(gVBPP_P_final<1.0)	gVBPP_P_final = 5.1;
	}
	else
	{
			gVBPP_P_final   = VBPP_P_Init_P + 0.05;	//B3 and later material
			if(OPCODE!=4400)		gVBPP_P_s_final = VBPP_P_Init_S + 0.05;	//B3 and later material
			if(OPCODE==4400)		gVBPP_P_s_final = VBPP_P_Init_S + 0.10;	//B3 and later material
			if(gVBPP_P_final<1.0)	gVBPP_P_final	= 5.45;
			if(gVBPP_P_s_final<4.8)	gVBPP_P_s_final = 5.05;
	}
			gVBPS_final		= gVBPS_P_Init	+0.05;	
			gVBPP_PV_final	= gVBPP_PV_Init +0.05;


    //Require VBPP correct threshold for other test +-   
//    if (PiGetAnyFailStatus() && gCharacterization)     
    if (PiGetAnyFailStatus())     
    {     
        if(gVBPP_PV_Init	< 5.2)			gVBPP_PV_Init	= 5.45;  
        if(gVBPP_P_Init		< 4.9)			gVBPP_P_Init	= 5.10;
        if(fabs(gVBPP_M_Init - 4.50)>0.2)	gVBPP_M_Init	= 4.50;
		if(fabs(gVBPS_P_Init - 4.35)>0.3)	gVBPS_P_Init	= 4.4;
		if(fabs(gVBPS_M_Init - 3.70)>0.4)	gVBPS_M_Init	= 3.7;

								gVBPS_final		= gVBPS_P_Init + 0.05;	
								gVBPP_PV_final	= gVBPP_PV_Init + 0.05;
		if(gSiliconRev_P<=2)	
		{
			gVBPP_P_final	= gVBPP_P_Init + 0.05;//B2 and older material
			if(gVBPP_P_final<1.0)	gVBPP_P_final = 5.1;
		}
		else					
		{	gVBPP_P_final   = VBPP_P_Init_P + 0.05;		//B3 and later material
			gVBPP_P_s_final = VBPP_P_Init_S + 0.05;		//B3 and later material
			if(gVBPP_P_final<1.0)	gVBPP_P_final = 5.45;
			if(gVBPP_P_s_final<4.8)	gVBPP_P_s_final = 5.10;

		}
		
    } 
	

}
