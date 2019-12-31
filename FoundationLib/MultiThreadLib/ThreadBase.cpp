#include "StdAfx.h"
#include "ThreadBase.h"
#include "threadentry.h"

CThreadBase::CThreadBase(BOOL createNow)
: m_hThread(NULL)
{
	m_returnValue=0;
	m_toStop=FALSE;

	if(createNow)
		create();
}

CThreadBase::~CThreadBase(void)
{
	if(m_status==Running || m_status==Paused || m_status==ToStop)
		terminate();
}

BOOL CThreadBase::create()
{
	if(m_hThread)
		terminate();

	m_hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadEntry,this,CREATE_SUSPENDED,&m_threadId);
	if(!m_threadId)
	{
		m_message="�̴߳���ʧ�ܣ�";
		m_status=Error;
		return FALSE;
	}
	else
	{
		m_status=Created;
		return TRUE;
	}
}

void CThreadBase::close()
{
	ExitThread(m_returnValue);// ����ǹر����̵߳ģ���Ӧ�õ��������������������������
	m_hThread=NULL;
	m_status=Closed;
}

HANDLE CThreadBase::getThreadHandle()
{
	return m_hThread;
}

BOOL CThreadBase::start()
{
	if(m_status==Stopped)
		create();

	DWORD ret=ResumeThread(m_hThread);
// 	if(ResumeThread(m_hThread)==(DWORD)-1)
	if(ret==(DWORD)-1)
	{
		m_message="�����߳�ʧ�ܣ�";
		m_status=Error;
		return FALSE;
	}
	else
	{
		m_status=Running;
		return TRUE;
	}
}

BOOL CThreadBase::pause()
{
	if(SuspendThread(m_hThread)==(DWORD)-1)
	{
		m_message="��ͣ�߳�ʧ�ܣ�";
		m_status=Error;
		return FALSE;
	}
	else
	{
		m_status=Paused;
		return TRUE;
	}
}

void CThreadBase::stop()
{
	if(m_status==Paused)
		start();

	m_status=ToStop;
	m_toStop=TRUE;
}

void CThreadBase::terminate()
{
	if(m_status!=Error && m_status!=Terminated && m_status!=Stopped)
	{
		m_returnValue=Thread_Stop_Forced;
		TerminateThread(m_hThread,(DWORD)m_returnValue);
		m_hThread=NULL;
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

	m_toStop=FALSE;
	m_returnValue=threadRun();

	m_status=Stopped;

	return 0;
}

DWORD CThreadBase::getExitCode()
{
	return m_returnValue;
}

// 	// ֹͣ�̣߳����ȴ��߳̽���
// 	// �ȴ� ms ����֮���������ֵ��ʧ�ܻ�ȡ������ֱ�ӽ����߳�
// 	// ע�⣺���ø÷���֮ǰ���벻Ҫ���� stop ����
// void CThreadBase::join(int ms)
// {
// 	if(m_status!=Running && m_status!=Paused)
// 		return;
// 
// 	stop();
// 	DWORD ret=WaitForSingleObject(m_hThread, ms);
// 	switch(ret)
// 	{
// 	case WAIT_ABANDONED:
// 	case WAIT_TIMEOUT:
// 	case WAIT_FAILED:
// 		terminate();
// 		break;
// 	default:
// 
// 		break;
// 	}
// }

// ѭ���ж�״̬�ǲ��� ToStop�������򷵻�
// ���ø� join ����֮ǰ������Ҫ�ȵ��� stop ��������Ϊ����߳��Ѿ�ֹͣ�ˣ��÷�����ʹ�̴߳���ToStop״̬���Ӷ��޷��˳�ѭ��      xxxxxx��ʹ�߳�״̬�ı�� ToStop������û����ѭ����ֱ�ӷ�����
// �� virtual ����˼������������а���ͬ�����󣬲����Ѿ��������ú���Ĭ�ϲ��ᴦ���ͻ�ʹ�����������ѭ����
// �������������ͬ��������ô��Ҫ��д�÷��������ڵ��ø���ĸ÷���֮ǰ������ͬ������
void CThreadBase::join()
{
	if(m_status!=Running && m_status!=Paused && m_status!=ToStop)
		return;

	stop();

	while(m_status==ToStop)
	{
		Sleep(1);
	}
}
