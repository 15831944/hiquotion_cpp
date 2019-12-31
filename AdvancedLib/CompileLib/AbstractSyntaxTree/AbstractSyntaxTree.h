// AbstractSyntaxTree.h: interface for the CAbstractSyntaxTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTSYNTAXTREE_H__130AEDD6_4310_49D3_9AC5_6CB3EB79729B__INCLUDED_)
#define AFX_ABSTRACTSYNTAXTREE_H__130AEDD6_4310_49D3_9AC5_6CB3EB79729B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\AdvancedLib\CompileLib\StatuteAnalyze\StatuteAnalyzer\StatuteTreeNode.h>
#include "AbstractSyntaxTreeNode.h"
#include <C++\FoundationLib\DataStructLib\PointerList.h>

// �����﷨����
// ���𽫹�Լ��ת���ɳ����﷨��
class CAbstractSyntaxTree  
{
public:
	CAbstractSyntaxTree();
	virtual ~CAbstractSyntaxTree();

	// ��Լ���������﷨����ת��
	static int convertST2AST(CStatuteTreeNode *statuteTreeRoot, CAbstractSyntaxTreeNode *abstractSyntaxTreeRoot);

protected:
	// ת����Լ�������к��ӽڵ㵽�����﷨���ڵ�
	static int convertSTNodeList2ASTNode(CPointerList<CStatuteTreeNode *> &statuteTreeNodeList, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode);
	// ת����Լ���ڵ㵽�����﷨���ڵ��б�
	// �������ͱ���б��ͣ�����Ѹ����﷨�������ɵĵݹ���ӵĹ�Լ����ɳ����﷨���ľ����б�
	static int convertSTNode2ASTNodeList(CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	// ת����Լ���ڵ㵽�����﷨���ڵ�
	static int convertSTNode2ASTNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode);
	// ����ָ�������ƣ�����ת����Լ���ڵ㵽�����﷨���ڵ�
	static int convertSTNode2ASTNode(std::string statuteTreeNodeName, CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode);
};

#endif // !defined(AFX_ABSTRACTSYNTAXTREE_H__130AEDD6_4310_49D3_9AC5_6CB3EB79729B__INCLUDED_)
