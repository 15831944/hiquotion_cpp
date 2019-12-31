// IShape.cpp: implementation of the IShape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IShape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IShape::IShape()
: IDrawing(), m_oldPen(NULL), m_oldBrush(NULL), m_isUseClip(FALSE), m_parentRgn(NULL), m_pTmpRgn(NULL)
{
	m_backColor=RGB(255,255,255);
	m_fillStyle=BS_SOLID;
	m_borderColor=RGB(0,0,0);
	m_borderStyle=PS_SOLID;
	m_borderWidth=1;
// 	m_figureMap.clear();
}

IShape::IShape(int left, int top, int right, int bottom)
: IDrawing(), ILocation(left, top, right, bottom), m_oldPen(NULL), m_oldBrush(NULL), m_isUseClip(FALSE), m_parentRgn(NULL), m_pTmpRgn(NULL)
{
	m_backColor=RGB(255,255,255);
	m_fillStyle=BS_SOLID;
	m_borderColor=RGB(0,0,0);
	m_borderStyle=PS_SOLID;
	m_borderWidth=1;
// 	m_figureMap.clear();
}

IShape::IShape(CRect rect)
: IDrawing(), ILocation(rect), m_oldPen(NULL), m_oldBrush(NULL), m_isUseClip(FALSE), m_parentRgn(NULL), m_pTmpRgn(NULL)
{
	m_backColor=RGB(255,255,255);
	m_fillStyle=BS_SOLID;
	m_borderColor=RGB(0,0,0);
	m_borderStyle=PS_SOLID;
	m_borderWidth=1;
// 	m_figureMap.clear();
}

IShape::~IShape()
{

}

// ����

void IShape::preparePenAndBrush(CDC *pDC)  // �ڻ�ͼǰ����׼���ñʺͻ�ˢ
{
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = m_borderColor;
	
	// PS_ENDCAP_ROUND ��ʾԲ��
	// 	pen.CreatePen(m_lineStyle|PS_GEOMETRIC|PS_ENDCAP_ROUND, 2, &logBrush);
	if(m_borderStyle>=0)
	{
		m_pen.CreatePen(m_borderStyle|PS_GEOMETRIC|PS_ENDCAP_SQUARE,m_borderWidth, &logBrush);
	}
	else
		m_pen.CreateStockObject(NULL_PEN);
	m_oldPen=pDC->SelectObject(&m_pen);

	switch(m_fillStyle)
	{
	case 0:  // ʵ�����
		m_brush.CreateSolidBrush(m_backColor);
		m_oldBrush=pDC->SelectObject(&m_brush);
		break;
	case 1:  // ͸�����
		// 		brush.CreateSysColorBrush(0);
		m_brush.CreateStockObject(NULL_BRUSH);
		m_oldBrush=pDC->SelectObject(&m_brush);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:  // Hatch ���
		m_brush.CreateHatchBrush(m_fillStyle-2,m_backColor);
		m_oldBrush=pDC->SelectObject(&m_brush);
		break;
	}
}

void IShape::restorePenAndBrush(CDC *pDC)  // ��ͼ֮�󣬻ָ�ԭ���ıʺͻ�ˢ
{
	if(m_oldBrush)
	{
		pDC->SelectObject(m_oldBrush);
		m_oldBrush=NULL;
	}

	if(m_oldPen)
	{
		pDC->SelectObject(m_oldPen);
		m_oldPen=NULL;
	}

	if(m_pen.GetSafeHandle())
		m_pen.DeleteObject();

	if(m_brush.GetSafeHandle())
		m_brush.DeleteObject();
}

void IShape::draw(CDC *pDC, CPoint point, CRgn *parentRgn)
{
	if(!pDC)
		return;
	
	if(!pDC->GetSafeHdc())
		return;
	
	preparePenAndBrush(pDC);

	prepareRgn(pDC, point, parentRgn);
	
	drawMe(pDC, point);

	restoreRgn(pDC);

	restorePenAndBrush(pDC);
}

void IShape::drawMe(CDC *pDC, CPoint point)
{
	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	pDC->MoveTo(p);
	CRect rect(p, m_rect.Size());
	
	pDC->Rectangle(&rect);
}

void IShape::prepareRgn(CDC *pDC, CPoint point, CRgn *parentRgn)
{
	if(!pDC)
		return;

	m_parentRgn=parentRgn;

	if(m_isUseClip)
	{
		createRng(point);

// 		pDC->SelectClipRgn(&m_rgn, RGN_AND);

		if(parentRgn)
		{
			// �����ͼ��ʹ�����򣬲��Ҹ����򲻿գ�˵����Ҫ����������ȡ����

			if(m_tmpRgn.GetSafeHandle())
				m_tmpRgn.DeleteObject();
			m_tmpRgn.CreateRectRgn(0,0,1,1);

			int ret=m_tmpRgn.CombineRgn(&m_rgn, parentRgn, RGN_AND);
			switch(ret)
			{
			case 0:  // CombineRgn ����ʧ��
				m_pTmpRgn=parentRgn;
				break;
			case 1:  // ���ཻ
				m_pTmpRgn=parentRgn;
				break;
			case 2:  // �ཻ
			case 3:  // �ཻ�������ڶ������
				m_pTmpRgn=&m_tmpRgn;
				break;
			}
		}
		else
		{
			// ���������Ϊ�գ���ֻ���ñ�ͼ�ε�����

			m_pTmpRgn=&m_rgn;
		}
	}
	else
	{
		// �����ͼ�β�ʹ�����򣬵������򲻿գ���ֱ��ʹ�ø����򣬷��򣬲��ı� pDC ����������
		if(parentRgn)
			m_pTmpRgn=parentRgn;
		else
			m_pTmpRgn=NULL;
	}

	// ��������
	if(m_pTmpRgn)
 		pDC->SelectClipRgn(m_pTmpRgn);
}

void IShape::restoreRgn(CDC *pDC)
{
	if(pDC)
		pDC->SelectClipRgn(m_parentRgn);
}

void IShape::createRng(CPoint point)
{
	if(m_rgn.GetSafeHandle())
		m_rgn.DeleteObject();

	CRect rect=m_rect;
	rect.OffsetRect(point);

	m_rgn.CreateRectRgnIndirect(&rect);
}

// �ж��ཻ
// BOOL IShape::intersect(CRect rect)
// {
// 
// }


void IShape::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_rect.OffsetRect(moveShift);
}

void IShape::moveTo(CPoint point)      // �ƶ���
{
	m_rect.SetRect(point.x, point.y, point.x+m_rect.Width(), point.y+m_rect.Height());
}

// ���Ӳ���
// ������������д���Ӳ����Ľ��
BOOL IShape::attach(CRect *rect)   // ���� IFigure��A������һ��rectָ�룬��rectָ����IFigure��B��rect����ôA�ı�rect�е�ֵʱ��B����ͼ�ε�λ�û���Ӧ�ı�
{
	return TRUE;
}

BOOL IShape::attach(IDrawing *figure) // ����ʵ�����������Ĺ��ܣ������ƶ�ʱ�������ӵ�IFigure��������figure���󣩻�һ���ƶ�
{
	return TRUE;
}
