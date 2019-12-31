// ILocation.h: interface for the ILocation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILOCATION_H__BAB5A131_6853_4035_A2AE_59987433676F__INCLUDED_)
#define AFX_ILOCATION_H__BAB5A131_6853_4035_A2AE_59987433676F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ILocation  
{
public:
	ILocation();
	ILocation(int left, int top, int right, int bottom);
	ILocation(CRect rect);
	
	virtual ~ILocation();

	void getRect(CRect &rect);
	CRect getRect();
	virtual CPoint getFirstPoint();
	CRect *getRectAddr();
	void setRect(CRect rect);
	void setRect(int left, int top, int right, int bottom);
	
protected:
	// �¼�����
	virtual void OnSize(int cx, int cy) {};
	
	void refreshRect();    // ������ͼ�εľ�������ת�˵�ʱ��ͨ���÷���ת�����
	
protected:
	CRect m_rect;

};

#endif // !defined(AFX_ILOCATION_H__BAB5A131_6853_4035_A2AE_59987433676F__INCLUDED_)
