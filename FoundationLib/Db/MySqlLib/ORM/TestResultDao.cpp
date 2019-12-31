#include "StdAfx.h"
#include "TestResultDao.h"

CTestResultDao::CTestResultDao()
: m_opr(NULL)
{
}

CTestResultDao::CTestResultDao(CDbOperation *opr)
: m_opr(opr)
{
}

CTestResultDao::~CTestResultDao(void)
{
}

// ��ȡ���һ�� AutoIncrement�����������ֶΣ� �������ݺ�� id ֵ
int CTestResultDao::getLastId()
{
	if(!m_opr)
		return -11;

	char *sql="select LAST_INSERT_ID()";

	ResultSet *rs=m_opr->executeQuery(sql, 0);
	if(!rs)
		return -12;

	if(rs->next()==false)
		return -13;

// 	ULONGLONG v=rs->getInt64(1);
	int v=rs->getInt(1);

	m_opr->closeResultSet(rs);

	return v;
}
