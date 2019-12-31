// Label.cpp: implementation of the CLabel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Label.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLabel::CLabel()
: m_caption(""), m_foreColor(RGB(0, 0, 0)), m_textAlign(0), m_oldFont(NULL), m_textWrapped(TRUE)
{
	memset(&m_logFont,0x00,sizeof(m_logFont));
	strcpy(m_logFont.lfFaceName,"����");
	m_logFont.lfHeight=16;
	m_logFont.lfWidth=8;
	m_logFont.lfUnderline=0;
	m_logFont.lfStrikeOut=0;

	m_borderStyle=-1;
	m_fillStyle=1;
}

CLabel::CLabel(int left, int top, int right, int bottom, std::string caption, COLORREF color, int textAlign)
: CRectangle(left, top, right, bottom), m_caption(caption), m_foreColor(color), m_textAlign(textAlign), m_oldFont(NULL), m_textWrapped(TRUE)
{
	memset(&m_logFont,0x00,sizeof(m_logFont));
	strcpy(m_logFont.lfFaceName,"����");
	m_logFont.lfHeight=16;
	m_logFont.lfWidth=8;
	m_logFont.lfUnderline=0;
	m_logFont.lfStrikeOut=0;
	
	m_borderStyle=-1;
	m_fillStyle=1;
}

CLabel::CLabel(CRect rect, std::string caption, COLORREF color, int textAlign)
: CRectangle(rect), m_caption(caption), m_foreColor(color), m_textAlign(textAlign), m_oldFont(NULL), m_textWrapped(TRUE)
{
	memset(&m_logFont,0x00,sizeof(m_logFont));
	strcpy(m_logFont.lfFaceName,"����");
	m_logFont.lfHeight=16;
	m_logFont.lfWidth=8;
	m_logFont.lfUnderline=0;
	m_logFont.lfStrikeOut=0;

	m_borderStyle=-1;
	m_fillStyle=1;
}

CLabel::~CLabel()
{

}

// ����

// ��ȡ�������ı�����
std::string CLabel::getCaption()
{
	return m_caption;
}

void CLabel::setCaption(std::string caption)
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
	return m_logFont;
}

void CLabel::setFont(tagLOGFONTA font)
{
	m_logFont=font;
}

// ����

void CLabel::preparePenAndBrush(CDC *pDC)  // �ڻ�ͼǰ����׼���ñʺͻ�ˢ
{
	IShape::preparePenAndBrush(pDC);

	m_font.CreateFontIndirect(&m_logFont);
	m_oldFont=pDC->SelectObject(&m_font);
}

void CLabel::restorePenAndBrush(CDC *pDC)  // ��ͼ֮�󣬻ָ�ԭ���ıʺͻ�ˢ
{
	IShape::restorePenAndBrush(pDC);

	if(m_oldFont)
	{
		pDC->SelectObject(m_oldFont);
		m_oldFont=NULL;
	}

	if(m_font.GetSafeHandle())
		m_font.DeleteObject();
}

void CLabel::drawMe(CDC *pDC, CPoint point)
{
	CRect rect=m_rect;
	rect.OffsetRect(point);
	
	pDC->MoveTo(rect.TopLeft());
	pDC->Rectangle(rect);
	pDC->SetTextColor(m_foreColor);
	//	pDC->SetTextAlign(m_textAlign);
	pDC->SetTextJustification(3,2);
	pDC->MoveTo(rect.TopLeft());
	pDC->SetBkMode(TRANSPARENT);    // �������ֱ���͸��������ʹ�þ��εı���ɫ
	UINT flag=m_textAlign;
	// �ж��ı��ǵ�����ʾ������������ʾ
	if(m_textWrapped)
		flag |= DT_WORDBREAK;
	else
		flag |= DT_SINGLELINE;
	pDC->DrawText(m_caption.c_str(),rect, flag);  // ������������ʾ���뷽ʽ��0-����1-���У�2-����
}

void CLabel::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_rect.OffsetRect(moveShift);
}
