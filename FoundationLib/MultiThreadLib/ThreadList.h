#pragma once

#include <c++\foudationlib\datastructlib\pointerlist.h>
#include "threadbase.h"

using namespace std;

class CThreadList : public CPointerList<CThreadBase *>
{
public:
	CThreadList(void);
	~CThreadList(void);

	void startAll();
	void stopAll();
	void removeAll();
	int getAliveCount();  // ���������С���ͣ��Ԥ��ͣ
	int getStartedCount();  // ���С���ͣ��Ԥ��ͣ
	void dontStopThread();

private:
	BOOL m_toStopThread;
};
