//Download by http://www.NewXing.com
#pragma once

#include <atlbase.h>
#include <windows.h>
#include <dshow.h>
#include <vector>
using namespace std;

#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
#include <qedit.h>

#include "ICallback.h"

#define MAX_FRIENDLY_NAME_LENGTH 1024
#define MAX_MONIKER_NAME_LENGTH 1024
#define MAX_PARAM_COUNT 16

//�豸����
struct TDeviceParam
{
	int width;				//�ֱ��ʿ�
	int height;				//�ֱ��ʸ�
	int avgTimePerFrame;	                //ÿ֡��ʱ��
	TDeviceParam() {
		Reset();
	}
	void Reset() {
		width = 0;
		height = 0;
		avgTimePerFrame = 1;
	}
	void Set(int w, int h, int avgTime) {
		width = w;
		height = h;
		avgTimePerFrame = avgTime;
	}
	void Copy(TDeviceParam& param) {
		Set(param.width, param.height, param.avgTimePerFrame);
	}
};

//�豸��Ϣ
struct TDeviceInfo
{
	WCHAR FriendlyName[MAX_FRIENDLY_NAME_LENGTH];   // �豸�Ѻ���  
	WCHAR MonikerName[MAX_MONIKER_NAME_LENGTH];     // �豸Moniker��
	int ParamCount;					// ��������
	TDeviceParam Params[MAX_PARAM_COUNT];		// ֧�ֵķֱ���
	TDeviceParam BestParam;                 //��õĲ���
	int BestParaIndex;  // ��ò����� Params �е�����

	TDeviceInfo() {
		Reset();
	}
	void Reset() {
		ParamCount = 0;
	}
	int SetResolution(int w, int h, int avgTime) {
		if (ParamCount >= MAX_PARAM_COUNT)
			return -1;
		for (int i = 0; i < ParamCount; i++) {
			if (Params[i].width == w && Params[i].height == h) {
				return 0;
			}
		}
		int insertIndex = 0;
		for (int i = 0; i < ParamCount; i++) {
			if (w > Params[i].width || h > Params[i].height) {
				break;
			}
			else {
				insertIndex++;
			}
		}
		for (int i = ParamCount - 1; i >= insertIndex; i--) {
			Params[i + 1].Copy(Params[i]);
		}
		Params[insertIndex].Set(w, h, avgTime);
		ParamCount++;
		if (w > BestParam.width) {
			BestParam.Set(w, h, avgTime);
			BestParaIndex=ParamCount-1;
		}
	}
};



// CSampleGrabberCB

class CSampleGrabberCB : public ISampleGrabberCB
{
public:
	long		m_lWidth;
	long		m_lHeight;
	CString		m_sFileName;
	BOOL		m_bSnapshot;

public:
	int m_action;  // 0-������ļ���1-bmp�ļ��Ļ������ص����ɻص��ߴ���

	void setCallback(ICameraCallback *callback){ m_callback=callback; };

private:
	ICameraCallback *m_callback;

public:

	CSampleGrabberCB();

	STDMETHODIMP_(ULONG) AddRef() { return 2; }
	STDMETHODIMP_(ULONG) Release() { return 1; }

	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);
	STDMETHODIMP SampleCB(double SampleTime, IMediaSample * pSample);
	STDMETHODIMP BufferCB(double dblSampleTime, BYTE * pBuffer, long lBufferSize);

private:
	BOOL SaveBitmap(BYTE* pBuffer, long lBufferSize);
};

// CCaptureVideo

class CCaptureVideo : public CWnd
{
	DECLARE_DYNAMIC(CCaptureVideo)

public:
	CCaptureVideo();
	virtual ~CCaptureVideo();

	int EnumDevices(CStringArray& listCamera);  // ֻ��ȡ�豸�����б�
	int EnumDevices(std::vector<TDeviceInfo>& deviceVec, REFGUID guidValue);  // ��ȡ�豸��Ϣ�б��������ơ�֧�ֵķֱ�������ȵ�
	HRESULT StartCapture(int iDeviceID);
	HRESULT StartCapture(int iDeviceID, int width, int height, int avgTimePerFrame);
	void StopCapture();

	void setSnapshotAction(int action){ m_action=action; };
	void setCallback(ICameraCallback *callback){ m_CB.setCallback(callback); }

private:
	IGraphBuilder *m_pGB;
	ICaptureGraphBuilder2* m_pCapture;
	IBaseFilter* m_pBF;
	IMediaControl* m_pMC;
	IVideoWindow* m_pVW;
	ATL::CComPtr<ISampleGrabber> m_pGrabber;
	
	CSampleGrabberCB m_CB;

	int		m_iCameraID;
	BOOL	m_bCaptureStart;
	BOOL	m_bFullScreen;

	int m_action;

	HRESULT InitCaptureGraphBuilder();
	bool BindFilter(int deviceId, IBaseFilter **pFilter);
	HRESULT SetupVideoWindow();
	void ResizeVideoWindow();
	void FreeMediaType(AM_MEDIA_TYPE& mt);
	void ReleaseCaptureRes();
	void UpdateMenuItemState(CMenu* pParent, UINT id, UINT nFlag);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCameraListItem(UINT id);

	afx_msg void OnPopmenuCapturestart();
	afx_msg void OnPopmenuCapturestop();
	afx_msg void OnPopmenuFullscreen();
	afx_msg void OnPopmenuSnapshot();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


