#pragma once

class ITarget
{
public:
	ITarget(void);
	~ITarget(void);

	// 0����ȣ�-1���Ȳ����е�״̬С��1���Ȳ����е�״̬��
	virtual int compare(ITarget *status)=0;
};
