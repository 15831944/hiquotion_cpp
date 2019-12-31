// Label.h: interface for the CLabel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABEL_H__715C6C15_54CC_489C_A01B_D130516D7346__INCLUDED_)
#define AFX_LABEL_H__715C6C15_54CC_489C_A01B_D130516D7346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "Rectangle.h"
#include <string>

class CLabel : public CRectangle  
{
public:
	CLabel();
	CLabel(int left, int top, int right, int bottom, std::string caption, COLORREF color=RGB(0,0,0), int textAlign=0);
	CLabel(CRect rect, std::string caption, COLORREF color=RGB(0,0,0), int textAlign=0);
	virtual ~CLabel();

	// ����
	
	// ��ȡ�������ı�����
	std::string getCaption();
	void setCaption(std::string caption);

	// ��ȡ������ǰ��ɫ
	COLORREF getForeColor();
	void setForeColor(COLORREF color);

	// ��ȡ�������ı����뷽ʽ
	int getTextAlign();
	void setTextAlign(int textAlign);

	// ��ȡ����������
	tagLOGFONTA getFont();
	void setFont(tagLOGFONTA font);

	// �����Ƿ�����������ʾ
	BOOL isTextWrapped() const { return m_textWrapped; }
	void setTextWrapped(BOOL val) { m_textWrapped = val; }
	
	// ����
	virtual void drawMe(CDC *pDC, CPoint point);
	void move(CSize moveShift);            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�

protected:
	virtual void preparePenAndBrush(CDC *pDC);  // �ڻ�ͼǰ����׼���ñʺͻ�ˢ
	virtual void restorePenAndBrush(CDC *pDC);  // ��ͼ֮�󣬻ָ�ԭ���ıʺͻ�ˢ

protected:
	std::string m_caption;
	COLORREF m_foreColor;
	int m_textAlign;
	LOGFONT m_logFont;
	CFont m_font;
	CFont *m_oldFont;

	BOOL m_textWrapped;  // �����Ƿ�����������ʾ
};

#endif // !defined(AFX_LABEL_H__715C6C15_54CC_489C_A01B_D130516D7346__INCLUDED_)
