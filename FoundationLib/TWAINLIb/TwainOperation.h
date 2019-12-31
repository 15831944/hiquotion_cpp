#pragma once
#include "TWAINDSM/include/TwainApp.h"

#ifdef _DEBUG
#pragma comment(lib, "C++/FoundationLib/TWAINLIb/TWAINDSM/lib/debug/TWAINDSM.lib")
#else
#pragma comment(lib, "C++/FoundationLib/TWAINLIb/TWAINDSM/lib/release/TWAINDSM.lib")
#endif

// #pragma comment(lib, "C++/FoundationLib/TWAINLIb/TWAINDSM/lib/FreeImage.lib")

// ȥ���˶� FreeImage �����ã���������ٰ��� FreeImage.h
// ͬʱ TiffWriter ��Ҳ�޷���ʹ��

#include <C++/FoundationLib/EventLib/EventEmu-��MFC���¼�����/IEventRaisable.h>
#include <C++/FoundationLib/EventLib/EventEmu-��MFC���¼�����/Delegate.h>

// TWAIN Э���װ��
// ���Բ���֧�� TWAIN Э����豸����������ǡ�ɨ���ǵȣ�
// �����ͨ�� TWAIN Э�飬���豸�Լ���ɨ�����ɨ�貢�ύɨ�赽��ͼƬ
// ��������豸�ύͼƬ��ʱ���׳� DataGot �¼����ϲ�Ӧ�ó��򼴿ɻ�ȡ��ͼƬ�Ļ�����
// ÿ��ͼƬ�׳�һ�� DataGot �¼�
// DataGot �¼����ṩ��ͼƬ�� BMP ��ʽ������ͼƬ����Ҫ�ϲ�������о���ͼƬ��һ���Ĵ�������ѹ�����ϴ���
class CTwainOperation : public TwainApp, public IEventRaisable
{
public:
	CTwainOperation(HWND hwnd = NULL);
	virtual ~CTwainOperation();

	int getDataSourceCount();
	int getDataSourceNames(CStringArray &dataSourceNames);
	BOOL showUI(HWND parent, int dsIndex = 0);

	CString getSavePath() { return m_strSavePath.c_str(); }
	void setSavePath(CString savePath) { m_strSavePath = savePath.GetBuffer(savePath.GetLength()); }

protected:
	void StartScan();
	void Transfer();

protected:
	BOOL        m_bKeepEnabled;         /**< Keep the DS GUI displayed after a scan - User press cancel to finish scanning */
	bool        m_bBusy;                /**< The application is waiting for a responce from TWAIN messages*/

public:
	CDelegate DataGot;
};

