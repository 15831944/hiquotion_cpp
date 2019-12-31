/*
IOCP Server v1.0
www.ipsky.net
*/

#include "iocpserver.h"

/************************************************************************/
/*                          ȫ�ֱ��� / ���� / ����                      */
/************************************************************************/
/*
�ص�����ָ��
*/
static PFUNC_OnConnected OnConnected;
static PFUNC_OnClosed OnClosed;
static PFUNC_OnError OnError;
static PFUNC_OnRecvCompleted OnRecvCompleted;
static PFUNC_OnSendCompleted OnSendCompleted;
static PFUNC_OnClientFree OnCltFree;
/*
�����������ͻ��˵�����
*/
static SOCKET sListen;
static unsigned int uiIP;
static unsigned short usPort;
static HANDLE hListenThread;
static HANDLE hCompletion;
static HANDLE hAcceptEvent;
static unsigned int uiWorkThread;
static LPFN_ACCEPTEX lpfnAcceptEx;
static LPFN_GETACCEPTEXSOCKADDRS lpfnGetAcceptExSockaddrs;

static CRITICAL_SECTION csAccept;	/*
									ͬ���� lAcceptPending �Ĳ���
									���ù� ::InterlockedXxx ϵ�к���
									�������� SIO ��С�� lAcceptPending ??? ���� ...
									*/
static long lInitAcceptNumber;
long lAcceptPending;

/*
�������е�������Clt
�������� / �Ͽ�����( closesocket )
*/
static Client *pConn;
static unsigned int uiConn;
static CRITICAL_SECTION csConn;
// SIO�Ļ���������
static unsigned int uiData;
// ��տ�1/2�������ʱ��
static unsigned int uiClearTime;
// ������CPU����
static unsigned int uiCPU;
// ��������������ǣ�0 / 1
static int iStart;

// ����ģ��ĵ��뺯��
extern void FreePool_Init(unsigned int uiDataLen,
				   unsigned int uiClearPerSec);
extern void FreePool_Free();
extern void FreePool_Clear();
extern unsigned int SIO_GetAllocNumber();
extern Client* Clt_Alloc(SOCKET sSocket);
extern void Clt_Free(Client *pClt);
extern unsigned int Clt_GetAllocNumber();

// ���uiDataΪ0�������AcceptEx�Ļ���������Ĭ�ϳ���Ϊ ACCEPTBUFLEN
#define ACCEPTBUFLEN 96
// ͬ����
#define LockClt(PCLT) ::EnterCriticalSection(&PCLT->csLock)
#define UnLockClt(PCLT) ::LeaveCriticalSection(&PCLT->csLock)
#define LockConn() ::EnterCriticalSection(&csConn)
#define UnLockConn() LeaveCriticalSection(&csConn)
#define LockAccept() ::EnterCriticalSection(&csAccept)
#define UnLockAccept() LeaveCriticalSection(&csAccept)

static std::string errMessage="";

std::string getErrMessage()
{
	return errMessage;
}

// ��չ�õ��ⲿ����
static void *ext=NULL;

void setExtData(void *extData)
{
	ext=extData;
}

/************************************************************************/
/*                                I/O ����                              */
/************************************************************************/
/*
Ͷ��һ��AcceptEx I/O����
����ɹ���ֵΪ IOCP_OK
ʧ�ܵĻ���ֵΪ IOCP_ERR ��sListen ���ر�ʱ����Ͷ��ʧ��
*/
int PostAccept(SynIO *pIO)
{
	errMessage="";
	
	DWORD dwBytes = 0;

	// IO����
	pIO->iIOType = IO_ACCEPT;
	// �����׽���
	pIO->sSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(INVALID_SOCKET != pIO->sSocket)
	{
		// Ͷ��AcceptEx����
		if(NO_ERROR != lpfnAcceptEx(sListen, 
			pIO->sSocket,
			pIO->pData, 
			0,
			sizeof(SOCKADDR_IN) + 16, 
			sizeof(SOCKADDR_IN) + 16, 
			&dwBytes, 
			&pIO->olIO))
		{
			// ����
			if(WSA_IO_PENDING != ::WSAGetLastError())
			{
				return IOCP_ERR;
			}
		}
	}
	else
	{
		// �����׽���ʧ�ܣ�����û�л���
		return IOCP_NOBUF;
	}

	return IOCP_OK;
}
/*
Ͷ��һ����������
������
pClt	�������ݵ��˿ͻ���
pData	���������ݵĻ�����
iLen	���ݵĳ��ȣ�ҪС��uiData����Ϊֻ����С�ڵ���uiData�����ݣ���������ݲ������ͣ�
��ֵ��
IOCP_ERR	����Ӧ��DisConn
IOCP_NOBUF	û���ڴ棺��1������SIOʧ��  ��2������WSASend�ǳ���IOCP_NOBUF����
IOCP_OK		Ͷ�ݳɹ�
*/
int PostSend(Client *pClt, char *pData, int iLen)
{
	errMessage="";
	
	SynIO *pIO = 0;

	// ����һ��SIO
	if(pIO = SIO_Alloc())
	{
		// uiDataΪ�գ���ʹ��pData�Ļ�������ַ
		// !!! pData ���ڴ治����PostSend���ʱ���ͷŻ��޸�
		if(0 == uiData)
		{
			pIO->pData = pData;
		}
		// uiData�ǿգ���pData���ڴ濽����SIO�Ļ�������
		else
		{
			iLen = (iLen > (int)uiData ? uiData : iLen);
			memcpy(pIO->pData, pData, iLen);
		}
		// ���ݵĳ���
		pIO->uiData = iLen;
		// Ͷ�ݳ���������
		switch(PostSend(pClt, pIO))
		{
			// Ͷ��Send IO�ɹ���IOCPģ�齫����OnSendCompleted�ص�����
		case IOCP_OK:
			break;
			// û���ڴ�WSAENOBUFS�������WSASendʹ��ϵͳ�ڲ����������е�4KB�ڴ��
		case IOCP_NOBUF:
			{
				SIO_Free(pIO);
				return IOCP_NOBUF;
			}
			// WSASend���ó���
		default:
			{
				SIO_Free(pIO);
				return IOCP_ERR;
			}
		}
	}
	else
	{
		return IOCP_NOBUF;
	}

	return IOCP_OK;
}
/*
Ͷ��һ����������
�����÷���PostSend����
*/
int PostRecv(Client *pClt, char *pData, int iLen)
{
	errMessage="";
	
	SynIO *pIO = 0;

	if(pIO = SIO_Alloc())
	{
		if(0 == uiData)
		{
			pIO->pData = pData;
		}
		pIO->uiData = (iLen > (int)uiData ? uiData : iLen);
		switch(PostRecv(pClt, pIO))
		{
		case IOCP_OK:
			break;
		case IOCP_NOBUF:
			{
				SIO_Free(pIO);
				return IOCP_NOBUF;
			}
		default:
			{
				SIO_Free(pIO);
				return IOCP_ERR;
			}
		}
	}
	else
	{
		return IOCP_NOBUF;
	}

	return IOCP_OK;
}
/*
Ͷ��һ�������������ֹ�����SIO�� pData / uiData
�˺�����Ϊ���ṩ���������ԣ�������OnRecvCompleted������SIO
*/
int PostSend(Client *pClt, SynIO *pIO)
{
	errMessage="";
	
	DWORD dwBytes = 0;
	DWORD dwFlags = 0;
	WSABUF wsaBuf = {0};

	// IO����
	pIO->iIOType = IO_SEND;
	// ��WSABUF
	wsaBuf.buf = pIO->pData;
	wsaBuf.len = pIO->uiData;

	// Ͷ�ݷ�������
	if(NO_ERROR != ::WSASend(pClt->sClient, 
								&wsaBuf, 
								1, 
								&dwBytes, 
								dwFlags, 
								&pIO->olIO, 
								NULL))
	{
		// ���Ͷ�ݳɹ�����ֵΪ NO_ERROR ��IOCPģ���ص�OnSendCompleted
		// ���Ͷ��ʧ�ܣ�WSAGetLastError() �� WSA_IO_PENDING ����˵�������ѹر�
		// �������IO��Ͷ��ʱ��ʧ�ܣ�û�н��е���ɶ˿ڵ�IO���У�����IOCPģ�鲻��Ϊ��SIO�ص�OnError��OnClosed
		switch(::WSAGetLastError())
		{
		case WSA_IO_PENDING:
			break;
		case WSAENOBUFS:
			return WSAENOBUFS;
		default:
			return IOCP_ERR;
		}
	}

	pClt->uiPendingSend ++;

	return IOCP_OK;
}
/*
Ͷ��һ��������
��PostSend����
*/
int PostRecv(Client *pClt, SynIO *pIO)
{
	errMessage="";
	
	DWORD dwBytes = 0;
	DWORD dwFlags = 0;
	WSABUF wsaBuf = {0};

	pIO->iIOType = IO_RECV;
	pIO->uiSeq = pClt->uiReadIOSeq;
	
	wsaBuf.buf = pIO->pData;
	wsaBuf.len = pIO->uiData;
	
	if(NO_ERROR != ::WSARecv(pClt->sClient, 
								&wsaBuf, 
								1, 
								&dwBytes, 
								&dwFlags, 
								&pIO->olIO, 
								NULL))
	{
		switch(::WSAGetLastError())
		{
		case WSA_IO_PENDING:
			break;
		case WSAENOBUFS:
			return WSAENOBUFS;
		default:
			return IOCP_ERR;
		}
	}
	
	pClt->uiPendingRecv ++;
	pClt->uiReadIOSeq ++;

	return IOCP_OK;
}
/*
�Ͽ���pClt������
�����ڻص������ڵ���
*/
void DisConn(Client *pClt)
{
	errMessage="";
	
	Client *pCur = 0 , *pBack = 0;
	// ����pConn������uiConn
	LockConn();
	// �ҳ�pClt��pConn��λ��
	for(pCur = pConn; pCur; )
	{
		if(pCur == pClt)
		{
			break;
		}
		pBack = pCur;
		pCur = pCur->pNext;
	}
	// ��pClt��pConn�жϿ�
	if(pCur)
	{
		(pBack ? pBack->pNext : pConn) = pCur->pNext;
		pCur->pNext = NULL;
		uiConn--;
	}
	// ���pClientû�йر��׽�������رգ�����λ���ֶΣ���ֹ��ε���DisConn  ...��
	if(INVALID_SOCKET != pClt->sClient)
	{
		::closesocket(pClt->sClient);
		pClt->sClient = INVALID_SOCKET;
		pClt->iState = CLT_DISC;
	}
	UnLockConn();
}

/************************************************************************/
/*                             ��������.�ڲ�����                        */
/************************************************************************/
// ����һ��AcceptEx��SIO
inline SynIO* AllocAcceptIO()
{
	errMessage="";
	
	SynIO *pIO = SIO_Alloc();
	if(pIO)
	{
		// ���uiDataΪ0�����ҪΪAcceptEx�Ļ���������һ���ڴ�
		if(0 == uiData)
		{
			pIO->pData = (char*)MemAlloc(ACCEPTBUFLEN);
			if(NULL == pIO->pData)
			{
				SIO_Free(pIO);
				return NULL;
			}
			pIO->uiData = ACCEPTBUFLEN;
		}
		// ���Ӽ�������ֹͣ��������ʱ����������Ͷ�ݵ�AcceptEx IO
		lAcceptPending++;
	}

	return pIO;
}
// �ͷ�һ��AcceptEx��SIO
inline void FreeAcceptIO(SynIO *pIO)
{
	errMessage="";
	
	if(pIO)
	{
		lAcceptPending--;
		if(0 == uiData)
		{
			MemFree(pIO->pData);
		}
		SIO_Free(pIO);
	}
}
// Ͷ��һ��AcceptEx����װ��AllocAcceptIO��ǰ���PostAccept
inline int PostAccept()
{
	errMessage="";
	
	SynIO *pIO = 0;

	if(pIO = AllocAcceptIO())
	{
		if(IOCP_OK == PostAccept(pIO))
		{
			return IOCP_OK;
		}
		else
		{
			FreeAcceptIO(pIO);
		}
	}

	return IOCP_ERR;
}
// ��pConn�������һ���µ�pClt
inline void AddConn(Client *pClt)
{
	errMessage="";
	
	LockConn();
	pClt->pNext = pConn;
	pConn = pClt;
	uiConn++;
	UnLockConn();
}
// ���pClt�����Ͽ����е�����
inline void DisConnAll()
{
	errMessage="";
	
	LockConn();
	while(pConn)
	{
		// �ر�
		if(INVALID_SOCKET != pConn->sClient)
		{
			::closesocket(pConn->sClient);
			pConn->sClient = INVALID_SOCKET;
		}
		pConn->iState = CLT_DISC;
		// ��һ��Clt
		pConn = pConn->pNext;
	}
	uiConn = 0;
	UnLockConn();
}

/************************************************************************/
/*                             �߳�                                     */
/************************************************************************/
// ��RecvIO���ʱ�������򣬵��ô˺����󣬷���һ��������IO����
inline SynIO* SortReadIO(Client *pClt, SynIO *pIO)
{
	errMessage="";
	
	// �Զ�I/O��������
	for(SynIO *pCur = pClt->pReadIO, *pBack = 0; pCur; )
	{
		if(pCur->uiSeq > pIO->uiSeq)
		{
			break;
		}
		pBack = pCur;
		pCur = pCur->pNext;
	}
	if(pBack)
	{
		pIO->pNext = pBack->pNext;
		pBack->pNext = pIO;
	}
	else
	{
		pIO->pNext = pClt->pReadIO;
		pClt->pReadIO = pIO;
	}
	// ��ȡ���а�����ɵĶ�IO
	for(pCur = pClt->pReadIO, pBack = NULL, pIO = NULL; pCur; )
	{
		// ��û�а���Ķ�IO
		if(pCur->uiSeq != pClt->uiReadSeq)
		{
			// pBackָ��������һ������Ķ�IO
			if(pBack)
			{
				pBack->pNext = NULL;
			}
			break;
		}
		// pIOΪ�����IO������׽��
		if(NULL == pIO)
		{
			pIO = pClt->pReadIO;
		}
		// ���û�����������������Ϣ
		pClt->pReadIO = pCur->pNext;
		pBack = pCur;
		pCur = pClt->pReadIO;
		pClt->uiReadSeq++;
	}

	return pIO;
}

// �����߳�
DWORD WINAPI WorkThread(LPVOID lp)
{
	errMessage="";

	// ��ɶ˿ں���
	BOOL bRet;
	SynIO *pIO;
	Client *pClt;
	DWORD dwTrans;
	// ��һ��IO�� ��������Ķ�IO / �ͷ�����Ķ�IO ��
	SynIO *pNextIO;
	// �˳���
	DWORD dwRetCode = IOCP_ERR;
	// AcceptEx���ȡ�׽�����Ϣ
	int nLocalLen, nRmoteLen;
	LPSOCKADDR pLocalAddr, pRemoteAddr;

	while(1)
	{
		// �ȴ�ϵͳ����I/O��ɻ������ط�����PostQueuedCompletionStatus
		bRet = ::GetQueuedCompletionStatus(hCompletion, 
			&dwTrans, 
			(LPDWORD)&pClt, 
			(LPOVERLAPPED*)&pIO, 
			WSA_INFINITE);

		// ���ڳ�ʱ����Ϊ WSA_INFINITE ���Է�ֵ�����֣�0���������0
		if(bRet)
		{
			// ֻ��PostQueuedCompletionStatus(hCompletion, -1, 0, NULL)�ŷ��Ϳ�I/O
			if(pIO)
			{
				if(IO_ACCEPT != pIO->iIOType)
				{
					// �������Ѵ�����ֽ���
					pIO->uiTrans = dwTrans;
					// ����pClt !!!
					LockClt(pClt);
					// Recv IO
					if(IO_RECV == pIO->iIOType)
					{
						// IO��������1
						pClt->uiPendingRecv--;
						// ����dwTrans�ֽڵ�����
						if(dwTrans)
						{
							// ����
							pIO = SortReadIO(pClt, pIO);
							// �����ύ
							for(; pIO; )
							{
								pNextIO = pIO->pNext;
								// �ص���pIO���ͷŲ����ɻص��������
								if(OnRecvCompleted)
									OnRecvCompleted(pClt, pIO);
								// ������յ�ʱ���ⲿ����DisConn()�Ͽ�����
								if(CLT_DISC == pClt->iState)
								{
									// �ͷ���ʣ����������IO
									for(pIO = pNextIO; pIO; )
									{
										pNextIO = pIO->pNext;
										SIO_Free(pIO);
										pIO = pNextIO;
									}
									// ����Ƿ�����ͷ�Clt
									goto ONFREE;
								}
								pIO = pNextIO;
							}
						}
						// �׽����ѱ��رգ�2���ͻ��˹ر��׽��֣�
						else
						{
ONCLOSED:
							// ֪ͨ�ϲ������ѹر�
							if(OnClosed)
								OnClosed(pClt, pIO);
ONFREE:
							// ���δ�ر��׽�������ر�
							if(CLT_CONN == pClt->iState)
							{
								DisConn(pClt);
							}
							// �����û��δ��I/O���ͷ�Clt
							if(0 == pClt->uiPendingRecv && 0 == pClt->uiPendingSend)
							{
								// �ͷŵ�����Ķ�IO
								for(pIO = pClt->pReadIO; pIO; )
								{
									pNextIO = pIO->pNext;
									SIO_Free(pIO);
									pIO = pNextIO;
								}
								// ������Clt�п���û�б��ͷ��ڴ棬�´����õ�ʱ������������
								UnLockClt(pClt);
								// ֪ͨ�ϲ�pClt�����ͷŵ��������ٶԴ��ڴ�����κβ���
								if(OnCltFree)
								{
									OnCltFree(pClt);
								}
								// ����Cltģ����ͷź���
								Clt_Free(pClt);
								// �����ȴ�IO���
								continue;
							}
						}
					}
					else
					{
						pClt->uiPendingSend--;
						if(dwTrans)
						{
							if(OnSendCompleted)
								OnSendCompleted(pClt, pIO);
							if(CLT_DISC == pClt->iState)
							{
								goto ONFREE;
							}
						}
						else
						{
							goto ONCLOSED;
						}
					}
					UnLockClt(pClt);
				}
				else
				{
					// ����Client������sClient������sListen��ͬ
					// AcceptEx ���Զ��̳� sListen �׽��ֵ�����
					if((pClt = Clt_Alloc(pIO->sSocket)) &&
						(SOCKET_ERROR != ::setsockopt( pIO->sSocket,
						SOL_SOCKET,
						SO_UPDATE_ACCEPT_CONTEXT,
						(char*)&sListen,
						sizeof(sListen))))
					{
						// ���ÿͻ��˵���չ�����ֶ�
						pClt->pExt=ext;

						// ��ӵ���������
						AddConn(pClt);
						// ��ȡ���ӵ���Ϣ
						lpfnGetAcceptExSockaddrs(
							pIO->pData,
							0,
							sizeof(sockaddr_in) + 16,
							sizeof(sockaddr_in) + 16,
							(SOCKADDR **)&pLocalAddr,
							&nLocalLen,
							(SOCKADDR **)&pRemoteAddr,
							&nRmoteLen);
						memcpy(&pClt->saServer, pLocalAddr, nLocalLen);
						memcpy(&pClt->saClient, pRemoteAddr, nRmoteLen);
						// ���ͻ����׽��ֹ�������ɶ˿�
						::CreateIoCompletionPort((HANDLE)pClt->sClient, hCompletion, (DWORD)pClt, 0);
						LockClt(pClt);
						// ֪ͨ�ϲ�
						if(OnConnected)
							OnConnected(pClt);
						// �ϴιرմ�����
						if(CLT_DISC == pClt->iState)
						{
							goto ONFREE;
						}
						UnLockClt(pClt);
					}
					// ����Cltʧ�ܻ����������׽�������ʧ��
					else
					{
						::closesocket(pIO->sSocket);
						if(pClt)
						{
							Clt_Free(pClt);
						}
					}
					// ���δ�ﵽ lInitAcceptNumber���ޣ��ٴ�Ͷ��һ��AcceptEx IO
					LockAccept();
					if(lAcceptPending > lInitAcceptNumber || 
						IOCP_OK != PostAccept(pIO))
					{
						FreeAcceptIO(pIO);
					}
					UnLockAccept();
				}
			}
			// �˳�
			else
			{
				dwRetCode = IOCP_OK;
				break;
			}
		}
		// ???����
		else
		{
			// ʧ�ܵ�I/O����
			if(pIO)
			{
				// WSARecv / WSASend Ͷ�ݵ�I/O����2�����������ر��׽��֣�
				if(IO_ACCEPT != pIO->iIOType)
				{
					// ����pClt
					LockClt(pClt);
					// I/O��������1
					if(IO_RECV == pIO->iIOType)
					{
						pClt->uiPendingRecv--;
					}
					else
					{
						pClt->uiPendingSend--;
					}
					// ֪ͨ�ϲ�
					if(OnError)
						OnError(pClt, pIO, ::GetLastError());
					// �����ͷŴ������
					goto ONFREE;
				}
				// AcceptEx���� ��sListen ���ر�
				// �������˳��߳� ��������Listen�߳���������е�δ��AcceptEx
				else
				{
					::closesocket(pIO->sSocket);
					LockAccept();
					FreeAcceptIO(pIO);
					UnLockAccept();
				}
			}
			// ?Ϊ��...ʲô���??
			else
			{
				;
			}
		}
	}

	return dwRetCode;
}

// �����߳�
DWORD WINAPI ListenThread(LPVOID lp)
{
	errMessage="";
	
	unsigned int ui = 0;
	SynIO *pIO = 0;
	HANDLE hWaitEvents[1 + 512] = {0};
	int nEventCount = 0;
	WSANETWORKEVENTS wsaEvent = {0};

	// ��ʼ��lAcceptPending
	lAcceptPending = 0;
	// Ͷ��lInitAcceptNumber��Accept I/O
	LockAccept();
	for(ui = 0; ui < (unsigned int)lInitAcceptNumber; ui++)
	{
		PostAccept();
	}
	UnLockAccept();
	// ���ɹ����߳�
	hWaitEvents[nEventCount ++] = hAcceptEvent;
	for(ui = 0; ui < uiWorkThread; ui++)
	{
		hWaitEvents[nEventCount ++] = ::CreateThread(NULL, 0, WorkThread, 0, 0, NULL);
	}
	// �ȴ�hAcceptEvent���˳�֪ͨ
	while(1)
	{
		ui = ::WSAWaitForMultipleEvents(nEventCount, hWaitEvents, FALSE, 30000, FALSE);
		if(0 == iStart || WSA_WAIT_FAILED == ui)
		{
			// �رռ����׽���
			::closesocket(sListen);
			// �ȴ����е�AcceptEx IO���������ͷ�
			while(lAcceptPending)
			{
				::Sleep(10);
			}
			// �Ͽ����е�����
			DisConnAll();
			while(Clt_GetAllocNumber())
			{
				::Sleep(10);
			}
			// ֪ͨ�����߳��˳�
			for(ui = 1; (int)ui < nEventCount; ui++)
			{
				::PostQueuedCompletionStatus(hCompletion, -1, 0, NULL);
			}
			// �ȴ����е�I/O�����߳��˳�
			::WaitForMultipleObjects(nEventCount - 1, &hWaitEvents[1], TRUE, INFINITE);
			// �ر������̵߳ľ��
			for(ui = 1; (int)ui < nEventCount; ui++)
			{	
				::CloseHandle(hWaitEvents[ui]);
			}
			// �ر���ɶ˿ڵľ��
			::CloseHandle(hCompletion);
			// �˳�
			ui = IOCP_OK;
			break;
		}
		if(WSA_WAIT_TIMEOUT == ui)
		{
			// �ͷŵ����г�һ��ı���
			FreePool_Clear();
			// ..
		}
		else
		{
			ui -= WAIT_OBJECT_0;
			if(0 == ui)
			{
				::WSAEnumNetworkEvents(sListen, hWaitEvents[ui], &wsaEvent);
				// hAcceptEvent���ţ��¼�ΪFD_ACCEPT��Ͷ�ݵ�Accept I/O������
				if(wsaEvent.lNetworkEvents & FD_ACCEPT)
				{
					// ���ﲻ����lInitAcceptNumberÿ������10��AcceptEx����Ϊ�������µ�����
					// ��WorkThread����lInitAcceptNumber����Ϊ�˷�ֹ���Ƶ�Accept IO����
					LockAccept();
					for(ui = 0; ui < 10; ui++)
					{
						PostAccept();
					}
					UnLockAccept();
				}
			}
			else
			{
				// �����߳��˳����д�������ֹͣ������
				iStart = 0;
				continue;
			}
		}
	}

	return ui;
}

/************************************************************************/
/*                            ģ��Ŀ��ƺ���                            */
/************************************************************************/
int IOCP_Init(PFUNC_OnConnected fConnected,
			  PFUNC_OnClosed fClosed,
			  PFUNC_OnError fErr,
			  PFUNC_OnRecvCompleted fRecv,
			  PFUNC_OnSendCompleted fSend,
			  PFUNC_OnClientFree fCltFree,
			  unsigned int uiDataLen,
			  unsigned int uiClearPerSec)
{
	errMessage="";

	// ��ȡCPU������
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	uiCPU = SystemInfo.dwNumberOfProcessors;

	// ��ʼ��WinSock2.2
	WSADATA wsaData = {0};
	WORD sockVersion = MAKEWORD(2, 2);
	int ret=::WSAStartup(sockVersion, &wsaData);
	if(ret!=0)
	{
		switch(ret)
		{
		case WSASYSNOTREADY:
			errMessage="WSAStartup ����ʧ�ܣ�����ͨ��������������ϵͳ��û��׼����";
			break;
		case WSAVERNOTSUPPORTED:
			errMessage="WSAStartup ����ʧ�ܣ������Windows Sockets API�İ汾δ���ض���Windows Socketsʵ���ṩ������Ҫ Windows Sockets �汾Ϊ 2.0��";
			break;
		case WSAEINVAL:
			errMessage="WSAStartup ����ʧ�ܣ�Ӧ�ó���ָ����Windows Sockets�汾��2.0��������DLL֧��";
			break;
		}
		return IOCP_ERR;
	}

	if(LOBYTE(wsaData.wVersion) < 2 || HIBYTE(wsaData.wVersion) < 2)//�жϰ汾�ţ��Ƿ�Ͷ����һ��
	{
		errMessage="Windows Sockets �İ汾���� 2.0";
		WSACleanup();   //�������⣬ж��֧�֣����������򷵻�-1
		return IOCP_ERR;
	}
	
	// Ϊ�ص�������ֵ
	OnConnected = fConnected;
	OnClosed = fClosed;
	OnError = fErr;
	OnRecvCompleted = fRecv;
	OnSendCompleted = fSend;
	OnCltFree = fCltFree;

	// ��ʼ��FreePool
	uiData = uiDataLen;
	uiClearTime = uiClearPerSec;
	FreePool_Init(uiData, uiClearTime);

	// Ϊ�����߳������¼����󣬵�Ͷ�ݵ�AcceptEx����ʱ�õ�֪ͨ
	hAcceptEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	if(!hAcceptEvent)
	{
		int errNo=GetLastError();
		std::stringstream ss;
		ss << "�����¼�����ʧ�ܣ�Windows ������Ϊ" << errNo;
		errMessage=ss.str();
		return IOCP_ERR;
	}

	// ��ʼ��csConn
	::InitializeCriticalSection(&csConn);
	pConn = NULL;
	uiConn = 0;
	//
	::InitializeCriticalSection(&csAccept);

	// 2016.4.21  -  hiquotion
	// �����´�����ɶ˿ڶ���Ĵ��룬�ƶ�����ʼ��������

	// ������ɶ˿ڶ���
	hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if(!hCompletion)
	{
		errMessage="������ɶ˿�ʧ�ܣ�";
		return IOCP_ERR;
	}

	return IOCP_OK;
}

int IOCP_Free()
{
	errMessage="";
	
	// ����ֹͣ����
	IOCP_Shutdown();
	// �ر�FreePoolģ��
	FreePool_Free();
	// �ͷ�WinSock�����Դ
	::WSACleanup();
	// �ر��¼�������
	::CloseHandle(hAcceptEvent);
	//
	::DeleteCriticalSection(&csConn);
	::DeleteCriticalSection(&csAccept);

	return IOCP_OK;
}

int IOCP_Start(const char *IP, 
			   unsigned short Port,
			   long InitAcceptNumber,
			   unsigned int uiThread,
			   unsigned long KeepAlive)
{
	errMessage="";

	// ����Ƿ�������
	if(iStart)
	{
		errMessage="�����Ѿ�����";
		return IOCP_OK;
	}

	// ��ʼͶ�ݵ�Accept������
	lInitAcceptNumber = InitAcceptNumber;
	// ��ʼ������󶨵ĵ�ַ��Ϣ
	SOCKADDR_IN si = {0};
	si.sin_family = AF_INET;
	si.sin_port = ::ntohs(Port);
	si.sin_addr.S_un.S_addr = ::inet_addr(IP);

	// ���ɼ����׽���
	sListen = ::WSASocket(AF_INET, 
		SOCK_STREAM, 
		0, 
		NULL, 
		0, 
		WSA_FLAG_OVERLAPPED);

	// KeepAlive
	if(KeepAlive)
	{
		#define SIO_KEEPALIVE_VALS IOC_IN | IOC_VENDOR | 4
		struct
		{
			unsigned long OnOff;
			unsigned long KeepAliveTime;
			unsigned long KeepAliveInterval;
		}ka = {0};
		unsigned long ulRet = 0;
		ka.OnOff = 1;						// ����KeepAlive
		ka.KeepAliveTime = KeepAlive * 1000;// ms. ��ʱʱ�䣨����ms������������
		ka.KeepAliveInterval = 5000;		// ms. Resend if No-Reply�����һ��KeepAlive��û����Ӧ�������ms������һ����
		if(SOCKET_ERROR == ::WSAIoctl(sListen, SIO_KEEPALIVE_VALS, &ka, sizeof(ka), NULL, 0, &ulRet, 0, NULL))
		{
			int errNo=WSAGetLastError();
			std::stringstream ss;
			ss << "Ϊʵ�� KeepAlive ����֧��ʱ������ WSAIoctl ʧ�ܣ�Windows ������Ϊ " << errNo;
			errMessage=ss.str();
			std::string errmsg="";
			switch(errNo)
			{
			case WSANOTINITIALISED:
				errmsg="�ڵ��ñ�API֮ǰӦ�ɹ�����WSAStartup()";
				break;
			case WSAENETDOWN:
				errmsg="������ϵͳʧЧ";
				break;
			case WSAEINVAL:
				errmsg="cmd����һ���Ϸ����������һ����������Ƿ�������������ڸ������͵��׽ӿڲ�����";
				break;
			case WSAEINPROGRESS:
				errmsg="��һ���ص���������ʱ�����˸ú���";
				break;
			case WSAENOTSOCK:
				errmsg="�����ֲ���һ���׽ӿ�";
				break;
			case WSAEOPNOTSUPP:
				errmsg="ָ����ioctl�����޷�ʵ�֣�������SIO_SET_QOS�� SIO_SET_GROUP_QOS��ָ�����������޷�ʵ��";
				break;
			case WSA_IO_PENDING:
				errmsg="һ���ص��������ɹ����������󽫱���������";
				break;
			case WSAEWOULDBLOCK:
				errmsg="�׽ӿڱ�־Ϊ���������������������������";
				break;
			}
			errMessage+="(" + errmsg + ")";
			::closesocket(sListen);
			sListen = INVALID_SOCKET;
			return IOCP_ERR;
		}
	}

	// ���׽����뱾�ص�ַ��
	if(SOCKET_ERROR == ::bind(sListen, (sockaddr*)&si, sizeof(si)))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "socket ��ʧ�ܣ�Windows ������Ϊ " << errNo;
		errMessage=ss.str();
		std::string errmsg="";
		switch(errNo)
		{
		case WSANOTINITIALISED:
			errmsg="��ʹ�ô�API֮ǰӦ���ȳɹ��ص���WSAStartup()";
			break;
		case WSAENETDOWN:
			errmsg="������ϵͳʧЧ";
			break;
		case WSAEADDRINUSE:
			errmsg="���󶨶˿�����ʹ���У��μ�setoption()�е�SO_REUSEADDRѡ�";
			break;
		case WSAEFAULT:
			errmsg="namelen����̫С��С��sockaddr�ṹ�Ĵ�С��";
			break;
		case WSAEINPROGRESS:
			errmsg="һ���������׽ӿڵ�������������";
			break;
		case WSAEAFNOSUPPORT:
			errmsg="��Э�鲻֧����ָ���ĵ�ַ��";
			break;
		case WSAEINVAL:
			errmsg="���׽ӿ�����һ����ַ����";
			break;
		case WSAENOBUFS:
			errmsg="���㹻���û����������ӹ���";
			break;
		case WSAENOTSOCK:
			errmsg="�����ֲ���һ���׽ӿ�";
			break;
		}
		errMessage+="(" + errmsg + ")";
		::closesocket(sListen);
		sListen = INVALID_SOCKET;
		return IOCP_ERR;
	}

	// ��ʼ����
	if(SOCKET_ERROR == ::listen(sListen, SOMAXCONN))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "socket ����ʧ�ܣ�Windows ������Ϊ " << errNo;
		errMessage=ss.str();
		std::string errmsg="";
		switch(errNo)
		{
		case WSANOTINITIALISED:
			errmsg="��ʹ�ô�API֮ǰӦ���ȳɹ��ص���WSAStartup()";
			break;
		case WSAENETDOWN:
			errmsg="������ϵͳʧЧ";
			break;
		case WSAEADDRINUSE:
			errmsg="���󶨶˿�����ʹ���У��μ�setoption()�е�SO_REUSEADDRѡ�";
			break;
		case WSAEINPROGRESS:
			errmsg="һ���������׽ӿڵ�������������";
			break;
		case WSAEINVAL:
			errmsg="���׽ӿ�����һ����ַ����";
			break;
		case WSAEISCONN:
			errmsg="�׽ӿ��ѱ�����";
			break;
		case WSAEMFILE:
			errmsg="�޿����ļ�������";
			break;
		case WSAENOBUFS:
			errmsg="���㹻���û����������ӹ���";
			break;
		case WSAENOTSOCK:
			errmsg="�����ֲ���һ���׽ӿ�";
			break;
		case WSAEOPNOTSUPP:
			errmsg="����listen()ʱ�����׽ӿڲ�����";
			break;
		}
		errMessage+="(" + errmsg + ")";
		::closesocket(sListen);
		sListen = INVALID_SOCKET;
		return IOCP_ERR;
	}

	// 2016.4.21  -   hiquotion
	// ������ע�Ͳ��֣��ƶ��� Init ������

// 	// ������ɶ˿ڶ���
// 	hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 
// 		0, 
// 		0, 
// 		0);
	if(!hCompletion)
	{
		errMessage="��ɶ˿ھ��Ϊ�գ����ȵ��� IOCP_INIT ��������ɶ˿�";
		return IOCP_ERR;
	}

	// �������׽��ֹ�������ɶ˿�
	if(!::CreateIoCompletionPort((HANDLE)sListen, hCompletion, (DWORD)0, 0))
	{
		errMessage="���� CreateIoCompletionPort() ʹ��ɶ˿ں��׽��ְ�ʱ���ִ���";
		return IOCP_ERR;
	}

	/*
	AcceptEx()������Winsock2�ܹ�֮�⣬ÿ�ε���ʱ��������ͨ��WSAIoctl()ȡ�ú���ָ��
	Ϊ�˱�������ܵ�Ӱ�죬�ֹ�����WSAIoctl������AcceptEx��GetAcceptExSockaddrs
	*/
	// ����AcceptEx
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	DWORD dwBytes = 0;
	if(SOCKET_ERROR == ::WSAIoctl(sListen, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx, 
		sizeof(GuidAcceptEx), &lpfnAcceptEx, sizeof(lpfnAcceptEx), &dwBytes, NULL, NULL))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "ȡ lpfnAcceptEx ����ָ��ʱ������ WSAIoctl ʧ�ܣ�Windows ������Ϊ " << errNo;
		errMessage=ss.str();
		return IOCP_ERR;
	}

	// ����GetAcceptExSockaddrs
	GUID GuidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
	if(SOCKET_ERROR == ::WSAIoctl(sListen, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidGetAcceptExSockaddrs,
		sizeof(GuidGetAcceptExSockaddrs), &lpfnGetAcceptExSockaddrs, sizeof(lpfnGetAcceptExSockaddrs), &dwBytes, NULL, NULL))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "ȡ lpfnGetAcceptExSockaddrs ����ָ��ʱ������ WSAIoctl ʧ�ܣ�Windows ������Ϊ " << errNo;
		errMessage=ss.str();
		return IOCP_ERR;
	}

	/*
	ע��FD_ACCEPT�¼���
	���Ͷ�ݵ�AcceptEx I/O�������̻߳���յ�FD_ACCEPT�����¼���
	˵��Ӧ��Ͷ�ݸ����AcceptEx I/O
	*/
	if(SOCKET_ERROR == WSAEventSelect(sListen, hAcceptEvent, FD_ACCEPT))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "Ϊʵ�֡�Ͷ�ݵ�AcceptEx I/O�������¼�֪ͨ��ʱ������ WSAEventSelect ����ʧ�ܣ�Windows ������Ϊ " << errNo;
		errMessage=ss.str();
		return IOCP_ERR;
	}

	// �����߳���
	uiWorkThread = (uiThread ? uiThread : 4 * uiCPU);
	// ���������߳�
	hListenThread = ::CreateThread(NULL, 0, ListenThread, 0, 0, NULL);
	if(!hListenThread)
	{
		errMessage="���������߳�ʧ�ܣ�";
		return IOCP_ERR;
	}

	// OK.
	iStart = 1;

	return IOCP_OK;
}

int IOCP_Shutdown()
{
	errMessage="";
	
	if(!iStart)
	{
		return IOCP_OK;
	}
	// ֪ͨ�����߳�
	iStart = 0;
	::SetEvent(hAcceptEvent);
	// �ȴ������߳��˳�
	::WaitForSingleObject(hListenThread, INFINITE);
	::CloseHandle(hListenThread);
	hListenThread = NULL;

	return IOCP_OK;
}

unsigned int IOCP_GetConnNumber()
{
	errMessage="";
	
	return uiConn;
}

