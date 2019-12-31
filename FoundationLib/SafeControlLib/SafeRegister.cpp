#include "StdAfx.h"
#include "SafeRegister.h"
#include "cathelp.h"

CSafeRegister::CSafeRegister(void)
{
}

CSafeRegister::~CSafeRegister(void)
{
}

HRESULT CSafeRegister::registerServer(GUID _tlid, GUID CLSID_SafeItem, CATID CATID_SafeForInitializing, CATID CATID_SafeForScripting)
{
	HRESULT hr;    // HResult used by Safety Functions

	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
	{
#ifdef _UNICODE
		AfxMessageBox(L"AfxOleRegisterTypeLib ����ʧ�ܣ�");
#else
		AfxMessageBox("AfxOleRegisterTypeLib ����ʧ�ܣ�");
#endif
		return ResultFromScode(SELFREG_E_TYPELIB);
	}

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
	{
#ifdef _UNICODE
		AfxMessageBox(L"COleObjectFactoryEx::UpdateRegistryAll ����ʧ�ܣ�");
#else
		AfxMessageBox("COleObjectFactoryEx::UpdateRegistryAll ����ʧ�ܣ�");
#endif
		return ResultFromScode(SELFREG_E_CLASS);
	}

	// Mark the control as safe for initializing.

	hr = CreateComponentCategory(CATID_SafeForInitializing, 
		"Controls safely initializable from persistent data!", 51);
	if (FAILED(hr))
	{
#ifdef _UNICODE
		AfxMessageBox(L"CreateComponentCategory(CATID_SafeForInitializing) ����ʧ�ܣ�");
#else
		AfxMessageBox("CreateComponentCategory(CATID_SafeForInitializing) ����ʧ�ܣ�");
#endif
		return hr;
	}

	hr = RegisterCLSIDInCategory(CLSID_SafeItem, 
		CATID_SafeForInitializing);
	if (FAILED(hr))
	{
#ifdef _UNICODE
		AfxMessageBox(L"RegisterCLSIDInCategory(CLSID_SafeItem) ����ʧ�ܣ�");
#else
		AfxMessageBox("RegisterCLSIDInCategory(CLSID_SafeItem) ����ʧ�ܣ�");
#endif
		return hr;
	}

	// Mark the control as safe for scripting.

	hr = CreateComponentCategory(CATID_SafeForScripting, 
#ifdef _UNICODE
		(LPSTR)"Controls safely scriptable!"
#else
		"Controls safely scriptable!"
#endif
		, 27);
	if (FAILED(hr))
	{
#ifdef _UNICODE
		AfxMessageBox(L"CreateComponentCategory(CATID_SafeForScripting) ����ʧ�ܣ�");
#else
		AfxMessageBox("CreateComponentCategory(CATID_SafeForScripting) ����ʧ�ܣ�");
#endif
		return hr;
	}

	hr = RegisterCLSIDInCategory(CLSID_SafeItem, 
		CATID_SafeForScripting);
	if (FAILED(hr))
	{
#ifdef _UNICODE
		AfxMessageBox(L"RegisterCLSIDInCategory ����ʧ�ܣ�");
#else
		AfxMessageBox("RegisterCLSIDInCategory ����ʧ�ܣ�");
#endif
		return hr;
	}

	return NOERROR;
}

HRESULT CSafeRegister::unregisterServer(GUID _tlid, GUID CLSID_SafeItem, CATID CATID_SafeForInitializing, CATID CATID_SafeForScripting, WORD _wVerMajor, WORD _wVerMinor)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);  

	// ɾ���ؼ���ʼ����ȫ���.   
	HRESULT hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);  

	if (FAILED(hr))  
		return hr;  

	// ɾ���ؼ��ű���ȫ���   
	hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);  

	if (FAILED(hr))  
		return hr;  

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))  
		return ResultFromScode(SELFREG_E_TYPELIB);  

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))  
		return ResultFromScode(SELFREG_E_CLASS);  

	return NOERROR;
}
