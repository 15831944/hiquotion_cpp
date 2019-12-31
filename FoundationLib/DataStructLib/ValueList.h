#pragma once

#include <vector>

template <class T>
class CValueList : public std::vector<T>
{
public:
	CValueList(void)
	{

	}

	~CValueList(void)
	{
		clear();
	}

	T removeByIndex(int index)
	{
		if(index<0 || index>=size())
			return NULL;

		if(index==0)
		{
			T t=at(0);
			erase(begin());
			return t;
		}

		CValueList<T>::iterator it=begin();
		for(int i=0;i<index;i++)
			it++;

		T t=*it;
		erase(it);
		return t;
	}

	// ����Ĳ���������������û��Ҫ�ٷ�����
	void remove(T t)
	{
		if(size()<=0)
			return;

		std::vector<T>::iterator it;
		for(it=begin();it!=end();it++)
		{
			if (*it==t)
			{
				erase(it);
				break;
			}
		}
	}

	BOOL contain(T t)
	{
		if(getIndexOf(t)>=0)
			return TRUE;

		return FALSE;
	}

	int getIndexOf(T t)
	{
		if(size()<=0)
			return -1;

		int i=0;
		std::vector<T>::iterator it;
		for(it=begin();it!=end();it++)
		{
			if (*it==t)
				return i;

			i++;
		}

		return -1;
	}

	// ����src1���е�src2��û�е�Ԫ�أ���ӵ�diff1��
	static void findDifferent(CValueList<T> &src1, CValueList<T> &src2, CValueList<T> &diff1)
	{
		if(src1.size()==0 || src2.size()==0)
			return;
		
		for(int i=0;i<src1.size();i++)
		{
			if(!src2.contain(src1.at(i)))
				diff1.push_back(src1.at(i));
		}
	}

	// ���������б��еĲ�ͬ��
	// �൱�ڰ�src1��src2����ͬ��Ԫ��ȥ����
	// src1ʣ��Ԫ�ص��б����diff1��src2ʣ��Ԫ�ص��б����diff2
	static void findDifferent(CValueList<T> &src1, CValueList<T> &src2, CValueList<T> &diff1, CValueList<T> &diff2)
	{
		if(src1.size()==0 && src2.size()==0)
			return;

		findDifferent(src1, src2, diff1);
		findDifferent(src2, src1, diff2);
	}
};
