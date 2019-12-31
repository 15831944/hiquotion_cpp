// KernelLexer.h: interface for the CKernelLexer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KERNELLEXER_H__AD7D3BF3_5236_4E9F_8908_360838C08991__INCLUDED_)
#define AFX_KERNELLEXER_H__AD7D3BF3_5236_4E9F_8908_360838C08991__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Lex\Lexer\ILexer.h"
#include <string>
#include "KernelLexStatusGraphBuilder.h"
#include "..\..\Lex\Lexer\Lexer.h"
#include "..\..\Lex\LexStatusMachine\LexStatusMachine.h"

using namespace std;

class CKernelLexer : public ILexer
{
public:
	CKernelLexer();
	virtual ~CKernelLexer();

	// ����ֵ��
	// -1������Ϊ��
	// -2��״̬���ڲ����󣨵�ǰ���Ϊ�գ�
	int analyze (string text, CPointerList<MachineToken *> &tokenList, CValueList<string> &errList);

private:
	// ��token�б���Ԥ����
	// 1. ��˫�����е����ݣ����һ��token
	// 2. ���� \" �Ĵ��������һ�������ڣ��������ַ������������һ�������⣬������token����
	// 3. ȥ���س����ո���ע�͡���ע�͵ȵȵ�token��
	// 4. ��ȡ��������������%֮����Ǳ���������ȡ˫����֮����ַ���֮������
	// ������
	// tokenList����Լʽ��token�б�
	int preProcessTokens (CPointerList<MachineToken *> &tokenList);

	// ������ʼ����ֹ����������ȡ�÷�Χ��tokensΪ�ַ���token
	int preProcessExtractStringToken (CPointerList<MachineToken *> &tokenList, int startIndex, int endIndex);

private:
	CKernelLexStatusGraphBuilder m_builder;
	CLexer m_lexer;
	CLexStatusMachine m_machine;

	string m_errMsg;
};

#endif // !defined(AFX_KERNELLEXER_H__AD7D3BF3_5236_4E9F_8908_360838C08991__INCLUDED_)
