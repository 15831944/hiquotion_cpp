// IST2ASTConverter.h: interface for the IST2ASTConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IST2ASTCONVERTER_H__E34C1138_F9CB_4CB9_8242_9BB80BCAA5B2__INCLUDED_)
#define AFX_IST2ASTCONVERTER_H__E34C1138_F9CB_4CB9_8242_9BB80BCAA5B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\AdvancedLib\CompileLib\StatuteAnalyze\StatuteAnalyzer\StatuteTreeNode.h>
#include "AbstractSyntaxTreeNode.h"

// ��Լ���������﷨����ת�����ӿ�
class IST2ASTConverter  
{
public:
	IST2ASTConverter();
	virtual ~IST2ASTConverter();

	// ��Լ���������﷨����ת��
	virtual int convertST2AST(CStatuteTreeNode *statuteTreeRoot, CAbstractSyntaxTreeNode *abstractSyntaxTreeRoot){return 0;};

// protected:
// 	// ת����Լ���ڵ㵽�����﷨���ڵ�
// 	virtual int convertSTNode2ASTNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode){return 0;};

};

#endif // !defined(AFX_IST2ASTCONVERTER_H__E34C1138_F9CB_4CB9_8242_9BB80BCAA5B2__INCLUDED_)
