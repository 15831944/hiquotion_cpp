// FileOperation.cpp: implementation of the CFileOperation class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"

#include "FileOperation.h"
#include "FolderOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileOperation::CFileOperation()
{

}

CFileOperation::~CFileOperation()
{

}

void CFileOperation::getFileNamesinFolder(CString folder,CString filter,CStringArray *files,BOOL isClearArray)
{
	if(!files)
		return;
	
	if (isClearArray)
		files->RemoveAll();

	CFileFind sFinder;
#ifdef _UNICODE
	CString strFile = L"", strFileFound = L"";
	strFile.Format(L"%s%s", CFolderOperation::addGang(folder), filter);
#else
	CString strFile = "", strFileFound = "";
	strFile.Format("%s%s", CFolderOperation::addGang(folder), filter);
#endif
	BOOL bFind = sFinder.FindFile(strFile);
	while(bFind)
	{
		bFind = sFinder.FindNextFile();
		strFileFound = sFinder.GetFileName();
		files->Add(strFileFound);
	}
	sFinder.Close();
}

void CFileOperation::getFileNamesinFolderExt(CString folder,CStringArray *filters,CStringArray *files,BOOL isClearArray)
{
	if(!filters)
		return;

	if(!files)
		return;

	if(isClearArray)
		files->RemoveAll();

	for(int i=0;i<filters->GetSize();i++)
	{
		CString filter=filters->GetAt(i);
		if(filter.GetLength()<=0)
			continue;

		getFileNamesinFolder(folder, filter, files, FALSE);
	}
}

// ��ָ��Ŀ¼��ȡ����ָ����չ�����ļ���������Ŀ¼���б�
// withFullFolder ָ�������б��е�ÿ��ǰ���ȫ·���������·����Ĭ���ǰ���ȫ·����
void CFileOperation::getFilesFromFolder(CString root,CString folder,CString filter,CStringArray *files, bool withFullFolder)
{
	if(files==NULL)
		return;

	CString path=TEXT("");
	if(root.GetLength()<=0 && folder.GetLength()<=0)
		path=TEXT(".");
	else if(root.GetLength()>0 && folder.GetLength()<=0)
		path=root;
	else if(root.GetLength()<=0 && folder.GetLength()>0)
		path=folder;
	else if(root.GetLength()>0 && folder.GetLength()>0)
		path=root + TEXT("\\") + folder;

	if(filter.GetLength()<=0)
		filter=TEXT("*.*");

	// ��ȡ��ǰ�ļ����µ��������ļ���
	CStringArray subfolderList;
	CFolderOperation::getSubFolders(path, subfolderList);

	// ��ȡ��ǰ�ļ����µ�ָ��filter�������ļ�
	CStringArray fileList;
	getFileNamesinFolder(path, filter, &fileList);

	// ����ǰ�ļ����µ��ļ���ӵ� files �б���
	CString fileName=TEXT("");
	int i=0;
	for(i=0;i<fileList.GetSize();i++)
	{
// 		if(withFullFolder)
// 		{
// 			if(folder!="")
// 				fileName=folder + "\\" + fileList[i];
// 			else
// 				fileName=fileList[i];
// 		}
// 		else
// 			fileName=fileList[i];

		if(withFullFolder)
		{
			fileName = path + TEXT("\\") + fileList[i];
		}
		else
		{
			if(folder.GetLength()>0)
				fileName=folder + TEXT("\\") + fileList[i];
			else
				fileName=fileList[i];
		}

		files->Add(fileName);
	}

	CString subFolder=TEXT("");
	// ��ÿ�����ļ��У�ִ����ͬ�Ĳ���
	for(i=0;i<subfolderList.GetSize();i++)
	{
		if(withFullFolder)
			subFolder = path + TEXT("\\") + subfolderList[i];
		else
		{
			if(folder.GetLength()>0)
				subFolder = folder + TEXT("\\") + subfolderList[i];
			else
				subFolder = subfolderList[i];
		}

		getFilesFromFolder(root, subFolder, filter, files, withFullFolder);
	}
}

// ��ָ����ȫ·���л�ȡ�ļ��к��ļ���
void CFileOperation::getFileInfoFromPath(CString fullPath, CString &folder, CString &fileName)
{
	// ���ԭ��Ϊ�գ���ȫ���ؿմ�
	if(fullPath.GetLength()<=0)
	{
		folder=TEXT("");
		fileName= TEXT("");
		return;
	}

	int pos=fullPath.ReverseFind(TEXT('\\'));
	// ���δ�ҵ��������ֻ���ļ���
	if(pos<0)
	{
		folder=TEXT("");
		fileName=fullPath;
		return;
	}

	folder=fullPath.Left(pos);
	fileName=fullPath.Right(fullPath.GetLength()-pos-1);
}

BOOL CFileOperation::isFileExist(CString fileFullPath)
{
	CFileFind find;
	BOOL result=FALSE;
	if(find.FindFile(fileFullPath)) 
    	result=TRUE; 
	find.Close();
	return result;
}

CString CFileOperation::getFileName( CString fullPath )
{
	CString name;
	// ��ȡ������չ�����ļ���
	int pos=fullPath.ReverseFind(TEXT('\\'));
	if(pos>0)    //////////////////////////////////////// ==0 ��ʱ���Ƿ��ʾ�ļ������硰.abcd������ʽ������
		name=fullPath.Right(fullPath.GetLength()-pos-1);
	else
		name=fullPath;
	
	return name;
}

// �ӣ��ɴ��ɲ���·���ģ��ļ�������ȡû����չ���Ĳ���
CString CFileOperation::getFileNameNoExt(CString fileNameNoPath)
{
	CString nameNoExt;
	// ��ȡ������չ�����ļ���
	int pos=fileNameNoPath.ReverseFind(TEXT('.'));
	if(pos>0)    //////////////////////////////////////// ==0 ��ʱ���Ƿ��ʾ�ļ������硰.abcd������ʽ������
		nameNoExt=fileNameNoPath.Left(pos);
	else
		nameNoExt=fileNameNoPath;
	
	return nameNoExt;
}


CString CFileOperation::GetFullFileNameNoExt(CString path,CString prefix,CString filter)
{
	int i=1;
	CFileFind fileFind;
	CString tmp;
	tmp.Format(TEXT("%s%s_%d%s"),path,prefix,i,filter);
	while(fileFind.FindFile(tmp))
	{
		i+=1;
		tmp.Format(TEXT("%s%s_%d%s"),path,prefix,i,filter);
	}
	tmp.Format(TEXT("%s%s_%d"),path,prefix,i);
	return tmp;
}

ULONGLONG CFileOperation::getFileSize(CString fileFullPath)
{
	CFileStatus status;
	memset(&status,0,sizeof(CFileStatus));
	CFile::GetStatus(fileFullPath,status);
	return status.m_size;
}

CString CFileOperation::getFileExtName(CString file)
{
	if(file.GetLength()<=0)
		return TEXT("");

	int pos=file.ReverseFind(TEXT('.'));
	if(pos==-1)
		return file;
	else
		return file.Right(file.GetLength()-pos-1);
}

CString CFileOperation::getTempFileFullPath(CString folder, CString prefix)
{
	TCHAR name[MAX_PATH-14];
	GetTempFileName(folder,prefix,0,name);
	CString ret=name;
	return ret;
}
