#if !defined(AFX_DRAWNOBJ_H__600DF739_337D_454D_8B25_7874E53C9315__INCLUDED_)
#define AFX_DRAWNOBJ_H__600DF739_337D_454D_8B25_7874E53C9315__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawnObj.h : header file
//

#include <string>
#include "Tracker.h"
#include <afxole.h>
#include "PropertyList.h"
using namespace std;

#pragma warning(disable : 4786)

/////////////////////////////////////////////////////////////////////////////
// CDrawnObj window

class CDrawnObj : public CWnd
{
// Construction
public:
	CDrawnObj();
	CDrawnObj(CRect rect);

// Attributes
public:
	// ����
	
	virtual string getType();                             // ��ȡ���ƶ��������
	virtual string getName();      // ��ȡ���ƶ��������
	virtual void setName(string name);     // ���û��ƶ��������
	virtual CTracker getTracker();     // ��ȡѡ�п�

	CRect getRect();
	void setRect(CRect rc);
	
	BOOL getSelected();                // ��ȡ�û��ƶ����Ƿ�ѡ��
	void setSelected(BOOL isSelected); // ���øû��ƶ����Ƿ�ѡ��

// Operations
public:
	// ����
	
	virtual void draw(CDC *pDC);                // ��Ļ�ϻ���
	// �ڴ������ƶ����ʱ����ƣ����draw���ƺܸ��ӣ��ڴ������ƶ����ʱ������������򻯻��ƣ�����߶�̬���Ƶ�Ч�ʣ�
	virtual void drawOnCreating(CDC *pDC);
	virtual BOOL isHitMe(CPoint hitPoint);      // �����������Ƿ�����˸û��ƶ���
	virtual void move(CSize moveShift);              // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
	virtual void moveHandle(int nHandle, CPoint point);  // �ƶ����ƶ���Tracker�ĵ�nHandle�ž����point����
	BOOL intersection(CRect rc);      // �жϻ��ƶ����Ƿ���ָ���ľ��������ཻ
	
	// 	virtual void setOrigPoint(POINT origPoint)=0;
	// 	virtual void setMovingPoint(POINT movingPoint)=0;
	
	virtual void Serialize(CArchive &ar);
	
	BOOL operator ==(CDrawnObj *drawnObj);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawnObj)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawnObj();

	DECLARE_SERIAL(CDrawnObj);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawnObj)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CRect m_rect;
	
	string m_name;
	
	BOOL m_selected;

	CPropertyList *m_properties;  // �û��ƶ����������������б�

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWNOBJ_H__600DF739_337D_454D_8B25_7874E53C9315__INCLUDED_)
