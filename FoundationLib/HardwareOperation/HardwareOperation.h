#pragma once
#include <C++\FoundationLib\DataStructLib\PointerList.h>
#include <setupapi.h>
#include <devguid.h>

typedef struct tagDeviceInfo
{
	//�豸�Ѻ�����
	CString szDeviceName;
	//�豸��
	CString szDeviceClass;
	//�豸��ʾ��
	CString szDeviceDesc;
	//�豸����
	CString szDriverName;
	//�豸ʵ��
	DWORD dwDevIns;
	//�豸���־
	GUID Guid;
	//����������
	bool operator < (const tagDeviceInfo &tmp) const
	{
		if (tmp.szDeviceClass != szDeviceClass)
		{
			return tmp.szDeviceClass.CompareNoCase (szDeviceClass) > 0;
		}
		else
		{
			return tmp.szDeviceDesc.CompareNoCase (szDeviceDesc) > 0;
		}
	}
}DeviceInfo;

enum FilterType
{
	Class,
	Description,
	Devid,
};

// enum IncludeMode
// {
// 	All,
// 	Include,
// 	Exclude,
// };

enum FilterMode
{
	All,   // ȫ��Ӳ��
	AllInClass,  // ָ�������µ�ȫ��Ӳ��
	Include,   // ����Ӳ��id�б��е�Ӳ����ֻ���˳�����ϵͳ���еģ�
	ExcludeInAll,   // ��ȫ��Ӳ�����ų�Ӳ��id�б��е�Ӳ��
	ExcludeInClass  // ��ָ��Class���ų�Ӳ��id�б��е�Ӳ��
};

class CHardwareOperation
{
public:
	CHardwareOperation(void);
	~CHardwareOperation(void);

	// ��ȡ�豸��Ϣ�б�
	// ���� Ӳ�������GUID�����ΪNULL�����ȡ���з�����豸����������δ֪�豸����fileterFlagָ����ȡ�Ǹ���Ϣ����ȡ����Ӳ��id �ַ����б�ָ������filgerFlag��ָ�������ַ���
	// ˵����ֻ����������filgerFlag��ֵΪ�����ַ�����Ӳ��filterFlag��ֵ���Ż���ӵ�hwids�б���
	// ����ֵ��
	//  0���ɹ�
	// -1������ SetupDiGetClassDevs ʧ��
	/*
	GUID ���������µ�ֵ��VS2010 devguid.h �ж��壩
	GUID_DEVCLASS_1394
	GUID_DEVCLASS_1394DEBUG
	GUID_DEVCLASS_61883
	GUID_DEVCLASS_ADAPTER
	GUID_DEVCLASS_APMSUPPORT,
	GUID_DEVCLASS_AVC,
	GUID_DEVCLASS_BATTERY,
	GUID_DEVCLASS_BIOMETRIC,
	GUID_DEVCLASS_BLUETOOTH,
	GUID_DEVCLASS_CDROM          // ����
	GUID_DEVCLASS_COMPUTER       // �����
	GUID_DEVCLASS_DECODER,
	GUID_DEVCLASS_DISKDRIVE      // ����������
	GUID_DEVCLASS_DISPLAY        // ��ʾ��
	GUID_DEVCLASS_DOT4,
	GUID_DEVCLASS_DOT4PRINT,
	GUID_DEVCLASS_ENUM1394,
	GUID_DEVCLASS_FDC            // ���̿�����
	GUID_DEVCLASS_FLOPPYDISK     // ����������
	GUID_DEVCLASS_GPS,
	GUID_DEVCLASS_HDC            // IDE ATA/ATAPI ������
	GUID_DEVCLASS_HIDCLASS,
	GUID_DEVCLASS_IMAGE,
	GUID_DEVCLASS_INFINIBAND,
	GUID_DEVCLASS_INFRARED,
	GUID_DEVCLASS_KEYBOARD       // ����
	GUID_DEVCLASS_LEGACYDRIVER,
	GUID_DEVCLASS_MEDIA          // ��������Ƶ����Ϸ������
	GUID_DEVCLASS_MEDIUM_CHANGER,
	GUID_DEVCLASS_MODEM          // MODEM
	GUID_DEVCLASS_MONITOR        // ������
	GUID_DEVCLASS_MOUSE          // ��������ָ���豸
	GUID_DEVCLASS_MTD,
	GUID_DEVCLASS_MULTIFUNCTION,
	GUID_DEVCLASS_MULTIPORTSERIAL,
	GUID_DEVCLASS_NET            // �����豸��
	GUID_DEVCLASS_NETCLIENT,
	GUID_DEVCLASS_NETSERVICE,
	GUID_DEVCLASS_NETTRANS,
	GUID_DEVCLASS_NODRIVER,
	GUID_DEVCLASS_PCMCIA,
	GUID_DEVCLASS_PNPPRINTERS,
	GUID_DEVCLASS_PORTS          // �˿ڣ�COM �� LPT��
	GUID_DEVCLASS_PRINTER,
	GUID_DEVCLASS_PRINTERUPGRADE,
	GUID_DEVCLASS_PROCESSOR,
	GUID_DEVCLASS_SBP2,
	GUID_DEVCLASS_SCSIADAPTER    // SCSI �� RAID ������
	GUID_DEVCLASS_SECURITYACCELERATOR,
	GUID_DEVCLASS_SENSOR,
	GUID_DEVCLASS_SIDESHOW,
	GUID_DEVCLASS_SMARTCARDREADER,
	GUID_DEVCLASS_SOUND,
	GUID_DEVCLASS_SYSTEM         // ϵͳ
	GUID_DEVCLASS_TAPEDRIVE,
	GUID_DEVCLASS_UNKNOWN        // δ֪�豸
	GUID_DEVCLASS_USB            // ͨ�ô������߿�����
	GUID_DEVCLASS_VOLUME,
	GUID_DEVCLASS_VOLUMESNAPSHOT,
	GUID_DEVCLASS_WCEUSBS,
	GUID_DEVCLASS_WPD,

	*/
	static int getUnknownDeviceIdAndCompatibleIdList(CPointerList<CStringArray *> &hwids);
	static int getDeviceIdAndCompatibleIdList(CPointerList<CStringArray *> &hwids, DWORD conditionFilgerFlag=-1, CString conditionString="");

	// ��ȡ�豸��Ϣ�б�SP_DEVINFO_DATA�ṹ�б�
	int getDeviceInfoList();

	// ��ȡδ֪�豸�б�δ֪�豸��SP_DEVINFO_DATA�ṹ�б�
	int getUnkownDeviceInfoList(CPointerList<SP_DEVINFO_DATA *> *unkownDeviceInfoList);

	// ��ϵͳ�л�ȡָ�����ָ�������豸id��ָ������ģʽ���豸�б�SP_DEVINFO_DATA�ṹ�б�
	// catalog���豸���
	// devidArray���豸id�б�
	// filterMode������ģʽ���ο� FilterMode �ṹ�壩
	// filteredDeviceInfoList�����յõ����豸�б�
	int getFilteredDeviceInfoList(FilterMode mode, CString catalog, CStringArray *devidArray, CPointerList<SP_DEVINFO_DATA *> *filteredDeviceInfoList);


	// ��ϵͳ�л�ȡָ���������͡�ָ���������͵� toMatchString �ַ������豸��Ϣ�����豸��Ϣ�б�SP_DEVINFO_DATA�ṹ�б�
	// type���������ͣ�����ȫ����ָ���ࡢָ��������ָ���豸id
	// toMatchString����ƥ���ַ��������type���࣬���ʾ��������������������ʾ������������豸id�����ʾ�豸id
	// filteredDeviceInfoList����ȡ�����豸��Ϣ�б�
	int getFilteredDeviceInfoList(FilterType type, CString toMatchString, CPointerList<SP_DEVINFO_DATA *> *filteredDeviceInfoList);

	CString getDeviceDescription(SP_DEVINFO_DATA *devInfo);
	CString getDeviceClass(SP_DEVINFO_DATA *devInfo);
	void getDeviceIds(SP_DEVINFO_DATA *devInfo, CStringArray *strArray);

	//�����豸״̬(����/ͣ��),1Ϊ����,0Ϊͣ��
	BOOL SetDeviceStatus(DeviceInfo *theDevice,BOOL bStatusFlag);
	BOOL SetDeviceStatus(SP_DEVINFO_DATA *theDevice,BOOL bStatusFlag);

	// ���豸��Ϣ��SP_DEVINFO_DATA�ṹ�б�ת����DeviceInfo�ṹ�б�
	int toDeviceInfoStructList(CPointerList<SP_DEVINFO_DATA *> *deviceInfoList, CPointerList<DeviceInfo *> *deviceInfoStructList);

protected:
	CPointerList<SP_DEVINFO_DATA *> m_deviceInfoList;
	HDEVINFO m_hDevInfo;
};
