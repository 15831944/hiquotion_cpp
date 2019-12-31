/*
IOCP Server v1.0
www.ipsky.net
*/

#include "iocpserver.h"

/************************************************************************/
/*                          ȫ�ֱ���                                    */
/************************************************************************/
static unsigned int uiClearPer;	/*�����������֮�������ʱ���� s*/

static CRITICAL_SECTION csSIO;	/*ͬ����SIO�Ĳ���*/
static SynIO *pFreeSIO;			/*����SIO����*/
static unsigned int uiData;		/*SIO���������Ĵ�С*/
static unsigned int uiFreeSIO;	/*����SIO������Ԫ�ص�����*/
static unsigned int uiSIOTime;	/*��һ��������������ʱ��*/
static long uiAllocIO;			/*�ѷ����ȥ��SIO����*/

static CRITICAL_SECTION csClt;
static Client *pFreeClt;
static unsigned int uiFreeClt;
static unsigned int uiCltTime;
static long uiAllocClt;

/************************************************************************/
/*                             ��                                       */
/************************************************************************/
#define IOLock() ::EnterCriticalSection(&csSIO)
#define IOUnLock() ::LeaveCriticalSection(&csSIO)
#define CltLock() ::EnterCriticalSection(&csClt)
#define CltUnLock() ::LeaveCriticalSection(&csClt)

/************************************************************************/
/*                     ���гصĳ�ʼ�����ͷ�                             */
/************************************************************************/
/*
uiDataLen		�������ĳ���
				��1������ֱ��ʹ�� IOCP FreePool ģ����ڴ�����շ�
				��2�����uiDataLenΪ0���ʾ���������û�����ģ�����ã��ṩ
uiClearPerSec	������տ��������ʱ����
				����������� Xxx_Free ʱִ��
*/
void FreePool_Init(unsigned int uiDataLen,
				   unsigned int uiClearPerSec)
{
	// �������ڣ�ÿ�� uiClearPer ms �ͷ�һ��Ļ���
	uiClearPer = uiClearPerSec * 1000;
	// ��ʼ�� I/O ����
	::InitializeCriticalSection(&csSIO);
	pFreeSIO = NULL;
	uiData = uiDataLen;
	uiFreeSIO = 0;
	uiSIOTime = ::GetTickCount() + uiClearPer;
	uiAllocIO = 0;
	// ��ʼ�� Clt ����
	::InitializeCriticalSection(&csClt);
	pFreeClt = NULL;
	uiFreeClt = 0;
	uiCltTime = ::GetTickCount() + uiClearPer;
	uiAllocClt = 0;
}

void FreePool_Free()
{
	// ɾ���ٽ���
	::DeleteCriticalSection(&csSIO);
	::DeleteCriticalSection(&csClt);
	// �ͷ����еĿ�����
	for(SynIO *pIO = pFreeSIO, *pNextIO; pIO; )
	{
		pNextIO = pIO->pNext;
		MemFree(pIO);
		pIO = pNextIO;
	}
	for(Client *pClt = pFreeClt, *pNextClt; pClt; )
	{
		pNextClt = pClt->pNext;
		MemFree(pClt);
		pClt = pNextClt;
	}
}

void FreePool_Clear()
{
	SynIO *pIO;
	Client *pClt;
	unsigned int ui;

	IOLock();
	// ����ѵ�����������
	if(::GetTickCount() > uiSIOTime)
	{
		// ȥ��һ��Ŀ�����
		ui = uiFreeSIO >> 1;
		uiFreeSIO -= ui;
		// ���ü�ʱ��
		uiSIOTime = GetTickCount() + uiClearPer;
		// ��������ı�����������Ƴ�
		while(pFreeSIO && ui--)
		{
			pIO = pFreeSIO;
			pFreeSIO = pFreeSIO->pNext;
			MemFree(pIO);
		}
	}
	IOUnLock();
	CltLock();
	if(::GetTickCount() > uiCltTime)
	{
		ui = uiFreeClt >> 1;
		uiFreeClt -= ui;
		uiCltTime = GetTickCount() + uiClearPer;
		while(pFreeClt && ui--)
		{
			pClt = pFreeClt;
			pFreeClt = pFreeClt->pNext;
			MemFree(pClt);
		}
	}
	CltUnLock();
}

/************************************************************************/
/*                                 SIO                                  */
/************************************************************************/
/*
����һ�����õ�SynIO
�����������ǿ���ֱ��ȡ��һ�����õ�SIO
���������µ�SIO
*/
SynIO* SIO_Alloc()
{
	SynIO *pIO = NULL;

	// �����������ǿ�ֱ�Ӵӿ��б���ȡ����һ��
	IOLock();
	if(pIO = pFreeSIO)
	{
		pFreeSIO = pFreeSIO->pNext;
	}
	IOUnLock();
	// ���б�û�п��õ�SIO�������µ�
	if(pIO || 
		(pIO = (SynIO*)MemAlloc(sizeof(SynIO) + uiData)))
	{
		memset(pIO, 0, sizeof(SynIO));
		pIO->pData = pIO->Data;
		pIO->uiData = uiData;
		pIO->sSocket = INVALID_SOCKET;
		::InterlockedIncrement(&uiAllocIO);
	}

	return pIO;
}
/*
�ͷ�һ��SIO
�����������ʱ�����ͷ� uiFreeSIO/2 �Ŀ��б���
*/
void SIO_Free(SynIO* pIO)
{
	IOLock();
	// ��SIO����������
	pIO->pNext = pFreeSIO;
	pFreeSIO = pIO;
	uiFreeSIO++;
	IOUnLock();
	::InterlockedDecrement(&uiAllocIO);
}

/*
��ȡ��ǰ�ѷ����ȥ��SIO
AllocNumber = SIO_Alloc�ĵ��ô��� - SIO_Free�ĵ��ô���
*/
unsigned int SIO_GetAllocNumber() { return uiAllocIO; }

/************************************************************************/
/*                               Client                                 */
/************************************************************************/
Client* Clt_Alloc(SOCKET sSocket)
{
	Client *pClt = NULL;

	CltLock();
	if(pClt = pFreeClt)
	{
		pFreeClt = pFreeClt->pNext;
	}
	CltUnLock();

	if(NULL == pClt && 
		(pClt = (Client*)MemAlloc(sizeof(Client))))
	{
		::InitializeCriticalSection(&pClt->csLock);
	}
	if(pClt)
	{
		CRITICAL_SECTION cs = pClt->csLock;
		memset(pClt, 0, sizeof(Client));
		pClt->csLock = cs;
		pClt->iState = CLT_CONN;
		pClt->sClient = sSocket;
		::InterlockedIncrement(&uiAllocClt);
	}
	
	return pClt;
}

void Clt_Free(Client *pClt)
{
	CltLock();
	pClt->pNext = pFreeClt;
	pClt->iState = CLT_FREE;
	pFreeClt = pClt;
	uiFreeClt++;
	CltUnLock();
	::InterlockedDecrement(&uiAllocClt);
}

unsigned int Clt_GetAllocNumber() { return uiAllocClt; }
