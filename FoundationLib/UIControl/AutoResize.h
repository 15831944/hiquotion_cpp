#pragma once

/****************************************
*
* �Զ��ı丸�������Ӵ��ڵĴ�С��λ��
*
* ʹ�÷�����
*
* 1���� .h �ļ�������
*         #include "AutoResize.h"
*
* 2���� .h �ļ�������
*         Declare_AutoResize
*
* 3���� .cpp �ļ��������Ӵ����ĸ��ߵ����ͣ�ԭʼ���� Original ��ê������ Anchor��
*    ����ʹ�����������궨��
*         Init_AutoResize_Normal(�Ӵ���id, ��������ָ�룩
*         Init_AutoResize(�Ӵ���id, ��������ָ��, �������, �ϱ�����, �ұ�����, �±����ͣ�
*         Init_AutoResize_Fill(�Ӵ���id, ��������ָ�룩
*   ��һ����WindowsĬ�����ͣ�������ϵ�λ���ǹ̶��ģ���ê�����ͣ���
*         �Һ�����ԭʼ���ͣ�����͸߱��ֲ��䣩
*   �ڶ�����Ҫ�ֶ������ĸ��ߵ�����
*   �����ֱ�ʾ�Ӵ����ڸ�������ƽ��ռ�������ڵ������ռ�
*
* 4���ڸ����ڵ�OnSize�¼���������º궨��
*         Do_Resize(cx, cy);
*
*****************************************/

#include <FoundationLib/DataStructLib/PointerList.h>

#define Declare_AutoResize \
	CAutoResizeManager m_auto;

// Maybe no use of Init_AutoResize_Normal definition...
#define Init_AutoResize_Normal(id, parent) \
{ \
	CAutoResize* ar=new CAutoResize(); \
	ar->setWnd(GetDlgItem(id));        \
	ar->init(GetDlgItem(id), parent);  \
	ar->setLeftResizeType(Anchor); \
	ar->setTopResizeType(Anchor);  \
	ar->setRightResizeType(Original);  \
	ar->setBottomResizeType(Original); \
	m_auto.push_back(ar); \
}

#define Init_AutoResize(id, parent, leftResizeType, topResizeType, rightResizeType, bottomResizeType) \
{ \
	CAutoResize* ar=new CAutoResize(); \
	ar->setWnd(GetDlgItem(id));        \
	ar->init(GetDlgItem(id), parent);  \
	ar->setLeftResizeType(leftResizeType); \
	ar->setTopResizeType(topResizeType);   \
	ar->setRightResizeType(rightResizeType);   \
	ar->setBottomResizeType(bottomResizeType); \
	m_auto.push_back(ar); \
}

#define Init_AutoResize_Fill(id, parent) \
{ \
	CAutoResize* ar=new CAutoResize();  \
	ar->setWnd(GetDlgItem(id));      \
	ar->initFill(GetDlgItem(id), parent);   \
	ar->setLeftResizeType(Anchor);   \
	ar->setTopResizeType(Anchor);    \
	ar->setRightResizeType(Anchor);  \
	ar->setBottomResizeType(Anchor); \
	ar->setLeftDistance(0);   \
	ar->setTopDistance(0);    \
	ar->setRightDistance(0);  \
	ar->setBottomDistance(0); \
	m_auto.push_back(ar);     \
}

#define Do_Resize(cx, cy) \
	m_auto.autoResize(cx, cy);

enum ResizeType
{
	Original,    // ����ԭ��
	Anchor,      // �߾�̶�
};

class CAutoResize
{
public:
	CAutoResize();
	CAutoResize(ResizeType leftResizeType, ResizeType topResizeType, ResizeType rightResizeType, ResizeType bottomResizeType);

	void init(CWnd* wnd, CWnd* parent, BOOL considerTitleHeight=TRUE);
	void init(RECT* rc, RECT* rcParent);
	void init(int leftDisatnce, int topDistance, int rightDistance, int bottomDistance, int width, int height);
	void initFill(CWnd* wnd, CWnd* parent, BOOL considerTitleHeight = TRUE);

	void autoResize(int cx, int cy);

	void setLeftDistance(int leftDistance) { m_leftDistance = leftDistance; }
	void setTopDistance(int topDistance) { m_topDistance = topDistance; }
	void setRightDistance(int rightDistance) { m_rightDistance = rightDistance; }
	void setBottomDistance(int bottomDistance) { m_bottomDistance = bottomDistance; }

	void setLeftResizeType(ResizeType leftResizeType) { m_leftResizeType = leftResizeType; }
	void setTopResizeType(ResizeType topResizeType) { m_topResizeType = topResizeType; }
	void setRightResizeType(ResizeType rightResizeType) { m_rightResizeType = rightResizeType; }
	void setBottomResizeType(ResizeType bottomResizeType) { m_bottomResizeType = bottomResizeType; }

	void setWnd(CWnd* wnd) { m_wnd = wnd; }

protected:
	BOOL checkWnd(CWnd* wnd);

private:
	CWnd* m_wnd;

	int m_leftDistance;  // �����ڸ����ڵ���߾�
	int m_topDistance;   // �����ڸ����ڵ��ϱ߾�
	int m_rightDistance; // �����ڸ����ڵ��ұ߾�
	int m_bottomDistance;// �����ڸ����ڵ��±߾�

	int m_width;    // ���ڿ��
	int m_height;   // ���ڸ߶�

	ResizeType m_leftResizeType;
	ResizeType m_topResizeType;
	ResizeType m_rightResizeType;
	ResizeType m_bottomResizeType;
};

class CAutoResizeManager : public CPointerList<CAutoResize*>
{
public:
	CAutoResizeManager()
	{
		setSelfDestroy(TRUE);
	}

	void autoResize(int cx, int cy)
	{
		for (int i = 0; i < (int)size(); i++)
		{
			CAutoResize* ar = at(i);
			if (!ar)
				continue;

			ar->autoResize(cx, cy);
		}
	}

};