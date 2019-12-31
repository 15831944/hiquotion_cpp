// BarCodePrint.cpp: implementation of the CBarCodePrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BarCodePrint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBarCodePrint::CBarCodePrint()
{

}

CBarCodePrint::~CBarCodePrint()
{

}

int CBarCodePrint::printBarCode(LPSTR text, CDC* pDC, float m_CodeWidth, float m_CodeHigh, float ratox, float ratoy, int x, int y)
{
	//  Դ��ѧϰ����www.lvcode.com
	//    ��ӭ����Դ���Love����
	CPen pen,*pOldPen;
	int High,i;
	LPSTR str=text;
	//�趨�������Ͻų�ʼ��
// 	CPoint point(50,50);
	CPoint point(x, y);
	
	//����Ϊ��ɫ
	pen.CreatePen (PS_SOLID,int(m_CodeWidth*ratox),RGB(0,0,0));
	//������ѡ���ӡ�豸����
	pOldPen=pDC->SelectObject (&pen);
	High=int(m_CodeHigh*ratoy);
	
	while(*str)
	{
		for(i=0;i<(*str-'0');i++)
		{
			pDC->MoveTo (point);
			pDC->LineTo (point.x,point.y+High);
			point.x+=int(m_CodeWidth*ratox);
		}
		str++;
		point.x+=int(m_CodeWidth*ratox)*(*str-'0');
		str++;
	}
	pDC->SelectObject (pOldPen);
	pen.DeleteObject ();
	return 0;
}

BOOL CBarCodePrint::printText(CString text, CDC *pDC, LPRECT rect, int textAlign, LOGFONT *m_font)
{
	CFont *oldFont=NULL;
	if(m_font)
	{
		CFont font;
		font.CreateFontIndirect(m_font);
		oldFont=pDC->SelectObject(&font);
	}

	CPen pen,*pOldPen;
	//����Ϊ��ɫ
	pen.CreatePen (PS_SOLID,1,RGB(0,0,0));

	pOldPen=pDC->SelectObject (&pen);
	pDC->DrawText(text, rect, textAlign+DT_WORDBREAK);  // ������������ʾ���뷽ʽ��0-����1-���У�2-����
	pDC->SelectObject (pOldPen);
	if(oldFont)
		pDC->SelectObject(oldFont);
	pen.DeleteObject ();

	return TRUE;
}
