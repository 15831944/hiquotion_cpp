// Chord.h: interface for the CChord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHORD_H__611C7431_7D30_46BE_BBE6_543AE3CF21E6__INCLUDED_)
#define AFX_CHORD_H__611C7431_7D30_46BE_BBE6_543AE3CF21E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IShape.h"

// ������Բ��ֱ���ཻ������
class CChord : public IShape  
{
public:
	CChord();
	CChord(int left, int top, int right, int bottom, int startx, int starty, int endx, int endy);
	CChord(int left, int top, int right, int bottom, POINT start, POINT end);
	CChord(RECT rect, int startx, int starty, int endx, int endy);
	CChord(RECT rect, POINT start, POINT end);
	virtual ~CChord();

	// ����
	void setPoints(POINT start, POINT end);
	virtual void drawMe(CDC *pDC, CPoint point);

protected:
 	POINT m_start, m_end;
};

#endif // !defined(AFX_CHORD_H__611C7431_7D30_46BE_BBE6_543AE3CF21E6__INCLUDED_)
