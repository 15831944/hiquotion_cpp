// ThradSafedQue.h: interface for the CThradSafedQue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THRADSAFEDQUE_H__105CC161_2D01_4345_94A4_A4CA44A1FBB3__INCLUDED_)
#define AFX_THRADSAFEDQUE_H__105CC161_2D01_4345_94A4_A4CA44A1FBB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <queue>
#include <afxmt.h>

template <class T>
class CThreadSafedQue : public std::queue<T>
{
public:
	CThreadSafedQue()
	{
		m_maxCount=0;
	};

	CThreadSafedQue(int maxCount)  // ��������������Ԫ�ظ���maxCount��0Ϊ������
	{
		m_maxCount=maxCount;
	};

	virtual ~CThreadSafedQue(){};

	void put(T t);   // ������������Ԫ�ظ���maxCount����maxCount��Ϊ0����ô�ﵽmaxCountʱ����ȴ���ֱ�����в���
	void get(T *t);  // �������Ϊ�գ���ȴ�ֱ�����в���Ϊֹ����֤���ص�t��ΪNULL������������֪���Ƿ��ȴ���Ҳ����Ԥ�Ƶȴ�ʱ��
	BOOL get_NoWaiting(T *t/*, int waitTimeMS=0*/);  // �������Ϊ�գ���ȴ�waitTimeMS����������ڼ�ȴ����ˣ��򷵻�TRUE��t�����򷵻�FALSE��NULL�����waitTimeMSΪ0���򲻵ȴ�����ȡ���ͷ���TRUE��t�����򷵻�FALSE��NULL

	int getMaxCount() const { return m_maxCount; }
// 	void setMaxCount(int val) { m_maxCount = val; }

private:
	void waitUntilNotFull();  // �ȴ���ֱ�����в���
	void notifyItsNotFull();  // ֪ͨ�����Ѿ�������
	void waitUntilNotEmpty(); // �ȴ���ֱ�����в���
	void notifyItsNotEmpty(); // ֪ͨ�����Ѿ�������

private:
	CMutex m_mutex;
	CEvent m_event4NotFull;
	CEvent m_event4NotEmpty;

	int m_maxCount;
};

template <class T>
void CThreadSafedQue<T>::put( T t )
{
	while(m_maxCount>0 && size()>=m_maxCount)
		waitUntilNotFull();

	m_mutex.Lock();
	push(t);
	m_mutex.Unlock();
	notifyItsNotEmpty();
}

template <class T>
void CThreadSafedQue<T>::get( T *t )
{
	if(size()<=0)
		waitUntilNotEmpty();

	m_mutex.Lock();
	*t=front();
	pop();
	m_mutex.Unlock();
	notifyItsNotFull();
}

template <class T>
BOOL CThreadSafedQue<T>::get_NoWaiting( T *t/*, int waitTimeMS*/ )
{
	if(size<=0)
		return FALSE;

	m_mutex.Lock();
	*t=front();
	pop();
	m_mutex.Unlock();
	notifyItsNotFull();
}

template <class T>
void CThreadSafedQue<T>::waitUntilNotFull()
{
	m_event4NotFull.Lock();
}

template <class T>
void CThreadSafedQue<T>::notifyItsNotFull()
{
	m_event4NotFull.PulseEvent();	
}

template <class T>
void CThreadSafedQue<T>::waitUntilNotEmpty()
{
	m_event4NotEmpty.Lock();
}

template <class T>
void CThreadSafedQue<T>::notifyItsNotEmpty()
{
	m_event4NotEmpty.PulseEvent();	
}

#endif // !defined(AFX_THRADSAFEDQUE_H__105CC161_2D01_4345_94A4_A4CA44A1FBB3__INCLUDED_)
