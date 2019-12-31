// DataBuffer.h: interface for the CDataBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABUFFER_H__8097583E_1F6A_4B96_A25F_0793B00B8BA4__INCLUDED_)
#define AFX_DATABUFFER_H__8097583E_1F6A_4B96_A25F_0793B00B8BA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BufferOperation.h"

// ���ݻ�������
// 1���ڻ�����������Ļ����ϣ�ʹ��һ��������
// 2������˳��׷�����ݣ�����˳���ȡ���ݣ�������Ҫָ����ȡ����ʼλ��
// 3������������ǰ�棬ָ��һ���ֽڴ�С������ͷ
// 4���������չ�������ָ����С������ͷ�������ȡ���������������ݵĲ���
class CDataBuffer : public CBufferOperation  
{
public:
	CDataBuffer();
	CDataBuffer(unsigned int headLength);
	virtual ~CDataBuffer();

	// ��ʼ��
	void init();

	// ����дȫ�������ֽ�����
	int readTotalData(char *data, int dataLength);
	int writeTotalData(char *data, int dataLength);
	
	// ����д��ǰλ�ÿ�ʼ��ָ�����ȵ��ֽ�����
	int readBytes(char *data, int dataLength);
	int appendBytes(char *data, int dataLength);
	
	// ����д��ǰλ�ÿ�ʼ��1���ֽ�
	int readByte(unsigned char *data);
	int appendByte(unsigned char data);
	
	// ����д��ǰλ�ÿ�ʼ��4�ֽ�����
	int readLong(int *lng);
	int writeLong(int lng);
	
	// ����д��ǰλ�ÿ�ʼ��2�ֽ�����
	int readInteger(short *integer);
	int writeInteger(short integer);
	
	// ����д��ǰλ�ÿ�ʼ��ָ�����ȵ��ַ���
	int readString(std::string &str, unsigned int length);
	int writeString(std::string str, unsigned int length);
	int readString(CString &str, unsigned int length);
	int writeString(CString str, unsigned int length);

	// ��ȡ�����õ�ǰ��������
	unsigned int getDataIndex() const { return m_dataIndex; }
	void setDataIndex(unsigned int val) { m_dataIndex = val; }

	// ��ȡ���ݳ���
	unsigned int getDataLength() const { return m_dataLength; }

	// �̳и���ķ���
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


protected:
	unsigned int m_dataIndex;
	unsigned int m_dataLength;
};

#endif // !defined(AFX_DATABUFFER_H__8097583E_1F6A_4B96_A25F_0793B00B8BA4__INCLUDED_)
