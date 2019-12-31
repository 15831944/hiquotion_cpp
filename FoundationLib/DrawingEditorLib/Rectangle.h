// Rect.h: interface for the CRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECT_H__79D00011_2420_4A2C_9C5B_4659FE4C569E__INCLUDED_)
#define AFX_RECT_H__79D00011_2420_4A2C_9C5B_4659FE4C569E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "ShapeObj.h"
#include "PropertyList.h"
#include "RectanglePropertySet.h"

class CRectangle : public CShapeObj  
{
public:
	CRectangle();
	CRectangle(CRect rect);
	virtual ~CRectangle();

	// ����
	
	virtual string getType();                     // ��ȡ���ƶ��������
	// 	POINT getSrc();     // ��ȡ�������
	// 	POINT getDst();     // ��ȡ�յ�����
	CTracker getTracker();   // ��ȡѡ�п�
	void setRect(CRect rect);  // ���þ��εĴ�С 
	
	// ����
	virtual void Serialize(CArchive &ar);

	virtual void draw(CDC *pDC);                // ��Ļ�ϻ���
	// �ڴ������ƶ����ʱ����ƣ����draw���ƺܸ��ӣ��ڴ������ƶ����ʱ������������򻯻��ƣ�����߶�̬���Ƶ�Ч�ʣ�
	virtual void drawOnCreating(CDC *pDC);
	
	virtual BOOL isHitMe(CPoint hitPoint);      // �����������Ƿ�����˸û��ƶ���
	virtual void move(CSize moveShift);            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�

protected:
	CRectanglePropertySet *m_properties;

	DECLARE_SERIAL(CRectangle);
// 	CRect m_rect;

	void refreshRect();    // ������ͼ�εľ�������ת�˵�ʱ��ͨ���÷���ת�����

private:
};

#endif // !defined(AFX_RECT_H__79D00011_2420_4A2C_9C5B_4659FE4C569E__INCLUDED_)
