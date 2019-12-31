// CycledBuffer.cpp: implementation of the CCycledBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CycledBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCycledBuffer::CCycledBuffer()
: m_isBufferOutside(FALSE), m_waitedReadLength(0), m_waitedWriteLength(0), m_isExit(FALSE),m_isEmpty(TRUE)
{
	m_cycledBuffer=new char[DEFAULT_BUFFER_LENGTH];
	m_bufferLength=DEFAULT_BUFFER_LENGTH;
	
	m_startIndex=0;
	m_endIndex=-1;

// 	m_notFull=new CSemaphore(DEFAULT_BUFFER_LENGTH, DEFAULT_BUFFER_LENGTH);
// 	m_notEmpty=new CSemaphore(0, DEFAULT_BUFFER_LENGTH);
}

CCycledBuffer::CCycledBuffer(unsigned int bufferLength)
: m_isBufferOutside(FALSE), m_waitedReadLength(0), m_waitedWriteLength(0), m_isExit(FALSE), m_isEmpty(TRUE)
{
	unsigned int len=0;
	if(bufferLength>0)
		len=bufferLength;
	else
		len=DEFAULT_BUFFER_LENGTH;

	m_cycledBuffer=new char[len];
	m_bufferLength=len;
	
	m_startIndex=0;
	m_endIndex=-1;

// 	m_notFull=new CSemaphore(DEFAULT_BUFFER_LENGTH, DEFAULT_BUFFER_LENGTH);
// 	m_notEmpty=new CSemaphore(0, DEFAULT_BUFFER_LENGTH);
}

// CCycledBuffer::CCycledBuffer(char *buffer, unsigned int bufferLength)
// : m_isBufferOutside(TRUE)
// {
// 	if(buffer && bufferLength>0)
// 	{
// 		m_cycledBuffer=buffer;
// 		m_bufferLength=bufferLength;
// 	}
// 	else
// 	{
// 	m_cycledBuffer=new char[DEFAULT_BUFFER_LENGTH];
// 	m_bufferLength=DEFAULT_BUFFER_LENGTH;
// 	}
// 	
// 	m_startPosition=0;
// 	m_endPosition=-1;
// }

CCycledBuffer::~CCycledBuffer()
{
	delete m_cycledBuffer;

	exitWaiting();

// 	delete m_notFull;
// 	delete m_notEmpty;
}

// ��ʼ��
void CCycledBuffer::init()
{
	m_readLock.Lock();
	m_writeLock.Lock();

	m_startIndex=0;
	m_endIndex=-1;
	m_isEmpty=TRUE;

	m_readLock.Unlock();
	m_writeLock.Unlock();

	m_notEmpty.SetEvent();
	m_notFull.SetEvent();

}

// ��ȡ����������
unsigned int CCycledBuffer::getBufferLength()
{
	return m_bufferLength;
}

// ��ȡ������ʣ�೤��
unsigned int CCycledBuffer::getRestLength()
{
	return m_bufferLength-getDataLength();
}

// ��ȡ���ݳ���
unsigned int CCycledBuffer::getDataLength()
{
	if(m_isEmpty)
		return 0;

	int length=m_endIndex-m_startIndex+1;
	if(length>0)
		return length;
	else
		return length+m_bufferLength;
}

// д������
// ����ֵ��
// 0���ɹ�
// -1����������
// -2��ȡ��д���Եȴ��˳�
// -3����д������ݳ��ȳ����˻���������
int CCycledBuffer::write(char *data, unsigned int dataLength)
{
	if(!data)
		return -1;

	if(dataLength==0)
		return -1;

	if(m_isExit)
		return -2;

	if(m_bufferLength<dataLength)
		return -3;

	unsigned int restLength=getRestLength();
	while(restLength<dataLength)
	{
		Sleep(1);

		m_waitedWriteLength=dataLength;
		// ���������ʣ�೤�Ȳ�������ȴ�
		WaitForSingleObject(m_notFull, INFINITE);

		if(m_isExit)
			return FALSE;

		Sleep(1);

		m_writeLock.Lock();

		// ��Lock֮ǰ�����������ʣ�೤���Ѿ���������ô��Lock֮����Ҫ��һ���ж�
		// ��ʱֻ�е�ǰ�̲߳������ݣ�����ֻҪ�������㣬�Ϳ��Լ���
		restLength=getRestLength();
		if(restLength<dataLength)
		{
			m_writeLock.Unlock();
			return FALSE;
		}

	}

	if(m_endIndex+dataLength<=m_bufferLength-1)   // pay attention : m_endPosition can be -1, but nothing serious because of above safe check.
	{
// 		unsigned int pos=(m_endIndex==-1 ? 0 : m_endIndex);
		memcpy(m_cycledBuffer+m_endIndex+1, data, dataLength);
		if(m_endIndex==-1)
			m_endIndex=dataLength-1;
		else
			m_endIndex+=dataLength;
// 		if(m_endIndex==m_bufferLength-1)
// 			m_endIndex=0;
	}
	else
	{
		int len1=m_bufferLength-1-m_endIndex;  // �Ǵ� m_endIndex ��һλ�ÿ�ʼ����������� m_endIndex �� m_bufferLength-1����ô�����û���ˣ�len1 ��Ϊ 0
		int len2=dataLength-len1;
		if(len1>0)
			memcpy(m_cycledBuffer+m_endIndex+1, data, len1);
		memcpy(m_cycledBuffer, data + len1, len2);
		m_endIndex=len2-1;
	}

	BOOL ret=FALSE;
// 	if(m_waitedReadLength>0)
// 	{
// 		if(getDataLength()>=m_waitedReadLength)
// 		{
			ret=m_notEmpty.SetEvent();
			m_waitedReadLength=0;
// 		}
// 	}

	m_writeLock.Unlock();

	m_isEmpty=FALSE;

	return 0;
}

// ��ȡ����
// ����ֵ��
// 0���ɹ�
// -1����������
// -2��ȡ��д���Եȴ��˳�
// -3����д������ݳ��ȳ����˻���������
int CCycledBuffer::read(char *data, unsigned int dataLength)
{
	if(!data)
		return -1;

	if(dataLength==0)
		return -1;

	if(m_isExit)
		return -2;

	if(m_bufferLength<dataLength)
		return -3;

	while(getDataLength()<dataLength)
	{
		Sleep(1);

		m_waitedReadLength=dataLength;
		// ������ݳ��Ȳ�������ȴ�
		WaitForSingleObject(m_notEmpty, INFINITE);

		if(m_isExit)
			return FALSE;

		Sleep(1);

		m_readLock.Lock();

		// ��Lock֮ǰ��������ݳ����Ѿ���������ô��Lock֮����Ҫ��һ���ж�
		// ��ʱֻ�е�ǰ�̲߳������ݣ�����ֻҪ�������㣬�Ϳ��Լ���
		if(getDataLength()<dataLength)
		{
			m_readLock.Unlock();
			return FALSE;
		}
	}

	if(m_startIndex+dataLength<=m_bufferLength-1)
	{
		memcpy(data, m_cycledBuffer+m_startIndex, dataLength);
		m_startIndex+=dataLength;
		if(m_startIndex==m_bufferLength)
			m_startIndex=0;
	}
	else
	{
// 		char *tmp=new char[dataLength];
		int len1=m_bufferLength-m_startIndex;   // �� m_startIndex ��ʼ�������� m_startIndex �� m_bufferLength ��ʱ�򣬺����û�У��� len1 Ϊ 0
		int len2=dataLength-len1;
		if(len1>0)
			memcpy(data, m_cycledBuffer+m_startIndex, len1);
		memcpy(data+len1, m_cycledBuffer, len2);
// 		memcpy(tmp, m_buffer+m_startPosition, len1);
// 		memcpy(tmp+len1, m_buffer, len2);
		m_startIndex=len2;
		
// 		memcpy(data, tmp, dataLength);
// 		delete tmp;
	}

	if((m_endIndex+1) % m_bufferLength == m_startIndex)
		m_isEmpty=TRUE;
	else
		m_isEmpty=FALSE;
	
	BOOL ret=FALSE;
// 	if(m_waitedWriteLength>0)
// 	{
// 		if(getRestLength()>=m_waitedWriteLength)
// 		{
			ret=m_notFull.SetEvent();
			m_waitedWriteLength=0;
// 		}
// 	}

	m_readLock.Unlock();

	return TRUE;
}

// �ض��建������С
void CCycledBuffer::redimLength(unsigned int length, BOOL reserveData)
{
	if(length<=0)
		return;

	char *tmp=new char[length];
	memset(tmp, 0x00, length);

	m_writeLock.Lock();
	m_readLock.Lock();

	if(reserveData)
		memcpy(tmp, m_cycledBuffer, min(m_bufferLength, length));

	delete m_cycledBuffer;
	m_cycledBuffer=tmp;

	m_bufferLength=length;

	m_readLock.Unlock();
	m_writeLock.Unlock();
}

// �˳��ȴ�״̬
void CCycledBuffer::exitWaiting()
{
	m_isExit=TRUE;
	m_notEmpty.SetEvent();
	m_notFull.SetEvent();
}

