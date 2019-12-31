// StatusGraph.h: interface for the CStatusGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSGRAPH_H__EDBAEACB_C869_49A7_8743_C6BC21AEEFE8__INCLUDED_)
#define AFX_STATUSGRAPH_H__EDBAEACB_C869_49A7_8743_C6BC21AEEFE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <c++\FoundationLib\DataStructLib\SelfContainer\Graph.h>
#include "StatusGraphNode.h"
#include "StatusGraphArc.h"

// �ʷ�����״̬ͼ��
// ������̬�Ľ��ͱ�
// �ǽ��ͱߵĴ洢�࣬ͬʱ�������ٴ���
// ���಻������״̬ͼ�Ĳ���������״̬ͼ����״̬����
class CLexStatusGraph : public CGraph<CStatusGraphNode *, CStatusGraphArc *>
{
public:
	CLexStatusGraph();
	virtual ~CLexStatusGraph();

	// �������� from ����Լ� to ���
	void genRelationship(CStatusGraphArc *arc, CStatusGraphNode *from=NULL, CStatusGraphNode *to=NULL);
	
	// �ӵ�ǰ����ӽ��� ch �ַ��ı��ƶ�����������һ�ڵ�
// 	CNode *move(CNode *currentNode, char ch);
};

#endif // !defined(AFX_STATUSGRAPH_H__EDBAEACB_C869_49A7_8743_C6BC21AEEFE8__INCLUDED_)
