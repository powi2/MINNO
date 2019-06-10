//==============================================================================
// LIST.CPP
//==============================================================================
#include "asl.h"
#include "function.h"

// There are five elements in each structure for each array position
// as shown below :-
/*
typedef struct	{
		// First, a name that is displayed on the list of functions screen
	char		*name;
		// Next the development number;
	unsigned long develop_no;
		// Next, the name of the actual function.
	void far	(*address)(test_function& func);
		// Next, the parameter setup section of the function
	void far	(*setup)(test_function& func,char **function_name,char *heading_line);
		// Next, the default initialization of the parameters (and various
		// memory requirements.
	void far	(*initialize)(short entry,test_function& func,char **function_name);
		// Lastly, the size of the block of parameters
	short			sizeof_param_block;
				} test_descriptions;
*/

//{ASL_CREATE BEGIN_TEST_LIST_INIT

test_descriptions g_test_list[] =
{
	{ "Setup",0L,Setup,setup_Setup,initialize_Setup,sizeof(Setup_params) },
	{ "Continuity",0L,Continuity,setup_Continuity,initialize_Continuity,sizeof(Continuity_params) },
	{ "Leakage",0L,Leakage,setup_Leakage,initialize_Leakage,sizeof(Leakage_params) },
	{ "BV_Vpin",0L,BV_Vpin,setup_BV_Vpin,initialize_BV_Vpin,sizeof(BV_Vpin_params) },
	{ "BV_FW",0L,BV_FW,setup_BV_FW,initialize_BV_FW,sizeof(BV_FW_params) },
	{ "BV_Drain",0L,BV_Drain,setup_BV_Drain,initialize_BV_Drain,sizeof(BV_Drain_params) },
	{ "VBP_Init",0L,VBP_Init,setup_VBP_Init,initialize_VBP_Init,sizeof(VBP_Init_params) },
	{ "RegPre_S",0L,RegPre_S,setup_RegPre_S,initialize_RegPre_S,sizeof(RegPre_S_params) },
	{ "IzPre",0L,IzPre,setup_IzPre,initialize_IzPre,sizeof(IzPre_params) },
	{ "BV_Drain_900V",0L,BV_Drain_900V,setup_BV_Drain_900V,initialize_BV_Drain_900V,sizeof(BV_Drain_900V_params) },
	{ "STRESS",0L,STRESS,setup_STRESS,initialize_STRESS,sizeof(STRESS_params) },
	{ "Feature_Trim_P",0L,Feature_Trim_P,setup_Feature_Trim_P,initialize_Feature_Trim_P,sizeof(Feature_Trim_P_params) },
	{ "Feature_Trim_S",0L,Feature_Trim_S,setup_Feature_Trim_S,initialize_Feature_Trim_S,sizeof(Feature_Trim_S_params) },
	{ "OVT",0L,OVT,setup_OVT,initialize_OVT,sizeof(OVT_params) },
	{ "IOV_Pre_P",0L,IOV_Pre_P,setup_IOV_Pre_P,initialize_IOV_Pre_P,sizeof(IOV_Pre_P_params) },
	{ "IOV_Trim",0L,IOV_Trim,setup_IOV_Trim,initialize_IOV_Trim,sizeof(IOV_Trim_params) },
	{ "IOV_post_P",0L,IOV_post_P,setup_IOV_post_P,initialize_IOV_post_P,sizeof(IOV_post_P_params) },
	{ "Fosc_Pre_P",0L,Fosc_Pre_P,setup_Fosc_Pre_P,initialize_Fosc_Pre_P,sizeof(Fosc_Pre_P_params) },
	{ "Fosc_Trim_P",0L,Fosc_Trim_P,setup_Fosc_Trim_P,initialize_Fosc_Trim_P,sizeof(Fosc_Trim_P_params) },
	{ "Fosc_post_P",0L,Fosc_post_P,setup_Fosc_post_P,initialize_Fosc_post_P,sizeof(Fosc_post_P_params) },
	{ "tOVL_Pre_S",0L,tOVL_Pre_S,setup_tOVL_Pre_S,initialize_tOVL_Pre_S,sizeof(tOVL_Pre_S_params) },
	{ "tOVL_Trim",0L,tOVL_Trim,setup_tOVL_Trim,initialize_tOVL_Trim,sizeof(tOVL_Trim_params) },
	{ "tOVL_post_S",0L,tOVL_post_S,setup_tOVL_post_S,initialize_tOVL_post_S,sizeof(tOVL_post_S_params) },
	{ "Fosc_Pre_S",0L,Fosc_Pre_S,setup_Fosc_Pre_S,initialize_Fosc_Pre_S,sizeof(Fosc_Pre_S_params) },
	{ "Fosc_Trim_S",0L,Fosc_Trim_S,setup_Fosc_Trim_S,initialize_Fosc_Trim_S,sizeof(Fosc_Trim_S_params) },
	{ "Fosc_post_S",0L,Fosc_post_S,setup_Fosc_post_S,initialize_Fosc_post_S,sizeof(Fosc_post_S_params) },
	{ "SR_Pre_S",0L,SR_Pre_S,setup_SR_Pre_S,initialize_SR_Pre_S,sizeof(SR_Pre_S_params) },
	{ "SR_Trim_S",0L,SR_Trim_S,setup_SR_Trim_S,initialize_SR_Trim_S,sizeof(SR_Trim_S_params) },
	{ "SR_post_S",0L,SR_post_S,setup_SR_post_S,initialize_SR_post_S,sizeof(SR_post_S_params) },
	{ "REQ_Pre_S",0L,REQ_Pre_S,setup_REQ_Pre_S,initialize_REQ_Pre_S,sizeof(REQ_Pre_S_params) },
	{ "REQ_Trim_S",0L,REQ_Trim_S,setup_REQ_Trim_S,initialize_REQ_Trim_S,sizeof(REQ_Trim_S_params) },
	{ "REQ_post_S",0L,REQ_post_S,setup_REQ_post_S,initialize_REQ_post_S,sizeof(REQ_post_S_params) },
	{ "ILIM_Pre",0L,ILIM_Pre,setup_ILIM_Pre,initialize_ILIM_Pre,sizeof(ILIM_Pre_params) },
	{ "ILIM_Trim",0L,ILIM_Trim,setup_ILIM_Trim,initialize_ILIM_Trim,sizeof(ILIM_Trim_params) },
	{ "ILIM",0L,ILIM,setup_ILIM,initialize_ILIM,sizeof(ILIM_params) },
	{ "Reg_S",0L,Reg_S,setup_Reg_S,initialize_Reg_S,sizeof(Reg_S_params) },
	{ "IzPost",0L,IzPost,setup_IzPost,initialize_IzPost,sizeof(IzPost_params) },
	{ "Iz_xChk_TrmCode_P",0L,Iz_xChk_TrmCode_P,setup_Iz_xChk_TrmCode_P,initialize_Iz_xChk_TrmCode_P,sizeof(Iz_xChk_TrmCode_P_params) },
	{ "Iz_xChk_Reg_S",0L,Iz_xChk_Reg_S,setup_Iz_xChk_Reg_S,initialize_Iz_xChk_Reg_S,sizeof(Iz_xChk_Reg_S_params) },
	{ "VBP_Supply",0L,VBP_Supply,setup_VBP_Supply,initialize_VBP_Supply,sizeof(VBP_Supply_params) },
	{ "IBP_Supply",0L,IBP_Supply,setup_IBP_Supply,initialize_IBP_Supply,sizeof(IBP_Supply_params) },
	{ "IOV_IUV_OT",0L,IOV_IUV_OT,setup_IOV_IUV_OT,initialize_IOV_IUV_OT,sizeof(IOV_IUV_OT_params) },
	{ "FOSC_Ton_ARST",0L,FOSC_Ton_ARST,setup_FOSC_Ton_ARST,initialize_FOSC_Ton_ARST,sizeof(FOSC_Ton_ARST_params) },
	{ "FWPK",0L,FWPK,setup_FWPK,initialize_FWPK,sizeof(FWPK_params) },
	{ "FWC_ACK_S",0L,FWC_ACK_S,setup_FWC_ACK_S,initialize_FWC_ACK_S,sizeof(FWC_ACK_S_params) },
	{ "SR_Delay_tREQinh",0L,SR_Delay_tREQinh,setup_SR_Delay_tREQinh,initialize_SR_Delay_tREQinh,sizeof(SR_Delay_tREQinh_params) },
	{ "Vesr",0L,Vesr,setup_Vesr,initialize_Vesr,sizeof(Vesr_params) },
	{ "SOA_SDS_TW50",0L,SOA_SDS_TW50,setup_SOA_SDS_TW50,initialize_SOA_SDS_TW50,sizeof(SOA_SDS_TW50_params) },
	{ "DATT",0L,DATT,setup_DATT,initialize_DATT,sizeof(DATT_params) },
	{ "TestTime",0L,TestTime,setup_TestTime,initialize_TestTime,sizeof(TestTime_params) },
	{ NULL,NULL }
};
// ASL_CREATE END_TEST_LIST_INIT}
