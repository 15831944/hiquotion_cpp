// LogLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LogLib.h"
#include "LogLibLog.h"
#include "LogConfig.h"
#include "ScreenLog.h"
#include "FileLog.h"
#include "LogList.h"
#include "LogBuilder.h"
#include "Remark.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

CLogLibLog loglibLog;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;
	}

// 	; �Ƿ���ÿ����־ǰ��ʾʱ��
// 	ShowTimeBeforeLevel=
// 	
// 	; ��Ļ��־�Ƿ񴴽�
// 	CreateScreenLog=
// 	; ������Ļ��־�������
// 	ScreenLogLevel=
// 	
// 	; �ļ���־�Ƿ񴴽�
// 	CreateFileLog=
// 	; �����ļ���־�������
// 	FileLogLevel=
// 	; ��־�ļ�����������չ������չ��Ϊ.log��
// 	LogFileName=log
// 	; ��־�ļ����Ƿ�����ں�׺
// 	LogFileNameAddDate=
// 	; ���԰���־�ļ���������־�ŵ�һ�����ļ����У�ָ�����ļ�������SubFolderName=������Ϊ������ͬĿ¼�ڴ����ļ���־��
// 	SubFolderName=Logs
// 	; �Ƿ�д������Ϊ׷�����ݣ�
// 	FileLogOverwritten=
	
// 	CLogConfig logConfig;
// 	printf("ShowTimeBeforeLevel=%d\n",logConfig.getShowTimeBeforeLevel());
// 	printf("CreateScreenLog=%d\n",logConfig.getCreateScreenLog());
// 	printf("ScreenLogLevel=%s\n",CLogLevel::LogLevel2String(logConfig.getScreenLogLevel()).c_str());
// 	printf("CreateFileLog=%d\n",logConfig.getCreateFileLog());
// 	printf("FileLogLevel=%s\n",CLogLevel::LogLevel2String(logConfig.getFileLogLevel()).c_str());
// 	printf("LogFileName=%s\n",logConfig.getLogFileName().c_str());
// 	printf("LogFileNameAddDate=%d\n",logConfig.getLogFileNameAddDate());
// 	printf("SubFolderName=%s\n",logConfig.getSubFolderName().c_str());
// 	printf("FileLogOverwritten=%d\n",logConfig.getFileLogOverwritten());

// 	CScreenLog screenLog;
// 	CFileLog fileLog("MyLog.log");
//	CLogList logs;

// 	logs.add((ILog *)&screenLog);
// 	logs.writeLn("����Ļ���");
// 	logs.add((ILog *)&fileLog);
// 	logs.writeLn("��Ļ���ļ������");
// 	logs.remove(screenLog.getLogName());
// 	logs.writeLn("���ļ����");


// 	CLogBuilder logBuilder(&logs,"C:\\");
// 	logs.writeLn("heihei haha hoho!");
// 	logs.writeLn(LOGLEVEL_SHOWINFO,"LOGLEVEL_SHOWINFO");

	CRemark remark;
	remark.doLog(LOGLEVEL_SHOWERROR,"hahahohohehe!");

	system("pause");

	return nRetCode;
}
