/************************************************************************************
 *			POWER INTEGRATION INNOSWITCH3-MX FAMILY TEST PROGRAM HISTORY			*
 ************************************************************************************
06/27/17  ET  v0.00      - Checking out Inno3_MX using INNO3X V2.11u program.
08/31/17  ET  v0.01      - Roll-in INNO3X V2.24F program.
09/05/17  ET  v0.01a     - Release for KJ to continue Primary side development
09/xx/17  ET  v0.02a     - Secondary side development
11/30/17  ET  v0.03a     - Merge Primary and Secondary code
12/18/17  ET  v0.03b     - Added SR and REQ to .lst, improved Fosc_S
01/22/18  KJ  v0.03e     - Merge Primary and Secondary code
01/30/18  ET  v0.03f     - Added FWC
02/08/18  ET  v0.03g     - Commented out non working tests for PD to generate samples
03/20/18  ET  v0.03h     - Fixed SR_Delay
05/16/18  ET  v0.03i     - H/W mod, map ACK to K38_pin2 and REQf to K36_pin2
                         - Implemented FWC_delay
05/22/18  ET  v0.04a     - merged in KJ's code
05/24/18  ET  v0.04b     - use trimsops v1.3,new tests for MINNO_S DX112B
07/02/18  ET  v0.04c     - merged KJ's code
07/05/18  KJ  v0.04d     - Fixed BPS IS2 switching current test in IBP supply function
07/10/18  KJ  v0.04e     - Updated program to use TrimOps Table Rev 1.4 
					     - Modified search algorithm for VBPS_M  
                         - Fixed BPS IS1 non-switching current test
						 - Disable REL_FLOW pass parameter from setup func.  DOPL bit from trimops table to decide REL_Flow or not.
07/11/18  KJ  v0.04f     - Commented out BPS charge current tests at different BPS voltage levels(not to be tested for MINNO secondary)
07/20/18  ET  v0.04g     - Modified Feature_Trim_S so it is easier to maintain
07/27/18  KJ  v0.04h     - Fixed tlineOV_fast test. Modified LB with zener diode and resistor between REQ and DDD
08/06/18  KJ  v0.04i     - Added condition to use Rped2 for ILIM SSS tests for sizex5,x6,x7(IM used from INNO3X)
08/17/18  KJ  v0.04j     - Fixed ILIM jitter tests. Modified search algorithm
                         - Implemented HVS check test in Setup function
08/24/18  KJ  v0.04k     - Fixed audible noise test
09/11/18  ET  v0.05a     - Release for DX112B1 parts screening, INN3465C, INN3466C, INN3476C, INN3468C
09/24/18  KJ  v0.05b     - Increased drive voltage Vind for sizex8 at 4300 for ILIM+1 test
09/26/18  ET  v0.05c     - Fixed ISR Rpu test
10/11/18  KJ  v0.05d     - Added condition to disable testing if Invsync check fails
10/12/18  ET  v0.05e     - Added 2.4A/2.6A Size 8 DLM and GaN trimops
10/17/18  ET  v0.05g     - Included STRESS test, tidy up Leakage.cpp and trimops table 1.7
10/24/18  KJ  v0.05h     - Updated trimops table 1.8 as per new DLM evaluation experiment requirements
10/26/18  KJ  v0.05i     - Added INN3477C.prg - size7,725V  and trimops table 1.9 - Updated stress current 
                           clamp for size 5,6,7 to 800uA as per new DLM stress table
						 - Uncomment Drain stress current measurement in BV_Drain.cpp 
						 - gStress_ON = 0 in setup.cpp
10/29/18  KJ  v0.05j     - Added condition for size 5,6,7 to use Rped2 for DLM evaluation experiment, ILIM and ILIM_Pt
11/02/18  KJ  v0.05k     - Modified RXTX test method to improve stability for 725V devices
11/05/18  KJ  v0.05l     - Modified SOA/SDS tests for size7,725V devices.
                         - Trimops table 2.0
11/08/18  KJ  v0.05m     - Updated condition to use Rped1 for ILIM SSS tests for sizex5,x6,x7(IM used from INNO3X)
						 - Temporary commented out ISR_pullup and Rpu tests
						 - Temporary uncommented g_Stress_Passed=1 in Stress.cpp function
						 - Disabled dynamic ILIM limits selection
						 - Temporary diabled BV Vpin test
11/21/18  KJ  v0.05n     - Trimops table 2.1(IOV+ target 112uA)
						 - 4501 Limits update
						 - Modified IOV pre-trim test to use KC5 relay to improve repeatability
						 - Fixed STRESS test
11/27/18  KJ  v0.05o     - Implemented BPP Cap Check similar to InnoPro. If BPP Cap not connected properly, datalog "-99" to VcontBPP.
						 - Vpin BV test enabled
						 - STRESS test enabled for REL and stress evaluation Hcodes
11/29/18  ET  v0.05p     - Enable STRESS test for virgin DUT only, include LB_Type_Rev,CB_Type_Rev,IB_Type_Rev, Hcode datalog. Updated some limits for rel
						 - Updated trimops table to rev 2.2, comment out unused Hcode and added new engineering Hcode
12/05/18  KJ  v0.05q     - Modified SOA search starting voltage for size x8
						 - Use Rped2 only for sizex8 2400 ILIM
						 - Limit update for Hcode test in STRESS.prg and POST_STRESS.prg
						 - Enable stress test for trimmed and untrimmed unit for special case INN3468C-HZ12
12/19/18  KJ  v0.05r     - 4501 Limits update for soft-start tests 
01/04/19  KJ  v0.05s     - ILIM target changed to 1950mA in trimops table for INN3477C-HY04
						 - Trimops table rev 2.3
01/10/19  KJ  v0.05t     - Trimops table rev 2.4
                         - Program modified to accept both Rev9 and Rev10 loadboards
02/07/19  KJ  v0.05u     - Latest Trimops table rev 2.4, from EeFu and Toine
02/18/19  KJ  v0.05v     - SR_th tests updated to use Testmode11
03/19/19  ET  v0.06a     - rev 10 LB, modified ILIM algorithm
04/19/19  KJ  v0.06b     - Limits update for BPP_IS2 STRESS test for INN3465C.prg
                         - STRESS test disabaled
						 - VSOA search starting voltage change for sizex5
04/24/19  KJ  v0.06c     - Fixed ILIM issue of part going into ILIM+1 mode when measuring ILIM_norm
05/01/19  KJ  v0.06d     - Fixed VBPS_Reset test unstability issue. Test method changed
                         - ILIM tests modified- soft-start algorithm
05/13/19  ET  v0.06e     - Added BV_Drain_900V for MINNO-GaN and created .prg for MINNO-GaN
						 - Updated .prg files with latest .lst file
						 - Added code to detect and init HVS19
						 - Added HVS checker code for HVS19 if detected
						 - Updated setup.cpp to capture hardware ID
						 - Removed some redundant variables and functions in setup.cpp and user.cpp (inherited from INNO3X)
						 - Updated IzPre.cpp, IzPost.cpp, Feature_Trim_P.cpp for GaN
						 - Further improvement on ILIM (ipeak detection) algorithm and apply to ILIM18K
						 - SR threshold test method is now selectable
						 - Updated trimops table to revision 2.6 to align with datasheet part marking
05/15/19  ET  v0.06f     - Updated INN3464C.prg, INN3467C.prg and INN3468C.prg
						 - Enable Size8 to select between 1.85A and 2.2A ILIM target by selecting different inductor
						 - Some timing adjustment on ILIM test
05/16/19  KJ  v0.06g     - STRESS test enabled
                         - STRESS test updated for BPS_IS2 measurement to resolve the issue with Size x4
05/22/19  ET  v0.06g     - Updated INN3475C.prg, INN3476C.prg and INN3477C.prg
						 - Separate the reporting of 650V and 725V in BV_Drain.cpp
						 - inline retest key tests like Fosc_pt_S, ILIM_Pt_P, ILIMs upto 3 times to improve Bin1
05/23/19  ET  v0.06h     - Added INN3468C-HR10 for DOPL test in trimops table, created INN3468C_REL.prg
05/17/19  CX  v0.06e CXa - Added coding for following test "Hold_off" "No_Pulse" "tLOfilter"
05/20/19  CX  v0.06e CXb - Added coding for tDable_300kHz and tDable_1MHz
05/21/19  CX  v0.06e CXc - Added coding for tDable_300kHz and 1MHz _1stR.  fail 1MHz_1stR intermittently.
05/24/19  CX  v0.06e CXd - Update coding to pass 300kHz/1MHz _1stR and tLOfilter consistently
05/31/19  ET  v0.06j     - merge code from CX (above) and code from KJ (STRESS.cpp)
						 - Updated trimops table to revision 2.8

History Revisions (Above)
*/

//==============================================================================
// USER.CPP
//==============================================================================
// include this nafxcwd.lib in linker->input-> ignore specific library for linker problem
// after ATE Generate Source Code

#define INNO3_MX			// uncomment for InnoSwitch3-MX test programs
#define PRG_FAMILYNAME		"Inno3_MX"
#define PRG_REVISION		"0.06j"
#define TRIMOPS_REVISION	"2.8"

#include "asl.h"
#include "USER.H"
#include "piclasses.h"
#include "piautocorr.h"
#include "PIserial.h"
#include "PITrimOptions.h"

//#include "stdafx.h"
//#include <malloc.h>
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <direct.h>
//#include <conio.h>

#include "userinfo.h"	// added for login. See "user_start_test"

// Disable warning C4244 "conversion from 'const double' to 'float', possible loss of data"
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)

ModalDialogDescription mdb;		// Create class object, allocate memory. 	Credence function

extern "C" __declspec(dllexport) void user_init (void);
extern "C" __declspec(dllexport) void user_load (void);
extern "C" __declspec(dllexport) void user_start_lot (void);
extern "C" __declspec(dllexport) void user_wait_sot (void);
extern "C" __declspec(dllexport) void user_start_test (void);
extern "C" __declspec(dllexport) void user_before_binning (void);
extern "C" __declspec(dllexport) void user_end_test (void);
extern "C" __declspec(dllexport) void user_next_device (void);
extern "C" __declspec(dllexport) void user_end_lot (void);
extern "C" __declspec(dllexport) void user_exit (void);
extern "C" __declspec(dllexport) void user_dut_power_off (void);
extern "C" __declspec(dllexport) void user_dut_power_on (void);
extern "C" __declspec(dllexport) void user_F12 (void);

#if defined(CSC_SITEBASE) && ((CSC_SITEBASE == 0) || (CSC_SITEBASE == 1))
const bool IsSiteSet = vISetSharedData::SetSiteBase(CSC_SITEBASE);  // This sets the systems Site Base
#elif defined(CSC_SITEBASE)
#error Invalid CSC_SITEBASE!
#endif

int g_pid = 0;  // Not really a global, but watch sheets need this exact name.

//{ASL_CREATE BEGIN BOARDS_FROM_LIST_PROPERTIES
// Regenerating source code will change the code between here and ASL_CREATE END BOARDS_FROM_LIST_PROPERTIES}
// Use the List Properties dialog to drive the changes to this code.
Ovi * ovi_1;
Pv3 * pv3_4;
Tmu * tmu_6;
Ddd * ddd_7;
Dvi * dvi_9;
Dvi * dvi_11;
Dvi * dvi_13;
Mux * mux_14;
Hvs * hvs_15;
Mux * mux_20;
 
void board_ptr_init(void)
{
	ovi_1 = &ovi_cards[board_ptr[BOARD_1]];
	pv3_4 = &pv3_cards[board_ptr[BOARD_4]];
	tmu_6 = &tmu_cards[board_ptr[BOARD_6]];
	ddd_7 = &ddd_cards[board_ptr[BOARD_7]];
	dvi_9 = &dvi_cards[board_ptr[BOARD_9]];
	dvi_11 = &dvi_cards[board_ptr[BOARD_11]];
	dvi_13 = &dvi_cards[board_ptr[BOARD_13]];
	mux_14 = &mux_cards[board_ptr[BOARD_14]];
	hvs_15 = &hvs_cards[board_ptr[BOARD_15]];
	mux_20 = &mux_cards[board_ptr[BOARD_20]];
}
 
void board_hardware_init(void)
{
	ovi_1->init();
	pv3_4->init();
	tmu_6->init();
	ddd_7->init();
	dvi_9->init();
	dvi_11->init();
	dvi_13->init();
	mux_14->init();
	hvs_15->init();
	mux_20->init();
}
//ASL_CREATE END BOARDS_FROM_LIST_PROPERTIES}

// This file must be present even if no user code is placed below
// Below are a number of routines that are called by the main program at
// various times. If the user needs to initialize any variables, or check for
// any situations during these times he may "fill in the blanks".

// **************************************************************************

/* ======================  Dual HVS configuration ============================*/
Hvs * hvs_19;		// Placed here to avoid being overwritten when regenerate source code in List

/* ======================  VIs and Channels Mapping ============================*/
// *** Primary Side Resources
Dvi *D_dvi;								// DVI_11_0		Drain
Dvi *BPP_DVI;							// DVI_11_0		BPP for breakdown test
Ovi *BPP_ovi;							// OVI_1_0		BPP 
Ovi *VPIN_ovi;							// OVI_1_1		UV

// *** Secondary Side Resources
Dvi *FWC_dvi2k;							// DVI_13_0		FWC
Ovi *REQ_ovi;							// OVI_1_2		REQ
Dvi *BPS_dvi;							// DVI_9_1		BPS
Dvi *SR_dvi2k;							// DVI_13_1		SR
Dvi *VO_dvi;							// DVI_9_0		VO
Dvi *FW_dvi;							// DVI_11_1		FW
Ovi *ACK_ovi;							// OVI_1_5		ACK

// *** Other Resources
Ovi *InvSyn_REF_ovi;					// OVI_1_4		InvSyn reference OVI
Ovi *InvSyn_Offset_ovi;					// OVI_1_6		InvSyn GND offset OVI
Ovi *BC_ovi;							// OVI_1_3		Buffer Clamp reference OVI
Dvi *Iped_dvi;							// DVI_11_0		Pedestal curent DVI


// *** Primary Side Channels
int	D_ch	= DVI_CHANNEL_0,			// DRAIN DVI_11_0
	BPP_ch	= DVI_CHANNEL_0,			// Primary BYPASS: Both OVI and DVI are channel 0 DVI_11_0 and OVI_1_0
	VPIN_ch	= OVI_CHANNEL_1;			// UV OVI_1_1

// *** Secondary Side Channels
int	FWC_ch	= DVI_CHANNEL_0,			// FWC DVI_13_0
	REQ_ch	= OVI_CHANNEL_2,			// REQ OVI_1_2
	BPS_ch	= DVI_CHANNEL_1,			// BPS DVI_9_1
	SR_ch	= DVI_CHANNEL_1,			// SR  DVI_13_1
	VO_ch	= DVI_CHANNEL_0,			// VO  DVI_9_0
	FW_ch	= DVI_CHANNEL_1,			// FW  DVI_11_1
	ACK_ch	= OVI_CHANNEL_5;			// ACK OVI_1_5

// *** Other Resources Channels
int	InvSyn_ch			= OVI_CHANNEL_4,	// InvSyn reference OVI_1_4
	InvSyn_Offset_ch	= OVI_CHANNEL_6,	// InvSyn GND offset OVI_1_6
	BC_ch				= OVI_CHANNEL_3,	// Buffer Clamp OVI_1_3
	Iped_ch				= DVI_CHANNEL_0;	// Pedestal current DVI_11_0


/* ======================  TEC Temperature Controller variable  ============================*/
int		gTEC_enable = 0;				// Flag to enable TEC temperature controller

/* ======================  Test Hardware ID Parameters  ============================*/
// Read from hardware ID
int		gLB_ID,							// Loadboard ID
		gCB_ID,							// Contactor ID
		gIB_ID;							// Inductor ID

int		LB_Type,						// Loadboard type for hardware ID
		LB_Rev,
		IB_Type,						// Inductor type for hardware ID
		IB_Rev,
		CB_Type,						// Contactor type for hardware ID
		CB_Rev,
		TB_Type,						// Testblock type for hardware ID
		TB_Rev;

double	gLB_Type_Rev,					// LB_Type_Rev = LB_Type	+ (LB_Rev / 100)
		gCB_Type_Rev,					// CB_Type_Rev = CB_Type	+ (CB_Rev / 100)
		gIB_Type_Rev,					// IB_Type_Rev = IB_Type	+ (IB_Rev / 100)
		gTB_Type_Rev;					// TB_Type_Rev = TB_Type	+ (TB_Rev / 100)

// Read from TrimOptions Table
int		BoardType,					// Loadboard type for hardware ID
		BoardRev,
		InductorType,					// Inductor type for hardware ID
		InductorRev,
		ContactorType,					// Contactor type for hardware ID
		ContactorRev,
		TestBlockType,					// Testblock type for hardware ID
		TestBolckRev;

int		gManual_Handler	= 0;			//is handler set to "Manual"?
int		gRasco_Handler	= 0;
int		gTurret_Handler	= 0;
char	*h_name;						// Handler Name

/* ======================  Trim Option Table variable  =============================*/
STRING	Trimops_Table_Rev = 0;

/* ======================  Die Parameters  =========================================*/
int		MOSFET_SIZE	= 0;
int		gDevNum		= 0;
int		gDLM_BV		= 0;
int		gDLM_Size	= 0;
bool	gGaN		= false;

/* ======================  Test Flow Control Parameter  ============================*/
bool	First_Time_Run	= true;
bool	AbortTest		= false;
int	 TRIM_ENABLE	= 0;
char *Dev_id;
char *gH_code;
char *gHC_code;
char *gHZ_code;
char *PrgRev;
char *FamilyName;
int	 gDevFamily		=0;
char OperCode[50]	={0};
char DevName[50]	={0};
int  OPCODE			= 0;
int  gREL_FLOW       =0;
int  Golden_Unit_Prg =0;
int  gHas_Var_AR_Func =0;
int  gHas_Fixed_AR_Func=0;
int  gHas_AR_Delay=0;
int  ours_ENG_Option =0;
int	 gCHAR_FLOW=0;
int	 gTrimmed_Device=0;
int  g_TurretCB = 0;
int  g_GRR      = 0;
int  g_Setup_OK = 0;
int	ours_SiliconRev_S;
int ours_SiliconRev_P;
int g_Check_InvSync_Circuit = 0;
int g_ReTrim_P = 0;
int skiphvs =0;
int hvsflag =0;

/*=======================   Sampling Variables    ===============================*/
int	  gDATT_FAIL=0;
int	  gQty_Pass_DATT=0;
int	  gDATT_Loop_Count=0;

/* ======================  Debug Parameters ============================*/
double ours_v_debug = 0;
double ours_i_debug = 0;
double ours_ms_debug= 0;
bool   BPP_4p7uF = false;
bool   BPP_p47uF = false;

/* ======================  Setup Variable  ============================*/
STRING CURRENT_SERIAL_NUM; 
int   SERIAL_NUM=0;
int   gFuncNum=0;
int	  gDisplay_FuncNum=0;
int	  gDisplay_ErrDlog=0;

/* ======================  Trimming Variable  ============================*/
float gTrim_Voltage = 0.0;
float gAF_2ND_TRIM_TRHD  = 0.0;			// 5uA
float gAF_1ST_TRIM_DELAY = 0.0;			// Should be 20ms
float gAF_2ND_TRIM_DELAY = 0.0;

/*=======================    Test Debug Variables    ===============================*/
CMicroTimer mytimer;					
LONGLONG starttime;
LONGLONG stoptime, stoptime1;
int DEBUG =0;
int gDEBUG=0;
char *Func_name;
char *WAVE_NAME = "NoWaveName"; 

/*=======================    Golden Unit Variables    ===============================*/
bool GoldenUnit = false;

/*=======================		DDD Variables		 ===============================*/
float Dclk_period  = 0.25e-6;		// DDD clock period
//float Dclk_period  = 0.125e-6;		// DDD clock period
float DDD_Vref	=	  0.0;			// DDD voltage reference 2.5V

int First_address, Last_address;
int Low_pat_start, Low_pat_stop, 
	Low_pat_start_dummy, Low_pat_stop_dummy, 
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
	FWPK_neg_0p50us_pulse_start, FWPK_neg_0p50us_pulse_stop,
	
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
	FWPK_p5us_Ring_pulse_start,	  FWPK_p5us_Ring_pulse_stop,
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
	AF_ClkVout_start,AF_ClkVout_stop,First_Clk_Edge=0,
	VO_Low_Pulse_Start, VO_Low_Pulse_End,
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
	ILIM_UPMED_132kHz_SRCH_ADDR,
	ILIM_RAMP_100kHz_start,	ILIM_RAMP_100kHz_stop,
	ILIM_UPMED_100kHz_SRCH_ADDR,
	FB_MINNO_SSS_pulse_start, FB_MINNO_SSS_pulse_stop;//MINNO Soft Start test REQ pattern new

	int FB_18kHz_pulse_start;
	int FB_18kHz_pulse_stop;
	int Vout_18kHz_pulse_start;
	int Vout_18kHz_pulse_stop;
	int FB_125kHz_pulse_start;
	int FB_125kHz_pulse_stop;
	//int Vout_125kHz_pulse_start;
	//int Vout_125kHz_pulse_stop;
	int FB_125kHz_pulse_start_X;
	int FB_125kHz_pulse_stop_X;
	int FB_100kHz_ILIM_pulse_start_X;
	int FB_100kHz_ILIM_pulse_stop_X;
	int Vpin_6clocks_start;
	int Vpin_6clocks_stop;
	int Vpin_4clocks_start;
	int Vpin_4clocks_stop;
	int Vpin_2clocks_start;
	int Vpin_2clocks_stop;
	int Vpin_3NegClocks_start;
	int Vpin_3NegClocks_stop;
	int Vpin_30usec_start;
	int Vpin_30usec_stop;
	int Vpin_one_30us_clock_start;
	int Vpin_one_30us_clock_stop;
	int FBpin_30usec_start;
	int FBpin_30usec_stop;
	int FB_100kHz_pulse_start_5X;
	int FB_100kHz_pulse_stop_5X;
	int FW_100kHz_pulse_start_40X;
	int FW_100kHz_pulse_stop_40X;

int gDDD_loop_end;
int gDDD_loop_pulses_stop;

/*=======================    Internal Registers   ===============================*/
int gVpin_Internal_Signal[16]	={0};	//Primary Internal Registers
int gSR_Internal_Signal[100]	={0};	//Secondary Internal Registers

int gVpin_AF[100]				={0};	// Primary AF data pre-trim
int gVpin_AF_post[100]			={0};	// Primary AF data post-trim
int gSR_AF[100]					={0};	// Secondary AF data pre-trim
int gSR_AF_post[100]			={0};	// Secondary AF data post-trim
float gIZ_AF_post_P[100]		={0};	// Primary AF current
float gIZ_AF_post_S[100]		={0};	// Current AF current

/*=======================    Characterization Variables    ===============================*/
bool gCharacterization = true;

/*=======================    CV_CC_CB_Vout Function Variables    ===============================*/
float	gGNDRes_Se			=0.0;
float	gCC_trim_weight[64] ={0.0};	//trim weight define in CC_Trim function and use at CV_CC_CB_Vout function Vout_th_Red1_TM
int		gCC_trimcode		=0.0;	//Decode from Izpost function and use in CV_CC_CB_Vout function for Vout_th_Red1_TM

/*=======================    BVD Function Variables    ===============================*/
float	scaled_ifrc=0.0;
float	gBVD_Room=0.0;
float	gBVD_Hot=0.0;

/*============================    VBP function   ===============================*/
float gVshunt_BPP =0.0, gVshunt_BPS =0.0;
float gVBPP_P_Init =0.0, gVBPP_P_final=0.0, gVBPS_P_Init =0.0,  gVBPS_final=0.0, 
	  gVBPP_M_Init =0.0, gVBPS_M_Init =0.0, gVBPP_PV_Init=0, gVBPP_PV_final=0,
	  gVBPP_P_s_final =0.0;
float gVBPP_VCEN=0.0, gVBPS_VCEN=0.0;
float gIBPS_nsw=0.0, gIBPS_sw=0.0;
float gVBPP_Low_Voltage_PU =0.0; 
float gVBPS_M = 0, gVBPS_P=0.0;  //JD will take out this later (duplicate of init global variables)

/*============================    BV_Drain_900V Variables    =================================*/
int disable900V = 1;		// Assume single HVS setup

/*============================    Stress Function Global Variables   ===============================*/
bool gStress_ON=0;
bool g_Stress_passed=0;

/*============================    Timing Global Variables   ===============================*/
float gDly_Wait_and_Listen_Normal_Mode = 0.0;
float gDly_Wait_and_Listen_Test_Mode = 0.0;
float g_readTime_p =0.0;
float g_readTime_s =0.0;
float g_trimTime_p =0.0;
float g_trimTime_s =0.0;
float g_StartTime  =0.0;
float g_StopTime   =0.0;
float g_Time_Diff  =0.0;
int	  g_tHandshake_SSS =0.0;
float g_tHandshake_SSS_floating =0.0;

ofstream dumparray;

/*============================    Anti-Fuse Variables   ===============================*/
//Primary
int gP_AF_Start_Addr_Primary			=0,
	gP_AF_Start_Addr_IOV				=0,
	gP_AF_Start_Addr_ILIM				=0,
	gP_AF_Start_Addr_TonMax				=0,
	gP_AF_Start_Addr_tOVL				=0,
	gP_AF_Start_Addr_Freq				=0,
	gP_AF_Start_Addr_IuvIov_Disable		=0,
	gP_AF_Start_Addr_Iuv_10uA			=0,
	gP_AF_Start_Addr_UV_400ms_dly		=0,
	gP_AF_Start_Addr_LatchOFF_aft_AR	=0,
	gP_AF_Start_Addr_Disable_AR			=0,
	gP_AF_Start_Addr_didt_comp			=0,
	gP_AF_Start_Addr_OT_Hys_30C			=0,
	gP_AF_Start_Addr_LatchOFF_w_OT		=0,
	gP_AF_Start_Addr_Disable_ILIM_Select=0,
	gP_AF_Start_Addr_Select_ILIM_Incr	=0,
	gP_AF_Start_Addr_minus_20pct_ILIM	=0,
	gP_AF_Start_Addr_plus_20pct_ILIM	=0,
	gP_AF_Start_Addr_Samsung_Mode		=0,
	gP_AF_Start_Addr_OTP				=0,
	gP_AF_Start_Addr_SDS_OFF			=0,
	gP_AF_Start_Addr_Rcv				=0,
	gP_AF_Start_Addr_Driver_Size		=0,
	gP_AF_Start_Addr_Rsense_up			=0,
	gP_AF_Start_Addr_Vx_adjust			=0,
	gP_AF_Start_Addr_ILIM_Ratio			=0,
	gP_AF_Start_Addr_ILIM_TC			=0,
	gP_AF_Start_Addr_AR_Request			=0,
	gP_AF_Start_Addr_ZF					=0;

//GaN Primary
int gP_AF_Start_Addr_ZVS_Ton			=0,
	gP_AF_Start_Addr_ZVS_Trim			=0,
	gP_AF_Start_Addr_ZVSon				=0,
	gP_AF_Start_Addr_UV					=0,
	gP_AF_Start_Addr_ZVSdelaym20		=0,
	gP_AF_Start_Addr_IlimLEB			=0,
	gP_AF_Start_Addr_VpinCTRL_iREF20pct	=0,
	gP_AF_Start_Addr_ZVS_Delay			=0,
	gP_AF_Start_Addr_SDSpct				=0;

//Secondary
int	gSecondary_AF_Addr_Start			=0,
	gFosc_AF_Addr_Start					=0,
	gFosc4_AF_Addr						=0,
	gPK_ssSpeed_AF_Addr_Start			=0,
	gCV1_AF_Addr						=0,
	gDVesrSlpAdj_AF_Addr_Start			=0,
	gPK_AF_Addr_Start					=0,
	gCP_AF_Addr_Start					=0,
	gPS_AF_Addr_Start					=0,					
	gTFB_AF_Addr_Start					=0,					
	gCC_AF_Addr_Start					=0, 
	gKP_AF_Addr_Start					=0,
	gSL_AF_Addr_Start					=0,
	gCS_AF_Addr_Start					=0, 
	gCB_AF_Addr_Start					=0,	
	gCV_AF_Addr_Start					=0, 
	gCV2_AF_Addr_Start					=0, 
	gAR_AF_Addr_Start					=0,
	gSCEN_Addr_Start					=0,
	gCBEN_Addr_Start					=0,
	gDsoftEn_Addr_Start					=0,
	gDOPL_AF_Addr_Start					=0,
	gOVLO_Addr_Start					=0,
	gVR_Addr_Start						=0,
	gCR_Addr_Start						=0,

	gCCAR_Addr_Start					=0,
	gESRsel_Addr_Start					=0,
	gDdampEn_Addr_Start					=0,

	gXFWPK_AF_Addr_Start					=0,
	gSpare_Addr_Start					=0,
	gZF_S_Addr							=0,
	
	gRnw_AF_Addr_Start					=0,
	gRnwFine_AF_Addr_Start				=0,
	gFWC2_AF_Addr_Start					=0,
	gNoFWC100mV_AF_Addr_Start			=0,
	gCap_AF_Addr_Start					=0,
	gPKdig_AF_Addr_Start				=0,
	gSRth_AF_Addr_Start					=0,
	gVshunt_AF_Addr_Start				=0,
	gVref_AF_Addr_Start					=0,
	gIintTC_AF_Addr_Start				=0,
	gREQlow_AF_Addr_Start				=0,
	gLO_dis_AF_Addr_Start				=0;

/*============================    Feature Trim Variables   ===============================*/
float	gHcode=0,
		gHCcode=0,
		gH_code_AN=0,
		gHZ_code_AN=0;

int		gTrim_iov_Off_P		=0,
		gTrim_iuvMinus_P	=0,
		gTrim_uvDelay_P		=0,
		gTrim_Loff_AR_P		=0,
		gTrim_DisablAR_P	=0,
		gTrim_didtComp_P	=0,
		gTrim_OT_Hys_P		=0,
		gTrim_LoffwOT_P		=0,
		gTrim_iLselOff_P	=0,
		gTrim_iLStdIcr_P	=0,
		gTrim_iL20dn_P		=0,
		gTrim_iL20up_P		=0,
		gTrim_SAM_P			=0,
		gTrim_OTP_P			=0,	//3 bits
		gTrim_SDS_OFF_P		=0,
		gTrim_Rcv_P			=0, //3 bits
		gTrim_drvSize_P		=0, //4 bits
		gTrim_RsenseUp_P	=0,
		gTrim_vxAdj_P		=0, //5 bits
		gTrim_iLRatio_P		=0, //4 bits
		gTrim_iLTC_P		=0, //4 bits
		gTrim_AR_req_P		=0;

int		gTrim_PK_S			=0, //revA 3 bit, revB 1 bit
		gTrim_DVesrSlpAdj	=0,	//bit 6
		gTrim_PS_S			=0,	//2 bits
		gTrim_TF_S			=0,	//2 bits
		gTrim_SCEN_S		=0,	//bit 39 revA
		gTrim_CBEN_S		=0, //bit 40 revA
		gTrim_DOPL_S		=0,	//bit 42 revA
		gTrim_XFWPK_S		=0,	//bit 46 revA
		gTrim_Spare_S		=0,	//bit 47 revA
		gTrim_CCAR_S		=0, //bit 49
		gTrim_ESRsel_S		=0, //bit 50
		gTrim_DdampEn_S		=0; //bit 51

// MINNO specific
int		gTrim_Rnw_S			=0, //2 bit
		gTrim_RnwFine_S		=0, //4 bit
		gTrim_FWC2_S		=0, //bit 17
		gTrim_NoFWC100mV_S	=0, //bit 18
		gTrim_Cap_S			=0, //3 bit
		gTrim_PKdig_S		=0, //4 bit
		gTrim_Vshunt_S		=0, //bit 30
		gTrim_IintTC_S		=0, //4 bit
		gTrim_REQlow_S		=0, //bit 43
		gTrim_LO_dis_S		=0; //bit 51

// Additional Target and Setting
char*	gDevType			= {0};				//Device Type (DLM or GaN)

// GaN Specific Targets and Feature Trim bits
int		gTrim_ZVS_Ton_sel_P	= 0,	// ZVS Ton select 2 bits 29-30
		gTrim_ZVS_Ton_Trm_P	= 0,	// ZVS Ton Trim 2 bits 31-32
		gTrim_ZVSon_p		= 0,	// bit 36
		gTrim_UV1_P			= 0,	// bit 37
		gTrim_UV2_P			= 0,	// bit 38
		gTrim_ZVSdlym20_P	= 0,	// bit 39
		gTrim_IlimLEB_P		= 0,	// bit 40
		gTrim_VpinIref20pct_P	= 0,	// Vpin Control Ref current bit 41
		gTrim_ZVS_dly_P		= 0,	// ZVS delay 4 bits 42-44
		gTrim_SDS30pct_P	= 0,	// SDS 30pct bit 46
		gTrim_SDS60pct_P	= 0;	// SDS 60pct bit 47

int		gRead_PK_S		=0, //3 bits
		gRead_CP_S		=0,	//3 bits
		gRead_PS_S		=0,	//2 bits
		gRead_TF_S		=0,	//2 bits
		gRead_AR_S		=0,	//2 bits
		gRead_SCEN_S	=0,	//bit 39
		gRead_CBEN_S	=0, //bit 40
		gRead_DsoftEn_S	=0,	//bit 41
		gRead_DOPL_S	=0,	//bit 42
		gRead_OVLO_S	=0,	//bit 43
		gRead_VR_S		=0,	//bit 44
		gRead_CR_S		=0,	//bit 45
		gRead_XFWPK_S	=0,	//bit 46
		gRead_Spare_S	=0;	//bit 47

int		gSiliconRev_P	=2, //0=revA, 1=revB, 2=revB2
		gSiliconRev_S	=2;	//0=revA, 1=revB, 2=revB2

int		gTotal_Addr_Count_P = 55,
		gTotal_Addr_Count_S = 52;

/*=======================    IzPre Function Variables    ===============================*/
float	gIzpt_NoZ_s=0.0, gIZ_NoZ_s=0.0, gIzpt_iov_Off_p=0.0;
float   gVread_AF_primary =0.0, gVread_AF_secondary =0.0;
int		gSiOption_p=-99, gSiOption_s=-99;

/*====================    Fosc Function Variables    ===============================*/
float	gFOSC_TARGET_P=0.0, gFOSC_TARGET_S =0.0;
float   gFosc_pt_P =0.0,   gFOSC_pt_S =0.0;
float   gFOSC_exp_P =0.0,  gFOSC_exp_S=0.0;
float   gFOSC_post_S=0.0;
float	gFS_trim_weight[16] ={0.0};	//trim weight define in Fosc_Trim_S func and use at FOSC_Ton_ARST func temporary for 1.92P 2.02S
int		gFS_trimcode		=0.0;	//Decode from Izpost function and use in FOSC_Ton_ARST func temporary for 1.92P 2.02S


/*======================    TonMax Variables    ====================================*/
float   gTonMax_TARGET=0.0;
float	gTonMax_S=0.0;
float   g_tOVL_TARGET=0.0;
float	g_tOVL_Pt =0.0;
float   g_tOVL_exp=0.0;
int		gHandShake_PASS =0;

/*======================    iOV- Variables    ====================================*/
float   giOV_plus_TARGET=0.0;
float	giOV_plus_Pt_P =0.0;
float   giOV_plus_exp=0.0;
bool	gIOV = false;

/*======================    CV Variables    ====================================*/
float   gCV_FB_TARGET=0.0,
		gCV_FB_Pre=0.0,
		gCV_Low=0.0;
float	gCV_post_S=0;
float	gCV_FB_S=0, gCV_FB_post_S=0;
float	gCV_VO_post_S=0;
float   gVcl2pct_QC2VO_S =0.0;
float   gVclamp_2pct_S_QC3 =0.0, gVclamp_10pct_S_QC3 =0.0;

/*======================    CC Variables    ====================================*/
float 	gKP_pt_S =0.0;
//float	gCC_Amp_pt_S =0.0;
float	gISvth_pt_S =0.0;
float   gKP_TARGET_S=0.0;
float   gSL_TARGET_S=0.0;

float	gCC_KPpt_S=0.0;
float	gCV_NM_KPpt_S=0.0;
float	gCB_KPpt_S=0.0;
float	gSL_pt_S=0.0;
float	gCC_Amp_SLpt_S=0.0;
float	gCC_ISvth_SLpt_S=0.0;
float	gVknee_actual_SLpt_S=0.0;
float	gCC_Amp_S=0.0;
float	gVknee_actual_S=0.0;

float	gISvth_S_9V_TARGET=0.0;
float	gISvth_S_12V_TARGET=0.0;
float	gISvth_S_20V_TARGET=0.0;
float	gISvth_exp_S=0;
float	gKP_exp_S=0.0;
float	gSL_exp_S=0.0;
float   iPV3_Cal_CC90=0.0;
float   iPV3_Cal_CC80=0.0;
float   iPV3_Cal_CC65=0.0;
float   iPV3_Cal_CC55=0.0;
float	iPV3_CC90  = 0.0;
float	iPV3_CC80  = 0.0;
float	iPV3_CC65  = 0.0;
float	iPV3_CC55  = 0.0;

/*======================    CB Variables    ====================================*/
int		gCB_CODE =0.0;
float   gCB_TARGET=0.0;
float   iPV3_Load=0.0, iDVI2K_Load=0.0;	// For CB vs load experiment
float	gCB_NoLoad_Pct_pt;
float	gvCB_pre_TM_S;

/*======================    FW pin Peak Switch Variables    ====================================*/


/*======================    IFB Variables    ====================================*/
float	gIFB_TH_Target_S	=0.0;
float	gIFB_250mA_pt_S		=0.0;
float	gIFB_130mA_pt_S		=0.0;
float	gIFB_TH_pt_S		=0.0;
float   gIFB_exp_S			=0.0;

/*======================    ILIM Variables    ====================================*/
float	gVped_Ilim =0.0, gVped_Ilim_Incr=0.0;
float	Vind_RM=0.0, Vind_HT=0.0;

float	gILIM_TARGET_S=0.0;
float	gILIM_P1_TARGET_S=0.0;
float	gILIM_LO_TARGET=0.0;
float	gILIM_LO_Med_TARGET=0.0;
float	gILIM_UP_Med_TARGET=0.0;
float	gI2F_S_TARGET=0.0;
float	gDIDT_TARGET=0.0;
float   gILIM_pt_S =0.0;
float   gILIM_exp_S =0.0;
float	gILIM_I2f_pt_S =0.0;

// For Capture and Find ILIM with digitizer
float   gIlim_Incr_max=0.0;
float	Ilim_gain=0.0, BUFgain=0.0;
int		SAMPLE_SIZE=0;

int		FIND_RDSON_Peak_FLAG	=0;
int		FIND_RDSON_Spec_FLAG	=0;
int		gFind_ILIM_Jitter		=0;
float	gIdmax[4000]				={-100.0};
int		gIdmax_addr[4000]		={0};
float	gIdmax_Jitter_132kHz	=0;
float	gIdmin_Jitter_132kHz	=0;
float	gIdmax_Jitter_18kHz		=0;
float	gIdmin_Jitter_18kHz		=0;
//float	Ton[10]					= {0.0};
//float	Toff[10]				= {0.0};

//bool	g_ILIM_INCR_secondary_control_active = false;

float	gTon_1stP			=0.0;
float	gTon_2ndP			=0.0;
float	gTon_3rdP			=0.0;
float	gToff_1stP			=0.0;
float	gToff_2ndP			=0.0;
float	gToff_3rdP			=0.0;
float	gILIM_pct_1stP		=0.0;
float	gILIM_pct_2ndP		=0.0;
float	gILIM_pct_3rdP		=0.0;
float   gRTM_Slope			=0.0;
float   gtDelta_RTM_Slope	=0.0;
float	gtDelta_RTM_Slope_200us =0.0;
float	gi_pct_drop_RTM		=0.0;
float	gILIM_200us_S		=0.0;
float   gILIM_200us_pct_S   =0.0;

/*======================    SR Comparator Variables    ====================================*/
float 	gSRth_pt_S			=0.0;
int		gSRth_CODE			=0.0;
float	gSRth_TARGET		=0.0;
float	gSRth_exp_S			=0.0;

/*======================    REQ Variables    ====================================*/
float	gREQ_0V				= 0.00;
float	gREQ_V_RingDet		= 0.45;
float	gREQ_V_Idle			= 0.90;
float	gREQ_V_Req			= 1.50;
float	gREQ_2V				= 2.00;	// TODO: use gREQ_V_Req only or rename to g_REQ_V_2V to avoid confusion
float	gREQ_V_LatchOff		= 5.00;
float	gREQ_Vref_pt_S		=0.0;
int		gREQ_Vref_CODE		=0.0;
float	gVref_TARGET		=0.0;
float	gVref_exp_S			=0.0;

/*=======================    VBP_Supply Function Variables    ===============================*/
float gVshunt_Init_Pr =0.0;
float gVshunt_Init_Se =0.0;
float gBPP_IS1_6p2_p = 0.0;
float gBPP_IS1_VBPP_p = 0.0;
float gBPP_IS2_VBPP_p = 0.0;
float gISD = 0;
float gISD_s = 0, gVSD_s = 0;
/*=======================    SOA Function Variables    ===============================*/
float VSOA_RM = 0.0,	
	  VSOA_HT = 0.0,
	  VSOA_RM_P = 0.0,	
	  VSOA_HT_P = 0.0,
	  VSDS_RM = 0.0,
	  VSDS_RM_P = 0.0,
	  VSDS_HT = 0.0;

/*=======================    STRESS Variables    ===============================*/
float	gILL_REQ_pre=0.0, 
		gILL_BPS_pre=0.0, 
		gILL_D_pre=0.0, 
		gILL_UV_pre=0.0, 
		gILL_SR_pre=0.0, 
		gILL_VO_pre=0.0, 
		gILL_FW_pre=0.0;
float	gILH_REQ_pre=0.0, 
		gILH_BPS_pre=0.0, 
		gILH_D_pre=0.0, 
		gILH_UV_pre=0.0, 
		gILH_SR_pre=0.0, 
		gILH_VO_pre=0.0, 
		gILH_FW_pre=0.0;

/*=======================    DATT Function Variables    ===============================*/
float	DATT_drain_current=0.0, DATT_pulse_time=0.0;
float	Norm_x_lim=0.0, Norm_n_lim=0.0;

/*===========================    HandShake Variables    ===============================*/
extern float HANDSHAKE_Vd_TM		= 0.0,		// Set Drain pull up voltage. 
			 FW_NEG_LEV_TM			= 0.0,		// Set FW desired negative level
			 HANDSHAKE_Vd_NM		= 0.0,		// Set Drain pull up voltage. 
			 FW_NEG_LEV_NM			= 0.0;		// Set FW desired negative level

// ======================  Gage Digitizer Variables=============================
int		SAMPLE_RATE_Hz	= 50e6;
float	SAMPLE_RATE_s	= 20e-9;
int		gDig_Type		= 0;


// ============================  Gage Digitizer ================================
//#define	GAGE_WAVEFORM_BUFFER_SIZE			GAGE_POST_32K		// 640us
//#define	GAGE_WAVEFORM_BUFFER_SIZE			GAGE_POST_64K		// 1280us or 1.28ms 
//#define	GAGE_WAVEFORM_BUFFER_SIZE			GAGE_POST_128K		// 2560us or 2.56ms
#define	GAGE_WAVEFORM_BUFFER_SIZE			GAGE_POST_1M		// 2560us or 2.56ms
#define GAGE_WAVEFORM_BUFFER_SIZE_ToffMax	GAGE_POST_256K		// 5.12ms to cover Fosc_min and Fosc_max
#define GAGE_WAVEFORM_BUFFER_SIZE_18kHz		GAGE_POST_256K		// 5.12ms to cover 18kHz tests. // DPG added //
#define GAGE_WAVEFORM_BUFFER_PAD	10	

signed short chan_a_16[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];
signed short chan_b_16[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];
		int	 Gage_pretrig_samples = 64;	//must be divisible by 32
//		int	 Gage_pretrig_samples = 0;	//must be divisible by 4

//// XP ////
	//XP variables for Gage
	int		debug_gage_error	=	0;	//set to 1 to print gage errors to DOS window
	int32						i32Status = CS_SUCCESS;
	TCHAR						szFileName[MAX_PATH];
	int64						i64StartOffset = 0;
	void*						pBuffer = NULL;
	float*						pVBuffer = NULL;
	uInt32						u32Mode;
	CSHANDLE					hSystem = 0;
	IN_PARAMS_TRANSFERDATA		InData = {0};
	OUT_PARAMS_TRANSFERDATA		OutData = {0};
	CSSYSTEMINFO				CsSysInfo = {0};
	CSAPPLICATIONDATA			CsAppData = {0};
	FileHeaderStruct			stHeader = {0};
	CSACQUISITIONCONFIG			CsAcqCfg = {0};
	CSCHANNELCONFIG				CsChanCfg = {0};
	CSCHANNELCONFIG				CsChanCfg_B = {0};
	CSTRIGGERCONFIG				CsTrigCfg = {0};
	uInt32						u32ChannelIndexIncrement;
	int64						i64Padding = 64; //extra samples to capture to ensure we get what we ask for
	int64						i64SavedLength;
	int64						i64MaxLength;
	int64						i64MinSA;  
	LONGLONG current_time;
	LONGLONG initial_time;

	int debug_test_time;
	float Gage_chan_a_voltage[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];//add padding 
	int16 chan_a_16_raw [GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];//old signed short.
    float Gage_chan_b_voltage[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD]; //old signed short.
	int16 chan_b_16_raw [GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD]; //old signed short.
		//// XP ////
	float Gage_chan_aa_voltage[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];//add padding 
	int16 chan_aa_16_raw [GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD];//old signed short.
	float Gage_chan_bb_voltage[GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD]; //old signed short.
	int16 chan_bb_16_raw [GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD]; //old signed short.

	// DPG added //
	// ++++++++++++++++++++++++++++++++++++++ //
	float *Gage_chan_a_voltageM = (float *)malloc((GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(float));
	int16 *chan_a_16_rawM = (int16 *)malloc((GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD)*2);
	float *Gage_chan_b_voltageM = (float *)malloc((GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(float));
	int16 *chan_b_16_rawM = (int16 *)malloc((GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD)*2);
	// ++++++++++++++++++++++++++++++++++++++ //

	int dig_ok,tbs,n;
	double trig_level;
	signed long starting_a,ending_a,trigger;
	signed long starting_b,ending_b;
	unsigned long offset_a,offset_b,timenow[10];
	BOOL data_ok,trig_ok;
#ifdef NT_
	signed long g_gage_sample_resolution_32;
#endif
	signed short	boards_in_system;
#ifdef NT_
	unsigned short /*far*/	gage_board_location[GAGE_B_L_BUFFER_SIZE];
	gage_driver_info_type   *board_info;
#endif
	//for Create_Awav 
	char			Wav_Outfile_path[100] = "e:\\DL4\\";
	char			Wav_outfile_name[100];
	STRING	Dut_serial_number;	
	STRING  lot_info_handler;

	STRING ProgramName, Prg_Name;



void user_init(void)
{	//  As TEST.EXE loads, before program name etc.
	g_pid = _getpid();  //do not remove

	STRING load_message = "Initializing";
	SendCommStatus(load_message);
	PiUserInit();

	GetProgramName(ProgramName);

	SendCommStatus(load_message);
}

// **************************************************************************

void user_load(void)
{	//  After the user selects the program, before user_start_lot().
	board_ptr_init();
	board_hardware_init();

	// *********** Enable TEC Temperature Controller ********** //
	if (gTEC_enable == 1)
	{
		printf("Initializing TEC Temperature Controller.\n");
		int ret = -999;

		ret  = TEC_Open();
		ret += TEC_Init();
		ret += TEC_Setup();

		ret += TTi_Open();
		ret += TTi_Init();
		ret += TTi_Setup();

		ret += LHC_Disable();

		ret += TTi_Close();
		ret += TEC_Close();

		if (ret != 0) printf("Error: TEC Temperature Controller failed to initialise!\n");
	}

	// *** Check for dual HVS and init second HVS at slot 19 ***
	int detected = NO_CARD_INSTALLED;
	int model = 0;
	int rev = 0;

	disable900V = 1;
	if (no_hvs_cards > 1)
	{
		detected = GetDetectedBoardType(BOARD_19, &model, &rev);
		if (detected == HVS_CARD && model == 7)
		{
			hvs_19 = &hvs_cards[board_ptr[BOARD_19]];
			hvs_19->init();
			disable900V = 0;
		}
	}

	// *** Primary Side Resources
	D_dvi				= dvi_11;		// DVI_11_0		Drain
	BPP_DVI				= dvi_11;		// DVI_11_0		BPP for breakdown test
	BPP_ovi				= ovi_1;		// OVI_1_0		BPP 
	VPIN_ovi			= ovi_1;		// OVI_1_1		UV

	// *** Secondary Side Resources
	FWC_dvi2k			= dvi_13;		// DVI_13_0		FWC
	REQ_ovi				= ovi_1;		// OVI_1_2		REQ
	BPS_dvi				= dvi_9;		// DVI_9_1		BPS
	SR_dvi2k			= dvi_13;		// DVI_13_1		SR
	VO_dvi				= dvi_9;		// DVI_9_0		VO
	FW_dvi				= dvi_11;		// DVI_11_1		FW
	ACK_ovi				= ovi_1;		// OVI_1_5		ACK

	// *** Other Resources
	InvSyn_REF_ovi		= ovi_1;		// OVI_1_4		InvSyn_IM reference OVI
	InvSyn_Offset_ovi	= ovi_1;		// OVI_1_6		InvSyn_IM GND offset OVI
	BC_ovi				= ovi_1;		// OVI_1_3		Buffer Clamp reference OVI

	char dummy[40];
	char fullname[200] = {0};
	STRING mystring;

	GetLimitSetName(mystring);

	istrstream theLimitSetName((char*)((const char*)mystring));

	theLimitSetName >> DevName  >> OperCode >> dummy >> dummy;// >> TestTemp;

	//	if ( strstr(Prg_Name,"Golden"))
	if ( strstr(DevName,"GU"))
		GoldenUnit = true;

	FamilyName = PRG_FAMILYNAME;	//This should be identical to PisetProgramname
	PrgRev = PRG_REVISION;			//This should be identical to PisetProgramname
	strcpy(fullname, FamilyName);
	strcat(fullname, " ");
	strcat(fullname, PrgRev);

	if(GoldenUnit == false)
	{
		//****************************************************************************************
		//***************** AUTO-CORRELATION *****************************************************
		//****************************************************************************************
		//Run AutoCorrReport function to share one golden unit for multiple devices of same family

		// TODO: golden unit
		if (!strnicmp( DevName, "SC1538C", 7 ))
		{
			if(Pi::AutoCorrReport::Verify("Inno3",PrgRev,"SC1538C_GU")) //Current GU prgRevName
			{
				printf("GU is ok  \n");
				Pi::AutoCorrReport::Modify(FamilyName, PrgRev, DevName);//Mod current GU prgRevName
			}
			else
				if(Pi::AutoCorrReport::Verify(FamilyName, PrgRev, DevName)) //Current GU prgRevName
					printf("GU is ok  \n");
				else
					printf("GU is NOT ok  \n");
		}
		else
			printf("GU is NOT ok  \n");
	}

	PiEnableGoldenUnit(8);

	PiSetProgramName(fullname);
	PiUserLoad();

	STRING load_message = "DDD load";
	SendCommStatus(load_message);
	DDD_init();

	/* ================ XP Gage digitizer Setup STARTS ==================*/
	//Gage Initialization
	load_message = "Gage Init";
	SendCommStatus(load_message);
	dig_ok = Gage_loadtime_setup();	//call this only once

	Gage_cal_table_setup_xp();
	Gage_init();			//can be called multiple times
	delay(1);

	//Gage Calibration (the following function call will calibrate current range)
	i32Status = CsDo(hSystem, ACTION_CALIB);	//Gage will calibrate for current range
	/* ================ XP Gage digitizer Setup ENDS ==================*/

	//Determine if InvSyn Circuit is working properly
	int InvSync_pass = 0;
	Check_InvSync_Circuit(&InvSync_pass);

	if (InvSync_pass == 1)
	{
		load_message = "Check InvCkt Pass";
		SendCommStatus(load_message);
		delay(200);
	}
	else
	{
		MessageBox(NULL,"Make sure NO PART Clamped in the handler, then reload test program. If there is no part, then InvSyn Circuit is possibly bad!","SETUP ERROR", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		g_Setup_OK = 0;
		AbortTest = true;// Don't continue if Invsync check fails
	}

	load_message = "Load Complete";
	SendCommStatus(load_message);
	//delay(500);
}

// **************************************************************************

void user_start_lot(void)
{ //  After Limit selection and LotID is entered or if a New Lot is started manually.
	PiUserStartLot( );
	First_Time_Run = true;

	//mode_change();	// To prevent problems when ENG techs starts a new lot and change op-code without getting out
						// of test program. 
}

// **************************************************************************

void user_wait_sot(void)
{	//  Obsolete and is not called.
	PiUserWaitSot( );
}

// **************************************************************************

void user_start_test(void)
{	//  After SOT, before 1st function.
	PiUserStartTest( );
	PV3_DriveOff_ChargeOn();				// Charge up PV3 capacitor bank early to save test time

	mux_14->close_relay(MUX_BANK_3_4);
	mux_14->close_relay(MUX_4_GND);
	mux_14->close_relay(MUX_BANK_5_6);
	mux_14->close_relay(MUX_6_GND);
	mux_14->close_relay(MUX_7_GND);
	mux_14->close_relay(MUX_8_GND);
	mux_20->close_relay(MUX_BANK_1_2);
	mux_20->close_relay(MUX_2_GND);
}

// **************************************************************************

void user_before_binning(void)
{	//  Before binning device.

	if (PiGetAnyFailStatus())
	{
		DDD_Load_Patterns();
		printf("\nDDD_Pattern_Reload: SERIAL_NUM = %i \n", SERIAL_NUM);
	}

	if (!PiGetAnyFailStatus())
	{
			
			int func[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
				          31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62};  // define list of required test functions by number
			size_t n = sizeof(func) / sizeof(int);
			PiSetRequiredFunctions(n, func,FALSE);

	
			PiUserBeforeBinning( );
	}
}

// **************************************************************************
void user_end_test(void)
{	//  After binning device.
	PiUserEndTest( );

	Power_Down_Everything();
	Open_All_Relays();
	delay(3);

	

	Open_relay(MUX_BANK_3_4);
	Open_relay(MUX_4_GND);
	Open_relay(MUX_BANK_5_6);
	Open_relay(MUX_6_GND);
	Open_relay(MUX_7_GND);
	Open_relay(MUX_8_GND);
	mux_20->open_relay(MUX_BANK_1_2);
	mux_20->open_relay(MUX_2_GND);
	delay(3);
	

}

// **************************************************************************

void user_next_device(void)
{	//  After displaying test results, before looking for SOT.

	PiUserNextDevice( );
}

// **************************************************************************

void user_end_lot(void)
{	//  After last EOT in a lot or if a New Lot is started manually.
//	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0.0,	RANGE_10_V);	// OVI_1_4	
	ovi_1->set_voltage(4, 0.0,	RANGE_10_V);	// OVI_1_4	
	pv3_4->charge_off();		// Discharge PV3 capacitor bank at end lot

	if (gTEC_enable == 1) LHC_Disable();

	PiUserEndLot( );
}

// **************************************************************************

void user_exit(void)
{	//  On program exit.

//{ASL_CREATE BEGIN USER_EXIT_FROM_LIST_PROPERTIES
// Regenerating source code will change the code between here and ASL_CREATE END USER_EXIT_FROM_LIST_PROPERTIES}
// Use the List Properties dialog to drive changes to this code.
//ASL_CREATE END USER_EXIT_FROM_LIST_PROPERTIES}
	/* =========== XP Gage Digitizer ============= */
	PiUserExit( );
	CsFreeSystem(hSystem); 	//Free Gage software handle (prevents crash when Visual Studio debugger started)	

}

// **************************************************************************

void user_F12(void)
{	//  User hit F12.
}

// **************************************************************************

void user_dut_power_off(void)
{	//  Dut power off occured.
}

// **************************************************************************

void user_dut_power_on(void)
{	//  Dut power on occured.
}

// **************************************************************************

//{ASL_CREATE BEGIN SAMPLE_CODE_FOR_CREATE_INSTRUMENT_FROM_LIST_PROPERTIES
// Regenerating source code will change the code between here and ASL_CREATE END SAMPLE_CODE_FOR_CREATE_INSTRUMENT_FROM_LIST_PROPERTIES}
// Use the List Properties dialog to drive changes to this code.
//ASL_CREATE END SAMPLE_CODE_FOR_CREATE_INSTRUMENT_FROM_LIST_PROPERTIES}




//============== InnoSwitch3-MX User Functions Definition START here ===============

void Close_relay(int Relay)
{
	if (Relay >= TMU_6_relay + 1000)
		return;
	else if (Relay >= TMU_6_relay)
		tmu_6->close_relay(Relay - TMU_6_relay);
	else if (Relay >= DVI_13_relay)
		dvi_13->close_relay(Relay - DVI_13_relay);
	else if (Relay >= DVI_11_relay)
		dvi_11->close_relay(Relay - DVI_11_relay);
	else if (Relay >= DVI_9_relay)
		dvi_9->close_relay(Relay - DVI_9_relay);
	else if (Relay >= MUX_20_relay)
		mux_20->close_relay(Relay - MUX_20_relay);
	else if (Relay >= MUX_14_relay)
	{
		if (Relay == K23 || Relay == K24)
		{
			mux_14->open_relay(MUX_BANK_1_2);
			mux_14->open_relay(MUX_2_BUS2);
			mux_14->close_relay(MUX_2_GND);
		}
		mux_14->close_relay(Relay - MUX_14_relay);
	}
	else
		mux_14->close_relay(Relay);
}

void Open_relay(int Relay)
{
	int relay_state = DEFAULT_VALUE;
	if (Relay >= TMU_6_relay + 1000)
		return;
	else if (Relay >= TMU_6_relay)
		tmu_6->open_relay(Relay - TMU_6_relay);
	else if (Relay >= DVI_13_relay)
		dvi_13->open_relay(Relay - DVI_13_relay);
	else if (Relay >= DVI_11_relay)
		dvi_11->open_relay(Relay - DVI_11_relay);
	else if (Relay >= DVI_9_relay)
		dvi_9->open_relay(Relay - DVI_9_relay);
	else if (Relay >= MUX_20_relay)
		mux_20->open_relay(Relay - MUX_20_relay);
	else if (Relay >= MUX_14_relay)
	{
		mux_14->open_relay(Relay - MUX_14_relay);
		relay_state  = mux_14->is_relay_open(MUX_2_3);
		relay_state += mux_14->is_relay_open(MUX_2_4);
		if (relay_state == 2)
		{
			mux_14->open_relay(MUX_2_GND);
			mux_14->close_relay(MUX_BANK_1_2);
		}
	}
	else
		mux_14->open_relay(Relay);
}

void Dump_IS_Data(char* Title,int lcnt,float tDelay,float IBPP_meas)
{
	char Outfile_name[100] ="\0";
	char buffer[15] ="\0";
	
	strcpy(Outfile_name,"e:\\DL4\\");
	strcat(Outfile_name, Dev_id);
	strcat(Outfile_name, "_");
	strcat(Outfile_name, Func_name);
	strcat(Outfile_name, "_");
	strcat(Outfile_name, WAVE_NAME);
	strcat(Outfile_name, ".txt");
	

	ofstream outfile;
	outfile.open(Outfile_name, ios::app);
	if(lcnt ==0) outfile<< Title <<endl;
	outfile<< lcnt <<"\t"<<tDelay<<"\t"<<IBPP_meas<<"\t"<<endl;

	outfile.close();
}

void Dump_V_th_Data(char* Title,int lcnt,float IBP_meas,float Vfb_meas, float tPeriod)
{
	char Outfile_name[100] ="\0";
	char buffer[15] ="\0";
	
	strcpy(Outfile_name,"e:\\DL4\\");
	strcat(Outfile_name, Dev_id);
	strcat(Outfile_name, "_");
	strcat(Outfile_name, Func_name);
	strcat(Outfile_name, "_");
	strcat(Outfile_name, WAVE_NAME);
	strcat(Outfile_name, ".txt");
	

	ofstream outfile;
	outfile.open(Outfile_name, ios::app);
	if(lcnt ==0) outfile<< Title <<endl;
	outfile<< lcnt <<"\t"<<IBP_meas<<"\t"<<Vfb_meas<<"\t"<<tPeriod<<"\t"<<endl;

	outfile.close();
}

void Dump_CC_th_Data(char* Title,int lcnt,float IBP_meas,float iDVI2k_frc,float iPV3_meas,float iDVI2k_meas, float CC)
{
	char Outfile_name[100] ="\0";
	char buffer[15] ="\0";
	

	strcpy(Outfile_name,"e:\\DL4\\");
	strcat(Outfile_name, Dev_id);
	strcat(Outfile_name, "_");
	strcat(Outfile_name, Func_name);
	strcat(Outfile_name, "_");
	strcat(Outfile_name, WAVE_NAME);
	strcat(Outfile_name, ".txt");

	ofstream outfile;
	outfile.open(Outfile_name, ios::app);
	if(lcnt ==0) outfile<< Title <<endl;
	outfile<< lcnt <<"\t"<<IBP_meas<<"\t"<<iDVI2k_frc<<"\t"
		   << iPV3_meas<<"\t\t"<<iDVI2k_meas<<"\t\t"<<CC<<endl;

	outfile.close();
}


void Dump_Freq_Data(char* Table_Field_Names, char* Param_Name, float Prm_Final_Result, int lcnt, float Freq_val, float Time_val)
{
	char Outfile_name[100] ="\0";
	char buffer[15] ="\0";
	
	strcpy(Outfile_name,"e:\\DL4\\");
	strcat(Outfile_name, Dev_id);
	strcat(Outfile_name, "_");
	strcat(Outfile_name, Func_name);
	strcat(Outfile_name, "_");
	strcat(Outfile_name, WAVE_NAME);
	strcat(Outfile_name, ".txt");
	

	ofstream outfile;
	outfile.open(Outfile_name, ios::app);
	if(lcnt ==0) 
	{
		outfile<<endl<<"SERIAL_NUM = "<<SERIAL_NUM<<endl;
		outfile<<"Final Result => "<< Param_Name <<" = "<<Prm_Final_Result<<endl<<endl;
		outfile<< Table_Field_Names <<endl;
	}
	outfile<< lcnt <<"\t"<<Freq_val<<"\t\t"<<Time_val<<"\t"<<endl;

	outfile.close();
}

void CreateAwav(double * data, int arr_size, float sample_rate, char * out_file_and_path) // DPG added //
{
	// create .awav file for debug //
	int i;
	FILE * fpr = fopen(out_file_and_path, "w");
	if (! fpr)
		return;
	fprintf (fpr, "version awav 0 2 0;\n");
	fprintf (fpr, "date 07 10 2003;\n");
	fprintf (fpr, "time 14 42 47;\n");
	fprintf (fpr, "name =  \"result_data\";\n");
	fprintf (fpr, "type = rrect;\n");
	fprintf (fpr, "size = %d;\n", arr_size);
	fprintf (fpr, "sample_interval = %13.11e;\n", sample_rate);
	fprintf (fpr, "offset = 0.000000e+000;\n");
	fprintf (fpr, "x_units = \"s \";\n");
	fprintf (fpr, "y_units = \"V \";\n");
	fprintf (fpr, "pattern;\n");
	fprintf (fpr, "  !Value\n");
	double val;
	for( i = 0; i < arr_size; i++)
		{
		val = data[i];
		if (val >= 0.0) 
			fprintf (fpr, "+");
		fprintf (fpr, "%18.16e; !%d\n", val, i);
		}
	fprintf (fpr, "pattern_end;\n");
	fclose(fpr);
	return;
}

void Find_Vfb_vs_Drain_Toff()
{
	// Vesr, linear search to find the start switching threshold
	float DeltaT1[150]	= {0};
	float VFB1[150]	= {0};
	float step	= 1e-3;
	int i = 0;
	float vfb = gCV_FB_S + 50e-3;
	float tmeas = 0;

	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);
	REQ_ovi->set_meas_mode(REQ_ch,			OVI_MEASURE_VOLTAGE);
	delay(2);

	for (i=0; i<150; i++)
	{
		vfb -= step;
		REQ_ovi->set_voltage(REQ_ch, vfb, 		RANGE_2_V);	// OVI_1_2	
		wait.delay_10_us(20);
		//exit while loop if device starts switching
		tmu_6->arm(128e-3); 
		wait.delay_10_us(200);
		tmeas = tmu_6->read();
		DeltaT1[i] = tmeas/128;
		VFB1[i]=REQ_ovi->measure_average(5);
	}

	char DumpFileName[4096];
	strcpy( DumpFileName,"e:\\dl4\\VfbvsDrainToff.txt");
	dumparray.open( DumpFileName, ios::app );
	dumparray << "Vfb vs. Drain Toff" << endl;
	dumparray << "Point" << '\x009' << '\x009' << "Vfb" << '\x009' << '\x009'<< "Drain Toff" << endl;
	for( i = 0; i < 150; i++)
	dumparray << i << '\x009' << '\x009' << VFB1[i] << '\x009' << '\x009' << DeltaT1[i] << endl;
	dumparray.close();
}

void mode_change(void)
{
	char dummy[40];
	STRING mystring;
	char* gHcode_str;
	char* gHCcode_str;
	char* gHZcode_str;
	char* gPartID_str;

	GetLimitSetName( mystring );

	istrstream theLimitSetName( (char*)((const char*)mystring) );

	theLimitSetName >> DevName  >> OperCode >> dummy >> dummy;// >> TestTemp;

	// TM InvSyn_IM settings for handshake (Diode added to keep FW above -300mV)
	HANDSHAKE_Vd_TM = 2.0;		// Set Drain pull up voltage. 

	// NM InvSyn_IM settings for handshake
	HANDSHAKE_Vd_NM = 5.0;		// Set Drain pull up voltage to be above Test Mode Vthres (3V)

	gVshunt_BPP = 5.5;			// vBPP does not want to go above 5.5V according to Lance
	gVshunt_BPS = 5.7;			// vBPS does not want to go above 5.7V according to Thomas

	// Common for all devices
	Vind_RM				= 45;
	Vind_HT				= 45;
	gVped_Ilim			= 45;
	gVped_Ilim_Incr		= 45;
	Ilim_gain			= 0.5;
	DATT_drain_current	= 1.0;
	DATT_pulse_time		= 125;
	Norm_x_lim			= -0.01;
	Norm_n_lim			= 0.01;

	//*******************************  Additional trim Targets  *************************************
	gCV_FB_TARGET  = 1.265;		//05/29/13 Per Alex  // TODO: to be rename for MINNO-PS

	//*******************************  OperCode  *************************************
	OPCODE = DEFAULT_VALUE;
	if (!strnicmp(OperCode, "4200", 4 ))	OPCODE = 4200;		// FT  @ 25C
	if (!strnicmp(OperCode, "4250", 4 ))	OPCODE = 4250;		// QA  @ 25C
	if (!strnicmp(OperCode, "4300", 4 ))	OPCODE = 4300;		// FT  @ HOT
	if (!strnicmp(OperCode, "4350", 4 ))	OPCODE = 4350;		// FT  @ COLD
	if (!strnicmp(OperCode, "4500", 4 ))	OPCODE = 4500;		// QA  @ HOT
	if (!strnicmp(OperCode, "4400", 4 ))	OPCODE = 4400;		// ENG @ COLD
	if (!strnicmp(OperCode, "4501", 4 ))	OPCODE = 4501;		// Minno uses 4501 opcode for REL

	if (OPCODE == DEFAULT_VALUE)
		MessageBox(NULL,"INVALID OP CODE!  Please re-enter New Lot Info","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);

	//*******************************  PartID  *************************************
	char* Part_id_name;
	Part_id_name = PiGetPartID();
	Dev_id = Part_id_name;

	if(GoldenUnit == false)
	{
		printf("\nPart ID = %s\n",Part_id_name);

		if((strcmp(Part_id_name,"NONE")) == 0)
		{
			DisplayErrorMessage("'Part ID' must be entered in 'New Lot Information' pop-up screen");
			DisplayErrorMessage("Program can not run.  Please re-enter New Lot Info");
			gDevNum = 0;
			return;
		}
	}
	else
	{
		//if(strstr(DevName, "SC1538C_GU") !=NULL)
		//	Part_id_name = "SC1538C_HC04";
	}

	char* dll_name = "Inno3_MX.dll";
	#define MAX_FILE_NAME2				200

	char DllFullName[MAX_FILE_NAME2];
	HMODULE		DllHandle;
	DllHandle = GetModuleHandle(dll_name);
	GetModuleFileName(DllHandle, DllFullName, MAX_FILE_NAME2);
	printf("DllFullName= %s\n", DllFullName);

	char* csvpath;
	csvpath = GetCSVPath(DllFullName, "Inno3_MX-TrimOptions.csv");
	printf("\n\nCSV Path= %s\n\n", csvpath);

	PITrimOptions* trimops = new PITrimOptions();

	int fields = trimops->Read(csvpath, Part_id_name);	//Allow to read once only
	if (fields == 0)
	{
		DisplayErrorMessage("You've entered 'Part ID' = ", Part_id_name, ". We do not have this product.  Please re-enter the correct Part ID");
		gDevNum = 0;
		return;
	}

	//*******************************  TrimOps Table  *************************************
	//Verify Trim options table revision
	Trimops_Table_Rev = trimops->GetRevision();
	if (strcmp(Trimops_Table_Rev, TRIMOPS_REVISION))	//Only accept the correct revision table
	{
		DisplayErrorMessage("Trim Option Table Revision is '", Trimops_Table_Rev, "', Wrong Revision!\n");
		DisplayErrorMessage("Program can not run.  Trim Option Table is not the correct Revision");
		gDevNum = 0;
		return;
	}

	// Retreive Trim option values
	// Get trim option values as Long or Double or String
	int trimops_num = 1;
	gPartID_str			= trimops->GetTrimOpAsString(trimops_num++);				//PartID
	trimops_num++;																	//Rev, not used in test program
	gHcode_str			= trimops->GetTrimOpAsString(trimops_num++);				//Hcode
	gHCcode_str			= trimops->GetTrimOpAsString(trimops_num++);				//HC code, column 4
	gHZcode_str			= trimops->GetTrimOpAsString(trimops_num++);				//HZ code, column 5

	trimops_num = 8;
	gDevFamily			= trimops->GetTrimOpAsLong(trimops_num++);					//Device Family (1=CE, 2=CP, 4=MX, 6=EP)
	gDLM_BV				= trimops->GetTrimOpAsLong(trimops_num++);					//DLM BV (6=650V, 7=725V)
	gDLM_Size			= trimops->GetTrimOpAsLong(trimops_num++);					//DLM Size (2 to 8)
	gDevNum				= trimops->GetTrimOpAsLong(trimops_num++);					//Device Number
	MOSFET_SIZE			= trimops->GetTrimOpAsLong(trimops_num++);					//Die Size

	// Primary Targets and Feature Trim bits
	giOV_plus_TARGET	= trimops->GetTrimOpAsDouble(trimops_num++) / 1e6;			//iOV-   (us to S) //115us;
	gILIM_TARGET_S		= trimops->GetTrimOpAsDouble(trimops_num++) / 1000;			//ILIM (mA to A)
	g_tOVL_TARGET		= trimops->GetTrimOpAsDouble(trimops_num++) / 1e6;			//tOVL (us to S)
	gFOSC_TARGET_P		= trimops->GetTrimOpAsDouble(trimops_num++) * 1000.0;		//Fosc (kHz to Hz)
	gTrim_iov_Off_P		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_iuvMinus_P	= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_uvDelay_P		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_Loff_AR_P		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_DisablAR_P	= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_didtComp_P	= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_OT_Hys_P		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_LoffwOT_P		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_iLselOff_P	= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_iLStdIcr_P	= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_iL20dn_P		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_iL20up_P		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_SAM_P			= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_OTP_P			= trimops->GetTrimOpAsLong(trimops_num++);					//OTP		bits 1,2,3
	gTrim_SDS_OFF_P		= trimops->GetTrimOpAsLong(trimops_num++);					//"SDS OFF" or "Vpin Control Reference current"
	gTrim_Rcv_P			= trimops->GetTrimOpAsLong(trimops_num++);					//Rcv		bits 1,2,Sign

	gBVD_Room			= trimops->GetTrimOpAsDouble(trimops_num++);				//BVD at Room
	gBVD_Hot			= trimops->GetTrimOpAsDouble(trimops_num++);				//BVD at Hot

	gTrim_drvSize_P		= trimops->GetTrimOpAsLong(trimops_num++);					//drvSize	bits 1,2,3,4
	gTrim_RsenseUp_P	= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_vxAdj_P		= trimops->GetTrimOpAsLong(trimops_num++);					//vxAdj		bits 1,2,3,4,5
	gTrim_iLRatio_P		= trimops->GetTrimOpAsLong(trimops_num++);					//iLRatio	bits 1,2,3,4
	gTrim_iLTC_P		= trimops->GetTrimOpAsLong(trimops_num++);					//iLTC		bits 1,2,3,4
	gTrim_AR_req_P		= trimops->GetTrimOpAsLong(trimops_num++);					//silicon revB have this additional bit.

	// Secondary Targets and Feature Trim bits
	gFOSC_TARGET_S		= trimops->GetTrimOpAsDouble(trimops_num++) * 1000;			//Fosc (kHz to Hz)
	gTrim_PK_S			= trimops->GetTrimOpAsLong(trimops_num++);					//PK bits1,2,3		revA silicon
	gTrim_Rnw_S			= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_RnwFine_S		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_FWC2_S		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_NoFWC100mV_S	= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_Cap_S			= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_PKdig_S		= trimops->GetTrimOpAsLong(trimops_num++);
	gSRth_TARGET		= trimops->GetTrimOpAsDouble(trimops_num++);
	gVref_TARGET		= trimops->GetTrimOpAsDouble(trimops_num++);
	gTrim_IintTC_S		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_DOPL_S		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_REQlow_S		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_XFWPK_S		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_Vshunt_S		= trimops->GetTrimOpAsLong(trimops_num++);
	gTrim_LO_dis_S		= trimops->GetTrimOpAsLong(trimops_num++);

	// Test Setup
	BoardType			= trimops->GetTrimOpAsLong(trimops_num++);					//LB SubType
	BoardRev			= trimops->GetTrimOpAsLong(trimops_num++);					//LB Rev
	gDIDT_TARGET		= trimops->GetTrimOpAsLong(trimops_num++)/1000.0;			//didt
	InductorType		= trimops->GetTrimOpAsLong(trimops_num++);					//IM SubType
	InductorRev			= trimops->GetTrimOpAsLong(trimops_num++);					//IM Rev
	ContactorType		= trimops->GetTrimOpAsLong(trimops_num++);					//CB SubType
	ContactorRev		= trimops->GetTrimOpAsLong(trimops_num++);					//CB Rev
	scaled_ifrc			= trimops->GetTrimOpAsDouble(trimops_num++);				//BV stress current
	Vind_RM				= trimops->GetTrimOpAsLong(trimops_num++);					//
	Vind_HT				= trimops->GetTrimOpAsLong(trimops_num++);					//
	VSOA_RM				= trimops->GetTrimOpAsLong(trimops_num++);					//
	VSOA_HT				= trimops->GetTrimOpAsLong(trimops_num++);					//
	VSDS_RM				= trimops->GetTrimOpAsLong(trimops_num++);					//
	VSDS_HT				= trimops->GetTrimOpAsLong(trimops_num++);					//
	gVped_Ilim			= trimops->GetTrimOpAsLong(trimops_num++);					//
	gVped_Ilim_Incr		= trimops->GetTrimOpAsLong(trimops_num++);					//
	Ilim_gain			= trimops->GetTrimOpAsDouble(trimops_num++);				//
	DATT_drain_current	= trimops->GetTrimOpAsDouble(trimops_num++);				//
	DATT_pulse_time		= trimops->GetTrimOpAsLong(trimops_num++);					//

	// Silicon Revisions
	gSiliconRev_P		= trimops->GetTrimOpAsLong(trimops_num++);					//
	gSiliconRev_S		= trimops->GetTrimOpAsLong(trimops_num++);					//

	// Additional Target and Setting
	gILIM_P1_TARGET_S	= trimops->GetTrimOpAsDouble(trimops_num++) / 1000;			//ILIM_P1 (mA to A)
	gDevType			= trimops->GetTrimOpAsString(trimops_num++);				//Device Type (DLM or GaN)

	// GaN Specific Targets and Feature Trim bits
	gTrim_ZVS_Ton_sel_P	= trimops->GetTrimOpAsLong(trimops_num++);					// ZVS Ton select 2 bits 29-30
	gTrim_ZVS_Ton_Trm_P	= trimops->GetTrimOpAsLong(trimops_num++);					// ZVS Ton Trim 2 bits 31-32
	gTrim_ZVSon_p		= trimops->GetTrimOpAsLong(trimops_num++);					// bit 36
	gTrim_UV1_P			= trimops->GetTrimOpAsLong(trimops_num++);					// bit 37
	gTrim_UV2_P			= trimops->GetTrimOpAsLong(trimops_num++);					// bit 38
	gTrim_ZVSdlym20_P	= trimops->GetTrimOpAsLong(trimops_num++);					// bit 39
	gTrim_IlimLEB_P		= trimops->GetTrimOpAsLong(trimops_num++);					// bit 40
	gTrim_VpinIref20pct_P	= trimops->GetTrimOpAsLong(trimops_num++);				// Vpin Control Ref current bit 41
	gTrim_ZVS_dly_P		= trimops->GetTrimOpAsLong(trimops_num++);					// ZVS delay 4 bits 42-44
	gTrim_SDS30pct_P	= trimops->GetTrimOpAsLong(trimops_num++);					// SDS 30pct bit 46
	gTrim_SDS60pct_P	= trimops->GetTrimOpAsLong(trimops_num++);					// SDS 60pct bit 47

	gIlim_Incr_max		= gILIM_TARGET_S * ( 1 + (2 * (float)(gTrim_iLRatio_P ^ 13) / 100));
	gI2F_S_TARGET		= gILIM_TARGET_S *gILIM_TARGET_S * gFOSC_TARGET_S * 1e-3;	

	//********************  Find H code from string gPartID_str  **************************
	//** Find H code or HC code from string gPartID_str **
	//   By definition, the PartID will end with _Hxxx or _HCxx 
	//	 (this code will also accomodate -Hxxx and -HCxxx using dashes instead of underlines)
	//	 One of three possible datalogs will be used: H_code, HC_code or H_code_char. All are integers.
	//   If the PartID ends with _Hxxx, where xxx is a number, then xxx will be datalogged using the H_code datalog
	//   If the PartID ends with _HCxx, where xx  is a number, then xx will be datalogged  using the HC_code datalog
	//   If the PartID ends with _Hxxx, where xxx is NOT A NUMBER, then xxx will be datalogged using the H_code_char datalog
	//   If the PartID ends with _HCxx, where xx  is NOT A NUMBER, then Cxx will be datalogged using the H_code_char datalog
	//   The H_code_char datalog will datalog a 6 digit integer representing the 3 characters after the _H
	//		The first  two digits will represent the first  character after _H
	//		The second two digits will represent the second character after _H
	//		The third  two digits will represent the third  character after _H
	//		A character is represented by two digits as follows:
	//			0->00
	//			.
	//			.
	//			.
	//			9->09
	//			A->10
	//			B->11
	//			.
	//			.
	//			.
	//			Z->36
	//		For example: _HZ85 datalogs as 350805	(Z->35,8->08,5->05)
	//		For example: _HC0A datalogs as 120010	(C->12,0->00,A->10)

	char* sc_ptr;
	char* ul_ptr;
	char* dash_ptr;
	//char* dashTL_ptr;
	char* h_ptr;
	char* c_ptr;
	int   len = 0;
	long  AN_int_return = 0;

	//Make sure PartID is all uppercase
	c_ptr = gPartID_str;
	while (*c_ptr != '\0')
	{
		*c_ptr = toupper((unsigned char)*c_ptr);
		c_ptr++;
	}

	//PartID: Find SC parts
	sc_ptr		= strstr(gPartID_str, "SC");

	//PartID: Find underline character
	ul_ptr		= strchr(gPartID_str, '_');
	dash_ptr	= strchr(gPartID_str, '-');

	//error check
	if ((ul_ptr == NULL) && (dash_ptr == NULL) && (sc_ptr == NULL))
	{
		DisplayErrorMessage("'Part ID' must contain an underscore or dash character");
		DisplayErrorMessage("Program can not run.  Please re-enter New Lot Info");
		gDevNum = 0;
		return;
	}

	//PartID: Find H character (after underline or dash)
	if (ul_ptr != NULL)
		h_ptr = strchr(ul_ptr, 'H');	//H after underline
	else if (dash_ptr != NULL)
		h_ptr = strchr(dash_ptr, 'H');	//H after dash
	else
		h_ptr = "";

	//error check
	if (sc_ptr == NULL && ((h_ptr == NULL) || ((h_ptr != (ul_ptr+1)) && (h_ptr != (dash_ptr+1)))))
	{
		DisplayErrorMessage("'Part ID' must contain an 'H' after the underscore character");
		DisplayErrorMessage("Program can not run.  Please re-enter New Lot Info");
		gDevNum = 0;
		return;
	}

	////PartID: Find dash "-TL" characters
	//dashTL_ptr=strchr(h_ptr,'-');	//example HC15-TL then it should return TL only

	//if(dashTL_ptr != NULL)  //error check if partID does have "-TL"
	//{
	//	if(strlen(h_ptr)!=7)  //error check if partID does not have "-TL"
	//	{
	//		DisplayErrorMessage("'Part ID' must contain exactly 7 characters after the H");
	//		DisplayErrorMessage("Program can not run.  Please re-enter New Lot Info");
	//		gDevNum = 0;
	//		return;
	//	}
	//}
	//else if(strlen(h_ptr)!=4)  //error check if partID does not have "-TL"
	//{
	//	DisplayErrorMessage("'Part ID' must contain exactly 3 characters after the H");
	//	DisplayErrorMessage("Program can not run.  Please re-enter New Lot Info");
	//	gDevNum = 0;
	//	return;
	//}

	//PartID: Convert to AN code without -TL
	if ((h_ptr != NULL) && (strlen(h_ptr)==4))
	{
		Convert_Alphanumeric_to_Float(&gH_code_AN, h_ptr+1);
	}

	if (gDEBUG) printf("H_code_AN = %.0f\n", gH_code_AN );

	//Find if there is a C charater
	if (h_ptr != NULL)
		c_ptr = strchr(h_ptr, 'C');	//xie 4/21/2017

	//get H code or HC code
	if (c_ptr != NULL)		//HC
	{
		gHcode = strtol(c_ptr+1, NULL, 10);	//convert HC code, zero means not a number
		gHCcode = gHcode;
		if (gDEBUG && gHcode) printf("HC_code = %.0f\n", gHcode );
	}
	else if (h_ptr != NULL)	//H
	{
		gHcode = strtol(h_ptr+1, NULL,10);	//convert H code, zero means not a number
		if (gDEBUG && gHcode) printf("H_code = %.0f\n", gHcode );
	}

	//Convert HZ code (if any)
	if (gHZcode_str != NULL) 
	{
		h_ptr = strchr(gHZcode_str, 'H');
		if ((h_ptr != NULL) && (strlen(h_ptr)==4))
			Convert_Alphanumeric_to_Float(&gHZ_code_AN, h_ptr+1);
		if (gDEBUG) printf("HZ_code_AN = %.0f\n", gHZ_code_AN );
	}

	//Make sure gDevType is all uppercase
	c_ptr = gDevType;
	while (*c_ptr != '\0')
	{
		*c_ptr = toupper((unsigned char)*c_ptr);
		c_ptr++;
	}
	//GaN device?
	if (!strncmp(gDevType, "GAN", 3)) gGaN = true;
	if (gGaN) gTrim_SDS_OFF_P = 1;

	// TODO: remove hardcoded VSOA, use trimopstable
	//********************  Setup variables  **************************
	if(MOSFET_SIZE==2)
	{
		VSOA_RM				= 4.0;
		VSOA_HT				= 5.0;
	}
	else if(MOSFET_SIZE==6)	
	{
		VSOA_RM				= 6.0;
		VSOA_HT				= 7.0;
	}
	else if(MOSFET_SIZE==8)	
	{
		VSOA_RM				= 7.0;
		VSOA_HT				= 8.0;
	}

	// DX001B5 Primary AF global addresses
	gP_AF_Start_Addr_Primary				= 1;
	gP_AF_Start_Addr_IOV					= 1;	//bits 1 to 5 
	gP_AF_Start_Addr_ILIM					= 6;	//bits 6 to 9
//	gP_AF_Start_Addr_TonMax					= 10;	//bits 10 to 12
	gP_AF_Start_Addr_tOVL					= 10;	//bits 10 to 12
	gP_AF_Start_Addr_Freq					= 13;	//bits 13 to 15
	gP_AF_Start_Addr_IuvIov_Disable			= 16;	
	gP_AF_Start_Addr_Iuv_10uA				= 17;	
	gP_AF_Start_Addr_UV_400ms_dly			= 18;	
	gP_AF_Start_Addr_LatchOFF_aft_AR		= 19;	//Latch OFF after any AR
	gP_AF_Start_Addr_Disable_AR				= 20;	//Disable AR if not switching (TV)
	gP_AF_Start_Addr_didt_comp				= 21;	//didt comp
	gP_AF_Start_Addr_OT_Hys_30C				= 22;	//OT 30C hysteresis
	gP_AF_Start_Addr_LatchOFF_w_OT			= 23;	//Latch OFF with OT
	gP_AF_Start_Addr_Disable_ILIM_Select	= 24;	//Disable ILIM Select via BP Cap
	gP_AF_Start_Addr_Select_ILIM_Incr		= 25;	//Select Standard or Increased ILIM
	gP_AF_Start_Addr_minus_20pct_ILIM		= 26;	
	gP_AF_Start_Addr_plus_20pct_ILIM		= 27;	
	gP_AF_Start_Addr_Samsung_Mode			= 28;	
	gP_AF_Start_Addr_OTP					= 29;	//bits 29 to 31
	gP_AF_Start_Addr_SDS_OFF				= 32;	//B3 silicon and later
	gP_AF_Start_Addr_Rcv					= 33;	//bits 33 to 35
	gP_AF_Start_Addr_Driver_Size			= 36;	//bits 36 to 39
	gP_AF_Start_Addr_Rsense_up				= 40;	
	gP_AF_Start_Addr_Vx_adjust				= 41;	//bits 41 to 45
	gP_AF_Start_Addr_ILIM_Ratio				= 46;	//bits 46 to 49 (ILIM Ratio = ILIM+1 / ILIM)
	gP_AF_Start_Addr_ILIM_TC				= 50;	//bits 50 to 53
	gP_AF_Start_Addr_AR_Request				= 54;	//AR request instead of latchoff request
	gP_AF_Start_Addr_ZF						= 55;	

	if (gGaN)
	{
		// DX121C Primary AF global addresses
		gP_AF_Start_Addr_OTP				= 20;	//bits 20 to 22
		gP_AF_Start_Addr_OT_Hys_30C			= 26;	//OT 30C hysteresis
		gP_AF_Start_Addr_Disable_AR			= 27;	//Disable AR if not switching (TV)
		gP_AF_Start_Addr_ZVS_Ton			= 29;	//bits 29 to 30
		gP_AF_Start_Addr_ZVS_Trim			= 31;	//bits 31 to 32
		gP_AF_Start_Addr_ZVSon				= 36;
		gP_AF_Start_Addr_UV					= 37;
		gP_AF_Start_Addr_ZVSdelaym20		= 39;
		gP_AF_Start_Addr_IlimLEB			= 40;
		gP_AF_Start_Addr_VpinCTRL_iREF20pct	= 41;
		gP_AF_Start_Addr_ZVS_Delay			= 42;	//bits 42 to 45
		gP_AF_Start_Addr_SDSpct				= 46;	//bits 46 to 47
		gP_AF_Start_Addr_ILIM_Ratio			= 48;	//bits 48 to 49 (ILIM Sense Ratio)
	}

	// DX112B2 Secondary AF global addresses
	gSecondary_AF_Addr_Start				= 1;
	gFosc_AF_Addr_Start						= 1;	//bits(1,2,3,4 => F1/2/3/4) "Frequency"
	gPK_ssSpeed_AF_Addr_Start				= 5;	//bit 5,6,7 "FWpin peak switch comm delay compensation / Softstart Speedload option"
	gRnw_AF_Addr_Start						= 11;	//bits(11,12 => Rnw5/6) "Rjfet matching adjustment"
	gRnwFine_AF_Addr_Start					= 13;	//bits(13,14,15,16 => Rnw1/2/3/4) "Rjfet matching fine adjustment"
	gFWC2_AF_Addr_Start						= 17;	//bits 17 "Select FWC alternate logic path (using edge detector)"
	gNoFWC100mV_AF_Addr_Start				= 18;	//bits 18 "disable FWC comparator +100mV threshold feature"
	gCap_AF_Addr_Start						= 19;	//bits(19,20,21 => Cap1/2/3) "FWC comparator filter cap size adjustment"
	gPKdig_AF_Addr_Start					= 22;	//bits(22,23,24,25 => PKdig1/2/3/4) "FWPK switch comm delay compensation 2, using digital ladder"
	gSRth_AF_Addr_Start						= 26;	//bits(26,27,28,29 => SRth1/2/3/4) "SR comparator threshold adjustment (zero TC)"
	gVshunt_AF_Addr_Start					= 30;	//bits 30 "Trim to enable shunt regulator"
	gVref_AF_Addr_Start						= 32;	//bits(32,33,34,35,36,37 => V1/2/3/4/5/6) "Vref(REQ) trim"
	gIintTC_AF_Addr_Start					= 38;	//bits(38,39,40,41 => IintTC1/2/3/4) "SR comparator biasing current TC adjustment"
	gDOPL_AF_Addr_Start						= 42;	//bit 42 "Trim to disable FWpin Peak SW"
	gREQlow_AF_Addr_Start					= 43;	//bit 43 "Select to give up control immediately when REQ pulled < Vref/4"
	gXFWPK_AF_Addr_Start					= 44;	//bit 44 "Trim to disable FW pin Peak switch"
	gLO_dis_AF_Addr_Start					= 51;	//bit 51 "Trim to disable sending out latch-off command"

	//********************  Get handler name  **************************
	h_name = our_handler->current->hdlr_info.GetHandlerName();
	if (!strnicmp(h_name, "Manual",	6))		gManual_Handler = 1;
	if (!strnicmp(h_name, "Rasco",	6))		gRasco_Handler  = 1;
	printf("%s handler selected\n", h_name);

	//********************  HardwareList  **************************
	LPCTSTR LB_name;
	LPCTSTR CB_name;
	LPCTSTR IB_name;
	char buffer[10] = {0};

	LB_name = HardwareList.LoadBoard().Name();
	CB_name = HardwareList.HandlerContactor().Name();
	IB_name = HardwareList.Inductor().Name();

	strncpy (buffer, LB_name + 2, strlen(LB_name) - 2);
	gLB_ID = atoi(buffer);
	strncpy (buffer, IB_name + 2, strlen(IB_name) - 2);
	gIB_ID = atoi(buffer);
	strncpy (buffer, CB_name + 2, strlen(CB_name) - 2);
	gCB_ID = atoi(buffer);

	LB_Type	= HardwareList.LoadBoard().HardwareSubType();
	LB_Rev	= HardwareList.LoadBoard().HardwareRevision();
	CB_Type	= HardwareList.HandlerContactor().HardwareSubType();
	CB_Rev	= HardwareList.HandlerContactor().HardwareRevision();
	IB_Type	= HardwareList.Inductor().HardwareSubType();
	IB_Rev	= HardwareList.Inductor().HardwareRevision();
	TB_Type	= HardwareList.TestBlock().HardwareSubType();
	TB_Rev	= HardwareList.TestBlock().HardwareRevision();

	gLB_Type_Rev =0;
	gCB_Type_Rev =0;
	gIB_Type_Rev =0;
	gTB_Type_Rev =0;
	gLB_Type_Rev = LB_Type	+ (LB_Rev / 100.0);
	gCB_Type_Rev = CB_Type	+ (CB_Rev / 100.0);
	gIB_Type_Rev = IB_Type	+ (IB_Rev / 100.0);
	gTB_Type_Rev = TB_Type	+ (TB_Rev / 100.0);

	//Rasco Hardware required
	if (BoardRev >= 9)
	{
		//HardwareList.RegisterRequiredBoard(CHardwareList::LOADBOARD, BoardType, BoardRev, "Inno3 LB Rev 10");
		HardwareList.RegisterRequiredBoard(CHardwareList::LOADBOARD, 6204, 10, "Inno3 LB Rev 10");
		HardwareList.RegisterRequiredBoard(CHardwareList::HANDLERCONTACTORBOARD, ContactorType, ContactorRev,"MINNO CB for RASCO Rev 10 LB");
		HardwareList.RegisterRequiredBoard(CHardwareList::INDUCTOR, InductorType, InductorRev, "MINNO Inductor");

		if (HardwareList.VerifyRequiredBoardList())
			g_Setup_OK = 1;
		else
			g_Setup_OK = 0;
	}
	else
	{
		g_Setup_OK = 0;
	}

	g_TurretCB = 0;

	INNO_Gage_ChanAB_setup(0.10);	//Setup for Gage Digitizer Channels A,B trigger level
}

void DDD_init()
{
	ddd_7->init();
	wait.delay_10_us(10); 
	ddd_7->ddd_set_clock_period(Dclk_period);		
	ddd_7->ddd_set_no_delay();
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(0.0);		// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_connect_drivers();	
	//ddd_7->ddd_set_voltage_ref(DDD_Vref);
	wait.delay_10_us(100); 
	ddd_7->ddd_set_voltage_ref(0.0);
	wait.delay_10_us(100);                
	DDD_Load_Loop_Pattern();
	wait.delay_10_us(10);
	DDD_Load_Patterns();
	wait.delay_10_us(10); 
	ddd_7->ddd_run_pattern(First_address, Last_address);
	wait.delay_1_us((int (Last_address- First_address+1)*Dclk_period*1e6) + 5.51); 
}

void DDD_Load_Loop_Pattern()
{	
	int	start_vec=0, stop_vec=0, pulses=0;
	int t_hi=0, t_lo=0, t_hi_1=0, t_lo_1=0, t_hi_2=0, t_lo_2=0, vec_hi=0, vec_lo=0;
	int t_hi_FW =0, t_lo_FW=0, t_hi_FB=0, t_lo_FB=0, t_hi_Vout=0, t_lo_Vout=0, FB_vec=0, FW_vec=0, Vout_cycle_vec=0;
	int t_hi_Vpin =0, t_lo_Vpin = 0, Vpin_vec=0, Vpin_cycle_vec=0, n_Vpin_cycles=0, Vout_vec=0;
	int i=0, j=0, k=0, m=0, n=0, p=0, FB_cycle_vec=0, FW_cycle_vec=0, n_FB_cycles=0, n_FW_cycles=0, n_Vout_cycles=0;
	float t_high=0, t_low=0;
	float Mclk_in_Mhz=0;
	int End_vec = 0;

	//FWPK Switching 
	float	t_hi_300kHz	=0,
			t_hi_1MHz	=0,
			t_hi_4us	=0,
			t_lo1st		=0;

	if(Dclk_period !=0) 
		Mclk_in_Mhz = 1/(Dclk_period*1e6);
	else Mclk_in_Mhz =0.0;

	First_address = 0;

	//-------------------------------------------------------------------
	//	FW negative pulses   - Loop pulses
	//  FB 100kHz clk pulses - Loop pulses
	//-------------------------------------------------------------------

	//t_hi_FW = 31*Mclk_in_Mhz; t_lo_FW = 4*Mclk_in_Mhz;		// FW   Hi,Low = 31us,4us for Secondary FW looping pulses
	t_hi_FW		= 6*Mclk_in_Mhz; t_lo_FW   = 6*Mclk_in_Mhz;		// FW   Hi,Low = 31us,4us for Secondary FW looping pulses
	t_hi_FB		= 9*Mclk_in_Mhz; t_lo_FB   = 1*Mclk_in_Mhz;		// FB   Hi,Low =  9us,1us for Secondary FB looping pulses
	//t_hi_Vpin	= 1*Mclk_in_Mhz; t_lo_Vpin = 29*Mclk_in_Mhz;	// Vpin Hi,Low =  1us,29us for Secondary Vpin looping pulses
	//HL made changes due to too narrow pulse (1us) on RS & Turret setup.
	t_hi_Vpin	= 5*Mclk_in_Mhz; t_lo_Vpin = 25*Mclk_in_Mhz;	// Vpin Hi,Low =  5us,25us for Secondary Vpin looping pulses
	t_hi_Vout	= 9*Mclk_in_Mhz; t_lo_Vout = 1*Mclk_in_Mhz;		// Vout Hi,Low =  9us,1us for Secondary FB looping pulses

	Vpin_cycle_vec	= t_hi_Vpin + t_lo_Vpin;	//120 vectors for 30us, 1us Lo and 29us High
	FB_cycle_vec	= t_hi_FB	+ t_lo_FB;		// 40 vectors for 100kHz with 0.25us per vector
	FW_cycle_vec	= t_hi_FW	+ t_lo_FW;		//140 vectors for 34us,1us Hi/Lo
	Vout_cycle_vec  = t_hi_Vout + t_lo_Vout;	// 40 vectors for 100kHz with 0.25us per vector

	i =0;
//	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	start_vec	= i; 
	stop_vec	= 2*Vpin_cycle_vec;	// 2 cycles of Hi/Lo 

	FW_Neg_loop_pulse_start		= start_vec;
	Vpin_loop_pulse_start		= start_vec;
	FB_100kHz_loop_pulse_start	= start_vec;

	n_FB_cycles		= stop_vec / FB_cycle_vec;
	n_Vpin_cycles	= stop_vec / Vpin_cycle_vec;
	n_FW_cycles		= stop_vec / FW_cycle_vec;
	n_Vout_cycles   = stop_vec / Vout_cycle_vec;

	for (i= start_vec; i< stop_vec; i++)	// Load FW and FB looping pulses at the same time
	{
		n = i/FB_cycle_vec;
		k = i/Vpin_cycle_vec;
		m = i/FW_cycle_vec;
		p = i/Vout_cycle_vec;

		// Define FB, Vpin and FW Hi/Lo
		if( i <= (n*FB_cycle_vec + t_hi_FB/2 - 1	  )																	)	FB_vec = 0;
		if( i >= (n*FB_cycle_vec + t_hi_FB/2		  )		  && i <= (n*FB_cycle_vec + t_hi_FB/2 + t_lo_FB-1		)	)	FB_vec = 1;
		if( i >= (n*FB_cycle_vec + t_hi_FB/2 + t_lo_FB)		  && i <= (n*FB_cycle_vec	+ t_hi_FB-1					)	)	FB_vec = 0;
		if( i <= (k*Vpin_cycle_vec + t_hi_Vpin/2 - 1		)															)	Vpin_vec = 1;
		if( i >= (k*Vpin_cycle_vec + t_hi_Vpin/2			) && i <= (k*Vpin_cycle_vec + t_hi_Vpin/2 + t_lo_Vpin-1 )	)	Vpin_vec = 0;
		if( i >= (k*Vpin_cycle_vec + t_hi_Vpin/2 + t_lo_Vpin) && i <= (k*Vpin_cycle_vec	+ t_hi_Vpin-1				)	)	Vpin_vec = 1;
		if( i <= (m*FW_cycle_vec + t_hi_FW/2 - 1	  )																	)	FW_vec = 0;
		if( i >= (m*FW_cycle_vec + t_hi_FW/2		  )		  && i <= (m*FW_cycle_vec + t_hi_FW/2 + t_lo_FW-1		)	)	FW_vec = 1;
		if( i >= (m*FW_cycle_vec + t_hi_FW/2 + t_lo_FW)		  && i <= (m*FW_cycle_vec + t_hi_FW-1					)	)	FW_vec = 0;
		if( i <= (p*Vout_cycle_vec + t_hi_Vout/2 - 1	  )																)	Vout_vec = 1;
		if( i >= (p*Vout_cycle_vec + t_hi_Vout/2		  )	  && i <= (p*Vout_cycle_vec + t_hi_Vout/2 + t_lo_Vout-1	)	)	Vout_vec = 0;
		if( i >= (p*Vout_cycle_vec + t_hi_Vout/2 + t_lo_Vout) && i <= (p*Vout_cycle_vec	+ t_hi_Vout-1				)	)	Vout_vec = 1;

		////Making Vout to be the same as FB so only FW,FB,Vpin should be care about below.
		//if( FW_vec==0 && FB_vec==0 && Vpin_vec==0 && Vout_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0000");
		//if( FW_vec==0 && FB_vec==0 && Vpin_vec==1 && Vout_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0001");
		//if( FW_vec==0 && FB_vec==1 && Vpin_vec==0 && Vout_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1010");
		//if( FW_vec==0 && FB_vec==1 && Vpin_vec==1 && Vout_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1011");
		//if( FW_vec==1 && FB_vec==0 && Vpin_vec==0 && Vout_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0100");
		//if( FW_vec==1 && FB_vec==0 && Vpin_vec==1 && Vout_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0101");
		//if( FW_vec==1 && FB_vec==1 && Vpin_vec==0 && Vout_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1110");
		//if( FW_vec==1 && FB_vec==1 && Vpin_vec==1 && Vout_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1111");
		//Vout(4) FW(3) FB(2) Vpin(1)
		if		( Vout_vec==0 && FW_vec==0 && FB_vec==0 && Vpin_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0000");
		else if	( Vout_vec==0 && FW_vec==0 && FB_vec==0 && Vpin_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX0001");
		else if	( Vout_vec==0 && FW_vec==0 && FB_vec==1 && Vpin_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0010");
		else if	( Vout_vec==0 && FW_vec==0 && FB_vec==1 && Vpin_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX0011");
		else if	( Vout_vec==0 && FW_vec==1 && FB_vec==0 && Vpin_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0100");
		else if	( Vout_vec==0 && FW_vec==1 && FB_vec==0 && Vpin_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX0101");
		else if	( Vout_vec==0 && FW_vec==1 && FB_vec==1 && Vpin_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX0110");
		else if	( Vout_vec==0 && FW_vec==1 && FB_vec==1 && Vpin_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX0111");
		else if	( Vout_vec==1 && FW_vec==0 && FB_vec==0 && Vpin_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX1000");
		else if	( Vout_vec==1 && FW_vec==0 && FB_vec==0 && Vpin_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1001");
		else if	( Vout_vec==1 && FW_vec==0 && FB_vec==1 && Vpin_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX1010");
		else if	( Vout_vec==1 && FW_vec==0 && FB_vec==1 && Vpin_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1011");
		else if	( Vout_vec==1 && FW_vec==1 && FB_vec==0 && Vpin_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX1100");
		else if	( Vout_vec==1 && FW_vec==1 && FB_vec==0 && Vpin_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1101");
		else if	( Vout_vec==1 && FW_vec==1 && FB_vec==1 && Vpin_vec==0)		ddd_7->ddd_load_pattern(i,"XXXX1110");
		else if	( Vout_vec==1 && FW_vec==1 && FB_vec==1 && Vpin_vec==1)		ddd_7->ddd_load_pattern(i,"XXXX1111");
		else																ddd_7->ddd_load_pattern(i,"XXXX0000");

	}
	FW_Neg_loop_pulse_stop		= i-1;
	FB_100kHz_loop_pulse_stop	= i-1;
	Vpin_loop_pulse_stop		= i-1;
	Vout_loop_pulse_stop		= i-1;

	stop_vec = FB_100kHz_loop_pulse_stop + (FB_cycle_vec * 18);	//18 cycles of FB clocking at 100kHz
	FB_100kHz_start = FB_100kHz_loop_pulse_stop + 1;
	for(i=FB_100kHz_start; i< stop_vec; i++)
	{
		//INNO3X Pattern
		/*for(j=0;j<t_hi_FB/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}
		for(j=0;j<t_lo_FB ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX00X");i++;} 
		for(j=0;j<t_hi_FB/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}*/

		//MINNO Pattern
		for(j=0;j<t_hi_FB/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}
		for(j=0;j<t_lo_FB ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX00X");i++;} 
		for(j=0;j<t_hi_FB/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}
		i--;
	}
		
	FB_100kHz_stop = i-1;

	stop_vec = FB_100kHz_stop + (FB_cycle_vec * 106);	//106 cycles (5 for start holdoff, 100 for meas, extra 1 for holdoff work properly)
	FB_100kHz_100_pulses_start  = FB_100kHz_stop + 1;
	FW_100kHz_3_pulses_start  = FB_100kHz_stop + 1;
	for(i=FB_100kHz_100_pulses_start; i< stop_vec; i++)
	{
		//INNO3X pattern
		/*for(j=0;j<t_hi_FB/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}
		for(j=0;j<t_lo_FB ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX00X");i++;} 
		for(j=0;j<t_hi_FB/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}*/

		//MINNO pattern
		for(j=0;j<t_hi_FB/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX00X");i++;}
		for(j=0;j<t_lo_FB ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} 
		for(j=0;j<t_hi_FB/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX00X");i++;}
		i--;
	}
	
	FB_100kHz_100_pulses_stop = i-1;
	FW_100kHz_3_pulses_stop = FW_100kHz_3_pulses_start + 85;
	i += 50;
	gDDD_loop_end = i;
	
}

void DDD_Load_Patterns()
{
	int	start_vec=0, stop_vec=0, pulses=0;
	int t_hi=0, t_lo=0, t_hi_1=0, t_lo_1=0, t_hi_2=0, t_lo_2=0, vec_hi=0, vec_lo=0;
	int t_hi_FW =0, t_lo_FW=0, t_hi_FB=0, t_lo_FB=0, t_hi_Vout=0, t_lo_Vout=0, FB_vec=0, FW_vec=0, Vout_cycle_vec=0;
	int t_hi_Vpin =0, t_lo_Vpin = 0, Vpin_vec=0, Vpin_cycle_vec=0, n_Vpin_cycles=0, Vout_vec=0;
	int i=0, j=0, k=0, m=0, n=0, p=0, FB_cycle_vec=0, FW_cycle_vec=0, n_FB_cycles=0, n_FW_cycles=0, n_Vout_cycles=0;
	float t_high=0, t_low=0;
	float Mclk_in_Mhz=0;
	int End_vec = 0;

	//FWPK Switching 
	float	t_hi_300kHz	=0,
			t_hi_1MHz	=0,
			t_hi_4us	=0,
			t_lo1st		=0;

	if(Dclk_period !=0) 
		Mclk_in_Mhz = 1/(Dclk_period*1e6);
	else Mclk_in_Mhz =0.0;

	First_address = gDDD_loop_end;
	i= gDDD_loop_end;//Important step for MINNO, i value should increament after its final value in DDD_load_loop_pattern function
	//-------------------------------------------------------------------
	//	FB 100kHz pulse - Single pulse 
	//-------------------------------------------------------------------
	t_hi= 9*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FB_100kHz_pulse_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}

		i--;
	}
	FB_100kHz_pulse_stop = i-1;

	/*******************************************************************************************************
	 *****	SR_10pctClampOff (DDD load pattern starting at FW high and FB high before FB request.
	 *******************************************************************************************************
		FW -----| |---------| |--| |--------------------|							-- FW high
				|_|			|_|  |_|					|______________________		__ FW Low

																
														|-------|					-- SR High (~vBPS_plus)
		SR _____________________________________________|		|______________		__ SR Low  (~0V)


		(Vout)													 ______________		__ FB 15% above CVth	or Vout 15% above Vout target
		 or														|
		(FB) -------------------------------| |------------------					-- FB 5%  above CVth	or Vout 5%  above Vout target
											|_|										__ FB     below CVth	or Vout		below Vout target
							 _	  _			 _
		Comm Pulse___________||___||_________||________________________________		xx Internal signal
											 |<-------->|
											     <30us
	 *******************************************************************************************************/
	t_hi= 9*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; 
	stop_vec= i + 1*(t_hi+t_lo) + 200; //Reserve 200 vectors for start/end patterns
	SR_10pctClampOff_start= start_vec;

	//FW,FB (high,high) -> FW,FB (high,high) =>FW,FB (high,low) =>FW,FB (high, high) -> FW (low, high)
	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<100;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}	//FW,FB (high,high) for 100 vectors
		for(j=0;j<t_hi/2;j++)	{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}	//FW,FB (high,high) 
		for(j=0;j<t_lo ;j++)	{ddd_7->ddd_load_pattern(i,"XXXXX10X");i++;}	//FW,FB (high,low )
		for(j=0;j<t_hi/2;j++)	{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}	//FW,FB (high,high)
		for(j=0;j<100;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}	//FW,FB (low, high)

		i--;
	}
	SR_10pctClampOff_end = i-1;

	//-------------------------------------------------------------------
	//	FB 100kHz pulse + RTM pulse for ILIM_NORM test 
	//  (18 pulses of 100kHz and stop for 30us, then 1 pulse of 100kHz, then stop for >200us, then 3 pulses of 100kHz)
	//-------------------------------------------------------------------
	t_hi= 9*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//9us High, 1us Low
	i +=50;
	FB_100kHz_ILIM_pulse_start= i;

	//18 pulses of 100kHz
	pulses = 1;
	while(pulses<=18)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}//MINNO pattern
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}//MINNO pattern
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}//MINNO pattern

			i--;
		}
		pulses++;
	}
	FB_100kHz_ILIM_18_pulse_stop = i-1;

	//ILIM OFF (FB High) for 30us (including the t_hi/2 from pulse of previous & next, the rest require for FB High would be 30us-9us = 21us)
	//for(j=0; j<((30-9)*Mclk_in_Mhz); j++)	{ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}//INNO3X pattern
	for(j=0; j<((30-9)*Mclk_in_Mhz); j++)	{ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}//MINNO pattern
	//5 pulse of 100kHz
	pulses = 1;
	while(pulses<=5)
	{
		start_vec = i; stop_vec= i + 1*(t_hi+t_lo);
		for (i= start_vec; i< stop_vec; i++)
		{
			//INNO3X pattern
			/*for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}*/

			//MINNO pattern
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
			i--;
		}
		pulses++;
	}

	//ILIM OFF (FB High) for >200us
	//for(j=0; j<(203*t_lo); j++)	{ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}//INNO3X pattern
	for(j=0; j<(203*t_lo); j++)	{ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}//MINNO pattern
	//3 pulses of 100kHz
	pulses = 1;
	while(pulses<=3)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			//INNO3X pattern 
			/*for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}*/

			//MINNO pattern
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}

			i--;
		}
		pulses++;
	}

	FB_100kHz_ILIM_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	FB 18kHz pulse. 300 pulses of 18kHz. 
	//-------------------------------------------------------------------
	t_hi= 55*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//55us High, 1us Low
	i +=50;
	FB_18kHz_pulse_start= i;

	//300 pulses of 18kHz
	pulses = 1;
	while(pulses<=300)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			//INNO3X pattern
			/*for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}*/

			//MINNO pattern
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}

			i--;
		}
		pulses++;
	}
	FB_18kHz_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	Vout 18kHz pulse.  80 pulses of 18kHz.
	//-------------------------------------------------------------------
	t_hi= 55*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//55us High, 1us Low
	i +=50;
	Vout_18kHz_pulse_start= i;

	//80 pulses of 18kHz
	pulses = 1;
	while(pulses<=80)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX1XXX");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0XXX");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX1XXX");i++;}

			i--;
		}
		pulses++;
	}
	Vout_18kHz_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	FB 125kHz pulses. 250 pulses of 125kHz. 
	//-------------------------------------------------------------------
	t_hi= 7*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//7us High, 1us Low
	i +=50;
	FB_125kHz_pulse_start= i;

	//250 pulses of 125kHz
	pulses = 1;
	while(pulses<=250)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			//INNO3X pattern
			/*for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}*/

			//MINNO pattern
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}

			i--;
		}
		pulses++;
	}
	FB_125kHz_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	Vout 125kHz pulses. 250 pulses of 125kHz. 
	//-------------------------------------------------------------------
	//t_hi= 7*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//7us High, 1us Low
	//i +=50;
	//Vout_125kHz_pulse_start= i;

	////250 pulses of 125kHz
	//pulses = 1;
	//while(pulses<=250)
	//{
	//	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	//	for (i= start_vec; i< stop_vec; i++)
	//	{
	//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX1XXX");i++;}
	//		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0XXX");i++;} 
	//		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX1XXX");i++;}

	//		i--;
	//	}
	//	pulses++;
	//}
	//Vout_125kHz_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	FB 125kHz pulses. 63 pulses of 125kHz. 
	//-------------------------------------------------------------------
	t_hi= 7*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//7us High, 1us Low
	i +=50;
	FB_125kHz_pulse_start_X= i;

	//63 pulses of 125kHz
	pulses = 1;
	while(pulses<=63)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}

			i--;
		}
		pulses++;
	}
	FB_125kHz_pulse_stop_X = i-1;

	//-------------------------------------------------------------------
	//	FB 100kHz pulses. 35 pulses of 100kHz. 
	//-------------------------------------------------------------------
	t_hi= 9*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//9us High, 1us Low
	i +=50;
	FB_100kHz_ILIM_pulse_start_X= i;

	//35 pulses of 100kHz
	pulses = 1;
	while(pulses<=35)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			//INNO3X pattern
			/*for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}*/

			//MINNO pattern
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}

			i--;
		}
		pulses++;
	}
	FB_100kHz_ILIM_pulse_stop_X = i-1;

	//-------------------------------------------------------------------
	//	Vpin 6 clocks. //
	//-------------------------------------------------------------------
	t_hi= 1*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//1us High, 1us Low
	i +=50;
	Vpin_6clocks_start = i;

	// 6 pulses //
	pulses = 1;
	while(pulses<=6)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;} 
			//for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}

			i--;
		}
		pulses++;
	}
	Vpin_6clocks_stop = i-1;

	//-------------------------------------------------------------------
	//	Vpin 4 clocks. //
	//-------------------------------------------------------------------
	t_hi= 1*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//1us High, 1us Low
	i +=50;
	Vpin_4clocks_start = i;

	// 4 pulses //
	pulses = 1;
	while(pulses<=4)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;} 
			//for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}

			i--;
		}
		pulses++;
	}
	Vpin_4clocks_stop = i-1;

	//-------------------------------------------------------------------
	//	Vpin 2 clocks. //
	//-------------------------------------------------------------------
	t_hi= 1*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//1us High, 1us Low
	i +=50;
	Vpin_2clocks_start = i;

	// 2 pulses //
	pulses = 1;
	while(pulses<=2)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;} 
			//for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}

			i--;
		}
		pulses++;
	}
	Vpin_2clocks_stop = i-1;

	//-------------------------------------------------------------------
	//	Vpin 3 negative clocks. //
	//-------------------------------------------------------------------
	t_hi= 50*Mclk_in_Mhz; t_lo= 50*Mclk_in_Mhz;	//50us High, 50us Low
	i +=50;
	Vpin_3NegClocks_start = i;

	// 3 pulses //
	pulses = 1;
	while(pulses<=3)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;} 
			//for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}

			i--;
		}
		pulses++;
	}
	Vpin_3NegClocks_stop = i-1;

	//-------------------------------------------------------------------
	//	Vpin 2 clocks 30usec apart. //
	//-------------------------------------------------------------------
	t_hi= 1*Mclk_in_Mhz; t_lo= 29*Mclk_in_Mhz;	//1us High, 29us Low
	i +=50;
	Vpin_30usec_start = i;

	// 2 pulses //
	pulses = 1;
	while(pulses<=2)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;} 
			//for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}

			i--;
		}
		pulses++;
	}
	Vpin_30usec_stop = i-1;

	//-------------------------------------------------------------------
	//	Vpin 1 clock.  30usec pulse width. //
	//-------------------------------------------------------------------
	t_hi= 30*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//30us High //
	i +=50;
	Vpin_one_30us_clock_start = i;

	// 1 pulses //
	pulses = 1;
	while(pulses<=1)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX1");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;} 
			//for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}

			i--;
		}
		pulses++;
	}
	Vpin_one_30us_clock_stop = i-1;

	//-------------------------------------------------------------------
	//	FBpin 2 clocks 30usec apart. //
	//-------------------------------------------------------------------
	t_hi= 1*Mclk_in_Mhz; t_lo= 29*Mclk_in_Mhz;	//1us High, 29us Low
	i +=50;
	FBpin_30usec_start = i;

	// 2 pulses //
	pulses = 1;
	while(pulses<=2)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
			//for(j=0;j<t_hi;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXXX0");i++;}
			i--;
		}
		pulses++;
	}
	FBpin_30usec_stop = i-1;

	//-------------------------------------------------------------------
	//	FB 100kHz pulses. 5 pulses of 100kHz. 
	//-------------------------------------------------------------------
	t_hi= 9*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;	//9us High, 1us Low
	i +=50;
	FB_100kHz_pulse_start_5X= i;

	// 5 pulses of 100kHz //
	pulses = 1;
	while(pulses<=5)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}

			i--;
		}
		pulses++;
	}
	FB_100kHz_pulse_stop_5X = i-1;

	//-------------------------------------------------------------------
	//	FW 100kHz pulses. 30 pulses of 100kHz. 
	//-------------------------------------------------------------------
	t_hi= 5*Mclk_in_Mhz; t_lo= 5*Mclk_in_Mhz;	//9us High, 1us Low
	i +=50;
	FW_100kHz_pulse_start_40X= i;

	// 40 pulses of 100kHz //
	pulses = 1;
	while(pulses<=40)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}

			i--;
		}
		pulses++;
	}
	FW_100kHz_pulse_stop_40X = i-1;



	//--------------------------------------------------------------------------------------------------------------------------------------
	//	FW Peak Switching Half Ring pulses  
	//  (1us Low duty cycle, Half Ring High Duty cycle (1.67us for 300kHz and 0.5us for 1MegaHz), then 1us low duty cycle, then high)
	//	* To avoid resetting the DDD clock period, use 1.75us instead of 1.67us, so it will be ~285.7kHz instead of 300kHz.
	//--------------------------------------------------------------------------------------------------------------------------------------
	t_hi_300kHz	= 1.75*Mclk_in_Mhz;	//1.75us High for 285.7kHz
	t_hi_1MHz	= 0.50*Mclk_in_Mhz;	//0.50us High for 1MegaHz
	t_hi_4us	= 4.00*Mclk_in_Mhz;	//4.00us High
	t_hi		= 0.50*Mclk_in_Mhz;	//0.50us High
	t_lo		= 1.0*Mclk_in_Mhz;	//1.00us Low  RLB 
	t_lo1st		= 2.0*Mclk_in_Mhz;	//2.00us Low  RLB 1.0u filter REV B, REV B2 may change back to 1.5us

	int t_1p75us = 1.75*Mclk_in_Mhz;
	int t_0p50us = 0.50*Mclk_in_Mhz;
	i +=50;
	FWPK_pos_1p75us_pulse_start = i;
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXX00XX");i++;}	//vout=0  xie 5/21/2019
	for (j=0; j<t_1p75us; j++)			{ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;}	//vout=0  xie 5/21/2019
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXX00XX");i++;}	//vout=0  xie 5/21/2019
	//for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;}
	//for (j=0; j<t_1p75us; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
	//for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;}
	FWPK_pos_1p75us_pulse_stop = i-1;

	i +=10;
	FWPK_pos_0p50us_pulse_start = i;
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;}
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;}
	FWPK_pos_0p50us_pulse_stop = i-1;
	
	i +=10;
	FWPK_neg_0p50us_pulse_start = i;
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;}
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXX00XX");i++;}
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;}
	FWPK_neg_0p50us_pulse_stop = i-1;

	i +=10;
	FWPK_neg_1p75us_pulse_start = i;
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
	for (j=0; j<t_1p75us; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;}
	for (j=0; j<t_0p50us; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
	FWPK_neg_1p75us_pulse_stop = i-1;
	
	i +=10;
	FWPK_300kHz_Ring_pulse_start= i;
	//4 pulses of ~300kHz Ring pulses (1us_Low, 1.75us_High, 1us_Low, 0.5us_High)
	//for(j=0;j<=t_lo1st ;j++)		{ddd_7->ddd_load_pattern(i,"XXXX00XX");i++;} //2.00us Low	(Vout=0, xie 5/21/2019)
	for(j=0;j<=t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXX00XX");i++;} //1.00us Low	(Vout=0, xie 5/21/2019)
	for(j=0;j<t_hi_300kHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;} //1.65us High (303kHz half ring) (takes ~100ns to reach vHigh)
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXX00XX");i++;} //0.50us Low	(Vout=0, xie 5/21/2019)
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;} //0.50us High	(Vout=0, xie 5/21/2019)
	FWPK_300kHz_Ring_pulse1_stop = i-1;

	i +=10;
	FWPK_300kHz_Ring_pulse_start_FB= i;	//This is same as above "FWPK_300kHz_Ring_pulse_start" except with FB start Hi, end Low.
	//4 pulses of ~300kHz Ring pulses (1us_Low, 1.75us_High, 1us_Low, 0.5us_High)
	for(j=0;j<=6 ;j++)				{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} //purposely set FB High before FW go Low
	for(j=0;j<=t_lo1st ;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;} //2.00us Low
	for(j=0;j<t_hi_300kHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} //1.65us High (303kHz half ring) (takes ~100ns to reach vHigh)
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;} //0.50us Low
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} //0.50us High
		//purposely set FW and FB high for an extra t_hi_300kHz (1.65us)
		for(j=0;j<t_hi_300kHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} //1.65us High (303kHz half ring) (takes ~100ns to reach vHigh)
										 ddd_7->ddd_load_pattern(i,"XXXXX10X");i++;	 //set FB back to low 
	FWPK_300kHz_Ring_pulse1_stop_FB = i-1;

	i +=10;
	FWPK_1MHz_Ring_learn_pulse_start= i;
	//4 pulses of 1MHz Ring pulses (1us_Low, 0.5us_High, 1us_Low, 0.5us_High)  Note: 0.40us High (1.25MHz half ring) (takes ~100ns to reach vHigh)
//	for(j=0;j<=t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}
	for(j=0;j<=t_lo1st ;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}
	for(j=0;j<t_hi_1MHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX100");i++;}
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX100");i++;}
	FWPK_1MHz_Ring_learn_pulse_stop = i-1;

	////FW stay high for 40us (40us for non-tSoft devices)
	//for(j=0;j<(40*Mclk_in_Mhz);j++) {ddd_7->ddd_load_pattern(i,"XXXXX100");i++;}

	//FW stay high for 80us (80us for     tSoft devices)
	for(j=0;j<(80*Mclk_in_Mhz);j++) {ddd_7->ddd_load_pattern(i,"XXXXX100");i++;}

	i +=10;
	FWPK_1MHz_Ring_Dable_pulse_start_FB= i;  //This is same as below "FWPK_1MHz_Ring_Dable_pulse_start" except with FB start Hi, end Low.
	//4 pulses of 1MHz Ring pulses (1us_Low, 0.5us_High, 1us_Low, 0.5us_High)  Note: 0.40us High (1.25MHz half ring) (takes ~100ns to reach vHigh)
	for(j=0;j<=2 ;j++)				{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}  //purposely set FB High before FW go Low
	for(j=0;j<=t_lo1st ;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}
	for(j=0;j<t_hi_1MHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}
		//purposely set FW and FB high for an extra t_hi_1MHz (0.5us)
		for(j=0;j<t_hi_1MHz*60;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} 
										 ddd_7->ddd_load_pattern(i,"XXXXX10X");i++;	 //set FB back to low 
	FWPK_1MHz_Ring_Dable_pulse_stop_FB = i-1;

	i +=10;
	FWPK_1MHz_Ring_Dable_pulse_start= i;
	//4 pulses of 1MHz Ring pulses (1us_Low, 0.5us_High, 1us_Low, 0.5us_High)  Note: 0.40us High (1.25MHz half ring) (takes ~100ns to reach vHigh)
	for(j=0;j<=t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}
//	for(j=0;j<=t_lo1st ;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}
	for(j=0;j<t_hi_1MHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX100");i++;}
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX100");i++;}
	FWPK_1MHz_Ring_Dable_pulse_stop = i-1;

	i +=10;
	FWPK_1MHz_Ring_pulse1_start_FB= i;  //This is same as above "FWPK_1MHz_Ring_pulse1_start" except with FB start Hi, end Low.
	for(j=0;j<=2 ;j++)				{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}	//purposely set FB High before FW go Low
	for(j=0;j<=t_lo1st ;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}	//FWPK_1MHz_HighPulse1_start = i;
	for(j=0;j<t_hi_1MHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} 	//FWPK_1MHz_HighPulse1_stop = i-1;
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}	//FWPK_1MHz_HighPulse2_start = i;
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}	//FWPK_1MHz_HighPulse2_stop = i-1;
	FWPK_1MHz_Ring_pulse1_stop_FB = i-1;
	for(j=0;j<=t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}	//FWPK_1MHz_HighPulse3_start = i;
	for(j=0;j<t_hi_1MHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} 	//FWPK_1MHz_HighPulse3_stop = i-1;
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}	//FWPK_1MHz_HighPulse4_start = i;
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}	//FWPK_1MHz_HighPulse4_stop = i-1;
	FWPK_1MHz_Ring_pulse2_stop_FB = i-1;
	for(j=0;j<=t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}	//FWPK_1MHz_HighPulse5_start = i;
	for(j=0;j<t_hi_1MHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} 	//FWPK_1MHz_HighPulse5_stop = i-1;
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}	//FWPK_1MHz_HighPulse6_start = i;
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}	//FWPK_1MHz_HighPulse6_stop = i-1;
	FWPK_1MHz_Ring_pulse3_stop_FB = i-1;
	for(j=0;j<=t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;}	//FWPK_1MHz_HighPulse7_start = i;
	for(j=0;j<t_hi_1MHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} 	//FWPK_1MHz_HighPulse7_stop = i-1;
//	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}	//FWPK_1MHz_HighPulse8_start = i;
//rlb remove last pulse keep high
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}	//FWPK_1MHz_HighPulse8_start = i;
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}	//FWPK_1MHz_HighPulse8_stop = i-1;
		//purposely set FW and FB high for an extra t_hi_1MHz (0.5us)
		for(j=0;j<t_hi_1MHz;j++)		{ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;} 
										 ddd_7->ddd_load_pattern(i,"XXXXX10X");i++;	 //set FB back to low 
	FWPK_1MHz_Ring_pulse4_stop_FB = i-1;


	//MaxF_FaultP pattern
	i +=10;
	t_hi		= 0.25*Mclk_in_Mhz;	
	t_lo		= 0.25*Mclk_in_Mhz;	
	FWPK_p5us_Ring_pulse_start= i;
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}	
	for(j=0;j<t_hi; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX100");i++;} 	
	for(j=0;j<t_lo ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}	
	for(j=0;j<t_hi ;j++)			{ddd_7->ddd_load_pattern(i,"XXXXX100");i++;}	
	FWPK_p5us_Ring_pulse_stop = i-1;

	//MinF_FaultP pattern
	i +=10;
	t_hi		= 2.00*Mclk_in_Mhz;	
	t_lo		= 2.00*Mclk_in_Mhz;	
	FWPK_4us_Ring_pulse_start= i;
	for(j=0;j<t_lo; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}	
	for(j=0;j<t_hi; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX100");i++;} 	
	for(j=0;j<t_lo; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}	
	for(j=0;j<t_hi; j++)			{ddd_7->ddd_load_pattern(i,"XXXXX100");i++;}	
	FWPK_4us_Ring_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	Low, High, TriState Start/Stop patterns
	//-------------------------------------------------------------------
	i +=50; //HL:  Do not change this number "50" or voltage drop below ground happens when loading the DDD low pattern

	Low_pat_start_dummy = i;//+++++++++++++++++++++++++++++++++++++++++++++++++		
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
	Low_pat_stop_dummy = i-1;

	Low_pat_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++		
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXX00000");i++;}
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
	//i--;
	Low_pat_stop = i-1;

	Low_FB_pat_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++		
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXX00000");i++;}
	//for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}//INNO3X pattern
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}//MINNO pattern
	//i--;
	Low_FB_pat_stop = i-1;

	Low_FB_pat_start_with_Vpin= i;//+++++++++++++++++++++++++++++++++++++++++++++++++		
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXX00000");i++;}
	//for(j=0;j<3;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}//INNO3X pattern
	//for(j=3;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX01");i++;}//INNO3X pattern
	for(j=0;j<3;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}//MINNO Pattern
	for(j=3;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX11");i++;}//MINNO pattern
	//i--;
	Low_FB_pat_stop_with_Vpin = i-1;
	
	Low_FW_pat_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++		
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
	//i--;
	Low_FW_pat_stop = i-1;

	Low_XXX_pat_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++		
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}//INNO3X pattern
	//i--;
	Low_XXX_pat_stop = i-1;

	Low_pat_REQ_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
	Low_pat_REQ_stop = i-1;

	High_pat_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXX11111");i++;}
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX1111");i++;}//INNO3X pattern
	//for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}//MINNO pattern
	//i--;
	High_pat_stop = i-1;

	High_pat_Vpin_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXX00001");i++;}
	//i--;
	High_pat_Vpin_stop = i-1;

	High_pat_FB_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
	//for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXX00010");i++;}//INNO3X pattern
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}//MINNO pattern
	//i--;
	High_pat_FB_stop = i-1;

	High_pat_FW_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXX00100");i++;}
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX0100");i++;}
	//i--;
	High_pat_FW_stop = i-1;

	High_pat_Vout_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
//	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXX01000");i++;}
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXX1000");i++;}
	//i--;
	High_pat_Vout_stop = i-1;

	High_pat_REQ_start= i;//+++++++++++++++++++++++++++++++++++++++++++++++++
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
	High_pat_REQ_stop = i-1;

	Tristate_pat_start= i;//+++++++++++++++++++++++++++++++++++++++++++++
	for(j=0;j<5;j++) {ddd_7->ddd_load_pattern(i,"XXXXXXXX");i++;}
	//i--;
	Tristate_pat_stop = i-1;

	//---------------------------------------------------------------------------------------
	//	FW negative Single pulse for 100ns per vector.  High_Low_High = 17500ns_100ns_17500ns
	//---------------------------------------------------------------------------------------
	t_hi = 175*2;	t_lo = 1;
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FW_Neg_pulse_100ns_start = start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}

		i--;
	}
	FW_Neg_pulse_100ns_stop = i-1;


	//-------------------------------------------------------------------
	//	FB (Low 1us, High X care or > 40us)
	//-------------------------------------------------------------------
	t_hi= 35*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FB_tOVL_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		//INNO3X Pattern
		/*for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}*/
		
		//MINNO Pattern
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}

		i--;
	}
	FB_tOVL_stop = i-1;


	//Note that the vectors "FW Negative 1st, 2nd, 3rd, and Negative Edge" are in series 
	//2nd,3rd and Negative in series will be used for VBPS_Reset_Threshold purpose

	//-------------------------------------------------------------------
	//	FW negative 1st pulse - Single pulse 
	//-------------------------------------------------------------------
//	t_hi= 34*Mclk_in_Mhz; t_lo= 1*Mclk_in_Mhz;//+++++++++++++++++++++++++
	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FW_Neg_1st_pulse_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;}	//vout = 0  xie 5/21/2019
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX00XX");i++;} //vout = 0  xie 5/21/2019
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;} //vout = 0  xie 5/21/2019
		//for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
		//for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
		//for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}

		i--;
	}
	FW_Neg_1st_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	FW negative 2nd pulse - Single pulse 
	//-------------------------------------------------------------------
	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;//+++++++++++++++++++++++++
//	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FW_Neg_2nd_pulse_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}

		i--;
	}
	FW_Neg_2nd_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	FW negative 3rd pulse - Single pulse 
	//-------------------------------------------------------------------
	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;//+++++++++++++++++++++++++
//	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FW_Neg_3rd_pulse_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}

		i--;
	}
	FW_Neg_3rd_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	FW negative 4th pulse - Single pulse 
	//-------------------------------------------------------------------
	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;//+++++++++++++++++++++++++
//	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FW_Neg_4th_pulse_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}

		i--;
	}
	FW_Neg_4th_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	FW negative edge - Single 
	//-------------------------------------------------------------------
	t_hi= 33*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;//+++++++++++++++++++++++++
//	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FW_Neg_Edge_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;}

		i--;
	}
	FW_Neg_Edge_stop = i-1;

	//-------------------------------------------------------------------
	//	FW negative pulse - pulse train for Secondary out of test mode power up
	//-------------------------------------------------------------------
	t_hi= 5*Mclk_in_Mhz; t_lo= 5*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	FW_pulse_train_start= i;

	for (int pulse_cnt=0; pulse_cnt <20; pulse_cnt++)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}

			i--;
		}
	}
	FW_pulse_train_stop = i-1;


	//-------------------------------------------------------------------
	//	Antifuse pulse - Single pulse - Rising edge trigger
	//-------------------------------------------------------------------
	//Primary - Single pulse: 1us Lo - 2us Hi - 1us Lo
	t_hi= 2*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	AF_UV_pulse_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{	// Using DDD7_1. Leave un-used channels high to avoid negative edge!!!
		for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX00");i++;}
		for(j=0;j<t_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX01");i++;} 
		for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX00");i++;}

		i--;
	}
	AF_UV_pulse_stop = i-1;

	//Secondary - Single pulse: 1us Lo - 2us Hi - 1us Lo
	t_hi= 2*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	AF_FB_pulse_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{	// Using DDD7_2. Leave un-used channels high to avoid negative edge!!!
		for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX00");i++;}
		for(j=0;j<t_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX10");i++;} 
		for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX00");i++;}

		i--;
	}
	AF_FB_pulse_stop = i-1;


	//Last_address = AF_FB_pulse_stop;

	//--------------------------------------------------------------------------
	//	Inno4 Primary - Vpin Clk(Long) pulse: 1us Lo - 10us Hi  - 1us Lo
	//												 ___________	
	//										Vpin ___|			|____
	//--------------------------------------------------------------------------
	t_high	= 11e-6;	
	t_low	= 3e-6; //1us Low before and after 1us High
	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
	i +=50;
	start_vec= i; stop_vec= i + vec_hi + vec_lo;	

	AF_Vpin_Clk_pulse_start= start_vec;
	for (i= start_vec; i< stop_vec; i++)
	{	
		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
		for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0001");i++;} 
		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
		i--;
	}
	AF_Vpin_Clk_pulse_stop = i-1;


	//HL added this to reduce transition time to 10us per DE advice (<20us).
	//--------------------------------------------------------------------------
	//	Inno4 Primary - Vpin Clk(Long) pulse: 1us Lo - 10us Hi  - 1us Lo
	//												 ___________	
	//										Vpin ___|			|____
	//--------------------------------------------------------------------------


	t_high	= 10e-6;	
	t_low	= 2e-6; //2us Low before and after 2us High ==> Total of 4us between 10us pulses.
	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
	i +=50;
	start_vec= i; stop_vec= i + vec_hi + vec_lo;	

	int n_pulse = 0;
	AF_Vpin_Clk_pulse_start_6pulses = start_vec;
	for(n_pulse = 0; n_pulse <6; n_pulse++)
	{
		for (i= start_vec; i< stop_vec; i++)
		{	
			for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
			for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0001");i++;} 
			for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
			i--;
		}
		start_vec= i; stop_vec= i+ vec_hi + vec_lo;
	}
	AF_Vpin_Clk_pulse_stop_6pulses = i-1;


	//HL added this to reduce transition time to 10us per DE advice (<20us) for Turret HW
	//--------------------------------------------------------------------------
	//	Inno4 Primary - Vpin Clk(Long) pulse: 1us Lo - 10us Hi  - 1us Lo
	//												 ___________	
	//										Vpin ___|			|____
	//--------------------------------------------------------------------------


	t_high	= 10e-6;	
	t_low	= 4e-6; //2us Low before and after 2us High ==> Total of 4us between 10us pulses.
	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
	i +=50;
	start_vec= i; stop_vec= i + vec_hi + vec_lo;	

	n_pulse = 0;
	AF_Vpin_Clk_pulse_start_6pulses_ET = start_vec;
	for(n_pulse = 0; n_pulse <6; n_pulse++)
	{
		for (i= start_vec; i< stop_vec; i++)
		{	
			for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
			for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0001");i++;} 
			for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
			i--;
		}
		start_vec= i; stop_vec= i+ vec_hi + vec_lo;
	}
	AF_Vpin_Clk_pulse_stop_6pulses_ET = i-1;


	//-------------------------------------------------------------------
	//	Vpin 5 clocks for 132kHz 
	//-------------------------------------------------------------------
	//												 ___________	
	//										Vpin ___|			|____
	//--------------------------------------------------------------------------
	t_hi= 5.5*Mclk_in_Mhz; 
	t_lo= 2*Mclk_in_Mhz;	
	i +=50;
	start_vec= i; 
	AF_Vpin_Clk_pulse_start_132kHz= start_vec;
	pulses = 1;
	while(pulses<=5)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
			for(j=0;j<t_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0001");i++;} 
			for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
			i--;
		}
		pulses++;
	}
	AF_Vpin_Clk_pulse_stop_132kHz = i-1;

	//--------------------------------------------------------------------------
	//	Inno4 Primary - Vpin Data(Short) pulse: 1us Lo  - 1us Hi - 1us Lo
	//													________	
	//										Vpin    ___|		|__
	//--------------------------------------------------------------------------
	// This change is made because of primary trimming issue seen on TMT82 (worse yield loss on TMT57 with DDD128 671-5334-0629048S
	// Original code before changes for primary trimming issues.
	//	t_high	= 1e-6;	
	//	t_low	= 2e-6; //1us Low before and after 10us High
	// Hiep made changes to increase the primary narrow pulse. 6/16/17.
	t_high	= 1.00e-6;	 //This is important. 6/23/17
	t_low	= 6e-6; 
	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
	i +=50;
	start_vec= i; stop_vec= i + vec_hi + vec_lo;	

	AF_Vpin_Data_pulse_start= start_vec;
	for (i= start_vec; i< stop_vec; i++)
	{	
		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
		for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0001");i++;} 
		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
		i--;
	}
	AF_Vpin_Data_pulse_stop = i-1;

	/////////////////////////////////////////////////////////////////////////////////


	//--------------------------------------------------------------------------
	//	Inno4 Primary - Vpin Data(Short) pulse: 1us Lo  - 1us Hi - 1us Lo
	//													________	
	//										Vpin    ___|		|__
	//--------------------------------------------------------------------------
	// HL added for re-trimming.
	t_high	= 1.5e-6;	 //Use 0.5us instead of 1.0us for re-trimming.HL 06/26/17
	t_low	= 6e-6; 
	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
	i +=50;
	start_vec= i; stop_vec= i + vec_hi + vec_lo;	

	AF_Vpin_Data_pulse_start_retrim = start_vec;
	for (i= start_vec; i< stop_vec; i++)
	{	
		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
		for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX0001");i++;} 
		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX0000");i++;}
		i--;
	}
	AF_Vpin_Data_pulse_stop_retrim = i-1;

	/////////////////////////////////////////////////////////////////////////////////







	//--------------------------------------------------------------------------
	//	Inno3X Secondary - Vout Single pulse: 1us Lo - 10us Hi - 1us Lo
	//											   _____________	
	//									Vout   ___|				|__
	//--------------------------------------------------------------------------
	t_high	= 10e-6;	
	t_low	= 2e-6; //1us Low before and after 10us High
	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
	i +=50;
	start_vec= i; stop_vec= i + vec_hi + vec_lo;	

	AF_Vout_pulse_start= start_vec;
	for (i= start_vec; i< stop_vec; i++)
	{	
		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;}
		for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXX11XX");i++;} 
		for(j=0;j<vec_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXX01XX");i++;}
		i--;
	}
	AF_Vout_pulse_stop = i-1;

	//---------------------------------------------------------------------------------------------
	//	Inno3X Secondary - FB Single Positive Edge: 1us Lo - 20us Hi  (vLow = 1V, vHigh = 1.3V)
	//												   _______________________________________	
	//										  FB   ___|				
	//---------------------------------------------------------------------------------------------
	t_high	= 20e-6;	
	t_low	= 1e-6; 
	vec_hi	= ceil(t_high / Dclk_period); //Num of vectors require for t_hi depends on Dclk_period.
	vec_lo	= ceil(t_low  / Dclk_period); //Num of vectors require for t_lo depends on Dclk_period.
	i +=50;
	start_vec= i; stop_vec= i + vec_hi + vec_lo;	

	FB_positive_edge_start= start_vec;
	for (i= start_vec; i< stop_vec; i++)
	{	
		//INNO3X Pattern
		//for(j=0;j<vec_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX000");i++;}	//FB Low
		//for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX010");i++;}	//FB High with Vout compare

		//MINNO Pattern
		for(j=0;j<vec_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX111");i++;}	//FB High
		for(j=0;j<vec_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX101");i++;}	//FB Low with Vout compare
		i--;
	}
	FB_positive_edge_stop = i-1;

	//-------------------------------------------------------------------
	//	Vclamp_10pct on FB pin
	//-------------------------------------------------------------------
	t_hi= 20*Mclk_in_Mhz; t_lo= 2*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	VCLAMP_10PCT_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{	// Using DDD7_2. Leave un-used channels high to avoid negative edge!!!
		for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
		for(j=0;j<t_hi ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
		for(j=0;j<t_lo/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}

		i--;
	}
	VCLAMP_10PCT_stop = i-1;

	//-------------------------------------------------------------------
	//	ILIM_RAMP for 132kHz device on FB pin 
	//-------------------------------------------------------------------
	//	   -----					  ------------------		   -----------
	// t_hi_1/2 |   	t_lo_1	     |t_hi_1/2+t_hi_2/2 | t_lo_2  |
	//			 --------------------				     ---------	
	//   10us off -> 120 us on   ->    10us + 50us off  ->50 us on
	t_hi_1= 20*Mclk_in_Mhz; t_lo_1= 120*Mclk_in_Mhz;	//+++++++++++++++++++++++++
	t_hi_2= 100*Mclk_in_Mhz; t_lo_2= 60*Mclk_in_Mhz;	//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi_1+t_lo_1);	
	ILIM_RAMP_132kHz_start= start_vec;
	ILIM_UPMED_132kHz_SRCH_ADDR =int(((t_hi_1+t_lo_1)/Mclk_in_Mhz)*1e-6 / 20e-9);

	for (i= start_vec; i< stop_vec; i++)
	{	// Using DDD7_2. Leave un-used channels high to avoid negative edge!!!
		for(j=0;j<t_hi_1/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
		for(j=0;j<t_lo_1 ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
		for(j=0;j<t_hi_1/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}

		i--;
	}
	start_vec= i; stop_vec= i + 1*(t_hi_2+t_lo_2);	
	for (i= start_vec; i< stop_vec; i++)
	{	// Using DDD7_2. Leave un-used channels high to avoid negative edge!!!
		for(j=0;j<t_hi_2/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
		for(j=0;j<t_lo_2 ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
		for(j=0;j<t_hi_2/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}

		i--;
	}
	ILIM_RAMP_132kHz_stop = i-1;

	//-------------------------------------------------------------------
	//	ILIM_RAMP for 80kHz device on FB pin 
	//-------------------------------------------------------------------
	//	   -----					  ------------------		   -----------
	// t_hi_1/2 |   	t_lo_1	     |t_hi_1/2+t_hi_2/2 | t_lo_2  |
	//			 --------------------				     ---------	
	//   10us off -> 120 us on   ->    10us + 50us off  ->50 us on
	t_hi_1= 20*Mclk_in_Mhz; t_lo_1= 200*Mclk_in_Mhz;	//+++++++++++++++++++++++++
	t_hi_2= 180*Mclk_in_Mhz; t_lo_2= 100*Mclk_in_Mhz;	//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi_1+t_lo_1);	
	ILIM_RAMP_100kHz_start= start_vec;
	ILIM_UPMED_100kHz_SRCH_ADDR =int(((t_hi_1+t_lo_1)/Mclk_in_Mhz)*1e-6 / 20e-9);

	for (i= start_vec; i< stop_vec; i++)
	{	// Using DDD7_2. Leave un-used channels high to avoid negative edge!!!
		for(j=0;j<t_hi_1/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
		for(j=0;j<t_lo_1 ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
		for(j=0;j<t_hi_1/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}

		i--;
	}
	start_vec= i; stop_vec= i + 1*(t_hi_2+t_lo_2);	
	for (i= start_vec; i< stop_vec; i++)
	{	// Using DDD7_2. Leave un-used channels high to avoid negative edge!!!
		for(j=0;j<t_hi_2/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
		for(j=0;j<t_lo_2 ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;} 
		for(j=0;j<t_hi_2/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}

		i--;
	}
	ILIM_RAMP_100kHz_stop = i-1;

	//-------------------------------------------------------------------
	//	FW negative pulse (10us with 5us +/- DC)
	//-------------------------------------------------------------------
	t_hi= 35*Mclk_in_Mhz; t_lo= 5*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FW_Neg_pulse_10us_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}

		i--;
	}
	FW_Neg_pulse_10us_stop = i-1;

	//-------------------------------------------------------------------
	//	FW negative pulse - pulse train (5us Low Duty Cycle, 35us High Duty Cycle)
	//-------------------------------------------------------------------
	t_hi= 65*Mclk_in_Mhz; t_lo= 5*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	FW_pulse_train_start_70us= i;

	for (int pulse_cnt=0; pulse_cnt <5; pulse_cnt++)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}

			i--;
		}
	}
	FW_pulse_train_stop_70us = i-1;

	//-------------------------------------------------------------------
	//	FW negative pulse - 10 pulses (30us Low Duty Cycle, 30us High Duty Cycle)
	//-------------------------------------------------------------------
	t_hi= 30*Mclk_in_Mhz; t_lo= 30*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	FW_30us_pulse_start = i;

	for (int pulse_cnt=0; pulse_cnt <10; pulse_cnt++)
	{
		start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
			for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;} 
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX1XX");i++;}
			i--;
		}
	}
	ddd_7->ddd_load_pattern(i,"XXXXX0XX");i++;
	FW_30us_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	FW negative pulse (3us) with REQ high
	//-------------------------------------------------------------------
	t_hi= 2*Mclk_in_Mhz; t_lo= 3*Mclk_in_Mhz;//+++++++++++++++++++++++++
	i +=50;
	start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	FW_Neg_pulse_3us_Req_start= start_vec;

	for (i= start_vec; i< stop_vec; i++)
	{
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}
		for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXX01X");i++;} 
		for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXX11X");i++;}

		i--;
	}
	FW_Neg_pulse_3us_Req_stop = i-1;

	FB_MINNO_SSS_pulse_start=i;
	//20 pulses of 100KHz
	pulses = 1;
	while(pulses<=45)//REQ=1.7 V for 200us
	{
		start_vec= i; stop_vec= i + 1*(t_hi/2);	
		for (i= start_vec; i< stop_vec; i++)
		{
			for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;}
			i--;
		}
		pulses++;
	}
	//pulses = 1;
	//while(pulses<=100)//Toggle REQ 100 times at 100KHZ
	//{
	//start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	//for (i= start_vec; i< stop_vec; i++)
	//{
	//	//MINNO Pattern
	//	for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
	//	for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
	//	for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}

	//	i--;
	//}
	//pulses++;
	//}
	//pulses = 1;
	//while(pulses<=50)//Toggle REQ 100 times at 100KHZ
	//{
	//start_vec= i; stop_vec= i + 1*(t_hi+t_lo);	
	//for (i= start_vec; i< stop_vec; i++)
	//{
	//	//MINNO Pattern
	//	for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}
	//	for(j=0;j<t_lo ;j++)   {ddd_7->ddd_load_pattern(i,"XXXXXX1X");i++;} 
	//	for(j=0;j<t_hi/2;j++)  {ddd_7->ddd_load_pattern(i,"XXXXXX0X");i++;}

	//	i--;
	//}
	//pulses++;
	//}
	FB_MINNO_SSS_pulse_stop = i-1;

	//-------------------------------------------------------------------
	//	AF Clock Vout
	//-------------------------------------------------------------------
	start_vec	= i;
	End_vec		= start_vec;
	AF_ClkVout_start= start_vec;

		for(j=0;j<100 ;j++)   {ddd_7->ddd_load_pattern(End_vec,"XXXX01XX");End_vec++;}

		for (k=0; k< 51; k++)
		{
			for(j=0;j<10 ;j++)   {ddd_7->ddd_load_pattern(End_vec,"XXXX01XX");End_vec++;}

			if(k==0)
				First_Clk_Edge = End_vec+5;

			for(j=0;j<10 ;j++)   {ddd_7->ddd_load_pattern(End_vec,"XXXX11XX");End_vec++;} 
	
		}

		for(j=0;j<100 ;j++)   {ddd_7->ddd_load_pattern(End_vec,"XXXX01XX");End_vec++;}
	
	AF_ClkVout_stop = End_vec-1;


	//Last_address = FW_pulse_train_stop_70us;

	Last_address = End_vec;

	if(Last_address > 128000)
	{
		MessageBox(NULL,"Attention for TE!  Vectors excced DDD card 128K memory Size","DDD MEMORY Oversize ERROR", MB_OK);
	}

	//////-------------------------------------------------------------------
	//////	Vout(clock) LOW
	//////-------------------------------------------------------------------
	////i +=50;
	////VO_Low_Pulse_Start	= i;
	////VO_Low_Pulse_End	= i+1;
	////ddd_7->ddd_load_pattern(VO_Low_Pulse_Start,"XXXX0XXX");
	////ddd_7->ddd_load_pattern(VO_Low_Pulse_End,  "XXXX0XXX");


	//-------------------------------------------------------------------
	//	Vout(clock) pulse.  (Secondary clock through each anti-fuse link)
	//-------------------------------------------------------------------

	

}


/////////////////////////////////////////////////
void DDD_Load_Loop_Pulses(short channel, float period_us)
{
	if ((channel < 1) && (channel >8)) return;

	int  vecnum = 0;
	char vector[8];
	sprintf(vector, "XXXXXXXX");

	float ddd_addr_length;
	ddd_addr_length = (period_us / 2) / (Dclk_period * 1e6);   //Number of address required for half period (50% duty cycle)

	//vector[channel * (-1) + 8] = '0';
	//for(vecnum; vecnum < ddd_addr_length; vecnum++)
	//{
	//	ddd_7->ddd_load_pattern(vecnum, vector);
	//}

	//vector[channel * (-1) + 8] = '1';
	//for(vecnum; vecnum < (ddd_addr_length * 2) + 1; vecnum++)
	//{
	//	ddd_7->ddd_load_pattern(vecnum, vector);
	//}

	int i, j;

	for (i = 0; i < 3; i++)
	{
		vector[channel * (-1) + 8] = '1';
		for (j = 0; j < ddd_addr_length; j++)
		{
			ddd_7->ddd_load_pattern(vecnum++, vector);
		}
		vector[channel * (-1) + 8] = '0';
		for (j = 0; j < ddd_addr_length; j++)
		{
			ddd_7->ddd_load_pattern(vecnum++, vector);
		}
	}
	/*vector[channel * (-1) + 8] = '1';
	ddd_7->ddd_load_pattern(vecnum++, vector);*/


	gDDD_loop_pulses_stop = vecnum - 1;
}

void Run_Loop_Pulses()
{

	ddd_7->ddd_end_pattern(gDDD_loop_pulses_stop);
	wait.delay_10_us(1);
	ddd_7->ddd_run_pattern();
	wait.delay_10_us(50);

}

void Stop_Loop_Pulses()
{
	ddd_7->ddd_stop_pattern();
}

void DDD_Wait_Pattern_End(int start_address, int stop_address)
{
	float overhead = (40 uS);
	char ErrorMessage[100];

	if (stop_address >= (start_address + 2))
	{
		float clock_freq = ddd_7->ddd_get_clock_freq();
		if (clock_freq > 0)
		{
			//wait until end of pattern burst
			float pat_duration = (float)(stop_address - start_address + 1) / clock_freq + overhead;
			wait.delay_10_us((unsigned long)(pat_duration / (float)(10 uS) + 0.5));
		}
		else
		{
			sprintf(ErrorMessage, "Pattern period/frequency not initialized");
			printf("%s\n", ErrorMessage);
			MessageBox(NULL, ErrorMessage, "Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		}
	}
	else
	{
		sprintf(ErrorMessage, "Stop_address before Start_address");
		printf("%s\n", ErrorMessage);
		MessageBox(NULL, ErrorMessage, "Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}
}

/////////////////////////////////////////////////


void Powerup_to_read_Antifuse(float Vp, float Vs)
{	
	float vDrain_Read_Powerup=0, vDrain_Read_AF=0;
	vDrain_Read_Powerup = 15;

	//Primary Power-up to read AF
	{
		//Drain_P set to 0V
		D_dvi->set_voltage(D_ch, 0.0, 			VOLT_10_RANGE);	// DVI_11_0
		D_dvi->set_current(D_ch, 3.0e-3,		RANGE_3_MA);
		
		//Bpp set 5V for 100us
		VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 200e-3); //BPP ramp up from 0 to 5V with 200mV step
		wait.delay_10_us(10);
		//Vpin clock 3 pulses (10us positive) to enter write mode
		Force_Vpin_Pulses_nTimes(3);
		
		//Drain setup to be able to see AF links
		dvi_11->set_voltage(DVI_CHANNEL_0, vDrain_Read_Powerup, VOLT_50_RANGE);
		wait.delay_10_us(50);

		//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
		VBPP_ramp_up(5.0, 5.5, 50e-3);		
		VBPP_ramp_down(5.5, 5, 50e-3);	

		//Drain voltage lower to do AF reading
		dvi_11->set_voltage(DVI_CHANNEL_0, Vp, VOLT_50_RANGE);
	}

	//Secondary Power-up to read AF
	//Secondary_Write_Mode_PowerUp();

}

void Powerup_to_trim_primary()
{
	float j = 0;
	// Initialize DDD
	wait.delay_10_us(100); 
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	delay(1);
	VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
	Close_relay(K2);					// Primary:	Connect DVI11_0 to Drain pin
	Close_relay(K12);					// Primary:	Connect DDD7_1  to UV pin
	delay(3);			// 4 ms delay is necessary to wait for DDD to settle down before powering up BPP pin to avoid mis-clocking

	//Drain set to 0V
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 300.0e-3,		RANGE_300_MA);
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);	//Meas mode only work with autorange

	//Bpp set 5V for 100us
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 200e-3); //BPP ramp up from 0 to 5V with 200mV step

	//Moved down to keep Vpin = GND before increasing BPP voltage.
	wait.delay_10_us(50);
	////VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
	////Close_relay(K12);					// Primary:	Connect DDD7_1  to UV pin
	////delay(4);			// 4 ms delay is necessary to wait for DDD to settle down before powering up BPP pin to avoid mis-clocking

	//Enter write mode, Vpin clock 3 pulses (10us positive) 
	Force_Vpin_Pulses_nTimes(3);
	wait.delay_10_us(50);
	//Drain setup to be able to see AF links and ready for trimming
	j = 0;
	while(j<gTrim_Voltage)
	{
		D_dvi->set_voltage(D_ch, j, VOLT_50_RANGE);		//AF Trimming vDrain
		wait.delay_10_us(1);
		j++;

	}
	D_dvi->set_voltage(D_ch, gTrim_Voltage, VOLT_50_RANGE);		//AF Trimming vDrain
	wait.delay_10_us(200);

	//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	VBPP_ramp_up(5.0, 5.5, 50e-3);		
	VBPP_ramp_down(5.5, 5.0, 50e-3);
	wait.delay_10_us(100);
	
//	D_dvi->set_voltage(D_ch, gTrim_Voltage, VOLT_50_RANGE);		//AF Trimming vDrain
}


void Powerup_to_trim_primary_Retrim()
{
	float j = 0;
	float Drain_V = 40;

	DDD_Load_Patterns();

	// Initialize DDD
	wait.delay_10_us(100); 
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	delay(1);
	VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
	Close_relay(K2);					// Primary:	Connect DVI11_0 to Drain pin
	Close_relay(K12);					// Primary:	Connect DDD7_1  to UV pin
	delay(3);			// 4 ms delay is necessary to wait for DDD to settle down before powering up BPP pin to avoid mis-clocking

	//Drain set to 0V
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 300.0e-3,		RANGE_300_MA);
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_CURRENT);	//Meas mode only work with autorange

	//Bpp set 5V for 100us
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 200e-3); //BPP ramp up from 0 to 5V with 200mV step

	//Moved down to keep Vpin = GND before increasing BPP voltage.
	wait.delay_10_us(50);
	////VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
	////Close_relay(K12);					// Primary:	Connect DDD7_1  to UV pin
	////delay(4);			// 4 ms delay is necessary to wait for DDD to settle down before powering up BPP pin to avoid mis-clocking

	//Enter write mode, Vpin clock 3 pulses (10us positive) 
	Force_Vpin_Pulses_nTimes(3);
	wait.delay_10_us(50);
	//Drain setup to be able to see AF links and ready for trimming

	j = 0;
	//while(j<gTrim_Voltage)
	while(j<=Drain_V)
	{
		D_dvi->set_voltage(D_ch, j, VOLT_50_RANGE);		//AF Trimming vDrain
		wait.delay_10_us(5);
		j++;

	}
	D_dvi->set_voltage(D_ch, Drain_V, VOLT_50_RANGE);		//AF Trimming vDrain
	wait.delay_10_us(100);

	//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	VBPP_ramp_up(5.0, 5.5, 50e-3);		
	VBPP_ramp_down(5.5, 5.0, 50e-3);
	wait.delay_10_us(100);
	
	j=Drain_V;
	while(j>=5.5)
	{
		D_dvi->set_voltage(D_ch, j, VOLT_50_RANGE);		//AF Trimming vDrain
		wait.delay_10_us(5);
		j=j-1;
	}

	D_dvi->set_voltage(D_ch, 5.5, VOLT_50_RANGE);		//AF Trimming vDrain
	wait.delay_10_us(100);
}

void Powerdown_from_trim_primary()
{

	D_dvi->set_voltage(D_ch, 0.0, 		VOLT_10_RANGE);	// DVI_11_0
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	wait.delay_10_us(10); 
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);	// OVI_1_0 To avoid overshoot
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop); // Power down UV pin
	wait.delay_10_us(2);

	VPIN_ovi->connect(1);	// Connect OVI from UV
	Open_relay(K2);			// Primary:		Connect DVI11_0 to Drain pin
	Open_relay(K12);		// Primary:		Connect DDD7_1  to UV pin
	wait.delay_10_us(2);
//	delay(2);


}

void Power_Down_Primary()
{
	D_dvi->set_voltage(D_ch, 0.0, 		VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 30e-3, 		RANGE_30_MA);	// DVI_11_0
	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);	// OVI_1_0 
	VPIN_ovi->connect(1);	// Connect OVI from UV (Also reset to 0V/100uA)
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0, RANGE_10_V);
//	ovi_1->connect(OVI_CHANNEL_1);
}

void Power_Down_Secondary()
{
	ddd_7->ddd_stop_pattern();								// Stop the DDD loop pattern
	wait.delay_10_us(10); 
	ddd_7->ddd_set_lo_level(0.1);							// Will immediately change to this level upon execution
	wait.delay_10_us(100);                           // HL do not remove delay.  Else, it will corrupt the DDD pattern.
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10); 
	VO_dvi->set_current(VO_ch, 1.0e-3,	RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 0.0, 	VOLT_5_RANGE);	// DVI_9_0
	REQ_ovi->set_current(REQ_ch, 1.0e-3,	RANGE_30_MA);
	REQ_ovi->set_voltage(REQ_ch, 0.0, 	RANGE_2_V);	// OVI_1_2
	FWC_dvi2k->set_current(FWC_ch, 0.1,	RANGE_2_A);
	FWC_dvi2k->set_voltage(FWC_ch, 0.0,	VOLT_2_RANGE);	// DVI-13-0
	BPS_dvi->set_current(BPS_ch, 300.0e-3,	RANGE_300_MA);				//NEED TO BE 300mA to pull down to GND faster.
	BPS_dvi->set_voltage(BPS_ch, 0.0, 	VOLT_5_RANGE);	// DVI_9_1
	FW_dvi->set_current(FW_ch, 1.0e-3, RANGE_30_MA);	
	FW_dvi->set_voltage(FW_ch, 0.0, VOLT_5_RANGE);		// DVI11-1
	SR_dvi2k->open_relay(BUS_SENSE1);
	SR_dvi2k->open_relay(BUS_FORCE1);
	mux_14->open_relay(MUX_3_BUS3);
	wait.delay_10_us(5);
	SR_dvi2k->close_relay(CONN_FORCE1);
	SR_dvi2k->close_relay(CONN_SENSE1);
	//SR_dvi2k->set_current(SR_ch, 1.0e-3,	RANGE_2_A);
	SR_dvi2k->set_voltage(SR_ch, 0.0,	VOLT_2_RANGE);
	wait.delay_10_us(5);
}

void DDD_Clock_UV_Antifuse(int pulse_num)
{
	for(int i=0; i<pulse_num; i++)
	{
		ddd_7->ddd_run_pattern(AF_Vpin_Clk_pulse_start, AF_Vpin_Clk_pulse_stop);
		//wait.delay_1_us(int((AF_UV_pulse_stop- AF_UV_pulse_start+10)*Dclk_period*1e6)+5.51);	// Add 5us overhead
		//wait.delay_10_us(5);
		DDD_Wait_Pattern_End(AF_Vpin_Clk_pulse_start, AF_Vpin_Clk_pulse_stop);
	}
}

void Powerup_to_trim_secondary()
{
	// Initialize DDD
	wait.delay_10_us(100); 
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
	delay(1);
	
	//Setup to have FW connect to DVI-11-1
	Close_relay(K18);					// Primary:	Connect DVI11_1 to FW pin
	//Setup Vout to connect to DDD7_4 and have DDD7_4 toggle to stay LOW to start with
	VO_dvi->open_relay(CONN_FORCE0);
	VO_dvi->open_relay(CONN_SENSE0);
	wait.delay_10_us(10); 
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);
	Close_relay(K27);
	delay(3);

	//1. Set VBPS to VBPS_M-100mV (Allow bandgap to start up and avoid large charge current from Vout to heat up the device)
	BPS_dvi->set_current(BPS_ch, 30.0e-3,					RANGE_30_MA);	
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 100e-3, 	VOLT_10_RANGE);	// DVI_9_1
	VBPS_ramp_up(0, gVBPS_M_Init - 100e-3, 100e-3);	//BPS ramp up from 0 to VBPS-M minus 100mV with 100mV step.
	wait.delay_10_us(5);

	//2. Set FB to 5V
	REQ_ovi->set_voltage(REQ_ch, 5.0, 		VOLT_5_RANGE);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, 5e-3,		RANGE_30_MA);
	wait.delay_10_us(10);
	
	//3. Set Vout to 0V
	//VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	//VO_dvi->set_current(VO_ch, 5e-3,		RANGE_30_MA);
	
	//4. Set VFW to -1V
	FW_dvi->set_voltage(FW_ch, -1.0, 		VOLT_50_RANGE);	// DVI_11_1
	FW_dvi->set_current(FW_ch, 30.0e-3,		RANGE_30_MA);
	wait.delay_10_us(10);
	delay(1);	//Minimum wait time is 700us in order for AF reading to work properly
	
	//5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
	VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVshunt_Init_Se - 100e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
	wait.delay_10_us(10);
	
	//6. Bring FB down to 0V to aviod mis-trim
	REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
	wait.delay_10_us(10);




}

void Powerdown_from_trim_secondary()
{
	REQ_ovi->set_voltage(REQ_ch,   0.0, 		RANGE_2_V);	// OVI_1_0
	FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_10_RANGE);	// DVI_11_1
	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_10_RANGE);	// OVI_1_0 To avoid overshoot
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop); // Power down UV pin
	wait.delay_10_us(5);

	Open_relay(K18);			// Seconday:	Connect DVI11_1 to FW	pin
	Open_relay(K27);			// Seconday:	Connect DDD7_4  to Vout pin
	wait.delay_10_us(5);
	VO_dvi->close_relay(CONN_FORCE0);
	VO_dvi->close_relay(CONN_SENSE0);
	delay(2);

}

void DDD_Clock_FB_Antifuse(int pulse_num)
{

	for(int i=0; i<pulse_num; i++)
	{
		ddd_7->ddd_run_pattern(AF_FB_pulse_start,AF_FB_pulse_stop);	
	//	wait.delay_1_us(int((AF_FB_pulse_stop- AF_FB_pulse_start)*Dclk_period*1e6)+5.51);
		wait.delay_10_us(5);
	}
	// Wait until device settles down before reading anti-fuses current. 
	   wait.delay_10_us(30);	// It is necessary for good ATE to Bench Correlation
}

void DDD_Clock_Vout_Antifuse(int pulse_num)
{

	for(int i=0; i<pulse_num; i++)
	{
		ddd_7->ddd_run_pattern(AF_Vout_pulse_start,AF_Vout_pulse_stop);	
		wait.delay_10_us(5);
	}
	// Wait until device settles down before reading anti-fuses current. 
//	   wait.delay_10_us(10);	// It is necessary for good ATE to Bench Correlation (300us)
}

void Trim_Anti_fuse_primary(float *iAF)
{	
	wait.delay_10_us(50);
	//Note that vTrim should be already setup from Powerup_to_trim_primary() function
	//Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
	ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Assert   data pulse 
	wait.delay_10_us(g_trimTime_p);		
	*iAF = D_dvi->measure_average(5);
	ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start, AF_Vpin_Data_pulse_stop);	//Deassert data pulse 
	wait.delay_10_us(50);
}


void Trim_Anti_fuse_primary_Retrim(float *iAF)
{	
	
	float j = 0;

	while(j<=gTrim_Voltage)
	{
		D_dvi->set_voltage(D_ch, j, VOLT_50_RANGE);		//AF Trimming vDrain
		wait.delay_10_us(5);
		j++;

	}
	D_dvi->set_voltage(D_ch, gTrim_Voltage, VOLT_50_RANGE);		//AF Trimming vDrain
	wait.delay_10_us(100);
	//Note that vTrim should be already setup from Powerup_to_trim_primary() function
	//Vpin assert and deassert for the selected anti-fuse link with vDrain at Trim voltage
	ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start_retrim, AF_Vpin_Data_pulse_stop_retrim);	//Assert   data pulse 
	wait.delay_10_us(g_trimTime_p+100);		
	*iAF = D_dvi->measure_average(25);
	ddd_7->ddd_run_pattern(AF_Vpin_Data_pulse_start_retrim, AF_Vpin_Data_pulse_stop_retrim);	//Deassert data pulse 
	wait.delay_10_us(100);

	printf("Primary Retrim Function Called \n");
}







void Trim_Anti_fuse_secondary(float *iAF_trim, int tZAP)
{	
	wait.delay_10_us(30);
	//FW set to -1V 
	FW_dvi->set_voltage(FW_ch, -1.0, 		VOLT_50_RANGE);	// DVI_11_0
	wait.delay_10_us(5);
	//additional delay fro FW pin to reach gnd	(11/9/16 pm)
	int prg_delay=20;
	wait.delay_10_us(prg_delay);

	//FW set 50V
	FW_dvi->set_meas_mode(FW_ch,			DVI_MEASURE_CURRENT);
	FW_dvi->set_voltage(FW_ch,gTrim_Voltage,	VOLT_50_RANGE);	
	//FW_dvi->set_voltage(FW_ch,5.0,	VOLT_50_RANGE);	 //debug 
	FW_dvi->set_current(FW_ch, 300e-3,		RANGE_300_MA);		

	//FB set 5V for duration of trim time to trim anti-fuse
	//REQ_ovi->set_voltage(REQ_ch, 5.0, 		VOLT_5_RANGE);	// OVI_1_2
	REQ_ovi->set_voltage(REQ_ch, 4.0, 		VOLT_5_RANGE);	// OVI_1_2 (for Silicon RevB)
	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);
	delay(tZAP);	

	*iAF_trim = FW_dvi->measure_average(5);

	//if(gSiliconRev_S==revA_S)
	//	FW_dvi->set_voltage(FW_ch, -1.0, 		VOLT_50_RANGE);	// DVI_11_0

	REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
	wait.delay_10_us(30);	
}

void Read_Anti_fuse_secondary(int AF_addr, float *iAF_read, float Vread)
{
	float Iz_Quiescent = 0.0; 
	//VBPS_ramp_up(gVBPS_P_Init + 50e-3, gVBPS_P_Init + 200e-3, 50e-3);	//BPS ramp up from VBPS-P +50mV to +200mV with 50mV step.
	//wait.delay_10_us(5);

	FW_dvi->set_meas_mode(FW_ch, DVI_MEASURE_CURRENT);
	//FW_dvi->set_current(FW_ch, 300e-6,		RANGE_300_UA);
	Iz_Quiescent = gIzpt_NoZ_s;

	if(gSiliconRev_S==revA_S)
	{
		//Bring FB up to 5V for reading.
		REQ_ovi->set_voltage(REQ_ch, 5.0, 		VOLT_5_RANGE);	// OVI_1_2
		wait.delay_10_us(20);
	}

	*iAF_read = FW_dvi->measure_average(20);
	*iAF_read -= Iz_Quiescent;	
	FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_5_RANGE);	// DVI_11_1

	if(gSiliconRev_S==revA_S)
		REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2

	wait.delay_10_us(10);	
}


//void Read_Secondary_AF_Reg (int *AF_reg_array)
//{
//	int i, Result;
//	wait.delay_10_us(100); 
//	ddd_7->ddd_set_voltage_ref(2.5);
//	delay(1);
//	//Reading AF register must be followed by write or wrong data will be left in the register
//	//Vout and SR must be connected to DDD
//		
//	//Vout clock through every bit to observe SR register to determine if bit is trimmed or not.
//	for (i = 1; i<=52; i++)  //Secondary: First clock count at address 3 for 1.6 silicon, and address 8 for 1.5 silicon
//	{
//		if(i==1)	//just load anything with low pattern and compare.  First bit ZF not require Vout clocking
//		{
//			//First bit does not require Vout clocking, run pattern but sample before clock
//			DDD_Clock_Vout_Antifuse(1);		// Vout clk
//			Result = ddd_7->ddd_read_pattern(AF_Vout_pulse_start+2); //Read SR result before clock, during Vout high vectors
//		}
//		else
//		{
//			if(i!=2)DDD_Clock_Vout_Antifuse(1);		// Vout clk
//			Result = ddd_7->ddd_read_pattern(AF_Vout_pulse_start+20); //Read SR result during Vout high vectors
//		}
//		AF_reg_array[53-i] = 0;//Reset to 0
//		AF_reg_array[53-i] =  Result/16;		//SR pin connects to DDD7_5.  x0000 => bit5 divided by 16 to get 1/0.
//	}
//	wait.delay_10_us(100); 
//	ddd_7->ddd_set_voltage_ref(0.0);
//	delay(1);
//	if (DEBUG && gDEBUG) 
//	{
//		printf("Read_Secondary_AF_Reg\n");
//		printf("AF=");
//		for (i = 1; i<=52; i++)  //
//		{
//			printf("%1i",AF_reg_array[i]);
//			if ((i==10)||(i==20)||(i==30)||(i==40)||(i==50)) printf(" ",AF_reg_array[i]);
//		}
//		printf("\n");
//	}
//}


void Read_Secondary_AF_Reg (int *AF_reg_array)
{
	int i, Result;
	ddd_7->ddd_set_voltage_ref(2.5);
	wait.delay_10_us(10); 
	//Reading AF register must be followed by write or wrong data will be left in the register
	//Vout and SR must be connected to DDD
		
	//Vout clock through every bit
	//observe SR pin to determine if bit is trimmed or not.
	ddd_7->ddd_run_pattern(AF_ClkVout_start,AF_ClkVout_stop);
	DDD_Wait_Pattern_End(AF_ClkVout_start,AF_ClkVout_stop);
	for (i = 1; i <= 52; i++)
	{
		Result = ddd_7->ddd_read_pattern( (First_Clk_Edge-20)+(i-1)*20); //Read SR result during Vout high vectors
		AF_reg_array[53-i] = 0;//Reset to 0
		//AF_reg_array[53-i] =  Result/16;		//SR pin connects to DDD7_5.  x0000 => bit5 divided by 16 to get 1/0.
		AF_reg_array[53-i] = (Result & 16) >> 4;
	}
	ddd_7->ddd_set_voltage_ref(0.0);
	wait.delay_10_us(10); 
}


void Write_Secondary_AF_Reg (int *AF_reg_array)
{
	int i;
		
	//Vout clock through every bit, force FB voltage
	for (i = 52; i>=1; i--)  //Secondary: First clock count at address 3 for 1.6 silicon, and address 8 for 1.5 silicon
	{
		if (AF_reg_array[i] == 0)
			REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_5_V);	
		else
			REQ_ovi->set_voltage(REQ_ch, 4.4, 		RANGE_5_V);	
		wait.delay_10_us(10);
		DDD_Clock_Vout_Antifuse(1);		// Vout clk
	}
}

void AF_Zero_Out_CS_and_CB_bits(int *AF_reg_array) 
{
	AF_reg_array[26]=0;
	AF_reg_array[27]=0;
	AF_reg_array[28]=0;
	AF_reg_array[29]=0;
	AF_reg_array[30]=0;
	AF_reg_array[31]=0;
	AF_reg_array[32]=0;
	//AF_reg_array[46]=1;

}


void Force_Neg_Pulses_FW_DVI (float High_lev, float Low_lev)
{
	int i=0;
//	int pulse_num = 2;
//	From 1.6-9G silicon forward, FW pin will use 3 pulses to  trigger test mode. The first pulse is for ???,  
//	the 2nd and 3rd poulses are to provide the two negative edges to switch the secondary 
	int pulse_num = 3;

	FW_dvi->set_current(FW_ch,   299e-3,	RANGE_300_MA);	 
	FW_dvi->set_voltage(FW_ch,	High_lev, VOLT_10_RANGE);	
	wait.delay_10_us(10);
	for( i = 0; i< pulse_num; i++)
	{
		FW_dvi->set_voltage(FW_ch,	Low_lev, VOLT_10_RANGE);
		wait.delay_10_us(10);
		FW_dvi->set_voltage(FW_ch,	High_lev, VOLT_10_RANGE);	
		wait.delay_10_us(10);
	}
	

}

void Force_Neg_Pulses_FW_DDD (float High_lev, float Low_lev)
{
	int i=0;
//	int pulse_num = 3;	// If the pulse_num is changed, BPS:Reset-S search will be affected and won't work properly. 
//	From 1.6-9G silicon forward, FW pin will use 3 pulses to  trigger test mode. The first pulse 
//  is to get out of test mode in order to read anti-fuses, 
//	the 2nd and 3rd poulses are to provide the two negative edges to switch the secondary 
//  For normal mode  
//NOTE:   For most power up, the first pulse is applied during BPS power up in Power_Up_Secondary_Normal_Mode
//		  or Power_up_Secondary_Test_Mode functions. This function only applies the two pulses to turn on secondary
//		  to mimic two handshake pulses.


	int start_vec=0, stop_vec=0;	
	int dly=0;
	wait.delay_10_us(100); 
	ddd_7->ddd_set_lo_level(Low_lev);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(High_lev);		// Will immediately change to this level upon execution
	delay(1);

	start_vec = FW_Neg_1st_pulse_start;
	//stop_vec  = FW_Neg_2nd_pulse_stop-1;
	stop_vec  = FW_Neg_3rd_pulse_stop-1;

//	start_vec = FW_100kHz_3_pulses_start;
//	stop_vec  = FW_100kHz_3_pulses_stop;
//	stop_vec  = FW_100kHz_3_pulses_start + 58;

//	for( i = 0; i< pulse_num; i++)
//	{
		ddd_7->ddd_run_pattern(start_vec,stop_vec);
		wait.delay_10_us(10);	
//	}
		
}

void Force_FW_2NegPulses_n_1NegEdge_DDD (float High_lev, float Low_lev)
{
	/*
	After power up, if BPS voltage drops below VBPS:Reset, seondary will need 3 negative pulses on FW to take control.
	1st pulse is to set a latch and 2nd + 3rd pulses to do handshake.  If BPS only drop below VBPS_M and above VBPS_Reset,
	it only needs 2	negative pulses on FW to take control.
	*/

	int start_vec=0, stop_vec=0;	
	int dly=0;
	wait.delay_10_us(100); 
	ddd_7->ddd_set_lo_level(Low_lev);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(High_lev);		// Will immediately change to this level upon execution
	delay(1);

	start_vec = FW_Neg_2nd_pulse_start;
	stop_vec  = FW_Neg_Edge_stop-1;
	ddd_7->ddd_run_pattern(start_vec,stop_vec);
	wait.delay_10_us(15);	//Need to wait at least 3*35us for DDD to finish running the pattern
}

void Force_FB_100kHz_Pulses_nTimes (int pulse_num)
{
	int i=0;

	int start_vec=0, stop_vec=0;	
	int dly=0;

	start_vec = FB_100kHz_pulse_start;
	stop_vec  = FB_100kHz_pulse_stop-1;
	for( i = 0; i< pulse_num; i++)
	{
		ddd_7->ddd_run_pattern(start_vec,stop_vec);
		wait.delay_10_us(1);	
	}
}

void Force_Vpin_Pulses_nTimes (int pulse_num)
{
	int i=0;

	int start_vec=0, stop_vec=0;	
	int dly=0;

	wait.delay_10_us(50);

	start_vec = AF_Vpin_Clk_pulse_start;
	stop_vec  = AF_Vpin_Clk_pulse_stop;
	for( i = 0; i< pulse_num; i++)
	{
		ddd_7->ddd_run_pattern(start_vec,stop_vec);
		wait.delay_10_us(5);	
		//wait.delay_1_us(5);	
	}
}

void Force_Vpin_Pulses_5_Times (float High_lev, float Low_lev)
{
	int start_vec=0, stop_vec=0;	

	ddd_7->ddd_set_lo_level(Low_lev);		// Will immediately change to this level upon execution 
	wait.delay_10_us(10);
	ddd_7->ddd_set_hi_level(High_lev);		// Will immediately change to this level upon execution
	wait.delay_10_us(10);

	start_vec = AF_Vpin_Clk_pulse_start_132kHz;
	stop_vec  = AF_Vpin_Clk_pulse_stop_132kHz;
	ddd_7->ddd_run_pattern(start_vec,stop_vec);
	DDD_Wait_Pattern_End(start_vec,stop_vec);
}

void 	SyncHS_PowerUp_SkipWaitNListen(int PowerUpMode_P, int PowerUpMode_S)
{
	int		i = 0;
	float	vBPS_final =0.0;
	float	vHandshake = HANDSHAKE_Vd_TM;

	if(OPCODE == 4200 || OPCODE == 4501)
			vBPS_final = gVBPS_P_Init + 0.05;	// When increase this voltage, handshake signal will be stronger. It will allow device with communication problem to pass. 
	else	vBPS_final = gVBPS_P_Init + 0.05;	// DO NOT change this condition unless confirm with Design. Increased it to 200mV to account for the droop on VBPS during switch-on
												// cycle. The droop of the VBPS voltage causes communication pulse to be weak and causes communication problem at HOT (100C and above). 
	//wait.delay_10_us(100); 
	ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	//delay(1);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);



	//Primary power-up
	if( PowerUpMode_P == Normal_Mode_P )
			Power_Up_Primary_Normal_Mode(ILIM_NORM);
	else 
	if( PowerUpMode_P == gObserve_Mode_Xcontrol_sec ||
		PowerUpMode_P == gObserve_Mode_Xlisten		||
		PowerUpMode_P == gObserve_Mode_XVTurnOn		||
		PowerUpMode_P == gObserve_Mode_XRestart		||
		PowerUpMode_P == gObserve_Mode_rcv			||
		PowerUpMode_P == gObserve_Mode_Pause		||
		PowerUpMode_P == gObserve_Mode_DSDS			||
		PowerUpMode_P == gObserve_Mode_OT			||
		PowerUpMode_P == gObserve_Mode_LatchOff		||
		PowerUpMode_P == gObserve_Mode_Xoc			||
		PowerUpMode_P == gObserve_Mode_DZwindow		||
		PowerUpMode_P == gObserve_Mode_DZwindow2	||
		PowerUpMode_P == gObserve_Mode_XZfQ			||
		PowerUpMode_P == gObserve_Mode_Xtest2		||
		PowerUpMode_P == gObserve_Mode_iplus			)
		{
			//Close_relay(K2);				// Primary:		Connect DVI11_0 to Drain	pin
			////VPIN_ovi->disconnect(VPIN_ch);	// Vpin disconnect OVI then below close K16 to connect to 5kohm to DDD-7-1
			////wait.delay_10_us(100); 
			////ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
			////ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
			////delay(1);
			////ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
			////wait.delay_10_us(10);
			////Close_relay(K12);	// 5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
			////delay(5);
			Power_Up_Primary_Observe_Mode(PowerUpMode_P);
			////Open_relay(K12);	// 5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
			////wait.delay_10_us(20);
	};
	
	//Secondary Power-up 
	// - Normal		Mode  
	// - Write		Mode  (Not available in this function, yet)
	// - Program	Mode with Testmodes 1,2,3,4,5,6,TFB1,TFB2,11,12,13,14
	// - Simulation Mode with Testmodes 1,2,3,4,5,6,TFB1,TFB2,11,12,13,14
	if( PowerUpMode_S == gNM_SkipWaitNListen_S )
	{
		Power_Up_Secondary_Skip_WaitNListen(gNM_SkipWaitNListen_S, gVBPS_P_Init + 0.05);
	}
	else // ProgMode only without Vout clocking to testmode
	if(PowerUpMode_S == gProgRead_S)
	{
		Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);
		wait.delay_10_us(20);
		//Set Vout high
		ddd_7->ddd_run_pattern(High_pat_start,High_pat_stop);
		wait.delay_10_us(10);
		//Float FW for InvSync Circuit
		FW_dvi->set_current(FW_ch, 0.1e-9,		RANGE_30_MA);
		wait.delay_10_us(10);
		Connect_InvSyn_IM(Low_Load_Vd_Input);
		if(gSiliconRev_P>=3)
		{
			//BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);		//						B3 material
			VBPP_ramp_down(gVBPP_P_final, gVBPP_P_s_final, 10e-3);	// vstart, vstop, vstep	B3 material
			wait.delay_10_us(10);
		}
		//Drain set to 5V for switching
		dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
		wait.delay_10_us(20);
		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.0,        VOLT_20_RANGE);    // cx 11/10/16
		wait.delay_10_us(50); 
	}
	else // Program	Mode with Testmodes 1,2,3,4,5,6,TFB1,TFB2,11,12,13,14
	if( PowerUpMode_S == gProgReadTestMode1_Vout_S	||
		PowerUpMode_S == gProgReadTestMode1_FB_S	||
		PowerUpMode_S == gProgReadTestMode2_S		||
		PowerUpMode_S == gProgReadTestMode3_S		||
		PowerUpMode_S == gProgReadTestMode4_S		||
		PowerUpMode_S == gProgReadTestMode5_S		||
		PowerUpMode_S == gProgReadTestMode6_S		||
		PowerUpMode_S == gProgReadTestModeTFB1_S	||
		PowerUpMode_S == gProgReadTestModeTFB2_S	||
		PowerUpMode_S == gProgReadTestMode11_S		||
		PowerUpMode_S == gProgReadTestMode12_S		||
		PowerUpMode_S == gProgReadTestMode13_S		||
		PowerUpMode_S == gProgReadTestMode14_S		||
		PowerUpMode_S == gProgReadTestMode18_S		||
		PowerUpMode_S == gProgReadTestMode19_S		||
		PowerUpMode_S == gProgReadTestMode20_S		||
		PowerUpMode_S == gProgReadTestMode21_S			)
	{
		Powerup_Secondary_in_Testmode(gProgRead_SkipWaitNListen_S, 0, 0);
		Secondary_Vout_Clock_to_Testmode(PowerUpMode_S);
		//Close_relay(K27);
		//delay(5);
		//	//Clock Vout through Register addresses (2 to 34) depending on the Testmode request
		//	if(PowerUpMode_S == gProgReadTestMode1_S)		DDD_Clock_Vout_Antifuse(2);		
		//	if(PowerUpMode_S == gProgReadTestMode2_S)		DDD_Clock_Vout_Antifuse(4);		
		//	if(PowerUpMode_S == gProgReadTestMode3_S)		DDD_Clock_Vout_Antifuse(6);		
		//	if(PowerUpMode_S == gProgReadTestMode4_S)		DDD_Clock_Vout_Antifuse(8);		
		//	if(PowerUpMode_S == gProgReadTestMode5_S)		DDD_Clock_Vout_Antifuse(10);		
		//	if(PowerUpMode_S == gProgReadTestMode6_S)		DDD_Clock_Vout_Antifuse(12);		
		//	if(PowerUpMode_S == gProgReadTestModeTFB1_S)	DDD_Clock_Vout_Antifuse(14);		
		//	if(PowerUpMode_S == gProgReadTestModeTFB2_S)	DDD_Clock_Vout_Antifuse(16);		
		//	if(PowerUpMode_S == gProgReadTestMode11_S)		DDD_Clock_Vout_Antifuse(22);		
		//	if(PowerUpMode_S == gProgReadTestMode12_S)		DDD_Clock_Vout_Antifuse(24);		
		//	if(PowerUpMode_S == gProgReadTestMode13_S)		DDD_Clock_Vout_Antifuse(26);		
		//	if(PowerUpMode_S == gProgReadTestMode14_S)		DDD_Clock_Vout_Antifuse(28);
		//delay(1);
		//Open_relay(K27);
		//delay(1);
	}

	else // Simulation Mode with Testmodes 1,2,3,4,5,6,TFB1,TFB2,11,12,13,14
	if( PowerUpMode_S == gSimuModeTestMode1_S		||
		PowerUpMode_S == gSimuModeTestMode2_S		||
		PowerUpMode_S == gSimuModeTestMode3_S		||
		PowerUpMode_S == gSimuModeTestMode4_S		||
		PowerUpMode_S == gSimuModeTestMode5_S		||
		PowerUpMode_S == gSimuModeTestMode6_S		||
		PowerUpMode_S == gSimuModeTestModeTFB1_S	||
		PowerUpMode_S == gSimuModeTestModeTFB2_S	||
		PowerUpMode_S == gSimuModeTestMode11_S		||
		PowerUpMode_S == gSimuModeTestMode12_S		||
		PowerUpMode_S == gSimuModeTestMode13_S		||
		PowerUpMode_S == gSimuModeTestMode14_S			)
	{
		Powerup_Secondary_in_Testmode(gProgSim, 0, 0);
			//Clock Vout to program data from FB into trim registers
			for(i=1; i<=48; i++)
			{
				REQ_ovi->set_voltage(REQ_ch, 5.0*gSR_AF[i], 		VOLT_5_RANGE);	// OVI_1_2
				wait.delay_10_us(7);
				//Vout to clock to AF link
				VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
				wait.delay_10_us(7);	
				VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
				wait.delay_10_us(7);	
				REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
				wait.delay_10_us(7);
			}
			//Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
				FW_dvi->set_voltage(FW_ch, -0.3, 		VOLT_50_RANGE);	// DVI_11_1
				wait.delay_10_us(50);
				FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
				FW_dvi->set_current(FW_ch, 0,			RANGE_300_MA);
				wait.delay_10_us(50);

				Skip_Wait_and_Listen();

			//FB back to 1V for switching
				REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		VOLT_5_RANGE);	// OVI_1_2
				wait.delay_10_us(40);
				delay(1);
		
			//Clock Vout through Register addresses (2 to 34) depending on the Testmode request
				Secondary_Vout_Clock_to_Testmode(PowerUpMode_S);
				//if(PowerUpMode_S == gSimuModeTestMode1_S)		DDD_Clock_Vout_Antifuse(2);		
				//if(PowerUpMode_S == gSimuModeTestMode2_S)		DDD_Clock_Vout_Antifuse(4);		
				//if(PowerUpMode_S == gSimuModeTestMode3_S)		DDD_Clock_Vout_Antifuse(6);		
				//if(PowerUpMode_S == gSimuModeTestMode4_S)		DDD_Clock_Vout_Antifuse(8);		
				//if(PowerUpMode_S == gSimuModeTestMode5_S)		DDD_Clock_Vout_Antifuse(10);		
				//if(PowerUpMode_S == gSimuModeTestMode6_S)		DDD_Clock_Vout_Antifuse(12);		
				//if(PowerUpMode_S == gSimuModeTestModeTFB1_S)	DDD_Clock_Vout_Antifuse(14);		
				//if(PowerUpMode_S == gSimuModeTestModeTFB2_S)	DDD_Clock_Vout_Antifuse(16);		
				//if(PowerUpMode_S == gSimuModeTestMode11_S)		DDD_Clock_Vout_Antifuse(22);		
				//if(PowerUpMode_S == gSimuModeTestMode12_S)		DDD_Clock_Vout_Antifuse(24);		
				//if(PowerUpMode_S == gSimuModeTestMode13_S)		DDD_Clock_Vout_Antifuse(26);		
				//if(PowerUpMode_S == gSimuModeTestMode14_S)		DDD_Clock_Vout_Antifuse(28);		

	}
	// Secondary should now have control. //
	if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
	{
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
		wait.delay_10_us(10);
	}
}

#if(0)
void 	SyncHS_PowerUp(int PowerUpMode_P, int ILIM_PU_Select, int PowerUpMode_S)
{
	int		i = 0;
	float	vBPS_final =0.0;
	float	vHandshake = HANDSHAKE_Vd_TM;
	wait.delay_10_us(100); 
	ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);


	//Primary power-up
	if( PowerUpMode_P == Normal_Mode_P )
			Power_Up_Primary_Normal_Mode(ILIM_PU_Select);
	else 
	if( PowerUpMode_P == gObserve_Mode_Xcontrol_sec ||
		PowerUpMode_P == gObserve_Mode_Xlisten		||
		PowerUpMode_P == gObserve_Mode_XVTurnOn		||
		PowerUpMode_P == gObserve_Mode_XRestart		||
		PowerUpMode_P == gObserve_Mode_rcv			||
		PowerUpMode_P == gObserve_Mode_Pause		||
		PowerUpMode_P == gObserve_Mode_DSDS			||
		PowerUpMode_P == gObserve_Mode_OT			||
		PowerUpMode_P == gObserve_Mode_LatchOff		||
		PowerUpMode_P == gObserve_Mode_Xoc			||
		PowerUpMode_P == gObserve_Mode_DZwindow		||
		PowerUpMode_P == gObserve_Mode_XZfQ			||
		PowerUpMode_P == gObserve_Mode_Xtest2		||
		PowerUpMode_P == gObserve_Mode_iplus			)
		{
			//Close_relay(K2);				// Primary:		Connect DVI11_0 to Drain	pin
			VPIN_ovi->disconnect(VPIN_ch);	// Vpin disconnect OVI then below close K16 to connect to 5kohm to DDD-7-1
			Close_relay(K16);	// 5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
			delay(3);

			Power_Up_Primary_Observe_Mode(PowerUpMode_P);
			Open_relay(K16);	// 5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
		}
	else
	if( PowerUpMode_P == gTM5_BypassWL_p)
	{
		////////Setup Vpin for digital clocking
		//////	ovi_1->disconnect(OVI_CHANNEL_1);	
		//////	wait.delay_10_us(100); 
		//////	// Initialize DDD
		//////	ddd_7->ddd_set_lo_level(0.1);		
		//////	ddd_7->ddd_set_hi_level(4.0);		
		//////	delay(1);
		//////	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		//////	wait.delay_10_us(10);
		//////	Close_relay(K12);									// Connect DDD7_1	to Vpin(UV)	pin
		//Primary TM5 bypass Wait and Listen power up
		Power_Up_Primary_BypassWL_TM5(ILIM_PU_Select);
		////////Bring Vpin OVI back
		//////	ovi_1->connect(OVI_CHANNEL_1);	
		//////	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);  
		//////	VPIN_ovi->set_current(VPIN_ch, 1e-3,		RANGE_30_MA);  
		//////	Open_relay(K12);	//disconnect DDD7_1	from Vpin(UV)	pin
	}
	
	//Secondary Power-up 
	// - Normal		Mode  
	// - Write		Mode  (Not available in this function, yet)
	// - Program	Mode with Testmodes 1,2,3,4,5,6,TFB1,TFB2,11,12,13,14
	// - Simulation Mode with Testmodes 1,2,3,4,5,6,TFB1,TFB2,11,12,13,14
	if( PowerUpMode_S == gNM_SkipWaitNListen_S )
	{
		Power_Up_Secondary_Skip_WaitNListen(gNM_SkipWaitNListen_S, gVBPS_P_Init + 0.05);
	}
	
	else // Program	Mode with Testmodes 1,2,3,4,5,6,TFB1,TFB2,11,12,13,14
	if( PowerUpMode_S == gProgReadTestMode1_Vout_S	||
		PowerUpMode_S == gProgReadTestMode1_FB_S	||
		PowerUpMode_S == gProgReadTestMode2_S		||
		PowerUpMode_S == gProgReadTestMode3_S		||
		PowerUpMode_S == gProgReadTestMode4_S		||
		PowerUpMode_S == gProgReadTestMode5_S		||
		PowerUpMode_S == gProgReadTestMode6_S		||
		PowerUpMode_S == gProgReadTestModeTFB1_S	||
		PowerUpMode_S == gProgReadTestModeTFB2_S	||
		PowerUpMode_S == gProgReadTestMode11_S		||
		PowerUpMode_S == gProgReadTestMode12_S		||
		PowerUpMode_S == gProgReadTestMode13_S		||
		PowerUpMode_S == gProgReadTestMode14_S		||
		PowerUpMode_S == gProgReadTestMode18_S		||
		PowerUpMode_S == gProgReadTestMode19_S		||
		PowerUpMode_S == gProgReadTestMode20_S		||
		PowerUpMode_S == gProgReadTestMode21_S			)
	{
		Powerup_Secondary_in_Testmode(gProgRead_SkipWaitNListen_S, 0, 0);
		Secondary_Vout_Clock_to_Testmode(PowerUpMode_S);
		//Close_relay(K27);
		//delay(5);
		//	//Clock Vout through Register addresses (2 to 34) depending on the Testmode request
		//	if(PowerUpMode_S == gProgReadTestMode1_S)		DDD_Clock_Vout_Antifuse(2);		
		//	if(PowerUpMode_S == gProgReadTestMode2_S)		DDD_Clock_Vout_Antifuse(4);		
		//	if(PowerUpMode_S == gProgReadTestMode3_S)		DDD_Clock_Vout_Antifuse(6);		
		//	if(PowerUpMode_S == gProgReadTestMode4_S)		DDD_Clock_Vout_Antifuse(8);		
		//	if(PowerUpMode_S == gProgReadTestMode5_S)		DDD_Clock_Vout_Antifuse(10);		
		//	if(PowerUpMode_S == gProgReadTestMode6_S)		DDD_Clock_Vout_Antifuse(12);		
		//	if(PowerUpMode_S == gProgReadTestModeTFB1_S)	DDD_Clock_Vout_Antifuse(14);		
		//	if(PowerUpMode_S == gProgReadTestModeTFB2_S)	DDD_Clock_Vout_Antifuse(16);		
		//	if(PowerUpMode_S == gProgReadTestMode11_S)		DDD_Clock_Vout_Antifuse(22);		
		//	if(PowerUpMode_S == gProgReadTestMode12_S)		DDD_Clock_Vout_Antifuse(24);		
		//	if(PowerUpMode_S == gProgReadTestMode13_S)		DDD_Clock_Vout_Antifuse(26);		
		//	if(PowerUpMode_S == gProgReadTestMode14_S)		DDD_Clock_Vout_Antifuse(28);
		//delay(1);
		//Open_relay(K27);
		//delay(1);
	}

	else // Simulation Mode with Testmodes 1,2,3,4,5,6,TFB1,TFB2,11,12,13,14
	if( PowerUpMode_S == gSimuModeTestMode1_S		||
		PowerUpMode_S == gSimuModeTestMode2_S		||
		PowerUpMode_S == gSimuModeTestMode3_S		||
		PowerUpMode_S == gSimuModeTestMode4_S		||
		PowerUpMode_S == gSimuModeTestMode5_S		||
		PowerUpMode_S == gSimuModeTestMode6_S		||
		PowerUpMode_S == gSimuModeTestModeTFB1_S	||
		PowerUpMode_S == gSimuModeTestModeTFB2_S	||
		PowerUpMode_S == gSimuModeTestMode11_S		||
		PowerUpMode_S == gSimuModeTestMode12_S		||
		PowerUpMode_S == gSimuModeTestMode13_S		||
		PowerUpMode_S == gSimuModeTestMode14_S			)
	{
		Powerup_Secondary_in_Testmode(gProgSim, 0, 0);
			//Clock Vout to program data from FB into trim registers
			for(i=1; i<=48; i++)
			{
				REQ_ovi->set_voltage(REQ_ch, 5.0*gSR_AF[i], 		VOLT_5_RANGE);	// OVI_1_2
				wait.delay_10_us(7);
				//Vout to clock to AF link
				VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
				wait.delay_10_us(7);	
				VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
				wait.delay_10_us(7);	
				REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
				wait.delay_10_us(7);
			}
			//Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
				FW_dvi->set_voltage(FW_ch, -0.3, 		VOLT_50_RANGE);	// DVI_11_1
				wait.delay_10_us(50);
				FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
				FW_dvi->set_current(FW_ch, 0,			RANGE_300_MA);
				wait.delay_10_us(50);

				Skip_Wait_and_Listen();

			//FB back to 1V for switching
				REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		VOLT_5_RANGE);	// OVI_1_2
				wait.delay_10_us(40);
				delay(1);
		
			//Clock Vout through Register addresses (2 to 34) depending on the Testmode request
				Secondary_Vout_Clock_to_Testmode(PowerUpMode_S);
				//if(PowerUpMode_S == gSimuModeTestMode1_S)		DDD_Clock_Vout_Antifuse(2);		
				//if(PowerUpMode_S == gSimuModeTestMode2_S)		DDD_Clock_Vout_Antifuse(4);		
				//if(PowerUpMode_S == gSimuModeTestMode3_S)		DDD_Clock_Vout_Antifuse(6);		
				//if(PowerUpMode_S == gSimuModeTestMode4_S)		DDD_Clock_Vout_Antifuse(8);		
				//if(PowerUpMode_S == gSimuModeTestMode5_S)		DDD_Clock_Vout_Antifuse(10);		
				//if(PowerUpMode_S == gSimuModeTestMode6_S)		DDD_Clock_Vout_Antifuse(12);		
				//if(PowerUpMode_S == gSimuModeTestModeTFB1_S)	DDD_Clock_Vout_Antifuse(14);		
				//if(PowerUpMode_S == gSimuModeTestModeTFB2_S)	DDD_Clock_Vout_Antifuse(16);		
				//if(PowerUpMode_S == gSimuModeTestMode11_S)		DDD_Clock_Vout_Antifuse(22);		
				//if(PowerUpMode_S == gSimuModeTestMode12_S)		DDD_Clock_Vout_Antifuse(24);		
				//if(PowerUpMode_S == gSimuModeTestMode13_S)		DDD_Clock_Vout_Antifuse(26);		
				//if(PowerUpMode_S == gSimuModeTestMode14_S)		DDD_Clock_Vout_Antifuse(28);		

	}

}
#endif

void Secondary_Vout_Clock_to_Testmode(int Testmode_S)
{
		ddd_7->ddd_set_hi_level(4.0);				// Will immediately change to this level upon execution
		wait.delay_10_us(10); 
		ddd_7->ddd_set_lo_level(0.1);				// Will immediately change to this level upon execution
		wait.delay_10_us(10); 

		Close_relay(K27);
		dvi_9->open_relay(CONN_SENSE0);
		dvi_9->open_relay(CONN_FORCE0);
		delay(5);

			//Clock Vout through Register addresses (2 to 34) depending on the Testmode request
			if(Testmode_S == gProgReadTestMode1_Vout_S)		DDD_Clock_Vout_Antifuse(1);		
			if(Testmode_S == gProgReadTestMode1_FB_S)		DDD_Clock_Vout_Antifuse(2);		
			if(Testmode_S == gProgReadTestMode2_S)			DDD_Clock_Vout_Antifuse(4);		
			if(Testmode_S == gProgReadTestMode3_S)			DDD_Clock_Vout_Antifuse(6);		
			if(Testmode_S == gProgReadTestMode4_S)			DDD_Clock_Vout_Antifuse(8);		
			if(Testmode_S == gProgReadTestMode5_S)			DDD_Clock_Vout_Antifuse(10);		
			if(Testmode_S == gProgReadTestMode6_S)			DDD_Clock_Vout_Antifuse(12);		
			if(Testmode_S == gProgReadTestModeTFB1_S)		DDD_Clock_Vout_Antifuse(14);		
			if(Testmode_S == gProgReadTestModeTFB2_S)		DDD_Clock_Vout_Antifuse(16);		
			if(Testmode_S == gProgReadTestMode11_S)			DDD_Clock_Vout_Antifuse(22);		
			if(Testmode_S == gProgReadTestMode12_S)			DDD_Clock_Vout_Antifuse(24);		
			if(Testmode_S == gProgReadTestMode13_S)			DDD_Clock_Vout_Antifuse(26);		
			if(Testmode_S == gProgReadTestMode14_S)			DDD_Clock_Vout_Antifuse(28);
			if(Testmode_S == gProgReadTestMode18_S)			DDD_Clock_Vout_Antifuse(36);
			if(Testmode_S == gProgReadTestMode19_S)			DDD_Clock_Vout_Antifuse(38);
			if(Testmode_S == gProgReadTestMode20_S)			DDD_Clock_Vout_Antifuse(40);
			if(Testmode_S == gProgReadTestMode21_S)			DDD_Clock_Vout_Antifuse(42);
			if(Testmode_S == gProgReadTestMode22_S)			DDD_Clock_Vout_Antifuse(44);
		delay(1);
		// These will get close/open after done with the tests that needs VO clocking to get into TEST MODES
			dvi_9->close_relay(CONN_SENSE0);
			dvi_9->close_relay(CONN_FORCE0);
			//delay(5);
			Open_relay(K27);
			delay(3);
}

void SyncHS_PowerUp_Secondary_in_Normal_Mode_Primary_TM5(int Vd_Input_Mode)
{
	//float vBPS_final =0.0;
	float vHandshake = HANDSHAKE_Vd_TM;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

// **** Synchronous Handshake PowerUp (Secondary in Normal Mode) ******
	//Vpin (0V)
	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
		//HL needs to change to 20mA or Turret CB won't work.
		//SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
		//SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		//delay(2);
		//mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.

	Close_relay(K5);//Connect SR to 5nF
	delay(5);
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	delay(3);
	//mux_14->close_relay(MUX_BANK_3_4);
	//mux_14->close_relay(MUX_4_GND);
	//Close_relay(K21);		// FW		to	DDD
//	Open_relay(K18);		// Make sure DVI_11_1 disconnect from FW
	delay(6);
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//This could cause a 1V glitch at BPS for 50us
	wait.delay_10_us(10);

	//Vout (0V)
	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
//	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0  "Stop device from switching"
	//FB (2V)  pull FB above CVth to force No Switching
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	REQ_ovi->set_voltage(REQ_ch, 0.9,	RANGE_2_V);	// OVI_1_2	

	//IS (0V)
	if(g_TurretCB)
	{
		//tmu_6->close_relay(TMU_EXT_DRV3); //Floating SR pin
		
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 200.0e-3,	RANGE_2_A);

	}
	else
	{
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	}
	wait.delay_10_us(10);
	//BPS (vPlus - 300mV)
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
	VBPS_Power_Up(gVBPS_P_Init-0.3);			// vfinal

	//Drain (0V/3mA)
	D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
	D_dvi->set_voltage(D_ch, 0, 		VOLT_50_RANGE);	// DVI_11_0	
	//D_dvi->set_voltage(D_ch, 45.0, 		VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(20);

	if (gIOV)
	{
		VPIN_ovi->set_voltage(VPIN_ch, 6.0,			RANGE_10_V);  
		VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	
	}
	else
	{
		VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_10_V);  
		VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);
	}

	//BPP set 0V
	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	//VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//wait.delay_10_us(5);
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2);	// vstart, vstop, vstep	
	// Initialize DDD
	wait.delay_10_us(100); 
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(50);

	VPIN_ovi->disconnect(1);				// Disconnect OVI from UV
	// Close K12 to connect DDD to VPIN
	Close_relay(K12);
	delay(4);
	Force_Vpin_Pulses_5_Times(5.0, 0.0);	
	wait.delay_10_us(10);
	D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 45.0, 			VOLT_50_RANGE);	// DVI_11_0

	//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	VBPP_ramp_up(5.0, gVBPP_PV_Init, 50e-3);		
	//Drain stays at 0V so BPP signal will be cleaner
	dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
	wait.delay_10_us(10);
	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
	wait.delay_10_us(5);
	//////Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
	////if     (ILIM_Select == ILIM_NORM)				wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
	////else if(ILIM_Select == ILIM_INCR)				wait.delay_10_us(150);	//10  uF	(ILIM+1)	1.2ms

	//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
	ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-200e-3, RANGE_10_V);
	wait.delay_10_us(50);
	if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
	{
		BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed 2mA to 3mA
		VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
		wait.delay_10_us(10);
	}
	else
	{
		ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+50e-3, RANGE_10_V);
		wait.delay_10_us(30);
	}

	//Drain set to 5V for switching
	dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_50_RANGE);
	wait.delay_10_us(10);
	Connect_InvSyn_IM(Vd_Input_Mode);

	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	wait.delay_10_us(10);

	//FB (1.7V) force Switching
	REQ_ovi->set_voltage(REQ_ch, 1.7,		RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(10);
	// Open K12 
	Open_relay(K12);
	VPIN_ovi->connect(1);				// Reconnect OVI from UV
	wait.delay_10_us(100); 
	ddd_7->ddd_set_hi_level(0.0);		// Will immediately change to this level upon execution
	wait.delay_10_us(10);
	delay(1);

}

void 	SyncHS_PowerUp_Secondary_in_Normal_Mode_SKIP_WAITnLISTEN(int Vd_Input_Mode)
{
	//float vBPS_final =0.0;
	float vHandshake = HANDSHAKE_Vd_TM;

//	if(OPCODE == 4200 || OPCODE == 4250)
////			vBPS_final = gVBPS_P_Init + 0.05;	// Keep the VBPS voltage low at room temp to screen out weak communication parts.  	 
//			vBPS_final = gVBPS_P_Init + 0.15;	// Communication pass for 8" EPSON
//	else	vBPS_final = gVBPS_P_Init + 0.10;	// DO NOT change this condition unless confirm with Design. Increased it to 200mV to account for the droop on VBPS during switch-on
//												// cycle. The droop of the VBPS voltage causes communication pulse to be weak and causes communication problem at HOT (100C and above). 

// **** Synchronous Handshake PowerUp (Secondary in Normal Mode) ******
	//Close_relay(K3);	//Connect Drain to DVI
	//Vpin (0V)
	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
	//if(g_TurretCB)
	//{
	//	//HL needs to change to 20mA or Turret CB won't work.
	//	SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
	//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	//	delay(2);
	//	mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
	//	delay(2);

	//}
	//else
	//{
	//	SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
	//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	//	dvi_13->close_relay(BUS_SENSE1);
	//	dvi_13->close_relay(BUS_FORCE1);
	//	mux_14->close_relay(MUX_3_BUS3);
	//}
	//
	//mux_14->close_relay(MUX_BANK_3_4);
	//mux_14->close_relay(MUX_4_GND);
	//FW to DDD

	Close_relay(K5);//Connect SR to 5nF
	delay(5);
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K21);		// FW		to	DDD
//	Open_relay(K18);		// Make sure DVI_11_1 disconnect from FW
	delay(4);
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//This could cause a 1V glitch at BPS for 50us
	wait.delay_10_us(10);

	//Vout (0V)
	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
//	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
//	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0  "Stop device from switching"
	delay(1);
	//FB (CVth+10%)  pull FB above CVth to force No Switching
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	if(LB_Rev >= 5)		REQ_ovi->set_voltage(REQ_ch, 0.9,		RANGE_2_V);	// OVI_1_2	
	else				REQ_ovi->set_voltage(REQ_ch, 0.9,		RANGE_2_V);	// OVI_1_2	

	//IS (0V)
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	wait.delay_10_us(10);
	//BPS (vPlus - 300mV)
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
	VBPS_Power_Up(gVBPS_P_Init-0.3);			// vfinal

	//Power up Primary
	Power_Up_Primary_Normal_Mode(ILIM_NORM);

	//BPS=gVBPS_final
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	wait.delay_10_us(10);
	wait.delay_10_us(10);


	////LT1016 LT/GND pin setup to be below GND so Comparator output can go below GND
	//ovi_1->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA);
	//ovi_1->set_voltage(OVI_CHANNEL_6, -1.5, VOLT_5_RANGE);	//revB inv_syn_circuit
	//InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3,			RANGE_30_MA);	//Temporary
	//if(Vd_Input_Mode == High_Vd_Input)
	//	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.0,		VOLT_20_RANGE);	// OVI_1_4	"Size x8 Vref max = 5V/2 (2.5V), so 3/2 = 1.5V (good margin)"
	//if(Vd_Input_Mode == Low_Vd_Input)
	//	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.5,		VOLT_20_RANGE);	// OVI_1_4	
	//delay(1);



	// Secondary send 2 negative FW pulses to cause Primary to see request so Primary will be switching
	Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
	wait.delay_10_us(10);  //more than 30us quiet time on FW signal

	//D=0V
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0		
	wait.delay_10_us(5);


	//Close_relay(K8);	//Connect InvSyn_IM_IN  to Drain
	//Close_relay(K19);	//Connect InvSyn_IM_OUT to FW pin
	//delay(4);

	//Connect InvSyn feedback buffer
	Connect_InvSyn_IM(Vd_Input_Mode);		
	//FW on OVI
	Open_relay(K21);		// FW		to	DDD
	wait.delay_10_us(10);
//	wait.delay_10_us(20);
	//D=5V
	D_dvi->set_voltage(D_ch, 5.0, 			VOLT_50_RANGE);	// DVI_11_0		
	wait.delay_10_us(140);
//	delay(1);

	//FB (1V) force Switching
	REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(10);
}

void 	SyncHS_PowerUp_Secondary_NM_Primary_TM5_ByPassWL(int ILIM_mode, int vinREF_InvSync)
{
	//Setup Vpin for digital clocking
		//////ovi_1->disconnect(OVI_CHANNEL_1);	
		//////wait.delay_10_us(100); 
		//////// Initialize DDD
		//////ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
		//////ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
		//////delay(1);
		//////ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
		//////wait.delay_10_us(10);
		//////Close_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin

	//Setup to have Secondary power up to VBPS minus
		//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
		//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
		SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		dvi_13->close_relay(BUS_SENSE1);
		dvi_13->close_relay(BUS_FORCE1);
		mux_14->close_relay(MUX_3_BUS3);
		wait.delay_10_us(20);
		//Vout (Will charge BPS if @5V)
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		VO_dvi->set_voltage(VO_ch, 3.5, 		VOLT_5_RANGE);	// DVI_9_0
		//FB (1V)
		REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
		REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		wait.delay_10_us(10);
		//BPS (vPlus - 200mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	
		VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal  

	//Have InvSync circuit ready for communication
	Connect_InvSyn_IM(vinREF_InvSync);


	//Primary TM5 bypass Wait and Listen power up
	Power_Up_Primary_BypassWL_TM5(ILIM_mode);

	////////Bring Vpin OVI back
	//////	ovi_1->connect(OVI_CHANNEL_1);	
	//////	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);  
	//////	VPIN_ovi->set_current(VPIN_ch, 1e-3,		RANGE_30_MA);  
	//////	Open_relay(K12);	//disconnect DDD7_1	from Vpin(UV)	pin


	//Secondary power up to vBPS final
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	wait.delay_10_us(10);

}

void 	SyncHS_PowerUp_Secondary_in_Test_Mode_SKIP_WAITnLISTEN(int Vd_Input_Mode, int ILIM_Mode)
{
	//float vBPS_final =0.0;
	float vHandshake = HANDSHAKE_Vd_TM;

//	if(OPCODE == 4200 || OPCODE == 4250)
////			vBPS_final = gVBPS_P_Init + 0.05;	// Keep the VBPS voltage low at room temp to screen out weak communication parts.  	 
//			vBPS_final = gVBPS_P_Init + 0.10;	// EPSON 8" wafer require higher to pass communication
//	else	vBPS_final = gVBPS_P_Init + 0.10;	
												
// **** Synchronous Handshake PowerUp (Secondary in Normal Mode) ******

	//Vpin (0V)
	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	if(gIOV == true)
		VPIN_ovi->set_voltage(VPIN_ch, 6.0,			RANGE_10_V);
	else
		VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
	SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	dvi_13->close_relay(BUS_SENSE1);
	dvi_13->close_relay(BUS_FORCE1);
	mux_14->close_relay(MUX_3_BUS3);
	//mux_14->close_relay(MUX_BANK_3_4);
	//mux_14->close_relay(MUX_4_GND);
	Close_relay(K21);		// FW		to	DDD
	Open_relay(K18);		// Make sure DVI_11_1 disconnect from FW
	delay(3);
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//This could cause a 1V glitch at BPS for 50us
	wait.delay_10_us(10); 
	//Vout (0V)
	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
//	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0  "Stop device from switching"
	//FB (2V)  pull FB above CVth to force No Switching
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
//	REQ_ovi->set_voltage(REQ_ch, 2.0,		RANGE_2_V);					// OVI_1_2	
	REQ_ovi->set_voltage(REQ_ch, gREQ_2V,		RANGE_2_V);	// OVI_1_2	(Take care of OVLO bit)
	//IS (0V)
//	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_voltage(FWC_ch, 20e-3,		VOLT_2_RANGE);	// DVI_21_0 (20mV) above ground so it's not short to GND (take care of SCEN bit)
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	wait.delay_10_us(10);
	//BPS (vPlus - 300mV)
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
	VBPS_Power_Up(gVBPS_P_Init-0.3);			// vfinal

	//Power_Up_Primary_Normal_Mode();
	VBPP_Power_Up_w_Test_Mode(gTM2_p, ILIM_Mode);	// TM2 requires the normal wait and listen 85ms
	//wait.delay_10_us(gDly_Wait_and_Listen_Test_Mode);	// Require for wait and listen first then device will switch

	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	wait.delay_10_us(10);

	// Secondary send 2 negative FW pulses to cause Primary to see request so Primary will be switching
	// Expect to see Drain respond within 4us after 3rd FW neg pulse.  The Drain response pulse should be ~7us ontime
	Force_Neg_Pulses_FW_DDD(5, -0.5);	
//	wait.delay_10_us(5);  //more than 30us quiet time on FW signal

	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0		
	wait.delay_10_us(5);

	Connect_InvSyn_IM(Vd_Input_Mode);		
	Open_relay(K21);		// FW		to	DDD
	wait.delay_10_us(10);
	D_dvi->set_voltage(D_ch, 5.0, 			VOLT_50_RANGE);	// DVI_11_0		
	wait.delay_10_us(140);
//	delay(1);

	//FB (1V) force Switching
	REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(10);
}

void SyncHS_PowerUp_Secondary_in_Normal_Mode(int Vd_Input_Mode)
{	
	float vBPS_final =0.0;
	float vHandshake = HANDSHAKE_Vd_TM;

	if(OPCODE == 4200 || OPCODE == 4501)
//			vBPS_final = gVBPS_P_Init + 0.05;	// Keep the VBPS voltage low at room temp to screen out weak communication parts.  	 
			vBPS_final = gVBPS_P_Init + 0.05;	// When increase this voltage, handshake signal will be stronger. It will allow device with communication problem to pass. 
	else	vBPS_final = gVBPS_P_Init + 0.05;	// DO NOT change this condition unless confirm with Design. Increased it to 200mV to account for the droop on VBPS during switch-on
												// cycle. The droop of the VBPS voltage causes communication pulse to be weak and causes communication problem at HOT (100C and above). 

// **** Synchronous Handshake PowerUp (Secondary in Normal Mode) ******

	//Vpin (0V)
	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
	SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	dvi_13->close_relay(BUS_SENSE1);
	dvi_13->close_relay(BUS_FORCE1);
	mux_14->close_relay(MUX_3_BUS3);
	//mux_14->close_relay(MUX_BANK_3_4);
	//mux_14->close_relay(MUX_4_GND);

	//Vout (0V)
	VO_dvi->set_current(VO_ch, 30.0e-3,		RANGE_30_MA);	
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  (If Vout bring high, this will bring vBPS high)
//	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0  (If Vout bring high, this will bring vBPS high)
	//FB (1V)
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	//IS (0V)
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	wait.delay_10_us(50);
	//BPS (vPlus - 300mV)
	VBPS_Power_Up(gVBPS_P_Init-0.3);			// vfinal

	Connect_InvSyn_IM(Vd_Input_Mode);		
//	Connect_InvSyn_IM(Low_Vd_Input);												

	Power_Up_Primary_Normal_Mode(ILIM_NORM);

	//As soon as VBPS_Plus hit, Handshake kick in.
	//Observed from scope showing that when HS kick in, 1st big +pulse is about 32us and the 2nd big +pulse is about 25us.
	//
	BPS_dvi->set_voltage(BPS_ch, vBPS_final, 	VOLT_10_RANGE);	// DVI_9_1

	delay(1);	// Wait for VBSP to settle, and communication to be established properly. Higher VBPS, stronger communication 
}

void SyncHS_PowerUp_Secondary_in_Test_Mode(int TestModeSelect=0, int ILIM_Mode=0)
{	
	//float vBPS_final =0.0;
	float vHandshake = HANDSHAKE_Vd_TM;
	int   InvSyn_IM_Vd_Input_Mode = 99;
	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	if(TestModeSelect == gTM_ILIM)
		InvSyn_IM_Vd_Input_Mode = High_Vd_Input;
	else
//		InvSyn_IM_Vd_Input_Mode = Low_Vd_Input;
		InvSyn_IM_Vd_Input_Mode = Low_Load_Vd_Input;

	Connect_InvSyn_IM(InvSyn_IM_Vd_Input_Mode);
	//Vpin (0V)
	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)

	if(g_TurretCB)
	{
		//HL needs to change to 20mA or Turret CB won't work.
		SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		delay(2);
		mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
		delay(2);
	}
	else
	{
		SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		dvi_13->close_relay(BUS_SENSE1);
		dvi_13->close_relay(BUS_FORCE1);
		mux_14->close_relay(MUX_3_BUS3);
		wait.delay_10_us(20);
		delay(3);
	}
	


	if(TestModeSelect==gTM5_BypassWL_p)
		Power_Up_Primary_BypassWL_TM5(ILIM_Mode);
	else
		VBPP_Power_Up_w_Test_Mode(TestModeSelect, ILIM_Mode);	//


	
	//mux_14->close_relay(MUX_BANK_3_4);
	//mux_14->close_relay(MUX_4_GND);

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

	//Make sure vBPS less than 5.0V
	if(gVBPS_M_Init < 5.0)
		VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal  
	else
		VBPS_Power_Up(4.5);			

//////////	if(TestModeSelect == gTM_ILIM)
//////////		InvSyn_IM_Vd_Input_Mode = High_Vd_Input;
//////////	else
////////////		InvSyn_IM_Vd_Input_Mode = Low_Vd_Input;
//////////		InvSyn_IM_Vd_Input_Mode = Low_Load_Vd_Input;
////////////
//////////	Open_relay(K18);
//////////	Open_relay(K21);
//////////	delay(1);
//////////	//Connect_InvSyn_IM(InvSyn_IM_Vd_Input_Mode);
//////////	//delay(2);
//////////	if(TestModeSelect==gTM5_BypassWL_p)
//////////		Power_Up_Primary_BypassWL_TM5(ILIM_Mode);
//////////	else
//////////		VBPP_Power_Up_w_Test_Mode(TestModeSelect, ILIM_Mode);	//
//

	//Make sure vBPS less than 5.0V
	//if(gVBPS_P_Init < 5.0)
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// DVI_9_1  
	wait.delay_10_us(3);
	
	if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
	{
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
		wait.delay_10_us(10);
	}
	//Connect_InvSyn_IM(InvSyn_IM_Vd_Input_Mode);

}

void SyncHS_PowerUp_Secondary_in_Test_Mode_MINNO(int TestModeSelect=0, int ILIM_Mode=0)
{	
	//float vBPS_final =0.0;
	float vHandshake = HANDSHAKE_Vd_TM;
	int   InvSyn_IM_Vd_Input_Mode = 99;
	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	if(TestModeSelect == gTM_ILIM)
		InvSyn_IM_Vd_Input_Mode = High_Vd_Input;
	else
//		InvSyn_IM_Vd_Input_Mode = Low_Vd_Input;
		InvSyn_IM_Vd_Input_Mode = Low_Load_Vd_Input;

	Connect_InvSyn_IM_New(InvSyn_IM_Vd_Input_Mode);
	//Vpin (0V)
	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)

	if(g_TurretCB)
	{
		//HL needs to change to 20mA or Turret CB won't work.
		SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		delay(2);
		mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
		delay(2);
	}
	else
	{
		SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		dvi_13->close_relay(BUS_SENSE1);
		dvi_13->close_relay(BUS_FORCE1);
		mux_14->close_relay(MUX_3_BUS3);
		wait.delay_10_us(20);
		delay(3);
	}
	
	//SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_20_UA);	
	//SR_dvi2k->set_voltage(SR_ch, 0.0,	RANGE_5_V);	// DVI_21_1
	//SR_dvi2k->open_relay(BUS_SENSE1);
	//SR_dvi2k->open_relay(BUS_FORCE1);
	//SR_dvi2k->open_relay(CONN_FORCE1);
	//SR_dvi2k->open_relay(CONN_SENSE1);
	//SR_dvi2k->open_relay(CONN_MEAS1);
	//mux_14->open_relay(MUX_3_BUS3);

	if(TestModeSelect==gTM5_BypassWL_p)
		Power_Up_Primary_BypassWL_TM5(ILIM_Mode);
	else
		VBPP_Power_Up_w_Test_Mode(TestModeSelect, ILIM_Mode);	//


	
	//mux_14->close_relay(MUX_BANK_3_4);
	//mux_14->close_relay(MUX_4_GND);

	//Vout (Will charge BPS if @5V)
	VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
	//VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_5_RANGE);	// DVI_9_0
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
	//FB (1V)
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	//REQ_ovi->set_voltage(REQ_ch, 0.8,		RANGE_2_V);	// OVI_1_2		//Try for low CVinit devices
	//REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	REQ_ovi->set_voltage(REQ_ch, 2.0,		RANGE_2_V);	// OVI_1_2	
	//IS (0V)
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	wait.delay_10_us(10);
	//BPS (vPlus - 200mV)
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	

	//Make sure vBPS less than 5.0V
	if(gVBPS_M_Init < 5.0)
		VBPS_Power_Up(gVBPS_M_Init-0.2);			// vfinal  
	else
		VBPS_Power_Up(4.5);			

//////////	if(TestModeSelect == gTM_ILIM)
//////////		InvSyn_IM_Vd_Input_Mode = High_Vd_Input;
//////////	else
////////////		InvSyn_IM_Vd_Input_Mode = Low_Vd_Input;
//////////		InvSyn_IM_Vd_Input_Mode = Low_Load_Vd_Input;
////////////
//////////	Open_relay(K18);
//////////	Open_relay(K21);
//////////	delay(1);
//////////	//Connect_InvSyn_IM(InvSyn_IM_Vd_Input_Mode);
//////////	//delay(2);
//////////	if(TestModeSelect==gTM5_BypassWL_p)
//////////		Power_Up_Primary_BypassWL_TM5(ILIM_Mode);
//////////	else
//////////		VBPP_Power_Up_w_Test_Mode(TestModeSelect, ILIM_Mode);	//
//

	//Make sure vBPS less than 5.0V
	//if(gVBPS_P_Init < 5.0)
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// DVI_9_1  
	BPS_dvi->set_voltage(BPS_ch, 5.0, 	VOLT_10_RANGE);	// DVI_9_1  
	wait.delay_10_us(3);
	//VBPP_Power_Up_w_Test_Mode(TestModeSelect, ILIM_Mode);
	if(gSiliconRev_P>=3)	//Lower BPP plus threshold correctly for Primary B3 silicon and later materials
	{
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
		wait.delay_10_us(10);
	}
	//Connect_InvSyn_IM(InvSyn_IM_Vd_Input_Mode);

}

void SyncHS_PowerUp_Secondary_in_ProgMode(int PowerUpMode_S=0, int PowerUpMode_P=0)
{	
	float vBPS_final =0.0;
	float vHandshake = HANDSHAKE_Vd_TM;
	int   InvSyn_IM_Vd_Input_Mode = 99;
	int	  i=0;

	Close_relay(K18);	//FW to dvi-11-1

	////Vpin (0V)
	//VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	//VPIN_ovi->set_voltage(VPIN_ch, 0.0,			VOLT_10_RANGE);

	//Vout
	VO_dvi->set_voltage(VO_ch, 0, 		VOLT_5_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
	//IS (0V)
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	//FB (5V)
	REQ_ovi->set_voltage(REQ_ch, 5.0,		VOLT_5_RANGE);	// OVI_1_2	
	REQ_ovi->set_current(REQ_ch, 5e-3,	RANGE_30_MA);	
	wait.delay_10_us(10);
	//BPS (vPlus - 200mV)
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
	VBPS_ramp_up(0, gVBPS_M_Init - 100e-3, 100e-3);	//BPS ramp up from 0 to VBPS-M minus 100mV with 100mV step.
	wait.delay_10_us(5);

	//4. Set VFW to 1V
	FW_dvi->set_voltage(FW_ch, 1.0, 		VOLT_50_RANGE);	// DVI_11_1
	FW_dvi->set_current(FW_ch, 300.0e-3,		RANGE_300_MA);
	wait.delay_10_us(10);
	delay(1);	//Minimum wait time is 700us in order for AF reading to work properly

	//5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
	VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVBPS_P_Init+50e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
	delay(2);  //Require min 1ms here for all SR_AF to read in properly

	for(i=1; i<=48; i++)
	{
		
		REQ_ovi->set_voltage(REQ_ch, 5.0*gSR_AF[i], 		VOLT_5_RANGE);	// OVI_1_2
		wait.delay_10_us(7);
		//Vout to clock to AF link
		VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
		wait.delay_10_us(7);	
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
		wait.delay_10_us(7);	
		REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
		wait.delay_10_us(7);
	}

	//7. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
		FW_dvi->set_voltage(FW_ch, -0.3, 		VOLT_50_RANGE);	// DVI_11_1
		wait.delay_10_us(50);
		FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
		FW_dvi->set_current(FW_ch, 0,			RANGE_300_MA);
		wait.delay_10_us(50);
		Open_relay(K18);

	//8. Set FB back to 1V
		REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		VOLT_5_RANGE);	// OVI_1_2
		wait.delay_10_us(40);
		delay(1);
		
		Connect_InvSyn_IM(Low_Vd_Input);

	if(PowerUpMode_P == Normal_Mode_P)
		Power_Up_Primary_Normal_Mode(ILIM_NORM);
	else
		VBPP_Power_Up_w_Test_Mode(PowerUpMode_P, ILIM_NORM);	//
}

void SyncHS_PowerUp_Secondary_in_ProgMode_Skip_WaitNListen(int PowerUpMode_S=0, int PowerUpMode_P=0)
{	
		int	  i=0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
		wait.delay_10_us(10);

		ddd_7->ddd_run_pattern(Low_XXX_pat_start, Low_XXX_pat_stop);	
		wait.delay_10_us(10);
		Open_relay(K12);	//Disconnect Vpin from DDD
		Close_relay(K18);	//FW to dvi-11-1
		delay(3);

		//Float SR pin
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);
		//Vpin (0V)
		if(PowerUpMode_P == gTM2_UVOV_NoDelay)
		{
			VPIN_ovi->set_voltage(VPIN_ch, 6.0,			VOLT_10_RANGE);
			VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	
		}
		else
		{		
			VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
			VPIN_ovi->set_voltage(VPIN_ch, 0.0,			VOLT_10_RANGE);
		}
		//Vout
		VO_dvi->set_voltage(VO_ch, 0, 		VOLT_5_RANGE);	// DVI_9_0
		VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);		
		//IS (0V)
		FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
		FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
		//FB (5V)
		REQ_ovi->set_voltage(REQ_ch, 5.0,		VOLT_5_RANGE);	// OVI_1_2	
		REQ_ovi->set_current(REQ_ch, 5e-3,	RANGE_30_MA);	
		wait.delay_10_us(10);
		//BPS (vPlus - 200mV)
		BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
		VBPS_ramp_up(0, gVBPS_M_Init - 100e-3, 100e-3);	//BPS ramp up from 0 to VBPS-M minus 100mV with 100mV step.
		wait.delay_10_us(5);

		//4. Set VFW to 1V
		FW_dvi->set_voltage(FW_ch, 1.0, 		VOLT_50_RANGE);	// DVI_11_1
		FW_dvi->set_current(FW_ch, 300.0e-3,		RANGE_300_MA);
		wait.delay_10_us(10);
		delay(1);	//Minimum wait time is 700us in order for AF reading to work properly

		//5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
		VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVBPS_P_Init+50e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
		delay(2);  //Require min 1ms here for all SR_AF to read in properly

	for(i=1; i<=48; i++)
	{
		
		REQ_ovi->set_voltage(REQ_ch, 5.0*gSR_AF[i], 		VOLT_5_RANGE);	// OVI_1_2
		wait.delay_10_us(7);
		//Vout to clock to AF link
		VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
		wait.delay_10_us(7);	
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
		wait.delay_10_us(7);	
		REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
		wait.delay_10_us(7);
	}

	//7. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
		FW_dvi->set_voltage(FW_ch, -0.3, 		VOLT_50_RANGE);	// DVI_11_1
		wait.delay_10_us(50);
		FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
		FW_dvi->set_current(FW_ch, 0,			RANGE_300_MA);
		wait.delay_10_us(50);
		Open_relay(K18);  //disconnect FW from dvi-11-1
		Close_relay(K21); //FW to DDD (once DDD connected, it will then be set to DDD's vLow)
		delay(3);

	if(PowerUpMode_P == Normal_Mode_P)
		Power_Up_Primary_Normal_Mode(ILIM_NORM);
	else
		VBPP_Power_Up_w_Test_Mode(PowerUpMode_P, ILIM_NORM);	//
		wait.delay_10_us(10);

		ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//Vpin set to vHigh
		wait.delay_10_us(10);
		// Secondary send 3 negative FW pulses to cause Primary to see request so Primary will be switching
		Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
		wait.delay_10_us(10);  //more than 30us quiet time on FW signal

		REQ_ovi->set_voltage(REQ_ch, gREQ_2V,	RANGE_2_V);	// OVI_1_2	
		D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0		
		wait.delay_10_us(5);

		Connect_InvSyn_IM(Low_Vd_Input);		
		Open_relay(K21);		// FW		to	DDD
		wait.delay_10_us(10);
		D_dvi->set_voltage(D_ch, 5.0, 			VOLT_50_RANGE);	// DVI_11_0		
		wait.delay_10_us(140);

	//8. Set FB back to 1V
		REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		VOLT_5_RANGE);	// OVI_1_2
		wait.delay_10_us(40);
		delay(1);
}

void Sync_HandShake_Powerdown()
{
	BPP_ovi->set_current(BPP_ch, 30e-3,				RANGE_30_MA);	 
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 				RANGE_10_V);	// DVI_9_1
	D_dvi->set_current(D_ch, 30e-3,	RANGE_30_MA);	
	D_dvi->set_voltage(D_ch, 0.0);										// Auto range
	wait.delay_10_us(30);

}

float Rdson_Buffer_Cal(float res_div_ratio)
{
	float	buf_gain=0.0;
	float	Vbuf_in =0.0;
	float	vsample =0.0;
	float	ChB_vrng=0.0;
	int		vrng_b	=0.0;
	int		iaddr	=0;
	int		lcnt	=0;
	int		vrng_a=0;
	float	ChA_vrng =0.0;
	float	Idmax_exp=0.0, Vdmax_exp=0.0;
	float	ilim_trig_lev=0;

	vrng_b = GAGE_PM_5_V;
	ChB_vrng = 5.0;

	Close_relay(K2);	
	Close_relay(K10);		// Connect Rdson Buffer to DVI_11_0
	delay(5);

	Vbuf_in = 4.875 * res_div_ratio;		// 97.5% of 5V range

	// Stop Primary from switching
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, RANGE_10_V);	// OVI_1_0
	BPP_ovi->set_current(BPP_ch, 30e-3,RANGE_30_MA);

	D_dvi->set_current(D_ch, 30e-3,	RANGE_30_MA);	
	D_dvi->set_voltage(D_ch, Vbuf_in);			// Auto range
	//	Set up Buffer Clamp
	BC_ovi->set_current(BC_ch, 30e-3,		RANGE_30_MA);
	BC_ovi->set_voltage(BC_ch, (ChB_vrng-0.6),VOLT_5_RANGE);	// OVI_1_3 Account for one diode drop
	delay(1);

	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,SAMPLE_SIZE); 
	delay(2);

	gage_input_control_xp (GAGE_CHAN_B,		// channel
			GAGE_INPUT_ENABLE,					// enable / disable
			GAGE_DC,							// coupling
			vrng_b|GAGE_1_MOHM_INPUT);			// range, impedance
	delay(2);
	
	gage_trigger_control_xp (GAGE_CHAN_B,		// trigger source
			GAGE_DC,							// coupling for ext trig
			vrng_b,								// range for CHA trigger
			GAGE_POSITIVE,						// slope
			1.0,								// 1.0V trigger level 
	   		SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE
	delay(2);
	
	Gage_Start_Capture( );
	delay(2);

	i32Status = CsDo(hSystem, ACTION_FORCE);
	delay(2);

	Gage_Wait_For_Capture_Complete( );
	delay(2);
	// Transfer data
	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array
	delay(2);
	
	if (!trig_ok || !data_ok)
	{
		buf_gain =0.0;
		return buf_gain;
	}

	lcnt =0;
	vsample =0.0;
	for (iaddr = 100 ; iaddr<SAMPLE_SIZE; iaddr+=25)
	{
		vsample += Gage_chan_b_voltage[iaddr];
		lcnt ++;
	}

	if (vsample>0.1 && lcnt >0)
	{
		vsample /= lcnt;
		buf_gain = Vbuf_in/vsample;
	}
	else
		buf_gain =0.0;




	//Power down
	D_dvi->set_voltage(D_ch, 0.0);	// Auto range
	wait.delay_10_us(10);
	Open_relay(K10);
	Open_relay(K2);
	delay(1);

	if(DEBUG==1 && gDEBUG)
		Create_Awav_xp("RDSON_BUF_CAL", Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);
	


	Idmax_exp = gIlim_Incr_max*Ilim_gain *1.2;// Increase 20% to cover the highest ILIM pretrim
	ilim_trig_lev = 0.10;	// Set a higher trigger level to have a consistency point of capture. HQL 07/08/14

	if(Idmax_exp < 0.5)	
	{	
		vrng_a = GAGE_PM_500_MV;
		ChA_vrng =0.5;
	}
	else if(Idmax_exp >= 0.5 && Idmax_exp < 1.0)
	{		
		vrng_a = GAGE_PM_1_V;
		ChA_vrng = 1.0; 
	}
	else if(Idmax_exp >= 1.0 && Idmax_exp < 2.0)	
	{	
		vrng_a = GAGE_PM_2_V;
		ChA_vrng = 2.0; 
	}
	else if(Idmax_exp >= 2.0)
	{	
		vrng_a = GAGE_PM_5_V;
		ChA_vrng = 5.0;
	}
	//Reset Trigger level for the rest of the program so it won't need to be called again
	gage_trigger_control_xp (GAGE_CHAN_A,		// trigger source
			GAGE_DC,							// coupling for ext trig
			vrng_a,								// range for CHA trigger
			GAGE_NEGATIVE,						// slope
			0.1,								// Tigger level in Volt (100mV)
	   		SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE


	return buf_gain;

	
}

void search_VBPP_th( float* vBPP_pV, float* vBPP_m, float* vBPP_p, float* vBPP_p_iHVoff, float* vBPP_vshuntPUseq)
{	
/********************************************************************************************************************************
 *		Priamry: vBPP_PV (1.4mA) --> vBPP_M (-5mA) --> vBPP_P (-1.2mA) --> vBPP_P_iHVoff (200uA) --> vBPP_ShuntPUseq			*
 *																																*
 * 1. Drain=0, BPP=5.0, IBPP=220uA, increase BPP until IBPP jumps to 1.4mA														*
 *    (this is around BPP=5.4V the first level when first powering up.  This is not the VBPP-P, a Vpin threshold for Testmodes)	*
 * 2. Bring BPP down to 5V, turn on Drain=50V through 1K load, IBPP is still positive around 1.2mA,								*
 *    decrease BPP down until IBPP flip sign from 0.6mA to -5mA (this is around 4.5V the first level when BPP goes down VBPP-M)	*
 * 3. Increase BPP to around 5V VBPP-P to see device starts switching															*
 *    (this is the level after 2nd time raise BPP up) IBPP around -1.2mA														*
 * 4. Increase BPP to around 5.1V to see IBPP drops to +200uA (this is where the high-voltage current source turns off)			*
 * 5. Increase BPP to around 5.4V VBPP-shunt when the device stops switching and IBPP = 11.3mA > 10mA (DE don't need this)		*
 ********************************************************************************************************************************/

	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float vstart=0, vstop=0, vBPP_P_Expect=0;
	float ich_th=0;
	int   lcnt1=0, lcnt2=0, rcnt =0;

	int		dly_BPP_p47uF, dly_BPP_4p7uF;

	dly_BPP_p47uF = 1; //ms
	dly_BPP_4p7uF = 3; //ms

	vBPP_P_Expect = 5;

	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		RANGE_10_V);	// OVI_1_0	
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);   
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
	wait.delay_10_us(30);

// ** VBPP_PV
	lcnt1 =0;
	lcnt2 =0;
	ich_th = 1.3e-3;			// threshold to decide if device is switching or not

	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 100e-3);    //BPP ramp up from 0V to 4.5V in 100mV step    (Needed for -40C)
	//VBPP_ramp_up(0, 4.5, 100e-3);	//BPP ramp up from 0V to 4.5V in 100mV step
	if(BPP_4p7uF) delay(3);
	if(BPP_p47uF) delay(1);
	imeas = BPP_ovi->measure_average(5);

	//delay(1);
	//VBPP_ramp_up(4.5, 5.5, 100e-3);	//BPP ramp up from 0V to 4.5V in 100mV step
	//imeas = BPP_ovi->measure_average(5);

	if(DEBUG==1 && gDEBUG)
	{
		printf("\nsearch_VBPP_PVth: VBPP-PV\n");
		printf("vBPP = %fV, iBPP = %fmA \n", 4.5, imeas*1e3);
	}

	if (imeas >ich_th)
	{	
		*vBPP_pV = 0.0;	
		return;
	}
	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.1;	// used to be 0.2
	vfrc = 4.5;
	while ((vstep >=0.1) && (vfrc < 6.3) && (lcnt1< 200))
	{
		if (imeas <ich_th)
		{	vfrc+=vstep;
			BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
			wait.delay_10_us(5);
			imeas = BPP_ovi->measure_average(5);
			if(DEBUG==1 && gDEBUG)
				printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);

		}
		else			
		{	// Reset device and reduce searching step
			vfrc -=  1.25* vstep;	// Back down 1.25 step
			vstep = 0.0025;			// Fine search, used to be 0.01
			// Reset device
			VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
			//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU,		RANGE_10_V);			// Starting search point
			wait.delay_10_us(10);

			VBPP_ramp_up(gVBPP_Low_Voltage_PU, vfrc, 50e-3);	//BPP ramp up from 0V to vfrc in 50mV step
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
			imeas = BPP_ovi->measure_average(5);				//expect device not switching here.
			if(DEBUG==1 && gDEBUG)
				printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
			if (imeas >ich_th)
			{	
				*vBPP_p = -1.0;	
				return;
			}
			while ((imeas < ich_th) && (lcnt2<100) && (vfrc <5.5) )
			{	vfrc+=vstep;
				BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);

				wait.delay_10_us(5);
				imeas = BPP_ovi->measure_average(5);
				if(DEBUG==1 && gDEBUG)
					printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
				lcnt2++;
			}
		} 
		lcnt1 ++;
	}

	*vBPP_pV = vfrc;


// ** VBPP_M

	D_dvi->set_voltage(D_ch,	 45,		VOLT_50_RANGE);  

	lcnt1 =0;	
	lcnt2 =0;
	ich_th = 0.7e-3;

	BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
	wait.delay_10_us(15);	// JD was 5, tester correlation
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
	imeas = BPP_ovi->measure_average(15);	// JD was 5, tester correlation
	if(DEBUG==1 && gDEBUG)
	{
		printf("\nsearch_VBPP_th: VBPP-M\n");
		printf("vBPP = %fV, iBPP = %fmA \n", vfrc, imeas*1e3);
	}

	if (imeas <ich_th)
	{	
		*vBPP_m = 0.0;	
		return;
	}

	vstep = 0.1;
	while ((vstep >=0.1) && (vfrc > 3.0) && (lcnt1< 200))
	{
		if (imeas >ich_th)
		{	vfrc-=vstep;
			BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
			wait.delay_10_us(5);
			imeas = BPP_ovi->measure_average(5);	
			if(DEBUG==1 && gDEBUG)
				printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
		}
		else			
		{	
			vstep = 0.0025;			// Fine search
			ich_th = 0;
			while ((imeas > ich_th) && (vfrc > 3.0) && (lcnt2<200))
			{	vfrc-=vstep;
				BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
				wait.delay_10_us(15);	// JD was 5, tester correlation
				imeas = BPP_ovi->measure_average(15);	// JD was 5, tester correlation
				if(DEBUG==1 && gDEBUG)
					printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
			
				lcnt2++;
			}
		} 
		lcnt1 ++;
	}
	*vBPP_m = vfrc;

if (*vBPP_m < 0.0) 
	*vBPP_m =0.0;


// ** VBPP_P
	lcnt1 =0;
	lcnt2 =0;
	ich_th = -2e-3;			// threshold to decide if device is switching or not
	vstep = 0.1;	// used to be 0.2

	BPP_ovi->set_voltage(BPP_ch, vfrc-10e-3,	RANGE_10_V);
	wait.delay_10_us(5);
	imeas = BPP_ovi->measure_average(5);

	while ((vstep >=0.1) && (vfrc < 6.0) && (lcnt1< 200))
	{
		if ( imeas<ich_th && vfrc<(vBPP_P_Expect-100e-3) )
		{	vfrc+=vstep;
			BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
			wait.delay_10_us(5);
			imeas = BPP_ovi->measure_average(5);
			if(DEBUG==1 && gDEBUG)
				printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);

		}
		else			
		{	
			vstep = 0.0025;			// Fine search, used to be 0.01
			while ((imeas < ich_th) && (lcnt2<100) && (vfrc <6.0) )
			{	vfrc+=vstep;
				BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
				wait.delay_10_us(5);
				imeas = BPP_ovi->measure_average(5);
				if(DEBUG==1 && gDEBUG)
					printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
				lcnt2++;
			}
		} 
		lcnt1 ++;
	}

	*vBPP_p = vfrc;


//4. Increase BPP to around 5.1V to see IBPP drops to +200uA (this is where the high-voltage current source turns off)			*
// ** VBPP_P_iHVoff
	lcnt1 =0;
	lcnt2 =0;
	ich_th = 170e-6;	//change from -1.2mA to 200uA.  170uA set as threshold

	vstep = 2.5e-3;		
	while ((imeas < ich_th) && (lcnt2<100) && (vfrc <5.5) )
	{	vfrc+=vstep;
		BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
		wait.delay_10_us(15);	// JD was 5, tester correlation
		imeas = BPP_ovi->measure_average(15);	// JD was 5, tester correlation
		if(DEBUG==1 && gDEBUG)
			printf("vBPP_P_iHVoff = %fV, iBPP = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
		lcnt2++;
	}

	*vBPP_p_iHVoff = vfrc;

//////5. Increase BPP to around 5.4V VBPP-shunt when the device stops switching and IBPP = 11.3mA > 10mA							*
////	lcnt1 =0;
////	lcnt2 =0;
////	ich_th = 10e-3;	//change from 200uA to 11.3mA  (10mA set as threshold)
////	vfrc	= *vBPP_pV - 50e-3;	//Start at a closer threshold for Vshunt.
////
////	vstep = 2.5e-3;		
////	while ((imeas < ich_th) && (lcnt2<100) && (vfrc <6.0) )
////	{	vfrc+=vstep;
////		BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
////			if(BPP_4p7uF) delay(3);
////			if(BPP_p47uF) delay(dly_BPP_p47uF);
////		wait.delay_10_us(5);
////		imeas = BPP_ovi->measure_average(5);
////		if(DEBUG==1)
////			printf("vBPP_vshunt_PUseq=%fV, iBPP=%fmA, vstep=%fV, lcnt2=%i \n", vfrc, imeas*1e3, vstep, lcnt2);
////		lcnt2++;
////	}
////	*vBPP_vshuntPUseq = vfrc;
}


////void search_VBPS_P_th( float* vBPS_p)
////{	
/////**************************************************************************************
//// *					Secondary: VBPS_P_Init, VBPS_M_Init, VBPS_HYS_Init				  *
//// *							 : VBPS_P,      VBPS_M,      VBPS_HYS					  *
//// *VBPS_Init_P:																		  *
//// * Chip consumption is the same at different states for secondary when device is not  *
//// * switching. Power up FW pin to see state transition by checking charge current. 	  *
//// * NOTE: CURRENT from FW to BPS guide line: (Vfw - Vbps - Vdiode)/200ohm			  *
//// *                           +200uA													  *			
//// *				 -20mA /----------------											  *
//// *					  /											            		  *	
//// *	BPS Pin			 /	                                                              *
//// *	FW =9.5V   	    /                                                                 *
//// **************************************************************************************/
////	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
////	float ich_th=0, IBPS_nsw=0;
////	int   lcnt1=0, lcnt2=0;
////
////	float result;
////
////	ddd_7->ddd_set_lo_level(-1.0);		// Will immediately change to this level upon execution 
////	delay(1);
////	ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
////	delay(1);
////
////	DDD_Load_Loop_Pulses(3, 60);
////
////	tmu_6->init();
////	tmu_6->close_relay(TMU_CHAN_A_DUT1);
////	tmu_6->open_relay(TMU_CHAN_A_DUT2);
////	tmu_6->open_relay(TMU_CHAN_B_DUT1);
////	tmu_6->open_relay(TMU_CHAN_B_DUT2);
////
////	//tmu_6->start_holdoff(5, TRUE); // Sets start holdoff to 1 events, 2nd parameter needed
////	//tmu_6->stop_holdoff(10,TRUE); // Sets stop holdoff to 10 events, 2nd parameter needed
////	tmu_6->start_trigger_setup(2.6, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
////	tmu_6-> stop_trigger_setup(2.4, POS_SLOPE, TMU_CHAN_A, TMU_IN_10V);
////	delay(1);
////	
////	//Run_Loop_Pulses();//ddd_7->ddd_run_pattern(0, gDDD_loop_pulses_stop);
////
////	for (vfrc = 3.5; vfrc < 5; vfrc = vfrc + 0.01)
////	{
////		BPS_dvi->set_voltage(BPS_ch, vfrc, VOLT_10_RANGE);
////		wait.delay_10_us(30);
////		tmu_6->arm();
////		//wait.delay_10_us(5);
////		ddd_7->ddd_run_pattern(0, gDDD_loop_pulses_stop);
////		wait.delay_10_us(70);
////		result = tmu_6->read();
////		//wait.delay_10_us(10);
////		//result = 1/result; // Convert to Frequency
////		if ((result > 0.00016) && (result < 0.0002)) break;
////	}
////	
/////********/
////	lcnt1 =0;
////	lcnt2 =0;
////	vfrc = 3.5;
////	//ich_th = 0.0;			// threshold 0mA  From neg to positive at transtion pt
////	BPS_dvi->set_voltage(BPS_ch, vfrc, 		VOLT_10_RANGE);	// Starting search point
////	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
////	wait.delay_10_us(30);
////
////	//imeas = BPS_dvi->measure();
////	tmu_6->arm();
////	//ddd_7->ddd_run_pattern(0, gDDD_loop_pulses_stop);
////	ddd_7->ddd_run_pattern(FW_30us_pulse_start, FW_30us_pulse_stop);
////	wait.delay_10_us(60);
////	result = tmu_6->read();
////
////	if(DEBUG==1 && gDEBUG)
////	{
////		printf("\nsearch_VBPS_P_th:\n");
////		printf("vBPS = %fV, iBPS = %fmA \n", vfrc, imeas*1e3);
////	}
////
////	//if (imeas >ich_th)
////	//{	
////	//	*vBPS_p = 0.0;	
////	//	return;
////	//}
////
////	//starttime = mytimer.GetElapsedTime();// testtime check
////	vstep = 0.2;
////	while ((vstep >0.1) && (vfrc < 5.4) && (lcnt1< 200))
////	{
////		//if (imeas <ich_th)		// imeas is negative 
////		//if (result < 0.00016)
////		if ((result < 0.00016) || (result > 0.0002))
////		{	
////			vfrc+=vstep;
////			BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
////			wait.delay_10_us(30);
////			//imeas = BPS_dvi->measure_average(5);
////			tmu_6->arm();
////			//ddd_7->ddd_run_pattern(0, gDDD_loop_pulses_stop);
////			ddd_7->ddd_run_pattern(FW_30us_pulse_start, FW_30us_pulse_stop);
////			wait.delay_10_us(60);
////			result = tmu_6->read();
////			if(DEBUG==1 && gDEBUG)
////				printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
////		}
////		else			
////		{	// Reset device and reduce searching step
//////			vfrc -= 1.5* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
////			vfrc -= 2.0* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
////			vstep = 0.01;			// Fine search
////
////			// Don't need to reset device
////			BPS_dvi->set_voltage(BPS_ch, 3.8,	VOLT_10_RANGE);	
////			wait.delay_10_us(10);
////			// But make sure only ramp one way to avoid comparator Hyst[about 0.2V](Not VBPS Hyst [about 0.5V])
////			BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	
////			wait.delay_10_us(60);
////			//imeas = BPS_dvi->measure();				// Should be negative
////			tmu_6->arm();
////			//ddd_7->ddd_run_pattern(0, gDDD_loop_pulses_stop);
////			ddd_7->ddd_run_pattern(FW_30us_pulse_start, FW_30us_pulse_stop);
////			wait.delay_10_us(60);
////			result = tmu_6->read();
////			if(DEBUG==1 && gDEBUG)
////				printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
////			//if (imeas >ich_th)
////			if ((result > 0.00016) && (result < 0.0002))//(result < 0.00016)
////			{	
////				*vBPS_p = -1.0;	
////				return;
////			}
////			//while ((imeas < ich_th) && (vfrc <5.4) && (lcnt2<200) )
////			while (!((result > 0.00016) && (result < 0.0002)) && (vfrc <5.4) && (lcnt2<200) )
////			{	vfrc+=vstep;
////				BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
////				wait.delay_10_us(30);
////				//imeas = BPS_dvi->measure_average(5);
////				tmu_6->arm();
////				//ddd_7->ddd_run_pattern(0, gDDD_loop_pulses_stop);
////				ddd_7->ddd_run_pattern(FW_30us_pulse_start, FW_30us_pulse_stop);
////				wait.delay_10_us(60);
////				result = tmu_6->read();
////
////				if(DEBUG==1 && gDEBUG)
////					printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
////				lcnt2++;
////			}
////		} 
////		lcnt1 ++;
////	}
////
/////********/
////
////	//Close_relay(K18);   // FW_dvi
////	//Open_relay(K21);
////	BPS_dvi->set_voltage(BPS_ch, 5.0, VOLT_10_RANGE);
////	delay(1);
////	REQ_ovi->set_voltage(REQ_ch, 1.0, RANGE_5_V);
////	delay(1);
////	result = BPS_dvi->measure_average(25);
////	delay(1);
////	REQ_ovi->set_voltage(REQ_ch, 2.0, RANGE_5_V);
////	delay(1);
////	Stop_Loop_Pulses();
////	DDD_Load_Loop_Pattern();
////	delay(1);
////
////
//////	lcnt1 =0;
//////	lcnt2 =0;
//////	vramp_pt =3.5;
//////	vfrc = vramp_pt;
//////	ich_th = 0.0;			// threshold 0mA  From neg to positive at transtion pt
//////	BPS_dvi->set_voltage(BPS_ch, vfrc, 		VOLT_10_RANGE);	// Starting search point
//////	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
//////	wait.delay_10_us(30);
//////
//////	imeas = BPS_dvi->measure();
//////
//////	if(DEBUG==1 && gDEBUG)
//////	{
//////		printf("\nsearch_VBPS_P_th:\n");
//////		printf("vBPS = %fV, iBPS = %fmA \n", vfrc, imeas*1e3);
//////	}
//////
//////	if (imeas >ich_th)
//////	{	
//////		*vBPS_p = 0.0;	
//////		return;
//////	}
//////
//////	//starttime = mytimer.GetElapsedTime();// testtime check
//////	vstep = 0.2;
//////	while ((vstep >0.1) && (vfrc < 5.4) && (lcnt1< 200))
//////	{
//////		if (imeas <ich_th)		// imeas is negative 
//////		{	vfrc+=vstep;
//////			BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
//////			wait.delay_10_us(60);
//////			imeas = BPS_dvi->measure_average(5);
//////			if(DEBUG==1 && gDEBUG)
//////				printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
//////		}
//////		else			
//////		{	// Reset device and reduce searching step
////////			vfrc -= 1.5* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
//////			vfrc -= 2.0* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
//////			vstep = 0.01;			// Fine search
//////
//////			// Don't need to reset device
//////			// But make sure only ramp one way to avoid comparator Hyst[about 0.2V](Not VBPS Hyst [about 0.5V])
//////			BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	
//////			wait.delay_10_us(60);
//////			imeas = BPS_dvi->measure();				// Should be negative
//////			if(DEBUG==1 && gDEBUG)
//////				printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
//////			if (imeas >ich_th)
//////			{	
//////				*vBPS_p = -1.0;	
//////				return;
//////			}
//////			while ((imeas < ich_th) && (vfrc <5.4) && (lcnt2<200) )
//////			{	vfrc+=vstep;
//////				BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
//////				wait.delay_10_us(10);
//////				imeas = BPS_dvi->measure_average(5);		
//////				if(DEBUG==1 && gDEBUG)
//////					printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
//////				lcnt2++;
//////			}
//////		} 
//////		lcnt1 ++;
//////	}
////
////	*vBPS_p = vfrc;
////
////	//BPS_ISS1: Bring vBPS up to vBPS_p + 50mV and datalog BPS sink current as no load consumption current
////	BPS_dvi->set_voltage(BPS_ch, vfrc+50e-3,	VOLT_10_RANGE);	// Starting search point
////	BPS_dvi->set_current(BPS_ch, 3e-3,	RANGE_3_MA);	
////	
////	//Require more delay according to JD for H105,H106 B5p of 8" wafer 
////	//if ( gHcode == 105 || gHcode == 106	)	
////	//{
////	//	wait.delay_10_us(150);	// JD was 1ms, saw tail going high on B5 primary and gets better with more delay.
////	//}
////	//else											
////		delay(1);				// 1ms
////	
////	gIBPS_nsw = 0.0;								//Always reset global variable here
////	gIBPS_nsw = BPS_dvi->measure_average(25);;	//gIBPS_nsw datalog as BPP:ISS1-S in IBP_Supply function
////	BPS_dvi->set_current(BPS_ch, 100e-3,	RANGE_300_MA);	 
////
////}

void search_VBPS_P_th( float* vBPS_p)
{	
/**************************************************************************************
 *					Secondary: VBPS_P_Init, VBPS_M_Init, VBPS_HYS_Init				  *
 *							 : VBPS_P,      VBPS_M,      VBPS_HYS					  *
 *VBPS_Init_P:																		  *
 * Chip consumption is the same at different states for secondary when device is not  *
 * switching. Power up FW pin to see state transition by checking charge current. 	  *
 * NOTE: CURRENT from FW to BPS guide line: (Vfw - Vbps - Vdiode)/200ohm			  *
 *                           +200uA													  *			
 *				 -20mA /----------------											  *
 *					  /											            		  *	
 *	BPS Pin			 /	                                                              *
 *	FW =9.5V   	    /                                                                 *
 **************************************************************************************/
	Pulse pulse(PULSE_RISING_EDGE,10e-6);
	//pulse.do_pulse();

	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float ich_th=0, IBPS_nsw=0;
	int   lcnt1=0, lcnt2=0;

	float result=0;

	ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
	delay(1);
	ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	delay(1);

	DDD_Load_Loop_Pulses(3, 80);

	tmu_6->init();
	tmu_6->close_relay(TMU_CHAN_B_DUT1);

	//tmu_6->start_holdoff(5, TRUE); // Sets start holdoff to 1 events, 2nd parameter needed
	//tmu_6->stop_holdoff(10,TRUE); // Sets stop holdoff to 10 events, 2nd parameter needed
	tmu_6->start_trigger_setup(2.1, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
	tmu_6-> stop_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
	wait.delay_10_us(10);
	
	Run_Loop_Pulses();
	//ddd_7->ddd_run_pattern(0,gDDD_loop_pulses_stop);
	//delay(1);

	//for (vfrc = 3.5; vfrc < 5; vfrc = vfrc + 0.01)
	//{
	//	BPS_dvi->set_voltage(BPS_ch, vfrc, VOLT_10_RANGE);
	//	wait.delay_10_us(50);
	//	tmu_6->arm();
	//	wait.delay_10_us(10);
	//	result = tmu_6->read();
	//	//result = 1/result; // Convert to Frequency
	//	if (result>20e-6) break;
	//}
	//
	//Close_relay(K18);   // FW_dvi
	//Open_relay(K21);
	//BPS_dvi->set_voltage(BPS_ch, 5.0, VOLT_10_RANGE);
	//delay(1);
	//REQ_ovi->set_voltage(REQ_ch, 1.0, RANGE_5_V);
	//delay(1);
	//result = BPS_dvi->measure_average(25);
	//delay(1);
	//gIBPS_nsw = 0.0;								//Always reset global variable here
	//gIBPS_nsw = BPS_dvi->measure_average(25);;	//gIBPS_nsw datalog as BPP:ISS1-S in IBP_Supply function
	//wait.delay_10_us(50);
	//REQ_ovi->set_voltage(REQ_ch, 2.0, RANGE_5_V);
	//delay(1);
	//Stop_Loop_Pulses();
	//DDD_Load_Loop_Pattern();//
	//delay(10);
	//DDD_Load_Patterns();
	//delay(1);

	lcnt1 =0;
	lcnt2 =0;
	vramp_pt =3.5;
	vfrc = vramp_pt;
//	ich_th = 0.0;			// threshold 0mA  From neg to positive at transtion pt
	BPS_dvi->set_voltage(BPS_ch, vfrc, 		VOLT_10_RANGE);	// Starting search point
//	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	wait.delay_10_us(30);
	tmu_6->arm();
	wait.delay_10_us(10);
	result = tmu_6->read();
//
	imeas = BPS_dvi->measure();
//
	if(DEBUG==1 && gDEBUG)
	{
		printf("\nsearch_VBPS_P_th:\n");
		printf("vBPS = %fV, iBPS = %fmA \n", vfrc, imeas*1e3);
	}
//
	if (result>2e-6)
	{	
		*vBPS_p = 0.0;	
		return;
	}
////
//	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.3;
	while ((vstep >0.1) && (vfrc < 5.6) && (lcnt1< 200))
	{
		tmu_6->arm();
		wait.delay_10_us(10);
		result = tmu_6->read();
		if (result<2e-6)		// No pulses on ACK
		{	vfrc+=vstep;
			BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
			wait.delay_10_us(60);
			//imeas = BPS_dvi->measure_average(5);
			if(DEBUG==1 && gDEBUG)
				printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
		}
		else			
		{	// Reset device and reduce searching step
			vfrc -= 2.0* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
			//vfrc -= 1.0* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
			vstep = 0.1;			// Fine search

			// Don't need to reset device
			// But make sure only ramp one way to avoid comparator Hyst[about 0.2V](Not VBPS Hyst [about 0.5V])
			BPS_dvi->set_voltage(BPS_ch, vramp_pt,	VOLT_10_RANGE);	
			wait.delay_10_us(60);
			tmu_6->arm();
		    wait.delay_10_us(10);
		     result = tmu_6->read();


			//imeas = BPS_dvi->measure();				// Should be negative
			if(DEBUG==1 && gDEBUG)
				printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
			if (result>2e-6)
			{	
				*vBPS_p = -1.0;	
				return;
			}
			while ((result<2e-6) && (vfrc <5.4) && (lcnt2<200) )
			{	
				vramp_pt+=vstep;
				BPS_dvi->set_voltage(BPS_ch, vramp_pt ,	VOLT_10_RANGE);	// Starting search point
				wait.delay_10_us(10);
				tmu_6->arm();
		         wait.delay_10_us(10);
		          result = tmu_6->read();

					if(vramp_pt>(vfrc-vstep))
					{
						vstep=0.01;
						while(result<2e-6)
						{
							vfrc+=vstep;
							BPS_dvi->set_voltage(BPS_ch, vfrc ,	VOLT_10_RANGE);	// Starting search point
							wait.delay_10_us(10);
							tmu_6->arm();
							wait.delay_10_us(10);
							result = tmu_6->read();
						}
					}
					
						

				/*imeas = BPS_dvi->measure_average(5);	*/	
				if(DEBUG==1 && gDEBUG)
					printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
				lcnt2++;
			}
		} 
		lcnt1 ++;
	}

	*vBPS_p = vfrc;

		
	//Stop_Loop_Pulses();
	//ddd_7->ddd_run_pattern(0,gDDD_loop_pulses_stop);
	//ddd_7->ddd_run_pattern(High_pat_FW_start,High_pat_FW_stop);
	//delay(1);
//
//BPS_ISS1: BPS Non-switching current. Bring REQ to 1V and BPS to 5V

	BPS_dvi->set_voltage(BPS_ch, 5.0, VOLT_10_RANGE);
	//BPS_dvi->set_current(BPS_ch, 3e-3,	RANGE_3_MA);
	//ovi_1->disconnect(5);//Float ACK
	tmu_6->open_relay(TMU_CHAN_B_DUT1);
	Stop_Loop_Pulses();//Stop FWD from switching
	//wait.delay_10_us(50);
	delay(1);
	REQ_ovi->set_voltage(REQ_ch, 1.0, RANGE_5_V);
	//delay(1);
	gIBPS_nsw = 0.0;//Always reset global variable here
	wait.delay_10_us(10);
	//pulse.do_pulse();
	gIBPS_nsw = BPS_dvi->measure_average(25);	//gIBPS_nsw datalog as BPP:ISS1-S in IBP_Supply function
	
	//pulse.do_pulse();

	//Stop_Loop_Pulses();
	//ddd_7->ddd_run_pattern(High_pat_FW_start,High_pat_FW_stop);
	//delay(1);
	//wait.delay_10_us(20);
	//REQ_ovi->set_voltage(REQ_ch, 2.0, RANGE_5_V);
	//tmu_6->close_relay(TMU_CHAN_B_DUT1);
	//ACK_ovi->connect(OVI_CHANNEL_5);//Connect OVI back to ACK
	////delay(1);
	
	//BPS_ISS1: Bring vBPS up to vBPS_p + 50mV and datalog BPS sink current as no load consumption current
	//BPS_dvi->set_voltage(BPS_ch, vfrc+50e-3,	VOLT_10_RANGE);	// Starting search point
	//BPS_dvi->set_current(BPS_ch, 3e-3,	RANGE_3_MA);	
	
	//Require more delay according to JD for H105,H106 B5p of 8" wafer 
	//if ( gHcode == 105 || gHcode == 106	)	
	//{
	//	wait.delay_10_us(150);	// JD was 1ms, saw tail going high on B5 primary and gets better with more delay.
	//}
	//else											
		//delay(1);				// 1ms
	
	
	//BPS_dvi->set_current(BPS_ch, 100e-3,	RANGE_300_MA);	 

}



void search_VBPS_M_th( float* vBPS_m)
{
/***************************************************************************************
 *					Secondary: VBPS_M_Init, VBPS_M									   *
 * VBPS_Init:																		   *
 *	In order to find VBPS_M, allow device to switch, chip consumption on BPS pin       *
 *  should drop from 2mA to 0.2mA when CV_th threshold is reached and switching is off.*						      
 ***************************************************************************************/
	Pulse pulse(PULSE_RISING_EDGE,10e-6);

	//pulse.do_pulse();
	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float ich_th=0, IBPS_sw=0;
	int   lcnt1=0, lcnt2=0;

	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//wait.delay_10_us(10);
	REQ_ovi->set_voltage(REQ_ch, 2.0, RANGE_5_V);
	wait.delay_10_us(10);
	//IBPS_sw = BPS_dvi->measure_average(5);	   // For debug (Positive current)

	if(DEBUG==1 && gDEBUG)
	{
		printf("\nsearch_VBPS_M_th: VBPS_M_th\n");
		printf("vBPS = %fV, iBPS = %fmA \n", gVBPS_P_Init+0.05, IBPS_sw*1e3);
	}

	float result;

	//ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
	//delay(1);
	//ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	//delay(1);

	//DDD_Load_Loop_Pulses(3, 60);

	tmu_6->init();
	tmu_6->close_relay(TMU_CHAN_B_DUT1);

	//tmu_6->start_holdoff(5, TRUE); // Sets start holdoff to 1 events, 2nd parameter needed
	//tmu_6->stop_holdoff(10,TRUE); // Sets stop holdoff to 10 events, 2nd parameter needed
	tmu_6->start_trigger_setup(2.1, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
	tmu_6-> stop_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_B, TMU_IN_10V);
	delay(1);
	
	Run_Loop_Pulses();

	//for (vfrc = 5; vfrc > 3.5; vfrc = vfrc - 0.01)
	//{
	//	BPS_dvi->set_voltage(BPS_ch, vfrc, VOLT_10_RANGE);
	//	delay(1);
	//	tmu_6->arm();
	//	delay(1);
	//	result = tmu_6->read();
	//	//printf("vfrc = %2.2g, result = %10.10g\n", vfrc, result);
	//	//result = 1/result; // Convert to Frequency
	//	if (result < 1.0e-12) break;
	//}
	/*BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);
	Stop_Loop_Pulses();
	DDD_Load_Loop_Pattern();
	Delay(10);*/

	
	lcnt1 =0;
	lcnt2 =0;
	vramp_pt =5;
	vfrc = vramp_pt;
//	ich_th = 0.0;			// threshold 0mA  From neg to positive at transtion pt
	BPS_dvi->set_voltage(BPS_ch, vfrc, 		VOLT_10_RANGE);	// Starting search point
//	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	wait.delay_10_us(30);
	tmu_6->arm();
	wait.delay_10_us(10);
	result = tmu_6->read();
//
	imeas = BPS_dvi->measure();
//
	if(DEBUG==1 && gDEBUG)
	{
		printf("\nsearch_VBPS_P_th:\n");
		printf("vBPS = %fV, iBPS = %fmA \n", vfrc, imeas*1e3);
	}
//
	if (result<2e-6)
	{	
		*vBPS_m = 0.0;	
		return;
	}
////
//	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.3;
	while ((vstep >0.1) && (vfrc > 3.4) && (lcnt1< 200))
	{
		tmu_6->arm();
		wait.delay_10_us(10);
		result = tmu_6->read();
		if (result>2e-6)		// pulses on ACK
		{	vfrc-=vstep;
			BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
			wait.delay_10_us(60);
			//imeas = BPS_dvi->measure_average(5);
			if(DEBUG==1 && gDEBUG)
				printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
		}
		else			
		{	// Reset device and reduce searching step
			vfrc += 2.0* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
			//vfrc += 2.0* vstep;	// 2*vstep for VBS_P search
			//vfrc -= 1.0* vstep;   // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
			vstep = 0.1;			// Fine search

			// Don't need to reset device
			// But make sure only ramp one way to avoid comparator Hyst[about 0.2V](Not VBPS Hyst [about 0.5V])
			BPS_dvi->set_voltage(BPS_ch, vramp_pt,	VOLT_10_RANGE);	
			wait.delay_10_us(60);
			tmu_6->arm();
		    wait.delay_10_us(10);
		     result = tmu_6->read();


			//imeas = BPS_dvi->measure();				// Should be negative
			if(DEBUG==1 && gDEBUG)
				printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
			if (result<2e-6)
			{	
				*vBPS_m = -1.0;	
				return;
			}
			while ((result>2e-6) && (vfrc >3.4) && (lcnt2<200) )
			{	
				vramp_pt-=vstep;
				BPS_dvi->set_voltage(BPS_ch, vramp_pt ,	VOLT_10_RANGE);	// Starting search point
				wait.delay_10_us(10);
				tmu_6->arm();
		         wait.delay_10_us(10);
		          result = tmu_6->read();

					if(vramp_pt<(vfrc-vstep))
					{
						vstep=0.01;
						while(result>2e-6)
						{
							vfrc-=vstep;
							BPS_dvi->set_voltage(BPS_ch, vfrc ,	VOLT_10_RANGE);	// Starting search point
							wait.delay_10_us(10);
							tmu_6->arm();
							wait.delay_10_us(10);
							result = tmu_6->read();
						}
					}
					
						

				/*imeas = BPS_dvi->measure_average(5);	*/	
				if(DEBUG==1 && gDEBUG)
					printf("vBPS = %fV, iBPS = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
				lcnt2++;
			}
		} 
		lcnt1 ++;
	}

	*vBPS_m = vfrc;	

	BPS_dvi->set_voltage(BPS_ch, 0.0, VOLT_10_RANGE);
	Stop_Loop_Pulses();
	DDD_Load_Loop_Pattern();
	Delay(10);
}

void search_VBPS_M_th_Inno4( float* vBPS_m)
{
/****************************************************************************************
 *					Secondary: VBPS_M_Init, VBPS_M										*
 * VBPS_Init:																			*
 *	- Continue from VBPS_P (BPS no longer have current sink from FW)					*
 *	- Set Vout to 5V																	*
 *	- Reduce VBPS until FW current source current again to BPS							*
 ****************************************************************************************/
	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float iFW_th=0, iFW=0;
	int   lcnt1=0, lcnt2=0;

	//VO set to 5V
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, 30.0e-3,		RANGE_30_MA);	
	wait.delay_10_us(10);
	//Setup to measure FW current 
	FW_dvi->set_meas_mode(FW_ch,			DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);
	iFW = FW_dvi->measure_average(5);	   // expect FW not sourcing any current to BPS (less than 50uA)

	if(DEBUG==1 && gDEBUG)
	{
		printf("\nsearch_VBPS_M_th: VBPS_M_th\n");
		printf("vBPS = %fV, iFW = %fmA \n", gVBPS_P_Init+0.05, iFW*1e3);
	}

	lcnt1 =0;
	lcnt2 =0;

	//VBPS_M typical = 3.8V
//	vramp_pt = 3.8 + 200e-3;
	vramp_pt = gVBPS_P_Init - 100e-3;
	vfrc = vramp_pt;
//	iFW_th = 20e-3;			// 20mA threshold to determine switching or not
	iFW_th = 5e-3;			// 5mA threshold to determine switching or not (request from DE)

	BPS_dvi->set_voltage(BPS_ch, vfrc, 		VOLT_10_RANGE);	// Starting search point
	wait.delay_10_us(30);

	imeas = FW_dvi->measure_average(5);

	if(DEBUG==1 && gDEBUG)
		printf("vBPS = %fV, iFW = %fmA \n", vfrc, imeas*1e3);

	if (imeas >iFW_th)			//Jump out of search loop if FW is sourcing (Device not switching)
	{	
		*vBPS_m = 0.0;	
		return;
	}

	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.2;
	while ((vstep >0.1) && (vfrc > 3.0) && (lcnt1< 200))
	{
		if (imeas <iFW_th)		// imeas is positive
		{	vfrc-=vstep;
			BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
			wait.delay_10_us(50);
			imeas = FW_dvi->measure_average(5);
			if(DEBUG==1 && gDEBUG)
				printf("vBPS = %fV, iFW = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
		}
		else			
		{	// Reset device and reduce searching step
			vfrc += 1.5* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
			//vfrc += 2.5* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
			vstep = 0.01;			// Fine search
			
			//FW set 0V (Need to take out sourcing supply when BPS at low voltage, else BPS go down slowly to 0V)
			FW_dvi->set_voltage(FW_ch,	0.0,		VOLT_10_RANGE);	 
			wait.delay_10_us(10);
			VBPS_ramp_up(0, gVBPS_P_Init+300e-3, 100e-3);
			//BPS_dvi->set_voltage(BPS_ch, 0,	VOLT_10_RANGE);	// Starting search point
			//wait.delay_10_us(20);
			//BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init+100e-3,	VOLT_10_RANGE);
			//wait.delay_10_us(50);
			imeas = FW_dvi->measure_average(5);				// FW should NOT be sourcing more than 50mA 

			 //FW set 9.5V (sourcing BPS before it reach VBPS-P)
//			FW_dvi->set_voltage(FW_ch,	9.5,		VOLT_10_RANGE);	 
			FW_dvi->set_voltage(FW_ch,	6.0,		VOLT_10_RANGE);	 
			wait.delay_10_us(10);

			VBPS_ramp_down(gVBPS_P_Init+100e-3, vfrc, 50e-3);
			//BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
			wait.delay_10_us(100);
			imeas = FW_dvi->measure_average(5);				// FW should NOT be sourcing more than 50mA 

			if(DEBUG==1 && gDEBUG)
				printf("vBPS = %fV, iFW = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);

			if (imeas >iFW_th)						//Ture if device is not switching
			{	
				*vBPS_m = -1.0;	
				return;
			}

			while ((imeas < iFW_th) && (vfrc >3.0) && (lcnt2<200) )
			{	vfrc-=vstep;
				BPS_dvi->set_voltage(BPS_ch, vfrc,	VOLT_10_RANGE);	// Starting search point
				wait.delay_10_us(10);
				imeas = FW_dvi->measure_average(5);
				if(DEBUG==1 && gDEBUG)
					printf("vBPS = %fV, iFW = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
							
				lcnt2++;
			}
		} 
		lcnt1 ++;
	}
	
	*vBPS_m = vfrc;	
}

void Find_VBP_vs_DrainCurrent()
{
	float vfrc[200] = {0.0}, vramp =0.0, vstep =0.0, vforce = 0.0;
	float imeas[200] = {0.0};
	float imeasure = 0;
	float tmeasure = 0;
	float tmeas[200] = {0.0};
	int FINE_SEARCH=1;
	int	lcnt =0, i=0;

	//if(DEBUG==1)
	//	printf("\nsearch_VBPP_Reset: SN=%i, Ton(6us)=%.2f us\n", SERIAL_NUM, imeas*1e6);
	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(30);
	imeasure = VPIN_ovi->measure_average(15);

	vforce = gVBPP_M_Init;	// Must be a lot less than Vbpm, seesm to have another threshold closer to Vbpm
	vramp = gVBPP_P_Init + 0.2;
	vstep = 0.01;
	FINE_SEARCH = 0;
	//lcnt = 0;

	//while (/*imeas > 250e-6 && */imeas < 420e-6 && vfrc > 2.0 && lcnt<100 )
	for (i=0; i<200; i++)
	{
		//lcnt += 1;
		vramp = vforce + 0.1;
		vforce -= vstep;

		//if(FINE_SEARCH)
		//	VBPP_ramp_down(vramp, vforce, 0.005);	// vstart, vstop, vstep - reduce undershoot
		//else
		//	VBPP_ramp_down(vramp, vforce, 0.1);	// vstart, vstop, vstep - reduce undershoot

		BPP_ovi->set_voltage(BPP_ch, vforce, 	RANGE_10_V);	// OVI_1_0
		wait.delay_10_us(50);
		BPP_ovi->set_meas_mode(BPP_ch,				OVI_MEASURE_VOLTAGE);
		wait.delay_10_us(20);
		vfrc[i] = BPP_ovi->measure_average(15);
		wait.delay_10_us(1);

		//BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init-0.05,	RANGE_10_V);	// OVI_1_0

		//// Check if switching
		//tmu_6->arm(); 
		//wait.delay_10_us(300);
		//tmeasure = tmu_6->read();
		//wait.delay_10_us(1);
		////if (tmeasure < 0.1e-6) break;
		//tmeas[i] = tmeasure;
		//wait.delay_10_us(1);

		imeasure = VPIN_ovi->measure_average(15);
		imeas[i] = imeasure;
		wait.delay_10_us(1);

	}

	char DumpFileName[4096];
	strcpy( DumpFileName,"e:\\dl4\\VBPPvsDrainCurrent.txt");
	dumparray.open( DumpFileName, ios::app );
	dumparray << "VBPP vs. Period" << endl;
	dumparray << "Point" << '\x009' << '\x009' << "VBPP" << '\x009' << '\x009'<< "Period" << '\x009' << '\x009'<< "Idrain"<< endl;
	for( i = 0; i < 200; i++)
	dumparray << i << '\x009' << '\x009' << vfrc[i] << '\x009' << '\x009' << tmeas[i] << '\x009' << '\x009' << imeas[i]<< endl;
	dumparray.close();
}

void search_VBPS_Reset(float *VBPS_Reset)
{
	float	vfrc =0.0, vstep =0.0;
	float	imeas =0.0, imeas_BPS=0.0;
	float	IBPS_sw=0;
	int		i=0, lcnt=0;
	float	vfrc_hi=0, vfrc_lo=0, tmeas=0;
Pulse pulse(PULSE_RISING_EDGE,10e-6);	
	vfrc = gVBPS_M-0.005;
	vstep = 10e-3;
	vfrc_hi = gVBPS_M-0.005;
	//VBPS_ramp_down(vfrc_hi, vfrc, 10e-3);	//Needs to ramp down to prevent undershoot
	//wait.delay_10_us(10);
	BPS_dvi->set_voltage(BPS_ch, vfrc, 	VOLT_10_RANGE);	// DVI_9_1
	wait.delay_10_us(50);
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);	// DVI_9_1  (8" EPSON require higher)
	BPS_dvi->set_voltage(BPS_ch, 5.0, 	VOLT_10_RANGE);	//MINNO
	wait.delay_10_us(50);
	ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_2nd_pulse_stop-1);
	wait.delay_10_us(10);
	if(LB_Rev>=5 )
	{
		wait.delay_10_us(30); //HL used to be 40. Adjust to 30 to fix repeatability failure
	}
	tmu_6->arm();						
	wait.delay_10_us(20);				
	tmeas = tmu_6->read(200e-6);
	//pulse.do_pulse();
	
	if (tmeas < 2e-6)
	{
		*VBPS_Reset = 0.0;
		return;
	}
	lcnt=0;
	while (tmeas>2e-6 && lcnt<200 && vfrc>2)
	{
		vfrc -= vstep;
		VBPS_ramp_down(vfrc_hi, vfrc, 10e-3);	//Needs to ramp down to prevent undershoot
		wait.delay_10_us(10);
		BPS_dvi->set_voltage(BPS_ch, vfrc, 	VOLT_10_RANGE);	// DVI_9_1
		wait.delay_10_us(20);
		//BPS_dvi->set_voltage(BPS_ch, gVBPS_final+0.1, 	VOLT_10_RANGE);	// DVI_9_1  (8" EPSON require higher)
		BPS_dvi->set_voltage(BPS_ch, 5.0, 	VOLT_10_RANGE);//MINNO
		wait.delay_10_us(20);
		if(g_TurretCB)
		{
			wait.delay_10_us(5);
		}
		ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_2nd_pulse_stop-1);
		wait.delay_10_us(10);
		tmu_6->arm();						
		if(g_TurretCB||LB_Rev>=5 )
		{
			wait.delay_10_us(25);
			tmeas = tmu_6->read(100e-6);
		}
		else
		{
			wait.delay_10_us(20);				
			tmeas = tmu_6->read(200e-6);
		}
		lcnt++;

	}

	*VBPS_Reset = vfrc;
}

void search_VBPP_Reset(float *VBPP_Reset)
{
	float vforce =0.0, vramp =0.0, vstep =0.0;
	float imeas =0.0;
	int FINE_SEARCH=0;
	int	lcnt =0;
	float imeasure = 0;
	float tmeasure = 0;

	//if(DEBUG==1)
	//	printf("\nsearch_VBPP_Reset: SN=%i, Ton(6us)=%.2f us\n", SERIAL_NUM, imeas*1e6);
	VPIN_ovi->set_meas_mode(VPIN_ch, OVI_MEASURE_CURRENT);
	wait.delay_10_us(30);
	imeasure = VPIN_ovi->measure_average(15);
	wait.delay_10_us(1);

	if (imeasure < 1.0e-6)		// Device should be switching here. Doing auto restart
	{	lcnt = 999;	
		*VBPP_Reset = 999.0;
	}
	else
		lcnt =0;

	if(DEBUG==1 && gDEBUG)
		printf("\nsearch_VBPP_Reset: SN=%i, Ton(6us)=%.2f us\n", SERIAL_NUM, imeasure*1e6);

	vforce = gVBPP_M_Init - 1.0;	// ~3.3V starting point, threshold is ~3.0V
	vstep = 0.01;
	FINE_SEARCH = 1;
	lcnt = 0;

	while (imeasure > 1.0e-6 && vforce > 2.0 && lcnt<200 )
	{
		lcnt += 1;
		vforce -= vstep;

		// JD ramp BPP down and look for a change in Vpin current
		BPP_ovi->set_voltage(BPP_ch, vforce, 	RANGE_10_V);	// OVI_1_0
		wait.delay_10_us(20);
		imeasure = VPIN_ovi->measure_average(15);
		//wait.delay_10_us(1);
		
		if(DEBUG==1 && gDEBUG)
			printf("FINE_SEARCH = %i, vfrc = %f V, Ton,Tmeas = %f us \n", FINE_SEARCH, vforce, imeasure*1e6);
	}

	*VBPP_Reset = vforce;
}

void search_CV_vFBth_AR(float *vFBth_AR_S)
{
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *							Secondary: vFBth_AR_S									  *
 *vFBth_AR_S:																		  *
 *	In order to find vFBth_AR_S, power up secondary with VFB at 0V, secondary is not SW.*
 *  Chip consumption on BPS pin should be 0.2mA. Ramp up VFB, until secondary starts  *
 *  switching, and chip consumption goes to 2mA.								      *
 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float ich_th=0, IBPS_nsw=0;
	float iBPS_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, lcnt2=0;
	int   db_cnt=0;

	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	IBPS_nsw = BPS_dvi->measure_average(5);	   // For debug (Positive current)

	lcnt1 =0;
	lcnt2 =0;
	vfrc = 0.05;
	ich_th = 0.0015;				// 1mA

	REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
	wait.delay_10_us(30);
	Force_Neg_Pulses_FW_DDD (0.5, -0.5);	   // Provide two neg pulses to start secondary switching

	imeas = BPS_dvi->measure();	// Device should not be switching
	if (imeas >ich_th)			//TURE if device is switching
	{	
		*vFBth_AR_S = 0.0;	
		return;
	}

	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.005;
	while ((vstep >0.003) && (vfrc < 1.0) && (lcnt1< 200))	
	{
		if (imeas <ich_th)		// imeas is positive
		{	
			vfrc+=vstep;

			REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
			wait.delay_10_us(10);
			Force_Neg_Pulses_FW_DDD (0.5, -0.5);	   // Provide two neg pulses to start secondary switching
			wait.delay_10_us(10);
			imeas = BPS_dvi->measure_average(5);
			if(DEBUG==1 && gDEBUG)
			{
				iBPS_meas[db_cnt] = imeas;
				Vfb_meas[db_cnt] = vfrc;
				db_cnt++;
			}

		}
		else// When FB pin goes above 
		{	// Reset device and reduce searching step
			vfrc -= 1.5* vstep;	    // Back down 1.5 step (Should be more than 0.2V - Comparator hysterisis)
			vstep = 0.001;			// Fine search

			REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
			wait.delay_10_us(20);

			// Need to reset device
			// But make sure only ramp one way to avoid reseting device everytime. 
			// It takes time to setup and apply two neg pulses. (5ms each)
			//VBPS_Power_Up(gVBPS_P_Init + 0.2);
			// Need to be out of test mode in order to read anti-fuses. 
			Power_Up_Secondary(Normal_Mode_S, gVBPS_P_Init + 0.05);			// Lower to 50mV per Alex for worst anti-fuse reading senario 
			Force_Neg_Pulses_FW_DDD (0.5, -0.5);	 // FW at 0V to keep switching noise low
			wait.delay_10_us(10);
			imeas = BPS_dvi->measure();				// Should be positive
			if (imeas >ich_th)						//TURE if device is switching
			{	
				*vFBth_AR_S = 0.9999;	// To avoid over range on OVI_2V_Range
				return;
			}
			while ((imeas < ich_th) && (vfrc <1.0) && (lcnt2<200) )
			{	
				vfrc+=vstep;

	
				REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
				REQ_ovi->set_voltage(REQ_ch, vfrc);
				wait.delay_10_us(10);
				Force_Neg_Pulses_FW_DDD (0.5, -0.5);	   // Provide two neg pulses to start secondary switching
				wait.delay_10_us(10);
				imeas = BPS_dvi->measure_average(5);
				lcnt2++;
			
				// For debug
				if(DEBUG==1 && gDEBUG)
				{
					iBPS_meas[db_cnt] = imeas;
					Vfb_meas[db_cnt] = vfrc;
					db_cnt++;
				}
			}
		} 
		lcnt1 ++;
	}
	
	*vFBth_AR_S = vfrc;	

	// Dump to file
	if(DEBUG==1 && gDEBUG)
	{
		char *Title ="\0";
		Title = "cnt	iBPS_meas	Vfb_meas";
		for(int i=0; i< db_cnt; i++)
			Dump_V_th_Data(Title, i, iBPS_meas[i], Vfb_meas[i], 0);
	}
	WAVE_NAME = "NoWaveName";

}

void search_CV_vFBth_AR_binary(float *vFBth_AR_S, float *AR_tFB_S)
{
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *							Secondary: vFBth_AR_S									  *
 *vFBth_AR_S:																		  *
 *  In order to find vFBth_AR_S, power up secondary with VFB at 0V, secondary is not SW.*
 *  use TMU to find if switching
 *	VFB=vfrc_lo, secondary is not SW.
 *  VFB=vfrc_hi, secondary is switching
 *  Reduce VFB until device stops switching
 *  Record threshold
 *  Increase VFB to switching level (above AR threshold)
 *	Loop until device starts switching again
 *  Record time until switching resumes
 *  Return threshold vFBth_AR_S                                                       *
 *  Return test time to finish searches AR_tFB_S
 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
	float imeas=0, vstep=0, vramp_pt=0;
	float ich_th=0, IBPS_sw=0;
	float iBPS_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt=0;
	float vfrc_hi=0, vfrc_lo=0, vmid=0;
	float tmeas=0, t_hi=0, t_lo=0, tmeas1=0;
	float starttime=0, stoptime=0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//////////

	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//wait.delay_10_us(10);

	REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		RANGE_2_V);	// OVI_1_2	(change from 1.25V to 1.0V  cx. 11/7/2016)
	wait.delay_10_us(100);

	//IBPS_sw = BPS_dvi->measure_average(15);	   // For debug (Positive current)
	if(g_TurretCB)
	{
		vfrc_hi=0.17; //HL changed from 0.15 to 0.17 to fix repeatability on Turret CB
	}
	else
	{
		vfrc_hi=0.15;
	}
	vfrc_lo=0.05;
	ich_th = 0.0015;				// 1mA
//	t_hi = 40e-6;
	t_hi = 55e-6;
	t_lo = 15e-6;

//////////

	//VFB=vfrc_lo
	REQ_ovi->set_voltage(REQ_ch, vfrc_lo, 		RANGE_2_V);	// OVI_1_2
	starttime = mytimer.GetElapsedTime();
	wait.delay_10_us(50);
	delay(1);
//////////

	// Device should not be switching
//	imeas = BPS_dvi->measure_average(15);	// Device should not be switching
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(20);				// Wait for TMU
	tmeas = tmu_6->read(200e-6);
//	if (imeas >ich_th)			//TRUE if device is switching
	if (tmeas > t_lo && tmeas < t_hi)			//TRUE if device is switching
	{	
		*vFBth_AR_S = 0.0;	
		starttime = -199;
		if (DEBUG && gDEBUG)
			printf("  search_CV_vFBth_AR_binary: Device should not be switching initially\n");
		return;
	}

	//VFB=vfrc_hi
	REQ_ovi->set_voltage(REQ_ch, vfrc_hi, 		RANGE_2_V);	// OVI_1_2
	if(g_TurretCB)
	{
		wait.delay_10_us(500); //HL changed timing as well for Turret CB
	}
	else
	{
		wait.delay_10_us(20);
	}

	// Device should be switching
	//	imeas = BPS_dvi->measure_average(15);	// Device should be switching
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(20);				// Wait for TMU
	tmeas = tmu_6->read(200e-6);
//	if (imeas >ich_th)			//TRUE if device is switching
	if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is switching
	{	
		*vFBth_AR_S = 0.9999;	// To avoid over range on OVI_2V_Range
		if (DEBUG && gDEBUG)
			printf("  search_CV_vFBth_AR_binary: Device should be switching\n");
		return;
	}

	//Reduce VFB until device stops switching
	while ( ((vfrc_hi-vfrc_lo) >= 0.001) && (lcnt < 15) )
	{
		vmid = (vfrc_hi+vfrc_lo)/2;		
		REQ_ovi->set_voltage(REQ_ch, vmid, 		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(50);
	//	imeas = BPS_dvi->measure_average(15);	// Device should be switching
		tmu_6->arm();						// Device doing auto-restart
		wait.delay_10_us(20);				// Wait for TMU
		tmeas = tmu_6->read(200e-6);
	//	if (imeas>ich_th)
		if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is not switching
		{
			vfrc_lo = vmid;
			if (DEBUG && gDEBUG)
				printf("  search_CV_vFBth_AR_binary LOOP: VFB= %.3fV, tmeas= %.1fus (Device NOT switching)\n",vmid , tmeas);
		}
		else
		{
			vfrc_hi = vmid;
			if (DEBUG && gDEBUG)
				printf("  search_CV_vFBth_AR_binary LOOP: VFB= %.3fV, tmeas= %.1fus (Device IS switching)\n",vmid , tmeas);
		}
			
		lcnt++;
	}

	//result
	*vFBth_AR_S = vmid;	
//////////

	//Increase VFB to switching level (above AR threshold)
	REQ_ovi->set_voltage(REQ_ch, vmid + 0.2, 		RANGE_2_V);	// OVI_1_2
	wait.delay_10_us(50);

	// Device should not be switching after AR threshold measurement
	//	imeas = BPS_dvi->measure_average(15);	// Device should be switching
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(20);				// Wait for TMU
	tmeas = tmu_6->read();
	if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is NOT switching
	{	
		*AR_tFB_S = 0.9999;	// To avoid over range on OVI_2V_Range
		if (DEBUG && gDEBUG)
			printf("  search_CV_vFBth_AR_binary: Device should not be switching after AR found\n");
		return;
	}
	lcnt=0;
	
	//Loop until device starts switching again
	while ((tmeas > t_lo && tmeas < t_hi)&& lcnt < 1000)	//1000 cnt => 1000 * 150us = 150ms
	{
		stoptime = mytimer.GetElapsedTime();
		tmu_6->arm(); 
		wait.delay_10_us(15);
		tmeas = tmu_6->read(150e-6); 
		lcnt++;
	}

//////////

	//save time until switching starts again
	*AR_tFB_S = (stoptime - starttime)*1e-6;

	if (DEBUG && gDEBUG)
		printf("  search_CV_vFBth_AR_binary: Device starts switching again after %.1f us \n",*AR_tFB_S);

}

void search_ISVth_TM18(float vIS_Start, float* ISvth_th)
{
	float vmeas=0, vstep=0, vramp_pt=0, tmeas=0, vmeas_High=0, vmeas_Low=0, tmeas_vLow=0, resolution=0.0;
	float vsr_th=0, IBPS_sw=0, iVO=0, imeas=0, i_ch=0;
	float iBPS_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, i=0, lcnt2=0;
	float vfrc_hi=0, vfrc_lo=0, vmid=0, vfrc_hi_Start=0, vfrc_lo_Start=0, min_vfrc=0, vfrc_ramp=0, vfrc_ramp_Start=0;
	float vstart=0.0, vfrc=0.0;
	bool  switching_status=false;
	float ISV_HYS=0, T_Low=0, T_High=0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	////////
		////Open_relay(K18);
		////Close_relay(K21);
		////Open_relay(K27);   //HL added to prevent repeatability failure on Turret CB
		////delay(4);
		////Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
		////wait.delay_10_us(150);  //more than 30us quiet time on FW signal
		////						//HL changed for Turret CB
		////Open_relay(K21);
		////Close_relay(K18);
		////delay(4);
	int min_dly=0, loop_dly=0;
	if(LB_Rev>=5 )
	{
		if ( gHcode == 105 || gHcode == 106	)		loop_dly	= 150;	//Change for B5pB4s by JD 6/20/17	
		else										loop_dly	= 20;	//Require delay to measure the correct timing (for Program Mode PU) for LB Rev E
	}
	else
	{
		loop_dly	= 20;	//Require delay to measure the correct timing (for Program Mode PU)
	}
	min_dly		= 10;
	ISV_HYS		= 15e-3;	//was 2mV before turret merge
	lcnt1		=0;
	lcnt2		=0;

	vfrc_hi = 1.00; //BRING BACK LATER
	vfrc_lo = 0.00;	//BRING BACK LATER

	vfrc_hi_Start = vfrc_hi;
	vfrc_lo_Start = vfrc_lo;
	vsr_th  = 4.0;				
			

	vstart	= vIS_Start;
	//i_ch = 1.8e-3;	//if greater than => device would be consider switching
	if(LB_Rev>=5 )
	{
		i_ch = 1.5e-3;
	}
	else
		i_ch = 1.8e-3;

	
	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		RANGE_2_V);	// OVI_1_2 
	FWC_dvi2k->set_voltage(FWC_ch, 1.0, 	VOLT_1_RANGE);	// DVI_21_0
	wait.delay_10_us(150); 	// SEC 8" B5B4 Parts need more delay
	if(gTrim_CCAR_S)
		delay(55);
						   
	imeas = BPS_dvi->measure_average(10);	   


	///DUT switches, then fails.
	if(imeas > i_ch)		
	{
		*ISvth_th = -99;
		if(DEBUG==1)
		{
			printf("\tvfrc = %.4f V, \tiBPS = %.4f mA \n", vfrc, imeas*1e3);
		}
		return;
	}


	vstep =0.020;
	resolution = 0.001;			// 1mV
	vfrc = 1.0 - vstep;
	while ((vstep >resolution) && (vfrc < 1.0) && (vfrc > 0.0) && (lcnt1< 2000) )
	{
	
		if (imeas < i_ch)		
		{	
			vfrc-=vstep;
			FWC_dvi2k->set_voltage(FWC_ch, vfrc, 	VOLT_1_RANGE);	
			if ( gHcode == 105 || gHcode == 106	)		wait.delay_10_us(150);	// SEC 8" B5B4 Parts need more delay
			else										wait.delay_10_us(20);	
			//if(gTrim_CCAR_S)
			//{
			//	Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
			//	wait.delay_10_us(100);  //more than 30us quiet time on FW signal
			//}
			imeas = BPS_dvi->measure_average(10);
			if(DEBUG==1)
			{
				printf("lcnt1 = %i, \tvstep = %.1f mV, \tvfrc = %.4f V, \tiBPS = %.4f mA \n", lcnt1, vstep*1000, vfrc, imeas*1e3);
			}
		}
		else
		{
			if(g_TurretCB)
			{
				vfrc += 5*vstep;
			}
			else
			{
				vfrc += 2*vstep;
			}
	
			vstep/=2.0;
			FWC_dvi2k->set_voltage(FWC_ch, vfrc + ISV_HYS, 	VOLT_1_RANGE);	
			wait.delay_10_us(loop_dly);	// SEC 8" B5B4 Parts need more delay
			if(gTrim_CCAR_S)
				delay(55);
			imeas = BPS_dvi->measure_average(10);
		
			if(DEBUG==1)
				printf("lcnt1 = %i, \tvstep = %.1f mV, \tvfrc = %.4f V, \tiBPS = %.4f mA \n", lcnt1, vstep*1000, vfrc+ISV_HYS, imeas*1e3);

			// Last step to ensure device switching. 
			if(vstep <resolution)
			{
				vfrc -= vstep*2;
				FWC_dvi2k->set_voltage(FWC_ch, vfrc - ISV_HYS, 	VOLT_1_RANGE);	
				wait.delay_10_us(loop_dly);	// SEC 8" B5B4 Parts need more delay
				//if(gTrim_CCAR_S)
				//{
				//	Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
				//	wait.delay_10_us(100);  //more than 30us quiet time on FW signal
				//}
				imeas = BPS_dvi->measure_average(10);
				
				if(DEBUG==1)
					printf("lcnt1 = %i, \tvstep = %.1f mV, \tvfrc = %.4f V, \tiBPS = %.4f mA \n", lcnt1, vstep*1000, vfrc, imeas*1e3);
				
				if (imeas > i_ch)
					vfrc = vfrc;
				else
					vfrc -= vstep;
			}
		}
		lcnt1++;
	}
	FWC_dvi2k->set_voltage(FWC_ch, vfrc, 	VOLT_1_RANGE);	
	FWC_dvi2k->set_meas_mode(FWC_ch,		DVI_MEASURE_VOLTAGE);
	delay(1);
	*ISvth_th = FWC_dvi2k->measure_average(10);
		
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void search_ISVth_Linear(float vIS_Start, float* ISvth_th)
{
	float vmeas=0, vstep=0, vramp_pt=0, tmeas=0, vmeas_High=0, vmeas_Low=0, tmeas_vLow=0, resolution=0.0;
	float vsr_th=0, IBPS_sw=0, iVO=0, imeas=0, i_ch=0;
	float iBPS_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, i=0, lcnt2=0, exit_loop = 0;
	float vfrc_hi=0, vfrc_lo=0, vmid=0, vfrc_hi_Start=0, vfrc_lo_Start=0, min_vfrc=0, vfrc_ramp=0, vfrc_ramp_Start=0;
	float vstart=0.0, vfrc=0.0;
	bool  switching_status=false;
	float ISV_HYS=0, T_Low=0, T_High=0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	////////

	int min_dly=0, loop_dly=0;
	if(LB_Rev>=5 )
	{
		loop_dly	= 5;	//Require delay to measure the correct timing (for Program Mode PU) for LB Rev E
	}
	else
	{
		loop_dly	= 20;	//Require delay to measure the correct timing (for Program Mode PU)
	}
	min_dly		= 10;
	ISV_HYS		= 15e-3;
	lcnt1		=0;
	lcnt2		=0;


	vfrc_hi = 1.00; //BRING BACK LATER
	vfrc_lo = 0.00;	//BRING BACK LATER

	vfrc_hi_Start = vfrc_hi;
	vfrc_lo_Start = vfrc_lo;
	vsr_th  = 4.0;				
			

	vstart	= vIS_Start;
	if(LB_Rev>=5 )
	{
		i_ch = 1.0e-3;
	}
	else
	{
		i_ch = 1.0e-3;
	}



	BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	REQ_ovi->set_voltage(REQ_ch, 1.0, 		RANGE_2_V);	// OVI_1_2 
	FWC_dvi2k->set_voltage(FWC_ch, 1.0, 	VOLT_1_RANGE);	// DVI_21_0
	wait.delay_10_us(200); 
						   
	imeas = BPS_dvi->measure_average(10);	   

	///DUT switches, then fails.
	if(imeas > i_ch)		
	{
		*ISvth_th = -99;
		return;
	}


	vstep =0.001; //1mV step size
	vfrc = 0.8;
	while( (vfrc > 0.6) && (exit_loop < 1))
	{
			
		vfrc-=vstep;
		FWC_dvi2k->set_voltage(FWC_ch, vfrc, 	VOLT_1_RANGE);	
		wait.delay_10_us(loop_dly);
		imeas = BPS_dvi->measure_average(10);

		if(imeas > i_ch)
		{
			exit_loop = 1;
		}	
	}
	

	FWC_dvi2k->set_voltage(FWC_ch, vfrc, 	VOLT_1_RANGE);	
	FWC_dvi2k->set_meas_mode(FWC_ch,		DVI_MEASURE_VOLTAGE);
	delay(1);
	*ISvth_th = FWC_dvi2k->measure_average(10);
		
}

void search_down_ARST_th( float* ARSTth)
{
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *							Secondary: ARSTth										  *
 *  (for silicon without tFB:ARdelay feature. All 1.81 secondary and before, some 2.0)*
 *ARSTth: This search is done on FB pin. 																		      *
 *	Secondary chip stops sending pulses to the primary chip when Vout (Or FB) voltage *
 *  drops below 2.75V ( or 2.75/4) while it’s operating in CC mode, so that the       *
 *  primary chip can go to auto-restart.																	  *
 *  Option 11 in 1.8 Secondary has this feature. Two out of four flavors of 1.81      *
 *  secondary chips will also have this function.									  *
 *  After secondary is power up in normal mode, BPS should be switching with 2mA      *
 *  current. When ARSTth is reached, BPS current should drop down to 0.2mA.           *   
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float resolution =0.0;
	float vstart=0.0;
	float ich_th=0, IBPS_sw=0;
	float iBPS_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	float tPeriod_meas[200] = {0.0};
	float iPV3_frc=0.0, vPV3_frc=0.0;
	int   lcnt1=0, lcnt2=0;
	int   db_cnt=0;
	float tmeas=0, t_hi=0, t_lo=0;
	int	  ARST_NM_respond_dly=0, ARST_TM_respond_dly=0, vFB_respond_dly=0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//wait.delay_10_us(10);
	//IBPS_sw = BPS_dvi->measure_average(5);	   // For debug (Positive current)

	ARST_NM_respond_dly =60;	//min 120ms wait require after hitting vFB_ARSTth to see part go into ARST 
	ARST_TM_respond_dly =20;	//min 12ms  wait require after hitting vFB_ARSTth to see part go into ARST 

	//If Power up in NM, use NM respond dly, otherwise use TM respond dly
	//vFB_respond_dly	=	ARST_NM_respond_dly;
	vFB_respond_dly	=	ARST_TM_respond_dly;

	lcnt1 =0;
	lcnt2 =0;
	ich_th = 0.001;				// 1mA
//	t_hi = 40e-6;
	t_hi = 55e-6;
	t_lo = 15e-6;

	vstart = 0.9;

	REQ_ovi->set_voltage(REQ_ch, vstart, 		RANGE_2_V);	// OVI_1_2
	wait.delay_10_us(30);
	tmu_6->arm(); 
	wait.delay_10_us(15);
	tmeas = tmu_6->read(150e-6);
	//imeas = BPS_dvi->measure();	// Device should be switching
//	if (imeas <ich_th)			//TURE if device is not switching
	if (tmeas < t_lo || tmeas > t_hi)			//TURE if device is not switching
	{	
		*ARSTth = 0.0;	
		return;
	}
	vstep =0.01;
	resolution = 0.001;			// 1mV
	vfrc = vstart + vstep;
	while ((vfrc > 0.1) && (lcnt1< 200) )
	{
//		if (imeas >ich_th)		// imeas is positive, Device switching
		if (tmeas > t_lo && tmeas < t_hi)		// imeas is positive, Device switching
		{	
//
			vfrc-=vstep;
			REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
			//wait.delay_10_us(20);
			delay(vFB_respond_dly);
			tmu_6->arm(); 
			wait.delay_10_us(15);
			tmeas = tmu_6->read(150e-6);
//			imeas = BPS_dvi->measure_average(5);
			if(DEBUG==1 && gDEBUG)
			{
				iBPS_meas[db_cnt] = imeas;
				Vfb_meas[db_cnt] = vfrc;
				tPeriod_meas[db_cnt] = tmeas;
				db_cnt++;
			}
		}
		//////else
		//////	{
		//////		vfrc += vstep;
		//////		vstep/=2.0;

		//////		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
		//////		wait.delay_10_us(20);
		//////		imeas = BPS_dvi->measure_average(5);

		//////		// Last step to ensure device stops switching. 
		//////		if(vstep <resolution)
		//////		{
		//////			vfrc -= vstep*2;
		//////			REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
		//////			wait.delay_10_us(20);
		//////			imeas = BPS_dvi->measure_average(5);
		//////		}
		//////	}
		lcnt1++;
	}

	*ARSTth = vfrc;	

	// Dump to file
	if(DEBUG==1 && gDEBUG)
	{
		char *Title ="\0";
		Title = "cnt	iBPS_meas	Vfb_meas	tPeriod";
		for(int i=0; i< db_cnt; i++)
			Dump_V_th_Data(Title, i, iBPS_meas[i], Vfb_meas[i], tPeriod_meas[i]);
	}

}

void search_Vout_ARST_th( float* ARSTth)
{
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *							Secondary: ARSTth										  *
 *ARSTth: This search is done on Vout pin. 																		      *
 *	Secondary chip stops sending pulses to the primary chip when Vout voltage drops   *
 *  below ARSTth
		(0,0) 63%				(gTrim_AR==0)
		(0,1) 35%				(gTrim_AR==1)
		(1,0) 90%				(gTrim_AR==2)
		(1,1) Fixed 3.45V Vout	(gTrim_AR==3)	//NOT apply inside this function

	Note1: This test could only be done with Linear ramp down and could not be done with
	       Binary search due to Vout is used for clocking at the same time in Testmode.

	Note2: if VR is trimmed for internal FB, then the above would reflect for Vout control instead of FB control
	(0,0)  External FB
	(0,1)  Internal FB 5V  Vout
	(1,0)  Internal FB 9V  Vout
	(1,1)  Internal FB 12V Vout
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	float imeas=0, vfrc=0, vstep=0, vramp_pt=0,vmeas=0;
	float resolution =0.0;
	float vstart=0.0;
	float ich_th=0, IBPS_sw=0;
	float iBPS_meas[200]	= {0.0};
	float Vo_meas[200]		= {0.0};
	float tmeas_Drain[200]	= {0.0};
	float iPV3_frc=0.0, vPV3_frc=0.0;
	int   lcnt1=0, lcnt2=0;
	int   db_cnt=0;
	float tmeas=0, t_lo=0, t_hi=0;

	lcnt1 =0;
	lcnt2 =0;
	ich_th = 0.001;				// 1mA
	t_hi=40e-6;
	t_lo=15e-6;
	

	REQ_ovi->set_current(REQ_ch, 0.1e-9,		RANGE_30_MA);	// FB float for Vout to take over control
	//REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// FB DO NOT SET TO 0V here for Vout to drive.  OVI will drive FB to 0V
	wait.delay_10_us(10);
	REQ_ovi->disconnect(REQ_ch);
	wait.delay_10_us(30); //need > 300us to settle
	//VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// Vout set 0V here will have SR signal switch from High to Low
	SR_dvi2k->set_voltage(SR_ch, 5.0, 	VOLT_5_RANGE);	// -.3 DVI_21_0
	SR_dvi2k->set_current(SR_ch, 2e-6,	RANGE_2_UA);			// -1.0
	wait.delay_10_us(10);
	SR_dvi2k->close_relay(CONN_FORCE1);
	SR_dvi2k->close_relay(CONN_SENSE1);
	delay(1);
	SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE);

	VO_dvi->set_voltage(VO_ch, vstart, 		VOLT_5_RANGE);	// DVI_9_0
	wait.delay_10_us(10);
	//Observe SR signal
	vmeas = SR_dvi2k->measure_average(5);	
	if(vmeas < 4.0)
	{
		*ARSTth = -99;
		return;
	}

	lcnt1=0;
	vfrc = vstart;
	while (vmeas > 0.5 && lcnt1 < 100)
	{
		vfrc -= vstep;
		VO_dvi->set_voltage(VO_ch, vfrc, 		VOLT_5_RANGE);	// DVI_9_0
		wait.delay_10_us(5);
		vmeas = SR_dvi2k->measure_average(5);	
		lcnt1++;
	}
	*ARSTth = vfrc;	
	
	REQ_ovi->connect(REQ_ch);	//Connect FB back to OVI after test done.
	wait.delay_10_us(10);

	// Dump to file
	if(DEBUG==1 && gDEBUG)
	{
		char *Title ="\0";
		Title = "cnt	tmeas_Drain	Vo_meas";
		for(int i=0; i< db_cnt; i++)
			Dump_V_th_Data(Title, i, tmeas_Drain[i], Vo_meas[i],0);
	}
}

void search_ARST_th_TM20( float* ARSTth)
{
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *							Secondary: ARSTth										  *
 *				(ONLY for 2.0 silicon with fixed AR feature on Vout pin)			  *
 *ARSTth: This search is done on Vout pin. 																		      *
 *	Secondary chip stops sending pulses to the primary chip when Vout voltage drops   *
 *  below 2.75V while it’s operating in CC mode, so that the primary chip can go to   *
 *  auto-restart.																	  *
 *  After secondary is power up in normal mode, BPS should be switching with 2mA      *
 *  current. When ARSTth is reached, BPS current should drop down to 0.2mA.           *   

		AR2,AR1 (AR threshold selection by trimming bits AR2,AR1)
		---------------------------------------------------------
		(0,0) 63%				(gTrim_AR==0)
		(0,1) 35%				(gTrim_AR==1)
		(1,0) 90%				(gTrim_AR==2)
		(1,1) Fixed 3.45V Vout	(gTrim_AR==3)

		Note: if VR is trimmed for internal FB, then the above would reflect for Vout control instead of FB control
		(0,0) External FB
		(0,1) Internal FB 5V  Vout
		(1,0) Internal FB 9V  Vout
		(1,1) Internal FB 12V Vout

 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	float vmeas=0, vstep=0, vramp_pt=0, tmeas=0, vmeas_High=0, vmeas_Low=0, tmeas_vLow=0, resolution=0.0;
	float vsr_th=0, IBPS_sw=0, iVO=0;
	float iBPS_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, i=0, lcnt2=0;
	float vfrc_hi=0, vfrc_lo=0, vmid=0, vfrc_hi_Start=0, vfrc_lo_Start=0, min_vfrc=0, vfrc_ramp=0, vfrc_ramp_Start=0;
	float vstart=0.0, vfrc=0.0;
	bool  switching_status=false;
	float CV_HYS=0, T_Low=0, T_High=0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	int min_dly=0, loop_dly=0;
	loop_dly	= 20;	//Require delay to measure the correct timing (for Program Mode PU)
	min_dly		= 10;
	CV_HYS		= 15e-3;
	lcnt1		=0;
	lcnt2		=0;

//	vsr_th  = 4.0;				
	vsr_th  = 2.5;		
	vstart  = 1.4;

	SR_dvi2k->set_voltage(SR_ch, 5.0, 	VOLT_5_RANGE);	// -.3 DVI_21_0
	SR_dvi2k->set_current(SR_ch, 2e-6,	RANGE_2_UA);			// -1.0
	wait.delay_10_us(10);
	SR_dvi2k->close_relay(CONN_FORCE1);
	SR_dvi2k->close_relay(CONN_SENSE1);
	delay(4);
	SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE);
	REQ_ovi->set_voltage(REQ_ch, vstart, 		RANGE_2_V);	// OVI_1_2
	wait.delay_10_us(10);	

	vmeas = SR_dvi2k->measure_average(5);	// SR should stay High

	if(vmeas < 4.0)
	{
		*ARSTth = -99;
		return;
	}

	vstart = 1;
	vstep =0.020;
	resolution = 0.001;			// 1mV
	vfrc = vstart - vstep;
	
	while ((vstep >resolution) && (vfrc < 1.90) && (vfrc > 0) && (lcnt1< 200) )
	{
		if (vmeas > vsr_th)		// imeas is positive, Device switching
		{	
			REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
			wait.delay_10_us(loop_dly);
			vmeas = SR_dvi2k->measure_average(5);	
			vfrc-=vstep;
			if(DEBUG==1 && gDEBUG)
			{
				printf("lcnt1 = %i, \tvstep = %.1f mV, \tvfrc = %.4f V, \tvSR = %.4f V \n", lcnt1, vstep*1000, vfrc-vstep, vmeas);
			}
		}
		else
		{
			vfrc += 2*vstep;
			vstep/=2.0;

			REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
			wait.delay_10_us(loop_dly);
			vmeas = SR_dvi2k->measure_average(5);	
			if(DEBUG==1 && gDEBUG)
				printf("lcnt1 = %i, \tvstep = %.1f mV, \tvfrc = %.4f V, \tvSR = %.4f V \n", lcnt1, vstep*1000, vfrc-vstep, vmeas);

			// Last step to ensure device stops switching. 
			if(vstep <resolution)
			{
				vfrc -= vstep*2;
				REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
				wait.delay_10_us(loop_dly);
				vmeas = SR_dvi2k->measure_average(5);
				if(DEBUG==1 && gDEBUG)
					printf("lcnt1 = %i, \tvstep = %.1f mV, \tvfrc = %.4f V, \tvSR = %.4f V \n", lcnt1, vstep*1000, vfrc-vstep, vmeas);
			}
		}
		lcnt1++;
	}

	*ARSTth = vfrc;	
	

	// Dump to file
	//if(DEBUG==1)
	//{
	//	char *Title ="\0";
	//	Title = "cnt	iBPS_meas	Vo_meas";
	//	for(int i=0; i< db_cnt; i++)
	//		Dump_V_th_Data(Title, i, iBPS_meas[i], Vo_meas[i],0);
	//}
//	DEBUG = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//HQL added this search function for Vout Threshold using TM13 and TM14.
////////////////////////////////////////////////////////////////////////////////////////////////
void search_Vout_th_TM(float VSTART, float *Vout_th, float *Vout_th_minus)
{
	float vmeas=0.0, ifrc=0.0;
	float resolution =0.0;
	float vsr_th=0.0, IBPS_sw=0.0;
	int   lcnt=0, lcnt1=0, lcnt2=0;

	float vstart=0.0, vrange =0.0;
	float vstep =0.0, vfrc =0.0;

	float VSR_meas[300]={0.0}, Vo_meas[300]={0,0};
	int   db_cnt=0;

	lcnt1 =0;
	lcnt2 =0;
	vsr_th = 2.0;				// 2V
	vstart = VSTART;
	
	SR_dvi2k->set_meas_mode(SR_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(10);
	vmeas = SR_dvi2k->measure_average(5);
	if(vstart  <= 9.0)
	{
		VO_dvi->set_voltage(VO_ch, vstart, 		VOLT_10_RANGE);	// OVI_1_2
		vrange =9.9;
	}
	else if(vstart  <= 19.0)
	{
		VO_dvi->set_voltage(VO_ch, vstart, 		VOLT_20_RANGE);	// OVI_1_2
		vrange =19.9;
	}
	else
	{
		VO_dvi->set_voltage(VO_ch, vstart, 		VOLT_50_RANGE);	// OVI_1_2
		vrange =49.9;
	}
	wait.delay_10_us(50);

	vmeas = SR_dvi2k->measure_average(5);	// SR should be High
	if(DEBUG==1)
	{
		printf("vstart=%f V, FB=0.8V, V_SR=%.2f V \n", vstart, vmeas);
	}

	if (vmeas <vsr_th)			//TRUE if SR is not High
	{	
		*Vout_th = 0.0;	
		return;
	}

	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep =0.1;
	resolution = 0.001;			// 1mV
	vfrc = vstart + vstep;

	while ((vfrc < vrange) && (lcnt1< 100) )
	{
		if (vmeas >vsr_th)		// SR is High
		{	
			vfrc+=vstep;
			if(vfrc  < 9.0)
			{
				VO_dvi->set_voltage(VO_ch, vfrc, 	VOLT_10_RANGE);	// DVI_9_0
				vrange =9.9;
			}
			else if(vfrc  < 19.0)
			{
				VO_dvi->set_voltage(VO_ch, vfrc, 	VOLT_20_RANGE);	// DVI_9_0
				vrange =19.9;
			}
			else 
			{
				VO_dvi->set_voltage(VO_ch, vfrc, 	VOLT_50_RANGE);	// DVI_9_0
				vrange =49.9;
			}
			wait.delay_10_us(50);
		
			vmeas = SR_dvi2k->measure_average(5);

			if(DEBUG==1)
			{
				printf("vstart=%f V, FB=0.8V, VSR=%.2f V \n", vfrc, vmeas);
				VSR_meas[db_cnt] = vmeas;
				Vo_meas[db_cnt] = vfrc;
				db_cnt++;
			}
		}
		lcnt1++;
	}

	*Vout_th = vfrc;	
	vfrc = vfrc+0.5;

	if(vfrc  <= 9.0)
	{
		VO_dvi->set_voltage(VO_ch, vfrc, 		VOLT_10_RANGE);	// OVI_1_2
		vrange =9.9;
	}
	else if(vfrc  <= 19.0)
	{
		VO_dvi->set_voltage(VO_ch, vfrc, 		VOLT_20_RANGE);	// OVI_1_2
		vrange =19.9;
	}
	else
	{
		VO_dvi->set_voltage(VO_ch, vfrc, 		VOLT_50_RANGE);	// OVI_1_2
		vrange =49.9;
	}
	wait.delay_10_us(50);

	vmeas = SR_dvi2k->measure_average(5);	// SR should stay low

	if (vmeas >vsr_th)	// TRUE if SR is Low
	{	
		*Vout_th = 0.0;	
		return;
	}
	while ((vfrc < vrange) && (lcnt2< 100) )
	{
		if (vmeas <vsr_th)		// SR is Low
		{	
			vfrc-=vstep;
			if(vfrc  < 9.0)
			{
				VO_dvi->set_voltage(VO_ch, vfrc, 	VOLT_10_RANGE);	// DVI_9_0
				vrange =9.9;
			}
			else if(vfrc  < 19.0)
			{
				VO_dvi->set_voltage(VO_ch, vfrc, 	VOLT_20_RANGE);	// DVI_9_0
				vrange =19.9;
			}
			else 
			{
				VO_dvi->set_voltage(VO_ch, vfrc, 	VOLT_50_RANGE);	// DVI_9_0
				vrange =49.9;
			}
			wait.delay_10_us(50);
		
			vmeas = SR_dvi2k->measure_average(5);

			if(DEBUG==1)
			{
				printf("vstart=%f V, FB=0.8V, VSR=%.2f V \n", vfrc, vmeas);
				VSR_meas[db_cnt] = vmeas;
				Vo_meas[db_cnt] = vfrc;
				db_cnt++;
			}
		}
		lcnt2++;
	}

	*Vout_th_minus = vfrc;	

	// Dump to file
	if(DEBUG==1)
	{
		char *Title ="\0";
		Title = "cnt	VSR_meas	Vo_meas";
		for(int i=0; i< db_cnt; i++)
			Dump_V_th_Data(Title, i, VSR_meas[i], Vo_meas[i],0);
		WAVE_NAME = "NoWaveName";
	}

	////////Power down
	//////pv3_4->set_current(0.0);				// auto range
	//////pv3_4->set_voltage(0, RANGE_3_V);
	//////pv3_4->drive_off();
	//////wait.delay_10_us(10);
	//////pv3_4->charge_on();	
	//////VO_dvi->set_voltage(VO_ch, 0.0, 	VOLT_20_RANGE);	// DVI_9_0 
	//////FWC_dvi2k->set_voltage(FWC_ch, 0.0, VOLT_1_RANGE);	// DVI_21_0  auto range
	

}

void search_Vclamp_10pct_th_VO( float* Vclamp, float *Iclamp)
{
/**************************************************************************************
 *							Secondary: Vclamp_10pct_S								  *
 *Vclamp_10pct_S:																	  *
 *	After Vclamp_2pct_S is found, continue ramping up FB pin voltage until Vout pin   *
 *  current jumps to  ~50mA from ~10mA.										  		  *
 **************************************************************************************/
	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float ich_th=0, IVout_below_10pct_clamp=0;
	float iVclamp_th =0.0;
	float iVout_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, lcnt2=0;
	int   db_cnt=0;


	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_meas_mode(VO_ch,	DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	IVout_below_10pct_clamp = VO_dvi->measure_average(5);	   // For debug (Positive current)

	lcnt1 =0;
	lcnt2 =0;
	vfrc = gVcl2pct_QC2VO_S+0.05;
	iVclamp_th = 0.010;			// 50mA threshold. From 2%Vclamp to 10%Vclamp, Vout pin current should jump from ~10mA to >50mA
	if (fabs(vfrc) <10.0)
		VO_dvi->set_voltage(VO_ch, vfrc, 		VOLT_10_RANGE);	
	else
		VO_dvi->set_voltage(VO_ch, vfrc, 		AUTORANGE);	
	wait.delay_10_us(30);

	imeas = VO_dvi->measure_average(5);		
	if (imeas >iVclamp_th)			//TRUE if Vout current is already above iVclamp threshold
	{	
		*Vclamp = 0.0;	
		return;
	}

	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.005;
	while ((imeas <iVclamp_th) && (vfrc < 9.99) && (lcnt1< 200))	
	{
		vfrc+=vstep;
		VO_dvi->set_voltage(VO_ch, vfrc, 		VOLT_10_RANGE);	
		wait.delay_10_us(10);
		imeas = VO_dvi->measure_average(5);
		//printf(" Step = %i,	V_VO = %.4f V.	i_VO = %.4f mA\n", lcnt1, vfrc, imeas*1e3);
		if(DEBUG==1 && gDEBUG)
		{
			iVout_meas[db_cnt] = imeas;
			Vfb_meas[db_cnt] = vfrc;
			db_cnt++;
		}
		lcnt1++;
	}

	*Vclamp = vfrc;	

	// Find Iclamp after Vclamp is found
//	if((*Vclamp  + 0.1)<2.0)
	VO_dvi->set_voltage(VO_ch, vfrc+vstep, 		VOLT_10_RANGE);	
	wait.delay_10_us(20);
	*Iclamp = VO_dvi->measure_average(5);

	// Dump to file
	if(DEBUG==1 && gDEBUG)
	{
		char *Title ="\0";
		Title = "cnt	iVout_meas	Vfb_meas";
		for(int i=0; i< db_cnt; i++)
			Dump_V_th_Data(Title, i, iVout_meas[i], Vfb_meas[i],0);
		WAVE_NAME = "NoWaveName";
	}
}

void search_Vclamp_2pct_th( float* Vclamp, float *Iclamp)
{
/**************************************************************************************
 *							Secondary: Vclamp_2pct_S								  *
 *Vclamp_2pct_S:																	  *
 *	Power up secondary and make it switch without involving primary. Ramp up FB pin   *
 *  voltage until Vout pin current increases.									      *
 **************************************************************************************/
	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float ich_th=0, IVout_below_2pct_clamp=0;
	float iVclamp_th =0.0;
	float iVout_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, lcnt2=0;
	int   db_cnt=0, loop_dly=0;

	loop_dly = 10;

	//ESPON sizex8 device measures different current @switching when we measure at differen testers.  TMT5~0.6mA, TMT81~0.2mA
	//(Manually increase vBPS from vPlus to vPlus + 100mV and notice the current increase from 0.2mA to 4mA easily)
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init+100e-3, 	VOLT_10_RANGE);	// Secondary vBPS_plus (zcx added for ESPON FAB)
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);			// Secondary vBPS_plus (zcx added for ESPON FAB)


	//BPS_dvi->set_meas_mode(BPS_ch,	DVI_MEASURE_CURRENT);
	//wait.delay_10_us(10);

	//ich_th = 1.0e-3;	//1mA

	//imeas = BPS_dvi->measure_average(5);	   // Device should be switching here (Positive current)
	//if(imeas <ich_th)			// TURE If device didn't power up properly and is not switching
	//{
	//	*Vclamp = 0.0;	
	//	return;
	//}
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	
	VO_dvi->set_current(VO_ch,	30.0e-3,	RANGE_30_MA);	
	VO_dvi->set_meas_mode(VO_ch,	DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	IVout_below_2pct_clamp = VO_dvi->measure_average(5);	   // For debug (Positive current)

	lcnt1 =0;
	lcnt2 =0;
	vfrc = gCV_FB_S;
	//vfrc = gCV_FB_S;
//	iVclamp_th = 0.002;			// 2mA
	iVclamp_th = 0.001;		// 1.5mA

	if(fabs(vfrc) > 2) vfrc = 0;  //This is to prevent Over Range pop-up error
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
	wait.delay_10_us(30);

	imeas = VO_dvi->measure_average(5);		
	if (imeas >iVclamp_th)			//TURE if Vout current is already above iVclamp threshold
	{	
		*Vclamp = 0.0;	
		return;
	}

	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.001;
	while ((imeas <iVclamp_th) && (vfrc < 1.99) && (lcnt1< 200))	
	{
		vfrc+=vstep;
		if(fabs(vfrc) > 2) vfrc = 0;  //This is to prevent Over Range pop-up error
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(loop_dly);
		imeas = VO_dvi->measure_average(5);
		//printf(" Step = %i,	V_FB = %.4f V.	i_VO = %.4f mA\n", lcnt1, vfrc, imeas*1e3);
		if(DEBUG==1 && gDEBUG)
		{
			iVout_meas[db_cnt] = imeas;
			Vfb_meas[db_cnt] = vfrc;
			db_cnt++;
		}
		lcnt1++;
	}

	*Vclamp = vfrc;	

	// Find Iclamp after Vclamp is found
//	if ((*Vclamp  + 0.05)<2.0)
	if (fabs(*Vclamp+vstep)<2.0)
		REQ_ovi->set_voltage(REQ_ch, *Vclamp+vstep, 		VOLT_2_RANGE);	// OVI_1_2
	else
		REQ_ovi->set_voltage(REQ_ch, *Vclamp+vstep,		AUTORANGE);

	wait.delay_10_us(80);
	wait.delay_10_us(20);
	*Iclamp = VO_dvi->measure_average(5);

	// Dump to file
	if(DEBUG==1 && gDEBUG)
	{
		char *Title ="\0";
		Title = "cnt	iVout_meas	Vfb_meas";
		for(int i=0; i< db_cnt; i++)
			Dump_V_th_Data(Title, i, iVout_meas[i], Vfb_meas[i],0);
		WAVE_NAME = "NoWaveName";
	}

}

void search_Vclamp_2pct_th_QC3( float* Vclamp, float *Iclamp)
{
/**************************************************************************************
 *							Secondary: Vclamp_2pct_S								  *
 *Vclamp_2pct_S:																	  *
 *	Power up secondary and make it switch without involving primary. Ramp up FB pin   *
 *  voltage until Vout pin current increases.									      *
 **************************************************************************************/
	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float ich_th=0, IVout_below_2pct_clamp=0;
	float iVclamp_th =0.0;
	float iVout_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, lcnt2=0;
	int   db_cnt=0, loop_dly=0;
	float vout=0;

	loop_dly = 10;

	//ESPON sizex8 device measures different current @switching when we measure at differen testers.  TMT5~0.6mA, TMT81~0.2mA
	//(Manually increase vBPS from vPlus to vPlus + 100mV and notice the current increase from 0.2mA to 4mA easily)
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init+100e-3, 	VOLT_10_RANGE);	// Secondary vBPS_plus (zcx added for ESPON FAB)
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);			// Secondary vBPS_plus (zcx added for ESPON FAB)

	BPS_dvi->set_meas_mode(BPS_ch,	DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	ich_th = 1.0e-3;

	imeas = BPS_dvi->measure_average(5);	   // Device should be switching here (Positive current)
	//if(imeas <ich_th)			// TURE If device didn't power up properly and is not switching
	//{
	//	*Vclamp = 0.0;	
	//	return;
	//}
	VO_dvi->set_voltage(VO_ch, 4.5, 		VOLT_10_RANGE);
	VO_dvi->set_current(VO_ch,	30.0e-3,	RANGE_30_MA);	
	VO_dvi->set_meas_mode(VO_ch,	DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	IVout_below_2pct_clamp = VO_dvi->measure_average(5);	   // For debug (Positive current)

	lcnt1 =0;
	lcnt2 =0;
	vout=4.5;
	vfrc = vout/4;
	iVclamp_th = 0.002;			// 2mA
	if (fabs(vfrc) <2.0)
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
	else
		REQ_ovi->set_voltage(REQ_ch, vfrc,		AUTORANGE);
	wait.delay_10_us(30);

	imeas = VO_dvi->measure_average(5);		
	if (imeas >iVclamp_th)			//TURE if Vout current is already above iVclamp threshold
	{	
		*Vclamp = 0.0;	
		return;
	}

	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.01;
	while ((imeas <iVclamp_th) && (vfrc < 1.99) && (vout < 9.99) && (lcnt1< 200))	
	{
		vout+=vstep;
		vfrc=vout/4;
		VO_dvi->set_voltage(VO_ch, vout, 		VOLT_10_RANGE);
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(loop_dly);
		imeas = VO_dvi->measure_average(5);
		//printf(" Step = %i,	V_FB = %.4f V.,	VOUT = %.2f V.,	i_VO = %.4f mA\n", lcnt1, vfrc, vout, imeas*1e3);
		if(DEBUG==1 && gDEBUG)
		{
			iVout_meas[db_cnt] = imeas;
			Vfb_meas[db_cnt] = vfrc;
			db_cnt++;
		}
		lcnt1++;
	}

	//*Vclamp = vfrc;	
	*Vclamp = vout;	

	// Find Iclamp after Vclamp is found
	VO_dvi->set_voltage(VO_ch, vout+vstep, 		VOLT_10_RANGE);
//	if ((*Vclamp  + 0.05)<2.0)
	if (fabs((vout+vstep)/4)<2.0)
		REQ_ovi->set_voltage(REQ_ch, (vout+vstep)/4, 		VOLT_2_RANGE);	// OVI_1_2
	else
		REQ_ovi->set_voltage(REQ_ch, (vout+vstep)/4,		AUTORANGE);

	wait.delay_10_us(80);
	wait.delay_10_us(20);
	*Iclamp = VO_dvi->measure_average(5);

	// Dump to file
	if(DEBUG==1 && gDEBUG)
	{
		char *Title ="\0";
		Title = "cnt	iVout_meas	Vfb_meas";
		for(int i=0; i< db_cnt; i++)
			Dump_V_th_Data(Title, i, iVout_meas[i], Vfb_meas[i],0);
		WAVE_NAME = "NoWaveName";
	}

}


void search_Vclamp_10pct_th_QC3( float* Vclamp, float *Iclamp)
{
/**************************************************************************************
 *							Secondary: Vclamp_10pct_S								  *
 *Vclamp_10pct_S:																	  *
 *	After Vclamp_2pct_S is found, continue ramping up FB pin voltage until Vout pin   *
 *  current jumps to  ~50mA from ~10mA.										  		  *
 **************************************************************************************/
	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float ich_th=0, IVout_below_10pct_clamp=0;
	float iVclamp_th =0.0;
	float iVout_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, lcnt2=0;
	int   db_cnt=0;
	float vout=0;

	// Set FB voltage to 6% above CV to ensure device is beyond 2%Vclamp. 
	// 125C problem. At 2%Vclamp, BPS is still switching slightly. 
	//if ((gCV_S * 1.06) <2.0)
	//	REQ_ovi->set_voltage(REQ_ch, gCV_S * 1.06, 		RANGE_2_V);	// OVI_1_2
	//else
	//	REQ_ovi->set_voltage(REQ_ch, gCV_FB_TARGET*1.06);

	//BPS_dvi->set_meas_mode(BPS_ch,	DVI_MEASURE_CURRENT);
	//wait.delay_10_us(40);

	//ich_th = 0.0015;						   // BPS Switching vs None Switching supply current Current threshold
	//imeas = BPS_dvi->measure_average(5);	   // Device is not switching here (Positive current)
	//if(imeas >ich_th)						   // TURE If device is switching. Device should be off from the Vclamp_2pct_S test
	//{
	//	*Vclamp = 0.0;	
	//	return;
	//}

	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_meas_mode(VO_ch,	DVI_MEASURE_CURRENT);
	wait.delay_10_us(10);

	IVout_below_10pct_clamp = VO_dvi->measure_average(5);	   // For debug (Positive current)

	lcnt1 =0;
	lcnt2 =0;
	vout = (gVclamp_2pct_S_QC3+0.05);
	vfrc = (gVclamp_2pct_S_QC3+0.05)/4;
	iVclamp_th = 0.010;			// 50mA threshold. From 2%Vclamp to 10%Vclamp, Vout pin current should jump from ~10mA to >50mA
	//VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_10_RANGE);
	if (fabs(vfrc) <2.0)
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
	else
		REQ_ovi->set_voltage(REQ_ch, vfrc,		AUTORANGE);
	wait.delay_10_us(30);

	imeas = VO_dvi->measure_average(5);		
	if (imeas >iVclamp_th)			//TURE if Vout current is already above iVclamp threshold
	{	
		*Vclamp = 0.0;	
		return;
	}

	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.01;
	while ((imeas <iVclamp_th) && (vfrc < 1.99) && (vout < 9.99) && (lcnt1< 200))	
	{
		vout+=vstep;
		vfrc=vout/4;
		VO_dvi->set_voltage(VO_ch, vout, 		VOLT_10_RANGE);
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(10);
		imeas = VO_dvi->measure_average(5);
		//printf(" Step = %i,	V_FB = %.4f V.,	VOUT = %.2f V.,	i_VO = %.4f mA\n", lcnt1, vfrc, vout, imeas*1e3);
		if(DEBUG==1 && gDEBUG)
		{
			iVout_meas[db_cnt] = imeas;
			Vfb_meas[db_cnt] = vfrc;
			db_cnt++;
		}
		lcnt1++;
	}

	//*Vclamp = vfrc;
	*Vclamp = vout;	

	// Find Iclamp after Vclamp is found
	VO_dvi->set_voltage(VO_ch, vout+vstep, 		VOLT_10_RANGE);
//	if((*Vclamp  + 0.1)<2.0)
	if(fabs((vout+vstep)/4 )<2.0)
		REQ_ovi->set_voltage(REQ_ch, (vout+vstep)/4, 		RANGE_2_V);	// OVI_1_2
	else
		REQ_ovi->set_voltage(REQ_ch, (vout+vstep)/4,		AUTORANGE);
	wait.delay_10_us(20);
	wait.delay_10_us(80);
	*Iclamp = VO_dvi->measure_average(5);

	// Dump to file
	if(DEBUG==1 && gDEBUG)
	{
		char *Title ="\0";
		Title = "cnt	iVout_meas	Vfb_meas";
		for(int i=0; i< db_cnt; i++)
			Dump_V_th_Data(Title, i, iVout_meas[i], Vfb_meas[i],0);
		WAVE_NAME = "NoWaveName";
	}
	
}

void search_Vclamp_20pct_th_QC2( float* Vclamp)
{
/**************************************************************************************
 *							Secondary: Vclamp_10pct_S	QC2.0						  *
 *Vclamp_10pct_S:																	  *
 *	After Vclamp_2pct_S is found, continue ramping up FB pin voltage until Vout pin   *
 *  current jumps to  ~50mA from ~10mA.										  		  *
 **************************************************************************************/
	float tmeas=0, vfrc=0, vstep=0, vstart=0;
	float iVclamp_th =0.0;
	float iVout_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, lcnt2=0;
	int   db_cnt=0;
	float vout=0;

	// If CV is not found, dont do this.
	if (gCV_FB_S > 2 || gCV_FB_S < 0)
		return;

	vstart = gCV_FB_S*1.1;	// Set FB starting at 10% above CV.
	vstep = 5e-3;

	REQ_ovi->set_voltage(REQ_ch, vstart,	RANGE_2_V);
	wait.delay_10_us(30);

	tmu_6->arm(); 
	wait.delay_10_us(30);
	tmeas = tmu_6->read(30e-6);
	if (tmeas > 0)			//TRUE if FB is still below the CV threshold
	{	
		*Vclamp = 0.0;	
		return;
	}

	vfrc = vstart;
	// Looking for non-switching to switching from Drain.
	// Near the 20% Clamp, secondary will try to send latch-off request and Drain response by switching once then stop
	// but near the threshold, the first few requests might fail. So continue to ramp up FB in the 2nd loop below.
	while ((tmeas <= 0 || tmeas > 50e-6) && (vfrc < 1.99) && (lcnt1< 200))	
	{
		vfrc+=vstep;
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(10);
		tmu_6->arm(); 
		wait.delay_10_us(30);
		tmeas = tmu_6->read(30e-6);
		//printf(" Step = %i,	V_FB = %.4f V.,	tmeas = %.4f uS\n", lcnt1, vfrc, tmeas*1e6);
		lcnt1++;
	}
	// This 2nd loop is to look for the switching to non-switching to find the right threshold.
	// If the right threshold is reach, drain should switch ONLY ONCE and then stop.
	while ((tmeas > 0 && tmeas < 50e-6) && (vfrc < 1.99) && (lcnt2< 200))	
	{
		vfrc+=vstep;
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(10);
		tmu_6->arm(); 
		wait.delay_10_us(30);
		tmeas = tmu_6->read(30e-6);
		//printf(" Step = %i,	V_FB = %.4f V.,	tmeas = %.4f uS\n", lcnt1, vfrc, tmeas*1e6);
		lcnt2++;
	}
	// Bring back FB to make sure Primary not switching
	REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		RANGE_2_V);	// OVI_1_2
	wait.delay_10_us(10);
	tmu_6->arm(); 
	wait.delay_10_us(30);
	tmeas = tmu_6->read(30e-6);
	if (tmeas > 0)
	{
		*Vclamp = -1.0;
		return;
	}
		
	*Vclamp = vfrc;
		
}

void search_Vclamp_20pct_th_QC3( float* Vclamp)
{
/**************************************************************************************
 *							Secondary: Vclamp_20pct_S QC3.0							  *
 *Vclamp_10pct_S:																	  *
 *	After Vclamp_2pct_S is found, continue ramping up FB pin voltage until Vout pin   *
 *  current jumps to  ~50mA from ~10mA.										  		  *
 **************************************************************************************/
	float tmeas=0, vfrc=0, vstep=0, vstart=0, vout=0;
	float ich_th=0, IVout_below_10pct_clamp=0;
	float iVclamp_th =0.0;
	float iVout_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt1=0, lcnt2=0;
	int   db_cnt=0;

	// If CV is not found, dont do this.
	if (gCV_FB_S > 2 || gCV_FB_S < 0)
		return;

	vstart = gCV_FB_S*1.1;	// Set FB starting at 10% above CV.
	vstep = 5e-3;

	vout = vstart*4;
	vfrc = vstart;

	VO_dvi->set_voltage(VO_ch, vout, 		VOLT_10_RANGE);
	REQ_ovi->set_voltage(REQ_ch, vfrc,	RANGE_2_V);
	wait.delay_10_us(30);

	tmu_6->arm(); 
	wait.delay_10_us(30);
	tmeas = tmu_6->read(30e-6);
	if (tmeas > 0)			//TRUE if FB is still below the CV threshold
	{	
		*Vclamp = 0.0;	
		return;
	}
	// Looking for non-switching to switching from Drain.
	// Near the 20% Clamp, secondary will try to send latch-off request and Drain response by switching once then stop
	// but near the threshold, the first few requests might fail. So continue to ramp up FB in the 2nd loop below.
	while ((tmeas <= 0 || tmeas > 50e-6) && (vfrc < 1.99) && (lcnt1< 200))	
	{
		vout+=vstep;
		vfrc =vout/4;
		VO_dvi->set_voltage(VO_ch, vout, 		VOLT_10_RANGE);
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(10);
		tmu_6->arm(); 
		wait.delay_10_us(30);
		tmeas = tmu_6->read(30e-6);
		//printf(" Step = %i,	V_FB = %.4f V.,	tmeas = %.4f uS\n", lcnt1, vfrc, tmeas*1e6);
		lcnt1++;
	}
	// This 2nd loop is to look for the switching to non-switching to find the right threshold.
	// If the right threshold is reach, drain should switch ONLY ONCE and then stop.
	while ((tmeas > 0 && tmeas < 50e-6) && (vfrc < 1.99) && (lcnt2< 200))	
	{
		vout+=vstep;
		vfrc =vout/4;
		VO_dvi->set_voltage(VO_ch, vout, 		VOLT_10_RANGE);
		REQ_ovi->set_voltage(REQ_ch, vfrc, 		RANGE_2_V);	// OVI_1_2
		wait.delay_10_us(10);
		tmu_6->arm(); 
		wait.delay_10_us(30);
		tmeas = tmu_6->read(30e-6);
		//printf(" Step = %i,	V_FB = %.4f V.,	tmeas = %.4f uS\n", lcnt1, vfrc, tmeas*1e6);
		lcnt2++;
	}
	// Bring back FB to make sure Primary not switching
	VO_dvi->set_voltage(VO_ch, 4.0, 		VOLT_10_RANGE);
	REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		RANGE_2_V);	// OVI_1_2
	wait.delay_10_us(10);
	tmu_6->arm(); 
	wait.delay_10_us(30);
	tmeas = tmu_6->read(30e-6);
	if (tmeas > 0)
	{
		*Vclamp = -1.0;
		return;
	}

	*Vclamp = vout;
}

void search_SR_th(float *SR_th)
{
	int lcnt = 0;
	float vSR = 0.0;
	float vfrc = 0.0;
	float vstep = 0.0;

	// Arm comparator by setting FW to -1V
	FW_dvi->set_voltage(FW_ch, -1.0, RANGE_1_V);
	wait.delay_10_us(10);
	vSR = SR_dvi2k->measure_average(5);		// Should be Low

	if (vSR > 2.5)
	{
		*SR_th = 998.0;
		return;
	}

	FW_dvi->set_voltage(FW_ch, -0.2, RANGE_1_V);
	wait.delay_10_us(5);
	FW_dvi->set_voltage(FW_ch, -50e-3, RANGE_1_V);
	wait.delay_10_us(5);
	
	//FW set to -25mV smoothly
	vfrc = -50e-3;
	vstep = 5e-3;
	while(vfrc < -25e-3)
	{
		vfrc += vstep;
		FW_dvi->set_voltage(FW_ch, vfrc, RANGE_1_V);
		wait.delay_10_us(5);
	}

	vfrc = -20e-3;
	vstep = 0.1e-3;
	while( vSR < 2.5 && lcnt < 500 && vfrc < 25e-3)
	{
		vfrc+=vstep;
		lcnt++;
		FW_dvi->set_voltage(FW_ch, vfrc, RANGE_1_V);
		wait.delay_10_us(10);
		vSR = SR_dvi2k->measure_average(5);		// Should be High 
		wait.delay_10_us(1);
	}

	if (vSR > 2.5 && lcnt < 500)
		*SR_th = vfrc;
	else 
		*SR_th = 999.0;
}

void search_SR_th_TM1(float *SR_th)
{
	int lcnt=0, icnt =0;
	float vSR = 999.0;
	float vintial= 0.0, vstart=0.0, vfrc=0.0, vstep=0.0;

	// Arm comparator by setting FW to -0.5V
	FW_dvi->set_voltage(FW_ch, -0.5, VOLT_1_RANGE);  
	wait.delay_10_us(10);
	vSR = SR_dvi2k->measure_average(3);		// Should be High

	if (vSR < 2.5)
	{
		*SR_th = 999.0;
		return;
	}

	FW_dvi->set_voltage(FW_ch, -50e-3, VOLT_1_RANGE);  
	wait.delay_10_us(15);
	
	//FW ramp to -15mV smoothly
	vfrc = -50e-3;
	vstep = 5e-3;
	while(vfrc < -20e-3)
	{
		vfrc += vstep;
		FW_dvi->set_voltage(FW_ch, vfrc, VOLT_1_RANGE);  
		wait.delay_10_us(2);
	}

	vfrc = -15e-3;
	vstep = 0.1e-3;
	while( vSR > 2.5 && lcnt < 500 && vfrc < 30e-3)
	{
		vfrc+=vstep;
		lcnt++;
		FW_dvi->set_voltage(FW_ch, vfrc, VOLT_1_RANGE);  
		wait.delay_10_us(5);
		vSR = SR_dvi2k->measure();		// Should be High 
		//wait.delay_10_us(1);
	}

	if (vSR < 2.5 && lcnt < 500)
		*SR_th = vfrc;
	else 
		*SR_th = 999.0;
}

void search_SR_th_Ramp_dn(float *SR_th)
{
	// When using DVI on FW pin, we will only see the first negative edge that would cause SR to go high for ~1.5us in this func.
	// If we miss the first one, we can not see it anymore using the DVI on FW pin.
	// In order for us to see SR switch again, FW requires 3 negative edge of 35us apart from each edge
	// Note: Only the first and the 3rd negative edge would make SR to go high.
	//		 The longest that SR can stay high is ~4us.  If FW switch low for 1us, then SR will stay high for 1us

	int lcnt=0, icnt =0;
	float vSR =0.0;
	float vintial= 0.0, vstart=0.0, vfrc=0.0, vstep=0.0; 
	float T_Low=0, T_High=0, tmeas=0;

	vintial	= 0.5;
	vstart	= 0.0;
	T_Low	= 0.5e-6;
	T_High	= 5.0e-6;

 	tmu_6->close_relay(TMU_CHAN_A_DUT2);    // Connect TMU Channel A to "330ohm to SR pin"
	tmu_6->start_trigger_setup(2.0, POS_SLOPE, TMU_CHAN_A, TMU_IN_2_5V);
	tmu_6->stop_trigger_setup(1.0,	NEG_SLOPE, TMU_CHAN_A, TMU_IN_2_5V);
	tmu_6->start_holdoff(0,FALSE);
	tmu_6->stop_holdoff(0,FALSE);

	SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE);

	tmu_6->arm(); //In case the ramp down cause SR to go high, arm() through out the ramp down process.

	// Ramp down FW pin voltage slowly, so there is no undershoot to trigger the SR threshold before the real searching 
	for (icnt = 1; icnt < 21 ; icnt ++)
	{
		vfrc = vintial - (vintial - vstart)*icnt/20;
		FW_dvi->set_voltage(FW_ch, vfrc,	VOLT_1_RANGE);  
		wait.delay_10_us(5);
	}

//	tmu_6->arm(); 
	tmeas = tmu_6->read(); 

	FW_dvi->set_current(FW_ch, 300.0e-3,RANGE_300_MA);		
	wait.delay_10_us(10);
	delay(2);

	//Expect SR stay low during the ramp down
	if (tmeas > T_Low && tmeas < T_High )
	{
		*SR_th = 0.0;
		return;
	}

	vfrc = vstart;
	vstep = -0.002;
	
	while( (tmeas<T_Low || tmeas>T_High) && lcnt < 500 && vfrc > -0.1)
	{
		vfrc+=vstep;
		tmu_6->arm(); 
		wait.delay_10_us(5);
		FW_dvi->set_voltage(FW_ch, vfrc,VOLT_1_RANGE);  
		wait.delay_10_us(5);
		tmeas = tmu_6->read(); 
	}

	if (tmeas > T_Low && tmeas < T_High && lcnt <50)	//expect it to be done with in 15 steps of 2mV
		*SR_th = vfrc;
	else 
		*SR_th = 999.0;
	
}

void search_SR_th_DDD(float *SR_th)
{
	int lcnt=0;
	float vSR =0.0;
	float vstart, vfrc, vstep;

	// Initial search voltage
	vstart = -0.1;
	SR_dvi2k->set_meas_mode(SR_ch,		DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(10);
	vSR = SR_dvi2k->measure();			// Should be High 

	if (vSR < 2.5)
	{
		*SR_th = 999.0;
		return;
	}

	vfrc = vstart;
	vstep = 0.002;
	wait.delay_10_us(10); 

	while( vSR >2.5 && lcnt <500)
	{
		vfrc+=vstep;
		ddd_7->ddd_set_lo_level(vfrc);		// Will immediately change to this level upon execution 
//		ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop); // This is not necessary 
		wait.delay_10_us(15);
		vSR = SR_dvi2k->measure();		// Should be High 
	}

	if (vSR < 2.5 && lcnt <100)
		*SR_th = vfrc;
	else 
		*SR_th = 999.0;
	
}

void search_FWC_th(float *FWC_th_M, float *FWC_th_P)
{
	int lcnt=0, icnt =0;
	float vFWC =0.0;
	float vintial= 0.0, vstart=0.0, vfrc=0.0, vstep=0.0; 

	REQ_ovi->set_voltage(REQ_ch, 2.0,		RANGE_2_V);	// OVI_1_2
	wait.delay_10_us(10);

	// Arm comparator by setting FW above 100mV
	FW_dvi->set_voltage(FW_ch, 300e-3, VOLT_1_RANGE);  
	wait.delay_10_us(50);
	vFWC = FWC_dvi2k->measure_average(5);		// Should be High 

	if (vFWC > 2.5)
	{
		*FWC_th_M = 999.0;
		return;
	}

	FW_dvi->set_voltage(FW_ch, 0.0, RANGE_1_V);  
	wait.delay_10_us(1);
	//FW_dvi->set_voltage(FW_ch, -50.0e-3, RANGE_1_V);  
	//wait.delay_10_us(1);
	vfrc = 0.0e-3;
	vstep = 1e-3;
	//FW ramp to -200mV smoothly
	while(vfrc >= -200e-3 && vFWC < 2.5)
	{
		FW_dvi->set_voltage(FW_ch, vfrc, RANGE_1_V);  
		wait.delay_10_us(10);
		vFWC = FWC_dvi2k->measure_average(5);
		//wait.delay_10_us(1);
		vfrc -= vstep;
		lcnt++;
	}
	*FWC_th_M = vfrc;
	
	FW_dvi->set_voltage(FW_ch, 0.0, RANGE_1_V);  
	wait.delay_10_us(1);
	FW_dvi->set_voltage(FW_ch, 50.0e-3, RANGE_1_V);  
	wait.delay_10_us(1);
	vfrc = 0.0e-3;
	//FW ramp to 200mV smoothly
	while(vfrc <= 200e-3 && vFWC > 2.5)
	{
		FW_dvi->set_voltage(FW_ch, vfrc, RANGE_1_V);  
		wait.delay_10_us(10);
		vFWC = FWC_dvi2k->measure_average(5);
		//wait.delay_10_us(1);
		vfrc += vstep;
	}
	*FWC_th_P = vfrc;

//	vfrc = -30e-3;
//	vstep = 0.1e-3;
////	vstep = 1e-3;
//	while( vSR < 2.5 && lcnt < 500 && vfrc < 25e-3)
//	//while( vSR < 2.5 && lcnt < 1000 && vfrc < 25e-3)
//	{
//		vfrc+=vstep;
//		lcnt++;
//		FW_dvi->set_voltage(FW_ch, vfrc, VOLT_1_RANGE);  
//		wait.delay_10_us(25);
//		vSR = SR_dvi2k->measure_average(5);		// Should be High 
//		wait.delay_10_us(1);
//	}
//
////	if (vSR > 2.5 && lcnt < 200)
//	if (vSR > 2.5 && lcnt < 1000)
//		*SR_th = vfrc;
//	else 
//		*SR_th = 999.0;
}

void search_REQ_Vref_th(float V_start, float V_step, float *REQ_Vref_M, float *REQ_Vref_P)
{
	int lcnt = 0;
	float vSR = 0.0;
	float vfrc = 0.0, vstep = 0.0; 
	float vmax = 2.0;
	int REQ_range = RANGE_2_V;

	if (V_start <= 1.0)
	{
		vmax = 1.0;
		REQ_range = RANGE_1_V;
	}
	if (V_start >= 2.0)
	{
		vmax = 5.0;
		REQ_range = RANGE_5_V;
	}

	REQ_ovi->set_voltage(REQ_ch, vmax,		REQ_range);	// OVI_1_2
	wait.delay_10_us(50);

	vSR = SR_dvi2k->measure_average(5);		// Should be HIGH
	wait.delay_10_us(1);

	if (vSR < 2.5)
	{
		*REQ_Vref_M = 999.0;
		*REQ_Vref_P = 999.0;
		return;
	}

	REQ_ovi->set_voltage(REQ_ch, 0.0,		REQ_range);	// OVI_1_2
	wait.delay_10_us(50);

	vSR = SR_dvi2k->measure_average(5);		// Should be LOW
	wait.delay_10_us(1);

	if (vSR > 2.5)
	{
		*REQ_Vref_M = 999.0;
		*REQ_Vref_P = 999.0;
		return;
	}

	// Sweep method
	//vfrc = V_start;
	//vstep = V_step;
	//REQ_ovi->set_voltage(REQ_ch, vfrc,		REQ_range);	// OVI_1_2
	//wait.delay_10_us(50);

	//while (vSR < 2.5 && lcnt < 150)
	//{
	//	REQ_ovi->set_voltage(REQ_ch, vfrc,		REQ_range);	// OVI_1_2  
	//	wait.delay_10_us(10);
	//	vSR = SR_dvi2k->measure_average(5);
	//	wait.delay_10_us(1);
	//	vfrc += vstep;
	//	lcnt++;
	//}

	//if (lcnt >= 150 || lcnt <= 1)
	//{
	//	*REQ_Vref_M = 999.0;
	//	*REQ_Vref_P = 999.0;
	//}
	//else
	//{
	//	*REQ_Vref_P = vfrc;
	//}

	// Binary search method
	int LO = 0;
	int HI = 1;
	
	int LO_TO_HI = 0;
	int HI_TO_LO = 1;
	
	float p_low_M = 0.0;
	float p_high_M = vmax;

	float p_low_P = p_low_M;
	float p_high_P = p_high_M;
	
	float delta_T = fabs(V_step);    
	float delta_M = p_high_M - p_low_M;
	float delta_P = p_high_P - p_low_P;
	int sigdir = LO_TO_HI;
	int m = 0;
	int p = 0;
	
	while (!((delta_M < delta_T) && (delta_P < delta_T)))
	{
		if (sigdir == LO_TO_HI)
		{
			if (delta_P > delta_T)
			{
				vfrc = (p_low_P + p_high_P) / 2;
				REQ_ovi->set_voltage(REQ_ch, vfrc * 0.9,	REQ_range);	// OVI_1_2  
				wait.delay_10_us(5);
				REQ_ovi->set_voltage(REQ_ch, vfrc * 0.95,	REQ_range);	// OVI_1_2  
				wait.delay_10_us(5);
				REQ_ovi->set_voltage(REQ_ch, vfrc,		REQ_range);	// OVI_1_2  
				wait.delay_10_us(10);
				vSR = SR_dvi2k->measure_average(5);
				wait.delay_10_us(1);
				if (vSR >= 2.5)
				{
					p_high_P = vfrc;
					sigdir = HI_TO_LO;
				}
				else
				{
					p_low_P = vfrc;
				}
				delta_P = p_high_P - p_low_P;
				p++;
			}
			else
			{
				sigdir = HI_TO_LO;
			}
		}
		else if (sigdir == HI_TO_LO)
		{
			if (delta_M > delta_T)
			{
				vfrc = (p_low_M + p_high_M) / 2;
				REQ_ovi->set_voltage(REQ_ch, vfrc * 1.1,	REQ_range);	// OVI_1_2  
				wait.delay_10_us(5);
				REQ_ovi->set_voltage(REQ_ch, vfrc * 1.05,	REQ_range);	// OVI_1_2  
				wait.delay_10_us(5);
				REQ_ovi->set_voltage(REQ_ch, vfrc,		REQ_range);	// OVI_1_2  
				wait.delay_10_us(10);
				vSR = SR_dvi2k->measure_average(5);
				wait.delay_10_us(1);
				if (vSR <= 2.5)
				{
					p_low_M = vfrc;
					sigdir = LO_TO_HI;
				}
				else
				{
					p_high_M = vfrc;
				}
				delta_M = p_high_M - p_low_M;
				m++;
			}
			else
			{
				sigdir = LO_TO_HI;
			}
		}
		lcnt++;
		if (lcnt > 50) break;
	}

	if (lcnt >= 50 || lcnt <= 1)
	{
		*REQ_Vref_M = 999.0;
		*REQ_Vref_P = 999.0;
	}
	else
	{
		*REQ_Vref_M = (p_low_M + p_high_M) / 2;
		*REQ_Vref_P = (p_low_P + p_high_P) / 2;
	}
}

void VBPP_Power_Up(int ILIM_Mode)
{
	int dly =0;
//	float v_pullup;

	////if (ILIM_Mode == ILIM_RED || ILIM_Mode == SOA_RED_P	|| ILIM_Mode == SOA_RED_S)	
	////	dly = 26;		//260us
	////else if (ILIM_Mode == ILIM_INCR)	// 325us < t
	////	dly = 200;		//need 2ms for ILIM_INCR. 1ms selects ILIM_RED
		
	//UV pin set to 0V
	VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_2_V);  
	VPIN_ovi->set_current(VPIN_ch, 10e-3,		RANGE_30_MA);		

	//BPP set 0V
	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 	RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(50);

	//BPP ramp up to 4V with 100mV step, then from 4V to VBPP_plus + 200mV
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 4.0, 0.1);	// vstart, vstop, vstep

	if(ILIM_Mode == ILIM_NORM)
	{
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init + 0.2, 	RANGE_10_V);	// OVI_1_0
		wait.delay_10_us(10);
	}
	else
	{
		BPP_ovi->set_voltage(BPP_ch, gVBPP_PV_Init, 		RANGE_10_V);	// OVI_1_0
//		wait.delay_10_us(dly);
		delay(1);
		BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init - 0.2, 	RANGE_10_V);	// OVI_1_0
		wait.delay_10_us(50);
		BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init + 0.2, 	RANGE_10_V);	// OVI_1_0
		wait.delay_10_us(50);
	}

}

void VBPP_ramp_up(float vstart, float vstop, float vstep)
{	
	int lcnt=0;
	vstart +=vstep;
	while( vstart < (vstop-vstep) && lcnt <500)			// Ramp up VBPP to reduce overshoot
	{	
		BPP_ovi->set_voltage(BPP_ch, vstart,	RANGE_10_V);			// OVI_1_0
		wait.delay_10_us(5);
		vstart +=vstep;
		lcnt++;
	}	
	BPP_ovi->set_voltage(BPP_ch, vstop,	RANGE_10_V);
	wait.delay_10_us(5);
}

void VBPP_ramp_down(float vstart, float vstop, float vstep)
{
	int lcnt=0;
	vstart -=vstep;
	while( vstart > (vstop+vstep) && lcnt <500)			// Ramp down VBPP to reduce undershoot
	{	
		BPP_ovi->set_voltage(BPP_ch, vstart,	RANGE_10_V);			// OVI_1_0
		wait.delay_10_us(5);
		vstart -=vstep;
		lcnt++;
	}	
	BPP_ovi->set_voltage(BPP_ch, vstop,	RANGE_10_V);			// OVI_1_0
	wait.delay_10_us(5);
}

void VBPS_ramp_up(float vstart, float vstop, float vstep)
{
	int lcnt=0;
	float vmeas=0;

	BPS_dvi->set_voltage(BPS_ch, vstart,	VOLT_10_RANGE);			
	wait.delay_10_us(5);
	//BPS_dvi->set_voltage(BPS_ch, vstart - 50e-3,	VOLT_5_RANGE);			
	//wait.delay_10_us(5);
	//vstart = vstart - 50e-3;
	while( vstart < (vstop+vstep) && lcnt <500)			// Ramp up VBPS
	{	
		vstart +=vstep;
		BPS_dvi->set_voltage(BPS_ch, vstart,	VOLT_10_RANGE);			
		wait.delay_10_us(1);
	}	
		BPS_dvi->set_voltage(BPS_ch, vstop,	VOLT_10_RANGE);			
		wait.delay_10_us(5);
}

void VBPS_ramp_down(float vstart, float vstop, float vstep)
{
	int lcnt=0;
	float vmeas=0;

	BPS_dvi->set_voltage(BPS_ch, vstart,	VOLT_10_RANGE);			
	wait.delay_10_us(5);
	BPS_dvi->set_voltage(BPS_ch, vstart - 50e-3,	VOLT_10_RANGE);			
	wait.delay_10_us(5);
	vstart = vstart - 50e-3;
	while( vstart > (vstop+vstep) && lcnt <500)			// Ramp down VBPS to reduce undershoot
	{	
		vstart -=vstep;
		BPS_dvi->set_voltage(BPS_ch, vstart,	VOLT_10_RANGE);			
		wait.delay_10_us(1);
	}	
		BPS_dvi->set_voltage(BPS_ch, vstop,	VOLT_10_RANGE);			
		wait.delay_10_us(5);
}

void VBPS_Power_Up(float vfinal)
{
	// For regular handshake involving primary, FW pin is usually switching before VBPS is powered all the way
	// up to VBPS_P. FW will see the first negative edge before BPS pin power up and reading anti-fuse for post 
	// trim parameters won't be a problem. Compare this to VBPS_Power_Up_TestModeSelect();
//	BPS_dvi->set_voltage(BPS_ch, 0.0, 					VOLT_10_RANGE);	// DVI_9_1
////	BPS_dvi->set_current(BPS_ch, 30e-3,					RANGE_30_MA);	 
//	wait.delay_10_us(5);
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init-0.5, 	VOLT_10_RANGE);		// DVI_9_1
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init-0.1, 	VOLT_10_RANGE);		// DVI_9_1
	wait.delay_10_us(10);
	BPS_dvi->set_voltage(BPS_ch, vfinal, 	VOLT_10_RANGE);				// DVI_9_1
	wait.delay_10_us(10);
}

void Power_Up_Secondary_Skip_WaitNListen(int Mode, float vfinal)
{
	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	if(Mode == Normal_Mode_S || Mode == gNM_SkipWaitNListen_S)
	{
		//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
		//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
//		if(g_TurretCB)
		//if(1)
		//{
		//	//HL needs to change to 20mA or Turret CB won't work.
		//	SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
		//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		//	delay(2);
		//	mux_20->close_relay(MUX_1_1);
		//	delay(2);
		//}
		//else
		//{
		//	SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
		//	SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
		//	dvi_13->close_relay(BUS_SENSE1);
		//	dvi_13->close_relay(BUS_FORCE1);
		//	mux_14->close_relay(MUX_3_BUS3);
		//}

		//Close_relay(K5);//Connect SR to 5nF
		SR_dvi2k->open_relay(CONN_FORCE1);
		SR_dvi2k->open_relay(CONN_SENSE1);
		//wait.delay_10_us(10);
		Close_relay(K5);//Connect SR to 5nF
		delay(2);
	
	
	}
	ddd_7->ddd_set_hi_level(5.0);		// Will immediately change to this level upon execution
	//delay(1);
	wait.delay_10_us(10);
//	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	
	ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);	
	wait.delay_10_us(10);
	Close_relay(K21);		// FW		to	DDD
	delay(5);

	//BPS (vPlus - 300mV)
	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
	VBPS_Power_Up(gVBPS_P_Init-0.1);			// vfinal

	//Vout (5V)
	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
	//VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0  "Stop device from switching"

	//FB (2V)  pull FB above CVth to force No Switching
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	REQ_ovi->set_voltage(REQ_ch, 0.9,	RANGE_2_V);	// OVI_1_2	
	//REQ_ovi->set_voltage(REQ_ch, 2.0,					RANGE_2_V);	// OVI_1_2	

	//IS (0V)
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	wait.delay_10_us(10);
		

	//BPS_dvi->set_voltage(BPS_ch, vfinal, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	BPS_dvi->set_voltage(BPS_ch, 5.0, 	VOLT_10_RANGE);	// Secondary vBPS_plus
	wait.delay_10_us(10);

	// Secondary send 3 negative FW pulses to cause Primary to see request so Primary will be switching (1st pulse = comm..  2nd&3rd = request)
	Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
	wait.delay_10_us(10);  //more than 30us quiet time on FW signal

	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0		
	wait.delay_10_us(5);

	ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);	
	wait.delay_10_us(10);
	Open_relay(K21);		// FW		to	DDD
	wait.delay_10_us(50);
	//delay(5);

	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0		
	wait.delay_10_us(10);

	//pulse.do_pulse();
	Connect_InvSyn_IM_New(Low_Vd_Input);		
	//Open_relay(K21);		// FW		to	DDD
	//pulse.do_pulse();
	wait.delay_10_us(50);

	//SR_dvi2k->open_relay(CONN_FORCE1);
	//SR_dvi2k->open_relay(CONN_SENSE1);
	//Close_relay(K5);//Connect SR to 5nF
	//delay(2);
	//pulse.do_pulse();
	//FB (1V) force Switching
	REQ_ovi->set_voltage(REQ_ch, 2.0,		RANGE_2_V);	// OVI_1_2	
	wait.delay_10_us(10);

	D_dvi->set_voltage(D_ch, 5.0, 			VOLT_50_RANGE);	// DVI_11_0		
	wait.delay_10_us(140);
}

void Power_Up_Secondary(int Mode, double vfinal)	//FB(1V), BPS(0V,vPlus-200mV then vPlus+50mV), FW(continuous clk 1us/34us Low/High)
{


	if(Mode == Normal_Mode_S)
	{
		//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
		////			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
		//	SR_dvi2k->set_current(SR_ch, 0.0e-6,	RANGE_2_UA);	
		//	SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);	// DVI_21_1
		//	delay(2);
		//	mux_20->close_relay(MUX_1_1);      //Direct short SR to GND on Turret Brd.
		//	delay(2);

		//
		Close_relay(K5);//Connect SR to 5nF
	delay(5);
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	}


	//BPS (VBPS_M - 200mV) "Allow bandgap to start up and avoid large charge current from Vout to heat up the device"
	BPS_dvi->set_current(BPS_ch, 300e-3,	RANGE_300_MA);	 
	BPS_dvi->set_voltage(BPS_ch, 0.0001,	VOLT_10_RANGE);				// DVI_9_1
	wait.delay_10_us(5);
	BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init-0.2, 		VOLT_10_RANGE);				// DVI_9_1
	wait.delay_10_us(10);

	//FW clocking spec is critical with respect to reaching VBPS_Plus.  Once vPlus reached, first negative pulse has to 
	//happen within 40us, then 2 more negative pulses for Secondary to take in control.  Then the following negative pulses
	//has to happen after 30us otherwise Secondary will give up control.
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);
	REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		RANGE_2_V);				// OVI_1_2
	wait.delay_10_us(5);

	//if(Mode == Normal_Mode_S)
	//{
	//	//SR (0V)	(Requires dead short.  DVI-2k is not responding fast enough that SR could have pull-up and back to ground)
	//	//			(We just can't see it from the scope.  So, try to short this from BUS3 through MUX_GND)
	//	if(!g_TurretCB)
	//	{
	//		SR_dvi2k->set_current(SR_ch, 0,			RANGE_2_UA);	
	//		SR_dvi2k->set_voltage(SR_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_1
	//		dvi_13->close_relay(BUS_SENSE1);
	//		dvi_13->close_relay(BUS_FORCE1);
	//		mux_14->close_relay(MUX_3_BUS3);
	//		delay(2);
	//	}
	//	
	//}

	//HL changed VO from 5V to 0V.
	//Vout (5V)
	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_10_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
	delay(1);
	if(Mode==Normal_Mode_with_FW || Mode==Test_Mode)
	{
		wait.delay_10_us(100); 
		ddd_7->ddd_set_hi_level(0.0);							// Will immediately change to this level upon execution
		delay(1);
		ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	
		wait.delay_10_us(10);

		Close_relay(K21);										// Connect FW pin to DDD, DDD is at 0V
		Open_relay(K18);										// Disconnect FW pin from DVI
		delay(5);

		ddd_7->ddd_stop_pattern();			// stop FW continuous clks
		wait.delay_10_us(100); 
		ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
		ddd_7->ddd_set_hi_level(0.5);		// Will immediately change to this level upon execution
		delay(1);
		ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//FW will start with High
		wait.delay_10_us(10);
	}

	if(Mode==Normal_Mode_with_FW)
	{
		ddd_7->ddd_end_pattern(FW_Neg_loop_pulse_stop);	//K21 needs to be closed for DDD connect to FW
		wait.delay_10_us(10); 
		ddd_7->ddd_run_pattern();
	}

	
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init-0.7, 	VOLT_10_RANGE);		// DVI_9_1
	//wait.delay_10_us(30);
	if(Mode==Normal_Mode_with_Vout)
	{
		VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_5_RANGE);	// DVI_9_0
		VO_dvi->set_current(VO_ch, 30.0e-3,		RANGE_30_MA);	
	}
	BPS_dvi->set_voltage(BPS_ch, vfinal, 	VOLT_10_RANGE);				// DVI_9_1
	wait.delay_10_us(50);
	wait.delay_10_us(500);

	//HL - New added to avoid glitch on VO pin when VBPS is powered up
	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 5.0, 		VOLT_10_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"
	delay(1);
	
	if(Mode==Test_Mode)			//Enter Test_Mode or Write_Mode if FW does not switch within 40us after reaching vPlus
	{
		wait.delay_10_us(10);
		ddd_7->ddd_end_pattern(FW_Neg_loop_pulse_stop);	//K21 needs to be closed for DDD connect to FW
		wait.delay_10_us(10); 
		ddd_7->ddd_run_pattern();
		wait.delay_10_us(10);
	}
//	ddd_7->ddd_stop_pattern();
}

void Power_up_Secondary_Test_Mode(float vfinal)
{
	// If FW see a negative edge within 40us after BPS reaches VBPS_P, secondary will be in normal mode. 
	// Vice versa, if above condition is not met, device will stay in test mode. 
	float start_vec, stop_vec;
	wait.delay_10_us(100); 
	ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(0.5);		// Will immediately change to this level upon execution
	delay(1);

	start_vec = FW_pulse_train_start;
	stop_vec  = FW_pulse_train_stop-1;

	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	
	wait.delay_10_us(10); 
	if(gHas_Fixed_AR_Func)
	{// For 2.0 Silicon on, some silicons have 3V fixed Autorestart on VO pin. Keep Vout above that threshold
		VO_dvi->set_current(VO_ch, 200.0e-3,	RANGE_300_MA);	
		VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	}
	// FW needs to see the first negative edge before BPS pin power up. Otherwise, anti-fuses won't be 
	// read properly, post trim measurement will be off. 
	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);
//	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_2_V);				// OVI_1_2
	// Set FB voltage to be above vFBth:SC threshold to inhibit handshake before BPS powers up.
	// Changed for 2.0 secondary silicon and forward
	REQ_ovi->set_voltage(REQ_ch, 0.3, 		RANGE_2_V);				// OVI_1_2
	wait.delay_10_us(20);
	BPS_dvi->set_current(BPS_ch, 300e-3,	RANGE_300_MA);	 
	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_10_RANGE);				// DVI_9_1
	wait.delay_10_us(20);
//	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init-0.5, 	VOLT_10_RANGE);		// DVI_9_1
	BPS_dvi->set_voltage(BPS_ch, gVBPS_P_Init-0.2, 	VOLT_10_RANGE);		// DVI_9_1
	wait.delay_10_us(30);

	BPS_dvi->set_voltage(BPS_ch, vfinal, 	VOLT_10_RANGE);				// DVI_9_1
	wait.delay_10_us(100);	// Wait way beyond 40us after BPS reaches VBPS_P to stay in test mode	

	//The first pulse from FW pin can only happen at least 40us after BPS pin reaches VBPS_P in order for the
	// device to remain in test mode
	ddd_7->ddd_run_pattern(start_vec,stop_vec);	// Apply neg pulse train to FW pin to turn on secondary 
	wait.delay_10_us(20);

}

void Powerup_Secondary_in_Testmode(int Testmode, float vTrim, float vRead)
{
/*	Secondary "Write Mode" Power Up
		1. Set VBPS to VBPS_M-100mV (Allow bandgap to start up and avoid large charge current from Vout to heat up the device)
		2. Set FB to 5V, Float SR pin
		3. Set Vout to 0V
		4. Set VFW to -1V
		5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
		6. Bring FB down to 0V to aviod mis-trim

		(To trim, apply the following steps.  And following steps will be called from another function)
		7. Clock Vout to anti-fuse
		8. Bring FW up to 50V
		9. Raise FB voltage to 5V for duration of trim time to trim anti-fuse.	
		
	Secondary "gProgram_Mode_S" Power Up
		1. Set VBPS to VBPS_M-100mV (Allow bandgap to start up and avoid large charge current from Vout to heat up the device)
		2. Set FB to 5V, Float SR pin
		3. Set Vout to 0V
		4. Set FW to 1V
		5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
		6. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
		7. Set FB back to 1V
		8. Clock Vout to TestMode #

	Secondary "Program Simu Mode" Power Up
		1. Set VBPS to VBPS_M-100mV (Allow bandgap to start up and avoid large charge current from Vout to heat up the device)
		2. Set FB to 5V, Float SR pin
		3. Set Vout to 0V
		4. Set FW to 1V
		5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
		6. Clock Vout to program data from FB into trim registers
		7. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
		8. Set FB back to 1V
		9. Clock Vout to TestMode #
	*/

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//1. Set VBPS to VBPS_M-100mV (Allow bandgap to start up and avoid large charge current from Vout to heat up the device)
	BPS_dvi->set_current(BPS_ch, 300.0e-3,					RANGE_300_MA);	
	//BPS_dvi->set_voltage(BPS_ch, gVBPS_M_Init - 100e-3, 	VOLT_10_RANGE);	// DVI_9_1
	VBPS_ramp_up(0, gVBPS_M_Init - 100e-3, 100e-3);	//BPS ramp up from 0 to VBPS-M minus 200mV with 100mV step.
	wait.delay_10_us(50);

	//Float SR pin
	//SR_dvi2k->open_relay(CONN_FORCE1);
	//SR_dvi2k->open_relay(CONN_SENSE1);

	//2. Set FB to 5V
	//REQ_ovi->set_voltage(REQ_ch, 5.0, 		VOLT_5_RANGE);	// OVI_1_2
	REQ_ovi->set_voltage(REQ_ch, 4.4, 		VOLT_5_RANGE);	// OVI_1_2
	//REQ_ovi->set_voltage(REQ_ch, 1.3, 		VOLT_5_RANGE);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);
	wait.delay_10_us(10);

	//3. Set Vout to 0V
	VO_dvi->set_current(VO_ch, 5e-3,		RANGE_30_MA);
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0


	switch (Testmode)
	{
		case gWrite_Mode_ReadAF:
			//Setup Vout to connect to DDD7_4 and have DDD7_4 toggle to stay LOW to start with
			VO_dvi->open_relay(CONN_FORCE0);
			VO_dvi->open_relay(CONN_SENSE0);
			delay(1);
			ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
			wait.delay_10_us(14);
			Close_relay(K27);	//Connect Vout to DDD7_4
			Close_relay(K18);	//Setup to have FW connect to DVI-11-1
			delay(3);			
			//4. Set VFW to -1V
			FW_dvi->set_voltage(FW_ch, -1.0, 		VOLT_50_RANGE);	// DVI_11_1
			FW_dvi->set_current(FW_ch, 30.0e-3,		RANGE_30_MA);
			wait.delay_10_us(10);
			delay(1);	//Minimum wait time is 700us in order for AF reading to work properly
			//5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
			VBPS_ramp_up(gVBPS_M_Init - 200e-3, gVshunt_Init_Se - 100e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
			wait.delay_10_us(10);
			//6. Bring FB down to 0V to aviod mis-trim
			REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
			wait.delay_10_us(10);
			break;

		case gWrite_Mode_TrimAF:	//Same as gWrite_Mode_ReadAF from above
			//Setup Vout to connect to DDD7_4 and have DDD7_4 toggle to stay LOW to start with
			VO_dvi->open_relay(CONN_FORCE0);
			VO_dvi->open_relay(CONN_SENSE0);
			wait.delay_10_us(100); 
			ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
			wait.delay_10_us(14);
			Close_relay(K27);	//Connect Vout to DDD7_4
			Close_relay(K18);	//Setup to have FW connect to DVI-11-1
			delay(3);			
			//4. Set VFW to -1V
			FW_dvi->set_voltage(FW_ch, -1.0, 		VOLT_50_RANGE);	// DVI_11_1
			FW_dvi->set_current(FW_ch, 30.0e-3,		RANGE_30_MA);
			wait.delay_10_us(10);
			delay(1);	//Minimum wait time is 700us in order for AF reading to work properly
			//5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
			VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVshunt_Init_Se - 100e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
			wait.delay_10_us(10);
			//6. Bring FB down to 0V to aviod mis-trim
			REQ_ovi->set_voltage(REQ_ch, 0.0, 		VOLT_5_RANGE);	// OVI_1_2
			wait.delay_10_us(10);
			break;

		case gProgRead_S:	//Read out SR signals
			/*****************************************************************************************************************
			Reg. Addr		TestMode Names		Signals output to SR		Function
			------------------------------------------------------------------------------------------------------------------
				2			TestMode1			SRO							Shorten AR timer by 10x. Shorten SC timer by 256x
				4			TestMode2			DableOn						DableOn from FW pin Peak Switch
				6			TestMode3			Pulse						Pulse Request
				8			TestMode4			DfuncOff					FW pin Peak Switch Fault
				10			TestMode5			Vp							SR pullup
				12			TestMode6			Control_S					To Verify is secondary is in control
				14			TestModeTFB<1>		SRO							normal SR signal
				16			TestModeTFB<2>		SRO							normal SR signal
				18			Not Used			SRO							Not Used
				20			Not Used			SRO							Not Used
				22			TestMode11			DFWh						SR comparator output
				24			TestMode12			FWFlate						FW min 1us negative pulse indication
				26			TestMode13			X9V20V						9V20V comparator signal
				28			TestMode14			X12V						12V comparator signal
				30			SiRev<3>			Vp or Vn					Silicon Rev
				32			SiRev<2>			Vp or Vn					Silicon Rev
				34			SiRev<1>			Vp or Vn					Silicon Rev
				Others		None				Vn							None									
			******************************************************************************************************************/
			// Disconnect VO dvi
			VO_dvi->open_relay(CONN_FORCE0);
			VO_dvi->open_relay(CONN_SENSE0);
			delay(1);
			ddd_7->ddd_set_lo_level(0.1);				// Will immediately change to this level upon execution
			wait.delay_10_us(100);						//HL Do not remove. Else, DDD will be corrupted.
			ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
			wait.delay_10_us(14);
			Close_relay(K27);	//Connect Vout to DDD7_4
			Close_relay(K18);	//Setup to have FW connect to DVI-11-1
			delay(4);	
			//Float SR pin
			SR_dvi2k->open_relay(CONN_FORCE1);
			SR_dvi2k->open_relay(CONN_SENSE1);
			//4. Set VFW to 1V
			FW_dvi->set_voltage(FW_ch, 1.0, 		VOLT_50_RANGE);	// DVI_11_1
			FW_dvi->set_current(FW_ch, 30.0e-3,		RANGE_30_MA);
			//wait.delay_10_us(10);
			delay(1);	//Minimum wait time is 700us in order for AF reading to work properly
			//5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
			//VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVBPS_final + 100e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
			VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVBPS_final+400e-3, 100e-3);	//Ramp up higher so if there's a dip, it will still be above vBPS_minus
			//delay(1);
			wait.delay_10_us(100);
			//6. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
			FW_dvi->set_voltage(FW_ch, -0.5, 		VOLT_50_RANGE);	// DVI_11_1
			wait.delay_10_us(10);
			//wait.delay_10_us(100);	//Leaving it stay below GND for 1ms will cause vBPS to go below vBPS_minus and will kick out of TM if BPS set to vPlus+100mV
			FW_dvi->set_voltage(FW_ch, 1.0, 		VOLT_50_RANGE);	// DVI_11_1
			wait.delay_10_us(10);
			//ddd_7->ddd_run_pattern(FW_Neg_1st_pulse_start,FW_Neg_1st_pulse_stop-1);
			//wait.delay_10_us(15);	
			//7. Set FB back to 1V
			REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		VOLT_5_RANGE);	// OVI_1_2
			wait.delay_10_us(40);

			//BPS set back to vBPS_final + 100mV
			BPS_dvi->set_voltage(BPS_ch, gVBPS_final+100e-3,	VOLT_10_RANGE);			
			wait.delay_10_us(10);

			//8. Clock Vout to TestMode #  (This will be done on a different function)
			break;

		case gProgRead_AFreg_S:	//Read/Write AntiFuse register-MINNO power up 
			// Disconnect VO dvi
			VO_dvi->open_relay(CONN_FORCE0);
			VO_dvi->open_relay(CONN_SENSE0);
			wait.delay_10_us(10);
			ddd_7->ddd_set_lo_level(0.1);				// Will immediately change to this level upon execution
			ddd_7->ddd_set_hi_level(5.0);				// Will immediately change to this level upon execution
			wait.delay_10_us(10);
			ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
			wait.delay_10_us(10);
			//Connect Vout to DDD7_4
			Close_relay(K27);	//Connect Vout to DDD7_4
			Close_relay(K18);	//Setup to have FW connect to DVI-11-1
			delay(3);
			//Float SR pin
			SR_dvi2k->open_relay(CONN_FORCE1);
			SR_dvi2k->open_relay(CONN_SENSE1);
			//4. Set VFW to 1V
			FW_dvi->set_voltage(FW_ch, 1.0, 		VOLT_50_RANGE);	// DVI_11_1
			FW_dvi->set_current(FW_ch, 30.0e-3,		RANGE_30_MA);
			//wait.delay_10_us(10);
			delay(1);	//Minimum wait time is 700us in order for AF reading to work properly
			VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVBPS_final+100e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
			//delay(1);
			//wait.delay_10_us(10);
			//7. Set REQ back to 1.7V-Not applicable for MINNO
			//REQ_ovi->set_voltage(REQ_ch, 1.7, 		VOLT_5_RANGE);	// OVI_1_2
			//wait.delay_10_us(40);
			//Read/write AF register
			Close_relay(K26);	//SR to DDD-7-5
			delay(4);
			//AF register can now be read/written to
			//pulse FW below ground to finish power up sequence
			//delay(1);
			break;

		case gProgRead_SkipWaitNListen_S:	//Read out SR signals
			/*****************************************************************************************************************
			Reg. Addr		TestMode Names		Signals output to SR		Function
			------------------------------------------------------------------------------------------------------------------
				2			TestMode1			SRO							Shorten AR timer by 10x. Shorten SC timer by 256x
				4			TestMode2			DableOn						DableOn from FW pin Peak Switch
				6			TestMode3			Pulse						Pulse Request
				8			TestMode4			DfuncOff					FW pin Peak Switch Fault
				10			TestMode5			Vp							SR pullup
				12			TestMode6			Control_S					To Verify is secondary is in control
				14			TestModeTFB<1>		SRO							normal SR signal
				16			TestModeTFB<2>		SRO							normal SR signal
				18			Not Used			SRO							Not Used
				20			Not Used			SRO							Not Used
				22			TestMode11			DFWh						SR comparator output
				24			TestMode12			FWFlate						FW min 1us negative pulse indication
				26			TestMode13			X9V20V						9V20V comparator signal
				28			TestMode14			X12V						12V comparator signal
				30			SiRev<3>			Vp or Vn					Silicon Rev
				32			SiRev<2>			Vp or Vn					Silicon Rev
				34			SiRev<1>			Vp or Vn					Silicon Rev
				Others		None				Vn							None									
			******************************************************************************************************************/
			VO_dvi->open_relay(CONN_FORCE0);
			VO_dvi->open_relay(CONN_SENSE0);
			wait.delay_10_us(100); 
			ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
			wait.delay_10_us(14);
			//Float SR pin
			SR_dvi2k->open_relay(CONN_FORCE1);
			SR_dvi2k->open_relay(CONN_SENSE1);
			//4. Set VFW to 1V
			FW_dvi->set_voltage(FW_ch, 5.0, 		VOLT_50_RANGE);	// DVI_11_1
			FW_dvi->set_current(FW_ch, 30.0e-3,		RANGE_30_MA);
			wait.delay_10_us(10);
			delay(1);	//Minimum wait time is 700us in order for AF reading to work properly
			//5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
			//VBPS_ramp_up(0, gVBPS_M_Init - 100e-3, 100e-3);	//BPS ramp up from 0 to VBPS-M minus 100mV with 100mV step.
			//wait.delay_10_us(5);
//			VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVshunt_Init_Se - 100e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
			VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVBPS_final, 50e-3);	
			delay(1);
			wait.delay_10_us(40);
			//6. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
			FW_dvi->set_voltage(FW_ch, -0.3, 		VOLT_50_RANGE);	// DVI_11_1
			wait.delay_10_us(50);
			FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
			wait.delay_10_us(10);
			
			Skip_Wait_and_Listen();			
			
			//7. Set FB back to 1V
			REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		VOLT_5_RANGE);	// OVI_1_2
			wait.delay_10_us(40);
			delay(1);		
			//8. Clock Vout to TestMode #  (This will be done on a different function)
			break;

		case gProgSim:	//Clock Vout to program data from FB into trim registers
			//Float SR pin
			//SR_dvi2k->open_relay(CONN_FORCE1);
			//SR_dvi2k->open_relay(CONN_SENSE1);
			//4. Set VFW to 1V
			FW_dvi->set_voltage(FW_ch, 1.0, 		VOLT_50_RANGE);	// DVI_11_1
			FW_dvi->set_current(FW_ch, 30.0e-3,		RANGE_30_MA);
			wait.delay_10_us(10);
			delay(1);	//Minimum wait time is 700us in order for AF reading to work properly
			//5. Set VBPS to VBPS_P+50mV. Wait (min. 50us) until AF reading is done.  (Might use VBPS_Shunt - 100mV instead)
			VBPS_ramp_up(gVBPS_M_Init - 100e-3, gVshunt_Init_Se - 100e-3, 50e-3);	//BPS ramp up from "VBPS-M minus 100mV" to "VBPS-Shunt - 100mV" with 50mV step.
			wait.delay_10_us(10);

			//Below steps will be done on a different function
			//6. Clock Vout to program data from FB into trim registers
			//7. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
			//8. Set FB back to 1V
			//9. Clock Vout to TestMode #
			break;

		default:
			break;
	}
}

void Secondary_Test_Mode_Vshunt_Power_up(double vfinal, double vFB, double iFB, double vVout, double iVout)
{
	//TestModeSelect Vshunt power up exist for Rev 2.5S and later materials
	//- FB		set 1V/100uA
	//- Vout	set 4V/1mA
	//- Power up secondary in TestModeSelect Vshunt and set BPS back to normal operating voltage.
	REQ_ovi->set_voltage(REQ_ch, vFB, 	VOLT_5_RANGE);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, iFB,		RANGE_30_UA);
	VO_dvi->set_voltage(VO_ch, vVout,	VOLT_5_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, iVout,	RANGE_300_MA);	
	wait.delay_10_us(20);
	BPS_dvi->set_current(BPS_ch, 15e-3,		RANGE_300_MA);	 
	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_10_RANGE);		// DVI_9_1
	wait.delay_10_us(20);
	BPS_dvi->set_voltage(BPS_ch, vfinal, 	VOLT_10_RANGE);		// DVI_9_1
	wait.delay_10_us(30);

	//BPS set 6V and it will clamp at Vshunt to enter Test Mode
	BPS_dvi->set_voltage(BPS_ch, 6.0, 		VOLT_10_RANGE);		// DVI_9_1
	wait.delay_10_us(50);
	//BPS set back to normal operating voltage for regular testing while it's still in Test Mode
	BPS_dvi->set_voltage(BPS_ch, vfinal, 	VOLT_10_RANGE);		// DVI_9_1
	wait.delay_10_us(30);

}
void VBPP_ILIM_NORM_Power_Up()
{
//                 |---BPP pin OVI takes over control any time after here.  
//                 |    __________________
//				   |  /
//			   /\  | /
//			  /  \ |/
//			 /    \/
//__________/
// Float BPP for ILIM_NORM power up after Vind voltage is established, so BPP is powered up by the TAP. 
// With 0.1uF cap on BPP pin, device will select ILIM_NORM state. After the first power up cycle, 
// ILIM_NORM is selected, connect BPP instrument to take over control of BPP voltage to turn off the TAP.

	//UV pin set to 0V
	VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_2_V);  
	VPIN_ovi->set_current(VPIN_ch, 10e-3,		RANGE_30_MA);		

	// Keep VBPP below VBPP_P before floating OVI on BPP pin
	// Slowly ramp up BPP voltage. Bandgap needs time to power up properly before VBPP raise up too high.
	// Problem gets worse at hot temp (125C). 1.8 Primary silicon needs more delay for proper power up.
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 4.0, 0.5);	// vstart, vstop, vstep

	// Float OVI
	BPP_ovi->set_current(BPP_ch,0.1e-6,RANGE_30_MA); //0.1e-6

	if(OPCODE == 4300 || OPCODE == 4500)	// At hot, device has less charge current. Need longer charge time
		wait.delay_10_us(30);		// Wait for device to be powerup by the TAP
	else
		wait.delay_10_us(60);	//15	// Wait for device to be powerup by the TAP

	// Take over control by OVI from TAP. Work with Float_BPP_ILIM_NORM function. 
	BPP_ovi->set_voltage(BPP_ch, gVBPP_P_Init +0.2, 	VOLT_10_RANGE);	// OVI_1_0
	wait.delay_10_us(10);
	BPP_ovi->set_current(BPP_ch, 30e-3,RANGE_30_MA);	// TAP should be off, ILIM_NORM should be selected at this point
	wait.delay_10_us(15);			// Wait until BPP voltage to settle down before capturing ILIM
}

void Connect_InvSyn_IM_New(int Vd_Input_Mode)
{	
	/********************************************************************************************
	 * When HV device turns off, Drain always overshoot above pullup level, which caused        *
	 * FW pin to go more negative than desired level, and clamped by the ESD diode. But this    *
	 * does affect the handshake.															    *
	 * Important NOTE: Make sure the rising edge of Drain or falling edge of FW are not longer  *
	 * than 0.5us. That will be at the margin of the communication window.						*
	 * 1.5us after device sees the rising edge of drain, secondary will send communication pulse*
	 * Primary will start looking for the the communication pulse from secondary from 1us to 2us*
	 * window.																					*
	 *			   _																			*
	 *			  / |																			*
	 *			 /  |																			*
	 *	Drain	/   |																			*
	 *----------    ------------------------													*
	 *----------	------------------------													*
	 *	FW		\___|__FW -100mV lev															*
	 *			|\	|				Secondary send												*
	 *			| \_|	       /|Communication pulses /|										*
	 *		    |   -1.5us-	 |/ |	internally		 / |										*
	 *			|------------|  |--------------------| |------									*
	 *          |																				*
	 *          | Primary Window to look for communication signal.								*
     *	    	|--------|       |-------------													*
	 *					1us     2us																*
	 ********************************************************************************************/
	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	if(LB_Rev>=8 || g_TurretCB)
	{
		//LT1016 LT/GND pin setup to be below GND so Comparator output can go below GND
		ovi_1->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA);
		if (OPCODE==4300 || OPCODE==4500)	ovi_1->set_voltage(OVI_CHANNEL_6, -1.8, VOLT_5_RANGE);	//jd pull down harder for hot test, has diode on loadboard
		else								ovi_1->set_voltage(OVI_CHANNEL_6, -3.0, VOLT_5_RANGE);	//revB inv_syn_circuit  (for tsoft ramp, sometimes secondary just skip sending the request)
		wait.delay_10_us(20);

		InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3,			RANGE_30_MA);	//Temporary
		wait.delay_10_us(10);
		if(Vd_Input_Mode == Low_Vd_Input)
		{
			if(MOSFET_SIZE==8)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.5,		VOLT_20_RANGE);	// OVI_1_4	
			if(MOSFET_SIZE==5)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, -3.0,		VOLT_20_RANGE);	// OVI_1_4	
			else					InvSyn_REF_ovi->set_voltage(InvSyn_ch, -3.0,		VOLT_20_RANGE);	// OVI_1_4	
									wait.delay_10_us(10);
		}
		if(Vd_Input_Mode == High_Vd_Input)
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, -1.0,		VOLT_20_RANGE);	// OVI_1_4	"Size x8 Vref max = 5V/2 (2.5V), so 3/2 = 1.5V (good margin)"

		if(Vd_Input_Mode == Low_Load_Vd_Input)
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, -5.0,		VOLT_20_RANGE);	// OVI_1_4. 08/30/17. HL changed from 1.0V to -5.0V for new Invsync Changed.

		if(Vd_Input_Mode == High_Temp_Vd_Input)
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 4.5,		VOLT_20_RANGE);	// Higher for hot test

		wait.delay_10_us(100);
		Close_relay(K8);	//Connect InvSyn_IM_IN  to Drain
		//pulse.do_pulse();
		Close_relay(K19);	//Connect InvSyn_IM_OUT to FW pin
		delay(5);
	}
	else	//LB_Rev 7 or older InvSync Circuit
	{
		//LT1016 LT/GND pin setup to be below GND so Comparator output can go below GND
		ovi_1->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA);
		if (OPCODE==4300 || OPCODE==4500)	ovi_1->set_voltage(OVI_CHANNEL_6, -1.8, VOLT_5_RANGE);	//jd pull down harder for hot test, has diode on loadboard
		else								ovi_1->set_voltage(OVI_CHANNEL_6, -3.0, VOLT_5_RANGE);	//revB inv_syn_circuit  (for tsoft ramp, sometimes secondary just skip sending the request)
		wait.delay_10_us(20);

		InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3,			RANGE_30_MA);	//Temporary
		wait.delay_10_us(10);
		if(Vd_Input_Mode == Low_Vd_Input)
		{
			if(MOSFET_SIZE==8)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.5,		VOLT_20_RANGE);	// OVI_1_4	
			if(MOSFET_SIZE==5)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.0,		VOLT_20_RANGE);	// OVI_1_4	
			else					InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.5,		VOLT_20_RANGE);	// OVI_1_4	
									wait.delay_10_us(10);
		}
		if(Vd_Input_Mode == High_Vd_Input)
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.0,		VOLT_20_RANGE);	// OVI_1_4	"Size x8 Vref max = 5V/2 (2.5V), so 3/2 = 1.5V (good margin)"

		if(Vd_Input_Mode == Low_Load_Vd_Input)
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.0,		VOLT_20_RANGE);	// OVI_1_4	

		if(Vd_Input_Mode == High_Temp_Vd_Input)
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 4.5,		VOLT_20_RANGE);	// Higher for hot test

		wait.delay_10_us(100);
		Close_relay(K8);	//Connect InvSyn_IM_IN  to Drain
		Close_relay(K19);	//Connect InvSyn_IM_OUT to FW pin
		delay(5);
	}

}
void Connect_InvSyn_IM(int Vd_Input_Mode)
{	
	/********************************************************************************************
	 * When HV device turns off, Drain always overshoot above pullup level, which caused        *
	 * FW pin to go more negative than desired level, and clamped by the ESD diode. But this    *
	 * does affect the handshake.															    *
	 * Important NOTE: Make sure the rising edge of Drain or falling edge of FW are not longer  *
	 * than 0.5us. That will be at the margin of the communication window.						*
	 * 1.5us after device sees the rising edge of drain, secondary will send communication pulse*
	 * Primary will start looking for the the communication pulse from secondary from 1us to 2us*
	 * window.																					*
	 *			   _																			*
	 *			  / |																			*
	 *			 /  |																			*
	 *	Drain	/   |																			*
	 *----------    ------------------------													*
	 *----------	------------------------													*
	 *	FW		\___|__FW -100mV lev															*
	 *			|\	|				Secondary send												*
	 *			| \_|	       /|Communication pulses /|										*
	 *		    |   -1.5us-	 |/ |	internally		 / |										*
	 *			|------------|  |--------------------| |------									*
	 *          |																				*
	 *          | Primary Window to look for communication signal.								*
     *	    	|--------|       |-------------													*
	 *					1us     2us																*
	 ********************************************************************************************/
	//Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
//
	if(LB_Rev>=8 || g_TurretCB)
	{
		//LT1016 LT/GND pin setup to be below GND so Comparator output can go below GND
		ovi_1->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA);
		if (OPCODE==4300 || OPCODE==4500)	ovi_1->set_voltage(OVI_CHANNEL_6, -1.8, VOLT_5_RANGE);	//jd pull down harder for hot test, has diode on loadboard
		//else								ovi_1->set_voltage(OVI_CHANNEL_6, -3.0, VOLT_5_RANGE);	//revB inv_syn_circuit  (for tsoft ramp, sometimes secondary just skip sending the request)
		else								ovi_1->set_voltage(OVI_CHANNEL_6, -1.8, VOLT_5_RANGE);	//revB inv_syn_circuit  (for tsoft ramp, sometimes secondary just skip sending the request)
		wait.delay_10_us(20);

		InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3,			RANGE_30_MA);	//Temporary
		wait.delay_10_us(10);
		if(Vd_Input_Mode == Low_Vd_Input)
		{
			if(MOSFET_SIZE==8)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.5,		VOLT_20_RANGE);	// OVI_1_4	
			if(MOSFET_SIZE==5)		InvSyn_REF_ovi->set_voltage(InvSyn_ch, -3.0,		VOLT_20_RANGE);	// OVI_1_4	
			else					InvSyn_REF_ovi->set_voltage(InvSyn_ch, -3.0,		VOLT_20_RANGE);	// OVI_1_4	
									//wait.delay_10_us(10);
		}
		if(Vd_Input_Mode == High_Vd_Input)
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.0,		VOLT_20_RANGE);	// OVI_1_4	"Size x8 Vref max = 5V/2 (2.5V), so 3/2 = 1.5V (good margin)"

		if(Vd_Input_Mode == Low_Load_Vd_Input)
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 1.0,		VOLT_20_RANGE);	// OVI_1_4. 

		if(Vd_Input_Mode == High_Temp_Vd_Input)
			InvSyn_REF_ovi->set_voltage(InvSyn_ch, 4.5,		VOLT_20_RANGE);	// Higher for hot test

		//wait.delay_10_us(10);
		Close_relay(K8);	//Connect InvSyn_IM_IN  to Drain
		Close_relay(K19);	//Connect InvSyn_IM_OUT to FW pin
		delay(4);
	}
}

void Disconnect_InvSyn_IM()
{	
	// !!! Make sure Drain voltage is less than +/-12V to avoid damaging InvSyn_IM
	//Disconnect InvSyn_IM_OUT from FW pin
	Open_relay(K19);
	//Disconnect InvSyn_IM_IN from drain
	Open_relay(K8);		
	wait.delay_10_us(20);

	InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3,	RANGE_30_MA);	
	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0.0,		RANGE_10_V);	// OVI_1_4	
	//LT1016 LT/GND pin 
	ovi_1->set_current(OVI_CHANNEL_6, 30e-3,		RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_6, 0.0,			VOLT_5_RANGE);
	wait.delay_10_us(20);
}

void Primary_Normal_Mode_Power_Up(int ILIM_Mode, float v_final)
{
	// To read anti-fuses
	D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
	D_dvi->set_voltage(D_ch, 6.0, 		VOLT_50_RANGE);	// DVI_11_0
	wait.delay_10_us(50);

	if (ILIM_Mode == ILIM_NORM)
		VBPP_ILIM_NORM_Power_Up();
	else
		VBPP_Power_Up(ILIM_Mode);

	D_dvi->set_voltage(D_ch, v_final,	VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(20);	

}


void Primary_Test_Mode_Power_Up(int ILIM_Mode, float v_final)
{
	D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
	D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(50);
	VBPP_Power_Up(ILIM_Mode);
	D_dvi->set_voltage(D_ch, v_final,	VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(30);	

}

void Setup_Ilimit_Pedestal(int Ilim_mode)
{
	// Inductors are designed to provide 4us on time for ILIM_NORM
	// Pedestals are only needed for ILIM+1 to achieve 4us on time
	float Vpedestal=0.0;

	if (Ilim_mode == ILIM_NORM || Ilim_mode == ILIM_Jit18K)	// No Pedestal for ILIM
	{
		Open_relay(K1);			// ILIM Pedestal	
		Open_relay(KIM3);		// ILIM Pedestal No pedestal. DVI pull up set to 0V
	}
	//else if(Ilim_mode == ILIM_INCR)
	else
	{
		Close_relay(K1);		// ILIM Pedestal	
		// Use Rped1 for ILIM+1
		Open_relay(KIM3);		// ILIM Pedestal Use resistor Rpd2
	}
	delay(4);

	if(Ilim_mode == ILIM_NORM)
		Vpedestal = 0.0;
	//else if(Ilim_mode == ILIM_INCR)
	else
		Vpedestal = gVped_Ilim_Incr;

	// Charge up pedestal capacitor early. 
	// 10uF * 50V/300mA = 1.67ms
	D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
	D_dvi->set_voltage(D_ch, Vpedestal, 	VOLT_50_RANGE);	// DVI_11_0
	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_VOLTAGE);
}

//=================== INNOSW XP gage digitizer functions ===================
void INNO_Gage_ChanAB_setup(float ilim_trig_lev)
{
	// Split this setup portion out from Gage_Capture_Ilim() function due to 4ms excution time on each input control
	// and trig control statement. Only excute this once for the whole test program.
	// 03/15/13 - As of today, Gage Razor changing range still takes 34ms. Therefore, only one range is used for the entire program
	//			  for now. In the future, when the new Gage Razor driver without long delay is available,
	//			  this can be modified to adjust ranges for different ILIM. 
	int vrng_a=0, vrng_b=0;
	float ChA_vrng =0.0, ChB_vrng =0.0;
	float Idmax_exp=0.0, Vdmax_exp=0.0;
	//float ilim_trig_lev =0.0;

	if(SAMPLE_SIZE > GAGE_WAVEFORM_BUFFER_SIZE)
	{ 
		if(gDEBUG)
			MessageBox(NULL,"Error: Sample_size is greater than GAGE_WAVEFORM_BUFFER_SIZE",Func_name, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		return;
	}

	Idmax_exp = gIlim_Incr_max*Ilim_gain *1.2;// Increase 20% to cover the highest ILIM pretrim
//	ilim_trig_lev = 0.05;
	//ilim_trig_lev = 0.10;	// Set a higher trigger level to have a consistency point of capture. HQL 07/08/14

	if(Idmax_exp < 0.5)	
	{	
		vrng_a = GAGE_PM_500_MV;
		ChA_vrng =0.5;
	}
	else if(Idmax_exp >= 0.5 && Idmax_exp < 1.0)
	{		
		vrng_a = GAGE_PM_1_V;
		ChA_vrng = 1.0; 
	}
	else if(Idmax_exp >= 1.0 && Idmax_exp < 2.0)	
	{	
		vrng_a = GAGE_PM_2_V;
		ChA_vrng = 2.0; 
	}
	else if(Idmax_exp >= 2.0)
	{	
		vrng_a = GAGE_PM_5_V;
		ChA_vrng = 5.0;
	}

	vrng_b = GAGE_PM_5_V;
	ChB_vrng = 5.0;

//	Set up Buffer Clamp
	BC_ovi->set_current(BC_ch, 30e-3,		RANGE_30_MA);
	BC_ovi->set_voltage(BC_ch, (ChB_vrng-0.6),VOLT_5_RANGE);	// OVI_1_3 Account for one diode drop

	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,SAMPLE_SIZE); 

	gage_input_control_xp (GAGE_CHAN_A,			// channel
			GAGE_INPUT_ENABLE,					// enable / disable
			GAGE_DC,							// coupling
			vrng_a|GAGE_1_MOHM_INPUT);			// range, impedance

	gage_input_control_xp (GAGE_CHAN_B,			// channel
			GAGE_INPUT_ENABLE,					// enable / disable
			GAGE_DC,							// coupling
			vrng_b|GAGE_1_MOHM_INPUT);			// range, impedance

	gage_trigger_control_xp (GAGE_CHAN_A,		// trigger source
			GAGE_DC,							// coupling for ext trig
			vrng_a,								// range for CHA trigger
			GAGE_NEGATIVE,						// slope
			ilim_trig_lev,						// Tigger level in Volt
			SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE
}

void INNO_Gage_ChanB_setup(float v_trig_lev)
{
	// Setup Digitizer Channel B//
	int vrng_b = GAGE_PM_5_V;

	// Channel B setup //
	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,SAMPLE_SIZE); 

	gage_input_control_xp (GAGE_CHAN_B,			// channel
			GAGE_INPUT_ENABLE,					// enable / disable
			GAGE_DC,							// coupling
			vrng_b|GAGE_1_MOHM_INPUT);			// range, impedance

	gage_trigger_control_xp (GAGE_CHAN_B,		// trigger source
			GAGE_DC,							// coupling for ext trig
			vrng_b,								// range for CHA trigger
			GAGE_POSITIVE,						// slope
			v_trig_lev,							// V trigger level 
			SAMPLE_SIZE);						// 20ns * GAGE_WAVEFORM_BUFFER_SIZE
}

void INNO_Gage_ChanB_ToffMax_setup()
{
	// 4ms excution time on each input control and trig control statement.
	// 03/15/13 - As of today, Gage Razor changing range still takes 34ms. Therefore, only one range is used for the entire program
	//			  for now. In the future, when the new Gage Razor driver without long delay is available,
	//			  this can be modified to adjust ranges for different ILIM. 
	int vrng_a=0, vrng_b=0;
	float ChA_vrng =0.0, ChB_vrng =0.0;
	float Idmax_exp=0.0, Vdmax_exp=0.0;
	float ilim_trig_lev =0.0;

	if(SAMPLE_SIZE > GAGE_WAVEFORM_BUFFER_SIZE_ToffMax)
	{ 
		if(gDEBUG)
			MessageBox(NULL,"Error: Sample_size is greater than GAGE_WAVEFORM_BUFFER_SIZE_ToffMax",Func_name, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		return;
	}

	vrng_b = GAGE_PM_5_V;
	ChB_vrng = 5.0;

//	Set up Buffer Clamp
	BC_ovi->set_current(BC_ch, 30e-3,		RANGE_30_MA);
	BC_ovi->set_voltage(BC_ch, (ChB_vrng-0.6),VOLT_5_RANGE);	// OVI_1_3 Account for one diode drop

	Gage_Setup_Acquisition_xp(SAMPLE_RATE_Hz,SAMPLE_SIZE); 

	gage_input_control_xp (GAGE_CHAN_B,		// channel
			GAGE_INPUT_ENABLE,					// enable / disable
			GAGE_DC,							// coupling
			vrng_b|GAGE_1_MOHM_INPUT);			// range, impedance

	// Don't set input_control_trigger to avoid test time increase when it is changed in ILIM capture. 
	// Will use force trigger for ToffMax-S test
}

void Gage_Capture_ToffMax()
{

}

void Gage_Capture_Ilim(int Ilim_mode, float InvSync_vREF)
{
	Pulse pulse(PULSE_RISING_EDGE,10e-6);
	int		SR_AF_temp[100]	 = {0};

	Close_relay(K3);				// Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
	Close_relay(K37);				// Connect 1uF to BPP pin via K37
	delay(4);

	Power_Up_Primary_BypassWL_TM5(Ilim_mode);

	Powerup_Secondary_in_Testmode(gProgRead_AFreg_S, 0, 0);
	BPS_dvi->set_voltage(BPS_ch, gVBPS_final,	RANGE_10_V);
	//wait.delay_10_us(20);

	// Read/write AF register
	Read_Secondary_AF_Reg (SR_AF_temp);	// must be followed by write
	// MINNO Trim bits
	// PROG mode to program out XFWPK bit to disable FWPK switching
	// Also Program out the External REQ option
	// Write corrected bits into AF register
	SR_AF_temp[5]=0;				// Programming out PK1&Xspeedload
	SR_AF_temp[6]=0;				// Programming out PK2
	SR_AF_temp[7]=0;				// Programming out PK3
	SR_AF_temp[22]=0;				// Programming out PKdig<1>
	SR_AF_temp[23]=0;				// Programming out PKdig<2>
	SR_AF_temp[24]=0;				// Programming out PKdig<3>
	SR_AF_temp[25]=0;				// Programming out PKdig<4>
	SR_AF_temp[42]=1;				// Programming in  DOPL
	SR_AF_temp[44]=1;				// Programming in  FWPK
	Write_Secondary_AF_Reg (SR_AF_temp);

	VO_dvi->set_voltage(VO_ch, 0.0,		RANGE_5_V);	// DVI_9_0
	wait.delay_10_us(10);

	//7. Provide negative pulse on FW to indicate end of Programming.  (FW go below -100mV)
	FW_dvi->set_voltage(FW_ch, -0.5,	RANGE_10_V);	// DVI_11_1
	wait.delay_10_us(10);
	FW_dvi->set_voltage(FW_ch, 5.0,		RANGE_10_V);	// DVI_11_1
	wait.delay_10_us(10);

	//8. Clock VOUT to TestMode#
	Secondary_Vout_Clock_to_Testmode(gProgReadTestMode1_FB_S);

	REQ_ovi->set_voltage(REQ_ch, gREQ_2V, 		RANGE_5_V);
	//REQ_ovi->set_voltage(REQ_ch, gREQ_V_Idle, 		RANGE_5_V);
	//wait.delay_10_us(10);

	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);				// Connect SR to 5nF
	Open_relay(K18);				// Disconnect FW from DVI
	Open_relay(K21);				// Disconnect FW from DDD
	Open_relay(K27);				// Disconnect VO from DDD
	//delay(4);

	Connect_InvSyn_IM(Low_Load_Vd_Input);

	VBPP_ramp_down(gVBPP_P_final, gVBPP_P_s_final, 10e-3);	// vstart, vstop, vstep	B3 material
	//wait.delay_10_us(10);

	InvSyn_REF_ovi->set_voltage(InvSyn_ch, 10.0,	RANGE_20_V);	// Avoid noise coupling over to InvSynCircuit to FW
	wait.delay_10_us(10); 

	ddd_7->ddd_set_hi_level(gREQ_2V);
	wait.delay_10_us(10);
	ddd_7->ddd_set_lo_level(gREQ_V_Idle);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	DDD_Wait_Pattern_End(High_pat_REQ_start, High_pat_REQ_stop);

	Close_relay(K17);				// Connect REQ to DDD
	//delay(4);

	PV3_Check_Charge(RANGE_100_V);
	pv3_4->charge_off();
	PV3_Connect_Drain_and_DriveON(Vind_RM);		//Drive Voltage

	ddd_7->ddd_run_pattern(Low_pat_REQ_start, Low_pat_REQ_stop);
	DDD_Wait_Pattern_End(Low_pat_REQ_start, Low_pat_REQ_stop);

	// Connect Inductor Module to Drain
	Open_relay(K3);					// Drain to RL pullup
	if ((strcmp(gDevType, "DLM") == 0) && gDLM_Size == 8 && (gILIM_TARGET_S > 1.8 && gILIM_TARGET_S < 1.9))
		Close_relay(KIM2);				// Connect Vind to CT2+ to CT2-
	else
		Close_relay(KIM1);				// Connect Vind to CT2+ to CT2-
	Close_relay(K9);				// Connect CT2- to Drain
	if (gDLM_Size > 7)
	{
		Close_relay(K22);			// Connect compensation winding on CT2877
	}
	//delay(4);

	Setup_Ilimit_Pedestal(Ilim_mode);
	delay(1);

	InvSyn_REF_ovi->set_voltage(InvSyn_ch, InvSync_vREF,	RANGE_20_V);
	wait.delay_10_us(10);

	// Enable RTM by switch >110kHz for >200usec. //
	//ddd_7->ddd_run_pattern(FB_125kHz_pulse_start_X,FB_125kHz_pulse_stop_X);
	//DDD_Wait_Pattern_End(FB_125kHz_pulse_start_X,FB_125kHz_pulse_stop_X);
	ddd_7->ddd_run_pattern(FB_125kHz_pulse_start_X,FB_125kHz_pulse_stop_X);
	DDD_Wait_Pattern_End(FB_125kHz_pulse_start_X,FB_125kHz_pulse_stop_X);

	Gage_Start_Capture();

	if (Ilim_mode == ILIM_Jit18K)
	{
		ddd_7->ddd_run_pattern(FB_18kHz_pulse_start,FB_18kHz_pulse_stop);
		DDD_Wait_Pattern_End(FB_18kHz_pulse_start,FB_18kHz_pulse_stop);
	}
	else
	{
		// Setup to have ILIM switch for 18pulses, then OFF 30us, ON 10us, OFF 200us and ON for 3 pulses of 100kHz
		ddd_7->ddd_run_pattern(FB_100kHz_ILIM_pulse_start,FB_100kHz_ILIM_pulse_stop);
		DDD_Wait_Pattern_End(FB_100kHz_ILIM_pulse_start,FB_100kHz_ILIM_pulse_stop);
	}

	Gage_Wait_For_Capture_Complete();

	PV3_Disconnect_Drain_and_DriveOFF();
}

void Gage_Capture_Ilim_SSS(int Ilim_mode, float InvSync_vREF)
{
	Pulse pulse(PULSE_RISING_EDGE,10e-6);
	// **** Synchronous Handshake PowerUp (Secondary in Normal Mode) ******
	Close_relay(K3);				// Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
	Close_relay(K37);				// Connect 1uF to BPP pin via K37
	Close_relay(K17);				// Connect REQ to DDD
	SR_dvi2k->open_relay(CONN_FORCE1);
	SR_dvi2k->open_relay(CONN_SENSE1);
	Close_relay(K5);				// Connect SR to 5nF
	delay(4);

	Power_Up_Primary_BypassWL_TM5(Ilim_mode);

	// Connect Inductor to Drain
	Open_relay(K3);					// Drain to RL pullup
	delay(5);			//try to see if it would improves the izpost intermittent failures  cxie per Hiep 5/24/19
	Close_relay(K9);				// Connect CT2- to Drain
	if ((strcmp(gDevType, "DLM") == 0) && gDLM_Size == 8 && (gILIM_TARGET_S > 1.8 && gILIM_TARGET_S < 1.9))
		Close_relay(KIM2);				// Connect Vind to CT2+ to CT2-
	else
		Close_relay(KIM1);				// Connect Vind to CT2+ to CT2-
	Close_relay(K1);				// Connect Iped to CT2+ to CT2-
	Close_relay(KIM3);				// ILIM Pedestal Use resistor Rpd2
	if (gDLM_Size > 7)
	{
		Close_relay(K22);			// Connect compensation winding on CT2877
	}
	delay(5);			//try to see if it would improves the izpost intermittent failures  cxie per Hiep 5/24/19


	// Setup Pedestal
	D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);
	D_dvi->set_voltage(D_ch, 45.0, 			VOLT_50_RANGE);	// DVI_11_0
	D_dvi->set_meas_mode(D_ch,				DVI_MEASURE_VOLTAGE);

	VO_dvi->set_current(VO_ch, 300.0e-3,	RANGE_300_MA);	
	VO_dvi->set_voltage(VO_ch, 3.0, 		VOLT_5_RANGE);	// DVI_9_0  "If Vout bring high, this will bring vBPS high"

	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);

	Connect_InvSyn_IM(Low_Load_Vd_Input);
	InvSyn_REF_ovi->set_voltage(InvSyn_ch, InvSync_vREF,	RANGE_20_V);

	PV3_Check_Charge(RANGE_100_V);
	pv3_4->charge_off();

	PV3_Connect_Drain_and_DriveON(Vind_RM); //Drive Voltage

	Gage_Start_Capture();

	BPS_dvi->set_current(BPS_ch, 300e-3,					RANGE_300_MA);	 
	VBPS_Power_Up(gVBPS_P_Init-0.3);

	ddd_7->ddd_set_hi_level(gREQ_2V);
	wait.delay_10_us(10);
	ddd_7->ddd_set_lo_level(gREQ_V_Idle);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	DDD_Wait_Pattern_End(High_pat_REQ_start, High_pat_REQ_stop);

	BPS_dvi->set_voltage(BPS_ch, gVBPS_final, 	VOLT_10_RANGE);
	// Secondary vBPS_plus	//Connect REQ pin to DDD to run 100KHz pulses
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(High_pat_REQ_start, High_pat_REQ_stop);
	DDD_Wait_Pattern_End(High_pat_REQ_start, High_pat_REQ_stop);
	ddd_7->ddd_end_pattern(FB_100kHz_loop_pulse_stop);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern();	// Start the 100kHz signal
	wait.delay_10_us(500);		// Use fixed delay here!!
	ddd_7->ddd_stop_pattern();	// Stop  the 100kHz signal
	wait.delay_10_us(10);

	BPP_ovi->set_voltage(BPP_ch, gVBPP_P_s_final, RANGE_10_V);
	wait.delay_10_us(20);

	Gage_Wait_For_Capture_Complete();

	PV3_Disconnect_Drain_and_DriveOFF();
}

void Gage_Find_Ilim_MINNO(float *Idmax_ave, float *DiDt_ave, float *Ton_ave, float *Rdson_peak_ave, float *Rdson_spec_ave)
{
	*Idmax_ave		= 0.0;
	*DiDt_ave		= 0.0;
	*Ton_ave		= 0.0;
	*Rdson_peak_ave	= 0.0;
	*Rdson_spec_ave	= 0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Idmax_ave		= DEFAULT_VALUE;
		*DiDt_ave		= DEFAULT_VALUE;
		*Ton_ave		= DEFAULT_VALUE;
		*Rdson_peak_ave	= DEFAULT_VALUE;
		*Rdson_spec_ave	= DEFAULT_VALUE;
		//gILIM_pct_1stP	= DEFAULT_VALUE;
		//gILIM_pct_2ndP	= DEFAULT_VALUE;
		//gILIM_pct_3rdP	= DEFAULT_VALUE;
		return;
	}

	int PULSE_NUM_NEED		= 0;	// Define min pulses numbers need to be caputre. 4*7.5us = 30us. 2K sample allows 40us. 4K -> 80us
	int PULSE_NUM_PROCESSED	= 0;	// Actual num pulses Processed. Exclude first pulse in ave calculation 
	int pulse_cnt			= 0;
	int icnt				= 0;

	// Variables for ILIM peak tests
	float pulse_width[400]	= {};
	float Ton[400]			= {};
	float Toff[400]			= {};
	float DiDt[400]			= {};
	int	  ACgnd_addr[400]	= {};				// GND is taken before device turns on

	// Variables for Rdson_spec tests at 10% ILIM_NORM level
	float Ilim_spec			= 0.0;
	float Vdson_spec[400]	= {};
	float Idson_spec[400]	= {};
	float Rdson_spec[400]	= {};
	float Vdson_peak_ave	= 0.0;
	int	  Id_spec_addr[400]	= {};
	float Id_temp			= 0.0;
	float Id_one_data_pts	= 0.0;
	
	int	  ave_start_pulse	= 0;
	int	  ave_pulses		= 0;
	int	  ave_end_pulse		= 0;

	float Period			= 0.0;
	int	  Sample_per_cycle	= 0;

	int	  RTM_30us			= 0;
	int	  RTM_200us			= 0;

	char  wave_name_Id[150]		= "/0";
	char  wave_name_Vd[150]		= "/0";
	char  debug_file_name[150]	= "/0";

	PULSE_NUM_NEED = 24;	// If fosc = 100kHz, every pulse would take 10us.  27  pulses would take 270us

	Period = 1 / (100e3 - 10e3);				// Takes care of device with Jitter up to 10kHz from 100kHz
	SAMPLE_RATE_s = 20e-9;
	Sample_per_cycle = Period / SAMPLE_RATE_s;

	for (icnt = 0; icnt < PULSE_NUM_NEED * 2; icnt++)
	{
		gIdmax[icnt]		= DEFAULT_VALUE;
		gIdmax_addr[icnt]	= 0;
	}

	// Transfer data to PC (XP)
	Gage_Transfer_Data(GAGE_CHAN_A);			// transfer data to Gage_chan_a_voltage array
	if (FIND_RDSON_Peak_FLAG || FIND_RDSON_Spec_FLAG)
		Gage_Transfer_Data(GAGE_CHAN_B);		// transfer data to Gage_chan_b_voltage array

	PULSE_NUM_PROCESSED = Gage_Find_Ipeak(Gage_chan_a_voltage, SAMPLE_SIZE, SAMPLE_RATE_s, Ilim_gain, PULSE_NUM_NEED+2, ACgnd_addr, gIdmax_addr, gIdmax, DiDt);

	pulse_cnt = 0;
	// Pulse width
	pulse_width[pulse_cnt] = gIdmax_addr[pulse_cnt] - ACgnd_addr[pulse_cnt];

	// Ton
	Ton[pulse_cnt] = (gIdmax_addr[pulse_cnt] - ACgnd_addr[pulse_cnt]) * SAMPLE_RATE_s;

	for (pulse_cnt = 1; pulse_cnt < PULSE_NUM_PROCESSED; pulse_cnt++)
	{
		// Pulse width
		pulse_width[pulse_cnt] = gIdmax_addr[pulse_cnt] - ACgnd_addr[pulse_cnt];

		// Ton
		Ton[pulse_cnt] = (gIdmax_addr[pulse_cnt] - ACgnd_addr[pulse_cnt]) * SAMPLE_RATE_s;

		// Toff
		Toff[pulse_cnt - 1] = (ACgnd_addr[pulse_cnt] - gIdmax_addr[pulse_cnt - 1]) * SAMPLE_RATE_s;

		if (Toff[pulse_cnt - 1] >  20e-6 && Toff[pulse_cnt - 1] <  50e-6) RTM_30us	= pulse_cnt;
		if (Toff[pulse_cnt - 1] > 180e-6 && Toff[pulse_cnt - 1] < 240e-6) RTM_200us	= pulse_cnt;

		// Locate Id_spec, Vd_spec location and calculate Rdson_spec
		if(FIND_RDSON_Spec_FLAG && DiDt[pulse_cnt] != 0.0 && pulse_cnt > 3)
		{
			if (MOSFET_SIZE==2)	Ilim_spec = 0.32 * gILIM_TARGET_S;	// Inno2's 550mA IM gives ~100mA pedestal.  30% -> Need more room away from noise
			else				Ilim_spec = 0.25 * gILIM_TARGET_S;	// !!! Use 25-30% Per Alex

			Id_spec_addr[pulse_cnt] = int(gIdmax_addr[pulse_cnt] - (gIdmax[pulse_cnt]- Ilim_spec)/(DiDt[pulse_cnt] *SAMPLE_RATE_s *1e6));
			Id_temp = Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]] / Ilim_gain;	//Id_temp must be > 0 since it's 25-30% of ILIM_target
			Id_one_data_pts = DiDt[pulse_cnt] * SAMPLE_RATE_s * 1e6; // Amps
			icnt = 0;
			while ((Ilim_spec - Id_temp) > Id_one_data_pts && icnt < 100)
			{
				Id_spec_addr[pulse_cnt]++;
				Id_temp = Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]] / Ilim_gain;
				icnt++;
			}
			Id_spec_addr[pulse_cnt] += 2;	// Move away from ringing

			if ((gIdmax_addr[pulse_cnt] - Id_spec_addr[pulse_cnt]) < pulse_width[pulse_cnt])
			{
				Vdson_spec[pulse_cnt] = Gage_chan_b_voltage[Id_spec_addr[pulse_cnt]] * BUFgain;
				Idson_spec[pulse_cnt] = Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]] / Ilim_gain;
				if (Idson_spec[pulse_cnt] != 0.0)
					Rdson_spec[pulse_cnt] = Vdson_spec[pulse_cnt] / (Idson_spec[pulse_cnt]);
				else
					Rdson_spec[pulse_cnt] = 0.0;
			}
			else 
				Rdson_spec[pulse_cnt] = 0.0;
		}
	}

	// Average Peak results
	if (PULSE_NUM_PROCESSED >= PULSE_NUM_NEED)
	{
		// Number of pulses used for ILIM_ave, Ton_ave, Didt_ave, Vdson_peak_ave, Rdson_spec_ave
		ave_start_pulse	= 6;	//good for both size x8 and x5
		ave_pulses		= 10;
		ave_end_pulse	= ave_start_pulse + ave_pulses;
		// Taking average Needed pulses peak values (Must skip the first 3 pulses since they are not at ILIM)
		for (pulse_cnt =ave_start_pulse; pulse_cnt< ave_end_pulse; pulse_cnt++)
		{
			*Idmax_ave += gIdmax[pulse_cnt];
			*Ton_ave   += Ton[pulse_cnt];
			*DiDt_ave  += DiDt[pulse_cnt];
			if( FIND_RDSON_Peak_FLAG)
				Vdson_peak_ave += Gage_chan_b_voltage[gIdmax_addr[pulse_cnt - 1]] * BUFgain;
			if (FIND_RDSON_Spec_FLAG)
				*Rdson_spec_ave += Rdson_spec[pulse_cnt];
		}

		if (FIND_RDSON_Peak_FLAG && *Idmax_ave != 0.0)
		{
			*Rdson_peak_ave = Vdson_peak_ave / (*Idmax_ave);
		}
		else
			*Rdson_peak_ave = DEFAULT_VALUE;

		if(FIND_RDSON_Spec_FLAG)
			*Rdson_spec_ave /= (ave_pulses+1e-23);
		else
			*Rdson_spec_ave = DEFAULT_VALUE;

		*Idmax_ave /= ave_pulses;
		*Ton_ave   /= ave_pulses;
		*DiDt_ave  /= ave_pulses;

		//ILIM_NORM: set global variables 
		if (WAVE_NAME == "ILIM_NORM")
		{
			//Reset 1st, 2nd, 3rd ILIM_Ramp variables
			gTon_1stP		= 0.0;
			gTon_2ndP		= 0.0;
			gTon_3rdP		= 0.0;
			gToff_1stP		= 0.0;
			gToff_2ndP		= 0.0;
			gToff_3rdP		= 0.0;
			gILIM_pct_1stP	= 0.0;
			gILIM_pct_2ndP	= 0.0;
			gILIM_pct_3rdP	= 0.0;
			gRTM_Slope		= 0.0;

			gILIM_pct_1stP	= gIdmax[RTM_200us]     / *Idmax_ave * 100.0;
			gILIM_pct_2ndP	= gIdmax[RTM_200us + 1] / *Idmax_ave * 100.0;
			gILIM_pct_3rdP	= gIdmax[RTM_200us + 2] / *Idmax_ave * 100.0;

			gTon_1stP		= Ton[RTM_200us];
			gTon_2ndP		= Ton[RTM_200us + 1];
			gTon_3rdP		= Ton[RTM_200us + 2];

			gToff_1stP		= Toff[RTM_200us];
			gToff_2ndP		= Toff[RTM_200us + 1];
			gToff_3rdP		= Toff[RTM_200us + 2];

			// RTM (Ramp Time Modulation) Slope
			// Expect the final ILIM_peak to be the first pulse of ILIM ramp.  It should be in the range of 200mA to 300mA
			if (gIdmax[RTM_200us] > 50e-3)
			{
				//gRTM_Slope = ( gIdmax[PULSE_NUM_PROCESSED-2] - gIdmax[PULSE_NUM_PROCESSED-3] ) / Toff[PULSE_NUM_PROCESSED-3]*1e-6;
				gtDelta_RTM_Slope	= Ton[RTM_30us] + Toff[RTM_30us - 1];
				gi_pct_drop_RTM		= ((gIdmax[RTM_30us] / gIdmax[RTM_30us - 1]) - 1.0) * 100.0;
				gRTM_Slope = gi_pct_drop_RTM / gtDelta_RTM_Slope * 1e-6;
				gRTM_Slope = ( (gIdmax[RTM_30us] - gIdmax[RTM_30us - 1]) / gIdmax[RTM_30us - 1] * 100) / 
							 ( gtDelta_RTM_Slope - 10e-6 ) * 1e-6;
				if (DEBUG==1 && gDEBUG)
					printf("\nIdmax = %.2f, Id_drop to = %.2f, time_drop = %.2f us, pct_drop = %.2f\n", gIdmax[PULSE_NUM_PROCESSED-9], gIdmax[PULSE_NUM_PROCESSED-8], Ton[PULSE_NUM_PROCESSED-8] + Toff[PULSE_NUM_PROCESSED-9]*1e6, gRTM_Slope);

				gtDelta_RTM_Slope_200us = Ton[RTM_200us] + Toff[RTM_200us - 1];
				gILIM_200us_S = gIdmax[RTM_200us];
				gILIM_200us_pct_S = ((gIdmax[RTM_200us] / gIdmax[RTM_200us - 1]) - 1.0) * 100.0;
			}
		}
	}
	else 
	{
			*Idmax_ave = DEFAULT_VALUE;
			*Ton_ave   = DEFAULT_VALUE;
			*DiDt_ave  = DEFAULT_VALUE;
			if (DEBUG == 1 && gDEBUG)
				MessageBox(NULL, "Error: PULSE_NUM_PROCESSED is less than PULSE_NUM_NEED",Func_name, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}

	//DEBUG text File
	if(DEBUG==1 && gDEBUG)
	{
		int i=0;
		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, DevName); 
		strcat (debug_file_name, "_");
		strcat (debug_file_name, WAVE_NAME);
		strcat (debug_file_name, "_debug.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print to file
		fprintf(fpr,"WAVE_NAME= %s \n\n",WAVE_NAME);

		//measured values
		fprintf(fpr,"ILIM(Idmax_ave) = %.3f A,  *DiDt_ave = %.2f A/us,  *Ton_ave= %.2f us\n",*Idmax_ave,  *DiDt_ave,  *Ton_ave*1e6);

		//RDSon
		if(FIND_RDSON_Peak_FLAG)
			fprintf(fpr,"Rdson_peak_ave = %.3f ohms (Vdson_peak_ave=%.3f V , Idmax_ave=%.3f A)\n",
				*Rdson_peak_ave,Vdson_peak_ave/ave_pulses,	*Idmax_ave);

		//pulses
		fprintf(fpr,"\n  PULSE_NUM_PROCESSED=%i\n",PULSE_NUM_PROCESSED);
		if(WAVE_NAME == "ILIM_NORM")
		{
			fprintf(fpr,"  ILIM, Ton, didt averaged from pulse %i to pulse %i\n\n", ave_start_pulse,ave_end_pulse);
			fprintf(fpr,"  ILIM_Lo taken from pulse %i\n", PULSE_NUM_PROCESSED-3);
			fprintf(fpr,"  ILIM_Med taken from pulse %i\n", PULSE_NUM_PROCESSED-2);
			fprintf(fpr,"  ILIM_Hi taken from pulse %i\n", PULSE_NUM_PROCESSED-1);
		}

		fprintf(fpr,"\nPeak Data: \n",WAVE_NAME);
		//Peak data
		for(i=0; i<PULSE_NUM_PROCESSED; i++)
		{
			if(gIdmax[i] > 0)
			fprintf(fpr,"ILIM_Pulse %i = %.1fmA, Ton_Pulse = %.1fus, Toff_Pulse = %.1fus, Freq = %.1fkHz, Ton_addr=%i, pk_addr=%i\n", 
				i, gIdmax[i]*1000, Ton[i]*1e6, Toff[i]*1e6, 1/(Ton[i]+Toff[i])/1000,ACgnd_addr[i],gIdmax_addr[i]);

			if(FIND_RDSON_Peak_FLAG)
			{
				fprintf(fpr,"  Vdson_peak %i = %.3f V \n",i,Gage_chan_b_voltage[gIdmax_addr[i]]*BUFgain);
				fprintf(fpr,"  Rdson_peak %i = %.3f ohm \n",i,(Gage_chan_b_voltage[gIdmax_addr[i]]*BUFgain)/gIdmax[i]);
			}
		}
		fprintf (fpr, "End of Peaks\n");
		fclose(fpr);
	}

	//DEBUG AWAV Files
	if(DEBUG==1 && gDEBUG)
	//if(DEBUG==1)
	{
		strcpy (wave_name_Id, WAVE_NAME);
		strcat (wave_name_Id, "_Id"); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		if(FIND_RDSON_Peak_FLAG || FIND_RDSON_Spec_FLAG)
		{
			strcpy (wave_name_Vd, WAVE_NAME);
			strcat (wave_name_Vd, "_Vd"); 
			Create_Awav_xp(wave_name_Vd, Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);
		}
		WAVE_NAME = "NoWaveName";
	}

	// Reset Flags
	FIND_RDSON_Peak_FLAG = 0;
	FIND_RDSON_Spec_FLAG = 0;
	gFind_ILIM_Jitter	 = 0;
}

void Gage_Find_Ilim(float *Idmax_ave, float *DiDt_ave, float *Ton_ave, float *Rdson_peak_ave, float *Rdson_spec_ave)
{
	*Idmax_ave =0.0;
	*DiDt_ave  =0.0;
	*Ton_ave   =0.0;
	*Rdson_peak_ave =0.0;
	*Rdson_spec_ave =0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Idmax_ave		=999.0;
		*DiDt_ave		=999.0;
		*Ton_ave		=999.0;
		*Rdson_peak_ave =999.0;
		*Rdson_spec_ave =999.0;
		gILIM_pct_1stP	= 0.0;
		gILIM_pct_2ndP	= 0.0;
		gILIM_pct_3rdP	= 0.0;
		return;
	}

	int	PULSE_NUM_NEED  =0;		// Define min pulses numbers need to be caputre. 4*7.5us = 30us. 2K sample allows 40us. 4K -> 80us
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	float Vdson_peak_ave =0.0;
	float Vped_threshold =0.0;
	
	// Variables for ILIM peak tests
	float ACgnd[400]      ={0.0};
	float ACgnd_Ave[400]  ={0.0};
	float Id05us_Ave[400] ={0.0};
	float pulse_width[400]={0.0};
	float Ton[400]		 ={0.0};
	float Toff[400]		 ={0.0};
	float DiDt[400]		 ={0.0};
	int Id05us_Addr[400]  ={0};
	int ACgnd_addr[400]   ={1000};				// GND is taken before device turns on
	int gnd_add_offset	= 0;

	// Variables for Rdson_spec tests at 10% ILIM_NORM level
	float Ilim_spec =0.0;
	float Vdson_spec[400] ={0.0};
	float Idson_spec[400] ={0.0};
	float Rdson_spec[400] ={0.0};
	float Vdson_spec_ave =0.0;
	float Idson_spec_ave =0.0;
	int Id_spec_addr[400] ={0};
	float istep_downdelta = 0.0;

	float Id_temp =0.0;
	float Id_one_data_pts =0.0;
	int	  lcnt =0, i=0;
	int	  ave_start_pulse =0;
	int	  ave_pulses	  =0;
	int	  ave_end_pulse	  =0;

	float Period=0.0;
	int	  Sample_per_cycle=0;
	int   FIND_ILIM_LO_FLAG=0;

	float Off_Time=0.0;
	float RTM_High_Id=0.0,
		  RTM_Low_Id=0.0;

	char wave_name_Id[150] ="/0"; 
	char wave_name_Vd[150] ="/0"; 
	char debug_file_name[150] ="/0"; 



	if(gFind_ILIM_Jitter)		PULSE_NUM_NEED  =100;	//If fosc = 100kHz, every pulse would take 10us.  100 pulses would take 1ms
	else						PULSE_NUM_NEED  =26;	//If fosc = 100kHz, every pulse would take 10us.  27  pulses would take 270us

	//Period = 1/(gFOSC_TARGET_P-10e3);		//Takes care of device with Jitter up to 10kHz
	Period = 1/(100e3-10e3);		//Takes care of device with Jitter up to 10kHz from 100kHz
	SAMPLE_RATE_s = 20e-9;
	Sample_per_cycle = Period/SAMPLE_RATE_s;

	for (icnt=0; icnt<PULSE_NUM_NEED*2; icnt++)
	{
		gIdmax[icnt] = -100;
		gIdmax_addr[icnt]  = 0;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array
	if(FIND_RDSON_Peak_FLAG || FIND_RDSON_Spec_FLAG)
		Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array


	
//	start_addr = 300;					// Skip 6us from negative trigger edge
//	start_addr = 1300;					// Skip the first 3 initial pulses (all 3 of them lower than ILIM)
	start_addr = 0;						// Include the 1st 3 pulses for datalog.

	while (Gage_chan_a_voltage[start_addr]< 0.0 && start_addr < SAMPLE_SIZE)
		start_addr+=1;					// Fast forward by 1 samples at rate of 20ns/sample

	start_addr += 8;	//Fast forward by 8 samples (This also jump over the FET turn-on spike)

	// Error check
	if ((start_addr + Sample_per_cycle + 125) > SAMPLE_SIZE ) 	// Searching window = Period + 2.5us(from next pulse).  
	{
		*Idmax_ave  = 999.0;
		return;
	}

	FIND_ILIM_LO_FLAG = 1;

	//if(DEBUG==1 && gDEBUG)
	//{
	//	printf("\n\n");
	//	printf(WAVE_NAME);
	//	printf(" (Serial Number)%i:\n", SERIAL_NUM);
	//}

	// Search for the peak
	while ((pulse_cnt<= PULSE_NUM_NEED)&& (start_addr < SAMPLE_SIZE))
	{
		// Find Idmax
//		for(icnt = start_addr; icnt< start_addr + Sample_per_cycle + 125 ; icnt++)		
		for(icnt = start_addr; icnt< start_addr + 300 ; icnt++)	// To avoid intermittence failure for RDSON reading. HQL 07/08/14	
		{// Searching window = Period + 2.5us(from next pulse). 
			if((Gage_chan_a_voltage[icnt] > gIdmax[pulse_cnt])&& Gage_chan_a_voltage[icnt]>50e-3)
			{
				gIdmax[pulse_cnt] = Gage_chan_a_voltage[icnt];
				gIdmax_addr[pulse_cnt] = icnt;
			}

			//First pulse breaks out of loop if Gage_chan_a_voltage starts dropping and greater than 50mV
			if(  FIND_ILIM_LO_FLAG == 1												&&
				(Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-1]) < -5e-3	&& 
				 Gage_chan_a_voltage[icnt] > 50e-3										)
			{
				FIND_ILIM_LO_FLAG = 0;
				break;
			}

			//break out of loop if Gage_chan_a_voltage starts dropping by 20mA (and greater than 50mV)
			if( ((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-1]) < -20e-3)	&& 
				 (Gage_chan_a_voltage[icnt] > 50e-3)					)
			{
				break;
			}
		}

		//if(DEBUG==1)
		//	printf("\ngIDmax[%i] = %.1fmA, gIdmax_addr[%i] = %i, ", pulse_cnt, gIdmax[pulse_cnt]*1000, pulse_cnt, gIdmax_addr[pulse_cnt]);

		if(MOSFET_SIZE==2)			Vped_threshold = 0.025;
		else if(MOSFET_SIZE==5)		Vped_threshold = 0.005;	//Hiep 1/25/2017
		else						Vped_threshold = 0.05;

		// Find AC Ground level before turn on, count backward from pulse peak until sample less than threshold
		ACgnd[pulse_cnt] = 1000;
//		for(icnt = start_addr; (icnt> 0) && (Gage_chan_a_voltage[icnt]>=0.0); icnt--)	//Secondary in control
		for(icnt = gIdmax_addr[pulse_cnt]; (icnt> 0) && (Gage_chan_a_voltage[icnt]>=Vped_threshold); icnt--)	//Primary in control
		{
			 ACgnd[pulse_cnt] = Gage_chan_a_voltage[icnt-1];
			 ACgnd_addr[pulse_cnt] = icnt;
		}
		
		//if(DEBUG==1)
		//	printf("ACgnd[%i] = %.1fmA, ACgnd_addr[%i] = %i, ", pulse_cnt, ACgnd[pulse_cnt]*1000, pulse_cnt, ACgnd_addr[pulse_cnt]);

		//First pulse ACgnd take care separately
		//if(pulse_cnt == 0)
		//	ACgnd_Ave[pulse_cnt] = ACgnd[pulse_cnt];
		//else
		if (MOSFET_SIZE==5 || MOSFET_SIZE==4)
			gnd_add_offset = 10;
		else
			gnd_add_offset = 0;

		if(g_TurretCB)
		{
			gnd_add_offset = gnd_add_offset + 2;  //Due to tDelta_RTM_30uS repeatability failure on TurretCB
		}
		ACgnd_Ave[pulse_cnt] = (Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(15+gnd_add_offset)]+	// 15 samples away from First data point
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(16+gnd_add_offset)]+
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(17+gnd_add_offset)]+
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(18+gnd_add_offset)]+
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(19+gnd_add_offset)])/5.0;

		//if(DEBUG==1)
		//	printf("ACgnd_Ave[%i] = %.1fmA\n", pulse_cnt, ACgnd_Ave[pulse_cnt]*1000);

		// Find 0.5us location from Idmax, pulse width is time from peak back to sample threshold
		pulse_width[pulse_cnt] = gIdmax_addr[pulse_cnt] - ACgnd_addr[pulse_cnt];

		if (pulse_width[pulse_cnt]> 25)		// Pulse > 0.5us
			Id05us_Addr[pulse_cnt] = gIdmax_addr[pulse_cnt]- 25;	// 0.5us away from Idmax
		else 
			Id05us_Addr[pulse_cnt] = gIdmax_addr[pulse_cnt] - int(pulse_width[pulse_cnt]/2);

		Id05us_Ave[pulse_cnt] = (Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]+2]+	
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]+1]+
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]  ]+
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]-1]+
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]-2])/5.0;

	
		// Individual Peak result
		Id05us_Ave[pulse_cnt] -= ACgnd_Ave[pulse_cnt];
		Id05us_Ave[pulse_cnt]/= Ilim_gain;

		gIdmax[pulse_cnt] -= ACgnd_Ave[pulse_cnt];
		gIdmax[pulse_cnt] /= Ilim_gain;

		// A/us
		DiDt[pulse_cnt]	= (gIdmax[pulse_cnt] - Id05us_Ave[pulse_cnt])/((gIdmax_addr[pulse_cnt] - Id05us_Addr[pulse_cnt])*SAMPLE_RATE_s*1e6);

		// Ton
			Ton[pulse_cnt]	= pulse_width[pulse_cnt] * SAMPLE_RATE_s;
		// Toff		
//		if(pulse_cnt > 0)	//Secondary in control
		if(pulse_cnt > 3)	//Primary in control (Discount pulses 0,1,2,3)
		{
			Toff[pulse_cnt-1]	= (ACgnd_addr[pulse_cnt] - gIdmax_addr[pulse_cnt-1])* SAMPLE_RATE_s;

			//Store RTM_Slope information
			if(WAVE_NAME == "ILIM_NORM")
			{
//				Off_Time = Ton[pulse_cnt] - Toff[pulse_cnt-1];
				Off_Time = Toff[pulse_cnt-1];
				if( Off_Time > 30e-6 && Off_Time < 50e-6 )	//Expect 40us RTM_Slope drop time or Off_Time
				{
					gRTM_Slope  = 0;	//Should only come into this if condition once
					RTM_High_Id = gIdmax[pulse_cnt-1];
					RTM_Low_Id	= gIdmax[pulse_cnt];
					gRTM_Slope  = (RTM_Low_Id - RTM_High_Id)/RTM_High_Id*100/(Off_Time*1e6);
				}
			}
		}
		//if(DEBUG==1)
		//	printf("Ton[%i] = %.1fus, Toff[%i] = %.1fus, ", pulse_cnt, Ton[pulse_cnt]*1e6, pulse_cnt, Toff[pulse_cnt-1]*1e6);

		// Locate Id_spec, Vd_spec location and calculate Rdson_spec
		if(FIND_RDSON_Spec_FLAG && DiDt[pulse_cnt] !=0.0 && pulse_cnt > 3)
		{
			if(MOSFET_SIZE==2)	Ilim_spec = 0.32 * gILIM_TARGET_S;	// Inno2's 550mA IM gives ~100mA pedestal.  30% -> Need more room away from noise
			else				Ilim_spec = 0.25 * gILIM_TARGET_S;	// !!! Use 25-30% Per Alex

			Id_spec_addr[pulse_cnt] = int(gIdmax_addr[pulse_cnt] - (gIdmax[pulse_cnt]- Ilim_spec)/(DiDt[pulse_cnt] *SAMPLE_RATE_s *1e6));
			Id_temp = Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]]/Ilim_gain;	//Id_temp must be > 0 since it's 25-30% of ILIM_target
			Id_one_data_pts = DiDt[pulse_cnt] * SAMPLE_RATE_s *1e6; // Amps
			while ((Ilim_spec - Id_temp)> Id_one_data_pts && lcnt < 100)
			{
				Id_spec_addr[pulse_cnt]++;
				Id_temp= Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]]/Ilim_gain;
			}
				Id_spec_addr[pulse_cnt]+=2;	// Move away from ringing

			if ((gIdmax_addr[pulse_cnt]-Id_spec_addr[pulse_cnt])< pulse_width[pulse_cnt])
			{
				Vdson_spec[pulse_cnt] = Gage_chan_b_voltage[Id_spec_addr[pulse_cnt]]*BUFgain;
				Idson_spec[pulse_cnt] = Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]]/Ilim_gain;
				if (Idson_spec[pulse_cnt] !=0.0)
					Rdson_spec[pulse_cnt]=Vdson_spec[pulse_cnt]/(Idson_spec[pulse_cnt]);
				else
					Rdson_spec[pulse_cnt] = 0.0;
			}
			else 
				Rdson_spec[pulse_cnt] = 0.0;
		}

		//Reset gIdmax
		if(gIdmax[pulse_cnt] < -100)
			gIdmax[pulse_cnt] = -100;

		// Reset start address after find a peak.
		if(gIdmax[pulse_cnt] > 0)	//only do additional count if it's a true Idmax
		{
			start_addr = gIdmax_addr[pulse_cnt] + 100;	//Fast forward 100 samples (2us) for the next loop to start 
			PULSE_NUM_PROCESSED ++;
			pulse_cnt ++;
		}


		////start_addr = gIdmax_addr[pulse_cnt-1]+100;	// Move forward 2us

		//////Move forward 200us for ILIM_LO
		////if( (gIdmax[pulse_cnt-1] - gIdmax[pulse_cnt-2]) < -50e-3 && 
		////	 Toff[pulse_cnt-2]>25e-6						 && 
		////	 Toff[pulse_cnt-2]<41e-6						  )
		////{
		////	//FIND_ILIM_LO_FLAG = 1;
		////	start_addr = gIdmax_addr[pulse_cnt-1]+1750;	// Move forward 35us (35us / 20ns = 1750 samples)
		////}



		while (Gage_chan_a_voltage[start_addr]< 35e-3 && start_addr < SAMPLE_SIZE)	
			start_addr+=1;					// Fast forward by 200ns/step
//			start_addr+=25;					// Fast forward by 0.5us/step
		start_addr+=9;	// Fast forward 9 samples of 20ns

		if ((icnt< start_addr + Sample_per_cycle + 125) > SAMPLE_SIZE ) 	// Searching window = Period + 2.5us(from next pulse). 
			break;
	}

	// Find Idmax_Jitter and Idmin_Jitter from Idmax[] array
	//if(gFind_ILIM_Jitter)
	//{
	//	for(pulse_cnt=4; pulse_cnt<PULSE_NUM_PROCESSED; pulse_cnt++)
	//	{
	//		if(gIdmax[pulse_cnt] > gIdmax_Jitter_132kHz)	gIdmax_Jitter_132kHz = gIdmax[pulse_cnt];
	//		if(pulse_cnt==4)						gIdmin_Jitter_132kHz = gIdmax_Jitter_132kHz;
	//		if(gIdmax[pulse_cnt] < gIdmin_Jitter_132kHz)	gIdmin_Jitter_132kHz = gIdmax[pulse_cnt];
	//	}
	//}

	// Average Peak results
	if(( PULSE_NUM_PROCESSED>= 16)) //Sometimes the first pulse miss-trigger.  Expect 22 if no missing trigger
	{
		// Number of pulses used for ILIM_ave, Ton_ave, Didt_ave, Vdson_peak_ave, Rdson_spec_ave
		//ave_start_pulse	= 4;	//good for size x8 but not size x5
		ave_start_pulse	= 6;	//good for both size x8 and x5
		ave_pulses		= 10;
		ave_end_pulse	= ave_start_pulse + ave_pulses;
		// Taking average Needed pulses peak values (Must skip the first 3 pulses since they are not at ILIM)
		for (pulse_cnt =ave_start_pulse; pulse_cnt< ave_end_pulse; pulse_cnt++)
		{
			*Idmax_ave+=gIdmax[pulse_cnt];
			*Ton_ave  +=Ton[pulse_cnt];
			*DiDt_ave +=DiDt[pulse_cnt];
			if(FIND_RDSON_Peak_FLAG)
				Vdson_peak_ave+=Gage_chan_b_voltage[gIdmax_addr[pulse_cnt]]*BUFgain;
			if(FIND_RDSON_Spec_FLAG)
				*Rdson_spec_ave+=Rdson_spec[pulse_cnt];
		}

		if(FIND_RDSON_Peak_FLAG && *Idmax_ave !=0.0)
		{
			*Rdson_peak_ave =Vdson_peak_ave/(*Idmax_ave);
		}
		else
			*Rdson_peak_ave =999.0;


		if(FIND_RDSON_Spec_FLAG)
			*Rdson_spec_ave /=(ave_pulses+1e-23);
		else
			*Rdson_spec_ave =999.0;

		*Idmax_ave /=ave_pulses;
		*Ton_ave   /=ave_pulses;
		*DiDt_ave  /=ave_pulses;

		//ILIM_NORM: set global variables 
		if(WAVE_NAME == "ILIM_NORM")
		{
			//Reset 1st, 2nd, 3rd ILIM_Ramp variables
			gTon_1stP		=0.0;
			gTon_2ndP		=0.0;
			gTon_3rdP		=0.0;
			gToff_1stP		=0.0;
			gToff_2ndP		=0.0;
			gToff_3rdP		=0.0;
			gILIM_pct_1stP	=0.0;
			gILIM_pct_2ndP	=0.0;
			gILIM_pct_3rdP	=0.0;
			gRTM_Slope		=0.0;
			
			gILIM_pct_1stP	= gIdmax[PULSE_NUM_PROCESSED-3] / *Idmax_ave * 100.0;
			gILIM_pct_2ndP	= gIdmax[PULSE_NUM_PROCESSED-2] / *Idmax_ave * 100.0;
			gILIM_pct_3rdP	= gIdmax[PULSE_NUM_PROCESSED-1] / *Idmax_ave * 100.0;

//if (gILIM_pct_3rdP < 50) // Debug only //
//delay(1); // Debug only //

			gTon_1stP		= Ton[PULSE_NUM_PROCESSED-3];
			gTon_2ndP		= Ton[PULSE_NUM_PROCESSED-2];
			gTon_3rdP		= Ton[PULSE_NUM_PROCESSED-1];
			gToff_1stP		= Toff[PULSE_NUM_PROCESSED-3]; //(ACgnd_addr[1] - gIdmax_addr[0])* SAMPLE_RATE_s;
			gToff_2ndP		= Toff[PULSE_NUM_PROCESSED-2]; //(ACgnd_addr[2] - gIdmax_addr[1])* SAMPLE_RATE_s;
			gToff_3rdP		= Toff[PULSE_NUM_PROCESSED-1]; //(ACgnd_addr[3] - gIdmax_addr[2])* SAMPLE_RATE_s;

			// RTM (Ramp Time Modulation) Slope
			// Expect the final ILIM_peak to be the first pulse of ILIM ramp.  It should be in the range of 200mA to 300mA
//			if(gIdmax[PULSE_NUM_PROCESSED-1] > 200e-3 && gIdmax[PULSE_NUM_PROCESSED-1] < 300e-3)
			
			/*
			if(gIdmax[PULSE_NUM_PROCESSED-3] > 50e-3)
			{
				//gRTM_Slope = ( gIdmax[PULSE_NUM_PROCESSED-2] - gIdmax[PULSE_NUM_PROCESSED-3] ) / Toff[PULSE_NUM_PROCESSED-3]*1e-6;
				gtDelta_RTM_Slope	= Ton[PULSE_NUM_PROCESSED-4] + Toff[PULSE_NUM_PROCESSED-5];
				gi_pct_drop_RTM		= ((gIdmax[PULSE_NUM_PROCESSED-4] / gIdmax[PULSE_NUM_PROCESSED-5]) - 1.0) * 100.0;
				gRTM_Slope = gi_pct_drop_RTM / gtDelta_RTM_Slope * 1e-6;
				gRTM_Slope = ( (gIdmax[PULSE_NUM_PROCESSED-4] - gIdmax[PULSE_NUM_PROCESSED-5]) / gIdmax[PULSE_NUM_PROCESSED-5] * 100) / 
							 ( gtDelta_RTM_Slope - 10e-6 ) * 1e-6;
				if(DEBUG==1)
					printf("\nIdmax = %.2f, Id_drop to = %.2f, time_drop = %.2f us, pct_drop = %.2f", gIdmax[PULSE_NUM_PROCESSED-5], gIdmax[PULSE_NUM_PROCESSED-4], Ton[PULSE_NUM_PROCESSED-4] + Toff[PULSE_NUM_PROCESSED-5]*1e6, gRTM_Slope);
			}
			*/
			if(gIdmax[PULSE_NUM_PROCESSED-3] > 50e-3)
			{
				//gRTM_Slope = ( gIdmax[PULSE_NUM_PROCESSED-2] - gIdmax[PULSE_NUM_PROCESSED-3] ) / Toff[PULSE_NUM_PROCESSED-3]*1e-6;
				gtDelta_RTM_Slope	= Ton[PULSE_NUM_PROCESSED-8] + Toff[PULSE_NUM_PROCESSED-9];
				gi_pct_drop_RTM		= ((gIdmax[PULSE_NUM_PROCESSED-8] / gIdmax[PULSE_NUM_PROCESSED-9]) - 1.0) * 100.0;
				gRTM_Slope = gi_pct_drop_RTM / gtDelta_RTM_Slope * 1e-6;
				gRTM_Slope = ( (gIdmax[PULSE_NUM_PROCESSED-8] - gIdmax[PULSE_NUM_PROCESSED-9]) / gIdmax[PULSE_NUM_PROCESSED-9] * 100) / 
							 ( gtDelta_RTM_Slope - 10e-6 ) * 1e-6;
				if(DEBUG==1 && gDEBUG)
					printf("\nIdmax = %.2f, Id_drop to = %.2f, time_drop = %.2f us, pct_drop = %.2f\n", gIdmax[PULSE_NUM_PROCESSED-9], gIdmax[PULSE_NUM_PROCESSED-8], Ton[PULSE_NUM_PROCESSED-8] + Toff[PULSE_NUM_PROCESSED-9]*1e6, gRTM_Slope);

				gtDelta_RTM_Slope_200us = Ton[PULSE_NUM_PROCESSED-3] + Toff[PULSE_NUM_PROCESSED-4];
				gILIM_200us_S = gIdmax[PULSE_NUM_PROCESSED-3];
				gILIM_200us_pct_S = ((gIdmax[PULSE_NUM_PROCESSED-3] / gIdmax[PULSE_NUM_PROCESSED-4]) - 1.0) * 100.0;
			}

		}
	}
	else 
	{
			*Idmax_ave =999.0;
			*Ton_ave   =999.0;
			*DiDt_ave  =999.0;
			if(DEBUG==1 && gDEBUG)
				MessageBox(NULL, "Error: PULSE_NUM_PROCESSED is less than PULSE_NUM_NEED",Func_name, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);

	}

	//DEBUG text File
	if(DEBUG==1 && gDEBUG)
	{
		int i=0;
		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, DevName); 
		strcat (debug_file_name, "_");
		strcat (debug_file_name, WAVE_NAME);
		strcat (debug_file_name, "_debug.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print to file
		fprintf(fpr,"WAVE_NAME= %s \n\n",WAVE_NAME);

		//measured values
		fprintf(fpr,"ILIM(Idmax_ave) = %.3f A,  *DiDt_ave = %.2f A/us,  *Ton_ave= %.2f us\n",*Idmax_ave,  *DiDt_ave,  *Ton_ave*1e6);

		//RDSon
		if(FIND_RDSON_Peak_FLAG)
			fprintf(fpr,"Rdson_peak_ave = %.3f ohms (Vdson_peak_ave=%.3f V , Idmax_ave=%.3f A)\n",
				*Rdson_peak_ave,Vdson_peak_ave/ave_pulses,	*Idmax_ave);

		//pulses
		fprintf(fpr,"\n  PULSE_NUM_PROCESSED=%i\n",PULSE_NUM_PROCESSED);
		if(WAVE_NAME == "ILIM_NORM")
		{
			fprintf(fpr,"  ILIM, Ton, didt averaged from pulse %i to pulse %i\n\n", ave_start_pulse,ave_end_pulse);
			fprintf(fpr,"  ILIM_Lo taken from pulse %i\n", PULSE_NUM_PROCESSED-3);
			fprintf(fpr,"  ILIM_Med taken from pulse %i\n", PULSE_NUM_PROCESSED-2);
			fprintf(fpr,"  ILIM_Hi taken from pulse %i\n", PULSE_NUM_PROCESSED-1);
		}

		fprintf(fpr,"\nPeak Data: \n",WAVE_NAME);
		//Peak data
		for(i=0; i<PULSE_NUM_PROCESSED; i++)
		{
			if(gIdmax[i] > 0)
			fprintf(fpr,"ILIM_Pulse %i = %.1fmA, Ton_Pulse = %.1fus, Toff_Pulse = %.1fus, Freq = %.1fkHz, Ton_addr=%i, pk_addr=%i\n", 
				i, gIdmax[i]*1000, Ton[i]*1e6, Toff[i]*1e6, 1/(Ton[i]+Toff[i])/1000,ACgnd_addr[i],gIdmax_addr[i]);

			if(FIND_RDSON_Peak_FLAG)
			{
				fprintf(fpr,"  Vdson_peak %i = %.3f V \n",i,Gage_chan_b_voltage[gIdmax_addr[i]]*BUFgain);
				fprintf(fpr,"  Rdson_peak %i = %.3f ohm \n",i,(Gage_chan_b_voltage[gIdmax_addr[i]]*BUFgain)/gIdmax[i]);
			}

		}
		fprintf (fpr, "End of Peaks\n");
		fclose(fpr);

	}

	//DEBUG AWAV Files
	if(DEBUG==1 && gDEBUG)
	//if(DEBUG==1)
	{
		strcpy (wave_name_Id, WAVE_NAME);
		strcat (wave_name_Id, "_Id"); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		if(FIND_RDSON_Peak_FLAG || FIND_RDSON_Spec_FLAG)
		{
			strcpy (wave_name_Vd, WAVE_NAME);
			strcat (wave_name_Vd, "_Vd"); 
			Create_Awav_xp(wave_name_Vd, Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);
		}
		WAVE_NAME = "NoWaveName";
	}

	// Reset Flags
	FIND_RDSON_Peak_FLAG	=0;
	FIND_RDSON_Spec_FLAG	=0;
	gFind_ILIM_Jitter		=0;
}

void Gage_Find_Ilim_Turret(float *Idmax_ave, float *DiDt_ave, float *Ton_ave, float *Rdson_peak_ave, float *Rdson_spec_ave)
{
	*Idmax_ave =0.0;
	*DiDt_ave  =0.0;
	*Ton_ave   =0.0;
	*Rdson_peak_ave =0.0;
	*Rdson_spec_ave =0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Idmax_ave		=999.0;
		*DiDt_ave		=999.0;
		*Ton_ave		=999.0;
		*Rdson_peak_ave =999.0;
		*Rdson_spec_ave =999.0;
		return;
	}

	int	PULSE_NUM_NEED  =0;		// Define min pulses numbers need to be caputre. 4*7.5us = 30us. 2K sample allows 40us. 4K -> 80us
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	float Vdson_peak_ave =0.0;
	float Vped_threshold =0.0;
	
	// Variables for ILIM peak tests
	float ACgnd[400]      ={0.0};
	float ACgnd_Ave[400]  ={0.0};
	float Id05us_Ave[400] ={0.0};
	float pulse_width[400]={0.0};
	float Ton[400]		 ={0.0};
	float Toff[400]		 ={0.0};
	float DiDt[400]		 ={0.0};
	int Id05us_Addr[400]  ={0};
	int ACgnd_addr[400]   ={1000};				// GND is taken before device turns on
	int gnd_add_offset	= 0;

	// Variables for Rdson_spec tests at 10% ILIM_NORM level
	float Ilim_spec =0.0;
	float Vdson_spec[400] ={0.0};
	float Idson_spec[400] ={0.0};
	float Rdson_spec[400] ={0.0};
	float Vdson_spec_ave =0.0;
	float Idson_spec_ave =0.0;
	int Id_spec_addr[400] ={0};

	float Id_temp =0.0;
	float Id_one_data_pts =0.0;
	int	  lcnt =0, i=0;
	int	  ave_start_pulse =0;
	int	  ave_pulses	  =0;
	int	  ave_end_pulse	  =0;

	float Period=0.0;
	int	  Sample_per_cycle=0;
	int   FIND_ILIM_LO_FLAG=0;

	float Off_Time=0.0;
	float RTM_High_Id=0.0,
		  RTM_Low_Id=0.0;

	char wave_name_Id[150] ="/0"; 
	char wave_name_Vd[150] ="/0"; 
	char debug_file_name[150] ="/0"; 



	if(gFind_ILIM_Jitter)		PULSE_NUM_NEED  =100;	//If fosc = 100kHz, every pulse would take 10us.  100 pulses would take 1ms
	else						PULSE_NUM_NEED  =26;	//If fosc = 100kHz, every pulse would take 10us.  27  pulses would take 270us

	//Period = 1/(gFOSC_TARGET_P-10e3);		//Takes care of device with Jitter up to 10kHz
	Period = 1/(100e3-10e3);		//Takes care of device with Jitter up to 10kHz from 100kHz
	SAMPLE_RATE_s = 20e-9;
	Sample_per_cycle = Period/SAMPLE_RATE_s;

	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	{
		gIdmax[icnt] = -100;
		gIdmax_addr[icnt]  = 0;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array
	if(FIND_RDSON_Peak_FLAG || FIND_RDSON_Spec_FLAG)
		Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array


	
//	start_addr = 300;					// Skip 6us from negative trigger edge
//	start_addr = 1300;					// Skip the first 3 initial pulses (all 3 of them lower than ILIM)
	start_addr = 0;						// Include the 1st 3 pulses for datalog.

	while (Gage_chan_a_voltage[start_addr]< 0.0 && start_addr < SAMPLE_SIZE)
		start_addr+=1;					// Fast forward by 1 samples at rate of 20ns/sample

	start_addr += 8;	//Fast forward by 8 samples (This also jump over the FET turn-on spike)

	// Error check
	if ((start_addr + Sample_per_cycle + 125) > SAMPLE_SIZE ) 	// Searching window = Period + 2.5us(from next pulse).  
	{
		*Idmax_ave  = 999.0;
		return;
	}

	FIND_ILIM_LO_FLAG = 1;

	//if(DEBUG==1 && gDEBUG)
	//{
	//	printf("\n\n");
	//	printf(WAVE_NAME);
	//	printf(" (Serial Number)%i:\n", SERIAL_NUM);
	//}

	// Search for the peak
	while ((pulse_cnt<= PULSE_NUM_NEED)&& (start_addr < SAMPLE_SIZE))
	{
		// Find Idmax
//		for(icnt = start_addr; icnt< start_addr + Sample_per_cycle + 125 ; icnt++)		
		for(icnt = start_addr; icnt< start_addr + 300 ; icnt++)	// To avoid intermittence failure for RDSON reading. HQL 07/08/14	
		{// Searching window = Period + 2.5us(from next pulse). 
			
			//Excluding spike on the pedestal.
			if ((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt - 10]) < 0.2)
			{
				//Excluding spike next to ILim peak.
				if((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt - 1])<0.015)
				
				{
					if((Gage_chan_a_voltage[icnt] > gIdmax[pulse_cnt])&& Gage_chan_a_voltage[icnt]>50e-3)
					{
						gIdmax[pulse_cnt] = Gage_chan_a_voltage[icnt];
						gIdmax_addr[pulse_cnt] = icnt;
					}
				}
			}

			//First pulse breaks out of loop if Gage_chan_a_voltage starts dropping and greater than 50mV
			if(  FIND_ILIM_LO_FLAG == 1												&&
				(Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-1]) < -5e-3	&& 
				 Gage_chan_a_voltage[icnt] > 50e-3										)
			{
				FIND_ILIM_LO_FLAG = 0;
				break;
			}

			//Due to large pedestal spike on the Turret handler, incorrect ilim peak is calculated, causing repeatability issue.
		
			if ((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt - 10]) > 0.19)
			{
							
				//break out of loop if Gage_chan_a_voltage starts dropping by 20mA (and greater than 50mV)
				if( ((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-1]) < -20e-3)	&& 
						(Gage_chan_a_voltage[icnt] > 50e-3)					)
				{
					break;
				}
			}
			
	
		}

		//if(DEBUG==1)
		//	printf("\ngIDmax[%i] = %.1fmA, gIdmax_addr[%i] = %i, ", pulse_cnt, gIdmax[pulse_cnt]*1000, pulse_cnt, gIdmax_addr[pulse_cnt]);

		if(MOSFET_SIZE==2)			Vped_threshold = 0.025;
		else if(MOSFET_SIZE==5)		Vped_threshold = 0.05;	
		else						Vped_threshold = 0.05;


		// Find AC Ground level before turn on
		ACgnd[pulse_cnt] = 1000;
//		for(icnt = start_addr; (icnt> 0) && (Gage_chan_a_voltage[icnt]>=0.0); icnt--)	//Secondary in control
		for(icnt = gIdmax_addr[pulse_cnt]; (icnt> 0) && (Gage_chan_a_voltage[icnt]>=Vped_threshold); icnt--)	//Primary in control
		{
			 ACgnd[pulse_cnt] = Gage_chan_a_voltage[icnt-1];
			 ACgnd_addr[pulse_cnt] = icnt;
		}
		
		//if(DEBUG==1)
		//	printf("ACgnd[%i] = %.1fmA, ACgnd_addr[%i] = %i, ", pulse_cnt, ACgnd[pulse_cnt]*1000, pulse_cnt, ACgnd_addr[pulse_cnt]);

		//First pulse ACgnd take care separately
		//if(pulse_cnt == 0)
		//	ACgnd_Ave[pulse_cnt] = ACgnd[pulse_cnt];
		//else
		if (MOSFET_SIZE==5)
			gnd_add_offset = 10;
		else
			gnd_add_offset = 0;

		if(g_TurretCB)
		{
			gnd_add_offset = gnd_add_offset + 2;  //Due to tDelta_RTM_30uS repeatability failure on TurretCB
		}
		ACgnd_Ave[pulse_cnt] = (Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(15+gnd_add_offset)]+	// 15 samples away from First data point
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(16+gnd_add_offset)]+
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(17+gnd_add_offset)]+
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(18+gnd_add_offset)]+
								Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-(19+gnd_add_offset)])/5.0;

		//if(DEBUG==1)
		//	printf("ACgnd_Ave[%i] = %.1fmA\n", pulse_cnt, ACgnd_Ave[pulse_cnt]*1000);

		// Find 0.5us location from Idmax
		pulse_width[pulse_cnt] = gIdmax_addr[pulse_cnt] - ACgnd_addr[pulse_cnt];

		if (pulse_width[pulse_cnt]> 25)		// Pulse > 0.5us
			Id05us_Addr[pulse_cnt] = gIdmax_addr[pulse_cnt]- 25;	// 0.5us away from Idmax
		else 
			Id05us_Addr[pulse_cnt] = gIdmax_addr[pulse_cnt] - int(pulse_width[pulse_cnt]/2);

		Id05us_Ave[pulse_cnt] = (Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]+2]+	
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]+1]+
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]  ]+
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]-1]+
								 Gage_chan_a_voltage[Id05us_Addr[pulse_cnt]-2])/5.0;

	
		// Individual Peak result
		Id05us_Ave[pulse_cnt] -= ACgnd_Ave[pulse_cnt];
		Id05us_Ave[pulse_cnt]/= Ilim_gain;

		gIdmax[pulse_cnt] -= ACgnd_Ave[pulse_cnt];
		gIdmax[pulse_cnt] /= Ilim_gain;

		// A/us
		DiDt[pulse_cnt]	= (gIdmax[pulse_cnt] - Id05us_Ave[pulse_cnt])/((gIdmax_addr[pulse_cnt] - Id05us_Addr[pulse_cnt])*SAMPLE_RATE_s*1e6);

		// Ton
			Ton[pulse_cnt]	= pulse_width[pulse_cnt] * SAMPLE_RATE_s;
		// Toff		
//		if(pulse_cnt > 0)	//Secondary in control
		if(pulse_cnt > 3)	//Primary in control (Discount pulses 0,1,2,3)
		{
			Toff[pulse_cnt-1]	= (ACgnd_addr[pulse_cnt] - gIdmax_addr[pulse_cnt-1])* SAMPLE_RATE_s;

			//Store RTM_Slope information
			if(WAVE_NAME == "ILIM_NORM")
			{
//				Off_Time = Ton[pulse_cnt] - Toff[pulse_cnt-1];
				Off_Time = Toff[pulse_cnt-1];
				if( Off_Time > 30e-6 && Off_Time < 50e-6 )	//Expect 40us RTM_Slope drop time or Off_Time
				{
					gRTM_Slope  = 0;	//Should only come into this if condition once
					RTM_High_Id = gIdmax[pulse_cnt-1];
					RTM_Low_Id	= gIdmax[pulse_cnt];
					gRTM_Slope  = (RTM_Low_Id - RTM_High_Id)/RTM_High_Id*100/(Off_Time*1e6);
				}
			}
		}
		//if(DEBUG==1)
		//	printf("Ton[%i] = %.1fus, Toff[%i] = %.1fus, ", pulse_cnt, Ton[pulse_cnt]*1e6, pulse_cnt, Toff[pulse_cnt-1]*1e6);

		// Locate Id_spec, Vd_spec location and calculate Rdson_spec
		if(FIND_RDSON_Spec_FLAG && DiDt[pulse_cnt] !=0.0 && pulse_cnt > 3)
		{
			if(MOSFET_SIZE==2)	Ilim_spec = 0.32 * gILIM_TARGET_S;	// Inno2's 550mA IM gives ~100mA pedestal.  30% -> Need more room away from noise
			else				Ilim_spec = 0.25 * gILIM_TARGET_S;	// !!! Use 25-30% Per Alex

			Id_spec_addr[pulse_cnt] = int(gIdmax_addr[pulse_cnt] - (gIdmax[pulse_cnt]- Ilim_spec)/(DiDt[pulse_cnt] *SAMPLE_RATE_s *1e6));
			Id_temp = Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]]/Ilim_gain;	//Id_temp must be > 0 since it's 25-30% of ILIM_target
			Id_one_data_pts = DiDt[pulse_cnt] * SAMPLE_RATE_s *1e6; // Amps
			while ((Ilim_spec - Id_temp)> Id_one_data_pts && lcnt < 100)
			{
				Id_spec_addr[pulse_cnt]++;
				Id_temp= Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]]/Ilim_gain;
			}
				Id_spec_addr[pulse_cnt]+=2;	// Move away from ringing

			if ((gIdmax_addr[pulse_cnt]-Id_spec_addr[pulse_cnt])< pulse_width[pulse_cnt])
			{
				Vdson_spec[pulse_cnt] = Gage_chan_b_voltage[Id_spec_addr[pulse_cnt]]*BUFgain;
				Idson_spec[pulse_cnt] = Gage_chan_a_voltage[Id_spec_addr[pulse_cnt]]/Ilim_gain;
				if (Idson_spec[pulse_cnt] !=0.0)
					Rdson_spec[pulse_cnt]=Vdson_spec[pulse_cnt]/(Idson_spec[pulse_cnt]);
				else
					Rdson_spec[pulse_cnt] = 0.0;
			}
			else 
				Rdson_spec[pulse_cnt] = 0.0;
		}

		//Reset gIdmax
		if(gIdmax[pulse_cnt] < -100)
			gIdmax[pulse_cnt] = -100;

		// Reset start address after find a peak.
		if(gIdmax[pulse_cnt] > 0)	//only do additional count if it's a true Idmax
		{
			start_addr = gIdmax_addr[pulse_cnt] + 100;	//Fast forward 100 samples (2us) for the next loop to start 
			PULSE_NUM_PROCESSED ++;
			pulse_cnt ++;
		}


		////start_addr = gIdmax_addr[pulse_cnt-1]+100;	// Move forward 2us

		//////Move forward 200us for ILIM_LO
		////if( (gIdmax[pulse_cnt-1] - gIdmax[pulse_cnt-2]) < -50e-3 && 
		////	 Toff[pulse_cnt-2]>25e-6						 && 
		////	 Toff[pulse_cnt-2]<41e-6						  )
		////{
		////	//FIND_ILIM_LO_FLAG = 1;
		////	start_addr = gIdmax_addr[pulse_cnt-1]+1750;	// Move forward 35us (35us / 20ns = 1750 samples)
		////}



		while (Gage_chan_a_voltage[start_addr]< 35e-3 && start_addr < SAMPLE_SIZE)	
			start_addr+=1;					// Fast forward by 200ns/step
//			start_addr+=25;					// Fast forward by 0.5us/step
		start_addr+=9;	// Fast forward 9 samples of 20ns

		if ((icnt< start_addr + Sample_per_cycle + 125) > SAMPLE_SIZE ) 	// Searching window = Period + 2.5us(from next pulse). 
			break;
	}

	// Find Idmax_Jitter and Idmin_Jitter from Idmax[] array
	//if(gFind_ILIM_Jitter)
	//{
	//	for(pulse_cnt=4; pulse_cnt<PULSE_NUM_PROCESSED; pulse_cnt++)
	//	{
	//		if(gIdmax[pulse_cnt] > gIdmax_Jitter_132kHz)	gIdmax_Jitter_132kHz = gIdmax[pulse_cnt];
	//		if(pulse_cnt==4)						gIdmin_Jitter_132kHz = gIdmax_Jitter_132kHz;
	//		if(gIdmax[pulse_cnt] < gIdmin_Jitter_132kHz)	gIdmin_Jitter_132kHz = gIdmax[pulse_cnt];
	//	}
	//}

	// Average Peak result
	if(( PULSE_NUM_PROCESSED>= 16)) //Sometimes the first pulse miss-trigger.  Expect 22 if no missing trigger
	{
		// Number of pulses used for ILIM_ave, Ton_ave, Didt_ave, Vdson_peak_ave, Rdson_spec_ave
		//ave_start_pulse	= 4;	//good for size x8 but not size x5
		ave_start_pulse	= 6;	//good for both size x8 and x5
		ave_pulses		= 10;
		ave_end_pulse	= ave_start_pulse + ave_pulses;
		// Taking average Needed pulses peak values (Must skip the first 3 pulses since they are not at ILIM)
		for (pulse_cnt =ave_start_pulse; pulse_cnt< ave_end_pulse; pulse_cnt++)
		{
			*Idmax_ave+=gIdmax[pulse_cnt];
			*Ton_ave  +=Ton[pulse_cnt];
			*DiDt_ave +=DiDt[pulse_cnt];
			if(FIND_RDSON_Peak_FLAG)
				Vdson_peak_ave+=Gage_chan_b_voltage[gIdmax_addr[pulse_cnt]]*BUFgain;
			if(FIND_RDSON_Spec_FLAG)
				*Rdson_spec_ave+=Rdson_spec[pulse_cnt];
		}

		if(FIND_RDSON_Peak_FLAG && *Idmax_ave !=0.0)
		{
			*Rdson_peak_ave =Vdson_peak_ave/(*Idmax_ave);
		}
		else
			*Rdson_peak_ave =999.0;


		if(FIND_RDSON_Spec_FLAG)
			*Rdson_spec_ave /=(ave_pulses+1e-23);
		else
			*Rdson_spec_ave =999.0;

		*Idmax_ave /=ave_pulses;
		*Ton_ave   /=ave_pulses;
		*DiDt_ave  /=ave_pulses;

		//ILIM_NORM: set global variables 
		if(WAVE_NAME == "ILIM_NORM")
		{
			//Reset 1st, 2nd, 3rd ILIM_Ramp variables
			gTon_1stP		=0.0;
			gTon_2ndP		=0.0;
			gTon_3rdP		=0.0;
			gToff_1stP		=0.0;
			gToff_2ndP		=0.0;
			gToff_3rdP		=0.0;
			gILIM_pct_1stP	=0.0;
			gILIM_pct_2ndP	=0.0;
			gILIM_pct_3rdP	=0.0;
			gRTM_Slope		=0.0;
			
			gILIM_pct_1stP	= gIdmax[PULSE_NUM_PROCESSED-3] / *Idmax_ave * 100.0;
			gILIM_pct_2ndP	= gIdmax[PULSE_NUM_PROCESSED-2] / *Idmax_ave * 100.0;
			gILIM_pct_3rdP	= gIdmax[PULSE_NUM_PROCESSED-1] / *Idmax_ave * 100.0;

//if (gILIM_pct_3rdP < 50) // Debug only //
//delay(1); // Debug only //

			gTon_1stP		= Ton[PULSE_NUM_PROCESSED-3];
			gTon_2ndP		= Ton[PULSE_NUM_PROCESSED-2];
			gTon_3rdP		= Ton[PULSE_NUM_PROCESSED-1];
			gToff_1stP		= Toff[PULSE_NUM_PROCESSED-3]; //(ACgnd_addr[1] - gIdmax_addr[0])* SAMPLE_RATE_s;
			gToff_2ndP		= Toff[PULSE_NUM_PROCESSED-2]; //(ACgnd_addr[2] - gIdmax_addr[1])* SAMPLE_RATE_s;
			gToff_3rdP		= Toff[PULSE_NUM_PROCESSED-1]; //(ACgnd_addr[3] - gIdmax_addr[2])* SAMPLE_RATE_s;

			// RTM (Ramp Time Modulation) Slope
			// Expect the final ILIM_peak to be the first pulse of ILIM ramp.  It should be in the range of 200mA to 300mA
//			if(gIdmax[PULSE_NUM_PROCESSED-1] > 200e-3 && gIdmax[PULSE_NUM_PROCESSED-1] < 300e-3)
			
			/*
			if(gIdmax[PULSE_NUM_PROCESSED-3] > 50e-3)
			{
				//gRTM_Slope = ( gIdmax[PULSE_NUM_PROCESSED-2] - gIdmax[PULSE_NUM_PROCESSED-3] ) / Toff[PULSE_NUM_PROCESSED-3]*1e-6;
				gtDelta_RTM_Slope	= Ton[PULSE_NUM_PROCESSED-4] + Toff[PULSE_NUM_PROCESSED-5];
				gi_pct_drop_RTM		= ((gIdmax[PULSE_NUM_PROCESSED-4] / gIdmax[PULSE_NUM_PROCESSED-5]) - 1.0) * 100.0;
				gRTM_Slope = gi_pct_drop_RTM / gtDelta_RTM_Slope * 1e-6;
				gRTM_Slope = ( (gIdmax[PULSE_NUM_PROCESSED-4] - gIdmax[PULSE_NUM_PROCESSED-5]) / gIdmax[PULSE_NUM_PROCESSED-5] * 100) / 
							 ( gtDelta_RTM_Slope - 10e-6 ) * 1e-6;
				if(DEBUG==1)
					printf("\nIdmax = %.2f, Id_drop to = %.2f, time_drop = %.2f us, pct_drop = %.2f", gIdmax[PULSE_NUM_PROCESSED-5], gIdmax[PULSE_NUM_PROCESSED-4], Ton[PULSE_NUM_PROCESSED-4] + Toff[PULSE_NUM_PROCESSED-5]*1e6, gRTM_Slope);
			}
			*/
			if(gIdmax[PULSE_NUM_PROCESSED-3] > 50e-3)
			{
				//gRTM_Slope = ( gIdmax[PULSE_NUM_PROCESSED-2] - gIdmax[PULSE_NUM_PROCESSED-3] ) / Toff[PULSE_NUM_PROCESSED-3]*1e-6;
				gtDelta_RTM_Slope	= Ton[PULSE_NUM_PROCESSED-8] + Toff[PULSE_NUM_PROCESSED-9];
				gi_pct_drop_RTM		= ((gIdmax[PULSE_NUM_PROCESSED-8] / gIdmax[PULSE_NUM_PROCESSED-9]) - 1.0) * 100.0;
				gRTM_Slope = gi_pct_drop_RTM / gtDelta_RTM_Slope * 1e-6;
				gRTM_Slope = ( (gIdmax[PULSE_NUM_PROCESSED-8] - gIdmax[PULSE_NUM_PROCESSED-9]) / gIdmax[PULSE_NUM_PROCESSED-9] * 100) / 
							 ( gtDelta_RTM_Slope - 10e-6 ) * 1e-6;
				if(DEBUG==1 && gDEBUG)
					printf("\nIdmax = %.2f, Id_drop to = %.2f, time_drop = %.2f us, pct_drop = %.2f\n", gIdmax[PULSE_NUM_PROCESSED-9], gIdmax[PULSE_NUM_PROCESSED-8], Ton[PULSE_NUM_PROCESSED-8] + Toff[PULSE_NUM_PROCESSED-9]*1e6, gRTM_Slope);

				gtDelta_RTM_Slope_200us = Ton[PULSE_NUM_PROCESSED-3] + Toff[PULSE_NUM_PROCESSED-4];
				gILIM_200us_S = gIdmax[PULSE_NUM_PROCESSED-3];
				gILIM_200us_pct_S = ((gIdmax[PULSE_NUM_PROCESSED-3] / gIdmax[PULSE_NUM_PROCESSED-4]) - 1.0) * 100.0;
			}

		}
	}
	else 
	{
			*Idmax_ave =999.0;
			*Ton_ave   =999.0;
			*DiDt_ave  =999.0;
			if(DEBUG==1 && gDEBUG)
				MessageBox(NULL, "Error: PULSE_NUM_PROCESSED is less than PULSE_NUM_NEED",Func_name, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);

	}

	//DEBUG text File
	if(DEBUG==1 && gDEBUG)
	{
		int i=0;
		strcpy (debug_file_name, "e:\\DL4\\"); 
		strcat (debug_file_name, DevName); 
		strcat (debug_file_name, "_");
		strcat (debug_file_name, WAVE_NAME);
		strcat (debug_file_name, "_debug.txt");

		//open file
		FILE * fpr = fopen(debug_file_name, "w");
		if (! fpr)
			return;

		//print to file
		fprintf(fpr,"WAVE_NAME= %s \n\n",WAVE_NAME);

		//measured values
		fprintf(fpr,"ILIM(Idmax_ave) = %.3f A,  *DiDt_ave = %.2f A/us,  *Ton_ave= %.2f us\n",*Idmax_ave,  *DiDt_ave,  *Ton_ave*1e6);

		//RDSon
		if(FIND_RDSON_Peak_FLAG)
			fprintf(fpr,"Rdson_peak_ave = %.3f ohms (Vdson_peak_ave=%.3f V , Idmax_ave=%.3f A)\n",
				*Rdson_peak_ave,Vdson_peak_ave/ave_pulses,	*Idmax_ave);

		//pulses
		fprintf(fpr,"\n  PULSE_NUM_PROCESSED=%i\n",PULSE_NUM_PROCESSED);
		if(WAVE_NAME == "ILIM_NORM")
			fprintf(fpr,"  ILIM, Ton, didt averaged from pulse %i to pulse %i\n", ave_start_pulse,ave_end_pulse);

		fprintf(fpr,"\nPeak Data: \n",WAVE_NAME);
		//Peak data
		for(i=0; i<PULSE_NUM_PROCESSED; i++)
		{
			if(gIdmax[i] > 0)
			fprintf(fpr,"ILIM_Pulse %i = %.1fmA, Ton_Pulse = %.1fus, Toff_Pulse = %.1fus, Freq = %.1fkHz, Ton_addr=%i, pk_addr=%i\n", 
				i, gIdmax[i]*1000, Ton[i]*1e6, Toff[i]*1e6, 1/(Ton[i]+Toff[i])/1000,ACgnd_addr[i],gIdmax_addr[i]);

			if(FIND_RDSON_Peak_FLAG)
			{
				fprintf(fpr,"  Vdson_peak %i = %.3f V \n",i,Gage_chan_b_voltage[gIdmax_addr[i]]*BUFgain);
				fprintf(fpr,"  Rdson_peak %i = %.3f ohm \n",i,(Gage_chan_b_voltage[gIdmax_addr[i]]*BUFgain)/gIdmax[i]);
			}

		}
		fprintf (fpr, "End of Peaks\n");
		fclose(fpr);

	}

	//DEBUG AWAV Files
	if(DEBUG==1 && gDEBUG)
	{
		strcpy (wave_name_Id, WAVE_NAME);
		strcat (wave_name_Id, "_Id"); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		if(FIND_RDSON_Peak_FLAG || FIND_RDSON_Spec_FLAG)
		{
			strcpy (wave_name_Vd, WAVE_NAME);
			strcat (wave_name_Vd, "_Vd"); 
			Create_Awav_xp(wave_name_Vd, Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);
		}
		WAVE_NAME = "NoWaveName";
	}

	// Reset Flags
	FIND_RDSON_Peak_FLAG	=0;
	FIND_RDSON_Spec_FLAG	=0;
	gFind_ILIM_Jitter		=0;
}

void Gage_Find_Ilim_SSS(float *Idmax_ave, float *tsoft, float *tHandshake, float *fosc_s_min, float *fosc_s_max, float *ilim_min, float *ilim_max, float *fModulation_P, float *Fosc_Sss_P, float *tRTM)
{
	*Idmax_ave =0.0;
	*tsoft  =0.0;
	*tHandshake   =0.0;
	*fosc_s_min =0.0;
	*fosc_s_max =0.0;
	*ilim_min =0.0;
	*ilim_max =0.0;
	*fModulation_P=0.0;
	*Fosc_Sss_P=0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Idmax_ave		=999.0;
		*tsoft		=999.0;
		*tHandshake		=999.0;
		*fosc_s_min =999.0;
		*fosc_s_max =999.0;
		*ilim_min =999.0;
		*ilim_max =999.0;
		*fModulation_P=999.0;
		*Fosc_Sss_P=999.0;
		*tRTM=999.0;
		return;
	}

	int	PULSE_NUM_NEED  =0;		// Define min pulses numbers need to be caputre. 4*7.5us = 30us. 2K sample allows 40us. 4K -> 80us
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int tsoft_start=0, tsoft_end=0;
	int RTM_end=0;
	int pulse_cnt =0;
	int icnt =0, cnt=0, tcnt=0; 
	float Vdson_peak_ave =0.0;
	float Vped_threshold =0.0;
	
	// Variables for ILIM peak tests
	float ACgnd[4000]      ={0.0};
	float ACgnd_Ave[4000]  ={0.0};
	float Id05us_Ave[4000] ={0.0};
	float pulse_width[4000]={0.0};
	float Ton[4000]		 ={0.0};
	float Toff[4000]		 ={0.0};
	float DiDt[4000]		 ={0.0};
	int Id05us_Addr[4000]  ={0};
	int ACgnd_addr[4000]   ={1000};				// GND is taken before device turns on
	float pulse_period[4000]	={0.0};
	float freq[4000]	={0.0};
	int start_addr_arry[4000] = {0};

	float FirstPeak_ILIM =0.0;
	float FirstPeak_addr =0.0;
	int   FirstPeak_cnt	 =0;
	float SecondPeak_ILIM =0.0;
	float SecondPeak_addr =0.0;
	int   SecondPeak_cnt  =0;
	float min=0, max=0;
	float start=0.0, start2=0.0;
	float dummy_array[200]={0.0};


	// Variables for Rdson_spec tests at 10% ILIM_NORM level
	float Ilim_spec =0.0;
	float Vdson_spec[4000] ={0.0};
	float Idson_spec[4000] ={0.0};
	float Rdson_spec[4000] ={0.0};
	float Vdson_spec_ave =0.0;
	float Idson_spec_ave =0.0;
	int Id_spec_addr[4000] ={0};

	float Id_temp =0.0;
	float Id_one_data_pts =0.0;
	int	  lcnt =0, i=0;
	int   loop_cnt=0;
	int	  ave_start_pulse =0;
	int	  ave_pulses	  =0;
	int	  ave_end_pulse	  =0;
	int	  peak_found=0;

	float Period=0.0;
	int	  Sample_per_cycle=0;
	int   FIND_ILIM_LO_FLAG=0;
	int DEEP_DEBUG=0;

	float Off_Time=0.0;
	float RTM_High_Id=0.0,
		  RTM_Low_Id=0.0,
		  Idmax_delta=0.0;

	char wave_name_Id[150] ="/0"; 
	char wave_name_Vd[150] ="/0"; 
	FILE * fpr4;

	int pk_thrsh;
	float ACGND_Offset_70pct;

	float tSoft_freq_delta =0,
		  freq_A_avg=0,
		  freq_B_avg=0;

	float	avg_6pulse_Idmax_tRTM=0, 
			avg_7pulse_Idmax_tRTM=0,
			avg_8pulse_Idmax_tRTM=0,
			avg_9pulse_Idmax_tRTM=0,
			avg_10pulse_Idmax_tRTM=0,
			avg_11pulse_Idmax_tRTM=0,
			avg_12pulse_Idmax_tRTM=0,
			avg_100ILIM_RTM=0;
	int   cnt_tRTM=0;
	//

	if(MOSFET_SIZE == 2)			ACGND_Offset_70pct = 30e-3;
	if(MOSFET_SIZE == 3)			ACGND_Offset_70pct = 30e-3;//30e-3 to 50e-3 fixed 70pct ILIM??
	if(MOSFET_SIZE == 4)			ACGND_Offset_70pct = 30e-3;
	if(MOSFET_SIZE == 5)			ACGND_Offset_70pct = 30e-3;
	if(MOSFET_SIZE == 6)			ACGND_Offset_70pct = 30e-3;
	if(MOSFET_SIZE == 7)			ACGND_Offset_70pct = 30e-3;
	if(MOSFET_SIZE == 8)			ACGND_Offset_70pct = 30e-3;


	if(MOSFET_SIZE == 2)			pk_thrsh = 0.05;
	else if(MOSFET_SIZE == 3)		pk_thrsh = 0.1;
	else if(MOSFET_SIZE == 4)		pk_thrsh = 0.1;
	else if(MOSFET_SIZE == 5)		pk_thrsh = 0.1;
	else if(MOSFET_SIZE == 6)		pk_thrsh = 0.1;
	else if(MOSFET_SIZE == 7)		pk_thrsh = 0.1;
	else if(MOSFET_SIZE == 8)		pk_thrsh = 0.1;

	if(gSiliconRev_P <=2 && OPCODE==4300)
	{
		tSoft_freq_delta = 0.01;
	}
	else
	{
		tSoft_freq_delta = 0.01;
	}

	Period = 1/(gFOSC_TARGET_P-10e3);		//Takes care of device with Jitter up to 10kHz
	SAMPLE_RATE_s = 20e-9;
	Sample_per_cycle = Period/SAMPLE_RATE_s;

//	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	for (icnt=0; icnt<4000; icnt++)
	{
		gIdmax[icnt] = -100;
		gIdmax_addr[icnt]  = 0;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array
	start_addr = 0;						// Include the 1st 3 pulses for datalog.

	//Awav
	if(DEBUG==1 && gDEBUG)
	//if(DEBUG==1)
	{
		strcpy (wave_name_Id, WAVE_NAME);
		strcat (wave_name_Id, "_Id"); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}

	while (Gage_chan_a_voltage[start_addr]< 0.0 && start_addr < SAMPLE_SIZE)
		start_addr+=1;					// Fast forward by 1 samples at rate of 20ns/sample
	// Error check
	if ((start_addr + Sample_per_cycle + 125) > SAMPLE_SIZE ) 	// Searching window = Period + 2.5us(from next pulse).  
	{
		*Idmax_ave  = 999.0;
		return;
	}
	
	DEEP_DEBUG=0;	//create huge file to debug SostStart
	if(DEEP_DEBUG && gDEBUG)
	{
		fpr4 = fopen("e:\\dl4\\Inn3xxx_ILIM_SSS_addr_loop_datadump.txt", "w");
		if (! fpr4)	return;
	}

	//Fast forward 1st peak by 80us (80us => 20ns per sample would take about 80000ns/20ns => 4000 samples or addresses
	//start_addr += 4000;	//zcx 3/13/2017

	// Search for the peaks
	while (start_addr < SAMPLE_SIZE-10)
	{
		// Find Idmax
//		for(icnt = start_addr; (icnt<(start_addr+SAMPLE_SIZE*0.01)) && ((icnt+5)<SAMPLE_SIZE) ; icnt++)
		peak_found=0;
		//count through each sample, Find next peak
		for(icnt = start_addr; (icnt<(start_addr+4500)) && ((icnt+5)<SAMPLE_SIZE) ; icnt++)
		{
			if(DEEP_DEBUG && gDEBUG)
			{
				//print line for each sample
				fprintf(fpr4,"icnt=%i, peaknum=%i,   Gage_chan_a_voltage[icnt]= %.3f \n",icnt, pulse_cnt,Gage_chan_a_voltage[icnt]);
				//check for catastrophic for loop escape condition--->gIdmax_addr[pulse_cnt] will remain default of 0 while pulse_cnt will be incremented
				if (icnt>(start_addr+4499)) 
					fprintf(fpr4,"(icnt>(start_addr+4500)), icnt=%i, start_addr+5000=%i, difference=%i\n",icnt,start_addr+5000,icnt-start_addr);
				if(Gage_chan_a_voltage[icnt]>0.8*gIdmax[pulse_cnt-1])
					fprintf(fpr4,"Gage_chan_a_voltage[icnt]= %.3f gIdmax[pulse_cnt]=%.3f, 0.8*gIdmax[pulse_cnt-1]=%.3f,addr=%i\n",
						Gage_chan_a_voltage[icnt], gIdmax[pulse_cnt] ,0.8*gIdmax[pulse_cnt-1],icnt);
			}

			//Initial gIdmax
			if(icnt==start_addr)
				gIdmax[pulse_cnt]= Gage_chan_a_voltage[icnt];
			if (pulse_cnt==0)
			{
				//first peak
				if(Gage_chan_a_voltage[icnt] >= gIdmax[pulse_cnt])
				{
					gIdmax[pulse_cnt] = Gage_chan_a_voltage[icnt];
					gIdmax_addr[pulse_cnt] = icnt;
					if ((gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt+5]) > pk_thrsh &&    //pk_thrsh added to adjust for FET size 
						abs(gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt-5]) < 0.10 )   
					{
						peak_found=1;
						break;	//peak found
					}
				}
			}
			else
			{
				//subsequent peaks
				//check if sample is higher than the highest sample we have and also more than 80% of previous peak
				if(Gage_chan_a_voltage[icnt] >= gIdmax[pulse_cnt] && Gage_chan_a_voltage[icnt]>0.8*gIdmax[pulse_cnt-1])
				{
					//save sample as the highest we have
					gIdmax[pulse_cnt] = Gage_chan_a_voltage[icnt];
					gIdmax_addr[pulse_cnt] = icnt;
					//check if sample is significantly higher than sample+5 (peak) and also not so different than sample-5 (not a spike)
					if ((gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt+5]) > pk_thrsh &&    //pk_thrsh added to adjust for FET size 
						abs(gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt-5]) < 0.10 )   
					{
						if (DEEP_DEBUG && gDEBUG)
							fprintf(fpr4,"Peak num %i found, addr=%i\n",pulse_cnt,gIdmax_addr[pulse_cnt] );
						peak_found=1;
						break;	//peak found
					}
					else if(DEEP_DEBUG && gDEBUG)
						fprintf(fpr4,"Peak rejected, addr=%i\n",gIdmax_addr[pulse_cnt] );
				}
				else 
				{	if(Gage_chan_a_voltage[icnt] < gIdmax[pulse_cnt])
					gIdmax[pulse_cnt]=0.0;	//reset after spike
				}
			}
		}	//end of for loop
		
		// Calculate period and freq based on Peak Ilim.
		if(pulse_cnt==0)
			pulse_period[pulse_cnt] = 45e-6;	// Assume 1st period is 45us (22kHz)
		else
			pulse_period[pulse_cnt] = (gIdmax_addr[pulse_cnt] - gIdmax_addr[pulse_cnt-1])*SAMPLE_RATE_s;
		
		freq[pulse_cnt] = 1/pulse_period[pulse_cnt];

		//Reset gIdmax
		if(gIdmax[pulse_cnt] < -100)
			gIdmax[pulse_cnt] = -100;

		//set start address to look for next peak
		if(freq[pulse_cnt]<20e3)
			start_addr = gIdmax_addr[pulse_cnt] + 500; 
		else if(freq[pulse_cnt]<40e3)
		{
			if (MOSFET_SIZE ==2)
				start_addr = gIdmax_addr[pulse_cnt] + 700;  //works for Size x8, and x5		
			else
				start_addr = gIdmax_addr[pulse_cnt] + 500; //works for Size x2 (PM)
		}
		else 
			start_addr = gIdmax_addr[pulse_cnt] + (pulse_period[pulse_cnt]/SAMPLE_RATE_s)*0.35; // - 200;
			//start_addr = gIdmax_addr[pulse_cnt] + (pulse_period[pulse_cnt]/SAMPLE_RATE_s)*0.7; // - 200;

		//debug: save start addresses in array, can later check against awav file
		if (DEBUG && gDEBUG)
		{
			start_addr_arry[pulse_cnt]=start_addr;
			if ( (pulse_cnt>3) && (start_addr_arry[pulse_cnt] < start_addr_arry[pulse_cnt-1]))
				printf("GAGE_fIND_iLIM_sss: pulse_cnt %i,  start_addr decrease: start_addr=%i, start_addr-1= %i\n",pulse_cnt,start_addr_arry[pulse_cnt] , start_addr_arry[pulse_cnt-1]);
		}

		PULSE_NUM_PROCESSED ++;
		pulse_cnt ++;

		if ( (icnt> (SAMPLE_SIZE-400)) || PULSE_NUM_PROCESSED > 3000) 	
			break;
	}//end of while loop

	loop_cnt=0;
	if (DEEP_DEBUG && gDEBUG)
		fclose(fpr4);

	//** Peaks all found, continue on **

	//Average ILIM 70pct from pulse 5-35 (30 pulses)
	for(cnt=5;cnt<35;cnt++)
	{
		ACgnd[cnt] = 1000;
		// Need to find AC_GND for the first portion of capture.

		//*****************************************************************
		//** This logic fail at the end of tSoft awav due to ILIM droop  **
		//*****************************************************************
		//for(i=gIdmax_addr[cnt]; (Gage_chan_a_voltage[i]>=0.0); i--)	
		/*
			When ILIM droop, ILIM drop below zero so searching back from the ILIM peak address to find AGND is wrong

		*/

//		for(i=gIdmax_addr[cnt]; (Gage_chan_a_voltage[i]>=0.0); i--)	
		for(i=gIdmax_addr[cnt]-20; i>gIdmax_addr[cnt-1]; i--)	
		{
			if (abs(Gage_chan_a_voltage[i]-Gage_chan_a_voltage[i-5])>30e-3)
			{
				 ACgnd[cnt] = Gage_chan_a_voltage[i];
				 ACgnd_addr[cnt] = i;
				 break;
			}
		}
		
		ACgnd_Ave[cnt] = (Gage_chan_a_voltage[ACgnd_addr[cnt]-15]+	// 15 samples away from First data point
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-16]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-17]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-18]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-19])/5.0;
		gIdmax[cnt] -= ACgnd_Ave[cnt];
		gIdmax[cnt] /= Ilim_gain;

		*Idmax_ave += gIdmax[cnt];
		*Fosc_Sss_P += freq[cnt];
		loop_cnt++;
	}
	if(loop_cnt != 0)
	{
		*Idmax_ave /= loop_cnt;
		*Fosc_Sss_P /= loop_cnt;
	}

	for(cnt=5;cnt<35;cnt++)
		gIdmax[cnt] *= Ilim_gain;	//restore captured values

	//find handshake based on freq
	for(cnt=0;cnt<PULSE_NUM_PROCESSED;cnt++)
	{
		//if(freq[cnt]<20e3)	//CX 12/26/2016
		//if(freq[cnt]>14e3 && freq[cnt]<17e3 && tsoft_start==0)	//cx 12/26/2016
		if(freq[cnt]>10e3 && freq[cnt]<17e3 && tsoft_start==0)	//cx 3/14/2016 (tHandShake change on the same part from 69us to 95us on B4 silicon)
		{
			*tHandshake = 1/freq[cnt];
			tsoft_start = cnt;
		}
	}

	//save frequency of first soft start cycle
	*fosc_s_min = freq[tsoft_start+1];
//	//find tsoft_end
//	//for(cnt=tsoft_start;(cnt+39)<PULSE_NUM_PROCESSED;cnt++)
//	for(cnt=tsoft_start;(cnt+39)<400;cnt++)
//
//	{
////		if(abs(freq[cnt]-freq[PULSE_NUM_PROCESSED-5])<1e3)
//		if(((freq[cnt+30]+
//			 freq[cnt+31]+
//			 freq[cnt+32]+
//			 freq[cnt+33]+
//			 freq[cnt+34]+
//			 freq[cnt+35]+
//			 freq[cnt+36]+
//			 freq[cnt+37]+
//			 freq[cnt+38]+
//			 freq[cnt+39])/10 - (freq[cnt]+
//								freq[cnt+1]+
//								freq[cnt+2]+
//								freq[cnt+3]+
//								freq[cnt+4]+
//								freq[cnt+5]+
//								freq[cnt+6]+
//								freq[cnt+7]+
//								freq[cnt+8]+
//								freq[cnt+9])/10)<0.2e3)
//		{
//			//printf("Cnt = %.2i, Delta = %.2f \n", cnt, freq[cnt]-freq[PULSE_NUM_PROCESSED-10]);
//			tsoft_end = cnt;
//			break;
//		}
//		tsoft_end = cnt;
//		
//	}
	
	// Looking for t_RTM_Release time, expect around 100us
	for(cnt=tsoft_start;(cnt < tsoft_start+20);cnt++) // 20 pulses should cover much more than 100us of data
	{
		//gIdmax[cnt] /= Ilim_gain;
		if(OPCODE==4300 || OPCODE==4500)
		{
			if		(MOSFET_SIZE == 2)	Idmax_delta = 0.020;
			else if	(MOSFET_SIZE == 3)	Idmax_delta = 0.022;
			else if	(MOSFET_SIZE == 4)	Idmax_delta = 0.030;
			else if	(MOSFET_SIZE == 5)	Idmax_delta = 0.026;
			else if	(MOSFET_SIZE == 6)	Idmax_delta = 0.028;
			else if	(MOSFET_SIZE == 7)	Idmax_delta = 0.030;
			else if	(MOSFET_SIZE == 8)	Idmax_delta = 0.032;
			else						Idmax_delta = 0.040;
		}
		else
		{
			if		(MOSFET_SIZE == 2)	Idmax_delta = 0.020;	
			else if	(MOSFET_SIZE == 3)	Idmax_delta = 0.025;	//0.03 to 0.02 to fix lower tRTM results IM Rev4
			else if	(MOSFET_SIZE == 4)	Idmax_delta = 0.040;	//0.026 to 0.04 to fix lower tRTM results INN3164C-H113  xie 1/25/2018
			else if	(MOSFET_SIZE == 5)	Idmax_delta = 0.028;
			else if	(MOSFET_SIZE == 6)	Idmax_delta = 0.050;	//Fixed tRTM readings of -2200...
			else if	(MOSFET_SIZE == 7)	Idmax_delta = 0.070;
			//else if	(MOSFET_SIZE == 8)	Idmax_delta = 0.050;//INNO3X
			else if	(MOSFET_SIZE == 8)	Idmax_delta = 0.050;//MINNO
			else						Idmax_delta = 0.040;
		}

		////if (fabs(gIdmax[cnt+1] - gIdmax[cnt])>Idmax_delta)	// CX 8/10/2017
		////{
		////	RTM_end = cnt;
		////	break;
		////}


		//Take into account of both conditions where there are parts with 6 pulses and 7 pulses
		//6 pulses stay at 70% while tRTMrelease is ~170us
		//7 pulses stay at 70% while tRTMrelease is ~170us
		avg_6pulse_Idmax_tRTM=0;
		avg_7pulse_Idmax_tRTM=0;
			for(cnt_tRTM=0; cnt_tRTM<=5; cnt_tRTM++)
			{
				avg_6pulse_Idmax_tRTM += gIdmax[cnt+cnt_tRTM];
			}
				avg_7pulse_Idmax_tRTM += avg_6pulse_Idmax_tRTM + gIdmax[cnt+6];
				avg_8pulse_Idmax_tRTM += avg_7pulse_Idmax_tRTM + gIdmax[cnt+7];
				avg_9pulse_Idmax_tRTM += avg_8pulse_Idmax_tRTM + gIdmax[cnt+8];
				avg_10pulse_Idmax_tRTM += avg_9pulse_Idmax_tRTM + gIdmax[cnt+9];
				avg_11pulse_Idmax_tRTM += avg_10pulse_Idmax_tRTM + gIdmax[cnt+10];
				avg_12pulse_Idmax_tRTM += avg_11pulse_Idmax_tRTM + gIdmax[cnt+11];

			avg_6pulse_Idmax_tRTM /= 6;
			avg_7pulse_Idmax_tRTM /= 7;
			avg_8pulse_Idmax_tRTM /= 8;
			avg_9pulse_Idmax_tRTM /= 9;
			avg_10pulse_Idmax_tRTM /= 10;
			avg_11pulse_Idmax_tRTM /= 11;
			avg_12pulse_Idmax_tRTM /= 12;

		if( (gIdmax[cnt+6] - avg_6pulse_Idmax_tRTM) > Idmax_delta )			//6 pulses condition
		{
			RTM_end = cnt+5;
			break;
		}
		else if( (gIdmax[cnt+7] - avg_7pulse_Idmax_tRTM) > Idmax_delta )	//7 pulses condition
		{
			RTM_end = cnt+6;
			break;
		}
		else if( (gIdmax[cnt+8] - avg_8pulse_Idmax_tRTM) > Idmax_delta )	//8 pulses condition
		{
			RTM_end = cnt+7;
			break;
		}
		else if( (gIdmax[cnt+9] - avg_9pulse_Idmax_tRTM) > Idmax_delta )	//9 pulses condition
		{
			RTM_end = cnt+8;
			break;
		}
		else if( (gIdmax[cnt+10] - avg_10pulse_Idmax_tRTM) > Idmax_delta )	//10 pulses condition
		{
			RTM_end = cnt+9;
			break;
		}
		else if( (gIdmax[cnt+11] - avg_11pulse_Idmax_tRTM) > Idmax_delta )	//11 pulses condition
		{
			RTM_end = cnt+10;
			break;
		}
		else if( (gIdmax[cnt+12] - avg_12pulse_Idmax_tRTM) > Idmax_delta )	//12 pulses condition
		{
			RTM_end = cnt+11;
			break;
		}

	}
	// RTM Release time is counted from the end of last primary pulse to the last pulse under 2ndary control where ILIM stays at 70%.
	*tRTM = (gIdmax_addr[RTM_end-1] - gIdmax_addr[tsoft_start-1])*SAMPLE_RATE_s;

	//*fosc_s_max = freq[pulse_cnt-5];
	*fosc_s_max = freq[RTM_end-1];
		//*tsoft = (gIdmax_addr[RTM_end] - gIdmax_addr[tsoft_start])*SAMPLE_RATE_s;
		// Find ILIM Jitter at 100kHz
	*ilim_min=100.0;
	*ilim_max=0.0;
	//subtract ACgnd from samples
		//Find the AC_Ground: 
		//Move backward from 50 samples before the peak to find a spot on the slope
		//back up more samples until the beginning of pedestal is found (sample to sample delta is > 50e-3)
		//back up another 10 to 15 samples to find the flat spot
		//error condition: stop if you get to the previous peak
		//note: (search_start x 20ns/sample) must be less than Ton for this to work
	RTM_end=RTM_end+1;
	
	while(freq[RTM_end]>101e3 || freq[RTM_end]<99e3) 
	{	
		RTM_end=RTM_end+1;
		
	}
	//for(i=RTM_end; i<(RTM_end+75);i++)//
	//	gIdmax[i] *= Ilim_gain;	
	//	
	//tsoft_end=RTM_end+75;
	//find ACgnd for each peak
	for(cnt=RTM_end;(cnt < RTM_end+400) && cnt<(PULSE_NUM_PROCESSED-5);cnt++) // 200 pulses cover ~2ms of data	// Exclude the last 5 points  of capture
	//for(cnt=RTM_end;(cnt < RTM_end+250) && cnt<400;cnt++)
	{
		ACgnd[cnt] = 1000;
		int search_start=50;
		float istep_downdelta=0;
		
		if(MOSFET_SIZE==8)	istep_downdelta=40e-3;	//equivalent to 80mA from awav
		else				istep_downdelta=30e-3;  //equivalent to 60mA from awav

		//////for(icnt = gIdmax_addr[cnt]-search_start; 
		////////for(icnt = gIdmax_addr[cnt]-100; // Move backward 4us after the peak to find the AC_Ground.
		//////	abs(Gage_chan_a_voltage[icnt]-Gage_chan_a_voltage[icnt-1])<50e-3 && icnt > gIdmax_addr[cnt-1]; // search AC_GND for the next 1us to find the flat portion.
		//////	icnt--)	
		//////{
		//////	ACgnd[cnt] = Gage_chan_a_voltage[icnt];
		//////	ACgnd_addr[cnt] = icnt;
		//////}
		for(icnt = gIdmax_addr[cnt]-search_start; 
		//for(icnt = gIdmax_addr[cnt]-100; // Move backward 4us after the peak to find the AC_Ground.
			icnt > gIdmax_addr[cnt-1]; // search AC_GND for the next 1us to find the flat portion.
			icnt--)	
		{
			//if (abs(Gage_chan_a_voltage[icnt]-Gage_chan_a_voltage[icnt-5])>30e-3)	
			if (abs(Gage_chan_a_voltage[icnt]-Gage_chan_a_voltage[icnt-5])>istep_downdelta)	//Fail at 61mA delta.  bump up to 80mA  cx. 3/2/17
			{
				ACgnd[cnt] = Gage_chan_a_voltage[icnt];
				ACgnd_addr[cnt] = icnt;
				break;
			}
		}
		ACgnd_Ave[cnt] = (Gage_chan_a_voltage[ACgnd_addr[cnt]-15]+	// Average 15 samples after First data point
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-16]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-17]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-18]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-19])/5.0;

		//subtract ACgnd from peak
		gIdmax[cnt] -= ACgnd_Ave[cnt];
		//multiply by 2 for current probe divider
		gIdmax[cnt] /= Ilim_gain;

		/*if((cnt>=tsoft_end) && (cnt<=(tsoft_end+170)) && (freq[cnt]>97e3) && (freq[cnt]<103e3))
		{
			if (*ilim_min >= gIdmax[cnt])
				*ilim_min = gIdmax[cnt];
			if (*ilim_max <= gIdmax[cnt])
				*ilim_max = gIdmax[cnt];
		}*/
				
	}

	for(tcnt=RTM_end;(tcnt+39)<PULSE_NUM_PROCESSED;tcnt++)
	{

		freq_B_avg = (ACgnd_Ave[tcnt+30]+
					  ACgnd_Ave[tcnt+31]+
					  ACgnd_Ave[tcnt+32]+
					  ACgnd_Ave[tcnt+33]+
					  ACgnd_Ave[tcnt+34]+
					  ACgnd_Ave[tcnt+35]+
					  ACgnd_Ave[tcnt+36]+
					  ACgnd_Ave[tcnt+37]+
					  ACgnd_Ave[tcnt+38]+
					  ACgnd_Ave[tcnt+39] )/10;
		freq_A_avg = (ACgnd_Ave[tcnt]+
					  ACgnd_Ave[tcnt+1]+
					  ACgnd_Ave[tcnt+2]+
					  ACgnd_Ave[tcnt+3]+
					  ACgnd_Ave[tcnt+4]+
					  ACgnd_Ave[tcnt+5]+
					  ACgnd_Ave[tcnt+6]+
					  ACgnd_Ave[tcnt+7]+
					  ACgnd_Ave[tcnt+8]+
					  ACgnd_Ave[tcnt+9] )/10;

		if( abs(freq_B_avg - freq_A_avg) < tSoft_freq_delta)
		{
			//printf("Cnt = %.2i, Delta = %.2f \n", cnt, freq[cnt]-freq[PULSE_NUM_PROCESSED-10]);
			tsoft_end = tcnt;
			break;
		}
		tsoft_end = tcnt;
		
	}



	for(tcnt=tsoft_end+10;((tcnt <= tsoft_end+170) && (tcnt<(PULSE_NUM_PROCESSED-5)));tcnt++) 
	{
		if((tcnt>=tsoft_end) && (tcnt<=(tsoft_end+170)) && (freq[tcnt]>97e3) && (freq[tcnt]<103e3))
		{
			if (*ilim_min >= gIdmax[tcnt])
				*ilim_min = gIdmax[tcnt];
			if (*ilim_max <= gIdmax[tcnt])
				*ilim_max = gIdmax[tcnt];
		}
	}

	
	////Calculate ILIM after RTM release -Expect 100% ILIM
	//RTM_end=RTM_end+1;
	//for(cnt=RTM_end; (cnt<=RTM_end+20); cnt++)
	//{
	//	if(gIdmax[cnt]<=gIdmax[RTM_end-1])
	//		break;
	//	avg_100ILIM_RTM = avg_100ILIM_RTM+gIdmax[cnt];
	//}

	//avg_100ILIM_RTM/=20;

	//*ilim_min=avg_100ILIM_RTM;

	//restore altered values
	for(i=RTM_end; i<cnt;i++)//i<cnt condition so as not to alter ILIM value when i=cnt
		gIdmax[i] *= Ilim_gain;	
	int jit_end;
	jit_end=cnt;

	///////////////////////////////
	//F_Modulation- Find two lowest peaks
	///////////////////////////////
 	start=tsoft_end+10;
	start2=tsoft_end+150;
	cnt=start;
	FirstPeak_ILIM = gIdmax[cnt];
	FirstPeak_addr =0;
	SecondPeak_ILIM =0;
	SecondPeak_addr =0;
	// Looking for 1st Peak
	for(cnt=start;(cnt < start+100);cnt++) // 100 pulses should cover 1ms of data, this loop will find First peak between 1 ms from RTM_end
	{
		if (gIdmax[cnt]>FirstPeak_ILIM) 
		{
			FirstPeak_ILIM = gIdmax[cnt];	
			FirstPeak_addr = gIdmax_addr[cnt];	
			FirstPeak_cnt  = cnt;
			start2 = cnt+20;	// Start the 2nd Peak search 50 pulses after the 1st Peak is found.
		}
	}
	//cnt=start2;
	//SecondPeak_ILIM = gIdmax[cnt];
	// Looking for 2nd Peak
	for(cnt=start2;(cnt < start2+100);cnt++) // 100 pulses should cover 1ms of data
	{
		if (gIdmax[cnt]>SecondPeak_ILIM) 
		{
			SecondPeak_ILIM = gIdmax[cnt];	
			SecondPeak_addr = gIdmax_addr[cnt];	
			SecondPeak_cnt  = cnt;
		}
	}
	
	*fModulation_P = 1/(abs(SecondPeak_addr-FirstPeak_addr)*SAMPLE_RATE_s);



	//Write Soft_start debug file
	//DEBUG = 1;
	if(DEBUG==1 && gDEBUG)
	//if(DEBUG==1)
	{
		int i,max_cnt,strt_cnt;
		i=0;
		max_cnt=700;
		strt_cnt=10;
		FILE * fpr = fopen("e:\\dl4\\Inn3xxx_ILIM_SSS_datadump.txt", "w");
		if (! fpr)
			return;
		fprintf(fpr,"ILIM_SSS, 20ns per sample (addr count)\n" );
		fprintf(fpr,"  Amplitude values are approximate (baseline shift has not been subtracted)\n" );
		fprintf(fpr,"  Start in Primary control, approx 25kHz rat\n" );
		fprintf(fpr,"  ILIM 70pct (taken from pulses 5-35, 30 pulses)\n" );
		fprintf(fpr,"	Idmax_ave   = %.1f mA\n",*Idmax_ave*1e3/Ilim_gain );
		fprintf(fpr,"	Fosc_Sss_P  = %.1f kHz\n",*Fosc_Sss_P );
		fprintf(fpr,"  Period of approx 60us signals handshake and Secondary takes control\n" );
		fprintf(fpr,"	tHandshake   = %.1f us at peak# %i \n",*tHandshake*1e6 ,tsoft_start);
		fprintf(fpr,"  Secondary control: Frequency and Ilim begin increasing\n" );
		fprintf(fpr,"  ILIM_Secondary Soft Start\n" );
		fprintf(fpr,"	tsoft_start = peak %i\n",tsoft_start );
		fprintf(fpr,"	tsoft_end   = peak %i\n",tsoft_end );
		fprintf(fpr,"	tsoft       = %.1f ms (addr[tsoft_end] - addr[tsoft_start])*SAMPLE_RATE)\n" ,  *tsoft*1e3);
		fprintf(fpr,"	fosc_s_min  = %.1f kHz (freq[tsoft_start])\n" , *fosc_s_min*1e-3);
		fprintf(fpr,"	fosc_s_max  = %.1f kHz (freq[tsoft_end])\n",    *fosc_s_max*1e-3 );
		fprintf(fpr,"  ILIM Jitter at 132kHz\n" );
		fprintf(fpr,"   FirstPeak_ILIM  = %.1f mA at addr %i\n",	FirstPeak_ILIM*1e3/Ilim_gain, (int) FirstPeak_addr);	
		fprintf(fpr,"   SecondPeak_ILIM = %.1f mA at addr %i\n",	SecondPeak_ILIM*1e3/Ilim_gain,(int) SecondPeak_addr);	
		fprintf(fpr,"   fModulation     = %.1f Hz (1/(abs(SecondPeak_addr-FirstPeak_addr)*SAMPLE_RATE)\n",*fModulation_P);
		fprintf(fpr,"   ilim_min  = %.1f mA \n",	*ilim_min*1e3/Ilim_gain);	
		fprintf(fpr,"   ilim_max  = %.1f mA \n",	*ilim_max*1e3/Ilim_gain);	

		fprintf(fpr,"\n" );
		fprintf(fpr,"\n" );

		//Start of pattern
		fprintf(fpr,"Start of pattern\n" );
		if (pulse_cnt<max_cnt) max_cnt = pulse_cnt;	//check number of actual samples
		for(i=0; i<max_cnt; i++)
		{
			if(gIdmax[i] > 0)
				fprintf(fpr,"ILIM_SSS, cnt= %i, %.1fmA, addr=%i, time= %.3fms, period= %.1fus, Freq = %.3fkHz\n", i, gIdmax[i]*1000/Ilim_gain, gIdmax_addr[i], gIdmax_addr[i]*20e-6,pulse_period[i]*1e6, freq[i]*1e-3);
		}
		fprintf(fpr,"\n" );

		//tsoft_end
		fprintf(fpr,"tsoft_end-50 peaks to ILIM_Jitter end+50 peaks\n" );
		strt_cnt=tsoft_end-50;	//check number of actual peaks
		max_cnt=SecondPeak_cnt+50;	//check number of actual peaks
		//Modification for MINNO
		/*strt_cnt=1000;
		max_cnt=1299;*/
		if (pulse_cnt<max_cnt) 
		{
			strt_cnt = pulse_cnt-10;
			max_cnt = pulse_cnt;
		}
		//End of MINNO modification
		fprintf(fpr,"tsoft_end   = peak %i\n",tsoft_end );
		for(i=strt_cnt; i<max_cnt; i++)
		{
			if(gIdmax[i] > 0)
				fprintf(fpr,"ILIM_SSS, cnt= %i, %.1fmA, addr=%i , time= %.3fms, period= %.1fus, Freq = %.3fkHz\n", i, gIdmax[i]*1000/Ilim_gain, gIdmax_addr[i], gIdmax_addr[i]*20e-6, pulse_period[i]*1e6, freq[i]*1e-3);
		}
		fprintf(fpr,"\n" );


		fprintf (fpr, "end;\n");
		fclose(fpr);

	}
	//DEBUG = 0;
	//Write Soft_start AC_offset debug file
	if(DEBUG==1 && gDEBUG)
	//if(DEBUG==1)
	{
		int i,max_cnt,strt_cnt;
		i=0;
		max_cnt=400;
		strt_cnt=10;
		FILE * fpr2 = fopen("e:\\dl4\\Inn3xxx_ILIM_SSS_GND_datadump.txt", "w");
		if (! fpr2)
			return;
		fprintf(fpr2,"ILIM_SSS_GND, 20ns per sample (addr count)\n" );
		fprintf(fpr2,"  Ground offset values for baseline shift of each peak\n" );

		fprintf(fpr2,"\n" );
		fprintf(fpr2,"\n" );

		//tsoft_end
		fprintf(fpr2,"Offset for each peak from tsoft_end to ILIM_Jitter end\n" );
		strt_cnt=tsoft_end;	//check number of actual peaks
		max_cnt=SecondPeak_cnt;	//check number of actual peaks	
		//strt_cnt=1;	//check number of actual peaks
		//max_cnt=600;	//check number of actual peaks	
		if (pulse_cnt<=max_cnt) 
		{
			strt_cnt = pulse_cnt-10;
			max_cnt = pulse_cnt;
		}
		for(i=strt_cnt; i<=max_cnt; i++)
		{
			fprintf(fpr2,"ILIM_SSS_GND, cnt= %i, Offset=%.2fmA, offset addr=%i, offset time= %.3fms,\n", i, ACgnd_Ave[i]*1000/Ilim_gain, ACgnd_addr[i], ACgnd_addr[i]*20e-6);
		}
		fprintf(fpr2,"\n" );
		fprintf (fpr2, "end;\n");
		fclose(fpr2);

	}

	//Write Search start_addr debug file
	if(DEBUG==1 && gDEBUG)
	{
		int i=0;
		int max_cnt,strt_cnt;
		max_cnt=700;
		strt_cnt=2;
		FILE * fpr3 = fopen("e:\\dl4\\Inn3xxx_ILIM_SSS_start_addr_datadump.txt", "w");
		if (! fpr3)
			return;
		fprintf(fpr3,"Start addresses from peak search algorithm\n" );
		fprintf(fpr3,"  Check against AWAV file to see the starting address for the search of each peak\n" );
		fprintf(fpr3,"\n" );
		fprintf(fpr3,"\n" );

		if (pulse_cnt<max_cnt) 
		{
			max_cnt = pulse_cnt;
		}
		if (strt_cnt<2) 
		{
			strt_cnt = 2;
		}
		for(i=strt_cnt; i<max_cnt-10; i++)
		{
			fprintf(fpr3,"peak number= %i, search start addr=%i,  pts from last peak= %i, pts from last start addr=%i\n", i, start_addr_arry[i], start_addr_arry[i] - gIdmax_addr[i],start_addr_arry[i] - start_addr_arry[i-1]);
		}
		fprintf(fpr3,"\n" );
		fprintf (fpr3, "end;\n");
		fclose(fpr3);

	}

}

void Gage_Find_Ilim_SSS_MINNO(float *Idmax_ave, float *tsoft, float *tHandshake, float *fosc_s_min, float *fosc_s_max, float *ilim_min, float *ilim_max, float *fModulation_P, float *Fosc_Sss_P, float *tRTM)
{
	*Idmax_ave =0.0;
	*tsoft  =0.0;
	*tHandshake   =0.0;
	*fosc_s_min =0.0;
	*fosc_s_max =0.0;
	*ilim_min =0.0;
	*ilim_max =0.0;
	*fModulation_P=0.0;
	*Fosc_Sss_P=0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Idmax_ave		=999.0;
		*tsoft		=999.0;
		*tHandshake		=999.0;
		*fosc_s_min =999.0;
		*fosc_s_max =999.0;
		*ilim_min =999.0;
		*ilim_max =999.0;
		*fModulation_P=999.0;
		*Fosc_Sss_P=999.0;
		*tRTM=999.0;
		return;
	}

	int	PULSE_NUM_PROCESSED = 0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr = 0;
	int tsoft_start = 0, tsoft_end = 0;
	int RTM_end = 0;
	int pulse_cnt = 0;
	int cnt = 0;
	int loop_cnt = 0;
	float DataValue = 0.0;
	float DataValueMin = 0.0;
	float DataValueMax = 0.0;

	// Variables for ILIM peak tests
	float DiDt[4000]		 = {};
	int ACgnd_addr[4000]	 = {};				// GND is taken before device turns on
	float pulse_period[4000] = {};
	float freq[4000]		 = {};

	float FirstPeak_ILIM	 = 0.0;
	float FirstPeak_addr	 = 0.0;
	int	  FirstPeak_cnt		 = 0;
	float SecondPeak_ILIM	 = 0.0;
	float SecondPeak_addr	 = 0.0;
	int	  SecondPeak_cnt	 = 0;
	float start1 = 0.0, start2 = 0.0;

	float Period = 0.0;
	int	  Sample_per_cycle = 0;

	Period = 1/(gFOSC_TARGET_P-10e3);		//Takes care of device with Jitter up to 10kHz
	SAMPLE_RATE_s = 20e-9;
	Sample_per_cycle = Period/SAMPLE_RATE_s;

	for (cnt = 0; cnt < 4000; cnt++)
	{
		gIdmax[cnt] = -100;
		gIdmax_addr[cnt]  = 0;
	}

	// transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	// transfer data to Gage_chan_a_voltage array
	start_addr = 0;						// Include the 1st 3 pulses for datalog.

	PULSE_NUM_PROCESSED = Gage_Find_Ipeak(Gage_chan_a_voltage, SAMPLE_SIZE, SAMPLE_RATE_s, Ilim_gain, 500, ACgnd_addr, gIdmax_addr, gIdmax, DiDt);

	pulse_period[0] = 45e-6;			// Assume 1st period is 45us (22kHz)
	freq[0] = 1 / pulse_period[0];
	for (pulse_cnt = 1; pulse_cnt < PULSE_NUM_PROCESSED; pulse_cnt++)
	{
		// period and freq based on Peak Ilim.
		pulse_period[pulse_cnt] = (gIdmax_addr[pulse_cnt] - gIdmax_addr[pulse_cnt-1]) * SAMPLE_RATE_s;
		freq[pulse_cnt] = 1 / pulse_period[pulse_cnt];
	}

	// Average ILIM 70pct from pulse 2-11 (10 pulses)
	loop_cnt = 0;
	for (cnt = 2; cnt <= 11; cnt++)
	{
		*Idmax_ave += gIdmax[cnt];
		*Fosc_Sss_P += freq[cnt];
		loop_cnt++;
	}
	*Idmax_ave /= loop_cnt;
	*Fosc_Sss_P /= loop_cnt;

	// find handshake based on freq
	for (cnt = 0; cnt < PULSE_NUM_PROCESSED; cnt++)
	{
		if (freq[cnt] > 10e3 && freq[cnt] < 19e3 && tsoft_start == 0)	//cx 3/14/2016 (tHandShake change on the same part from 69us to 95us on B4 silicon)
		{
			*tHandshake = 1 / freq[cnt];
			tsoft_start = cnt;
			break;
		}
	}

	float sum_Idmax_tRTM = 0.0;
	float avg_Idmax_tRTM = 0.0;
	loop_cnt = 0;
	// Looking for t_RTM_Release time, expect around 100us
	for (cnt = tsoft_start; cnt < (tsoft_start + 20); cnt++) // 20 pulses should cover much more than 100us of data
	{
		sum_Idmax_tRTM += gIdmax[cnt];
		loop_cnt++;
		avg_Idmax_tRTM = sum_Idmax_tRTM / loop_cnt;

		if ((avg_Idmax_tRTM / gIdmax[cnt + 1]) < 0.85)
		{
			RTM_end = cnt;
			break;
		}
	}

	// RTM Release time is counted from the end of last primary pulse to the last pulse under 2ndary control where ILIM stays at 70%.
	*tRTM = (gIdmax_addr[RTM_end-1] - gIdmax_addr[tsoft_start-1])*SAMPLE_RATE_s;

	DataValueMin = 99999;
	DataValueMax = -9999;
	for (cnt = tsoft_start+1; cnt < RTM_end; cnt++)
	{
		DataValue = freq[cnt];
		if (DataValue < DataValueMin)
			DataValueMin = DataValue;
		if (DataValue > DataValueMax)
			DataValueMax = DataValue;
	}

	*fosc_s_min = DataValueMin;
	*fosc_s_max = DataValueMax;
	
	*tsoft = (gIdmax_addr[RTM_end] - gIdmax_addr[tsoft_start])*SAMPLE_RATE_s;
	
	// Find ILIM Jitter at 100kHz
	*ilim_min = 100.0;
	*ilim_max =   0.0;
	RTM_end = RTM_end + 1;
	
	while (freq[RTM_end] > 101e3 || freq[RTM_end] < 99e3)
	{
		RTM_end = RTM_end+1;
	}

	tsoft_end = RTM_end;

	for (cnt = tsoft_end + 10; ((cnt <= tsoft_end + 170) && (cnt < (PULSE_NUM_PROCESSED - 5))); cnt++)
	{
		if ((cnt >= tsoft_end) && (cnt <= (tsoft_end + 170)) && (freq[cnt] > 97e3) && (freq[cnt] < 103e3))
		{
			if (*ilim_min >= gIdmax[cnt])
				*ilim_min = gIdmax[cnt];
			if (*ilim_max <= gIdmax[cnt])
				*ilim_max = gIdmax[cnt];
		}
	}

	// F_Modulation- Find two lowest peaks
	start1 = tsoft_end + 10;
	start2 = tsoft_end + 150;
	cnt = start1;
	FirstPeak_ILIM = gIdmax[cnt];
	FirstPeak_addr = 0;
	SecondPeak_ILIM = 0;
	SecondPeak_addr = 0;
	// Looking for 1st Peak
	for (cnt = start1; cnt < start1 + 100; cnt++) // 100 pulses should cover 1ms of data, this loop will find First peak between 1 ms from RTM_end
	{
		if (gIdmax[cnt] > FirstPeak_ILIM)
		{
			FirstPeak_ILIM = gIdmax[cnt];
			FirstPeak_addr = gIdmax_addr[cnt];
			FirstPeak_cnt  = cnt;
			start2 = cnt + 20;	// Start the 2nd Peak search 20 pulses after the 1st Peak is found.
		}
	}

	// Looking for 2nd Peak
	for (cnt = start2; cnt < start2 + 100; cnt++) // 100 pulses should cover 1ms of data
	{
		if (gIdmax[cnt] > SecondPeak_ILIM)
		{
			SecondPeak_ILIM = gIdmax[cnt];
			SecondPeak_addr = gIdmax_addr[cnt];
			SecondPeak_cnt  = cnt;
		}
	}
	
	*fModulation_P = 1 / (abs(SecondPeak_addr - FirstPeak_addr) * SAMPLE_RATE_s);


	//Awav
	if(DEBUG==1 && gDEBUG)
	//if(DEBUG==1)
	{
		char wave_name_Id[150] ="/0";

		strcpy (wave_name_Id, WAVE_NAME);
		strcat (wave_name_Id, "_Id"); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}

	//Write Soft_start debug file
	//DEBUG = 1;
	if(DEBUG==1 && gDEBUG)
	//if(DEBUG==1)
	{
		int i,max_cnt,strt_cnt;
		i=0;
		max_cnt=700;
		strt_cnt=10;
		FILE * fpr = fopen("e:\\dl4\\Inn3xxx_ILIM_SSS_datadump.txt", "w");
		if (! fpr)
			return;
		fprintf(fpr,"ILIM_SSS, 20ns per sample (addr count)\n" );
		fprintf(fpr,"  Amplitude values are approximate (baseline shift has not been subtracted)\n" );
		fprintf(fpr,"  Start in Primary control, approx 25kHz rat\n" );
		fprintf(fpr,"  ILIM 70pct (taken from pulses 5-35, 30 pulses)\n" );
		fprintf(fpr,"	Idmax_ave   = %.1f mA\n",*Idmax_ave*1e3/Ilim_gain );
		fprintf(fpr,"	Fosc_Sss_P  = %.1f kHz\n",*Fosc_Sss_P );
		fprintf(fpr,"  Period of approx 60us signals handshake and Secondary takes control\n" );
		fprintf(fpr,"	tHandshake   = %.1f us at peak# %i \n",*tHandshake*1e6 ,tsoft_start);
		fprintf(fpr,"  Secondary control: Frequency and Ilim begin increasing\n" );
		fprintf(fpr,"  ILIM_Secondary Soft Start\n" );
		fprintf(fpr,"	tsoft_start = peak %i\n",tsoft_start );
		fprintf(fpr,"	tsoft_end   = peak %i\n",tsoft_end );
		fprintf(fpr,"	tsoft       = %.1f ms (addr[tsoft_end] - addr[tsoft_start])*SAMPLE_RATE)\n" ,  *tsoft*1e3);
		fprintf(fpr,"	fosc_s_min  = %.1f kHz (freq[tsoft_start])\n" , *fosc_s_min*1e-3);
		fprintf(fpr,"	fosc_s_max  = %.1f kHz (freq[tsoft_end])\n",    *fosc_s_max*1e-3 );
		fprintf(fpr,"  ILIM Jitter at 132kHz\n" );
		fprintf(fpr,"   FirstPeak_ILIM  = %.1f mA at addr %i\n",	FirstPeak_ILIM*1e3/Ilim_gain, (int) FirstPeak_addr);	
		fprintf(fpr,"   SecondPeak_ILIM = %.1f mA at addr %i\n",	SecondPeak_ILIM*1e3/Ilim_gain,(int) SecondPeak_addr);	
		fprintf(fpr,"   fModulation     = %.1f Hz (1/(abs(SecondPeak_addr-FirstPeak_addr)*SAMPLE_RATE)\n",*fModulation_P);
		fprintf(fpr,"   ilim_min  = %.1f mA \n",	*ilim_min*1e3/Ilim_gain);	
		fprintf(fpr,"   ilim_max  = %.1f mA \n",	*ilim_max*1e3/Ilim_gain);	

		fprintf(fpr,"\n" );
		fprintf(fpr,"\n" );

		//Start of pattern
		fprintf(fpr,"Start of pattern\n" );
		if (pulse_cnt<max_cnt) max_cnt = pulse_cnt;	//check number of actual samples
		for(i=0; i<max_cnt; i++)
		{
			if(gIdmax[i] > 0)
				fprintf(fpr,"ILIM_SSS, cnt= %i, %.1fmA, addr=%i, time= %.3fms, period= %.1fus, Freq = %.3fkHz\n", i, gIdmax[i]*1000/Ilim_gain, gIdmax_addr[i], gIdmax_addr[i]*20e-6,pulse_period[i]*1e6, freq[i]*1e-3);
		}
		fprintf(fpr,"\n" );

		//tsoft_end
		fprintf(fpr,"tsoft_end-50 peaks to ILIM_Jitter end+50 peaks\n" );
		strt_cnt=tsoft_end-50;	//check number of actual peaks
		max_cnt=SecondPeak_cnt+50;	//check number of actual peaks
		//Modification for MINNO
		/*strt_cnt=1000;
		max_cnt=1299;*/
		if (pulse_cnt<max_cnt) 
		{
			strt_cnt = pulse_cnt-10;
			max_cnt = pulse_cnt;
		}
		//End of MINNO modification
		fprintf(fpr,"tsoft_end   = peak %i\n",tsoft_end );
		for(i=strt_cnt; i<max_cnt; i++)
		{
			if(gIdmax[i] > 0)
				fprintf(fpr,"ILIM_SSS, cnt= %i, %.1fmA, addr=%i , time= %.3fms, period= %.1fus, Freq = %.3fkHz\n", i, gIdmax[i]*1000/Ilim_gain, gIdmax_addr[i], gIdmax_addr[i]*20e-6, pulse_period[i]*1e6, freq[i]*1e-3);
		}
		fprintf(fpr,"\n" );
		fprintf (fpr, "end;\n");
		fclose(fpr);
	}
}

void Gage_Find_Ilim_SSS_Turret(float *Idmax_ave, float *tsoft, float *tHandshake, float *fosc_s_min, float *fosc_s_max, float *ilim_min, float *ilim_max, float *fModulation_P, float *Fosc_Sss_P, float *tRTM)
{
	*Idmax_ave =0.0;
	*tsoft  =0.0;
	*tHandshake   =0.0;
	*fosc_s_min =0.0;
	*fosc_s_max =0.0;
	*ilim_min =0.0;
	*ilim_max =0.0;
	*fModulation_P=0.0;
	*Fosc_Sss_P=0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Idmax_ave		=999.0;
		*tsoft		=999.0;
		*tHandshake		=999.0;
		*fosc_s_min =999.0;
		*fosc_s_max =999.0;
		*ilim_min =999.0;
		*ilim_max =999.0;
		*fModulation_P=999.0;
		*Fosc_Sss_P=999.0;
		return;
	}

	int	PULSE_NUM_NEED  =0;		// Define min pulses numbers need to be caputre. 4*7.5us = 30us. 2K sample allows 40us. 4K -> 80us
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int tsoft_start=0, tsoft_end=0;
	int pulse_cnt =0;
	int icnt =0, cnt=0; 
	float Vdson_peak_ave =0.0;
	float Vped_threshold =0.0;
	
	// Variables for ILIM peak tests
	float ACgnd[4000]      ={0.0};
	float ACgnd_Ave[4000]  ={0.0};
	float Id05us_Ave[4000] ={0.0};
	float pulse_width[4000]={0.0};
	float Ton[4000]		 ={0.0};
	float Toff[4000]		 ={0.0};
	float DiDt[4000]		 ={0.0};
	int Id05us_Addr[4000]  ={0};
	int ACgnd_addr[4000]   ={1000};				// GND is taken before device turns on
	float pulse_period[4000]	={0.0};
	float freq[4000]	={0.0};

	float FirstPeak_ILIM =0.0;
	float FirstPeak_addr =0.0;
	int   FirstPeak_cnt	 =0;
	float SecondPeak_ILIM =0.0;
	float SecondPeak_addr =0.0;
	int   SecondPeak_cnt  =0;
	float min=0, max=0;
	float start=0.0, start2=0.0;
	float dummy_array[200]={0.0};


	// Variables for Rdson_spec tests at 10% ILIM_NORM level
	float Ilim_spec =0.0;
	float Vdson_spec[4000] ={0.0};
	float Idson_spec[4000] ={0.0};
	float Rdson_spec[4000] ={0.0};
	float Vdson_spec_ave =0.0;
	float Idson_spec_ave =0.0;
	int Id_spec_addr[4000] ={0};
	float istep_downdelta = 0.0;

	float Id_temp =0.0;
	float Id_one_data_pts =0.0;
	int	  lcnt =0, i=0;
	int   loop_cnt=0;
	int	  ave_start_pulse =0;
	int	  ave_pulses	  =0;
	int	  ave_end_pulse	  =0;

	float Period=0.0;
	int	  Sample_per_cycle=0;
	int   FIND_ILIM_LO_FLAG=0;

	float Off_Time=0.0;
	float RTM_High_Id=0.0,
		  RTM_Low_Id=0.0;

	char wave_name_Id[150] ="/0"; 
	char wave_name_Vd[150] ="/0"; 


	Period = 1/(gFOSC_TARGET_P-10e3);		//Takes care of device with Jitter up to 10kHz
	SAMPLE_RATE_s = 20e-9;
	Sample_per_cycle = Period/SAMPLE_RATE_s;

//	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	for (icnt=0; icnt<4000; icnt++)
	{
		gIdmax[icnt] = -100;
		gIdmax_addr[icnt]  = 0;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array
	start_addr = 0;						// Include the 1st 3 pulses for datalog.

	if(DEBUG==1)
	{
		strcpy (wave_name_Id, WAVE_NAME);
		strcat (wave_name_Id, "_Id"); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}

	while (Gage_chan_a_voltage[start_addr]< 0.0 && start_addr < SAMPLE_SIZE)
		start_addr+=1;					// Fast forward by 1 samples at rate of 20ns/sample
	// Error check
	if ((start_addr + Sample_per_cycle + 125) > SAMPLE_SIZE ) 	// Searching window = Period + 2.5us(from next pulse).  
	{
		*Idmax_ave  = 999.0;
		return;
	}
	// Search for the peak
//	while ((pulse_cnt< PULSE_NUM_NEED)&& (start_addr < SAMPLE_SIZE))
	//while (start_addr < SAMPLE_SIZE)
	while (start_addr < SAMPLE_SIZE-10)
	{
		// Find Idmax
//		for(icnt = start_addr; (icnt<(start_addr+SAMPLE_SIZE*0.01)) && ((icnt+5)<SAMPLE_SIZE) ; icnt++)
		for(icnt = start_addr; (icnt<(start_addr+4500)) && ((icnt+5)<SAMPLE_SIZE) ; icnt++)
		{
			//Initial gIdmax
			if(icnt==start_addr)
				gIdmax[pulse_cnt]= Gage_chan_a_voltage[icnt];
			if (pulse_cnt==0)
			{
				if(Gage_chan_a_voltage[icnt] >= gIdmax[pulse_cnt])
				{
					if((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-10] < 0.1)&&((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-10] > 0.0)))  //Need to skip pedestal peak ilim.
					{
						gIdmax[pulse_cnt] = Gage_chan_a_voltage[icnt];
						gIdmax_addr[pulse_cnt] = icnt;
						if ((gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt+5]) > 0.15 &&      //HL modified to fix wrong Ilim peak calculation.
							abs(gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt-10]) < 0.15 )    //HL modified to fix wrong Ilim peak calculation.
						//if ((gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt+5]) > 0.10 &&     
						//	abs(gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt-5]) < 0.10 )   
						{
							if((SAMPLE_SIZE-icnt) > 200)
							{
								for (i=0 ; i<199;i++)
									dummy_array[i] = Gage_chan_a_voltage[(icnt-50)+i];	//save to observable array
							}
							break;	//peak found
						}
					}
				
				}
			}
			else
			{
				if(Gage_chan_a_voltage[icnt] >= gIdmax[pulse_cnt] && Gage_chan_a_voltage[icnt]>0.8*gIdmax[pulse_cnt-1])
				{
					if((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-10] < 0.1)&&((Gage_chan_a_voltage[icnt] - Gage_chan_a_voltage[icnt-10] > 0.0)))
					{
						gIdmax[pulse_cnt] = Gage_chan_a_voltage[icnt];
						gIdmax_addr[pulse_cnt] = icnt;
						if ((gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt+5]) > 0.10 &&      //HL modified to fix wrong Ilim peak calculation.
							abs(gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt-10]) < 0.10 )    //HL modified to fix wrong Ilim peak calculation.
						//if ((gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt+5]) > 0.10 &&     
						//	abs(gIdmax[pulse_cnt] - Gage_chan_a_voltage[icnt-5]) < 0.10 )   
						{
							if((SAMPLE_SIZE-icnt) > 200)
							{
								for (i=0 ; i<199;i++)
									dummy_array[i] = Gage_chan_a_voltage[(icnt-50)+i];	//save to observable array
							}
							break;	//peak found
						}
					}
				}
			}
		}
		
		// Calculate period and freq based on Peak Ilim.
		if(pulse_cnt==0)
			pulse_period[pulse_cnt] = 45e-6;	// Assume 1st period is 45us (22kHz)
		else
			pulse_period[pulse_cnt] = (gIdmax_addr[pulse_cnt] - gIdmax_addr[pulse_cnt-1])*SAMPLE_RATE_s;
		
		freq[pulse_cnt] = 1/pulse_period[pulse_cnt];

		//Reset gIdmax
		if(gIdmax[pulse_cnt] < -100)
			gIdmax[pulse_cnt] = -100;

		if(freq[pulse_cnt]<20e3)
			start_addr = gIdmax_addr[pulse_cnt] + 500; 
		else if(freq[pulse_cnt]<40e3)
			start_addr = gIdmax_addr[pulse_cnt] + 700;  //works for Size x8, and x5		
//			start_addr = gIdmax_addr[pulse_cnt] + 1500; //works for Size x8, not x5		12/19/2016 xie
		else 
			start_addr = gIdmax_addr[pulse_cnt] + (pulse_period[pulse_cnt]/SAMPLE_RATE_s)*0.35; // - 200;
//			start_addr = gIdmax_addr[pulse_cnt] + (pulse_period[pulse_cnt]/SAMPLE_RATE_s)*0.7; // - 200;

		PULSE_NUM_PROCESSED ++;
		pulse_cnt ++;

		if ( (icnt> (SAMPLE_SIZE-400)) || PULSE_NUM_PROCESSED > 3000) 	
			break;
	}

	loop_cnt=0;
	
	//Average ILIM 70pct from pulse 5-35 (30 pulses)
	for(cnt=5;cnt<35;cnt++)
	{
		ACgnd[cnt] = 1000;
		// Need to find AC_GND for the first portion of capture.

		//*****************************************************************
		//** This logic fail at the end of tSoft awav due to ILIM droop  **
		//*****************************************************************
		//for(i=gIdmax_addr[cnt]; (Gage_chan_a_voltage[i]>=0.0); i--)	
		/*
			When ILIM droop, ILIM drop below zero so searching back from the ILIM peak address to find AGND is wrong

		*/

//		for(i=gIdmax_addr[cnt]; (Gage_chan_a_voltage[i]>=0.0); i--)	
		for(i=gIdmax_addr[cnt]-20; i>gIdmax_addr[cnt-1]; i--)	
		{
			if (abs(Gage_chan_a_voltage[i]-Gage_chan_a_voltage[i-5])>30e-3)
			{
				 ACgnd[cnt] = Gage_chan_a_voltage[i];
				 ACgnd_addr[cnt] = i;
				 break;
			}
		}
		
		ACgnd_Ave[cnt] = (Gage_chan_a_voltage[ACgnd_addr[cnt]-15]+	// 15 samples away from First data point
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-16]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-17]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-18]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-19])/5.0;
		gIdmax[cnt] -= ACgnd_Ave[cnt];
		gIdmax[cnt] /= Ilim_gain;

		*Idmax_ave += gIdmax[cnt];
		*Fosc_Sss_P += freq[cnt];
		loop_cnt++;
	}
	if(loop_cnt != 0)
	{
		*Idmax_ave /= loop_cnt;
		*Fosc_Sss_P /= loop_cnt;
	}

	for(cnt=5;cnt<35;cnt++)
		gIdmax[cnt] *= Ilim_gain;	//restore captured values

	for(cnt=0;cnt<PULSE_NUM_PROCESSED;cnt++)
	{
		//if(freq[cnt]<20e3)	//CX 12/26/2016
		if(freq[cnt]>14e3 && freq[cnt]<17e3 && tsoft_start==0)	//cx 12/26/2016
		{
			*tHandshake = 1/freq[cnt];
			tsoft_start = cnt+1;
		}
	}

	if(g_TurretCB&&freq[tsoft_start] < 28e-3)
	{
		tsoft_start++;
	}
	*fosc_s_min = freq[tsoft_start];
	for(cnt=tsoft_start;cnt<PULSE_NUM_PROCESSED;cnt++)
	{
		if(abs(freq[cnt]-freq[PULSE_NUM_PROCESSED-10])<1e3)
		{
			//printf("Cnt = %.2i, Delta = %.2f \n", cnt, freq[cnt]-freq[PULSE_NUM_PROCESSED-10]);
			tsoft_end = cnt;
			break;
		}
		
	}
	*fosc_s_max = freq[tsoft_end];
	*tsoft = (gIdmax_addr[tsoft_end] - gIdmax_addr[tsoft_start])*SAMPLE_RATE_s;

// Find ILIM Jitter at 132kHz
	*ilim_min=100.0;
	*ilim_max=0.0;
	for(cnt=tsoft_end;(cnt < tsoft_end+250) && cnt<(PULSE_NUM_PROCESSED-5);cnt++) // 250 pulses cover ~2ms of data	// Exclude the last 5 points  of capture
	{
		ACgnd[cnt] = 1000;
		int search_start=50;
		float istep_down_delta=0;
		
		if(MOSFET_SIZE==8)	istep_downdelta=40e-3;	//equivalent to 80mA from awav
		else				istep_downdelta=30e-3;  //equivalent to 60mA from awav

		//////for(icnt = gIdmax_addr[cnt]-search_start; 
		////////for(icnt = gIdmax_addr[cnt]-100; // Move backward 4us after the peak to find the AC_Ground.
		//////	abs(Gage_chan_a_voltage[icnt]-Gage_chan_a_voltage[icnt-1])<50e-3 && icnt > gIdmax_addr[cnt-1]; // search AC_GND for the next 1us to find the flat portion.
		//////	icnt--)	
		//////{
		//////	ACgnd[cnt] = Gage_chan_a_voltage[icnt];
		//////	ACgnd_addr[cnt] = icnt;
		//////}
		for(icnt = gIdmax_addr[cnt]-search_start; 
		//for(icnt = gIdmax_addr[cnt]-100; // Move backward 4us after the peak to find the AC_Ground.
			icnt > gIdmax_addr[cnt-1]; // search AC_GND for the next 1us to find the flat portion.
			icnt--)	
		{
			//if (abs(Gage_chan_a_voltage[icnt]-Gage_chan_a_voltage[icnt-5])>30e-3)	
			if (abs(Gage_chan_a_voltage[icnt]-Gage_chan_a_voltage[icnt-5])>istep_downdelta)	//Fail at 61mA delta.  bump up to 80mA  cx. 3/2/17
			{
				ACgnd[cnt] = Gage_chan_a_voltage[icnt];
				ACgnd_addr[cnt] = icnt;
				break;
			}
		}
		ACgnd_Ave[cnt] = (Gage_chan_a_voltage[ACgnd_addr[cnt]-15]+	// Average 15 samples after First data point
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-16]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-17]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-18]+
						  Gage_chan_a_voltage[ACgnd_addr[cnt]-19])/5.0;


		gIdmax[cnt] -= ACgnd_Ave[cnt];
		gIdmax[cnt] /= Ilim_gain;
		if (*ilim_min >= gIdmax[cnt])
			*ilim_min = gIdmax[cnt];
		if (*ilim_max <= gIdmax[cnt])
			*ilim_max = gIdmax[cnt];
		
	}
	//restore altered values
	for(i=tsoft_end; i<=cnt;i++)
		gIdmax[i] *= Ilim_gain;	
	int jit_end;
	jit_end=cnt;

	///////////////////////////////
	//F_Modulation
	///////////////////////////////
 	start=tsoft_end+50;
	start2=tsoft_end+150;

	FirstPeak_ILIM =0;
	FirstPeak_addr =0;
	SecondPeak_ILIM =0;
	SecondPeak_addr =0;
	// Looking for 1st Peak
	for(cnt=start;(cnt < start+100);cnt++) // 100 pulses should cover 1ms of data
	{
		if (gIdmax[cnt]>FirstPeak_ILIM) 
		{
			FirstPeak_ILIM = gIdmax[cnt];	
			FirstPeak_addr = gIdmax_addr[cnt];	
			FirstPeak_cnt  = cnt;
			start2 = cnt+50;	// Start the 2nd Peak search 50 pulses after the 1st Peak is found.
		}
	}
	// Looking for 2nd Peak
	for(cnt=start2;(cnt < start2+100);cnt++) // 100 pulses should cover 1ms of data
	{
		if (gIdmax[cnt]>SecondPeak_ILIM) 
		{
			SecondPeak_ILIM = gIdmax[cnt];	
			SecondPeak_addr = gIdmax_addr[cnt];	
			SecondPeak_cnt  = cnt;
		}
	}
	
	*fModulation_P = 1/(abs(SecondPeak_addr-FirstPeak_addr)*SAMPLE_RATE_s);

	//Write Soft_start debug file
	if(DEBUG==1)
	{
		int i=0;
		int max_cnt=400,strt_cnt;
		FILE * fpr = fopen("e:\\dl4\\Inn3xxx_ILIM_SSS_datadump.txt", "w");
		if (! fpr)
			return;
		fprintf(fpr,"ILIM_SSS, 20ns per sample (addr count)\n" );
		fprintf(fpr,"  Amplitude values are approximate (baseline shift has not been subtracted)\n" );
		fprintf(fpr,"  Start in Primary control, approx 25kHz rat\n" );
		fprintf(fpr,"  ILIM 70pct (taken from pulses 5-35, 30 pulses)\n" );
		fprintf(fpr,"	Idmax_ave   = %.1f mA\n",*Idmax_ave*1e3/Ilim_gain );
		fprintf(fpr,"	Fosc_Sss_P  = %.1f kHz\n",*Fosc_Sss_P );
		fprintf(fpr,"  Period of approx 60us signals handshake and Secondary takes control\n" );
		fprintf(fpr,"	tHandshake   = %.1f us at peak# %i \n",*tHandshake*1e6 ,tsoft_start);
		fprintf(fpr,"  Secondary control: Frequency and Ilim begin increasing\n" );
		fprintf(fpr,"  ILIM_Secondary Soft Start\n" );
		fprintf(fpr,"	tsoft_start = peak %i\n",tsoft_start );
		fprintf(fpr,"	tsoft_end   = peak %i\n",tsoft_end );
		fprintf(fpr,"	tsoft       = %.1f ms (addr[tsoft_end] - addr[tsoft_start])*SAMPLE_RATE)\n" ,  *tsoft*1e3);
		fprintf(fpr,"	fosc_s_min  = %.1f kHz (freq[tsoft_start])\n" , *fosc_s_min*1e-3);
		fprintf(fpr,"	fosc_s_max  = %.1f kHz (freq[tsoft_end])\n",    *fosc_s_max*1e-3 );
		fprintf(fpr,"  ILIM Jitter at 132kHz\n" );
		fprintf(fpr,"   FirstPeak_ILIM  = %.1f mA at addr %i\n",	FirstPeak_ILIM*1e3/Ilim_gain, (int) FirstPeak_addr);	
		fprintf(fpr,"   SecondPeak_ILIM = %.1f mA at addr %i\n",	SecondPeak_ILIM*1e3/Ilim_gain,(int) SecondPeak_addr);	
		fprintf(fpr,"   fModulation     = %.1f Hz (1/(abs(SecondPeak_addr-FirstPeak_addr)*SAMPLE_RATE)\n",*fModulation_P);
		fprintf(fpr,"   ilim_min  = %.1f mA \n",	*ilim_min*1e3/Ilim_gain);	
		fprintf(fpr,"   ilim_max  = %.1f mA \n",	*ilim_max*1e3/Ilim_gain);	

		fprintf(fpr,"\n" );
		fprintf(fpr,"\n" );

		//Start of pattern
		fprintf(fpr,"Start of pattern\n" );
		if (pulse_cnt<max_cnt) max_cnt = pulse_cnt;	//check number of actual samples
		for(i=0; i<max_cnt; i++)
		{
			if(gIdmax[i] > 0)
				fprintf(fpr,"ILIM_SSS, cnt= %i, %.1fmA, addr=%i, time= %.3fms, period= %.1fus, Freq = %.3fkHz\n", i, gIdmax[i]*1000/Ilim_gain, gIdmax_addr[i], gIdmax_addr[i]*20e-6,pulse_period[i]*1e6, freq[i]*1e-3);
		}
		fprintf(fpr,"\n" );

		//tsoft_end
		fprintf(fpr,"tsoft_end-50 peaks to ILIM_Jitter end+50 peaks\n" );
		strt_cnt=tsoft_end-50;	//check number of actual peaks
		max_cnt=SecondPeak_cnt+50;	//check number of actual peaks		
		if (pulse_cnt<max_cnt) 
		{
			strt_cnt = pulse_cnt-10;
			max_cnt = pulse_cnt;
		}
		fprintf(fpr,"tsoft_end   = peak %i\n",tsoft_end );
		for(i=strt_cnt; i<max_cnt; i++)
		{
			if(gIdmax[i] > 0)
				fprintf(fpr,"ILIM_SSS, cnt= %i, %.1fmA, addr=%i , time= %.3fms, period= %.1fus, Freq = %.3fkHz\n", i, gIdmax[i]*1000/Ilim_gain, gIdmax_addr[i], gIdmax_addr[i]*20e-6, pulse_period[i]*1e6, freq[i]*1e-3);
		}
		fprintf(fpr,"\n" );


		fprintf (fpr, "end;\n");
		fclose(fpr);

	}

	//Write Soft_start AC_offset debug file
	if(DEBUG==1)
	{
		int i=0;
		int max_cnt=400,strt_cnt;
		FILE * fpr2 = fopen("e:\\dl4\\Inn3xxx_ILIM_SSS_GND_datadump.txt", "w");
		if (! fpr2)
			return;
		fprintf(fpr2,"ILIM_SSS_GND, 20ns per sample (addr count)\n" );
		fprintf(fpr2,"  Ground offset values for baseline shift of each peak\n" );

		fprintf(fpr2,"\n" );
		fprintf(fpr2,"\n" );

		//tsoft_end
		fprintf(fpr2,"Offset for each peak from tsoft_end to ILIM_Jitter end\n" );
		strt_cnt=tsoft_end;	//check number of actual peaks
		max_cnt=SecondPeak_cnt;	//check number of actual peaks		
		if (pulse_cnt<=max_cnt) 
		{
			strt_cnt = pulse_cnt-10;
			max_cnt = pulse_cnt;
		}
		for(i=strt_cnt; i<=max_cnt; i++)
		{
			fprintf(fpr2,"ILIM_SSS_GND, cnt= %i, Offset=%.2fmA, offset addr=%i, offset time= %.3fms,\n", i, ACgnd_Ave[i]*1000/Ilim_gain, ACgnd_addr[i], ACgnd_addr[i]*20e-6);
		}
		fprintf(fpr2,"\n" );
		fprintf (fpr2, "end;\n");
		fclose(fpr2);

	}
}

void Gage_Find_Ilim_18kHz(float *ILIM_Jit18K_S, float *ILIMhi_Jit18K_S, float *ILIMLo_Jit18K_S, float *Fosc_Mod_18K_S)
{
	// Initialize //
	*ILIM_Jit18K_S   = 0;
	*ILIMhi_Jit18K_S = 0;
	*ILIMLo_Jit18K_S = 0;
	*Fosc_Mod_18K_S  = 0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*ILIM_Jit18K_S   = DEFAULT_VALUE;
		*ILIMhi_Jit18K_S = DEFAULT_VALUE;
		*ILIMLo_Jit18K_S = DEFAULT_VALUE;
		*Fosc_Mod_18K_S  = DEFAULT_VALUE;
		if(DEBUG==1 && gDEBUG)
			printf(" Gage_Find_Ilim_18kHz error: Gage data not OK\n");
		return;
	}

	// Declare Variables //
	int i = 0;
	int j = 0;
	float Idmax_rslt[500]	= {0};
	int	  Idmax_addr[500]	= {0};
	int	  ton_addr[500]		= {0};
	float di_dt[500]		= {0};
	int	  Num_ILIM_Peaks = 175; //255
	int	  PULSE_NUM_PROCESSED;

	SAMPLE_RATE_s = 20e-9;

	// Transfer data to PC (XP) //
	Gage_Transfer_Data (GAGE_CHAN_A); // XP //

	PULSE_NUM_PROCESSED = Gage_Find_Ipeak(Gage_chan_a_voltage, SAMPLE_SIZE, SAMPLE_RATE_s, Ilim_gain, Num_ILIM_Peaks, ton_addr, Idmax_addr, Idmax_rslt, di_dt);

	// Look for ILIM ramping up or down. //
	int RampUp = 0;
	int RampDown = 0;
	int MaxAddress1 = 0;
	int MaxAddress2 = 0;
	int MinAddress = 0;

	// Looking for ILIM_Max and ILIM_Min
	float ILIM_Max1 = -999.0;
	float ILIM_Max2 = -999.0;
	float ILIM_Min  = +999.0;

	for (j = 0; j < Num_ILIM_Peaks; j++)
	{
		if (Idmax_rslt[j] > ILIM_Max1)
		{
			ILIM_Max1 = Idmax_rslt[j];
			MaxAddress1 = j;
		}
		if (Idmax_rslt[j] < ILIM_Min)
		{
			ILIM_Min = Idmax_rslt[j];
			MinAddress = j;
		}
	}

	if (MaxAddress1 > Num_ILIM_Peaks/2)
	{
		RampUp = 0;
		RampDown = 1;
	}
	else
	{
		RampUp = 1;
		RampDown = 0;
	}

	if (RampUp)
	{
		// Now look for 2nd Peak
		for (i = MaxAddress1 + 10; i < MaxAddress1 + 30; i++)
		{
			if(Idmax_rslt[i] > ILIM_Max2)
			{
				ILIM_Max2 = Idmax_rslt[i];
				MaxAddress2 = i;
			}
		}
	}
	if (RampDown)
	{
		// Now look for 2nd Peak
		for (i = MaxAddress1 - 10; i > MaxAddress1 - 30; i--)
		{
			if(Idmax_rslt[i] > ILIM_Max2)
			{
				ILIM_Max2 = Idmax_rslt[i];
				MaxAddress2 = i;
			}
		}
	}

	if (RampUp)
		*Fosc_Mod_18K_S = 1 / ((Idmax_addr[MaxAddress2] - Idmax_addr[MaxAddress1]) * SAMPLE_RATE_s);
	else
		*Fosc_Mod_18K_S = 1 / ((Idmax_addr[MaxAddress1] - Idmax_addr[MaxAddress2]) * SAMPLE_RATE_s);

	*ILIMhi_Jit18K_S = Idmax_rslt[MaxAddress1];
	*ILIMLo_Jit18K_S = Idmax_rslt[MinAddress];
	*ILIM_Jit18K_S = (*ILIMLo_Jit18K_S / *ILIMhi_Jit18K_S) * 100;


	//DEBUG AWAV Files
	if(DEBUG==1 && gDEBUG)
	{
		char  wave_name_Id[150]		= "/0";
		char  debug_file_name[150]	= "/0";

		strcpy (wave_name_Id, WAVE_NAME);
		strcat (wave_name_Id, "_Id"); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}
}

void Gage_Find_Ilim_ramp(float *Ilim_lo_ave, float *Ilim_lo_med_ave, float *Ilim_up_med_ave)
{
	*Ilim_lo_ave =0.0;
	*Ilim_lo_med_ave =0.0;
	*Ilim_up_med_ave =0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Ilim_lo_ave =999.0;
		*Ilim_lo_med_ave =999.0;
		*Ilim_up_med_ave =999.0;
		return;
	}
	int	PULSE_LO_LoMED_NEED  =10;		// Define min pulses numbers need to be caputre
	int PULSE_UPMED_NEED	  = 5;
	int	PULSE_LO_LoMED_PROCESSED =0;	// Actual num pulses Processed. Exclude first pulse in ave calculation 
	int	PULSE_UPMED_PROCESSED	  =0;
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	int srch_group =0;
	enum {SRCH_LO_LoMED, SRCH_UPMED}; 

	// Variables for ILIM peak tests
	float Idmax[50] = {0.0};
	int	  Idmax_addr[50] = {0};
	float ACgnd[50]      ={0.0};
	float ACgnd_Ave[50]  ={0.0};
	int	  ACgnd_addr[50]   ={1000};				// GND is taken before device turns on

	int	  lcnt =0;

	float Period=0.0;
	int	  Sample_per_cycle=0;

	if (gFOSC_TARGET_S == 132e3)
	{
		if ( gFOSC_post_S > 110e3 && gFOSC_post_S < 150e3)
			Period = 1/gFOSC_post_S;
		else
			Period = 7.5e-6;
	}
	else
	{
		if ( gFOSC_post_S > 65e3 && gFOSC_post_S < 95e3)
			Period = 1/gFOSC_post_S;
		else
			Period = 12.5e-6;
	}


	Sample_per_cycle = Period/SAMPLE_RATE_s;


	char wave_name_Id[50] ="/0"; 
	char wave_name_Vd[50] ="/0"; 

	for (icnt=0; icnt<(PULSE_LO_LoMED_NEED + PULSE_UPMED_NEED); icnt++)
	{
		Idmax[icnt] = -100;
		Idmax_addr[icnt]  = 0;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);						//transfer data to Gage_chan_a_voltage array

	start_addr = 300;										// Skip 6us from negative trigger edge
	while (Gage_chan_a_voltage[start_addr]< 0.0 && start_addr < SAMPLE_SIZE)
		start_addr+=25;										// Fast forward by 0.5us/step

	// Error check
	if ((start_addr + 500) > SAMPLE_SIZE )					// 10us until the end of samples
	{														
		*Ilim_lo_ave =998.0;
		*Ilim_lo_med_ave =998.0;
		*Ilim_up_med_ave =998.0;
		return;
	}

	// First loop, look for ILIM_LO and ILIM_LO_MED. Second loop, look for ILIM_UP_MED
		srch_group = SRCH_LO_LoMED;
		while ((pulse_cnt< (PULSE_LO_LoMED_NEED+PULSE_UPMED_NEED) )&& (start_addr < SAMPLE_SIZE))
		{
			// Find Idmax
			// Limit search window to 5us to avoid algorithm error during ILIM levels transition. 
			// e.g. if the window is 10us. The last sample point in the window could be from the first ILIM_NORM pulse
			// which can be higher than the last peak of ILIM_UP_MED
//			for(icnt = start_addr; icnt< start_addr + 250 ; icnt++)
			for(icnt = start_addr; icnt< start_addr + 350 ; icnt++)	//ZCX 06/30/14  Search range increase to 7us
			{
				if(Gage_chan_a_voltage[icnt] > Idmax[pulse_cnt]) // Look at 5 us starting from the on pulse and find the peak. 
				{
					Idmax[pulse_cnt] = Gage_chan_a_voltage[icnt];
					Idmax_addr[pulse_cnt] = icnt;
				}
			}

			// Find AC Ground lvel
			ACgnd[pulse_cnt] = 1000;
			for(icnt = start_addr; (icnt> 0) && (Gage_chan_a_voltage[icnt]>0.0); icnt--)
			{
				 ACgnd[pulse_cnt] = Gage_chan_a_voltage[icnt-1];
				 ACgnd_addr[pulse_cnt] = icnt;
			}
			
			ACgnd_Ave[pulse_cnt] = (Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-20]+	// 20 samples away from First data point
									Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-21]+
									Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-22]+
									Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-23]+
									Gage_chan_a_voltage[ACgnd_addr[pulse_cnt]-24])/5.0;
		
			// Individual Peak result
			Idmax[pulse_cnt] -= ACgnd_Ave[pulse_cnt];
			Idmax[pulse_cnt] /= Ilim_gain;

			// Reset start address after find a peak.
			if (srch_group == SRCH_LO_LoMED)
				PULSE_LO_LoMED_PROCESSED ++;			// Search ILIM_LO and ILIM_LO_MED
			else
				PULSE_UPMED_PROCESSED ++;				// Search ILIM_UP_MED

			pulse_cnt ++;
			start_addr = Idmax_addr[pulse_cnt-1]+100;	// Move forward 2us

			// If ILIM_LO, ILIM_LO_MED processed pulses are enough, skip ahead to the ILIM_UP_MED pulses group
			// Refer to scope capture or gage capture to see the group of pulses
			if (PULSE_LO_LoMED_PROCESSED >=  PULSE_LO_LoMED_NEED && srch_group == 0)  
			{
				if (gFOSC_TARGET_S >= 130e3)	//ZCX 06/30/14
					start_addr = ILIM_UPMED_132kHz_SRCH_ADDR;
				else
					start_addr = ILIM_UPMED_100kHz_SRCH_ADDR;
				srch_group = SRCH_UPMED;
			}

			while (Gage_chan_a_voltage[start_addr]< 0.0 && start_addr < SAMPLE_SIZE)
				start_addr+=25;	

			// Fast forward by 0.5us/step
			if ((start_addr + 250) > SAMPLE_SIZE )		// 250 samples = 5us; 
				break;

	
		}


	// Average Peak result
	if(PULSE_LO_LoMED_PROCESSED >= PULSE_LO_LoMED_NEED)
	{
		// Taking average 3 peak values 

		//** ILIM_lo
		//for (pulse_cnt =1; pulse_cnt< 4; pulse_cnt++)
		//{
		//	*Ilim_lo_ave+=Idmax[pulse_cnt];
		//}
		//*Ilim_lo_ave /=3;
		*Ilim_lo_ave+=Idmax[2];
		//** ILIM_lo_med Start from captured pulse number # to ensure we are in the lo_med pulses group
		//for (pulse_cnt =7; pulse_cnt< 10; pulse_cnt++)
		//{
		//	*Ilim_lo_med_ave+=Idmax[pulse_cnt];
		//}
		//*Ilim_lo_med_ave  /=3;
		*Ilim_lo_med_ave+=Idmax[8];
		//** ILIM_Up_med Start from captured pulse number # to ensure we are in the lo_med pulses group
		//for (pulse_cnt =11; pulse_cnt< 14; pulse_cnt++)
		//{
		//	*Ilim_up_med_ave+=Idmax[pulse_cnt];
		//}
		//*Ilim_up_med_ave  /=3;
		*Ilim_up_med_ave+=Idmax[12];

	}
	else
	{	
		if(DEBUG==1 && gDEBUG)
			MessageBox(NULL, "Error: PULSE_NUM_PROCESSED is less than PULSE_NUM_NEED",Func_name, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}


	if(DEBUG==1 && gDEBUG)
	{
		strcpy (wave_name_Id, WAVE_NAME);
		strcat (wave_name_Id, "_Id"); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);
		WAVE_NAME = "NoWaveName";
	}
}

int Gage_Find_Ipeak(float const *v_data, int const arr_size, float const samp_rate, float const scale, int const max_pulse, int *ton_addr, int *ipeak_addr, float *ipeak, float *di_dt)
{
/* Function:	Process a voltage array from GaGe into array of Ipeak
 *				Will process minimum pulse width 700ns (at 20ns/sample) with turn-on spike/ring less than 500ns
 *
 * Input:
 * v_data		- voltage array from GaGe
 * arr_size		- size of v_data
 * samp_rate	- sample rate of v_data, in second
 * scale		- multiplier to convert v to i. scale = v/i
 * max_pulse	- maximum pulses to process for output arrays
 *
 * Output:
 * Output arrays size must be at least max_pulse
 * ton_addr		- store Ton address in v_data for each pulse
 * ipeak_addr	- store Ipeak address in v_data for each pulse
 * ipeak		- store Ipeak(A) for each pulse
 * di_dt		- store di_dt(A/us) for each pulse
 *
 * Returns number of pulse_processed
 *
 *                            ipeak_addr[1]
 *           ipeak_addr[0]     ipeak[1]
 *              ipeak[0]       di_dt[1]
 *              di_dt[0]       /|
 *              /|            / |
 *   0V  ....../.|.........../..|........ . . .
 *  gnd  _____/  |__________/   |________ _ _ _
 *           ^             ^
 *         ton_addr[0]   ton_addr[1]
 */

	int   cnt_array;					// loop counter for v_data
	int   h_step		= 20;			// sample step size for derivative calculation. 400ns/sample_rate=400ns/20ns
	float *dv_dt		= NULL;			// derivative of v_data
	float *gnd			= NULL;			// ground offset of v_data due to current transformer
	int   *gnd_addr		= NULL;			// ground offset address of v_data
	float dvdt_thres	= 0.7e-3;		// threshold for detecting Ton and Toff. di/di*sample_rate*scale_factor. 70mA/us*20ns*0.5
	int   ton_blanking	= 25;			// skip the turn-on spikes and noise. 500ns/sample_rate=500ns/20ns
	int   ton_valid		= 10;			// minumum valid turn-on after blanking. 200ns/sample_rate=200ns/20ns
	int   toff_blanking	= 100;			// skip the turn-off spikes and noise. 2us/sample_rate=2us/20ns
	int   gnd_samp_size	= 15;			// average of gnd offset. 300ns/sample_rate=300ns/20ns
	int   i, j;
	float data_value;
	float data_average;
	float data_range;
	float data_min;
	float data_max;
	float max_delta;
	bool  flat_found	= false;		// flag when gnd offset is found
	bool  ton_found		= false;		// flag for Ton search
	bool  toff_found	= false;		// flag for Toff search

	int pulse_processed = 0;

	// Clear output array
	for (i = 0; i < max_pulse; i++)
	{
		ton_addr[i] = 0;
		ipeak_addr[i] = 0;
		ipeak[i] = DEFAULT_VALUE;
		di_dt[i] = DEFAULT_VALUE;
	}

	// resize internal arrays dynamically and initialise to 0
	dv_dt = (float *)calloc(arr_size + 1, sizeof(*dv_dt));
	if (dv_dt == NULL)
	{
		printf("Memory allocation error\n");
		return DEFAULT_VALUE;
	}

	gnd = (float *)calloc(max_pulse + 1, sizeof(*gnd));
	if (gnd == NULL)
	{
		printf("Memory allocation error\n");
		return DEFAULT_VALUE;
	}

	gnd_addr = (int *)calloc(max_pulse + 1, sizeof(*gnd_addr));
	if (gnd_addr == NULL)
	{
		printf("Memory allocation error\n");
		return DEFAULT_VALUE;
	}

	// Calculate dv/dt of v_data using backward difference
	cnt_array = h_step;
	while (cnt_array < arr_size)
	{
		dv_dt[++cnt_array] = (v_data[cnt_array] - v_data[cnt_array -  h_step]) / h_step;
	}

	// Skip the partial pulse at the beginning
	cnt_array = 2 * ton_blanking;
	while (dv_dt[cnt_array++] > dvdt_thres);

	while (cnt_array < arr_size)
	{
		if (ton_found == false)
		{
			// Search for turn on
			while (dv_dt[cnt_array++] < dvdt_thres && cnt_array < arr_size);

			// Check turn on is real
			for (i = (cnt_array + ton_blanking); i < (cnt_array + ton_blanking + ton_valid) && cnt_array < arr_size; i++)
			{
				if (dv_dt[i] > dvdt_thres && v_data[i] > 0)
				{
					ton_found = true;
				}
				else
				{
					ton_found = false;
					break;
				}
			}
		}
		else
		{
			ton_addr[pulse_processed] = cnt_array - 1;

			// Search gnd offset
			// The current probe coupling will cause the current to tend to 
			// drift negative. The "zero" value must be found in order to get an 
			// accurate reading.
			// To find the voffset value, look at the flat just before the start of the ramp.  
			flat_found = false;
			max_delta = 0.02;			// maximum delta when determining gnd offset is flat enough. 20mV
			for (i = cnt_array - 1; i > (cnt_array - 2 * gnd_samp_size) && i > gnd_samp_size; i--)
			{
				data_min = 9999.0;
				data_max = -9999.0;
				data_average = 0.0;
				for (j = 0; j < gnd_samp_size; j++)
				{
					data_value = v_data[i - j];
					data_average += data_value;
					if (data_value < data_min)
						data_min = data_value;
					if (data_value > data_max)
						data_max = data_value;
				}
				data_range = data_max - data_min;
				if (data_range < 0) data_range *= -1;	// Take absolute value
				if (data_range < max_delta)
				{
					flat_found = true;
					gnd[pulse_processed] = data_average / gnd_samp_size;
					gnd_addr[pulse_processed] = i;
					break;
				}
			}

			// Search Ipeak
			if (flat_found)
			{
				cnt_array += ton_blanking;

				// Search for Ipeak (turn off)
				ipeak[pulse_processed] = DEFAULT_VALUE;		// -999.0
				while (dv_dt[cnt_array++] > dvdt_thres && cnt_array < arr_size)
				{
					if (ipeak[pulse_processed] < v_data[cnt_array])
					{
						ipeak[pulse_processed] = v_data[cnt_array];
						ipeak_addr[pulse_processed] = cnt_array;
					}
				}
				// Apply offset and scale factor
				ipeak[pulse_processed] -= gnd[pulse_processed];
				ipeak[pulse_processed] /= scale;

				// Calculate di/dt
				max_delta = 2.0e-3;			// maximum delta when determining dv_dt is flat, i.e. inductor not saturating.
				data_range = max_delta + 1;
				for (i = 0; ((i < 5) && (data_range > max_delta)); i++)
				{
					data_min = 9999.0;
					data_max = -9999.0;
					data_average = 0.0;
					for (j = 0; j < h_step; j++)
					{
						data_value = dv_dt[ipeak_addr[pulse_processed] - i - j];
						data_average += data_value;
						if (data_value < data_min)
							data_min = data_value;
						if (data_value > data_max)
							data_max = data_value;
					}
					data_range = data_max - data_min;
					if (data_range < 0) data_range *= -1;	// Take absolute value
				}

				if (data_range < max_delta)
				{
					di_dt[pulse_processed] = data_average / h_step;
					di_dt[pulse_processed] = (di_dt[pulse_processed] / samp_rate * 1e-6) / scale;
				}
				else
				{
					di_dt[pulse_processed] = DEFAULT_VALUE;
					//printf("didt range too big. possible inductor saturation.\n");
				}
			}

			if (flat_found == true && ipeak[pulse_processed] >= 100e-3 && di_dt[pulse_processed] > dvdt_thres)
			{
				pulse_processed++;
				cnt_array += toff_blanking;
			}
			else
			{
				gnd[pulse_processed] = 0.0;
				gnd_addr[pulse_processed] = 0;
				ton_addr[pulse_processed] = 0;
				ipeak[pulse_processed] = DEFAULT_VALUE;
				ipeak_addr[pulse_processed] = 0;
				cnt_array++;
			}
			ton_found = false;
		}
		if (pulse_processed >= max_pulse) break;
	}

	free(dv_dt);
	free(gnd);
	free(gnd_addr);

	dv_dt = NULL;
	gnd = NULL;
	gnd_addr = NULL;

	return pulse_processed;
}

void Gage_Find_SOA(float *SOA, float *TW_50)
{
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	int i = 0;
	double v_delt_st=0.0,v_delt_on=0.0,v_delt_off=0.0;


	float On_addr[200] ={0}, Off_addr[200] ={0};
	float ILIM_On_addr[200] ={0}, ILIM_Off_addr[200] ={0};
	float On_Time[200] ={0}, Off_Time[200] ={0};

	float SOA_On_addr[200] ={0}, SOA_Off_addr[200] ={0}, SOA_On_Time[200] ={0}, SOA_Cycle_Time[200] ={0};
	int	  SOA_cnt=0;

	char wave_name_Id[50] ="/0"; 

	*SOA =0.0;
	*TW_50 =0.0;

	//Initialize all variables
	i			=0;
	start_addr	=0;
	pulse_cnt	=0;
	icnt		=0; 

	for (i=0; i<GAGE_WAVEFORM_BUFFER_SIZE; i++)
		Gage_chan_a_voltage[i] = 0;	// Initialize array before data transfer

	for (i=0; i<200; i++)
	{
		On_addr[i]			=0; 
		Off_addr[i]			=0;
		ILIM_On_addr[i]		=0; 
		ILIM_Off_addr[i]	=0;
		On_Time[i]			=0; 
		Off_Time[i]			=0;

		SOA_On_addr[i]		=0; 
		SOA_Off_addr[i]		=0;
		SOA_On_Time[i]		=0; 
		SOA_Cycle_Time[i]	=0;
	}
	
	//set v_delt values for different sizes
	v_delt_st	=	100e-3;
	v_delt_on	=	 50e-3;
	v_delt_off	=	-50e-3;
	if (MOSFET_SIZE <= 5) 
	{
		v_delt_st	=	20e-3;	//smaller sizes don't have 100mV between samples, PMiller
		v_delt_on	=	20e-3;
		v_delt_off	=	-20e-3;

		if(g_TurretCB)
		{
			v_delt_st	=	50e-3;	//Turret Cb has more noise ==> Require larger threshold.
			v_delt_on	=	50e-3;
			v_delt_off	=	-50e-3;
		}
	}

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*SOA  = 999.0;
		*TW_50 =999.0;
		if(DEBUG && gDEBUG)
			printf("  Gage_Find_SOA %s : Bad acquisition \n", WAVE_NAME);
		return;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array

	// During SOA. Device skips pulses. Period ~=25us
	start_addr = 1;	
	//SAMPLE_SIZE = 32000; // JD test time reduction, shaves 80ms
	
	//find start address where voltage starts increasing
	while ( (Gage_chan_a_voltage[start_addr] - Gage_chan_a_voltage[start_addr-1]) < v_delt_st && 
			 start_addr < SAMPLE_SIZE)	
		start_addr+=1;					

	start_addr -= 1;

	// Error check
	if ((start_addr + 1500) > SAMPLE_SIZE ) 	// 30us to cover two pulses.
	{
		*SOA  = 999.0;
		*TW_50 =999.0;
		if(DEBUG && gDEBUG)
			printf("  Gage_Find_SOA: start_addr error (%s) \n", WAVE_NAME);
		return;
	}

	while (start_addr < SAMPLE_SIZE && pulse_cnt<200 )	//Process all captured data
	{
		// Find ON address right before device turns on
		while (  Gage_chan_a_voltage[start_addr] < 150e-3 &&
				(Gage_chan_a_voltage[start_addr] - Gage_chan_a_voltage[start_addr-1]) < v_delt_on )	
		{
			 On_addr[pulse_cnt]			= start_addr;
			 ILIM_On_addr[pulse_cnt]	= Gage_chan_a_voltage[start_addr];
			 start_addr +=1;
		}

		// Find OFF address
		while ( (Gage_chan_a_voltage[start_addr] - Gage_chan_a_voltage[start_addr-1]) > v_delt_off && start_addr < SAMPLE_SIZE)	
		{
			 Off_addr[pulse_cnt]		= start_addr;
			 ILIM_Off_addr[pulse_cnt]	= Gage_chan_a_voltage[start_addr];
			 start_addr +=1;
		}

		On_Time[pulse_cnt] = (Off_addr[pulse_cnt] - On_addr[pulse_cnt])*SAMPLE_RATE_s;

		//Store pulses with On_Time less than 1us
		if(On_Time[pulse_cnt] < 1e-6 && On_Time[pulse_cnt] > 1e-9)
		{
			SOA_On_addr[SOA_cnt] = On_addr[pulse_cnt];
			SOA_Off_addr[SOA_cnt] = Off_addr[pulse_cnt];
			SOA_On_Time[SOA_cnt] = On_Time[pulse_cnt];
			//Store cycle time
			if(SOA_cnt > 0)
			{
				SOA_Cycle_Time[SOA_cnt] = (SOA_Off_addr[SOA_cnt] - SOA_Off_addr[SOA_cnt-1])*SAMPLE_RATE_s;
				//Store SOA_P
				if(SOA_Cycle_Time[SOA_cnt] > (10e-6))	
				{
					*SOA = SOA_Cycle_Time[SOA_cnt];
					*TW_50 = SOA_On_Time[SOA_cnt];	//The 1st Pulse should be the real TW50
					//Break out of function after the second SOA pulse found
					if(SOA_cnt > 2)
						break; //Found SOA and TW50...  DONE	cx 11/10/16
				}
			}
			SOA_cnt++;
		}

		pulse_cnt++;
		start_addr += 100;	//fast forward by 2us after finding Off_addr
	}

	//debug
	if(DEBUG==1 && gDEBUG)
	{
		printf("  Gage_Find_SOA:%s\n",WAVE_NAME);
		for (i=0;(i<= pulse_cnt) && (i<10) ; i++)
			printf("  Gage_Find_SOA: On_Time=%.3f us, On_addr=%.0f,  Off_addr=%.0f  \n",On_Time[i]*1e6,On_addr[i],Off_addr[i]);
		for (i=0;(i<= SOA_cnt) && (i<10) ; i++)
		{
			printf("  Gage_Find_SOA: SOA_Cycle_Time=%.3f us,TW_50=%.1fns, SOA_On_addr=%.0f,  SOA_Off_addr=%.0f  \n",SOA_Cycle_Time[i]*1e6,SOA_On_Time[i]*1e9,SOA_On_addr[i],SOA_Off_addr[i]);
		}
	}
	
	//awav
	if(DEBUG==1 && gDEBUG)
	{
		strcpy (wave_name_Id, WAVE_NAME); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);
	}

}

void Gage_Find_SDS(float *SDS, float *SDS_TW_50, float *SDS_P_nsw)
{
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	int PULSES_NEEDED = 2;
	start_addr=0;
	pulse_cnt =0;
	icnt =0; 
	PULSES_NEEDED = 2;

	float On_addr[200] ={0}, Off_addr[200] ={0};
	float ILIM_On_addr[200] ={0}, ILIM_Off_addr[200] ={0};
	float On_Time[200] ={0}, Off_Time[200] ={0};

	float SDS_On_addr[200] ={0}, SDS_Off_addr[200] ={0}, SDS_On_Time[200] ={0}, SDS_Cycle_Time[200] ={0};
	int	  SDS_cnt=0;
	double v_delt_st=0.0,v_delt_on=0.0,v_delt_off=0.0;

	char wave_name_Id[50] ="/0"; 

	*SDS =0.0;
	*SDS_TW_50 =0.0;
	
	//set v_delt values for different sizes
	v_delt_st	=	  50e-3;
	v_delt_on	=	 100e-3;
	v_delt_off	=	 100e-3;
	if (MOSFET_SIZE == 2) 
	{
		v_delt_st	=	 20e-3;	//size 2 doesn't have 100mV between samples, PMiller
		v_delt_on	=	 20e-3;
		v_delt_off	=	100e-3;
	}

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*SDS  = 999.0;
		*SDS_TW_50 =999.0;
		*SDS_P_nsw = 99.0;
		if(DEBUG==1)
			printf("Gage_Find_SDS: Bad acquisition\n", SERIAL_NUM);
		return;
	}

	int i = 0;
	for (i=0; i<GAGE_WAVEFORM_BUFFER_SIZE; i++)
		Gage_chan_a_voltage[i] = 0;	// Initialize array before data transfer

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array
	if(DEBUG==1 && gDEBUG)
	{
		strcpy (wave_name_Id, WAVE_NAME); 
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);
	}

	// During SOA. Device skips pulses. Period ~=25us
	start_addr = 1;	
	//SAMPLE_SIZE = 33000; // soft start devices need 32k

	while ( (Gage_chan_a_voltage[start_addr] - Gage_chan_a_voltage[start_addr-1]) < v_delt_st  && 
			 start_addr < SAMPLE_SIZE)	
		start_addr+=1;					

	start_addr -= 1;

	// Error check
	if ((start_addr + 1500) > SAMPLE_SIZE ) 	// 30us to cover two pulses.
	{
		*SDS  = 999.0;
		*SDS_TW_50 =999.0;
		return;
	}

	while (start_addr < SAMPLE_SIZE && pulse_cnt<100)	//Process all captured data
	{
		// Find ON address right before device turns on
		while (  Gage_chan_a_voltage[start_addr] < 250e-3 &&
				(Gage_chan_a_voltage[start_addr] - Gage_chan_a_voltage[start_addr-1]) < v_delt_on  && 
				 start_addr < SAMPLE_SIZE)	
		{
			 On_addr[pulse_cnt]			= start_addr;
			 ILIM_On_addr[pulse_cnt]	= Gage_chan_a_voltage[start_addr];
			 start_addr +=1;
		}

		// Find OFF address
		while ( (Gage_chan_a_voltage[start_addr] - Gage_chan_a_voltage[start_addr+1]) < -100e-6 && start_addr < SAMPLE_SIZE)	
		{
			 Off_addr[pulse_cnt]		= start_addr;
			 ILIM_Off_addr[pulse_cnt]	= Gage_chan_a_voltage[start_addr];
			 start_addr +=1;
		}

		On_Time[pulse_cnt] = (Off_addr[pulse_cnt] - On_addr[pulse_cnt])*SAMPLE_RATE_s;

		//Store pulses with On_Time less than 1us
		if(On_Time[pulse_cnt] < 1e-6 && On_Time[pulse_cnt] > 0 && On_Time[pulse_cnt] > 1e-9)
		{
			SDS_On_addr[SDS_cnt] = On_addr[pulse_cnt];
			SDS_Off_addr[SDS_cnt] = Off_addr[pulse_cnt];
			SDS_On_Time[SDS_cnt] = On_Time[pulse_cnt];
			//Store cycle time
			if(SDS_cnt > 0)
			{
				SDS_Cycle_Time[SDS_cnt] = (SDS_Off_addr[SDS_cnt] - SDS_Off_addr[SDS_cnt-1])*SAMPLE_RATE_s;
				////Store SDS_P
				//if(SDS_Cycle_Time[SDS_cnt] > (2 * 1/gFOSC_TARGET_P))
				//{
					*SDS = SDS_Cycle_Time[SDS_cnt];
					*SDS_TW_50 = SDS_On_Time[SDS_cnt-1];	//The 1st Pulse should be the real TW50
				//}
			}
			SDS_cnt++;
		}

		pulse_cnt++;
		start_addr += 100;	//fast forward by 2us after finding Off_addr
	}
// Functional Check to make sure device is in ARST off after 2 SDS pulses.
	if (start_addr==(SAMPLE_SIZE+100) && (pulse_cnt-1)==2)
		*SDS_P_nsw = 0; // Passing
	else
		*SDS_P_nsw = 99; // Failing

	//debug
	if(DEBUG==1 && gDEBUG)
	{
		printf("  Gage_Find_SDS:%s\n",WAVE_NAME);
		for (i=0;(i<= pulse_cnt) && (i<10) ; i++)
			printf("  Gage_Find_SDS: On_Time=%.3f us, On_addr=%.0f,  Off_addr=%.0f  \n",On_Time[i]*1e6,On_addr[i],Off_addr[i]);
		for (i=0;(i<= SDS_cnt) && (i<10) ; i++)
		{
			printf("  Gage_Find_SDS: SDS_Cycle_Time=%.3f us,TW_50=%.1fns, SDS_On_addr=%.0f,  SDS_Off_addr=%.0f  \n",SDS_Cycle_Time[i]*1e9,SDS_On_Time[i]*1e6,SDS_On_addr[i],SDS_Off_addr[i]);
		}
	}
	
	////if(DEBUG==1)
	////{
	////	strcpy (wave_name_Id, WAVE_NAME); 
	////	Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);
	////}

}


void Gage_Count_Cycles(float *Cycle_Count)
{
	int	PULSE_NUM_NEED  =110;	// Define min # of pulses need to be caputred
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 

	float On_addr[200] ={0}, Off_addr[200] ={0};
	float curr_lev[200]={0}, next_lev[200]={0};
	float comp_lev=0.0;
	float vdelta  =0.0;
	char wave_name_Id[200] ="/0"; 

	//wave_name_Id = "RxTx_cnt";

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Cycle_Count  = 999.0;
		return;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_A);	//transfer data to Gage_chan_a_voltage array

//	start_addr = 100;					// Skip 2us from negative trigger edge
	start_addr = 0;					
//	while (Gage_chan_a_voltage[start_addr]< 0.00 && start_addr < SAMPLE_SIZE)	//Expect true start to be greater than 2mV
	while (Gage_chan_a_voltage[start_addr]< 0.010 && start_addr < SAMPLE_SIZE)	//Expect true start to be greater than 2mV
	//while (Gage_chan_a_voltage[start_addr]< 0.015 && start_addr < SAMPLE_SIZE)	//Expect true start to be greater than 2mV
		start_addr++;					// Fast forward by 0.1us/step
//		start_addr+=5;					// Fast forward by 0.1us/step
//		start_addr+=10;					// Fast forward by 0.2us/step

	// Error check
	if ((start_addr + 1000) > SAMPLE_SIZE ) 	
	{
		*Cycle_Count  = 0;
		return;
	}

	while ((pulse_cnt< PULSE_NUM_NEED)&& (start_addr < SAMPLE_SIZE))
	{
		// Find On address right before device turns on
		start_addr += 10;
		//for(icnt = start_addr; (icnt> 0) && (Gage_chan_a_voltage[icnt]>0.0015); icnt--)
		for(icnt = start_addr; (icnt> 0) && (Gage_chan_a_voltage[icnt]>0.02); icnt--)
		{
			 On_addr[pulse_cnt] = icnt;
		}
		
		// Find Current turn off point
		//start_addr += 5;				// Fast forward by 0.1us/step
		curr_lev[pulse_cnt] = Gage_chan_a_voltage[start_addr];
		next_lev[pulse_cnt] = Gage_chan_a_voltage[start_addr+1];
		//vdelta= (next_lev[pulse_cnt] - curr_lev[pulse_cnt])/Ilim_gain;
		vdelta= fabs(next_lev[pulse_cnt] - curr_lev[pulse_cnt]);
		//comp_lev = -1*gILIM_TARGET_S*0.03;	//Found Off edge when next level is much less than current level
		if (gILIM_TARGET_S < 1.2)
			comp_lev = 10e-3;	//Found Off edge when next level is much less than current level
		else
			comp_lev = 20e-3;	//Found Off edge when next level is much less than current level

//		for(icnt = start_addr;icnt< (SAMPLE_SIZE-1) && (vdelta >comp_lev); icnt++)
		for(icnt = start_addr;icnt< (SAMPLE_SIZE-1) && (vdelta <comp_lev); icnt++)
		{
			 curr_lev[pulse_cnt] = Gage_chan_a_voltage[icnt];
			 next_lev[pulse_cnt] = Gage_chan_a_voltage[icnt+1];
			 //vdelta = (next_lev[pulse_cnt] - curr_lev[pulse_cnt])/Ilim_gain;
			 vdelta = fabs(next_lev[pulse_cnt] - curr_lev[pulse_cnt]);
			 Off_addr[pulse_cnt] = icnt+1;
		}
	
		// Reset start address after find a peak.
		if( (Off_addr[pulse_cnt] - On_addr[pulse_cnt]) > 10 && Off_addr[pulse_cnt] != 0) //On duty cycle > 0.2us
		{
			PULSE_NUM_PROCESSED ++;
			pulse_cnt ++;
			if(pulse_cnt==1)
				start_addr = Off_addr[pulse_cnt-1]+450;		// Move forward 10us for the first pulse since first pulse, TON is only ~1us.
			else
				start_addr = Off_addr[pulse_cnt-1]+400;		// Move forward 8us
		}
		else
		{
			start_addr = SAMPLE_SIZE+1;		// exit while loop
			//////Overwrite ON/OFF address of long pulses that's greater than 2x the expected ON-time ( < 300ns )
			////On_addr[pulse_cnt] = 0;
			////Off_addr[pulse_cnt] = 0;
		}

//		start_addr = Off_addr[pulse_cnt-1]+100;		// Move forward 2us
		while (Gage_chan_a_voltage[start_addr]< 0.001 && start_addr < SAMPLE_SIZE)
			start_addr+=5;							// Fast forward by 0.1us/step since it only take ~10 samples for TW50
//			start_addr+=10;							// Fast forward by 0.2us/step

//		if ((start_addr + 1500) > SAMPLE_SIZE ) 	// 500 samples = 10us; 
		if ((start_addr + 50) > SAMPLE_SIZE ) 		
			break;
		
	}

	*Cycle_Count = pulse_cnt;

	if(DEBUG==1 && gDEBUG)
	{
		//Create_Awav
		strcpy (wave_name_Id, WAVE_NAME);
		Create_Awav_xp(wave_name_Id, Gage_chan_a_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		//Write Dumparray file
		char file_name_Id[200] ="e:\\dl4\\Inn3xxx_"; 
		strcat (file_name_Id, WAVE_NAME);
		strcat (file_name_Id, "_datadump.txt");

		FILE * fpr = fopen(file_name_Id, "w");
		if (fpr)
		{
			fprintf(fpr,file_name_Id );
			fprintf(fpr,"\n" );
			fprintf(fpr,"Cycle_Count= %i\n" , *Cycle_Count);
			fprintf(fpr,"\n" );
			for (int i=0; i< *Cycle_Count; i++)
			{
				fprintf(fpr,"Cycle# %i off_addr= %.0f" , i+1, Off_addr[i]);
				if (i>0)	
					fprintf(fpr,", distance= %.0f\n" ,Off_addr[i]- Off_addr[i-1]);
				else 
					fprintf(fpr,"\n" );
			}
			fprintf (fpr, "end;\n");
			fclose(fpr);
		}
	}

}

void Gage_Count_Cycles_CHB(float *Cycle_Count)
{
	int	PULSE_NUM_NEED  =110;	// Define min # of pulses need to be caputred
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0; 
	int on_cnt=0;
	long int i = 0;

	float On_addr[200] ={0}, Off_addr[200] ={0};
	float curr_lev[200]={0}, next_lev[200]={0};
	float comp_lev=0.0;
	float Vdata =0.0;
	char wave_name_Id[200] ="/0"; 

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*Cycle_Count  = 999.0;
		return;
	}
	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array

	// Save captured data as .awav file. //
	//if(WAVE_NAME == "ILIM_P1")

	start_addr = 100;		
	pulse_cnt = 0;
	for ( icnt = start_addr; icnt < (SAMPLE_SIZE-20);  icnt++ )
	{
		// Look for drain turn off. //
		Vdata = Gage_chan_b_voltage[icnt];
		if (Vdata > 1.0) // Found drain turn off. //
		{
			pulse_cnt++;
			on_cnt=icnt;
			//Jump ahead 5 usec to look for drain turn-on. //
			icnt = icnt + 250;
			while (Vdata > 1.0)
			{
				if (icnt >(SAMPLE_SIZE-20))
					break;
				icnt++;
				Vdata = Gage_chan_b_voltage[icnt];
			}

			// Drain turn-on found //
			// Jump ahead 100nsec to be sure past turn on edge. //
			icnt = icnt + 5;
			if (DEBUG && gDEBUG)
			{
				//printf("   Gage_Count_Cycles_CHB: pulse_cnt=%i, on_addr=%i, off_addr=%i\n",pulse_cnt-1,on_cnt,icnt);
				Off_addr[pulse_cnt-1] =icnt;
			}
		}
		if (icnt >(SAMPLE_SIZE-20))
			break;
	}
	*Cycle_Count = pulse_cnt;


	if (DEBUG && gDEBUG)
//	if (DEBUG)
	{
		char file_name_Id[200] ="e:\\dl4\\Inn3xxx_"; 
		char file_awav[200];
		char file_txt[200];
		strcat (file_name_Id, WAVE_NAME);
		strcpy (file_awav, file_name_Id);
		strcpy (file_txt, file_name_Id);

		//Write Dumparray file
		strcat (file_awav, "_awav.awav");
			double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
			for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
			{	
				capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
			}
			CreateAwav(	capture_data_B, // Data array //
							GAGE_WAVEFORM_BUFFER_SIZE-10, // Size of array //
							20.0e-9, // Sampling period //				 
							file_awav); // Output file and path //
			free (capture_data_B);
	
		//Write Datadump file
		strcat (file_txt, "_datadump.txt");

		FILE * fpr = fopen(file_txt, "w");
		if (fpr)
		{
			fprintf(fpr,file_name_Id );
			fprintf(fpr,"\n" );
			fprintf(fpr,"Cycle_Count= %i\n" , *Cycle_Count);
			fprintf(fpr,"\n" );
			for (int i=0; i< *Cycle_Count; i++)
			{
				fprintf(fpr,"Cycle# %i off_addr= %.0f" , i+1, Off_addr[i]);
				if (i>0)	
					fprintf(fpr,", distance= %.0f\n" ,Off_addr[i]- Off_addr[i-1]);
				else 
					fprintf(fpr,"\n" );
			}
			fprintf (fpr, "end;\n");
			fclose(fpr);
		}
	}

}

void Gage_Find_DChUp(float *DChUp_Result)
{
	int start_addr=0;
	int stop_addr=0;
	int icnt =0; 
	int j_cnt = 0;
	long int i = 0;
	float DataValue =0.0;
	float DataValueMax = 0;
	float DataValueMin = 0;
	float DataRange = 0;
	float VmaxAddress = 0;
	int QtyPoints = 20;
	int FoundRampStart = 0;
	int RampStartAddr = 0;
	float MaxDelta = .024;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*DChUp_Result  = 999.0;
		return;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array

	// Save captured data as .awav file. //
	if (DEBUG==1 && gDEBUG)
	{
			double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
			for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
			{	
				capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
			}
			CreateAwav(	capture_data_B, // Data array //
							GAGE_WAVEFORM_BUFFER_SIZE-10, // Size of array //
							20.0e-9, // Sampling period //				 
							"e:\\dl4\\DChUp.awav"); // Output file and path //
			free (capture_data_B);
	}

	// Look for max value. //
	start_addr = 1750;		
	stop_addr = 4250;
	DataValueMax = -9999;
	for ( icnt = start_addr; icnt < stop_addr;  icnt++ )
	{
		DataValue = Gage_chan_b_voltage[icnt];
		if (DataValue > DataValueMax)
		{
			DataValueMax = 	DataValue;
			VmaxAddress = icnt;
		}
	}

	// Look for ramp start. //
	icnt = VmaxAddress;
	FoundRampStart = 0;
	while (icnt > (VmaxAddress-1250) && FoundRampStart < 1)
	{
		DataValueMin = 9999;
		DataValueMax = -9999;
		for (j_cnt = 0; j_cnt < QtyPoints; j_cnt++)
		{
			DataValue = Gage_chan_b_voltage[icnt-j_cnt];
			if (DataValue < DataValueMin)
				DataValueMin = 	DataValue;
			if (DataValue > DataValueMax)
				DataValueMax = 	DataValue;
		}
		DataRange = DataValueMax - DataValueMin;
		if(DataRange < 0)
			DataRange *= -1; // Take absolute value. //
		if (DataRange < MaxDelta)
		{
			FoundRampStart = 1;
			RampStartAddr = icnt;
		}
		icnt--;
	}
	*DChUp_Result = (VmaxAddress - RampStartAddr)*20e-9;
	*DChUp_Result += 80e-9;  // Always measures about 80nsec too small. //
}

void Gage_Find_tOVL(float *tOVL)
{
	
	int start_addr=0;
	int stop_addr=0;
	int start_trig_addr=0;
	int stop_trig_addr=0;
	int icnt =0; 
	int loop_cnt = 0, valid_cnt = 0;
	int j_cnt = 0;
	long int i = 0;
	float tOVL_Avg[10];
	float tOVL_Sum = 0.0, tOVL_Sum2 = 0.0;
	float Start_Value = 0;
	float Stop_Value = 0;
	//float Start_Trig = 4.7;
	//float Stop_Trig = 4.2;
	float Start_Trig = 4.60; //4.7 is for Turret Rev A
	float Stop_Trig = 4.15; //4.2 is for Turret Rev A

	loop_cnt= 0;
	
	while(loop_cnt < 10)
	{
		tOVL_Avg[loop_cnt] = 0.0;
		loop_cnt++;
	}

	if(LB_Rev>=5 )
	{
		Start_Trig = 4.60;
		Stop_Trig  = 4.15;
	}

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*tOVL  = 999.0;
		return;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array

	// Save captured data as .awav file. //
	//DEBUG=1;
	if (DEBUG==1)
	{
			double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
			for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
			{	
				capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
			}
			CreateAwav(	capture_data_B, // Data array //
							GAGE_WAVEFORM_BUFFER_SIZE-10, // Size of array //
							20.0e-9, // Sampling period //				 
							"e:\\dl4\\tOVL.awav"); // Output file and path //
			free (capture_data_B);
	}

	loop_cnt= 0;
	while(loop_cnt < 10)
	{
		// Look for start trigger point //
		if(loop_cnt == 0)
		{
			start_addr = 10;		
		}
		else
		{
			start_addr = start_addr + 2000;		
		}
		//for ( icnt = start_addr; icnt < SAMPLE_SIZE - 100;  icnt++ )
		for ( icnt = start_addr; icnt < start_addr + 2500 ;  icnt++ )
		{
			if (fabs(Gage_chan_b_voltage[icnt] - Gage_chan_b_voltage[icnt+6])>0.040)//used to be 50mV
			{
				Start_Value = Gage_chan_b_voltage[icnt];
				start_trig_addr = icnt;
				break;
			}
		}
		// Look for stop trigger point //
		if(g_TurretCB)
		{
			start_addr = start_trig_addr + 300;		//HL- fast forward 6us due to slight higher stop threshold		
		}
		else
		{
			start_addr = start_trig_addr + 200;		//fast forward 4us.
		}

		for ( icnt = start_addr; icnt < SAMPLE_SIZE - 100;  icnt++ )
		{
			if ((Gage_chan_b_voltage[icnt+2] - Gage_chan_b_voltage[icnt])>0.02 && ((Gage_chan_b_voltage[icnt+5] - Gage_chan_b_voltage[icnt])>0.03))//Added to eliminate wrong stop trigger.
			{
				Stop_Value = Gage_chan_b_voltage[icnt];
				stop_trig_addr = icnt;
				break;
				
			}
		}
		tOVL_Avg[loop_cnt] = float ((stop_trig_addr - start_trig_addr)*20e-9);
		//tOVL_Sum = tOVL_Sum + tOVL_Avg[loop_cnt];
	
		if (DEBUG==1)
		{
			printf("	Start_addr   = %i,  Stop_addr  = %i  with tOVL = %0.2f us\n",start_trig_addr ,stop_trig_addr, (1e6)*tOVL_Avg[loop_cnt]);
		}
		loop_cnt++;
	}


	//*tOVL = tOVL_Sum/valid_cnt;
	//*tOVL = (stop_trig_addr - start_trig_addr)*20e-9;

	//Eliminate noisy pulse which can cause wrong average.
	for(i=0;i<10;i++)
	{
		if(tOVL_Avg[i]  > 7.0e-6 && tOVL_Avg[i] < 12e-6)
		{
			tOVL_Sum2 = tOVL_Sum2 + tOVL_Avg[i];
			valid_cnt++;
		}
	}

	if(valid_cnt >0)
	{
		*tOVL = tOVL_Sum2/valid_cnt;
	}
	else
	{
		*tOVL = -888e-6;
	}
	
}
	
void Gage_Find_tOVL_Turret(float *tOVL)
{
	int start_addr=0;
	int stop_addr=0;
	int start_trig_addr=0;
	int stop_trig_addr=0;
	int icnt =0; 
	int loop_cnt = 0, valid_cnt = 0;
	int j_cnt = 0;
	long int i = 0;
	float tOVL_Avg[10];
	float tOVL_Sum = 0.0, tOVL_Sum2 = 0.0;
	float Start_Value = 0;
	float Stop_Value = 0;
	//float Start_Trig = 4.7;
	//float Stop_Trig = 4.2;
	float Start_Trig = 4.60; //4.7 is for Turret Rev A
	float Stop_Trig = 4.15; //4.2 is for Turret Rev A

	loop_cnt= 0;
	
	while(loop_cnt < 10)
	{
		tOVL_Avg[loop_cnt] = 0.0;
		loop_cnt++;
	}

	if(LB_Rev>=5 )
	{
		Start_Trig = 4.60;
		Stop_Trig  = 4.15;
	}

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*tOVL  = 999.0;
		return;
	}

	//transfer data to PC (XP)
	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array

	// Save captured data as .awav file. //
	if (DEBUG==1)
	{
			double *capture_data_B = (double *)malloc((GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD)*sizeof(double));
			for( i = 0; i < (GAGE_WAVEFORM_BUFFER_SIZE-10); i++)
			{	
				capture_data_B[i] = (double)(Gage_chan_b_voltage[i]); // XP //	
			}
			CreateAwav(	capture_data_B, // Data array //
							GAGE_WAVEFORM_BUFFER_SIZE-10, // Size of array //
							20.0e-9, // Sampling period //				 
							"e:\\dl4\\tOVL.awav"); // Output file and path //
			free (capture_data_B);
	}

	loop_cnt= 0;
	while(loop_cnt < 10)
	{
		// Look for start trigger point //
		if(loop_cnt == 0)
		{
			start_addr = 10;		
		}
		else
		{
			start_addr = start_addr + 2000;		
		}
		//for ( icnt = start_addr; icnt < SAMPLE_SIZE - 100;  icnt++ )
		for ( icnt = start_addr; icnt < start_addr + 2500 ;  icnt++ )
		{
			if (fabs(Gage_chan_b_voltage[icnt] - Gage_chan_b_voltage[icnt+6])>0.040)//used to be 50mV
			{
				Start_Value = Gage_chan_b_voltage[icnt];
				start_trig_addr = icnt;
				break;
			}
		}
		// Look for stop trigger point //
		if(g_TurretCB)
		{
			start_addr = start_trig_addr + 300;		//HL- fast forward 6us due to slight higher stop threshold		
		}
		else
		{
			start_addr = start_trig_addr + 200;		//fast forward 4us.
		}

		for ( icnt = start_addr; icnt < SAMPLE_SIZE - 100;  icnt++ )
		{
			if ((Gage_chan_b_voltage[icnt+2] - Gage_chan_b_voltage[icnt])>0.02 && ((Gage_chan_b_voltage[icnt+5] - Gage_chan_b_voltage[icnt])>0.03))//Added to eliminate wrong stop trigger.
			{
				Stop_Value = Gage_chan_b_voltage[icnt];
				stop_trig_addr = icnt;
				break;
				
			}
		}
		tOVL_Avg[loop_cnt] = float ((stop_trig_addr - start_trig_addr)*20e-9);
		//tOVL_Sum = tOVL_Sum + tOVL_Avg[loop_cnt];
	
		if (DEBUG==1)
		{
			printf("	Start_addr   = %i,  Stop_addr  = %i  with tOVL = %0.2f us\n",start_trig_addr ,stop_trig_addr, (1e6)*tOVL_Avg[loop_cnt]);
		}
		loop_cnt++;
	}


	//*tOVL = tOVL_Sum/valid_cnt;
	//*tOVL = (stop_trig_addr - start_trig_addr)*20e-9;

	//Eliminate noisy pulse which can cause wrong average.
	for(i=0;i<10;i++)
	{
		if(tOVL_Avg[i]  > 7.0e-6 && tOVL_Avg[i] < 12e-6)
		{
			tOVL_Sum2 = tOVL_Sum2 + tOVL_Avg[i];
			valid_cnt++;
		}
	}

	if(valid_cnt >0)
	{
		*tOVL = tOVL_Sum2/valid_cnt;
	}
	else
	{
		*tOVL = -888e-6;
	}
	
}

void Gage_Find_FWPK_4Rings_DableON_Timer(float *tDableON, float *FWPK_Timer, float *FWPK4Ring, float *DableOnHi4Ring)
{
	*tDableON		=0.0;
	*FWPK_Timer		=0.0;
	*FWPK4Ring		=0.0;
	*DableOnHi4Ring	=0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*tDableON		=999;
		*FWPK_Timer		=999;
		*FWPK4Ring		=999;
		*DableOnHi4Ring	=999;
		return;
	}

	/***********************************************************************************************************************************
	 ***********************************************************************************************************************************

				 tDable											  Rings cnt					  DableOn stays High
				 Ontime											  1st    2nd     3rd     4th  after 4th Ring
	 =================================================================================================================================
		SR _____  _		  _ 	Timer  	  ______________________  _		 _ 		 _ 	     _   ____________________________________	5V
				| ||	  ||<--  20us --> |						| ||	 ||		 ||	     ||  |
				|_||______||______________|						|_||_____||______||______||__|										0V
		FW _	 ___	 ___________________________________	 ___	 ___	 ___	 ___	 ___	 ___	 ________________	5V
			|   |	|	|									|   |	|	|	|   |	|	|	|   |	|	|	|   |	
			|___|	|___|									|___|1st|___|2nd|___|3rd|___|4th|___|5th|___|6th|___|7th				< -150mV
		FB  ____________________________________			____________________________________________________________			(110% CVth)
		    |									|			|															|
		   _|									|___________|															|________	(1V)
		
	 IMPORTANT: Normal request cycle coming from BPS is ~33us.  FB has to be within 30us going from low to high to stop request and
				stay in sync with FW.  Otherwise, the SR signal "DableOnTime" will not work.

	 rlb REV B changed missing 3rd X pulse 10/19/2016
	 
	 =================================================================================================================================
		Expect SR signals: 8 Low, 8 High.  1st Low start from SR high to Low and final High with SR stays High
		Note: Both tLow must be greater or equal to 1us while tHigh = half Ring of Freq = 0.5(1/Freq)

		1MHz	(tHigh = 0.5us)								300kHz	(tHigh = 1.67us)			
		FW _	 ___	 _____								FW _	 ___	 _____
			|   |	|	|										|   |	|	|		
			|___|	|___|										|___|	|___|		

		Array Variables to expect:
		------------------------------------------------------------------------------------------------------------------
		SR_tLow[8]			SR_tLow[2] = 20us Timer		(expect ~24us)
		SR_tHigh[8]			SR_tHigh[0]= tDable Ontime	(expect ~320ns for 300kHz half ring, ~100ns for 1MHz half ring)
		Ring_Pulse[4]
		DableOnHi4pulse

	 ***********************************************************************************************************************************
	 ***********************************************************************************************************************************/

	int	PULSE_NUM_NEED  =12;		// 12 negative edges and 12 positive edges
	int	PULSE_NUM_PROCESSED =0;		// Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0, Sample_per_cycle=0, i=0, j=0; 
	float Vdson_peak_ave =0.0;
	bool Find_Negative_Edge_Flag, Find_Positive_Edge_Flag, tLow_Found, tHigh_Found;
	int tLow_Found_cnt, tHigh_Found_cnt;

	// Variables for FWPK SR signals
	//float	SRon_tReqInhibit[12]	= {0.0};
	float	tLow[24]					= {0.0};
	float	tHigh[24]				= {0.0};
	float	SRlow[24]				= {0.0};
	float	SRhigh[24]				= {0.0};
	int		SRlow_addr[24]			= {0};
	int		SRhigh_addr[24]			= {0};

	char wave_name_SR[150] ="/0"; 

	// Require to capture ~120us for everything.  (20ns/sample => 6000 samples.  If 10ns/sample => 12000 samples)
	//Sample_per_cycle = 1750;

	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	{
		//SRon_tReqInhibit[icnt]	= -100;
		SRlow[icnt]				= 0;
		SRhigh[icnt]				= 0;
		SRlow_addr[icnt]			= 0;
		SRhigh_addr[icnt]		= 0;
	}

	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array
	
	start_addr = 0;						
	//while (Gage_chan_b_voltage[start_addr]> 4.0 && start_addr < SAMPLE_SIZE)
	//	start_addr+=50;					// Fast forward by 1us with sample rate of 20ns

	//start_addr -= 50;	//Step back 1us to start

	Find_Negative_Edge_Flag	= true;
	Find_Positive_Edge_Flag	= false;
	tLow_Found				= false;
	tHigh_Found				= false;
	pulse_cnt				=0;
	tLow_Found_cnt			=0;
	tHigh_Found_cnt			=0;

	// Search for the negative and positive edges
	//while ((pulse_cnt< PULSE_NUM_NEED)&& (start_addr < SAMPLE_SIZE))
	//{
		for(icnt = start_addr; icnt< SAMPLE_SIZE ; icnt++)	
		{
			// Find Negative edge
			if(Gage_chan_b_voltage[icnt] < 1.0 && Find_Negative_Edge_Flag==true)
			//if(Gage_chan_b_voltage[icnt] < 1.50 && Find_Negative_Edge_Flag==true)//JD cold debug
			{
				SRlow[pulse_cnt]			= Gage_chan_b_voltage[icnt];
				SRlow_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= true;
				Find_Negative_Edge_Flag		= false;
				tLow_Found			= false;
				tHigh_Found			= true;
				tHigh_Found_cnt		+= 1;
				pulse_cnt++;
				//break;
			}
			// Find Positive edge
			else
			if(Gage_chan_b_voltage[icnt] > 1.75 && Find_Positive_Edge_Flag==true)
			//if(Gage_chan_b_voltage[icnt] > 3.0 && Find_Positive_Edge_Flag==true)//JD cold debug
			
			{
				SRhigh[pulse_cnt]		= Gage_chan_b_voltage[icnt];
				SRhigh_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= false;
				Find_Negative_Edge_Flag		= true;
				tLow_Found					= true;
				tLow_Found_cnt				+= 1;
				tHigh_Found					= false;
				pulse_cnt++;
				//break;
			}
			
		//}

		// Ton 
		//if(tLow_Found == true)
		//	tLow[pulse_cnt]	= (SRhigh_addr[pulse_cnt] - SRlow_addr[pulse_cnt-1])* SAMPLE_RATE_s;
		//if(pulse_cnt > 1 && tHigh_Found == true)
		//	tHigh[pulse_cnt]	= (SRlow_addr[pulse_cnt] - SRhigh_addr[pulse_cnt-1])* SAMPLE_RATE_s;


		//// Reset start address after find a Negative or Positive edge.
		//PULSE_NUM_PROCESSED ++;
		////if(Find_Positive_Edge_Flag == true)
		////	start_addr = SRlow_addr[pulse_cnt]+750;	// Move forward 15us
		////else
		////	start_addr = SRhigh_addr[pulse_cnt]+500;	// Move forward 10us
		//pulse_cnt ++;
	}


	//Analyze Results
//	if( tLow_Found_cnt == 12 && tHigh_Found_cnt == 12 ) //RLB
	if( tLow_Found_cnt == 8 && tHigh_Found_cnt == 8 ) 
	{
		j=0;
		//for(i=0; i<=23; i++)//RLB
		for(i=0; i<=15; i++)
		{
			tLow[j]  = (SRhigh_addr[i+1] - SRlow_addr[i])    * SAMPLE_RATE_s;
			tHigh[j] = (SRlow_addr[i+2]  - SRhigh_addr[i+1]) * SAMPLE_RATE_s;
			j++;
			i++;
		}
		*tDableON	= tHigh[0];
		//'*FWPK_Timer	= tLow[2];
		*FWPK_Timer	= tLow[2]+tLow[1]+tLow[0]+tHigh[1]+tHigh[0];	// JD, FWpk times is the entire 1st window (~20us)

		//FWPK 4 Rings count
//		for(i=7; i<=10; i++)//RLB
		for(i=3; i<=6; i++)
		{
			if(tHigh[i] > 40e-9)
				*FWPK4Ring  += 1;
		}

		//DableOn stays High after 4th Ring (just need to make sure it stays high for > 20us)
		*DableOnHi4Ring = true;
//		for(i=SRhigh_addr[23]; i< SRhigh_addr[23]+ 20e-6/SAMPLE_RATE_s; i++)//RLB
		for(i=SRhigh_addr[15]; i< SRhigh_addr[15]+ 20e-6/SAMPLE_RATE_s; i++)
		{
			if(Gage_chan_b_voltage[i] < 1.50)
				*DableOnHi4Ring = false;
		}
	}
	else 
	{
		*tDableON		= 999;
		*FWPK_Timer		= 999;
		*FWPK4Ring		= 999;
		*DableOnHi4Ring = false;
	}

	if(DEBUG==1)
	{
		strcpy (wave_name_SR, WAVE_NAME);
		strcat (wave_name_SR, "_SR"); 
		Create_Awav_xp(wave_name_SR, Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}
}

void Gage_Find_FWPK_DableON_Timer(float *tDableON, float *FWPK_Timer)
{
	*tDableON		=0.0;
	*FWPK_Timer		=0.0;
	//*FWPK4Ring		=0.0;
	//*DableOnHi4Ring	=0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*tDableON		=999;
		*FWPK_Timer		=999;
		//*FWPK4Ring		=999;
		//*DableOnHi4Ring	=999;
		return;
	}

	/***********************************************************************************************************************************
	 ***********************************************************************************************************************************

				 tDable											  Rings cnt					  DableOn stays High
				 Ontime											  1st    2nd     3rd     4th  after 4th Ring
	 =================================================================================================================================
		SR _____  _		  _ 	Timer  	  ______________________  _		 _ 		 _ 	     _   ____________________________________	5V
				| ||	  ||<--  20us --> |						| ||	 ||		 ||	     ||  |
				|_||______||______________|						|_||_____||______||______||__|										0V
		FW _	 ___	 ___________________________________	 ___	 ___	 ___	 ___	 ___	 ___	 ________________	5V
			|   |	|	|									|   |	|	|	|   |	|	|	|   |	|	|	|   |	
			|___|	|___|									|___|1st|___|2nd|___|3rd|___|4th|___|5th|___|6th|___|7th				< -150mV
		FB  ____________________________________			____________________________________________________________			(110% CVth)
		    |									|			|															|
		   _|									|___________|															|________	(1V)
		
	 IMPORTANT: Normal request cycle coming from BPS is ~33us.  FB has to be within 30us going from low to high to stop request and
				stay in sync with FW.  Otherwise, the SR signal "DableOnTime" will not work.

	 rlb REV B changed missing 3rd X pulse 10/19/2016
	 
	 =================================================================================================================================
		Expect SR signals: 8 Low, 8 High.  1st Low start from SR high to Low and final High with SR stays High
		Note: Both tLow must be greater or equal to 1us while tHigh = half Ring of Freq = 0.5(1/Freq)

		1MHz	(tHigh = 0.5us)								300kHz	(tHigh = 1.67us)			
		FW _	 ___	 _____								FW _	 ___	 _____
			|   |	|	|										|   |	|	|		
			|___|	|___|										|___|	|___|		

		Array Variables to expect:
		------------------------------------------------------------------------------------------------------------------
		SR_tLow[8]			SR_tLow[2] = 20us Timer		(expect ~24us)
		SR_tHigh[8]			SR_tHigh[0]= tDable Ontime	(expect ~320ns for 300kHz half ring, ~100ns for 1MHz half ring)
		Ring_Pulse[4]
		DableOnHi4pulse

	 ***********************************************************************************************************************************
	 ***********************************************************************************************************************************/

	int	PULSE_NUM_NEED  =3;			// 3 negative edges and 3 positive edges
	int	PULSE_NUM_PROCESSED =0;		// Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0, Sample_per_cycle=0, i=0, j=0; 
	float Vdson_peak_ave =0.0;
	bool Find_Negative_Edge_Flag, Find_Positive_Edge_Flag, tLow_Found, tHigh_Found;
	int tLow_Found_cnt, tHigh_Found_cnt;

	// Variables for FWPK SR signals
	//float	SRon_tReqInhibit[12]	= {0.0};
	float	tLow[24]					= {0.0};
	float	tHigh[24]				= {0.0};
	float	SRlow[24]				= {0.0};
	float	SRhigh[24]				= {0.0};
	int		SRlow_addr[24]			= {0};
	int		SRhigh_addr[24]			= {0};

	char wave_name_SR[150] ="/0"; 

	// Require to capture ~120us for everything.  (20ns/sample => 6000 samples.  If 10ns/sample => 12000 samples)
	//Sample_per_cycle = 1750;

	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	{
		//SRon_tReqInhibit[icnt]	= -100;
		SRlow[icnt]				= 0;
		SRhigh[icnt]				= 0;
		SRlow_addr[icnt]			= 0;
		SRhigh_addr[icnt]		= 0;
	}

	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array
	
	start_addr = 0;						

	Find_Negative_Edge_Flag	= true;
	Find_Positive_Edge_Flag	= false;
	tLow_Found				= false;
	tHigh_Found				= false;
	pulse_cnt				=0;
	tLow_Found_cnt			=0;
	tHigh_Found_cnt			=0;

		for(icnt = start_addr; icnt< SAMPLE_SIZE ; icnt++)	
		{
			// Find Negative edge
			if(Gage_chan_b_voltage[icnt] < 1.0 && Find_Negative_Edge_Flag==true)
			//if(Gage_chan_b_voltage[icnt] < 1.50 && Find_Negative_Edge_Flag==true)//JD cold debug
			{
				SRlow[pulse_cnt]			= Gage_chan_b_voltage[icnt];
				SRlow_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= true;
				Find_Negative_Edge_Flag		= false;
				tLow_Found			= false;
				tHigh_Found			= true;
				tHigh_Found_cnt		+= 1;
				pulse_cnt++;
				//break;
			}
			// Find Positive edge
			else
			if(Gage_chan_b_voltage[icnt] > 1.75 && Find_Positive_Edge_Flag==true)
			//if(Gage_chan_b_voltage[icnt] > 3.0 && Find_Positive_Edge_Flag==true)//JD cold debug
			
			{
				SRhigh[pulse_cnt]		= Gage_chan_b_voltage[icnt];
				SRhigh_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= false;
				Find_Negative_Edge_Flag		= true;
				tLow_Found					= true;
				tLow_Found_cnt				+= 1;
				tHigh_Found					= false;
				pulse_cnt++;
				//break;
			}
			

	}


	//Analyze Results
//	if( tLow_Found_cnt == 12 && tHigh_Found_cnt == 12 ) //RLB
	if( tLow_Found_cnt == 3 && tHigh_Found_cnt == 3 ) 
	{
		j=0;
		//for(i=0; i<=23; i++)//RLB
		for(i=0; i<=5; i++)
		{
			tLow[j]  = (SRhigh_addr[i+1] - SRlow_addr[i])    * SAMPLE_RATE_s;
			tHigh[j] = (SRlow_addr[i+2]  - SRhigh_addr[i+1]) * SAMPLE_RATE_s;
			j++;
			i++;
		}
		*tDableON	= tHigh[0];
		*FWPK_Timer	= tLow[2];
		//*FWPK_Timer	= tLow[2]+tLow[1]+tLow[0]+tHigh[1]+tHigh[0];	// JD, FWpk times is the entire 1st window (~20us)

//////////		//FWPK 4 Rings count
////////////		for(i=7; i<=10; i++)//RLB
//////////		for(i=3; i<=6; i++)
//////////		{
//////////			if(tHigh[i] > 40e-9)
//////////				*FWPK4Ring  += 1;
//////////		}
//////////
//////////		//DableOn stays High after 4th Ring (just need to make sure it stays high for > 20us)
//////////		*DableOnHi4Ring = true;
////////////		for(i=SRhigh_addr[23]; i< SRhigh_addr[23]+ 20e-6/SAMPLE_RATE_s; i++)//RLB
//////////		for(i=SRhigh_addr[15]; i< SRhigh_addr[15]+ 20e-6/SAMPLE_RATE_s; i++)
//////////		{
//////////			if(Gage_chan_b_voltage[i] < 1.50)
//////////				*DableOnHi4Ring = false;
//////////		}
	}
	else 
	{
		*tDableON		= 999;
		*FWPK_Timer		= 999;
		////////*FWPK4Ring		= 999;
		////////*DableOnHi4Ring = false;
	}

	if(DEBUG==1)
	{
		strcpy (wave_name_SR, WAVE_NAME);
		strcat (wave_name_SR, "_SR"); 
		Create_Awav_xp(wave_name_SR, Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}
}

void Gage_Find_FWPK_4Rings(float *FWPK4Ring, float *DableOnHi4Ring)
{
	//*tDableON		=0.0;
	//*FWPK_Timer		=0.0;
	*FWPK4Ring		=0.0;
	*DableOnHi4Ring	=0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		//*tDableON		=999;
		//*FWPK_Timer		=999;
		*FWPK4Ring		=999;
		*DableOnHi4Ring	=999;
		return;
	}

	/***********************************************************************************************************************************
	 ***********************************************************************************************************************************

				 tDable											  Rings cnt					  DableOn stays High
				 Ontime											  1st    2nd     3rd     4th  after 4th Ring
	 =================================================================================================================================
		SR _____  _		  _ 	Timer  	  ______________________  _		 _ 		 _ 	     _   ____________________________________	5V
				| ||	  ||<--  20us --> |						| ||	 ||		 ||	     ||  |
				|_||______||______________|						|_||_____||______||______||__|										0V
		FW _	 ___	 ___________________________________	 ___	 ___	 ___	 ___	 ___	 ___	 ________________	5V
			|   |	|	|									|   |	|	|	|   |	|	|	|   |	|	|	|   |	
			|___|	|___|									|___|1st|___|2nd|___|3rd|___|4th|___|5th|___|6th|___|7th				< -150mV
		FB  ____________________________________			____________________________________________________________			(110% CVth)
		    |									|			|															|
		   _|									|___________|															|________	(1V)
		
	 IMPORTANT: Normal request cycle coming from BPS is ~33us.  FB has to be within 30us going from low to high to stop request and
				stay in sync with FW.  Otherwise, the SR signal "DableOnTime" will not work.

	 rlb REV B changed missing 3rd X pulse 10/19/2016
	 
	 =================================================================================================================================
		Expect SR signals: 8 Low, 8 High.  1st Low start from SR high to Low and final High with SR stays High
		Note: Both tLow must be greater or equal to 1us while tHigh = half Ring of Freq = 0.5(1/Freq)

		1MHz	(tHigh = 0.5us)								300kHz	(tHigh = 1.67us)			
		FW _	 ___	 _____								FW _	 ___	 _____
			|   |	|	|										|   |	|	|		
			|___|	|___|										|___|	|___|		

		Array Variables to expect:
		------------------------------------------------------------------------------------------------------------------
		SR_tLow[8]			SR_tLow[2] = 20us Timer		(expect ~24us)
		SR_tHigh[8]			SR_tHigh[0]= tDable Ontime	(expect ~320ns for 300kHz half ring, ~100ns for 1MHz half ring)
		Ring_Pulse[4]
		DableOnHi4pulse

	 ***********************************************************************************************************************************
	 ***********************************************************************************************************************************/

	int	PULSE_NUM_NEED  =5;		// 5 negative edges and 5 positive edges
	int	PULSE_NUM_PROCESSED =0;		// Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0, Sample_per_cycle=0, i=0, j=0; 
	float Vdson_peak_ave =0.0;
	bool Find_Negative_Edge_Flag, Find_Positive_Edge_Flag, tLow_Found, tHigh_Found;
	int tLow_Found_cnt, tHigh_Found_cnt;

	// Variables for FWPK SR signals
	//float	SRon_tReqInhibit[12]	= {0.0};
	float	tLow[24]					= {0.0};
	float	tHigh[24]				= {0.0};
	float	SRlow[24]				= {0.0};
	float	SRhigh[24]				= {0.0};
	int		SRlow_addr[24]			= {0};
	int		SRhigh_addr[24]			= {0};

	char wave_name_SR[150] ="/0"; 

	// Require to capture ~120us for everything.  (20ns/sample => 6000 samples.  If 10ns/sample => 12000 samples)
	//Sample_per_cycle = 1750;

	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	{
		//SRon_tReqInhibit[icnt]	= -100;
		SRlow[icnt]				= 0;
		SRhigh[icnt]				= 0;
		SRlow_addr[icnt]			= 0;
		SRhigh_addr[icnt]		= 0;
	}

	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array
	
	start_addr = 0;						
	Find_Negative_Edge_Flag	= true;
	Find_Positive_Edge_Flag	= false;
	tLow_Found				= false;
	tHigh_Found				= false;
	pulse_cnt				=0;
	tLow_Found_cnt			=0;
	tHigh_Found_cnt			=0;

	// Search for the negative and positive edges
	//while ((pulse_cnt< PULSE_NUM_NEED)&& (start_addr < SAMPLE_SIZE))
	//{
		for(icnt = start_addr; icnt< SAMPLE_SIZE ; icnt++)	
		{
			// Find Negative edge
			if(Gage_chan_b_voltage[icnt] < 1.0 && Find_Negative_Edge_Flag==true)
			//if(Gage_chan_b_voltage[icnt] < 1.50 && Find_Negative_Edge_Flag==true)//JD cold debug
			{
				SRlow[pulse_cnt]			= Gage_chan_b_voltage[icnt];
				SRlow_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= true;
				Find_Negative_Edge_Flag		= false;
				tLow_Found			= false;
				tHigh_Found			= true;
				tHigh_Found_cnt		+= 1;
				pulse_cnt++;
				//break;
			}
			// Find Positive edge
			else
			if(Gage_chan_b_voltage[icnt] > 1.75 && Find_Positive_Edge_Flag==true)
			//if(Gage_chan_b_voltage[icnt] > 3.0 && Find_Positive_Edge_Flag==true)//JD cold debug
			
			{
				SRhigh[pulse_cnt]		= Gage_chan_b_voltage[icnt];
				SRhigh_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= false;
				Find_Negative_Edge_Flag		= true;
				tLow_Found					= true;
				tLow_Found_cnt				+= 1;
				tHigh_Found					= false;
				pulse_cnt++;
				//break;
			}
			
	}


	//Analyze Results
//	if( tLow_Found_cnt == 12 && tHigh_Found_cnt == 12 ) //RLB
	if( tLow_Found_cnt == 5 && tHigh_Found_cnt == 5 ) 
	{
		j=0;
		//for(i=0; i<=23; i++)//RLB
		for(i=0; i<=9; i++)
		{
			tLow[j]  = (SRhigh_addr[i+1] - SRlow_addr[i])    * SAMPLE_RATE_s;
			tHigh[j] = (SRlow_addr[i+2]  - SRhigh_addr[i+1]) * SAMPLE_RATE_s;
			j++;
			i++;
		}
		//*tDableON	= tHigh[0];
		//'*FWPK_Timer	= tLow[2];
		//*FWPK_Timer	= tLow[2]+tLow[1]+tLow[0]+tHigh[1]+tHigh[0];	// JD, FWpk times is the entire 1st window (~20us)

		//FWPK 4 Rings count
//		for(i=7; i<=10; i++)//RLB
		for(i=0; i<=3; i++)
		{
			if(tHigh[i] > 40e-9)
				*FWPK4Ring  += 1;
		}

		//DableOn stays High after 4th Ring (just need to make sure it stays high for > 20us)
		*DableOnHi4Ring = true;
//		for(i=SRhigh_addr[23]; i< SRhigh_addr[23]+ 20e-6/SAMPLE_RATE_s; i++)//RLB
		for(i=SRhigh_addr[9]; i< SRhigh_addr[9]+ 20e-6/SAMPLE_RATE_s; i++)
		{
			if(Gage_chan_b_voltage[i] < 1.50)
				*DableOnHi4Ring = false;
		}
	}
	else 
	{
		//*tDableON		= 999;
		//*FWPK_Timer		= 999;
		*FWPK4Ring		= 999;
		*DableOnHi4Ring = false;
	}

	if(DEBUG==1 && gDEBUG)
	{
		strcpy (wave_name_SR, WAVE_NAME);
		strcat (wave_name_SR, "_SR"); 
		Create_Awav_xp(wave_name_SR, Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}
}

void Gage_Find_FWPK_4Rings_Turret(float *FWPK4Ring, float *DableOnHi4Ring)
{
	//*tDableON		=0.0;
	//*FWPK_Timer		=0.0;
	*FWPK4Ring		=0.0;
	*DableOnHi4Ring	=0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		//*tDableON		=999;
		//*FWPK_Timer		=999;
		*FWPK4Ring		=999;
		*DableOnHi4Ring	=999;
		return;
	}

	/***********************************************************************************************************************************
	 ***********************************************************************************************************************************

				 tDable											  Rings cnt					  DableOn stays High
				 Ontime											  1st    2nd     3rd     4th  after 4th Ring
	 =================================================================================================================================
		SR _____  _		  _ 	Timer  	  ______________________  _		 _ 		 _ 	     _   ____________________________________	5V
				| ||	  ||<--  20us --> |						| ||	 ||		 ||	     ||  |
				|_||______||______________|						|_||_____||______||______||__|										0V
		FW _	 ___	 ___________________________________	 ___	 ___	 ___	 ___	 ___	 ___	 ________________	5V
			|   |	|	|									|   |	|	|	|   |	|	|	|   |	|	|	|   |	
			|___|	|___|									|___|1st|___|2nd|___|3rd|___|4th|___|5th|___|6th|___|7th				< -150mV
		FB  ____________________________________			____________________________________________________________			(110% CVth)
		    |									|			|															|
		   _|									|___________|															|________	(1V)
		
	 IMPORTANT: Normal request cycle coming from BPS is ~33us.  FB has to be within 30us going from low to high to stop request and
				stay in sync with FW.  Otherwise, the SR signal "DableOnTime" will not work.

	 rlb REV B changed missing 3rd X pulse 10/19/2016
	 
	 =================================================================================================================================
		Expect SR signals: 8 Low, 8 High.  1st Low start from SR high to Low and final High with SR stays High
		Note: Both tLow must be greater or equal to 1us while tHigh = half Ring of Freq = 0.5(1/Freq)

		1MHz	(tHigh = 0.5us)								300kHz	(tHigh = 1.67us)			
		FW _	 ___	 _____								FW _	 ___	 _____
			|   |	|	|										|   |	|	|		
			|___|	|___|										|___|	|___|		

		Array Variables to expect:
		------------------------------------------------------------------------------------------------------------------
		SR_tLow[8]			SR_tLow[2] = 20us Timer		(expect ~24us)
		SR_tHigh[8]			SR_tHigh[0]= tDable Ontime	(expect ~320ns for 300kHz half ring, ~100ns for 1MHz half ring)
		Ring_Pulse[4]
		DableOnHi4pulse

	 ***********************************************************************************************************************************
	 ***********************************************************************************************************************************/

	int	PULSE_NUM_NEED  =5;		// 5 negative edges and 5 positive edges
	int	PULSE_NUM_PROCESSED =0;		// Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0, Sample_per_cycle=0, i=0, j=0; 
	float Vdson_peak_ave =0.0;
	bool Find_Negative_Edge_Flag, Find_Positive_Edge_Flag, tLow_Found, tHigh_Found;
	int tLow_Found_cnt, tHigh_Found_cnt;

	// Variables for FWPK SR signals
	//float	SRon_tReqInhibit[12]	= {0.0};
	float	tLow[24]					= {0.0};
	float	tHigh[24]				= {0.0};
	float	SRlow[24]				= {0.0};
	float	SRhigh[24]				= {0.0};
	int		SRlow_addr[24]			= {0};
	int		SRhigh_addr[24]			= {0};

	char wave_name_SR[150] ="/0"; 

	// Require to capture ~120us for everything.  (20ns/sample => 6000 samples.  If 10ns/sample => 12000 samples)
	//Sample_per_cycle = 1750;

	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	{
		//SRon_tReqInhibit[icnt]	= -100;
		SRlow[icnt]				= 0;
		SRhigh[icnt]				= 0;
		SRlow_addr[icnt]			= 0;
		SRhigh_addr[icnt]		= 0;
	}

	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array
	
	start_addr = 0;						
	Find_Negative_Edge_Flag	= true;
	Find_Positive_Edge_Flag	= false;
	tLow_Found				= false;
	tHigh_Found				= false;
	pulse_cnt				=0;
	tLow_Found_cnt			=0;
	tHigh_Found_cnt			=0;

	// Search for the negative and positive edges
	//while ((pulse_cnt< PULSE_NUM_NEED)&& (start_addr < SAMPLE_SIZE))
	//{
		for(icnt = start_addr; icnt< SAMPLE_SIZE ; icnt++)	
		{
			// Find Negative edge
			if(Gage_chan_b_voltage[icnt] < 1.0 && Find_Negative_Edge_Flag==true)
			//if(Gage_chan_b_voltage[icnt] < 1.50 && Find_Negative_Edge_Flag==true)//JD cold debug
			{
				SRlow[pulse_cnt]			= Gage_chan_b_voltage[icnt];
				SRlow_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= true;
				Find_Negative_Edge_Flag		= false;
				tLow_Found			= false;
				tHigh_Found			= true;
				tHigh_Found_cnt		+= 1;
				pulse_cnt++;
				//break;
			}
			// Find Positive edge
			else
			if(Gage_chan_b_voltage[icnt] > 1.75 && Find_Positive_Edge_Flag==true)
			//if(Gage_chan_b_voltage[icnt] > 3.0 && Find_Positive_Edge_Flag==true)//JD cold debug
			
			{
				SRhigh[pulse_cnt]		= Gage_chan_b_voltage[icnt];
				SRhigh_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= false;
				Find_Negative_Edge_Flag		= true;
				tLow_Found					= true;
				tLow_Found_cnt				+= 1;
				tHigh_Found					= false;
				pulse_cnt++;
				//break;
			}
			
	}


	//Analyze Results
//	if( tLow_Found_cnt == 12 && tHigh_Found_cnt == 12 ) //RLB
//	if( tLow_Found_cnt == 5 && tHigh_Found_cnt == 5 ) 

	if( tLow_Found_cnt == 8 && tHigh_Found_cnt == 8 ) 

	{
		j=0;
		for(i=0; i<=23; i++)//RLB
		//for(i=0; i<=9; i++)
		{
			tLow[j]  = (SRhigh_addr[i+1] - SRlow_addr[i])    * SAMPLE_RATE_s;
			tHigh[j] = (SRlow_addr[i+2]  - SRhigh_addr[i+1]) * SAMPLE_RATE_s;
			j++;
			i++;
		}
		//*tDableON	= tHigh[0];
		//'*FWPK_Timer	= tLow[2];
		//*FWPK_Timer	= tLow[2]+tLow[1]+tLow[0]+tHigh[1]+tHigh[0];	// JD, FWpk times is the entire 1st window (~20us)

		//FWPK 4 Rings count
	for(i=0; i<=10; i++)//RLB
		//for(i=0; i<=3; i++)
		{
			if(tHigh[i] > 40e-9)
				*FWPK4Ring  += 1;
		}

		//DableOn stays High after 4th Ring (just need to make sure it stays high for > 20us)
		*DableOnHi4Ring = true;
//		for(i=SRhigh_addr[23]; i< SRhigh_addr[23]+ 20e-6/SAMPLE_RATE_s; i++)//RLB
		for(i=SRhigh_addr[9]; i< SRhigh_addr[9]+ 20e-6/SAMPLE_RATE_s; i++)
		{
			if(Gage_chan_b_voltage[i] < 1.50)
				*DableOnHi4Ring = false;
		}
	}
	else 
	{
		//*tDableON		= 999;
		//*FWPK_Timer		= 999;
		*FWPK4Ring		= 999;
		*DableOnHi4Ring = false;
	}

	if(DEBUG==1 && gDEBUG)
	{
		strcpy (wave_name_SR, WAVE_NAME);
		strcat (wave_name_SR, "_SR"); 
		Create_Awav_xp(wave_name_SR, Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}
}

void Gage_Find_tReqInhibit(float *TREQ_Inhibit, float *Ton_ave, float *Toff_ave, float *Num_Cycles, int *Unwanted_pulses)
{
	/*********************************************************************************************************************
	tREQ_INH, tREQ_INH_cycles (No Response cycles), Unwanted_Pulses

	Procedure:
		1. Primary power-up with TM5 at low load and have Sync Circuit ready
		2. Secondary power-up to take over control
		3. FB set above CVth to stop switching
		4. Disconnect Sync Circuit and leave 2ndary in control
		5. FB set low and observe 8 unwanted pulses from Drain pin

		Drain ______
					|
					|____
					
	***********************************************************************************************************************/

	*TREQ_Inhibit	=0.0;
	*Ton_ave		=0.0;
	*Toff_ave		=0.0;
	*Num_Cycles		=0.0;

	int i = 0;
	for (i=0; i<GAGE_WAVEFORM_BUFFER_SIZE; i++)
		Gage_chan_b_voltage[i] = 0;	// Initialize array before data transfer

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*TREQ_Inhibit	=999;
		*Ton_ave		=999;
		*Toff_ave		=999;
		*Num_Cycles		=999;
		return;
	}

	//	We will see 9 of ~17us negative duty cycle and 8 of ~12us positive duty cycle.  
	//  will stay high like the drain default condition.

	int	PULSE_NUM_NEED  =9;		// 4 negative edges and 4 positive edges
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0, Sample_per_cycle=0; 
	float Vdson_peak_ave =0.0;
	bool Find_Negative_Edge_Flag, Find_Positive_Edge_Flag, Ton_Found, Toff_Found;
	int Ton_Found_cnt, Toff_Found_cnt;

	// Variables for TREQ_Inhibit
	float	Vdon_tReqInhibit[10]	= {0.0};
	float	Ton[10]					= {0.0};
	float	Toff[10]				= {0.0};
	float	Vdon[10]				= {0.0};
	float	Vdoff[10]				= {0.0};
	int		Vdon_addr[10]			= {0};
	int		Vdoff_addr[10]			= {0};

	char wave_name_Vd[150] ="/0"; 

	// Every cycle takes ~30us.  To be on the safe side set it to be ~35us so we will not miss the search  (35us/20ns = 1750 samples)
	Sample_per_cycle = 2250;

	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	{
		Vdon_tReqInhibit[icnt]	= -100;
		Vdon[icnt]				= 0;
		Vdoff[icnt]				= 0;
		Vdon_addr[icnt]			= 0;
		Vdoff_addr[icnt]		= 0;
	}

	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array
	
	start_addr = 500;		//HL changed to 500 to totally skip the first pulse. 6/28/17

	while (Gage_chan_b_voltage[start_addr]> 0.5 && start_addr < SAMPLE_SIZE)
		start_addr+=50;					// Fast forward by 1us with sample rate of 20ns

	//start_addr -= 100;	//Step back 1us to start

	Find_Negative_Edge_Flag	= true;
	Find_Positive_Edge_Flag	= false;
	Ton_Found				= false;
	Toff_Found				= false;
	pulse_cnt				=0;
	Ton_Found_cnt			=0;
	Toff_Found_cnt			=0;

	// Search for the negative and positive edges
	while ((pulse_cnt< PULSE_NUM_NEED)&& (start_addr < SAMPLE_SIZE))
	{
		// Find Positive edge

		for(icnt = start_addr; icnt< start_addr + Sample_per_cycle ; icnt++)	
		{
			// Find Negative edge
			if(Gage_chan_b_voltage[icnt] < 0.5 && Find_Negative_Edge_Flag==true)
			{
				Vdon[pulse_cnt]			= Gage_chan_b_voltage[icnt];
				Vdon_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= true;
				Find_Negative_Edge_Flag		= false;
				if(pulse_cnt > 0)
				{
					Ton_Found			= false;
					Toff_Found			= true;
					Toff_Found_cnt		+= 1;
				}
				break;
			}
			// Find Positive edge
			else
			if(Gage_chan_b_voltage[icnt] > 0.5 && Find_Positive_Edge_Flag==true)
			{
				Vdoff[pulse_cnt]		= Gage_chan_b_voltage[icnt];
				Vdoff_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= false;
				Find_Negative_Edge_Flag		= true;
				Ton_Found					= true;
				Ton_Found_cnt				+= 1;
				Toff_Found					= false;
				break;
			}
			
		}

		// Ton 
		if(Ton_Found == true)
			Ton[pulse_cnt]	= (Vdoff_addr[pulse_cnt] - Vdon_addr[pulse_cnt-1])* SAMPLE_RATE_s;
		if(pulse_cnt > 1 && Toff_Found == true)
			Toff[pulse_cnt]	= (Vdon_addr[pulse_cnt] - Vdoff_addr[pulse_cnt-1])* SAMPLE_RATE_s;


		// Reset start address after find a Negative or Positive edge.
		PULSE_NUM_PROCESSED ++;
		if(Find_Positive_Edge_Flag == true)
			start_addr = Vdon_addr[pulse_cnt]+750;	// Move forward 15us
		else
			start_addr = Vdoff_addr[pulse_cnt]+500;	// Move forward 10us
		pulse_cnt ++;
	}


	//Average results
	if( Ton_Found_cnt == 4 && Toff_Found_cnt == 4 ) 
	{	// Skip first edges
		for(i=5; i<=8; i++)	// First Ton falling edge often low as it triggers in a sighly different palce each time
		{
			*Ton_ave	+= Ton[i];
			*Toff_ave	+= Toff[i];
		}

		*Ton_ave   /=Ton_Found_cnt-2;	// average last 2 readings
		*Toff_ave  /=Toff_Found_cnt-2;
		*TREQ_Inhibit = *Ton_ave + *Toff_ave;
		*Num_Cycles = (Ton_Found_cnt + (Toff_Found_cnt + 1)) / 2;	//Toff_Found_cnt + 1 because Drain stays off afterward
		*Unwanted_pulses = pulse_cnt-1;
	}
	else 
	{
			*TREQ_Inhibit	=999.0;
			*Ton_ave		=999.0;
			*Toff_ave		=999.0;
			*Num_Cycles		=999.0;
	}

	if(DEBUG==1 && gDEBUG)
	{
		strcpy (wave_name_Vd, WAVE_NAME);
		strcat (wave_name_Vd, "_Vd"); 
		Create_Awav_xp(wave_name_Vd, Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}
}


void Gage_Find_tHandshake(float *tHandshake, float *Fosc_P_tHS, float *Fosc_S_tHS)
{
	*tHandshake		=0.0;
	*Fosc_P_tHS		=0.0;
	*Fosc_S_tHS		=0.0;

	if (!trig_ok || !data_ok)
	{
		//Bad acquisition
		*tHandshake		=999;
		*Fosc_P_tHS		=999;
		*Fosc_S_tHS		=999;
		return;
	}

	//	We will see 4 negative pulses of 17us and 3 positive pulses of 12us.  The last positive pulse can not be used because it
	//  will stay high like the drain default condition.

	int	PULSE_NUM_NEED  =34;		// 15 negative edges and 15 positive edges
	int	PULSE_NUM_PROCESSED =0; // Actual num pulses Processed. Exclude first pulse in ave calculation 
	int start_addr=0;
	int pulse_cnt =0;
	int icnt =0, Sample_per_cycle=0, i=0; 
	float Vdson_peak_ave =0.0;
	bool Find_Negative_Edge_Flag, Find_Positive_Edge_Flag, Ton_Found, Toff_Found;
	int Ton_Found_cnt, Toff_Found_cnt;

	float	Ton_Primary=0, Toff_Primary=0, Ton_Secondary=0, Toff_Secondary=0;
	int		Ton_Primary_cnt=0, Toff_Primary_cnt=0, Ton_Secondary_cnt=0, Toff_Secondary_cnt=0;

	// Variables
	float	Ton[50]					= {0.0};
	float	Toff[50]				= {0.0};
	float	Vdon[50]				= {0.0};
	float	Vdoff[50]				= {0.0};
	int		Vdon_addr[50]			= {0};
	int		Vdoff_addr[50]			= {0};

	char wave_name_Vd[150] ="/0"; 

	//Before HS in place, Primary switch at ~100kHz with ~7us/~3us(ON/OFF)
	//When HS in place, device stop switching for 2 primary cycles and pass over control to Secondary on the 3rd cycle's falling edge
	//HS takes about 3 primary cycles ~ 32us.  (Use 35us in search routine for guardband)
	//Then Secondary takes over with switching frequency of ~35kHz with ~17us/11us(ON/OFF).  17us is from 2ndary and 11us from Primary
	
	Sample_per_cycle = 1750;	//use the longest cycle => 35us/20ns = 1750 samples

	for (icnt=0; icnt<PULSE_NUM_NEED; icnt++)
	{
		Ton[icnt]				= 0;
		Toff[icnt]				= 0;
		Vdon[icnt]				= 0;
		Vdoff[icnt]				= 0;
		Vdon_addr[icnt]			= 0;
		Vdoff_addr[icnt]		= 0;
	}

	Gage_Transfer_Data (GAGE_CHAN_B);	//transfer data to Gage_chan_b_voltage array
	
	start_addr = 0;						
	//We do not know if captured drain signal start at low or high
	while (Gage_chan_b_voltage[start_addr]< 0.25 && start_addr < SAMPLE_SIZE)
		start_addr+=50;					// Fast forward by 1us with sample rate of 20ns

	Find_Negative_Edge_Flag	= true;
	Find_Positive_Edge_Flag	= false;
	Ton_Found				= false;
	Toff_Found				= false;
	pulse_cnt				=0;
	Ton_Found_cnt			=0;
	Toff_Found_cnt			=0;

	// Search for the negative and positive edges
	while ((pulse_cnt< PULSE_NUM_NEED)&& (start_addr < SAMPLE_SIZE))
	{
		// Find Positive edge
		for(icnt = start_addr; icnt < start_addr + Sample_per_cycle; icnt++)	
		{
			// Find Negative edges
			if(Gage_chan_b_voltage[icnt] < 0.25 && Find_Negative_Edge_Flag==true)
			{
				Vdon[pulse_cnt]			= Gage_chan_b_voltage[icnt];
				Vdon_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= true;
				Find_Negative_Edge_Flag		= false;
				if(pulse_cnt > 0)
				{
					Ton_Found			= false;
					Toff_Found			= true;
					Toff_Found_cnt		+= 1;
				}
				break;
			}
			// Find Positive edge
			else
			if(Gage_chan_b_voltage[icnt] > 0.25 && Find_Positive_Edge_Flag==true)
			{
				Vdoff[pulse_cnt]		= Gage_chan_b_voltage[icnt];
				Vdoff_addr[pulse_cnt]	= icnt;
				Find_Positive_Edge_Flag		= false;
				Find_Negative_Edge_Flag		= true;
				Ton_Found					= true;
				Ton_Found_cnt				+= 1;
				Toff_Found					= false;
				break;
			}
			
		}

		// Ton 
		if(Ton_Found == true)
			Ton[pulse_cnt]	= (Vdoff_addr[pulse_cnt] - Vdon_addr[pulse_cnt-1])* SAMPLE_RATE_s;
		if(pulse_cnt > 1 && Toff_Found == true)
			Toff[pulse_cnt]	= (Vdon_addr[pulse_cnt] - Vdoff_addr[pulse_cnt-1])* SAMPLE_RATE_s;


		// Reset start address after find a Negative or Positive edge.
		PULSE_NUM_PROCESSED ++;
		if(Find_Positive_Edge_Flag == true && Toff[pulse_cnt] > 0)
		{
			start_addr = Vdon_addr[pulse_cnt]+250;	// Move forward 2.5us	(2500ns/20ns = 125)
			pulse_cnt ++;
		}
		else
		if(Ton[pulse_cnt] > 0)
		{
			start_addr = Vdoff_addr[pulse_cnt]+125;	// Move forward 5us		(5000ns/20ns = 250)
			pulse_cnt ++;
		}
		else
		if(pulse_cnt == 0)
		{
			if(Find_Positive_Edge_Flag == true)
				start_addr = Vdon_addr[pulse_cnt]+250;	// Move forward 2.5us	(2500ns/20ns = 125)
			else
				start_addr = Vdoff_addr[pulse_cnt]+125;	// Move forward 5us		(5000ns/20ns = 250)
			pulse_cnt ++;
		}
		else
			start_addr += 250;	//to prevent stuck in while loop.
	}

	delay(1);
	//Find the tHandshake
	if( Ton_Found_cnt > 6 && Toff_Found_cnt > 6 ) 
	{
		//Primary Ton=7us , Toff=3us
		//tHandshake =32us (tOFF)
		//2nddary Ton=17us, Toff=11us
		for(i=1; i<=30; i++)
		{
			//Ton Primary
			if(Ton[i] > 5.7e-6 && Ton[i] > 0)
			{
				Ton_Primary			+= Ton[i];
				Ton_Primary_cnt		+=1;
			}
			//Toff Primary
			if(Toff[i] > 3e-6 && Toff[i] > 0)
			{
				Toff_Primary		+= Toff[i];
				Toff_Primary_cnt	+= 1;
			}
			//tHandshake
			if(Toff[i] > 25e-6 && Toff[i] > 0)
				*tHandshake = Toff[i];
			//Ton Secondary
			if(Ton[i] < 5.7e-6 && Ton[i] > 0)
			{
				Ton_Secondary		+= Ton[i];
				Ton_Secondary_cnt	+=1;
			}
			//Toff Secondary
			if(Toff[i] < 2.9e-6 && Toff[i] < 25e-6)
			{
				Toff_Secondary		+= Toff[i];
				Toff_Secondary_cnt	+= 1;
			}
		}

		*Fosc_P_tHS  = 1 / ( Ton_Primary/Ton_Primary_cnt     + Toff_Primary/Toff_Primary_cnt     );
		*Fosc_S_tHS  = 1 / ( Ton_Secondary/Ton_Secondary_cnt + Toff_Secondary/Toff_Secondary_cnt );
	}
	else 
	{
			*tHandshake	=999.0;
			*Fosc_P_tHS		=999.0;
			*Fosc_S_tHS		=999.0;
	}

	if(DEBUG==1 && gDEBUG)
	{
		strcpy (wave_name_Vd, WAVE_NAME);
		strcat (wave_name_Vd, "_Vd"); 
		Create_Awav_xp(wave_name_Vd, Gage_chan_b_voltage, SAMPLE_SIZE-1, SAMPLE_RATE_s);

		WAVE_NAME = "NoWaveName";
	}
}


void Convert_Alphanumeric_to_Float(float *AN_int_return, char *an1)
{
	//pass in null terminqated string three alphanumeric characters
	//		Each character will be represented by two digits as follows:
	//			0->00
	//			.
	//			.
	//			.
	//			9->09
	//			A->10
	//			B->11
	//			.
	//			.
	//			.
	//			Z->36
	//		Three characters will be represented by 6 digits
	//		For example: HZ85 converts to 350805	(Z->35,8->08,5->05)
	//		For example: HC0A converts to 120010	(C->12,0->00,A->10)


	int int1_val, int2_val, int3_val;
	char temp1[2];
	
	strncpy(temp1, an1, 1);		//first charatcer
	temp1[1] = '\0';			//null character manually added
	int1_val = Alphanumeric_Lookup(an1);
	if (int1_val ==- 99)
	{
		*AN_int_return=-99.0;
		return;
	}

	strncpy(temp1, an1+1, 1);	//second character
	temp1[1] = '\0';			//null character manually added
	int2_val = Alphanumeric_Lookup(an1+1);
	if (int2_val == -99)
	{
		*AN_int_return=-99.0;
		return;
	}

	strncpy(temp1, an1+2, 1);	//third character
	temp1[1] = '\0';			//null character manually added
	int3_val = Alphanumeric_Lookup(an1+2);
	if (int3_val == -99)
	{
		*AN_int_return=-99.0;
		return;
	}

	*AN_int_return = (float)((int1_val*10000) + (int2_val*100) + int3_val);
}

int Alphanumeric_Lookup(char* an)
{
	if (*an >= '0' && *an <= '9')
		return (*an - '0');
	else if (*an >= 'A' && *an <= 'Z')
		return (*an - 'A' + 10);
	else if (*an >= 'a' && *an <= 'z')
		return (*an - 'a' + 10);
	else
		return -99;
}

void Create_Awav_xp (	char	*wave_name,
						float   *v_data,
						int		arr_size,
						float	samp_rate )
{
	//GetSerialNum(Dut_serial_number);

//		strcpy (Wav_outfile_name, Wav_Outfile_path); 
		strcpy (Wav_outfile_name, "e:\\DL4\\"); 
		strcat (Wav_outfile_name, DevName); 
		//strcat (Wav_outfile_name, "_#"); strcat (Wav_outfile_name, Dut_serial_number); 
		strcat (Wav_outfile_name, "_"); 
		strcat (Wav_outfile_name, wave_name);
		//strcat (Wav_outfile_name, "_"); strcat (Wav_outfile_name, Hdwr_id); 
		strcat (Wav_outfile_name, ".awav"); 

		FILE * fpr_1 = fopen (Wav_outfile_name, "w"); 
		if (!fpr_1) return;

		fprintf (fpr_1, "version awav 0 2 0;\n");
		fprintf (fpr_1, "date 07 10 2003;\n");
		fprintf (fpr_1, "time 14 42 47;\n");
		fprintf (fpr_1, "name =  \"result_data\";\n");
		fprintf (fpr_1, "type = rrect;\n");
		fprintf (fpr_1, "size = %d;\n", arr_size);
		fprintf (fpr_1, "sample_interval = %13.11e;\n", samp_rate);
		fprintf (fpr_1, "offset = 0.000000e+000;\n");
		fprintf (fpr_1, "x_units = \"s \";\n");
		fprintf (fpr_1, "y_units = \"V \";\n");
		fprintf (fpr_1, "pattern;\n");
		fprintf (fpr_1, "  !Value\n");

		for (int i = 0; i < arr_size; i++)	
		{
			if ( v_data[i] >= 0.0) fprintf (fpr_1, "+");
			fprintf (fpr_1, "%18.16e; !%d\n", v_data[i] * 2.0, i);
		}

		fprintf (fpr_1, "pattern_end;\n"); fclose (fpr_1);
	return;
}

void Dump_Data(char	*wave_name,
			   int   serial_num,
			   float iPV3,
			   float iDVI2K,
			   float vFB, 
			   float vCB)
{

	ofstream outfile;

	strcpy(Wav_outfile_name, Wav_Outfile_path);
	strcat(Wav_outfile_name,DevName);
	strcat (Wav_outfile_name, "_"); 
	strcat (Wav_outfile_name, wave_name);
	strcat (Wav_outfile_name, ".txt"); 

	outfile.open(Wav_outfile_name,ios::app);
	if (!outfile.is_open()) return;

	if (serial_num==1)
		outfile<<"serial_num"<< "\t"<<"iPV3"<< "\t\t"<<"iDVI2K"<< "\t\t"<<"vFB"<<"\t\t"<<"vCB"<<"\t"<< endl;
	outfile<<serial_num<< "\t\t"<<iPV3<< "\t\t"<<iDVI2K<<"\t\t"<<vFB<<"\t\t"<<vCB<<"\t"<< endl;

	outfile.close();
	return;

}

//=================== XP gage digitizer Setup Codes STARTS here ===================
void Gage_init() {	
	
	//	CsFreeSystem(hSystem);	//Call only once at end of program
	//	InitBoard();	//Call only once at program load

	float gain = 1.00;		// start with 1.00 56X
	trig_ok = true;
	data_ok = true;

	CsAcqCfg.i64TriggerHoldoff=Gage_pretrig_samples;

	//Set Dual Mode.
 	//CSACQUISITIONCONFIG CsAcqCfg;
	CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
	CsAcqCfg.u32Mode = CS_MODE_DUAL;     //Dual Mode.
	CsAcqCfg.i64SampleRate = 50000000;    //50Mhz
	CsAcqCfg.i64Depth = 8192-CsAcqCfg.i64TriggerHoldoff;             //8K  4K
	CsAcqCfg.i64SegmentSize = CsAcqCfg.i64Depth+CsAcqCfg.i64TriggerHoldoff;
	CsAcqCfg.u32SegmentCount = 1;
	CsAcqCfg.i64TriggerTimeout = 100; //Definition: 100ns units.
	CsAcqCfg.u32ExtClk = 0;

	CsSet(hSystem, CS_ACQUISITION, &CsAcqCfg);


//Set CHANA to 200mV Range with 1Mohm Impedance.
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 1;      //Channel A
	CsChanCfg.u32Term = CS_COUPLING_DC; //GAGE_DC
	CsChanCfg.u32InputRange = CS_GAIN_400_MV	;     //400<==>200mVp-p, 4000==>2V
	CsChanCfg.u32Impedance = CS_REAL_IMP_1M_OHM	;   //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);


	//Set CHANB to 5V Range with 1Mohm Impedance.
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 2;      //Channel B
	CsChanCfg.u32Term = CS_COUPLING_DC; //GAGE_DC
	CsChanCfg.u32InputRange = 10000;     //5Vp-p
	CsChanCfg.u32Impedance = 1000000;   //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);


	//CSTRIGGERCONFIG CsTrigCfg;
	CsTrigCfg.u32Size = sizeof(CSTRIGGERCONFIG);
	CsTrigCfg.u32TriggerIndex		= 1;	//should always be 1
	CsTrigCfg.i32Source = CS_TRIG_SOURCE_CHAN_1;     //Channel A
	CsTrigCfg.u32ExtCoupling = CS_COUPLING_DC;		//GAGE_DC
	CsTrigCfg.u32ExtTriggerRange = 400; //2000;             //GAGE_PM_1_V
    CsTrigCfg.u32Condition = CS_TRIG_COND_NEG_SLOPE; //GAGE_NEGATIVE
	CsTrigCfg.i32Level = 0;							//Trigger Level 0V
	CsTrigCfg.u32ExtImpedance = 10000000;           //Impedance = 10Mhz;
	CsSet(hSystem, CS_TRIGGER, &CsTrigCfg);

	i32Status = CsDo(hSystem, ACTION_COMMIT); //Necessary to send settings to Hardware.

	//Get the current sample size, resolution and offset parameters from the driver
	//by calling CsGet for the ACQUISTIONCONFIG structure. These values are used
	//when saving the file.

	CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
	i32Status = CsGet(hSystem, CS_ACQUISITION, CS_ACQUISITION_CONFIGURATION, &CsAcqCfg);
	if (CS_FAILED(i32Status))
	{
		
		CsFreeSystem(hSystem);
		
	}

    CsAppData.i64TransferLength = GAGE_WAVEFORM_BUFFER_SIZE;
	CsAppData.u32TransferSegmentCount = 1;
	CsAppData.u32TransferSegmentStart = 1;
	CsAppData.u32PageSize = 32768;
	CsAppData.i32SaveFormat = 2;
}

void	Gage_Setup_Acquisition_xp ( int sample_rate_in_Hz, int sample_size )
{
	//Setup gage acquisition using XP driver
	//must be followed by ACTION_COMMIT to send settings to Hardware.
	CsAcqCfg.u32Size             = sizeof(CSACQUISITIONCONFIG);
	CsAcqCfg.u32Mode             = CS_MODE_DUAL;     //Dual Mode.
	CsAcqCfg.i64SampleRate       = sample_rate_in_Hz ;    //example:50000000
	CsAcqCfg.i64Depth            = sample_size-CsAcqCfg.i64TriggerHoldoff; 
	CsAcqCfg.i64SegmentSize		 = CsAcqCfg.i64Depth+CsAcqCfg.i64TriggerHoldoff;
	CsAcqCfg.u32SegmentCount	 = 1;
	CsAcqCfg.i64TriggerTimeout   = 100; //Definition: 100ns units.
	CsAcqCfg.u32ExtClk           = 0;
	CsAcqCfg.i64TriggerTimeout   = CS_TIMEOUT_DISABLE;

	i32Status = CsSet(hSystem, CS_ACQUISITION, &CsAcqCfg);
	//must be followed by ACTION_COMMIT to send settings to Hardware.
//	i32Status = CsDo(hSystem, ACTION_COMMIT); //Necessary to send settings to Hardware.
/*	char *lpBuffer;
	int  nBufferMax = 100;
	CsGetErrorString( i32Status,lpBuffer, nBufferMax);*/

	if (CS_FAILED(i32Status))
	{
//		MessageBox(NULL,"Error while setting Gage_Setup_Acquisition_xp.","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}

}


void	Gage_Setup_Chan_A ( int pk_pk_range_in_mV )
{
	//Setup Gage CHAN_A
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size         = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 1;                   //Channel A
	CsChanCfg.u32Term         = CS_COUPLING_DC;      //GAGE_DC
	CsChanCfg.u32InputRange   = pk_pk_range_in_mV ;  //mVp-p (example:400 -> 400mV pk-pk -> +/-200mV)
	CsChanCfg.u32Impedance    = 1000000;             //1 MOhm impedance
	CsChanCfg.i32DcOffset     = 0;                   //no offset
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);
}

void	Gage_Setup_Chan_B ( int pk_pk_range_in_mV )
{
	//Setup Gage CHAN_B
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 2;                //Channel B
	CsChanCfg.u32Term = CS_COUPLING_DC;           //GAGE_DC
	CsChanCfg.u32InputRange = pk_pk_range_in_mV ; //Example: 10000 = 5Vp-p
	CsChanCfg.u32Impedance = 1000000;             //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;                    //no offset
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);
	//must be followed by ACTION_COMMIT to send settings to Hardware.
}



int gage_input_control_xp (int16 channel, int16 enable, int16 coupling, int16 gain)
{
	//Setup Gage CHAN_B
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	if (channel==GAGE_CHAN_A)
		CsChanCfg.u32ChannelIndex = 1;                //Channel A
	else
		CsChanCfg.u32ChannelIndex = 2;                //Channel B
	////Fixed DC coupling
	CsChanCfg.u32Term = CS_COUPLING_DC;           //GAGE_DC
	//Set range
	if (gain == GAGE_PM_5_V)
		CsChanCfg.u32InputRange = 10000 ; //Example: 10000 = 5Vp-p
	if (gain == GAGE_PM_2_V)
		CsChanCfg.u32InputRange = 4000 ; //Example: 4000 = 2Vp-p
	if (gain == GAGE_PM_1_V)
		CsChanCfg.u32InputRange = 2000 ; //Example: 10000 = 5Vp-p
	if (gain == GAGE_PM_500_MV)
		CsChanCfg.u32InputRange = 1000 ; //Example: 10000 = 5Vp-p
	if (gain == GAGE_PM_200_MV)
		CsChanCfg.u32InputRange = 400 ; //Example: 10000 = 5Vp-p
	if (gain == GAGE_PM_100_MV)
		CsChanCfg.u32InputRange = 200 ; //Example: 10000 = 5Vp-p
	
	CsChanCfg.u32Impedance = 1000000;			//Fixed 1 MOhm impedance        
	CsChanCfg.i32DcOffset = 0;					//no offset
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);		//must be followed by ACTION_COMMIT to send settings to Hardware.
	i32Status = CsDo(hSystem, ACTION_COMMIT);	//Send settings to Hardware.

	if (i32Status>0)
		return 1;	//success
	else
		return 0;
}

//** gage_trigger_control_xp **
//int		gage_trigger_control_xp (int16 source, int16 ext_coupling, int16 ext_gain, int16 slope, int16 level_in_volts, int32 depth)
int		gage_trigger_control_xp (int16 source, int16 ext_coupling, int16 ext_gain, int16 slope, float level_in_volts, int32 depth)
{
	//CSTRIGGERCONFIG CsTrigCfg;
	CsTrigCfg.u32Size				= sizeof(CSTRIGGERCONFIG);
	CsTrigCfg.u32TriggerIndex		= 1;	//should always be 1
	//source
	if ( source == GAGE_EXTERNAL )
		CsTrigCfg.i32Source          = CS_TRIG_SOURCE_EXT;  //Channel A
	else if ( source == GAGE_CHAN_A )
		CsTrigCfg.i32Source          = CS_TRIG_SOURCE_CHAN_1;  //Channel A
	else if ( source == GAGE_CHAN_B )
		CsTrigCfg.i32Source          = CS_TRIG_SOURCE_CHAN_2;  //Channel B

	//coupling
	if ( ext_coupling == GAGE_DC )
		CsTrigCfg.u32ExtCoupling     = CS_COUPLING_DC;	       //GAGE_DC

	//ext trig range
	if ( ext_gain == GAGE_PM_10_V )
		CsTrigCfg.u32ExtTriggerRange = 20000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_5_V )
		CsTrigCfg.u32ExtTriggerRange = 10000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_2_V )
		CsTrigCfg.u32ExtTriggerRange = 4000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_1_V )
		CsTrigCfg.u32ExtTriggerRange = 2000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_500_MV )
		CsTrigCfg.u32ExtTriggerRange = 1000;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_200_MV )
		CsTrigCfg.u32ExtTriggerRange = 400;  //pk_pk_range_in_mV 
	else if ( ext_gain == GAGE_PM_100_MV )
		CsTrigCfg.u32ExtTriggerRange = 200;  //pk_pk_range_in_mV 

	//slope
	if ( slope == GAGE_POSITIVE )
    	CsTrigCfg.u32Condition       = CS_TRIG_COND_POS_SLOPE; //GAGE_POSITIVE
	else
    	CsTrigCfg.u32Condition       = CS_TRIG_COND_NEG_SLOPE; //GAGE_NEGATIVE

	//Trigger level as a percentage of the trigger source input range, 0% is 0V, 100% is full scale positive
	//source
	if ( source == GAGE_EXTERNAL )
		//Set external trigger level (percent of range_in_millivolts/2)
		CsTrigCfg.i32Level           = (100* (int)(level_in_volts * 1000)) / (CsTrigCfg.u32ExtTriggerRange/2);	
	else if ( source == GAGE_CHAN_A )
	{
		//Find Chan A range
		CsChanCfg.u32ChannelIndex = 1;                //Channel A
		CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		//Set Chan A trigger level (percent of range_in_millivolts/2)
		CsTrigCfg.i32Level           = (100* (int)(level_in_volts * 1000)) / (CsChanCfg.u32InputRange/2);	
	}
	else if ( source == GAGE_CHAN_B )
	{
		//Find Chan B range
		CsChanCfg.u32ChannelIndex = 2;                //Channel B
		CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		//Set Chan B trigger level (percent of range_in_millivolts/2)
		CsTrigCfg.i32Level           = (100* (int)(level_in_volts * 1000)) / (CsChanCfg.u32InputRange/2);	
	}

	//Set trigger values
	CsSet(hSystem, CS_TRIGGER, &CsTrigCfg);

	//Set Acquisition depth
	CsAcqCfg.i64Depth       = depth-CsAcqCfg.i64TriggerHoldoff;             
	CsAcqCfg.i64SegmentSize = CsAcqCfg.i64Depth+CsAcqCfg.i64TriggerHoldoff;
	CsSet(hSystem, CS_ACQUISITION, &CsAcqCfg);

	
	//Note: must be followed by ACTION_COMMIT to send settings to Hardware.
	i32Status = CsDo(hSystem, ACTION_COMMIT);

	Gage_print_error("gage_trigger_control_xp");

	if (i32Status>0)
		return 1;	//success
	else
		return 0;
}



void	Gage_Commit ( void )	//Send to hardware
{
	i32Status = CsDo(hSystem, ACTION_COMMIT); //Necessary to send settings to Hardware.
}


void	Gage_Start_Capture( void )
{	//Begin Data Capture
	i32Status = CsDo(hSystem, ACTION_START);

}


void	Gage_Wait_For_Capture_Complete( void )
{	//capture wait loop after capture has been started, Gage_trig_ok,Gage_data_ok status is set
	int gageStatus=-1,icnt;

	//Get starting time stamp
	timenow[2] = mytimer.GetElapsedTime();
	starttime = timenow[2];

	//Retrieve initial Capture Status.
	i32Status = CsGetStatus(hSystem);
	Sleep(0);
	//if (i32Status==0)printf("initial i32Status=0\n");

   	//Wait until ACQ_STATUS_READY is true

	int  while_flag = 1; //To prevent infinite loop.
	while (while_flag && (i32Status != ACQ_STATUS_READY))
	{
		stoptime = mytimer.GetElapsedTime();
		i32Status = CsGetStatus(hSystem);
		Sleep(0);
		if((float)(stoptime-starttime) >=30000)	//30000=30ms
		{
			CsDo(hSystem, ACTION_FORCE);	//Force capture.
			printf("\nGage Forced capture\n");
			for (icnt=0;icnt<=150;icnt++)
			{	
				wait.delay_10_us(10);			//wait for forced capture to end
				gageStatus = CsGetStatus(hSystem);
				if (gageStatus == ACQ_STATUS_READY)
					break;
			}
			while_flag = 0; //condition to exit loop.
		}
	}

	//calculate capture time
	stoptime = mytimer.GetElapsedTime();
	float temp_1 = float(stoptime-starttime);
	int debug_capture=0;
	if (debug_capture){
		printf("acquisition time= %8.3f ms, Status=%i \n",temp_1/1000.0,i32Status);
	}

	if (i32Status == ACQ_STATUS_READY) {	//0=ACQ_STATUS_READY, 1=ACQ_STATUS_WAIT_TRIGGER
		//change variable here to match rest of program
		trig_ok = TRUE;
		//Gage_trig_ok = TRUE;
		//Gage_data_ok = TRUE;
	}
	else {
		//capture was forced
		//change variable here to match rest of program
		trig_ok = FALSE;
		//Gage_trig_ok = FALSE;
		//Gage_data_ok = FALSE;
	}

}


void Gage_Transfer_Data ( int channel_num )
{	
	int i;
	int icnt; 
	//Acquisition is now complete. 
	//Fill in the InData structure for transferring the data
	//Non multiple record captures should have the segment set to 1.
	//InData.u32Mode refers to the transfer mode. Regular transfer is 0

	InData.u32Segment = 1;
	if (channel_num == GAGE_CHAN_A)
		InData.u16Channel = GAGE_CHAN_A;	//Channel A
	else
		InData.u16Channel = GAGE_CHAN_B;	//Channel B

	InData.u32Mode = TxMODE_DEFAULT;

  	//min start Address. (TriggerDelay=0,i64Depth=samples,i64SegmentSize=samples
	i64MinSA = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Set starting address for transfer (relative to trigger address)
	InData.i64StartAddress = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Transfer a little more than we need so we're sure to get what we requested, regardless of any hw alignment issuses
	InData.i64Length =  CsAcqCfg.i64SegmentSize + i64Padding;

	//Input data is chan_a_16_raw
	if (channel_num == GAGE_CHAN_A)
		InData.pDataBuffer = chan_a_16_raw;
	else
		InData.pDataBuffer = chan_b_16_raw;

	//clear memory
	if (channel_num == GAGE_CHAN_A)
		ZeroMemory(chan_a_16_raw,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD));
	else
		ZeroMemory(chan_b_16_raw,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD));

	// QMc 02-21-13
	// Initialize Gage_chan_a and Gage_chan_b, so the data from the previous unit can't be used for current testing unit
	if (channel_num == GAGE_CHAN_A)
	{
		for (icnt=0; icnt<GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD; icnt ++)
		{
			Gage_chan_a_voltage[icnt] =0.0;
		}
	}
	else if (channel_num == GAGE_CHAN_B)
	{
		for (icnt=0; icnt<GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD; icnt ++)
		{
			Gage_chan_b_voltage[icnt] =0.0;
		}
	}


	//Set Channel for transfer
	if (channel_num == GAGE_CHAN_A)
		i = 1; //CHAN A Only.
	else
		i = 2; //CHAN B Only.

	InData.u16Channel = (uInt16)i;

	//** CsTransfer **
	//Transfer the captured data
	//Note: InData contains data buffer pointer in memory, OutData contains data position adjustments 
	i32Status = CsTransfer(hSystem, &InData, &OutData);
	if (i32Status == -80 )
		printf ("CsTransfer: CS_CHANNEL_PROTECT_FAULT		-80	\nIncomplete acquisition due to user Abort request or Channel Proctection Fault.\n");
	if (i32Status != CS_SUCCESS ) {
		Gage_print_error("CsTransfer ");
		//Gage_print_setup();
		CsChanCfg.u32ChannelIndex = 1;	//Chan A
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		CsChanCfg_B.u32ChannelIndex = 2;	//Chan B
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg_B);
		CsChanCfg.u32ChannelIndex = i;	//restore
		i32Status = CsGet(hSystem, CS_ACQUISITION, CS_CURRENT_CONFIGURATION, &CsAcqCfg);
		i32Status = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &CsTrigCfg);

		return;
	}

	//Gather up the information needed for the volt conversion and/or file header
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = i;
	CsGet(hSystem, CS_CHANNEL, CS_ACQUISITION_CONFIGURATION, &CsChanCfg);
	i64StartOffset = InData.i64StartAddress - OutData.i64ActualStart;
	if (i64StartOffset < 0)
	{
		i64StartOffset = 0;
		InData.i64StartAddress = OutData.i64ActualStart;
	}

	//Save the smaller of the requested transfer length or the actual transferred length
	i64SavedLength = CsAppData.i64TransferLength <= OutData.i64ActualLength ? CsAppData.i64TransferLength : OutData.i64ActualLength;
	i64SavedLength -= i64StartOffset;

	//** ConvertToVolts **
	//Call the ConvertToVolts function. This function will convert the raw
	//data to voltages. We pass the buffer plus the actual start, which will be converted
	//from 0 to actual length in the volts buffer.  
	//PI's method:
	if (channel_num == GAGE_CHAN_A)
		//Channel A
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_a_16_raw, Gage_chan_a_voltage);
	else
		//Channel B
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_b_16_raw, Gage_chan_b_voltage);

	//Save to file (not coded yet)
	int save_to_file=0;
	if (save_to_file)
	{
	}

}	//end of Gage_Transfer_Data()


void Gage_Transfer_DataM ( int channel_num )
{	
	int i;
	int icnt; 
	//Acquisition is now complete. 
	//Fill in the InData structure for transferring the data
	//Non multiple record captures should have the segment set to 1.
	//InData.u32Mode refers to the transfer mode. Regular transfer is 0

	InData.u32Segment = 1;
	if (channel_num == GAGE_CHAN_A)
		InData.u16Channel = GAGE_CHAN_A;	//Channel A
	else
		InData.u16Channel = GAGE_CHAN_B;	//Channel B

	InData.u32Mode = TxMODE_DEFAULT;

  	//min start Address. (TriggerDelay=0,i64Depth=samples,i64SegmentSize=samples
	i64MinSA = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Set starting address for transfer (relative to trigger address)
	InData.i64StartAddress = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Transfer a little more than we need so we're sure to get what we requested, regardless of any hw alignment issuses
	InData.i64Length =  CsAcqCfg.i64SegmentSize + i64Padding;

	//Input data is chan_a_16_raw
	if (channel_num == GAGE_CHAN_A)
		InData.pDataBuffer = chan_a_16_rawM;
	else
		InData.pDataBuffer = chan_b_16_rawM;

	//clear memory
	if (channel_num == GAGE_CHAN_A)
		ZeroMemory(chan_a_16_rawM,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD));
	else
		ZeroMemory(chan_b_16_rawM,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD));

	// QMc 02-21-13
	// Initialize Gage_chan_a and Gage_chan_b, so the data from the previous unit can't be used for current testing unit
	if (channel_num == GAGE_CHAN_A)
	{
		for (icnt=0; icnt<GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD; icnt ++)
		{
			Gage_chan_a_voltageM[icnt] =0.0;
		}
	}
	else if (channel_num == GAGE_CHAN_B)
	{
		for (icnt=0; icnt<GAGE_WAVEFORM_BUFFER_SIZE_18kHz + GAGE_WAVEFORM_BUFFER_PAD; icnt ++)
		{
			Gage_chan_b_voltageM[icnt] =0.0;
		}
	}


	//Set Channel for transfer
	if (channel_num == GAGE_CHAN_A)
		i = 1; //CHAN A Only.
	else
		i = 2; //CHAN B Only.

	InData.u16Channel = (uInt16)i;

	//** CsTransfer **
	//Transfer the captured data
	//Note: InData contains data buffer pointer in memory, OutData contains data position adjustments 
	i32Status = CsTransfer(hSystem, &InData, &OutData);
	if (i32Status == -80 )
		printf ("CsTransfer: CS_CHANNEL_PROTECT_FAULT		-80	\nIncomplete acquisition due to user Abort request or Channel Proctection Fault.\n");
	if (i32Status != CS_SUCCESS ) {
		Gage_print_error("CsTransfer ");
		//Gage_print_setup();
		CsChanCfg.u32ChannelIndex = 1;	//Chan A
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		CsChanCfg_B.u32ChannelIndex = 2;	//Chan B
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg_B);
		CsChanCfg.u32ChannelIndex = i;	//restore
		i32Status = CsGet(hSystem, CS_ACQUISITION, CS_CURRENT_CONFIGURATION, &CsAcqCfg);
		i32Status = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &CsTrigCfg);

		return;
	}

	//Gather up the information needed for the volt conversion and/or file header
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = i;
	CsGet(hSystem, CS_CHANNEL, CS_ACQUISITION_CONFIGURATION, &CsChanCfg);
	i64StartOffset = InData.i64StartAddress - OutData.i64ActualStart;
	if (i64StartOffset < 0)
	{
		i64StartOffset = 0;
		InData.i64StartAddress = OutData.i64ActualStart;
	}

	//Save the smaller of the requested transfer length or the actual transferred length
	i64SavedLength = CsAppData.i64TransferLength <= OutData.i64ActualLength ? CsAppData.i64TransferLength : OutData.i64ActualLength;
	i64SavedLength -= i64StartOffset;

	//** ConvertToVolts **
	//Call the ConvertToVolts function. This function will convert the raw
	//data to voltages. We pass the buffer plus the actual start, which will be converted
	//from 0 to actual length in the volts buffer.  
	//PI's method:
	if (channel_num == GAGE_CHAN_A)
		//Channel A
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_a_16_rawM, Gage_chan_a_voltageM);
	else
		//Channel B
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_b_16_rawM, Gage_chan_b_voltageM);

	//Save to file (not coded yet)
	int save_to_file=0;
	if (save_to_file)
	{
	}

}	//end of Gage_Transfer_Data()


void Gage_Transfer_Data_ilim_states ( int channel_num )
{
	int i;
	//Acquisition is now complete. 
	//Fill in the InData structure for transferring the data
	//Non multiple record captures should have the segment set to 1.
	//InData.u32Mode refers to the transfer mode. Regular transfer is 0

	InData.u32Segment = 1;
	if (channel_num == GAGE_CHAN_A)
		InData.u16Channel = GAGE_CHAN_A;	//Channel A
	else
		InData.u16Channel = GAGE_CHAN_B;	//Channel B

	InData.u32Mode = TxMODE_DEFAULT;

  	//min start Address. (TriggerDelay=0,i64Depth=samples,i64SegmentSize=samples
	i64MinSA = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Set starting address for transfer (relative to trigger address)
	InData.i64StartAddress = CsAcqCfg.i64TriggerDelay + CsAcqCfg.i64Depth - CsAcqCfg.i64SegmentSize;

	//Transfer a little more than we need so we're sure to get what we requested, regardless of any hw alignment issuses
	InData.i64Length =  CsAcqCfg.i64SegmentSize + i64Padding;

	//Input data is chan_a_16_raw
	if (channel_num == GAGE_CHAN_A)
		InData.pDataBuffer = chan_aa_16_raw;
	else
		InData.pDataBuffer = chan_bb_16_raw;

	//clear memory
	if (channel_num == GAGE_CHAN_A)
		ZeroMemory(chan_aa_16_raw,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD));
	else
		ZeroMemory(chan_bb_16_raw,(size_t)(GAGE_WAVEFORM_BUFFER_SIZE + GAGE_WAVEFORM_BUFFER_PAD));


	//Set Channel for transfer
	if (channel_num == GAGE_CHAN_A)
		i = 1; //CHAN A Only.
	else
		i = 2; //CHAN B Only.

	InData.u16Channel = (uInt16)i;

	//** CsTransfer **
	//Transfer the captured data
	//Note: InData contains data buffer pointer in memory, OutData contains data position adjustments 
	i32Status = CsTransfer(hSystem, &InData, &OutData);
	if (i32Status == -80 )
		printf ("CsTransfer: CS_CHANNEL_PROTECT_FAULT		-80	\nIncomplete acquisition due to user Abort request or Channel Proctection Fault.\n");
	if (i32Status != CS_SUCCESS ) {
		Gage_print_error("CsTransfer ");
		//Gage_print_setup();
		CsChanCfg.u32ChannelIndex = 1;	//Chan A
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
		CsChanCfg_B.u32ChannelIndex = 2;	//Chan B
		i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg_B);
		CsChanCfg.u32ChannelIndex = i;	//restore
		i32Status = CsGet(hSystem, CS_ACQUISITION, CS_CURRENT_CONFIGURATION, &CsAcqCfg);
		i32Status = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &CsTrigCfg);
		return;
	}


	//Gather up the information needed for the volt conversion and/or file header
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = i;
	CsGet(hSystem, CS_CHANNEL, CS_ACQUISITION_CONFIGURATION, &CsChanCfg);
	i64StartOffset = InData.i64StartAddress - OutData.i64ActualStart;
	if (i64StartOffset < 0)
	{
		i64StartOffset = 0;
		InData.i64StartAddress = OutData.i64ActualStart;
	}

	//Save the smaller of the requested transfer length or the actual transferred length
	i64SavedLength = CsAppData.i64TransferLength <= OutData.i64ActualLength ? CsAppData.i64TransferLength : OutData.i64ActualLength;
	i64SavedLength -= i64StartOffset;

	//** ConvertToVolts **
	//Call the ConvertToVolts function. This function will convert the raw
	//data to voltages. We pass the buffer plus the actual start, which will be converted
	//from 0 to actual length in the volts buffer.  
	//PI's method:
	if (channel_num == GAGE_CHAN_A)
		//Channel A
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_aa_16_raw, Gage_chan_aa_voltage);
	else
		//Channel B
		i32Status = CsAs_ConvertToVolts(i64SavedLength, CsChanCfg.u32InputRange, CsAcqCfg.u32SampleSize,
											CsAcqCfg.i32SampleOffset, CsAcqCfg.i32SampleRes, 
											CsChanCfg.i32DcOffset, chan_bb_16_raw, Gage_chan_bb_voltage);

	//Save to file (not coded yet)
	int save_to_file=0;
	if (save_to_file)
	{
	}

}	//end of Gage_Transfer_Data_ilim_states()


void Gage_print_error(string text_str)
{
	//Print the Gage error status to the console (DOS) window
	//use if return value <0 for CsDo,CsFreeSystem,CsGet,CsGetStatus,CsGetSystem,CsInitialize,CsSet,CsTransfer
	if ((debug_gage_error) && (i32Status<0)){
		char return_string2[40]=" ";
		CsGetErrorString(i32Status,return_string2,40);
		printf("Gage Error Status (%s): %s\n",text_str.c_str(),return_string2);
	}
}


void Gage_print_setup(string text_str)
{
	//Print the Gage settings to the Console (DOS) Window
	printf("Gage Status (%s):\n",text_str.c_str());
	i32Status = CsGet(hSystem, CS_ACQUISITION, CS_ACQUISITION_CONFIGURATION, &CsAcqCfg);
	printf("  Sample Size= %i \n",CsAcqCfg.i64Depth		);
	printf("  Sample Rate= %i Msa/sec\n",CsAcqCfg.i64SampleRate /1000000		);
	
	CsChanCfg.u32ChannelIndex = 1;      //Channel A
	i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
	printf("  Chan A Input Range (mV,pk-pk)= %i\n",CsChanCfg.u32InputRange 		);
	int chan_a_rng=CsChanCfg.u32InputRange;
	CsChanCfg.u32ChannelIndex=2;//chan b
	i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
	printf("  Chan B Input Range (mV,pk-pk)= %i\n",CsChanCfg.u32InputRange 		);
	int chan_b_rng=CsChanCfg.u32InputRange;


	i32Status = CsGet(hSystem, CS_TRIGGER, CS_CURRENT_CONFIGURATION, &CsTrigCfg);
	if (CsTrigCfg.i32Source == 1)
	{
		printf("  Trigger source= CHAN_1\n"	);
		printf("  Trig Level (percentage of half the full scale range)= %i %%\n",CsTrigCfg.i32Level 		);
		printf("  Trig Level = %6.0f mV\n",((float)CsTrigCfg.i32Level/100)*((float)chan_a_rng/2) 	);
	}
	if (CsTrigCfg.i32Source == 2)
	{
		printf("  Trigger source= CHAN_2\n");
		printf("  Trig Level (percentage of half the full scale range)= %i %%\n",CsTrigCfg.i32Level 		);
		printf("  Trig Level = %6.0f mV\n",((float)CsTrigCfg.i32Level/100)*((float)chan_b_rng/2) 	);
	}
	if (CsTrigCfg.i32Source == -1)
	{
		printf("  Trigger source= EXTERNAL\n"	);
		printf("  Ext Trig Full Scale Range (mV)= %i\n",CsTrigCfg.u32ExtTriggerRange 		);
		printf("  Ext Trig Level (percentage of half the full scale range)= %i %%\n",CsTrigCfg.i32Level 		);
		printf("  Ext Trig Level = %6.0f mV\n",((float)CsTrigCfg.i32Level/100)*((float)CsTrigCfg.u32ExtTriggerRange/2) 	);
	}
}


int		Gage_loadtime_setup (void)
{
/*	Initializes all the CompuScope boards found in the system.  The routine
	attempts to read the GAGESCOP.INC configuration file to find out the memory
	segment and I/O addresses of the boards. The routine also updates several tables
	and structures depending upon the board type that is found.
*/
//Call InitBoard only once


//	uInt32					i;
	//LPCTSTR					szIniFile = _T("Acquire.ini");	
	int64					i64Padding = 64; //extra samples to capture to ensure we get what we ask for



/*
	Initializes the CompuScope boards found in the system. If the
	system is not found a message with the error code will appear.
	Otherwise i32Status will contain the number of systems found.
*/
	i32Status = CsInitialize();

	if (CS_FAILED(i32Status))
	{
		//MessageBox(NULL, str, "Razor Digitizer Fails to Initialize", MB_OK);
		MessageBox(NULL,"Digitizer FAILS TO INITIATE!","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		
	}

	//Obtain the handle to the first Compuscope in the system
	i32Status = CsGetSystem(&hSystem, 0, 0, 0, 0);


	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Fails to Obtain Digitizer Handle!","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);		
	}

/*
	Get System information. The u32Size field must be filled in
	 prior to calling CsGetSystemInfo
*/
	CsSysInfo.u32Size = sizeof(CSSYSTEMINFO);
	i32Status = CsGetSystemInfo(hSystem, &CsSysInfo);


/*
	Display the system name from the driver
*/
	_ftprintf(stdout, _T("\nDigitizer Type: %s\n"), CsSysInfo.strBoardName);  //Display Razor Model


	//Set CHANA, CHANB, Trigger for Razor
	
	//Set Dual Mode.
 	//CSACQUISITIONCONFIG CsAcqCfg

	CsAcqCfg.u32Size = sizeof(CsAcqCfg);
	i32Status = CsGet(hSystem, CS_ACQUISITION, CS_ACQUISITION_CONFIGURATION, &CsAcqCfg);

	//Set Dual Mode.
 	//CSACQUISITIONCONFIG CsAcqCfg;
	CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
	CsAcqCfg.u32Mode = CS_MODE_DUAL;     //Dual Mode.
	CsAcqCfg.i64SampleRate = 50000000;    //50Mhz
	CsAcqCfg.i64Depth = 8192-CsAcqCfg.i64TriggerHoldoff;             //8K
	CsAcqCfg.i64SegmentSize = CsAcqCfg.i64Depth+CsAcqCfg.i64TriggerHoldoff;
	CsAcqCfg.u32SegmentCount = 1;
	CsAcqCfg.i64TriggerTimeout = 10000000;
	CsAcqCfg.u32ExtClk = 0;


	i32Status = CsDo(hSystem, ACTION_COMMIT);

	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Error while setting Dual Mode.","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		CsFreeSystem(hSystem);
	}
/*
	Get the current sample size, resolution and offset parameters from the driver
	by calling CsGet for the ACQUISTIONCONFIG structure. These values are used
	when saving the file.
*/
	CsAcqCfg.u32Size = sizeof(CSACQUISITIONCONFIG);
	i32Status = CsGet(hSystem, CS_ACQUISITION, CS_ACQUISITION_CONFIGURATION, &CsAcqCfg);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Fails to get the configured Dual Mode parameters from driver!","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		CsFreeSystem(hSystem);
	}


	//Set CHANA to 200mV Range with 1Mohm Impedance.
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg_B.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 1;      //Channel A
	CsChanCfg.u32Term = CS_COUPLING_DC; //GAGE_DC
	CsChanCfg.u32InputRange = 400;      //200mVp-p
	CsChanCfg.u32Impedance = 1000000;   //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);

	i32Status = CsDo(hSystem, ACTION_COMMIT);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Error while setting CHAN A Input Control.","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		CsFreeSystem(hSystem);
	}

	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Fails to get the configured CHAN A parameters from driver!","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		CsFreeSystem(hSystem);
	}


		//Set CHANB to 5V Range with 1Mohm Impedance.
	//CSCHANNELCONFIG CsChanCfg;
	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	CsChanCfg.u32ChannelIndex = 2;      //Channel B
	CsChanCfg.u32Term = CS_COUPLING_DC; //GAGE_DC
	CsChanCfg.u32InputRange = 10000;      //5Vp-p
	CsChanCfg.u32Impedance = 1000000;   //1 MOhm impedance
	CsChanCfg.i32DcOffset = 0;
	CsSet(hSystem, CS_CHANNEL, &CsChanCfg);
	
	i32Status = CsDo(hSystem, ACTION_COMMIT);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Error while setting CHB Input Control.","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		CsFreeSystem(hSystem);
	}

	CsChanCfg.u32Size = sizeof(CSCHANNELCONFIG);
	i32Status = CsGet(hSystem, CS_CHANNEL, CS_CURRENT_CONFIGURATION, &CsChanCfg);
	if (CS_FAILED(i32Status))
	{
		MessageBox(NULL,"Fails to get the configured CHAN B      parameters from driver!","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		CsFreeSystem(hSystem);
	}


/*
	We need to allocate a buffer
	for transferring the data
*/

	CsAppData.i64TransferLength = GAGE_WAVEFORM_BUFFER_SIZE;

	pBuffer  = VirtualAlloc(NULL, (size_t)((CsAppData.i64TransferLength + i64Padding) * CsAcqCfg.u32SampleSize), MEM_COMMIT, PAGE_READWRITE);

  
	if (NULL == pBuffer)
	{
		//_ftprintf (stderr, _T("\nUnable to allocate memory\n"));
		MessageBox(NULL,"Unable to allocate memory!","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		CsFreeSystem(hSystem);
	}

	if (TYPE_FLOAT == CsAppData.i32SaveFormat)
	{
/*
		Allocate another buffer to pass the data that is going to be converted
		into voltages
*/
		pVBuffer  = (float *)VirtualAlloc(NULL, (size_t)(CsAppData.i64TransferLength * sizeof(float)), MEM_COMMIT, PAGE_READWRITE);

		if (NULL == pVBuffer)
		{
			//_ftprintf (stderr, _T("\nUnable to allocate memory\n"));
			MessageBox(NULL,"Unable to allocate memory!","Error", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
			CsFreeSystem(hSystem);
			VirtualFree(pBuffer, 0, MEM_RELEASE);
			
		}
	}

  return (0);

}       /*  End of Gage_loadtime_setup ().  */


void	Gage_cal_table_setup_xp()
{
	//Force Gage Calibration
	//This routine calibrates Chan A at 4 settings and Chan B at 4 settings
	//The user can comment out the unescessary ranges
	//run this routine at program load time
	//Note: Gage will automatically run calibration at EVERY input change for the first 20 minutes after system boot-up

	//Set input voltage range, +/-500mV
	Gage_Setup_Chan_A (1000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-1V
	Gage_Setup_Chan_A (2000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-2V
	Gage_Setup_Chan_A (4000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-5V
	Gage_Setup_Chan_A (10000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//B input settings
	//Set input voltage range, +/-500mV
	//Gage_Setup_Chan_B (1000);					//pk_pk_range_in_mV (int)
	//CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	//Delay(100);
	//i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	//Delay(250);
	//if (i32Status<0) Gage_print_error("Gage Cal Error");

	////Set input voltage range, +/-1V
	//Gage_Setup_Chan_B (2000);					//pk_pk_range_in_mV (int)
	//CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	//Delay(100);
	//i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	//Delay(250);
	//if (i32Status<0) Gage_print_error("Gage Cal Error");

	////Set input voltage range, +/-2V
	//Gage_Setup_Chan_B (4000);					//pk_pk_range_in_mV (int)
	//CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	//Delay(100);
	//i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	//Delay(250);
	//if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-5V
	Gage_Setup_Chan_B (10000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	//Set input voltage range, +/-10V
	Gage_Setup_Chan_B (20000);					//pk_pk_range_in_mV (int)
	CsDo(hSystem, ACTION_COMMIT);				//Send settings to Hardware.
	Delay(100);
	i32Status = CsDo(hSystem,ACTION_CALIB);		//force calibration
	Delay(250);
	if (i32Status<0) Gage_print_error("Gage Cal Error");

	debug_test_time=0;
	if (debug_test_time)
	{
		initial_time = mytimer.GetElapsedTime();	// start trimming
		Gage_Setup_Chan_A(2000);	Gage_Commit();	PrintCaptureTime("Gage_cal_setup, after Gage_Setup_Chan_A complete");
		Gage_Setup_Chan_B(1000);	Gage_Commit();	PrintCaptureTime("Gage_cal_setup, after Gage_Setup_Chan_B complete");
		Gage_Setup_Chan_A(10000); 	Gage_Commit();	PrintCaptureTime("Gage_cal_setup, after Gage_Setup_Chan_A complete");
		Gage_Setup_Chan_B(10000);	Gage_Commit();	PrintCaptureTime("Gage_cal_setup, after Gage_Setup_Chan_B complete");
		debug_test_time=0;
	}

}

void PrintCaptureTime(string text_str)
{
	double elapsed_time;
	if (!debug_test_time)
		return;
	current_time = mytimer.GetElapsedTime();	// start trimming
	elapsed_time = (double)(current_time-initial_time)/1e6;// elapsed time
	printf("Elapsed Capture Time, %s: %6.0f msec\n",text_str.c_str(),	elapsed_time*1e3);

	return;
}

//=================== XP gage digitizer Setup Codes ENDS here ===================

char* GetCSVPath (const char* dllpath, const char* csvname)
{
  size_t len = strlen(dllpath) + strlen(csvname) + 1;  // little more space than should need
  char* csvpath = (char*) calloc((len + 1), sizeof(char));
  strncpy(csvpath, dllpath, len);
  char* bs1 = strrchr(csvpath,'\\');
  *bs1 = '\0';  // replace right most backslash with string terminator
  char* bs2 = strrchr(csvpath,'\\');
  *bs2 = '\0';  // replace 2nd from right backslash with string terminator
  strncat(csvpath, "\\Programs\\",(len - strlen(csvpath)));
  strncat(csvpath, csvname, (len - strlen(csvpath)));
  return(csvpath);
}

bool PIPulse::do_pulse(void)
{
	//do_pulse() provides a debug pulse on J1B9
	Dvi *Pulse_dvi = dvi_9;
	//Read initial data
	unsigned short regData = Pulse_dvi->card.adc_val;

	if ( pulse_width_in_seconds < 10e-6)
		pulse_width_in_seconds=10e-6;
	
	if ( pulse_width_in_seconds > 10e-3)
		pulse_width_in_seconds=10e-3;
	
	// Set Ext Clock Low
	regData &= ~DUT_NVRAM_CK;

	//Output low
	outport(Pulse_dvi->base, regData);
	Pulse_dvi->card.adc_val = regData;

	// Set Ext Clock High
	regData |= DUT_NVRAM_CK;

	//Output high
	outport(Pulse_dvi->base, regData);
	Pulse_dvi->card.adc_val = regData;

	//Pulse width
	wait.delay_10_us((unsigned long) (pulse_width_in_seconds*1e5));

	// Set Ext Clock Low
	regData &= ~DUT_NVRAM_CK;

	//Output low
	outport(Pulse_dvi->base, regData);
	Pulse_dvi->card.adc_val = regData;
	
	return true;
}

void IS_250mA_Sequence(int Seq, int xTimes, int dly)
{
	float IS_Current;
	int i=0;

	IS_Current = 0.35;

	for(i=0; i < xTimes; i++)
	{
		if(Seq == -1) //Decrease Sequence "3,3,3,1,1,5" of 250mA
		{
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(3*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(3*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(3*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(1*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(1*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(5*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
		}
		else		//Increase Sequence "1,1,3,3,3,5" of IS_Current
		{
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(1*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(1*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(3*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(3*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(3*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
			delay(5*dly);
			FWC_dvi2k->set_current(FWC_ch, 0.0,			RANGE_2_A);
			delay(dly);
			FWC_dvi2k->set_current(FWC_ch, IS_Current,	RANGE_2_A);
		}
	}
}

void VBPP_Power_Up_w_Test_Mode(int TestModeSelect, int ILIM_Mode)
{
	Pulse pulse(PULSE_RISING_EDGE,10e-6);
	
	//TestMode1 selected
	//	- Speed up everything by 32x.  Expect ~2.5ms/~65ms  ON_Time/OFF_Time
	if (TestModeSelect == gTM1_p						||
		TestModeSelect == gTM_OverTemp				||
		TestModeSelect == gTM_Fast_Counter_32x		||
		TestModeSelect == gTM_TonMax1us				||
		TestModeSelect == gTM_Receiver_Threshold	||
		TestModeSelect == gTM1_UVOV_NoDelay				)
	{
			//Drain = 0V
			D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
			D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
			wait.delay_10_us(5);
	}
	//TestMode2 selected
	
	else 
			
	if (TestModeSelect == gTM2_p					||
		TestModeSelect == gTM_Trim_Readable			||
		TestModeSelect == gTM_Jitter_to_Vpin		||
		TestModeSelect == gTM_MaxF_to_Vpin			||
		TestModeSelect == gTM_ILIM					||
		TestModeSelect == gTM2_UVOV_NoDelay				)
	{
			//Drain = 6V
			D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
//			D_dvi->set_voltage(D_ch, 7.0, 		VOLT_50_RANGE);	// DVI_11_0	
			D_dvi->set_voltage(D_ch, 15.0, 		VOLT_50_RANGE);	// DVI_11_0	
			wait.delay_10_us(20);
	}

	if (TestModeSelect == gTM_Jitter_to_Vpin	||
	    TestModeSelect == gTM2_UVOV_NoDelay		)	//45V from Lance
//	    TestModeSelect == gTM1_UVOV_NoDelay    ) //zcx don't think this should be here
	{
			D_dvi->set_voltage(D_ch, 45.0, 		VOLT_50_RANGE);	// DVI_11_0	
			wait.delay_10_us(20);
	}


	if (TestModeSelect == gTM2_UVOV_NoDelay || 
	    TestModeSelect == gTM1_UVOV_NoDelay    ) 
	{
		//UV pin (Vpin) set to 6V/80uA before PU
		VPIN_ovi->set_voltage(VPIN_ch, 6.0,			RANGE_10_V);  
		VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	
	}
	else
	{
		//UV pin (Vpin) set to 0V before PU
		VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_10_V);  
		VPIN_ovi->set_current(VPIN_ch, 20e-3,		RANGE_30_MA);	
	}
	
	//BPP set 0V
	BPP_ovi->set_current(BPP_ch, 15e-3,	RANGE_30_MA);	// Set 2mA here to prevent BPP go into Vshunt for B3 silicon
	//VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);	// Set 2mA here to prevent BPP go into Vshunt for B3 silicon
	BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(5);

	//BPP power-up sequence requires BPP_PV to be a bit higher in order for TM1 to work properly for 8" wafer.  What about TM2?
	//BPP ramp up to VBPP_PV  (Note: DO NOT GO ABOVE 5.5V ON BPP, Above 5.5V might cause damage to device)
	//if( (gVBPP_PV_Init + 75e-3) < 5.5 )
	//	VBPP_ramp_up(3.5, gVBPP_PV_Init+75e-3, 0.2);	// vstart, vstop, vstep		FOR INNO4
	//else
		VBPP_ramp_up(3.5, gVBPP_PV_final, 0.2);	// vstart, vstop, vstep		FOR INNO4

			////Debug
			//BPP_ovi->set_voltage(BPP_ch, 5.5, 	RANGE_10_V);	// OVI_1_0	


	//VBPP_ramp_up(0.0, 5.5, 0.1);	// vstart, vstop, vstep		FOR INNO4
	wait.delay_10_us(5);			
	//if(BPP_4p7uF) delay(3);
	//if(BPP_p47uF) delay(1);

	//TestModeSelect2
	if (TestModeSelect == gTM2_p			||
	    TestModeSelect == gTM_Trim_Readable		||
	    TestModeSelect == gTM_Jitter_to_Vpin	||
	    TestModeSelect == gTM_MaxF_to_Vpin		||
	    TestModeSelect == gTM_ILIM			||
	    TestModeSelect == gTM2_UVOV_NoDelay		)
//	    TestModeSelect == gTM1_UVOV_NoDelay    		) //zcx don't think this should be here
	{
			//Drain = 0V
			D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
			D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
			wait.delay_10_us(5);
	}

	//Additional delay for UVOV testmode
	if(TestModeSelect == gTM2_UVOV_NoDelay ||
	   TestModeSelect == gTM1_UVOV_NoDelay    		) 
		wait.delay_10_us(30);

//	VBPP_ramp_down(gVBPP_P_Init + 0.2, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
	//BPP_ovi->set_current(BPP_ch,  15e-3,	RANGE_30_MA);	// 15mA here so iBPP_minus won't clamp at 2mA from above for B3 silicon
	
	//Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
//	if     (ILIM_Mode == ILIM_NORM)				wait.delay_10_us(2);	//1.0 uF	(ILIM)		25us
	if     (ILIM_Mode == ILIM_NORM)				wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
//	else if(ILIM_Mode == ILIM_RED)				wait.delay_10_us(30);	//0.1 uF	(ILIM-1)	300us
	else if(ILIM_Mode == ILIM_INCR)				wait.delay_10_us(150);	//10  uF	(ILIM+1)	1.2ms

//	if(MOSFET_SIZE==2)	wait.delay_10_us(500);	//addditional delay	for hot

	wait.delay_10_us(1);	//Delay is critical for 1.8A device.  w/o 10us, ILIM read 70mA lower and not as repeatable.

	//TestModeSelect2
	if (TestModeSelect == gTM2_p						||
		TestModeSelect == gTM_Trim_Readable			||
		TestModeSelect == gTM_Jitter_to_Vpin		||
		TestModeSelect == gTM_MaxF_to_Vpin		||
		TestModeSelect == gTM_ILIM			||
		TestModeSelect == gTM2_UVOV_NoDelay		||
		TestModeSelect == gTM1_UVOV_NoDelay			)
	{
			//Drain = 0V
			D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
			D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
	}

	//delay(etime);

	VBPP_ramp_down(gVBPP_M_Init +0.25, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
	BPP_ovi->set_current(BPP_ch,  2e-3,	RANGE_30_MA);				// Before 2nd BPP ramp up clamp to 2mA for B3 silicon
	//BPP_ovi->set_current(BPP_ch,  3e-3,	RANGE_30_MA);				// Before 2nd BPP ramp up clamp to 2mA for B3 silicon
	wait.delay_10_us(10);
	//if(BPP_4p7uF) delay(3);
	//if(BPP_p47uF) delay(1);

	if(gSiliconRev_P>=3)
	{
		//BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//B3 material. Hiep recommended 2mA instead of 3mA
		BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);
		VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
	}
	else
	{
		VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
	}
	wait.delay_10_us(10);

	//TestModeSelect2
	if (TestModeSelect == gTM2_p						||
		TestModeSelect == gTM_Trim_Readable			||
		TestModeSelect == gTM_Jitter_to_Vpin		||
		TestModeSelect == gTM_MaxF_to_Vpin			||
		TestModeSelect == gTM_ILIM							)
	{
			//Drain = 7V	(6V not enough to read the fuse links)
			D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
//			D_dvi->set_voltage(D_ch, 7.0, 		VOLT_50_RANGE);	// DVI_11_0	
			D_dvi->set_voltage(D_ch, 10.0, 		VOLT_50_RANGE);	// DVI_11_0	
			wait.delay_10_us(50);
	}
	else
	{
			//Drain = 2.5V (in DR doc, but 1V would be better for noise)
			D_dvi->set_voltage(D_ch, HANDSHAKE_Vd_TM, 	VOLT_5_RANGE);	// DVI_11_0	
//			wait.delay_10_us(30);										//Require minimum of 300us delay before VBPS pull up to vPlus
	}

	//delay(htime);

	if (TestModeSelect == gTM2_UVOV_NoDelay	||
	    TestModeSelect == gTM1_UVOV_NoDelay		)
	{
			//Drain = 100mV like PH device to lower the noise
//			D_dvi->set_voltage(D_ch, 100e-3, 	VOLT_50_RANGE);	// DVI_11_0	
//			D_dvi->set_voltage(D_ch, 200e-3, 	VOLT_50_RANGE);	// DVI_11_0	
			D_dvi->set_voltage(D_ch, 2.0, 	VOLT_50_RANGE);	// DVI_11_0	
			wait.delay_10_us(5);
	}
	//delay(itime);

//	wait.delay_10_us(220);	// Require for wait and listen first then device will switch
}

void Powerup_Primary_in_Testmode(int Testmodes)
{
	float vDrainPowerup =0;

	//Drain_P set to 0V
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 30.0e-3,		RANGE_30_MA);
	wait.delay_10_us(10);
	
	//Bpp set 5V for 100us
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 200e-3); //BPP ramp up from 0 to 5V with 200mV step

	//Vpin clock
	if(Testmodes == gOT_Mode)	
		Force_Vpin_Pulses_nTimes(4);	//Vpin clock 4 pulses (10us positive) to enter OT mode
	else
	{
		Force_Vpin_Pulses_nTimes(3);	//Vpin clock 3 pulses (10us positive) to enter write mode
		if((LB_Rev >= 5||g_TurretCB) && (OPCODE==4200||OPCODE== 4501))
		{
			wait.delay_10_us(150);
		}
		//Drain setup to be able to see AF links
		vDrainPowerup = 40;
		dvi_11->set_voltage(DVI_CHANNEL_0, vDrainPowerup, VOLT_50_RANGE);
		wait.delay_10_us(150);
	}

	//////Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	////VBPP_ramp_up(5.0, 5.5, 50e-3);		
	////VBPP_ramp_down(5.5, 5, 50e-3);	

	//Bpp ramp from 5V -> gVBPP_PV_final -> 5V with 50mV step
	VBPP_ramp_up	(5.0,				gVBPP_PV_final, 50e-3);
	VBPP_ramp_down	(gVBPP_PV_final,	5.0,				50e-3);	
	if(g_TurretCB || LB_Rev >= 5)
	{
		delay(2);
	}

	switch (Testmodes)
	{
		case gWrite_Mode_ReadAF:
			D_dvi->set_voltage(D_ch, gVread_AF_primary, VOLT_50_RANGE);	//AF Reading vDrain
			break;

		case gWrite_Mode_TrimAF:
			D_dvi->set_voltage(D_ch, gTrim_Voltage, VOLT_50_RANGE);		//AF Trimming vDrain
			break;

		case gObserve_Mode:
			D_dvi->set_voltage(D_ch, 0.0, VOLT_50_RANGE);	//Drain stays at 0V so BPP signal will be cleaner
			wait.delay_10_us(20);
			//BPP set 4.5V for 100us and 5.1V to bring chip back to normal operation
			ovi_1->set_voltage(OVI_CHANNEL_0, 4.2, RANGE_10_V);
			wait.delay_10_us(50);
			ovi_1->set_voltage(OVI_CHANNEL_0, 5.2, RANGE_10_V);
			wait.delay_10_us(30);
			break;

		//case gOT_Mode:
		//	//BPP set 4.5V for 100us and 5.1V to bring chip back to normal operation
		//	ovi_1->set_voltage(OVI_CHANNEL_0, 4.1, RANGE_10_V);
		//	wait.delay_10_us(50);
		//	//Drain set to 2V so device will switch at a low voltage
		//	D_dvi->set_voltage(D_ch, 2.0, VOLT_5_RANGE);
		//	wait.delay_10_us(30);
		//	if(gSiliconRev_P>=3)
		//	{
		//		BPP_ovi->set_current(BPP_ch, 2e-3,	RANGE_30_MA);		//						B3 material
		//		VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
		//		wait.delay_10_us(10);
		//	}
		//	else
		//	{
		//		ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+100e-3, RANGE_10_V);
		//	}
		//	break;

		case gOT_Mode:
			//BPP set 4.5V for 100us and 5.1V to bring chip back to normal operation
			ovi_1->set_voltage(OVI_CHANNEL_0, 4.1, RANGE_10_V);
			wait.delay_10_us(50);
			//Drain set to 2V so device will switch at a low voltage
			D_dvi->set_voltage(D_ch, 2.0, VOLT_5_RANGE);
			wait.delay_10_us(30);
			if(gSiliconRev_P>=3)
			{
				BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//B3 material . HL changed from 2mA to 3mA
				VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
				wait.delay_10_us(10);
			}
			else
			{
				ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+100e-3, RANGE_10_V);
			}
			break;

		default:
			break;
	}
}

void Power_Up_Primary_Observe_Mode(int ObsMode_xx) 
{
	int num_pulses_Vpin = 0;
	int i = 0;
	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	
	VPIN_ovi->set_current(VPIN_ch, 30e-3, RANGE_30_MA);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,   RANGE_5_V);
	wait.delay_10_us(20);
	//Drain (0V/3mA)
	D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
	D_dvi->set_voltage(D_ch, 0, 		VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(20);

	//BPP set 0V
	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	//VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(5);

	//BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
	VBPP_ramp_up(0.0, 5.0, 0.2);	// vstart, vstop, vstep	
	wait.delay_10_us(50);

	VPIN_ovi->disconnect(VPIN_ch);	// Vpin disconnect OVI then below close K16 to connect to 5kohm to DDD-7-1
	//wait.delay_10_us(100); 
	ddd_7->ddd_set_hi_level(4.0);		// Will immediately change to this level upon execution
	ddd_7->ddd_set_lo_level(0.1);		// Will immediately change to this level upon execution 
	//delay(1);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	wait.delay_10_us(10);
	Close_relay(K12);
	delay(5);
	
	////Vpin clock 3 pulses (10us positive) to enter write mode	
	///*Force_Vpin_Pulses_nTimes(3);	*/
	//wait.delay_10_us(10);
	//dvi_11->set_voltage(DVI_CHANNEL_0, 40.0, VOLT_50_RANGE);	//be able to see AF links properly
	//wait.delay_10_us(50);

	if	(ObsMode_xx == gObserve_Mode_DZwindow)			Force_Vpin_Pulses_nTimes(3);	// Clock 3 pulses to help fUB/fLB tests.
	else												Force_Vpin_Pulses_nTimes(2);	// Clock 2 pulses to help fUB/fLB tests.
//	wait.delay_10_us(10);
	wait.delay_10_us(50);	// Increase this wait time help with repeatability
	dvi_11->set_voltage(DVI_CHANNEL_0, 40.0, VOLT_50_RANGE);	//be able to see AF links properly
	wait.delay_10_us(50);
	
	
	//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	VBPP_ramp_up(5.0, 5.5, 50e-3);		
	VBPP_ramp_down(5.5, 5, 50e-3);	

	//Drain stays at 0V so BPP signal will be cleaner
	dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
	wait.delay_10_us(20);

	//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
	//ovi_1->set_voltage(OVI_CHANNEL_0, 4.2, RANGE_10_V);
	VBPP_ramp_down(5.0, gVBPP_M_Init -0.2, 50e-3);	
	wait.delay_10_us(50);
	if(gSiliconRev_P >= 3)
	{
		BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
		VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
		wait.delay_10_us(10);
	}
	else
	{
		ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+50e-3, RANGE_10_V);
		wait.delay_10_us(30);
	}

	//ovi_1->set_voltage(OVI_CHANNEL_0, 5.2, RANGE_10_V);
	//wait.delay_10_us(30);
	if(gSiliconRev_P >= 3)
	{
		if		(ObsMode_xx == gObserve_Mode_Xcontrol_sec)	num_pulses_Vpin = 0;
		else if	(ObsMode_xx == gObserve_Mode_Xlisten)		num_pulses_Vpin = 1;
		else if (ObsMode_xx == gObserve_Mode_XVTurnOn)		num_pulses_Vpin = 2;
		else if (ObsMode_xx == gObserve_Mode_DChUp)			num_pulses_Vpin = 3;
		else if (ObsMode_xx == gObserve_Mode_rcv)			num_pulses_Vpin = 4;
		else if (ObsMode_xx == gObserve_Mode_Pause)			num_pulses_Vpin = 5;
		else if (ObsMode_xx == gObserve_Mode_DSDS)			num_pulses_Vpin = 6;
		else if (ObsMode_xx == gObserve_Mode_OT)			num_pulses_Vpin = 7;
		else if (ObsMode_xx == gObserve_Mode_LatchOff)		num_pulses_Vpin = 8;
		else if (ObsMode_xx == gObserve_Mode_Xoc)			num_pulses_Vpin = 9;
		else if (ObsMode_xx == gObserve_Mode_DZwindow)		num_pulses_Vpin = 10;
		else if (ObsMode_xx == gObserve_Mode_DZwindow2)		num_pulses_Vpin = 10;
		else if (ObsMode_xx == gObserve_Mode_XZfQ)			num_pulses_Vpin = 11;
		else if (ObsMode_xx == gObserve_Mode_HSwindow)		num_pulses_Vpin = 12;
		else if (ObsMode_xx == gObserve_Mode_XRestart)		num_pulses_Vpin = 13;
		else												num_pulses_Vpin = 0;
	}

	for(i=0; i<num_pulses_Vpin; i++)
	{
		ddd_7->ddd_run_pattern(AF_Vpin_Clk_pulse_start,AF_Vpin_Clk_pulse_stop);
		wait.delay_10_us(5);	
	}
//Bring Vpin OVI back
	ovi_1->connect(VPIN_ch);	
	wait.delay_10_us(20);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);  
	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);  
	wait.delay_10_us(10);
	Open_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
	wait.delay_10_us(10);
}

void Power_Up_Primary_BypassWL_TM5(int ILIM_Select)
{
	/******************************************************************************************************
	Rev B silicon implemented new test mode to bypass wait and listen.
	To get into this mode, VPIN is grounded at startup.  BPP then ramps to 5V and 5 clock edges are applied 
	on VPIN.  Then allow BPP to complete the power up sequence.  This is a test time saving mode and should 
	be used to bypass wait and listen time when applicab
	le.
	*******************************************************************************************************/

	// Initialize DDD
	ddd_7->ddd_set_lo_level(0.0);
	wait.delay_10_us(10);
	ddd_7->ddd_set_hi_level(5.0);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	//DDD_Wait_Pattern_End(Low_XXX_pat_start,Low_XXX_pat_stop);

	// Drain (0V/3mA)
	D_dvi->set_voltage(D_ch, 0.0,			RANGE_50_V);	// DVI_11_0
	D_dvi->set_current(D_ch, 300e-3,		RANGE_300_MA);

	// UV pin (Vpin) set to 0V before PU
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_10_V);
	VPIN_ovi->set_current(VPIN_ch, 1e-3,	RANGE_30_MA);

	// BPP set 0V
	BPP_ovi->set_voltage(BPP_ch, 0.0,		RANGE_10_V);
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);
	wait.delay_10_us(5);

	// BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
	VBPP_ramp_up(gVBPP_Low_Voltage_PU, 5.0, 0.2);	// vstart, vstop, vstep	

	// Setup Vpin for digital clocking
	Close_relay(K12);						// Connect DDD7_1	to Vpin(UV)	pin
	VPIN_ovi->disconnect(VPIN_ch);
	delay(4);

	// Vpin clock 5 pulses (10us positive) to enter write mode
	Force_Vpin_Pulses_5_Times(5.0, 0.0);	// DDD_High_level, DDD_Low_level
	//wait.delay_10_us(5);

	if (ILIM_Select == ILIM_NORM || ILIM_Select == ILIM_INCR)
	{
		D_dvi->set_voltage(D_ch, 15.0, 		RANGE_50_V);
		wait.delay_10_us(10);
	}

	// Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	VBPP_ramp_up(5.0, gVBPP_PV_final, 0.1);
	//wait.delay_10_us(10);

	// Drain 0V to enter TM2
	D_dvi->set_voltage(D_ch, 0.0, 		RANGE_50_V);
	wait.delay_10_us(10);

	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep

	// Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
	if     (ILIM_Select == ILIM_NORM)				wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
	else if(ILIM_Select == ILIM_INCR)				wait.delay_10_us(150);	//10  uF	(ILIM+1)	1.2ms
	else if(ILIM_Select == ILIM_Jit18K)				wait.delay_10_us(3);
	else if(ILIM_Select == ILIM_SSS)				wait.delay_10_us(50);
	else											wait.delay_10_us(3);

	// BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
	VBPP_ramp_down(gVBPP_M_Init +0.25, gVBPP_M_Init -0.2, 0.05);	// vstart, vstop, vstep
	wait.delay_10_us(10);

	BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);
	VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 0.1);	// vstart, vstop, vstep
	wait.delay_10_us(10);

	// Drain set to 5V for switching
	D_dvi->set_voltage(D_ch, 5.0, 		RANGE_50_V);
	wait.delay_10_us(10);

	// Bring Vpin OVI back
	VPIN_ovi->connect(VPIN_ch);
	wait.delay_10_us(20);
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	VPIN_ovi->set_current(VPIN_ch, 1e-3,		RANGE_30_MA);
	//wait.delay_10_us(10);
	Open_relay(K12);					// Connect DDD7_1	to Vpin(UV)	pin
	//wait.delay_10_us(10);
}

void Power_Up_Primary_TM6(int ILIM_Select) 
{
	/******************************************************************************************************
	Rev B2p silicon implemented new test mode to trick Primary think that Secondary is in control

	To get into this mode, VPIN is grounded at startup.  BPP then ramps to 5V and 6 clock edges are applied 
	on VPIN.  Then allow BPP to complete the power up sequence.  Vpin sends 30us continuous pulses to act
	as Secondary FB pin to make request every 30us.  
	*******************************************************************************************************/

	//Drain (0V/3mA)
	D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
	D_dvi->set_voltage(D_ch, 0, 		VOLT_50_RANGE);	// DVI_11_0	
	wait.delay_10_us(20);

	//Vpin disconnect from OVI
	ovi_1->disconnect(OVI_CHANNEL_1);
	delay(2);

	//BPP set 0V
	BPP_ovi->set_current(BPP_ch, 15e-3,	RANGE_30_MA);
	wait.delay_10_us(5);

	//BPP ramp up to 5.0V with 200mV step, then from 5V to VBPP_plus + 200mV
	VBPP_ramp_up(4.2, 5.0, 0.1);	// vstart, vstop, vstep	

	//Vpin clock 6 pulses (10us positive) to enter write mode
	//Force_Vpin_Pulses_nTimes(6);	
	//wait.delay_10_us(5);

	if(g_TurretCB)
	{
		//Vpin clock 6 pulses (10us high, 2us low) to fix hot issues. 7/20/17
		ddd_7->ddd_run_pattern(AF_Vpin_Clk_pulse_start_6pulses_ET,AF_Vpin_Clk_pulse_stop_6pulses_ET);
		wait.delay_10_us(10);
	}
	else
	{
		//Vpin clock 6 pulses (10us high, 2us low) to fix hot issues. 7/20/17
		ddd_7->ddd_run_pattern(AF_Vpin_Clk_pulse_start_6pulses,AF_Vpin_Clk_pulse_stop_6pulses);
		wait.delay_10_us(10);
	}


	dvi_11->set_voltage(DVI_CHANNEL_0, 40, VOLT_50_RANGE);	//be able to see AF links properly
	wait.delay_10_us(10);

	//Bpp ramp from 5V -> 5.5V -> 5V with 50mV step
	VBPP_ramp_up(5.0, gVBPP_PV_Init+50e-3, 50e-3);
	//Drain stays at 0V so BPP signal will be cleaner
	dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
	wait.delay_10_us(10);

	VBPP_ramp_down(gVBPP_PV_Init, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	

	//Determine what ILIM mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
	if     (ILIM_Select == ILIM_NORM)				wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
	else if(ILIM_Select == ILIM_INCR)				wait.delay_10_us(150);	//10  uF	(ILIM+1)	1.2ms

	//BPP set 4.5V for 100us and 5.2V to bring chip back to normal operation
	ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-200e-3, RANGE_10_V);
	wait.delay_10_us(50);

	if(gSiliconRev_P >= 3)
	{
		BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
		VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_Init+50e-3, 50e-3);	// vstart, vstop, vstep	B3 material
		wait.delay_10_us(10);
	}
	else
	{
		ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+50e-3, RANGE_10_V);
		wait.delay_10_us(30);
	}

	//Drain set to 5V for switching
	dvi_11->set_voltage(DVI_CHANNEL_0, 25.0, VOLT_50_RANGE);
	wait.delay_10_us(10);

	//Vpin clock 30us continuously



}

void Power_Up_Primary_Normal_Mode(int ILIM_PU_Select) 
{
	//Vpin setup, Vpin=6V,80uA for IOV, Vpin=0V,30mA for all others
	if (gIOV)
	{
		//Vpin current to control switching or not (Below iOV+)
		VPIN_ovi->set_voltage(VPIN_ch, 6.0,			RANGE_10_V);  
		VPIN_ovi->set_current(VPIN_ch, 80e-6,		RANGE_300_UA);	
	}
	else
	{
		//Vpin set to 0V before PU (Low Jitter for ILIM_NORM if Primary in control)
		VPIN_ovi->set_voltage(VPIN_ch, 0,			RANGE_10_V);  
		VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);
	}

	//BPP set 0V
	BPP_ovi->set_current(BPP_ch, 30e-3,	RANGE_30_MA);
	BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);	// OVI_1_0
	wait.delay_10_us(5);

	//Drain (>15V read anti-fuses)
	D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
	D_dvi->set_voltage(D_ch, 40, 		VOLT_50_RANGE);	// DVI_11_0	
	delay(3);

	VBPP_ramp_up(0.0, gVBPP_PV_final, 0.2);	// vstart, vstop, vstep	
	wait.delay_10_us(20);

	VBPP_ramp_down(gVBPP_PV_final, gVBPP_M_Init +0.25, 0.1);	// vstart, vstop, vstep	
	
	//Determine what ILIM PowerUp mode we want to be power-up in  (IMPORTANT: ZF-P MUST TRIM FOR REFLECTION)
	if     (ILIM_PU_Select == ILIM_NORM)				wait.delay_10_us(3);	//1.0 uF	(ILIM)		30us
	else if(ILIM_PU_Select == ILIM_INCR)				wait.delay_10_us(150);	//10  uF	(ILIM+1)	1.2ms

	//BPP_ovi->set_voltage(BPP_ch, gVBPP_M_Init - 0.2, 	RANGE_10_V);	// OVI_1_0
	VBPP_ramp_down(gVBPP_M_Init +0.25, gVBPP_M_Init -0.2, 0.1);	// vstart, vstop, vstep	
	wait.delay_10_us(50);
	if(gSiliconRev_P>=3)
	{
		if(g_TurretCB)
		{
			BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material. HL changed from 2mA to 3mA
			VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
			wait.delay_10_us(10);
		}
		else
		{
			BPP_ovi->set_current(BPP_ch, 3e-3,	RANGE_30_MA);		//						B3 material
			VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 10e-3);	// vstart, vstop, vstep	B3 material
			wait.delay_10_us(10);
		}
	}
	else
	{
		VBPP_ramp_up(gVBPP_M_Init -0.2, gVBPP_P_final, 0.2);	// vstart, vstop, vstep	
		wait.delay_10_us(50);
	}
	
	//Drain=5V, above Test Mode Vthres (3V)
	D_dvi->set_voltage(D_ch, HANDSHAKE_Vd_NM, 		VOLT_10_RANGE);	// DVI_11_0	
	wait.delay_10_us(20);

}

void PV3_DriveOff_ChargeOn()
{
	//pv3_4->set_current(0);						// 590us for both
	//pv3_4->set_voltage(0, RANGE_100_V);
	//wait.delay_10_us(20);
	//pv3_4->drive_off();
	//wait.delay_10_us(20);
	//pv3_4->charge_on();	//prepare for next device
	PV3_Charge_On(RANGE_100_V);
}

void PV3_Charge_On(int Vrange)
{
	pv3_4->normal_comp();
	pv3_4->set_voltage(0,	Vrange);	//3V or 100V Range
	pv3_4->set_current(0,	RANGE_10_A);
	pv3_4->drive_off();
	pv3_4->charge_on();
}

void PV3_Check_Charge(int Vrange)
{
	float PV3_Charge = 0;
	int	  lcnt		 = 0;
	float Vcharge_th = 0;
	float iCharge	 = 0;
	BYTE  drv_status = 0;
	BYTE  chg_status = 0;

	pv3_4->set_meas_mode(PV3_CHARGE_S);
	drv_status = pv3_4->is_drive_on();
	chg_status = pv3_4->is_charge_on();

	if (Vrange == RANGE_3_V)
		Vcharge_th = 2.5;
	else
		Vcharge_th = 60;

	if (drv_status == 1) pv3_4->drive_off();
	if (chg_status == 0) pv3_4->charge_on();

	PV3_Charge = pv3_4->measure();
	while ((PV3_Charge < Vcharge_th) && (lcnt < 2000)) // 60V is enough
	{
		delay(1);
		lcnt++;
		PV3_Charge = pv3_4->measure();
		//if(PV3_Charge > Vcharge_th)
		//{
		//	pv3_4->set_meas_mode(PV3_MEASURE_CURRENT);
		//	delay(1);
		//	iCharge = pv3_4->measure();
		//}
		//printf("\nlcnt=%i, PV3_Charge=%.2f V, delay=%i ms\n", lcnt, PV3_Charge, lcnt);
	}

	//printf("iCharge = %.2f A\n", iCharge);
	//pv3_4->charge_off();
	//delay(2);
}

void PV3_Connect_Drain_and_DriveON(float Vdrive)
{
	float Vpv3_meas	 = 0;
	int	  lcnt		 = 0;

	//	connect PV3 to drain ILIM
	pv3_4->close_switch(PV3_LOW_FORCE_2);
	pv3_4->close_switch(PV3_LOW_SENSE_2);
	pv3_4->close_switch(PV3_HIGH_FORCE_1);
	pv3_4->close_switch(PV3_HIGH_SENSE_1);
	delay(2);

	pv3_4->set_meas_mode(PV3_MEASURE_VOLTAGE);		
	pv3_4->set_current(10.0, RANGE_10_A);			// Time=1e3*7e-3*(Vcap-(userV+5V))/userI; max C*U/I = 369mS
	pv3_4->set_voltage(Vdrive, RANGE_100_V);
	wait.delay_10_us(20);

	//turn on PV3
	pv3_4->drive_on(); 

	Vpv3_meas = pv3_4->measure();
	lcnt = 0;
	while ( Vpv3_meas	< Vdrive*0.98	&&
			lcnt		< 100				)	
	{
		lcnt++;
		Vpv3_meas = pv3_4->measure();
		wait.delay_10_us(20);
		//printf("\nPV3 drive voltage currently at %.2f V, Delay = %i ms", Vpv3_meas, lcnt);
	}
}

void PV3_Disconnect_Drain_and_DriveOFF()
{
	pv3_4->drive_off();
	pv3_4->set_voltage(0, RANGE_100_V);
	pv3_4->set_current(1.0e-6, RANGE_10_A);
	pv3_4->open_switch(PV3_LOW_FORCE_2);
	pv3_4->open_switch(PV3_LOW_SENSE_2);
	pv3_4->open_switch(PV3_HIGH_FORCE_1);
	pv3_4->open_switch(PV3_HIGH_SENSE_1);
	delay(1);
	pv3_4->charge_on();	
}

void Gage_Reset_Channels_AB_raw_data()
{
	for(int i=0; i<GAGE_WAVEFORM_BUFFER_SIZE-1; i++) 
	{
		chan_a_16_raw[i] = 0;
		chan_b_16_raw[i] = 0;
	}
}

void Observe_Vpin_Internal_Signals()
{
	/*******************************************************************************************************************
	Description: Also new in Inno4 is a way to bring out some internal logic signals to be observed on the VPIN.  
	The way this mode is entered is by ending either Write or Program Mode.  We do this by bringing the BP voltage 
	below UV- (4.5V) and then bringing it back above UV+(5.1V).  The chip goes into normal operation at this point, 
	but VPIN continues to serve as a clock input and at the same time is being driven by a current sink 
	controlled by the observation signal.
	*******************************************************************************************************************/

	int		i			=0;
	float	vVpin[16]	={0},
			iVpin[16]	={0};

	//Drain stays at 0V so BPP signal will be cleaner
//	dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_50_RANGE);
	//wait.delay_10_us(20);

	//BPP set 4.5V for 100us and 5.1V to bring chip back to normal operation
	ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_M_Init-0.3, RANGE_10_V);
	wait.delay_10_us(10);
	ovi_1->set_voltage(OVI_CHANNEL_0, gVBPP_P_Init+0.2, RANGE_10_V);
	wait.delay_10_us(10);

		ovi_1->connect(OVI_CHANNEL_1);
	//Setup to connect 5kohm between Vpin and DDD
	Open_relay(K16);	//5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
	Open_relay(K12);	//Vpin (UV) to DDD-7-1
	//Close_relay(K16);	//5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
		////debug only
		Close_relay(KC5); //Vpin to 5kohm to OVI-1-1
	delay(4);

	gSiOption_p = 0;

	//Vpin continues to serve as clock input and being drive by current sink controlled by observed signal.
	//note: if Vpin continue negative edge clocking after the 15th address, it will go back to addr 0 and start over.
	for(i=0; i<16; i++)
	{
		//if(i<=13)
		//{
			//This is to get a clean signal of Vpin from scope without connecting OVI for measurement 
			//Force_Vpin_Pulses_nTimes(1);	//clk through each address to find out internal signals (addr 0 to 15)
		//}
		//else	//record device ID signals
		//{
			//purposely set it to end HIGH so we have time to measure voltage at bit14,15
			//ddd_7->ddd_run_pattern(AF_Vpin_Clk_pulse_start,AF_Vpin_Clk_pulse_stop-8);
			//wait.delay_10_us(5);	
				//Vpin OVI setup to act like a sense vMeter 
				//ovi_1->connect(OVI_CHANNEL_1);
				ovi_1->set_voltage(OVI_CHANNEL_1, 5.0, RANGE_10_V);
				ovi_1->set_current(OVI_CHANNEL_1, 1.0e-3, RANGE_30_MA);
				ovi_1->set_meas_mode(OVI_CHANNEL_1, OVI_MEASURE_VOLTAGE, RANGE_5_V);
				wait.delay_10_us(5);
				vVpin[i] = ovi_1->measure_average(5);
				//Require disconnecting from Vpin for clean digitial signal from DDD
				ovi_1->set_meas_mode(OVI_CHANNEL_1, OVI_MEASURE_CURRENT);
				wait.delay_10_us(5);
				iVpin[i] = ovi_1->measure_average(5);
				ovi_1->set_voltage(OVI_CHANNEL_1, -1.5, RANGE_10_V);
				//ovi_1->disconnect(OVI_CHANNEL_1);
				wait.delay_10_us(10);
			//ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
			//wait.delay_10_us(5);

			////if(vVpin[i] > 4.5)		gVpin_Internal_Signal[i]=1;
			////else					gVpin_Internal_Signal[i]=0;

			//////Determine deviceID from Vpin threshold
			////if(i==14)	//bit ID0
			////{
			////	if(vVpin[i] < 4.5)			gSiOption_p = 0;
			////	else						gSiOption_p = 1;
			////}
			////if(i==15)	//bit ID1
			////{
			////	if(vVpin[i] > 4.5)			gSiOption_p = gSiOption_p + 2;
			////}

			if(iVpin[i] < 0)	gVpin_Internal_Signal[i]=1;
			else				gVpin_Internal_Signal[i]=0;
		//}
	}
				ovi_1->disconnect(OVI_CHANNEL_1);

	//ID1 and ID0
	if(gVpin_Internal_Signal[14] == 1)
		gSiOption_p += 1;
	if(gVpin_Internal_Signal[15] == 1)
		gSiOption_p += 2;

	Open_relay(K16);	//5kohm btw DDD-7-1 & UVf "DDD7-1 K12_pin8 Normally close to K12_pin9 to 5kohm to K16_pin8 to K16_pin7 to K12_pin4 to UVf)
	Open_relay(KC5); //Vpin to 5kohm to OVI-1-1

}

void Skip_Wait_and_Listen()
{
	//Before calling this function, Primary is already "ON" and Secondary is already "ON"
	//This function is purely created to skip the "Wait and Listen" time also known as "tWL" ~85ms

	//If Primary power-up by itself, it will go through tWL first and then switch for ~85ms and do ARST for ~2second
	//We do not want to have tWL added to test time everytime we do a power-up.  To avoid tWL, secondary to have 
	//trick primary thinking that secondary is already in control by supplying 3 FW negative pulses so Primary will
	//give up control and bypass tWL.

	//Setup FW to connect to DDD
	Open_relay(K18);  //disconnect FW from dvi-11-1
	Close_relay(K21); //FW to DDD (once DDD connected, it will then be set to DDD's vLow)
	delay(5);

	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//Vpin set to vHigh
	wait.delay_10_us(10); 
	// Secondary send 3 negative FW pulses to cause Primary to see request so Primary will be switching
	Force_Neg_Pulses_FW_DDD(5, -0.5);	//expect Drain to give acknowlege pulse after the 3rd FW pulse.
	wait.delay_10_us(10);  //more than 30us quiet time on FW signal

	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_50_RANGE);	// DVI_11_0		
	wait.delay_10_us(5);
	
	REQ_ovi->set_voltage(REQ_ch, gREQ_2V, 		VOLT_5_RANGE);	// OVI_1_2
	wait.delay_10_us(40);

	Connect_InvSyn_IM(Low_Vd_Input);		
	Open_relay(K21);		// FW		to	DDD
	wait.delay_10_us(10);
	D_dvi->set_voltage(D_ch, 5.0, 			VOLT_50_RANGE);	// DVI_11_0		
	wait.delay_10_us(140);
}

void Force_Neg_Pulses_FW_DDD_continuously()
{
	FW_dvi->set_voltage(FW_ch, 0.0,		VOLT_50_RANGE);	// DVI_11_1
	FW_dvi->set_current(FW_ch, 0.0,		RANGE_30_MA);


	if(g_TurretCB)
	{
		delay(2);
		FW_dvi->open_relay(CONN_FORCE1);
		FW_dvi->open_relay(CONN_SENSE1);
		
	}
	delay(2); //HL added in due to repeability on Turret CB
	ddd_7->ddd_set_hi_level(0.0);							// Will immediately change to this level upon execution
	delay(1);
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	
	wait.delay_10_us(10);

	Close_relay(K21);										// Connect FW pin to DDD, DDD is at 0V
	Open_relay(K18);										// Disconnect FW pin from DVI
	delay(5);
	if(!g_TurretCB)
	{
		FW_dvi->open_relay(CONN_FORCE1);
		FW_dvi->open_relay(CONN_SENSE1);
		delay(2); //HL added in due to repeability on Turret CB
	}
	ddd_7->ddd_stop_pattern();			// stop FW continuous clks
	delay(1);
	ddd_7->ddd_set_lo_level(-0.5);		// Will immediately change to this level upon execution 
	ddd_7->ddd_set_hi_level(3.0);		// Will immediately change to this level upon execution
	delay(1);
//	ddd_7->ddd_set_hi_level(0.5);		// Will immediately change to this level upon execution
	ddd_7->ddd_run_pattern(High_pat_start, High_pat_stop);	//FW will start with High
	wait.delay_10_us(10);
	ddd_7->ddd_end_pattern(FW_Neg_loop_pulse_stop);	//K21 needs to be closed for DDD connect to FW
	wait.delay_10_us(10); 
	ddd_7->ddd_run_pattern();
	wait.delay_10_us(10); 
	
	//Need to issue ddd_7->ddd_stop_patter() when finished outside this function else FW will switch continuously
}

void search_IOVp_linear_TM2(float *iOVp, float *iOVm, float *iUVp, float *iUVm)
{
	float	iOV_plus		=0, 
			iOV_minus		=0, 
			iOVplus_start	=0,
			iOV_Hys			=0,
			tOV_minus		=0,
			iUV_minus		=0,
			iUV_plus		=0,
			iUV_Hys			=0,
			tUV_minus		=0,
			iOV_plus_err	=0,
			iOV_plus_exp	=0,
			iOV_plus_act	=0;
	float	i_start			=0,
			i_stop			=0,
			i_step			=0,
			i_VPIN			=0,
			i_Hys			=0,
			tmeas			=0;
	bool	SWITCHING		=false,
			NO_SWITCHING	=false;
	int		count			=0;

	//Vpin (0V)
	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//Vout (3V)
	VO_dvi->set_current(VO_ch, 5.0e-3,		RANGE_30_MA);	
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	//FB (1V)
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	//IS (0V)
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	wait.delay_10_us(10);

	//	////////
	VBPP_Power_Up_w_Test_Mode(gTM2_UVOV_NoDelay, ILIM_INCR);	//
	delay(gDly_Wait_and_Listen_Normal_Mode);
	D_dvi->set_voltage(D_ch, 0.5, 		VOLT_2_RANGE);	// DVI_11_0	
	wait.delay_10_us(20);

	starttime = mytimer.GetElapsedTime();
	if(DEBUG==1 && gDEBUG)
	{
		printf("\nIUV_IOV:\n");
		printf("\nTESTMODE2 PowerUp\n");
	}

	//Ramp up iVpin until device stop switching (iOV- ~=110uA)
	i_start		= 104e-6;
	i_stop		= 130e-6;
	i_step		= 2.5e-6;
	SWITCHING	= true;
	i_VPIN		= i_start;
	i_Hys		= 18e-6;

	starttime = mytimer.GetElapsedTime();

	// Do rough step size first
	while (i_VPIN < i_stop && SWITCHING == true)
	{
		i_VPIN += i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(5);
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(5);
		tmeas = tmu_6->read(50e-6); 
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG && gDEBUG)
			printf("(iOV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas < 0.1e-6) 
			SWITCHING = false;
	}
	//////////
	*iOVm = i_VPIN;
	
	//Ramp down iVpin until device start switching (iOV+ ~=100uA)
	i_start		= iOV_plus - 10e-6;	//iOV_Hys ~=10-15uA
	i_stop		= iOV_plus - 30e-6;
	i_step		= 0.5e-6;
	i_VPIN		= i_start;
	starttime = mytimer.GetElapsedTime();

	//Ramp down with 1uA step until device stop switching
	while(i_VPIN > i_stop && SWITCHING == false)
	{
		i_VPIN -= i_step;	
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(600);				// >10ms for part to respond
		//exit while loop if device stop switching
		tmu_6->arm();	
		wait.delay_10_us(600);				// >10ms for part to respond
		tmeas = tmu_6->read(50e-6); 		// Increased wait for trigger
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG && gDEBUG)
			printf("(iOV+)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas > 0.1e-6)
		{
			SWITCHING = true;
			if(DEBUG && gDEBUG)
				printf("\n");
		}
	}
	//////////
	*iOVp = i_VPIN + i_step/2;
	//iOV_plus = i_VPIN;

	// JD do finer resolution step IOV-
	i_start		= iOV_plus - 3e-6;	// Back 10 steps
	i_stop		= 130e-6;
	i_step		= 0.25e-6;
	SWITCHING	= true;
	i_VPIN		= i_start;
	
	while (i_VPIN < i_stop && SWITCHING == true)
	{
		i_VPIN += i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(5);
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(5);
		tmeas = tmu_6->read(50e-6); 
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG && gDEBUG)
			printf("(iOV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
				//IF WE WANT TO FINE TUNE IT, IT WILL REQUIRE ANOTHER POWER-UP AND ANOTHER WAIT AND LISTEN TIME
			if(tmeas < 0.1e-6) 
				SWITCHING = false;
	}
	//////////
	//iOV_plus = i_VPIN;
	*iOVm = i_VPIN - i_step/2;

	//Power Down
	Power_Down_Primary();
	wait.delay_10_us(50);

	//Vpin (0V)
	VPIN_ovi->set_current(VPIN_ch, 30e-3,		RANGE_30_MA);	
	VPIN_ovi->set_voltage(VPIN_ch, 0.0,			RANGE_10_V);
	//Vout (3V)
	VO_dvi->set_current(VO_ch, 5.0e-3,		RANGE_30_MA);	
	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	//FB (1V)
	REQ_ovi->set_current(REQ_ch, 30e-3,	RANGE_30_MA);	
	REQ_ovi->set_voltage(REQ_ch, gCV_Low,		RANGE_2_V);	// OVI_1_2	
	//IS (0V)
	FWC_dvi2k->set_voltage(FWC_ch, 0.0, 		VOLT_2_RANGE);	// DVI_21_0
	FWC_dvi2k->set_current(FWC_ch, 20.0e-3,	RANGE_20_MA);
	wait.delay_10_us(10);

	//	////////
	VBPP_Power_Up_w_Test_Mode(gTM2_UVOV_NoDelay, ILIM_INCR);	//
	delay(gDly_Wait_and_Listen_Normal_Mode);

	if(DEBUG==1 && gDEBUG)
	{
		printf("\nIUV_IOV:\n");
		printf("\nTESTMODE2 PowerUp\n");
	}

	D_dvi->set_voltage(D_ch, 0.5, 		VOLT_2_RANGE);	// DVI_11_0	
	wait.delay_10_us(20);

	//Ramp dn from iOV+ until device stop switching (iUV- ~=15uA.  Acutal = 17uA)
	//Manually ramp down iVpin with 10uA per step to be 10uA above iUV_plus ~30uA
	i_start		= 23e-6;
	i_stop		= 10e-6;
	i_VPIN		= i_start;
	i_step		= 0.25e-6;
	SWITCHING	= true;
	starttime = mytimer.GetElapsedTime();
	//Ramp dow with 1uA step until device stop switching
	while(i_VPIN > i_stop && SWITCHING == true)
	{
		i_VPIN -= i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_30_UA);	
		wait.delay_10_us(5);
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(5);
		tmeas = tmu_6->read(20e-6);
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG && gDEBUG)
			printf("(iUV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas < 0.5e-6)
		{
			SWITCHING = false;
			if(DEBUG && gDEBUG)
				printf("\n");
		}
	}
	*iUVm = i_VPIN + i_step;
	//iUV_minus = i_VPIN;
	//////////

	//Ramp up from iUV- until device start switching (iUV+ ~=25uA. Actual = 24uA)	iUV_Hys ~=10uA
	i_start		= iUV_minus + 2e-6;
	i_stop		= iUV_minus + 15e-6;
	i_step		= 0.1e-6;
	i_VPIN		= i_start;
	starttime = mytimer.GetElapsedTime();

	//Ramp up with 1uA step until device stop switching
	while(i_VPIN < i_stop && SWITCHING == false)
	{
		i_VPIN += 0.25e-6;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_30_UA);	
		delay(10);			// ~10ms for part to respond
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(10);
		tmeas = tmu_6->read(20e-6);
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG && gDEBUG)
			printf("(iUV+)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas > 0.1e-6)
		{
			SWITCHING = true;
			if(DEBUG && gDEBUG)
				printf("\n");
		}
	}
	*iUVp = i_VPIN - i_step;
	//iUV_plus = i_VPIN;
	//////////
}

void search_IOVp_Binary(float *iOVp)
{
	//IOV+ binary search to find threshold where switching stops
	//Notes:
	//	- Device will stop switching immediately if goes above IOV+
	//	- Going from non-switching to switching requires minimum 100us tOV to see device start switching.
	//	- iHys_OV is ~10uA
	//	- Going from IOV- to IUV+ will not change switching status.  Device will stay switching
	//	- Going from IUV+ to below IUV- will require a wait time of tUV ~35ms to see device go from switching to OFF
	//	- iHys_UV is ~5uA
	//	- Going from IUV- to above IUV+ also requires ~100us min to see device go from non-switch to switch.

	float	ifrc_hi		=0,
			ifrc_lo		=0,
			i_mid		=0,
			ifrc		=0,
			iHys		=0,
			istep		=0,
			tmeas		=0,
			tmeas_th	=0,
			t_hi		=0,
			t_lo		=0,
			j           =0;
			
	int		switching_status	=0,
			lcnt				=0,
			i					=0;


	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	ifrc_hi		= 150e-6;
	ifrc_lo		= 75e-6;
	iHys		= 30e-6;
	istep		= 0.1e-6;
	tmeas_th	= 10e-6;	//use 10us Period threshold to determine switching or not.
	t_hi		= 80e-6;
	t_lo		= 2e-6;//Temporary commented out due to drain on time issue
	//Temporary statement
	//t_lo=0.1e-6;//Change this back to 2 us when ton on drain issue is resolved
	//iHys		= 15e-6;
//	t_hi		= 60e-6;
//	t_lo		= 10e-6;
//DEBUG=1;
	if(DEBUG==1 && gDEBUG)	printf("\nIUV_IOV:\n");
	
	//expect to see device switching after power-up with 80uA iVpin
	tmu_6->arm(); 
	wait.delay_10_us(50);		//ok to pause here when using scope
	tmeas = tmu_6->read(100e-6); //expect to see device switching after power-up with 80uA iVpin
	//if(tmeas < 10e-6)//- Change this back to 2us when ton on drain issue is resolved
	if(tmeas < 10e-6)
	{
		*iOVp = -999e-6;	//fail if not switching
		switching_status = 0;
		return;
	}
	if(DEBUG==1 && gDEBUG)
				printf("IOV switching at initial low current\n");

	//expect stop switching with iVpin 150uA
	VPIN_ovi->set_current(VPIN_ch, ifrc_hi,		RANGE_300_UA);	//expect stop switching
	wait.delay_10_us(15);
	tmu_6->arm(); 
	wait.delay_10_us(10);
	tmeas = tmu_6->read(100e-6); 
	if(tmeas > t_lo && tmeas < t_hi)
	{
		*iOVp = 999e-6;	//fail if switching
		switching_status = 1;
		return;
	}
	if(DEBUG==1 && gDEBUG)
				printf("IOV stops switching at initial high current\n");

	//delay(10); //WHY is this delay?  Why do we need it for iOV final only??

	//start search loop
	switching_status = 0;
	while ( ((ifrc_hi-ifrc_lo) > 0.125e-6) && (lcnt < 20) )
	{
		i_mid = (ifrc_hi+ifrc_lo)/2;	

		if(switching_status == 0)	//Only require if previous status is OFF
		{
			//Bring device back to switching with subtraction to Hysteresis
			VPIN_ovi->set_current(VPIN_ch, i_mid-iHys,		RANGE_300_UA);	
			wait.delay_10_us(15);	//require minimum of 100us going from nsw to sw
			if(gTrim_Loff_AR_P)
			{
				VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
				wait.delay_10_us(10);
				VBPP_ramp_up(gVBPP_M_Init -0.25, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
				wait.delay_10_us(50);
				//delay(1);
			}
		}
		//Now set the current in between New High and New Low
		VPIN_ovi->set_current(VPIN_ch, i_mid,		RANGE_300_UA);	
		wait.delay_10_us(15);
		tmu_6->arm();						
		wait.delay_10_us(10);
		tmeas = tmu_6->read(100e-6);

		if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is not switching
		{
			ifrc_hi = i_mid;
			switching_status = 0;
			if(DEBUG==1)
				printf("ifrc_lo = %.2f uA, ifrc_hi = %.2f uA, ifrc = %.2f uA, toff_meas = %.2f us\n", ifrc_lo*1e6, ifrc_hi*1e6, i_mid*1e6, tmeas*1e6);
		}
		else
		{
			ifrc_lo = i_mid;
			switching_status = 1;
			if(DEBUG==1)
				printf("ifrc_lo = %.2f uA, ifrc_hi = %.2f uA, ifrc = %.2f uA, ton_meas = %.2f us\n", ifrc_lo*1e6, ifrc_hi*1e6, i_mid*1e6, tmeas*1e6);
		}
			
		lcnt++;
	}


	//Fine Tune in 10 steps of 100nA
	//Bring device back to switching with subtraction to Hysteresis
	VPIN_ovi->set_current(VPIN_ch, i_mid-iHys,		RANGE_300_UA);	
	wait.delay_10_us(15);	//require minimum of 100us going from nsw to sw
	if(gTrim_Loff_AR_P)
	{
		VBPP_ramp_down(gVBPP_P_final, gVBPP_M_Init -0.25, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(10);
		VBPP_ramp_up(gVBPP_M_Init -0.25, gVBPP_P_final, 0.1);	// vstart, vstop, vstep	
		wait.delay_10_us(50);
		//delay(1);
	}

	//Ramp up from "i_mid-iHys" to 2uA below "i_mid"
	ifrc	= i_mid - iHys;
	istep	= 0.5e-6;
	while(ifrc < (i_mid-2e-6))
	{
		VPIN_ovi->set_current(VPIN_ch, ifrc,		RANGE_300_UA);	
		wait.delay_10_us(5);
		ifrc += istep;
	}
	//Now set the current in between New High and New Low
	//VPIN_ovi->set_current(VPIN_ch, i_mid - 2e-6,		RANGE_300_UA);
	//wait.delay_10_us(5);
	//VPIN_ovi->set_current(VPIN_ch, i_mid - 1e-6,		RANGE_300_UA);
	//wait.delay_10_us(5);
	ifrc = i_mid - 1e-6;
	istep	= 0.1e-6;
	for(i=1; i<40; i++)
	{
		ifrc = (i_mid - 1e-6) + i*istep;
		VPIN_ovi->set_current(VPIN_ch, ifrc,		RANGE_300_UA);	
		wait.delay_10_us(10);
		tmu_6->arm();						
		wait.delay_10_us(10);
		tmeas = tmu_6->read(100e-6);
		if(DEBUG==1)
			printf("ifrc_lo = %.2f uA, ifrc_hi = %.2f uA, ifrc = %.2f uA, tmeas = %.2f us\n", ifrc_lo*1e6, ifrc_hi*1e6, ifrc*1e6, tmeas*1e6);
		if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is not switching
			break;
	}

	*iOVp = ifrc;	
	wait.delay_10_us(20);

}

void search_IOVp_Binary_TurretCB(float *iOVp)
{
	//IOV+ binary search to find threshold where switching stops
	//Notes:
	//	- Device will stop switching immediately if goes above IOV+
	//	- Going from non-switching to switching requires minimum 100us tOV to see device start switching.
	//	- iHys_OV is ~10uA
	//	- Going from IOV- to IUV+ will not change switching status.  Device will stay switching
	//	- Going from IUV+ to below IUV- will require a wait time of tUV ~35ms to see device go from switching to OFF
	//	- iHys_UV is ~5uA
	//	- Going from IUV- to above IUV+ also requires ~100us min to see device go from non-switch to switch.

	float	ifrc_hi		=0,
			ifrc_lo		=0,
			i_mid		=0,
			ifrc		=0,
			iHys		=0,
			istep		=0,
			tmeas		=0,
			tmeas_th	=0,
			t_hi		=0,
			t_lo		=0,
			j           =0;


	int		switching_status	=0,
			lcnt				=0,
			i					=0;


	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug

	ifrc_hi		= 150e-6;
	ifrc_lo		= 75e-6;
	iHys		= 30e-6;
	istep		= 0.1e-6;
	tmeas_th	= 10e-6;	//use 10us Period threshold to determine switching or not.
	t_hi		= 80e-6;
	t_lo		= 2e-6;
	//iHys		= 15e-6;
//	t_hi		= 60e-6;
//	t_lo		= 10e-6;

	tmu_6->arm(); 
	wait.delay_10_us(10);
	tmeas = tmu_6->read(100e-6); //expect to see device switching after power-up with 80uA iVpin
	if(tmeas < 10e-6)
	{
		*iOVp = -999e-6;
		switching_status = 0;
		return;
	}

	VPIN_ovi->set_current(VPIN_ch, ifrc_hi,		RANGE_300_UA);	//expect stop switching
	wait.delay_10_us(30);
	tmu_6->arm(); 
	wait.delay_10_us(10);
	tmeas = tmu_6->read(100e-6); 
	if(tmeas > t_lo && tmeas < t_hi)
	{
		*iOVp = 999e-6;
		switching_status = 1;
		return;
	}

	if(DEBUG==1)	printf("\nIUV_IOV:\n");
	

	delay(10); //WTF is this delay?  Why do we need it for iOV final only??

	switching_status = 0;
	while ( ((ifrc_hi-ifrc_lo) > 0.125e-6) && (lcnt < 20) )
	{
		i_mid = (ifrc_hi+ifrc_lo)/2;	

		j = 0;
		while(j < i_mid)
		{
			VPIN_ovi->set_current(VPIN_ch, j,		RANGE_300_UA);	
			j = j + 0.5e-6;
		}
		//Now set the current in between New High and New Low
		VPIN_ovi->set_current(VPIN_ch, i_mid,		RANGE_300_UA);	
		wait.delay_10_us(15);
		tmu_6->arm();						
		wait.delay_10_us(10);
		if (MOSFET_SIZE==2) delay(100);	//required for SC1535 on TMT03, 11/14/16, TMT43 11/23/16 pm
		tmeas = tmu_6->read(100e-6);

		if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is not switching
		{
			ifrc_hi = i_mid;		//not switching, look to lower current
			switching_status = 0;
			if(DEBUG==1 && gDEBUG)
				printf("ifrc_lo = %.2f uA, ifrc_hi = %.2f uA, ifrc = %.2f uA, toff_meas = %.2f us\n", ifrc_lo*1e6, ifrc_hi*1e6, i_mid*1e6, tmeas*1e6);
		}
		else
		{
			ifrc_lo = i_mid;		//switching, look to higher current
			switching_status = 1;
			if(DEBUG==1 && gDEBUG)
				printf("ifrc_lo = %.2f uA, ifrc_hi = %.2f uA, ifrc = %.2f uA, ton_meas = %.2f us\n", ifrc_lo*1e6, ifrc_hi*1e6, i_mid*1e6, tmeas*1e6);
		}
			
		lcnt++;
	}


	//Fine Tune in 10 steps of 100nA
	//Bring device back to switching with subtraction to Hysteresis
	VPIN_ovi->set_current(VPIN_ch, i_mid-iHys,		RANGE_300_UA);	
	wait.delay_10_us(15);	//require minimum of 100us going from nsw to sw

	//Ramp up from "i_mid-iHys" to 2uA below "i_mid"
	ifrc	= i_mid - iHys;
	istep	= 0.5e-6;
	while(ifrc < (i_mid-2e-6))
	{
		VPIN_ovi->set_current(VPIN_ch, i_mid-iHys,		RANGE_300_UA);	
		wait.delay_10_us(5);
		ifrc += istep;
	}
	//Now set the current in between New High and New Low
	//VPIN_ovi->set_current(VPIN_ch, i_mid - 2e-6,		RANGE_300_UA);
	//wait.delay_10_us(5);
	//VPIN_ovi->set_current(VPIN_ch, i_mid - 1e-6,		RANGE_300_UA);
	//wait.delay_10_us(5);
	ifrc = i_mid - 1e-6;
	istep	= 0.1e-6;
	for(i=1; i<40; i++)
	{
		ifrc = (i_mid - 1e-6) + i*istep;
		VPIN_ovi->set_current(VPIN_ch, ifrc,		RANGE_300_UA);	
		wait.delay_10_us(10);
		tmu_6->arm();						
		wait.delay_10_us(10);
		tmeas = tmu_6->read(100e-6);
		if(DEBUG==1 && gDEBUG)
			printf("ifrc_lo = %.2f uA, ifrc_hi = %.2f uA, ifrc = %.2f uA, tmeas = %.2f us\n", ifrc_lo*1e6, ifrc_hi*1e6, ifrc*1e6, tmeas*1e6);
		if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is not switching
			break;
	}

	*iOVp = ifrc;	
	wait.delay_10_us(20);

}

void search_IOVp_linear_ProgMode(float *iOVp, float *iOVm, float *iUVp, float *iUVm)
{
	float	iOV_plus		=0, 
			iOV_minus		=0, 
			iOVplus_start	=0,
			iOV_Hys			=0,
			tOV_minus		=0,
			iUV_minus		=0,
			iUV_plus		=0,
			iUV_Hys			=0,
			tUV_minus		=0,
			iOV_plus_err	=0,
			iOV_plus_exp	=0,
			iOV_plus_act	=0;
	float	i_start			=0,
			i_stop			=0,
			i_step			=0,
			i_VPIN			=0,
			i_Hys			=0,
			tmeas			=0;
	bool	SWITCHING		=false,
			NO_SWITCHING	=false;
	int		count			=0;

	// Program mode will switch continuously
	SyncHS_PowerUp_Secondary_in_ProgMode_Skip_WaitNListen(gTM1_UVOV_NoDelay, gTM2_UVOV_NoDelay);
	D_dvi->set_voltage(D_ch, 0.5, 	VOLT_2_RANGE);	// DVI_11_0	
	wait.delay_10_us(10);

	if(DEBUG==1 && gDEBUG)
	{
		printf("\nIUV_IOV:\n");
		printf("\nTESTMODE/Program Mode PowerUp\n");
	}

	//Ramp up iVpin until device stop switching (iOV- ~=110uA)
	i_start		= 90e-6;
	i_stop		= 130e-6;
	i_step		= 2e-6;
	SWITCHING	= true;
	i_VPIN		= i_start;
	i_Hys		= 18e-6;	// Larger than actual hysteresis

	starttime = mytimer.GetElapsedTime();

	// IOV- rough threshold test
	// IOV- ramp up Vpin current in large steps to find rough threshold where switching stops
	while (i_VPIN < i_stop && SWITCHING == true)
	{
		i_VPIN += i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(10);
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(5);
		tmeas = tmu_6->read(50e-6); 
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG==1 && gDEBUG)
			printf("(iOV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas < 0.1e-6)
		{
			SWITCHING = false;
			if(DEBUG && gDEBUG)
				printf("\n");
		}
	}
	iOV_plus = i_VPIN;
	
	// IOV+ rough threshold test
	// Ramp down iVpin, large steps until device start switching (iOV+ ~=100uA)	iOV_Hys ~=10uA
	i_start		= iOV_plus - 8e-6;	// depends on hysteresis
	i_stop		= iOV_plus - 20e-6;
	i_VPIN		= i_start;
	i_step		= 0.5e-6;
	SWITCHING	= false;
	starttime = mytimer.GetElapsedTime();

	//Ramp up with 1uA step until device stop switching
	while(i_VPIN > i_stop && SWITCHING == false)
	{
		i_VPIN -= i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(10);
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(5);
		tmeas = tmu_6->read(50e-6); 
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG && gDEBUG)
			printf("(iOV+)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas > 0.1e-6)
		{
			SWITCHING = true;
			if(DEBUG && gDEBUG)
				printf("\n");
		}
	}
	iOV_plus = i_VPIN;
	*iOVp = iOV_plus;

	// IUV- fine threshold test
	// Ramp up iVpin until device stop switching (iOV- ~=115uA)
	i_start		= iOV_plus - 2.5e-6;
	i_stop		= 130e-6;
	i_step		= 0.1e-6;
	SWITCHING	= true;
	i_VPIN		= i_start;
	starttime = mytimer.GetElapsedTime();

	// IUV- ramp up in small steps to find exact threshold (OVI 12 bits ~75nA min step size)
	// Min trim bit weight is 1%, accuracy 0.3uA, have 10X quantization
	while (i_VPIN < i_stop && SWITCHING == true)
	{
		i_VPIN += i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(10);
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(5);
		tmeas = tmu_6->read(50e-6); 
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG==1 && gDEBUG)
			printf("(iOV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas < 0.1e-6)
			SWITCHING = false;
		if(DEBUG && gDEBUG)
			printf("\n");
	}
	//////////
	iOV_plus = i_VPIN;
	*iOVm = iOV_plus;

	// IOV+  fine threshold test
	//Ramp down iVpin, small steps until device start switching (iOV+ ~=100uA)	iOV_Hys ~=10uA
	i_start		= iOV_plus + 2.5e-6;		// start a little above threshold
	i_stop		= iOV_plus - i_Hys;
	i_VPIN		= i_start;
	i_step		= 0.1e-6;				// Forcing accuracy best ~75nA
	SWITCHING	= false;
	starttime = mytimer.GetElapsedTime();

	//Ramp down with 0.1uA step until device stop switching
	while(i_VPIN > i_stop && SWITCHING == false)
	{
		i_VPIN -= i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(10);
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(5);
		tmeas = tmu_6->read(50e-6); 
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG && gDEBUG)
			printf("(iOV+)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas > 0.1e-6)
		{
			SWITCHING = true;
			if(DEBUG && gDEBUG)
				printf("\n");
		}
	}
	iOV_plus = i_VPIN-i_step/2;	// transition actully happens between steps
	*iOVp = iOV_plus;

	//Ramp dn from iOV+ until device stop switching (iUV- ~=15uA.  Acutal = 17uA)
	//Manually ramp down iVpin with 10uA per step to be 10uA above iUV_plus ~30uA
	i_VPIN		= iOV_plus;
	while (i_VPIN > 26e-6 && count < 40)
	{
		i_VPIN = i_VPIN - 10e-6;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(5);
		count++;
	}
	
	// IUV
	i_start		= i_VPIN;
	i_stop		= i_start - 15e-6;
	i_VPIN		= i_start;
	i_step		= 0.1e-6;
	SWITCHING	= true;
	starttime = mytimer.GetElapsedTime();
	//Ramp down with 1uA step until device stop switching
	while(i_VPIN > i_stop && SWITCHING == true)
	{
		i_VPIN -= i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(10);
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(5);
		tmeas = tmu_6->read(50e-6); 
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG && gDEBUG)
			printf("(iUV-)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas < 0.1e-6)
		{
			SWITCHING = false;
			if(DEBUG && gDEBUG)
				printf("\n");
		}
	}
	iUV_minus = i_VPIN+i_step/2;
	*iUVm = iUV_minus;
	//////////

	//Ramp up from iUV- until device start switching (iUV+ ~=25uA. Actual = 24uA)	iUV_Hys ~=10uA
	i_start		= iUV_minus + 2e-6;
	i_stop		= iUV_minus + 15e-6;
	i_VPIN		= i_start;
	i_step		= 0.1e-6;
	SWITCHING	= false;
	starttime = mytimer.GetElapsedTime();

	//Ramp up with 1uA step until device stop switching
	while(i_VPIN < i_stop && SWITCHING == false)
	{
		i_VPIN += i_step;
		VPIN_ovi->set_current(VPIN_ch, i_VPIN,		RANGE_300_UA);	
		wait.delay_10_us(10);
		//exit while loop if device stop switching
		tmu_6->arm(); 
		wait.delay_10_us(5);
		tmeas = tmu_6->read(50e-6); 
		stoptime = mytimer.GetElapsedTime();
		if(DEBUG && gDEBUG)
			printf("(iUV+)iVPIN = %.2f uA, tmeas = %.2f us, Timecount = %.2f ms\n", i_VPIN * 1e6, tmeas*1e6, (stoptime-starttime)/1e3);
		if(tmeas > 0.1e-6)
		{
			SWITCHING = true;
			if(DEBUG && gDEBUG)
				printf("\n");
		}
	}
	iUV_plus = i_VPIN-i_step/2;
	*iUVp = iUV_plus;
	//////////
		
	//Power Down
	Power_Down_Secondary();
	Power_Down_Primary();
}

void Open_All_Relays()
{
	//Open All Relays //
	Open_relay(K1);
	Open_relay(K2);
	Open_relay(K3);
	Open_relay(K4);
	Open_relay(K5);
	Open_relay(K6);
	Open_relay(K7);
	Open_relay(K8);
	Open_relay(K9);
	Open_relay(K10);
	Open_relay(K11);
	Open_relay(K12);
	Open_relay(K13);
	Open_relay(K14);
	Open_relay(K15);
	Open_relay(K16);
	Open_relay(K17);
	Open_relay(K18);
	Open_relay(K19);
	Open_relay(K20);
	Open_relay(K21);
	Open_relay(K22);
	Open_relay(K23);
	Open_relay(K24);
	Open_relay(K25);
	Open_relay(K26);
	Open_relay(K27);
	Open_relay(K28);
	//Open_relay(K29);	// K28, K29, K34 are linked
	//Open_relay(K34);	// K28, K29, K34 are linked
	Open_relay(K35);
	Open_relay(K36);
	Open_relay(K37);
	Open_relay(K38);
	Open_relay(K39);
	Open_relay(K40);
	Open_relay(K41);
	Open_relay(K42);
	Open_relay(K43);
	Open_relay(KC5);
	Open_relay(KC6);
	Open_relay(KC7);
	Open_relay(KC8);
	Open_relay(KIM1);
	Open_relay(KIM2);
	Open_relay(KIM3);

	//tmu_6->open_relay(TMU_HIZ_DUT1);			
	//tmu_6->open_relay(TMU_HIZ_DUT2);			
	//tmu_6->open_relay(TMU_HIZ_DUT3);			
	//tmu_6->open_relay(TMU_HIZ_DUT4);			
	//tmu_6->open_relay(TMU_CHAN_A_DUT1);			
	//tmu_6->open_relay(TMU_CHAN_A_DUT2);			
	//tmu_6->open_relay(TMU_CHAN_B_DUT1);			
	//tmu_6->open_relay(TMU_CHAN_B_DUT2);			
}

void Power_Down_Everything()
{
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 30e-3, 		RANGE_30_MA);	// DVI_11_0

	BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0 
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);

	VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_10_V);
	VPIN_ovi->set_current(VPIN_ch, 30e-3,	RANGE_30_MA);
	VPIN_ovi->connect(VPIN_ch);

	ddd_7->ddd_stop_pattern();								// Stop the DDD loop pattern
	wait.delay_10_us(10);
	ddd_7->ddd_set_lo_level(0.1);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	DDD_Wait_Pattern_End(Low_XXX_pat_start,Low_XXX_pat_stop);

	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);	

	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_2_V);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);

	FWC_dvi2k->set_voltage(FWC_ch, 0.0,		VOLT_2_RANGE);	// DVI-13-0
	FWC_dvi2k->set_current(FWC_ch, 0.1,		RANGE_2_A);

	FW_dvi->set_voltage(FW_ch, 0.0,			VOLT_5_RANGE);		// DVI11-1
	FW_dvi->set_current(FW_ch, 30e-3,		RANGE_30_MA);	

	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_1
	BPS_dvi->set_current(BPS_ch, 300.0e-3,	RANGE_300_MA);				//NEED TO BE 300mA to pull down to GND faster.

	SR_dvi2k->open_relay(BUS_SENSE1);
	SR_dvi2k->open_relay(BUS_FORCE1);
	mux_14->open_relay(MUX_3_BUS3);
	wait.delay_10_us(5);
	
	SR_dvi2k->close_relay(CONN_FORCE1);
	SR_dvi2k->close_relay(CONN_SENSE1);
	SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);
	SR_dvi2k->set_current(SR_ch, 0.1,		RANGE_2_A);

	//IS
	mux_14->open_relay(MUX_2_GND);
	wait.delay_10_us(5);

	//BUF Clamp
	ovi_1->set_current(OVI_CHANNEL_3, 30e-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_3, 0.0,	 RANGE_2_V);
	wait.delay_10_us(5);
}

void Power_Down_Everything_Except_Buf_Clamp()
{
	D_dvi->set_voltage(D_ch, 0.0, 			VOLT_10_RANGE);	// DVI_11_0
	D_dvi->set_current(D_ch, 30e-3, 		RANGE_30_MA);	// DVI_11_0

	BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0 
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);

	VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_10_V);
	VPIN_ovi->set_current(VPIN_ch, 30e-3,	RANGE_30_MA);
	VPIN_ovi->connect(VPIN_ch);

	ddd_7->ddd_stop_pattern();								// Stop the DDD loop pattern
	wait.delay_10_us(10);
	ddd_7->ddd_set_lo_level(0.1);
	wait.delay_10_us(10);
	ddd_7->ddd_run_pattern(Low_XXX_pat_start,Low_XXX_pat_stop);
	DDD_Wait_Pattern_End(Low_XXX_pat_start,Low_XXX_pat_stop);

	VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0
	VO_dvi->set_current(VO_ch, 300e-3,		RANGE_300_MA);	

	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_2_V);	// OVI_1_2
	REQ_ovi->set_current(REQ_ch, 30e-3,		RANGE_30_MA);

	FWC_dvi2k->set_voltage(FWC_ch, 0.0,		VOLT_2_RANGE);	// DVI-13-0
	FWC_dvi2k->set_current(FWC_ch, 0.1,		RANGE_2_A);

	FW_dvi->set_voltage(FW_ch, 0.0,			VOLT_5_RANGE);		// DVI11-1
	FW_dvi->set_current(FW_ch, 30e-3,		RANGE_30_MA);	

	BPS_dvi->set_voltage(BPS_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_1
	BPS_dvi->set_current(BPS_ch, 300.0e-3,	RANGE_300_MA);				//NEED TO BE 300mA to pull down to GND faster.

	SR_dvi2k->open_relay(BUS_SENSE1);
	SR_dvi2k->open_relay(BUS_FORCE1);
	mux_14->open_relay(MUX_3_BUS3);
	wait.delay_10_us(5);
	
	SR_dvi2k->close_relay(CONN_FORCE1);
	SR_dvi2k->close_relay(CONN_SENSE1);
	SR_dvi2k->set_voltage(SR_ch, 0.0,		VOLT_2_RANGE);
	SR_dvi2k->set_current(SR_ch, 0.1,		RANGE_2_A);

	//IS
	mux_14->open_relay(MUX_2_GND);
	wait.delay_10_us(5);
}

void Find_SOA_SDS_vs_Voltage()
{
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

	float   PV3_Charge =0.0;

	int	    lcnt  =0;
	float   Vpv3_meas =0.0;
	float   vSOA =0.0, 
			vSDS =0.0,
			Vref_cmp=0.0;

	float	soa_s[400] = {0},
			tw50_s[400] ={0},
			soa_p[400] ={0},
			tw50_p[400] ={0},
			sds_s[400] ={0},
			tw50_sds_s[400]={0}, 
			sds_p[400] ={0},
			tw50_sds_p[400]={0},
			vsoa[400] = {0},
			vsds[400] = {0};

	float	tmeas=0.0;

	
	// JD put in mode change later
	if(MOSFET_SIZE == 2)
	{
		VSOA_RM				= 3.5;
		VSOA_HT				= 7.0;
		VSDS_RM				= 19.5;
	}
	else
	{
		VSOA_RM				= 3.0;	// TMT81 needs 8V top give correct waveform, TMT91 and 43 6V
		VSOA_RM_P			= 8.0;
		VSOA_HT				= 8.0;
		VSOA_HT_P			= 6.5;
		VSDS_RM				= 18.0,
		VSDS_RM_P			= 23.0;
	}

	if(OPCODE==4200 || OPCODE==4250 || OPCODE==4501)
	{
		vSOA = VSOA_RM;
		vSDS = VSDS_RM;
	}
	else
	{
		vSOA = VSOA_HT;
		vSDS = VSDS_HT;
	}

//*************************************************************************************************************
//**********  SOA-P  ******************************************************************************************
//*************************************************************************************************************
	//Information:
	//	- SOA pullup resistance
	//		* 5ohm (Require hardware modification)

	//int starttime = mytimer.GetElapsedTime();
	int i = 0;
	for (i=0; i<400; i++)
	{
		PV3_Charge_On(RANGE_100_V);	//Prepare PV3 before power-up
		PV3_Check_Charge(RANGE_100_V);  //Note: Once Charge Off, V start dropping due to discharge over time
			
		vSOA		+= 100e-3;
		vSDS		+= 100e-3;
		vsoa[i]		= vSOA;
		vsds[i]		= vSDS;

		//Setup to measure SOA/SDS - Primary
 		tmu_6->close_relay(TMU_HIZ_DUT1);    // Connect TMU HIZ to Drain 

		tmu_6->start_trigger_setup(3.0, NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->stop_trigger_setup(3.4,	NEG_SLOPE, TMU_HIZ, TMU_IN_10V);
		tmu_6->start_holdoff(10,TRUE);
		tmu_6->stop_holdoff(10,TRUE);

		Open_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
		Close_relay(K9);	//Drain to CT2+						//mux-5-1
		Close_relay(K7);	//CT2+	to 2ohm pull-up by PVI		//mux-4-3
		Close_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
 		wait.delay_10_us(250);

		//Power_Up_Primary_Normal_Mode();
		VBPP_Power_Up_w_Test_Mode(gTM1_p, ILIM_NORM);

		D_dvi->set_current(D_ch, 0.1e-6,	RANGE_300_MA);		
		D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	

		D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
		D_dvi->set_voltage(D_ch, vSOA, 		VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(40);	// JD delay critical, must be >280us for test to work

		pv3_4->charge_off();	
		pv3_4->close_switch(PV3_LOW_FORCE_2);
		pv3_4->close_switch(PV3_LOW_SENSE_2);
		pv3_4->close_switch(PV3_HIGH_FORCE_3);
		pv3_4->close_switch(PV3_HIGH_SENSE_3);
		wait.delay_10_us(250);
		pv3_4->set_meas_mode(PV3_MEASURE_VOLTAGE);		
		pv3_4->set_voltage(vSOA, RANGE_100_V);	//Size3(6V), Size7(15V)
		pv3_4->set_current(10.0);
		pv3_4->drive_on(); 

		//Start capture here for size 7 device
		Gage_Start_Capture( );	//Wait for trigger here for SOA

		//DEBUG=1;
		//if(DEBUG==1)	////////
		Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set

		WAVE_NAME =  "SOA_TW50_P";
		Gage_Find_SOA(&SOA_P, &TW50_P);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing

		// Turn off gage
		pv3_4->drive_off();	
		wait.delay_10_us(40);
		pv3_4->set_voltage(0.0, RANGE_100_V);
		pv3_4->set_current(0.0);
		pv3_4->open_switch(PV3_LOW_FORCE_2);
		pv3_4->open_switch(PV3_LOW_SENSE_2);
		pv3_4->open_switch(PV3_HIGH_FORCE_3);
		pv3_4->open_switch(PV3_HIGH_SENSE_3);
		pv3_4->charge_on();	
		
		soa_p[i]	= SOA_P;
		tw50_p[i]	= TW50_P;
	
		//Power Down
		D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
		Power_Down_Primary();
		wait.delay_10_us(150);
		
		if(SOA_P > 990.0)
			SOA_P/=1e6;			// For datalog purpose
		if(TW50_P > 990.0)
			TW50_P/=1e6;		// For datalog purpose
		
		////Datalog
		//PiDatalog(func, A_TW50_P,	TW50_P,		set_fail_bin,	POWER_NANO);
		//PiDatalog(func, A_SOA_P,	SOA_P,		set_fail_bin,	POWER_MICRO);

		Close_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
		Open_relay(K9);		//Drain to CT2+						//mux-5-1
		Open_relay(K7);		//CT2+	to 2ohm pull-up by PVI		//mux-4-3
		wait.delay_10_us(250);

		//Delay require for SOA-S and SDS-S test
		if(MOSFET_SIZE == 2)
			delay(5);		//Delay for relays and PVI to fully charged again.
		else
			delay(10);		//need to verify with size 4 and 7 devices

		//*************************************************************************************************************
		//**********  SOA-S  ******************************************************************************************
		//*************************************************************************************************************
		SyncHS_PowerUp_Secondary_in_Test_Mode_SKIP_WAITnLISTEN(High_Vd_Input, ILIM_INCR);
		//******* Handshake done ********
		wait.delay_10_us(150);
		
		//////////
		REQ_ovi->set_voltage(REQ_ch, 0.0,	RANGE_2_V);	// OVI_1_2	"Force device to stop switching while 2ndary in control"
		wait.delay_10_us(5);

		D_dvi->set_current(D_ch, 0.1e-3,	RANGE_300_MA);		
		D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
		
		pv3_4->charge_off();
		pv3_4->close_switch(PV3_LOW_FORCE_2);
		pv3_4->close_switch(PV3_LOW_SENSE_2);
		pv3_4->close_switch(PV3_HIGH_FORCE_3);
		pv3_4->close_switch(PV3_HIGH_SENSE_3);
		wait.delay_10_us(100);

		Close_relay(K7);	//CT2+	to 2ohm pull-up by PVI		//mux-4-3
		Open_relay(K3);		//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0
		Close_relay(K9);	//Drain to CT2+						//mux-5-1
		wait.delay_10_us(250);
		
		D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
		D_dvi->set_voltage(D_ch, vSOA, 		VOLT_50_RANGE);	// DVI_11_0	
		wait.delay_10_us(50);	// Must be >300us

		Vref_cmp = 6.0;
	//	Vref_cmp = 8.0;

		/*if(MOSFET_SIZE == 4 || MOSFET_SIZE == 2)
			ovi_1->set_voltage(OVI_CHANNEL_4, Vref_cmp, AUTORANGE);		//CMP Vref for FW output
		if(MOSFET_SIZE >= 6)
			ovi_1->set_voltage(OVI_CHANNEL_4, Vref_cmp, AUTORANGE);		//CMP Vref for FW output
		if(MOSFET_SIZE >= 7)*/
		ovi_1->set_voltage(OVI_CHANNEL_4, Vref_cmp, AUTORANGE);		//CMP Vref for FW output

		pv3_4->set_meas_mode(PV3_MEASURE_VOLTAGE);	
		pv3_4->set_voltage(vSOA, RANGE_100_V);
		pv3_4->set_current(10.0);
		wait.delay_10_us(10);

		pv3_4->drive_on(); 
		wait.delay_10_us(50);

		Gage_Start_Capture( );			//Wait for trigger here for SOA

		REQ_ovi->set_voltage(REQ_ch, gCV_Low,	RANGE_2_V);	// OVI_1_2	"Force device to stop switching while 2ndary in control"

		//DEBUG=1;
		//if(DEBUG==1)	////////
		Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set
			
		//Expect SR pin to be switching at SOA timing
		WAVE_NAME =  "SOA_TW50_S";
		Gage_Find_SOA(&SOA_S, &TW50_S);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing

		REQ_ovi->set_voltage(REQ_ch, 0.0,	RANGE_2_V);	// OVI_1_2	"Force device to stop switching while 2ndary in control"
		wait.delay_10_us(15);
		//pv3_4->drive_off();
		
		//if (gCHAR_FLOW)
		if (1)
		{
			pv3_4->set_voltage(vSDS, RANGE_100_V);
			D_dvi->set_voltage(D_ch, vSDS, 		VOLT_50_RANGE);	// DVI_11_0	
			//pv3_4->drive_on(); 
			wait.delay_10_us(20);

			Gage_Start_Capture( );			//Wait for trigger here for SOA

			// Turn on again
			REQ_ovi->set_voltage(REQ_ch, gCV_Low,	RANGE_2_V);	// OVI_1_2	"Force device to stop switching while 2ndary in control"
			DEBUG=0;
			//if(DEBUG==1)	////////
			Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set
			
			//Expect SR pin to be switching at SOA timing
			WAVE_NAME =  "SDS_TW50_S";
			//Gage_Find_SDS(&SDS_S, &TW50_SDS_S);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing

			REQ_ovi->set_voltage(REQ_ch, 0.0,	RANGE_2_V);	// OVI_1_2	"Force device to stop switching while 2ndary in control"
			wait.delay_10_us(5);
		
			if(SDS_S > 990.0)
				SDS_S/=1e6;			// For datalog purpose
			if(TW50_SDS_S > 990.0)
				TW50_SDS_S/=1e6;		// For datalog purpose

			////Datalog
			//PiDatalog(func, A_SDS_S,	SDS_S,		set_fail_bin,	POWER_MICRO);
			//PiDatalog(func, A_SDS_TW50_S,	TW50_SDS_S,		set_fail_bin,	POWER_NANO);
		}

		// Turn off gage
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
		Power_Down_Secondary();
		Power_Down_Primary();
		wait.delay_10_us(10);

		sds_s[i]	= SDS_S;
		tw50_sds_s[i]= TW50_SDS_S;

		if(SOA_S > 990.0)
			SOA_S/=1e6;			// For datalog purpose
		if(TW50_S > 990.0)
			TW50_S/=1e6;		// For datalog purpose

		////Datalog
		//PiDatalog(func, A_SOA_S,	SOA_S,		set_fail_bin,	POWER_MICRO);
		//PiDatalog(func, A_TW50_S,	TW50_S,		set_fail_bin,	POWER_NANO);
		
		Open_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
		Close_relay(K9);	//Drain to CT2+						//mux-5-1
		Close_relay(K7);	//CT2+	to 2ohm pull-up by PVI		//mux-4-3
		Close_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
		wait.delay_10_us(250);

		soa_s[i]	= SOA_S;
		tw50_s[i]	= TW50_S;

		//if (gCHAR_FLOW)
		if (1)
		{
			delay(95);		//need to verify with size 4 and 7 devices

			//Power_Up_Primary_Normal_Mode();
			VBPP_Power_Up_w_Test_Mode(gTM1_p, ILIM_NORM);

			D_dvi->set_current(D_ch, 0.1e-6,	RANGE_300_MA);		
			D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	

			D_dvi->set_current(D_ch, 300e-3,	RANGE_300_MA);		
			D_dvi->set_voltage(D_ch, vSDS, 		VOLT_50_RANGE);	// DVI_11_0	
			wait.delay_10_us(250);	// Must be >1.2ms

			pv3_4->charge_off();	
			pv3_4->close_switch(PV3_LOW_FORCE_2);
			pv3_4->close_switch(PV3_LOW_SENSE_2);
			pv3_4->close_switch(PV3_HIGH_FORCE_3);
			pv3_4->close_switch(PV3_HIGH_SENSE_3);
			pv3_4->set_meas_mode(PV3_MEASURE_VOLTAGE);		
			pv3_4->set_voltage(vSDS, RANGE_100_V);	//Size3(6V), Size7(15V)
			pv3_4->set_current(10.0);
			pv3_4->drive_on(); 

			//DEBUG=1;
			//if(DEBUG==1)	////////
			//Start capture here
			Gage_Start_Capture( );			//Wait for trigger here for SOA

			Gage_Wait_For_Capture_Complete();	//capture wait loop after capture has been started, Gage_trig_ok status is set

			WAVE_NAME =  "SDS_TW50_P";
			//Gage_Find_SDS(&SDS_P, &TW50_SDS_P);	//Use the last two pulses to determine Off-Time and the last pulse for TW50 timing

			// Turn off gage
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
			D_dvi->set_voltage(D_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_0	
			Power_Down_Primary();
			wait.delay_10_us(15);

			if(SDS_P > 990.0)
				SDS_P/=1e6;			// For datalog purpose
			if(TW50_SDS_P > 990.0)
				TW50_SDS_P/=1e6;	// For datalog purpose

			////Datalog
			//PiDatalog(func, A_SDS_TW50_P,	TW50_SDS_P,		set_fail_bin,	POWER_NANO);
			//PiDatalog(func, A_SDS_P,	SDS_P,		set_fail_bin,	POWER_MICRO);
			
			sds_p[i]	= SDS_P;
			tw50_sds_p[i]= TW50_SDS_P;
		}

		//Require some delay for PVI to be charged.  
		//Size 2 does not require delay.
		if(MOSFET_SIZE == 4 || MOSFET_SIZE >= 7)
			delay(5);

		//Power Down
		VPIN_ovi->set_voltage(VPIN_ch, 0.0,		RANGE_10_V);	// OVI_1_1
 		BPP_ovi->set_voltage(BPP_ch, 0.0, 	RANGE_10_V);	// OVI_1_0
		BPS_dvi->set_voltage(BPS_ch, 0.0, 	VOLT_10_RANGE);	// DVI_9_1
		REQ_ovi->set_voltage(REQ_ch, 0.0,	RANGE_2_V);	// OVI_1_2	
		VO_dvi->set_voltage(VO_ch, 0.0, 	VOLT_5_RANGE);	// DVI_9_0

		pv3_4->set_voltage(0, RANGE_3_V);

		//	connect PV3 to drain ILIM
		pv3_4->open_switch(PV3_LOW_FORCE_2);
		pv3_4->open_switch(PV3_LOW_SENSE_2);
		pv3_4->open_switch(PV3_HIGH_FORCE_3);
		pv3_4->open_switch(PV3_HIGH_SENSE_3);

		ddd_7->ddd_stop_pattern();								//Need to do a stop pattern when you don't want ddd looping
		wait.delay_10_us(10); 
		Open_relay(K9);
		Open_relay(K7);
		Open_relay(K17);
		Open_relay(K3);
		Disconnect_InvSyn_IM();

		pv3_4->drive_off();	
		delay(1);
		pv3_4->charge_on();	

		Power_Down_Primary();
		Power_Down_Secondary();
		wait.delay_10_us(50);

		Open_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
		Close_relay(K9);	//Drain to CT2+						//mux-5-1
		Close_relay(K7);	//CT2+	to 2ohm pull-up by PVI		//mux-4-3
		Close_relay(K3);	//Drain to L1 to 50ohm to K2NC to K1NC to DVI-11-0 (delay is inside power-up)
		delay(3);
	}

	char DumpFileName[4096];
	strcpy( DumpFileName,"e:\\dl4\\SOAvsVoltage.txt");
	dumparray.open( DumpFileName, ios::app );
	dumparray << "SOA vs. Voltage" << endl;
	dumparray << "Point" << '\x009' << "VSOA" << '\x009' << "SOA_S" << '\x009' << "TW50_S" << '\x009' << "SOA_P" << '\x009' << "TW50_P" << '\x009'<< "VSDS" << '\x009'<< "SDS_S" << '\x009' << "TW50_SDS_S" << '\x009' << "SDS_P" << '\x009' << "TW50_SDS_P" << '\x009' << endl;
	for( i = 0; i < 400; i++)
	dumparray << i << '\x009' << vsoa[i] << '\x009' << soa_s[i] << '\x009' << tw50_s[i] << '\x009' << soa_p[i] << '\x009' << tw50_p[i] << '\x009'<< vsds[i] << '\x009' << sds_s[i] << '\x009' << tw50_sds_s[i] << '\x009' << sds_p[i] << '\x009' << tw50_sds_p[i] << '\x009' << endl;
	dumparray.close();

}

void VBPP_Negative_Cycle()
{
	if(gSiliconRev_P<3)
	{
		BPP_ovi->set_current(BPP_ch, 3e-3,		RANGE_3_MA);
		BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0 
		wait.delay_10_us(5);
		BPP_ovi->set_voltage(BPP_ch, -1.0, 		RANGE_10_V);	// OVI_1_0 
		delay(1);	
		BPP_ovi->set_voltage(BPP_ch, 0.0, 		RANGE_10_V);	// OVI_1_0 
		wait.delay_10_us(10);
	}
}


void search_VBPP_th_B3( float* vBPP_pV, float* vBPP_m, float* vBPP_p, float* vBPP_p_iHVoff, float* vBPP_vshuntPUseq, float* vBPP_s)
{	
/********************************************************************************************************************************
 *		Priamry: vBPP_PV (1.4mA) --> vBPP_M (-5mA) --> vBPP_P (-1.2mA) --> vBPP_P_iHVoff (200uA) --> vBPP_ShuntPUseq			*
 *																																*
 * 1. Drain=0, BPP=5.0, IBPP=220uA, increase BPP until IBPP jumps to 1.4mA														*
 *    (this is around BPP=5.4V the first level when first powering up.  This is not the VBPP-P, a Vpin threshold for Testmodes)	*
 * 2. Bring BPP down to 5V, turn on Drain=50V through 1K load, IBPP is still positive around 1.2mA,								*
 *    decrease BPP down until IBPP flip sign from 0.6mA to -5mA (this is around 4.5V the first level when BPP goes down VBPP-M)	*
 * 3. Increase BPP to around 5V VBPP-P to see device starts switching															*
 *    (this is the level after 2nd time raise BPP up) IBPP around -1.2mA														*
 * 4. Increase BPP to around 5.1V to see IBPP drops to +200uA (this is where the high-voltage current source turns off)			*
 * 5. Increase BPP to around 5.4V VBPP-shunt when the device stops switching and IBPP = 11.3mA > 10mA (DE don't need this)		*
 ********************************************************************************************************************************/

	float imeas=0, vfrc=0, vstep=0, vramp_pt=0;
	float vstart=0, vstop=0, vBPP_P_Expect=0;
	float ich_th=0;
	int   lcnt1=0, lcnt2=0, rcnt =0;
	float vmeas=0;
	int	  i=0;

	int		dly_BPP_p47uF, dly_BPP_4p7uF;

	dly_BPP_p47uF = 1; //ms
	dly_BPP_4p7uF = 3; //ms

	//vBPP_P_Expect = 5.0;	//B2 and older material
	vBPP_P_Expect = 5.5;	//B3 and newer material

	VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
	//BPP_ovi->set_voltage(BPP_ch, gVBPP_Low_Voltage_PU, 		RANGE_10_V);	// OVI_1_0	
	BPP_ovi->set_current(BPP_ch, 30e-3,		RANGE_30_MA);   
	BPP_ovi->set_meas_mode(BPP_ch,			OVI_MEASURE_CURRENT);
	wait.delay_10_us(30);

// ** VBPP_PV
	lcnt1 =0;
	lcnt2 =0;
	ich_th = 1.3e-3;			// threshold to decide if device is switching or not

	if (OPCODE==4400)
	{
		VBPP_ramp_up(gVBPP_Low_Voltage_PU, 3.0, 100e-3);    //BPP ramp up from 0V to 4.5V in 100mV step    (Needed for -40C)
	
	}
	else
	{
		VBPP_ramp_up(gVBPP_Low_Voltage_PU, 4.5, 100e-3);    //BPP ramp up from 0V to 4.5V in 100mV step    (Needed for -40C)
	}
	//VBPP_ramp_up(0, 4.5, 100e-3);	//BPP ramp up from 0V to 4.5V in 100mV step
	//if(BPP_4p7uF) delay(3);
	//if(BPP_p47uF) delay(1);
	imeas = BPP_ovi->measure_average(5);

	//delay(1);
	//VBPP_ramp_up(4.5, 5.5, 100e-3);	//BPP ramp up from 0V to 4.5V in 100mV step
	//imeas = BPP_ovi->measure_average(5);

	/*if(DEBUG==1)
	{
		printf("\nsearch_VBPP_PVth: VBPP-PV\n");
		printf("vBPP = %fV, iBPP = %fmA \n", 4.5, imeas*1e3);
	}*/
	//if(DEBUG==1 && imeas > ich_th)
	//{
	//	int i=0;
	//	printf("\nsearch_VBPP_PVth: VBPP-PV\n");
	//	for(i=0; i<10; i++)
	//	{
	//		BPP_ovi->set_voltage(BPP_ch, 4.0+i*100e-3,	RANGE_10_V);
	//		wait.delay_10_us(30);
	//		imeas = BPP_ovi->measure_average(5);	//EXPECT ~0.28mA
	//		printf("vBPP = %fV, iBPP = %fmA \n", 4.0+i*100e-3, imeas*1e3);
	//	}
	//}

	if (imeas >ich_th)
	{	
		*vBPP_pV = 0.0;	
		return;
	}
	//starttime = mytimer.GetElapsedTime();// testtime check
	vstep = 0.1;	// used to be 0.2
	vfrc = 4.5;
	while ((vstep >=0.1) && (vfrc < 5.6) && (lcnt1< 200))
	{
		if (imeas <ich_th)
		{	vfrc+=vstep;
			BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			/*if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);*/
			wait.delay_10_us(5);
			imeas = 0.0;
			if(vfrc > 5.0) 
			{
				imeas = BPP_ovi->measure_average(5);
			}
			if(DEBUG==1)
				printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);

		}
		else			
		{	// Reset device and reduce searching step
			//vfrc -=  1.25* vstep;	// Back down 1.25 step
			vfrc -=  2.00* vstep;	// Back down 2.00 step
			vstep = 0.0025;			// Fine search, used to be 0.01
			// Reset device
			//VBPP_ramp_down(3, gVBPP_Low_Voltage_PU, 0.05);
			BPP_ovi->set_voltage(BPP_ch, 0.0,		RANGE_10_V);			// Starting search point
			wait.delay_10_us(10);

			//VBPP_ramp_up(gVBPP_Low_Voltage_PU, vfrc, 50e-3);	//BPP ramp up from 0V to vfrc in 50mV step
			VBPP_ramp_up(0.0, vfrc, 50e-3);	//BPP ramp up from 0V to vfrc in 50mV step
			/*if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);*/
			imeas = 0.0;
			if(vfrc > 5.0)
			{
				imeas = BPP_ovi->measure_average(5);				//expect device not switching here.
			}
				/*if(DEBUG==1)
				printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);*/
			if (imeas >ich_th)
			{	
				*vBPP_p = -1.0;	
				return;
			}
			while ((imeas < ich_th) && (lcnt2<100) && (vfrc <5.5) )
			{	vfrc+=vstep;
				BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
				/*if(BPP_4p7uF) delay(3);
				if(BPP_p47uF) delay(dly_BPP_p47uF);*/

				wait.delay_10_us(5);
				imeas = 0.0;
				if(vfrc > 5.0)
				{
					imeas = BPP_ovi->measure_average(5);
				}
				if(DEBUG==1)
					printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
				lcnt2++;
			}
		} 
		lcnt1 ++;
	}

	*vBPP_pV = vfrc;


// ** VBPP_M

	D_dvi->set_voltage(D_ch,	 45,		VOLT_50_RANGE); 
	D_dvi->set_meas_mode(D_ch, DVI_MEASURE_VOLTAGE);
	wait.delay_10_us(5);
	while(vmeas<44 && i<50)			//vDrain has to be high in order for vBPP_M to work properly
	{
		vmeas = D_dvi->measure();
		i++;
	}

	lcnt1 =0;	
	lcnt2 =0;
	ich_th = 0.7e-3;

	BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
	wait.delay_10_us(15);	// JD was 5, tester correlation
			/*if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);*/
	imeas = BPP_ovi->measure_average(15);	// JD was 5, tester correlation
	/*if(DEBUG==1)
	{
		printf("\nsearch_VBPP_th: VBPP-M\n");
		printf("vBPP = %fV, iBPP = %fmA \n", vfrc, imeas*1e3);
	}*/

	if (imeas <ich_th || vmeas<44)
	{	
		*vBPP_m = 0.0;	
		return;
	}

	vstep = 0.1;
	while ((vstep >=0.1) && (vfrc > 3.0) && (lcnt1< 200))
	{
		if (imeas >ich_th)
		{	vfrc-=vstep;
			BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
			wait.delay_10_us(5);
			imeas = BPP_ovi->measure_average(5);	
			if(DEBUG==1)
				printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);
		}
		else			
		{	
			vstep = 0.0025;			// Fine search
			ich_th = 0;
			while ((imeas > ich_th) && (vfrc > 3.0) && (lcnt2<200))
			{	vfrc-=vstep;
				BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
				wait.delay_10_us(15);	// JD was 5, tester correlation
				imeas = BPP_ovi->measure_average(15);	// JD was 5, tester correlation
				if(DEBUG==1)
					printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
			
				lcnt2++;
			}
		} 
		lcnt1 ++;
	}
	*vBPP_m = vfrc;

if (*vBPP_m < 0.0) 
	*vBPP_m =0.0;


// ** VBPP_P
	lcnt1 =0;
	lcnt2 =0;
	ich_th = -2e-3;			// threshold to decide if device is switching or not
	vstep = 0.1;	// used to be 0.2

	BPP_ovi->set_voltage(BPP_ch, vfrc-10e-3,	RANGE_10_V);
	wait.delay_10_us(5);
	imeas = BPP_ovi->measure_average(5);

	while ((vstep >=0.1) && (vfrc < 6.0) && (lcnt1< 200))
	{
		if ( imeas<ich_th && vfrc<(vBPP_P_Expect-100e-3) )
		{	vfrc+=vstep;
			BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
			wait.delay_10_us(5);
			imeas = BPP_ovi->measure_average(5);
			if(DEBUG==1 && *vBPP_pV<0.1)
				printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt1 = %i \n", vfrc, imeas*1e3, vstep, lcnt1);

		}
		else			
		{	
			vstep = 0.0025;			// Fine search, used to be 0.01
			while ((imeas < ich_th) && (lcnt2<100) && (vfrc <6.0) )
			{	vfrc+=vstep;
				BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
			if(BPP_4p7uF) delay(3);
			if(BPP_p47uF) delay(dly_BPP_p47uF);
				wait.delay_10_us(5);
				imeas = BPP_ovi->measure_average(5);
				if(DEBUG==1 && *vBPP_pV<0.1)
					printf("vBPP = %fV, iBPP = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
				lcnt2++;
			}
		} 
		lcnt1 ++;
	}

	*vBPP_p = vfrc;



////4. Increase BPP to around 5.1V to see IBPP drops to +200uA (this is where the high-voltage current source turns off)			*
//// ** VBPP_P_iHVoff
//	lcnt1 =0;
//	lcnt2 =0;
//	ich_th = 170e-6;	//change from -1.2mA to 200uA.  170uA set as threshold
//
//	vstep = 2.5e-3;		
//	while ((imeas < ich_th) && (lcnt2<100) && (vfrc <5.5) )
//	{	vfrc+=vstep;
//		BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
//			if(BPP_4p7uF) delay(3);
//			if(BPP_p47uF) delay(dly_BPP_p47uF);
//		wait.delay_10_us(15);	// JD was 5, tester correlation
//		imeas = BPP_ovi->measure_average(15);	// JD was 5, tester correlation
//		if(DEBUG==1)
//			printf("vBPP_P_iHVoff = %fV, iBPP = %fmA, vstep = %fV, lcnt2 = %i \n", vfrc, imeas*1e3, vstep, lcnt2);
//		lcnt2++;
//	}
//
//	*vBPP_p_iHVoff = vfrc;

//////5. Increase BPP to around 5.4V VBPP-shunt when the device stops switching and IBPP = 11.3mA > 10mA							*
////	lcnt1 =0;
////	lcnt2 =0;
////	ich_th = 10e-3;	//change from 200uA to 11.3mA  (10mA set as threshold)
////	vfrc	= *vBPP_pV - 50e-3;	//Start at a closer threshold for Vshunt.
////
////	vstep = 2.5e-3;		
////	while ((imeas < ich_th) && (lcnt2<100) && (vfrc <6.0) )
////	{	vfrc+=vstep;
////		BPP_ovi->set_voltage(BPP_ch, vfrc,	RANGE_10_V);	// Starting search point
////			if(BPP_4p7uF) delay(3);
////			if(BPP_p47uF) delay(dly_BPP_p47uF);
////		wait.delay_10_us(5);
////		imeas = BPP_ovi->measure_average(5);
////		if(DEBUG==1)
////			printf("vBPP_vshunt_PUseq=%fV, iBPP=%fmA, vstep=%fV, lcnt2=%i \n", vfrc, imeas*1e3, vstep, lcnt2);
////		lcnt2++;
////	}
////	*vBPP_vshuntPUseq = vfrc;
}

void search_CV_vVOUTth_AR_binary(float *vVOUTth_AR_S, float *AR_tVOUT_S)
{
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *							Secondary: vVOUTth_AR_S									  *
 *vVOUTth_AR_S:																		  *
 *  In order to find vVOUTth_AR_S, power up secondary with Vout at 0V, secondary is not SW.*
 *  use TMU to find if switching
 *	VOUT=vfrc_lo, secondary is not SW.
 *  VOUT=vfrc_hi, secondary is switching
 *  Reduce VOUT until device stops switching
 *  Record threshold
 *  Increase VOUT to switching level (above AR threshold)
 *	Loop until device starts switching again
 *  Record time until switching resumes
 *  Return threshold vOUTth_AR_S                                                       *
 *  Return test time to finish searches AR_tVOUT_S

	We know that Vout is about 4x of vFB.
	Knowing vFB_SC is supposed to be ~100mV, we expect vVout_SC to be ~400mV
 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
	float imeas=0, vstep=0, vramp_pt=0;
	float ich_th=0, IBPS_sw=0;
	float iBPS_meas[200] = {0.0};
	float Vfb_meas[200] = {0.0};
	int   lcnt=0;
	float vfrc_hi=0, vfrc_lo=0, vmid=0;
	float tmeas=0, t_hi=0, t_lo=0, tmeas1=0;
	float starttime=0, stoptime=0;

	Pulse pulse(PULSE_RISING_EDGE,10e-6);			//external trigger pulse from dvi for debug
	//////////

	//BPS_dvi->set_meas_mode(BPS_ch,			DVI_MEASURE_CURRENT);
	//wait.delay_10_us(10);

	//Vout set lower than 3.25V so device will go into ARST after tVo(AR), which is ~100ms or ~120ms
	//VO_dvi->set_voltage(VO_ch, gCV_Low*4.0, 		VOLT_10_RANGE);	// DVI_9_0
	VO_dvi->set_voltage(VO_ch, 1.0, 		VOLT_10_RANGE);	// DVI_9_0	(vout set lower than 30% of 5V '1.5V')
	//REQ_ovi->set_voltage(REQ_ch, gCV_Low, 		RANGE_2_V);	// OVI_1_2	
	REQ_ovi->set_voltage(REQ_ch, 0.0, 		RANGE_2_V);	// OVI_1_2	
	//disconnect FB
	ovi_1->disconnect(REQ_ch);	
	wait.delay_10_us(100);		//If trap point set here, you will see device switch for 48ms (AR_timer) and turn OFF

	//IBPS_sw = BPS_dvi->measure_average(15);	   // For debug (Positive current)
	if(g_TurretCB)
	{
		vfrc_hi=0.17*4.0; //HL changed from 0.15 to 0.17 to fix repeatability on Turret CB
	}
	else
	{
		vfrc_hi=0.15*4.0;
	}
	vfrc_lo=0.05*4.0;	//Vout voltage is fb voltage multiplied by 4
	ich_th = 0.0015;				// 1mA
//	t_hi = 40e-6;
	t_hi = 55e-6;
	t_lo = 15e-6;



//////////

	//VO=vfrc_lo
	VO_dvi->set_voltage(VO_ch, vfrc_lo, 		VOLT_10_RANGE);	// DVI_9_0
	starttime = mytimer.GetElapsedTime();
	wait.delay_10_us(50);
	delay(1);
//////////

	// Device should not be switching
//	imeas = BPS_dvi->measure_average(15);	// Device should not be switching
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(20);				// Wait for TMU
	tmeas = tmu_6->read(200e-6);
//	if (imeas >ich_th)			//TRUE if device is switching
	if (tmeas > t_lo && tmeas < t_hi)			//TRUE if device is switching
	{	
		*vVOUTth_AR_S = 0.0;	
		starttime = -199;
		if (DEBUG && gDEBUG)
			printf("  search_CV_vVOUTth_AR_binary: Device should not be switching initially\n");
		return;
	}

	//VOUT=vfrc_hi
	//REQ_ovi->set_voltage(REQ_ch, vfrc_hi, 		RANGE_2_V);	// OVI_1_2
	VO_dvi->set_voltage(VO_ch, vfrc_hi, 		VOLT_10_RANGE);	// DVI_9_0
	if(g_TurretCB)
	{
		wait.delay_10_us(500); //HL changed timing as well for Turret CB
	}
	else
	{
		wait.delay_10_us(20);
	}

	// Device should be switching
	//	imeas = BPS_dvi->measure_average(15);	// Device should be switching
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(20);				// Wait for TMU
	tmeas = tmu_6->read(200e-6);
	//	if (imeas >ich_th)			//TRUE if device is switching
	if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is switching
	{	
		*vVOUTth_AR_S = 0.9999;	// To avoid over range on OVI_2V_Range
		if (DEBUG && gDEBUG)
			printf("  search_CV_vVOUTth_AR_binary: Device should be switching\n");
		return;
	}

	//Reduce VOUT until device stops switching
	while ( ((vfrc_hi-vfrc_lo) >= 0.001) && (lcnt < 15) )
	{
		vmid = (vfrc_hi+vfrc_lo)/2;		
		//REQ_ovi->set_voltage(REQ_ch, vmid, 		RANGE_2_V);	// OVI_1_2
		VO_dvi->set_voltage(VO_ch, vmid, 		VOLT_10_RANGE);	// DVI_9_0
		wait.delay_10_us(50);
	//	imeas = BPS_dvi->measure_average(15);	// Device should be switching
		tmu_6->arm();						// Device doing auto-restart
		wait.delay_10_us(20);				// Wait for TMU
		tmeas = tmu_6->read(200e-6);
	//	if (imeas>ich_th)
		if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is not switching
		{
			vfrc_lo = vmid;
			if (DEBUG && gDEBUG)
				printf("  search_CV_vOUTth_AR_binary LOOP: VO= %.3fV, tmeas= %.1fus (DUT NOT switching)\n",vmid , tmeas);
		}
		else
		{
			vfrc_hi = vmid;
			if (DEBUG && gDEBUG)
				printf("  search_CV_vOUTth_AR_binary LOOP: VO= %.3fV, tmeas= %.1fus (DUT IS switching)\n",vmid , tmeas);
		}
			
		lcnt++;
	}

	//result
	*vVOUTth_AR_S = vmid;	
//////////

	//Increase VFB to switching level (above AR threshold)
	//REQ_ovi->set_voltage(REQ_ch, vmid + 0.2, 		RANGE_2_V);	// OVI_1_2
	VO_dvi->set_voltage(VO_ch, vmid + 0.8, 		VOLT_10_RANGE);	// DVI_9_0
	wait.delay_10_us(50);

	// Device should not be switching after AR threshold measurement
	//	imeas = BPS_dvi->measure_average(15);	// Device should be switching
	tmu_6->arm();						// Device doing auto-restart
	wait.delay_10_us(20);				// Wait for TMU
	tmeas = tmu_6->read();
	if (tmeas < t_lo || tmeas > t_hi)			//TRUE if device is NOT switching
	{	
		*AR_tVOUT_S = 0.9999;	// To avoid over range on OVI_2V_Range
		if (DEBUG && gDEBUG)
			printf("  search_CV_vVOUTth_AR_binary: Device should not be switching after AR found\n");
		return;
	}
	lcnt=0;
	
	//Loop until device starts switching again
	while ((tmeas > t_lo && tmeas < t_hi)&& lcnt < 1000)	//1000 cnt => 1000 * 150us = 150ms
	{
		stoptime = mytimer.GetElapsedTime();
		tmu_6->arm(); 
		wait.delay_10_us(15);
		tmeas = tmu_6->read(150e-6); 
		lcnt++;
	}

//////////

	//save time until switching starts again
	*AR_tVOUT_S = (stoptime - starttime)*1e-6;

	if (DEBUG && gDEBUG)
		printf("  search_CV_vVOUTth_AR_binary: Device starts switching again after %.1f ms \n",*AR_tVOUT_S*1e3);

	VO_dvi->set_voltage(VO_ch, 5.0, 	VOLT_5_RANGE);						// Vout > ARSTth so part switches

	//connect FB
	ovi_1->connect(REQ_ch);

}

void Check_InvSync_Circuit(int *Check_pass_fail)
{
	*Check_pass_fail = 0;

	Close_relay(MUX_BANK_3_4);
	Close_relay(MUX_4_GND);
	Close_relay(MUX_BANK_5_6);
	Close_relay(MUX_6_GND);
	Close_relay(MUX_7_GND);
	Close_relay(MUX_8_GND);
	mux_20->close_relay(MUX_BANK_1_2);
	mux_20->close_relay(MUX_2_GND);
	delay(5);

	float vmeas_high=0, vmeas_low=0;
	
	//This test must have Handtest or CB in place in order for it to work

	//FW setup to measure InvSyn_IM_OUT
	dvi_11->set_voltage(DVI_CHANNEL_1, 5.0, VOLT_5_RANGE);
	dvi_11->set_current(DVI_CHANNEL_1, 0.0, RANGE_30_MA);
	dvi_11->set_meas_mode(DVI_CHANNEL_1, DVI_MEASURE_VOLTAGE);
	dvi_11->open_relay(CONN_FORCE1);
	Close_relay(K18);

	Close_relay(K3);
	Close_relay(K8);	//Connect InvSyn_IM_IN  to Drain
	Close_relay(K19);	//Connect InvSyn_IM_OUT to FW pin
	delay(4);


	if(LB_Rev==7)
	{

		//GND pin set to negative voltage so OUT will go negative
		ovi_1->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA);
		ovi_1->set_voltage(OVI_CHANNEL_6, -1.0, VOLT_5_RANGE);	
		//+IN pin (set 3V and ends up with 1.5V at +IN pin)
		//InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3,	RANGE_30_MA);
		//InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.0,		VOLT_20_RANGE);	
		ovi_1->set_current(OVI_CHANNEL_4, 30e-3, RANGE_30_MA);
		ovi_1->set_voltage(OVI_CHANNEL_4, 3.0, VOLT_5_RANGE);

		//Setup to measure Low(Negative) from InvSync_IM_OUT
			//-IN pin (5V)
			dvi_11->set_voltage(DVI_CHANNEL_0, 5.0, VOLT_5_RANGE);
			dvi_11->set_current(DVI_CHANNEL_0, 5e-3, RANGE_30_MA);
			wait.delay_10_us(50);
			vmeas_low = dvi_11->measure_average(25);
			printf("InvSyn Check vmeas_low = %.2f V.  Expect lower than -0.4V\n", vmeas_low);
		//Setup to measure High from InvSync_IM_OUT
			//-IN pin (0V)
			dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_5_RANGE);
			wait.delay_10_us(50);
			vmeas_high = dvi_11->measure_average(25);
			printf("InvSyn Check vmeas_high = %.2f V.  Expect higher than 3.5V\n", vmeas_high);

		if(vmeas_high > 3.5 && vmeas_low < -0.4)
			*Check_pass_fail = 1;
	}
	else
	{
			//GND pin set to negative voltage so OUT will go negative
			ovi_1->set_current(OVI_CHANNEL_6, 30e-3, RANGE_30_MA);
			ovi_1->set_voltage(OVI_CHANNEL_6, -1.0, VOLT_5_RANGE);	
			//+IN pin (set 3V and ends up with 1.5V at +IN pin)
			//InvSyn_REF_ovi->set_current(InvSyn_ch, 30e-3,	RANGE_30_MA);
			//InvSyn_REF_ovi->set_voltage(InvSyn_ch, 3.0,		VOLT_20_RANGE);	
			ovi_1->set_current(OVI_CHANNEL_4, 30e-3, RANGE_30_MA);
			ovi_1->set_voltage(OVI_CHANNEL_4, 3.0, VOLT_5_RANGE);

			//Setup to measure Low(Negative) from InvSync_IM_OUT
			//-IN pin (5V)
			dvi_11->set_voltage(DVI_CHANNEL_0, 9.0, VOLT_10_RANGE);
			dvi_11->set_current(DVI_CHANNEL_0, 5e-3, RANGE_30_MA);
			wait.delay_10_us(50);
			vmeas_low = dvi_11->measure_average(25);
			printf("InvSyn Check vmeas_low = %.2f V.  Expect lower than -0.4V\n", vmeas_low);
			//Setup to measure High from InvSync_IM_OUT
			//-IN pin (0V)
			dvi_11->set_voltage(DVI_CHANNEL_0, 0.0, VOLT_5_RANGE);
			wait.delay_10_us(50);
			vmeas_high = dvi_11->measure_average(25);
			printf("InvSyn Check vmeas_high = %.2f V.  Expect higher than 3.5V\n", vmeas_high);

			if(vmeas_high > 3.5 && vmeas_low < -0.4)
				*Check_pass_fail = 1;
	}


	//Reset all above resources
	dvi_11->set_voltage(DVI_CHANNEL_1, 0.0, VOLT_5_RANGE);
	dvi_11->set_current(DVI_CHANNEL_1, 0.0, RANGE_30_MA);
	dvi_11->close_relay(CONN_FORCE1);
	Open_relay(K18);
	Open_relay(K3);
	Open_relay(K8);		//disonnect InvSyn_IM_IN  to Drain
	Open_relay(K19);	//disonnect InvSyn_IM_OUT to FW pin
	delay(3);

	//GND pin 
	ovi_1->set_current(OVI_CHANNEL_6, 0.0,  RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_6, 0.0,  VOLT_5_RANGE);	
	//+IN pin 
	//InvSyn_REF_ovi->set_current(InvSyn_ch, 0.0,	RANGE_30_MA);
	//InvSyn_REF_ovi->set_voltage(InvSyn_ch, 0.0,	VOLT_20_RANGE);	
	ovi_1->set_current(OVI_CHANNEL_4, 0.0e-3, RANGE_30_MA);
	ovi_1->set_voltage(OVI_CHANNEL_4, 0.0, VOLT_5_RANGE);
	wait.delay_10_us(500);
}

void WaitDelay_With_HandShake_Timing(int Offset_Time)
{

		float start_time = 0.0;
		float stop_time  = 0.0;
		int count      = 0;

		//Need to subtract 10 because tmu arm takes at least 10us to execute.
		g_tHandshake_SSS_floating = g_tHandshake_SSS_floating+Offset_Time; 
		start_time = mytimer.GetElapsedTime();

//		while((stop_time-start_time) <= g_tHandshake_SSS_floating)
		while((stop_time-start_time) <= g_tHandshake_SSS_floating && count < 500)	// Fixed the program freeze issue.
		{
			stop_time = mytimer.GetElapsedTime();
			count++;
		}

	////	printf("----------------------------------------------------------\n");
	////	printf("g_tHandshake_SSS measured @ ILIM = %.4f us\n", (g_tHandshake_SSS_floating-Offset_Time));
	////	printf("Actual g_tHandshake_SSS used     = %.4f us\n",  g_tHandshake_SSS_floating);
	////	printf("Number of loop @ 25C             = %i \n", count);				
	////	printf("g_tHandshake_SSS_floating @ 25C  = %.4f us\n", stop_time-start_time);
	////	printf("----------------------------------------------------------\n");


}

void tDable_Powerup()
{
			Power_Down_Secondary();
			Open_relay(K21);	//FW to DDD-7-3
			Close_relay(K18);	//FW to dvi-11-1
			Open_relay(K17);	//REQ to DDD-7-2
			delay(4);
			Powerup_Secondary_in_Testmode(gProgRead_S, 0, 0);

			//HL removed due to cause of repeatability for both RS and Turret.
			//VO_dvi->set_voltage(VO_ch, 0.0, 		VOLT_5_RANGE);	// DVI_9_0  RLB

			Secondary_Vout_Clock_to_Testmode(gProgReadTestMode2_S);

			if(g_TurretCB || LB_Rev>=5 )		BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	
			else								BPS_dvi->set_current(BPS_ch, 290.0e-3,	RANGE_300_MA);	

			VO_dvi->set_current(VO_ch, 200.0e-3,		RANGE_300_MA);	
	
			if (MOSFET_SIZE==8 && gILIM_TARGET_S > 2.2)             //Used DVI from pedestal IM to add more current to PVI.
			{
				if(OPCODE==4300||OPCODE== 4500)		VO_dvi->set_voltage(VO_ch, 1.00, 	VOLT_5_RANGE);
				else								VO_dvi->set_voltage(VO_ch, 1.15, 	VOLT_5_RANGE);// Higher voltages work better for low yield parts
			}
			else
			{
				if(OPCODE==4300||OPCODE== 4500)		VO_dvi->set_voltage(VO_ch, 1.05, 	VOLT_5_RANGE);
				else								VO_dvi->set_voltage(VO_ch, 1.15, 	VOLT_5_RANGE);// Higher voltages work better for low yield parts
			}
	
			FW_dvi->set_voltage(FW_ch, 0.0, 		VOLT_50_RANGE);	// DVI_11_1
			delay(1);
			ddd_7->ddd_set_lo_level(0.1);
			ddd_7->ddd_set_hi_level(4.0);		// FW toggle high to 4V  (per Qing 10/17/2016)
			delay(1);
			
			ddd_7->ddd_run_pattern(Low_XXX_pat_start,	Low_XXX_pat_stop);
			
			wait.delay_10_us(100);
			Close_relay(K21);	//FW to DDD-7-3 (HOT SWAP)
			if(g_TurretCB)  
			{
				FW_dvi->set_current(FW_ch, 0.0e-3,		RANGE_30_MA);
				FW_dvi->set_voltage(FW_ch, 0.1, 		VOLT_50_RANGE);	// DVI_11_1
				delay(1);			
			}
			Open_relay(K18);   // FW disconnect from DVI-11-1 for RS setup.
			delay(4);
			ddd_7->ddd_run_pattern(High_pat_FW_start, High_pat_FW_stop);
			wait.delay_10_us(10);

			//Setup for REQ connects to DDD-7-2
			REQ_ovi->set_current(REQ_ch, 0,						RANGE_30_MA);
			wait.delay_10_us(10);
			Close_relay(K17);	//REQ connect to DDD-7-2 in parallel with 1kohm in series with ovi-1-2
			delay(4);
			//Setup to have FW do request and FW learn pulse then DableON pulse
			ddd_7->ddd_set_lo_level(-0.7);		
			delay(1);
}

//******************************************************************//
//*************   START of Unified Resource Control   **************//
//******************************************************************//
static char VRANGE_CACHE[32] = {-1};
static char IRANGE_CACHE[32] = {-1};

void Set_Vrange(resource_t resource, char force_range)
{
	VRANGE_CACHE[resource] = force_range;
}

void Set_Irange(resource_t resource, char force_range)
{
	IRANGE_CACHE[resource] = force_range;
}

char Get_Vrange(resource_t resource)
{
	return VRANGE_CACHE[resource];
}

char Get_Irange(resource_t resource)
{
	return IRANGE_CACHE[resource];
}

void Set_Default_Vrange()
{
	// *** Primary Side Resources
	VRANGE_CACHE[res_D_dvi]				= RANGE_10_V;	// DVI_11_0		Drain
	VRANGE_CACHE[res_BPP_dvi]			= RANGE_10_V;	// DVI_11_0		BPP for breakdown test
	VRANGE_CACHE[res_BPP_ovi]			= RANGE_10_V;	// OVI_1_0		BPP
	VRANGE_CACHE[res_VPIN_ovi]			= RANGE_10_V;	// OVI_1_1		UV

	// *** Secondary Side Resources
	VRANGE_CACHE[res_FWC_dvi2k]			= RANGE_10_V;	// DVI_13_0		FWC
	VRANGE_CACHE[res_REQ_ovi]			= RANGE_10_V;	// OVI_1_2		REQ
	VRANGE_CACHE[res_BPS_dvi]			= RANGE_10_V;	// DVI_9_1		BPS
	VRANGE_CACHE[res_SR_dvi2k]			= RANGE_10_V;	// DVI_13_1		SR
	VRANGE_CACHE[res_VO_dvi]			= RANGE_10_V;	// DVI_9_0		VO
	VRANGE_CACHE[res_FW_dvi]			= RANGE_10_V;	// DVI_11_1		FW
	VRANGE_CACHE[res_ACK_ovi]			= RANGE_10_V;	// OVI_1_5		ACK

	// *** High Voltage Resources
	VRANGE_CACHE[res_BV_hvs]			= RANGE_1_KV;	// HVS_15		D, UV, FW

	// *** Other Resources
	VRANGE_CACHE[res_InvSyn_REF_ovi]	= RANGE_10_V;	// OVI_1_4		InvSyn_IM reference OVI
	VRANGE_CACHE[res_InvSyn_Offset_ovi]	= RANGE_10_V;	// OVI_1_6		InvSyn_IM GND offset OVI
	VRANGE_CACHE[res_BC_ovi]			= RANGE_10_V;	// OVI_1_3		Buffer Clamp reference OVI
	VRANGE_CACHE[res_Iped_dvi]			= RANGE_10_V;	// DVI_11_0		Pedestal current
}

void Set_Default_Irange()
{
	// *** Primary Side Resources
	IRANGE_CACHE[res_D_dvi]				= RANGE_300_MA;	// DVI_11_0		Drain
	IRANGE_CACHE[res_BPP_dvi]			= RANGE_300_MA;	// DVI_11_0		BPP for breakdown test
	IRANGE_CACHE[res_BPP_ovi]			= RANGE_30_MA;	// OVI_1_0		BPP
	IRANGE_CACHE[res_VPIN_ovi]			= RANGE_30_MA;	// OVI_1_1		UV

	// *** Secondary Side Resources
	IRANGE_CACHE[res_FWC_dvi2k]			= RANGE_200_MA;	// DVI_13_0		FWC
	IRANGE_CACHE[res_REQ_ovi]			= RANGE_30_MA;	// OVI_1_2		REQ
	IRANGE_CACHE[res_BPS_dvi]			= RANGE_300_MA;	// DVI_9_1		BPS
	IRANGE_CACHE[res_SR_dvi2k]			= RANGE_200_MA;	// DVI_13_1		SR
	IRANGE_CACHE[res_VO_dvi]			= RANGE_300_MA;	// DVI_9_0		VO
	IRANGE_CACHE[res_FW_dvi]			= RANGE_300_MA;	// DVI_11_1		FW
	IRANGE_CACHE[res_ACK_ovi]			= RANGE_30_MA;	// OVI_1_5		ACK

	// *** High Voltage Resources
	IRANGE_CACHE[res_BV_hvs]			= RANGE_1_MA;	// HVS_15		D, UV, FW

	// *** Other Resources
	IRANGE_CACHE[res_InvSyn_REF_ovi]	= RANGE_30_MA;	// OVI_1_4		InvSyn_IM reference OVI
	IRANGE_CACHE[res_InvSyn_Offset_ovi]	= RANGE_30_MA;	// OVI_1_6		InvSyn_IM GND offset OVI
	IRANGE_CACHE[res_BC_ovi]			= RANGE_30_MA;	// OVI_1_3		Buffer Clamp reference OVI
	IRANGE_CACHE[res_Iped_dvi]			= RANGE_300_MA;	// DVI_11_0		Pedestal current
}

void Set_Default_VIrange()
{
	Set_Default_Vrange();
	Set_Default_Irange();
}

void Set_V(resource_t resource, float v_in, unsigned long settling_us)
{
	switch (resource)
	{
		// *** Primary Side Resources
		case res_D_dvi:				// DVI_11_0		Drain
			D_dvi->set_voltage(D_ch,		v_in,	VRANGE_CACHE[resource]);
			break;
		case res_BPP_dvi:			// DVI_11_0		BPP for breakdown test
			BPP_DVI->set_voltage(BPP_ch,	v_in,	VRANGE_CACHE[resource]);
			break;
		case res_BPP_ovi:			// OVI_1_0		BPP
			BPP_ovi->set_voltage(BPP_ch,	v_in,	VRANGE_CACHE[resource]);
			break;
		case res_VPIN_ovi:			// OVI_1_1		UV
			VPIN_ovi->set_voltage(VPIN_ch,	v_in,	VRANGE_CACHE[resource]);
			break;

		// *** Secondary Side Resources
		case res_FWC_dvi2k:			// DVI_13_0		FWC
			FWC_dvi2k->set_voltage(FWC_ch,	v_in,	VRANGE_CACHE[resource]);
			break;
		case res_REQ_ovi:			// OVI_1_2		REQ
			REQ_ovi->set_voltage(REQ_ch,	v_in,	VRANGE_CACHE[resource]);
			break;
		case res_BPS_dvi:			// DVI_9_1		BPS
			BPS_dvi->set_voltage(BPS_ch,	v_in,	VRANGE_CACHE[resource]);
			break;
		case res_SR_dvi2k:			// DVI_13_1		SR
			SR_dvi2k->set_voltage(SR_ch,	v_in,	VRANGE_CACHE[resource]);
			break;
		case res_VO_dvi:			// DVI_9_0		VO
			VO_dvi->set_voltage(VO_ch,		v_in,	VRANGE_CACHE[resource]);
			break;
		case res_FW_dvi:			// DVI_11_1		FW
			FW_dvi->set_voltage(FW_ch,		v_in,	VRANGE_CACHE[resource]);
			break;
		case res_ACK_ovi:			// OVI_1_5		ACK
			ACK_ovi->set_voltage(ACK_ch,	v_in,	VRANGE_CACHE[resource]);
			break;

		// *** High Voltage Resources
		case res_BV_hvs:			// HVS_15		D, UV, FW
			hvs_15->set_voltage(			v_in,	VRANGE_CACHE[resource]);
			break;

		// *** Other Resources
		case res_InvSyn_REF_ovi:	// OVI_1_4		InvSyn_IM reference OVI
			InvSyn_REF_ovi->set_voltage(InvSyn_ch,	v_in,	VRANGE_CACHE[resource]);
			break;
		case res_InvSyn_Offset_ovi:	// OVI_1_6		InvSyn_IM GND offset OVI
			InvSyn_Offset_ovi->set_voltage(InvSyn_Offset_ch,	v_in,	VRANGE_CACHE[resource]);
			break;
		case res_BC_ovi:			// OVI_1_3		Buffer Clamp reference OVI
			BC_ovi->set_voltage(BC_ch,		v_in,	VRANGE_CACHE[resource]);
			break;
		case res_Iped_dvi:			// DVI_11_0		Pedestal current
			Iped_dvi->set_voltage(Iped_ch,	v_in,	VRANGE_CACHE[resource]);
			break;
		
		default:
			break;
	}

	if (settling_us > 0)
	{
		if (settling_us <= 10)
			wait.delay_10_us(1);	//minimum 10us delay
		else if	(settling_us <= 50000)
			wait.delay_10_us(settling_us / 10); 
		else
			delay(50);				//maximum 50ms delay
	}
}

void Set_I(resource_t resource, float i_in, unsigned long settling_us)
{
	// Set current limit
	switch (resource)
	{
		// *** Primary Side Resources
		case res_D_dvi:				// DVI_11_0		Drain
			D_dvi->set_current(D_ch,		i_in,	IRANGE_CACHE[resource]);
			break;
		case res_BPP_dvi:			// DVI_11_0		BPP for breakdown test
			BPP_DVI->set_current(BPP_ch,	i_in,	IRANGE_CACHE[resource]);
			break;
		case res_BPP_ovi:			// OVI_1_0		BPP
			BPP_ovi->set_current(BPP_ch,	i_in,	IRANGE_CACHE[resource]);
			break;
		case res_VPIN_ovi:			// OVI_1_1		UV
			VPIN_ovi->set_current(VPIN_ch,	i_in,	IRANGE_CACHE[resource]);
			break;

		// *** Secondary Side Resources
		case res_FWC_dvi2k:			// DVI_13_0		FWC
			FWC_dvi2k->set_current(FWC_ch,	i_in,	IRANGE_CACHE[resource]);
			break;
		case res_REQ_ovi:			// OVI_1_2		REQ
			REQ_ovi->set_current(REQ_ch,	i_in,	IRANGE_CACHE[resource]);
			break;
		case res_BPS_dvi:			// DVI_9_1		BPS
			BPS_dvi->set_current(BPS_ch,	i_in,	IRANGE_CACHE[resource]);
			break;
		case res_SR_dvi2k:			// DVI_13_1		SR
			SR_dvi2k->set_current(SR_ch,	i_in,	IRANGE_CACHE[resource]);
			break;
		case res_VO_dvi:			// DVI_9_0		VO
			VO_dvi->set_current(VO_ch,		i_in,	IRANGE_CACHE[resource]);
			break;
		case res_FW_dvi:			// DVI_11_1		FW
			FW_dvi->set_current(FW_ch,		i_in,	IRANGE_CACHE[resource]);
			break;
		case res_ACK_ovi:			// OVI_1_5		ACK
			ACK_ovi->set_current(ACK_ch,	i_in,	IRANGE_CACHE[resource]);
			break;

		// *** High Voltage Resources
		case res_BV_hvs:			// HVS_15		D, UV, FW
			hvs_15->set_current(			i_in,	IRANGE_CACHE[resource]);
			break;

		// *** Other Resources
		case res_InvSyn_REF_ovi:	// OVI_1_4		InvSyn_IM reference OVI
			InvSyn_REF_ovi->set_current(InvSyn_ch,	i_in,	IRANGE_CACHE[resource]);
			break;
		case res_InvSyn_Offset_ovi:	// OVI_1_6		InvSyn_IM GND offset OVI
			InvSyn_Offset_ovi->set_current(InvSyn_Offset_ch,	i_in,	IRANGE_CACHE[resource]);
			break;
		case res_BC_ovi:			// OVI_1_3		Buffer Clamp reference OVI
			BC_ovi->set_current(BC_ch,		i_in,	IRANGE_CACHE[resource]);
			break;
		case res_Iped_dvi:			// DVI_11_0		Pedestal current
			Iped_dvi->set_current(Iped_ch,	i_in,	IRANGE_CACHE[resource]);
			break;
		
		default:
			break;
	}

	if (settling_us > 0)
	{
		if (settling_us <= 10)
			wait.delay_10_us(1);	//minimum 10us delay
		else if	(settling_us <= 50000)
			wait.delay_10_us(settling_us / 10); 
		else
			delay(50);				//maximum 50ms delay
	}
}

void Set_VI(resource_t resource, float v_in, float i_in, unsigned long settling_us)
{
	Set_I(resource, i_in, settling_us);
	Set_V(resource, v_in, settling_us);
}

void Reset_V()
{
	for (int resource = 0; resource < (int)last_vi; resource++)
	{
		Set_V((resource_t)resource, 0.0);
	}
}

void Reset_I(void)
{
	// *** Primary Side Resources
	Set_I(res_D_dvi,			 30 mA);		// DVI_11_0		Drain
	//Set_I(res_BPP_dvi,			 30 mA);		// DVI_11_0		BPP for breakdown test
	Set_I(res_BPP_ovi,			 20 mA);		// OVI_1_0		BPP
	Set_I(res_VPIN_ovi,			 20 mA);		// OVI_1_1		UV

	// *** Secondary Side Resources
	Set_I(res_FWC_dvi2k,		 20 mA);		// DVI_13_0		FWC
	Set_I(res_REQ_ovi,			 20 mA);		// OVI_1_2		REQ
	Set_I(res_BPS_dvi,			 30 mA);		// DVI_9_1		BPS
	Set_I(res_SR_dvi2k,			 20 mA);		// DVI_13_1		SR
	Set_I(res_VO_dvi,			 20 mA);		// DVI_9_0		VO
	Set_I(res_FW_dvi,			 20 mA);		// DVI_11_1		FW
	Set_I(res_ACK_ovi,			 20 mA);		// OVI_1_5		ACK

	// *** High Voltage Resources
	Set_I(res_BV_hvs,			500 uA);		// HVS_15		D, UV, FW

	// *** Other Resources
	Set_I(res_InvSyn_REF_ovi,	 10 mA);		// OVI_1_4		InvSyn_IM reference OVI
	Set_I(res_InvSyn_Offset_ovi, 20 mA);		// OVI_1_6		InvSyn_IM GND offset OVI
	Set_I(res_BC_ovi,			 30 mA);		// OVI_1_3		Buffer Clamp reference OVI
	//Set_I(res_Iped_dvi,			 30 mA);		// DVI_11_0		Pedestal current
}

void Reset_VI(void)
{
	Reset_V();
	wait.delay_10_us(10);
	Reset_I();
}

float Meas_VIaverage(resource_t resource, unsigned char mode, unsigned short samples, unsigned long settling_us, char range)
{
	float measured = DEFAULT_VALUE;
	unsigned char	dvi_meas_mode;
	unsigned char	ovi_meas_mode;
	unsigned short	hvs_meas_mode;
	unsigned short	counts;
	unsigned long	settling_10us;

	if (mode == MEASURE_CURRENT)
	{
		dvi_meas_mode = DVI_MEASURE_CURRENT;
		ovi_meas_mode = OVI_MEASURE_CURRENT;
		hvs_meas_mode = HVS_MEASURE_CURRENT;
	}
	else
	{
		dvi_meas_mode = DVI_MEASURE_VOLTAGE;
		ovi_meas_mode = OVI_MEASURE_VOLTAGE;
		hvs_meas_mode = HVS_MEASURE_VOLTAGE;
	}

	counts = (samples < 1 ? 1 : samples);

	settling_10us = (settling_us < 10 ? 1 : (settling_us/10));

	switch (resource)
	{
		// *** Primary Side Resources
		case res_D_dvi:				// DVI_11_0		Drain
		case res_Iped_dvi:			// DVI_11_0		Pedestal current
			D_dvi->set_meas_mode(D_ch,			dvi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = D_dvi->measure_average(counts);
			break;
		case res_BPP_dvi:			// DVI_11_0		BPP for breakdown test
			BPP_DVI->set_meas_mode(BPP_ch,		dvi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = BPP_DVI->measure_average(counts);
			break;
		case res_BPP_ovi:			// OVI_1_0		BPP
			BPP_ovi->set_meas_mode(BPP_ch,		ovi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = BPP_ovi->measure_average(counts);
			break;
		case res_VPIN_ovi:			// OVI_1_1		UV
			VPIN_ovi->set_meas_mode(VPIN_ch,	ovi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = VPIN_ovi->measure_average(counts);
			break;

		// *** Secondary Side Resources
		case res_FWC_dvi2k:			// DVI_13_0		FWC
			FWC_dvi2k->set_meas_mode(FWC_ch,	dvi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = FWC_dvi2k->measure_average(counts);
			break;
		case res_REQ_ovi:			// OVI_1_2		REQ
			REQ_ovi->set_meas_mode(REQ_ch,		ovi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = REQ_ovi->measure_average(counts);
			break;
		case res_BPS_dvi:			// DVI_9_1		BPS
			BPS_dvi->set_meas_mode(BPS_ch,		dvi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = BPS_dvi->measure_average(counts);
			break;
		case res_SR_dvi2k:			// DVI_13_1		SR
			SR_dvi2k->set_meas_mode(SR_ch,		dvi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = SR_dvi2k->measure_average(counts);
			break;
		case res_VO_dvi:			// DVI_9_0		VO
			VO_dvi->set_meas_mode(VO_ch,		dvi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = VO_dvi->measure_average(counts);
			break;
		case res_FW_dvi:			// DVI_11_1		FW
			FW_dvi->set_meas_mode(FW_ch,		dvi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = FW_dvi->measure_average(counts);
			break;
		case res_ACK_ovi:			// OVI_1_5		ACK
			ACK_ovi->set_meas_mode(ACK_ch,		ovi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = ACK_ovi->measure_average(counts);
			break;

		// *** High Voltage Resources
		case res_BV_hvs:			// HVS_15		D, UV, FW
			hvs_15->set_meas_mode(hvs_meas_mode);
			wait.delay_10_us(settling_10us);
			measured = hvs_15->measure_average(counts);
			break;
		
		// *** Other Resources
		case res_InvSyn_REF_ovi:	// OVI_1_4		InvSyn_IM reference OVI
			InvSyn_REF_ovi->set_meas_mode(InvSyn_ch,	ovi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = InvSyn_REF_ovi->measure_average(counts);
			break;
		case res_InvSyn_Offset_ovi:	// OVI_1_6		InvSyn_IM GND offset OVI
			InvSyn_Offset_ovi->set_meas_mode(InvSyn_Offset_ch,	ovi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = InvSyn_Offset_ovi->measure_average(counts);
			break;
		case res_BC_ovi:			// OVI_1_3		Buffer Clamp reference OVI
			BC_ovi->set_meas_mode(BC_ch,	ovi_meas_mode,	range);
			wait.delay_10_us(settling_10us);
			measured = BC_ovi->measure_average(counts);
			break;
		
		default:
			break;
	}
	return measured;
}

void OVI_connect_all(int slot)
{
	Ovi * instr_ptr;

	if (no_ovi_cards > 0)
	{
		if (GetDetectedBoardType(slot) == OVI_CARD)
		{
			instr_ptr = &ovi_cards[board_ptr[slot]];
			instr_ptr->connect(OVI_CHANNEL_0);
			instr_ptr->connect(OVI_CHANNEL_1);
			instr_ptr->connect(OVI_CHANNEL_2);
			instr_ptr->connect(OVI_CHANNEL_3);
			instr_ptr->connect(OVI_CHANNEL_4);
			instr_ptr->connect(OVI_CHANNEL_5);
			instr_ptr->connect(OVI_CHANNEL_6);
			instr_ptr->connect(OVI_CHANNEL_7);
			instr_ptr = NULL;
		}
	}
}

void OVI_disconnect_all(int slot)
{
	Ovi * instr_ptr;

	if (no_ovi_cards > 0)
	{
		if (GetDetectedBoardType(slot) == OVI_CARD)
		{
			instr_ptr = &ovi_cards[board_ptr[slot]];
			instr_ptr->disconnect(OVI_CHANNEL_0);
			instr_ptr->disconnect(OVI_CHANNEL_1);
			instr_ptr->disconnect(OVI_CHANNEL_2);
			instr_ptr->disconnect(OVI_CHANNEL_3);
			instr_ptr->disconnect(OVI_CHANNEL_4);
			instr_ptr->disconnect(OVI_CHANNEL_5);
			instr_ptr->disconnect(OVI_CHANNEL_6);
			instr_ptr->disconnect(OVI_CHANNEL_7);
			instr_ptr = NULL;
		}
	}
}

void TMU_disconnect_all(int slot)
{
	Tmu * instr_ptr;

	if (no_tmu_cards > 0)
	{
		if (GetDetectedBoardType(slot) == TMU_CARD)
		{
			instr_ptr = &tmu_cards[board_ptr[slot]];
			instr_ptr->open_relay(TMU_HIZ_DUT1);
			instr_ptr->open_relay(TMU_HIZ_DUT2);
			instr_ptr->open_relay(TMU_HIZ_DUT3);
			instr_ptr->open_relay(TMU_HIZ_DUT4);
			instr_ptr->open_relay(TMU_CHAN_A_DUT1);
			instr_ptr->open_relay(TMU_CHAN_A_DUT2);
			instr_ptr->open_relay(TMU_CHAN_B_DUT1);
			instr_ptr->open_relay(TMU_CHAN_B_DUT2);
			instr_ptr = NULL;
		}
	}
}
//*************    END of Unified Resource Control    **************//
