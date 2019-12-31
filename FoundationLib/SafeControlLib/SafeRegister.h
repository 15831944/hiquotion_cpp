#pragma once

/*

	ʹ�÷���

	1���� �ؼ�����.cpp �� const GUID CDECL BASED_CODE _tlid = ��������������¶��壨VS2010 ����������� const GUID CDECL _tlid��

	const CATID CLSID_SafeItem =
			{ 0x5ded544d, 0xaf, 0x44fb, { 0x9f, 0xf1, 0xa, 0x1, 0xf5, 0x19, 0x26, 0xba } };

	���е� Class ID ���� �ؼ�����Ctrl.cpp �� IMPLEMENT_OLECREATE_EX ������Ǹ�������������ţ������ֻ��һ��ʾ����

	2���� �ؼ�����.cpp ���滻 DllRegister ��������Ϊ

		return CSafeRegister::registerServer(_tlid, CLSID_SafeItem, CATID_SafeForInitializing, CATID_SafeForScripting);

		�����鱣����ǰ��� AFX_MANAGE_STATE(_afxModuleAddrThis);��

	3���� �ؼ�����.cpp ���滻 DllUnregister ��������Ϊ

		return CSafeRegister::unregisterServer(_tlid, CLSID_SafeItem, CATID_SafeForInitializing, CATID_SafeForScripting, _wVerMajor, _wVerMinor);

		�����鱣����ǰ��� AFX_MANAGE_STATE(_afxModuleAddrThis);��

	4������ͨ������

*/

#include "comcat.h"
#include "Objsafe.h"

class CSafeRegister
{
public:
	CSafeRegister(void);
	~CSafeRegister(void);

	static HRESULT registerServer(GUID _tlid, GUID CLSID_SafeItem, CATID CATID_SafeForInitializing, CATID CATID_SafeForScripting);
	static HRESULT unregisterServer(GUID _tlid, GUID CLSID_SafeItem, CATID CATID_SafeForInitializing, CATID CATID_SafeForScripting, WORD _wVerMajor, WORD _wVerMinor);
};
