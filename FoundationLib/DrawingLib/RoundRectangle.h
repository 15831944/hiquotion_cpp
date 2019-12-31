// RoundRectangle.h: interface for the CRoundRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_)
#define AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "Rectangle.h"

class CRoundRectangle : public CRectangle
{
public:
	CRoundRectangle();
	CRoundRectangle(int left, int top, int right, int bottom, POINT roundCenter=CPoint(15,15));
	CRoundRectangle(CRect rect, POINT roundCenter=CPoint(5,5));
	virtual ~CRoundRectangle();

	// ����
	
	int getRoundPointX();          // ��ȡԲ�ǵ��ˮƽ����
	void setRoundPointX(int x);    // ����Բ�ǵ��ˮƽ����

	int getRoundPointY();          // ��ȡԲ�ǵ�Ĵ�ֱ����
	void setRoundPointY(int y);    // ����Բ�ǵ�Ĵ�ֱ����

	// ����
	virtual void drawMe(CDC *pDC, CPoint point);
	void move(CSize moveShift);            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�

protected:
	virtual void createRng(CPoint point);

private:
	POINT m_roundCenter;
};

#endif // !defined(AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_)
