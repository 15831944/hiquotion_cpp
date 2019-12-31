#ifndef __AVPlayer_H__
#define __AVPlayer_H__
#include <iostream>
#include <Windows.h>
typedef __int64 ssize_t;
#include "vlc/vlc.h"
#include "vlc/libvlc_media.h"
#include <string>

#pragma comment(lib, "vlc/lib/libvlc.lib")
#pragma comment(lib, "vlc/lib/libvlccore.lib")

typedef void (* pfnCallback) (void *data);  // VLC�¼��Ļص�����ָ��
struct libvlc_instance_t;
struct libvlc_media_player_t;
struct libvlc_event_t;

#define PLAY_FAILURE_RETRY_TIMES 0

class CAVPlayer
{
    // VLC���¼�����
    friend void OnVLC_Event(const libvlc_event_t *event, void *data);

public:
    CAVPlayer(void);
    ~CAVPlayer(void);

	bool Play(const std::string& strPath, int type=0);  // ����·��ΪstrPath���ļ�
	bool PlayUrl(const std::string& url);  // ���ŵ�ַΪurl����Ƶ��
	void Play ();                           // ������Ƶ�ļ���ʼ
    void Pause();                           // ��ͣ
    void Stop ();                           // ֹͣ

    void Volume(int iVol);                  // ��������ΪiVol
    void VolumeIncrease();                  // ��������
    void VolumeReduce();                    // ������С 

    void SeekTo(int iPos);                  // ����ָ��λ��iPos
    void SeekForward();                     // ���
    void SeekBackward();                    // ����

    void SetHWND(HWND hwnd);                // ������Ƶ��ʾ�Ĵ��ھ��
    HWND GetHWND();                         // ��ȡ��Ƶ��ʾ�Ĵ��ھ��

	void SetFullScreen(bool full);			//����ȫ��

    bool    IsOpen();                       // �ļ��Ƿ��
    bool    IsPlaying();                    // �ļ��Ƿ����ڲ���
    bool    IsPlayingError();
    int     GetPos();                       // ��ȡ�ļ���ǰ���ŵ�λ��
    __int64 GetTotalTime();                 // ��ȡ��ʱ��
    __int64 GetTime();                      // ��ȡʱ��
    int     GetVolume();                    // ��ȡ����

	void SetWatermarkString(CString str, int fontSize = 32, int x = 0, int y = 0, COLORREF color = RGB(255, 255, 255), int transparent = 0, int timeout = 0);
	void SetWatermarkLogo(CString logoPath, int x = 0, int y = 0, int transparent = 0);

    void SetFnData(void* data) { m_fnData = data; };
    void* GetFnData() { return m_fnData; }
    void SetCallbackPlaying(pfnCallback pfn);         // �����ļ�ͷ��ȡ���ʱ�Ļص�����
    void SetCallbackPosChanged(pfnCallback pfn);      // �����ļ�λ�øı�ʱ�Ļص�����
    void SetCallbackEndReached(pfnCallback pfn);      // �����ļ��������ʱ�Ļص�����
    void SetCallbackMediaStateChanged(pfnCallback pfn) {
        m_pfnMediaStateChanged = pfn;
    };
    void SetCallbackMediaPlayerEncounteredError(pfnCallback pfn) {
        m_pfnMediaPlayerEncounteredError = pfn;
    };
    void SetCallbackVlmMediaInstanceStatusError(pfnCallback pfn) {
        m_pfnVlmMediaInstanceStatusError = pfn;
    };

    std::string getErrMsg() { return m_errMsg; }

private:
    libvlc_instance_t       *m_pVLC_Inst;   // VLCʵ��
	libvlc_media_t* m_vlc_media;
    libvlc_media_player_t   *m_pVLC_Player; // VLC������
    HWND                    m_hWnd;         // ��Ƶ��ʾ�Ĵ��ھ��
	int m_retryTimes;   // ����ʧ�ܵ����Դ���
    std::string m_errMsg;
    pfnCallback             m_pfnPlaying;   // �ļ���ȡ��ϣ�׼������
    pfnCallback             m_pfnPosChanged;// �ļ�λ�øı�ʱ�Ļص�����
	pfnCallback             m_pfnEndReached;// �ļ�������ϵĻص�����
	pfnCallback             m_pfnMediaStateChanged;
	pfnCallback             m_pfnMediaPlayerEncounteredError;
	pfnCallback             m_pfnVlmMediaInstanceStatusError;

    void* m_fnData;

    void Init();                            // ��ʼ��
    void Release();                         // �����ڴ�
};

#endif