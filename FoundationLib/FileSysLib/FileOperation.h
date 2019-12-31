// FileOperation.h: interface for the CFileOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPERATION_H__1D073143_EBBB_4F30_BFEE_94F75335B8A7__INCLUDED_)
#define AFX_FILEOPERATION_H__1D073143_EBBB_4F30_BFEE_94F75335B8A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileOperation  
{
public:
	CFileOperation();
	virtual ~CFileOperation();

	static void getFileNamesinFolder(CString folder,CString filter,CStringArray *files,BOOL isClearArray=TRUE);
	static void getFileNamesinFolderExt(CString folder,CStringArray *filters,CStringArray *files,BOOL isClearArray=TRUE);

	// ��ָ��Ŀ¼��ȡ����ָ����չ�����ļ���������Ŀ¼���б�
	// withFullFolder ָ�������б��е�ÿ��ǰ���ȫ·���������·����Ĭ���ǰ���ȫ·����
	static void getFilesFromFolder(CString root,CString folder,CString filter,CStringArray *files, bool withFullFolder = true);

	// ��ָ����ȫ·���л�ȡ�ļ��к��ļ���
	static void getFileInfoFromPath(CString fullPath, CString &folder, CString &fileName);

	// ��ȫ·���л�ȡ�ļ���������չ���ģ�
	static CString getFileName(CString fullPath);

	static CString getFileNameNoExt(CString fileNameNoPath);

	// �����֪���ƺ���չ�����ļ����ҵ�������ֺ�׺���ļ�
	// ���� abc.hit�����ҵ� abc_1.hit��123_4.ef�����ҵ�123_5.ef �ȵ�
	static CString GetFullFileNameNoExt(CString path,CString prefix,CString filter);

	static BOOL isFileExist(CString fileFullPath);

	static ULONGLONG getFileSize(CString fileFullPath);

	static CString getFileExtName(CString file);

	static CString getTempFileFullPath(CString folder, CString prefix=TEXT("tmp"));
};

#endif // !defined(AFX_FILEOPERATION_H__1D073143_EBBB_4F30_BFEE_94F75335B8A7__INCLUDED_)
