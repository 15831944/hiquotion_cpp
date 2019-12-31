// ShapeObj.h: interface for the CShapeObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPEOBJ_H__039D17D7_6AE3_46C9_B4F0_73CF6ADA4089__INCLUDED_)
#define AFX_SHAPEOBJ_H__039D17D7_6AE3_46C9_B4F0_73CF6ADA4089__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "DrawnObj.h"

// ��ʱ����
class CShapeObj : public CDrawnObj  
{
public:
	CShapeObj();
	CShapeObj(CRect rect);
	virtual ~CShapeObj();

	// ��������

	// ����ɫ
	COLORREF getBackColor() const { return m_backColor; }
	void setBackColor(COLORREF val) { m_backColor = val; }

	// ���������ʽ
	int getFillStyle() const { return m_fillStyle; }
	void setFillStyle(int val) { m_fillStyle = val; }

	// �߿���ɫ
	COLORREF getBorderColor() const { return m_borderColor; }
	void setBorderColor(COLORREF val) { m_borderColor = val; }

	// �߿���ʽ
	int getBorderStyle() const { return m_borderStyle; }
	void setBorderStyle(int val) { m_borderStyle = val; }

	// �߿���
	virtual int getBorderWidth() const { return m_borderWidth; }
	virtual void setBorderWidth(int val) { m_borderWidth = val; }

	// ����

	DECLARE_SERIAL(CShapeObj);

	virtual void Serialize(CArchive &ar);

protected:
	COLORREF m_backColor;
	int m_fillStyle;
	COLORREF m_borderColor;
	int m_borderStyle;
	int m_borderWidth;
};

#endif // !defined(AFX_SHAPEOBJ_H__039D17D7_6AE3_46C9_B4F0_73CF6ADA4089__INCLUDED_)
