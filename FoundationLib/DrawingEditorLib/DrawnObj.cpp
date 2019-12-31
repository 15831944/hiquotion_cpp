// DrawnObj.cpp : implementation file
//

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "DrawnObj.h"
#include "SystemPropertyLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CDrawnObj, CObject, 0)

/////////////////////////////////////////////////////////////////////////////
// CDrawnObj

CDrawnObj::CDrawnObj()
{
	m_rect=CRect(0,0,30,20);
	m_selected=FALSE;
	m_properties=NULL;
}

CDrawnObj::CDrawnObj(CRect rect)
{
	m_rect=rect;
	m_selected=FALSE;
}

CDrawnObj::~CDrawnObj()
{
}


BEGIN_MESSAGE_MAP(CDrawnObj, CWnd)
	//{{AFX_MSG_MAP(CDrawnObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDrawnObj message handlers

// ����

string CDrawnObj::getType()                    // ��ȡ���ƶ��������
{
	return "CDrawnObj";
}

// ��ȡ���ƶ��������
string CDrawnObj::getName()
{
	return m_name;
}

// ���û��ƶ��������
void CDrawnObj::setName(string name)
{
	m_name=name;
}

CRect CDrawnObj::getRect()
{
	return m_rect;
}

void CDrawnObj::setRect(CRect rc)
{
	m_rect=rc;
}

// ��ȡ�û��ƶ����Ƿ�ѡ��
BOOL CDrawnObj::getSelected()
{
	return m_selected;
}

// ���øû��ƶ����Ƿ�ѡ��
void CDrawnObj::setSelected(BOOL isSelected)
{
	m_selected=isSelected;
}

BOOL CDrawnObj::operator ==(CDrawnObj *drawnObj)
{
	if(getName()==drawnObj->getName())
		return TRUE;
	else
		return FALSE;
}

void CDrawnObj::draw(CDC *pDC)                // ��Ļ�ϻ���
{

}

// �ڴ������ƶ����ʱ����ƣ����draw���ƺܸ��ӣ��ڴ������ƶ����ʱ������������򻯻��ƣ�����߶�̬���Ƶ�Ч�ʣ�
void CDrawnObj::drawOnCreating(CDC *pDC)
{
	draw(pDC);
}

BOOL CDrawnObj::isHitMe(CPoint hitPoint)      // �����������Ƿ�����˸û��ƶ���
{
	return FALSE;
}

void CDrawnObj::move(CSize moveShift)            // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
{

}

CTracker CDrawnObj::getTracker()     // ��ȡѡ�п�
{
	CTracker tracker;
	return tracker;
}

void CDrawnObj::moveHandle(int nHandle, CPoint point)  // �ƶ����ƶ���Tracker�ĵ�nHandle�ž����point����
{
	m_rect=getTracker().moveTrackerHandle(nHandle,point);
}

// �жϻ��ƶ����Ƿ���ָ���ľ��������ཻ
BOOL CDrawnObj::intersection(CRect rc)
{
 	CRect rect;
	return rect.IntersectRect(&m_rect,&rc); 
// 	return m_rect.IntersectRect(&m_rect,&rc);
}


void CDrawnObj::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_rect.left;
		ar << m_rect.top;
		ar << m_rect.right;
		ar << m_rect.bottom;
		ar << (DWORD)getSelected();
	}
	else
	{
		// get the document back pointer from the archive
//		m_pDocument = (CDrawDoc*)ar.m_pDocument;
// 		ASSERT_VALID(m_pDocument);
// 		ASSERT_KINDOF(CDrawDoc, m_pDocument);
		
		ar >> m_rect.left;
		ar >> m_rect.top;
		ar >> m_rect.right;
		ar >> m_rect.bottom;
		DWORD dtmp=0;
		ar >> dtmp;
		setSelected((BOOL)dtmp);
	}

}
