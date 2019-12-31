// IShape.h: interface for the IShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISHAPE_H__CA2B6CC1_58CA_453E_BECA_093CAA3DB716__INCLUDED_)
#define AFX_ISHAPE_H__CA2B6CC1_58CA_453E_BECA_093CAA3DB716__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDrawing.h"
#include "ILocation.h"
#include <C++\FoudationLib\DataStructLib\PointerMap.h>

class IShape : public IDrawing, public ILocation
{
public:
	IShape();
	IShape(int left, int top, int right, int bottom);
	IShape(CRect rect);
	virtual ~IShape();

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
	
	// ���Ӳ���
	// ������������д���Ӳ����Ľ��
	virtual BOOL attach(CRect *rect);   // ���� IFigure��A������һ��rectָ�룬��rectָ����IFigure��B��rect����ôA�ı�rect�е�ֵʱ��B����ͼ�ε�λ�û���Ӧ�ı�
	virtual BOOL attach(IDrawing *figure); // ����ʵ�����������Ĺ��ܣ������ƶ�ʱ�������ӵ�IFigure��������figure���󣩻�һ���ƶ�
	
	BOOL getFullfill() const { return m_fullfill; }
	void setFullfill(BOOL val) { m_fullfill = val; }
	
	BOOL isUseClip() const { return m_isUseClip; }
	void setUseClip(BOOL val) { m_isUseClip = val; }
	
	// ����
	virtual void draw(CDC *pDC, CPoint point=CPoint(0, 0), CRgn *parentRgn=NULL);
	virtual void drawMe(CDC *pDC, CPoint point);
	virtual void move(CSize moveShift);            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
	virtual void moveTo(CPoint point);      // �ƶ���
protected:
	virtual void preparePenAndBrush(CDC *pDC);  // �ڻ�ͼǰ����׼���ñʺͻ�ˢ
	virtual void restorePenAndBrush(CDC *pDC);  // ��ͼ֮�󣬻ָ�ԭ���ıʺͻ�ˢ

	virtual void prepareRgn(CDC *pDC, CPoint point, CRgn *parentRgn);
	virtual void restoreRgn(CDC *pDC);

	virtual void createRng(CPoint point);

protected:
// 	// �ж��ཻ
// 	virtual BOOL intersect(CRect rect);

protected:
	COLORREF m_backColor;
	int m_fillStyle;
	COLORREF m_borderColor;
	int m_borderStyle;
	int m_borderWidth;

	CPen m_pen;
	CPen *m_oldPen;

	CBrush m_brush;
	CBrush *m_oldBrush;

	BOOL m_fullfill;

	BOOL m_isUseClip;  // �Ƿ�ʹ�ü������ܣ�Ĭ��Ϊ FALSE��
	CRgn m_rgn;
	CRgn *m_parentRgn;
	CRgn m_tmpRgn;
	CRgn *m_pTmpRgn;
};

#endif // !defined(AFX_ISHAPE_H__CA2B6CC1_58CA_453E_BECA_093CAA3DB716__INCLUDED_)
