#include "StdAfx.h"
#include "TimeElapse.h"

CTimeElapse::CTimeElapse(void)
{
	m_status=0;
	m_start=0;
	m_end=0;
}

CTimeElapse::~CTimeElapse(void)
{
}

// ���status����0����ֱ�ӷ��أ�������Ϊ1
void CTimeElapse::start()
{
	if(m_status!=0)
		return;

	m_start=GetTickCount();
	m_status=1;
}

// ���status����1����ֱ�ӷ��أ�������Ϊ2
void CTimeElapse::end()
{
	if(m_status!=1)
		return;

	m_end=GetTickCount();
	m_status=2;
}

// ���status����2���򷵻�0��������Ϊ0
int CTimeElapse::getElapse()
{
	if(m_status!=2)
		return 0;

	int interval=m_end-m_start;
	m_start=0;
	m_end=0;
	m_status=0;

	return interval;
}
