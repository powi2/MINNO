//==============================================================================
// FUNCTION.H 
//==============================================================================

// ********************************************************************
// For each individual test function, define a structure that holds all of its parameters.

typedef struct
{
    USHORT      fail_bin;
    double      Debug;
    double      Wait;
    USHORT      GRR;
    USHORT      SiliconRev_P;
    USHORT      SiliconRev_S;
    USHORT      TRIM_ENABLE;
    USHORT      SAMPLE;
    double      Trim_Voltage;
    double      VFW_Read_AF;
    double      AF_1ST_TRIM_DELAY;
    double      AF_2ND_TRIM_DELAY;
    double      AF_2ND_TRIM_TRHD;
    USHORT      CHAR_FLOW;
    USHORT      REL_FLOW;
    double      ENG_Option;
    double      v_debug;
    double      i_debug;
    double      ms_debug;
} Setup_params;


typedef struct
{
    USHORT      fail_bin;
} Continuity_params;


typedef struct
{
    USHORT      fail_bin;
} Leakage_params;


typedef struct
{
    USHORT      fail_bin;
    double      BV_Clamp;
    double      BV_stress_time;
} BV_Vpin_params;


typedef struct
{
    USHORT      fail_bin;
    double      BV_Clamp;
    double      BV_stress_time;
} BV_FW_params;


typedef struct
{
    USHORT      fail_bin;
    double      BVD_D_Clamp;
    double      BVD_stress_time;
} BV_Drain_params;


typedef struct
{
    USHORT      fail_bin;
} VBP_Init_params;


typedef struct
{
    USHORT      fail_bin;
} RegPre_S_params;


typedef struct
{
    USHORT      fail_bin;
} IzPre_params;


typedef struct
{
    USHORT      fail_bin;
    double      BVD_D_Clamp;
    double      BVD_stress_time;
} BV_Drain_900V_params;


typedef struct
{
    USHORT      fail_bin;
    float       vStress;
} STRESS_params;


typedef struct
{
    USHORT      fail_bin;
    short       force_code;
} Feature_Trim_P_params;


typedef struct
{
    USHORT      fail_bin;
    short       force_code;
} Feature_Trim_S_params;


typedef struct
{
    USHORT      fail_bin;
} OVT_params;


typedef struct
{
    USHORT      fail_bin;
} IOV_Pre_P_params;


typedef struct
{
    USHORT      fail_bin;
    short       force_code;
} IOV_Trim_params;


typedef struct
{
    USHORT      fail_bin;
} IOV_post_P_params;


typedef struct
{
    USHORT      fail_bin;
} Fosc_Pre_P_params;


typedef struct
{
    USHORT      fail_bin;
    short       force_code;
} Fosc_Trim_P_params;


typedef struct
{
    USHORT      fail_bin;
} Fosc_post_P_params;


typedef struct
{
    USHORT      fail_bin;
} tOVL_Pre_S_params;


typedef struct
{
    USHORT      fail_bin;
    short       force_code;
} tOVL_Trim_params;


typedef struct
{
    USHORT      fail_bin;
} tOVL_post_S_params;


typedef struct
{
    USHORT      fail_bin;
} Fosc_Pre_S_params;


typedef struct
{
    USHORT      fail_bin;
    short       force_code;
} Fosc_Trim_S_params;


typedef struct
{
    USHORT      fail_bin;
} Fosc_post_S_params;


typedef struct
{
    USHORT      fail_bin;
} SR_Pre_S_params;


typedef struct
{
    USHORT      fail_bin;
    short       force_code;
} SR_Trim_S_params;


typedef struct
{
    USHORT      fail_bin;
} SR_post_S_params;


typedef struct
{
    USHORT      fail_bin;
} REQ_Pre_S_params;


typedef struct
{
    USHORT      fail_bin;
    short       force_code;
} REQ_Trim_S_params;


typedef struct
{
    USHORT      fail_bin;
} REQ_post_S_params;


typedef struct
{
    USHORT      fail_bin;
} ILIM_Pre_params;


typedef struct
{
    USHORT      fail_bin;
    short       force_code;
    short       force_ZF_P_code;
} ILIM_Trim_params;


typedef struct
{
    USHORT      fail_bin;
} ILIM_params;


typedef struct
{
    USHORT      fail_bin;
} Reg_S_params;


typedef struct
{
    USHORT      fail_bin;
} IzPost_params;


typedef struct
{
    USHORT      fail_bin;
} Iz_xChk_TrmCode_P_params;


typedef struct
{
    USHORT      fail_bin;
} Iz_xChk_Reg_S_params;


typedef struct
{
    USHORT      fail_bin;
} VBP_Supply_params;


typedef struct
{
    USHORT      fail_bin;
} IBP_Supply_params;


typedef struct
{
    USHORT      fail_bin;
} IOV_IUV_OT_params;


typedef struct
{
    USHORT      fail_bin;
} FOSC_Ton_ARST_params;


typedef struct
{
    USHORT      fail_bin;
} FWPK_params;


typedef struct
{
    USHORT      fail_bin;
} FWC_ACK_S_params;


typedef struct
{
    USHORT      fail_bin;
} SR_Delay_tREQinh_params;


typedef struct
{
    USHORT      fail_bin;
} Vesr_params;


typedef struct
{
    USHORT      fail_bin;
    double      NEW_PARAM;
} SOA_SDS_TW50_params;


typedef struct
{
    USHORT      fail_bin;
} DATT_params;


typedef struct
{
    USHORT      fail_bin;
} TestTime_params;

// ********************************************************************
// Now pre-define the routines used in program development

/////////// Setup ///////////////////////////////////////////////////////
void Setup(test_function &func);
void initialize_Setup(short test_entry, test_function &func, char **func_name);
void setup_Setup(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Continuity ///////////////////////////////////////////////////////
void Continuity(test_function &func);
void initialize_Continuity(short test_entry, test_function &func, char **func_name);
void setup_Continuity(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Leakage ///////////////////////////////////////////////////////
void Leakage(test_function &func);
void initialize_Leakage(short test_entry, test_function &func, char **func_name);
void setup_Leakage(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BV_Vpin ///////////////////////////////////////////////////////
void BV_Vpin(test_function &func);
void initialize_BV_Vpin(short test_entry, test_function &func, char **func_name);
void setup_BV_Vpin(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BV_FW ///////////////////////////////////////////////////////
void BV_FW(test_function &func);
void initialize_BV_FW(short test_entry, test_function &func, char **func_name);
void setup_BV_FW(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BV_Drain ///////////////////////////////////////////////////////
void BV_Drain(test_function &func);
void initialize_BV_Drain(short test_entry, test_function &func, char **func_name);
void setup_BV_Drain(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VBP_Init ///////////////////////////////////////////////////////
void VBP_Init(test_function &func);
void initialize_VBP_Init(short test_entry, test_function &func, char **func_name);
void setup_VBP_Init(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// RegPre_S ///////////////////////////////////////////////////////
void RegPre_S(test_function &func);
void initialize_RegPre_S(short test_entry, test_function &func, char **func_name);
void setup_RegPre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IzPre ///////////////////////////////////////////////////////
void IzPre(test_function &func);
void initialize_IzPre(short test_entry, test_function &func, char **func_name);
void setup_IzPre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// BV_Drain_900V ///////////////////////////////////////////////////////
void BV_Drain_900V(test_function &func);
void initialize_BV_Drain_900V(short test_entry, test_function &func, char **func_name);
void setup_BV_Drain_900V(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// STRESS ///////////////////////////////////////////////////////
void STRESS(test_function &func);
void initialize_STRESS(short test_entry, test_function &func, char **func_name);
void setup_STRESS(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Feature_Trim_P ///////////////////////////////////////////////////////
void Feature_Trim_P(test_function &func);
void initialize_Feature_Trim_P(short test_entry, test_function &func, char **func_name);
void setup_Feature_Trim_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Feature_Trim_S ///////////////////////////////////////////////////////
void Feature_Trim_S(test_function &func);
void initialize_Feature_Trim_S(short test_entry, test_function &func, char **func_name);
void setup_Feature_Trim_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// OVT ///////////////////////////////////////////////////////
void OVT(test_function &func);
void initialize_OVT(short test_entry, test_function &func, char **func_name);
void setup_OVT(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IOV_Pre_P ///////////////////////////////////////////////////////
void IOV_Pre_P(test_function &func);
void initialize_IOV_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_IOV_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IOV_Trim ///////////////////////////////////////////////////////
void IOV_Trim(test_function &func);
void initialize_IOV_Trim(short test_entry, test_function &func, char **func_name);
void setup_IOV_Trim(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IOV_post_P ///////////////////////////////////////////////////////
void IOV_post_P(test_function &func);
void initialize_IOV_post_P(short test_entry, test_function &func, char **func_name);
void setup_IOV_post_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_Pre_P ///////////////////////////////////////////////////////
void Fosc_Pre_P(test_function &func);
void initialize_Fosc_Pre_P(short test_entry, test_function &func, char **func_name);
void setup_Fosc_Pre_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_Trim_P ///////////////////////////////////////////////////////
void Fosc_Trim_P(test_function &func);
void initialize_Fosc_Trim_P(short test_entry, test_function &func, char **func_name);
void setup_Fosc_Trim_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_post_P ///////////////////////////////////////////////////////
void Fosc_post_P(test_function &func);
void initialize_Fosc_post_P(short test_entry, test_function &func, char **func_name);
void setup_Fosc_post_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// tOVL_Pre_S ///////////////////////////////////////////////////////
void tOVL_Pre_S(test_function &func);
void initialize_tOVL_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_tOVL_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// tOVL_Trim ///////////////////////////////////////////////////////
void tOVL_Trim(test_function &func);
void initialize_tOVL_Trim(short test_entry, test_function &func, char **func_name);
void setup_tOVL_Trim(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// tOVL_post_S ///////////////////////////////////////////////////////
void tOVL_post_S(test_function &func);
void initialize_tOVL_post_S(short test_entry, test_function &func, char **func_name);
void setup_tOVL_post_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_Pre_S ///////////////////////////////////////////////////////
void Fosc_Pre_S(test_function &func);
void initialize_Fosc_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_Fosc_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_Trim_S ///////////////////////////////////////////////////////
void Fosc_Trim_S(test_function &func);
void initialize_Fosc_Trim_S(short test_entry, test_function &func, char **func_name);
void setup_Fosc_Trim_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Fosc_post_S ///////////////////////////////////////////////////////
void Fosc_post_S(test_function &func);
void initialize_Fosc_post_S(short test_entry, test_function &func, char **func_name);
void setup_Fosc_post_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// SR_Pre_S ///////////////////////////////////////////////////////
void SR_Pre_S(test_function &func);
void initialize_SR_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_SR_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// SR_Trim_S ///////////////////////////////////////////////////////
void SR_Trim_S(test_function &func);
void initialize_SR_Trim_S(short test_entry, test_function &func, char **func_name);
void setup_SR_Trim_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// SR_post_S ///////////////////////////////////////////////////////
void SR_post_S(test_function &func);
void initialize_SR_post_S(short test_entry, test_function &func, char **func_name);
void setup_SR_post_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// REQ_Pre_S ///////////////////////////////////////////////////////
void REQ_Pre_S(test_function &func);
void initialize_REQ_Pre_S(short test_entry, test_function &func, char **func_name);
void setup_REQ_Pre_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// REQ_Trim_S ///////////////////////////////////////////////////////
void REQ_Trim_S(test_function &func);
void initialize_REQ_Trim_S(short test_entry, test_function &func, char **func_name);
void setup_REQ_Trim_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// REQ_post_S ///////////////////////////////////////////////////////
void REQ_post_S(test_function &func);
void initialize_REQ_post_S(short test_entry, test_function &func, char **func_name);
void setup_REQ_post_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ILIM_Pre ///////////////////////////////////////////////////////
void ILIM_Pre(test_function &func);
void initialize_ILIM_Pre(short test_entry, test_function &func, char **func_name);
void setup_ILIM_Pre(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ILIM_Trim ///////////////////////////////////////////////////////
void ILIM_Trim(test_function &func);
void initialize_ILIM_Trim(short test_entry, test_function &func, char **func_name);
void setup_ILIM_Trim(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// ILIM ///////////////////////////////////////////////////////
void ILIM(test_function &func);
void initialize_ILIM(short test_entry, test_function &func, char **func_name);
void setup_ILIM(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Reg_S ///////////////////////////////////////////////////////
void Reg_S(test_function &func);
void initialize_Reg_S(short test_entry, test_function &func, char **func_name);
void setup_Reg_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IzPost ///////////////////////////////////////////////////////
void IzPost(test_function &func);
void initialize_IzPost(short test_entry, test_function &func, char **func_name);
void setup_IzPost(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Iz_xChk_TrmCode_P ///////////////////////////////////////////////////////
void Iz_xChk_TrmCode_P(test_function &func);
void initialize_Iz_xChk_TrmCode_P(short test_entry, test_function &func, char **func_name);
void setup_Iz_xChk_TrmCode_P(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Iz_xChk_Reg_S ///////////////////////////////////////////////////////
void Iz_xChk_Reg_S(test_function &func);
void initialize_Iz_xChk_Reg_S(short test_entry, test_function &func, char **func_name);
void setup_Iz_xChk_Reg_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// VBP_Supply ///////////////////////////////////////////////////////
void VBP_Supply(test_function &func);
void initialize_VBP_Supply(short test_entry, test_function &func, char **func_name);
void setup_VBP_Supply(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IBP_Supply ///////////////////////////////////////////////////////
void IBP_Supply(test_function &func);
void initialize_IBP_Supply(short test_entry, test_function &func, char **func_name);
void setup_IBP_Supply(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// IOV_IUV_OT ///////////////////////////////////////////////////////
void IOV_IUV_OT(test_function &func);
void initialize_IOV_IUV_OT(short test_entry, test_function &func, char **func_name);
void setup_IOV_IUV_OT(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// FOSC_Ton_ARST ///////////////////////////////////////////////////////
void FOSC_Ton_ARST(test_function &func);
void initialize_FOSC_Ton_ARST(short test_entry, test_function &func, char **func_name);
void setup_FOSC_Ton_ARST(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// FWPK ///////////////////////////////////////////////////////
void FWPK(test_function &func);
void initialize_FWPK(short test_entry, test_function &func, char **func_name);
void setup_FWPK(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// FWC_ACK_S ///////////////////////////////////////////////////////
void FWC_ACK_S(test_function &func);
void initialize_FWC_ACK_S(short test_entry, test_function &func, char **func_name);
void setup_FWC_ACK_S(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// SR_Delay_tREQinh ///////////////////////////////////////////////////////
void SR_Delay_tREQinh(test_function &func);
void initialize_SR_Delay_tREQinh(short test_entry, test_function &func, char **func_name);
void setup_SR_Delay_tREQinh(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// Vesr ///////////////////////////////////////////////////////
void Vesr(test_function &func);
void initialize_Vesr(short test_entry, test_function &func, char **func_name);
void setup_Vesr(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// SOA_SDS_TW50 ///////////////////////////////////////////////////////
void SOA_SDS_TW50(test_function &func);
void initialize_SOA_SDS_TW50(short test_entry, test_function &func, char **func_name);
void setup_SOA_SDS_TW50(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// DATT ///////////////////////////////////////////////////////
void DATT(test_function &func);
void initialize_DATT(short test_entry, test_function &func, char **func_name);
void setup_DATT(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);

/////////// TestTime ///////////////////////////////////////////////////////
void TestTime(test_function &func);
void initialize_TestTime(short test_entry, test_function &func, char **func_name);
void setup_TestTime(test_function &func, char **function_name, char *heading_line, unsigned short *want_print, char manual_setup);


#include "USER.H"
