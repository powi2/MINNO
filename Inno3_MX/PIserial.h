#if !defined(PISERIAL_H)
#define PISERIAL_H
//==============================================================================
// PIserial.H
//==============================================================================

//===================  Serial port, Arroyo TEC controller and TTi PSU STARTS here  =======================//
#define CR					"\r"
#define LF					"\n"
#define CRLF				"\r\n"
#define LFCR				"\n\r"

/*
//
// Baud rates at which the communication device operates
//
#define CBR_110             110
#define CBR_300             300
#define CBR_600             600
#define CBR_1200            1200
#define CBR_2400            2400
#define CBR_4800            4800
#define CBR_9600            9600
#define CBR_14400           14400
#define CBR_19200           19200
#define CBR_38400           38400
#define CBR_56000           56000
#define CBR_57600           57600
#define CBR_115200          115200
#define CBR_128000          128000
#define CBR_256000          256000

//
// Parity bit
//
#define NOPARITY            0
#define ODDPARITY           1
#define EVENPARITY          2
#define MARKPARITY          3
#define SPACEPARITY         4

//
// Stop bit
//
#define ONESTOPBIT          0
#define ONE5STOPBITS        1
#define TWOSTOPBITS         2
*/


int Com_Open(char* commport, HANDLE *hComm);
int Com_Setup(HANDLE hComm, DWORD BaudRate, BYTE ByteSize, BYTE Parity, BYTE StopBits, int timeout);
int Com_Write_Line(HANDLE hComm, char* wbuffer);
int Com_Read_Line(HANDLE hComm, char* rbuffer);
int Com_WriteRead_Line(HANDLE hComm, char* wbuffer, char* rbuffer, unsigned long delay_ms);
int Com_Close(HANDLE hComm);


extern HANDLE g_TEC_hComm;
extern COMSTAT g_TEC_comStat;
extern DCB g_TEC_dcb;
extern COMMTIMEOUTS g_TEC_timeouts;
extern char* g_TEC_port;

enum TEC_COND_Reg_t {
	CURRENT_LIMIT		= 0x0001,
	VOLTAGE_LIMIT		= 0x0002,
	RESISTANCE_LIMIT	= 0x0004,
	HIGH_TEMP_LIMIT		= 0x0008,
	LOW_TEMP_LIMIT		= 0x0010,
	SHORTED_SENSOR		= 0x0020,
	OPEN_SENSOR			= 0x0040,
	OPEN_TEC_MODULE		= 0x0080,
	OUT_OF_TOLERANCE	= 0x0200,
	OUTPUT_ON			= 0x0400,
};

int TEC_Set_Commport(char* commport);
int TEC_Open();
int TEC_Init();
int TEC_Setup();
int TEC_Set_Temp(double temperature);
int TEC_Get_Temp(double *temperature);
int TEC_Settle_T(int timeout_s);
int TEC_Get_Cond(int *cond_reg);
int TEC_Enable();
int TEC_Disable();
int TEC_Close();


#define TTi_ON	1
#define TTi_OFF	0

extern HANDLE g_TTi_hComm;
extern COMSTAT g_TTi_comStat;
extern DCB g_TTi_dcb;
extern COMMTIMEOUTS g_TTi_timeouts;
extern char* g_TTi_port;

enum TTi_Channel_t {
	ALL_CHN   = 0,
	OUTPUT1   = 1,
	OUTPUT2   = 2,
	AUXILIARY = 3,
	BOTH      = 4,
};

enum TTi_VRange_t {
	RANGE_15V5A  = 0,
	RANGE_35V3A  = 1,
	RANGE_35V0A5 = 2,
};

enum TTi_Mode_t {
	LINKED = 0,
	CTRL_1 = 1,
	CTRL_2 = 2,
};

int TTi_Set_Commport(char* commport);
int TTi_Open();
int TTi_Init();
int TTi_Setup();
int TTi_SetV(int channel, double voltage);
int TTi_GetV(int channel, double *voltage);
int TTi_GetI(int channel, double *current);
int TTi_SetILimit(int channel, double current);
int TTi_GetILimit(int channel, double *current);
int TTi_SetOVP(int channel, double voltage);
int TTi_GetOVP(int channel, double *voltage);
int TTi_SetOCP(int channel, double current);
int TTi_GetOCP(int channel, double *current);
int TTi_SetRange(int channel, int vrange);
int TTi_GetRange(int channel, int *vrange);
int TTi_SetMode(int mode);
int TTi_GetMode(int *mode);
int TTi_Output_On(int channel);
int TTi_Output_Off(int channel);
int TTi_Close();

#define ROOM_LO 15
#define ROOM_HI 45
extern double g_LHC_T;
int LHC_Set_Temp(double temperature);
int LHC_Enable();
int LHC_Disable();

#define NELEMS(x) (sizeof(x) / sizeof(x[0]))

double interpolate_segment(double x0, double y0, double x1, double y1, double x);
//===================  Serial port, Arroyo TEC controller and TTi PSU ENDS here  =======================//

#endif