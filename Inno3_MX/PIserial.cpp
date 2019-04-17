/************************************************************************************
 *			POWER INTEGRATION SERIAL INTERFACE HISTORY								*
 ************************************************************************************
19/12/17  ET  v1.00      - Initial release


History Revisions (Above)
*/

//==============================================================================
// PIserial.CPP
//==============================================================================
#include "asl.h"
#include "PIserial.h"

//===================  Serial port, Arroyo TEC controller and TTi PSU STARTS here  =======================//
//************** Comm port command **************//
int Com_Open(char* commport, HANDLE *hComm)
{
	*hComm = CreateFile( commport,
						GENERIC_READ | GENERIC_WRITE,
						0,
						NULL,
						OPEN_EXISTING,
						0,
						NULL);
	if (*hComm == INVALID_HANDLE_VALUE) return -1;
	
	return 0;
}

int Com_Setup(HANDLE hComm, DWORD BaudRate, BYTE ByteSize, BYTE Parity, BYTE StopBits, int timeout)
{
	DCB dcb = {0};
	COMMTIMEOUTS timeouts = {0};

	//FillMemory(&dcb, sizeof(dcb), 0);
	dcb.DCBlength = sizeof(dcb);					/* sizeof(DCB)                     */
	// Get current DCB
	if (!GetCommState(hComm, &dcb)) return -2;
	
	// Update DCB
	dcb.BaudRate			= BaudRate;				/* Baudrate at which running       */
//	dcb.fBinary				= TRUE;					/* Binary Mode (skip EOF check)    */
	dcb.fParity				= FALSE;				/* Enable parity checking          */
	dcb.fOutxCtsFlow		= FALSE;				/* CTS handshaking on output       */
	dcb.fOutxDsrFlow		= FALSE;				/* DSR handshaking on output       */
	dcb.fDtrControl			= DTR_CONTROL_DISABLE;	/* DTR Flow control                */
	dcb.fDsrSensitivity		= FALSE;				/* DSR Sensitivity                 */
//	dcb.fTXContinueOnXoff	= FALSE;				/* Continue TX when Xoff sent      */
	dcb.fOutX				= FALSE;				/* Enable output X-ON/X-OFF        */
	dcb.fInX				= FALSE;				/* Enable input X-ON/X-OFF         */
//	dcb.fErrorChar			= FALSE;				/* Enable Err Replacement          */
//	dcb.fNull				= FALSE;				/* Enable Null stripping           */
	dcb.fRtsControl			= RTS_CONTROL_DISABLE;	/* Rts Flow control                */
//	dcb.fAbortOnError		= FALSE;				/* Abort all reads and writes on Error */
//	dcb.XonLim				= 2048;					/* Transmit X-ON threshold         */
//	dcb.XoffLim				= 512;					/* Transmit X-OFF threshold        */
	dcb.ByteSize			= ByteSize;				/* Number of bits/byte, 4-8        */
	dcb.Parity				= Parity;				/* 0-4=None,Odd,Even,Mark,Space    */
	dcb.StopBits			= StopBits;				/* 0,1,2 = 1, 1.5, 2               */
//	dcb.XonChar				= 17;					/* Tx and Rx X-ON character        */
//	dcb.XoffChar			= 19;					/* Tx and Rx X-OFF character       */
//	dcb.ErrorChar			= 0;					/* Error replacement char          */
//	dcb.EofChar				= 0;					/* End of Input character          */
//	dcb.EvtChar				= 0;					/* Received Event character        */

	// Set new DCB
	if (!SetCommState(hComm, &dcb)) return -3;

	// Cache DCB
	g_TEC_dcb = dcb;

	// Set Comm timeouts
	timeouts.ReadIntervalTimeout			= timeout * 5;	/* Maximum time between read chars. */
	timeouts.ReadTotalTimeoutMultiplier		= timeout * 5;	/* Multiplier of characters.        */
	timeouts.ReadTotalTimeoutConstant		= timeout;		/* Constant in milliseconds.        */
	timeouts.WriteTotalTimeoutMultiplier	= timeout * 5;	/* Multiplier of characters.        */
	timeouts.WriteTotalTimeoutConstant		= timeout;		/* Constant in milliseconds.        */
	if (!SetCommTimeouts(hComm, &timeouts)) return -4;

	// Cache timeouts
	g_TEC_timeouts = timeouts;

	return 0;
}

int Com_Write_Line(HANDLE hComm, char* wbuffer)
{
	char bufstr[255] = {0};
	DWORD bufsize;
	DWORD BytesWritten;

	strcpy(bufstr, wbuffer);
	strcat(bufstr, CRLF);
	bufsize = strlen(bufstr);
	if (!WriteFile(	hComm,
					bufstr,
					bufsize,
					&BytesWritten,
					NULL)) return -1;

	return (int)BytesWritten;
}

int Com_Read_Line(HANDLE hComm, char* rbuffer)
{
	char tempchar = 0;
	DWORD BytesRead = 0;
	int bytecount = 0;

	do
	{
		ReadFile(hComm,
				 &tempchar,
				 sizeof(tempchar),
				 &BytesRead,
				 NULL);
		if (BytesRead == 0) break;
		rbuffer[bytecount++] = tempchar;
	} while (BytesRead > 0);

	return bytecount;
}

int Com_WriteRead_Line(HANDLE hComm, char* wbuffer, char* rbuffer, unsigned long delay_ms)
{
	Com_Write_Line(hComm, wbuffer);

	delay(delay_ms);

	return Com_Read_Line(hComm, rbuffer);
}

int Com_Close(HANDLE hComm)
{
	if (!CloseHandle(hComm)) return -1;
	
	return 0;
}

//************** TEC command **************//
HANDLE g_TEC_hComm = INVALID_HANDLE_VALUE;
COMSTAT g_TEC_comStat = {0};
DCB g_TEC_dcb = {0};
COMMTIMEOUTS g_TEC_timeouts = {0};
char* g_TEC_port = "COM3";
bool g_TEC_exist = false;

int TEC_Set_Commport(char* commport)
{
	g_TEC_port = commport;
	return 0;
}

int TEC_Open()
{
	if (g_TEC_hComm == INVALID_HANDLE_VALUE)
	{
		Com_Open(g_TEC_port, &g_TEC_hComm);
		if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;

		return Com_Setup(g_TEC_hComm, CBR_115200, 8, NOPARITY, ONESTOPBIT, 1);
	}
	return 0;
}

int TEC_Init()
{
	char rbuffer[255] = {0};

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	
	Com_WriteRead_Line(g_TEC_hComm, "*IDN?", rbuffer, 10);

	if (!strncmp(rbuffer, "Arroyo 5305 ", 11))
	{
		g_TEC_exist = true;
	}
	else
	{
		g_TEC_exist = false;
		return -2;
	}

	Com_Write_Line(g_TEC_hComm, "TERM 0;RADIX DEC");

	return 0;
}

int TEC_Setup()
{
	char rbuffer[255] = {0};

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	
	TEC_Disable();
	Com_Write_Line(g_TEC_hComm, "TEC:FAN 12.0,1,5");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:GAIN PID");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:HEATCOOL BOTH");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:SENSOR 6");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:LIM:ITE 1.80");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:LIM:RHI 192.0");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:LIM:RLO 20.0");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:LIM:THI 175.0");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:LIM:TLO -70.6");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:MODE:T");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:CONST 3.98480,-0.58700,-4.00000,100.000");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:PID 0.2500,0.0200,0.6000");
	//delay(10);
	Com_Write_Line(g_TEC_hComm, "TEC:TOL 0.10,5.0");
	delay(10);

	//FillMemory(&rbuffer, sizeof(rbuffer), 0);
	Com_WriteRead_Line(g_TEC_hComm, "ERRSTR?", rbuffer, 10);

	Com_Write_Line(g_TEC_hComm, "*CLS");

	if (!((strlen(rbuffer) == 3) && (rbuffer[0] == '0')))
	{
		printf("TEC ERROR CODE E-%s\n", rbuffer);
		return -2;
	}

	return 0;
}

int TEC_Set_Temp(double temperature)
{
	char wbuffer[255] = {0};
	
	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;

	sprintf(wbuffer, "TEC:T %.2f", temperature);

	Com_Write_Line(g_TEC_hComm, wbuffer);

	return 0;
}

int TEC_Get_Temp(double *temperature)
{
	char rbuffer[255] = {0};

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	
	Com_WriteRead_Line(g_TEC_hComm, "TEC:T?", rbuffer, 10);

	*temperature = atof(rbuffer);

	return 0;
}

int TEC_Settle_T(int timeout_s)
{
	char rbuffer[255] = {0};
	int status = 0;
	int cnt = 0;

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	
	while (cnt < timeout_s)
	{
		TEC_Get_Cond(&status);

		if ((status & OUTPUT_ON) && (!(status & OUT_OF_TOLERANCE))) break;
		
		delay(900);
		cnt++;
	}

	if (cnt >= timeout_s) return 1;

	return 0;
}

int TEC_Get_Cond(int *cond_reg)
{
	char rbuffer[255] = {0};

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	
	Com_WriteRead_Line(g_TEC_hComm, "TEC:COND?", rbuffer, 10);

	*cond_reg = atoi(rbuffer);

	return 0;
}

int TEC_Enable()
{
	char rbuffer[255] = {0};

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	
	Com_WriteRead_Line(g_TEC_hComm, "TEC:OUT?", rbuffer, 10);

	if (rbuffer[0] == '0')
	{
		Com_Write_Line(g_TEC_hComm, "TEC:OUT ON");
	}

	return 0;
}

int TEC_Disable()
{
	char rbuffer[255] = {0};

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	
	Com_WriteRead_Line(g_TEC_hComm, "TEC:OUT?", rbuffer, 10);

	if (rbuffer[0] == '1')
	{
		Com_Write_Line(g_TEC_hComm, "TEC:OUT OFF");
	}

	return 0;
}

int TEC_Close()
{
	Com_Close(g_TEC_hComm);
	g_TEC_hComm = INVALID_HANDLE_VALUE;

	return 0;
}

//************** TTi command **************//
HANDLE g_TTi_hComm = INVALID_HANDLE_VALUE;
COMSTAT g_TTi_comStat = {0};
DCB g_TTi_dcb = {0};
COMMTIMEOUTS g_TTi_timeouts = {0};
char* g_TTi_port = "COM4";
bool g_TTi_exist = false;

int TTi_Set_Commport(char* commport)
{
	g_TTi_port = commport;
	return 0;
}

int TTi_Open()
{
	if (g_TTi_hComm == INVALID_HANDLE_VALUE)
	{
		Com_Open(g_TTi_port, &g_TTi_hComm);
		if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;

		return Com_Setup(g_TTi_hComm, CBR_19200, 8, NOPARITY, ONESTOPBIT, 5);
	}
	return 0;
}

int TTi_Init()
{
	char rbuffer[255] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	
	Com_Write_Line(g_TTi_hComm, "*RST");
	delay(500);
	Com_WriteRead_Line(g_TTi_hComm, "*IDN?", rbuffer, 100);

	if (!strncmp(rbuffer, "THURLBY-THANDAR,QL355TP", 23))
	{
		g_TTi_exist = true;
	}
	else
	{
		g_TTi_exist = false;
		return -2;
	}

	return 0;
}

int TTi_Setup()
{
	int ret = 0;

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;

	if (ret == 0) ret = TTi_Output_Off(ALL_CHN);
	delay(50);
	if (ret == 0) ret = TTi_SetRange(OUTPUT1, RANGE_15V5A);
	delay(50);
	if (ret == 0) ret = TTi_SetRange(OUTPUT2, RANGE_15V5A);
	delay(50);
	if (ret == 0) ret = TTi_SetILimit(OUTPUT1, 5.0);
	delay(50);
	if (ret == 0) ret = TTi_SetILimit(OUTPUT2, 5.0);
	delay(50);
	if (ret == 0) ret = TTi_SetOVP(OUTPUT1, 14.0);
	delay(50);
	if (ret == 0) ret = TTi_SetOVP(OUTPUT2, 14.0);
	delay(50);
	if (ret == 0) ret = TTi_SetOCP(OUTPUT1, 5.2);
	delay(50);
	if (ret == 0) ret = TTi_SetOCP(OUTPUT2, 5.2);
	delay(50);
	if (ret == 0) ret = TTi_SetMode(LINKED);
	delay(50);

	return ret;
}

int TTi_SetV(int channel, double voltage)
{
	char wbuffer[255] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;

	sprintf(wbuffer, "V%d %.4f", channel, voltage);

	Com_Write_Line(g_TTi_hComm, wbuffer);

	return 0;
}

int TTi_GetV(int channel, double *voltage)
{
	char wbuffer[255] = {0};
	char rbuffer[255] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;
	
	sprintf(wbuffer, "V%dO?", channel);
	Com_WriteRead_Line(g_TTi_hComm, wbuffer, rbuffer, 100);

	*voltage = atof(rbuffer);

	return 0;
}

int TTi_GetI(int channel, double *current)
{
	char wbuffer[255] = {0};
	char rbuffer[255] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;
	
	sprintf(wbuffer, "I%dO?", channel);
	Com_WriteRead_Line(g_TTi_hComm, wbuffer, rbuffer, 100);

	*current = atof(rbuffer);

	return 0;
}

int TTi_SetILimit(int channel, double current)
{
	char wbuffer[255] = {0};
	double MAX_CURRENT = 0.5;
	int range;

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;

	TTi_GetRange(channel, &range);
	if (range == RANGE_15V5A) MAX_CURRENT = 5.0;
	if (range == RANGE_35V3A) MAX_CURRENT = 3.0;
	if (range == RANGE_35V0A5) MAX_CURRENT = 0.5;

	if (current < 0.001 || current > MAX_CURRENT) return -3;

	sprintf(wbuffer, "I%d %.3f", channel, current);

	Com_Write_Line(g_TTi_hComm, wbuffer);

	return 0;
}

int TTi_GetILimit(int channel, double *current)
{
	char wbuffer[255] = {0};
	char rbuffer[255] = {0};
	char temp[16] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;
	
	sprintf(wbuffer, "I%d?", channel);
	Com_WriteRead_Line(g_TTi_hComm, wbuffer, rbuffer, 100);

	strncpy(temp, rbuffer + 3, 16);
	if (strlen(temp) == 0)
	{
		*current = -99;
		return -3;
	}

	*current = atof(temp);

	return 0;
}

int TTi_SetOVP(int channel, double voltage)
{
	char wbuffer[255] = {0};
	double MAX_VOLTAGE = 40.0;
	//int range;

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;

	//TTi_GetRange(channel, &range);
	//if (range == RANGE_15V5A) MAX_VOLTAGE = 15.0;
	//if (range == RANGE_35V3A) MAX_VOLTAGE = 35.0;
	//if (range == RANGE_35V0A5) MAX_VOLTAGE = 35.0;

	if (voltage < 1.0 || voltage > MAX_VOLTAGE) return -3;

	sprintf(wbuffer, "OVP%d %.3f", channel, voltage);

	Com_Write_Line(g_TTi_hComm, wbuffer);

	return 0;
}

int TTi_GetOVP(int channel, double *voltage)
{
	char wbuffer[255] = {0};
	char rbuffer[255] = {0};
	char temp[16] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;
	
	sprintf(wbuffer, "OVP%d?", channel);
	Com_WriteRead_Line(g_TTi_hComm, wbuffer, rbuffer, 100);

	strncpy(temp, rbuffer + 4, 16);
	if (strlen(temp) == 0)
	{
		*voltage = -99;
		return -3;
	}

	*voltage = atof(temp);

	return 0;
}

int TTi_SetOCP(int channel, double current)
{
	char wbuffer[255] = {0};
	double MAX_CURRENT = 5.5;
	//int range;

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;

	//TTi_GetRange(channel, &range);
	//if (range == RANGE_15V5A) MAX_CURRENT = 5.0;
	//if (range == RANGE_35V3A) MAX_CURRENT = 3.0;
	//if (range == RANGE_35V0A5) MAX_CURRENT = 0.5;

	if (current < 0.01 || current > MAX_CURRENT) return -3;

	sprintf(wbuffer, "OCP%d %.3f", channel, current);

	Com_Write_Line(g_TTi_hComm, wbuffer);

	return 0;
}

int TTi_GetOCP(int channel, double *current)
{
	char wbuffer[255] = {0};
	char rbuffer[255] = {0};
	char temp[16] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;
	
	sprintf(wbuffer, "OCP%d?", channel);
	Com_WriteRead_Line(g_TTi_hComm, wbuffer, rbuffer, 100);

	strncpy(temp, rbuffer + 4, 16);
	if (strlen(temp) == 0)
	{
		*current = -99;
		return -3;
	}

	*current = atof(temp);

	return 0;
}

int TTi_SetRange(int channel, int vrange)
{
	char wbuffer[255] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;
	if (vrange < RANGE_15V5A || vrange > RANGE_35V0A5) return -3;

	sprintf(wbuffer, "RANGE%d %d", channel, vrange);

	Com_Write_Line(g_TTi_hComm, wbuffer);

	return 0;
}

int TTi_GetRange(int channel, int *vrange)
{
	char wbuffer[255] = {0};
	char rbuffer[255] = {0};
	char temp[16] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < OUTPUT1 || channel > OUTPUT2) return -2;
	
	sprintf(wbuffer, "RANGE%d?", channel);
	Com_WriteRead_Line(g_TTi_hComm, wbuffer, rbuffer, 100);

	strncpy(temp, rbuffer + 3, 1);
	if (strlen(temp) == 0)
	{
		*vrange = -99;
		return -3;
	}
	
	*vrange = atoi(temp);
	
	return 0;
}

int TTi_SetMode(int mode)
{
	char wbuffer[255] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (mode < LINKED || mode > CTRL_2) return -2;

	sprintf(wbuffer, "MODE %d", mode);

	Com_Write_Line(g_TTi_hComm, wbuffer);

	return 0;
}

int TTi_GetMode(int *mode)
{
	char wbuffer[255] = {0};
	char rbuffer[255] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	
	sprintf(wbuffer, "MODE?");
	Com_WriteRead_Line(g_TTi_hComm, wbuffer, rbuffer, 100);

	*mode = -99;
	if (strncmp(rbuffer, "LINKED", 6) == 0) *mode = LINKED;
	if (strncmp(rbuffer, "CTRL 1", 6) == 0) *mode = CTRL_1;
	if (strncmp(rbuffer, "CTRL 2", 6) == 0) *mode = CTRL_2;
	
	return 0;
}

int TTi_Output_On(int channel)
{
	char wbuffer[255] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < ALL_CHN || channel > BOTH) return -2;

	switch (channel)
	{
		case ALL_CHN:
			sprintf(wbuffer, "OPALL %d", TTi_ON);
			break;

		case BOTH:
			sprintf(wbuffer, "OP1 %d;OP2 %d", TTi_ON, TTi_ON);
			break;

		default:
			sprintf(wbuffer, "OP%d %d", channel, TTi_ON);
			break;
	}

	Com_Write_Line(g_TTi_hComm, wbuffer);

	return 0;
}

int TTi_Output_Off(int channel)
{
	char wbuffer[255] = {0};

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (channel < ALL_CHN || channel > BOTH) return -2;

	switch (channel)
	{
		case ALL_CHN:
			sprintf(wbuffer, "OPALL %d", TTi_OFF);
			break;

		case BOTH:
			sprintf(wbuffer, "OP1 %d;OP2 %d", TTi_OFF, TTi_OFF);
			break;

		default:
			sprintf(wbuffer, "OP%d %d", channel, TTi_OFF);
			break;
	}

	Com_Write_Line(g_TTi_hComm, wbuffer);

	return 0;
}

int TTi_Close()
{
	Com_Close(g_TTi_hComm);
	g_TTi_hComm = INVALID_HANDLE_VALUE;

	return 0;
}

//************** LHC command **************//

double g_LHC_T;
static double TTi_volt[] = {-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,7,8,9,10,11,12,13};
static double LHC_temp[] = {126,118,110,102,93,84,76,68,60,52,44,37,30,17,11,6,1.5,-2.4,-5.5,-8,-10,-11.4,-12.4,-13,-13.2,-13.4};

int LHC_Set_Temp(double temperature)
{
	int segment;
	double voltage = 0.0;
	double meas_T;
	int TEC_status;

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) TEC_Open();
	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	if (g_TEC_exist == false) return -2;

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) TTi_Open();
	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (g_TTi_exist == false) return -2;

	TEC_Get_Cond(&TEC_status);
	TEC_Get_Temp(&meas_T);

	if (g_LHC_T < -20) TEC_Disable();
	if (fabs(g_LHC_T - meas_T) > 50)
	{
		if (TEC_status & OUTPUT_ON) TEC_Disable();
		TTi_Output_Off(BOTH);
	}

	TEC_Set_Temp(temperature);
	g_LHC_T = temperature;

	if (temperature < -18)
	{
		voltage = 13.0;
	}

	if ((temperature >= -18) && (temperature < ROOM_LO))
	{
		for (segment = 0; segment < sizeof(LHC_temp); segment++)
		{
			if ((LHC_temp[segment] <= (temperature + 5)) &&
				(LHC_temp[segment + 1] >= (temperature + 5)))
			{
				voltage = interpolate_segment(LHC_temp[segment], TTi_volt[segment],
											  LHC_temp[segment + 1], TTi_volt[segment + 1],
											  (temperature + 5));
				break;
			}
		}
	}

	if ((temperature >= ROOM_LO) && (temperature < ROOM_HI))
	{
		voltage = 0.0;
	}

	if ((temperature >= ROOM_HI) && (temperature < 115))
	{
		for (segment = 0; segment < sizeof(LHC_temp); segment++)
		{
			if ((LHC_temp[segment] >= (temperature - 10)) &&
				(LHC_temp[segment + 1] <= (temperature - 10)))
			{
				voltage = interpolate_segment(LHC_temp[segment], TTi_volt[segment],
											  LHC_temp[segment + 1], TTi_volt[segment + 1],
											  (temperature - 10));
				break;
			}
		}
	}

	if (temperature >= 115)
	{
		voltage = -13.0;
	}

	if (voltage < 0)
	{
		voltage = voltage * -1;
		TTi_Output_On(AUXILIARY);
	}
	else
	{
		TTi_Output_Off(AUXILIARY);
	}
	
	TTi_SetV(OUTPUT1, voltage);
	TTi_SetV(OUTPUT2, voltage);

	TEC_Close();
	TTi_Close();

	return 0;
}

int LHC_Enable()
{
	double meas_T;
	int TEC_status;
	long cnt;
	int ret;

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) TEC_Open();
	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	if (g_TEC_exist == false) return -2;

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) TTi_Open();
	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (g_TTi_exist == false) return -2;

	TEC_Get_Cond(&TEC_status);
	TEC_Get_Temp(&meas_T);

	if (g_LHC_T < -20) TEC_Disable();
	if ((fabs(g_LHC_T - meas_T) > 50) && (TEC_status & OUTPUT_ON)) TEC_Disable();

	TTi_Output_On(BOTH);
	
	cnt = 0;
	while (fabs(g_LHC_T - meas_T) > 35)
	{
		if (cnt++ > 240)   // 4 minutes timeout
		{
			TEC_Disable();
			TTi_Output_Off(BOTH);
			return -3;
		}
		delay(900);
		TEC_Get_Temp(&meas_T);
	}

	TEC_Enable();

	if (g_LHC_T < -20)
	{
		ret = TEC_Settle_T(240);
	}
	else
	{
		ret = TEC_Settle_T(120);
	}

	TEC_Close();
	TTi_Close();

	return 0;
}

int LHC_Disable()
{
	double meas_T;
	long cnt;

	if (g_TEC_hComm == INVALID_HANDLE_VALUE) TEC_Open();
	if (g_TEC_hComm == INVALID_HANDLE_VALUE) return -1;
	if (g_TEC_exist == false) return -2;

	if (g_TTi_hComm == INVALID_HANDLE_VALUE) TTi_Open();
	if (g_TTi_hComm == INVALID_HANDLE_VALUE) return -1;
	if (g_TTi_exist == false) return -2;

	TEC_Get_Temp(&meas_T);
	if (meas_T > (ROOM_HI + 10)) TTi_Output_Off(AUXILIARY);
	else if (meas_T < (ROOM_LO - 10)) TTi_Output_On(AUXILIARY);

	TEC_Set_Temp(25);
	g_LHC_T = 25;

	if ((meas_T > (ROOM_HI + 10)) || (meas_T < (ROOM_LO - 10)))
	{
		TTi_SetV(OUTPUT1, 12);
		TTi_SetV(OUTPUT2, 12);
		TTi_Output_On(BOTH);
		TEC_Enable();
		cnt = 0;
		while ((meas_T > ROOM_HI) || (meas_T < ROOM_LO))
		{
			if (cnt++ > 180) break;   // 3 minutes timeout
			delay(900);
			TEC_Get_Temp(&meas_T);
		}
	}
	delay(100);
	TEC_Disable();
	TTi_SetV(OUTPUT1, 0);
	TTi_SetV(OUTPUT2, 0);
	TTi_Output_Off(ALL_CHN);

	TEC_Close();
	TTi_Close();

	return 0;
}

/**
* Returns the interpolated y-value.
* Saturates to y0 or y1 if x outside interval [x0, x1].
*/
double interpolate_segment(double x0, double y0, double x1, double y1, double x)
{
    double t;

    if (x <= x0) { return y0; }
    if (x >= x1) { return y1; }

    t =  (x-x0);
    t /= (x1-x0);

    return y0 + t*(y1-y0);
}
/******************************************************************************/

//===================  Serial port, Arroyo TEC controller and TTi PSU ENDS here  =======================//
