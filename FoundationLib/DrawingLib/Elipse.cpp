// Elipse.cpp: implementation of the CElipse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Elipse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CElipse::CElipse() : CRectangle()
{

}

CElipse::CElipse(int left, int top, int right, int bottom)
: CRectangle(left, top, right, bottom)
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

// ����

void CElipse::drawMe(CDC *pDC, CPoint point)
{
	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	
	pDC->MoveTo(p);
	CRect rect(p, m_rect.Size());
	pDC->Ellipse(&rect);
}

void CElipse::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_rect.OffsetRect(moveShift);
}

void CElipse::createRng(CPoint point)
{
	if(m_rgn.GetSafeHandle())
		m_rgn.DeleteObject();

	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	
	CRect rect(p, m_rect.Size());
	m_rgn.CreateEllipticRgnIndirect(&rect);
}
