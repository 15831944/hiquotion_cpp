#include "StdAfx.h"
#include "FileSizeTarget.h"

CFileSizeTarget::CFileSizeTarget(void)
{
}

CFileSizeTarget::~CFileSizeTarget(void)
{
}

// 0����ȣ�-1���Ȳ����е�״̬С��1���Ȳ����е�״̬��
int CFileSizeTarget::compare(ITarget *target)
{
	CFileSizeTarget *ftarget=(CFileSizeTarget *)target;
	if(FileSize > ftarget->FileSize)
		return 1;
	else if(FileSize < ftarget->FileSize)
		return -1;
	else
		return 0;
}
