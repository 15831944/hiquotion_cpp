// ClipboardOperation.cpp: implementation of the CClipboardOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClipboardOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClipboardOperation::CClipboardOperation()
{

}

CClipboardOperation::~CClipboardOperation()
{

}

BOOL CClipboardOperation::open(HWND hwnd)
{
	return OpenClipboard(hwnd);
}

void CClipboardOperation::close()
{
	CloseClipboard();
}

void CClipboardOperation::clear()
{
	EmptyClipboard();
}

void CClipboardOperation::copyText( CString txt )
{
	if(txt.GetLength()<=0)
		return;

	HANDLE hClip;      //����һ�����  
	CString str;  
	char *pBuf;  
	clear();  //�ÿ�������а壬�ҵõ����а������Ȩ  
	hClip=GlobalAlloc(GMEM_MOVEABLE,txt.GetLength()+1);  
	//��������һ�������ݵ��ڴ�����  
	pBuf=(char *)GlobalLock(hClip);//�õ�ָ���ڴ�����ĵ�һ���ֽ�ָ��  
	strcpy(pBuf,txt);//���ı����ֵ�������ڴ���  
	GlobalUnlock(hClip);//����ڴ�����  
	SetClipboardData(CF_TEXT,hClip);//�������ݵ����а���  
	close();//�رռ��а�
}
