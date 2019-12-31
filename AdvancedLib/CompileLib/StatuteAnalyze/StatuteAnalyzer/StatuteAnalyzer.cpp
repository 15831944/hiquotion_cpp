// MergenceAnalyzer.cpp: implementation of the CMergenceAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteAnalyzer.h"
#include <sstream>
#include <C++\FoundationLib\StringExtLib\StringExt.h>
//#include "../StatuteAnalyzer/StatuteStatusMachineBuilder.h"
#include "../../KernelLex/KernelLexer/KernelLexer.h"
#include "StatuteTreeNode.h"
#include <C++\FoundationLib\DataStructLib\PointerStack.h>
#include <sstream>
#include "../MemManager/MemManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// static CStatuteItemList g_statuteItemList;
static CPointerList<CStatuteTreeNode *> g_statuteTreeNodeList;
static CPointerList<MachineToken *> g_tokenList;

extern CLog log;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteAnalyzer::CStatuteAnalyzer()
{
	g_statuteTreeNodeList.setSelfDestroy(TRUE);
	g_tokenList.setSelfDestroy(TRUE);

#ifdef _DEBUG
	log.setProjectName("StatuteAnalyzer");
#endif

}

CStatuteAnalyzer::~CStatuteAnalyzer()
{
	// ���������˳�֮ǰ��Ҫɾ�����й�Լ��Ŀ
	CMemManager::destroyAllStatuteItems();
}

// int CStatuteAnalyzer::analyzeFromSrcText( std::string text, ILexer *lexer, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList )
// {
// 	CPointerList<MachineToken *> tokenList;
// 	tokenList.setSelfDestroy(TRUE);
// 	
// // 	CKernelLexer lex;
// 	CValueList<string> errlst;
// 	int ret=lexer->analyze(text, tokenList, errlst);
// 	if(ret!=0)
// 	{
// 		stringstream ss;
// 		ss<<"Դ�����дʷ����󣡴������� " << ret;
// 		printf(ss.str().c_str());
// 		printf("\n");
// 		return -1;
// 	}
// 	
// // 	CStatuteTreeNode root;
// // 	CPointerList<MachineToken *> grammer_errList;
// 	return analyze(tokenList, root, errorTokenList);
// 
// // 	ret=m_kernelAnalyzer.analyze(tokenList, &root, grammer_errList);
// // 	if(ret!=0)
// // 	{
// // 		stringstream ss;
// // 		ss<<"Դ�������﷨���󣡴������� " << ret;
// // 		printf(ss.str().c_str());
// // 		printf("\n");
// // 		system("pause");
// // 		return -2;
// // 	}
// // 	
// // 	printf("Դ������ɹ���");
// // 	return 0;
// }
// 
// int CStatuteAnalyzer::analyzeFromSrcFile( std::string filePath, ILexer *lexer, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList )
// {
// 	CFile fileLang;
// 	fileLang.Open(filePath.c_str(), CFile::shareDenyWrite);
// 	//	char lang[10240];
// 	int len=fileLang.GetLength();
// 	char *lang=new char[len+1];
// 	fileLang.Read(lang, len);
// 	lang[len]='\0';
// 	fileLang.Close();
// 	
// 	std::string text=lang;
// 
// 	return analyzeFromSrcText(text, lexer, root, errorTokenList);
// }



// ���ɹ�Լ��
// ������
// tokenList��Դ���token�б�
// origStatuteList����ʼ��Լ�б�
// root�����صĹ�Լ���ĸ�
// errorTokenList������ʱ���صĴ���Token�б�
// ����ֵ��
//  1�������ɹ�
//  0��������ɣ����д�����Ҫ�鿴������errorTokenList
// -1��token�б�Ϊ��
// -2����Լ״̬ͼ��û�нڵ�
// -3����ʼ����ǰ�ڵ�ʧ��
// -4��ɨ�������е��ַ����󣬵�ǰ�ڵ��ǿɹ�Լʱ��ִ�й�Լ���ִ���
// -5��û���ߵ��ɽ��ܽڵ㣬����ʧ��
// -11����Լʱ����ǰ�ڵ��м�¼�Ĺ�Լ�б����������б�Χ
// -12����Լʱ����ǰ�ڵ��м�¼�ĵ�ǰ�����Ĺ�ԼʽΪ��
// -13����Լʽ��token�����������򳬳��˵�ǰtokenջ��Ԫ�صĸ���
// -14����Լ��graph�߹�Լ��Ĺ�Լ����·�����ɹ���˵��graph�Ĺ��������⣨����Ӧ����һ���ɹ��ģ�
int CStatuteAnalyzer::analyze(CPointerList<MachineToken *> &tokenList, /*CStatuteList &origStatuteList,*/ CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList)
{
#ifdef _DEBUG
	log.writeDebug("�﷨����������ڣ�");
#endif
				
	if(tokenList.size()<=0)
		return -1;

	CPointerStack<CStatuteStatusGraphNode *> statuteStatusGraphNodeStack;
	CPointerStack<CStatuteTreeNode *> statuteTreeNodeStack;

// 	statuteTreeNodeStack.setSelfDestroy(TRUE);

	errorTokenList.destroyAll();
	errorTokenList.clear();

  /*
	1. graph��ʼ����ǰ�ڵ�
	2. ��ȡtokenList�ĵ�ǰtoken
	3. �����graph�ĵ�ǰ�ڵ��ܹ�����token�ߵ���һ�ڵ㣬��
		1) ��token����ɹ�Լ���ڵ㣬�����Լ���ڵ�ջ
		2) ��graph�ĵ�ǰ�ڵ����Լ״̬ͼ�ڵ�ջ
		3) ����һ�ڵ���Ϊ��ǰ�ڵ�
	����
		1) �����ǰ�ڵ��ǿɽ��ܽڵ㣬��
			a ������Լ���ڵ�ջ�е�һ���ڵ㣬���ýڵ���ӵ���Լ����root�ڵ��Ϊ����һ�����ӽڵ�
			b ��չ�Լ���ڵ�ջ����չ�Լ״̬ͼ�ڵ�ջ
			c graph��ʼ����ǰ�ڵ�
		2) ���������ǰ�ڵ����ս�㣬��
			a ���ݸù�Լʽ��token�ĸ���n��������Լ���ڵ�ջ�е�n���ڵ�
			b ��n���ڵ��л�ȡn��token
			c �½�һ��tokenParent������position���Էֱ�����Ϊ��һ��token�����һ��token��positionֵ
			d �½�һ����Լ���ڵ�nodeParent������װ��tokenParent
			e ��n���ڵ���ӵ�nodeParent��Ϊ�亢�ӽ��
			f ���ݸù�Լʽ��token�ĸ���n��������Լ״̬ͼ�ڵ�ջ�е�n���ڵ�
			g ����Լ״̬ͼ�ڵ�ջ��ջ���ڵ㣬��Ϊ��ǰ�ڵ�
			h graph������Լʽ�������ڻ���������һ�ڵ�
			i ������һ�ڵ���Ϊ��ǰ�ڵ�
			j ��nodeParent�ڵ���ӵ���Լ���ڵ�ջ��
			k ����tokenList�е�һ��token
		3) ����
			a ����token��ӵ�errTokenList��
x			b �����ǰtoken��tokenList�е����һ�����򷵻�0��������ɣ����д�����Ҫ�鿴������errorTokenList��
x			  ����
x				1> ����һ��token stack
x				2> ��graph�л�ȡ������һtoken(nextToken)
x				3> ��graph�����л���ΪarcList
x				4> ��arcList�л�ȡ��һtoken�����л��б�arcList
x				5> ֻҪarcList�еĻ�����һ��������Ӹ�token��token stack�У����ظ�4
x				6> ���tokenList��û����һtoken�ˣ��򽫵�ǰtoken֮�������token��ӵ������б���
x				7> ���arcList��ֻ��һ������˵���ҵ���Ψһ�Ĺ�Լʽ�������ܹ�Լʽǰ�����Ϣ�ж�ʧ����Ϊ�����token����
x					���ݹ�Լʽtoken�ĸ���m������m����Լ���ڵ㣬���к��漸����

	*/

	if(m_machine.getNodeCount()<=0)
		return -2;

	// 1. graph��ʼ����ǰ�ڵ�
	if(!m_machine.initCurrentNode())
		return -3;

	// ����ϴ�ִ�и÷������洢����������
	g_tokenList.destroyAll();
	g_tokenList.clear();
	g_statuteTreeNodeList.destroyAll();
	g_statuteTreeNodeList.clear();

	// ����ǰ�ڵ���ջ
	statuteStatusGraphNodeStack.push(m_machine.getCurrentNode());

#ifdef _DEBUG
	CString str;
	str.Format("token������%d", tokenList.size());
	log.writeDebug((LPTSTR)(LPCSTR)str);
#endif
	
	//////////////////////////////////////////////////////////////////////////
	// DEBUG
	int i=0;
	int sz=tokenList.size();
	for (i=0;i<tokenList.size();i++)
	{
#ifdef _DEBUG
		log.writeDebug("��ǰ�ڵ���Ϣ��");
		log.writeDebug(m_machine.getCurrentNode()->printStatuteItemListInfo());
#endif
		
 		// 3. ��ȡtokenList�ĵ�ǰtoken
 		MachineToken *token=tokenList.at(i);
 		if(!token)
 			continue;

#ifdef _DEBUG
		str.Format("��ǰtoken��%s", token->toString().c_str());
		log.writeDebug((LPTSTR)(LPCSTR)str);
#endif

// #if _DEBUG
// 	printf("%s", token->token.c_str());
// #endif

		CStatuteTreeNode *node=NULL;
		int ret=m_machine.goThrough(token);
		switch(ret)
		{
		case 1: // �ɹ�

#ifdef _DEBUG
			log.writeDebug("�ӵ�ǰ�ڵ��ߵ�ǰtoken�ɹ���");
#endif

// 			3. �����graph�ĵ�ǰ�ڵ��ܹ�����token�ߵ���һ�ڵ㣬��
// 			1) ��token����ɹ�Լ���ڵ㣬�����Լ���ڵ�ջ
// 			2) ��graph�ĵ�ǰ�ڵ����Լ״̬ͼ�ڵ�ջ
// 			3) ����һ�ڵ���Ϊ��ǰ�ڵ�
			node=new CStatuteTreeNode(token);
			g_statuteTreeNodeList.push_back(node);

			statuteTreeNodeStack.push(node);
			statuteStatusGraphNodeStack.push(m_machine.getCurrentNode());

// #if _DEBUG
// 			printf("\n", token->token.c_str());
// #endif
			
			break;
		case 0: // ����������Ϊtoken�ĳ���

#ifdef _DEBUG
			log.writeDebug("�ӵ�ǰ�ڵ㲻�����ߵ�ǰtoken�ĳ�����");
#endif

// #if _DEBUG
// 			printf("\b", token->token.c_str());
// #endif

// 			1) �����ǰ�ڵ��ǿɽ��ܽڵ㣬��
// 			a ������Լ���ڵ�ջ�е�һ���ڵ㣬���ýڵ���ӵ���Լ����root�ڵ��Ϊ����һ�����ӽڵ�
// 			b ��չ�Լ���ڵ�ջ����չ�Լ״̬ͼ�ڵ�ջ
// 			c graph��ʼ����ǰ�ڵ�
			if(m_machine.isCurrentNodeAccepted())
			{
#ifdef _DEBUG
				log.writeDebug("��ǰ����ǿɽ��ܽ�㣡");
#endif

				CStatuteTreeNode *nodeAccepted=statuteTreeNodeStack.popout();
				root->addChild(nodeAccepted);
				statuteStatusGraphNodeStack.clear();
				statuteTreeNodeStack.clear();
				m_machine.initCurrentNode();

// #if _DEBUG
// 	printf("Statute tree node stack size is %d", (int)statuteTreeNodeStack.size());
// #endif

				continue;
			}
// 			2) ���������ǰ�ڵ����ս�㣬��
// 			a ���ݸù�Լʽ��token�ĸ���n��������Լ���ڵ�ջ�е�n���ڵ�
// 			b ��n���ڵ��л�ȡn��token
// 			c �½�һ��statuteTreeNodeParent������position���Էֱ�����Ϊ��һ��token�����һ��token��positionֵ
// 			d �½�һ����Լ���ڵ�statuteTreeNodeParent������װ��tokenParent
// 			e ��n���ڵ���ӵ�statuteTreeNodeParent��Ϊ�亢�ӽ��
// 			f ���ݸù�Լʽ��token�ĸ���n��������Լ״̬ͼ�ڵ�ջ�е�n���ڵ�
// 			g ����Լ״̬ͼ�ڵ�ջ��ջ���ڵ㣬��Ϊ��ǰ�ڵ�
// 			h graph������Լʽ�������ڻ���������һ�ڵ�
// 			i ������һ�ڵ���Ϊ��ǰ�ڵ�
// 			j ��statuteTreeNodeParent�ڵ���ӵ���Լ���ڵ�ջ��
// 			k ����tokenList�е�һ��token
			else if(m_machine.isCurrentNodeFinal())
			{
#ifdef _DEBUG
				log.writeDebug("��ǰ������ս�㣡ִ�й�Լ������");
#endif
				
				int ret=statute(m_machine.getStatuteStatusGraph(), /*origStatuteList,*/ statuteStatusGraphNodeStack, statuteTreeNodeStack);
				if(ret!=0)
					return ret-10;

				// 			k ����tokenList�е�һ��token
				i--;
			}
			else
			{
#ifdef _DEBUG
				log.writeDebug("�����﷨����");
#endif

				errorTokenList.push_back(token);
				break;
			}
			break;
		default: // ����
// 			3) ���򣬽���token��ӵ�errTokenList��
#ifdef _DEBUG
			log.writeDebug("��������ǰ����������б�");
#endif
			
			errorTokenList.push_back(token);
			break;
		}

	}

	if(i==(int)tokenList.size())  // ˵��ɨ����Դ�ַ���
	{
#ifdef _DEBUG
		log.writeDebug("���н�㶼������ϣ�");
#endif
		
		while(!m_machine.isCurrentNodeAccepted() && m_machine.isCurrentNodeFinal())
		{
#ifdef _DEBUG
			log.writeDebug("��ǰ��㲻�ǿɽ��ܽڵ㣬�����ս�㣬��ִ�й�Լ������");
#endif
			
			int ret=statute(m_machine.getStatuteStatusGraph(), /*origStatuteList,*/ statuteStatusGraphNodeStack, statuteTreeNodeStack);
			if(ret!=0)
				return -4;

#ifdef _DEBUG
			log.writeDebug("��ǰ�ڵ���Ϣ��");
			log.writeDebug(m_machine.getCurrentNode()->printStatuteItemListInfo());
#endif
		}

		if(!m_machine.isCurrentNodeAccepted()/* && !m_graph->isCurrentNodeFinal()*/)
		{
#ifdef _DEBUG
			log.writeDebug("��ǰ����Բ��ǿɽ��ܽ�㣡����");
#endif
			
			return -5;
		}

		CStatuteTreeNode *nodeAccepted=statuteTreeNodeStack.popout();
		root->addChild(nodeAccepted);
		statuteStatusGraphNodeStack.clear();
		statuteTreeNodeStack.clear();
		m_machine.initCurrentNode();
			
// #if _DEBUG
// 		printf("At the end, statute tree node stack size is %d\n", (int)statuteTreeNodeStack.size());
// #endif
	}
	else
	{
#ifdef _DEBUG
		log.writeDebug("�����﷨���󣬷�����ֹ��");
#endif
		
		return -6;
	}
	
// #if _DEBUG
// 	printf("Global statute tree node list size is %d\n", (int)g_statuteTreeNodeList.size());
// 	printf("Global machine token list size is %d\n", (int)g_tokenList.size());
// #endif

#ifdef _DEBUG
	log.writeDebug("�����ɹ���");
	log.writeDebug("��Լ����Ϣ��");
	log.writeDebug(root->getTreeNodeInfo());
#endif

	return 0;
}

// ����ֵ��
//  0���ɹ�
//xx -1����Լʱ����ǰ�ڵ��м�¼�Ĺ�Լ�б����������б�Χ
// -2����Լʱ����ǰ�ڵ��м�¼�ĵ�ǰ�����Ĺ�ԼʽΪ��
// -3����Լʽ��token�����������򳬳��˵�ǰtokenջ��Ԫ�صĸ���
// -4����Լ��graph�߹�Լ��Ĺ�Լ����·�����ɹ���˵��graph�Ĺ��������⣨����Ӧ����һ���ɹ��ģ�
int CStatuteAnalyzer::statute(CStatuteStatusGraph *graph, /*CStatuteList &origStatuteList,*/ CPointerStack<CStatuteStatusGraphNode *> &statuteStatusGraphNodeStack, CPointerStack<CStatuteTreeNode *> &statuteTreeNodeStack)
{
#ifdef _DEBUG
	log.writeDebug("��Լ������ڣ�");
#endif
				
	// 			a ���ݸù�Լʽ��token�ĸ���n��������Լ���ڵ�ջ�е�n���ڵ�
	// 			b ��n���ڵ��л�ȡn��token
	// 			c �½�һ��statuteTreeNodeParent������position���Էֱ�����Ϊ��һ��token�����һ��token��positionֵ
	// 			d �½�һ����Լ���ڵ�statuteTreeNodeParent������װ��tokenParent
	// 			e ��n���ڵ���ӵ�statuteTreeNodeParent��Ϊ�亢�ӽ��
// 	int index=graph->getIndexInStatuteItemList();
// 	if(index<0 || index>=origStatuteList.size())
// 		return -1;
	
//	Statute *statute=origStatuteList.at(index);
	Statute *statute=graph->getStatuteOfFinal();
	if(!statute)
		return -2;
	
	int n=statute->tokenList.size();
	if(n<=0 || n>statuteTreeNodeStack.size())
		return -3;
	
	CStatuteTreeNode *statuteTreeNodeParent=new CStatuteTreeNode(&statuteTreeNodeStack, n);
	g_statuteTreeNodeList.push_back(statuteTreeNodeParent);
	
	MachineToken *tokenParent=new MachineToken();
#ifdef _DEBUG
	CString str;
	str.Format("��token��", tokenParent->toString().c_str());
	log.writeDebug((LPTSTR)(LPCSTR)str);
#endif
				
	g_tokenList.push_back(tokenParent);
	tokenParent->token=statute->statuteName;
	tokenParent->type="statute";
	
	statuteTreeNodeParent->setMachineToken(tokenParent);
	statuteTreeNodeParent->genTokenPosition();
	
	// 			f ���ݸù�Լʽ��token�ĸ���n��������Լ״̬ͼ�ڵ�ջ�е�n���ڵ�
	// 			g ����Լ״̬ͼ�ڵ�ջ��ջ���ڵ㣬��Ϊ��ǰ�ڵ�
	for(int p=0;p<n;p++)
	{
		statuteStatusGraphNodeStack.popout();
	}
	
	m_machine.setCurrentNode(statuteStatusGraphNodeStack.top());
#ifdef _DEBUG
	str.Format("��ǰ����ǣ�", m_machine.getCurrentNode()->printStatuteItemListInfo());
	log.writeDebug((LPTSTR)(LPCSTR)str);
#endif
	
	// 			h graph������Լʽ�������ڻ���������һ�ڵ�
	// 			i ������һ�ڵ���Ϊ��ǰ�ڵ�
	// 			j ��statuteTreeNodeParent�ڵ���ӵ���Լ���ڵ�ջ��
	int ret=m_machine.goThrough(tokenParent);
	if(ret!=1)
	{
#ifdef _DEBUG
		log.writeDebug("�ߵ�ǰ���ʧ�ܣ�");
#endif

		return -4;
	}
	
#ifdef _DEBUG
	log.writeDebug("�ߵ�ǰ���ɹ���");
#endif
	
	statuteTreeNodeStack.push(statuteTreeNodeParent);
	statuteStatusGraphNodeStack.push(m_machine.getCurrentNode());

#ifdef _DEBUG
	log.writeDebug("�����˳��Ĺ�Լ�������ڣ�");
#endif
	return 0;
}
