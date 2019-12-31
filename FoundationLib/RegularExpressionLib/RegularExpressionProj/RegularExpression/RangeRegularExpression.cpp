// RangeRegularExpression.cpp: implementation of the CRangeRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RangeRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\RE2SGConverter\RE2SGConverter.h"
// #include "..\CharChecker\RangeCharChecker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRangeRegularExpression::CRangeRegularExpression()
: m_charFrom(NULL), m_charTo(NULL)
{

}

CRangeRegularExpression::CRangeRegularExpression(char from, char to)
: m_charFrom(from), m_charTo(to)
{
	
}

CRangeRegularExpression::~CRangeRegularExpression()
{

}

void CRangeRegularExpression::setRange(char from, char to)
{
	m_charFrom=from;
	m_charTo=to;
}

void CRangeRegularExpression::getRange(char from, char to)
{
	from=m_charFrom;
	to=m_charTo;
}

// CStatusGraphic *CRangeRegularExpression::genStatusGraphic()
// {
// 	return CRE2SGConverter::genFromRangeRE(this);
// }

// ��Ҫ�ⲿ�ͷ�ָ��
// ICharChecker *CRangeRegularExpression::getChecker()
// {
// 	return new CRangeCharChecker(m_charFrom, m_charTo);
// }

// ��������ʽ�Ƿ���� ch �ַ�
BOOL CRangeRegularExpression::accept(char *ch)
{
	if(!ch)
		return FALSE;

	if(m_charFrom<= ch[0] && ch[0]<=m_charTo)
		return TRUE;

	return FALSE;
}
