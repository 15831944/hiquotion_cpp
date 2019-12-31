#pragma once

#include "ithread.h"
// #include <afxmt.h>

#define Thread_Normal_Exit 0;          // �߳������˳�
#define Thread_Error 0xE0000000;       // �߳��쳣�˳�
#define Thread_To_Stop 0xE0000001;     // �߳�׼���˳�
#define Thread_Stop_Forced 0xE0000002; // �̱߳�ǿ���˳�

class CThreadBase : public IThread
{
public:
	CThreadBase(BOOL createNow=TRUE);
	virtual ~CThreadBase(void);

	BOOL create();
	void close();
	HANDLE getThreadHandle();
	BOOL start();
	virtual BOOL pause();
	virtual void stop();
	void terminate();
	UINT run();
	DWORD getExitCode();
	ThreadStatus getStatus(){return m_status;};

// 	// ֹͣ�̣߳����ȴ��߳̽���
// 	// �ȴ� ms ����֮���������ֵ��ʧ�ܻ�ȡ������ֱ�ӽ����߳�
// 	// �����������̫��ʹ����ȡ���˰�
// 	void join(int ms=INFINITE);

	// ѭ���ж�״̬�ǲ��� ToStop�������򷵻�
	// ���ø� join ����֮ǰ����Ҫ�ȵ��� stop ������ʹ�߳�״̬�ı�� ToStop������û����ѭ����ֱ�ӷ�����
	// �� virtual ����˼������������а���ͬ�����󣬲����Ѿ��������ú���Ĭ�ϲ��ᴦ���ͻ�ʹ�����������ѭ����
	// �������������ͬ��������ô��Ҫ��д�÷��������ڵ��ø���ĸ÷���֮ǰ������ͬ������
	virtual void join();

	string getErrMessage(){return m_message;};

	HANDLE m_hThread;

protected:

	// �̳�CThread������࣬��Ҫ��д�÷�����������߳���Ҫ��ɵ�����
	virtual UINT threadRun(){return 0;};

	DWORD m_threadId;
	ThreadStatus m_status;
	BOOL m_toStop;  // ��ʶ�ͻ��Ƿ�ϣ���߳�����������ֹ����������stop����
	string m_message;
	UINT m_returnValue;
};
