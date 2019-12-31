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

class CLabel : public CRectangle  
{
public:
	CLabel();
	CLabel(CRect rect, string caption, COLORREF color=RGB(0,0,0), int textAlign=0);
	virtual ~CLabel();

	// ����
	
	string getType();                     // ��ȡ���ƶ��������

	// ��ȡ�������ı�����
	string getCaption();
	void setCaption(string caption);

	// ��ȡ������ǰ��ɫ
	COLORREF getForeColor();
	void setForeColor(COLORREF color);

	// ��ȡ�������ı����뷽ʽ
	int getTextAlign();
	void setTextAlign(int textAlign);

	// ��ȡ����������
	tagLOGFONTA getFont();
	void setFont(tagLOGFONTA font);

	
	// ����
	virtual void Serialize(CArchive &ar);
	
	void draw(CDC *pDC);                // ��Ļ�ϻ���
	void move(CSize moveShift);            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�


protected:
	DECLARE_SERIAL(CLabel);


	string m_caption;
	COLORREF m_foreColor;
	int m_textAlign;
	LOGFONT m_font;
};

#endif // !defined(AFX_LABEL_H__715C6C15_54CC_489C_A01B_D130516D7346__INCLUDED_)
