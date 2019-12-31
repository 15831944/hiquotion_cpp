#pragma once
#include "../MonitorLib/Interface/ITarget.h"

class CFileSizeTarget :
	public ITarget
{
public:
	CFileSizeTarget(void);
	CFileSizeTarget(int fileSize);
	~CFileSizeTarget(void);

	// 0����ȣ�-1���Ȳ����е�״̬С��1���Ȳ����е�״̬��
	int compare(ITarget *target);

public:
	ULONGLONG FileSize;

};
