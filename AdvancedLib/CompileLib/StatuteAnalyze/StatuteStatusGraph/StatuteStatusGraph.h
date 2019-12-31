// MergeStatusGraph.h: interface for the CMergeStatusGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERGESTATUSGRAPH_H__37F4D06F_354A_433B_AB6B_23F96193DE5B__INCLUDED_)
#define AFX_MERGESTATUSGRAPH_H__37F4D06F_354A_433B_AB6B_23F96193DE5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\SelfContainer\Graph.h>
#include "StatuteStatusGraphNode.h"
#include "StatuteStatusGraphArc.h"
#include "..\..\LEX\LEXER\ILexer.h"

class CStatuteStatusGraph : public CGraph<CStatuteStatusGraphNode *, CStatuteStatusGraphArc *>
{
public:
	CStatuteStatusGraph();
	virtual ~CStatuteStatusGraph();

	// �ж��Ƿ����Ψһ��ǵĽڵ�
	BOOL containNodeby(string statuteKey);
	// ȡָ��Ψһ��ǵĽڵ�
	CStatuteStatusGraphNode *getNodeby(string statuteKey);

	// ����һ���ǳ�ʼ�ڵ�����Ϊ���ܽڵ�
	BOOL setAcceptNode();

	// ��ӡ״̬ͼ��Ϣ
	void printGraphInfo();

	// ��ʼ����ǰ�ڵ�
	BOOL initCurrentNode();

	// �ӵ�ǰ�ڵ���ָ�����Ƶĳ���
	int walkThroughArc(MachineToken *arcData);

	// ��ǰ�ڵ��Ƿ��ǿɽ��ܵ�
	BOOL isCurrentNodeAccepted();
	// ��ǰ�ڵ��Ƿ����սڵ�
	BOOL isCurrentNodeFinal();
	// ��ȡ�սڵ�Ψһ��Լʽ�ڹ�Լ��Ŀ�б��е�����
// 	int getIndexInStatuteItemList();
	// ��ȡ�սڵ�Ψһ��Լʽ
	Statute *getStatuteOfFinal();
	// ��ȡ�սڵ�Ψһ��Լʽ��token�ĸ���
	int getTokenCount();
	// ��ȡ�սڵ�Ψһ��Լʽ�й�Լ������
	std::string getStatuteName();

	CStatuteStatusGraphNode * getCurrentNode() const { return m_currentNode; }
	void setCurrentNode(CStatuteStatusGraphNode * val) { m_currentNode = val; }

private:
	CStatuteStatusGraphNode *m_currentNode;
};

#endif // !defined(AFX_MERGESTATUSGRAPH_H__37F4D06F_354A_433B_AB6B_23F96193DE5B__INCLUDED_)
