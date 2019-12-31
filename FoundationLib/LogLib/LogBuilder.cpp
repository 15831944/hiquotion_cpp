// LogBuilder.cpp: implementation of the CLogBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogBuilder.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogBuilder::CLogBuilder(CLogList *logList, string path)
:fileLog(NULL),screenLog(NULL)
{
	m_Path=CFolderOperation::addGang(path.c_str());

	// ���������Ļ��־��
	if(logConfig.getCreateScreenLog())
	{
		screenLog=new CScreenLog(logConfig.getShowTimeBeforeLevel());
		// ���������Ļ��־�ļ�������
		if(CLogBuilderBase::m_ignoreLogLevelinConfig)
			screenLog->setLogLevel(CScreenLog::getDefaultLogLevel());
		else
			screenLog->setLogLevel(logConfig.getScreenLogLevel());

		// ��ӵ���־�б�
		logList->add((ILog *)screenLog);
	}

	// ��������ļ���־
	if(logConfig.getCreateFileLog())
	{
// 		; ��־�ļ�����������չ������չ��Ϊ.log��
// 		LogFileName=log
// 		; ��־�ļ����Ƿ�����ں�׺
// 		LogFileNameAddDate=
// 		; ���԰���־�ļ���������־�ŵ�һ�����ļ����У�ָ�����ļ�������SubFolderName=������Ϊ������ͬĿ¼�ڴ����ļ���־��
// 		SubFolderName=Logs
// 		; �Ƿ�д������Ϊ׷�����ݣ�
// 		FileLogOverwritten=

		// �Ƿ���ļ���־�ŵ����ļ�����
		string subFolder=logConfig.getSubFolderName();
		if(subFolder!="")
		{
			m_Path += subFolder.c_str();
			m_Path += "\\";

			// ���û�������ļ��У��򴴽�
			if(!CFolderOperation::isFolderExist(m_Path))
				CFolderOperation::createDir(m_Path);
		}

		// ��ȡ���õ���־�ļ�������������չ����
		string logFileName=logConfig.getLogFileName();
		if(logFileName=="")
			m_Path += "mylog";
		else
			m_Path += logFileName.c_str();

		// �ļ������Ƿ������־
		if(logConfig.getLogFileNameAddDate())
		{
			CTime time=CTime::GetCurrentTime();
			CString strTime;
			strTime.Format("_%.4d%.2d%.2d",time.GetYear(),time.GetMonth(),time.GetDay());
			m_Path += strTime;
		}

		BOOL isOverWritten=logConfig.getFileLogOverwritten();
		fileLog=new CFileLog(m_Path.GetBuffer(m_Path.GetLength()),".log",isOverWritten,logConfig.getShowTimeBeforeLevel());

		// �����ļ���־����
		if(CLogBuilderBase::m_ignoreLogLevelinConfig)
			fileLog->setLogLevel(CFileLog::getDefaultLogLevel());
		else
			fileLog->setLogLevel(logConfig.getFileLogLevel());
		
		// ��LogHelper�������־��
		logList->add((ILog *)fileLog);
	}

}

CLogBuilder::~CLogBuilder()
{
	if(fileLog)
	{
		delete(fileLog);
		fileLog=NULL;
	}

	if(screenLog)
	{
		delete(screenLog);
		screenLog=NULL;
	}
}
