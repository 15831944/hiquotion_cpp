// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__C6A64DC4_B1B0_4834_9FFC_5BB92500170C__INCLUDED_)
#define AFX_ARC_H__C6A64DC4_B1B0_4834_9FFC_5BB92500170C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Node.h"

// ͼ�ڵ�֮��Ļ���Ҳ�����ߣ�Weight�ǻ���Ȩ�أ�Node�ǽڵ㣬Arc�ǻ�
template <class NodeData, class ArcWeight>
class CNode;

template <class NodeData, class ArcWeight>
class CArc  
{
public:
	CArc()
	{
		m_weight=NULL;
		m_isWeightDestroy=FALSE;
		m_nodeStart=NULL;
		m_nodeToEnd=NULL;
	};

	CArc(CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
	{
		m_weight=NULL;
		m_isWeightDestroy=FALSE;
		m_nodeStart=nodeStart;
		m_nodeToEnd=nodeEnd;
	};

	CArc(ArcWeight data, CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
	{
		m_weight=data;
		m_isWeightDestroy=FALSE;
		m_nodeStart=nodeStart;
		m_nodeToEnd=nodeEnd;
	};

	CArc(ArcWeight data, BOOL isWeightDestroy, CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
	{
		m_weight=data;
		m_isWeightDestroy=isWeightDestroy;
		m_nodeStart=nodeStart;
		m_nodeToEnd=nodeEnd;
	};
	
	virtual ~CArc()
	{
		if(m_isWeightDestroy)
			delete m_weight;
	};

	ArcWeight getWeight() const { return m_weight; }
	void setWeight(ArcWeight val) { m_weight = val; }
	
	CNode<NodeData, ArcWeight> *getNodeStart() const { return m_nodeStart; }
	void setNodeStart(CNode<NodeData, ArcWeight> *val) { m_nodeStart = val; }
	
	CNode<NodeData, ArcWeight> *getNodeEnd() const { return m_nodeToEnd; }
	void setNodeEnd(CNode<NodeData, ArcWeight> *val) { m_nodeToEnd = val; }
	
	BOOL isNoWeight()
	{
		if(!m_weight)
			return TRUE;

		return FALSE;
	}
	
	BOOL isWeightDestroy() const { return m_isWeightDestroy; }
	void isWeightDestroy(BOOL val) { m_isWeightDestroy = val; }

protected:
	ArcWeight m_weight;     // ����Ȩ��
	BOOL m_isWeightDestroy; // Ȩ���Ƿ���Ҫdelete��Ĭ���ǲ���Ҫ
	CNode<NodeData, ArcWeight> *m_nodeStart;     // ��ʼ�ڵ�
	CNode<NodeData, ArcWeight> *m_nodeToEnd;     // ��ֹ�ڵ�
};

#endif // !defined(AFX_ARC_H__C6A64DC4_B1B0_4834_9FFC_5BB92500170C__INCLUDED_)
