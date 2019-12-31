// RectangleTracker.cpp: implementation of the CRectangleTracker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "RectangleTracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangleTracker::CRectangleTracker(CRect rect) : CTracker(rect)
{
// 	m_rect=rect;

	// ���Ͼ��
	CPoint point=rect.TopLeft();
	CHandle handle(point.x-Default_Handle_Sizex,point.y-Default_Handle_Sizey);
	m_handles.push_back(handle);

	// ���Ͼ��
	handle.setHandlePosition(rect.CenterPoint().x-Default_Handle_Sizex/2,point.y-Default_Handle_Sizey);
	m_handles.push_back(handle);

	// ���Ͼ��
	handle.setHandlePosition(point.x+rect.Width(),point.y-Default_Handle_Sizey);
	m_handles.push_back(handle);

	// ����
	handle.setHandlePosition(point.x-Default_Handle_Sizex,rect.CenterPoint().y-Default_Handle_Sizey/2);
	m_handles.push_back(handle);

	// �Ҿ��
	handle.setHandlePosition(point.x+rect.Width(),rect.CenterPoint().y-Default_Handle_Sizey/2);
	m_handles.push_back(handle);

	// ���¾��
	handle.setHandlePosition(point.x-Default_Handle_Sizex,point.y+rect.Height());
	m_handles.push_back(handle);

	// ���¾��
	handle.setHandlePosition(rect.CenterPoint().x-Default_Handle_Sizex/2,point.y+rect.Height());
	m_handles.push_back(handle);

	// ���¾��
	point=rect.BottomRight();
	handle.setHandlePosition(point.x,point.y);
	m_handles.push_back(handle);
}

CRectangleTracker::~CRectangleTracker()
{

}
