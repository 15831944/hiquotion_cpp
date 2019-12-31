/*
IOCP Server v1.0
www.ipsky.net
*/

#ifndef ___IOCPSERVER
#define ___IOCPSERVER

#include <string>
#include <sstream>

// ������ֵ������
#include "iocpret.h"
// WinSock2�ĺ���
#include <winsock2.h>
// LPFN_ACCEPTEX ��WinSock2����չ����
#include <Mswsock.h>
// WinSock2�ĺ����⣬�������ء�Mswsock���Ŀ⣬�ֶ�������չ����
#pragma comment(lib, "ws2_32")

// ȥ���ṹ�嶨��Ϊ0���ȵ����ݾ���
// warning C4200: nonstandard extension used : zero-sized array in struct/union
#pragma warning(disable:4200)

// �ڴ����
const HANDLE hCurrentProcess = ::GetProcessHeap();
#define MemAlloc(LEN) ::HeapAlloc(hCurrentProcess, HEAP_ZERO_MEMORY, LEN)
#define MemFree(P) ::HeapFree(hCurrentProcess, 0, P)

// IO���ͣ���������/��������/��������
#define IO_ACCEPT	1
#define IO_RECV		2
#define IO_SEND		3

// Clt״̬���ѱ��ͷ�/����/�ѹر�
#define CLT_FREE	0
#define CLT_CONN	1
#define CLT_DISC	-1

typedef struct _SynIO
{
	WSAOVERLAPPED olIO;			/* ��ɶ˿�ģ�ͱ���Ľṹ�� */
	struct _SynIO *pNext;		/* ��һ��I/O */
	void *pExt;					/* ��չ�� */
	SOCKET sSocket;				/* I/O��Ӧ���׽��� */
	char *pData;				/* PostXxx()ʱ������������ݻ����� */
	unsigned int uiData;		/* PostXxx()ʱ�����������ݵĳ��� */
	unsigned int uiTrans;		/* �Ѵ�����ֽ��� */
	unsigned int uiSeq;			/* ���ڶ�����ָʾ��I/O����� */
	int iIOType;				/* IO_Xxx ָʾ��I/O������ */
	char Data[0];
}SynIO;

typedef struct _Client
{
	struct _Client *pNext;		/* ��һ���ͻ��� */
	void *pExt;					/* ��չ�� */
	SOCKET sClient;				/* �ͻ��˶�Ӧ���׽��� */
	SOCKADDR_IN saServer;		/* �����������ӵ�ַ��Ϣ */
	SOCKADDR_IN saClient;		/* �ͻ��˵����ӵ�ַ��Ϣ */
	int iState;					/* �Ƿ����ڹرտͻ��˵����� */
	unsigned int uiPendingRecv;	/* ���𣨼�δ��ɣ��Ķ����������� */
	unsigned int uiPendingSend;	/* �����д���������� */
	unsigned int uiReadIOSeq;	/* ���Ÿ�����IO����һ�����к� */
	unsigned int uiReadSeq;		/* ��ǰҪ�������к� */
	SynIO *pReadIO;				/* û�а�˳����ɵĶ�I/O */
	CRITICAL_SECTION csLock;	/* ͬ����Client�ṹ��Ĳ��� */
}Client;

// �ص��������κλص������������IO��������ʽ����SIO_Free�����ͷ�!!
/*
����һ��������
1���Ѷ�pClt�����������������ٶ�csLock���м���
2�����Ե���DisConn���Ͽ���pClt������
*/
typedef void (*PFUNC_OnConnected)(Client* pClt);
/*
�Է��ر�����
ע�⣺�˺����ص��󣬲����ٶ�pClt�����κ�I/O�����������ڵ��� ������pClt�п��ܱ��ͷ��ڴ�
*/
typedef void (*PFUNC_OnClosed)(Client* pClt, SynIO* pIO);
/*
���������ر�����
ע�⣺��OnClosedһ��
*/
typedef void (*PFUNC_OnError)(Client* pClt, SynIO* pIO, int iErr);
/*
�����������
1���ڲ��ѽ�������RecvCompleted���ص���pIO�������
2�����Ե���DisConn���Ͽ���pClt������
*/
typedef void (*PFUNC_OnRecvCompleted)(Client* pClt, SynIO* pIO);
/*
�����������
ע�⣺pIO->uiTransΪʵ�ʷ��͵��ֽ�����pIO->uiDataΪͶ�ݷ�������ʱϣ�����͵��ֽ���
	  �������ȣ������ֻ�����˲������ݶ��ѣ�ʣ�� pIO->uiData - pIO->uiTrans û�б�����
*/
typedef void (*PFUNC_OnSendCompleted)(Client* pClt, SynIO* pIO);
/*
��pClt���ͷ�ʱ���˺������ص���ǰ���OnClosed / OnError���п��ܱ��ͷ�
�˻ص���һ�����ͷ�pClt�ڴ棬����pClt���ڴ治���ٽ��в���!!!
1���Ͽ����� DisConn		���ر��׽���(pClt->sClient)����λpClt->iState���
2���ͷ��ڴ�	Clt_Free	�ͷ��ڴ�(pClt)��pClt���е�δ��I/O����ɺ���ܱ��ͷ�
*/
typedef void (*PFUNC_OnClientFree)(Client* pClt);

// ��ʼ��IOCPģ��
int IOCP_Init(PFUNC_OnConnected fConnected=NULL,			/* �ص����� */
			  PFUNC_OnClosed fClosed=NULL,
			  PFUNC_OnError fErr=NULL,
			  PFUNC_OnRecvCompleted fRecv=NULL,
			  PFUNC_OnSendCompleted fSend=NULL,
			  PFUNC_OnClientFree fCltFree=NULL,
			  unsigned int uiDataLen = 4096,		/*
													����0֮��
													ֻҪͶ��WSASend/WSARecv����ֵΪWSA_IO_PENGDING
													ϵͳ����ΪIO����4KB���ڴ�
													���Խ�IO�Ļ���������Ϊ4KB
													*/
			  unsigned int uiClearPerSec = 30		/* ����s�Կ����������һ������ */
			  );
// �ͷ�IOCPģ�����Դ
int IOCP_Free();

// ����IOCP������
int IOCP_Start(const char *IP = "0",				/* �����������ı��ص�ַ , 0 ��ʾ�������ص����е�ַ */
//			   unsigned short Port = 2012,			/* ����˿� */
			   unsigned short Port = 15100,			/* ����˿� */
			   long InitAcceptNumber = 30,			/* ��ʼ��Ͷ�ݶ��ٸ�AcceptEx �������������Ͷ��ά���������Χ�� */
			   unsigned int uiThread = 0,			/* IOCP���߳��� �� Ĭ��Ϊ 4 * CPU */
			   unsigned long KeepAlive = 60			/* ����s���һ��������� : KeepAlive */
			   );
// ֹͣIOCP������
int IOCP_Shutdown();

// ��ȡ��ǰ��������
unsigned int IOCP_GetConnNumber();

/*
���º��������ڻص������ڵ���
���� Recv / Send ��ʱ��Ҫ���� 0 �ֽڵ��ڴ棬IOCPģ���ڲ��ᵱ���ر��׽��ִ���
*/
// �Ͽ���pClt������
void DisConn(Client *pClt);
/*
Ͷ�ݶ�����
��ֵ��
1��IOCP_OK Ͷ�ݳɹ��������Recv��������еõ�
2��IOCP_ERRͶ��ʧ�ܣ��ر��׽���!!!
3��IOCP_NOBUF����ISOʧ��

PostXxx ϵ�к�����������LockClt����ɣ���WorkThread���ƣ�
*/
extern SynIO* SIO_Alloc();
extern void SIO_Free(SynIO* pIO);
int PostRecv(Client *pClt, char *pData, int iLen);
int PostSend(Client *pClt, char *pData, int iLen);
int PostRecv(Client *pClt, SynIO *pIO);
int PostSend(Client *pClt, SynIO *pIO);

#endif
