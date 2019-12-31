// Bezier.h: interface for the CBezier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIER_H__8FBF14B4_B2D3_4A2A_9003_32BB4D49BD74__INCLUDED_)
#define AFX_BEZIER_H__8FBF14B4_B2D3_4A2A_9003_32BB4D49BD74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Line.h"
#include <C++\FoudationLib\DataStructLib\PointerList.h>

// �������������е�Ľṹ
// ÿ�����������Ƶ���ҿ��Ƶ�
// ��������Ƶ���յ���ҿ��Ƶ�û�����壬�ڻ�ͼʱ������
struct BesierPointStruct
{
	POINT p;  // ���ߵĶ˵�
	POINT leftControl;   // �ö˵������Ƶ�
	POINT rightControl;  // �ö˵���ҿ��Ƶ�
	BOOL symmetrical;        // �������ҿ��Ƶ��Ƿ��Ըõ�Ϊ�Գ�����

	BOOL operator ==(BesierPointStruct bps)
	{
		if(p.x==bps.p.x && p.y==bps.p.y
			&& leftControl.x==bps.leftControl.x && leftControl.y==bps.leftControl.y
			&& rightControl.x==bps.rightControl.x && rightControl.y==bps.rightControl.y
// 			&& symmetrical==bps.symmetrical
			)
			return TRUE;
		else
			return FALSE;
	}
};

// ������������
// MFC GDI ʹ�����������Լ������ҿ��Ƶ���ҵ������Ƶ�������������֮��ı���������
// ����ʹ�õĽṹʹÿ����������������Ƶ㣬��������Ŀ���Ǳ����߼��ϵ����
// ͬʱ��Ҫָ������������Ƶ���յ���ҿ��Ƶ�û�����壬�ڻ�ͼʱ������
class CBezier : public ILine
{
public:
	CBezier();
	virtual ~CBezier();

	void addPoint(POINT point, POINT leftControl, POINT rightControl, BOOL symmetrical=TRUE);
	void addPoint(POINT point, POINT leftControl, POINT rightControl, BOOL symmetrical, int indexAfter);  // ������ indexAfter ֮����� point
	
	BesierPointStruct *getBesierPointStruct(int index);
	int getBesierPointStructIndex(BesierPointStruct *point);
	
	void removePoint(BesierPointStruct *point);
	void removePoint(int index);
	
	void movePoint(BesierPointStruct *from, POINT to);
	void movePoint(int index, POINT to);

	void moveLeftControl(BesierPointStruct *from, POINT to);
	void moveLeftControl(int index, POINT to);
	
	void moveRightControl(BesierPointStruct *from, POINT to);
	void moveRightControl(int index, POINT to);

	BOOL getSymmetrical(BesierPointStruct *from);
	BOOL getSymmetrical(int index);
	
	void setSymmetrical(BesierPointStruct *from, BOOL symmetrical);
	void setSymmetrical(int index, BOOL symmetrical);
	
	virtual void drawMe(CDC *pDC, CPoint point);
	
protected:
	CPointerList<BesierPointStruct *> m_pointList;
};

#endif // !defined(AFX_BEZIER_H__8FBF14B4_B2D3_4A2A_9003_32BB4D49BD74__INCLUDED_)
