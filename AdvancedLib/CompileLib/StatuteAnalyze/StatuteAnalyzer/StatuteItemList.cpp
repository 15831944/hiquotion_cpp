// StatuteItemList.cpp: implementation of the CStatuteItemList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteItemList.h"
#include "../MemManager/MemManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteItemList::CStatuteItemList()
{

}

CStatuteItemList::CStatuteItemList(CStatuteItemList *lst)
{
	if(!lst)
		return;

	for(int i=0;i<lst->size();i++)
	{
		StatuteItem *statuteItem=lst->at(i);
		if(!statuteItem)
			continue;

		push_back(statuteItem);
	}
}

CStatuteItemList::~CStatuteItemList()
{

}

// ��鵱ǰ��Լ��Ŀ�б����Ƿ����ָ�����ƵĹ�Լ��Ŀ
BOOL CStatuteItemList::isContainedByStatuteName( string name )
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		Statute *statute=statuteItem->statute;
		if(!statute)
			continue;
		
		if(statute->statuteName==name)
			return TRUE;
	}
	
	return FALSE;
}

// ����Ƿ����������λ�õ���Ŀ
BOOL CStatuteItemList::isContainItemInFinalPosition()
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->isFinalItemPosition())
			return TRUE;
	}
	
	return FALSE;
}

void CStatuteItemList::getStatuteItemListInFinalPosition(CStatuteItemList *retList)
{
	if(!retList)
		return;

	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->isFinalItemPosition())
			retList->push_back(statuteItem);
	}
}

// ���ݹ�Լ���ƻ�ȡ��Լ��Ŀ�б�
void CStatuteItemList::getStatuteItemListbyName( string name, CStatuteItemList *retList )
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;

		Statute *statute=statuteItem->statute;
		if(!statute)
			continue;
		
		if(statute->statuteName==name)
		{
//			if(!((CValueList<StatuteItem *> *)retList)->contain(statuteItem))
			if(!retList->contain(statuteItem))
				retList->push_back(statuteItem);
		}
	}
}

// ���ݵ�һ����Լʽ�Ĺ�Լ��������ȡ��Լ��Ŀ�б�
// ����ֵ��
// 0���ɹ�
// -1����Լʽ��Ŀ�б��еĵ�һ����ԼʽΪ��ָ��
// -2����һ����Լʽ��Ŀ�еĹ�Լʽָ��Ϊ��
// -3����һ����Լʽ�Ĺ�Լ����Ϊ��
int CStatuteItemList::getStatuteItemListby1stStatuteName( CStatuteItemList *retList )
{
	StatuteItem *statuteItem=at(0);
	if(!statuteItem)
		return -1;
	
	Statute *statute=statuteItem->statute;
	if(!statute)
		return -2;
	
	string name=statute->statuteName;
	if(name=="")
		return -3;
	
	getStatuteItemListbyName(name, retList);
	if(retList->size()<=0)
		return -4;  // ���ٰ���һ������������жϿ���ûʲô��

	return 0;
}

// ��ȡ��Ŀλ�ò������Ĺ�Լʽ��Ŀ�б�
void CStatuteItemList::getStatuteItemListNotinFinalPosition(CStatuteItemList *retList)
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;

		if(!statuteItem->isFinalItemPosition())
			retList->push_back(statuteItem);
	}
}

// ��ȡtoken����Ϊname�ĵ�ǰ��Լ��Ŀ�б�
void CStatuteItemList::getCurrentStatuteItemListbyTokenName(string name, CStatuteItemList *retList)
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->isFinalItemPosition())
			continue;
		
		Statute *statute=statuteItem->statute;
		if(!statute)
			continue;
		
		MachineToken *token=statute->tokenList.at(statuteItem->itemPosition);
		if(!token)
			continue;
		
		if(token->token==name)
			retList->push_back(statuteItem);
	}
}

// ��ȡ��ǰ�б������й�Լʽ����һ����Լ��Ŀ���б�
void CStatuteItemList::genNextStatuteItemList(CStatuteItemList *retList)
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;

		StatuteItem *item=statuteItem->genNextStatuteItem();
		if(item)
		{
			CMemManager::addStatuteItem(item);
			retList->push_back(item);
		}
	}
}

// �հ����㣬�����������б��ڳ�ʼ��Լ��Ŀ�б��в��ң�����ǰ��Լ��Ŀ�Ƿ��ս���Ĺ�Լ��Ŀ��ӵ������б���
void CStatuteItemList::closure( CStatuteItemList &origStatuteItemList )
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->isFinalItemPosition())
			continue;
		
		Statute *statute=statuteItem->statute;
		if(!statute)
			continue;
		
		MachineToken *token=statute->tokenList.at(statuteItem->itemPosition);
		if(!token)
			continue;

		if(token->token=="")
			continue;
		
		if(origStatuteItemList.isContainedByStatuteName(token->token))
		{
			CStatuteItemList lst;
			origStatuteItemList.getStatuteItemListbyName(token->token, &lst);

			for(int i=0;i<lst.size();i++)
			{
				StatuteItem *item=lst.at(i);
				if(!item)
					continue;

				Statute *statute=item->statute;
				if(!statute)
					continue;

				if(!containbyKey(item->printStatute()))
					push_back(item);
			}
		}
	}
}

std::string CStatuteItemList::genStatuteKey()
{
	string key="{";
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;

		key+=statuteItem->printStatute();
		if(i!=size()-1)
			key+="}|{";
		else
			key+="}";
	}

	return key;
}

BOOL CStatuteItemList::containbyKey(string key)
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->printStatute()==key)
			return TRUE;
	}

	return FALSE;
}


