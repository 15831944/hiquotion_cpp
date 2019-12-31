// RoundRectangle.cpp: implementation of the CRoundRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "RoundRectangle.h"
#include "RoundRectangleTracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CRoundRectangle, CRectangle, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoundRectangle::CRoundRectangle() : CRectangle()
{
	m_roundCenter=CPoint(15,15);
	m_drawRoundHandle=FALSE;
}

CRoundRectangle::CRoundRectangle(CRect rect, POINT roundCenter, BOOL isDrawRoundHandle) : CRectangle(rect)
{
// 	m_rect=rect;
	m_roundCenter=roundCenter;
	m_drawRoundHandle=isDrawRoundHandle;
}

CRoundRectangle::~CRoundRectangle()
{

}

// ����

string CRoundRectangle::getType()                   // ��ȡ���ƶ��������
{
	return "CRoundRectangle";
}

CTracker CRoundRectangle::getTracker()   // ��ȡѡ�п�
{
	CRoundRectangleTracker rectTracker(m_rect, m_roundCenter,m_drawRoundHandle);
	return rectTracker;
}

void CRoundRectangle::setDrawRoundHandle(BOOL isDrawRoundHandle)   // �����Ƿ���Ƶ���Բ�ǻ��ȵľ��
{
	m_drawRoundHandle=isDrawRoundHandle;
}

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

void CRoundRectangle::draw(CDC *pDC)                // ��Ļ�ϻ���
{
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = m_borderColor;
	
	CPen pen;
	// PS_ENDCAP_ROUND ��ʾԲ��
	// 	pen.CreatePen(m_lineStyle|PS_GEOMETRIC|PS_ENDCAP_ROUND, 2, &logBrush);
	pen.CreatePen(m_borderStyle|PS_GEOMETRIC|PS_ENDCAP_SQUARE,m_borderWidth, &logBrush);
// 	CPen pen;
// 	pen.CreatePen(m_borderStyle,m_borderWidth,m_borderColor);
	CPen *oldPen=pDC->SelectObject(&pen);
	
	CBrush brush;
	CBrush *oldBrush=NULL;
	switch(m_fillStyle)
	{
	case 0:  // ʵ�����
		brush.CreateSolidBrush(m_backColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	case 1:  // ͸�����
		
		// 		brush.CreateSysColorBrush(0);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:  // Hatch ���
		brush.CreateHatchBrush(m_fillStyle-2,m_backColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	}

	pDC->MoveTo(m_rect.TopLeft());
	pDC->RoundRect(m_rect, m_roundCenter);
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

// �ڴ������ƶ����ʱ����ƣ����draw���ƺܸ��ӣ��ڴ������ƶ����ʱ������������򻯻��ƣ�����߶�̬���Ƶ�Ч�ʣ�
// void CRoundRectangle::drawOnCreating(CDC *pDC)
// {
// 	draw(pDC);
// }

BOOL CRoundRectangle::isHitMe(CPoint hitPoint)      // �����������Ƿ�����˸û��ƶ���
{
	refreshRect();
	return m_rect.PtInRect(hitPoint);
}

void CRoundRectangle::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_rect.OffsetRect(moveShift);
}

void CRoundRectangle::moveHandle(int nHandle, CPoint point)  // �ƶ����ƶ���Tracker�ĵ�nHandle�ž����point����
{
	if(nHandle<=HP_RIGHT_BOTTOM)
		m_rect=getTracker().moveTrackerHandle(nHandle,point);
	else
	{
		m_roundCenter.x=point.x-m_rect.TopLeft().x;
		m_roundCenter.y=point.y-m_rect.TopLeft().y;
		if(m_roundCenter.x<=0)
			m_roundCenter.x=0;
		else if(m_roundCenter.x>=m_rect.Width())
			m_roundCenter.x=m_rect.Width();
		if(m_roundCenter.y<=0)
			m_roundCenter.y=0;
		else if(m_roundCenter.y>=m_rect.Height())
			m_roundCenter.y=m_rect.Height();
	}
	
}

void CRoundRectangle::Serialize(CArchive &ar)
{
	CRectangle::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_roundCenter.x;
		ar << m_roundCenter.y;
		ar << (DWORD)m_drawRoundHandle;
	}
	else
	{
		ar >> m_roundCenter.x;
		ar >> m_roundCenter.y;
		DWORD dtmp=0;
		ar >> dtmp;
		m_drawRoundHandle=(BOOL)dtmp;
	}
	
}

// void CRoundRectangle::refreshRect()    // ������ͼ�εľ�������ת�˵�ʱ��ͨ���÷���ת�����
// {
// 	if(m_rect.right<m_rect.left)
// 	{
// 		long tmp=m_rect.left;
// 		m_rect.left=m_rect.right;
// 		m_rect.right=tmp;
// 	}
// 	if(m_rect.bottom<m_rect.top)
// 	{
// 		long tmp=m_rect.bottom;
// 		m_rect.bottom=m_rect.top;
// 		m_rect.top=tmp;
// 	}
// }

