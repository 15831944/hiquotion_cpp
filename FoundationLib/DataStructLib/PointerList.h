#pragma once

// #include <vector>
#include "ValueList.h"

template <class T>
class CPointerList : public CValueList<T> // std::vector<T>
{
public:
	CPointerList(void)
	{
		m_isSelfDestroy=FALSE;
	}

	~CPointerList(void)
	{
		if(m_isSelfDestroy)
	 		destroyAll();
		clear();
	}

	void destroyAll()
	{
		for(int i=0;i<(int)size();i++)
		{
			if(at(i))
				delete at(i);
		}
		clear();
	}

	void destroyByIndex(int index)
	{
		if(size()<=0)
			return;

		if(index<0 || index>=size())
			return;

		T t=removeByIndex(index);
		if(t)
			delete t;
	}

	void destroy(T t)
	{
		if(remove(t))
			delete t;
	}

	T remove(T t)
	{
		if(size()<=0)
			return NULL;

		std::vector<T>::iterator it;
		for(it=begin();it!=end();it++)
		{
			if (*it==t)
			{
				erase(it);
				return t;    // ����д�� *it����Ϊ *it������� T �����Ѿ����Ƴ��ˣ�*it����Ұָ�룬����ԭ���� *it �ˡ�
				break;
			}
		}

		return NULL;
	}

//	BOOL contain(T t)
//	int getIndexOf(T t)

	// ����src1���е�src2��û�е�Ԫ�أ���ӵ�diff1��
	static void findDifferent(CPointerList<T> *src1, CPointerList<T> *src2, CPointerList<T> *diff1)
	{
		if(src1->size()==0 || src2->size()==0)
			return;
		
		for(int i=0;i<src1->size();i++)
		{
			if(!src2->contain(src1->at(i)))
				diff1->push_back(src1->at(i));
		}
	}

	// ���������б��еĲ�ͬ��
	// �൱�ڰ�src1��src2����ͬ��Ԫ��ȥ����
	// src1ʣ��Ԫ�ص��б����diff1��src2ʣ��Ԫ�ص��б����diff2
	static void findDifferent(CPointerList<T> *src1, CPointerList<T> *src2, CPointerList<T> *diff1, CPointerList<T> *diff2)
	{
		if(src1->size()==0 && src2->size()==0)
			return;

		findDifferent(src1, src2, diff1);
		findDifferent(src2, src1, diff2);
	}

	BOOL isSelfDestroy() const { return m_isSelfDestroy; }
	void setSelfDestroy(BOOL val) { m_isSelfDestroy = val; }

protected:
	BOOL m_isSelfDestroy;
};
