#include "stdafx.h"
#include "AudioG729AGetData4DecodeThread.h"

CAudioG729AGetData4DecodeThread::CAudioG729AGetData4DecodeThread(void)
{
}

CAudioG729AGetData4DecodeThread::~CAudioG729AGetData4DecodeThread(void)
{
}

// �ж������Ƿ��㹻
BOOL CAudioG729AGetData4DecodeThread::isDataEnough()
{
	if(m_cycledBuffer.getDataLength()<10)
		return FALSE;
	
	return TRUE;
}

// �����㹻ʱ�������ó������ݳ���
unsigned int CAudioG729AGetData4DecodeThread::getEnoughDataLength()
{
// 	unsigned int length=m_cycledBuffer.getDataLength();
// 	unsigned int count=length/10;
// 	length=count*10;
// 	return length;
	return m_cycledBuffer.getDataLength()/10*10;
}
