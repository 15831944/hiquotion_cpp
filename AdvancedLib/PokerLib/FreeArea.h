// FreeArea.h: interface for the CFreeArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FREEAREA_H__35CC4A04_4C97_46FD_9BD8_E6E7E98DB108__INCLUDED_)
#define AFX_FREEAREA_H__35CC4A04_4C97_46FD_9BD8_E6E7E98DB108__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FOUDATIONLIB\UIHANDLERLIB\IUIHandler.h>
#include <C++\ADVANCEDLIB\POKERLIB\IPokerArea.h>
#include "Poker.h"
#include "PokerColumnArea.h"

class CFreeArea : public IPokerArea  
{
public:
	CFreeArea();
	virtual ~CFreeArea();

	// �ж��Ƿ�������Ƶķ���
	virtual BOOL canDrop(CPoker *poker, CPoint relativeTopLeft=CPoint(0, 0));
	
protected:
	// �¼�����
	virtual void OnSize(int cx, int cy);

private:
	CRect m_areaRect[4];

};

#endif // !defined(AFX_FREEAREA_H__35CC4A04_4C97_46FD_9BD8_E6E7E98DB108__INCLUDED_)
