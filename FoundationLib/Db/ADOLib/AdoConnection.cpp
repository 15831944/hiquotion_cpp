// AdoConnection.cpp: implementation of the CAdoConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdoConnection.h"
#include <sstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoConnection::CAdoConnection()
: m_isConnected(FALSE)
{
	HRESULT hr = pMyConnect.CreateInstance(__uuidof(Connection));
	if( FAILED(hr) )
	{
		std::stringstream ss;
		ss << "�������ݿ����Ӷ���ʧ�ܣ�Windows �������� " << GetLastError();
		m_errMessage=ss.str();
		m_isCreated=FALSE;
		return;
	}
	m_isCreated=TRUE;
}

CAdoConnection::~CAdoConnection()
{
	if(m_isConnected)
		pMyConnect->Close();
}

BOOL CAdoConnection::isCreated()
{
	return m_isCreated;
}

BOOL CAdoConnection::connect(CString connStr)
{
	if(!m_isCreated)
	{
		m_errMessage="���ȴ������Ӷ���";
		m_isConnected=FALSE;
		return FALSE;
	}

	try
	{
		pMyConnect->Open(connStr.AllocSysString(),"","",NULL);
	}
	catch (_com_error &e)
	{
		m_errMessage="�������ݿ�ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		m_isConnected=FALSE;
		return FALSE;
	}

	m_isConnected=TRUE;
	return TRUE;
}

BOOL CAdoConnection::isConnected()
{
	if(!m_isCreated)
	{
		m_errMessage="���ȴ������Ӷ���";
		return FALSE;
	}

	return m_isConnected;
}

BOOL CAdoConnection::beginTrans()
{
	if(!m_isConnected)
	{
		m_errMessage="���ݿ�δ���ӡ�";
		return FALSE;
	}

	try
	{
		pMyConnect->BeginTrans();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="��ʼ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoConnection::commitTrans()
{
	if(!m_isConnected)
	{
		m_errMessage="���ݿ�δ���ӡ�";
		return FALSE;
	}
	
	try
	{
		pMyConnect->CommitTrans();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="�ύ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoConnection::rollbackTrans()
{
	if(!m_isConnected)
	{
		m_errMessage="���ݿ�δ���ӡ�";
		return FALSE;
	}
	
	try
	{
		pMyConnect->RollbackTrans();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="�ع�����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

_RecordsetPtr CAdoConnection::execute(CString sql, long *affected)
{
	if(!m_isConnected)
	{
		m_errMessage="���ݿ�δ���ӡ�";
		return NULL;
	}
	
	try
	{
		VARIANT recordAffected;
		_RecordsetPtr rec=pMyConnect->Execute(sql.AllocSysString(), &recordAffected, adCmdText);
		*affected=recordAffected.lVal;
		return rec;
	}
	catch (_com_error &e)
	{
		m_errMessage="ִ�� " + sql + " ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return NULL;
	}
}
