// StringSimpleParser.h: interface for the CStringSimpleParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGSIMPLEPARSER_H__6BB8BAC8_FA59_4079_9D78_F37BC0EBD325__INCLUDED_)
#define AFX_STRINGSIMPLEPARSER_H__6BB8BAC8_FA59_4079_9D78_F37BC0EBD325__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "StringAnalyzer.h"

// �ַ����򵥽�����
// ��������ָ���ַ����Ƿ����ָ���ַ�����CStringAnalyzer �ࣩ�б������
class CStringSimpleParser  
{
public:
	CStringSimpleParser();
	virtual ~CStringSimpleParser();

	void add(CStringAnalyzer *analyzer);

	// ���� src �ַ���
	int parse(CString src);

private:
	std::vector<CStringAnalyzer *> m_list;

};

#endif // !defined(AFX_STRINGSIMPLEPARSER_H__6BB8BAC8_FA59_4079_9D78_F37BC0EBD325__INCLUDED_)
