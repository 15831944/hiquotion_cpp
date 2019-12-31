#include "stdafx.h"
#include "G729ADecoder.h"

CG729ADecoder::CG729ADecoder(void)
{
	srcLen=SERIAL_SIZE;  //*sizeof(Word16);
	dstLen=L_FRAME*sizeof(Word16);
	init();
}

CG729ADecoder::~CG729ADecoder(void)
{
}

void CG729ADecoder::init()
{
	/*-----------------------------------------------------------------*
	*           Initialization of decoder                             *
	*-----------------------------------------------------------------*/

	for (i=0; i<M; i++) synth_buf[i] = 0;
	synth = synth_buf + M;

	Init_Decod_ld8k();
	Init_Post_Filter();
	Init_Post_Process();
	voicing = 60;

}

// src���Ⱥ�dst���ȶ��ǹ̶���
// ���� Word16��32λ��Ӧ���� 2 �ֽڣ�64λ��Ϊ 4 �ֽڣ� Ϊ���ȵ�λ��������
// src���� = SERIAL_SIZE�����ж���Ϊ��80�� �� sizeof(Word16) = 160��32λ�£��� 320��64λ�£�
// dst���� = L_FRAME�����ж���Ϊ��80+2�� �� sizeof(Word16) = 164��32λ�£��� 328��64λ�£�
int CG729ADecoder::decode(char *src, char *dst)
{
	if(!src || !dst)
		return -1;

// 	memcpy(serial, src, srcLen);

// 	bits2prm_ld8k( &serial[2], &parm[1]);
// 	bits2prm_ld8k( serial, &parm[1]);
	bits2prm_ld8k( (unsigned char *)src, &parm[1]);

// 	/* the hardware detects frame erasures by checking if all bits
// 	are set to zero
// 	*/
// 	parm[0] = 0;           /* No frame erasure */
// 	for (i=2; i < SERIAL_SIZE; i++)
// 		if (serial[i] == 0 ) parm[0] = 1; /* frame erased     */
// 
// 	/* check parity and put 1 in parm[4] if parity error */
// 
// 	parm[4] = Check_Parity_Pitch(parm[3], parm[4]);

	parm[0] = 0;  /* ����û�ж�֡ */
	parm[4] = 0 ; /* ��������Ч������ */

	Decod_ld8k(parm, voicing, synth, Az_dec, &T0_first);

	/* Postfilter */

	voicing = 0;
	ptr_Az = Az_dec;
	for(i=0; i<L_FRAME; i+=L_SUBFR) {
		Post(T0_first, &synth[i], ptr_Az, &pst_out[i], &sf_voic);
		if (sf_voic != 0) { voicing = sf_voic;}
		ptr_Az += MP1;
	}
	Copy(&synth_buf[L_FRAME], &synth_buf[0], M);

	Post_Process(pst_out, L_FRAME);

#ifdef HARDW
	{
		Word16 *my_pt;
		Word16 my_temp;
		int my_i;
		my_pt = pst_out;
		for(my_i=0; my_i < L_FRAME; my_i++) {
			my_temp = *my_pt;
			my_temp = add( my_temp, (Word16) 4); /* rounding on 13 bit */
			my_temp = my_temp & 0xFFF8; /* mask on 13 bit */
			*my_pt++ = my_temp;
		}
	}
#endif

	memcpy(dst, pst_out, dstLen);

	return 0;
}

// ����
// ԭ���ȱ����� 10 ��������
int CG729ADecoder::decodeEx(char *src, unsigned int srcLen, char *dst)
{
	int count=srcLen / 10;
// 	char srcSlip[10];
// 	char dstSlip[160];
	for(int i=0;i<count;i++)
	{
// 		memcpy(srcSlip, src + i * 10, 10);
		decode((char *)(src + i * 10), (char *)(dst + i * 160));
// 		memcpy(dst + i * 160, dstSlip, 160);

// 		Sleep(1);
	}

	return 0;
}
