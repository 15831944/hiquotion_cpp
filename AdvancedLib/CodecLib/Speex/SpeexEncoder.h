#pragma once

#include <C++\3rdParty\Speex\speex.h>

#define FRAME_SIZE 160

// Speex ������
// ע�����ݹٷ��ĵ���Speex �����̰߳�ȫ�ģ����Ը���Ҳ�����̰߳�ȫ��
// �߳���ִ�б���ʱ�������
// �Ժ��л��ῴֱ�Ӽ�������ʡ���ⲿ����

class CSpeexEncoder
{
public:
	CSpeexEncoder(void);
	~CSpeexEncoder(void);

	BOOL init(int quality=8);
	BOOL encode(float *src, int srcLen, char *dst, int *dstLen);
	void destroy();

private:
	SpeexBits bits;
	void *state;
};
