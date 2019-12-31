// AdoRecordset.cpp: implementation of the CAdoRecordset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdoRecordset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoRecordset::CAdoRecordset(CAdoConnection *conn)
: m_conn(conn), m_isOpenBySelf(FALSE)
{
	HRESULT hr=m_pRecordset.CreateInstance( __uuidof( Recordset ));
	if( FAILED(hr) )
	{
		m_errMessage="�������ݿ��¼������ʧ�ܣ�";
		m_isCreated=FALSE;
	}

	m_isCreated=TRUE;
}

CAdoRecordset::CAdoRecordset(_RecordsetPtr rec)
: m_conn(FALSE), m_isOpenBySelf(FALSE), m_pRecordset(rec)
{

}

CAdoRecordset::~CAdoRecordset()
{
	if(m_isOpenBySelf)
	{
		try
		{
			m_pRecordset->Close();
		}
		catch (_com_error &e)
		{
			m_errMessage=(LPCSTR)e.Description();
		}
	}
}

BOOL CAdoRecordset::open(CString tableName, int openWay)
{
	if(!m_conn)
	{
		m_errMessage="���ȴ�����¼������";
		m_isOpenBySelf=FALSE;
		return FALSE;
	}

	if(!m_conn->isConnected())
	{
		m_errMessage="���ݿ�δ���ӡ�";
		m_isOpenBySelf=FALSE;
		return FALSE;
	}

	try
	{
// 		m_pRecordset->Open(_variant_t("zzspbc_o"), _variant_t((IDispatch *)pMyConnect,true), adOpenKeyset, adLockOptimistic, adCmdTable);
		switch(openWay)
		{
		case 0:
			m_pRecordset->Open(_variant_t(tableName), _variant_t((IDispatch *)m_conn->getAdoConnectionPtr(),true), adOpenKeyset, adLockOptimistic, adCmdTable);
			break;
		case 1:
			m_pRecordset->Open(_variant_t(tableName), _variant_t((IDispatch *)m_conn->getAdoConnectionPtr(),true), adOpenKeyset, adLockOptimistic, adCmdText);
			break;
		}
	}
	catch (_com_error &e)
	{
		m_errMessage="�� " + tableName + " ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		m_isOpenBySelf=FALSE;
		return FALSE;
	}

	m_isOpenBySelf=TRUE;
	return TRUE;
}

void CAdoRecordset::setFilter(CString filter)  // �൱�� where ������������ where �ַ�����
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return;
// 	}

	m_pRecordset->Filter=_variant_t(filter);
}

int CAdoRecordset::getRecordCount()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return 0;
// 	}

	int count=0;
	try
	{
		count=m_pRecordset->GetRecordCount();
	}
	catch (_com_error &e)
	{
		m_errMessage="��ȡ��¼��ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return 0;
	}

	return count;
}

BOOL CAdoRecordset::isEOF()
{
	return m_pRecordset->adoEOF==VARIANT_TRUE;
}

BOOL CAdoRecordset::isBOF()
{
	return m_pRecordset->BOF==VARIANT_TRUE;
}

BOOL CAdoRecordset::moveFirst()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}

	try
	{
		m_pRecordset->MoveFirst();
	}
	catch (_com_error &e)
	{
		m_errMessage="��¼�� MoveFirst ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}

BOOL CAdoRecordset::moveLast()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->MoveLast();
	}
	catch (_com_error &e)
	{
		m_errMessage="��¼�� MoveLast ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}

BOOL CAdoRecordset::moveNext()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->MoveNext();
	}
	catch (_com_error &e)
	{
		m_errMessage="��¼�� MoveNext ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
	
	return TRUE;
}

BOOL CAdoRecordset::movePrevious()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->MovePrevious();
	}
	catch (_com_error &e)
	{
		m_errMessage="��¼�� MovePrevious ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
	
	return TRUE;
}

CString CAdoRecordset::getFieldString(CString fieldName)  // ��ȡ��ǰ��¼ָ���ֶε��ַ���
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return "";
// 	}

	if(fieldName.GetLength()<=0)
	{
		m_errMessage="ָ�����ֶ�����Ϊ���ַ�����";
		return "";
	}

	try
	{
		// ��ʱ��ע�͵�������û��ʲô����
// 		if(m_pRecordset->adoEOF==VARIANT_TRUE)
// 		{
// 			m_errMessage="ָ�����ֶ�����Ϊ���ַ�����";
// 			return "";
// 		}

		CString svalue=(char*)(_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t(fieldName))->Value);
		return svalue;
	}
	catch (_com_error &e)
	{
		m_errMessage="��ȡ�ֶ� " + fieldName + "ֵʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return "";
	}
}

BOOL CAdoRecordset::setFieldString(CString fieldName, CString fieldValue)  // ���õ�ǰ��¼��ָ���ֶε�ֵ
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	if(fieldName.GetLength()<=0)
	{
		m_errMessage="ָ�����ֶ�����Ϊ���ַ�����";
		return FALSE;
	}

	if(fieldValue.GetLength()<=0)
	{
		m_errMessage="ָ�����ֶ�ֵΪ���ַ�����";
		return FALSE;
	}
	
	try
	{
		m_pRecordset->Fields->GetItem(_variant_t(fieldName))->Value=_bstr_t(fieldValue);;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="�����ֶ� " + fieldName + "ֵΪ " + fieldValue + " ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

int CAdoRecordset::getFielInt(CString fieldName)  // ��ȡ��ǰ��¼��ָ���ֶε�ֵ
{
	if(fieldName.GetLength()<=0)
	{
		m_errMessage="ָ�����ֶ�����Ϊ���ַ�����";
		return -1;
	}
	
	try
	{
		int nvalue=(m_pRecordset->Fields->GetItem(_variant_t(fieldName))->Value).dblVal;
		return nvalue;
	}
	catch (_com_error &e)
	{
		m_errMessage="��ȡ�ֶ� " + fieldName + "ֵʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return -1;
	}
}

BOOL CAdoRecordset::addNew()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}

	try
	{
		m_pRecordset->AddNew();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="���� AddNew ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::update()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->Update();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="���� Update ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::cancelUpdate()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->CancelUpdate();
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="���� CancelUpdate ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::updateBatch(AffectEnum ae)
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->UpdateBatch(ae);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="���� UpdateBatch ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::cancelBatch(AffectEnum ae)
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->CancelBatch(ae);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="���� CancelBatch ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::deleteRecord(AffectEnum ae)  // ɾ����ǰ��¼
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->Delete(ae);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="���� Delete ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoRecordset::requery()
{
// 	if(!m_isOpenBySelf)
// 	{
// 		m_errMessage="���ȴ򿪼�¼����";
// 		return FALSE;
// 	}
	
	try
	{
		m_pRecordset->Requery(0);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_errMessage="���� Requery ����ʧ�ܣ�\n";
		m_errMessage+=(LPCSTR)e.Description();
		return FALSE;
	}
}
