// Poker.h: interface for the CPoker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POKER_H__2BE0A91D_CD35_4F49_A898_00CAE78AD3DA__INCLUDED_)
#define AFX_POKER_H__2BE0A91D_CD35_4F49_A898_00CAE78AD3DA__INCLUDED_

#include <C++\FoudationLib\UIHandlerLib\IUIHandler.h>
#include <C++\FoudationLib\DrawingLib\Picture.h>
#include <string>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ͼ��λ�ö���

// 1��Ĭ��ֽ�ƿ��
#define DEFAULT_POKER_WIDTH   450
#define DEFAULT_POKER_HEIGHT  685

// 2��Ĭ�ϴ�ɫ���
#define DEFAULT_POKER_LARGE_TYPE_WIDTH 90
#define DEFAULT_POKER_LARGE_TYPE_HEIGHT 110

// 3��Ĭ��С��ɫ���
#define DEFAULT_POKER_SMALL_TYPE_WIDTH DEFAULT_POKER_LARGE_TYPE_WIDTH/2
#define DEFAULT_POKER_SMALL_TYPE_HEIGHT DEFAULT_POKER_LARGE_TYPE_HEIGHT/2

// Ĭ��С��ɫ����
// ���Ͻ�20,130
#define Default_Poker_Small_Type_LeftTop_X 20
#define Default_Poker_Small_Type_LeftTop_Y 130

// ���½�380,505
#define Default_Poker_Small_Type_RightBottom_X 380
#define Default_Poker_Small_Type_RightBottom_Y 505

// 4��Ĭ������ֵ���
#define DEFAULT_POKER_VALUE_WIDTH 50
#define DEFAULT_POKER_VALUE_HEIGHT 80

// Ĭ������ֵ���Ͻ�����
#define Default_Value_LeftTop_X 15
#define Default_Value_LeftTop_Y 35

// Ĭ������ֵ���½�����
#define Default_Value_RightBottom_X 380
#define Default_Value_RightBottom_Y 575

// Ĭ�� JKQ ͼ�����Ͻ�����
#define JKQ_X 73
#define JKQ_Y 63

// Ĭ�� JKQ ͼ�����
#define JKQ_Width 300
#define JKQ_Height 565

int GetZoomedValue(int a, int len, int defaultLen);
// {
// 	if(len==defaultLen)
// 		return a;
// 	else
// 		return a*len/defaultLen;
// }

#define GetZoomedX2(x, width) GetZoomedValue(x, width, DEFAULT_POKER_WIDTH)
#define GetZoomedY2(y, height) GetZoomedValue(y, height, DEFAULT_POKER_HEIGHT)

#define GetZoomedX(x) GetZoomedX2(x, m_rect.Width())
#define GetZoomedY(y) GetZoomedY2(y, m_rect.Height())

// ֽ�Ƶ�ʵ�ʿ��
static int pokerWidth=DEFAULT_POKER_WIDTH;
static int pokerHeight=DEFAULT_POKER_HEIGHT;

int getPokerWidth();
void setPokerWidth(int width);
int getPokerHeight();
void setPokerHeight(int height);

// 7�����ݽṹ����

// λ�����ݶ���

// ��ɫλ��ͼ���ݣ��� .cpp��

// ��ɫλ�������ڻ�ɫλ��ͼ�е�����
// ��ά�����У���һά��ʾ����ֵ���ڶ�ά��ʾ��ɫλ��ͼ�е��������飨����Ԫ�ظ���������ֵһ�£�
// ���� .cpp��

// �߼����ݶ���

// 1����ɫ

enum PokerType
{
	Black,  // ����
	Red,    // ����
	Flower, // �ݻ�
	Diamond, // ��Ƭ
//	Joker,  // ��
};

// 2������ֵ

enum PokerValue
{
	PVAce,//=1,
	PV2,
	PV3,
	PV4,
	PV5,
	PV6,
	PV7,
	PV8,
	PV9,
	PV10,
	PVJack,
	PVQueen,
	PVKing,

// 	// ��
// 	PVMinorJoker=100,
// 	PVMajorJoker=101,
};

// 3��һ���˿���

struct Poker
{
	PokerType type;
	PokerValue value;
};

// 4��һ���˿�

// struct PokerSet
// {
// 	Poker poker[54];
// };

static CPicture m_background;     // �������ͼ
static CPicture m_offBackground;  // �Ʊ����ͼ
static CPicture m_type[4];        // ��ɫͼ
static CPicture m_typeRotated[4]; // ��ת�Ļ�ɫͼ
static CPicture m_value[2][13];         // ����ֵ
static CPicture m_valueRotated[2][13];  // ��ת������ֵ
static CPicture m_people[4][3];         // ����ֵ���J��Q��K����ά���飬��һά��ʾ���ֻ�ɫ���ڶ�ά��ʾJ��Q��K
	
// ���������汳��ͼ�ͱ��汳��ͼ
void setBackgroundResource(DWORD res, DWORD imgExtType);
void setBackgroundPicture(std::string path, DWORD imageType=0);
void setOffBackgroundRecource(DWORD res, DWORD imgExtType);
void setOffBackgroundPicture(std::string path, DWORD imageType=0);

// ���û�ɫ������ֵ�Լ�JKQ����Դ�Ż�ͼƬ·��
void setTypeResource(PokerType type, DWORD res, DWORD imgExtType);
void setTypePath(PokerType type, std::string path, DWORD imageType=0);

void setValueResource(PokerType type, PokerValue v, DWORD res, DWORD imgExtType);
void setValuePath(PokerType type, PokerValue v, std::string path, DWORD imageType=0);

void setJResource(PokerType type, DWORD res, DWORD imgExtType);
void setJPath(PokerType type, std::string path, DWORD imageType=0);

void setKResource(PokerType type, DWORD res, DWORD imgExtType);
void setKPath(PokerType type, std::string path, DWORD imageType=0);

void setQResource(PokerType type, DWORD res, DWORD imgExtType);
void setQPath(PokerType type, std::string path, DWORD imageType=0);

// 5��������ɽ�����һ����
class CPoker : public IUIHandler  
{
public:
	CPoker();
	CPoker(PokerType pokerType, PokerValue pokerValue);
	virtual ~CPoker();

	static int getWidth() { return getPokerWidth(); }
	static void setWidth(int width) { setPokerWidth(width); }
	static int getHeight() { return getPokerHeight(); }
	static void setHeight(int height) { setPokerHeight(height); }

	Poker getPoker() const { return m_poker; }
	void setPoker(Poker val) { m_poker = val; }
	void setPoker(PokerType pokerType, PokerValue pokerValue)
	{
		m_poker.type=pokerType;
		m_poker.value=pokerValue;
	}

	PokerType getPokerType() const { return m_poker.type; }
	void setPokerType(PokerType val) { m_poker.type=val; }

	PokerValue getPokerValue() const {return m_poker.value; }
	void setPokerValue(PokerValue val) { m_poker.value=val; }

	BOOL getOff() const { return m_isOff; }
	void setOff(BOOL val);

	int getAbsoluteX() const { return m_absoluteX; }
	int getAbsoluteY() const { return m_absoluteY; }

protected:
	void init();
	virtual void drawMe(CDC *pDC, CPoint point);

	// �̳�
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnMouseDrag(UINT nFlags, CPoint currPoint, CPoint origPoint);
	virtual void OnSize(int cx, int cy);

protected:
	Poker m_poker;
	BOOL m_isOff;          // ���Ƿ��ǿ��ŵģ�������ʾ��Щͼ�Σ�

	// �������������ͼ�����Ͻǵ�x y����
	int m_absoluteX;
	int m_absoluteY;
};

#endif // !defined(AFX_POKER_H__2BE0A91D_CD35_4F49_A898_00CAE78AD3DA__INCLUDED_)
