#pragma once

#include "ithread.h"
#include <afxmt.h>

#define Thread_Normal_Exit 0;          // �߳������˳�
#define Thread_Error 0xE0000000;       // �߳��쳣�˳�
#define Thread_To_Stop 0xE0000001;     // �߳�׼���˳�
#define Thread_Stop_Forced 0xE0000002; // �̱߳�ǿ���˳�

class CThreadBase : public IThread
{
public:
	CThreadBase(void);
	virtual ~CThreadBase(void);

	HANDLE getThreadHandle();
	void start();
	void pause();
	virtual void stop();
	void terminate();
	UINT run();
	DWORD getExitCode();
	ThreadStatus getStatus(){return m_status;};
// 	// ֹͣ�̣߳����ȴ��߳̽���
// 	// �ȴ� ms ����֮���������ֵ��ʧ�ܻ�ȡ������ֱ�ӽ����߳�
// 	void join(int ms=INFINITE);

	string getMessage(){return m_message;};

protected:
	// �̳�CThread������࣬��Ҫ��д�÷�����������߳���Ҫ��ɵ�����
	virtual UINT threadRun(){return 0;};

	HANDLE m_handle;
	DWORD m_threadId;
	ThreadStatus m_status;
	BOOL m_toStop;  // ��ʶ�ͻ��Ƿ�ϣ���߳�����������ֹ����������stop����
	string m_message;
	UINT m_returnValue;

	CEvent m_threadEvent;
};
