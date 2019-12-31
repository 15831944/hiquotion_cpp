// StatuteStatusMachine.cpp: implementation of the CStatuteStatusMachine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteStatusMachine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteStatusMachine::CStatuteStatusMachine()
: m_statuteStatusGraph(NULL)
{

}

CStatuteStatusMachine::CStatuteStatusMachine( CStatuteStatusGraph *statuteStatusGraph )
: m_statuteStatusGraph(statuteStatusGraph)
{

}

CStatuteStatusMachine::~CStatuteStatusMachine()
{

}

BOOL CStatuteStatusMachine::initCurrentNode()
{
	if(!m_statuteStatusGraph)
		return FALSE;

	return m_statuteStatusGraph->initCurrentNode();
}

void CStatuteStatusMachine::setCurrentNode(CStatuteStatusGraphNode *node)
{
	if(!m_statuteStatusGraph)
		return;

	m_statuteStatusGraph->setCurrentNode(node);
}

CStatuteStatusGraphNode *CStatuteStatusMachine::getCurrentNode()
{
	if(!m_statuteStatusGraph)
		return NULL;

	return m_statuteStatusGraph->getCurrentNode();
}

// �ӵ�ǰ�ڵ���ָ�����Ƶĳ���
// ����ֵ��
// 1���ɹ�
// 0����ǰ�ڵ㲻��������Ϊ arcName �ĳ���
// -1��������ָ��Ϊ��
// -2����Լ״̬��ָ��Ϊ��
// -3����ǰ�ڵ�Ϊ�գ��������³�ʼ��ʧ��
// -4����ǰ�ڵ�Ϊ�գ��������³�ʼ������ȻΪ��
// -5����ǰ�ڵ������Ϊ arcName �ĳ�����Ψһ
// -6��ָ������ arcName �ĳ������ڣ�����Ϊ��
// -7��ָ������ arcName �ĳ�����to�ڵ�Ϊ��
//int CStatuteStatusMachine::goThrough(string arcName)
int CStatuteStatusMachine::goThrough(MachineToken *arcData)
{
	if(!arcData)
		return -1;

	if(!m_statuteStatusGraph)
		return -2;
	
	CStatuteStatusGraphNode *currentNode=m_statuteStatusGraph->getCurrentNode();
	if(!currentNode)
	{
		if(!m_statuteStatusGraph->initCurrentNode())
			return -3;

		currentNode=m_statuteStatusGraph->getCurrentNode();
		if(!currentNode)
			return -4;
	}
		
	CPointerList<CStatuteStatusGraphArc *> arcList;
	currentNode->getOutArcsBy(arcData, arcList);
	if(arcList.size()<=0)
		return 0;
	
	if(arcList.size()>1)
		return -5;
	
	CStatuteStatusGraphArc *arc=arcList.at(0);
	if(!arc)
		return -6;
	
	CStatuteStatusGraphNode *nodeTo=arc->getNodeTo();
	if(!nodeTo)
		return -7;
	
	m_statuteStatusGraph->setCurrentNode(nodeTo);
		
	return 1;
}

BOOL CStatuteStatusMachine::isCurrentNodeAccepted()
{
	if(!m_statuteStatusGraph)
		return FALSE;

	return m_statuteStatusGraph->isCurrentNodeAccepted();
}

BOOL CStatuteStatusMachine::isCurrentNodeFinal()
{
	if(!m_statuteStatusGraph)
		return FALSE;
	
	return m_statuteStatusGraph->isCurrentNodeFinal();	
}

int CStatuteStatusMachine::getNodeCount()
{
	if(!m_statuteStatusGraph)
		return -1;

	return m_statuteStatusGraph->getNodeCount();
}