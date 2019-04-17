//==============================================================================
// BV_FW.cpp (User function)
// 
//    void BV_FW_user_init(test_function& func)
//    void BV_FW(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "BV_FW.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void BV_FW_user_init(test_function& func)
{
	BV_FW_params *ours;
    ours = (BV_FW_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void BV_FW(test_function& func)
{
    // The two lines below must be the first two in the function.
    BV_FW_params *ours;
    ours = (BV_FW_params *)func.params;

	int set_fail_bin = ours->fail_bin;


	Func_name = "FW_BVD";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_BV_FW,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	//if (AbortTest || MOSFET_SIZE==8)	//The 1st SilRev of sizex8 fail BV
	if (AbortTest)
		return;

	double	ifrc_FW_str=0,
			ifrc_FW=0;
	float	vfrc_FW=0,
			vfrc_FW_REL=0,
			bvdss_FW_str1=0,
			bvdss_FW_str2=0,
			//////////BVDSS_FW_ISTR=0,
			//////////BVDSS_FW_STR=0,
			//////////BVDSS_FW_WALK=0,
			BVD_FW_25UA=0,
			IDS_FW_25UA=0,
			vfrc_init = 0;

	float	Imeas=0.0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
//

// Instrument protection
	ovi_1->disconnect(0);
	ovi_1->disconnect(1);
	ovi_1->disconnect(2);
	ovi_1->disconnect(3);
	ovi_1->disconnect(4);
	ovi_1->disconnect(5);
	ovi_1->disconnect(6);
	ovi_1->disconnect(7);
	tmu_6->open_relay(TMU_HIZ_DUT1);			// protect TMU
	tmu_6->open_relay(TMU_HIZ_DUT2);			// protect TMU
	tmu_6->open_relay(TMU_HIZ_DUT3);			// protect TMU
	tmu_6->open_relay(TMU_HIZ_DUT4);			// protect TMU
	tmu_6->open_relay(TMU_CHAN_A_DUT1);			// protect TMU
	tmu_6->open_relay(TMU_CHAN_A_DUT2);			// protect TMU
	tmu_6->open_relay(TMU_CHAN_B_DUT1);			// protect TMU
	tmu_6->open_relay(TMU_CHAN_B_DUT2);			// protect TMU

/*****************************************************************************
 *						150V Device on FW pin BVD							 *
 * NOTE1: FW BVD leakage needs to be measured outside of test mode. The only *
 *        way to power up the device outside of test mode is to provide 3    *
 *        negative pulses to FW pin during and after BPS power up.			 *
 * NOTE2: FB has to be above FB threahold for the power up to happen properly*
 *        After the power up. FB is either connected to the OVI or DDD thru  *
 *        LB relay. Leave FB pin connected to OVI and disconnect OVI channel *
 *        from the instrument to avoid high voltage glitch to damge OVI even *
 *        though the voltage is only 150V.									 *
          Disconnect DDD from FW pin for the same purpose. 					 *
 ****************************************************************************/
	// Power down HVS before connecting it to FW pin
	hvs_15->set_current(100e-6,		RANGE_1_MA);							
	hvs_15->set_voltage(0.0,		RANGE_500_V);	
	delay(2);
	Close_relay(K11); //Connect BPP to DVI-11-0
	Close_relay(K2);  //Kelvin to Drain pin.
	ovi_1->connect(REQ_ch);  //Connect OVI to FB pin for test mode later.
	delay(3);
	BPP_DVI->set_current(BPP_ch, 10e-3, 	RANGE_30_MA); 	// DVI_11_0 
	BPP_DVI->set_voltage(BPP_ch, 0.0, 		VOLT_10_RANGE); 	// DVI_11_0 
	wait.delay_10_us(10);

	//////Close FW to connect to DVI-11-1 
	////FW_dvi->set_current(FW_ch, 30e-3,		RANGE_30_MA);	
	////FW_dvi->set_voltage(FW_ch, 0.0,			VOLT_5_RANGE);		// DVI11-1
	////Close_relay(K18);			// Connect FW to DVI-11-1
	//////Open dvi-11-1 conn(force/sense) from FW
	////FW_dvi->open_relay(CONN_FORCE1);
	////FW_dvi->open_relay(CONN_SENSE1);
	////wait.delay_10_us(10);

	Close_relay(K4);			// Connect HVS to 47k resistor
	delay(3);				


	//NOT REQUIRE FOR INNO4 (Once BPS power-up, it will go into Normal mode automatically.  Vout(high)||FB(low)||FW(pulses) )
	////Close_relay(K21);			// Connect FW pin to DDD
	////ovi_1->connect(REQ_ch);
	////delay(3);

	//****************************************************************************************
	//*** FW 150V device stress condition ***
	//****************************************************************************************
	//If we go above ~170V, device will snap back to turn on SCR ESD based on Randy's input

	ifrc_FW		= 200.0e-6;		
	vfrc_FW		= 260;	// MINNO_S FW pin is 250V

	//Disconnect DDD from FW pin since this powerup doesn't require DDD connects to FW pin.
	Open_relay(K21);					// Disconnect FW pin to DDD
	delay(2);
	
	// Need to be out of test mode in order to read anti-fuses. 
	//Power_Up_Secondary(Normal_Mode_S, 5.4);	//vBPS set to Vshunt-100mV first then set to 4.8V to avoid charging path stays on
												//for devices with vBPS_vPlus > 4.8V for characterization
	Power_Up_Secondary(Normal_Mode_S, 4.55);	// Change to BPS +100mv. (4.55V) per Randy's email on 1 Aug 2018. ET

	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_5_V);	// OVI_1_2
	wait.delay_10_us(10);

	//Open_relay(K21);					// Disconnect FW pin to DDD
	mux_14->close_relay(MUX_BANK_8_1);	
	mux_14->close_relay(MUX_1_4); //Ground FB thru Mux
	mux_14->close_relay(MUX_1_2);
	delay(2);
	ovi_1->disconnect(REQ_ch);			// Disconnect OVI on FB pin to avoid damage
	delay(1);

	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);		//HVS commands takes about 1ms per instruction.
	hvs_15->close_relay(HVS_NEG_FORCE);				// NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->close_relay(HVS_SHORT_NEG_FS);	
	hvs_15->close_relay(HVS_GND_NEG_SENSE);	
	hvs_15->close_relay(HVS_SHORT_POS_FS);
	hvs_15->close_relay(HVS_FORCE_POS);				// POS_FORCE (J6,B9) to drain	
	Close_relay(K5);		
	delay(4);

    vfrc_init = 100;
	//hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
	hvs_15->set_current(ifrc_FW,			RANGE_1_MA);	
	hvs_15->set_voltage(vfrc_init,			RANGE_500_V); //added here because vfrc_FW_REL added from above
						
	wait.delay_10_us(100);

	while(vfrc_init<vfrc_FW)
	{
		hvs_15->set_voltage(vfrc_init,			RANGE_500_V);
		vfrc_init = vfrc_init + 10;
	}

	hvs_15->set_voltage(vfrc_FW,			RANGE_500_V);

	//This 10ms delay is needed.  TMT81 shows that after setting ifrc_FW, HVS ramp all the way up to 175V over ~3ms and 
	//stays for ~5ms, then HVS would drop from 175V to 155V over 500us and stays put.
	delay(15);	
	//delay(20);		// JD cold debug was 10
	
	Imeas = hvs_15->measure_average(5);// measure avalanche current
//

	hvs_15->set_meas_mode(HVS_MEASURE_VOLTAGE); 
	delay(2);							
	//** BVD_100UA
	BVD_FW_25UA = hvs_15->measure_average(5);
	BVD_FW_25UA -= Imeas * 47e3;				// subtract 47k vdrop 47.3ms
	IDS_FW_25UA = Imeas;
//
	hvs_15->set_voltage(BVD_FW_25UA-10,			RANGE_500_V); //Need to back up 10V from BV to measure leakage
	wait.delay_10_us(50);
//
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
	delay(5);	
	IDS_FW_25UA = hvs_15->measure_average(5);// measure avalanche current

	if(DEBUG==1 && gDEBUG)
	{
		printf("BVD_FW_25UA = %.2f V\n", BVD_FW_25UA);
		printf("IDS_FW_25UA = %.2f uA\n", IDS_FW_25UA*1e6);
		printf("Note that IR drop over 47kohm = %.2f V\n", IDS_FW_25UA*47e3);
	}

	// Power down and disconnect relays; BPP was powered down before FW BVD tests
	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_10_RANGE); 	wait.delay_10_us(10);	// DVI_9_1 
	hvs_15->set_voltage(0.0, RANGE_1_KV);
	delay(1);	// 10V remains
	if(g_TurretCB)
	{
		//HL added this section because of parts being damaged on the Turret due to the slow settling of the HVS.
		//Onboard relays were damaged, leading to IS damages.
		delay(10);
		hvs_15->set_voltage(0.0, RANGE_100_V);
		delay(5);	// 10V remains
	}

	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_10_RANGE); 	// DVI_9_1 
	wait.delay_10_us(30);	
//
	ovi_1->connect(0);
	ovi_1->connect(1);
	ovi_1->connect(2);
	ovi_1->connect(3);
	ovi_1->connect(4);
	ovi_1->connect(5);
	ovi_1->connect(6);
	ovi_1->connect(7);
	Open_relay(K4);			// Disconnect HVS from Drain
	Open_relay(K11);		// Disconnect BPP from DVI
	Open_relay(K5);			// Disconnect HVS from FW pin
	Open_relay(K18);		// Disconnect FW  from DVI-11-1
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
	hvs_15->open_relay(HVS_NEG_FORCE);		// NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->open_relay(HVS_SHORT_NEG_FS);	
	hvs_15->open_relay(HVS_GND_NEG_SENSE);	
	hvs_15->open_relay(HVS_SHORT_POS_FS);
	hvs_15->open_relay(HVS_FORCE_POS);		// POS_FORCE (J6,B9) to drain	
	mux_20->open_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
	mux_14->open_relay(MUX_BANK_8_1);  //HL added.	
	mux_14->open_relay(MUX_1_4);	   //Disconnect FB from GND.
	mux_14->open_relay(MUX_1_2);	   //Disconnect FB from GND.
	delay(2);
	ovi_1->disconnect(REQ_ch);			// Disconnect OVI on FB pin to avoid damage
	delay(1);
	Open_relay(K11); //Connect BPP to DVI-11-0
	Open_relay(K2);  //Kelvin to Drain pin.
	delay(2);

	hvs_15->init();	
	// Datalog
	//////////PiDatalog(func, A_BVDSS_FW_STR,		BVDSS_FW_STR,	set_fail_bin,		POWER_UNIT);		
	//////////PiDatalog(func, A_BVDSS_FW_ISTR,	BVDSS_FW_ISTR,  set_fail_bin,		POWER_MICRO);		
	//////////PiDatalog(func, A_BVDSS_FW_WALK,	BVDSS_FW_WALK,  set_fail_bin,		POWER_UNIT);		
	PiDatalog(func, A_BVD_FW_25UA,		BVD_FW_25UA,	set_fail_bin,		POWER_UNIT);		
	PiDatalog(func, A_IDS_FW_25UA,		IDS_FW_25UA,	set_fail_bin,		POWER_MICRO);	

	if(gDEBUG)
	printf("Function BV_FW Done\n");

	if(BVD_FW_25UA < 100.0)
		AbortTest = true;	//Don't continue on if BV_FW is too low

}
