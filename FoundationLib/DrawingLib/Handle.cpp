// Handle.cpp: implementation of the CHandle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Handle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHandle::CHandle(POINT handlePosition, BOOL bHandleEnabled)
{
	m_bHandleEnabled=bHandleEnabled;
	m_handlePosition=handlePosition;

	m_handleSize.cx=Default_Handle_Sizex;
	m_handleSize.cy=Default_Handle_Sizey;
}

CHandle::CHandle(int handlePositionX, int handlePositionY, BOOL bHandleEnabled)
{
	m_bHandleEnabled=bHandleEnabled;
	m_handlePosition.x=handlePositionX;
	m_handlePosition.y=handlePositionY;
	
	m_handleSize.cx=Default_Handle_Sizex;
	m_handleSize.cy=Default_Handle_Sizey;
}

CHandle::~CHandle()
{

}

// ����

BOOL CHandle::isHandleEnabled()    // �������ǲ��ǿ��Բ�����
{
	return m_bHandleEnabled;
}

SIZE CHandle::getHandleSize()      // ��ȡ����ĳߴ�
{
	return m_handleSize;
}

POINT CHandle::getHandlPosition()  // ��ȡ�����λ��
{
	return m_handlePosition;
}

void CHandle::setHandlePosition(int x, int y) // ���þ����λ��
{
	m_handlePosition.x=x;
	m_handlePosition.y=y;
}


void CHandle::setHandleSize(SIZE handleSize)  // ���þ����С��Ĭ�ϲ���Ҫ����
{
	m_handleSize=handleSize;
}

// ����

void CHandle::drawHandle(CDC *DC)
{
	CRect rect(m_handlePosition,m_handleSize);
	DC->Rectangle(&rect);
}

// ��ȡ������ڵ�Rect
CRect CHandle::getHandleRect()
{
	CRect rc(m_handlePosition,CPoint(m_handlePosition.x+getHandleSize().cx,m_handlePosition.y+getHandleSize().cy));
	return rc;
}
