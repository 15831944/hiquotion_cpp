#include "stdafx.h"
#include "VA_G729AEncoder.h"

CVA_G729AEncoder::CVA_G729AEncoder(void)
{
	init();
}

CVA_G729AEncoder::~CVA_G729AEncoder(void)
{
}

void CVA_G729AEncoder::init()
{
	va_g729a_init_encoder();
}

int CVA_G729AEncoder::encode(char *src, char *dst)
{
	if(!src || !dst)
		return -1;

	va_g729a_encoder((short *)src, (unsigned char *)dst);

	return 0;
}

// ����
// ԭ���ȱ����� 160 ��������
int CVA_G729AEncoder::encodeEx(char *src, unsigned int srcLen, char *dst)
{
	int count=srcLen / 160;
	for(int i=0;i<count;i++)
	{
		encode((char *)(src + i * 160), (char *)(dst + i * 10));
	}

	return 0;
}
