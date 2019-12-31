// ILine.cpp: implementation of the ILine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ILine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ILine::ILine()
: oldPen(NULL)
{
	m_start.x=0;
	m_start.y=0;
	m_end.x=0;
	m_end.y=0;
	
	m_lineColor=RGB(0,0,0);
	m_lineStyle=PS_SOLID;
	m_lineWidth=0;
	
	m_srcPointCap=PS_ENDCAP_SQUARE;
	m_dstPointCap=PS_ENDCAP_SQUARE;
}

ILine::~ILine()
{

}

// ����

CPoint ILine::getFirstPoint()
{
	return m_start;
}

CPoint ILine::getSrc()     // ��ȡ���
{
	return m_start;
}

CPoint ILine::getDst()     // ��ȡ�յ�
{
	return m_end;
}

// ��ȡ��������㡢�յ�ĺ�������
int ILine::getX1()
{
	return m_start.x;
}

void ILine::setX1(int x1)
{
	m_start.x=x1;
}

int ILine::getY1()
{
	return m_start.y;
}

void ILine::setY1(int y1)
{
	m_start.y=y1;
}

int ILine::getX2()
{
	return m_end.x;
}

void ILine::setX2(int x2)
{
	m_end.x=x2;
}

int ILine::getY2()
{
	return m_end.y;
}

void ILine::setY2(int y2)
{
	m_end.y=y2;
}

// ���������������˵�
void ILine::setPoints(CPoint src,CPoint dst)
{
	m_start.x=src.x;
	m_start.y=src.y;
	m_end.x=dst.x;
	m_end.y=dst.y;
}


// ����

void ILine::preparePen(CDC *pDC)  // �ڻ�ͼǰ����׼���ñ�
{
	// PS_ENDCAP_ROUND ��ʾԲ��
	pen.CreatePen(m_lineStyle|PS_GEOMETRIC|m_srcPointCap|m_dstPointCap,m_lineWidth, m_lineColor);
	CPen *oldPen=pDC->SelectObject(&pen);
}

void ILine::restorePen(CDC *pDC)  // ��ͼ֮�󣬻ָ�ԭ���ı�
{
	if(oldPen)
	{
		pDC->SelectObject(oldPen);
		oldPen=NULL;
	}

	if(pen.GetSafeHandle())
		pen.DeleteObject();
}

void ILine::draw(CDC *pDC, CPoint point)
{
	preparePen(pDC);

	drawMe(pDC, point);
	
	restorePen(pDC);
}

void ILine::drawMe(CDC *pDC, CPoint point)
{
	CPoint src=m_start;
	CPoint dst=m_end;
	src.Offset(point);
	dst.Offset(point);

	pDC->MoveTo(src);
	pDC->LineTo(dst);
}

void ILine::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_start.x+=moveShift.cx;
	m_start.y+=moveShift.cy;
	
	m_end.x+=moveShift.cx;
	m_end.y+=moveShift.cy;
}
