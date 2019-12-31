// Label.cpp: implementation of the CLabel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "Label.h"
#include "RectangleTracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CLabel, CRectangle, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLabel::CLabel()
{
	m_caption="���������";
	m_foreColor=RGB(0,0,0);
	m_textAlign=0;
	memset(&m_font,0x00,sizeof(m_font));
	strcpy(m_font.lfFaceName,"����");
	m_font.lfHeight=16;
	m_font.lfWidth=8;
	m_font.lfUnderline=0;
	m_font.lfStrikeOut=0;
}

CLabel::CLabel(CRect rect, string caption, COLORREF color, int textAlign) : CRectangle(rect)
{
	m_caption=caption;
	m_foreColor=RGB(0,0,0);
	m_foreColor=color;
	m_textAlign=textAlign;
	memset(&m_font,0x00,sizeof(m_font));
	strcpy(m_font.lfFaceName,"����");
	m_font.lfHeight=16;
	m_font.lfWidth=8;
	m_font.lfUnderline=0;
	m_font.lfStrikeOut=0;
}

CLabel::~CLabel()
{

}

// ����

string CLabel::getType()                   // ��ȡ���ƶ��������
{
	return "CLabel";
}

// CTracker CLabel::getTracker()   // ��ȡѡ�п�
// {
// 	CRectangleTracker rectTracker(m_rect);
// 	return rectTracker;
// }

// ��ȡ�������ı�����
string CLabel::getCaption()
{
	return m_caption;
}

void CLabel::setCaption(string caption)
{
	m_caption=caption;
}

// ��ȡ������ǰ��ɫ
COLORREF CLabel::getForeColor()
{
	return m_foreColor;
}

void CLabel::setForeColor(COLORREF color)
{
	m_foreColor=color;
}

// ��ȡ�������ı����뷽ʽ
int CLabel::getTextAlign()
{
	return m_textAlign;
}

void CLabel::setTextAlign(int textAlign)
{
	if(textAlign>=0 && textAlign<3)
		m_textAlign=textAlign;
	else
		m_textAlign=0;
}

// ��ȡ����������
tagLOGFONTA CLabel::getFont()
{
	return m_font;
}

void CLabel::setFont(tagLOGFONTA font)
{
	m_font=font;
}


// ����

void CLabel::draw(CDC *pDC)                // ��Ļ�ϻ���
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

	CFont font;
	font.CreateFontIndirect(&m_font);
	CFont *oldFont=pDC->SelectObject(&font);

	pDC->MoveTo(m_rect.TopLeft());
	pDC->Rectangle(m_rect);
	pDC->SetBkMode(1);    // �������ֱ���͸��������ʹ�þ��εı���ɫ
	pDC->SetTextColor(m_foreColor);
//	pDC->SetTextAlign(m_textAlign);
	pDC->SetTextJustification(3,2);
	pDC->DrawText(m_caption.c_str(),m_rect,m_textAlign+DT_WORDBREAK);  // ������������ʾ���뷽ʽ��0-����1-���У�2-����

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldFont);
}

void CLabel::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_rect.OffsetRect(moveShift);
}

void CLabel::Serialize(CArchive &ar)
{
	CRectangle::Serialize(ar);
	if (ar.IsStoring())
	{
		CString s=m_caption.c_str();
		ar << s;
		ar << m_foreColor;
		ar << m_textAlign;
		ar.Write(&m_font,sizeof(m_font));

	}
	else
	{
		CString s="";
		ar >> s;
		m_caption=s.GetBuffer(s.GetLength());
		ar >> m_foreColor;
		ar >> m_textAlign;
		if(m_textAlign<0 || m_textAlign>2)
			m_textAlign=0;
		ar.Read(&m_font,sizeof(m_font));
	}
	
}

