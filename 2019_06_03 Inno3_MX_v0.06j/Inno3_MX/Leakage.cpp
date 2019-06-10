//==============================================================================
// Lekage.cpp (User function)
// 
//    void Lekage_user_init(test_function& func)
//    void Lekage(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "Leakage.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void Leakage_user_init(test_function& func)
{
	Leakage_params *ours;
    ours = (Leakage_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void Leakage(test_function& func)
{
    // The two lines below must be the first two in the function.
    Leakage_params *ours;
    ours = (Leakage_params *)func.params;

	int set_fail_bin = ours->fail_bin;
	
	set_fail_bin = 12;

	Func_name = "Leakage";

	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_Leakage,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//Initialize all variables to be 99mA;
	float	ILL_D	= 99 mA, 
			ILL_BPP	= 99 mA, 
			ILL_UV	= 99 mA, 
			ILL_FWC	= 99 mA, 
			ILL_REQ	= 99 mA, 
			ILL_BPS	= 99 mA, 
			ILL_SR	= 99 mA, 
			ILL_VO	= 99 mA, 
			ILL_FW	= 99 mA,
			ILL_ACK	= 99 mA;
	float	ILH_D	= 99 mA, 
			ILH_BPP	= 99 mA, 
			ILH_UV	= 99 mA, 
			ILH_FWC	= 99 mA, 
			ILH_REQ	= 99 mA, 
			ILH_BPS	= 99 mA, 
			ILH_SR	= 99 mA, 
			ILH_VO	= 99 mA, 
			ILH_FW	= 99 mA,
			ILH_ACK	= 99 mA;
	float	vmeas	= 99 mA, 
			imeas	= 99 mA;
	int		i = 0;

	//Connect Relays
	Close_relay(K2);	//Connects Drain to DVI_11_0
	Close_relay(K18);	//Connects FW to DVI_11_1

	//All pins to 0V
	VPIN_ovi->set_voltage(VPIN_ch,	0.0, 		RANGE_20_V);	// OVI_1_1
	VPIN_ovi->set_current(VPIN_ch,	300.0e-6,	RANGE_300_UA);	

	VO_dvi->set_voltage(VO_ch,		0.0,		VOLT_5_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch,		30.0e-6,	RANGE_30_UA);

	BPS_dvi->set_voltage(BPS_ch,	0.0,		VOLT_5_RANGE);	// DVI_9_1
	BPS_dvi->set_current(BPS_ch,	30.0e-3,	RANGE_30_MA);
	
	D_dvi->set_voltage(D_ch,		0.0,		VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch,		300.0e-3,	RANGE_300_MA);

	BPP_ovi->set_voltage(BPP_ch,	0.0,		RANGE_10_V);	// OVI_1_0
	BPP_ovi->set_current(BPP_ch,	30.0e-6,	RANGE_30_UA);

	FWC_dvi2k->set_voltage(FWC_ch,	0.0,		VOLT_10_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch,	200.0e-6,	RANGE_200_UA);

	FW_dvi->set_voltage(FW_ch,		0.0,		VOLT_5_RANGE);	// DVI_11_1
	FW_dvi->set_current(FW_ch,		20.0e-6,	RANGE_30_UA);

	SR_dvi2k->set_voltage(SR_ch,	0.0,		VOLT_10_RANGE);	// DVI_21_1
	SR_dvi2k->set_current(SR_ch,	200.0e-6,	RANGE_200_UA);

	REQ_ovi->set_voltage(REQ_ch,	0.0,		RANGE_10_V);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch,	30.0e-6,	RANGE_30_UA);

	ACK_ovi->set_voltage(ACK_ch,	0.0,		RANGE_10_V);	// OVI_1_5
	ACK_ovi->set_current(ACK_ch,	30.0e-6,	RANGE_30_UA);

	//**********************************
	//** Primary Leakages
	//**********************************

	//Drain Low Leakage test only (High leakage is already in BV_Drain function)
	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_CURRENT);
	D_dvi->set_voltage(D_ch, 0.0,			VOLT_10_RANGE); 
	D_dvi->set_current(D_ch, 3e-3,		RANGE_3_MA);		//Use 3mA to bring it to GND faster then smaller Range
	wait.delay_10_us(50);
	D_dvi->set_current(D_ch, 300.0e-6,		RANGE_300_UA);	//Use 300uA for better accuracy
	delay(5);
	ILL_D  = D_dvi->measure_average(15);
	gILL_D_pre = ILL_D;

	D_dvi->set_voltage(D_ch, 5.5,			VOLT_10_RANGE); 
	wait.delay_10_us(50);
	//If BPP is set to 5.5V, Vpin at 20V will fail (It has to go through the BPP power cycle)
	BPP_ovi->set_current(BPP_ch, 30.0e-3,	RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, 5.5,		VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)
	wait.delay_10_us(20);
	BPP_ovi->set_voltage(BPP_ch, 4.5,		VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)
	wait.delay_10_us(20);
	BPP_ovi->set_voltage(BPP_ch, 5.1,		VOLT_10_RANGE); //Leave BPP power-up  (Wonder if it should go through BPP cycle)

	VPIN_ovi->set_meas_mode(VPIN_ch,		OVI_MEASURE_CURRENT);
	VPIN_ovi->set_voltage(VPIN_ch, 5.5,		RANGE_10_V);		//Bring this back after Vpin BV circuit in place
	wait.delay_10_us(50);
	ILH_UV = VPIN_ovi->measure_average(5);		
	gILH_UV_pre = ILH_UV;

	VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_2_V); 
	wait.delay_10_us(50);
	ILL_UV = VPIN_ovi->measure_average(5);	
	gILL_UV_pre = ILL_UV;

	//Primary pins set to 0V
	BPP_ovi->set_voltage(BPP_ch, 0.0,		VOLT_10_RANGE); 
	D_dvi->set_voltage(D_ch, 0.0,			VOLT_10_RANGE); 


	//**********************************
	//** Secondary Leakages
	//**********************************

	////BPS leakage (Only the low leakage since vBPS_Hi will either be device power-up or Ishunt)
	BPS_dvi->set_current(BPS_ch,	10.0e-3,	RANGE_30_MA);
	BPS_dvi->set_voltage(BPS_ch,	4.5, 		VOLT_5_RANGE);
	wait.delay_10_us(50);

	//FW leakage (Make sure it's less than vBPS else it could provide charge to BPS easily)
	FW_dvi->set_meas_mode(FW_ch,				DVI_MEASURE_CURRENT);
	FW_dvi->set_current(FW_ch,		30.0e-6,	RANGE_30_UA);
	FW_dvi->set_voltage(FW_ch,		0.0,		VOLT_5_RANGE);
	wait.delay_10_us(5);
	ILL_FW  = FW_dvi->measure_average(5);
	gILL_FW_pre = ILL_FW;

	//REQ leakage
	REQ_ovi->set_meas_mode(REQ_ch,				OVI_MEASURE_CURRENT);
	REQ_ovi->set_voltage(REQ_ch, 0.0,				RANGE_10_V); 
	wait.delay_10_us(5);
	ILL_REQ = REQ_ovi->measure_average(5); 
	gILL_REQ_pre = ILL_REQ;

	//Vout Leakage	(Low Leakage test only.  Vout can provide charge to BPS)
	VO_dvi->set_meas_mode(VO_ch,				DVI_MEASURE_CURRENT);
	wait.delay_10_us(5);
	ILL_VO = VO_dvi->measure_average(5);		
	gILL_VO_pre = ILL_VO;

	//Secondary pins set to 0V0
	BPS_dvi->set_voltage(BPS_ch,	0.0, 		VOLT_5_RANGE);
	
	//Datalog
	PiDatalog(func, A_ILL_D,	ILL_D, set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_ILL_UV,	ILL_UV, set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_ILH_UV,	ILH_UV, set_fail_bin,	POWER_MILLI);
	PiDatalog(func, A_ILL_FW,	ILL_FW, set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_ILL_VO,	ILL_VO, set_fail_bin,	POWER_MICRO);
	PiDatalog(func, A_ILL_REQ,	ILL_REQ, set_fail_bin,	POWER_MICRO);

	if (PiGetAnyFailStatus())
	{
		AbortTest = true;
		delay(50);	// Wait 50ms if failing continuity for Handler to respond properly
	}

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


	if(gDEBUG==1)
	printf("Leakage_Done\n");


}
