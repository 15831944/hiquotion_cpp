// HandArea.h: interface for the CHandArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANDAREA_H__C2E8CE6B_C5AB_4B08_B47B_5672B2519FD7__INCLUDED_)
#define AFX_HANDAREA_H__C2E8CE6B_C5AB_4B08_B47B_5672B2519FD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FOUDATIONLIB\UIHANDLERLIB\IUIHandler.h>
#include <C++\ADVANCEDLIB\POKERLIB\IPokerArea.h>

class CHandArea : public IPokerArea  
{
public:
	CHandArea();
	virtual ~CHandArea();

	// �ж��Ƿ�������Ƶķ���
	virtual BOOL canDrop(CPoker *poker, CPoint relativeTopLeft=CPoint(0, 0));
	
protected:
	// �¼�����
	virtual void OnSize(int cx, int cy);

private:
	CRect m_areaRect[3];

};

#endif // !defined(AFX_HANDAREA_H__C2E8CE6B_C5AB_4B08_B47B_5672B2519FD7__INCLUDED_)
