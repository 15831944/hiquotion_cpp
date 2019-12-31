// ImageConverter.cpp: implementation of the CImageConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageConverter::CImageConverter()
{
	m_status=GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);
}

CImageConverter::~CImageConverter()
{
	if(m_status!=GdiplusNotInitialized)
		GdiplusShutdown(m_pGdiToken);
}

BOOL CImageConverter::isInitialized()
{
	if(m_status==Ok)
		return TRUE;
	else
		return FALSE;
}

Status CImageConverter::getStatus()
{
	return m_status;
}

CString CImageConverter::getFormatFromFileExt(CString ext)
{
	CString capExt=ext;
	capExt.MakeUpper();
// BMP��GIF��JPEG ��Exif ��PNG ��TIFF ��ICON��WMF ��EMF
	if(capExt=="BMP")
		return FMT_BMP;
	if(capExt=="GIF")
		return FMT_GIF;
	if(capExt=="JPG" || capExt=="JPEG")
		return FMT_JPG;
	if(capExt=="PNG")
		return FMT_PNG;
	if(capExt=="TIF" || capExt=="TIFF")
		return FMT_XPNG;  // ???
	if(capExt=="ICO" || capExt=="ICON")
		return FMT_XICO;
	if(capExt=="WMF" || capExt=="EMF" || capExt=="EXIF")
		return FMT_XWMF;
	
	return FMT_BMP;
}

int CImageConverter::GetImageCLSID(const WCHAR* format, CLSID* pCLSID)
{
	//�õ���ʽΪformat��ͼ���ļ��ı���ֵ�����ʸø�ʽͼ���COM�����
		//GUIDֵ������pCLSID��
		UINT num = 0;
		UINT size = 0;
		ImageCodecInfo* pImageCodecInfo = NULL;
		GetImageEncodersSize(&num, &size);
		
		if(size == 0)
			return FALSE; // ������Ϣ������
		
		//�����ڴ�
		pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
		if(pImageCodecInfo == NULL)
			return FALSE; // ����ʧ��
		
		//���ϵͳ�п��õı��뷽ʽ��������Ϣ
		GetImageEncoders(num, size, pImageCodecInfo);
		
		//�ڿ��ñ�����Ϣ�в���format��ʽ�Ƿ�֧��
		for(UINT i = 0; i < num; ++i)
		{ //MimeType�����뷽ʽ�ľ�������
			if( wcscmp(pImageCodecInfo[i].MimeType, format) == 0 )
			{
				*pCLSID = pImageCodecInfo[i].Clsid;
				free(pImageCodecInfo);
				return TRUE;
			}
		}
		free(pImageCodecInfo);
		return FALSE;
}

WCHAR* CImageConverter::ToWChar(char *str)
{
    //�� GDI���У��й��ַ��Ĳ�������ȫ������ WCHAR ���͵�
    //�ú����ǽ���ͳ�ַ�������ת��
    static WCHAR buffer[1024];
    wcsset(buffer,0);
    MultiByteToWideChar(CP_ACP,0,str,strlen(str),buffer,1024);
    return buffer;
}

// ��ͼ���ļ�ת��Ϊ bmp ��ʽ
// ����ֵ��
//  0���ɹ�
// -1��Ŀ���ļ���չ��Ϊ��
// -2����ȡ�洢��ʽ��class idʧ��
int CImageConverter::convertToBmp(CString srcFile, CString toFile)
{
	Image image(ToWChar((LPTSTR)(LPCSTR)srcFile));
// 	CString ext=CFileOperation::getFileExtName(toFile);
// 	if(ext=="")
// 		return -1;
	CLSID clsid;
	if(!GetImageCLSID(FMT_BMP, &clsid))
		return -2;
	
	m_status=image.Save(ToWChar((LPTSTR)(LPCSTR)toFile), &clsid, NULL);

	return 0;
}
