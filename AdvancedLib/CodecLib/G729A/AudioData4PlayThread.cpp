#include "stdafx.h"
#include "AudioData4PlayThread.h"

CAudioData4PlayThread::CAudioData4PlayThread(void)
{
}

CAudioData4PlayThread::~CAudioData4PlayThread(void)
{
}

// �ж������Ƿ��㹻
BOOL CAudioData4PlayThread::isDataEnough()
{
	if(m_cycledBuffer.getDataLength()<=100)
		return FALSE;

	return TRUE;
}

// �����㹻ʱ�������ó������ݳ���
unsigned int CAudioData4PlayThread::getEnoughDataLength()
{
	return m_cycledBuffer.getDataLength();
}
