#pragma once

#include "threadstatus.h"

// ������̱߳�־
// ���Ǽ̳иýӿڵ��࣬��ʹ��ʱ���ñ�־���Զ���Ч
#define SUPPORT_MULTI_THREAD

class IThread
{
public:
	IThread(void){};
	virtual ~IThread(void){};

	virtual HANDLE getThreadHandle(){return NULL;};
	virtual BOOL start(){ return FALSE; };
	virtual int pause(){ return 0; };
	virtual void stop(){};
	virtual void terminate(){};
	virtual UINT run(){return 0;};
	virtual ThreadStatus getStatus(){return Terminated;};
	virtual void join(){};
};
