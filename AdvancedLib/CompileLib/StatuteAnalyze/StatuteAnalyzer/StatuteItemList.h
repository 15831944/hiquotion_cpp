// StatuteItemList.h: interface for the CStatuteItemList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUTEITEMLIST_H__CDCFBBB6_6E4F_453B_9E04_97B44CE83740__INCLUDED_)
#define AFX_STATUTEITEMLIST_H__CDCFBBB6_6E4F_453B_9E04_97B44CE83740__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\PointerList.h>
#include "Statute.h"

class CStatuteItemList : public CPointerList<StatuteItem *>  
{
public:
	CStatuteItemList();
	CStatuteItemList(CStatuteItemList *lst);
	virtual ~CStatuteItemList();

	// ��鵱ǰ��Լ��Ŀ�б����Ƿ����ָ�����ƵĹ�Լ��Ŀ
	BOOL isContainedByStatuteName(string name);
	// ����Ƿ����������λ�õ���Ŀ
	BOOL isContainItemInFinalPosition();
	// ��ȡ������λ�õ���Ŀ����
	void getStatuteItemListInFinalPosition(CStatuteItemList *retList);
	// ���ݹ�Լ���ƻ�ȡ��Լ��Ŀ�б�
	void getStatuteItemListbyName(string name, CStatuteItemList *retList);
	// ���ݵ�һ����Լʽ�Ĺ�Լ��������ȡ��Լ��Ŀ�б�
	int getStatuteItemListby1stStatuteName(CStatuteItemList *retList);
	// ��ȡ��Ŀλ�ò������Ĺ�Լʽ��Ŀ�б�
	void getStatuteItemListNotinFinalPosition(CStatuteItemList *retList);
	// ��ȡtoken����Ϊname�ĵ�ǰ��Լ��Ŀ�б�
	void getCurrentStatuteItemListbyTokenName(string name, CStatuteItemList *retList);
	// ��ȡ��ǰ�б������й�Լʽ����һ����Լ��Ŀ���б�
	void genNextStatuteItemList(CStatuteItemList *retList);
	// �հ����㣬�����������б��ڳ�ʼ��Լ��Ŀ�б��в��ң�����ǰ��Լ��Ŀ�Ƿ��ս���Ĺ�Լ��Ŀ��ӵ������б���
	void closure(CStatuteItemList &origStatuteItemList);

	// ���ɶ����Լʽ��ĿΪһ���ַ��������ǹ�Լʽ�д�С��������ַ�������ϣ�����Ψһ��Ǹù�Լʽ�б����ڽڵ�
	string genStatuteKey();
	// �жϸù�Լʽ�б��Ƿ����ָ����Ψһ���
	BOOL containbyKey(string key);
};

#endif // !defined(AFX_STATUTEITEMLIST_H__CDCFBBB6_6E4F_453B_9E04_97B44CE83740__INCLUDED_)
