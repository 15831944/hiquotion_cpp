// StringAnalyzer.h: interface for the CStringAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGANALYZER_H__D9003D83_AAC9_4625_BA57_236C329E3A30__INCLUDED_)
#define AFX_STRINGANALYZER_H__D9003D83_AAC9_4625_BA57_236C329E3A30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

// �ַ���������
// �����������ַ��б������Ƿ��ѡ�ı�־��������鷽��
class CStringAnalyzer  
{
public:
	CStringAnalyzer();
	CStringAnalyzer(BOOL optional);
	CStringAnalyzer(CString s, BOOL optional);
	virtual ~CStringAnalyzer();

	// ��Ӵ�����ַ���
	void add(CString s)
	{
		m_list.push_back(s);
	}

	// ���Դ�ַ��� src���Ƿ���� m_list ��ָ�����ַ���
	// ����ֵ��
	// 1���ɹ�
	// 0��ʧ��
	// -1���д���
	int check(CString src, CString &dst);

	BOOL getOptional() const { return m_optional; }

private:
	std::vector<CString> m_list;
	BOOL m_optional;
};

#endif // !defined(AFX_STRINGANALYZER_H__D9003D83_AAC9_4625_BA57_236C329E3A30__INCLUDED_)
