// WaveOperation.h: interface for the CWaveOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEOPERATION_H__76DAED93_153A_4D2D_803E_4E26A4242AE3__INCLUDED_)
#define AFX_WAVEOPERATION_H__76DAED93_153A_4D2D_803E_4E26A4242AE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <c++\foundationlib\MultiThreadLib\ThreadBase.h>
#include <mmsystem.h>
#include <mmreg.h>
// #include <afxmt.h>
#include <c++\foundationlib\bufferlib\cycledbuffer.h>

#pragma  comment(lib, "winmm.lib")

#define Default_Channels 1
#define Default_BitPerSample 16
#define Default_SamplePerSecond 8000

#define Buffer_Count 8
#define Buffer_Length 1024
#define Max_Buffer_Length 10240  // 10KB��Ū1MB��ʹ�������������������ʹ�� m_waveFormat.nBlockAlign ��������������ڶ��β�������ʱ���ܻᵼ���������Ų�����

// #define Data_Length 4000

class CWavePlayer //: public CThreadBase
{
public:
	CWavePlayer();
	virtual ~CWavePlayer();

	// ��ʼ��Wave��ʽ
	// ������������λ����8λ��16λ�ȵȣ���������
	void initWaveFormat(int channels, int bitPerSample, int samplePerSecond);
	void initWaveFormat(WAVEFORMATEX waveFormat);

// 	// �Ƿ������Ƶ�豸
// 	BOOL hasWaveDev();

	// ����Ƶ����豸
	BOOL waveOutOpen();

	// ����
	BOOL CWavePlayer::wavePlay(char* buf, unsigned int nSize);

	// �Ƿ����ڲ���
	BOOL isPlaying() const { return m_isPlaying; }

	// �ر��豸
	void waveOutClose();

	// ���úͻ�ȡ��Ƶ����
	DWORD getWaveVolume();
	void setWaveVolume(DWORD volValue);

// 	void setCycledBuffer(CCycledBuffer * val) { m_cycledBuffer = val; }

// 	CEvent WavePlayDone;

	void setBufferSize(int size);
	BOOL addData(char *data, int length);

protected:
// 	UINT threadRun();

// 	void play();

	afx_msg void OnBlockDone(WPARAM wParam, LPARAM lParam);
	afx_msg void OnQuitThread(WPARAM wParam, LPARAM lParam);

// 	DECLARE_MESSAGE_MAP()

private:
	WAVEFORMATEX m_waveFormat;

	HWAVEOUT m_hWaveOut;
	MMRESULT m_result;

	WAVEHDR m_waveHeader[Buffer_Count];
	int m_currentWaveHeaderIndex;

	BOOL m_isOpen;

	BOOL m_isPlaying;

	CCycledBuffer m_cycledBuffer;
	char m_buffer[Buffer_Count][Buffer_Length];
	char m_bufferPlaying[Max_Buffer_Length];
};

#endif // !defined(AFX_WAVEOPERATION_H__76DAED93_153A_4D2D_803E_4E26A4242AE3__INCLUDED_)
