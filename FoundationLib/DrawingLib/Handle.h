// Handle.h: interface for the CHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANDLE_H__1024BD7F_9DA1_4809_9368_4FFA033AC574__INCLUDED_)
#define AFX_HANDLE_H__1024BD7F_9DA1_4809_9368_4FFA033AC574__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
// ѡ����еĿ��Բ����ľ��Σ������

#define Default_Handle_Sizex 8
#define Default_Handle_Sizey 8

class CHandle  
{
public:
	CHandle(POINT handlePosition, BOOL bHandleEnabled=TRUE);
	CHandle(int handlePositionX, int handlePositionY, BOOL bHandleEnabled=TRUE);
	virtual ~CHandle();

	// ����
	BOOL isHandleEnabled();    // �������ǲ��ǿ��Բ�����
	SIZE getHandleSize();      // ��ȡ����ĳߴ�
	POINT getHandlPosition();  // ��ȡ�����λ��
	void setHandlePosition(int x, int y); // ���þ����λ��
	void setHandleSize(SIZE handleSize);  // ���þ����С��Ĭ�ϲ���Ҫ����
	CRect getHandleRect();     // ��ȡ������ڵ�Rect

	// ����
	void drawHandle(CDC *DC);

protected:
	BOOL m_bHandleEnabled;
	POINT m_handlePosition;
	SIZE m_handleSize;

};

#endif // !defined(AFX_HANDLE_H__1024BD7F_9DA1_4809_9368_4FFA033AC574__INCLUDED_)
