// Log.h: interface for the CFileLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__0F098EAB_6C3D_4A7D_A75D_0D5C986D67C9__INCLUDED_)
#define AFX_LOG_H__0F098EAB_6C3D_4A7D_A75D_0D5C986D67C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_MSG_LEN 2000

#include "ILog.h"
//////////////////////////////////////////////////////////////////////////
//
// CFileLog ��־��
//
// ����������־�ļ�
//
// �̳��� ILog �ӿ�
//
// ���ù��캯��������־�ļ���
// ����ѡ���Ǹ��ǣ�isOverWritten=true������׷�ӣ�isOverWritten=false��
//
// ���� write(),writeLn() �� debugWrite(),debugWriteLn() д��־���ı�
//
//////////////////////////////////////////////////////////////////////////

class CFileLog : public ILog
{
public:
	CFileLog();
	CFileLog(std::string logFile, std::string extName, BOOL isOverWritten=FALSE,BOOL ShowTimeBeforeLevel=FALSE);
	virtual ~CFileLog();

	virtual std::string getLogName();

	void setLogLevel(LogLevel level);
	static LogLevel getDefaultLogLevel();     // ��̬ʵ��

	void write(std::string logMsg);
	void writeLn(std::string logMsg);
	
	virtual void write(LogLevel expectedLevel, std::string logMsg);
	virtual void writeLn(LogLevel expectedLevel, std::string logMsg);

// 	void debugWrite(string logMsg);
// 	void debugWriteLn(string logMsg);

protected:
	CStdioFile log;

	LogLevel m_level;
	BOOL m_ShowTimeBeforeLevel;

};

#endif // !defined(AFX_LOG_H__0F098EAB_6C3D_4A7D_A75D_0D5C986D67C9__INCLUDED_)
