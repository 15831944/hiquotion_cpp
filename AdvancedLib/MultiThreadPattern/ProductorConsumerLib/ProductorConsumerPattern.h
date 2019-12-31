// ProductorConsumerPattern.h: interface for the CProductorConsumerPattern class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCTORCONSUMERPATTERN_H__A34DC90B_A53D_4338_89BB_DF80D5EA00C1__INCLUDED_)
#define AFX_PRODUCTORCONSUMERPATTERN_H__A34DC90B_A53D_4338_89BB_DF80D5EA00C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\DataStructLib\PointerList.h>

#define DEFALT_CAPABILITY 128

template<class T>
class CProductorConsumerPattern  
{
public:
	CProductorConsumerPattern()
	{
		m_capacity=DEFALT_CAPABILITY;
		
		//�����ź���
		m_emptySemaphore = CreateSemaphore(NULL, DEFALT_CAPABILITY, DEFALT_CAPABILITY, NULL);//��ֵΪ����ش�С�����Ϊ����ش�С
		m_fullSemaphore = CreateSemaphore(NULL, 0, DEFALT_CAPABILITY, NULL);       //��ֵΪ0�����Ϊ����ش�С
		m_mutexSemaphore = CreateSemaphore(NULL,1,1,NULL);               //��ֵΪ1,���Ϊ1
	}

	CProductorConsumerPattern(int capacity)
	{
		//�����ź���
		if(capacity>0)
		{
			m_capacity=capacity;
			m_emptySemaphore = CreateSemaphore(NULL, capacity, capacity, NULL);//��ֵΪ����ش�С�����Ϊ����ش�С
			m_fullSemaphore = CreateSemaphore(NULL, 0, capacity, NULL);       //��ֵΪ0�����Ϊ����ش�С
		}
		else
		{
			m_capacity=DEFALT_CAPABILITY;
			
			m_emptySemaphore = CreateSemaphore(NULL, DEFALT_CAPABILITY, DEFALT_CAPABILITY, NULL);//��ֵΪ����ش�С�����Ϊ����ش�С
			m_fullSemaphore = CreateSemaphore(NULL, 0, DEFALT_CAPABILITY, NULL);       //��ֵΪ0�����Ϊ����ش�С
		}
		
		m_mutexSemaphore = CreateSemaphore(NULL,1,1,NULL);               //��ֵΪ1,���Ϊ1
	}

	virtual ~CProductorConsumerPattern()
	{
		CloseHandle(m_emptySemaphore);
		CloseHandle(m_fullSemaphore);
		CloseHandle(m_mutexSemaphore);
	}

	void produce(T product)
	{
		WaitForSingleObject(m_emptySemaphore, INFINITE);//�ȴ�ͬ���ź���empty
		
		WaitForSingleObject(m_mutexSemaphore, INFINITE);//�ȴ������ź���mutex
		m_products.push_back(product);
#ifdef _DEBUG
		printf("Produced a product.\n");
#endif
		ReleaseSemaphore(m_mutexSemaphore, 1, NULL);//�ͷŻ����ź���mutex
		
		ReleaseSemaphore(m_fullSemaphore, 1, NULL);//�ͷ�ͬ���ź���full
	}

	void comsume(T *product)
	{
		WaitForSingleObject(m_fullSemaphore, INFINITE);//�ȴ�ͬ���ź���full
		
		WaitForSingleObject(m_mutexSemaphore, INFINITE);//�ȴ������ź���mutex
		*product=m_products.front();
		m_products.erase(0);
#ifdef _DEBUG
		printf("Comsumed a product.\n");
#endif
		ReleaseSemaphore(m_mutexSemaphore, 1, NULL);//�ͷŻ����ź���mutex
		
		ReleaseSemaphore(m_emptySemaphore, 1, NULL);//�ͷ��ź���
	}

protected:
	//���ź���
	HANDLE m_emptySemaphore;
	//���ź���
	HANDLE m_fullSemaphore;
	//�����ź������������������߻��⣬�������������߻��⣬�������������߻���
	HANDLE m_mutexSemaphore;
	// ��Ʒ
	CPointerList<T> m_products;

	// �ֿ�����
	int m_capacity;
};

#endif // !defined(AFX_PRODUCTORCONSUMERPATTERN_H__A34DC90B_A53D_4338_89BB_DF80D5EA00C1__INCLUDED_)
