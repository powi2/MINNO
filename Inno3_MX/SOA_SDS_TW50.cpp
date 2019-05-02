//==============================================================================
// SOA_SDS_TW50.cpp (User function)
// 
//    void SOA_SDS_TW50_user_init(test_function& func)
//    void SOA_SDS_TW50(test_function& func)
//
//==============================================================================

#include "asl.h"
// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

#include "SOA_SDS_TW50.h"

// !!!! User #includes and externs can be placed between the comments
// !!!!

// *************************************************************************

void SOA_SDS_TW50_user_init(test_function& func)
{
	SOA_SDS_TW50_params *ours;
    ours = (SOA_SDS_TW50_params *)func.params;

// !!!! User initialization code below this comment (do not remove comment)

// !!!! User initialization code above this comment (do not remove comment)
}

// *************************************************************************

void SOA_SDS_TW50(test_function& func)
{
    // The two lines below must be the first two in the function.
    SOA_SDS_TW50_params *ours;
    ours = (SOA_SDS_TW50_params *)func.params;

	int set_fail_bin = ours->fail_bin;

	Func_name = "SOA_SDS_TW50";
	gFuncNum++;
	if(gDisplay_FuncNum)
		PiDatalog(func, A_Func_Num_SOA_SDS_TW50,		gFuncNum,		set_fail_bin,	POWER_UNIT);

	//Skip Test if AbortTest set 
	if (AbortTest)
		return;

	//standard pulse
	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//wide pulse
	Pulse pulse2(PULSE_RISING_EDGE,50e-6);			//external trigger pulse from dvi for debug
//pulse.do_pulse();
	//Find_SOA_SDS_vs_Voltage();	// For debug only

	float	SOA_S		=0.0,
			TW50_S		=0.0,
			SOA_P		=0.0,
			TW50_P		=0.0,
			SDS_P		=0.0,
			TW50_SDS_P	=0.0,
			SDS_S		=0.0,
			TW50_SDS_S	=0.0,
			SDS_P_sw	=0.0,	//Only for REL_Flow
			SDS_S_sw	=0.0,	//Only for REL_Flow
			SDS_P_nsw	=0.0,
			SDS_S_nsw	=0.0;

	float tARoffShort_P = 0;

	float   PV3_Charge =0.0;

	int	    lcnt  =0,
			Rep_cnt=0;
	float   Vpv3_meas =0.0;
	float   vSOA =0.0, 
			vSOA_P =0.0,
			vSDS =0.0,
			vSDS_P =0.0,
			Vref_cmp=0.0,
			tmu_trig;
	float	tmeas=0.0, vsync_set = 0.0;
	int count = 0;
	int MaxCount = 0;
	int FlagError = 0;

	float	vTrig_Start	=0.0,
			vTrig_Stop	=0.0;
	float vfrc=0.0, vstep=0.0;
	int		SR_AF_temp[100]={0};

	////if(OPCODE==4200 || OPCODE==4250 || OPCODE==4501)
	////{
	////	vSOA	= VSOA_RM;
	////	vSOA_P	= VSOA_RM_P;
	////	vSDS	= VSDS_RM;
	////}
	////else
	////{
	////	vSOA	= VSOA_HT;
	////	vSOA_P	= VSOA_HT_P;
	////	vSDS	= VSDS_HT;
	////}


/*****************************************************************************************
SDS test: (diode short) 
	Resistive/inductive pull-up provided by wire-wound resistor
	Higher pull-up voltage will cause drain pulse width to be very small (<180ns)
	DUT will detect short pulse width and enter SDS mode
	Test is done twice, once with primary in control, once with secondary in control
	Primary in control, SOA mode puts out two pulses approx. 115us apart
	Secondary in control, 	SDS mode is two pulses, short gap, one pulse, 200ms gap

SOA test: (safe operating area)
	Resistive/inductive pull-up provided by wire-wound resistor
	Slightly lower pull-up voltage will cause drain pulse width to be short (<320ns) but longer than SDS pulse (>180ns)
	DUT will detect intermediate short pulse width and enter SOA mode
	Test is done twice, once with primary in control, once with secondary in control
	Primary in control, SOA mode puts out a single pulse approx. every 115us
	Secondary in control, SOA mode repeats this sequence: pulse, 8us gap, pulse, 35us gap

*****************************************************************************************/

	Power_Down_Everything();
		Open_All_Relays();
		Disconnect_InvSyn_IM();
		delay(2);
	if(g_TurretCB)
	{
		//Disconnect_InvSyn_IM();
		Power_Down_Everything();
		Open_All_Relays();
		Disconnect_InvSyn_IM();
		delay(2);
	}


	if (MOSFET_SIZE == 8)
	{
		if(LB_Rev>=8)	{
							vSOA		= 27.0;	//search starting point, MINNO ILIM=2400
							tmu_trig	= 10.0;	//lset for clean triggering 
						}
		else            {
							vSOA = 18.0;		//search starting point
							tmu_trig	= 5.0;	//set for clean triggering
						}
		
	}
	else if (MOSFET_SIZE == 7)
	{
		vSOA		= 20.0;	//search starting point
		tmu_trig	= 10.0;	//set for clean triggering
		//vSDS = 22.5;		//no longer used
	}
	else if (MOSFET_SIZE == 6)
	{
		vSOA = 30.0;		//search starting point
		tmu_trig	= 10.0;	//set for clean triggering
		//vSDS = 22.0;		//no longer used	//updated from 19.5 to 22V to pass SDS-S  cx. 11/7/2016
	}
	else if (MOSFET_SIZE == 5)	//MINNO ILIM = 1150mA
	{
		vSOA = 19.0;		//search starting point
		if(g_TurretCB)
		{
			tmu_trig	= 5.0;	//set for clean triggering. Used to be 5.

		}
		else
		{
			tmu_trig	= 10.0;	//set for clean triggering. Used to be 5.
		}
	}
	//else if (MOSFET_SIZE == 5)	//CP family and ILIM = 950mA
	//{
	//	
	//	vSOA = 9.0;			//search starting point	
	//	
	//	if(g_TurretCB)
	//	{
	//		tmu_trig	= 5.0;	//set for clean triggering. Used to be 5.
	//	}
	//	else
	//	{
	//		tmu_trig	= 5.0;	//set for clean triggering. Used to be 5.
	//	}
	//}
	else if (MOSFET_SIZE == 4)
	{
		vSOA = 7.0;			//search starting point
		tmu_trig	= 4.0;	//lset for clean triggering
		//vSDS = 8.0;		//no longer used
	}
	else if (MOSFET_SIZE == 3)
	{
		vSOA = 4.5;			//search starting point
		tmu_trig	= 4.0;	//set for clean triggering
		//vSDS = 5.25;		//no longer used
	}
	else if (MOSFET_SIZE == 2)
	{
		vSOA = 6.0;			//search starting point
		tmu_trig	= 6.0;	//set for clean triggering
		//vSDS = 8.0;		//no longer used
	}
	SAMPLE_SIZE = GAGE_POST_64K;
	INNO_Gage_ChanAB_setup(0.15);	// Only do it when SAMPLE_SIZE is diff from previous. 

	if(LB_Rev >= 9)	
	{
		if(gSiliconRev_P>=3)
		{
			Close_relay(K37);				//Connect 1uF to BPP pin via Mux_20_1_2
			//mux_20->close_relay(MUX_1_2);	//Connect 1uF to BPP pin via Mux_20_1_2
			delay(3);
		}
	}
	
	//tmu_6->init();
	PV3_Charge_On(RANGE_100_V);	//Prepare PV3 before power-up
	PV3_Check_Charge(RANGE_100_V);  //Note: Once Charge Off, V start dropping due to discharge over time
	pv3_4->close_switch(PV3_LOW_FORCE_2);
	pv3_4->close_switch(PV3_LOW_SENSE_2);
	pv3_4->close_switch(PV3_HIGH_FORCE_3);
	pv3_4->close_switch(PV3_HIGH_SENSE_3);
	wait.delay_10_us(250);
	pv3_4->set_meas_mode(PV3_MEASURE_VOLTAGE);		
	// Force 5V below normal VSOA and search up for the right VSOA. Some devices require lower VSOA while some require higher.
	
	if (vSOA>8)		
		pv3_4->set_voltage(vSOA-5, RANGE_100_V);	//Size3(6V), Size7(15V)
	else	
		pv3_4->set_voltage(vSOA-2, RANGE_100_V);	//Size3(6V), Size7(15V)	
	
	//pv3_4->set_voltage(4.0, RANGE_100_V);	//Size3(6V), Size7(15V)
	pv3_4->set_current(10.0);
	wait.delay_10_us(20);	// Skip the first few pulses
	pv3_4->charge_off();

	tmu_6->close_relay(TMU_HIZ_DUT2); // Connect TMU HIZ to Drain //

	//measure pulse spacing, rising edge to rising edge
	tmu_6->start_trigger_setup( tmu_trig   , POS_SLOPE, TMU_HIZ, TMU_IN_100V);	// cx 11/10/16
	tmu_6->stop_trigger_setup( tmu_trig-0.5,	POS_SLOPE, TMU_HIZ, TMU_IN_100V);	// cx 11/10/16
	tmu_6->start_holdoff(0,FALSE);  
	tmu_6->stop_holdoff(0,FALSE);
	delay(5);
//*************************************************************************************************************
//**********  SOA-P  &  SDS-P  ********************************************************************************
//*************************************************************************************************************
		//Information:
	//	- SOA pullup resistance
	//		* 5ohm (Require hardware modification)

	//Rep_cnt = 1;
	//while( (SDS_S<10e-6 || SDS_S>45e-6) && Rep_cnt <=2)	//repeatability issue (take care of it later)
	//{

		Close_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
		delay(4);// 
		/*ovi_1->disconnect(OVI_CHANNEL_1);	
		delay(1);*/
		// Initialize DDD
		//ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
		//ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
		//delay(1);
		//
		////Strange, same pattern at different location, causing FW to drop below GND.
		////ddd_7->ddd_run_pattern(Low_FW_pat_start,	Low_FW_pat_stop);
		//ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);
		//wait.delay_10_us(10);
		//Close_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
		//delay(4);

		//VBPP_Negative_Cycle();
		//delay(2);

		if(g_TurretCB)
		{
			SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
			SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);	// DVI_21_1
			delay(2);
			mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
			delay(2);

		}

		Power_Up_Primary_BypassWL_TM5(ILIM_NORM) ;
		delay(1);
		D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
		delay(1);
		Open_relay(K3);		// Disconnect Drain from DVI
		delay(5);
	// Turn off the switching of device before connecting PV3 to drain to avoid the hot switching.
		if(g_TurretCB)
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-200e-3, RANGE_10_V);
		}
		else
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-50e-3, RANGE_10_V);
		}
		wait.delay_10_us(20);
		if(gSiliconRev_P>=3)
		{
			BPP_ovi->set_current(BPP_ch, 10e-3,	RANGE_30_MA);	// This current clamp is needed to avoid Drain charging BPP which could cause the BPP/Drain is switching.
			wait.delay_10_us(10);
		}
		Close_relay(K9);	//Drain to CT2+						//mux-5-1
		Close_relay(K7);	//CT2+	to 2ohm pull-up by PVI		//mux-4-3
		delay(4);
		//turn on PV3
		//pv3_4->drive_on(); 
 		//delay(5);
	
	    if(gSiliconRev_P>=3)
		{
			BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
			VBPP_ramp_up(gVBPP_M_Init-50e-3, gVBPP_P_final, 10e-3);			//B3 material
			wait.delay_10_us(10);
		}
		else
		{  
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_final, RANGE_10_V);		
		}
		if(g_TurretCB)
		{
			wait.delay_10_us(100); //HL Turret CB requires a bit more settling time.
		}
		else
		{
			wait.delay_10_us(10);
		}

		
		////tmu_6->arm();	
		////wait.delay_10_us(6);
		////tmeas = tmu_6->read(100e-9);
		// Force 5V below normal VSOA and search up for the right VSOA. 
		// Some devices require lower VSOA while some require higher.

		if (vSOA>8)
		{
			if(MOSFET_SIZE == 8)	vfrc = vSOA-6;//MINNO 2400 ILIM
			else					vfrc = vSOA-4;
			
			//setup vstep
			if(MOSFET_SIZE == 2)	vstep = 0.1;	//increase vSOA search time from ~30ms to 60ms.  (vSDS is only 200mV higher than vSOA)
			else					vstep = 0.2;
		}
		else
		{
			vfrc = vSOA-2;
			vstep = 0.2;
		}



		/*if (g_TurretCB&&MOSFET_SIZE == 5)
		{
			vfrc = vSOA-2;
		}
		else
		{
			if (vSOA>8)
				vfrc = vSOA-2;
			else
				vfrc = vSOA-2;
		}*/

		//HL moved turn on PV3 here.
		//turn on PV3



		pv3_4->drive_on(); 
	
		//if(g_TurretCB)
		//{
		//	vstep = 0.2;  //HL changed step to 0.5V

		//}
		//else
		//{
		//	vstep = 0.2;  //HL changed step to 0.5V
		//}
		tmeas = 0.0;
		//DEBUG=1;
		if (DEBUG && gDEBUG)
			printf("  vSOA = %fV, tmeas = %.1fns \n", vfrc, tmeas*1e9);

		if (!strnicmp( DevName, "LYT6063C", 7 ) ||
		!strnicmp( DevName, "LYT6065C", 7 ) ||
		!strnicmp( DevName, "LYT6067C", 7 ) ||
		!strnicmp( DevName, "LYT6068C", 7 ) 	)
	{

		count = 0;	// JD count added to get out of vSOA grey area (normal and SOA mode alternately)
		while (vfrc<25 && tmeas<90e-6 && count<3)	//
		//while (vfrc<12)	//
		{
			vfrc+=vstep;	//increase pull-up voltage
			if(!g_TurretCB)
			{
				// Adjusting the tmu trigger for a more robust capture of tmeas from TMU
				//tmu_6->start_trigger_setup( (vfrc+3)   , POS_SLOPE, TMU_HIZ, TMU_IN_100V);
				//tmu_6->stop_trigger_setup( (vfrc+3)-1.0,	POS_SLOPE, TMU_HIZ, TMU_IN_100V);
			}
			pv3_4->set_voltage(vfrc, RANGE_100_V);	//Size3(6V), Size7(15V)

			//PV3 in use, do not pause here
			wait.delay_10_us(10);
//
			tmu_6->arm();	
			wait.delay_10_us(30);
			tmeas = tmu_6->read(100e-9);

			//if(tmeas > 90e-6&&(OPCODE==4300 || OPCODE==4500))
			if(tmeas > 90e-6)
			{
				count += 1;
				if(OPCODE==4300 || OPCODE==4500)
				{
//					pv3_4->set_voltage((vfrc+3*vstep), RANGE_100_V);	//Size3(6V), Size7(15V)
					pv3_4->set_voltage((vfrc+2*vstep), RANGE_100_V);	//Size3(6V), Size7(15V)
				}
				else
				{
					pv3_4->set_voltage((vfrc+vstep), RANGE_100_V);	//Size3(6V), Size7(15V)

				}
				wait.delay_10_us(10);
			}

			if (DEBUG && gDEBUG)
				printf("  vSOA = %fV, tmeas = %.1fus \n", vfrc, tmeas*1e6);
		}
	}
	else
	{
		while (vfrc<40 && tmeas<90e-6)	//
		//while (vfrc<12)	//
		{
			vfrc+=vstep;	//increase pull-up voltage
			if(g_TurretCB)
			{
				// Adjusting the tmu trigger for a more robust capture of tmeas from TMU
				tmu_6->start_trigger_setup( (vfrc-1)   , POS_SLOPE, TMU_HIZ, TMU_IN_100V);
				tmu_6->stop_trigger_setup( (vfrc-1)-3.0,	POS_SLOPE, TMU_HIZ, TMU_IN_100V);
			}
		
			pv3_4->set_voltage(vfrc, RANGE_100_V);	//Size3(6V), Size7(15V)

			//PV3 in use, do not pause here
			wait.delay_10_us(10);
//
			tmu_6->arm();	
			wait.delay_10_us(30);
			tmeas = tmu_6->read(100e-9);

			//cx add an extra measurement to make sure we are out of the grey area between SOA/SDS
				tmu_6->arm();	
				wait.delay_10_us(30);
				tmeas += tmu_6->read(100e-9);
				//tmeas = tmeas/2.0;
			//cx add an extra measurement to make sure we are out of the grey area between SOA/SDS
				tmu_6->arm();	
				wait.delay_10_us(30);
				tmeas += tmu_6->read(100e-9);
				tmeas = tmeas/3.0;

			//if(tmeas > 90e-6&&(OPCODE==4300 || OPCODE==4500))
			if(tmeas > 90e-6)
			{
				if(OPCODE==4300 || OPCODE==4500)
				{
//					pv3_4->set_voltage((vfrc+3*vstep), RANGE_100_V);	//Size3(6V), Size7(15V)
					pv3_4->set_voltage((vfrc+vstep), RANGE_100_V);	//Size3(6V), Size7(15V)
					wait.delay_10_us(50);
					
				}
				else
				{
					if(MOSFET_SIZE == 4)	pv3_4->set_voltage((vfrc),   RANGE_100_V);	
					if(MOSFET_SIZE == 2)	pv3_4->set_voltage((vfrc+vstep),   RANGE_100_V);	
					else					pv3_4->set_voltage((vfrc+vstep),   RANGE_100_V);	//Size3(6V), Size7(15V)

				}
				wait.delay_10_us(10);
			}

			if (DEBUG && gDEBUG)
				printf("  vSOA = %fV, tmeas = %.1fus \n", vfrc, tmeas*1e6);
		}
	}
	
		if (DEBUG && gDEBUG)
		{
			if(tmeas<90e-6)printf("  vSOA loop fails, tmeas = %.1fns \n",  tmeas*1e9);
		}
		//printf(" END \n");
		//Save search result for later use

		vSOA = vfrc;

		//Debug only start
					//pv3_4->set_voltage((vfrc+2*vstep), RANGE_100_V);	//Size3(6V), Size7(15V)
					//wait.delay_10_us(10);
		//Debug only end

		if(g_TurretCB)
		{
			if		(MOSFET_SIZE == 2)	vSDS = vSOA+5; 
			else if	(MOSFET_SIZE == 3)	vSDS = vSOA+6; 
			else if	(MOSFET_SIZE == 4)	vSDS = vSOA+5; 
			else if	(MOSFET_SIZE == 5)	vSDS = vSOA+5; 
			else if (MOSFET_SIZE == 6)	vSDS = vSOA+5;	
			else if (MOSFET_SIZE == 7)	vSDS = vSOA+5;	
			else if (MOSFET_SIZE == 8)	vSDS = vSOA+5; 
			else						vSDS = 5;	
		}
		else
		{
			if(LB_Rev>=8)
			{
				if(OPCODE==4300 || OPCODE==4500) 
				{
					if		(MOSFET_SIZE == 2)	vSDS = vSOA+8;	
					else if (MOSFET_SIZE == 3)	vSDS = vSOA+8;	
					else if (MOSFET_SIZE == 4)	vSDS = vSOA+8;	
					else if	(MOSFET_SIZE == 5)	vSDS = vSOA+8; 
					else if (MOSFET_SIZE == 6)	vSDS = vSOA+12;
					else if (MOSFET_SIZE == 7)	vSDS = vSOA+14; 
					else if (MOSFET_SIZE == 8)	vSDS = vSOA+16; 
					else						vSDS = 5;	
				}
				else
				{
					if		(MOSFET_SIZE == 2)	vSDS = vSOA+6;	
					else if (MOSFET_SIZE == 3)	vSDS = vSOA+6;	
					else if (MOSFET_SIZE == 4)	vSDS = vSOA+5;	
					else if	(MOSFET_SIZE == 5)	vSDS = vSOA+5; 
					else if (MOSFET_SIZE == 6)	vSDS = vSOA+10;	
					else if (MOSFET_SIZE == 7)	vSDS = vSOA+10; 
					else if (MOSFET_SIZE == 8)	vSDS = vSOA+10; 
					else						vSDS = 5;	
				}
			}
			else	//LB_Rev 7 or older
			{
				if(OPCODE==4300 || OPCODE==4500) 
				{
					if		(MOSFET_SIZE == 2)	vSDS = vSOA+8;	
					else if (MOSFET_SIZE == 3)	vSDS = vSOA+8;	
					else if (MOSFET_SIZE == 4)	vSDS = vSOA+8;	
					else if	(MOSFET_SIZE == 5)	vSDS = vSOA+8; 
					else if (MOSFET_SIZE == 6)	vSDS = vSOA+12;
					else if (MOSFET_SIZE == 7)	vSDS = vSOA+14; 
					else if (MOSFET_SIZE == 8)	vSDS = vSOA+16; 
					else						vSDS = 5;	
				}
				else
				{
					if		(MOSFET_SIZE == 2)	vSDS = vSOA+6;	
					else if (MOSFET_SIZE == 3)	vSDS = vSOA+6;	
					else if (MOSFET_SIZE == 4)	vSDS = vSOA+5;	
					else if	(MOSFET_SIZE == 5)	vSDS = vSOA+5; 
					else if (MOSFET_SIZE == 6)	vSDS = vSOA+12;	
					else if (MOSFET_SIZE == 7)	vSDS = vSOA+10; 
					else if (MOSFET_SIZE == 8)	vSDS = vSOA+10; 
					else						vSDS = 5;	
				}
			}


		}

		
	
		//DEBUG=0;
		if (DEBUG && gDEBUG)
			printf("  SOA_SDS: Primary search final voltages: vSOA = %.1fV, vSDS = %.1fV \n", vSOA,vSDS);
		if (DEBUG && gDEBUG) 
			pulse2.do_pulse();		//Wide pulse
		DEBUG=0;

		//** SOA_P **
		//device switching, 
		//** start SOA_P capture **
		Gage_Start_Capture( );	

		Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set

		// HL turned off switching before PV3 drive-off.
		// Turn off the switching of device before SDS test
		 if(g_TurretCB)
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-100e-3, RANGE_10_V);
		}
		else
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-50e-3, RANGE_10_V);
		}
	
		// Turn off gage
		pv3_4->drive_off(); 
 		delay(1);
		pv3_4->set_voltage(0.0, RANGE_100_V);
		pv3_4->set_current(0.0);
		pv3_4->charge_on();
		delay(5);
		// Turn off the switching
	 //  /* if(g_TurretCB)
		//{
		//	ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-100e-3, RANGE_10_V);
		//}
		//else
		//{
		//	ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-50e-3, RANGE_10_V);
		//}*/
		//HL changed from 10mA to 5mA due to a SDS-P repeatability failure seen on TMT92. 06/13/17
		if(gSiliconRev_P>=3)
			BPP_ovi->set_current(BPP_ch, 10e-3,	RANGE_30_MA);	// This current clamp is needed to avoid Drain charging BPP which could cause the BPP/Drain is switching.														// Primary should not switch with BPP at VBPP_M - 50m	
		
		wait.delay_10_us(50);
		pv3_4->charge_off();
		delay(5);
		//Process capture
		//DEBUG=1;
		//gDEBUG = 1;
		WAVE_NAME =  "SOA_TW50_P";
		Gage_Find_SOA(&SOA_P, &TW50_P);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing

		//DEBUG=0;
		//gDEBUG = 0;
		// Setting voltage for SDS test
		if(vSDS > 49.5)
		{
			vSDS = 49.0;
		}
		//pv3_4->set_voltage(vSDS+5, RANGE_100_V);	//Size3(6V), Size7(15V)
		pv3_4->set_voltage(vSDS, RANGE_100_V);	
		pv3_4->set_current(10.0);
		pv3_4->drive_on();	
		delay(5);
		//DEBUG=1;
		if (DEBUG && gDEBUG) 
			pulse2.do_pulse();		//Wide pulse
		//DEBUG=0;
		//** start SDS_P capture **
		Gage_Start_Capture( );	

		if(gSiliconRev_P>=3)
			BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);	// This current clamp is needed to avoid Drain charging BPP which could cause the BPP/Drain is switching.														// Primary should not switch with BPP at VBPP_M - 50m	
	// Turn device back on...
	
		if(g_TurretCB)
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_final, RANGE_10_V);
			wait.delay_10_us(20); //HL Turret CB requires a bit more settling time.
		}
		else
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_final, RANGE_10_V);
			wait.delay_10_us(10);
		}
		
		Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set
		// Turn off gage
		
		pv3_4->drive_off();	
		if(g_TurretCB)
		{
			ovi_1->set_voltage(OVI_CHANNEL_0, 1, RANGE_10_V);
		}
		wait.delay_10_us(100);	// Tc test, delat not critical
		/*pv3_4->set_voltage(0.0, RANGE_100_V);
		pv3_4->set_current(0.0);
		pv3_4->charge_on();
		wait.delay_10_us(500);*/
		//Process capture
		//DEBUG=1;
		WAVE_NAME =  "SDS_TW50_P";
		Gage_Find_SDS(&SDS_P, &TW50_SDS_P, &SDS_P_nsw);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing
		//DEBUG=0;
		pv3_4->set_voltage(0.0, RANGE_100_V);
		pv3_4->set_current(0.0);
		pv3_4->charge_on();
		wait.delay_10_us(500);

		/*if(SDS_P_nsw>0 && gTrim_SDS_OFF_P)
			SDS_P_sw = 1;*/
		if(SDS_P_nsw==1)	SDS_P_sw=0;
		else				SDS_P_sw=1;

		//Power Down
		ovi_1->connect(OVI_CHANNEL_1);	
		wait.delay_10_us(100); 
		// Initialize DDD
		ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(0.0);		// Will immediately change to this level upon execution
		delay(1);
		D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
		Power_Down_Primary();
		Power_Down_Everything();
		Open_All_Relays();
		//tmu_6->open_relay(TMU_HIZ_DUT2); // Connect TMU HIZ to Drain //
		wait.delay_10_us(100);

		if(SOA_P > 990.0)
			SOA_P/=1e6;			// For datalog purpose
		if(TW50_P > 990.0)
			TW50_P/=1e6;		// For datalog purpose
		if(SDS_P > 990.0)
			SDS_P/=1e6;			// For datalog purpose
		if(TW50_SDS_P > 990.0)
			TW50_SDS_P/=1e6;		// For datalog purpose

		//*************************************************************************************************************
		//****  Secondary: SOA-S & SDS-S ***********************************************************************************
		//*************************************************************************************************************


		//if(OPCODE==4300 || OPCODE==4500) 
		//{	//HL added this condition for hot (SC1546 hot fix)
		//	pv3_4->set_voltage(vSOA-0.3, RANGE_100_V);	//Size3(6V), Size7(15V)
		//}
		//else
		//{
		//	if(g_TurretCB)
		//	{
		//		pv3_4->set_voltage(vSOA, RANGE_100_V);	//Size3(6V), Size7(15V)
		//	}
		//	else
		//	{
		//		pv3_4->set_voltage(vSOA, RANGE_100_V);	//Size3(6V), Size7(15V)

		//	}
		//}
		pv3_4->set_voltage(vSOA, RANGE_100_V);	//Size3(6V), Size7(15V)
		pv3_4->set_current(10.0);
		wait.delay_10_us(20);	// Skip the first few pulses
		pv3_4->charge_off();
		wait.delay_10_us(500);
		Close_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
		delay(4);



		VBPP_Negative_Cycle();
		//// Setting up Vpin for TM5 power up.
		//ovi_1->disconnect(OVI_CHANNEL_1);
		//wait.delay_10_us(100); 
		//// Initialize DDD
		//ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
		//ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
		//delay(1);
		//ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		//wait.delay_10_us(10);
		//Close_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
		//delay(5);
	
		Power_Up_Primary_BypassWL_TM5(ILIM_NORM) ;

		if(g_TurretCB)
		{
			
			dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
			wait.delay_10_us(50);
		}
	////Bring Vpin OVI back
	//	ovi_1->connect(OVI_CHANNEL_1);	
	//	wait.delay_10_us(20);
	//	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);  
	//	VPIN_ovi->set_current(VPIN_ch, 1e-3,		RANGE_30_MA);  
	//	wait.delay_10_us(50);
	//	Open_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
	//	delay(1);

#define PU_2ndary_Prog_AF_REG
#ifndef PU_2ndary_Prog_AF_REG
		Power_Up_Secondary(Normal_Mode_S, gVBPS_final);
		Open_relay(K18);
		wait.delay_10_us(50);
		Connect_InvSyn_IM(Low_Vd_Input);

		if(g_TurretCB && MOSFET_SIZE == 5)
		{
			vsync_set = 4.0;
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, vsync_set + g_Voffset,	VOLT_20_RANGE);	// OVI_1_4	3.3 @ room.
		}
		else if (MOSFET_SIZE == 5)	//HL Inv requires 3.75V at hot.  
		{		
			vsync_set = 3.0;
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, vsync_set + g_Voffset,		VOLT_20_RANGE);	// OVI_1_4			
		}
		else
		{
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.5,		VOLT_20_RANGE);	// OVI_1_4			
		}


		//if(gSiliconRev_P>=3&&!g_TurretCB)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
		if(gSiliconRev_P>=3)	
		{
			BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final+0.2, RANGE_10_V);
			wait.delay_10_us(10);
		}
		if(gTrim_AR_S==2)
		{
			REQ_ovi->set_voltage(REQ_ch, gCVth_5pct_Lower, 	RANGE_2_V);	// OVI_1_2
			wait.delay_10_us(100);
		}

		if(g_TurretCB)
			REQ_ovi->set_voltage(REQ_ch, gCVth_8pct_Higher,		RANGE_2_V);	//HL dropped FB by 50mV to prevent DUT from being latched up on Turret CB
		else
			REQ_ovi->set_voltage(REQ_ch, 0.9,		RANGE_2_V);	// OVI_1_2

		wait.delay_10_us(50);

		Open_relay(K3);		//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0
		delay(4);	
		Close_relay(K7);	//CT2+	to 2ohm pull-up by PVI		//mux-4-3
		Close_relay(K9);	//Drain to CT2+						//mux-5-1
		delay(4);
	
		//////////turn on PV3
		////////pv3_4->drive_on(); 
		////////delay(5);

		//////////** SOA_S **

		//////////DEBUG=1;
		////////if (DEBUG && gDEBUG) 
		////////			//pulse
		////////DEBUG=0;

		//////////** start SOA_S capture **
		////////Gage_Start_Capture( );	

		////////if(gTrim_AR_S==2)
		////////{
		////////	REQ_ovi->set_voltage(REQ_ch, gCVth_5pct_Lower, 	RANGE_2_V);	// OVI_1_2
		////////	wait.delay_10_us(100);
		////////}
		////////else
		////////{
		////////	REQ_ovi->set_voltage(REQ_ch, gCV_Low, 	RANGE_2_V);	// OVI_1_2 (Bring FB OVI to a lower voltage range)
		////////	wait.delay_10_us(100);
		////////}

		////////Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set


		////////if(g_TurretCB)
		////////{
		////////	//HL dropped FB by 50mV to prevent DUT from being latched up on Turret CB
		////////	REQ_ovi->set_voltage(REQ_ch, gCVth_15pct_Higher,		RANGE_2_V);	// OVI_1_2	
		////////}
		////////else
		////////{
		////////	if(LB_Rev >= 5)		REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	
		////////	else				REQ_ovi->set_voltage(REQ_ch, gCVth_10pct_Higher,		RANGE_2_V);	// OVI_1_2	
		////////}
		////////wait.delay_10_us(15);
		//////////pv3_4->drive_off();
		////////
		////////// Turn off gage
		////////pv3_4->drive_off();	
		////////wait.delay_10_us(100);	// Tc test, delat not critical
		////////pv3_4->set_voltage(0.0, RANGE_100_V);
		////////pv3_4->set_current(0.0);
		////////pv3_4->charge_on();
		////////wait.delay_10_us(500);
		//////////DEBUG=1;
		//////////gDEBUG = 1;
		////////WAVE_NAME =  "SOA_TW50_S";
		////////Gage_Find_SOA(&SOA_S, &TW50_S);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing
		//////////DEBUG=0;
		//////////gDEBUG = 0;
#endif

#ifdef PU_2ndary_Prog_AF_REG
	//PROG mode to program out XFWPK bit to disable FWPK switching
	// Also Program out the External FB option

	Powerup_Secondary_in_Testmode(gProgRead_AFreg_S, 0, 0);
	wait.delay_10_us(20);
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final,	VOLT_10_RANGE);			
	wait.delay_10_us(20);

	//Read/write AF register
	Close_relay(K26);	//SR to DDD-7-5
	delay(5);
	//DEBUG=1;
	Read_Secondary_AF_Reg (SR_AF_temp);	//must be followed by write
	//MINNO Trim bits
	//Write corrected bits into AF register
	SR_AF_temp[5]=0;	// Programming out PK1&Xspeedload
	SR_AF_temp[6]=0;	// Programming out PK2
	SR_AF_temp[7]=0;	// Programming out PK3
	SR_AF_temp[22]=0;	// Programming out PKdig<1>
	SR_AF_temp[23]=0;	// Programming out PKdig<2>
	SR_AF_temp[24]=0;	// Programming out PKdig<3>
	SR_AF_temp[25]=0;	// Programming out PKdig<4>
	SR_AF_temp[42]=1;	// Programming in  DOPL
	SR_AF_temp[44]=1;	// Programming in  FWPK
	Write_Secondary_AF_Reg (SR_AF_temp);

	Open_relay(K18);
	Open_relay(K21);
	delay(1);

	REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		RANGE_5_V);	
	wait.delay_10_us(10);
	dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
			wait.delay_10_us(50);
	Connect_InvSyn_IM(Low_Load_Vd_Input);
	dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
			wait.delay_10_us(50);
if(g_TurretCB)
	{
		if (MOSFET_SIZE == 5)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4			
		if (MOSFET_SIZE == 4)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 5.0,		VOLT_20_RANGE);	// OVI_1_4			
		if (MOSFET_SIZE == 3)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.0,		VOLT_20_RANGE);	// //ET Note: Vinminus varies from -3.0V to 3.0V. So, vinplus = 2.5V should be good. 
		if (MOSFET_SIZE == 2)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2.0,		VOLT_20_RANGE);	// OVI_1_4			
	}
	else
	{
		if(LB_Rev >=8)
		{
			//Setting InvSync Reference voltage per FET Size over different temperature
			if(OPCODE==4300 || OPCODE==4500) 
			{
				if (MOSFET_SIZE == 8)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 5.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 7)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 6)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 5)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 5.5,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 4)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.5,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 3)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.5,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 2)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 7.0,		VOLT_20_RANGE);	// OVI_1_4			
			}
			else	//ROOM Temp InvSyn Ref voltage
			{
				if (MOSFET_SIZE == 8)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 5.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 7)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// 
				if (MOSFET_SIZE == 6)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// 6V to pass
				if (MOSFET_SIZE == 5)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 4)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 3)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.5,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 2)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2.0,		VOLT_20_RANGE);	// OVI_1_4			
			}
		}
		else	//LB_Rev 7 or older
		{
			//Setting InvSync Reference voltage per FET Size over different temperature
			if(OPCODE==4300 || OPCODE==4500) 
			{
				if (MOSFET_SIZE == 8)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 4.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 7)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 5.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 6)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 5)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 5.5,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 4)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.5,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 3)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.5,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 2)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 7.0,		VOLT_20_RANGE);	// OVI_1_4			
			}
			else	//ROOM Temp InvSyn Ref voltage
			{
				if (MOSFET_SIZE == 8)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 5.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 7)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 5.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 6)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// 
				if (MOSFET_SIZE == 5)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 4)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.0,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 3)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 6.5,		VOLT_20_RANGE);	// OVI_1_4			
				if (MOSFET_SIZE == 2)	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 2.0,		VOLT_20_RANGE);	// OVI_1_4			
			}
		}
	}

	wait.delay_10_us(20);

	if(gSiliconRev_P>=3)
	{
		//BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);		//						B3 material
		VBPP_ramp_down(gVBPP_P_final, gVBPP_P_s_final, 10e-3);	// vstart, vstop, vstep	B3 material
		wait.delay_10_us(10);
	}
	//Drain set to 5V for switching
	//dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
	//wait.delay_10_us(20);

	REQ_ovi->set_voltage(REQ_ch, 0.9,		RANGE_2_V);	// OVI_1_2
#endif

	// Only test tARoffShort-P for characterizaton.  200 msec duration. //
		if(1)
		//if(gCHAR_FLOW)
		{
			//Start and Stop trigger setup 
			if(OPCODE==4300 || OPCODE==4500) 
			{
				if(MOSFET_SIZE==2)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==3)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==4)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==5)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==6)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==7)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==8)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
			}
			else
			{
				if(MOSFET_SIZE==2)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==3)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==4)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==5)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==6)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==7)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
				if(MOSFET_SIZE==8)	{vTrig_Start = vSDS-5;	vTrig_Stop = vSDS-3;}
			}

			if(g_TurretCB)
			{
				if(MOSFET_SIZE==2)
				{
					vTrig_Start = vSDS-3;	vTrig_Stop = vSDS-2;
				}
				else if(MOSFET_SIZE==3)
				{
					vTrig_Start = vSDS-3;	vTrig_Stop = vSDS-2;
				}
				else if(MOSFET_SIZE==4)
				{
					vTrig_Start = vSDS-3;	vTrig_Stop = vSDS-2;
				}
				else if(MOSFET_SIZE==5)
				{
					vTrig_Start = vSDS-3;	vTrig_Stop = vSDS-2;
				}
				else if(MOSFET_SIZE==6)
				{
					vTrig_Start = vSDS-3;	vTrig_Stop = vSDS-2;
				}
				else if(MOSFET_SIZE==7)
				{
					vTrig_Start = vSDS-3;	vTrig_Stop = vSDS-2;
				}
				else if(MOSFET_SIZE==8)
				{
					vTrig_Start = vSDS-3;	vTrig_Stop = vSDS-1;
				}
			}

			tmu_6->close_relay(TMU_HIZ_DUT2); // Connect TMU HIZ to Drain // 
			tmu_6->start_trigger_setup( vTrig_Start,	NEG_SLOPE, TMU_HIZ, TMU_IN_100V);	// cx 11/10/16
			tmu_6->stop_trigger_setup(vTrig_Stop,  POS_SLOPE, TMU_HIZ, TMU_IN_100V);	// cx 11/10/16
			//tmu_6->start_holdoff(1e-3,FALSE);  // Wait for 1msec after tmu arm to ignore the first two SDS pulses. //
			tmu_6->start_holdoff(0,FALSE);  // remove the 1ms  cx 1/30/2017
			tmu_6->stop_holdoff(0,FALSE);
			wait.delay_10_us(200);
		}
	    dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
		wait.delay_10_us(20);	
	    Open_relay(K3);		//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0
		wait.delay_10_us(50);
		Close_relay(K7);	//CT2+	to 2ohm pull-up by PVI		//mux-4-3
		Close_relay(K9);	//Drain to CT2+						//mux-5-1
		delay(5);

		//turn on PV3
		/*pv3_4->drive_on(); 
		delay(5);*/

		//** SOA_S **

		//DEBUG=1;
		//if (DEBUG && gDEBUG) 
		//			//pulse
		//DEBUG=0;

		//** start SDS_S capture **
		Gage_Start_Capture( );
		pv3_4->set_voltage(vSDS,		RANGE_100_V);	//voltage found in search above

			delay(1);
			//pv3_4->set_current(10.0);
			pv3_4->drive_on();	
			delay(5);  
			// Turn device back on...

		REQ_ovi->set_voltage(REQ_ch, gCV_Low,	RANGE_2_V);	// OVI_1_2	"Force device to stop switching while 2ndary in control"
		//wait.delay_10_us(100);
		// Only test tARoffShort-P for characterizaton.  200 msec duration. //
//
		//tmu_6->arm();		//use the "2nd pulse's rise edge as the start edge" and the "3rd pulse come in after ARoffTime fall edge as stop edge"
		//if(gCHAR_FLOW)
		if(1)
		{
			wait.delay_10_us(1);	//wait for first pulse to pass by and start arm before the 2nd pulse.
			tmu_6->arm();		//use the "2nd pulse's rise edge as the start edge" and the "3rd pulse come in after ARoffTime fall edge as stop edge"
			wait.delay_10_us(30);//why 1ms.
			tmeas = tmu_6->read(100e-6);	//note that the result refer to the last stop and start trigger pulse. (Take pulse ending noise into account)

			starttime = mytimer.GetElapsedTime();
			wait.delay_10_us(10);
		}	
		else
			wait.delay_10_us(2);

		Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set



float dummy = 0;
dummy = tmeas;

		//DEBUG=1;
		//gDEBUG = 1;
		WAVE_NAME =  "SDS_TW50_S";
		//if(g_TurretCB)
		//{
		//	Gage_Find_SDS_New(&SDS_S, &TW50_SDS_S, &SDS_S_nsw);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing

		//}
		/*else
		{*/
			Gage_Find_SDS(&SDS_S, &TW50_SDS_S, &SDS_S_nsw);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing
		/*}*/
		//gDEBUG=0;
		//DEBUG=0;

		//if(gTrim_SDS_OFF_P)
		//{
			if(SDS_S_nsw==1)	SDS_S_sw=0;
			else				SDS_S_sw=1;
		//}
		////if(SDS_S_nsw>0 && gTrim_SDS_OFF_P)
		////	SDS_S_sw = 1;

		//if(SDS_S_nsw==0 && gDEBUG==1)
		if(0)
		{
			gDEBUG=1;
			DEBUG=1;
			WAVE_NAME =  "SDS_TW50_S";
			Gage_Find_SDS(&SDS_S, &TW50_SDS_S, &SDS_S_nsw);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing
			gDEBUG=0;
			DEBUG=0;
		}
		//DEBUG=0;
		//gDEBUG = 0;

	//	Rep_cnt++;
	//}


//
	// Only test tARoffShort-P for characterizaton.  200 msec duration. //
	//if(gCHAR_FLOW && !gTrim_Loff_AR_P && !gTrim_SDS_OFF_P)
	if(!gTrim_Loff_AR_P && !gTrim_SDS_OFF_P)
	{
		tmu_6->arm();	//only need to arm once.  If the trigger is used, then we shall exit the while loop.  cx.  1/30/2017
		// Wait for next SDS pulse (approx 200msec). //
		count = 0;
		MaxCount = 3000;
		FlagError = 0;
		while (count < MaxCount) // About 100usec per loop //
		{
			wait.delay_10_us(10);
			tmeas = tmu_6->read(100e-6);
			//if (tmeas > 10e-9 && tmeas < 500e-9) // If device made a request in AR_off_short time, tmeas has to be between 10ns and 500ns
			if (tmeas > 10e-9 && tmeas < 500e-9) // If device made a request in AR_off_short time, tmeas has to be between 10ns and 500ns
				break;
			count++;
		}
		if(count > (MaxCount-1))
			FlagError = 1; // Part did not start switching. //

		stoptime = mytimer.GetElapsedTime();

		if(FlagError)
			tARoffShort_P = -99999;
		else
			tARoffShort_P = (stoptime - starttime) / 1e6;
	}


	// Turn off PV3
	pv3_4->drive_off();	
	wait.delay_10_us(100);	// Tc test, delat not critical
	pv3_4->set_voltage(0.0, RANGE_100_V);
	pv3_4->set_current(0.0);
	pv3_4->open_switch(PV3_LOW_FORCE_2);
	pv3_4->open_switch(PV3_LOW_SENSE_2);
	pv3_4->open_switch(PV3_HIGH_FORCE_3);
	pv3_4->open_switch(PV3_HIGH_SENSE_3);
	pv3_4->charge_on();	

	//Power Down
	//Power_Down_Secondary();
	//Power_Down_Primary();
	//Disconnect_InvSyn_IM();
	Power_Down_Everything();
	Open_All_Relays();
	Disconnect_InvSyn_IM();
	tmu_6->open_relay(TMU_HIZ_DUT2);
	wait.delay_10_us(10);

	if(LB_Rev >= 9)	
	{
		//Disconnect 1uF from BPP pin via Mux_20_1_2
		mux_20->open_relay(MUX_1_2);
		delay(3);
	}

	if(SOA_S > 990.0)
		SOA_S/=1e6;			// For datalog purpose
	if(TW50_S > 990.0)
		TW50_S/=1e6;		// For datalog purpose
	if(SDS_S > 990.0)
		SDS_S/=1e6;			// For datalog purpose
	if(TW50_SDS_S > 990.0)
		TW50_SDS_S/=1e6;		// For datalog purpose

	if(SDS_S_nsw >1)
	{
		delay(2);
	}


	//Datalog
	PiDatalog(func, A_vSOA,		vSOA,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_vSDS,		vSDS,		set_fail_bin,	POWER_UNIT);
	PiDatalog(func, A_TW50_P,		TW50_P,		set_fail_bin,	POWER_NANO);
	PiDatalog(func, A_SOA_P,		SOA_P,		set_fail_bin,	POWER_MICRO);
	//PiDatalog(func, A_SOA_S,		SOA_S,		set_fail_bin,	POWER_MICRO);
	//PiDatalog(func, A_TW50_S,		TW50_S,		set_fail_bin,	POWER_NANO);

	if (!gTrim_SDS_OFF_P)
	{
		PiDatalog(func, A_SDS_TW50_P,	TW50_SDS_P,		set_fail_bin,	POWER_NANO);
		PiDatalog(func, A_SDS_P,		SDS_P,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_SDS_S,		SDS_S,		set_fail_bin,	POWER_MICRO);
		PiDatalog(func, A_SDS_TW50_S,	TW50_SDS_S,		set_fail_bin,	POWER_NANO);
		PiDatalog(func, A_SDS_P_nsw,	SDS_P_nsw,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_SDS_S_nsw,	SDS_S_nsw,		set_fail_bin,	POWER_UNIT);	
	}
	else
	{
		PiDatalog(func, A_SDS_P_sw,	SDS_P_sw,		set_fail_bin,	POWER_UNIT);	
		PiDatalog(func, A_SDS_S_sw,	SDS_S_sw,		set_fail_bin,	POWER_UNIT);	
	}
	if(gCHAR_FLOW && !gTrim_Loff_AR_P && !gTrim_SDS_OFF_P)
		PiDatalog(func, A_tARoffShort_P, tARoffShort_P, set_fail_bin, POWER_MILLI);	


	if(gDEBUG==1)
	printf("Function SOA_SDS_TW50 Done\n");

}
