// StatuteStatusMachine.h: interface for the CStatuteStatusMachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUTESTATUSMACHINE_H__9316458F_4E25_4EF3_B90F_1773D44E7458__INCLUDED_)
#define AFX_STATUTESTATUSMACHINE_H__9316458F_4E25_4EF3_B90F_1773D44E7458__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\StatuteStatusGraph\StatuteStatusGraph.h"
#include "..\..\LEX\LEXER\ILexer.h"

class CStatuteStatusMachine  
{
public:
	CStatuteStatusMachine();
	CStatuteStatusMachine(CStatuteStatusGraph *statuteStatusGraph);
	virtual ~CStatuteStatusMachine();

	// ��ʼ����ǰ�ڵ�
	BOOL initCurrentNode();

	void setCurrentNode(CStatuteStatusGraphNode *node);
	CStatuteStatusGraphNode *getCurrentNode();

	// �ӵ�ǰ�ڵ���ָ�����Ƶĳ���
	int goThrough(MachineToken *arcData);

	BOOL isCurrentNodeAccepted();
	BOOL isCurrentNodeFinal();

	int getNodeCount();

	CStatuteStatusGraph * getStatuteStatusGraph() const { return m_statuteStatusGraph; }
	void setStatuteStatusGraph(CStatuteStatusGraph * val) { m_statuteStatusGraph = val; }
private:
	CStatuteStatusGraph *m_statuteStatusGraph;

};

#endif // !defined(AFX_STATUTESTATUSMACHINE_H__9316458F_4E25_4EF3_B90F_1773D44E7458__INCLUDED_)
