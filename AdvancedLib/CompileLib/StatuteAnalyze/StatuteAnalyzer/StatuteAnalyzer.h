// MergenceAnalyzer.h: interface for the CMergenceAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERGENCEANALYZER_H__4BDDD584_9C5A_4C68_B62C_F97FE5F02BBE__INCLUDED_)
#define AFX_MERGENCEANALYZER_H__4BDDD584_9C5A_4C68_B62C_F97FE5F02BBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <c++\FoundationLib\DataStructLib\PointerList.h>
#include "StatuteTreeNode.h"
#include <C++\FoundationLib\DataStructLib\PointerStack.h>
#include "..\StatuteStatusGraph\StatuteStatusGraphNode.h"
#include "StatuteList.h"
#include "..\StatuteStatusMachine\StatuteStatusMachine.h"

using namespace std;

// ��Լ���������
// ���ݣ��ӹ�Լ�����ļ��ж�ȡ�����ģ���Լ�����ַ����������﷨����������Ĺ�Լ״̬ͼ
// �����ܹ�����Դ���token�б�͹�Լ״̬ͼ�����ɹ�Լ�������ع�Լ���ĸ��ڵ�
class CStatuteAnalyzer  
{
public:
	CStatuteAnalyzer();
	virtual ~CStatuteAnalyzer();

	// ���ɹ�Լ״̬ͼ
	// ������1-��Լʽ�ı��������Թ����壩��2-��Լ��ʶ����Ĭ���� =>����3-���з���Ĭ���� \r\n)
// 	int genStatuteStatusGraph(string text, CStatuteList &statuteList, string statuteSymbol="=>", string lineSplitter="\r\n");

// 	// ����Դ���ı�
// 	int analyzeFromSrcText(std::string text, ILexer *lexer, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList);
// 	// ����Դ���ļ�
// 	int analyzeFromSrcFile(std::string filePath, ILexer *lexer, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList);

	// ���ɹ�Լ��
	// ������
	// tokenList��Դ���token�б�
	// root�����صĹ�Լ�����ڵ�
	// ����ֵ��0-�ɹ�������-ʧ��
	int analyze(CPointerList<MachineToken *> &tokenList, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList);
	
	CStatuteStatusGraph * getStatuteStatusGraph() const { return m_machine.getStatuteStatusGraph(); }
	void setStatuteStatusGraph(CStatuteStatusGraph * val) { m_machine.setStatuteStatusGraph(val); }
	
	string getErrMsg() const { return m_errMsg; }

protected:
	int statute(CStatuteStatusGraph *graph, /*CStatuteList &origStatuteList,*/ CPointerStack<CStatuteStatusGraphNode *> &statuteStatusGraphNodeStack, CPointerStack<CStatuteTreeNode *> &statuteTreeNodeStack);

private:
	CStatuteStatusMachine m_machine;
	string m_errMsg;
};

#endif // !defined(AFX_MERGENCEANALYZER_H__4BDDD584_9C5A_4C68_B62C_F97FE5F02BBE__INCLUDED_)
