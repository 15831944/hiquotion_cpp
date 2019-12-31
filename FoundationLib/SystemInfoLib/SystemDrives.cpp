// SystemDrives.cpp: implementation of the CSystemDrives class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemDrives.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemDrives::CSystemDrives()
{

}

CSystemDrives::~CSystemDrives()
{

}

// ��ѯ�������������������������ͣ��洢�������������б���
void CSystemDrives::queryDrives()
{
	clearDrives();
	
	CString drv="";
	char drvChar='\0';
	int drvType=DRIVE_UNKNOWN;
	for(int i=2;i<26;i++)
	{
		drvChar='A' + i;
		drv=drvChar;
		drv+=":\\";
		
		// #define DRIVE_UNKNOWN     0
		// #define DRIVE_NO_ROOT_DIR 1
		// #define DRIVE_REMOVABLE   2
		// #define DRIVE_FIXED       3
		// #define DRIVE_REMOTE      4
		// #define DRIVE_CDROM       5
		// #define DRIVE_RAMDISK     6
		drvType=GetDriveType(drv);
		switch(drvType)
		{
		case DRIVE_UNKNOWN:
			break;
		case DRIVE_NO_ROOT_DIR:
			break;
		case DRIVE_REMOVABLE:
			RemovableDrives.push_back(drvChar);
			break;
		case DRIVE_FIXED:
			FixedDrives.push_back(drvChar);
			break;
		case DRIVE_REMOTE:
			RemoteDrives.push_back(drvChar);
			break;
		case DRIVE_CDROM:
			Cdroms.push_back(drvChar);
			break;
		case DRIVE_RAMDISK:
			RamdiskDrives.push_back(drvChar);
			break;
		}
	}
};

// ��ѯָ�����͵�������������0��ʾȫ��
void CSystemDrives::queryDrives(std::vector<char> &drives, UINT type/*=0*/)
{
	drives.clear();

	CString drv="";
	char drvChar='\0';
	for(int i=2;i<26;i++)
	{
		drvChar='A' + i;
		drv=drvChar;
		drv+=":\\";

		
		// #define DRIVE_UNKNOWN     0
		// #define DRIVE_NO_ROOT_DIR 1
		// #define DRIVE_REMOVABLE   2
		// #define DRIVE_FIXED       3
		// #define DRIVE_REMOTE      4
		// #define DRIVE_CDROM       5
		// #define DRIVE_RAMDISK     6
		int drvType=GetDriveType(drv);
		if(drvType==DRIVE_UNKNOWN || drvType==DRIVE_NO_ROOT_DIR)
			continue;

		if(type==0)
			drives.push_back(drvChar);
		else if(type==drvType)
			drives.push_back(drvChar);
	}
}

// ��ȡָ�����̵�ʣ��ռ�
// �������̷��ַ���ʣ��ռ�ṹ��
// ����ֵ���ɹ����
BOOL CSystemDrives::getDriveSpace(char drvChar, DriveSpace &driveSpace)
{
	CString drv=drvChar;
	drv+=":";
	DriveSpace space;
	memset(&space, 0x00, sizeof(DriveSpace));
	if(!GetDiskFreeSpaceEx(drv, &space.available, &space.total, &space.rested))
		return FALSE;

	driveSpace=space;
	return TRUE;
};

// ��ȡ���ʣ��ռ�Ĵ����̷���ʣ��ռ��С�����ֽڣ�
BOOL CSystemDrives::getMaxFreeSpaceDrive(std::vector<char> drives, char &drvChar, ULARGE_INTEGER *maxFreeSpace)
{
	if(drives.size()<=0)
		return FALSE;

	DriveSpace space;
	ULARGE_INTEGER maxfree;
	memset(&maxfree, 0x00, sizeof(ULARGE_INTEGER));
	int maxindex=0;
	int first=0;

	// �ҵ���һ���ܹ���ȡ�����ռ���̷������ǲ�����ʧ�ܵģ�
	while(!getDriveSpace(drives[first], space))
	{
		first++;
		if(first==drives.size())   // ��ֹ����
			break;
	}

	// ���һ����û�У��򷵻�ʧ��
	if(first==drives.size())
		return FALSE;

	// �����ҵ���һ��
	maxfree=space.rested;
	maxindex=first;

	// ����Ѿ������б������򷵻سɹ������������ҵ���һ��������
	first++;
	if(first==drives.size())
	{
		drvChar=drives[maxindex];
		memcpy(&maxFreeSpace, &maxfree, sizeof(ULARGE_INTEGER));
		return TRUE;
	}

	// ˵���б��л���ʣ����̷�������ȡʣ��ռ�ɹ����̷���Ҫ��ǰ���ҵ����̷���ʣ��ռ����Ƚϣ������³������
	while(getDriveSpace(drives[first], space))
	{
		if(maxfree.QuadPart<space.rested.QuadPart)                    // ���Ƚ�
		{
			memcpy(&maxfree, &space.rested, sizeof(ULARGE_INTEGER));  // ���³������
			maxindex=first;
		}
		first++;
		if(first==drives.size())     // ��ֹ����
			break;
	}
	
	// ȫ���Ƚ���ϣ����سɹ�����������߸�����
	drvChar=drives[maxindex];
	memcpy(&maxFreeSpace, &maxfree, sizeof(ULARGE_INTEGER));
	return TRUE;
};

void CSystemDrives::clearDrives()
{
	RemovableDrives.clear();
	FixedDrives.clear();
	RemoteDrives.clear();
	Cdroms.clear();
	RamdiskDrives.clear();
}

// �ײ�����·��ת���� Win32 ·��
CString CSystemDrives::convertDrvFoldertoWin32(CString drvFolder)
{
	if(drvFolder.GetLength()<=0)
		return "";

	if(drvFolder.Find("\\Device", 0)!=0)
		return drvFolder;
	
	std::vector<char> drives;
	queryDrives(drives, 0);
	CString sret=drvFolder;

	for(int i=0;i<drives.size();i++)
	{
		CString drv=drives.at(i);
		drv+=":";
		std::string drvName="";
		BOOL ret=getDosDriveString((LPTSTR)(LPCSTR)drv, drvName);
		drvName+="\\";
		if(sret.Find(drvName.c_str(), 0)==0)
			sret.Replace(drvName.c_str(), drv+"\\");
	}

	return sret;
}

// BOOL CSystemDrives::getLogicalDriveStringList(std::vector<std::string> &drives)
// {
// 	// ��ȡLogic Drive String����
//     UINT uiLen = GetLogicalDriveStrings(0, NULL);
//     if (0 == uiLen)
//     {
//         return FALSE;
//     }
// 	
//     PTSTR pLogicDriveString = new TCHAR[uiLen + 1];
//     ZeroMemory(pLogicDriveString, uiLen + 1);
//     uiLen = GetLogicalDriveStrings(uiLen, pLogicDriveString);
//     if (0 == uiLen)
//     {
//         delete[]pLogicDriveString;
//         return FALSE;
//     }
// 	
// 	PTSTR pLogicIndex = pLogicDriveString;
// 	drives.clear();
// 
// 	do
//     {
// 		std::string drive=*pLogicIndex;
//         drives.push_back(drive);
// 
//         /*while*/ (*pLogicIndex++);
//     }
// 	while (*pLogicIndex);
// 	
// 
// }

// ��ȡ�ײ��������б�
BOOL CSystemDrives::getDosDriveString(std::string driveString, std::string &drive)
{
	PTSTR pDosDriveName = new TCHAR[MAX_PATH];
	UINT uiLen = QueryDosDevice(driveString.c_str(), pDosDriveName, MAX_PATH);
	if (0 == uiLen)
	{
		DWORD ret=GetLastError();
		if (ERROR_INSUFFICIENT_BUFFER != ret)
		{
			return FALSE;
		}
		
		delete[]pDosDriveName;
		pDosDriveName = new TCHAR[uiLen + 1];
		uiLen = QueryDosDevice(driveString.c_str(), pDosDriveName, uiLen + 1);
		if (0 == uiLen)
		{
			return FALSE;
		}
	}
	
	drive=pDosDriveName;
	delete pDosDriveName;

	return TRUE;
}
