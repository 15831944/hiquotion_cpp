// CycledBuffer.h: interface for the CCycledBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYCLEDBUFFER_H__015A0855_671E_4402_A97D_07E5E1C89090__INCLUDED_)
#define AFX_CYCLEDBUFFER_H__015A0855_671E_4402_A97D_07E5E1C89090__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>

#define DEFAULT_BUFFER_LENGTH 10240000

class CCycledBuffer  
{
public:
	CCycledBuffer();
	CCycledBuffer(unsigned int bufferLength);
// 	CCycledBuffer(char *buffer, unsigned int bufferLength);
	virtual ~CCycledBuffer();

	// ��ʼ��
	void init();

	// ��ȡ����������
	unsigned int getBufferLength();

	// ��ȡ������ʣ�೤��
	unsigned int getRestLength();
	// ��ȡ���ݳ���
	unsigned int getDataLength();
	// д������
	int write(char *data, unsigned int dataLength);
	// ��ȡ����
	int read(char *data, unsigned int dataLength);

	// �ض��建������С
	void redimLength(unsigned int length, BOOL reserveData=TRUE);

	char *getCycledBuffer() const { return m_cycledBuffer; }

	unsigned int getStartIndex() const { return m_startIndex; }
	unsigned int getEndIndex() const { return m_endIndex; }

	// �˳��ȴ�״̬
	void exitWaiting();

#ifdef _DEBUG

	// for test only
	void setStartIndex(unsigned int val) { m_startIndex = val; }

	// for test only
	void setEndIndex(int val) { m_endIndex = val; }

	// for test only
	BOOL isEmpty() const { return m_isEmpty; }
	// for test only
	void setEmpty(BOOL val) { m_isEmpty = val; }

	// for test only
	void setBufferData(int index, char data)
	{
		if(index<0 || index>m_bufferLength)
			return;

		m_cycledBuffer[index]=data;
	};

	char getBufferData(int index)
	{
		if(index<0 || index>m_bufferLength)
			return 0;

		return m_cycledBuffer[index];
	}

#endif

private:
	char *m_cycledBuffer;
	unsigned int m_bufferLength;
	BOOL m_isBufferOutside;

	unsigned int m_startIndex;  // ��ʼλ������
	int m_endIndex;    // ����λ������
	BOOL m_isEmpty;             // ������������ڿ�ʼ�����ĺ�һλ�ã����жϲ�������û�����ݻ�����������������������������ж�
	CMutex m_writeLock;
	CMutex m_readLock;
// 	CSemaphore *m_notFull;
// 	CSemaphore *m_notEmpty;

	CEvent m_notFull;
	CEvent m_notEmpty;

	int m_waitedReadLength;
	int m_waitedWriteLength;

	BOOL m_isExit;
};

#endif // !defined(AFX_CYCLEDBUFFER_H__015A0855_671E_4402_A97D_07E5E1C89090__INCLUDED_)
