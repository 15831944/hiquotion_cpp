// SystemDrives.h: interface for the CSystemDrives class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMDRIVES_H__D137DBFA_4BC7_41E3_B1E4_C3182B76151E__INCLUDED_)
#define AFX_SYSTEMDRIVES_H__D137DBFA_4BC7_41E3_B1E4_C3182B76151E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

struct DriveSpace
{
	ULARGE_INTEGER available;
	ULARGE_INTEGER total;
	ULARGE_INTEGER rested;
};

// ϵͳ��������
// ���еķ���������������static����Ϊvector�ı����ᵼ���޷��������ⲿ���š�����
class CSystemDrives  
{
public:
	CSystemDrives();//{};
	virtual ~CSystemDrives();//{};

	std::vector<char> RemovableDrives;
	std::vector<char> FixedDrives;
	std::vector<char> RemoteDrives;
	std::vector<char> Cdroms;
	std::vector<char> RamdiskDrives;

	// ��ѯ�������������������������ͣ��洢�������������б���
	void queryDrives();

	// ��ѯָ�����͵�������������0��ʾȫ��
	// #define DRIVE_REMOVABLE   2
	// #define DRIVE_FIXED       3
	// #define DRIVE_REMOTE      4
	// #define DRIVE_CDROM       5
	// #define DRIVE_RAMDISK     6
	void queryDrives(std::vector<char> &drives, UINT type=0);

	// ��ȡָ�����̵�ʣ��ռ�
	// �������̷��ַ���ʣ��ռ�ṹ��
	// ����ֵ���ɹ����
	BOOL getDriveSpace(char drvChar, DriveSpace &driveSpace);

	// ��ȡ���ʣ��ռ�Ĵ����̷���ʣ��ռ��С�����ֽڣ�
	BOOL getMaxFreeSpaceDrive(std::vector<char> drives, char &drvChar, ULARGE_INTEGER *maxFreeSpace);

// 	// ��ȡ�������б�
// 	BOOL getLogicalDriveStringList(std::vector<std::string> &drives);

	// ��ȡָ���̷�������"C:\"���ĵײ��������ַ���
	BOOL getDosDriveString(std::string driveString, std::string &drives);

	// ָ��ĳ��������
	
	// �ײ�����·��ת���� Win32 ·��
	CString convertDrvFoldertoWin32(CString drvFolder);

private:
	void clearDrives();
};

#endif // !defined(AFX_SYSTEMDRIVES_H__D137DBFA_4BC7_41E3_B1E4_C3182B76151E__INCLUDED_)
