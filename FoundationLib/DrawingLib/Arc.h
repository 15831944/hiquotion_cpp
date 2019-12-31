// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__07FFACD5_148F_4536_8FEF_50DE476131D1__INCLUDED_)
#define AFX_ARC_H__07FFACD5_148F_4536_8FEF_50DE476131D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ILine.h"

// ������Բ�ϵ�һ�λ�
// �û��� start �� end �����
// �����㲻һ���ڻ���
// ����������ԲԲ��������ֱ��������Բ�ཻ�Ľ�����Ϊ���������յ�
class CArc : public ILine  
{
public:
	CArc();
	CArc(int left, int top, int right, int bottom, int startx, int starty, int endx, int endy);
	CArc(int left, int top, int right, int bottom, POINT start, POINT end);
	CArc(RECT rect, int startx, int starty, int endx, int endy);
	CArc(RECT rect, POINT start, POINT end);
	virtual ~CArc();

	virtual void drawMe(CDC *pDC, CPoint point);
};

#endif // !defined(AFX_ARC_H__07FFACD5_148F_4536_8FEF_50DE476131D1__INCLUDED_)
