// StatuteTreeNode.h: interface for the CStatuteTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUTETREENODE_H__CBA7BC2A_7556_4633_B045_518917CD57AB__INCLUDED_)
#define AFX_STATUTETREENODE_H__CBA7BC2A_7556_4633_B045_518917CD57AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\SelfContainer\SelfTreeNode.h>
#include "../StatuteStatusGraph/StatuteStatusGraphNode.h"
#include "..\..\Lex\Lexer\Lexer.h"
#include <C++\FoundationLib\DataStructLib\PointerStack.h>

class CStatuteTreeNode : public CSelfTreeNode<CStatuteTreeNode *>
{
public:
	CStatuteTreeNode();
	CStatuteTreeNode(MachineToken *machineToken);
	// ��ָ��ջ�еĽڵ���ӵ�����ĺ��ӽ����
	// ע��ջ�нڵ�˳����Ҫ�����������ε����Ľڵ�ֱ����ӵ������ӽ���б��е�
	CStatuteTreeNode(CPointerStack<CStatuteTreeNode *> *reversedMachineTokenStack);
	// ��ָ��ջ�е�ָ���������ڵ���ӵ������ӽ����
	// ע��ջ�нڵ�˳���Ƿ��ģ������ε����Ľڵ���Ҫ���뵽�������б��е��׶�
	CStatuteTreeNode(CPointerStack<CStatuteTreeNode *> *machineTokenStack, int popoutCount);
	virtual ~CStatuteTreeNode();

	// ��ȡ���ӽ���е�token������б�
	void genTokenPosition();

	// ��ȡ���ڵ���Ϣ�������ӽڵ㣩�����ڲ���
	std::string getTreeNodeInfo();
	// ��ȡָ����������ڵ���Ϣ��level��ʾ��ǰ�ڵ��������ĵڼ��㣬���ڲ���
	std::string getTreeNodeInfoByLevel(CStatuteTreeNode *node, unsigned int level, int space=4);

	// ��ӡ���ڵ���Ϣ�������ӽڵ㣩�����ڲ���
	void printTreeNodeInfo();
	// ��ӡָ����������ڵ���Ϣ��level��ʾ��ǰ�ڵ��������ĵڼ��㣬���ڲ���
	void printTreeNodeInfoByLevel(CStatuteTreeNode *node, unsigned int level);

	MachineToken * getMachineToken() const { return m_machineToken; }
	void setMachineToken(MachineToken * val) { m_machineToken = val; }

private:
	MachineToken *m_machineToken;
};

#endif // !defined(AFX_STATUTETREENODE_H__CBA7BC2A_7556_4633_B045_518917CD57AB__INCLUDED_)
