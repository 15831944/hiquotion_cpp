// PokerColumnArea.h: interface for the CPokerColumnArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POKERCOLUMNAREA_H__FB046CFD_8AE9_4FC4_8849_DFCDE2ABF766__INCLUDED_)
#define AFX_POKERCOLUMNAREA_H__FB046CFD_8AE9_4FC4_8849_DFCDE2ABF766__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FOUDATIONLIB\UIHANDLERLIB\IUIHandler.h>
#include "Poker.h"

class CPokerColumnArea : public IUIHandler
{
public:
	CPokerColumnArea();
	virtual ~CPokerColumnArea();

	// �ж��Ƿ�������Ƶķ���
	virtual BOOL canDrop(CPoker *poker, CPoint relativeTopLeft=CPoint(0, 0));

	// ��ȡ��һ�����Ƶ�λ��
	CPoint getNextDrop();
	
	// ���Ʒ���
	virtual void drop(CPoker *poker);

	// ʰ�Ʒ���
	virtual void pickup(CPoker *poker);

	// �Ƿ����ָ��ֽ��
	BOOL contain(CPoker *poker);

	// ��ȡ������������һ����
	CPoker *getBottomPoker();

	CPoint getRelativePositioin() const { return CPoint(m_relativeX, m_relativeY); }
	void setRelativePositioin(int x, int y) { m_relativeX = x; m_relativeY = y; }
	void setRelativePositioin(CPoint relativePosition) { m_relativeX = relativePosition.x; m_relativeY = relativePosition.y; }

protected:
	// ��ȡ�����Ƶ�����һ����
	CPoker *getParentofPokerChild(CPoker *pokerChild);

	// �¼�����
	virtual void OnSize(int cx, int cy) {};

private:
	int m_relativeX;
	int m_relativeY;

	CPoker *m_bottomPoker;

	// ���ֽ������Ӧ����һ��ͨ�õ������κ��˿�����Ϸ���У���ô������������Ӧ�����ⲿ��ָ���ȽϺ�
	// Ҳ����˵���ڲ�Ӧ����һ�� IPokerArea ����ָ����������ⲿ����ö�����Ϊ�жϵĲ���
	// Ŀǰ�ó����Ȳ������ģ���Ϊ�Ժ���²���������Ϸ�ˡ���
};

#endif // !defined(AFX_POKERCOLUMNAREA_H__FB046CFD_8AE9_4FC4_8849_DFCDE2ABF766__INCLUDED_)
