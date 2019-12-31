#pragma once

#if _MSC_VER<=1200
#define BIF_NEWDIALOGSTYLE   0x40
#define BIF_USENEWUI (BIF_NEWDIALOGSTYLE|BIF_EDITBOX)
#endif

class CDialogOperation
{
public:
	CDialogOperation(void);
	~CDialogOperation(void);

	// ���ļ��Ի���
	// ����ֵ��TRUE��ѡ�����ļ���FALSE��ȡ����
// 	static BOOL openFileDialog(CString &fileName, HWND hwnd=NULL, CString title="��", CString filter="*.*\0*.*\0\0", CString defaultFileName="", CString defaultExt="*.*", DWORD flag=OFN_FILEMUSTEXIST|OFN_HIDEREADONLY);
	static BOOL openFileDialog(CString &fileName, CWnd *hwnd=NULL, CString filter="�����ļ�(*.*)|*.*||", CString defaultExt="*.*", CString defaultFileName="", CString title="��", DWORD flag=OFN_FILEMUSTEXIST|OFN_HIDEREADONLY);

	// ���ļ��Ի����ļ���ѡ��
	// ����ֵ��TRUE��ѡ�����ļ���FALSE��ȡ����
	static BOOL openMultiFilesDialog(CStringArray &fileNames, CWnd *hwnd=NULL, CString filter="�����ļ�(*.*)|*.*||", CString defaultExt="*.*", CString defaultFileName="", CString title="�򿪣��ļ��ɶ�ѡ��", DWORD flag=OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT);
	
	// �����ļ��Ի���
	// ����ֵ��TRUE��ѡ�����ļ���FALSE��ȡ����
	static BOOL saveFileDialog(CString &fileNames, CWnd *hwnd=NULL, CString filter="�����ļ�(*.*)|*.*||", CString defaultExt="", CString defaultFileName="", CString title="����", DWORD flag=OFN_OVERWRITEPROMPT);

	// ��Ŀ¼�Ի���
	static BOOL openFolderDlg(HWND hwnd,CString &folder,CString title="ѡ��·��", CString initFolder="", BOOL isShowNewButton=FALSE);

};
