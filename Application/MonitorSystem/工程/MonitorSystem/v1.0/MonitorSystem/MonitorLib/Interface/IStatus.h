#pragma once

class IStatus
{
public:
	IStatus(void);
	~IStatus(void);

	// 0����ȣ�-1���Ȳ����е�״̬С��1���Ȳ����е�״̬��
	virtual int compare(IStatus *status)=0;
};
