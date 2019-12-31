// CppConverter.h: interface for the CCppConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPPCONVERTER_H__8DE020C4_A0E3_4EA1_B95E_C151F45E64BB__INCLUDED_)
#define AFX_CPPCONVERTER_H__8DE020C4_A0E3_4EA1_B95E_C151F45E64BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IST2ASTConverter.h"

class CCppConverter : public IST2ASTConverter  
{
public:
	CCppConverter();
	virtual ~CCppConverter();

	// ��Լ���������﷨����ת��
	int convertST2AST(CStatuteTreeNode *statuteTreeRoot, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

protected:
	// ת����Լ�������к��ӽڵ㵽�����﷨���ڵ�
	int convertSTNodeList2ASTNodeList(CPointerList<CStatuteTreeNode *> &statuteTreeNodeList, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	// ת����Լ���ڵ㵽�����﷨���ڵ��б�
	// �������ͱ���б��ͣ�����Ѹ����﷨�������ɵĵݹ���ӵĹ�Լ����ɳ����﷨���ľ����б�
	int convertSTNode2ASTNodeList(CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	// ת����Լ���ڵ㵽�����﷨���ڵ�
	int convertSTNode2ASTNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	// ת�� centences �������﷨���ڵ��б�
	int convertCentences2AstNodeList(CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	int convertBlock2AstNodeList(CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	int convertCentence2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	int convertStatement2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertIf2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertWhile2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertDoWhile2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertCentenceBlock2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	int convertDeclare2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertSetValue2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertDeclareAndSetValue2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	int convertVarType2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertVarName2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	int convertExpression2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

};

#endif // !defined(AFX_CPPCONVERTER_H__8DE020C4_A0E3_4EA1_B95E_C151F45E64BB__INCLUDED_)
