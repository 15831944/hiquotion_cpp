#include "StdAfx.h"
#include "FileSizeStatus.h"

CFileSizeStatus::CFileSizeStatus(void)
{
}

CFileSizeStatus::~CFileSizeStatus(void)
{
}

// 0����ȣ�-1���Ȳ����е�״̬С��1���Ȳ����е�״̬��
int CFileSizeStatus::compare(IStatus *status)
{
	CFileSizeStatus *fstatus=(CFileSizeStatus *)status;
	if(FileSize > fstatus->FileSize)
		return 1;
	else if(FileSize < fstatus->FileSize)
		return -1;
	else
		return 0;
}
