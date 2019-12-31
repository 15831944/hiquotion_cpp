// FormattedString.cpp: implementation of the CFormattedString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FormattedString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFormattedString::CFormattedString()
{

}

CFormattedString::~CFormattedString()
{

}

std::string CFormattedString::formatString(char *msg, ...)
{
	char s[1000];
	memset(s, 0x00, 1000);
	va_list ap;
	int n=0,size=1000;
	va_start(ap, msg); //��ÿɱ�����б�,����fmt���ó��������������ͣ�Ҳ�Ƿ������������ơ�%d%s�����ַ���
	n=_vsnprintf(s, size, msg, ap); //д���ַ���s
	va_end(ap); //�ͷ���Դ,������va_start�ɶԵ���
	std::string str=s;
	return str;
}
