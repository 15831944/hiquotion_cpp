#pragma once
#include <c++\AdvancedLib\multithreadpattern\productorconsumer\ProductConsumeEventThreadBase.h>

class CAudioData4PlayThread :
	public CProductConsumeEventThreadBase
{
public:
	CAudioData4PlayThread(void);
	~CAudioData4PlayThread(void);

	// �ж������Ƿ��㹻
	virtual BOOL isDataEnough();

	// �����㹻ʱ�������ó������ݳ���
	virtual unsigned int getEnoughDataLength();

};
