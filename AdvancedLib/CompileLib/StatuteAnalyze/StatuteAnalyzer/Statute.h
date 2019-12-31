#include "..\..\Lex\Lexer\Lexer.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ����ṹ���ǹ�Լʽ�ڴʷ�������õ���
// ������Լ���ƺʹ����б�
typedef struct Statute
{
	std::string statuteName;                  // ��Լ�������
	CPointerList<MachineToken *> tokenList;  // �����б�
} Statute;  // ��Լ

// ��Լʽ��Ŀ�����Ǵ�С������֣�
typedef struct StatuteItem
{
	StatuteItem()
	{
		statute=NULL;
		indexInStatuteList=-1;
		itemPosition=-1;
	}

	StatuteItem(Statute *s, int indxInStatuteList)
	{
		statute=s;
		indexInStatuteList=indxInStatuteList;
		itemPosition=0;
	}
	
	StatuteItem(Statute *s, int indxInStatuteList, int itemPos)
	{
		statute=s;
		indexInStatuteList=indxInStatuteList;
		itemPosition=itemPos;
	}

	StatuteItem(StatuteItem *item)
	{
		statute=item->statute;
		indexInStatuteList=item->indexInStatuteList;
		itemPosition=item->itemPosition;
	}

	StatuteItem *genNextStatuteItem()
	{
		checkPosition();

		if(itemPosition==statute->tokenList.size())
			return NULL;

		else
			return new StatuteItem(statute, indexInStatuteList, itemPosition+1);
	}
	
	// ��ӡ��Լʽ
	string printStatute()
	{
		return printStatute(itemPosition);
	}

	// ��ӡ��Լʽ
	string printStatute(int itemPosition)
	{
		int i=0;
		string ret;
		ret=statute->statuteName;
		ret+="=>";
		
		if(itemPosition==0)
			ret+=".";
		else
		{
			for(i=0;i<itemPosition;i++)
			{
				MachineToken *token=statute->tokenList.at(i);
				if(!token)
					continue;
				
				ret+=token->token;
			}
			
			ret+=".";
		}
		
		for(i=itemPosition;i<statute->tokenList.size();i++)
		{
			MachineToken *token=statute->tokenList.at(i);
			if(!token)
				continue;
			
			ret+=token->token;
		}
		
		return ret;
	}

	void checkPosition()
	{
		if(itemPosition>statute->tokenList.size())
			itemPosition=statute->tokenList.size();
		
		if(itemPosition<0)
			itemPosition=0;
	}

	BOOL isFinalItemPosition()
	{
		checkPosition();

		if(itemPosition==statute->tokenList.size())
			return TRUE;

		return FALSE;
	}
	
	Statute *statute;
	int indexInStatuteList;
	int itemPosition; // С������λ�ã�0��ʾ��ǰ��
} StatuteItem;  // ��Լʽ��Ŀ

