// TypeValue.cpp: implementation of the CTypeValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EntityGenerator.h"
#include "TypeValue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTypeValue::CTypeValue()
{

}

CTypeValue::~CTypeValue()
{

}

CString CTypeValue::getDefaultValue( CString type )
{
	// ָ�����͵ģ�Ĭ��ֵΪ NULL
	if(type.Right(1)=="*")
		return "NULL";

	// ���ֵģ�Ĭ��ֵΪ 0
	if(type=="int" || type=="long" || type=="float" || type=="double")
		return "0";
	
	if(type=="string" || type=="std::string" || type=="CString")
		return "\"\"";

	if(type=="char")
		return "'\0'";

	return "";
}