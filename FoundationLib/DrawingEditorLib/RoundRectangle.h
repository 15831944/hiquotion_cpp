// RoundRectangle.h: interface for the CRoundRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_)
#define AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

// #include "DrawnObj.h"
#include "Rectangle.h"

class CRoundRectangle : public CRectangle //CDrawnObj  
{
public:
	CRoundRectangle();
	CRoundRectangle(CRect rect, POINT roundCenter=CPoint(15,15), BOOL isDrawRoundHandle=FALSE);
	virtual ~CRoundRectangle();

	// ����
	
	string getType();                     // ��ȡ���ƶ��������
	// 	POINT getSrc();     // ��ȡ�������
	// 	POINT getDst();     // ��ȡ�յ�����
	CTracker getTracker();   // ��ȡѡ�п�
	void setDrawRoundHandle(BOOL isDrawRoundHandle);   // �����Ƿ���Ƶ���Բ�ǻ��ȵľ��

	int getRoundPointX();          // ��ȡԲ�ǵ��ˮƽ����
	void setRoundPointX(int x);    // ����Բ�ǵ��ˮƽ����

	int getRoundPointY();          // ��ȡԲ�ǵ�Ĵ�ֱ����
	void setRoundPointY(int y);    // ����Բ�ǵ�Ĵ�ֱ����

	// ����
	virtual void Serialize(CArchive &ar);

	void draw(CDC *pDC);                // ��Ļ�ϻ���
// 	// �ڴ������ƶ����ʱ����ƣ����draw���ƺܸ��ӣ��ڴ������ƶ����ʱ������������򻯻��ƣ�����߶�̬���Ƶ�Ч�ʣ�
// 	void drawOnCreating(CDC *pDC);
	BOOL isHitMe(CPoint hitPoint);      // �����������Ƿ�����˸û��ƶ���
	void move(CSize moveShift);            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
	void moveHandle(int nHandle, CPoint point);  // �ƶ����ƶ���Tracker�ĵ�nHandle�ž����point����

protected:
	DECLARE_SERIAL(CRoundRectangle);
		
private:
// 	void refreshRect();    // ������ͼ�εľ�������ת�˵�ʱ��ͨ���÷���ת�����

// 	CRect m_rect;
	POINT m_roundCenter;
	BOOL m_drawRoundHandle;
};

#endif // !defined(AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_)
