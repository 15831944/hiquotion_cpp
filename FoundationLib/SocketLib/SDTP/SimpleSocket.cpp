// SimpleSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleSocket

CSimpleSocket::CSimpleSocket()
: m_isHeadWanted(TRUE), m_dataWanted(SDTP_HEAD_LENGTH), m_status(SSS_NO_ACTION)
{
	AfxSocketInit();
	m_buffer.redimBufferLength(SS_RECEIVE_BUFFER_TOTAL_LENGTH);
}

CSimpleSocket::~CSimpleSocket()
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

void CSimpleSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	// �������Ҫ���գ�����Ե��������
	DWORD dwReceived;
	
	if (!IOCtl(FIONREAD, &dwReceived))
	{
		// Error handling here
		MessageBox(0, "��ȡ���յ������ݳ���ʱʧ�ܣ�", "", MB_OK);
		m_buffer.init();
		m_sdtp.init();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	if(dwReceived<=0)
	{
		m_buffer.init();
		m_sdtp.init();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	if(m_status==SSS_NO_ACTION)
	{
		m_buffer.init();
		m_sdtp.init();
		CSocket::OnReceive(nErrorCode);
		return;
	}

	// ������������Ȳ������򻺳�������һ�������ұ���ԭ��������
	if(m_buffer.getDataLength()+dwReceived>m_buffer.getBufferLength())
		m_buffer.redimBufferLength(max(m_buffer.getDataLength()+dwReceived, m_buffer.getBufferLength()) * 2, TRUE);

// 	char buf[SS_RECEIVE_BUFFER_LENGTH];
	char *buf=new char[dwReceived];
	DWORD sum=0;
// 	do 
// 	{
		// ��������
// 		int ret=Receive(buf, SS_RECEIVE_BUFFER_LENGTH);
		int ret=Receive(buf, dwReceived);
		if(ret>0)
		{
			// д������
			m_buffer.appendBytes(buf, ret);
// 			sum+=ret;
		}
// 	}
// 	while(sum<dwReceived);

	delete buf;

	// ������յ������ݱ�ϣ�����յ��������٣��򷵻أ������ȴ�
	if(m_buffer.getDataLength()<m_dataWanted)
	{
		CSocket::OnReceive(nErrorCode);
		return;
	}

	char *data=new char[m_buffer.getDataLength()];
	int len=m_buffer.getDataLength();
	m_buffer.readTotalData(data, len);
	// �����ϣ������Э��ͷ�����Э��ͷ��ʼд����������
	if(m_isHeadWanted)
		m_sdtp.setTotalData(data, m_buffer.getDataLength());
	// ������������׷������
	else
		m_sdtp.appendData(data, m_buffer.getDataLength());
	delete data;

	// �����ϣ������Э��ͷ
	if(m_isHeadWanted)
	{
		int datalen=0;
		// ��ȡЭ��ͷ�е����ݳ���
		m_sdtp.getDataLengthInHead(&datalen);
		// ���Э��ͷ�е����ݳ��ȷ���������Ըð����Ժ�İ�
		if(datalen<=0)
		{
			m_status=SSS_NO_ACTION;
			m_buffer.init();
			m_sdtp.init();
			CSocket::OnReceive(nErrorCode);
			return;
		}

		// Э��ͷ�������
// 		m_isHeadWanted=FALSE;
// 		m_dataWanted=datalen;
		wantData(datalen);
	}
// 	else
// 	{

	// ���������������ж�

		// ������յ������ݳ�����Э��ͷ�е����ݳ���һ�£����׳��¼�
		if(m_dataWanted<=m_sdtp.getDataLength())
		{
			wantHeader();

			int len=m_sdtp.getDataLength();
			char *data=new char[len];
			ZeroMemory(data, len);
			m_sdtp.getData(data);
			m_buffer.init();
			CSSDataArriveEvent e(this, "SSDataArrived", (BYTE *)data, len);
			DataArrived.raiseEvent(this, &e);
			delete data;
			m_buffer.init();
			m_sdtp.init();
		}
// 	}

	CSocket::OnReceive(nErrorCode);
}

int CSimpleSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!lpBuf)
		return -1;

	if(nBufLen<=0)
		return -2;

	m_sdtp.init();
	m_sdtp.genHead('s','d','t','p',1,0,0,0);
	m_sdtp.appendData((char *)lpBuf, nBufLen);
	m_sdtp.setCheckCodeInHead(m_sdtp.genCheckCode());
	m_sdtp.setDataLengthInHead(nBufLen);

	char *buf=new char[m_sdtp.getTotalDataLength()];
	m_sdtp.getTotalData(buf);

	int ret=CSocket::Send(buf, m_sdtp.getTotalDataLength(), nFlags);
	delete buf;
	return ret;
}

void CSimpleSocket::setBufferLength(int bufferLength)
{
	m_sdtp.setBufferLength(bufferLength);
}

void CSimpleSocket::setStatus(SS_STATUS val)
{
	m_status = val;
	if(m_status!=SSS_NO_ACTION)
		wantHeader();
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

// ϣ������Э��ͷ
void CSimpleSocket::wantHeader()
{
	m_isHeadWanted=TRUE;
	m_dataWanted=SDTP_HEAD_LENGTH;
}

// ϣ����������
void CSimpleSocket::wantData(int dataLength)
{
	if(dataLength<=0)
		return;

	m_isHeadWanted=FALSE;
	m_dataWanted=dataLength;
}



CSSDataArriveEvent::CSSDataArriveEvent(IEventRaisable *sender, string eventId, BYTE *data, int dataLength)
: IEvent(sender, eventId), m_data(data), m_dataLength(dataLength)
{
}

CSSDataArriveEvent::~CSSDataArriveEvent()
{
	
}
