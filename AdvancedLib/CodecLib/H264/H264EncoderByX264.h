#pragma once

extern "C"
{
#include "H264-x264/extras/stdint.h"
#include "H264-x264/x264.h"
};

#define DATA_MAX 300000

class CH264EncoderByX264
{
public:
	CH264EncoderByX264(void);
	~CH264EncoderByX264(void);

	BOOL initEncoder(int width, int height);
	void closeEncoder();
// 	void setParameter(int width, int height, int bitrate=DEFAULT_BIT_RATE, float framerate=DEFAULT_FRAME_RATE, int aspect_ratio=DEFAULT_ASPECT_RATIO, int video_format=DEFAULT_VIDEO_FORMAT);
	BOOL encode(BYTE *yuvSrc, BYTE *dst, int *dstLen);

protected:
	void init_param();

private:
	int m_width;
	int m_height;
	int m_bitrate;
	float m_framerate;
	int m_aspect_ratio;
	int m_video_format;

	int m_size;

// 	T264_param_t m_param;
// 	T264_t* m_encoder_t;
	// 	T264_t* m_decoder_t;
	int m_totalno;

	x264_t *m_encoder_t;//��������
	x264_picture_t pic;//����ͼ��YUV
	x264_picture_t m_picin;//����ͼ��YUV
	x264_picture_t m_picout;//���ͼ��RAW
	x264_param_t m_param;//��������

	uint8_t data[DATA_MAX];

	// 	CString m_src;
	// 	CString m_dst;
	// 	CString m_rec;

	uint8_t *m_buf, *m_dst, *m_rec;

	BOOL m_isOpen;

};
