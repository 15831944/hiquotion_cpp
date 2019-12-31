// LogConfig.cpp: implementation of the CLogConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "LogLibLog.h"
#include "LogConfig.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>
#include <C++\FoudationLib\FileSysLib\FileOperation.h>
#include <algorithm>
#include "LogLevel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// extern CLogLibLog loglibLog;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogConfig::CLogConfig(string configName)
{
	section="LOG";
	ShowTimeBeforeLevel="ShowTimeBeforeLevel";
	CreateScreenLog="CreateScreenLog";
	ScreenLogLevel="ScreenLogLevel";
	
	CreateFileLog="CreateFileLog";
	FileLogLevel="FileLogLevel";
	LogFileName="LogFileName";
	LogFileNameAddDate="LogFileNameAddDate";
	SubFolderName="SubFolderName";
	FileLogOverwritten="FileLogOverwritten";
	
	appPath=CFolderOperation::GetModulePath();
	config.setFileName((LPTSTR)(LPCTSTR)(appPath + "\\" + configName.c_str()));
	if(!CFileOperation::isFileExist(appPath + "\\" + configName.c_str()))
	{
//		loglibLog.doLog(LOGLEVEL_SHOWERROR,"�����ļ� " + configName+ " �����ڣ�");
		AfxMessageBox(("�����ļ� " + configName+ " �����ڣ�").c_str());
	}
}

CLogConfig::~CLogConfig()
{

}

//	�Ƿ���ÿ����־ǰ��ʾʱ��
BOOL CLogConfig::getShowTimeBeforeLevel()
{
	string result=config.getSectionValueString(section,ShowTimeBeforeLevel);
	// תΪСд
	transform(result.begin(),result.end(),result.begin(),tolower);

	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}

//	��Ļ��־�Ƿ񴴽�
BOOL CLogConfig::getCreateScreenLog()
{
	string result=config.getSectionValueString(section,CreateScreenLog);
	// תΪСд
	transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}

//	������Ļ��־�������
LogLevel CLogConfig::getScreenLogLevel()
{
	string result=config.getSectionValueString(section,ScreenLogLevel);
	return CLogLevel::String2LogLevel(result);
}

//	�ļ���־�Ƿ񴴽�
BOOL CLogConfig::getCreateFileLog()
{
	string result=config.getSectionValueString(section,CreateFileLog);
	// תΪСд
	transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}

//	�����ļ���־�������
LogLevel CLogConfig::getFileLogLevel()
{
	string result=config.getSectionValueString(section,FileLogLevel);
	return CLogLevel::String2LogLevel(result);
}

//	��־�ļ�����������չ������չ��Ϊ.log��
string CLogConfig::getLogFileName()
{
	return config.getSectionValueString(section,LogFileName);
}

//	��־�ļ����Ƿ�����ں�׺
BOOL CLogConfig::getLogFileNameAddDate()
{
	string result=config.getSectionValueString(section,LogFileNameAddDate);
	// תΪСд
	transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}

//	���԰���־�ļ���������־�ŵ�һ�����ļ����У�ָ�����ļ�������SubFolderName=������Ϊ������ͬĿ¼�ڴ����ļ���־��
string CLogConfig::getSubFolderName()
{
	return config.getSectionValueString(section,SubFolderName);
}

//	�Ƿ�д������Ϊ׷�����ݣ�
BOOL CLogConfig::getFileLogOverwritten()
{
	string result=config.getSectionValueString(section,FileLogOverwritten);
	// תΪСд
	transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return TRUE;
	else if(result=="false")
		return FALSE;
	else
		return FALSE;
}
