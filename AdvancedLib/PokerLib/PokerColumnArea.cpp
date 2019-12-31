// PokerColumnArea.cpp: implementation of the CPokerColumnArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PokerColumnArea.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPokerColumnArea::CPokerColumnArea()
: m_relativeX(0), m_relativeY(0), m_bottomPoker(NULL)
{

}

CPokerColumnArea::~CPokerColumnArea()
{

}

CPoker *CPokerColumnArea::getBottomPoker()
{
	return m_bottomPoker;

// 	if(CTreeNode<IUIHandler *>::count()<=0)
// 		return NULL;
// 
// 	CPoker *childParent=(CPoker *)this;
// 	CPoker *child=(CPoker *)getUIHandler(0);
// 	while(child)
// 	{
// 		childParent=child;
// 		child=(CPoker *)child->getUIHandler(0);
// 	}
// 
// 	return childParent;  // ����Ҫ������������ƣ����� childParent �������������
}

// �ж��Ƿ�������Ƶķ���
BOOL CPokerColumnArea::canDrop(CPoker *poker, CPoint relativeTopLeft)
{
	if(!poker)
		return FALSE;

	// ��ȡ����������ƣ����һ����Ҳû�У��򷵻� NULL
	CPoker *bottom=getBottomPoker();
	if(!bottom)
	{
		// һ����Ҳû�У���ôֻ����� K 
		if(poker->getPokerValue()==PVKing)
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		// �Ѿ������ˣ�����������������ͬ��ɫ�����ұ����������ֵС1����������ƣ����򲻿���
		if(bottom->getPokerType()==poker->getPokerType() && bottom->getPokerValue()==poker->getPokerValue()+1)
			return TRUE;
		else
			return FALSE;
	}
}

// ��ȡ��һ�����Ƶ�λ��
CPoint CPokerColumnArea::getNextDrop()
{
	CRect rect;
	if(!getUIHandler(0))
	{
		rect=getRect();
		return rect.TopLeft();
	}

	CPoker *bottom=getBottomPoker();
	if(!bottom)
	{
		rect=getRect();
		return rect.TopLeft();
	}

	rect=bottom->getRect();
	rect.OffsetRect(m_relativeX, m_relativeY);
	return rect.TopLeft();
}

// ���Ʒ���
void CPokerColumnArea::drop(CPoker *poker)
{
// 	if(!m_bottomPoker)
//	if(CTreeNode<IUIHandler *>::count()<=0)
// 	{
		addUIHandler(poker);
		int y= (CTreeNode<IUIHandler *>::count()-1) * m_relativeY;
		poker->setRect(m_relativeX, y, m_relativeX + CPoker::getWidth(), y + CPoker::getHeight());
// 		m_bottomPoker=poker;
// 		return;
// 	}

// 	m_bottomPoker->addUIHandler(poker);
// 	poker->setRect(m_relativeX, m_relativeY, m_relativeX+CPoker::getWidth(), m_relativeY+CPoker::getHeight());
// 
// 	m_bottomPoker=poker;
}

// ʰ�Ʒ���
void CPokerColumnArea::pickup(CPoker *poker)
{
	if(CTreeNode<IUIHandler *>::count()<=0)
		return;

	if(!poker)
		return;

	// ������Ҫ�� poker ������һ�����а� poker ��ɾ��
	CPoker *pokerParent=getParentofPokerChild(poker);
	if(!pokerParent)
		return;

	pokerParent->removeUIHandler(poker);
}

// �Ƿ����ָ��ֽ��
BOOL CPokerColumnArea::contain(CPoker *poker)
{
	if(CTreeNode<IUIHandler *>::count()<=0)
		return FALSE;

	if(!poker)
		return FALSE;

	return CTreeNode<IUIHandler *>::m_children->contain(poker);

// 	if(getUIHandler(0)==poker)
// 		return TRUE;
// 
// 	CPoker *child=(CPoker *)getUIHandler(0);
// 	while(child)
// 	{
// 		if(child->getUIHandler(0)==poker)
// 			return TRUE;
// 
// 		child=(CPoker *)child->getUIHandler(0);
// 	}
// 	
// 	return FALSE;
}

CPoker *CPokerColumnArea::getParentofPokerChild(CPoker *pokerChild)
{
	if(CTreeNode<IUIHandler *>::count()<=0)
		return NULL;

	if(!pokerChild)
		return NULL;
	
	CPoker *childParent=(CPoker *)this;
	CPoker *child=(CPoker *)getUIHandler(0);

	while(child)
	{
		if(child==pokerChild)
			return childParent;

		childParent=child;
		child=(CPoker *)child->getUIHandler(0);
	}
	
	return NULL;
}