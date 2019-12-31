// Tracker.h: interface for the CTracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACKER_H__05C7D39B_A0B8_460E_ACAD_6BAB36931DC9__INCLUDED_)
#define AFX_TRACKER_H__05C7D39B_A0B8_460E_ACAD_6BAB36931DC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "Handle.h"
#include <vector>
using namespace std;

// Selected Handle Position
#define HP_NONE_SELECTED -1
#define HP_LEFT_TOP      0
#define HP_TOP           1
#define HP_RIGHT_TOP     2
#define HP_LEFT          3
#define HP_RIGHT         4
#define HP_LEFT_BOTTOM   5
#define HP_BOTTOM        6
#define HP_RIGHT_BOTTOM  7

//////////////////////////////////////////////////////////////////////////
// ����ѡ�к���ֵ�ѡ���

class CTracker  
{
public:
	CTracker();
	CTracker(CRect rect);
	virtual ~CTracker();

	// ����
// 	virtual int getHandleCount();     // ��ȡ�������
// 	virtual list<CHandle> getTrackerItems();

	// ����
	virtual void drawTracker(CDC *DC);
	virtual int isHitTracker(CPoint hitPoint);  // �����������Ƿ�����˻��ƶ����Tracker��
	virtual CRect moveTrackerHandle(int nHandle, CPoint point);  // �ƶ�Tracker�ĵ�nHandle�ž����point����

protected:
	CRect m_rect;
	vector<CHandle> m_handles;
};

#endif // !defined(AFX_TRACKER_H__05C7D39B_A0B8_460E_ACAD_6BAB36931DC9__INCLUDED_)
