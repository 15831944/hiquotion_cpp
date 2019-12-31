#include "StdAfx.h"
#include "ThreadBase.h"
#include "threadentry.h"

CThreadBase::CThreadBase(void)
{
	m_returnValue=0;
	m_toStop=FALSE;

	m_handle=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadEntry,this,CREATE_SUSPENDED,&m_threadId);
	if(!m_threadId)
		m_status=Error;
	else
		m_status=Created;
}

CThreadBase::~CThreadBase(void)
{
	if(m_status==Running || m_status==Paused || m_status==ToStop)
		terminate();

// 	m_threadEvent.SetEvent();

}

HANDLE CThreadBase::getThreadHandle()
{
	return m_handle;
}

void CThreadBase::start()
{
	if(m_status==Created || m_status==Paused || m_status==Stopped)
	{
		if(ResumeThread(m_handle)==(DWORD)-1)
		{
			m_message="�����߳�ʧ�ܣ�";
			m_status=Error;
		}
		else
			m_status=Running;
	}
}

void CThreadBase::pause()
{
	if(m_status==Running)
	{
		if(SuspendThread(m_handle)==(DWORD)-1)
		{
			m_message="��ͣ�߳�ʧ�ܣ�";
			m_status=Error;
		}
		else
			m_status=Paused;
	}
}

void CThreadBase::stop()
{
	if(m_status==Running || m_status==Paused)
	{
		m_status=ToStop;
// 		m_message="�û�ϣ���߳�����������ֹ��";
		m_toStop=TRUE;
	}
}

void CThreadBase::terminate()
{
	if(m_status!=Error && m_status!=Terminated && m_status!=Stopped)
	{
		m_returnValue=Thread_Stop_Forced;
		TerminateThread(m_handle,(DWORD)m_returnValue);
// 		m_message="ǿ����ֹ���̡߳�";
		m_status=Terminated;
	}
}

UINT CThreadBase::run()
{
	if(m_status==Error)
	{
		m_returnValue=Thread_Error;
		return Thread_Error;
	}

	m_status=Running;
// 	m_message="�߳̿�ʼִ�С�";

	if(!m_toStop)
		m_returnValue=threadRun();

	m_status=Stopped;
// 	m_message="�߳̽�����";
	ExitThread(m_returnValue);

// 	m_threadEvent.SetEvent();

	return 0;
}

DWORD CThreadBase::getExitCode()
{
	return m_returnValue;
}

// ֹͣ�̣߳����ȴ��߳̽���
// �ȴ� ms ����֮���������ֵ��ʧ�ܻ�ȡ������ֱ�ӽ����߳�
// void CThreadBase::join(int ms)
// {
// 	stop();
// 	DWORD ret=WaitForSingleObject(m_threadEvent, ms);
// 	switch(ret)
// 	{
// 	case WAIT_ABANDONED:
// 	case WAIT_TIMEOUT:
// 	case WAIT_FAILED:
// 		terminate();
// 		break;
// 	}
// }
