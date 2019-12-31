// Rect.cpp: implementation of the CRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "Rectangle.h"
#include "RectangleTracker.h"
#include "RectanglePropertySet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4786)

IMPLEMENT_SERIAL(CRectangle, CShapeObj, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangle::CRectangle() : CShapeObj()
{

}

CRectangle::CRectangle(CRect rect) : CShapeObj(rect)
{

}

CRectangle::~CRectangle()
{

}

// ����

string CRectangle::getType()                   // ��ȡ���ƶ��������
{
	return "CRectangle";
}

CTracker CRectangle::getTracker()   // ��ȡѡ�п�
{
	CRectangleTracker rectTracker(m_rect);
	return rectTracker;
}

void CRectangle::setRect(CRect rect)  // ���þ��εĴ�С 
{
	m_rect=rect;
}

// ����

void CRectangle::draw(CDC *pDC)                // ��Ļ�ϻ���
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
	pDC->Rectangle(m_rect);
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

// �ڴ������ƶ����ʱ����ƣ����draw���ƺܸ��ӣ��ڴ������ƶ����ʱ������������򻯻��ƣ�����߶�̬���Ƶ�Ч�ʣ�
void CRectangle::drawOnCreating(CDC *pDC)
{
	pDC->MoveTo(m_rect.TopLeft());
	pDC->Rectangle(m_rect);
}

BOOL CRectangle::isHitMe(CPoint hitPoint)      // �����������Ƿ�����˸û��ƶ���
{
	refreshRect();
	return m_rect.PtInRect(hitPoint);
}

void CRectangle::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_rect.OffsetRect(moveShift);
}

void CRectangle::refreshRect()    // ������ͼ�εľ�������ת�˵�ʱ��ͨ���÷���ת�����
{
	if(m_rect.right<m_rect.left)
	{
		long tmp=m_rect.left;
		m_rect.left=m_rect.right;
		m_rect.right=tmp;
	}
	if(m_rect.bottom<m_rect.top)
	{
		long tmp=m_rect.bottom;
		m_rect.bottom=m_rect.top;
		m_rect.top=tmp;
	}
}

void CRectangle::Serialize(CArchive &ar)
{
	CShapeObj::Serialize(ar);
	if (ar.IsStoring())
	{

	}
	else
	{

	}
	
}

