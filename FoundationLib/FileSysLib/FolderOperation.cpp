#include "stdafx.h"

#include "FolderOperation.h"
#include <vector>
using namespace std;


CFolderOperation::CFolderOperation(void)
{
}

CFolderOperation::~CFolderOperation(void)
{
}

// �ж��ļ����Ƿ����
BOOL CFolderOperation::isFolderExist(CString strPath)
{
    DWORD dwAttr;  
    dwAttr = GetFileAttributes(strPath);  
    if(dwAttr == -1L) //pszDir��ָĿ�겻����
        return FALSE; 
    if(dwAttr & FILE_ATTRIBUTE_DIRECTORY) //pszDir��ָĿ�����ļ���
        return TRUE; 
    return FALSE;//pszDir��ָĿ�����ļ�
}


// �����ļ���
BOOL CFolderOperation::createDir(CString strPath)
{   
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	//���涨������Կ���ʡ�ԡ� ֱ��return ::CreateDirectory( path, NULL); ����
	return ::CreateDirectory( strPath, &attrib);
}

// �����༶Ŀ¼
BOOL CFolderOperation::createDirEx(const CString& szPath)
{
	CString strDir(szPath);//���Ҫ������Ŀ¼�ַ���
	//ȷ����'\'��β�Դ������һ��Ŀ¼
	if (strDir.GetAt(strDir.GetLength()-1)!='\\')
	{
		strDir+='\\';
	}
	vector<CString> vpath;//���ÿһ��Ŀ¼�ַ���
	CString strTemp;//һ����ʱ����,���Ŀ¼�ַ���
	//����Ҫ�������ַ���
	for (int i=0;i<strDir.GetLength();++i)
	{
		if (strDir.GetAt(i) != '\\') 
		{//�����ǰ�ַ�����'\\'
			strTemp+=(strDir.GetAt(i));
		}
		else 
		{//�����ǰ�ַ���'\\'
			vpath.push_back(strTemp);//����ǰ����ַ�����ӵ�������
			strTemp+=('\\');
		}
	}

	//�������Ŀ¼������,����ÿ��Ŀ¼
	BOOL bSuccess = TRUE;//�ɹ���־
	for (int j=0;j<(int)vpath.size();j++) 
	{
		//���CreateDirectoryִ�гɹ�,����true,���򷵻�false
		CString path=vpath[j];
		if(!isFolderExist(path))
			bSuccess &= createDir(path);
	}

	return bSuccess;
}

CString CFolderOperation::getFolderFromFullPath( CString fullPath )
{
	return fullPath.Left(fullPath.ReverseFind('\\'));
}

// ��ȡ�������ڵ�ǰ·��
CString CFolderOperation::GetModulePath(HINSTANCE instance)
{
// 	TCHAR path[MAX_PATH*10];
// // 	::GetModuleFileName(AfxGetInstanceHandle(),path,MAX_PATH*10);
// 	::GetModuleFileName(NULL,path,MAX_PATH*10);
// 	CString strTemp = _T("");
// 	CString strLocalPath = _T("");
// 	strTemp.Format("%s",path);
	CString strTemp = GetModuleFullPath();
	CString strLocalPath = _T("");
	strLocalPath = getFolderFromFullPath(strTemp);
	return strLocalPath;
}

// ���ļ�����ȫ·��
CString CFolderOperation::GetModuleFullPath(HINSTANCE instance)
{
	TCHAR path[MAX_PATH*10];
	// 	::GetModuleFileName(AfxGetInstanceHandle(),path,MAX_PATH*10);
	::GetModuleFileName(instance,path,MAX_PATH*10);
	CString strTemp = _T("");
	strTemp.Format(TEXT("%s"),path);
	return strTemp;

// 	TCHAR moduleName[MAX_PATH] = {0}; 
// 	GetModuleFileName(instance,moduleName,MAX_PATH); 
// 	TCHAR _strLongPath[MAX_PATH] = _T("\0");
// 	::GetLongPathName(moduleName, _strLongPath, MAX_PATH);
// 	CString strPath(_strLongPath);
// 	return strPath;
}

// ��ȡģ��·��
CString CFolderOperation::getOcxPath(COleControlModule *module)
{
	if(!module)
		return TEXT("");

	return getFolderFromFullPath(module->m_pszHelpFilePath);
}

// ���ļ���������"\"
CString CFolderOperation::addGang(CString path)
{
	if(path.GetLength()<=0)
#ifdef _UNICODE
		return L"";
#else
		return "";
#endif

#ifdef _UNICODE
	if (path.Right(1) != L'\\')
	{
		return path + L"\\";
	}
#else
	char *ch=(LPTSTR)(LPCSTR)path.Right(1);
	if(ch[0]!='\\')
	{
		return path + "\\";
	}
#endif

	return path;
}

// ȥ�����·�������"\"��"/"
CString CFolderOperation::removeLeftGang(CString path)
{
	if(path.GetLength()<=0)
		return TEXT("");

#ifdef _UNICODE
	if(path.Left(1)==L"/" || path.Left(1)==L"\\")
		return path.Right(path.GetLength() - 1);
#else
	char *ch=(LPTSTR)(LPCSTR)path.Left(1);
	if(ch[0]=='/' || ch[0]=='\\')
		return path.Right(path.GetLength()-1);
#endif
	return path;
}

string CFolderOperation::getSystemDrive()
{
	TCHAR path[MAX_PATH*10];
	::GetWindowsDirectory(path,MAX_PATH*10);
	path[2]=TEXT('\0');
	CString systemDrive=path;
	return (LPCSTR)systemDrive.GetBuffer(systemDrive.GetLength());
}

// ��ȡ Windows ��ʱ�ļ���Ŀ¼
CString CFolderOperation::getTempFolder()
{
#if _MSC_VER<=1200  // vc6.0 or lower
	return getenv(TEXT("TEMP"));
#else
#ifdef _UNICODE
#else
	char* env = NULL;
	size_t n = 0;
	errno_t ret = _dupenv_s(&env, &n, "TEMP");
	if (!ret)
		return TEXT("");

	CString envval = env;
	free(env);
	return envval;
#endif
#endif
}

// ��ȡָ��Ŀ¼�µ�һ����Ŀ¼�б�
void CFolderOperation::getSubFolders(CString folder, CStringArray &subFolders, CString filter, BOOL clearSubFoldersArray)
{
#ifdef _UNICODE
#else
	if(folder.GetLength()<=0)
		folder=".";

	if(!isFolderExist(folder))
		return;

	if (clearSubFoldersArray)
		subFolders.RemoveAll();

	WIN32_FIND_DATA   wfd;
	
	HANDLE hFind = FindFirstFile(addGang(folder)+filter, &wfd);
	do
	{
		if((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			CString fileName=wfd.cFileName;
			char *ch=(LPTSTR)(LPCSTR)fileName;
			// ���� "."��Ҳ���� ".."
			if(ch[0]!='.' || (ch[0]=='.' && ch[1]!='.'))
				subFolders.Add(fileName);
		}
	}
	while(FindNextFile(hFind,&wfd));

	FindClose(hFind);
#endif
}

// �ֽ��ļ�·��Ϊ�ļ��к��ļ���
void CFolderOperation::parsePath(CString path, CString &folder, CString &file)
{
	if(path.GetLength()<=0)
	{
		folder="";
		file="";
		return;
	}

	int pos=path.ReverseFind('\\');
	if(pos<=0)
	{
		// ֻ���ļ���
		folder="";
		file=path;
		return;
	}

	if(pos==path.GetLength()-1)
	{
		// û���ļ���
		folder=path;
		file="";
		return;
	}

	folder = path.Left(pos);
	file=path.Right(path.GetLength()-pos-1);
}

// ɾ���ļ���
BOOL CFolderOperation::removeFolder(CString folder)
{
	CFileFind tempFind;
	CString tempFileFind;
	tempFileFind.Format(TEXT("%s\\*.*"),folder);
	BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
	while(IsFinded)
	{
		IsFinded=(BOOL)tempFind.FindNextFile();
		if(!tempFind.IsDots())
		{
			CString foundFileName=tempFind.GetFileName();
			if(tempFind.IsDirectory())
			{
				CString tempDir;
				tempDir.Format(TEXT("%s\\%s"),folder,foundFileName);
				SetFileAttributes(tempDir, FILE_ATTRIBUTE_NORMAL);
				// ɾ�� tempDir �ڲ����ļ����ļ���
				removeFolder(tempDir);
				// ɾ�� tempDir �ļ��б���
				RemoveDirectory(tempDir);
			}
			else
			{
				CString tempFileName;
				tempFileName.Format(TEXT("%s\\%s"),folder,foundFileName);
				SetFileAttributes(tempFileName, FILE_ATTRIBUTE_NORMAL);
				DeleteFile(tempFileName);
			}
		}
	}
	tempFind.Close();
	if(!RemoveDirectory(folder))
		return FALSE;

	return TRUE;

	// ����Ĵ���ֻ��ɾ���ǿ�Ŀ¼

	//if(RemoveDirectory(folder))
	//	return TRUE;
	//else
	//	return FALSE;

	// ��������ڴ���δ����֮ǰ������ò��ɹ�

//	SHFILEOPSTRUCT FileOp={0};
//	FileOp.fFlags = // FOF_ALLOWUNDO |   //����Żػ���վ
//		FOF_NO_UI;          // �������κ� UI ����
//// 		FOF_NOCONFIRMATION; //������ȷ�϶Ի���
//	FileOp.pFrom = (LPCSTR)folder;
//	FileOp.pTo = NULL;      //һ��Ҫ��NULL
//	FileOp.wFunc = FO_DELETE;    //ɾ������
//
//	if(SHFileOperation(&FileOp) == 0)
//		return TRUE;
//	else
//		return FALSE;
}
