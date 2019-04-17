//==============================================================================
// DLLMAIN.CPP
//==============================================================================

#include "asl.h"
#include "user.h"
#include "resource.h"

// ********************************************************************
// Function prototypes for local functions within DLLMAIN.CPP

BOOL InitializeProcessData(void);
BOOL UninitializeProcessData(void);

bool operator>>(FILE*& ar, FUNCTION_LIBRARY_EXPORT_INFO& g_fle);

// ********************************************************************
// Process global data - this data is shared between all threads in the process

extern short g_test_descr_n;
extern unsigned short *g_pBoard_count;
extern board_desc **g_pBoard_descs;

FUNCTION_LIBRARY_EXPORT_INFO g_fle;

extern void initialize_required_board_configs(void);

// Turn off "warning C4101: xxx : unreferenced local variable" for dwThreadId and hThread
#pragma warning (disable : 4101)

// ********************************************************************
BOOL APIENTRY DllMain( HINSTANCE hInstDll, DWORD dwReason, LPVOID lpReserved )
{
	HANDLE hThread;
	DWORD dwThreadId;
	BOOL bReturnStatus = TRUE;

	switch (dwReason)
	{
		// The DLL is being mapped into the process's address space
		case DLL_PROCESS_ATTACH:
			break;

		// A thread is being created - not all threads may come here
		case DLL_THREAD_ATTACH:
			break;

		// A thread is exiting cleaning - not being terminated
		case DLL_THREAD_DETACH:
			break;

		// The DLL is being unmapped from the process's address space
		// Process must exit cleanly to come here - can't terminate
		case DLL_PROCESS_DETACH:
			UninitializeProcessData();
			break;
	}

	return (bReturnStatus);
}

bool operator>>(FILE*& ar, FUNCTION_LIBRARY_EXPORT_INFO& g_fle)
{
	char ipd_version[32];
	fscanf( ar, "%s",	&ipd_version);

	for (short function_i = 0; function_i < g_test_descr_n; function_i ++)
	{
		FUNCTION_PARAM_DATA param;
		dlog_test dt_data;
		int function_no, num_params, num_sub_tests;
	
		fscanf( ar, "%d",	&function_no);
		fscanf( ar, "%d",	&num_params);
		fscanf( ar, "%d",	&num_sub_tests);
	
		int iDevnum;
		int iCount = 0;
		char function_name[32];
	
		fscanf( ar, "%d",	&iDevnum);
		fscanf( ar, "%d",	&iCount);
	
		if (strcmp(ipd_version,"1.0.0.0") != 0)
		{
			fread(&function_name, 1, 1, ar );
		}
	
		memset(function_name,0,sizeof(function_name));
		fread(&function_name, iCount, 1, ar );
	
		g_fle.SetFunctionDevNum(function_no, iDevnum);
		g_fle.SetFunctionName(function_no, function_name);
		g_fle.SetParamsN(function_no, num_params);
		g_fle.SetSubTestsN(function_no, num_sub_tests);
	
		for (short param_i = 0; param_i < num_params; param_i ++)
		{
			char dValue[256];
			int iType;
			float dMul = 1.0;
			int iPower;
			char param_unit[8];
			char param_interfacename[32];
			char param_cname[32];
	
			fscanf( ar, "%d",	&iCount);
			fread(&dValue, 1, 1, ar );
			memset(dValue,0,sizeof(dValue));
			fread(&dValue, iCount, 1, ar );
			fscanf( ar, "%d",		&iType);
			fscanf( ar, "%e",		&dMul);
			fscanf( ar, "%d",		&iPower);
			fscanf( ar, "%d",	&iCount);
	
			if (strcmp(ipd_version,"1.0.0.0") != 0)
			{
				fread(&param_unit, 1, 1, ar );
			}
	
			memset(param_unit,0,sizeof(param_unit));
			fread(&param_unit, iCount, 1, ar );
			fscanf( ar, "%d",	&iCount);
			fread(&param_interfacename, 1, 1, ar );
			memset(param_interfacename,0,sizeof(param_interfacename));
			fread(&param_interfacename, iCount, 1, ar );
			fscanf( ar, "%d",	&iCount);
			fread(&param_cname, 1, 1, ar );
			memset(param_cname,0,sizeof(param_cname));
			fread(&param_cname, iCount, 1, ar );
	
			param.Value().SetValue(&dValue,iType);
			param.SetMultiplier(dMul);
			param.Value().m_power = (BYTE) iPower;
			param.SetUnitsString(param_unit);
			param.SetUserInterfaceName(param_interfacename);
			param.SetCLangName(param_cname);
	
			g_fle.SetParamData(function_no, param_i, param);
		}
	
		for (short subtest_i = 0; subtest_i < num_sub_tests; subtest_i ++)
		{
			memset(&dt_data, 0, sizeof(dlog_test));
	
			float dMaxValue = 0.0;
			float dMinValue = 0.0;
			short iPower;
			short max_limit_active, min_limit_active;
			char subtest_name[16];
			char subtest_comment[80];
			char subtest_unit[8];
			char subtest_note[16];
	
			fscanf( ar, "%d",	&iCount);
			fread(&subtest_name, 1, 1, ar );
			memset(subtest_name,0,sizeof(subtest_name));
			fread(&subtest_name, iCount, 1, ar );
			strcpy(dt_data.test_name, subtest_name);

			fscanf( ar, "%d",	&iCount);
			fread(&subtest_comment, 1, 1, ar );
			memset(subtest_comment,0,sizeof(subtest_comment));
			fread(&subtest_comment, iCount, 1, ar );
			fscanf( ar, "%d",	&iCount);
			fread(&subtest_unit, 1, 1, ar );
			memset(subtest_unit,0,sizeof(subtest_unit));
			fread(&subtest_unit, iCount, 1, ar );
			fscanf( ar, "%d",	&iCount);
			fread(&subtest_note, 1, 1, ar );
			memset(subtest_note,0,sizeof(subtest_note));
			fread(&subtest_note, iCount, 1, ar );
	
			strcpy(dt_data.pretest_comment,subtest_comment);
			strcpy(dt_data.units, subtest_unit);
			strcpy(dt_data.note, subtest_note);
	
			fscanf( ar, "%d",		&iPower);
			dt_data.power = (char) iPower;
	
			fscanf( ar, "%d",		&max_limit_active);
			dt_data.max_limit_active = (char)max_limit_active;
	
			for (short maxlimit_i=0; maxlimit_i < 4; maxlimit_i++)
			{
				fscanf( ar, "%e",	&dMaxValue);
				dt_data.f_max_limit_val[maxlimit_i] = (float)dMaxValue;
			}
	
			fscanf( ar, "%d",		&min_limit_active);
			dt_data.min_limit_active = (char)min_limit_active;
	
			for (short minlimit_i=0; minlimit_i < 4; minlimit_i++)
			{
				fscanf( ar, "%e",	&dMinValue);
				dt_data.f_min_limit_val[minlimit_i] = (float)dMinValue;
			}
	
			g_fle.SetSubTestData(function_no, subtest_i, &dt_data);
		}
	}
	
	return true;
}

// Set this warning back to default to be safe
#pragma warning (default : 4101)

BOOL InitializeProcessData(void)
{
    g_fle.SetLibraryDevNum(0);
    g_fle.SetFunctionsN(g_test_descr_n);

	HMODULE	hLibrary		= NULL;
	HRSRC	hResource		= NULL;
	HGLOBAL hResourceLoaded = NULL;
	LPBYTE	lpBuffer		= NULL;
	
	hLibrary = ::LoadLibrary("Inno3_MX.dll");
	hResource = ::FindResource(hLibrary, MAKEINTRESOURCE(IDR_IPD_DATA), "IPD");
	
	if (hResource)
	{
		hResourceLoaded = ::LoadResource(hLibrary, hResource);
		if (hResourceLoaded)
		{
			lpBuffer = (LPBYTE) LockResource(hResourceLoaded);
			if (lpBuffer)
			{
				DWORD	dwFileSize		 = 0;
				DWORD	dwBytesWritten	 = 0;
				HANDLE  hFile			 = INVALID_HANDLE_VALUE;
				char	szTempPath[MAX_PATH];
				char	szTempFilePath[MAX_PATH];
	
				::GetTempPath(sizeof(szTempPath)/sizeof(szTempPath[0]), szTempPath);
				::GetTempFileName(szTempPath,"IPD",0,szTempFilePath);
	
				dwFileSize = ::SizeofResource(hLibrary, hResource);
				hFile = ::CreateFile(szTempFilePath,
					GENERIC_WRITE,
					0,
					NULL,
					CREATE_ALWAYS,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
	
				if (hFile != INVALID_HANDLE_VALUE)
				{
					::WriteFile(hFile, lpBuffer, dwFileSize, &dwBytesWritten, NULL);
					::CloseHandle(hFile);
	
					FILE* stream = NULL;
					stream = fopen(szTempFilePath, "rb" );
					if(stream )
					{
						stream >> g_fle;
						fclose(stream);
					}
	
					::DeleteFile(szTempFilePath);
					::FreeLibrary(hLibrary);
				}
			}
		}  
	}

	// Board info for functions
	initialize_required_board_configs();

	return TRUE;
}

BOOL UninitializeProcessData(void)
{
	// For each function in this library, delete the board descriptors
	// then delete the array of pointers to those descriptors

	if ( g_pBoard_descs )
	{
		for ( short func = 0; func < g_test_descr_n; func++ )
		{
			delete [] g_pBoard_descs[func];
		}
		delete [] g_pBoard_descs;
	}

	// Delete array containing the number of boards needed by each function.
	if ( g_pBoard_count )
	{
		delete [] g_pBoard_count;
	}

	return TRUE;
}
