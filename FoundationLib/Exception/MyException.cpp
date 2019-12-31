// Exception.cpp: implementation of the CException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyException::CMyException(eExceptionType exceptionType,string description,string reason,string reason4Debug)
{
	m_exceptionType=exceptionType;
	m_description=description;
	m_reason=reason;
	m_reason4Debug=reason4Debug;
}

CMyException::~CMyException()
{

}

void CMyException::showMessage()
{
	switch(m_exceptionType)
	{
// 		EXCEPTION_UNKNOWN,  //  0
// 		EXCEPTION_INTERNAL, // 1
// 		EXCEPTION_EXTERNAL, // 2

		// δ֪�쳣��ûɶ˵��
		// �ڲ��쳣�����û������йص�û��ֱ�ӹ�ϵ���쳣
			// ��ʱ����������ڵ���״̬������ʾ m_reason4Debug �ĳ���ԭ�򣬱��ڵ��ԣ�������ʾ m_reason4Debug��
		// �ⲿ�쳣�����û�����ֱ�ӹ�ϵ���쳣

		case EXCEPTION_UNKNOWN:
			showUnknownMessage();
			break;
		case EXCEPTION_INTERNAL:
			showInternalMessage();
			break;
		case EXCEPTION_EXTERNAL:
			showExternalMessage();
			break;
	}
}

string CMyException::toString(BOOL showDebugReason)
{
	string str="\n�쳣�����\n�쳣���ͣ�";
	switch(m_exceptionType)
	{
		case EXCEPTION_UNKNOWN:
			str+="δ֪�쳣";
			break;
		case EXCEPTION_INTERNAL:
			str+="�ڲ��쳣";
			break;
		case EXCEPTION_EXTERNAL:
			str+="�ⲿ�쳣";
			break;
	}
	str+="\n�쳣������"+m_description;
	str+="\n�쳣ԭ��"+m_reason;
	if(showDebugReason)
		str+="\n�쳣ԭ��(���Ի���)��"+m_reason4Debug;
	str+="\n�쳣������\n";

	return str;
}

void CMyException::showUnknownMessage()
{
	AfxMessageBox("��������δ֪�쳣");
}

void CMyException::showInternalMessage()
{
	string msg="���������ڼ�������������쳣��������������˲��㣬�������Ǹ�⡣\n\n";
	msg = msg + "�쳣������" + m_description +"\n\n";
	msg = msg + "�쳣ԭ��" + m_reason +"\n\n";
#ifdef _DEBUG
	msg = msg + "������Ϣ��" + m_reason4Debug;
#endif
	AfxMessageBox(msg.c_str());
}

void CMyException::showExternalMessage()
{
	string msg="���������ڼ�������������쳣��������������˲��㣬�������Ǹ�⡣\n\n";
	msg = msg + "�쳣������" + m_description +"\n\n";
	msg = msg + "�쳣ԭ��" + m_reason;
	AfxMessageBox(msg.c_str());
}
