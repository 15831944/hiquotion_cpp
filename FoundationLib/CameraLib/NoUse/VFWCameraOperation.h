#if !defined(AFX_VFWCAMERAOPERATION_H__FF245693_222A_4D91_9C89_479F4A17E36D__INCLUDED_)
#define AFX_VFWCAMERAOPERATION_H__FF245693_222A_4D91_9C89_479F4A17E36D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VFWCameraOperation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVFWCameraOperation window

#include "ivfwcallback.h"
#include <vfw.h>

#define MAX_VFW_DIRVER_COUNT 10
#define MAX_VFW_DEVICE_COUNT 100

enum PreviewMode
{
	Overlay,
	Preview,
};

LRESULT CALLBACK OnCaptureVideoData(HWND hWnd, LPVIDEOHDR lpVHdr);

class CVFWCameraOperation //: public CStatic
{
// 	typedef LRESULT (CALLBACK *VideoDataCallback)(CVFWCameraOperation *opr, LPVIDEOHDR lpVHdr);
// 	typedef LRESULT (CALLBACK *AudioDataCallback)(CVFWCameraOperation *opr, LPWAVEHDR lpWHdr);
// 	typedef LRESULT (CALLBACK *StatusCallback)(CVFWCameraOperation *opr, int nID, LPCSTR lpsz);
// 	typedef LRESULT (CALLBACK *ErrorCallback)(CVFWCameraOperation *opr, int nID, LPCSTR lpsz);
// 	typedef LRESULT (CALLBACK *CaptureControlCallback)(CVFWCameraOperation *opr, int nState);


	// biCompression��ֵ
	// 844715353   YUV2
	// 1498831189  UYVY,biBitCount=16(2 bytes)

	
// Construction
public:
	CVFWCameraOperation();
// 	CVFWCameraOperation(IVFWCallback *vfwCallback);

// Attributes
public:

// Operations
public:
// 	��ʼ��
// 		����vfw��Ƶ���񴰿�
// 		�����񴰿ڹ���������������Ϊ������Ӵ���
	BOOL create(CWnd *pWnd, CRect *rect, BOOL visible=FALSE);

	// ��ȡ�û�window
	CWnd * getUserWnd() const { return m_pWnd; }

	// ��ȡ�û�Rect
	CRect *getUserRect();

	// ��ȡ�û�DC
	HDC getUserDC();

	// ��ȡ����ͷ�Ĵ���
	HWND getCamaraWnd();

	BOOL getVisible() const { return m_visible; }

	// ��ȡ��ͼ����·��
	CString getImageSavePath() const { return m_path; }

	// ��ȡ�������û�����
	void setUserData(void *userData) { m_userData=userData; }
	void *getUserData() { return m_userData; }

	// ��ȡ��Ƶ֡ BitmapInfo �ṹ
	BITMAPINFO *getBitmapInfo() { return &m_videoInfo; }
	// ��ȡ��Ƶ��ʽ��Ϣ
	WAVEFORMATEX getAudioFormat() const { return m_audioInfo; }

	// ���ûص������Ľӿ�
	IVFWCallback * getVfwCallback() const;
	void setVfwCallback(IVFWCallback * val);

	// 	��ȡ����ͷ��������
	// 		����豸�б�Ϊ�գ����ȡ�豸
	// 		�����豸�б����
	int getCameraDriverCount();

	// ��ȡ��������
	int getCameraDeviceCount();

	// 	��ȡ�豸�б�
	// 		����豸�б�Ϊ�գ���ö���豸
	// 		�����豸�б�
	void getCameraDeviceList(CStringArray &cameraList);

	// ˢ������ͷ�б�
	void refreshCameraList();

	// 	���ӺͶϿ�ָ������ͷ
	BOOL connectCamera(unsigned int index=0);
	BOOL disconnectCamera();

	// 	��ָ������ͷ
	BOOL openCamera(unsigned int index=0);

// 	��ȡ�����ô��ڲ����������Ƿ񲶻������ȵ�
	BOOL getCameraParameter(PCAPTUREPARMS para);
	BOOL setCameraparameter(PCAPTUREPARMS para);

//	��ȡ��������Ƶ��ʽ
	BOOL getVideoFormat(PBITMAPINFO pInfo);
	BOOL setVideoFormat(PBITMAPINFO pInfo);

	// ��ȡ��������Ƶ��ʽ
	BOOL getAudioFormat(PWAVEFORMATEX pWaveInfo);
	BOOL setAudioFormat(PWAVEFORMATEX pWaveInfo);

// 	��ȡ��������Ƶ��С��������Ƶ��Сʱ��������ҲҪ���ű仯��
	BOOL getVideoSize(int &width, int &height);
	BOOL setVideoSize(int width, int height);

// 	����Ԥ����Overlay��Preview��Ĭ��Preview��
	BOOL startPreview(PreviewMode mode=Preview, int rate=25);

//	ֹͣԤ��
	BOOL stopPreview();

// 	��ȡ��Ƶͼ��
	BOOL isCaptureImage() const { return m_isCaptureImage; }
	// ʹ�� preview ģʽ
	BOOL captureImage(CString path);
	// ʹ�� capture ģʽ
	BOOL saveImage(unsigned char *data, int dataLen);

	// ��ʼ����
	BOOL startCapture(HDC hdc, int width=-1, int height=-1);

	// ��ʾ�����֡���ݣ�ÿ��ȡһ�����ݣ���Ҫ����һ�Σ�
	BOOL captureShow(unsigned char *data, int dstx, int dsty, int dstWidth=-1, int dstHeight=-1, int srcWidth=-1, int srcHeight=-1);

	// ֹͣ����
	void stopCapture();

// 	��ʾ����ͷ�豸���������
	BOOL showCameraProperty();

// 	capDlgVideoSource
// 	capDlgVideoFormat
	int showVideoSource();
	BOOL showVideoFormat();

// 	�ر�ָ������ͷ
	BOOL closeCamera();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVFWCameraOperation)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVFWCameraOperation();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVFWCameraOperation)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// 	DECLARE_MESSAGE_MAP()

protected:
	// ö������ͷ����������ͷ�����б�
	void enumCameraDrivers();
	// ö������ͷ�豸������ͷ�б�
	void enumCameraDevices();

private:
	// 	������Ƶ�ص�����
	// 	typedef LRESULT (CALLBACK* CAPVIDEOCALLBACK)  (HWND hWnd, LPVIDEOHDR lpVHdr);
	BOOL setVideoCallback();

	// 	������Ƶ�ص�����
	// 	typedef LRESULT (CALLBACK* CAPWAVECALLBACK)   (HWND hWnd, LPWAVEHDR lpWHdr);
	BOOL setAudioCallback();

	//	���ÿ��ƻص�����
	// 	typedef LRESULT (CALLBACK* CAPCONTROLCALLBACK)(HWND hWnd, int nState);
	BOOL setControlCallback();

	//	�����豸״̬�ص�����
	//	LRESULT CALLBACK capStatusCallback(HWND hWnd, int nID, LPCSTR lpsz);
	BOOL setStatusCallback();

	//	�����쳣�ص�����
	//	LRESULT CALLBACK capErrorCallback(HWND hWnd, int nID, LPCSTR lpsz);
	BOOL setErrorCallback();

public:
// 	VideoDataCallback OnVideoDataCallback;
// 	AudioDataCallback OnAudioDataCallback;
// 	CaptureControlCallback OnCaptureControlCallback;
// 	StatusCallback OnStatusCallback;
// 	ErrorCallback OnErrorCallback;

private:
	HWND m_hWndVideo;

	int m_vfwDevices[MAX_VFW_DEVICE_COUNT];
	int m_vfwDeviceCount;

	HDRAWDIB m_hDib;
	BITMAPINFO m_videoInfo;
	WAVEFORMATEX m_audioInfo;
	CStringArray m_cameraDriverList;
	CStringArray m_cameraList;

	CWnd *m_pWnd;
	HDC m_hdc;
	CRect m_rect;
	BOOL m_visible;
	BOOL m_isCaptureImage;
	CString m_path;

	void *m_userData;

	IVFWCallback *m_vfwCallback;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VFWCAMERAOPERATION_H__FF245693_222A_4D91_9C89_479F4A17E36D__INCLUDED_)
