#include "StdAfx.h"
#include "MonitedObjectCreator.h"
#include "../FileMonitor/MonitedFileSize.h"

CMonitedObjectCreator::CMonitedObjectCreator(void)
{
}

CMonitedObjectCreator::~CMonitedObjectCreator(void)
{
}

IMonitedObject *CMonitedObjectCreator::create(string type, string status)
{
	CString stype=type.c_str();
	stype=stype.MakeUpper();
	CString sstatus=status.c_str();
	sstatus=sstatus.MakeUpper();
	if(stype=="FILE")
	{
		if(sstatus=="SIZE")
			return new CMonitedFileSize(type, status);  // ������Ĭ�Ϲ��캯�������������Լ�¼������ض������ĸ����͵ģ��Լ���ض�����ĸ�״̬���Ա��ڽ����Ͽ��������Ϣ
	}

	return NULL;
}
