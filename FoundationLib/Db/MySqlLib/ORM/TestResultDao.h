#pragma once

#include "DbOperation.h"

class CTestResultDao
{
public:
	CTestResultDao();
	CTestResultDao(CDbOperation *opr);
	~CTestResultDao(void);

	// ��ȡ���һ�� AutoIncrement�����������ֶΣ� �������ݺ�� id ֵ
	int getLastId();

protected:
	CDbOperation *m_opr;
};
