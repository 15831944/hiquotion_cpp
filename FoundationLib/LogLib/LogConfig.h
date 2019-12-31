// LogConfig.h: interface for the CLogConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_)
#define AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\INILib\IniOperation.h>
#include "LogLevel.h"

class CLogConfig  
{
public:
	CLogConfig(string configName="logconfig.ini");
	virtual ~CLogConfig();

//	�Ƿ���ÿ����־ǰ��ʾʱ��
	BOOL getShowTimeBeforeLevel();

//	��Ļ��־�Ƿ񴴽�
	BOOL getCreateScreenLog();

//	������Ļ��־�������
	LogLevel getScreenLogLevel();

//	�ļ���־�Ƿ񴴽�
	BOOL getCreateFileLog();

//	�����ļ���־�������
	LogLevel getFileLogLevel();

//	��־�ļ�����������չ������չ��Ϊ.log��
	string getLogFileName();

//	��־�ļ����Ƿ�����ں�׺
	BOOL getLogFileNameAddDate();

//	���԰���־�ļ���������־�ŵ�һ�����ļ����У�ָ�����ļ�������SubFolderName=������Ϊ������ͬĿ¼�ڴ����ļ���־��
	string getSubFolderName();

//	�Ƿ�д������Ϊ׷�����ݣ�
	BOOL getFileLogOverwritten();

private:
	CIniOperation config;
	CString appPath;
	
	char *section;
	char *ShowTimeBeforeLevel;
	char *CreateScreenLog;
	char *ScreenLogLevel;

	char *CreateFileLog;
	char *FileLogLevel;
	char *LogFileName;
	char *LogFileNameAddDate;
	char *SubFolderName;
	char *FileLogOverwritten;
};

#endif // !defined(AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_)
