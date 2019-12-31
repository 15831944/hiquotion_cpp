#pragma once
#include "../MonitorLib/Interface/IStatus.h"

class CFileSizeStatus :
	public IStatus
{
public:
	CFileSizeStatus(void);
	CFileSizeStatus(int fileSize);
	~CFileSizeStatus(void);

	// 0����ȣ�-1���Ȳ����е�״̬С��1���Ȳ����е�״̬��
	int compare(IStatus *status);

public:
	ULONGLONG FileSize;

};
