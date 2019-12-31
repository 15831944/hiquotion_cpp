// Elipse.cpp: implementation of the CElipse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "Elipse.h"
#include "RectangleTracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4786)

IMPLEMENT_SERIAL(CElipse, CRectangle, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CElipse::CElipse() : CRectangle()
{

}

CElipse::CElipse(CRect rect) : CRectangle(rect)
{
// 	m_rect=rect;
}

CElipse::~CElipse()
{

}

// ����

string CElipse::getType()                   // ��ȡ���ƶ��������
{
	return "CElipse";
}

// CTracker CElipse::getTracker()   // ��ȡѡ�п�
// {
// 	CRectangleTracker rectTracker(m_rect);
// 	return rectTracker;
// }



// ����

void CElipse::draw(CDC *pDC)                // ��Ļ�ϻ���
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
	pDC->Ellipse(m_rect);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

BOOL CElipse::isHitMe(CPoint hitPoint)      // �����������Ƿ�����˸û��ƶ���
{
	refreshRect();
	float a=m_rect.Width()/2.0,b=m_rect.Height()/2.0;
	CPoint center=m_rect.CenterPoint();
	if((hitPoint.x-center.x)*(hitPoint.x-center.x)/(a*a)+(hitPoint.y-center.y)*(hitPoint.y-center.y)/(b*b)<1.0)
		return TRUE;
	else
		return FALSE;
}

void CElipse::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_rect.OffsetRect(moveShift);
}

void CElipse::Serialize(CArchive &ar)
{
	CRectangle::Serialize(ar);
	if (ar.IsStoring())
	{

	}
	else
	{

	}
	
}
