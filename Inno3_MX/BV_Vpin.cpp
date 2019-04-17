//==============================================================================
// BV_Vpin.cpp (User function)
// 
//    void BV_Vpin_user_init(test_function& func)
//    void BV_Vpin(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "BV_Vpin.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void BV_Vpin_user_init(test_function& func)
{
	BV_Vpin_params *ours;
    ours = (BV_Vpin_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void BV_Vpin(test_function& func)
{
    // The two lines below must be the first two in the function.
    BV_Vpin_params *ours;
    ours = (BV_Vpin_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "Vpin_BVD";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_BV_Vpin,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	//if (AbortTest || MOSFET_SIZE==8)	//The 1st SilRev of sizex8 fail BV
	if (AbortTest)
		return;

	//if(LB_Rev >=9)//Temporarily diable this test 11/12/18-MinnoP/S
	//	return;
	
	// Disable the this Vpin BV test at HOT per PE and DE
	if (OPCODE==4300 ||OPCODE==4500)
		return;

	
	//Don't do BV_Vpin in Manual mode when collecting GRR.
	if (gManual_Handler && g_GRR)
		return;

	//Don't do BV_Vpin in RS manual test socket, arcing may occur.
	//Okay to do BV_Vpin in Turret manual test socket, no arcing observed so far. This is for debugging only, not for collecting GRR

	/*if (gManual_Handler && !g_TurretCB)
		return;
	*/

	float 	ifrc_Vpin_str  =0,
			ifrc_Vpin       =0;
	float	vfrc_Vpin      =0,
			vfrc_Vpin_REL  =0,
			bvdss_Vpin_str1=0,
			bvdss_Vpin_str2=0,
			vset            = 200,
			
			BVD_Vpin       =0,
			IDS_Vpin       =0;

	float	Imeas_750V = 0.0, Imeas_700V=0.0, Imeas_650V=0.0,Imeas_500V=0.0;



if(LB_Rev >=3||g_TurretCB)	//Only if the Vpin hardware change is in place, then do this test
{


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
	Open_relay(K4);					    //Disconnect HVS from 47k resistor
	Open_relay(K1);						 //Disconnect DVI_11_0 from Drain directly (Kelvin connection)
	Open_relay(K2);
	Open_relay(K18);
	Open_relay(K5);
	Open_relay(K4);			// Disconnect HVS from Drain
	Open_relay(K11);		// Disconnect BPP from DVI
	Open_relay(K5);			// Disconnect HVS from FW pin
	Open_relay(K18);		// Disconnect FW  from DVI-11-1
	mux_14->open_relay(MUX_BANK_8_1);	
	mux_14->open_relay(MUX_1_1);
	tmu_6->open_relay(TMU_EXT_DRV1);
	wait.delay_10_us(250);
/*****************************************************************************
 *						700V Device on Vpin pin BVD							 *
 * Procedure:
 * 1) Set D = 40V
 * 2) Set Vpin = 0V.
 * 3) Ramp BPP from 0V to 5.5V
 * 4) Then raise Vpin to 500V, 650V & 700V and measure leakage currents.
 * 5) Then clamp Vpin to 750V, force 100uA into Vpin and ensure voltage can clamp
 *    to 750V to ensure BV > 750V
 ****************************************************************************/
	

	// Power down HVS before connecting it to UV pin
	hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);		//HVS commands takes about 1ms per instruction.
	hvs_15->set_current(10e-6,	RANGE_1_MA);							
	hvs_15->set_voltage(0.0,	RANGE_1_KV);	
	wait.delay_10_us(50);

	//Close relay K5 & K18 is needed to avoid the large glitch caused by closing HVS relays to get to D, UV or FW pins.
	Close_relay(K5);
	Close_relay(K18);
	wait.delay_10_us(500);

	//Connect HVS relays.
	hvs_15->close_relay(HVS_NEG_FORCE);				// NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->close_relay(HVS_SHORT_NEG_FS);	
	hvs_15->close_relay(HVS_GND_NEG_SENSE);	
	hvs_15->close_relay(HVS_SHORT_POS_FS);
	hvs_15->close_relay(HVS_FORCE_POS);				// POS_FORCE (J6,B9) to drain	



	wait.delay_10_us(500);



	BPP_DVI->set_voltage(BPP_ch, 0.0, 		VOLT_10_RANGE); 	// DVI_11_0 
	dvi_11->set_current(DVI_CHANNEL_1, 100e-3, RANGE_300_MA);
	dvi_11->set_voltage(DVI_CHANNEL_1, 0.0, VOLT_50_RANGE);
	wait.delay_10_us(50);
	
	Open_relay(K11);                     //Use DVI_11_0 to power up D = 40V during BV test.
	
	tmu_6->close_relay(TMU_EXT_DRV1);    //Switch relay on contactor board to remove OVI from UV pin & connect HVS to UV pin.
	wait.delay_10_us(250);										 //Connect DVI_11_1 to BPP in order to ramp from 0V to 5.5V later. 

Close_relay(K4);					 //Connect HVS to 47k resistor
	wait.delay_10_us(250);		                                     //Disconnect HVS from FW & D
	
	Open_relay(K1);						 //Connect DVI_11_0 to Drain directly (Kelvin connection)
	Close_relay(K2);
	Open_relay(K18);					// Disconnect DVI_11_1 from Fw pin.
	wait.delay_10_us(500);				


	
	//if(gREL_FLOW)	//REL_FLOW and Production FLOW 
	//{
	//	ifrc_Vpin	= 100.0e-6;		
	//	ifrc_Vpin	= 100.0e-6;		
	//	vfrc_Vpin   = 750;
	//}
	//else			//CHAR FLOW over temperature
	//{
	//	ifrc_Vpin		= 100.0e-6;		
	//	vfrc_Vpin		= 750;
	//}



//
	
	//Set D = 40V / 100mA
	dvi_11->set_current(DVI_CHANNEL_0, 100e-3, RANGE_300_MA);
	dvi_11->set_voltage(DVI_CHANNEL_0, 40, VOLT_50_RANGE);
	wait.delay_10_us(100);

	//HL moved to the Vpin = 0V here before powering up BPP voltage.
	//Keep Vpin = 0V
	hvs_15->set_current(100e-6,	RANGE_1_MA);
	hvs_15->set_voltage(0,		RANGE_1_KV); 
	wait.delay_10_us(100);

	//Ramp VBPP from 0V to 5.5V (DVI_11_1)
	//Bpp set 5.5V for 100us
	float j = 0;
	while(j<=5.5)
	{
		dvi_11->set_voltage(DVI_CHANNEL_1, j, VOLT_10_RANGE);
		j=j+0.1;
		wait.delay_10_us(5);
	}
	wait.delay_10_us(50);

	//Note: Vpin_BV could cause arcing since Vpin is too close to BPP.  Just be aware.
	if (OPCODE==4300 || OPCODE==4500)
	{
		ifrc_Vpin	= 100.0e-6;		
		vset		= 700;
	}
	else
	{
		ifrc_Vpin	= 100.0e-6;		
//		vset		= 730;
		vset		= 710;	// Changed to 710V per PE and DE.  12/20/16 HQL
	}

	//Keep Vpin = 0V
	//hvs_15->set_current(100e-6,	RANGE_1_MA);
	//hvs_15->set_voltage(0,		RANGE_1_KV); 
	//wait.delay_10_us(50);

	hvs_15->set_current(ifrc_Vpin,	RANGE_1_MA);
	hvs_15->set_voltage(vset,		RANGE_1_KV); 
	wait.delay_10_us(1500); //NEED 15MS 
	Imeas_750V = hvs_15->measure_average(25);	

	hvs_15->set_meas_mode(HVS_MEASURE_VOLTAGE); 
	wait.delay_10_us(500);							
	//** BVD_100UA
	BVD_Vpin = hvs_15->measure_average(25);
	BVD_Vpin -= Imeas_750V * 47e3;						// subtract 47k vdrop 

	if(BVD_Vpin >= 650)
	{

			//HL made changes to keep Vpin testing at 700V, 650V & 500V as DE requested in the beginning.
			hvs_15->set_meas_mode(HVS_MEASURE_CURRENT);
			hvs_15->set_current(ifrc_Vpin,	RANGE_1_MA);
			hvs_15->set_voltage(700,		RANGE_1_KV); 
			wait.delay_10_us(500);
			Imeas_700V = hvs_15->measure_average(25);		

			hvs_15->set_current(ifrc_Vpin,	RANGE_1_MA);
			hvs_15->set_voltage(650,		RANGE_1_KV); 
			wait.delay_10_us(500);
			Imeas_650V = hvs_15->measure_average(25);		

			hvs_15->set_current(ifrc_Vpin,	RANGE_1_MA);
			hvs_15->set_voltage(500,		RANGE_1_KV); 
			wait.delay_10_us(500);
			Imeas_500V = hvs_15->measure_average(25);	
		
	}

	hvs_15->set_current(ifrc_Vpin,	RANGE_1_MA);
	hvs_15->set_voltage(40,			RANGE_1_KV); 
	wait.delay_10_us(50);

	hvs_15->set_current(ifrc_Vpin,	RANGE_1_MA);
	hvs_15->set_voltage(10,			RANGE_1_KV); 
	wait.delay_10_us(50);

	hvs_15->set_current(ifrc_Vpin,	RANGE_1_MA);
	hvs_15->set_voltage(5,			RANGE_1_KV); 
	wait.delay_10_us(50);

	hvs_15->set_current(ifrc_Vpin,	RANGE_1_MA);
	hvs_15->set_voltage(0,			RANGE_1_KV); 
	wait.delay_10_us(50);


	//Ramp VBPP from 5.5V to 0V
	j=5.5;
	while(j>=0)
	{
		dvi_11->set_voltage(DVI_CHANNEL_1, j, VOLT_10_RANGE);
		j=j-0.1;	
	}
	wait.delay_10_us(50);


	//Set D = 00V / 100mA

	dvi_11->set_voltage(DVI_CHANNEL_0, 0, VOLT_50_RANGE);
	wait.delay_10_us(50);

	tmu_6->open_relay(TMU_EXT_DRV1);    //Turn relay off on contactor board to reconnect OVI to UV pin & disconnect HVS from UV pin.
										//Disconnect DVI_11_1 from BPP.
	                                    //Reconnect HVS to either D or FWf.
	Open_relay(K4);					    //Disconnect HVS from 47k resistor
	Open_relay(K1);						 //Disconnect DVI_11_0 from Drain directly (Kelvin connection)
	Open_relay(K2);
	Open_relay(K18);
	Open_relay(K5);
	
//////////////////////////////////////////////////////////////////////////////////////////


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
	hvs_15->open_relay(HVS_NEG_FORCE);		// NEG_FORCE (J6,B3)  hardwired to gnd 
	hvs_15->open_relay(HVS_SHORT_NEG_FS);	
	hvs_15->open_relay(HVS_GND_NEG_SENSE);	
	hvs_15->open_relay(HVS_SHORT_POS_FS);
	hvs_15->open_relay(HVS_FORCE_POS);		// POS_FORCE (J6,B9) to drain	
	delay(2);
	Open_All_Relays();

	hvs_15->init();	
	// Datalog
	PiDatalog(func, A_BVD_Vpin,			BVD_Vpin,	set_fail_bin,		POWER_UNIT);		
	PiDatalog(func, A_IDS_750V_Vpin,	Imeas_750V,  set_fail_bin,		POWER_MICRO);		
	PiDatalog(func, A_IDS_700V_Vpin,	Imeas_700V,  set_fail_bin,		POWER_MICRO);		
	PiDatalog(func, A_IDS_650V_Vpin,	Imeas_650V,	set_fail_bin,		POWER_MICRO);		
	PiDatalog(func, A_IDS_500V_Vpin,	Imeas_500V,	set_fail_bin,		POWER_MICRO);	

	if(DEBUG==1)
	printf("Function BV_Vpin Done\n");

	if(BVD_Vpin < 450.0)
		AbortTest = true;	//Don't continue on if BV_FW is too low

}



}
