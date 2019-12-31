// Picture.h: interface for the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_H__39525CCB_9249_4C72_AEEF_A8E53E6A71C8__INCLUDED_)
#define AFX_PICTURE_H__39525CCB_9249_4C72_AEEF_A8E53E6A71C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "Rectangle.h"

// cximage.lib jasper.lib Jpeg.lib libdcr.lib png.lib Tiff.lib zlib.lib
#pragma comment(lib,"cxImage\\cximage.lib")
#pragma comment(lib,"cxImage\\jasper.lib")
#pragma comment(lib,"cxImage\\Jpeg.lib")
#pragma comment(lib,"cxImage\\libdcr.lib")
#pragma comment(lib,"cxImage\\png.lib")
#pragma comment(lib,"cxImage\\Tiff.lib")
#pragma comment(lib,"cxImage\\zlib.lib")

#include <ximage.h>

class CPicture : public CRectangle  
{
public:
	CPicture();
	virtual ~CPicture();

	// ����
	
	virtual string getType();                     // ��ȡ���ƶ��������

	// ͼƬ·��
	string getPath() const { return m_path; }
	void setPath(string val);

	// �߿���
	// �ڲ��洢�����ݱ����濴���Ĵ� 2 ��
	virtual int getBorderWidth() const { return m_borderWidth; }
	virtual void setBorderWidth(int val) { m_borderWidth = val; }

	// ����

	virtual void draw(CDC *pDC);                // ��Ļ�ϻ���

	virtual void Serialize(CArchive &ar);
	
protected:
	DECLARE_SERIAL(CPicture);

	string m_path;
	CxImage m_image;
};

#endif // !defined(AFX_PICTURE_H__39525CCB_9249_4C72_AEEF_A8E53E6A71C8__INCLUDED_)
