#pragma once

void CALLBACK OnTimerCallback(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime);

/*

  C++ Timer �÷�


  ����һ��
  ����SetTimerʱָ�����ھ��hWnd��nIDEvent��ָ����ʱ��ID����lpTimerFunc��NULL�Ӷ���ʹ��TimerProc��
  �ڴ��ڹ����д���WM_TIMER��Ϣ������KillTimerʱ��ʹ��SetTimer��ָ����hWnd��id��


  ��������
  ����SetTimerʱָ�����ھ��hWnd��nIDEvent��ָ����ʱ��ID��lpTimerFunc������ΪNULL��ָ��ΪTimerProc������ָ�롣
  ���ַ���ʹ��TimerProc����(���ֿ��Զ�)����WM_TIMER��Ϣ


  ��������
  ����SetTimerʱ��ָ�����ھ��(ΪNULL)��iTimerID������Ȼ�����ԣ�lpTimerFunc��ΪNULL��ָ��ΪTimerProc��ָ�롣
  ��������SetTimer����������˵�ģ���ʱSetTimer�ķ���ֵ�����½����ļ�ʱ����ID���轫���ID�����Թ�KillTimer���ټ�ʱ��ʱ���á�
  ��Ȼ��KillTimer��hWnd����Ҳ��ΪNULL�����ַ���ͬ����TimerProc����WM_TIMER��Ϣ��
  

*/

class CTimerBase
{
public:
	CTimerBase(void);
	CTimerBase(int interval);
	~CTimerBase(void);

	BOOL start();
// 	// Ϊ��ʹ�ûص�����������
// 	BOOL start(TIMERPROC TimerProc);

	void stop();

	void TimerCallback(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime);

	int getInterval();
	void setInterval(int interval);  // ����ʱ��������λ�����룩

	HWND getHwnd() const { return m_hwnd; }
	void setHwnd(HWND val) { m_hwnd = val; }

	UINT_PTR getTimerId();

protected:
	virtual void OnTimer(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime){};
	BOOL createTimer(int interval);
// 	BOOL createTimer(int interval, TIMERPROC TimerProc);
	void destroyTimer();

protected:
	HWND m_hwnd;
	UINT_PTR m_timerId;
	int m_interval;   // ʱ�������Ժ���Ϊ��λ
};


static CTimerBase *timerBase=NULL;

