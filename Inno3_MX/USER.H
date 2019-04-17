#if !defined(USER_H)
#define USER_H
//==============================================================================
// USER.H
//==============================================================================
#define STRING(x) #x
#define LINE_STRING(line_number) STRING(line_number)
#define LOCATION __FILE__"("LINE_STRING(__LINE__)")"
//Include from PI START
#include "piclasses.h"
#include "qcsample.h"
#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream> 
#include "gage_drv.h"
#include <process.h>
#include "CsStruct.h"
#include "CsPrototypes.h"
#include "CsAppSupport.h"
#include "CsTchar.h"
#include "CsSdkMisc.h"
#include "CsTypes.h"

#include "ModalDialogDescription.h"
#include "ui.h"
#include "NPMSupport.h"

using namespace std;
#ifdef NT_
#include <strstrea.h>
#include <fstream.h>
#include "M310.h"
#else
// XP //
#include <strstream>
#include <fstream>
#endif
//Include from PI END

// Include from Credence START
#include "vType.h"
#include "vVector.h"
#include "vAnyTypeSharedData.h"
#include "vISetSharedData.h"
#include "ISiteMgrPub.h"
#include "sc_status.h"
// Include from Credence END

#define CSC_SITEBASE (1)	// value must be 0 or 1
#define Pulse PIPulse

extern ModalDialogDescription mdb;		// External class object, allocate memory. Credence function
extern int g_pid;  //Not really a global, but watch sheets need this exact name.

//{ASL_CREATE BEGIN BOARDS_FROM_LIST_PROPERTIES
// Regenerating source code will change code between here and ASL_CREATE END BOARDS_FROM_LIST_PROPERTIES}
// Use the List Properties dialog to drive the changes to this code.
 
void board_ptr_init(void);
void board_hardware_init(void);
 
extern Ovi * ovi_1;
extern Pv3 * pv3_4;
extern Tmu * tmu_6;
extern Ddd * ddd_7;
extern Dvi * dvi_9;
extern Dvi * dvi_11;
extern Dvi * dvi_13;
extern Mux * mux_14;
extern Hvs * hvs_15;
extern Mux * mux_20;
//ASL_CREATE END BOARDS_FROM_LIST_PROPERTIES}
// This file must be present even if no user code is placed below

#endif

enum relay_grp{
	MUX_14_relay = 1000,
	MUX_20_relay = 2000,
	DVI_9_relay  = 3000,
	DVI_11_relay = 4000,
	DVI_13_relay = 5000,
	TMU_6_relay  = 6000,
};

enum relay{
	//MUX_14
	K24 = MUX_14_relay + MUX_2_3,	// control for	DVI13_0		to IS with or without R_divider 1/20.
	K23 = MUX_14_relay + MUX_2_4,	// control for	HVS_15/19	to HVS-BVD (single or stack)

	K1  = MUX_14_relay + MUX_3_1,	// control for	DVI11_0		to Drain or IM_Iped
	K2  = MUX_14_relay + MUX_3_2,	// control for	DVI11_0		to Drain or Load+Drain
	K3  = MUX_14_relay + MUX_3_3,	// control for	Drain		to DVI_11_0 or Load
	K4  = MUX_14_relay + MUX_3_4,	// control for	HVS15		to HVS-BVD

	K5  = MUX_14_relay + MUX_4_1,	// control for	HVS-BVD		to Drain or FW for BVD and SRf to 5nF
	K6  = MUX_14_relay + MUX_4_2,	// control for	PVI			to Drain for DATT 
	K7  = MUX_14_relay + MUX_4_3,	// control for	PVI			to Drain for SOA
	K8  = MUX_14_relay + MUX_4_4,	// control for	InvSyn_IM	to Drain 

	K9  = MUX_14_relay + MUX_5_1,	// control for	CT Pearson	to Drain
	K10 = MUX_14_relay + MUX_5_2,	// control for	Rdson Buf	to Drain
	K11 = MUX_14_relay + MUX_5_3,	// control for	DVI or OVI	to BPP
	K12 = MUX_14_relay + MUX_5_4,	// control for	DDD			to UV

	K13 = MUX_14_relay + MUX_6_1,	// control for	PVI & SRC-P	to Ground
	K14 = MUX_14_relay + MUX_6_2,	// control for	DVI			to IS with or without R7
	K15 = MUX_14_relay + MUX_6_3,	// control for	PVI			to IS or calibration
	K16 = MUX_14_relay + MUX_6_4,	// control for	DVI			to IS for sensing

	K17 = MUX_14_relay + MUX_7_1,	// control for	OVI or DDD	to FB
	K18 = MUX_14_relay + MUX_7_2,	// control for	DVI or HVS	to FW
	K19 = MUX_14_relay + MUX_7_3,	// control for	InvSyn_IM	to FW
	K20 = MUX_14_relay + MUX_7_4,	// control for	DVI9_sense	to Sense Resistor for Calibraion

	KC5 = MUX_14_relay + MUX_8_1,	// control for	K5 on CB	to UV pin for 15kohm decoupling Res
	KC6 = MUX_14_relay + MUX_8_2,	// control for	K6 on CB	to UV to TMU and Vpin_Gage
	KIM1= MUX_14_relay + MUX_8_3,	// control for	K1 on IM	to L1
	KIM2= MUX_14_relay + MUX_8_4,	// control for	K2 on IM	to L2

	//MUX_20
	KC8 = MUX_20_relay + MUX_1_1,	// control for	K8 on CB	to short SRf_dut to CB_GND
	K36 = MUX_20_relay + MUX_1_1,	// control for	TMU			to FW or REQ
	K37 = MUX_20_relay + MUX_1_2,	// control for	BPP			to 1uF
	K38 = MUX_20_relay + MUX_1_3,	// control for	TMU			to ACK or FWC
	K39 = MUX_20_relay + MUX_1_4,	// control for	BPP			to 2.2uF

	K40 = MUX_20_relay + MUX_2_1,	// control for	DDD7_2		to 2.4V zener clamp
	K43 = MUX_20_relay + MUX_2_2,	// spare
	K41 = MUX_20_relay + MUX_2_3,	// spare
	K42 = MUX_20_relay + MUX_2_4,	// spare

	//DVI_9
	KIM3= DVI_9_relay + DVI_EXT_DRV1,	// control for	K3 on IM	to Rpd1 or Rpd2
	K21 = DVI_9_relay + DVI_EXT_DRV2,	// control for	DDD7_3		to FW

	//DVI_11
	K25 = DVI_11_relay + DVI_EXT_DRV1,	// control for	OVI1		to REQ
	K26 = DVI_11_relay + DVI_EXT_DRV2,	// control for	DDD7_5		to SR

	//DVI_13
	K27 = DVI_13_relay + DVI_EXT_DRV1,	// control for	DDD7_4		to VO
	K22 = DVI_13_relay + DVI_EXT_DRV2,	// control for	CT2877 compensation winding

	//TMU_6
	K29 = TMU_6_relay + TMU_EXT_DRV1,	// control for	DVI11_1		to BPP
	K28 = TMU_6_relay + TMU_EXT_DRV1,	// Connect Vpin to HVS for BPP stress test
	K34 = TMU_6_relay + TMU_EXT_DRV1,	// Connect Vpin to HVS for BPP stress test
	K35 = TMU_6_relay + TMU_EXT_DRV2,	// control for	VPIN_Gage	to Rdson Buffer
	KC7 = TMU_6_relay + TMU_EXT_DRV3,	// control for	K7 on CB	to disconnect SR
};

// *** Primary Side Resources
extern	Dvi *D_dvi	;			// DVI_11_0		Drain
extern	Dvi *BPP_DVI;			// DVI_11_0		BPP for breakdown test
extern	Ovi *BPP_ovi;			// OVI_1_0		BPP 
extern	Ovi *VPIN_ovi;			// OVI_1_1		UV

// *** Secondary Side Resources
extern	Dvi *FWC_dvi2k;			// DVI_13_0		FWC
extern	Ovi *REQ_ovi;			// OVI_1_2		REQ
extern	Dvi *BPS_dvi;			// DVI_9_1		BPS
extern	Dvi *SR_dvi2k;			// DVI_13_1		SR
extern	Dvi *VO_dvi	;			// DVI_9_0		VO
extern	Dvi *FW_dvi	;			// DVI_11_1		FW
extern	Ovi *ACK_ovi;			// OVI_1_5		ACK 


// *** Other Resources
extern	Ovi *InvSyn_REF_ovi;	// OVI_1_4		InvSyn_IM reference OVI 
extern	Ovi *InvSyn_Offset_ovi;	// OVI_1_6		InvSyn_IM GND offset OVI
extern	Ovi *BC_ovi;			// OVI_1_3		Buffer Clamp reference OVI

// *** Gage Digitizer
extern 	CSSYSTEMINFO	CsSysInfo ;
extern  int				gDig_Type;

// *** Primary Side Channels
extern int
	D_ch	,			// DRAIN DVI11_0
	BPP_ch	,			// Primary BYPASS: Both OVI and DVI are channel 0 DVI11_0 and OVI1_0
	VPIN_ch   ;			// UV OVI1_1
	
// *** Secondary Side Channels
extern int
	FWC_ch   ,			// FWC DVI21_0
	REQ_ch	,			// REQ OVI1_2
	BPS_ch	,			// BPS DVI9_1
	SR_ch	,			// SR  DVI21_1
	VO_ch   ,			// VO  DVI9_0
	FW_ch	,			// FW  DVI11_1
	ACK_ch	;			// ACK OVI1_5

// *** Other Resources Channels
extern int
	InvSyn_ch,			// InvSyn OVI_1_4
	BC_ch;				// Buffer Clamp OVI_1_3	

// *** Program Name
extern STRING ProgramName;
extern STRING Trimops_Table_Rev;
extern float gTrimops_Table_Rev_float;


/* ======================  Test Hardware ID Parameters  ============================*/
extern int	BoardSubType,					// Loadboard type for hardware ID
			LB_Rev,
			InductorType,				// Inductor type for hardware ID
			InductorRev,
 			ContactorType,				// Contactor type for hardware ID
			ContactorRev,
			gManual_Handler,
			gRasco_Handler,
			gTurret_Handler;

extern double gLB_ID,					// LB_ID = BoardSubType		+ (LB_Rev		/ 100)
			  gCB_ID,					// CB_ID = ContactorType	+ (ContactorRev / 100)
			  gIB_ID,					// IB_ID = InductorType		+ (InductorRev	/ 100)
			  gTB_ID;					// TB_ID = TestBlockType	+ (TB_Rev		/ 100)

/* ======================  Die Parameters  =========================================*/
extern int gDevFamily;
extern int MOSFET_SIZE;
extern int gDevNum;
extern int gDLM_BV;
extern int gDLM_Size;


/* ======================  Test Flow Control Parameter  ============================*/
extern int  First_Time_Run;
extern int	AbortTest; 
extern int	TRIM_ENABLE;
extern int	Pkg_id;
extern char *Dev_id;
extern char *gH_code;
extern char *gHC_code;
extern char *gHZ_code;
extern char *PrgRev;
extern char *FamilyName;
extern char *gDev_Family;
extern char OperCode[];
extern char DevName[];
extern int  OPCODE;	
extern int  gREL_FLOW;
extern double Primary_Si_Rev;
extern double Secondary_Si_Rev;
extern int  gDevFOSC;
extern int  Golden_Unit_Prg;
extern  int gHas_Var_AR_Func;
extern  int gHas_Fixed_AR_Func;
extern  int gHas_AR_Delay;
extern int ours_ENG_Option;
extern int gCHAR_FLOW;
extern int gTrimmed_Device;
extern int g_TurretCB;
extern int g_GRR;
extern int g_Original_ISVth_Search;
extern int g_Setup_OK;
extern float g_Drain_V;
extern int ours_SiliconRev_S;
extern int ours_SiliconRev_P;
extern int g_DDD_Reload;
extern int g_Check_InvSync_Circuit;
extern float g_Voffset;
extern float g_VoffsetRxTx;
//extern float gIBPS_sw;
extern int   g_ReTrim_P;
extern int skiphvs;
extern int hvsflag;

//extern int g_LB_RevE;
extern unsigned short gStoponfail;

/*=======================   Sampling Variables    ===============================*/
extern int	  gDATT_FAIL;
extern int	  gQty_Pass_DATT;
extern int	  gDATT_Loop_Count;

/* ======================  TestTime Saving ============================*/
extern bool gRemove_Test_from_all_Devices;
extern bool gRemove_Test_per_Device_option;

enum Remove_Test_Per_Device {	SC1566C,
								SC1565C,
								SC1567C,
								SC1546C_HC15,	//could not use dash for enum purpose
								SC1536C,
								SC1540C,
								SC1542C,
								INN3168C,
								INN3166C,
								SC1537C,
								SC1538C,
								SC1541C,
								SC1545C,
								SC1543C,
								SC1547C,
							};

/* ======================  Debug Parameters ============================*/
extern double ours_v_debug;
extern double ours_i_debug;
extern double ours_ms_debug;
extern bool   BPP_4p7uF;
extern bool   BPP_p47uF;



enum SiliconRev_P{ revA_P, revB_P, revB2_P, revB3_P};
enum SiliconRev_S{ revA_S, revA1_S, revB_S, revB2_S, revB3_S};
enum Device_ID{ SC0062K, SC0063K, SC0064K, SC0065K, SC0066K, SC0067K, SC0068K}; 
enum Package_Type {ReSOP};
enum Die {PRIMARY, SECONDARY};
enum Capture_Mode {ILIM_NORM, ILIM_RED, ILIM_INCR, ILIM_RAMP, SOA_RED_S, SOA_RED_P, ILIM_INCR_secondary_control, ILIM_Jit18K, ILIM_SSS };
enum CV_CB_FLAG {Srch_CV, Srch_CB};
enum Control_Mode {gPrimary_CTRL, gSecondary_CTRL};
//enum Test_Modes {gTM1_p, gTM2, gTM_OverTemp, gTM_Fast_Counter_32x, gTM_TonMax1us, gTM_Receiver_Threshold, gTM_UVOV_NoDelay, 
//				 gTM_Trim_Readable, gTM_Jitter_to_Vpin, gTM_MaxF_to_Vpin, gTM_ILIM};
//enum Inno4_Testmodes {gWrite_Mode_ReadAF, gWrite_Mode_TrimAF, gObserve_Mode, gOT_Mode, 
//					  gProgRead_S, gProgSim};

enum Power_Up_Modes {	Normal_Mode_P, 
						Normal_Mode_S,
						Normal_Mode_with_FW, 
						Normal_Mode_with_Vout, 
						gNM_SkipWaitNListen_S,
						Test_Mode, 
						gTM1_p, 
						gTM2_p,
						gTM5_BypassWL_p,
						gTM_OverTemp, 
						gTM_Fast_Counter_32x, 
						gTM_TonMax1us, 
						gTM_Receiver_Threshold, 
						gTM1_UVOV_NoDelay,
						gTM2_UVOV_NoDelay,
						gTM_Trim_Readable, 
						gTM_Jitter_to_Vpin, 
						gTM_MaxF_to_Vpin, 
						gTM_ILIM,
						gWrite_Mode_ReadAF, 
						gWrite_Mode_TrimAF, 
						gObserve_Mode, 
						gOT_Mode, 
						gProgRead_S,
						gProgRead_AFreg_S,
						gProgRead_SkipWaitNListen_S,
						gProgSim,
						//INNO2
						gObserve_Mode_Xcontrol_sec,
						gObserve_Mode_Xlisten,
						gObserve_Mode_XVTurnOn,
						gObserve_Mode_XRestart,
						gObserve_Mode_rcv,
						gObserve_Mode_Pause,
						gObserve_Mode_DSDS,
						gObserve_Mode_OT,
						gObserve_Mode_LatchOff,
						gObserve_Mode_Xoc,
						gObserve_Mode_DZwindow,          //Apply 3 Vpin clock
						gObserve_Mode_DZwindow2,		//Apply 2 Vpin clock 
						gObserve_Mode_XZfQ,
						gObserve_Mode_Xtest2,
						gObserve_Mode_iplus,
						//INNO3X B3p
						gObserve_Mode_DChUp,
						gObserve_Mode_HSwindow,
						gProgReadTestMode1_FB_S,		//Shorten AR timer by 10x.  Shorten SC timer by 256x
						gProgReadTestMode1_Vout_S,		//Shorten AR timer by 10x.  Shorten SC timer by 256x
						gProgReadTestMode2_S,			//DableOn from FW pin Peak Switch
						gProgReadTestMode3_S,			//Pulse Request
						gProgReadTestMode4_S,			//FW pin Peak Switch FAult
						gProgReadTestMode5_S,			//SR pullup
						gProgReadTestMode6_S,			//verify secondary is in control
						gProgReadTestModeTFB1_S,			//normal SR signal
						gProgReadTestModeTFB2_S,			//normal SR signal
						gProgReadTestMode11_S,			//SR comparator output
						gProgReadTestMode12_S,			//FW min 1us negative pulse indication
						gProgReadTestMode13_S,			//9V20V comparator signal
						gProgReadTestMode14_S,			//12V comparator signal
						gProgReadTestMode18_S,			//CV comparator signal
						gProgReadTestMode19_S,			//
						gProgReadTestMode20_S,			//
						gProgReadTestMode21_S,			//
						gProgReadTestMode22_S,			//
						gSimuModeTestMode1_S,			//Shorten AR timer by 10x.  Shorten SC timer by 256x
						gSimuModeTestMode2_S,			//DableOn from FW pin Peak Switch
						gSimuModeTestMode3_S,			//Pulse Request
						gSimuModeTestMode4_S,			//FW pin Peak Switch FAult
						gSimuModeTestMode5_S,			//SR pullup
						gSimuModeTestMode6_S,			//verify secondary is in control
						gSimuModeTestModeTFB1_S,			//normal SR signal
						gSimuModeTestModeTFB2_S,			//normal SR signal
						gSimuModeTestMode11_S,			//SR comparator output
						gSimuModeTestMode12_S,			//FW min 1us negative pulse indication
						gSimuModeTestMode13_S,			//9V20V comparator signal
						gSimuModeTestMode14_S,			//12V comparator signal
																			};

enum Vd_Input_Mode {High_Vd_Input, Low_Vd_Input, High_Temp_Vd_Input, Low_Load_Vd_Input};
enum Vpin_Condition {gVpinLow_after_PU, gVpinHigh_after_PU};
//enum Device_Fosc{100e3, 132e3};

/* ======================    Trimming Variable  ============================*/
extern float gTrim_Voltage;
extern float gAF_2ND_TRIM_TRHD ;  			// 5uA
extern float gAF_1ST_TRIM_DELAY ;			// Should be 20ms
extern float gAF_2ND_TRIM_DELAY ;

/*======================= LB Component Variables =============================*/
extern double R7_decouple, R8_4wire;


/* ======================  Setup Variable  ============================*/
extern STRING CURRENT_SERIAL_NUM; 
extern int   SERIAL_NUM;
extern int   gFuncNum;
extern int   gDisplay_FuncNum;
extern int	 gDisplay_ErrDlog;

/*=======================   Test Debug Variables ===============================*/
extern CMicroTimer mytimer;					
extern LONGLONG starttime;
extern LONGLONG stoptime, stoptime1;
extern int DEBUG;
extern int gDEBUG;
extern char *Func_name;
extern char *WAVE_NAME; 

/*=======================   Golden Unit Variables    ===============================*/
extern bool GoldenUnit;

/*=======================		DDD Variables		 ===============================*/
extern float Dclk_Period;		// DDD clock period
extern float DDD_Vref;			// DDD voltage reference 2.5V

extern int First_address, Last_address;
extern int Low_pat_start, Low_pat_stop, 
		Low_pat_start_dummy,Low_pat_stop_dummy,
		Low_FB_pat_start, Low_FB_pat_stop, 
		Low_FB_pat_start_with_Vpin, Low_FB_pat_stop_with_Vpin, 
		Low_FW_pat_start, Low_FW_pat_stop, 
		Low_XXX_pat_start, Low_XXX_pat_stop,
		Low_pat_REQ_start, Low_pat_REQ_stop,
		High_pat_start, High_pat_stop,
		High_pat_FB_start, High_pat_FB_stop,
		High_pat_FW_start, High_pat_FW_stop,
		High_pat_Vpin_start, High_pat_Vpin_stop,
		High_pat_Vout_start, High_pat_Vout_stop,
		High_pat_REQ_start, High_pat_REQ_stop,
		Tristate_pat_start,Tristate_pat_stop,  
		FW_Neg_pulse_100ns_start, FW_Neg_pulse_100ns_stop,
		FW_Neg_1st_pulse_start, FW_Neg_1st_pulse_stop,
		FW_Neg_2nd_pulse_start, FW_Neg_2nd_pulse_stop,
		FW_Neg_3rd_pulse_start, FW_Neg_3rd_pulse_stop,
		FW_Neg_4th_pulse_start, FW_Neg_4th_pulse_stop,

		FWPK_pos_1p75us_pulse_start, FWPK_pos_1p75us_pulse_stop,
		FWPK_pos_0p50us_pulse_start, FWPK_pos_0p50us_pulse_stop,
		FWPK_neg_1p75us_pulse_start, FWPK_neg_1p75us_pulse_stop,
		
		FWPK_300kHz_Ring_pulse_start_FB, FWPK_300kHz_Ring_pulse1_stop_FB,
		FWPK_300kHz_Ring_pulse_start, FWPK_300kHz_Ring_pulse1_stop,

		FWPK_1MHz_Ring_Dable_pulse_start_FB, FWPK_1MHz_Ring_Dable_pulse_stop_FB,

		FWPK_1MHz_Ring_learn_pulse_start, FWPK_1MHz_Ring_learn_pulse_stop,
		FWPK_1MHz_Ring_Dable_pulse_start, FWPK_1MHz_Ring_Dable_pulse_stop,
		FWPK_1MHz_Ring_pulse_start_FB,	  FWPK_1MHz_Ring_pulse_stop_FB,	  
		FWPK_1MHz_Ring_pulse1_start_FB,  FWPK_1MHz_Ring_pulse1_stop_FB,
		FWPK_1MHz_Ring_pulse2_stop_FB,
		FWPK_1MHz_Ring_pulse3_stop_FB,
		FWPK_1MHz_Ring_pulse4_stop_FB,
		FWPK_1MHz_HighPulse1_start,   FWPK_1MHz_HighPulse1_stop,
		FWPK_1MHz_HighPulse2_start,   FWPK_1MHz_HighPulse2_stop,
		FWPK_1MHz_HighPulse3_start,   FWPK_1MHz_HighPulse3_stop,
		FWPK_1MHz_HighPulse4_start,   FWPK_1MHz_HighPulse4_stop,
		FWPK_1MHz_HighPulse5_start,   FWPK_1MHz_HighPulse5_stop,
		FWPK_1MHz_HighPulse6_start,   FWPK_1MHz_HighPulse6_stop,
		FWPK_1MHz_HighPulse7_start,   FWPK_1MHz_HighPulse7_stop,
		FWPK_1MHz_HighPulse8_start,   FWPK_1MHz_HighPulse8_stop,
		FWPK_p5us_Ring_pulse_start,   FWPK_p5us_Ring_pulse_stop,
		FWPK_4us_Ring_pulse_start,    FWPK_4us_Ring_pulse_stop,
		FW_Neg_Edge_start, FW_Neg_Edge_stop,
		Vout_loop_pulse_start, Vout_loop_pulse_stop,
		FW_Neg_loop_pulse_start, FW_Neg_loop_pulse_stop,
		Vpin_loop_pulse_start, Vpin_loop_pulse_stop,
		FB_100kHz_loop_pulse_start, FB_100kHz_loop_pulse_stop, 
		FB_100kHz_start, FB_100kHz_stop,
		FB_100kHz_100_pulses_start, FB_100kHz_100_pulses_stop, FW_100kHz_3_pulses_start, FW_100kHz_3_pulses_stop,
		FB_100kHz_pulse_start, FB_100kHz_pulse_stop,
		SR_10pctClampOff_start, SR_10pctClampOff_end,
		FB_100kHz_ILIM_pulse_start, FB_100kHz_ILIM_pulse_stop, FB_100kHz_ILIM_18_pulse_stop,
		FB_tOVL_start, FB_tOVL_stop,
		FW_Neg_pulse_10us_start, FW_Neg_pulse_10us_stop,
		FW_pulse_train_start,FW_pulse_train_stop,
		FW_pulse_train_start_70us, FW_pulse_train_stop_70us,
		FW_30us_pulse_start, FW_30us_pulse_stop,
		FW_Neg_pulse_3us_Req_start, FW_Neg_pulse_3us_Req_stop,
		AF_ClkVout_start,AF_ClkVout_stop,First_Clk_Edge,
		VO_Low_Pulse_Start, VO_Low_Pulse_END,
		AF_UV_pulse_start, AF_UV_pulse_stop,
		AF_FB_pulse_start, AF_FB_pulse_stop,
		AF_Vpin_Clk_pulse_start, AF_Vpin_Clk_pulse_stop,
		AF_Vpin_Clk_pulse_start_6pulses, AF_Vpin_Clk_pulse_stop_6pulses,
		AF_Vpin_Clk_pulse_start_6pulses_ET, AF_Vpin_Clk_pulse_stop_6pulses_ET,
		AF_Vpin_Clk_pulse_start_132kHz, AF_Vpin_Clk_pulse_stop_132kHz,
		AF_Vpin_Data_pulse_start,AF_Vpin_Data_pulse_stop,
		AF_Vpin_Data_pulse_start_retrim,AF_Vpin_Data_pulse_stop_retrim,
		AF_Vout_pulse_start, AF_Vout_pulse_stop,
		FB_positive_edge_start, FB_positive_edge_stop,
		VCLAMP_10PCT_start, VCLAMP_10PCT_stop,
		ILIM_RAMP_132kHz_start,	ILIM_RAMP_132kHz_stop,
		ILIM_UPMED_100kHz_SRCH_ADDR,
		ILIM_RAMP_100kHz_start,	ILIM_RAMP_100kHz_stop,
		ILIM_UPMED_100kHz_SRCH_ADDR,
		FB_MINNO_SSS_pulse_start, FB_MINNO_SSS_pulse_stop;//MINNO Soft Start test REQ pattern new

extern int FB_18kHz_pulse_start;
extern int FB_18kHz_pulse_stop;
extern int Vout_18kHz_pulse_start;
extern int Vout_18kHz_pulse_stop;
extern int FB_125kHz_pulse_start;
extern int FB_125kHz_pulse_stop;
extern int Vout_125kHz_pulse_start;
extern int Vout_125kHz_pulse_stop;
extern int FB_125kHz_pulse_start_X;
extern int FB_125kHz_pulse_stop_X;
extern int FB_100kHz_ILIM_pulse_start_X;
extern int FB_100kHz_ILIM_pulse_stop_X;
extern int Vpin_6clocks_start;
extern int Vpin_6clocks_stop;
extern int Vpin_4clocks_start;
extern int Vpin_4clocks_stop;
extern int Vpin_2clocks_start;
extern int Vpin_2clocks_stop;
extern int Vpin_3NegClocks_start;
extern int Vpin_3NegClocks_stop;
extern int Vpin_30usec_start;
extern int Vpin_30usec_stop;
extern int Vpin_one_30us_clock_start;
extern int Vpin_one_30us_clock_stop;
extern int FBpin_30usec_start;
extern int FBpin_30usec_stop;
extern int FB_100kHz_pulse_start_5X;
extern int FB_100kHz_pulse_stop_5X;

extern int gDDD_loop_end;
extern int gDDD_loop_pulses_stop;


/*=======================    Internal Registers   ===============================*/
extern int gVpin_Internal_Signal[16];	//Primary Internal Registers
extern int gSR_Internal_Signal[100];	//Secondary Internal Registers

extern int gVpin_AF[100];		// Primary AF data pre-trim
extern int gVpin_AF_post[100];	// Primary AF data post-trim
extern int gSR_AF[100];			//SR data for AF links
extern int gSR_AF_post[100];
extern float gIZ_AF_post_P[100];
extern float gIZ_AF_post_S[100];

/*=======================    Characterization Variables    ===============================*/
extern bool gCharacterization;

/*=======================    CV_CC_CB_Vout Function Variables    ===============================*/
extern float gGNDRes_Se;
extern float gCC_trim_weight[64];
extern int	 gCC_trimcode;	
extern float gFS_trim_weight[16];
extern int	 gFS_trimcode;

extern float g_vFBth_SC_S;
extern float gARSTth_S;
/*=======================    BVD Function Variables    =============================*/
extern float	scaled_ifrc;
extern float	gBVD_Room;
extern float	gBVD_Hot;

/*============================    FAB wafer Size   ===============================*/
extern int		gSEC_8in;

/*============================    VBP Variables    =================================*/
extern float gVshunt_BPP, gVshunt_BPS;
extern float gVBPS_P_Init, gVBPP_P_Init, gVBPP_P_final, gVBPS_final, gVBPP_M_Init, gVBPS_M_Init, gVBPP_PV_Init, gVBPP_PV_final; 
extern float gVBPP_P_s_final;
extern float gVBPP_VCEN, gVBPS_VCEN;
extern float gIBPS_nsw, gIBPS_sw;
extern float gVBPP_Low_Voltage_PU; 

/*============================    Stress Function Global Variables   ===============================*/
extern bool gStress_ON;
extern bool g_Stress_passed;

/*============================    Timing Global Variables   ===============================*/
extern float gDly_Wait_and_Listen_Normal_Mode;
extern float gDly_Wait_and_Listen_Test_Mode;
extern float g_readTime_p;
extern float g_readTime_s;
extern float g_trimTime_p;
extern float g_trimTime_s;
extern float g_StartTime;
extern float g_StopTime;
extern float g_Time_Diff;
extern int   g_ILIM_dly;
extern int   g_REL_dly;
extern int   g_tHandshake_SSS;
extern float g_tHandshake_SSS_floating;
/*============================    FB Global Variables   ===============================*/
extern float gVset_FB;
/*============================    Anti-Fuse Variables   ===============================*/
//Primary
extern int  gP_AF_Start_Addr_Primary,
			gP_AF_Start_Addr_Primary,
			gP_AF_Start_Addr_IOV	,
			gP_AF_Start_Addr_ILIM	,
			gP_AF_Start_Addr_TonMax	,
			gP_AF_Start_Addr_tOVL	,
			gP_AF_Start_Addr_Freq	,
			gP_AF_Start_Addr_IuvIov_Disable	,
			gP_AF_Start_Addr_Iuv_10uA		,
			gP_AF_Start_Addr_UV_400ms_dly	,
			gP_AF_Start_Addr_LatchOFF_aft_AR,
			gP_AF_Start_Addr_Disable_AR		,
			gP_AF_Start_Addr_didt_comp		,
			gP_AF_Start_Addr_OT_Hys_30C		,
			gP_AF_Start_Addr_LatchOFF_w_OT	,
			gP_AF_Start_Addr_Disable_ILIM_Select,
			gP_AF_Start_Addr_Select_ILIM_Incr	,
			gP_AF_Start_Addr_minus_20pct_ILIM	,
			gP_AF_Start_Addr_plus_20pct_ILIM	,
			gP_AF_Start_Addr_Samsung_Mode		,
			gP_AF_Start_Addr_OTP				,
			gP_AF_Start_Addr_VpinCTRL_iREF20pct	,
			gP_AF_Start_Addr_SDS_OFF			,
			gP_AF_Start_Addr_Rcv				,
			gP_AF_Start_Addr_Driver_Size		,
			gP_AF_Start_Addr_Rsense_up			,
			gP_AF_Start_Addr_Vx_adjust			,
			gP_AF_Start_Addr_ILIM_Ratio			,
			gP_AF_Start_Addr_ILIM_TC			,
			gP_AF_Start_Addr_AR_Request			,
			gP_AF_Start_Addr_ZF					;
//Secondary
extern int	gSecondary_AF_Addr_Start,
			gFosc_AF_Addr_Start,
			gFosc4_AF_Addr,
			gPK_ssSpeed_AF_Addr_Start,
			gCV1_AF_Addr,
			gDVesrSlpAdj_AF_Addr_Start,
			gPK_AF_Addr_Start,
			gCP_AF_Addr_Start,
			gPS_AF_Addr_Start,					
			gTFB_AF_Addr_Start,					
			gCC_AF_Addr_Start, 
			gKP_AF_Addr_Start,
			gSL_AF_Addr_Start,
			gCS_AF_Addr_Start, 
			gCB_AF_Addr_Start,	
			gCV_AF_Addr_Start, 
			gCV2_AF_Addr_Start, 
			gAR_AF_Addr_Start,
			gSCEN_Addr_Start,
			gCBEN_Addr_Start,
			gDsoftEn_Addr_Start,
			gDOPL_AF_Addr_Start,
			gOVLO_Addr_Start,
			gVR_Addr_Start,
			gCR_Addr_Start,
			gCCAR_Addr_Start,
			gESRsel_Addr_Start,
			gDdampEn_Addr_Start,
			gXFWPK_AF_Addr_Start,
			gSpare_Addr_Start,
			gZF_S_Addr,
			gRnw_AF_Addr_Start,
			gRnwFine_AF_Addr_Start,
			gFWC2_AF_Addr_Start,
			gNoFWC100mV_AF_Addr_Start,
			gCap_AF_Addr_Start,
			gPKdig_AF_Addr_Start,
			gSRth_AF_Addr_Start,
			gVshunt_AF_Addr_Start,
			gVref_AF_Addr_Start,
			gIintTC_AF_Addr_Start,
			gREQlow_AF_Addr_Start,
			gLO_dis_AF_Addr_Start;

/*============================    Feature Trim Variables   ===============================*/
extern float	gHcode,
		gHCcode,
		gH_code_AN,
		gHZ_code_AN,
		gTrim_code;


extern int	gTrim_iov_Off_P		,
			gTrim_iuvMinus_P	,
			gTrim_uvDelay_P		,
			gTrim_Loff_AR_P		,
			gTrim_DisablAR_P	,
			gTrim_didtComp_P	,
			gTrim_OT_Hys_P		,
			gTrim_LoffwOT_P		,
			gTrim_iLselOff_P	,
			gTrim_iLStdIcr_P	,
			gTrim_iL20dn_P		,
			gTrim_iL20up_P		,
			gTrim_SAM_P			,
			gTrim_OTP_P			, //3 bits
			gTrim_Vpin_ctrl_iREF_P	,
			gTrim_SDS_OFF_P			,
			gTrim_bit32_P			,
			gTrim_Rcv_P				, //3 bits
			gTrim_drvSize_P			, //4 bits
			gTrim_RsenseUp_P		,
			gTrim_vxAdj_P			, //5 bits
			gTrim_iLRatio_P			, //4 bits
			gTrim_iLTC_P			, //4 bits
			gTrim_AR_req			;

extern int	gTrim_PK_S		,  //3 bits
			gTrim_DVesrSlpAdj,
			gTrim_CP_S		,	//3 bits
			gTrim_PS_S		,	//2 bits
			gTrim_TF_S		,	//2 bits
			gTrim_AR_S		,	//2 bits
			gTrim_SCEN_S	,	//bit 39
			gTrim_CBEN_S	,   //bit 40
			gTrim_DsoftEn_S	,	//bit 41
			gTrim_DOPL_S	,	//bit 42
			gTrim_OVLO_S	,	//bit 43
			gTrim_VR_S		,	//bit 44
			gTrim_CR_S		,	//bit 45
			gTrim_XFWPK_S	,	//bit 46
			gTrim_Spare_S	,	//bit 47
			gTrim_CCAR_S	,
			gTrim_ESRsel_S	,
			gTrim_DdampEn_S	;

// MINNO specific
extern int	gTrim_Rnw_S			, //2 bit
			gTrim_RnwFine_S		, //4 bit
			gTrim_FWC2_S		, //bit 17
			gTrim_NoFWC100mV_S	, //bit 18
			gTrim_Cap_S			, //3 bit
			gTrim_PKdig_S		, //4 bit
			gTrim_Vshunt_S		, //bit 30
			gTrim_IintTC_S		, //4 bit
			gTrim_REQlow_S		, //bit 43
			gTrim_LO_dis_S		; //bit 51

extern int	gRead_PK_S		, //3 bits
			gRead_CP_S		,	//3 bits
			gRead_PS_S		,	//2 bits
			gRead_TF_S		,	//2 bits
			gRead_AR_S		,	//2 bits
			gRead_SCEN_S	,	//bit 39
			gRead_CBEN_S	, //bit 40
			gRead_DsoftEn_S	,	//bit 41
			gRead_DOPL_S	,	//bit 42
			gRead_OVLO_S	,	//bit 43
			gRead_VR_S		,	//bit 44
			gRead_CR_S		,	//bit 45
			gRead_XFWPK_S	,	//bit 46
			gRead_Spare_S	;	//bit 47

extern int	gSiliconRev_P, 
			gSiliconRev_S;	

extern bool	gSAMSUNG_Device_P,
			gSAMSUNG_Device_S;

extern int	gTotal_Addr_Count_P,
			gTotal_Addr_Count_S;


/*=======================    IzPre Function Variables    ===============================*/
extern float	gIzpt_NoZ_s, gIZ_NoZ_s, gIzpt_iov_Off_p;
extern float    gVread_AF_primary, gVread_AF_secondary;
extern float    gSec_tr1_ZapTime;
extern float    gSec_tr2_AFtrhd;
extern int		gSiOption_p, gSiOption_s, g_Silicon_Rev;

/*====================    Fosc Function Variables    ===============================*/
extern float	gFosc_pt_P,    gFOSC_pt_S;
extern float	gFOSC_TARGET_P, gFOSC_TARGET_S;
extern float    gFOSC_exp_P,   gFOSC_exp_S;
extern float    gFOSC_post_S;

/*======================    TonMax Variables    ====================================*/
extern float   gTonMax_TARGET;
extern float   gTonMax_Pt, gTonMax_S;
extern float   gTonMax_exp;
extern float   g_tOVL_TARGET;
extern float   g_tOVL_Pt;
extern float   g_tOVL_exp;
extern int	   gHandShake_PASS;

/*======================    iOV- Variables    ====================================*/
extern float	giOV_plus_TARGET;
extern float	giOV_plus_Pt_P;
extern float	giOV_plus_exp;

/*======================    CV Variables    ====================================*/
extern float 	gCV_FB_Init_pt_S;
extern float	gCV_FB_pt_S;
extern float	gCV_VO_pt_S;
extern float    gCV_FB_TARGET, gCVth_5pct_Lower, gCVth_5pct_Higher, gCVth_8pct_Higher,
				gCVth_10pct_Higher, gCVth_15pct_Higher, gCVtgt_15pct_Higher, gCV_FB_Pre, 
				gCV_Low;
extern float    gCV_VOUT_TARGET;
extern float	gCV_exp_S;
extern float	gCV_S,		gCV_post_S;
extern float	gCV_FB_S,	gCV_FB_post_S;
extern float	gCV_VO_S,	gCV_VO_post_S;

extern float    gVclamp_2pct_S, gVclamp_10pct_S;
extern float    gVclamp_2pct_S_QC3, gVclamp_10pct_S_QC3;
extern float	gVcl2pct_QC2VO_S;

/*======================    CC Variables    ====================================*/
extern int		DEVICE_CC_PROFILE;
extern float 	gCC_pt_S;
extern float 	gKP_pt_S;
extern float 	gSL_pt_S;
//extern float	gCC_Amp_pt_S;
extern float	gISvth_pt_S;
extern float    gCC_Amp_TARGET;
extern float    gISvth_TARGET;
extern float	gKP_TARGET_S;
extern float	gSL_TARGET_S;
extern float	gCB_TARGET;

extern float	gCC_KPpt_S;
extern float	gCV_NM_KPpt_S;
extern float	gCB_KPpt_S;
extern float	gSL_pt_S;
extern float	gCC_Amp_SLpt_S;
extern float	gCC_ISvth_SLpt_S;
extern float	gVknee_actual_SLpt_S;
extern float	gCC_Amp_S;
extern float	gVknee_actual_S;

extern float	gCC_S_9V_TARGET;
extern float	gCC_S_12V_TARGET;
extern float	gCC_S_20V_TARGET;
extern float	gCC_exp_S;
extern float	gISvth_S_9V_TARGET;
extern float	gISvth_S_12V_TARGET;
extern float	gISvth_S_20V_TARGET;
extern float	gISvth_exp_S;
extern float	gKP_exp_S;
extern float	gSL_exp_S;

extern float    iPV3_Cal_CC90;
extern float    iPV3_Cal_CC80;
extern float    iPV3_Cal_CC65;
extern float    iPV3_Cal_CC55;
extern float	iPV3_CC90;
extern float	iPV3_CC80;
extern float	iPV3_CC65;
extern float	iPV3_CC55;

/*======================    CB Variables    ====================================*/
extern float 	gCB_pt_S;
extern int		gCB_CODE;
extern float    gCB_TARGET;
extern float    gCS_TARGET;
extern float    gCB_exp_S;
extern float    iPV3_Load, iDVI2K_Load;	// For CB vs load experiment
extern float	gCB_NoLoad_Pct_pt;
extern float	gvCB_pre_TM_S;

/*======================    FW pin Peak Switch Variables    ====================================*/
extern float   gPK_TARGET;

/*======================    IFB Variables    ====================================*/
extern float	gIFB_TH_Target_S;
extern float	gIFB_250mA_pt_S;
extern float	gIFB_130mA_pt_S;
extern float	gIFB_TH_pt_S;
extern float	gIFB_exp_S;

/*======================    ILIM Variables    ====================================*/
extern float	gVped_Ilim, gVped_Ilim_Incr;
extern float	Vind_RM, Vind_HT;

extern float	gILIM_TARGET_S;
extern float	gILIM_LO_TARGET;
extern float	gILIM_LO_Med_TARGET;
extern float	gILIM_UP_Med_TARGET;
extern float	gI2F_S_TARGET;
extern float	gDIDT_TARGET;
extern float    gILIM_pt_S;
extern float    gILIM_exp_S;
extern float	gILIM_I2f_pt_S;
// For Capture and Find ILIM with digitizer
extern float    gIlim_Incr_max;
extern float	Ilim_gain, BUFgain;
extern int		SAMPLE_SIZE;

extern int		FIND_RDSON_Peak_FLAG;
extern int		FIND_RDSON_Spec_FLAG;
extern int		gFind_ILIM_Jitter;
extern float	gIdmax[4000];
extern int		gIdmax_addr[4000];
extern float	gIdmax_Jitter_132kHz;
extern float	gIdmin_Jitter_132kHz;
extern float	gIdmax_Jitter_18kHz;
extern float	gIdmin_Jitter_18kHz;
//extern float	Ton[10];
//extern float	Toff[10];

//extern bool		g_ILIM_INCR_secondary_control_active;

extern float	gTon_1stP;
extern float	gTon_2ndP;
extern float	gTon_3rdP;
extern float	gToff_1stP;
extern float	gToff_2ndP;
extern float	gToff_3rdP;
extern float	gILIM_pct_1stP;
extern float	gILIM_pct_2ndP;
extern float	gILIM_pct_3rdP;
extern float	gRTM_Slope;
extern float	gtDelta_RTM_Slope;
extern float	gtDelta_RTM_Slope_200us;
extern float	gi_pct_drop_RTM;
extern float	gILIM_200us_S;
extern float	gILIM_200us_pct_S;

/*======================    SR Comparator Variables    ====================================*/
extern float 	gSRth_pt_S;
extern int		gSRth_CODE;
extern float	gSRth_TARGET;
extern float	gSRth_exp_S;

/*======================    REQ Variables    ====================================*/
extern float	gREQ_0V;
extern float	gREQ_V_RingDet;
extern float	gREQ_V_Idle;
extern float	gREQ_V_Req;
extern float	gREQ_2V;
extern float	gREQ_V_LatchOff;
extern float 	gREQ_Vref_pt_S;
extern int		gREQ_Vref_CODE;
extern float	gVref_TARGET;
extern float	gVref_exp_S;

/*=======================    CV_CC_CB_Vout Function Variables    ===============================*/
extern float gISvth;
extern float MEAS_Isvth_FLAG;

/*=======================    VBP_Supply Function Variables    ===============================*/
extern float gVshunt_Init_Pr;
extern float gVshunt_Init_Se;
extern float gBPP_IS1_6p2_p;
extern float gBPP_IS1_VBPP_p;
extern float gBPP_IS2_VBPP_p;
extern float gISD;
extern float gVBPS_M, gVBPS_P;	//JD  redundunt variables
extern float gISD_s, gVSD_s;


/*=======================    IOV/UV Function Variables    ===============================*/

extern bool gIOV;

/*=======================    SOA Function Variables    ===============================*/
extern float VSOA_RM,
			 VSOA_RM_P,
			 VSOA_HT,
			 VSOA_HT_P,
			 VSDS_RM,	
			 VSDS_RM_P,
			 VSDS_HT;

/*=======================    STRESS Variables    ===============================*/
extern float	gILL_REQ_pre, 
				gILL_BPS_pre, 
				gILL_D_pre, 
				gILL_UV_pre, 
				gILL_SR_pre, 
				gILL_VO_pre, 
				gILL_FW_pre;
extern float	gILH_REQ_pre, 
				gILH_BPS_pre, 
				gILH_D_pre, 
				gILH_UV_pre, 
				gILH_SR_pre, 
				gILH_VO_pre, 
				gILH_FW_pre;
extern float	gIDS_FW_pre;

/*=======================    DATT Function Variables    ===============================*/
extern float	DATT_drain_current, DATT_pulse_time;
extern float	Norm_x_lim, Norm_n_lim;

extern int	Gage_pretrig_samples;

/*===========================    HandShake Variables    ===============================*/
extern float HANDSHAKE_Vd_TM   ,	// Set Drain pull up voltage. 
			 FW_NEG_LEV_TM		,	// Set FW desired negative level
			 HANDSHAKE_Vref_Low_Vd	,	// Set OVI_4 ref on InvSync
			 HANDSHAKE_Vd_NM,	// Set Drain pull up voltage. 
			 FW_NEG_LEV_NM	,	// Set FW desired negative level
			 HANDSHAKE_Vref_High_Vd;	// Set OVI_4 ref on InvSync

// +++++++++++++++++++++++++++++++++   Inno3X, InnoCHY variables  ++++++++++++++++++++++++++++++++//
extern int gInnoCHY; // DPG added //
extern int gInno3X; // DPG added //
extern int MYtempVar; // Debug only. //

// ======================  Gage Digitizer Variables=============================
extern int SAMPLE_RATE_Hz;
extern float SAMPLE_RATE_s;


//================== Omniswitch User Functions Headers START here ===============
void Close_relay(int);
void Open_relay(int);
void Open_All_Relays();
void Dump_IS_Data(char*,int,float,float);
void Dump_V_th_Data(char*,int,float,float);
void Dump_CC_th_Data(char*,int,float,float,float,float,float);
void Dump_Freq_Data(char*,char*,float,int,float,float);
void Find_Vfb_vs_Drain_Toff();
void Find_SOA_SDS_vs_Voltage();
void Convert_Alphanumeric_to_Float( float *AN_int_return, char *an1);
int  Alphanumeric_Lookup( char *an);


void mode_change(void);
void DDD_init();
void DDD_Load_Patterns();
void DDD_Load_Loop_Pattern();
void DDD_Load_Loop_Pulses(short, float);
void Run_Loop_Pulses();
void Stop_Loop_Pulses();
void DDD_Wait_Pattern_End(int start_address, int stop_address);

void Set_CC_gCS_TARGET( char *, float*, float*, float*);
void Powerup_to_read_Antifuse(float, float);
void Powerup_to_trim_primary();
void Powerup_to_trim_primary_Retrim();
void Powerdown_from_trim_primary();
void Trim_Anti_fuse_primary(float*);
void Trim_Anti_fuse_primary_Retrim(float*);
void DDD_Clock_UV_Antifuse(int);
void Find_VBP_vs_DrainCurrent();

void VBPP_Power_Up_w_Test_Mode(int, int);
void Powerup_Primary_in_Testmode(int);
void Observe_Vpin_Internal_Signals();
void Powerup_Secondary_in_Testmode(int, float, float);
void Power_Up_Secondary_Skip_WaitNListen(int, float);

void Power_Up_Primary_Observe_Mode(int);
void Power_Up_Primary_BypassWL_TM5(int);
void Power_Up_Primary_TM6(int);
void Power_Up_Primary_Normal_Mode(int);
void Power_Down_Secondary();
void Power_Down_Primary();
void Power_Down_Everything();
void Power_Down_Everything_Except_Buf_Clamp();

void Powerup_to_trim_secondary();
void Powerdown_from_trim_secondary();
void Trim_Anti_fuse_secondary(float*, int);
void Read_Anti_fuse_secondary(int , float *, float);
void Read_Secondary_AF_Reg (int * array_min_size_54);
void Write_Secondary_AF_Reg (int * array_min_size_54);
void AF_Zero_Out_CS_and_CB_bits (int * array_min_size_54);
void DDD_Clock_FB_Antifuse(int);
void DDD_Clock_Vout_Antifuse(int);
void Force_Neg_Pulses_FW_DVI (float, float);
void Force_Neg_Pulses_FW_DDD (float, float);
void Force_Neg_Pulses_FW_DDD_continuously();
void Force_FW_2NegPulses_n_1NegEdge_DDD (float, float);
void Force_FB_100kHz_Pulses_nTimes (int);
void Force_Vpin_Pulses_nTimes (int);
void Force_Vpin_Pulses_5_Times (float, float);
void Force_VpinOnly_Pulses_nTimes (int pulse_num);
void Secondary_Vout_Clock_to_Testmode(int);

void Skip_Wait_and_Listen();
void SyncHS_PowerUp_SkipWaitNListen(int, int);
void SyncHS_PowerUp_Secondary_NM_Primary_TM5_ByPassWL(int, int);
void SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(int);
void SyncHS_PowerUp_Secondary_in_Normal_Mode_Primary_TM5(int);
void SyncHS_PowerUp_Secondary_in_Test_Mode_SKIP_WAITnLISTEN(int, int);
void SyncHS_PowerUp_Secondary_in_Normal_Mode(int);
void SyncHS_PowerUp_Secondary_in_Test_Mode(int, int);
void SyncHS_PowerUp_Secondary_in_Test_Mode_MINNO(int, int);
void SyncHS_PowerUp_Secondary_in_ProgMode(int, int);
void SyncHS_PowerUp_Secondary_in_ProgMode_Skip_WaitNListen(int, int);
void Force_HandShake();
void Remove_HandShake();
void Sync_HandShake_Powerdown();
float Rdson_Buffer_Cal(float);
float iPV3_CC80_Cal(float, float);
void IS_250mA_Sequence(int, int, int);

void search_VBPP_th( float*, float*, float*, float*, float* );
void search_VBPP_th_B3( float*, float*, float*, float*, float*, float* );
void search_VBPS_P_th( float* );
void search_VBPS_M_th( float* );
void search_VBPS_M_th_Inno4( float* );
void search_VBPS_Reset(float *);
void search_VBPP_Reset(float *);
void VBPP_Negative_Cycle();
void VBPP_Power_Up(int);
void VBPP_ramp_up(float, float, float);
void VBPP_ramp_down(float, float, float);
void VBPS_ramp_up(float, float, float);
void VBPS_ramp_down(float, float, float);
void VBPS_Power_Up(float);
void Power_Up_Secondary(int, double);
void Power_up_Secondary_Test_Mode(float);
//void Secondary_Write_Mode_PowerUp();
void Secondary_Test_Mode_Vshunt_Power_up(double, double, double, double, double);
void Secondary_Power_TestModeSelect(float);
void VBPP_ILIM_NORM_Power_Up();
void search_CV_vFBth_AR(float *);
void search_CV_vFBth_AR_binary(float *, float *);
void search_CV_vVOUTth_AR_binary(float *, float *);
void search_tFB_ARdelay(float *);
void search_CV_HS_VOth(float *);
void search_CV_HS_FBth(float *);
void search_CV_CB_th( float*, int);
void search_CV_CB_th_Binary(float*, int);
void search_CV_TM18(float*, int);
void search_CV_DDD(float*);
void search_CV_VOUT_TM18(float*, int);
void search_ISVth_TM18(float vIS_Start, float* ISvth_th);
void search_ISVth_Linear(float vIS_Start, float* ISvth_th);
void search_down_ARST_th( float*);
void search_Vout_ARST_th( float*);
void search_ARST_th_TM20( float*);
void search_up_ARST_th( float*);
void search_ARST_th_Binary( float*);
void search_CC_th(float, float*);
void search_CC_th_using_IBPS(float iPV3, float*);
void search_ISvth(float, float*);
void search_ISvth_TM(float, float*);
void search_VoutKP_th(float, float, float *);
void search_Vout_CCRed_th(float, float, float*, float*);
void search_Vout_CCRed_th_NewMethod(float, float, float*, float*);
void search_Vout_th_TM(float, float*, float*);
void search_Vclamp_2pct_th( float*, float*);
void search_Vclamp_10pct_th(float*, float*);
void search_Vclamp_2pct_th_VO( float*, float*);
void search_Vclamp_10pct_th_VO(float*, float*);
void search_Vclamp_20pct_th_QC2(float*);
void search_Vclamp_20pct_th_QC2_VO(float*);
void search_Vclamp_2pct_th_QC3( float*, float*);
void search_Vclamp_10pct_th_QC3(float*, float*);
void search_Vclamp_20pct_th_QC3(float*);
void search_SR_th(float *);
void search_SR_th_TM1(float *);
void search_SR_th_Ramp_dn(float *);
void search_FWC_th(float *, float*);
void search_REQ_Vref_th(float, float, float *, float *);
void search_IOVp_Binary(float*);
void search_IOVp_Binary_TurretCB(float*);
void search_IOVp_linear_TM2(float*, float*, float*, float*);
void search_IOVp_linear_ProgMode(float*, float*, float*, float*);
//void ILIM_RxTx_PowerUp();
void WaitDelay_With_HandShake_Timing(int Offset_Time);
void tDable_Powerup();

void Check_InvSync_Circuit(int*);
void Connect_InvSyn_IM_New(int);
void Connect_InvSyn_IM(int);
void Disconnect_InvSyn_IM();

void Primary_Normal_Mode_Power_Up(int , float);
void Primary_Test_Mode_Power_Up(int, float);
void Setup_Ilimit_Pedestal(int);
void Create_Awav_xp ( char *, float *,int arr_size, float  samp_rate);
void Dump_Data(char	*, int, float, float, float, float);

void PV3_DriveOff_ChargeOn();
void PV3_Charge_On(int);
void PV3_Check_Charge(int);
void PV3_Connect_Drain_and_DriveON(float Vdrive);
void PV3_Disconnect_Drain_and_DriveOFF();

//=================== INNOSW XP gage digitizer Headers ===================
void INNO_Gage_ChanAB_setup(float);
void INNO_Gage_ChanB_setup(float);
void INNO_Gage_ChanB_ToffMax_setup( );
void Gage_Capture_Ilim(int, float);
void Gage_Capture_Ilim_SSS(int, float);
void Gage_Find_Ilim(float *, float *, float *, float *, float *);
void Gage_Find_Ilim_MINNO(float *, float *, float *, float *, float *);
void Gage_Find_Ilim_Turret(float *, float *, float *, float *, float *);
void Gage_Find_Ilim_18kHz(float *, float *, float *, float *);
void Gage_Find_Ilim_SSS(float *, float *, float *, float *, float *, float *, float *, float *, float *, float *);
void Gage_Find_Ilim_SSS_MINNO(float *, float *, float *, float *, float *, float *, float *, float *, float *, float *);
void Gage_Find_Ilim_SSS_Turret(float *, float *, float *, float *, float *, float *, float *, float *, float *, float *);
void Gage_Find_Ilim_ramp(float *, float *, float *);
void Gage_Find_SOA(float *, float *);
void Gage_Find_SDS(float *, float *, float *);
void Gage_Find_FWPK_4Rings_DableON_Timer(float *, float *, float *, float *);
void Gage_Find_FWPK_4Rings(float *, float *);
void Gage_Find_FWPK_4Rings_Turret(float *, float *);
void Gage_Find_FWPK_DableON_Timer(float *, float *);
void Gage_Find_tReqInhibit(float *, float *, float *, float *, int *);
void Gage_Count_Cycles(float *);
void Gage_Count_Cycles_CHB(float *);
void Gage_Find_DChUp(float *);
void Gage_Find_tOVL(float *);
void Gage_Find_tOVL_Turret(float *);
void Gage_Find_tHandshake(float *, float *, float *);
void Gage_Reset_Channels_AB_raw_data();
char* GetCSVPath (const char* dllpath, const char* csvname);



//=================== XP gage PIPULSE Definition STARTS here ===================

//PIPulse class to replace Pulse class removed by LTXC for VATE 7.0 release
enum
{
	PULSE_RISING_EDGE,
	PULSE_FALLING_EDGE,
};
class PIPulse
{
	private:
		int logic ;
		double pulse_width_in_seconds;
	public:
		PIPulse(int logic_ = 0, double pulse_width_ = 10e-6 )
		{	
			logic=0;
			pulse_width_in_seconds=pulse_width_;
		}
		~PIPulse(){};
		bool	do_pulse(void);
};
//=================== XP gage PIPULSE Definition ENDS here ===================
extern	CSHANDLE	hSystem;

//=================== XP gage digitizer func Header STARTS here ===================
void	Gage_init();
void	Gage_Setup_Acquisition_xp ( int sample_rate_in_Hz, int sample_size );
void	Gage_Capture_Data( );
void	Gage_Setup_Chan_A ( int pk_pk_range_in_mV );
void	Gage_Setup_Chan_B ( int pk_pk_range_in_mV );
int		gage_input_control_xp (int16 channel, int16 enable, int16 coupling, int16 gain);
//int		gage_trigger_control_xp (int16 source, int16 ext_coupling, int16 ext_gain, int16 slope, int16 level, int32 depth);
int		gage_trigger_control_xp (int16 source, int16 ext_coupling, int16 ext_gain, int16 slope, float level, int32 depth);
void	Gage_Commit ( void );
void	Gage_Start_Capture( void );
void	Gage_Wait_For_Capture_Complete( void );
void	Gage_Wait_For_Capture_Complete_ET( void );
void	Gage_Transfer_Data ( int channel_num );
void	Gage_Transfer_DataM ( int channel_num );
void	Gage_Transfer_Data_ilim_states ( int channel_num );
void	Gage_print_error(string text_str);
void	Gage_print_setup(string text_str);
int     Gage_loadtime_setup(void);
void	Gage_cal_table_setup_xp();
void	PrintCaptureTime(string text_str);
//=================== XP gage digitizer func Header ENDS here ===================

//**********   unit definitions   **********
#define V  *(1.0)
#define mV *(1.0e-3)
#define uV *(1.0e-6)

#define A  *(1.0)
#define mA *(1.0e-3)
#define uA *(1.0e-6)
#define nA *(1.0e-9)
#ifndef pA
	#define pA *(1.0e-12)
#endif

#define S  *(1.0)
#define mS *(1.0e-3)
#define uS *(1.0e-6)
#define nS *(1.0e-9)

#define GHz *(1.0e9)
#define MHz *(1.0e6)
#define KHz *(1.0e3)
#define kHz *(1.0e3)
#define Hz  *(1.0)

//**********   START of Unified Resource Control   **********//
#define DEFAULT_VALUE -999

typedef enum pin_resource{
	// *** Primary Side Resources
	res_D_dvi,				// DVI_11_0		Drain
	res_BPP_dvi,			// DVI_11_0		BPP for breakdown test
	res_BPP_ovi,			// OVI_1_0		BPP
	res_VPIN_ovi,			// OVI_1_1		UV

	// *** Secondary Side Resources
	res_FWC_dvi2k,			// DVI_13_0		FWC
	res_REQ_ovi,			// OVI_1_2		REQ
	res_BPS_dvi,			// DVI_9_1		BPS
	res_SR_dvi2k,			// DVI_13_1		SR
	res_VO_dvi,				// DVI_9_0		VO
	res_FW_dvi,				// DVI_11_1		FW
	res_ACK_ovi,			// OVI_1_5		ACK

	// *** High Voltage Resources
	res_BV_hvs,				// HVS_15		D, UV, FW

	last_vi,				// resources below this line will not be reset V

	// *** Other Resources
	res_InvSyn_REF_ovi,		// OVI_1_4		InvSyn_IM reference OVI
	res_InvSyn_Offset_ovi,	// OVI_1_6		InvSyn_IM GND offset OVI
	res_BC_ovi,				// OVI_1_3		Buffer Clamp reference OVI
	res_Iped_dvi,			// DVI_11_0		Pedestal curent DVI
} resource_t;

enum // MEASURE_MODE
{
	MEASURE_VOLTAGE,
	MEASURE_CURRENT,
};

void Set_Vrange(resource_t resource, char force_range);
void Set_Irange(resource_t resource, char force_range);
char Get_Vrange(resource_t resource);
char Get_Irange(resource_t resource);
void Set_Default_Vrange(void);
void Set_Default_Irange(void);
void Set_Default_VIrange(void);
void Set_V(resource_t resource, float v_in, unsigned long settling_us = 0);
void Set_I(resource_t resource, float i_in, unsigned long settling_us = 0);
void Set_VI(resource_t resource, float v_in, float i_in, unsigned long settling_us = 0);
void Reset_V(void);
void Reset_I(void);
void Reset_VI(void);
float Meas_VIaverage(resource_t resource, unsigned char mode, unsigned short samples = 10, unsigned long settling_us = 10, char range = -1);

//**********    END of Unified Resource Control    **********//
