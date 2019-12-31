// Shortcut.cpp: implementation of the CShortcut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Shortcut.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShortcut::CShortcut()
{

}

CShortcut::~CShortcut()
{

}

BOOL CShortcut::createFileShortcut(LPCSTR lpszFileFullPath, LPCSTR lpszLnkFileDir, LPCSTR lpszLnkFileName, LPCSTR lpszArguments, LPCSTR lpszWorkDir, WORD wHotkey, LPCTSTR lpszDescription, int iShowCmd)
{
	if (lpszLnkFileDir == NULL)
		return FALSE;
	
	HRESULT hr;
	IShellLink     *pLink;  //IShellLink����ָ��
	IPersistFile   *ppf; //IPersisFil����ָ��
	
	//����IShellLink����
	hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
	if (FAILED(hr))
		return FALSE;
	
	//��IShellLink�����л�ȡIPersistFile�ӿ�
	hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
	if (FAILED(hr))
	{
		pLink->Release();
		return FALSE;
	}
	
	//Ŀ��
	if (lpszFileFullPath == NULL)
		pLink->SetPath(_pgmptr);
	else
		pLink->SetPath(lpszFileFullPath);
	
	//����Ŀ¼
	if (lpszWorkDir != NULL)
		pLink->SetWorkingDirectory(lpszWorkDir);

	// ����
	if(lpszArguments!=NULL)
		pLink->SetArguments(lpszArguments);
	
	//��ݼ�
	if (wHotkey != 0)
		pLink->SetHotkey(wHotkey);
	
	//��ע
	if (lpszDescription != NULL)
		pLink->SetDescription(lpszDescription);
	
	//��ʾ��ʽ
	pLink->SetShowCmd(iShowCmd);
	
	
	//��ݷ�ʽ��·�� + ����
	char szBuffer[MAX_PATH];
	if (lpszLnkFileName != NULL) //ָ���˿�ݷ�ʽ������
		sprintf(szBuffer, "%s\\%s", lpszLnkFileDir, lpszLnkFileName);
	else   
	{
		//û��ָ�����ƣ��ʹ�ȡָ���ļ����ļ�����Ϊ��ݷ�ʽ���ơ�
		char *pstr;
		if (lpszFileFullPath != NULL)
			pstr = strrchr(lpszFileFullPath, '\\');
		else
			pstr = strrchr(_pgmptr, '\\');
		
		if (pstr == NULL)
		{	
			ppf->Release();
			pLink->Release();
			return FALSE;
		}
		//ע���׺��Ҫ��.exe��Ϊ.lnk
		sprintf(szBuffer, "%s\\%s", lpszLnkFileDir, pstr);
		int nLen = strlen(szBuffer);
		szBuffer[nLen - 3] = 'l';
		szBuffer[nLen - 2] = 'n';
		szBuffer[nLen - 1] = 'k';
	}
	//�����ݷ�ʽ��ָ��Ŀ¼��
	WCHAR  wsz[MAX_PATH];  //����Unicode�ַ���
	MultiByteToWideChar(CP_ACP, 0, szBuffer, -1, wsz, MAX_PATH);
	
	hr = ppf->Save(wsz, TRUE);
	
	ppf->Release();
	pLink->Release();
	return SUCCEEDED(hr);
}
