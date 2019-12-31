#include "stdafx.h"
#include "AVPlayer.h"
#include <cmath>
#include <C++/FoundationLib/StringExtLib/StringConverter.h>

CAVPlayer::CAVPlayer(void) :
m_pVLC_Inst(NULL),
m_vlc_media(NULL),
m_pVLC_Player(NULL),
m_hWnd(NULL),
m_pfnPlaying(NULL),
m_pfnPosChanged(NULL),
m_pfnEndReached(NULL),
m_retryTimes(PLAY_FAILURE_RETRY_TIMES)
{
}

CAVPlayer::~CAVPlayer(void)
{
    Release();
}

void CAVPlayer::Init()
{
    m_errMsg = "";

    Release();

    if (! m_pVLC_Inst)
    {
		const char* const vlc_args[] = {
	   "-I", "dummy", /* Don't use any interface */
// 	   "--sub-filter=logo{file=D:\\������\\G\\ͼƬ\\2014-09-15_12-23-56_741.jpg}",
	    //"--sub-filter=logo{file=c:\\mediaport.png}:rss{urls=http://www.bbc.co.uk/persian/index.xml,length=120,size=23,title=0,speed=300000,x=-10,y=-30,position=8}",
        //"--sub-filter=logo{file=dummy}",
	   //"--no-rss-images",
//        "--rotation-angle=30",  // ʵ������ʧ�ܣ���ʹд��90Ҳ����
//       "--video-filter=transform",  // ��ʱ����ת90�ȣ���ʹ��
//       "--transform-type=",   // ֵ������ 90, 180, 270, hfilp, vfilp

        // ������ marq �Ͳ�Ҫ���� logo��
        // ������ logo marq �Զ�����ʾ��һ����û�ˣ�
	   "--sub-filter=marq",    // �����������������

// 	   "--sub-filter=logo",// ������ʾ logo

        "--verbose", "0",
	   //"--verbose-objects=+filter",
// 	   "-vvv",
	   //"--sout=#duplicate{dst=std{access=mmsh,mux=asfh,dst=0.0.0.0:8080},dst=display}",
	   //"--ignore-config",
	   //"--loop",
	   //"--repeat",
	   //"-R",
	   "--no-video-title-show",
	   //"--network-caching 20000",
	   //":mmsh-caching=20000",
		};

		int vlc_argc = sizeof(vlc_args) / sizeof(*vlc_args);
		m_pVLC_Inst = libvlc_new(vlc_argc, vlc_args);
//		m_pVLC_Inst = libvlc_new(0, NULL);
	}
}

void CAVPlayer::Release()
{
    Stop();

    if (m_vlc_media)
    {
        libvlc_media_release(m_vlc_media);
        m_vlc_media = NULL;
    }

    if (m_pVLC_Inst)
    {
        libvlc_release (m_pVLC_Inst);
        m_pVLC_Inst   = NULL;
    }
}

bool CAVPlayer::Play(const std::string &strPath, int type)
{
	m_errMsg = "";
    int retryTimes = m_retryTimes;

    Init();

    if(strPath.empty() || ! m_pVLC_Inst)
    {
		m_errMsg = "�������Ϊ�գ��򲥷���ʵ������ʧ�ܣ�";
        return false;
    }

    Stop();

    bool bRet = false;

	switch (type)
	{
	case 0:
		m_vlc_media = libvlc_media_new_path(m_pVLC_Inst, strPath.c_str());
		break;
	case 1:
		m_vlc_media = libvlc_media_new_location(m_pVLC_Inst, strPath.c_str());
// 		m = libvlc_media_new_location(m_pVLC_Inst, "screen://");  // ��ʾ��Ļ���ݾ�ȻҲ����
		break;
	default:
		m_vlc_media = libvlc_media_new_path(m_pVLC_Inst, strPath.c_str());
		break;
	}

    if (!m_vlc_media)
    {
		m_errMsg = "ý���ļ�����ʧ�ܣ�";
		return false;
    }

	// ����˵��ô���õ�ʱ�򣬱���ǰ����ð�ţ������Ƕ̻��߻�˫�̻���
	libvlc_media_add_option(m_vlc_media, ":rtsp-tcp");
// 	libvlc_media_add_option(m_vlc_media, ":ipv4-timeout=3000");  // ��������ӳ�ʱ
//  libvlc_media_add_option(m_vlc_media, ":rtp-timeout=5000");  // ����� rtp ��Ƶ����ʱ
// 	libvlc_media_add_option(m_vlc_media, ":rtsp-session-timeout=10000");   // ���� rtsp Э���ı������ó�ʱ
	libvlc_media_add_option(m_vlc_media, ":network-caching=1000");
	libvlc_media_add_option(m_vlc_media, ":rtsp-frame-buffer-size=0.5");
// 	libvlc_media_add_option(m_vlc_media, ":global-key-toggle-fullscreen={f}");

	//libvlc_media_add_option(m_vlc_media, "--avcodec-threads=124");
	//libvlc_media_add_option(m_vlc_media, "--ignore-config");
// 	libvlc_media_add_option(m_vlc_media, "--network-caching=1500000");
// 	libvlc_media_add_option(m_vlc_media, "--rtsp-frame-buffer-size=2000000");
// 	libvlc_media_add_option(m_vlc_media, "--rtsp-tcp");
	//libvlc_media_add_option(m_vlc_media, "--advanced");
// 	libvlc_media_add_option(m_vlc_media, "--global-key-toggle-fullscreen=f");
// 	//libvlc_media_add_option(m_vlc_media, "--key-toggle-fullscreen=f");
// 	libvlc_media_add_option(m_vlc_media, "--global-key-leave-fullscreen={ESC}");
// 	//libvlc_media_add_option(m_vlc_media, "--key-leave-fullscreen={ESC}");
// 	libvlc_media_add_option(m_vlc_media, "--global-key-play-pause={SPACE}");
// 	//libvlc_media_add_option(m_vlc_media, "--key-play-pause={SPACE}");

	if (m_pVLC_Player = libvlc_media_player_new_from_media(m_vlc_media))
    {
        /*
			enum libvlc_video_marquee_option_t
			Marq options definition.

			Enumerator
			libvlc_marquee_Enable   0
			libvlc_marquee_Text     1
			libvlc_marquee_Color    2    string argument
			libvlc_marquee_Opacity  3
			libvlc_marquee_Position 4
			libvlc_marquee_Refresh  5
			libvlc_marquee_Size     6
			libvlc_marquee_Timeout  7
			libvlc_marquee_X        8
			libvlc_marquee_Y        9
        */

// 		SetWatermarkString(L"����fdsf");  // ���� ����ˮӡ ��ʹ������
// 		SetWatermarkLogo(L"D:\\01.png");  // ���� logo ����ʹ

		libvlc_media_player_set_hwnd(m_pVLC_Player, m_hWnd);
        int ret=libvlc_media_player_play(m_pVLC_Player);
        while (ret != 0)
        {
            if (retryTimes == 0)
            {
				m_errMsg = libvlc_errmsg();
                return false;
            }

            retryTimes--;
            ret = libvlc_media_player_play(m_pVLC_Player);
        }

        // �¼�����
        libvlc_event_manager_t *vlc_evt_man = libvlc_media_player_event_manager(m_pVLC_Player);
        libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerPlaying, ::OnVLC_Event, this);
        libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerPositionChanged, ::OnVLC_Event, this);
		libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerEndReached, ::OnVLC_Event, this);
		libvlc_event_attach(vlc_evt_man, libvlc_MediaStateChanged, ::OnVLC_Event, this);
		libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerEncounteredError, ::OnVLC_Event, this);
		libvlc_event_attach(vlc_evt_man, libvlc_VlmMediaInstanceStatusError, ::OnVLC_Event, this);
        bRet = true;
    }

//     libvlc_media_release(m_vlc_media);

    return bRet;
}

bool CAVPlayer::PlayUrl(const std::string& url)  // ���ŵ�ַΪurl����Ƶ��
{
	return Play(url, 1);
}


void CAVPlayer::Stop()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_stop (m_pVLC_Player);      /* Stop playing */    
        libvlc_media_player_release (m_pVLC_Player);   /* Free the media_player */
        m_pVLC_Player = NULL;
    }
}

void CAVPlayer::Play()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_play(m_pVLC_Player);
    }
}

void CAVPlayer::Pause()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_pause(m_pVLC_Player);
    }
}

void CAVPlayer::Volume(int iVol)
{
    if (iVol < 0)
    {
        return;
    }

    if (m_pVLC_Player)
    {
        libvlc_audio_set_volume(m_pVLC_Player,int(iVol * 1.3)); // ����ŵ�100���о���Ѹ�׵�100����30������������1.3������
    }
}

void CAVPlayer::VolumeIncrease()
{
    if (m_pVLC_Player)
    {
        int iVol = libvlc_audio_get_volume(m_pVLC_Player);
        Volume((int)ceil(iVol * 1.1));
    }
}

void CAVPlayer::VolumeReduce()
{
    if (m_pVLC_Player)
    {
        int iVol = libvlc_audio_get_volume(m_pVLC_Player);
        Volume((int)floor(iVol * 0.9));
    }
}

int CAVPlayer::GetPos()
{   
    if (m_pVLC_Player)
    {
        return (int)(1000 * libvlc_media_player_get_position(m_pVLC_Player));
    }

    return 0;
}

void CAVPlayer::SeekTo(int iPos)
{
    if (iPos < 0 || iPos > 1000)
    {
        return;
    }

    if (m_pVLC_Player)
    {
        libvlc_media_player_set_position(m_pVLC_Player, iPos/(float)1000.0);
    }
}

void CAVPlayer::SeekForward()
{
    //int iPos = GetPos();
    //SeekTo((int)ceil(iPos * 1.1));

    // һ�ο���5��
    if (m_pVLC_Player)
    {
        libvlc_time_t i_time = libvlc_media_player_get_time(m_pVLC_Player) + 5000;

        if (i_time > GetTotalTime())
        {
            i_time = GetTotalTime();
        }

        libvlc_media_player_set_time(m_pVLC_Player, i_time);
    }
}

void CAVPlayer::SeekBackward()
{
    //int iPos = GetPos();
    //SeekTo((int)floor(iPos * 0.9));

    if (m_pVLC_Player)
    {
        libvlc_time_t i_time = libvlc_media_player_get_time(m_pVLC_Player) - 5000;

        if (i_time < 0)
        {
            i_time = 0;
        }

        libvlc_media_player_set_time(m_pVLC_Player, i_time);
    }
}

void CAVPlayer::SetHWND( HWND hwnd )
{
    if (::IsWindow(hwnd))
    {
        m_hWnd = hwnd;
    }
}

HWND CAVPlayer::GetHWND()
{
    return m_hWnd;
}


void CAVPlayer::SetFullScreen(bool full)
{
	libvlc_set_fullscreen(m_pVLC_Player, full);
	int iRet = libvlc_get_fullscreen(m_pVLC_Player);
}

bool CAVPlayer::IsOpen()
{
    return NULL != m_pVLC_Player;
}

bool CAVPlayer::IsPlaying()
{
    if (m_pVLC_Player)
    {
		return (1 == libvlc_media_player_is_playing(m_pVLC_Player));
	}

    return false;
}

bool CAVPlayer::IsPlayingError()
{
    libvlc_state_t status = libvlc_media_get_state(m_vlc_media);
    if (status == libvlc_Error)
        return true;

    return false;
}

__int64 CAVPlayer::GetTotalTime()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_get_length(m_pVLC_Player);
    }

    return 0;
}

__int64 CAVPlayer::GetTime()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_get_time(m_pVLC_Player);
    }

    return 0;
}

int CAVPlayer::GetVolume()
{
    if (m_pVLC_Player)
    {
        return libvlc_audio_get_volume(m_pVLC_Player);
    }

    return 0;
}

void CAVPlayer::SetWatermarkString(CString str, int fontSize, int x, int y, COLORREF color, int transparent, int timeout)
{
// 	libvlc_video_set_logo_string(m_pVLC_Player, libvlc_logo_file, "c:\\audio.png");//Logo �ļ���

	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Enable, 1);
#ifdef _UNICODE
    std::string disp = CStringConverter::UnicodeToUtf8(str);
#else
    std::string disp = (LPTSTR)(LPCSTR)str;
#endif
	libvlc_video_set_marquee_string(m_pVLC_Player, libvlc_marquee_Text, disp.c_str());
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Color, color);
// 	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Position, 0);
	//{0 (����), 1 (��), 2 (��), 4 (��), 8 (��), 5 (����), 6 (����), 9 (����), 10 (����)} 
// 	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Opacity, transparent);
	//0 = ͸����255 = ��ȫ��͸����
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_X, x); //����Ļ���Ե��ʼ�� X ƫ�ơ�
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Y, y);//  ����Ļ�������µ� Y ƫ�ơ�
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Timeout, timeout);
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Size, fontSize);
// 	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Refresh, 10);
}

void CAVPlayer::SetWatermarkLogo(CString logoPath, int x /*= 0*/, int y /*= 0*/, int transparent /*= 0*/)
{
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_enable, 1);//�����������logo
	libvlc_video_set_logo_string(m_pVLC_Player, libvlc_logo_file, "D:\\01.png,10,10;");//Logo �ļ���
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_x, 100);  //logo�� X ���ꡣ
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_y, 100); // logo�� Y ���ꡣ
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_delay, 0);//��־�ļ��ͼ��ʱ��Ϊ����,ͼ����ʾ���ʱ�� 0 - 60000 ���롣
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_repeat, 0); // ��־logo��ѭ��,  ��־������ѭ��������-1 = ����, 0 = �ر�
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_opacity, 122); // logo ͸���� (��ֵ���� 0(��ȫ͸��) �� 255(��ȫ��͸��)
	//libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_position, 6);//1 (��), 2 (��), 4 (����), 8 (�ײ�), 5 (����), 6 (����), 9 (����), 10 (����),��Ҳ���Ի��ʹ����Щֵ������ 6=4+2��ʾ����)��
}

void CAVPlayer::SetCallbackPlaying( pfnCallback pfn )
{
    m_pfnPlaying = pfn;
}

void CAVPlayer::SetCallbackPosChanged( pfnCallback pfn )
{
    m_pfnPosChanged = pfn;
}

void CAVPlayer::SetCallbackEndReached( pfnCallback pfn )
{
    m_pfnEndReached = pfn;
}

void OnVLC_Event( const libvlc_event_t *event, void *data )
{
    CAVPlayer *pAVPlayer = (CAVPlayer *) data;
    pfnCallback pfn = NULL;

    if (! pAVPlayer)
    {
        return;
    }

    switch(event->type)
    {
    case libvlc_MediaStateChanged:
		pfn = pAVPlayer->m_pfnMediaStateChanged;
		break;
    case libvlc_MediaPlayerPlaying:
        pfn = pAVPlayer->m_pfnPlaying;
        break;
    case libvlc_MediaPlayerEndReached:
        pfn = pAVPlayer->m_pfnEndReached;
        break;
    case libvlc_MediaPlayerEncounteredError:
		pfn = pAVPlayer->m_pfnMediaPlayerEncounteredError;
		break;
    case libvlc_MediaPlayerPositionChanged:
        pfn = pAVPlayer->m_pfnPosChanged;
        break;
    case libvlc_VlmMediaInstanceStatusError:
		pfn = pAVPlayer->m_pfnVlmMediaInstanceStatusError;
		break;
    default:
       break;
    }

    if (pfn)
    {
        pfn(pAVPlayer->GetFnData());  // �˻ص����������Դ�����������������data�⣬����event�ĸ�����Ϣ����event->u.media_player_position_changed.new_position���ȵȣ���������չ��
    }   
}
