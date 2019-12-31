// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__C69410E0_F0F8_4A47_9BDE_6E3C5E524CE7__INCLUDED_)
#define AFX_LINE_H__C69410E0_F0F8_4A47_9BDE_6E3C5E524CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "LineObj.h"
#include "PropertyList.h"
#include "LinePropertySet.h"

class CLine : public CLineObj  
{
public:
	CLine();
	CLine(CRect rect);
	CLine(POINT src, POINT dst);
	virtual ~CLine();

	// ����
	
	string getType();                     // ��ȡ���ƶ��������

	POINT getSrc();     // ��ȡ���
	POINT getDst();     // ��ȡ�յ�

	// ��ȡ��������㡢�յ�ĺ�������
	int getX1();
	void setX1(int x1);
	int getY1();
	void setY1(int y1);
	int getX2();
	void setX2(int x2);
	int getY2();
	void setY2(int y2);

	CTracker getTracker();   // ��ȡѡ�п�
	// ���ݾ��ε����ϽǺ����½ǵ㣬ȷ��ֱ�ߵ������˵�λ��
	void setPoints(CPoint oldPoint,CPoint newPoint);

	// ����
	virtual void Serialize(CArchive &ar);

	void draw(CDC *pDC);                // ��Ļ�ϻ���
	// �ڴ������ƶ����ʱ����ƣ����draw���ƺܸ��ӣ��ڴ������ƶ����ʱ������������򻯻��ƣ�����߶�̬���Ƶ�Ч�ʣ�
	void drawOnCreating(CDC *pDC);
	BOOL isHitMe(CPoint hitPoint);      // �����������Ƿ�����˸û��ƶ���
	void move(CSize moveShift);            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
	void moveHandle(int nHandle, CPoint point);  // �ƶ����ƶ���Tracker�ĵ�nHandle�ž����point����

	// �жϸ�ֱ���Ƿ���ָ���ľ����ཻ
	BOOL intersection(CRect rc);

protected:
	DECLARE_SERIAL(CLine);

	// �ж������߶��Ƿ��ཻ
	BOOL intersectionTwoLines(CPoint line1P1,CPoint line1P2,CPoint line2P1,CPoint line2P2);
	int f(CPoint a,CPoint b,CPoint c);   // �ж������߶��Ƿ��ཻ���õ��ķ���

	CLinePropertySet *m_properties;
// 	CPropertyList *m_properties;

	POINT m_src,m_dst;

};

#endif // !defined(AFX_LINE_H__C69410E0_F0F8_4A47_9BDE_6E3C5E524CE7__INCLUDED_)
