// LogLevel.cpp: implementation of the CLogLevel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogLevel.h"
// #include "LogLibLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// extern CLogLibLog loglibLog;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogLevel::CLogLevel()
{

}

CLogLevel::~CLogLevel()
{

}

std::string CLogLevel::LogLevel2String(LogLevel level)
{
	std::string sLevel="";
	switch(level)
	{
	case LOGLEVEL_SHOWDEBUG:
		sLevel="[DEBUG]";
		break;
	case LOGLEVEL_SHOWINFO:
		sLevel="[INFO]";
		break;
	case LOGLEVEL_SHOWWARNING:
		sLevel="[WARN]";
		break;
	case LOGLEVEL_SHOWERROR:
		sLevel="[ERROR]";
		break;
	}
	return sLevel;
}

LogLevel CLogLevel::String2LogLevel(std::string level)
{
	LogLevel logLevel=LOGLEVEL_SHOWINFO;
	CString csLeven=level.c_str();
	std::string strLOGLEVEL_SHOWDEBUG="LOGLEVEL_SHOWDEBUG";
	std::string strLOGLEVEL_SHOWINFO="LOGLEVEL_SHOWINFO";
	std::string strLOGLEVEL_SHOWWARNING="LOGLEVEL_SHOWWARNING";
	std::string strLOGLEVEL_SHOWERROR="LOGLEVEL_SHOWERROR";

	if(csLeven=="LOGLEVEL_SHOWDEBUG")
		logLevel=LOGLEVEL_SHOWDEBUG;
	else if(csLeven=="LOGLEVEL_SHOWINFO")
		logLevel=LOGLEVEL_SHOWINFO;
	else if(csLeven=="LOGLEVEL_SHOWWARNING")
		logLevel=LOGLEVEL_SHOWWARNING;
	else if(csLeven=="LOGLEVEL_SHOWERROR")
		logLevel=LOGLEVEL_SHOWERROR;
	else
	{
		// �� LogLib.log �����������Ϣ
// 		loglibLog.doLog(LOGLEVEL_SHOWWARNING,"�������־��������ַ�����" + level);
		std::string str="�������־��������ַ�����";
		str+=level;
		AfxMessageBox(str.c_str());

		// ����������־����Ϊ LOGLEVEL_SHOWINFO
// 		loglibLog.doLog(LOGLEVEL_SHOWWARNING,"������־����Ϊ LOGLEVEL_SHOWINFO");
		logLevel=LOGLEVEL_SHOWINFO;
	}
	return logLevel;
}
