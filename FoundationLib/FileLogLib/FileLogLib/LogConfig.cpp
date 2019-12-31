// LogConfig.cpp: implementation of the CLogConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "LogLibLog.h"
#include "LogConfig.h"
#include <algorithm>
#include "LogLevel.h"
#include <C++\FoundationLib\FileSysLib\FolderOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// extern CLogLibLog loglibLog;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogConfig::CLogConfig(std::string configName)
{
	CString logPath=CFolderOperation::addGang(CFolderOperation::GetModulePath())+"log.xml";
	m_xmlOperation=new CXmlOperation((LPTSTR)(LPCSTR)logPath);
	if(!m_xmlOperation->isOpenSuccess())
	{
		AfxMessageBox("�� log.xml �ļ�ʧ�ܣ�");
	}

	m_showTimeBeforeLevel=getShowTime();
	m_fileLogLevel=getLevel();
	m_logFileName=getLogName();
	m_logFileNameAddDate=getFileNameWithDate();
	m_subFolderName=getSubFolder();
	m_fileLogOverwritten=getOverwritten();

}

CLogConfig::~CLogConfig()
{
	delete m_xmlOperation;
}

//	�Ƿ���ÿ����־ǰ��ʾʱ��
bool CLogConfig::getShowTime()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("showTime");  // ��ȡ�ڵ�
	if(!element)
		return true;
	
	std::string result=m_xmlOperation->getElementText(element);
	if(result=="")
		return true;
	
	// תΪСд
	std::transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return true;
	else if(result=="false")
		return false;
	else
		return true;
}

//	�����ļ���־�������
LogLevel CLogConfig::getLevel()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("level");  // ��ȡ�ڵ�
	if(!element)
		m_fileLogLevel=LOGLEVEL_SHOWINFO;
	
	std::string result=m_xmlOperation->getElementText(element);
	if(result=="")
		m_fileLogLevel=LOGLEVEL_SHOWINFO;
	
	// תΪ��д
	std::transform(result.begin(),result.end(),result.begin(),toupper);
	
	return CLogLevel::String2LogLevel(result);
}

//	��־�ļ�����������չ������չ��Ϊ.log��
std::string CLogConfig::getLogName()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("fileName");  // ��ȡ�ڵ�
	if(!element)
		return "";
	
	std::string result=m_xmlOperation->getElementText(element);
	return result;
}

//	��־�ļ����Ƿ�����ں�׺
bool CLogConfig::getFileNameWithDate()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("fileNameWithDate");  // ��ȡ�ڵ�
	if(!element)
		return true;
	
	std::string result=m_xmlOperation->getElementText(element);
	if(result=="")
		return true;
	// תΪСд
	std::transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return true;
	else if(result=="false")
		return false;
	else
		return false;
}

//	���԰���־�ļ���������־�ŵ�һ�����ļ����У�ָ�����ļ�������SubFolderName=������Ϊ������ͬĿ¼�ڴ����ļ���־��
std::string CLogConfig::getSubFolder()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("subFolderName");  // ��ȡ�ڵ�
	if(!element)
		return "";
	
	std::string result=m_xmlOperation->getElementText(element);
	return result;
}

//	�Ƿ�д������Ϊ׷�����ݣ�
bool CLogConfig::getOverwritten()
{
	TiXmlElement *element=m_xmlOperation->getElementInSubtree("overwrite");  // ��ȡ�ڵ�
	if(!element)
		return false;
	
	std::string result=m_xmlOperation->getElementText(element);
	if(result=="")
		return false;

	// תΪСд
	std::transform(result.begin(),result.end(),result.begin(),tolower);
	
	if(result=="true")
		return true;
	else if(result=="false")
		return false;
	else
		return false;
}
