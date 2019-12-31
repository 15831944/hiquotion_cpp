// StatuteStatusGraphBuilder.h: interface for the CStatuteStatusGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUTESTATUSGRAPHBUILDER_H__337B3EFD_F7BF_4D6F_BF7C_5F10D2025AE6__INCLUDED_)
#define AFX_STATUTESTATUSGRAPHBUILDER_H__337B3EFD_F7BF_4D6F_BF7C_5F10D2025AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IStatuteStatusGraphBuilder.h"
#include "StatuteList.h"
#include <string>
#include "..\StatuteStatusGraph\StatuteStatusGraph.h"

class CStatuteStatusGraphBuilder : public IStatuteStatusGraphBuilder  
{
public:
	CStatuteStatusGraphBuilder();
	virtual ~CStatuteStatusGraphBuilder();

	int buildStatuteStatusGraph(CStatuteList *statuteList/*, CStatuteStatusGraph *graph*/);
	int buildStatuteStatusGraphFromDefText(std::string text, ILexer *lexer/*, CStatuteStatusGraph *graph*/, string statuteSymbol="=>", string lineSplitter="\r\n");
	int buildStatuteStatusGraphFromDefFile(std::string filePath, ILexer *lexer/*, CStatuteStatusGraph *graph*/, string statuteSymbol="=>", string lineSplitter="\r\n");
	int build();

	CStatuteList * getStatuteList() const { return m_statuteList; }
	void setStatuteList(CStatuteList * val) { m_statuteList = val; }

	CStatuteStatusGraph *getStatuteStatusGraph() const { return m_graph; }

	std::string getErrMsg() const { return m_errMsg; }
	
private:
	// ���ݹ�Լʽ�б������ʼ�ڵ��б�
	static int buildOrigNodeList(CStatuteItemList &statuteItemList, CPointerList<CStatuteStatusGraphNode *> &origNodeList);
	// �ӳ�ʼ�ڵ��б���������ڵ�
	static int buildOtherNodes(CPointerList<CStatuteStatusGraphNode *> &origNodeList, CStatuteItemList &origStatuteItemList, CStatuteStatusGraph *graph);
	// �ӳ�ʼ�ڵ��б��еĽڵ㣬��������ڵ�
	static int buildPostNodes(CStatuteStatusGraphNode *node, CPointerList<CStatuteStatusGraphNode *> &origNodeList, CStatuteItemList &origStatuteItemList, CStatuteStatusGraph *graph);
	// ����Լʽ�б�ת���ɹ�Լʽ��Ŀ�б�
	static void statuteList2StatuteItemList(CStatuteList *statuteList, CStatuteItemList *statuteItemList);

private:
	CStatuteStatusGraph *m_graph;
	CStatuteList *m_statuteList;
	std::string m_errMsg;
};

#endif // !defined(AFX_STATUTESTATUSGRAPHBUILDER_H__337B3EFD_F7BF_4D6F_BF7C_5F10D2025AE6__INCLUDED_)
