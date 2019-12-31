// DataBuffer.h: interface for the CDataBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABUFFER_H__BEED6793_FA14_4B6C_B9DD_F7C7E622F10C__INCLUDED_)
#define AFX_DATABUFFER_H__BEED6793_FA14_4B6C_B9DD_F7C7E622F10C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SUPPORT_MULTI_THREAD

#ifdef SUPPORT_MULTI_THREAD
#include <afxmt.h>
#endif
#include <string>

#define MAX_BUFFER_LENGTH 200000

// ������������
// �������������������Բ�����������
// �ṩ������Ķ�д����
class CBufferOperation  
{
public:
	CBufferOperation(unsigned int bufferLength=MAX_BUFFER_LENGTH);
	virtual ~CBufferOperation();

	// ��ȡ����������
	unsigned int getBufferLength() const { return m_bufferLength; }
// 	void setBufferLength(unsigned int val) { m_bufferLength = val; }

// 	// x����������������ˣ����׵������ڶ�ȡ������ʱ�������е����ݱ��ƻ���������²⣩�����Ҳ����׼��Ա���
	// �ض��建������С��Ĭ�ϲ�����ԭ�������е����ݣ�
	// �ض�����ԭ��С�������ʱ������
	int redimBufferLength(int bufferLength, BOOL reserveData=FALSE);

// 	// ��ȡ���ݳ���
// 	unsigned int getDataLength() const { return m_dataLength; }

	// ����дȫ���������ֽ�����
	int readTotalBuffer(char *data);
	int writeTotalBuffer(char *data);

	// ����дָ��λ�ÿ�ʼ��ָ�����ȵ��ֽ�����
	int readBytes(unsigned int pos, char *data, int dataLength);
	int writeBytes(unsigned int pos, char *data, int dataLength);

	// ����дָ��λ�ÿ�ʼ��1���ֽ�
	int readByte(unsigned int pos, unsigned char *data);
	int writeByte(unsigned int pos, unsigned char data);

	// ����дָ��λ�ÿ�ʼ��4�ֽ�����
	int readLong(unsigned int pos, int *lng);
	int writeLong(unsigned int pos, int lng);

	// ����дָ��λ�ÿ�ʼ��2�ֽ�����
	int readInteger(unsigned int pos, short *integer);
	int writeInteger(unsigned int pos, short integer);

// 	// ����дָ��λ�ÿ�ʼ��1���ַ�
// 	int readChar(unsigned int pos, char *data);
// 	int writeChar(unsigned int pos, char data);

	// ����дָ��λ�ÿ�ʼ��ָ�����ȵ��ַ���
	int readString(unsigned int pos, std::string &str, unsigned int length);
	int writeString(unsigned int pos, std::string str, unsigned int length);
	int readString(unsigned int pos, CString &str, unsigned int length);
	int writeString(unsigned int pos, CString str, unsigned int length);

	unsigned int getHeadLength() const { return m_headLength; }
	void setHeadLength(unsigned int val) { m_headLength = val; }

protected:
	unsigned int m_bufferLength;

	unsigned int m_headLength;
	char *m_buffer;

#ifdef SUPPORT_MULTI_THREAD
	CMutex m_lock;
#endif

};

#endif // !defined(AFX_DATABUFFER_H__BEED6793_FA14_4B6C_B9DD_F7C7E622F10C__INCLUDED_)
