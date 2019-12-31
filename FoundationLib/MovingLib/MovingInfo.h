// MovingInfo.h: interface for the CMovingInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVINGINFO_H__41AECCF5_BC40_49F6_9B43_FD04DC90C0CA__INCLUDED_)
#define AFX_MOVINGINFO_H__41AECCF5_BC40_49F6_9B43_FD04DC90C0CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ����˶��������յ㣬����С�ƶ������Լ�������ƶ�ʱ�䣨���룩��Լ���£������˶�����
class CMovingInfo  
{
public:
	CMovingInfo();
	virtual ~CMovingInfo();

	// ����˶��������յ㣬����С�ƶ������Լ�������ƶ�ʱ�䣨���룩��Լ���£������˶�����
	// ������涨��С�ƶ�������������ƶ�ʱ�䣬����Ӧֵ����Ϊ0
	// �����С�ƶ�������������ƶ�ʱ�䶼Ϊ0���򷵻� to - from
	static float getMovingStep(float from, float to, float frameRate, float minStep=10, int maxTotalInterval=500);

	static float getMovingStep(float from, float to, float frameRate, int maxTotalInterval=500);


	static CSize getMovingStep2D(CPoint from, CPoint to, float frameRate, CPoint minStep=CPoint(10, 10), int maxTotalInterval=500);
};

#endif // !defined(AFX_MOVINGINFO_H__41AECCF5_BC40_49F6_9B43_FD04DC90C0CA__INCLUDED_)
