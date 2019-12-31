// IUIHandler.h: interface for the IUIHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IUIHANDLER_H__4DE9534E_53D4_4646_809B_169308CA8D62__INCLUDED_)
#define AFX_IUIHANDLER_H__4DE9534E_53D4_4646_809B_169308CA8D62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\TreeProj\TreeNode.h>
#include "IInteractiveEventHandler.h"
// #include <C++\FoundationLib\DrawingLib\ILocation.h>
// #include "EventHandlingContainer.h"
// #include <C++\FoundationLib\DrawingLib\Container.h>
#include <C++\FoundationLib\DrawingLib\IShape.h>

enum EventHandleOrder
{
	EventDisabled,
	SelfOnlyHandled,
	ChildOnlyHandled,
	SelfThenChild,
	ChildThenSelf
};

class IUIHandler : public CTreeNode<IUIHandler *>, public IInteractiveEventHandler/*, public ILocation*/
{
public:
	IUIHandler();
	IUIHandler(IShape *shape);
	virtual ~IUIHandler();

// 	void draw(CDC *pDC);

	// ����ӽ��
	void addUIHandler(IUIHandler *handler);
// 	void addFigure(IShape *figure, BOOL fullfill=FALSE);

	// ȡ�ӽ��
	CTreeNode<IUIHandler *> *getUIHandlerTreeNode(int index);
	CTreeNode<IUIHandler *> *getUIHandlerTreeNode(IUIHandler *handler);

	// ȡ���ڵ��е� IUIHandler ����
	IUIHandler *getUIHandler(int index);
	
	// �ж��Ƿ����ָ�� IUIHandler ����isCheckChilren ��ʾ�Ƿ����ӽ���е� IUIHandler ����
	BOOL isContainUIHandler(IUIHandler *handler, BOOL isCheckChilren=TRUE);

	// �Ƴ� IUIHandler ����ͬʱɾ���ӽ�㣩
	void removeUIHandler(IUIHandler *handler);
// 	void removeFigure(IShape *figure);

	virtual void draw(CDC *pDC, CPoint point=CPoint(0, 0), CRgn *parentRgn=NULL);

	// ����任
	// ��
	CPoint pointToClient(IUIHandler *child, CPoint ptInParent);
	CPoint pointToParent(CPoint ptInClient);
	// ����
	CRect rectToClient(IUIHandler *child, CRect rtInParent);
	CRect rectToParent(CRect rtInClient);
	
	CWnd * getWndForRefresh() const { return m_wndForRefresh; }
	void setWndForRefresh(CWnd * val) { m_wndForRefresh = val; }

	void updateUI();

	IUIHandler * getHandlerSelected() const { return m_handlerSelected; }
	CPoint getLastDraggedPoint() const { return m_lastDraggedPoint; }

	IShape * getShape() const { return m_shape; }
	void setShape(IShape * val) { m_shape = val; if(!val) m_rect=val->getRect(); }

	CRect getRect() const { return m_rect; }

	// �ⲿ����¼�
	void leftButtonDown(UINT nFlags, CPoint point);
	void leftButtonUp(UINT nFlags, CPoint point);
	void leftButtonDoubleClick(UINT nFlags, CPoint point);
	
	void rightButtonDown(UINT nFlags, CPoint point);
	void rightButtonUp(UINT nFlags, CPoint point);
	void rightButtonDblClick(UINT nFlags, CPoint point);
	
	void mouseMove(UINT nFlags, CPoint point);
	void mouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void keyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void keyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	EventHandleOrder getMovingEffected() const { return m_eventEffected; }
	void setMovingEffected(EventHandleOrder val) { m_eventEffected = val; }

protected:
	IUIHandler *isPointInChild(CPoint point);

	// ������ֱ�ӵ��¼�
	
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	// 	virtual void OnLButtonClick();
	virtual void OnLButtonDblClick(UINT nFlags, CPoint point);
	virtual void OnLButton3Click();
	
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonDblClick(UINT nFlags, CPoint point);
	
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnMouseDrag(UINT nFlags, CPoint currPoint, CPoint origPoint);
	virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	// ���ͼ��̵��¼����Ч��
	
	// 	virtual void OnMouseHove(UINT nFlags, CPoint point);   // OnMouseMove + ��ͣ���ٺ��룬�������¼�
	// 	void OnMouseMoveIn(CDrawnObj *drawnObj); // OnMouseMove
	// 	void OnMouseMoveOut(CDrawnObj *drawnObj);// OnMouseMove��������λ�ò��ڻ�ͼ������ڲ�����ʱ������

protected:
	BOOL m_isMouseIn;
	CPoint m_pointAtMouseDown;
	BOOL m_altPressed;
	EventHandleOrder m_eventEffected;
	CPoint m_lastDraggedPoint;

	CRect m_rect;
	IShape *m_shape;

	CWnd *m_wndForRefresh;

	IUIHandler *m_handlerSelected;
};

#endif // !defined(AFX_IUIHANDLER_H__4DE9534E_53D4_4646_809B_169308CA8D62__INCLUDED_)
