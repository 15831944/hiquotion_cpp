// ILine.h: interface for the ILine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILINE_H__CD54F328_5D71_403B_83B4_FC0F404F8DED__INCLUDED_)
#define AFX_ILINE_H__CD54F328_5D71_403B_83B4_FC0F404F8DED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IShape.h"

class ILine : public IShape  
{
public:
	ILine();
	virtual ~ILine();

	// ����
	
	CPoint getFirstPoint();
	CPoint getSrc();     // ��ȡ���
	CPoint getDst();     // ��ȡ�յ�
	
	// ��ȡ��������㡢�յ�ĺ�������
	int getX1();
	void setX1(int x1);
	int getY1();
	void setY1(int y1);
	int getX2();
	void setX2(int x2);
	int getY2();
	void setY2(int y2);
	
	// ���������������˵�
	void setPoints(CPoint src,CPoint dst);
	
	// ��������
	
	// ������ɫ
	int getLineColor() const { return m_lineColor; }
	void setLineColor(int val) { m_lineColor = val; }
	// ������ʽ
	int getLineStyle() const { return m_lineStyle; }
	void setLineStyle(int val) { m_lineStyle = val; }
	// �������
	int getLineWidth() const { return m_lineWidth; }
	void setLineWidth(int val) { m_lineWidth = val; }
	
	// �����˵㣨��㡢�յ㣩����״
	int getSrcPointCap() const { return m_srcPointCap; }
	void setSrcPointCap(int val) { m_srcPointCap = val; }
	int getDstPointCap() const { return m_dstPointCap; }
	void setDstPointCap(int val) { m_dstPointCap = val; }
	
	// ����
	virtual void draw(CDC *pDC, CPoint point=CPoint(0, 0));
	virtual void drawMe(CDC *pDC, CPoint point);
	void move(CSize moveShift);  // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�

protected:
	virtual void preparePen(CDC *pDC);  // �ڻ�ͼǰ����׼���ñ�
	virtual void restorePen(CDC *pDC);  // ��ͼ֮�󣬻ָ�ԭ���ı�

protected:
	CPoint m_start,m_end;
	
	int m_lineColor;
	int m_lineWidth;
	int m_lineStyle;
	int m_srcPointCap;
	int m_dstPointCap;

	CPen pen;
	CPen *oldPen;
};

#endif // !defined(AFX_ILINE_H__CD54F328_5D71_403B_83B4_FC0F404F8DED__INCLUDED_)
