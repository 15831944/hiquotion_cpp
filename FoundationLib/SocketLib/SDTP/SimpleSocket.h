#if !defined(AFX_SIMPLESOCKET_H__814A6119_BBDF_4C8C_8899_AEA0B07E0284__INCLUDED_)
#define AFX_SIMPLESOCKET_H__814A6119_BBDF_4C8C_8899_AEA0B07E0284__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimpleSocket.h : header file
//

#include <C++\FoudationLib\EventLib\EventEmu-��MFC���¼�����\IEventRaisable.h>
#include <C++\FoudationLib\EventLib\EventEmu-��MFC���¼�����\Delegate.h>
#include <C++\FoudationLib\ProtocolLib\SDTP\SDTP.h>
#include <C++\FoudationLib\BufferLib\DataBuffer.h>
#include <C++\FoudationLib\EventLib\EventEmu-��MFC���¼�����\IEvent.h>

// ��������ݰ��ռ����ݴ���Э�飨��SDTP��

// �����ÿ����Ҫ��������ݶ���װ�������Ĵ���Э������ݣ�Ȼ���ٷ���
// �������ݺ��ȸ���Э��ͷ�ж����ݳ��ȣ����ж������Ƿ�����㹻�������㹻���׳��¼����¼��а���ʵ�ʴ�������ݺͳ������ԣ�

#define SS_RECEIVE_BUFFER_TOTAL_LENGTH 10240000
#define SS_RECEIVE_BUFFER_LENGTH 1000

enum SS_STATUS
{
	SSS_NO_ACTION,
	SSS_RECEIVE_DATA,
};

#include <afxsock.h>

/////////////////////////////////////////////////////////////////////////////
// CSimpleSocket command target

class CSimpleSocket : public CSocket, public IEventRaisable
{
// Attributes
public:

// Operations
public:
	CSimpleSocket();
	virtual ~CSimpleSocket();
	
	int sendString(CString &msg);

	CDelegate DataArrived;

	void setBufferLength(int bufferLength);

	SS_STATUS getStatus() const { return m_status; }
	void setStatus(SS_STATUS val);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSimpleSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	// ϣ������Э��ͷ
	void wantHeader();
	// ϣ����������
	void wantData(int dataLength);

protected:
	CSDTP m_sdtp;

// 	CByteBuffer m_buffer;
	CDataBuffer m_buffer;

	BOOL m_isHeadWanted;
	int m_dataWanted;

	SS_STATUS m_status;
};

class CSSDataArriveEvent : public IEvent
{
public:
	CSSDataArriveEvent(IEventRaisable *sender, string eventId, BYTE *data, int dataLength);
	virtual ~CSSDataArriveEvent();

	BYTE * getData() const { return m_data; }
	int getDataLength() const { return m_dataLength; }

private:
	BYTE *m_data;
	int m_dataLength;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLESOCKET_H__814A6119_BBDF_4C8C_8899_AEA0B07E0284__INCLUDED_)
