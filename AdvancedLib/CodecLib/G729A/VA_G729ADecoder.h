#pragma once

extern "C"
{
#include <C++\3rdParty\G729A\va_g729a.h>
};

// ����ǰ�ĳ������ڿ�������������Ϊ 10 �ֽ�

class CVA_G729ADecoder
{
public:
	CVA_G729ADecoder(void);
	~CVA_G729ADecoder(void);

	void init();

	// src���Ⱥ�dst���ȶ��ǹ̶���
	// ���� Word16��32λ��Ӧ���� 2 �ֽڣ�64λ��Ϊ 4 �ֽڣ� Ϊ���ȵ�λ��������
	// xxx src���� = SERIAL_SIZE�����ж���Ϊ��80+2�� �� sizeof(Word16) = 164��32λ�£��� 328��64λ�£�
	// src����������Ϊ 10 �ֽ�
	// dst���� = L_FRAME�����ж���Ϊ��80�� �� sizeof(Word16) = 160��32λ�£��� 320��64λ�£�
	int decode(char *src, char *dst);

	// ����
	// ԭ���ȱ����� 10 ��������
	int decodeEx(char *src, unsigned int srcLen, char *dst);

private:
// 	Word16  synth_buf[L_FRAME+M], *synth; /* Synthesis                   */
// 	Word16  parm[PRM_SIZE+1];             /* Synthesis parameters        */
// // 	Word16  serial[SERIAL_SIZE];          /* Serial stream               */
// 	unsigned char serial[SERIAL_SIZE];          /* Serial stream               */
// 	Word16  Az_dec[MP1*2], *ptr_Az;       /* Decoded Az for post-filter  */
// 	Word16  T0_first;                     /* Pitch lag in 1st subframe   */
// 	Word16  pst_out[L_FRAME];             /* Postfilter output           */
// 
// 	Word16  voicing;                      /* voicing from previous frame */
// 	Word16  sf_voic;                      /* voicing for subframe        */
// 
// 	Word16  i, frame;
// 
// 	Word16 srcLen;
// 	Word16 dstLen;
};
