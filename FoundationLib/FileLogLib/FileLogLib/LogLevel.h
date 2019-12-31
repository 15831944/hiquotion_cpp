// LogLevel.h: interface for the CLogLevel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGLEVEL_H__AF5D0C92_6802_4712_9F7D_471B37E3B627__INCLUDED_)
#define AFX_LOGLEVEL_H__AF5D0C92_6802_4712_9F7D_471B37E3B627__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

enum eLogLevel
{
//	LOGLEVEL_SHOWALL,           // ��ʾ������־����
	LOGLEVEL_SHOWDEBUG,         // ���Լ����Գ���ʱ��Ҫ����ģ�����������ݵ�
//	LOGLEVEL_SHOWRELEASEDEBUG,  // �ڳ��򽻸�ʹ�õ�ʱ����ʾ�ı��ڳ�����ĵ�����Ϣ�������Ϣ�� Release �汾���Կ�����ʾ
	LOGLEVEL_SHOWINFO,          // ��ʾ��Ϣ
	LOGLEVEL_SHOWWARNING,       // ��ʾ������Ϣ
	LOGLEVEL_SHOWERROR,         // ��ʾ������Ϣ
//	LOGLEVEL_SHOWLOGONLY,       // ����ʾ��־����

// �ڳ����ȶ���һ������Ϊ LOGLEVEL_SHOWWARNING ���ɡ�
};

typedef eLogLevel LogLevel;

class CLogLevel  
{
public:
	CLogLevel();
	virtual ~CLogLevel();

	static std::string LogLevel2String(LogLevel level);
	static LogLevel String2LogLevel(std::string level);

};

#endif // !defined(AFX_LOGLEVEL_H__AF5D0C92_6802_4712_9F7D_471B37E3B627__INCLUDED_)
