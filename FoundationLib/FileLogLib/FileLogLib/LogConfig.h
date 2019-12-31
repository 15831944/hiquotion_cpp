// LogConfig.h: interface for the CLogConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_)
#define AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogLevel.h"
#include "XmlOperation.h"

class CLogConfig  
{
public:
	CLogConfig(std::string configName="log.xml");
	virtual ~CLogConfig();

	bool getShowTimeBeforeLevel() const { return m_showTimeBeforeLevel; }
// 	void setShowTimeBeforeLevel(bool val) { m_showTimeBeforeLevel = val; }
	LogLevel getLogLevel() const { return m_fileLogLevel; }
	std::string getLogFileName() const { return m_logFileName; }
// 	void setLogFileName(string val) { m_logFileName = val; }
	bool getLogFileNameAddDate() const { return m_logFileNameAddDate; }
// 	void setLogFileNameAddDate(bool val) { m_logFileNameAddDate = val; }
	std::string getSubFolderName() const { return m_subFolderName; }
// 	void setSubFolderName(string val) { m_subFolderName = val; }
	bool getFileLogOverwritten() const { return m_fileLogOverwritten; }
// 	void setFileLogOverwritten(bool val) { m_fileLogOverwritten = val; }

private:

//	�Ƿ���ÿ����־ǰ��ʾʱ��
	bool getShowTime();

//	�����ļ���־�������
	LogLevel getLevel();

//	��־�ļ�����������չ������չ��Ϊ.log��
	std::string getLogName();

//	��־�ļ����Ƿ�����ں�׺
	bool getFileNameWithDate();

//	���԰���־�ļ���������־�ŵ�һ�����ļ����У�ָ�����ļ�������SubFolderName=������Ϊ������ͬĿ¼�ڴ����ļ���־��
	std::string getSubFolder();

//	�Ƿ�д������Ϊ׷�����ݣ�
	bool getOverwritten();

private:
	CXmlOperation *m_xmlOperation;
	
	bool m_showTimeBeforeLevel;
	LogLevel m_fileLogLevel;
	std::string m_logFileName;
	bool m_logFileNameAddDate;
	std::string m_subFolderName;
	bool m_fileLogOverwritten;
};

#endif // !defined(AFX_LOGCONFIG_H__DCAC38DE_E577_47FE_A8DD_CB3D11C39FC4__INCLUDED_)
