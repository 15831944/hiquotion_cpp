// FilledArea.cpp: implementation of the CFilledArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FilledArea.h"

#include <C++\3rdParty\GDIPlus\Includes\GdiplusTypes.h>
#include <C++\3rdParty\GDIPlus\Includes\GdiplusGpStubs.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilledArea::CFilledArea()
{
	m_shape=Rect;
	m_bgColor=RGB(0,0,0);
	m_fillType=Solid;
	m_bgTransparent=FALSE;
	m_hatchStyle=HS_HORIZONTAL;     // ���� Hatch ���
	m_hatchColor=RGB(0,0,0); // ���� Hatch ����ǰ��ɫ
	m_gradientType=Horizen;  // ���� Gradient ���
	m_gradientColor1=RGB(0,0,0);    // ���ڽ������ĵ�һ����ɫ
	m_gradientColor2=RGB(255,255,255);    // ���ڽ������ĵڶ�����ɫ
	m_picture=NULL;    // ����ͼƬ���
	m_roundPoint.x=5;   // ����Բ�Ǿ��ε�Բ����С
	m_roundPoint.y=5;   // ����Բ�Ǿ��ε�Բ����С
	m_fillFigure=NULL;  // Figure ��ʽ���
}

CFilledArea::~CFilledArea()
{

}

void CFilledArea::draw(CDC *pDC)                // ��Ļ�ϻ���
{
	if(!pDC)
		return;

	CPen pen;
	CPen *oldPen=NULL;
	
	CBrush brush;
	CBrush *oldBrush=NULL;
	Gdiplus::Graphics graphics(pDC->GetSafeHdc());
	
	// ��ȡ��ͼ�ͻ�����С
	// ����һ�����Խ��仭ˢ����������̵�˳��������ɫ����
	Gdiplus::LinearGradientBrush linGrBrush(Gdiplus::Point(100,0),Gdiplus::Point(100,m_rect.Height()/2),Gdiplus::Color(255,255,0,0),Gdiplus::Color(255,255,0,255));
	Gdiplus::Color colors[] = {
		Gdiplus::Color(255, 255, 0, 0),   // red
		Gdiplus::Color(255, 255, 255, 0), //yellow
		Gdiplus::Color(255, 0, 255, 0),   // green
		Gdiplus::Color(255, 0, 255, 255),   // ��
		Gdiplus::Color(255, 0, 0, 255),   // blue
		Gdiplus::Color(255, 255, 0, 255)  // ��
	};
// 	Gdiplus::REAL positions[] = {0.0f, 0.33f, 0.66f, 1.0f};  
	Gdiplus::REAL positions[] = {0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f};  
	BOOL ret=FALSE;
	switch(m_fillType)
	{
	case Solid:  // ʵ�����
		brush.CreateSolidBrush(m_bgColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	case Hatch:  // Hatch ���
// 		if(m_bgTransparent)
// 			pDC->SetBkMode(TRANSPARENT);
// 		else
// 			pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(m_bgColor); // ���������д��ʱȥ������ɫ�ġ�����
		brush.CreateHatchBrush(m_hatchStyle, m_hatchColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	case Gradient:
		// ����һ����ͼ����
		linGrBrush.SetInterpolationColors(colors, positions,6);
		// ���ָ���������
		graphics.FillRectangle(&linGrBrush,m_rect.Width()/2,0,80,m_rect.Height()/2);
// 		AfxMessageBox("��δʵ��");
// 		GDI+�Ķ�ɫ���Խ��仭ˢ��Ҳ����ʵ������ǶȵĽ��仭ˢ������֪������ǶȻ��ƶ�ɫ�����Ƿ���ԣ�
// 		��ͷ�ļ��м�������Ĵ��룺
// #include <GdiPlus.h>
// using namespace Gdiplus;
// #pragma comment(lib,"gdiplus.lib")
// 		��ʼ����
// 		GdiplusStartupInput gdiplusStartupInput; 
// 		ULONG_PTR gdiplusToken; 
// 		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); 
//		ʹ��
// 		Gdiplus::Rect rc(0,0,100,100);
//		//  ���ĸ����������ǽ���ɫ�ĽǶ� (Gdiplus::REAL)(90 - iRotation));  //  ����ɫ�ĽǶ�
// 		Gdiplus::LinearGradientBrush brush(rc,RGB(255,0,0,255), RGB(255,255,0,0), LinearGradientModeVertical);
// 		Gdiplus::REAL pos[] = {0.0f,0.3f,0.7f,1.0f};
// 		Gdiplus::Color cor[] = {Gdiplus::Color(255,0,0,255),Gdiplus::Color(255,0,255,0), Gdiplus::Color(255,255,255,0), Gdiplus::Color(255,255,0,0)};
// 		brush.SetInterpolation(&cor[0],&pos[0],4);
// 		CDC *pDC = GetDC();
// 		Gdiplus::Graphics draw = Gdiplus::Graphics::FromHDC(pDC->GetSafeHdc();
// 		draw.FillRectangle(&brush,rc);
// 		ReleaseDC(pDC);
// 		���٣�
// 		ULONG_PTR gdiplusToken = NULL; 
// 		GdiplusShutdown(gdiplusToken);
		break;
	case Picture:
// 		AfxMessageBox("��δʵ�֣���Ϊ��֧��DIBλͼ�������⹦��̫���ˣ�");
		break;
// 		if(m_patternBitmap)
// 		{
// 			ret=brush.CreatePatternBrush(m_patternBitmap);
// 			oldBrush=pDC->SelectObject(&brush);
// 		}
// 		break;
	case Figure:
		pDC->SetBkColor(m_bgColor); // ���������д��ʱȥ������ɫ�ġ�����
		break;
	}
	
	if(m_bgTransparent)
		pDC->SetBkMode(TRANSPARENT);
	else
		pDC->SetBkMode(OPAQUE);
	
	pDC->MoveTo(m_rect.TopLeft());

	int length=0;
	if(m_fillType==Picture)
	{
		if(m_picture)
		{
			if(m_picture->IsValid())
				m_picture->Draw2(pDC->GetSafeHdc(), m_rect);
		}
	}
	else if(m_fillType==Figure)
	{
		pen.CreatePen(PS_SOLID,0, m_hatchColor);
		oldPen=pDC->SelectObject(&pen);
		if(m_fillFigure)
		{
			CPoint pt=m_fillFigure->getFirstPoint();
			pt.Offset(m_rect.TopLeft());
			m_fillFigure->draw(pDC, pt);
		}
	}
	else if(m_fillType==Gradient)
	{

	}
	else if(!m_bgTransparent || m_fillType==Hatch)
	{
		pen.CreatePen(PS_NULL,1, RGB(0,0,0));
		oldPen=pDC->SelectObject(&pen);
		switch(m_shape)
		{
		case Rect:
			pDC->Rectangle(m_rect);
			break;
		case Circle:
			length=min(m_rect.Width(), m_rect.Height());
			pDC->Ellipse(m_rect.left, m_rect.top, m_rect.left+length, m_rect.top+length);
			break;
		case Eclipse:
			pDC->Ellipse(m_rect);
			break;
		case RoundRectangle:
			pDC->RoundRect(m_rect, m_roundPoint);
			break;
		}
	}

	if(oldBrush)
		pDC->SelectObject(oldBrush);
	if(oldPen)
		pDC->SelectObject(oldPen);
}

void CFilledArea::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{
	m_rect.OffsetRect(moveShift);
}
