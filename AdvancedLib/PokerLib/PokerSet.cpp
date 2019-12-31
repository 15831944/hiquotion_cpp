// PokerSet.cpp: implementation of the CPokerSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PokerSet.h"
#include <C++\FoudationLib\RandLib\Rand.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPokerSet::CPokerSet()
: m_pokerCount(52)
{
	init();
}

CPokerSet::~CPokerSet()
{

}

// ��ʼ��ֽ������
void CPokerSet::init()
{
	int i=0;
	for(i=0;i<4;i++)
	{
		for(int j=0;j<13;j++)
		{
			poker[13*i+j].setPoker((PokerType)i, (PokerValue)j);
		}
	}

	for(i=0;i<54;i++)
	{
		m_unshuffled.push_back(i);
	}
}

// ����ֽ�ƴ�С
void CPokerSet::setPokerSize(int width, int height)
{
	for(int i=0;i<54;i++)
	{
		CRect rect=poker[i].getRect();
		rect.right=rect.left+width;
		rect.bottom=rect.top+height;
		poker[i].setRect(rect);
	}
}

// ����δϴ�Ƶ�˳���������Ϊ�գ�����˳������
void CPokerSet::setUnshuffled(int n[], int count)
{
	m_unshuffled.clear();

	int i=0;
	if(!n || count<=0)
	{
		for(i=0;i<54;i++)
		{
			m_unshuffled.push_back(i);
		}
		return;
	}

	for(i=0;i<count;i++)
	{
		m_unshuffled.push_back(n[i]);
	}
}

// ϴ��
void CPokerSet::shuffle(int times)
{
	if(times<1)
		times=1;

	memset(m_shuffled, 0, 54*sizeof(int));
	CRand rander;
	rander.init();
	for(int i=0;i<times;i++)
	{
		for(int j=0;j<m_pokerCount-1;j++)
		{
// 			rander.init();
			int rnd=rander.randNumberN(m_pokerCount-j);
			m_shuffled[j]=m_unshuffled.at(rnd);
			m_unshuffled.remove(m_unshuffled.at(rnd));
		}

		m_shuffled[m_pokerCount-1]=m_unshuffled.at(0);
		m_unshuffled.clear();

		if(times>1)
			setUnshuffled(m_shuffled, m_pokerCount);
	}
}

// ��ȡ�� index ���ƣ�ԭʼ˳��
CPoker *CPokerSet::getPoker(int index)
{
	if(index<0 || index >= m_pokerCount)
		return NULL;

	return &poker[index];
}
// ��ȡ�� index ���ƣ�ϴ�ƺ��˳��
CPoker *CPokerSet::getShuffledPoker(int index)
{
	if(index<0 || index >= m_pokerCount)
		return NULL;

	return &poker[m_shuffled[index]];
}

void CPokerSet::setPokerCount(int val)
{
	if(val>54)
		return;

	m_pokerCount = val;
}
