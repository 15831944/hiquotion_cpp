// SystemVersion.cpp: implementation of the CSystemVersion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemVersion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemVersion::CSystemVersion()
{

}

CSystemVersion::~CSystemVersion()
{

}

typedef void(__stdcall*NTPROC)(DWORD*, DWORD*, DWORD*);

SystemVersion CSystemVersion::getSystemVersion()
{
	//���ж��Ƿ�Ϊwin8.1��win10
	HINSTANCE hinst = LoadLibrary("ntdll.dll");
	if(hinst)
	{
		DWORD dwMajor, dwMinor, dwBuildNumber;
		NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
		if(proc)
		{
			proc(&dwMajor, &dwMinor, &dwBuildNumber); 
			if (dwMajor == 6 && dwMinor == 3)	//win 8.1
			{
// 				vname = "Microsoft Windows 8.1";
// 				printf_s("�˵��Եİ汾Ϊ:%s\n", vname.c_str());
				return Win8_1;
			}
			if (dwMajor == 10 && dwMinor == 0)	//win 10
			{
// 				vname = "Microsoft Windows 10";
// 				printf_s("�˵��Եİ汾Ϊ:%s\n", vname.c_str());
				return Win10;
			}
		}
	}

	//�����жϲ���Win Server����Ϊ���˻�δ������ϵͳ�Ļ��ӣ���ʱ������



	//�ж�win8.1���µİ汾
	SYSTEM_INFO info;                //��SYSTEM_INFO�ṹ�ж�64λAMD������  
	GetSystemInfo(&info);            //����GetSystemInfo�������ṹ  
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	#pragma warning(disable:4996)
	if (GetVersionEx((OSVERSIONINFO *)&os))
	{
		BYTE wProductType=0;
#if _MSC_VER==1200
		//VC6
#define VER_NT_WORKSTATION  1 
#define PROCESSOR_ARCHITECTURE_AMD64 9
#define SM_SERVERR2 89

		wProductType=(BYTE)os.wReserved[1] % 256;
#else if _MSC_VER>1200
		//���ߵ�VC�汾
		wProductType=os.wProductType;
#endif
		//������ݰ汾��Ϣ�жϲ���ϵͳ����  
		switch (os.dwMajorVersion)
		{                        //�ж����汾��  
		case 4:
			switch (os.dwMinorVersion)
			{                //�жϴΰ汾��  
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
//					vname ="Microsoft Windows NT 4.0";  //1996��7�·���  
					return WinNT4_0;
				else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
//					vname = "Microsoft Windows 95";
					return Win95;
				break;
			case 10:
//				vname ="Microsoft Windows 98";
				return Win98;
				break;
			case 90:
//				vname = "Microsoft Windows Me";
				return WinME;
				break;
			}
			break;
		case 5:
			switch (os.dwMinorVersion)
			{               //�ٱȽ�dwMinorVersion��ֵ  
			case 0:
//				vname = "Microsoft Windows 2000";    //1999��12�·���  
				return Win2000;
				break;
			case 1:
//				vname = "Microsoft Windows XP";      //2001��8�·���  
				return WinXP;
				break;
			case 2:
				if (wProductType == VER_NT_WORKSTATION &&
					info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
// 					vname = "Microsoft Windows XP Professional x64 Edition";
					return WinXPx64;
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
//					vname = "Microsoft Windows Server 2003";   //2003��3�·���  
					return WinServer2003;
				else if (GetSystemMetrics(SM_SERVERR2) != 0)
// 					vname = "Microsoft Windows Server 2003 R2";
					return WinServer2003R2;
				break;
			}
			break;
		case 6:
			switch (os.dwMinorVersion)
			{
			case 0:
				if (wProductType == VER_NT_WORKSTATION)
//					vname = "Microsoft Windows Vista";
					return WinVista;
				else
//					vname = "Microsoft Windows Server 2008";   //�������汾  
					return WinServer2008;
				break;
			case 1:
				if (wProductType == VER_NT_WORKSTATION)
//					vname = "Microsoft Windows 7";
					return Win7;
				else
//					vname = "Microsoft Windows Server 2008 R2";
					return WinServer2008R2;
				break;
			case 2:
				if (wProductType == VER_NT_WORKSTATION)
//					vname = "Microsoft Windows 8";
					return Win8;
				else
//					vname = "Microsoft Windows Server 2012";
					return WinServer2012;
				break;
			}
			break;
		default:
//			vname = "δ֪����ϵͳ";
			return Unknown;
		}
// 		printf_s("�˵��Եİ汾Ϊ:%s\n", vname.c_str());
	}
// 	else
//		printf_s("�汾��ȡʧ��\n");

	return Unknown;

}