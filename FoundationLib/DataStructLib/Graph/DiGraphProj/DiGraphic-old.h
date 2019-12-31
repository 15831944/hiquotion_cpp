
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\DataStructLib\PointerList.h>
#include "Node.h"
#include "Arc.h"

// ͼ��Node�ǽڵ㣬Arc�ǻ�
// template <class Node, class NodeKey, class Arc, class ArcKey>
template <class NodeData, class ArcWeight>
class CDiGraphic
{
public:
	CDiGraphic()
	{
		m_isNodesDestroy=TRUE;
		m_isArcsDestroy=TRUE;
	};

	virtual ~CDiGraphic()
	{
		if(m_isNodesDestroy)
			m_nodes.destroyAll();
		if(m_isArcsDestroy)
			m_arcs.destroyAll();
	}

	CPointerList<CNode<NodeData, ArcWeight> *> *getNodes() { return &m_nodes; }
// 	void setNodes(CPointerMap<NodeKey, Node> val) { m_nodes = val; }

	CPointerList<CArc<NodeData, ArcWeight> *> *getArcs() { return &m_arcs; }
// 	void setArcs(CPointerMap<ArcKey, Arc> val) { m_arcs = val; }

	CNode<NodeData, ArcWeight> *addNode(CNode<NodeData, ArcWeight> *node)
	{
		m_nodes.push_back(node);
		return node;
	}

	BOOL addNodes(CPointerList<CNode<NodeData, ArcWeight> *> *nodes)
	{
		for(int i=0;i<nodes->size();i++)
			m_nodes.push_back(nodes->at(i));
		return TRUE;
	}

	CArc<NodeData, ArcWeight> *addArc(CArc<NodeData, ArcWeight> *arc)
	{
		m_arcs.push_back(arc);
		return arc;
	}
	
	BOOL addArcs(CPointerList<CArc<NodeData, ArcWeight> *> *arcs)
	{
		if(!arcs)
			return FALSE;

		for(int i=0;i<arcs->size();i++)
			m_arcs.push_back(arcs->at(i));
		return TRUE;
	}

	BOOL getNodesDestroy() const { return m_isNodesDestroy; }
	void setNodesDestroy(BOOL val) { m_isNodesDestroy = val; }

	BOOL getArcsDestroy() const { return m_isArcsDestroy; }
	void setArcsDestroy(BOOL val) { m_isArcsDestroy = val; }

	// ���� arc ������ʼ���ͽ������
	// 1���� arc ��ӿ�ʼ������ֹ���
	// 2������ arc ��ӵ���ʼ���ĳ����б��Լ���ӵ����������뻡�б�
	void add(CArc<NodeData, ArcWeight> *arc, CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
	{
		if(!arc)
			return;
		
		if(!nodeStart)
			return;

		if(!nodeEnd)
			return;

		arc->setNodeStart(nodeStart);
		arc->setNodeEnd(nodeEnd);

		nodeStart->addArcOut(arc);
		nodeEnd->addArcIn(arc);
	}

protected:
	CPointerList<CNode<NodeData, ArcWeight> *> m_nodes;
	CPointerList<CArc<NodeData, ArcWeight> *> m_arcs;

	// ���˳�ʱ���Ƿ�delete�ڵ��б�Ԫ�أ�Ĭ��Ϊ��
	BOOL m_isNodesDestroy;  
	// ���˳�ʱ���Ƿ�delete���б�Ԫ�أ�Ĭ��Ϊ��
	BOOL m_isArcsDestroy;
};