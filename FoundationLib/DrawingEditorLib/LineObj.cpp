// LineObj.cpp: implementation of the CLineObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "LineObj.h"
#include "DrawnObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4786)

IMPLEMENT_SERIAL(CLineObj, CDrawnObj, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineObj::CLineObj()
{
	m_lineColor=RGB(0,0,0);
	m_lineStyle=0;
	m_lineWidth=1;
}

CLineObj::CLineObj(CRect rect) : CDrawnObj(rect)
{

}

CLineObj::~CLineObj()
{

}

void CLineObj::Serialize(CArchive &ar)
{
	CDrawnObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_lineColor;
		ar << m_lineStyle;
		ar << m_lineWidth;
	}
	else
	{
		// get the document back pointer from the archive
		ar >> m_lineColor;
		ar >> m_lineStyle;
		ar >> m_lineWidth;

	}

}

int CLineObj::getLineStyle()   // ��ȡ������ʽ
{
	return m_lineStyle;
}

void CLineObj::setLineStyle(int lineStyle)   // ����������ʽ
{
	m_lineStyle=lineStyle;
}

int CLineObj::getLineColor()   // ��ȡ������ɫ
{
	return m_lineColor;
}

void CLineObj::setLineColor(int lineColor)   // ����������ɫ
{
	m_lineColor=lineColor;
}

int CLineObj::getLineWidth()   // ��ȡ�������
{
	return m_lineWidth;
}

void CLineObj::setLineWidth(int lineWidth)   // �����������
{
	m_lineWidth=lineWidth;
}

