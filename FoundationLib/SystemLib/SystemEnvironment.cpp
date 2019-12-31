// SystemEnvironment.cpp: implementation of the CSystemEnvironment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemEnvironment.h"
#include <atlbase.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemEnvironment::CSystemEnvironment()
: m_errMsg("")
{
	m_regKey="System\\CurrentControlSet\\Control\\Session Manager\\Environment";
}

CSystemEnvironment::~CSystemEnvironment()
{

}

// ���
// ��������ԭ��û���򴴽���ԭ�������޸�
BOOL CSystemEnvironment::add(CString name, CString value)
{
	m_errMsg="";

	if(name=="" || value=="")
	{
		m_errMsg="����Ϊ�գ�";
		return FALSE;
	}

	CRegKey key;
	LONG ret=key.Open(HKEY_LOCAL_MACHINE, m_regKey);
	if(ret!=ERROR_SUCCESS)
	{
		m_errMsg="��ע��� " + m_regKey + " ʧ�ܣ�";
		return FALSE;
	}

	ret=key.SetValue(value, name);
	if(ret!=ERROR_SUCCESS)
	{
		m_errMsg="���ü�ֵ " + name + " ������ " + value + " ʱʧ�ܣ�";
		return FALSE;
	}

	return TRUE;
}

// ׷��
// ��������ԭ��û���򴴽���ԭ������׷��
BOOL CSystemEnvironment::append(CString name, CString value)
{
	m_errMsg="";
	
	if(name=="" || value=="")
	{
		m_errMsg="����Ϊ�գ�";
		return FALSE;
	}
	
	m_errMsg="��δʵ�֡�";
	return FALSE;
}

// ɾ��
// ��������ԭ��û������ԣ�ԭ��������valueΪ����ɾ������������value����ɾ�����������е�valueֵ
BOOL CSystemEnvironment::del(CString name, CString value)
{
	m_errMsg="";
	
	if(name=="")
	{
		m_errMsg="����Ϊ�գ�";
		return FALSE;
	}
	
	m_errMsg="��δʵ�֡�";
	return FALSE;
}
