// DialogPanelSwitcher.cpp: implementation of the CDialogPanelSwitcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FVerifyShell.h"
#include "DialogPanelSwitcher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDialogPanelSwitcher::CDialogPanelSwitcher()
: m_currentSelected(0), m_oldSelected(m_currentSelected)
{
	m_panelList.setSelfDestroy(FALSE);
}

CDialogPanelSwitcher::~CDialogPanelSwitcher()
{

}

void CDialogPanelSwitcher::insert(CDialog *dlg)
{
	if(!dlg)
		return;

	m_panelList.push_back(dlg);
}

void CDialogPanelSwitcher::remove(CDialog *dlg)
{
	if(!dlg)
		return;
	
	m_panelList.remove(dlg);
}
void CDialogPanelSwitcher::removeAt(unsigned int index)
{
	if(index>=m_panelList.size())
		return;

	m_panelList.remove(m_panelList.at(index));
}

int CDialogPanelSwitcher::getCount()
{
	return m_panelList.size();
}

unsigned int CDialogPanelSwitcher::getCurrentSelected()
{
	return m_currentSelected;
}

void CDialogPanelSwitcher::setCurrentSelected(unsigned int index)
{
	if(index>=m_panelList.size())
		return;

	// �����ǰѡ��������������һ�£��򷵻�
	// ���ڵ�һ�ε��øú�����ʱ�򣬵�ǰ���������������0����ȣ���Ҫ�ų��������
	if(m_currentSelected!=m_oldSelected && m_currentSelected==index)
		return;

	CDialogPanelSwitcherEvent changingEvent(this, "SelectChanging", index, m_currentSelected);
	SelectChanging.raiseEvent(this, &changingEvent);

	m_oldSelected=m_currentSelected;
	m_currentSelected=index;
	
	CDialogPanelSwitcherEvent changeEvent(this, "SelectChanged", m_currentSelected, m_oldSelected);
	SelectChanged.raiseEvent(this, &changeEvent);

	if(m_oldSelected==-1)
	{
		for(int i=0;i<(int)m_panelList.size();i++)
		{
			CDialog *dlg=m_panelList.at(i);
			if(!dlg)
				continue;
			
			dlg->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		CDialog *dlg=m_panelList.at(m_oldSelected);
		if(dlg)
			dlg->ShowWindow(SW_HIDE);
	}

	CDialog *dlg=m_panelList.at(index);
	if(dlg)
		dlg->ShowWindow(SW_SHOW);
}

CDialogPanelSwitcherEvent::CDialogPanelSwitcherEvent(IEventRaisable *sender, std::string eventId, unsigned int currentSelected, unsigned int oldSelected)
: IEvent(sender, eventId), m_currentSelected(currentSelected), m_oldSelected(oldSelected)
{

}

CDialogPanelSwitcherEvent::~CDialogPanelSwitcherEvent()
{

}
