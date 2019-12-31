// StatuteStatusGraphBuilder.cpp: implementation of the CStatuteStatusGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteStatusGraphBuilder.h"
#include "..\MemManager\MemManager.h"
#include <C++\FoundationLib\StringExtLib\StringExt.h>
#include <string>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteStatusGraphBuilder::CStatuteStatusGraphBuilder()
{
	m_graph=new CStatuteStatusGraph();
}

CStatuteStatusGraphBuilder::~CStatuteStatusGraphBuilder()
{
	// ���������˳�֮ǰ��Ҫɾ�����й�Լ��Ŀ
	CMemManager::destroyAllStatuteItems();

	delete m_graph;
}

int CStatuteStatusGraphBuilder::buildStatuteStatusGraph( CStatuteList *statuteList/*, CStatuteStatusGraph *m_graph*/ )
{
	if(statuteList->size()<=0)
		return -1;
	
	if(!m_graph)
		return -2;

	// ���״̬ͼ
	m_graph->removeAllNodes();
	m_graph->removeAllArcs();
	
	// ����ϴ�ִ�и÷������洢����������
	CMemManager::destroyAllStatuteItems();
	
	CStatuteItemList statuteItemList;
	// ת����Լʽ�б�Ϊ��Լʽ��Ŀ�б����Ǵ�С������֣�
	statuteList2StatuteItemList(statuteList, &statuteItemList);
	
#ifdef _DEBUG
	int count1=statuteItemList.size();
#endif
	
	CPointerList<CStatuteStatusGraphNode *> origNodeList;
	
	// ������Լʽ״̬ͼ�еĳ�ʼ�ڵ㣬ͨ���ǵ�һ����ڵ�
	int ret=buildOrigNodeList(statuteItemList, origNodeList);
	if(ret!=0)
		return -3;
	
	// �ѳ�ʼ�ڵ���ӵ���Լʽ״̬ͼ��
	int i=0;
	for(i=0;i<origNodeList.size();i++)
	{
		CStatuteStatusGraphNode *node=origNodeList.at(i);
		if(!node)
			continue;
		
		m_graph->addNode(node);
	}
	
	// #ifdef _DEBUG
	// 	printf("1st graph info:\n\n");
	// 	graph->printGraphInfo();
	// #endif
	
	// �����Լʽ״̬ͼ�е������ڵ�
	ret=buildOtherNodes(origNodeList, statuteItemList, m_graph);
	if(ret!=0)
		return -4;
	
	// #ifdef _DEBUG
	// 	printf("last graph info:\n\n");
	// 	graph->printGraphInfo();
	// #endif
	
	// �����ɹ�������һ���ǳ�ʼ�ڵ�����Ϊ���ܽڵ�
	if(!m_graph->setAcceptNode())
		return -5;
	
	// #ifdef _DEBUG
	// 	int count2=statuteItemList.size();
	// 
	// 	printf("pre-statuteItemList element count is %d\n", count1);
	// 	printf("post-statuteItemList element count is %d\n", count2);
	// 	printf("MemManager statuteItem count is %d\n", CMemManager::getStatuteItemCount());
	// #endif
	
	statuteItemList.clear();
	
	// CMemManager�еĹ�Լ��Ŀ������Ͳ�ɾ���ˣ��Ա��﷨�������ִ����ʱ�������Ϣ֮��
	// ���ڳ������н���֮ǰҪɾ��
	// 	CMemManager::destroyAllStatuteItems();
	
	return 0;
}

int CStatuteStatusGraphBuilder::buildStatuteStatusGraphFromDefText( std::string text, ILexer *lexer/*, CStatuteStatusGraph *m_graph*/, string statuteSymbol/*="=>"*/, string lineSplitter/*="\r\n"*/ )
{
	if(text.length()<=0)
	{
		m_errMsg="�ı�Ϊ�գ�";
		return -1;
	}
	
	CString txt=text.c_str();
	CStringArray txtArray;
	CStringExt::Split(txt, txtArray, lineSplitter.c_str());
	
	int ret=0;
	CStatuteList statuteList;
	
	for(int i=0;i<txtArray.GetSize();i++)
	{
		CString line=txtArray.GetAt(i);
		if(line.GetLength()<=0)
			continue;
		
		// �����һ���ַ�����a-z �� A-Z������Ϊ������ע�ͣ�������������
		char first=line.GetAt(0);
		if(first<'A' || (first>'Z' && first<'a') || first>'z')
			continue;
		
		if(line.Find(statuteSymbol.c_str())<=0)
		{
			m_errMsg="��Լʽ�﷨���󣡲����ڹ�Լ���ţ�" + statuteSymbol + "��";
			return -2;
		}
		
		CStringArray statuteStringArray;
		CStringExt::Split(line, statuteStringArray, statuteSymbol.c_str());
		
		std::string name=(LPTSTR)(LPCSTR)statuteStringArray.GetAt(0);
		std::string statuteString=(LPTSTR)(LPCSTR)statuteStringArray.GetAt(1);
		
		Statute *statute=new Statute;
		statute->tokenList.setSelfDestroy(TRUE);
		statute->statuteName=name;
		CValueList<string> errs;
		
// 		CKernelLexer lexer;
		ret=lexer->analyze(statuteString, statute->tokenList, errs);
		if(ret<0)
		{
			m_errMsg="�ʷ�����ʧ�ܣ�";
			if(errs.size()>0)
			{
				m_errMsg+="��һ��������Ϣ�ǣ�";
				m_errMsg+=errs.at(0).c_str();
			}
			
			delete statute;
			
			return -3;
		}
		
		if(statute->tokenList.size()<=0)
		{
			m_errMsg="token�б�Ϊ�գ������Լʽ�Ƿ���д��ȷ��";
			delete statute;
			return -4;
		}
		
		if(i==0 && statute->tokenList.size()!=1)
		{
			m_errMsg="��ʹ����չ�ķ�������֤��һ����Լʽ��ֻ����һ��token��";
			delete statute;
			return -5;
		}
		
		statuteList.push_back(statute);
	}
	
// 	m_builder.setStatuteList(&m_statuteList);
	
	return buildStatuteStatusGraph(&statuteList/*, m_graph*/);
}

int CStatuteStatusGraphBuilder::buildStatuteStatusGraphFromDefFile( std::string filePath, ILexer *lexer/*, CStatuteStatusGraph *m_graph*/, string statuteSymbol/*="=>"*/, string lineSplitter/*="\r\n"*/ )
{
	CFile fileLang;
// 	fileLang.Open("RegularDef.txt", CFile::shareDenyWrite);
	fileLang.Open(filePath.c_str(), CFile::shareDenyWrite);
//	char lang[10240];
	int len=fileLang.GetLength();
	char *lang=new char[len+1];
	fileLang.Read(lang, len);
	lang[len]='\0';
	fileLang.Close();
	
	std::string text=lang;

	return buildStatuteStatusGraphFromDefText(text, lexer/*, m_graph*/, statuteSymbol, lineSplitter);
}

int CStatuteStatusGraphBuilder::build()
{
	if(m_statuteList->size()<=0)
		return -1;
	
	if(!m_graph)
		return -2;
	
	// ����ϴ�ִ�и÷������洢����������
	CMemManager::destroyAllStatuteItems();
	
	CStatuteItemList statuteItemList;
	// ת����Լʽ�б�Ϊ��Լʽ��Ŀ�б����Ǵ�С������֣�
	statuteList2StatuteItemList(m_statuteList, &statuteItemList);
	
#ifdef _DEBUG
	int count1=statuteItemList.size();
#endif
	
	CPointerList<CStatuteStatusGraphNode *> origNodeList;
	
	// ������Լʽ״̬ͼ�еĳ�ʼ�ڵ㣬ͨ���ǵ�һ����ڵ�
	int ret=buildOrigNodeList(statuteItemList, origNodeList);
	if(ret!=0)
		return -3;
	
	// �ѳ�ʼ�ڵ���ӵ���Լʽ״̬ͼ��
	int i=0;
	for(i=0;i<origNodeList.size();i++)
	{
		CStatuteStatusGraphNode *node=origNodeList.at(i);
		if(!node)
			continue;
		
		m_graph->addNode(node);
	}
	
	// #ifdef _DEBUG
	// 	printf("1st graph info:\n\n");
	// 	graph->printGraphInfo();
	// #endif
	
	// �����Լʽ״̬ͼ�е������ڵ�
	ret=buildOtherNodes(origNodeList, statuteItemList, m_graph);
	if(ret!=0)
		return -4;
	
	// #ifdef _DEBUG
	// 	printf("last graph info:\n\n");
	// 	graph->printGraphInfo();
	// #endif
	
	// �����ɹ�������һ���ǳ�ʼ�ڵ�����Ϊ���ܽڵ�
	if(!m_graph->setAcceptNode())
		return -5;
	
	// #ifdef _DEBUG
	// 	int count2=statuteItemList.size();
	// 
	// 	printf("pre-statuteItemList element count is %d\n", count1);
	// 	printf("post-statuteItemList element count is %d\n", count2);
	// 	printf("MemManager statuteItem count is %d\n", CMemManager::getStatuteItemCount());
	// #endif
	
	statuteItemList.clear();
	
	// CMemManager�еĹ�Լ��Ŀ������Ͳ�ɾ���ˣ��Ա��﷨�������ִ����ʱ�������Ϣ֮��
	// ���ڳ������н���֮ǰҪɾ��
	// 	CMemManager::destroyAllStatuteItems();
	
	return 0;
}

// ���ݹ�Լʽ�б������ʼ�ڵ��б�
// ����ֵ��
// 0���ɹ�
// -1����Լʽ�б�Ϊ��
int CStatuteStatusGraphBuilder::buildOrigNodeList( CStatuteItemList &statuteItemList, CPointerList<CStatuteStatusGraphNode *> &origNodeList )
{
	if(statuteItemList.size()<=0)
		return -1;

	origNodeList.destroyAll();
	origNodeList.clear();

	CStatuteItemList *currentList=new CStatuteItemList(statuteItemList);

	while(currentList->size()>0)
	{
		// ���ݵ�һ����Լʽ�Ĺ�Լ��������ȡ��Լ��Ŀ�б�
		CStatuteItemList *lst=new CStatuteItemList();
		currentList->getStatuteItemListby1stStatuteName(lst);
		if(lst->size()<=0)
		{
			delete currentList;
			return -2;
		}
		
		// �Ի�ȡ���Ĺ�Լʽ��Ŀ�б����հ�����
		lst->closure(statuteItemList);
		
		// �հ�����󣬽��ù�Լʽ��Ŀ�б���ӵ�״̬ͼ�ڵ���
		CStatuteStatusGraphNode *node=new CStatuteStatusGraphNode(lst);
		node->setOrigNode(TRUE);
		origNodeList.push_back(node);

		CStatuteItemList *rest=new CStatuteItemList();
		
		// �ӳ�ʼ��Լ��Ŀ�б��а��Ѿ���ӵ���Ŀȥ����ʣ�µ�������У����ظ�ѭ��
		CPointerList<StatuteItem *>::findDifferent((CPointerList<StatuteItem *> *)currentList, (CPointerList<StatuteItem *> *)lst, (CPointerList<StatuteItem *> *)rest);

		delete currentList;
		currentList=rest;
	}

	delete currentList;

	return 0;
}

// �ӳ�ʼ�ڵ��б��еĽڵ㣬��������ڵ�
// ����ֵ��
// 0���ɹ�
// -1����ʼ�ڵ��б�Ϊ��
// -2����ʼ��Լ��Ŀ�б�Ϊ��
// -3��ͼָ��Ϊ��
int CStatuteStatusGraphBuilder::buildOtherNodes( CPointerList<CStatuteStatusGraphNode *> &origNodeList, CStatuteItemList &origStatuteItemList, CStatuteStatusGraph *graph )
{
	if(origNodeList.size()<=0)
		return -1;

	if(origStatuteItemList.size()<=0)
		return -2;

	if(!graph)
		return -3;
	
	// ��Գ�ʼ�ڵ��б��е�ÿһ���ڵ㣬���������ڵ㣨�������ĺ����ڵ�Ҳ����ӵ���ʼ�ڵ��б��У����γɵݹ鴦��
	for(int i=0;i<origNodeList.size();i++)
	{
		CStatuteStatusGraphNode *node=origNodeList.at(i);
		if(!node)
			continue;
		
		buildPostNodes(node, origNodeList, origStatuteItemList, graph);
	}

	return 0;
}

// �ӳ�ʼ�ڵ��б��еĽڵ㣬��������ڵ�
// ����ֵ��
// 0���ɹ�
// -1��������ڵ�ָ��Ϊ��
// -2����ʼ�ڵ��б�Ϊ��
// -3����ʼ��Լ��Ŀ�б�Ϊ��
// -4��ͼָ��Ϊ��
// -5��������ڵ��еĹ�Լ��Ŀ�б�Ϊ��
// -6��������ڵ��еĹ�Լ��Ŀ�б��е�Ԫ�ظ���Ϊ0
// -7�����ս��Լ��Ŀ�б�ĵ�һ����Լ��ĿΪ��
// -8�����ս��Լ��Ŀ�б�ĵ�һ����Լ��Ŀ�еĹ�ԼʽΪ��
// -9�����ս��Լ��Ŀ�б�ĵ�һ����Լ��Ŀ�еĹ�Լʽ�еĵ�ǰ��ĿtokenΪ��
// -10�����ս��Լ��Ŀ�б�ĵ�һ����Լ��Ŀ�еĹ�Լʽ�еĵ�ǰ��Ŀtoken��token����Ϊ��
// -11����token���Ƶĵ�ǰ��Լ��Ŀ�б��е�Ԫ�ظ���Ϊ0
// -12����ǰ�ڵ��У�������λ�õĹ�Լ��Ŀ����һ�����������﷨������
// -13���ڵ�����Ĺ�Լʽ��Ŀ�б��еĵ�һ����Լʽ��ĿΪ��
// -14���ڵ�����Ĺ�Լʽ��Ŀ�б��еĵ�һ����Լʽ��Ŀ�еĹ�ԼʽΪ��
int CStatuteStatusGraphBuilder::buildPostNodes(CStatuteStatusGraphNode *node, CPointerList<CStatuteStatusGraphNode *> &origNodeList, CStatuteItemList &origStatuteItemList, CStatuteStatusGraph *graph)
{
	if(!node)
		return -1;

	if(origNodeList.size()<=0)
		return -2;

	if(origStatuteItemList.size()<=0)
		return -3;

	if(!graph)
		return -4;
	
	// �ӽڵ��л�ȡ����Լʽ��Ŀ�б�
	CStatuteItemList *statuteItemList4Node=node->getStatuteItemList();
	if(!statuteItemList4Node)
		return -5;

	if(statuteItemList4Node->size()<=0)
		return -6;

	// �����Լ��Ŀ�д�������λ�õ���Ŀ��˵���ýڵ����ս��
	if(statuteItemList4Node->isContainItemInFinalPosition())
	{
		node->setFinal(TRUE);

		CStatuteItemList *finalList=new CStatuteItemList();
		finalList->setSelfDestroy(FALSE);
		statuteItemList4Node->getStatuteItemListInFinalPosition(finalList);
		if(finalList->size()>1)
		{
			delete finalList;
			return -12;
		}

		StatuteItem *statuteItem=statuteItemList4Node->at(0);
		if(!statuteItem)
		{
			delete finalList;
			return -13;
		}
		
		Statute *statute=statuteItem->statute;
		if(!statute)
		{
			delete finalList;
			return -14;
		}		
		
//		node->setIndexInStatuteList(statuteItem->indexInStatuteList);
		node->setStatuteOfFinal(statuteItem->statute);
		node->setTokenCount(statute->tokenList.size());

		delete finalList;
	}

	// �ӹ�Լʽ��Ŀ�б��л�ȡ��ЩС��λ�ò��������Ĺ�Լʽ��Ŀ�б�
	CStatuteItemList *currentList=new CStatuteItemList();
	statuteItemList4Node->getStatuteItemListNotinFinalPosition(currentList);
	if(currentList->size()<=0)
	{
		// ˵�������սڵ㡣ǰ���Ѿ�������������սڵ�Ҫ�����£�����ֱ�ӷ���

		delete currentList;

		return 0;
	}

	while(currentList->size()>0)
	{
		StatuteItem *statuteItem=currentList->at(0);
		if(!statuteItem)
		{
			delete currentList;
			return -7;
		}
		
		statuteItem->checkPosition();
		
		Statute *statute=statuteItem->statute;
		if(!statute)
		{
			delete currentList;
			return -8;
		}
		
		MachineToken *token=statute->tokenList.at(statuteItem->itemPosition);
		if(!token)
		{
			delete currentList;
			return -9;
		}
		
		if(token->token=="")
		{
			delete currentList;
			return -10;
		}

		// �ڵ�ǰ��Լʽ��Ŀ�б��У��ӵ�ǰ��Ŀλ����token�Ĺ�Լʽ�������ж�������Է����б�
		CStatuteItemList *lst=new CStatuteItemList();
		currentList->getCurrentStatuteItemListbyTokenName(token->token, lst);
		if(lst->size()<=0)
		{
			delete lst;
			delete currentList;
			return -11;
		}

		// ����token�Ĺ�Լʽ��Ŀ�б��У���ȡ�߹�token��Ĺ�Լʽ��Ŀ�б�
		CStatuteItemList *nextList=new CStatuteItemList();
		lst->genNextStatuteItemList(nextList);
		
		// ����߹�token��Ĺ�Լʽ��Ŀ�б����հ�����
		nextList->closure(origStatuteItemList);
		
		// ����߹�token��Ĺ�Լʽ��Ŀ�б��Ѿ������Լ״̬ͼ�е�ĳ���ڵ㣬��ֱ�ӻ�ȡ�ýڵ�
		// ���򣬴����½ڵ�
		CStatuteStatusGraphNode *postNode=NULL;
		string key=nextList->genStatuteKey();
		if(graph->containNodeby(key))
		{
			// ���� DestroyAll() �б��е�����Ԫ�أ���Ϊ��Щ���� CMemManager ��ģ���Щ�Ǵӱ���б������ù�����
			// DestroyAll() �ᵼ�������б��л�ȡԪ������ʧ�ܣ�
			nextList->clear();
			delete nextList;

			postNode=graph->getNodeby(key);
		}
		else
		{
			postNode=new CStatuteStatusGraphNode(nextList);
			graph->addNode(postNode);
			origNodeList.push_back(postNode);
		}
		
		// ������ǰ�ڵ㵽�ýڵ�Ļ�
		CStatuteStatusGraphArc *arcToPostNode=new CStatuteStatusGraphArc(node, postNode, token);
		graph->addArc(arcToPostNode);
		
		// �ӵ�ǰ��Լ��Ŀ�б��а��Ѿ���ӵ���Ŀȥ����ʣ�µ�������У����ظ�ѭ��
		CStatuteItemList *rest=new CStatuteItemList();
		CPointerList<StatuteItem *>::findDifferent((CPointerList<StatuteItem *> *)currentList, (CPointerList<StatuteItem *> *)lst, (CPointerList<StatuteItem *> *)rest);

// #ifdef _DEBUG
// 		printf("/*******************\n");
// 		printf("currentList size = %d\n lst size = %d\n rest size = %d\n\n", currentList->size(), lst->size(), rest->size());
// 		printf("ist graph info:\n\n");
// 		graph->printGraphInfo();
// 		printf("*******************/\n\n");
// #endif
		
		delete lst;
		delete currentList;
		currentList=rest;
	}

	delete currentList;

	return 0;
}

// ����Լʽ�б�ת���ɹ�Լʽ��Ŀ�б�
void CStatuteStatusGraphBuilder::statuteList2StatuteItemList( CStatuteList *statuteList, CStatuteItemList *statuteItemList )
{
	if(!statuteList || !statuteItemList)
		return;

	statuteItemList->destroyAll();
	statuteItemList->clear();

	for(int i=0;i<statuteList->size();i++)
	{
		Statute *statute=statuteList->at(i);
		if(!statute)
			continue;

		StatuteItem *item=new StatuteItem(statute, i);
		CMemManager::addStatuteItem(item);
		statuteItemList->push_back(item);
	}
}
