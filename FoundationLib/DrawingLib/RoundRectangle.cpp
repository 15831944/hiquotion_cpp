// RoundRectangle.cpp: implementation of the CRoundRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoundRectangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoundRectangle::CRoundRectangle()
: CRectangle(), m_roundCenter(CPoint(5, 5))
{

}

CRoundRectangle::CRoundRectangle(int left, int top, int right, int bottom, POINT roundCenter)
: CRectangle(left, top, right, bottom), m_roundCenter(roundCenter)
{

}

CRoundRectangle::CRoundRectangle(CRect rect, POINT roundCenter)
: CRectangle(rect), m_roundCenter(roundCenter)
{

}

CRoundRectangle::~CRoundRectangle()
{

}

// ����

int CRoundRectangle::getRoundPointX()          // ��ȡԲ�ǵ��ˮƽ����
{
	return m_roundCenter.x;
}

void CRoundRectangle::setRoundPointX(int x)    // ����Բ�ǵ��ˮƽ����
{
	m_roundCenter.x=x;
}

int CRoundRectangle::getRoundPointY()          // ��ȡԲ�ǵ�Ĵ�ֱ����
{
	return m_roundCenter.y;
}

void CRoundRectangle::setRoundPointY(int y)    // ����Բ�ǵ�Ĵ�ֱ����
{
	m_roundCenter.y=y;
}

// ����

void CRoundRectangle::drawMe(CDC *pDC, CPoint point)
{
	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	pDC->MoveTo(p);
	CRect rect(p, m_rect.Size());
	pDC->RoundRect(rect, m_roundCenter);
}

void CRoundRectangle::createRng(CPoint point)
{
	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	CRect rect(p, m_rect.Size());

	if(m_rgn.GetSafeHandle())
		m_rgn.DeleteObject();

	m_rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, m_roundCenter.x, m_roundCenter.y);

}

void CRoundRectangle::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_rect.OffsetRect(moveShift);
}
