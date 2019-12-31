// Elipse.h: interface for the CElipse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELIPSE_H__C8BEC427_116B_41D5_AC70_799A532218C3__INCLUDED_)
#define AFX_ELIPSE_H__C8BEC427_116B_41D5_AC70_799A532218C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

// #include "DrawnObj.h"
#include "Rectangle.h"

class CElipse : public CRectangle // CDrawnObj  
{
public:
	CElipse();
	CElipse(CRect rect);
	virtual ~CElipse();

	// ����
	
	string getType();                     // ��ȡ���ƶ��������
	// 	POINT getSrc();     // ��ȡ�������
	// 	POINT getDst();     // ��ȡ�յ�����
// 	CTracker getTracker();   // ��ȡѡ�п�
	
	// ����
	virtual void Serialize(CArchive &ar);
	
	void draw(CDC *pDC);                // ��Ļ�ϻ���
	BOOL isHitMe(CPoint hitPoint);      // �����������Ƿ�����˸û��ƶ���
	void move(CSize moveShift);            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�

protected:
	DECLARE_SERIAL(CElipse);


private:
// 	CRect m_rect;
};

#endif // !defined(AFX_ELIPSE_H__C8BEC427_116B_41D5_AC70_799A532218C3__INCLUDED_)
