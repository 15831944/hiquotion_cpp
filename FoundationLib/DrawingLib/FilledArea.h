// FilledArea.h: interface for the CFilledArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILLEDAREA_H__1BF4F826_B86D_40E2_B920_91A2226D90B0__INCLUDED_)
#define AFX_FILLEDAREA_H__1BF4F826_B86D_40E2_B920_91A2226D90B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDrawing.h"

enum Shape
{
	Rect,
	Circle,
	Eclipse,
	RoundRectangle,
};

enum FillType
{
	Solid,        // ��ɫ���
	Hatch,        // Hatch ͼ�����
	Gradient,     // �������
	Picture,      // BMP ͼƬ���
	Figure,       // IFigure �������䣨����䷽ʽ�����Ƶ�ͼ�ο��ܻᳬ���������
};

enum GradientType
{
	Horizen,      // ˮƽ���
	Vertical,     // ��ֱ���
	Angel,        // ĳ�Ƕ�ֱ�����
	Radial,       // ����
	Clockwise,    // ˳ʱ��
	Unclockwise,  // ��ʱ��
};

#pragma comment(lib,"cxImage\\cximage.lib")
#pragma comment(lib,"cxImage\\jasper.lib")
#pragma comment(lib,"cxImage\\Jpeg.lib")
#pragma comment(lib,"cxImage\\libdcr.lib")
#pragma comment(lib,"cxImage\\png.lib")
#pragma comment(lib,"cxImage\\Tiff.lib")
#pragma comment(lib,"cxImage\\zlib.lib")

#include <C++/3rdParty/cxImage/include/ximage.h>

#pragma comment(lib,"gdiplus.lib")
#define ULONG_PTR ULONG
#include <C++/3rdParty/GDIPlus/Includes/GdiPlus.h>

using namespace Gdiplus;

// �������
// ��ɫ��䡢����ɫ��䡢ͼ�����
// �����ʽ
class CFilledArea : public IDrawing
{
public:
	CFilledArea();
	virtual ~CFilledArea();

	// ��״
	Shape getShape() const { return m_shape; }
	void setShape(Shape val) { m_shape = val; }

	// ���������ɫ
	COLORREF getColor() const { return m_bgColor; }
	void setColor(COLORREF val) { m_bgColor = val; }

	// �������
	FillType getFillType() const { return m_fillType; }
	void setFillType(FillType val) { m_fillType = val; }

	// �����Ƿ�͸��
	BOOL getBgTransparent() const { return m_bgTransparent; }
	void setBgTransparent(BOOL val) { m_bgTransparent = val; }

	// hatch �����ʽ
	int getHatchStyle() const { return m_hatchStyle; }
	void setHatchStyle(int val) { m_hatchStyle = val; }

	// hatch ����ǰ��ɫ
	COLORREF getHatchColor() const { return m_hatchColor; }
	void setHatchColor(COLORREF val) { m_hatchColor = val; }

	// �����������
	GradientType getGradientType() const { return m_gradientType; }
	void setGradientType(GradientType val) { m_gradientType = val; }

	// ����ɫ
	Color getGradientColor1() const { return m_gradientColor1; }
	void setGradientColor1(Color val) { m_gradientColor1 = val; }
	Color getGradientColor2() const { return m_gradientColor2; }
	void setGradientColor2(Color val) { m_gradientColor2 = val; }

	// ͼ������õ� BMP ͼƬ
	CxImage * getPicture() const { return m_picture; }
	void setPiture(CxImage * val) { m_picture = val; }

	// Բ�Ǿ��ε�Բ�Ǵ�С
	POINT getRoundPoint() const { return m_roundPoint; }
	void setRoundPoint(POINT val) { m_roundPoint = val; }

	// Figure ��ʽ���
	IDrawing * getFillFigure() const { return m_fillFigure; }
	void setFillFigure(IDrawing * val) { m_fillFigure = val; }

	virtual void draw(CDC *pDC);        // ��Ļ�ϻ���
	virtual void move(CSize moveShift); // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�

protected:
	Shape m_shape;
	COLORREF m_bgColor;
	FillType m_fillType;
	BOOL m_bgTransparent;
	int m_hatchStyle;     // ���� Hatch ���
	COLORREF m_hatchColor; // ���� Hatch ����ǰ��ɫ
	GradientType m_gradientType;  // ���� Gradient ���
	Color m_gradientColor1;    // ���ڽ������ĵ�һ����ɫ
	Color m_gradientColor2;    // ���ڽ������ĵڶ�����ɫ
	Color *m_colorArray;  // ���ڽ���������ɫ����
	REAL *positionArray;  // ���ڽ�������λ������
	CxImage *m_picture;    // ����ͼƬ���
	POINT m_roundPoint;   // ����Բ�Ǿ��ε�Բ����С
	IDrawing *m_fillFigure;    // Figure ��ʽ���
};

#endif // !defined(AFX_FILLEDAREA_H__1BF4F826_B86D_40E2_B920_91A2226D90B0__INCLUDED_)
