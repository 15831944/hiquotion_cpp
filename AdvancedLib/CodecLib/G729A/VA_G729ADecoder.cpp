#include "stdafx.h"
#include "VA_G729ADecoder.h"

CVA_G729ADecoder::CVA_G729ADecoder(void)
{
	init();
}

CVA_G729ADecoder::~CVA_G729ADecoder(void)
{
}

void CVA_G729ADecoder::init()
{
	/*-----------------------------------------------------------------*
	*           Initialization of decoder                             *
	*-----------------------------------------------------------------*/

	va_g729a_init_decoder();
}

// src���Ⱥ�dst���ȶ��ǹ̶���
// ���� Word16��32λ��Ӧ���� 2 �ֽڣ�64λ��Ϊ 4 �ֽڣ� Ϊ���ȵ�λ��������
// src���� = SERIAL_SIZE�����ж���Ϊ��80�� �� sizeof(Word16) = 160��32λ�£��� 320��64λ�£�
// dst���� = L_FRAME�����ж���Ϊ��80+2�� �� sizeof(Word16) = 164��32λ�£��� 328��64λ�£�
int CVA_G729ADecoder::decode(char *src, char *dst)
{
	if(!src || !dst)
		return -1;

	va_g729a_decoder((unsigned char *)src, (short *)dst, 0);

	return 0;
}

// ����
// ԭ���ȱ����� 10 ��������
int CVA_G729ADecoder::decodeEx(char *src, unsigned int srcLen, char *dst)
{
	int count=srcLen / 10;
	for(int i=0;i<count;i++)
	{
		decode((char *)(src + i * 10), (char *)(dst + i * 160));
	}

	return 0;
}
