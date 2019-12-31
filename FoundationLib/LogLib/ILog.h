// ILog.h: interface for the ILog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILOG_H__7AB09502_335E_4CB4_B0C0_A6E6ABC1D5A6__INCLUDED_)
#define AFX_ILOG_H__7AB09502_335E_4CB4_B0C0_A6E6ABC1D5A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// enum enumLogLevel
// {
// 	//	LOGLEVEL_SHOWALL,           // ��ʾ������־����
// 	LOGLEVEL_SHOWDEBUG,         // ���Լ����Գ���ʱ��Ҫ����ģ�����������ݵ�
// 	//	LOGLEVEL_SHOWRELEASEDEBUG,  // �ڳ��򽻸�ʹ�õ�ʱ����ʾ�ı��ڳ�����ĵ�����Ϣ�������Ϣ�� Release �汾���Կ�����ʾ
// 	LOGLEVEL_SHOWINFO,          // ��ʾ��Ϣ
// 	LOGLEVEL_SHOWWARNING,       // ��ʾ������Ϣ
// 	LOGLEVEL_SHOWERROR,         // ��ʾ������Ϣ
// 	//	LOGLEVEL_SHOWLOGONLY,       // ����ʾ��־����
// 
// 	// �ڳ����ȶ���һ������Ϊ LOGLEVEL_SHOWWARNING ���ɡ�
// };
// 
// typedef enumLogLevel LogLevel;

// #include <LogLib\LogLevel.h>

#include <C++\FoudationLib\Interface.h>

#include "LogLevel.h"
#include <string>

using namespace std;

MyInterface ILog  
{
public:
	ILog();
	virtual ~ILog();

	virtual void setLogLevel(LogLevel level);

	virtual void write(std::string logMsg);
	virtual void writeLn(std::string logMsg);

	virtual void write(LogLevel expectedLevel, std::string logMsg);
	virtual void writeLn(LogLevel expectedLevel, std::string logMsg);

// 	virtual void debugWrite(string logMsg)=0;
// 	virtual void debugWriteLn(string logMsg)=0;


};

#endif // !defined(AFX_ILOG_H__7AB09502_335E_4CB4_B0C0_A6E6ABC1D5A6__INCLUDED_)
