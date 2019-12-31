// LogBuilder.cpp: implementation of the CLogBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogBuilder.h"
#include <C++\FoundationLib\FileSysLib\FolderOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogBuilder::CLogBuilder()
:m_log(NULL)
{
	m_logPath=CFolderOperation::addGang(CFolderOperation::GetModulePath());

	// ���ϣ�����������ļ��ж������־�����뽫���Ϊ true��
	m_ignoreLogLevelinConfig=false;

	// �����ļ���־
// 		; ��־�ļ�����������չ������չ��Ϊ.log��
// 		LogFileName=m_log
// 		; ��־�ļ����Ƿ�����ں�׺
// 		LogFileNameAddDate=
// 		; ���԰���־�ļ���������־�ŵ�һ�����ļ����У�ָ�����ļ�������SubFolderName=������Ϊ������ͬĿ¼�ڴ����ļ���־��
// 		SubFolderName=Logs
// 		; �Ƿ�д������Ϊ׷�����ݣ�
// 		FileLogOverwritten=

	// �Ƿ���ļ���־�ŵ����ļ�����
	std::string subFolder=config.getSubFolderName();
	if(subFolder!="")
	{
		m_logPath += subFolder.c_str();
		m_logPath += "\\";

		// ���û�������ļ��У��򴴽�
		if(!CFolderOperation::isFolderExist(m_logPath.c_str()))
			CFolderOperation::createDir(m_logPath.c_str());
	}

	// ��ȡ���õ���־�ļ�������������չ����
	std::string logFileName=config.getLogFileName();
	if(logFileName=="")
		m_logPath += "mylog";
	else
		m_logPath += logFileName.c_str();

	// �ļ������Ƿ��������
	if(config.getLogFileNameAddDate())
	{
		CTime time=CTime::GetCurrentTime();
		CString strTime;
		strTime.Format("_%.4d%.2d%.2d",time.GetYear(),time.GetMonth(),time.GetDay());
		m_logPath += strTime;
	}

	// �����չ��
	m_logPath += ".log";

	BOOL isOverWritten=config.getFileLogOverwritten();
	m_log=new CFileLog();
	if(!m_log)
		return;

	if(!m_log->open(m_logPath, isOverWritten, config.getShowTimeBeforeLevel()))
		return;

	// �����ļ���־����
	if(m_ignoreLogLevelinConfig)
		m_log->setLogLevel(CFileLog::getDefaultLogLevel());
	else
		m_log->setLogLevel(config.getLogLevel());
}

CLogBuilder::~CLogBuilder()
{
	if(m_log)
	{
		delete(m_log);
		m_log=NULL;
	}
}
