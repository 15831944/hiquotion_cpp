// IOCP.h: interface for the CIOCP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOCP_H__A0545D7D_A081_40DF_8CE3_8E78AC6222CA__INCLUDED_)
#define AFX_IOCP_H__A0545D7D_A081_40DF_8CE3_8E78AC6222CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BOOL int
#define TRUE 1
#define FALSE 0

void Connected(Client *pClt);
void Closed(Client* pClt, SynIO* pIO);
void Error(Client* pClt, SynIO* pIO, int iErr);
void RecvCompleted(Client* pClt, SynIO* pIO);
void SendCompleted(Client* pClt, SynIO* pIO);
void CltFree(Client *pClt);

class CIOCP  
{
public:
	CIOCP();
	virtual ~CIOCP();

	// ��ʼ��IOCPģ��
	BOOL init(unsigned int uiDataLen = 4096,		/*
													����0֮��
													ֻҪͶ��WSASend/WSARecv����ֵΪWSA_IO_PENGDING
													ϵͳ����ΪIO����4KB���ڴ�
													���Խ�IO�Ļ���������Ϊ4KB
													*/
			  unsigned int uiClearPerSec = 30		/* ����s�Կ����������һ������ */
		);

	// ����IOCP������
	BOOL start(unsigned short Port = 15100,			/* ����˿� */
			long InitAcceptNumber = 30,			/* ��ʼ��Ͷ�ݶ��ٸ�AcceptEx �������������Ͷ��ά���������Χ�� */
			unsigned int uiThread = 0,			/* IOCP���߳��� �� Ĭ��Ϊ 4 * CPU */
			unsigned long KeepAlive = 60			/* ����s���һ��������� : KeepAlive */
		);

	// ֹͣIOCP������
	int IOCP_Shutdown();

	// �ͷ�IOCPģ�����Դ
	int IOCP_Free();

	// ��ȡ��ǰ��������
	unsigned int IOCP_GetConnNumber();

	// �ڲ��¼�֪ͨ�����ڸ����ڲ��Ĵ��������ڲ���¼��־�ȣ���֮��������Ӧ���ⲿ�¼�֪ͨ
	void InConnected(Client *pClt);
	void InClosed(Client* pClt, SynIO* pIO);
	void InError(Client* pClt, SynIO* pIO, int iErr);
	void InRecvCompleted(Client* pClt, SynIO* pIO);
	void InSendCompleted(Client* pClt, SynIO* pIO);
	void InClientFree(Client *pClt);


	// �ⲿ�¼�֪ͨ���û�����̳�
	virtual void OnConnected(Client *pClt);
	virtual void OnClosed(Client* pClt, SynIO* pIO);
	virtual void OnError(Client* pClt, SynIO* pIO, int iErr);
	virtual void OnRecvCompleted(Client* pClt, SynIO* pIO);
	virtual void OnSendCompleted(Client* pClt, SynIO* pIO);
	virtual void OnClientFree(Client *pClt);

};

#endif // !defined(AFX_IOCP_H__A0545D7D_A081_40DF_8CE3_8E78AC6222CA__INCLUDED_)
