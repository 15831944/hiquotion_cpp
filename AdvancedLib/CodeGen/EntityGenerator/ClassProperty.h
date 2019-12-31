// ClassProperty.h: interface for the CClassProperty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSPROPERTY_H__7151F377_8E51_4CD4_A045_20EE00793FB9__INCLUDED_)
#define AFX_CLASSPROPERTY_H__7151F377_8E51_4CD4_A045_20EE00793FB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClassProperty  
{
public:
	CClassProperty();
	CClassProperty(CString name, CString type, /*CString scope, */CString defaultValue);
	virtual ~CClassProperty();

	CString genDeclareCode();      // ������������
	CString genFunctionParaCode();      // ���ɺ�����������
	CString genConstructInitDefaltCode();    // ���ɹ��캯���г�ʼ���Ĵ���
	CString genConstructInitCode();    // ���ɹ��캯���г�ʼ���Ĵ���
	CString genGetCode();       // ���� get ����
	CString genSetCode();       // ���� set ����

	CString getName() const { return m_name; }
	void setName(CString val) { m_name = val; }

	CString getType() const { return m_type; }
	void setType(CString val) { m_type = val; }

// 	CString getScope() const { return m_scope; }
// 	void setScope(CString val) { m_scope = val; }

	CString getDefault() const { return m_default; }
	void setDefault(CString val) { m_default = val; }

private:
	CString m_name;     // ������
	CString m_type;     // ��������
// 	CString m_scope;    // ���÷�Χ
	CString m_default;  // ����Ĭ��ֵ
};

#endif // !defined(AFX_CLASSPROPERTY_H__7151F377_8E51_4CD4_A045_20EE00793FB9__INCLUDED_)
