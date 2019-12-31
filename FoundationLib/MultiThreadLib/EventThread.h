#pragma once
#include "threadbase.h"
#include <C++\FoudationLib\EventLib\EventEmu-��MFC���¼�����\IEventRaisable.h>
#include <string>
#include <C++\FoudationLib\EventLib\EventEmu-��MFC���¼�����\Delegate.h>

class CEventThread :
	public CThreadBase, public IEventRaisable
{
public:
	CEventThread(void);
	~CEventThread(void);

	CDelegate ThreadCompleted;

protected:
	void raiseEvent(IEventRaisable *sender, std::string eventId, int ret=0, std::string msg="");
};
