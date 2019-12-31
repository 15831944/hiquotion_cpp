// DataBuffer.cpp: implementation of the CDataBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBufferOperation::CBufferOperation(unsigned int bufferLength)
: m_headLength(0)//, m_dataLength(0)
{
	unsigned int length=bufferLength;
	if(length==0)
		length=MAX_BUFFER_LENGTH;

	m_buffer=new char[length];
	m_bufferLength=length;
}

CBufferOperation::~CBufferOperation()
{
	delete m_buffer;
	m_buffer=NULL;
}

// �ض��建������С��Ĭ�ϲ�����ԭ�������е����ݣ�
// �ض�����ԭ��С�������ʱ������
int CBufferOperation::redimBufferLength(int bufferLength, BOOL reserveData)
{
	if(bufferLength<m_bufferLength)
		return 0;

	char *buffer=new char[bufferLength];
	memset(buffer, 0x00, bufferLength);
	memcpy(buffer, m_buffer, m_bufferLength);

	delete m_buffer;
	m_buffer=buffer;
	m_bufferLength=bufferLength;

	return 0;
}

// ����дȫ���������ֽ�����
// ����ֵ��
// 0���ɹ�
// -1��dataΪ�գ���*dataΪ��
int CBufferOperation::readTotalBuffer(char *data)
{
	if(!data)
		return -1;

	memcpy(data, m_buffer+m_headLength, m_bufferLength-m_headLength);
	return 0;
}

// ����ֵ��
// 0���ɹ�
// -1��dataΪ��
int CBufferOperation::writeTotalBuffer(char *data)
{
	if(!data)
		return -1;

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif

	memcpy(m_buffer+m_headLength, data, m_bufferLength-m_headLength);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
return 0;
}

// ����дָ��λ�ÿ�ʼ��ָ�����ȵ��ֽ�����
// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
// -2����ȡ�ĳ��ȷ������򳬳��˴�posλ��֮��Ļ���������
int CBufferOperation::readBytes(unsigned int pos, char *data, int dataLength)
{
	if(pos>=m_bufferLength)
		return -1;

	if(dataLength<=0 || dataLength>m_bufferLength-1-pos)
		return -2;

	memcpy(data, m_buffer+m_headLength+pos, dataLength);
	return 0;
}

// ����ֵ��
// 0���ɹ�
// -1��д���λ�ó����˻���������-1
// -2��д��ĳ��ȷ������򳬳��˴�posλ��֮��Ļ���������
int CBufferOperation::writeBytes(unsigned int pos, char *data, int dataLength)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(dataLength<=0 || dataLength>m_bufferLength-1-pos)
		return -2;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	memcpy(m_buffer+m_headLength+pos, data, dataLength);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// ����дָ��λ�ÿ�ʼ��1���ֽ�
// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
// -2��dataΪ��
int CBufferOperation::readByte(unsigned int pos, unsigned char *data)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(!data)
		return -2;

	*data=m_buffer[m_headLength+pos];
	return 0;
}

// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
int CBufferOperation::writeByte(unsigned int pos, unsigned char data)
{
	if(pos>=m_bufferLength)
		return -1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	m_buffer[m_headLength+pos]=data;

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// ����дָ��λ�ÿ�ʼ��4�ֽ�����
// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
// -2�����ͱ���ָ��Ϊ��
int CBufferOperation::readLong(unsigned int pos, int *lng)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(!lng)
		return -2;

	memcpy(lng, m_buffer+m_headLength+pos, 4);
	return 0;
}

// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
int CBufferOperation::writeLong(unsigned int pos, int lng)
{
	if(pos>=m_bufferLength)
		return -1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	memcpy(m_buffer+m_headLength+pos, &lng, 4);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// ����дָ��λ�ÿ�ʼ��2�ֽ�����
// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
// -2�����ͱ���ָ��Ϊ��
int CBufferOperation::readInteger(unsigned int pos, short *integer)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(!integer)
		return -2;
	
	memcpy(integer, m_buffer+m_headLength+pos, 2);
	return 0;

}

// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
int CBufferOperation::writeInteger(unsigned int pos, short integer)
{
	if(pos>=m_bufferLength)
		return -1;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	memcpy(m_buffer+m_headLength+pos, &integer, 2);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// // ����дָ��λ�ÿ�ʼ��1���ַ�
// int CDataBuffer::readChar(unsigned int pos, char *data)
// {
// 
// }
// 
// int CDataBuffer::writeChar(unsigned int pos, char data)
// {
// 
// }

// ����дָ��λ�ÿ�ʼ��ָ�����ȵ��ַ���
// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
// -2��ָ���ĳ��ȷ������򳬳��˴�posλ��֮��Ļ���������
int CBufferOperation::readString(unsigned int pos, std::string &str, unsigned int length)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-1-pos)
		return -2;

	char *ch=new char[length+1];
	readBytes(pos, ch, length);
	ch[length]='\0';
	str=ch;
	delete ch;
	return 0;
}

// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
// -2��ָ���ĳ��ȷ������򳬳��˴�posλ��֮��Ļ���������
int CBufferOperation::writeString(unsigned int pos, std::string str, unsigned int length)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-1-pos)
		return -2;
	
#ifdef SUPPORT_MULTI_THREAD
	m_lock.Lock();
#endif
	
	memcpy(m_buffer+m_headLength+pos, str.c_str(), length);

#ifdef SUPPORT_MULTI_THREAD
	m_lock.Unlock();
#endif
	
	return 0;
}

// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
// -2��ָ���ĳ��ȷ������򳬳��˴�posλ��֮��Ļ���������
int CBufferOperation::readString(unsigned int pos, CString &str, unsigned int length)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-1-pos)
		return -2;
	
	std::string s;
	readString(pos, s, length);
	str=s.c_str();
	return 0;
}

// ����ֵ��
// 0���ɹ�
// -1����ȡ��λ�ó����˻���������-1
// -2��ָ���ĳ��ȷ������򳬳��˴�posλ��֮��Ļ���������
int CBufferOperation::writeString(unsigned int pos, CString str, unsigned int length)
{
	if(pos>=m_bufferLength)
		return -1;
	
	if(length<=0 || length>m_bufferLength-1-pos)
		return -2;
	
	std::string s=(LPTSTR)(LPCSTR)str;
	writeString(pos, s, length);
	return 0;
}
