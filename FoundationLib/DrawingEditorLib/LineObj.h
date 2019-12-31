// LineObj.h: interface for the CLineObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINEOBJ_H__328EEA23_80C7_4213_8259_5D23C41EF19A__INCLUDED_)
#define AFX_LINEOBJ_H__328EEA23_80C7_4213_8259_5D23C41EF19A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "DrawnObj.h"
#include "Property.h"

// ��ʱ����
class CLineObj : public CDrawnObj  
{
public:
	CLineObj();
	virtual ~CLineObj();

	CLineObj(CRect rect);

	DECLARE_SERIAL(CLineObj);

	virtual void Serialize(CArchive &ar);

public:
	// ����
	virtual int getLineStyle();   // ��ȡ������ʽ
	virtual void setLineStyle(int lineStyle);   // ����������ʽ
	virtual int getLineColor();   // ��ȡ������ɫ
	virtual void setLineColor(int lineColor);   // ����������ɫ
	virtual int getLineWidth();   // ��ȡ�������
	virtual void setLineWidth(int lineWidth);   // �����������

protected:
	int m_lineColor;
	int m_lineStyle;
	int m_lineWidth;

};

#endif // !defined(AFX_LINEOBJ_H__328EEA23_80C7_4213_8259_5D23C41EF19A__INCLUDED_)
