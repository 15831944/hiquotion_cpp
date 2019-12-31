// SimpleSocket.cpp : implementation file
//

#include "stdafx.h"
#include "EventSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleSocket

CEventSocket::CEventSocket()
{
	AfxSocketInit();
	m_buffer.redimBufferSize(SS_RECEIVE_BUFFER_TOTAL_LENGTH);
}

CEventSocket::~CEventSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSimpleSocket, CSocket)
	//{{AFX_MSG_MAP(CSimpleSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSimpleSocket member functions

void CEventSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	// �������Ҫ���գ�����Ե��������
	DWORD dwReceived;
	
	if (!IOCtl(FIONREAD, &dwReceived))
	{
		// Error handling here
		MessageBox(0, "��ȡ���յ������ݳ���ʱʧ�ܣ�", "", MB_OK);
		m_buffer.clearData();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	if(dwReceived<=0)
	{
		m_buffer.clearData();
		m_sdtp.init();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	// ������������Ȳ������򻺳�������һ�������ұ���ԭ��������
	if(m_buffer.getDataLength()+dwReceived>m_buffer.getBufferLength())
		m_buffer.redimBufferSize(max(m_buffer.getDataLength()+dwReceived, m_buffer.getBufferLength()) * 2, TRUE);

	char buf[SS_RECEIVE_BUFFER_LENGTH];
	DWORD sum=0;
	do 
	{
		// ��������
		int ret=Receive(buf, SS_RECEIVE_BUFFER_LENGTH);
		if(ret>0)
		{
			// д������
			m_buffer.append((BYTE *)buf, ret);
			sum+=ret;
		}
	}
	while(sum<dwReceived);

	char *data=new char[m_buffer.getDataLength()];
	int len=0;
	m_buffer.getTotalData((BYTE *)data, &len);

		int datalen=0;
		// ��ȡЭ��ͷ�е����ݳ���
		m_sdtp.getDataLengthInHead(&datalen);
		// ���Э��ͷ�е����ݳ��ȷ���������Ըð����Ժ�İ�
		if(datalen<=0)
		{
			m_status=SSS_NO_ACTION;
			m_buffer.clearData();
			m_sdtp.init();
			CSocket::OnReceive(nErrorCode);
			return;
		}

		// Э��ͷ�������
// 		m_isHeadWanted=FALSE;
// 		m_dataWanted=datalen;
	}
// 	else
// 	{

	// ���������������ж�

		// ������յ������ݳ�����Э��ͷ�е����ݳ���һ�£����׳��¼�
			char *data=new char[len];
			ZeroMemory(data, len);
			m_buffer.clearData();
			CSSDataArriveEvent e(this, "SSDataArrived", (BYTE *)data, len);
			DataArrived.raiseEvent(this, &e);
			delete data;
			m_buffer.clearData();
			m_sdtp.init();
// 	}

	CSocket::OnReceive(nErrorCode);
}

void CSimpleSocket::setBufferLength(int bufferLength)
{
	m_sdtp.setBufferLength(bufferLength);
}

void CSimpleSocket::setStatus(SS_STATUS val)
{
	m_status = val;
}

void CSimpleSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_status=SSS_NO_ACTION;

	CSocket::OnClose(nErrorCode);
}

void CSimpleSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	setStatus(SSS_RECEIVE_DATA);

	CSocket::OnConnect(nErrorCode);
}
int CSimpleSocket::sendString(CString &msg)
{
	if(msg=="")
		return -1;

	return Send((LPTSTR)(LPCSTR)msg, msg.GetLength());
}



CSSDataArriveEvent::CSSDataArriveEvent(IEventRaisable *sender, string eventId, BYTE *data, int dataLength)
: IEvent(sender, eventId), m_data(data), m_dataLength(dataLength)
{
}

CSSDataArriveEvent::~CSSDataArriveEvent()
{
	
}
