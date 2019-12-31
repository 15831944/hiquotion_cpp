// VFWCameraOperation.cpp : implementation file
//

#include "stdafx.h"
#include "VFWCameraOperation.h"
#include <math.h>
#include <C++\FoudationLib\ColorSystemLib\ColorSystemConverter.h>
#include <C++\FoudationLib\BitmapLib\BitmapOperation.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LRESULT CALLBACK OnCaptureVideoData(HWND hWnd,LPVIDEOHDR lphdr)
{
	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
	
	if(opr==NULL )
		return -1;

	if(opr->getVfwCallback())
		opr->getVfwCallback()->OnVideoDataReceived(lphdr);

// 	if(opr->OnVideoDataCallback)
// 		return opr->OnVideoDataCallback(opr, lphdr);
	
	return 0;
}

LRESULT CALLBACK OnCaptureAudioData(HWND hWnd,LPWAVEHDR lpWHdr)
{
	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
	
	if(opr==NULL )
		return -1;

	if(opr->getVfwCallback())
		opr->getVfwCallback()->OnAudioDataReceived(lpWHdr);
	
// 	if(opr->OnAudioDataCallback)
// 		return opr->OnAudioDataCallback(opr, lpWHdr);
	
	return 0;
}

LRESULT CALLBACK OnStatus(HWND hWnd, int nID, LPCSTR lpsz)
{
	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
	
	if(opr==NULL )
		return -1;

	if(opr->getVfwCallback())
		opr->getVfwCallback()->OnStatus(nID, lpsz);
	
// 	if(opr->OnStatusCallback)
// 		return opr->OnStatusCallback(opr, nID, lpsz);
	
	return 0;
}

LRESULT CALLBACK OnError(HWND hWnd, int nID, LPCSTR lpsz)
{
	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
	
	if(opr==NULL )
		return -1;

	if(opr->getVfwCallback())
		opr->getVfwCallback()->OnError(nID, lpsz);
	
// 	if(opr->OnErrorCallback)
// 		return opr->OnErrorCallback(opr, nID, lpsz);
	
	return 0;
}

// ��������Ժ���Ƶ���ݾͻ�ȡ�����ˣ���֪��Ϊʲô
// LRESULT CALLBACK OnControl(HWND hWnd, int nState )
// {
// 	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
// 	
// 	if(opr==NULL )
// 		return -1;
// 
// 	if(opr->getVfwCallback())
// 		opr->getVfwCallback()->OnCaptureControl(nState);
// 	
// // 	if(opr->OnCaptureControlCallback)
// // 		return opr->OnCaptureControlCallback(opr, nState);
// 	
// 	return 0;
// }

/////////////////////////////////////////////////////////////////////////////
// CVFWCameraOperation

CVFWCameraOperation::CVFWCameraOperation()
{
	m_hDib=NULL;
	m_isCaptureImage=FALSE;
	m_path="";
	m_userData=NULL;

	m_vfwCallback=NULL;

	memset(&m_audioInfo, 0x00, sizeof(WAVEFORMATEX));

	m_vfwDeviceCount=0;
	memset(m_vfwDevices, 0x00, MAX_VFW_DEVICE_COUNT * sizeof(int));

// 	OnVideoDataCallback=NULL;
// 	OnAudioDataCallback=NULL;
// 	OnStatusCallback=NULL;
// 	OnErrorCallback=NULL;
// 	OnCaptureControlCallback=NULL;
}

// CVFWCameraOperation::CVFWCameraOperation(IVFWCallback *vfwCallback)
// {
// 	m_hDib=NULL;
// 	m_isCaptureImage=FALSE;
// 	m_path="";
// 	m_userData=NULL;
// 
// 	m_vfwCallback=vfwCallback;
// }


CVFWCameraOperation::~CVFWCameraOperation()
{
}


// BEGIN_MESSAGE_MAP(CVFWCameraOperation, CStatic)
// 	//{{AFX_MSG_MAP(CVFWCameraOperation)
// 		// NOTE - the ClassWizard will add and remove mapping macros here.
// 	//}}AFX_MSG_MAP
// END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVFWCameraOperation message handlers

// 	��ʼ��
// 		����vfw��Ƶ���񴰿�
// 		�����񴰿ڹ���������������Ϊ������Ӵ���
BOOL CVFWCameraOperation::create(CWnd *pWnd, CRect *rect, BOOL visible)
{
	m_pWnd=pWnd;
	if(rect)
	{
		m_rect.left=rect->left;
		m_rect.top=rect->top;
		m_rect.right=rect->right;
		m_rect.bottom=rect->bottom;
		m_visible=visible;
	}

	UINT flag=WS_CHILD;
	if(m_visible)
		flag |= WS_VISIBLE;

	m_hWndVideo=capCreateCaptureWindow(NULL,flag,m_rect.left,m_rect.top,m_rect.Width(),m_rect.Height(),m_pWnd->GetSafeHwnd(),0);
	if(!m_hWndVideo)
		return FALSE;

	capSetUserData(m_hWndVideo, this);

	return TRUE;
}

// ��ȡ�û�Rect
CRect *CVFWCameraOperation::getUserRect()
{
	return &m_rect;
}

// ��ȡ�û�DC
HDC CVFWCameraOperation::getUserDC()
{
	return m_hdc;
}

// ��ȡ����ͷ�Ĵ���
HWND CVFWCameraOperation::getCamaraWnd()
{
	return m_hWndVideo;
}

// ö������ͷ����������ͷ�����б�
void CVFWCameraOperation::enumCameraDrivers()
{
	char camName[MAX_PATH], ver[MAX_PATH];
	m_cameraDriverList.RemoveAll();
	m_vfwDeviceCount=0;
	for(int i=0;i<MAX_VFW_DIRVER_COUNT;i++)
	{
		if(capGetDriverDescription(i, camName, MAX_PATH, ver, MAX_PATH))
		{
			m_cameraDriverList.Add(camName);
		}
	}
}

// ö������ͷ�豸������ͷ�б�
void CVFWCameraOperation::enumCameraDevices()
{
	if(!m_hWndVideo)
		return;

	for(int j=m_vfwDeviceCount;j<MAX_VFW_DEVICE_COUNT;j++)
	{
		if(connectCamera(j))
		{
			m_vfwDevices[m_vfwDeviceCount]=j;
			m_vfwDeviceCount++;
			CString devDesc;
			devDesc.Format("��Ƶ�豸 #%d", m_vfwDeviceCount);
			m_cameraList.Add(devDesc);
			disconnectCamera();
		}
	}
}


// 	��ȡ�豸����
// 		����豸�б�Ϊ�գ����ȡ�豸
// 		�����豸�б����
int CVFWCameraOperation::getCameraDriverCount()
{
	if(m_cameraDriverList.GetSize()>0)
		return m_cameraDriverList.GetSize();

	enumCameraDrivers();

	return m_cameraDriverList.GetSize();
}

// 	��ȡ�豸�б�
// 		����豸�б�Ϊ�գ���ö���豸
// 		�����豸�б�
void CVFWCameraOperation::getCameraDeviceList(CStringArray &cameraList)
{
	if(m_cameraDriverList.GetCount()<=0)
		enumCameraDrivers();

	if(m_cameraDriverList.GetCount()<=0)
		return;

	if(m_cameraList.GetCount()<=0)
		enumCameraDevices();

	if(m_cameraList.GetCount()<=0)
		return;

	cameraList.RemoveAll();
	for(int i=0;i<m_cameraList.GetCount();i++)
		cameraList.Add(m_cameraList.GetAt(i));
}

// ˢ������ͷ�б�
void CVFWCameraOperation::refreshCameraList()
{
	enumCameraDrivers();
}

// 	����ָ������ͷ
BOOL CVFWCameraOperation::connectCamera(unsigned int index)
{
	if(!capDriverConnect(m_hWndVideo, index))
		return FALSE;
	else
		return TRUE;
}

// 	��ָ������ͷ
BOOL CVFWCameraOperation::openCamera(unsigned int index)
{
	if(!capDriverConnect(m_hWndVideo, index))
		return FALSE;

	CAPTUREPARMS para;
	if(!getCameraParameter(&para))
		return FALSE;

	para.fAbortLeftMouse=FALSE;
	para.fAbortRightMouse=FALSE;
	para.fCaptureAudio=FALSE;
// 	para.dwRequestMicroSecPerFrame=6667;
// 	para.fMakeUserHitOKToCapture=FALSE;
	para.fYield=TRUE;     // ʹ�ñ�����ҵ
	para.wPercentDropForError = 50;   // ������ʧ�İٷֱ�

	if(!setCameraparameter(&para))
		return FALSE;

	return TRUE;
}

// 	��ȡ�����ô��ڲ����������Ƿ񲶻������ȵ�
BOOL CVFWCameraOperation::getCameraParameter(PCAPTUREPARMS para)
{
	return capCaptureGetSetup(m_hWndVideo, para, sizeof(CAPTUREPARMS));
}

BOOL CVFWCameraOperation::setCameraparameter(PCAPTUREPARMS para)
{
	return capCaptureSetSetup(m_hWndVideo, para, sizeof(CAPTUREPARMS));
}

//	��ȡ��������Ƶ��ʽ��Ϣ
BOOL CVFWCameraOperation::getVideoFormat(PBITMAPINFO pInfo)
{
	return capGetVideoFormat(m_hWndVideo, pInfo, sizeof(BITMAPINFO));
}

BOOL CVFWCameraOperation::setVideoFormat(PBITMAPINFO pInfo)
{
	return capSetVideoFormat(m_hWndVideo, pInfo, sizeof(BITMAPINFO));
}

// ��ȡ��������Ƶ��ʽ
BOOL CVFWCameraOperation::getAudioFormat(PWAVEFORMATEX pWaveInfo)
{
	return capGetAudioFormat(m_hWndVideo, pWaveInfo, sizeof(WAVEFORMATEX));
}

BOOL CVFWCameraOperation::setAudioFormat(PWAVEFORMATEX pWaveInfo)
{
	return capSetAudioFormat(m_hWndVideo, pWaveInfo, sizeof(WAVEFORMATEX));
}

// 	��ȡ��������Ƶ��С��������Ƶ��Сʱ��������ҲҪ���ű仯��
BOOL CVFWCameraOperation::getVideoSize(int &width, int &height)
{
	BITMAPINFO info;
	if(!capGetVideoFormat(m_hWndVideo, &info, sizeof(BITMAPINFO)))
	{
		width=0;
		height=0;
		return FALSE;
	}

	width=info.bmiHeader.biWidth;
	height=info.bmiHeader.biHeight;
	return TRUE;
}

BOOL CVFWCameraOperation::setVideoSize(int width, int height)
{
	BITMAPINFO info;
	if(!capGetVideoFormat(m_hWndVideo, &info, sizeof(BITMAPINFO)))
		return FALSE;
	
	info.bmiHeader.biWidth=width;
	info.bmiHeader.biHeight=height;

	if(!capSetVideoFormat(m_hWndVideo, &info, sizeof(BITMAPINFO)))
		return FALSE;

	return TRUE;
}

// 	����Ԥ����Overlay��Preview��Ĭ��Preview��
BOOL CVFWCameraOperation::startPreview(PreviewMode mode, int rate)
{
	UINT style=GetWindowLong(m_hWndVideo, GWL_STYLE);
	style |= WS_VISIBLE;
	SetWindowLong(m_hWndVideo, GWL_STYLE, style);
    //����Ԥ��ʱ�ı��� 
	capPreviewScale(m_hWndVideo, TRUE);

    //����Ԥ��ʱ��֡Ƶ�� 
	capPreviewRate(m_hWndVideo, rate);
	
	switch(mode)
	{
	case Overlay:
// 		capPreview(m_hWndVideo, 0);
		capOverlay(m_hWndVideo, 1);
		break;
	case Preview:
// 		capOverlay(m_hWndVideo, 0);
		capPreview(m_hWndVideo, 1);
		break;
	}
	return TRUE;
}

//	ֹͣԤ��
BOOL CVFWCameraOperation::stopPreview()
{
	capOverlay(m_hWndVideo, 0);
	capPreview(m_hWndVideo, 0);
	capCaptureAbort(m_hWndVideo);  
	UINT style=GetWindowLong(m_hWndVideo, GWL_STYLE);
	style &= ~WS_VISIBLE;
	SetWindowLong(m_hWndVideo, GWL_STYLE, style);
	return TRUE;
}

// 	��ȡ��Ƶͼ�񣨻��BitmapInfoHeader��Bitmap���ݣ�����ֱ�ӱ��浽�ļ������֣�
BOOL CVFWCameraOperation::captureImage(CString path)
{
	m_path=path;
	m_isCaptureImage=TRUE;

	return TRUE;
}

BOOL CVFWCameraOperation::saveImage(unsigned char *data, int dataLen)
{
	m_isCaptureImage=FALSE;

	if(m_path=="")
		return FALSE;

	int width=m_videoInfo.bmiHeader.biWidth;
	int height=m_videoInfo.bmiHeader.biHeight;

	unsigned char *dt=NULL;
	unsigned char *dtrgb=NULL;
	unsigned char *dtrgb2=NULL;
	unsigned long len=0;
	if(m_videoInfo.bmiHeader.biCompression==844715353)
	{
		// YUV2 to RGB( tested RGB to YUV420Planar, and then to RGB, test success!)

// 		dtrgb=new unsigned char[dataLen*3/2];
// 		dtrgb2=new unsigned char[dataLen*3/2];
// 		ColorSystemConverter::YUY2ToRGB(data, dtrgb, dataLen);
// 		ColorSystemConverter::Vertical(dtrgb, width, height, dtrgb2);
// 		delete dtrgb;
// 		dtrgb=NULL;
// 		dt=dtrgb2;
// 		len=dataLen*3/2;
// 
// 		unsigned char *yuv=new unsigned char[len];
// 		ColorSystemConverter::RGBToYUV420Planar(dt, width, height, yuv);
// 		unsigned char *rgb=new unsigned char[len];
// 		ColorSystemConverter::YUV420PlanarToRGB(yuv, width, height, dtrgb2);
// 
// 		delete yuv;
// 		delete rgb;
// 
// 		dt=dtrgb2;

		// tested YUV2 to YUV420Planar, and then to RGB

		unsigned char *dtyuv420=new unsigned char[dataLen];
		CColorSystemConverter::YUV2ToYUV420Planar(data, width, height, dtyuv420);
		dtrgb=new unsigned char[dataLen * 3 / 2];
		CColorSystemConverter::YUV420PlanarToRGB(dtyuv420, width, height, dtrgb);
		dtrgb2=new unsigned char[dataLen * 3 / 2];
		CColorSystemConverter::Vertical(dtrgb, width, height, dtrgb2);
 		delete dtrgb;
		delete dtyuv420;

		len=dataLen*3/2;
		
		dt=dtrgb2;
	}
	else
	{
		dt=data;
		len=dataLen;
	}

	BITMAPINFOHEADER infoHead;
	memcpy(&infoHead, &m_videoInfo.bmiHeader, sizeof(BITMAPINFOHEADER));
	if(infoHead.biCompression==844715353)
	{
		infoHead.biBitCount=24;
		infoHead.biCompression=BI_RGB;
		infoHead.biSizeImage=0;
	}
	
	if(!CBitmapOperation::saveBmp(m_path, infoHead, &m_videoInfo.bmiColors[0], dt, len))
	{
		if(dtrgb2)
			delete dtrgb2;
		return FALSE;
	}

	if(dtrgb2)
		delete dtrgb2;

	return TRUE;
}

// ��ʼ����
BOOL CVFWCameraOperation::startCapture(HDC hdc, int width, int height)
{
	m_hdc=hdc;

	m_hDib=DrawDibOpen();
	if(!m_hDib)
		return FALSE;

	if(!getVideoFormat(&m_videoInfo))
		return FALSE;

	if(!getAudioFormat(&m_audioInfo))
	{
		MessageBox(0, "��ȡ��Ƶ��ʽ��Ϣʧ�ܣ�", "", 0);
		return FALSE;
	}

	if(!DrawDibBegin(m_hDib,
				m_hdc,
				width,				// don't stretch
				height,				// don't stretch
				&m_videoInfo.bmiHeader,
				m_videoInfo.bmiHeader.biWidth,         // width of image
				m_videoInfo.bmiHeader.biHeight,        // height of image
				DDF_HURRYUP //0				
				))
		return FALSE;

	//���Ҫ������Ƶ������Ҫʹ�ú���ָ���������ļ������򽫻��Զ�����AVI�ļ�   
	if(!capCaptureSequenceNoFile(m_hWndVideo))
		return FALSE;

	return TRUE;
}

// ��ʾ�����֡����
BOOL CVFWCameraOperation::captureShow(unsigned char *data, int dstx, int dsty, int dstWidth, int dstHeight, int srcWidth, int srcHeight)
{
	int width=srcWidth;
	int height=srcHeight;

	if(width==-1)
		width=m_videoInfo.bmiHeader.biWidth;
	if(height==-1)
		height=m_videoInfo.bmiHeader.biHeight;

	/*********************************************************************

	DrawDib Flags

	**********************************************************************/
// #define DDF_0001            0x0001          /* ;Internal */
// #define DDF_UPDATE          0x0002          /* re-draw the last DIB */
// #define DDF_SAME_HDC        0x0004          /* HDC same as last call (all setup) */
// #define DDF_SAME_DRAW       0x0008          /* draw params are the same */
// #define DDF_DONTDRAW        0x0010          /* dont draw frame, just decompress */
// #define DDF_ANIMATE         0x0020          /* allow palette animation */
// #define DDF_BUFFER          0x0040          /* always buffer image */
// #define DDF_JUSTDRAWIT      0x0080          /* just draw it with GDI */
// #define DDF_FULLSCREEN      0x0100          /* use DisplayDib */
// #define DDF_BACKGROUNDPAL   0x0200	    /* Realize palette in background */
// #define DDF_NOTKEYFRAME     0x0400          /* this is a partial frame update, hint */
// #define DDF_HURRYUP         0x0800          /* hurry up please! */
// #define DDF_HALFTONE        0x1000          /* always halftone */
// #define DDF_2000            0x2000          /* ;Internal */
// 
// #define DDF_PREROLL         DDF_DONTDRAW    /* Builing up a non-keyframe */
// #define DDF_SAME_DIB        DDF_SAME_DRAW
// #define DDF_SAME_SIZE       DDF_SAME_DRAW

	BOOL ret=DrawDibDraw(m_hDib,
		m_hdc,
		dstx,		// dest : left pos
		dsty,		// dest : top pos
		dstWidth,					 // don't zoom x
		dstHeight,					 // don't zoom y
		&m_videoInfo.bmiHeader,			 // bmp header info
		data,					 // bmp data
// 		dstx,					 // src :left
// 		dsty,					 // src :top
		0,
		0,
		width,				 // src : width
		height,				 // src : height
		DDF_SAME_DRAW			 // use prev params....
		);

	return ret;
}

// ֹͣ����
void CVFWCameraOperation::stopCapture()
{
// 	capSetCallbackOnVideoStream(m_hWndVideo, NULL);
// 	capSetCallbackOnWaveStream(m_hWndVideo, NULL);
// 	capSetCallbackOnCapControl(m_hWndVideo, NULL);
// 	capSetCallbackOnStatus(m_hWndVideo, NULL);
// 	capSetCallbackOnError(m_hWndVideo, NULL);

	if(m_hDib)
	{
		DrawDibEnd(m_hDib);
		DrawDibClose(m_hDib);
		m_hDib=NULL;
	}
	
	capCaptureStop(m_hWndVideo);
	//ֹͣ����   
	capCaptureAbort(m_hWndVideo);
}

// 	// 	������Ƶ�ص�����
// 	BOOL CVFWCameraOperation::setVideoCallback(VideoDataCallback videoCallback)
// 	{
// 		OnVideoDataCallback=videoCallback;
// 		return capSetCallbackOnVideoStream(m_hWndVideo, OnCaptureVideoData);
// 	}
// 
// 	// 	������Ƶ�ص�����
// 	BOOL CVFWCameraOperation::setAudioCallback(AudioDataCallback audioCallback)
// 	{
// 		OnAudioDataCallback=audioCallback;
// 		return capSetCallbackOnWaveStream(m_hWndVideo, OnCaptureAudioData);
// 	}
// 
// 	//	���ÿ��ƻص�����
// 	// 	typedef LRESULT (CALLBACK* CAPCONTROLCALLBACK)(HWND hWnd, int nState);
// 	BOOL CVFWCameraOperation::setControlCallback(CaptureControlCallback controlCallback)
// 	{
// 		OnCaptureControlCallback=controlCallback;
// 		return capSetCallbackOnCapControl(m_hWndVideo, OnControl);
// 	}
// 
// 	//	�����豸״̬�ص�����
// 	//	LRESULT CALLBACK capStatusCallback(HWND hWnd, int nID, LPCSTR lpsz);
// 	BOOL CVFWCameraOperation::setStatusCallback(StatusCallback statusCallback)
// 	{
// 		OnStatusCallback=statusCallback;
// 		return capSetCallbackOnStatus(m_hWndVideo, OnStatus);
// 	}
// 
// 	//	�����쳣�ص�����
// 	BOOL CVFWCameraOperation::setErrorCallback(ErrorCallback errorCallback)
// 	{
// 		OnErrorCallback=errorCallback;
// 		return capSetCallbackOnError(m_hWndVideo, OnError);
// 	}

// 	��ʾ����ͷ�豸���������
BOOL CVFWCameraOperation::showCameraProperty()
{
	return capDlgVideoSource(m_hWndVideo);
}

// 	capDlgVideoSource
// 	capDlgVideoFormat
int CVFWCameraOperation::showVideoSource()
{
	CAPDRIVERCAPS CapDrvCaps;
	ZeroMemory(&CapDrvCaps, sizeof(CapDrvCaps));
	if(!capDriverGetCaps(m_hWndVideo, &CapDrvCaps, sizeof (CAPDRIVERCAPS)))
		return -1;

	if(!CapDrvCaps.fHasDlgVideoSource)
		return -2;

	if(!capDlgVideoSource(m_hWndVideo))
		return -3;

	return 0;
}

BOOL CVFWCameraOperation::showVideoFormat()
{
	return capDlgVideoFormat(m_hWndVideo);
}

// ���ûص������Ľӿ�
IVFWCallback *CVFWCameraOperation::getVfwCallback() const
{
	return m_vfwCallback;
}

void CVFWCameraOperation::setVfwCallback(IVFWCallback * val)
{
	m_vfwCallback = val;
	setVideoCallback();
	setAudioCallback();
	setStatusCallback();
	setErrorCallback();
}

// 	�ر�ָ������ͷ
BOOL CVFWCameraOperation::closeCamera()
{
    // Disable the callback function..
	capSetCallbackOnVideoStream(m_hWndVideo, NULL);
	capSetCallbackOnWaveStream(m_hWndVideo, NULL);
	capSetCallbackOnCapControl(m_hWndVideo, NULL);
	capSetCallbackOnStatus(m_hWndVideo, NULL);
	capSetCallbackOnError(m_hWndVideo, NULL);
	
	Sleep(300);		// This delay is important...
	
	//������ͬ�������Ͽ�   
	return capDriverDisconnect(m_hWndVideo);
}

BOOL CVFWCameraOperation::disconnectCamera()
{
	return capDriverDisconnect(m_hWndVideo);
}

// 	������Ƶ�ص�����
// 	typedef LRESULT (CALLBACK* CAPVIDEOCALLBACK)  (HWND hWnd, LPVIDEOHDR lpVHdr);
BOOL CVFWCameraOperation::setVideoCallback()
{
	return capSetCallbackOnVideoStream(m_hWndVideo, OnCaptureVideoData);
}

// 	������Ƶ�ص�����
// 	typedef LRESULT (CALLBACK* CAPWAVECALLBACK)   (HWND hWnd, LPWAVEHDR lpWHdr);
BOOL CVFWCameraOperation::setAudioCallback()
{
	return capSetCallbackOnWaveStream(m_hWndVideo, OnCaptureAudioData);
}

//	���ÿ��ƻص�����
// ��������Ժ���Ƶ���ݾͻ�ȡ�����ˣ���֪��Ϊʲô
// 	typedef LRESULT (CALLBACK* CAPCONTROLCALLBACK)(HWND hWnd, int nState);
// BOOL CVFWCameraOperation::setControlCallback()
// {
// 	return capSetCallbackOnCapControl(m_hWndVideo, OnControl);
// }

//	�����豸״̬�ص�����
//	LRESULT CALLBACK capStatusCallback(HWND hWnd, int nID, LPCSTR lpsz);
BOOL CVFWCameraOperation::setStatusCallback()
{
	return capSetCallbackOnStatus(m_hWndVideo, OnStatus);
}

//	�����쳣�ص�����
//	LRESULT CALLBACK capErrorCallback(HWND hWnd, int nID, LPCSTR lpsz);
BOOL CVFWCameraOperation::setErrorCallback()
{
	return capSetCallbackOnError(m_hWndVideo, OnError);
}
