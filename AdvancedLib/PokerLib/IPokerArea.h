// IPokerArea.h: interface for the IPokerArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPOKERAREA_H__3FD1517B_61DD_4A93_8113_D017449E5004__INCLUDED_)
#define AFX_IPOKERAREA_H__3FD1517B_61DD_4A93_8113_D017449E5004__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Poker.h"
#include "PokerColumnArea.h"
#include "..\..\FoudationLib\DataStructLib\PointerList.h"

class IPokerArea : public IUIHandler
{
public:
	IPokerArea();
	IPokerArea(int count, CPoint relativePosition);
	virtual ~IPokerArea();

	// ��ʼ��ʱ�����
	void add(int columnIndex, CPoker *poker);
	
	// �����˿����ж���
	void setPokerColumnArea(int count, CPoint relativePosition);

	// �ж��Ƿ�������Ƶķ���
	virtual BOOL canDrop(CPoker *poker, CPoint relativeTopLeft=CPoint(0, 0)) { return FALSE; };

	// ��ȡ��һ�����Ƶ�λ��
	CPoint getNextDrop();

	// ���Ʒ���
	virtual void drop(CPoker *poker);

	// ��ȡ��ʰȡֽ�Ƶ�λ������
	virtual int getPickupIndex(CPoker *poker);

	// ʰ�Ʒ���
	virtual void pickup(CPoker *poker);

protected:
	CPointerList<CPokerColumnArea *> m_pokerColumnArea;
	int m_count;
	
	int m_pokerDropIndex;
	int m_pokerPickupIndex;
};

#endif // !defined(AFX_IPOKERAREA_H__3FD1517B_61DD_4A93_8113_D017449E5004__INCLUDED_)
