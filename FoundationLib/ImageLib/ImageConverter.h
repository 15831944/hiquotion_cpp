// ImageConverter.h: interface for the CImageConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGECONVERTER_H__8913A583_388D_46D3_BF9B_751DBC26A5C2__INCLUDED_)
#define AFX_IMAGECONVERTER_H__8913A583_388D_46D3_BF9B_751DBC26A5C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++/FoudationLib/ImageLib/include.h>

/*
	ͼ��ת����

	֧�� BMP��GIF��JPEG ��Exif ��PNG ��TIFF ��ICON��WMF ��EMF ��ʽ��ת

*/
/*
	�÷���

	�� stdafx.h ������������ݣ�

	// #include <afxdtctl.h>
	#define ULONG_PTR ULONG
	#include <GDIPlus/Includes/gdiplus.h>
	using namespace Gdiplus;
	#pragma comment(lib, "gdiplus.lib")

	ע�⣺��Щ������Ҫ�� std �����ռ�֮ǰ��ӣ��������֡���ģ����Ҫģ������б��Ĵ�����ʾ�����ܱ���ͨ����

	
*/
/*
	image/bmp
	image/gif
	image/jpeg
	image/pjpeg
	image/png
	image/x-icon
	image/x-jg
	image/x-png
	image/x-wmf
*/

#define FMT_BMP L"image/bmp"
#define FMT_GIF L"image/gif";
#define FMT_JPG L"image/jpeg";
#define FMT_PJPG L"image/pjpeg"
#define FMT_PNG L"image/png"
#define FMT_XICO L"image/x-icon"
#define FMT_XJG L"image/x-jg"
#define FMT_XPNG L"image/x-png"
#define FMT_XWMF L"image/x-wmf"

class CImageConverter  
{
public:
	CImageConverter();
	virtual ~CImageConverter();

	BOOL isInitialized();
	Status getStatus();

	// ��ͼ���ļ�ת��Ϊ bmp ��ʽ
	// ����ֵ��
	//  0���ɹ�
	// -1��Ŀ���ļ���չ��Ϊ��
	// -2����ȡ�洢��ʽ��class idʧ��
	int convertToBmp(CString srcFile, CString toFile);

protected:
	CString getFormatFromFileExt(CString ext);
	int GetImageCLSID(const WCHAR* format, CLSID* pCLSID);
	WCHAR* ToWChar(char *str);

protected:
	GdiplusStartupInput m_gdiplusStartupInput;
    ULONG_PTR m_pGdiToken;

	Status m_status;

};

#endif // !defined(AFX_IMAGECONVERTER_H__8913A583_388D_46D3_BF9B_751DBC26A5C2__INCLUDED_)
