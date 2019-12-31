// SystemEnvironment.h: interface for the CSystemEnvironment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMENVIRONMENT_H__C1538397_1B15_41F7_AEE1_67D758047F62__INCLUDED_)
#define AFX_SYSTEMENVIRONMENT_H__C1538397_1B15_41F7_AEE1_67D758047F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Windows ϵͳ��������������
class CSystemEnvironment  
{
public:
	CSystemEnvironment();
	virtual ~CSystemEnvironment();

	// ���
	// ��������ԭ��û���򴴽���ԭ�������޸�
	BOOL add(CString name, CString value);

	// ׷��
	// ��������ԭ��û���򴴽���ԭ������׷��
	BOOL append(CString name, CString value);

	// ɾ��
	// ��������ԭ��û������ԣ�ԭ��������valueΪ����ɾ������������value����ɾ�����������е�valueֵ
	BOOL del(CString name, CString value="");

	CString getErrMsg() const { return m_errMsg; }

private:
	CString m_regKey;
	CString m_errMsg;
};

#endif // !defined(AFX_SYSTEMENVIRONMENT_H__C1538397_1B15_41F7_AEE1_67D758047F62__INCLUDED_)
