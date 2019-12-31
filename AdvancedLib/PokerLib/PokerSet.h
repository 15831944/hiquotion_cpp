// PokerSet.h: interface for the CPokerSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POKERSET_H__BBEC10B1_3AEF_40BC_BBA3_923F18A1A5B2__INCLUDED_)
#define AFX_POKERSET_H__BBEC10B1_3AEF_40BC_BBA3_923F18A1A5B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Poker.h"
#include <C++\FoudationLib\DataStructLib\ValueList.h>

// 4��һ���˿���
static CPoker poker[54];

// һ���˿��Ƶ���
class CPokerSet  
{
public:
	CPokerSet();
	virtual ~CPokerSet();

	// ��ʼ��ֽ������
	void init();
	// ����ֽ�ƴ�С
	void setPokerSize(int width, int height);
	// ����δϴ�Ƶ�˳���������Ϊ�գ�����˳������
	void setUnshuffled(int n[], int count=54);
	// ϴ��
	void shuffle(int times=1);
	// ��ȡ�� index ���ƣ�ԭʼ˳��
	CPoker *getPoker(int index);
	// ��ȡ�� index ���ƣ�ϴ�ƺ��˳��
	CPoker *getShuffledPoker(int index);

	int getPokerCount() const { return m_pokerCount; }
	void setPokerCount(int val);

private:
	CValueList<int> m_unshuffled;
	int m_shuffled[54];
	int m_pokerCount;
};

#endif // !defined(AFX_POKERSET_H__BBEC10B1_3AEF_40BC_BBA3_923F18A1A5B2__INCLUDED_)
