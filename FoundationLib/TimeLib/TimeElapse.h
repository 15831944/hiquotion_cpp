#pragma once

class CTimeElapse
{
public:
	CTimeElapse(void);
	~CTimeElapse(void);

	void start();     // ���status����0����ֱ�ӷ��أ�������Ϊ1
	void end();       // ���status����1����ֱ�ӷ��أ�������Ϊ2
	int getElapse();  // ���status����2���򷵻�0��������Ϊ0

private:
	DWORD m_start;
	DWORD m_end;

	int m_status; // 0����ʼ����1��������start��2��������end��ֻ����2��ʱ�򣬲ſ���ȡʱ���
};
