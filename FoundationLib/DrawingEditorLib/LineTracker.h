// LineTracker.h: interface for the CLineTracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINETRACKER_H__1EF5B0D2_84EB_4C76_AE82_058570981ADB__INCLUDED_)
#define AFX_LINETRACKER_H__1EF5B0D2_84EB_4C76_AE82_058570981ADB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Tracker.h"

class CLineTracker : public CTracker  
{
public:
	CLineTracker(CRect rect);
	CLineTracker(POINT src, POINT dst);
	virtual ~CLineTracker();

// 	int isHitTracker(CPoint hitPoint);  // �����������Ƿ�����˻��ƶ����Tracker��
// 	CRect moveTrackerHandle(int nHandle, CPoint point);  // �ƶ�Tracker�ĵ�nHandle�ž����point����

private:
	POINT m_src,m_dst;   // �ߵ������յ�
};

#endif // !defined(AFX_LINETRACKER_H__1EF5B0D2_84EB_4C76_AE82_058570981ADB__INCLUDED_)
