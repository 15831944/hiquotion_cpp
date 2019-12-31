// Elipse.h: interface for the CElipse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELIPSE_H__C8BEC427_116B_41D5_AC70_799A532218C3__INCLUDED_)
#define AFX_ELIPSE_H__C8BEC427_116B_41D5_AC70_799A532218C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include "DrawnObj.h"
#include "Rectangle.h"

class CElipse : public CRectangle // CDrawnObj  
{
public:
	CElipse();
	CElipse(int left, int top, int right, int bottom);
	CElipse(CRect rect);
	virtual ~CElipse();

	// ����
	
	// ����
	virtual void drawMe(CDC *pDC, CPoint point);
	void move(CSize moveShift);            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�

protected:
	virtual void createRng(CPoint point);

};

#endif // !defined(AFX_ELIPSE_H__C8BEC427_116B_41D5_AC70_799A532218C3__INCLUDED_)
