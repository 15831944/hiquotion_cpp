// MergenceStatusGraphNode.h: interface for the CMergenceStatusGraphNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERGENCESTATUSGRAPHNODE_H__922E4D9D_844B_42D3_AE71_A96170429DE6__INCLUDED_)
#define AFX_MERGENCESTATUSGRAPHNODE_H__922E4D9D_844B_42D3_AE71_A96170429DE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StatuteStatusGraphArc.h"
#include <string>
#include <c++\FoundationLib\DataStructLib\SelfContainer\SelfGraphNode.h>
#include "../StatuteAnalyzer/Statute.h"
#include "../StatuteAnalyzer/StatuteItemList.h"
// #include "StatuteInfoList.h"

using namespace std;

class CStatuteStatusGraphArc;

class CStatuteStatusGraphNode : public CSelfGraphNode<CStatuteStatusGraphArc *, int>
{
public:
	CStatuteStatusGraphNode();
	CStatuteStatusGraphNode(CStatuteItemList *itemList);
	CStatuteStatusGraphNode(BOOL isFinal);
	CStatuteStatusGraphNode(std::string errMsg);
	CStatuteStatusGraphNode(BOOL isFinal, std::string errMsg);
	virtual ~CStatuteStatusGraphNode();

	// �ж� token �� ������arcData �Ƿ����
	BOOL isArcDataEquals(MachineToken *token, MachineToken *arcData);

	// �ڵ��Ƿ����ָ�����Ƶĳ���
	BOOL containOutArcBy(MachineToken *arcData);

	// ������������ȡ�����б�Ϊʲô���б���Ϊ�����п�����������ͬ�ģ�
	void getOutArcsBy(MachineToken *arcData, CPointerList<CStatuteStatusGraphArc *> &arcs);

	// ����Ƿ��е� nodeTo �ڵ�ĳ���
	BOOL hasOutArcToNode(CStatuteStatusGraphNode *nodeTo);
	
	// ��ӹ�Լʽ��Ŀ
	void add(StatuteItem *item);
	void add(Statute *statute, int indexInStatuteList);
	void add(Statute *statute, int indexInStatuteList, int itemPosition);

	// ��ӡ��Լʽ��Ŀ��Ϣ
	string printStatuteItemListInfo();

	BOOL isOrigNode() const { return m_isOrigNode; }
	void setOrigNode(BOOL val) { m_isOrigNode = val; }

	BOOL isFinal() const { return m_isFinal; }
	void setFinal(BOOL val) { m_isFinal = val; }
	
// 	int getIndexInStatuteItemList() const { return m_indexInStatuteList; }
// 	void setIndexInStatuteList(int val) { m_indexInStatuteList = val; }
	
	Statute * getStatuteOfFinal() const { return m_statuteOfFinal; }
	void setStatuteOfFinal(Statute * val) { m_statuteOfFinal = val; }

	int getTokenCount() const { return m_tokenCount; }
	void setTokenCount(int val) { m_tokenCount = val; }

	BOOL isAccepted() const { return m_isAccepted; }
	void setAccepted(BOOL val) { m_isAccepted = val; }

	std::string getErrMsg() const { return m_errMsg; }
	void setErrMsg(std::string val) { m_errMsg = val; }
	
	CStatuteItemList * getStatuteItemList() const { return m_itemList; }
	void setItemList(CStatuteItemList * val) { m_itemList = val; }

private:
	BOOL m_isOrigNode;  // �������ֳ�ʼ�ڵ�ͺ��������Ľڵ㣬��һ�����������Ľڵ��ǽ��ܽڵ㣬���Ըñ������������ҽ��ܽڵ�ʱ�����õ�
	BOOL m_isFinal;  // �Ƿ����սڵ�
// 	int m_indexInStatuteList;  // �����սڵ㣬��Ҫ֪���ڹ�Լ�б��е�����
	Statute *m_statuteOfFinal;  // �����սڵ㣬��Ҫ֪���ڹ�Լ�б��еĹ�Լʽ
	int m_tokenCount;  // �����սڵ㣬��Ҫ֪��token�ĸ������Ա����ϲ����֪����ջ�е������ٸ��ڵ�
	BOOL m_isAccepted;  // �Ƿ��ǿɽ��ܽڵ�
	string m_errMsg;

	CStatuteItemList *m_itemList;
};

#endif // !defined(AFX_MERGENCESTATUSGRAPHNODE_H__922E4D9D_844B_42D3_AE71_A96170429DE6__INCLUDED_)
