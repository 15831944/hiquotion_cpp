#pragma once

#include <c++\AdvancedLib\multithreadpattern\productorconsumer\ProductConsumeEventThreadBase.h>

class CAudioG729AGetData4EncodeThread :
	public CProductConsumeEventThreadBase
{
public:
	CAudioG729AGetData4EncodeThread(void);
	~CAudioG729AGetData4EncodeThread(void);

	// �ж������Ƿ��㹻
	virtual BOOL isDataEnough();

	// �����㹻ʱ�������ó������ݳ���
	virtual unsigned int getEnoughDataLength();

};
