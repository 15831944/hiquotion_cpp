// DiGraphic.h: interface for the CDiGraphic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIGRAPHIC_H__1478DA1A_75C2_4925_B1BB_685BAF7D9EAC__INCLUDED_)
#define AFX_DIGRAPHIC_H__1478DA1A_75C2_4925_B1BB_685BAF7D9EAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Node.h"
#include "Arc.h"

class CNode;
class CArc;

class CDiGraphic  
{
public:
	CDiGraphic();
	virtual ~CDiGraphic();

	CNode *addNode(CNode *node);
	
	BOOL addNodes(CPointerList<CNode *> *nodes);
	
	CArc *addArc(CArc *arc);
	
	BOOL addArcs(CPointerList<CArc *> *arcs);
	
	// ���� arc ������ʼ���ͽ������
	// 1���� arc ��ӿ�ʼ������ֹ���
	// 2������ arc ��ӵ���ʼ���ĳ����б��Լ���ӵ����������뻡�б�
	void add(CArc *arc, CNode *nodeStart, CNode *nodeEnd);

	BOOL getNodesDestroy() const { return m_isNodesDestroy; }
	void setNodesDestroy(BOOL val) { m_isNodesDestroy = val; }
	
	BOOL getArcsDestroy() const { return m_isArcsDestroy; }
	void setArcsDestroy(BOOL val) { m_isArcsDestroy = val; }
	
protected:
	CPointerList<CNode *> m_nodes;
	CPointerList<CArc *> m_arcs;
	
	// ���˳�ʱ���Ƿ�delete�ڵ��б�Ԫ�أ�Ĭ��Ϊ��
	BOOL m_isNodesDestroy;  
	// ���˳�ʱ���Ƿ�delete���б�Ԫ�أ�Ĭ��Ϊ��
	BOOL m_isArcsDestroy;
};

#endif // !defined(AFX_DIGRAPHIC_H__1478DA1A_75C2_4925_B1BB_685BAF7D9EAC__INCLUDED_)
