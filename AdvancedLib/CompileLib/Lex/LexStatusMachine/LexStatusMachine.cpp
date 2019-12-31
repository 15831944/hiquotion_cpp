// StatusMachine.cpp: implementation of the CStatusMachine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LexStatusMachine.h"
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\IRegularExpression.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLexStatusMachine::CLexStatusMachine()
: m_initStatus(-1)
{
}

CLexStatusMachine::CLexStatusMachine(CLexStatusGraph *graphic)
: m_initStatus(-1)
{
	m_graphic=graphic;
}

CLexStatusMachine::~CLexStatusMachine()
{

}

// �ָ���ʼ״̬����ָ��ʼ״̬
void CLexStatusMachine::init()
{
	m_string="";

	if(!m_graphic)
	{
		m_currentNode=NULL;
		return;
	}

	m_currentNode=m_graphic->getStartNode();
	m_initStatus=1;
}

// �Ƿ���ܸ������ַ�
// 1������
// 0��������
// -1����ǰ���ָ��Ϊ��
int CLexStatusMachine::accept(char ch)
{
	if(!m_currentNode)
		return -1;

	for(int i=0;i<m_currentNode->getOutArcCount();i++)
	{
		CStatusGraphArc *arc=m_currentNode->getOutArc(i);
		if(!arc)
			continue;

		IRegularExpression *re=arc->getArcData();
		if(!re)
			continue;

		// ������ܣ��򱣴浱ǰ�ַ�����״̬�ƶ�����һ����㣬����TRUE�����ܣ�
		if(re->accept(&ch))
		{
			m_string+=ch;
			m_currentNode=arc->getNodeTo();

			m_initStatus=0;

			return 1;
		}
	}

	return 0;
}

// ��������ĳ�ַ�ʱ���ж��Ƿ��ڽ���״̬
// 1����
// 0������
// -1����ǰ���ָ��Ϊ��
int CLexStatusMachine::isFinalStatus()
{
	if(!m_currentNode)
		return -1;

	if(m_currentNode->isFinal())
		return 1;
	else
		return 0;
}

// ��ȡ״̬�����ַ��������ͣ����������Ե�ǰ��̬��㣩
std::string CLexStatusMachine::getStringType()
{
	if(!m_currentNode)
		return "";

	if(!m_currentNode->isFinal())
		return "";

	return m_currentNode->getType();
}

// ��ȡ״̬�����ַ����������ͣ����������Ե�ǰ��̬��㣩
std::string CLexStatusMachine::getStringSubType()
{
	if(!m_currentNode)
		return "";
	
	if(!m_currentNode->isFinal())
		return "";
	
	return m_currentNode->getSubtype();
}

// ��ȡ״̬��������Ϣ������Ϣ���Է���̬��㣩
std::string CLexStatusMachine::getErrMsg()
{
	if(!m_currentNode)
		return "";

	if(m_currentNode->isFinal())
		return "";

	return m_currentNode->getErrMsg();
}
