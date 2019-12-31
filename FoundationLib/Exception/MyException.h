// MyException.h: interface for the CMyException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEXCEPTION_H__77B9451D_4B03_49F1_BAFA_4D8BAC71851C__INCLUDED_)
#define AFX_MYEXCEPTION_H__77B9451D_4B03_49F1_BAFA_4D8BAC71851C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum eExceptionType
{
	// δ֪�쳣��ûɶ˵��
	// �ڲ��쳣�����û������йص�û��ֱ�ӹ�ϵ���쳣
	// ��ʱ����������ڵ���״̬������ʾ m_reason4Debug �ĳ���ԭ�򣬱��ڵ��ԣ�������ʾ m_reason4Debug��
	// �ⲿ�쳣�����û�����ֱ�ӹ�ϵ���쳣

	EXCEPTION_UNKNOWN,  //  0
	EXCEPTION_INTERNAL, // 1
	EXCEPTION_EXTERNAL, // 2
};

class CMyException 
{
public:
	CMyException(eExceptionType exceptionType,string description="",string reason="",string reason4Debug="");
	virtual ~CMyException();

	void showMessage();
	string toString(BOOL showDebugReason=FALSE);

	string m_description;
	string m_reason;
	string m_reason4Debug;   // ˵���������ĸ��ļ����ĸ��࣬�ĸ�����������ʲô��ʱ����ֵ��쳣�����ڵ��Ե�ʱ��λ

protected:
	void showUnknownMessage();
	void showInternalMessage();
	void showExternalMessage();

	eExceptionType m_exceptionType;

};

#endif // !defined(AFX_MyEXCEPTION_H__77B9451D_4B03_49F1_BAFA_4D8BAC71851C__INCLUDED_)
