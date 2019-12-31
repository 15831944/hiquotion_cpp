// EntityClassGen.h: interface for the CEntityClassGen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITYCLASSGEN_H__B9A1DC1B_64B9_49E4_AB29_4AB4514F52E1__INCLUDED_)
#define AFX_ENTITYCLASSGEN_H__B9A1DC1B_64B9_49E4_AB29_4AB4514F52E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\DataStructLib\PointerList.h>
#include "ClassProperty.h"

class CEntityClassGen  
{
public:
	CEntityClassGen();
	CEntityClassGen(CString className, BOOL isIncludeStdAfx=TRUE);
	virtual ~CEntityClassGen();

	int genInclude(CString includeList);
	int genProperty(CString propertyList);

	CString genHeadFileCode(CString filename);
	CString genImplementFileCode(CString filename);
	
	int genFile(CString filename);

	CString genDefaultConstructDeclareCode();  // ����Ĭ�Ϲ��캯������������
	CString genConstructDeclareCode(); // ���ɹ��캯������������
	CString genDefaultConstructCode();  // ����Ĭ�Ϲ��캯�����룬��ʼ�����б���ΪĬ��ֵ
	CString genConstructCode(); // ���ɹ��캯�����룬ͬʱ��ʼ�����б���Ϊ�������
	CString genDeconstructCode();  // ������������

	CString getClassname() const { return m_classname; }
	void setClassname(CString val) { m_classname = val; }

// 	CString getFilename() const { return m_filename; }
// 	void setFilename(CString val) { m_filename = val; }

private:
	CString m_classname;
	CStringArray m_include;
	CPointerList<CClassProperty *> m_propertyList;
// 	CString m_filename;

	BOOL m_isIncludeStdAfx;
};

#endif // !defined(AFX_ENTITYCLASSGEN_H__B9A1DC1B_64B9_49E4_AB29_4AB4514F52E1__INCLUDED_)
