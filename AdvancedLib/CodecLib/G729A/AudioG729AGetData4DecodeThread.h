#pragma once

#include <c++\AdvancedLib\multithreadpattern\productorconsumer\ProductConsumeEventThreadBase.h>

class CAudioG729AGetData4DecodeThread :
	public CProductConsumeEventThreadBase
{
public:
	CAudioG729AGetData4DecodeThread(void);
	~CAudioG729AGetData4DecodeThread(void);

	// �ж������Ƿ��㹻
	virtual BOOL isDataEnough();

	// �����㹻ʱ�������ó������ݳ���
	virtual unsigned int getEnoughDataLength();

};
