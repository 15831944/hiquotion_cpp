// StringRegularExpression.cpp: implementation of the CStringRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringRegularExpression.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringRegularExpression::CStringRegularExpression()
: m_expr("")
{

}

CStringRegularExpression::CStringRegularExpression(std::string expr)
: m_expr(expr)
{

}

CStringRegularExpression::~CStringRegularExpression()
{

}

// ��������ʽ�Ƿ���� ch �ַ�
BOOL CStringRegularExpression::accept(char *ch)
{
	if(!ch)
		return FALSE;

	std::string s=ch;
	return m_expr==s;
}