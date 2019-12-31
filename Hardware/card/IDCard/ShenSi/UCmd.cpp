#include "StdAfx.h"
#include "UCmd.h"

HINSTANCE hModule;

pUCmmand1		mycmd;
pGetInfo	GetSAMIDToStr;

pGetInfo myGetName    ;     //��ȡ����
pGetInfo myGetSex     ;     //��ȡ�Ա�
pGetInfo myGetFolk    ;     //��ȡ����
pGetInfo myGetBirth   ;     //��ȡ����
pGetInfo myGetAddr    ;     //��ȡסַ
pGetInfo myGetIDNum   ;     //��ȡ������ݺ���
pGetInfo myGetDep     ;     //��ȡǩ������
pGetInfo myGetBegin   ;     //��ȡ��Ч����
pGetInfo myGetEnd     ;     //��ȡ��Ч��ֹ
pGetInfo myGetNewAddr ;     //��ȡ���µ�ַ
pGetInfo myGetPicPath ;     //��ȡͷ��ͼƬ·��

// BOOL LoadDll();
// void FreeDll();

BOOL LoadDll()
{
	hModule=LoadLibrary(_T("RdCard.dll"));
	if(hModule ==NULL )
	{
		//AfxMessageBox(_T("���ض�̬��ʧ��"));
		return FALSE;
	}

	mycmd		=(pUCmmand1)GetProcAddress(hModule,"UCommand1");

	GetSAMIDToStr	=(pGetInfo)GetProcAddress(hModule,"GetSAMIDToStr");

    myGetName    =(pGetInfo)GetProcAddress(hModule,"GetName");
    myGetSex     =(pGetInfo)GetProcAddress(hModule,"GetSex");
    myGetFolk    =(pGetInfo)GetProcAddress(hModule,"GetFolk");
    myGetBirth   =(pGetInfo)GetProcAddress(hModule,"GetBirth");
    myGetAddr    =(pGetInfo)GetProcAddress(hModule,"GetAddr");
    myGetIDNum   =(pGetInfo)GetProcAddress(hModule,"GetIDNum");
    myGetDep     =(pGetInfo)GetProcAddress(hModule,"GetDep");
    myGetBegin   =(pGetInfo)GetProcAddress(hModule,"GetBegin");
    myGetEnd     =(pGetInfo)GetProcAddress(hModule,"GetEnd");
    myGetNewAddr =(pGetInfo)GetProcAddress(hModule,"GetNewAddr");
    myGetPicPath =(pGetInfo)GetProcAddress(hModule,"GetBmpPath");


	if( (mycmd==NULL) )
	{
		return FALSE;
	}
    else
    {
        return TRUE;
    }
}

void FreeDll()
{
	if(hModule !=NULL )
	{
		FreeLibrary(hModule);
		hModule=NULL;
	}	

}
