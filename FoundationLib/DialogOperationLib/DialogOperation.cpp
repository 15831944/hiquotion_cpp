#include "StdAfx.h"
#include "DialogOperation.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>

CDialogOperation::CDialogOperation(void)
{
}

CDialogOperation::~CDialogOperation(void)
{
}

// ���ļ��Ի���
// ����ֵ��TRUE��ѡ�����ļ���FALSE��ȡ����
// BOOL CFileDialogOperation::openFileDialog(CString &fileName, HWND hwnd, CString title, CString filter, CString defaultFileName, CString defaultExt, DWORD flag)
BOOL CDialogOperation::openFileDialog(CString &fileName, CWnd *hwnd, CString filter, CString defaultExt, CString defaultFileName, CString title, DWORD flag)
{
	CFileDialog openDlg(TRUE, defaultExt, defaultFileName, flag, filter, hwnd);
	openDlg.m_ofn.lpstrTitle=title;
	if(openDlg.DoModal()==IDOK)
	{
		fileName=openDlg.GetPathName();
		return TRUE;
	}
	return FALSE;

}

// ���ļ��Ի����ļ���ѡ��
// ����ֵ��TRUE��ѡ�����ļ���FALSE��ȡ����
BOOL CDialogOperation::openMultiFilesDialog(CStringArray &fileNames, CWnd *hwnd, CString filter, CString defaultExt, CString defaultFileName, CString title, DWORD flag)
{
	CFileDialog openDlg(TRUE, defaultExt, defaultFileName, flag|OFN_ALLOWMULTISELECT, filter, hwnd);
	openDlg.m_ofn.lpstrTitle=title;
	if(openDlg.DoModal()==IDOK)
	{
		POSITION pos=openDlg.GetStartPosition();
		while(pos)
		{
			CString name=openDlg.GetNextPathName(pos);
			fileNames.Add(name);
		}
		return TRUE;
	}
	return FALSE;
}

// �����ļ��Ի���
// ����ֵ��TRUE��ѡ�����ļ���FALSE��ȡ����
BOOL CDialogOperation::saveFileDialog(CString &fileName, CWnd *hwnd,  CString filter, CString defaultExt, CString defaultFileName, CString title, DWORD flag)
{
	CFileDialog openDlg(FALSE, defaultExt, defaultFileName, flag, filter, hwnd);
	openDlg.m_ofn.lpstrTitle=title;
	if(openDlg.DoModal()==IDOK)
	{
		fileName=openDlg.GetPathName();
		return TRUE;
	}
	return FALSE;
}

// ��ʼ����Ŀ¼�Ի����ʼĿ¼�Ļص�����
int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
       if(uMsg == BFFM_INITIALIZED)
       {
              SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
       }
       return 0; 
}

// ��Ŀ¼�Ի���
BOOL CDialogOperation::openFolderDlg(HWND hwnd,CString &folder,CString title, CString initFolder, BOOL sShowNewButton)
{
	CString sFolderPath;
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner = hwnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle = "ѡ��·��";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	if(sShowNewButton)  // �Ƿ���ʾ���½��ļ��С���ť
		bi.ulFlags |= BIF_USENEWUI;
	bi.lpfn = NULL;
	bi.iImage = 0;
	bi.lParam =0;
	bi.lpfn = NULL;
	if(initFolder.GetLength()>0)
	{
		if(CFolderOperation::isFolderExist(initFolder))
		{
			bi.lParam =(long)(initFolder.GetBuffer(initFolder.GetLength()));//��ʼ��·��������(_T("c:\\Symbian"));
			bi.lpfn = BrowseCallbackProc;
		}
	}
	//��ʼ����ڲ���bi����
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���
	if(!pIDList)
		return FALSE;

	SHGetPathFromIDList(pIDList, Buffer);
	//ȡ���ļ���·����Buffer��
	sFolderPath = Buffer;//��·��������һ��CString������
	folder=sFolderPath;

	return TRUE;
}
