// FreeArea.cpp: implementation of the CFreeArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FreeArea.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFreeArea::CFreeArea()
: IPokerArea(4, CPoint(0, 10))
{
	setBorderColor(RGB(255,255,255));
	setBorderStyle(BS_SOLID);
	setFillStyle(BS_SOLID);
	setMovingEffected(ChildHandled);
}

CFreeArea::~CFreeArea()
{

}

// �ж��Ƿ�������Ƶķ���
BOOL CFreeArea::canDrop(CPoker *poker, CPoint relativeTopLeft)
{
	if(!poker)
		return FALSE;

	// ���drop�����������滹���ƣ��Ͳ��������
	if(poker->getUIHandler(0))
		return FALSE;

	CRect pokerRect=poker->getRect();

	CRect rect;
	for(int i=0;i<4;i++)
	{
		CRect relativeRect=m_rect[i];
		relativeRect.OffsetRect(relativeTopLeft);
		
		if(rect.IntersectRect(&pokerRect, &relativeRect))
		{
			CPoker *bottom=m_pokerColumnArea[i]->getBottomPoker();
			// ������������ƣ�����������Ϊ A������Է���
			if(!bottom && poker->getPokerValue()==PVAce)
				return TRUE;

			// ��������������ƣ���������������ƣ���drop��������ͬ��ɫ��������ֵС1�����������
			if(bottom->getPokerType()==poker->getPokerType() && bottom->getPokerValue()==poker->getPokerValue()-1)
				return TRUE;

			return FALSE;
		}
	}

	return FALSE;
}

// �¼�����
void CFreeArea::OnSize(int cx, int cy)
{
	int left=cx/25;
	int width=cx/5;
	int interval=cx/25;
	
	int top=cy/20;
	int height=cy*4/5;
	
	for(int i=0;i<4;i++)
	{
// 		m_areaRect[i].left=left+i*(width+interval);
		m_areaRect[i].left=left+i*(CPoker::getWidth()+interval);
		m_areaRect[i].top=top;
		m_areaRect[i].right=m_areaRect[i].left+CPoker::getWidth(); //width;
		m_areaRect[i].bottom=top+height;
		
		m_pokerColumnArea[i]->setRect(m_areaRect[i]);
	}
}
