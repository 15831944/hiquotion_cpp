#pragma once
#include <afxctl.h>
#include <string>

class CFolderOperation
{
public:
	CFolderOperation(void);
	~CFolderOperation(void);

	// �ж��ļ����Ƿ����
	static BOOL isFolderExist(CString strPath);

	// �����ļ���
	static BOOL createDir(CString strPath);

	// �����༶Ŀ¼
	static BOOL createDirEx(const CString& szPath);

	// ��ȫ·�����л�ȡ�ļ�����·��
	static CString getFolderFromFullPath(CString fullPath);

	// ��ȡ�������ڵ�ǰ·��
	static CString GetModulePath(HINSTANCE instance=NULL);

	// ���ļ�����ȫ·��
	static CString GetModuleFullPath(HINSTANCE instance=NULL);

	// ��ȡģ��·��
	static CString getOcxPath(COleControlModule *module);

	// ���ļ���������"\"
	static CString addGang(CString path);
	// ȥ�����·�������"\"��"/"
	static CString removeLeftGang(CString path);

	// ��ȡϵͳ��������
	static std::string getSystemDrive();

	// ��ȡ Windows ��ʱ�ļ���Ŀ¼
	static CString getTempFolder();

	// ��ȡָ��Ŀ¼�µ�һ����Ŀ¼�б�
	static void getSubFolders(CString folder, CStringArray &subFolders, CString filter=
#ifdef _UNICODE
		L"*.*", BOOL clearSubFoldersArray = TRUE);
#else
		"*.*", BOOL clearSubFoldersArray = TRUE);
#endif

	// �ֽ��ļ�·��Ϊ�ļ��к��ļ���
	static void parsePath(CString path, CString &folder, CString &file);

	// ɾ���ļ���
	static BOOL removeFolder(CString folder);
};
