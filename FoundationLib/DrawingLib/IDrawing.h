// IFigure.h: interface for the IFigure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IFIGURE_H__8368ADB1_4552_410E_BF23_BA49E54A77F8__INCLUDED_)
#define AFX_IFIGURE_H__8368ADB1_4552_410E_BF23_BA49E54A77F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ���������ŵ� StdAfx.h ͷ�ļ�����ǰ�棬���Խ��� 4786 ������Ϣ
// #pragma warning(disable : 4786)

// ��ȡϵͳ����ķ���
// GetStockObject(SYSTEM_FONT); 

class IDrawing  
{
public:
	IDrawing();
	virtual ~IDrawing();

	virtual void draw(CDC *pDC, CPoint point=CPoint(0, 0));
	virtual void move(CSize moveShift){};  // �ƶ����ƶ��󣬶��ھ������͵Ļ��ƶ��󣬸õ��ʾ���ε����Ͻǣ��������ͣ�ֱ�߻����ߣ����õ��ʾ��һ���˵�
	virtual void moveTo(CPoint point){};      // �ƶ���

protected:
};

#endif // !defined(AFX_IFIGURE_H__8368ADB1_4552_410E_BF23_BA49E54A77F8__INCLUDED_)
