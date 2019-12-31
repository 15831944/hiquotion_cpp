// FtpUploadThread.cpp: implementation of the CFtpUploadThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FtpUploadThread.h"
#include <C++\3rdParty\CKFtpLib\include\CkSettings.h>
#include "FtpProgressEvent.h"
#include <C++\FoudationLib\StringExtLib\StringExt.h>
#include "FtpMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpUploadThread::CFtpUploadThread()
{
	m_threadType=1;
	m_progress.Progress+=this;
}

CFtpUploadThread::~CFtpUploadThread()
{
	m_progress.Progress-=this;
	m_ftp.put_AbortCurrent(true);
	m_ftp.Disconnect();
	CkSettings::cleanupMemory();
}

Begin_Event_Map(CFtpUploadThread)
Event_Map(&m_progress, "Progress", OnProgress)
End_Event_Map()

UINT CFtpUploadThread::threadRun()
{
	CString msg;
	bool success = m_ftp.UnlockComponent("AARONKFTP_p9PO06K09ZnG");
	if(success==false)
	{
		m_message="FTP �����Ȩʧ�ܣ�\n";
		m_message+=m_ftp.lastErrorText();
		sendFailedEvent();
		return -1;
	}
	
	m_ftp.put_Hostname((LPTSTR)(LPCSTR)m_ip);
	m_ftp.put_Port((int)m_port);
	m_ftp.put_Username((LPTSTR)(LPCSTR)m_user);
	m_ftp.put_Password((LPTSTR)(LPCSTR)m_psw);
	
	if(m_connectTimeout>0)  // Ĭ���� 30 ��
		m_ftp.put_ConnectTimeout(m_connectTimeout);
	if(m_readTimeout>0)
		m_ftp.put_ReadTimeout(m_readTimeout);
	m_ftp.put_Passive(true);  // Ĭ���� true
	m_ftp.put_PassiveUseHostAddr(true);  // ���Է���˱���ip��ַ

	m_ftp.put_EventCallbackObject(&m_progress);

	success = m_ftp.Connect();
	if (success==false) {
		msg.Format("ftp ���ӷ�����(%s:%d) ʧ��", m_ip, m_port);
		m_message=(LPTSTR)(LPCSTR)msg;
		sendFailedEvent();
		return -1;
	}

	success = m_ftp.ChangeRemoteDir(m_ftpFolder);
	if(success==false)
	{
		// m_ftpFolder �϶������� "/"
		// ��Ҫ�� FTP �ϴ����༶Ŀ¼
		CStringArray divfolders;
		CStringArray folders;
		CStringExt::Split(m_ftpFolder, divfolders, "/");
		if(divfolders.GetSize()==1)
		{
			// ��Ϊ���Ŀ¼����Ҳ�᷵��false�����Բ����жϷ��ؽ��
			success=m_ftp.CreateRemoteDir((LPTSTR)(LPCSTR)m_ftpFolder);
		}
		else /*if(divfolders.GetSize()>1)*/
		{
			folders.Add(divfolders[0]);
			int i=0;
			for(i=1;i<divfolders.GetSize();i++)
			{
				CString tmp;
				tmp.Format("%s/%s", folders[i-1], divfolders[i]);
				folders.Add(tmp);
			}

			for(i=1;i<divfolders.GetSize();i++)
			{
				// ��Ϊ���Ŀ¼����Ҳ�᷵��false�����Բ����жϷ��ؽ��
				success=m_ftp.CreateRemoteDir(folders[i]);
				Sleep(200);
				success=m_ftp.ChangeRemoteDir(folders[i]);
				if (success==false)
				{
					msg.Format("���� ftp Ŀ¼Ϊ %s ʧ��", folders[i]);
					m_message=(LPTSTR)(LPCSTR)msg;
					sendFailedEvent();
					return -1;
				}
			}
		}
	}

	success = m_ftp.ChangeRemoteDir(m_ftpFolder);
	if (success==false){
		msg.Format("���� ftp Ŀ¼Ϊ %s ʧ��", m_ftpFolder);
		m_message=(LPTSTR)(LPCSTR)msg;
		sendFailedEvent();
		return -1;
	}

	m_ftp.put_RestartNext(true); // �´��ش�
	CString log;
	log.Format("D:\\ftpUploadThread%d.log", m_localFileId);
	m_ftp.put_DebugLogFilePath((LPTSTR)(LPCSTR)log);

	int retryTimes=m_retryTimes;
	success = m_ftp.PutFile((LPTSTR)(LPCSTR)m_localFullPath, (LPTSTR)(LPCSTR)m_ftpFileName);
	while(success==false && retryTimes>0)
	{
		success = m_ftp.PutFile((LPTSTR)(LPCSTR)m_localFullPath, (LPTSTR)(LPCSTR)m_ftpFileName);
		if(success!=false)
			break;
		
		retryTimes--;
	}
	if (success==false)
	{
		msg.Format("�ļ� %s �ϴ�ʧ�ܣ�\n%s", m_localFullPath, m_ftp.lastErrorText());
		m_message=(LPTSTR)(LPCTSTR)msg;
		sendFailedEvent();
		return -1;
	}

	sendSuccessEvent();
	
	m_ftp.Disconnect();
	
	return 0;
}

void CFtpUploadThread::OnProgress( IEvent *e )
{
	CFtpProgressEvent *ee=(CFtpProgressEvent *)e;
// 	if(m_hwnd)
// 		PostMessage(m_hwnd, FU_PROGRESS, (WPARAM)this, (LPARAM)ee->getProgress());
	sendProgressEvent(ee->getProgress());
}

void CFtpUploadThread::sendProgressEvent( UINT progress )
{
	if(m_isRaiseWndEvent)
	{
		if(m_hwnd)
			PostMessage(m_hwnd, FU_PROGRESS, (WPARAM)this, (LPARAM)progress);
	}
	else
	{
		CFtpProgressEvent e(this, "Progress", m_localFileId, progress);
		Progress.raiseEvent(this, &e);
	}
}

void CFtpUploadThread::sendSuccessEvent()
{
	if(m_isRaiseWndEvent)
	{
		if(m_hwnd)
			PostMessage(m_hwnd, FU_SUCCESS, (WPARAM)this, 0);
	}
	else
	{
		IEvent e(this, "Success");
		Progress.raiseEvent(this, &e);
	}
}

void CFtpUploadThread::sendFailedEvent()
{
	if(m_isRaiseWndEvent)
	{
		if(m_hwnd)
			PostMessage(m_hwnd, FU_FAILED, (WPARAM)this, 0);
	}
	else
	{
		IEvent e(this, "Failed", m_message.c_str());
		Progress.raiseEvent(this, &e);
	}
}
