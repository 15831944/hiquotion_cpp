#pragma once

extern "C"
{
#include "g.729a\typedef.h"
#include "g.729a\basic_op.h"
#include "g.729a\ld8k.h"
};

// #define L_TOTAL     240        /* Total size of speech buffer.              */
// #define L_WINDOW    240        /* Window size in LP analysis.               */
// #define L_NEXT      40         /* Lookahead in LP analysis.                 */
// #define L_FRAME     80         /* Frame size.                               */
// #define L_SUBFR     40         /* Subframe size.                            */

/*----------------------------------------------------------------------*
*      Initialize pointers to speech vector.                            *
*                                                                       *
*                                                                       *
*   |--------------------|-------------|-------------|------------|     *
*     previous speech           sf1           sf2         L_NEXT        *
*                                                                       *
*   <----------------  Total speech vector (L_TOTAL)   ----------->     *
*   <----------------  LPC analysis window (L_WINDOW)  ----------->     *
*   |                   <-- present frame (L_FRAME) -->                 *
* old_speech            |              <-- new speech (L_FRAME) -->     *
* p_window              |              |                                *
*                     speech           |                                *
*                             new_speech                                *
*-----------------------------------------------------------------------*/

// sf1 = sf2 = L_NEXT
// L_FRAME = 2 * L_NEXT


// �����ĳ������ڿ�������������Ϊ 10 �ֽ�

// extern Word16 *new_speech;     /* Pointer to new speech data            */

class CG729AEncoder
{
public:
	CG729AEncoder(void);
	~CG729AEncoder(void);

	void init();

	// src���Ⱥ�dst���ȶ��ǹ̶���
	// ���� Word16 Ϊ���ȵ�λ�������ݣ�Word16 �� short int
	// �鿴����ʵ���������� 32 λ���� 64 λ�£�short int ���� 2 �ֽڣ��� 16 λ
	// ���ԣ�src ���� = L_FRAME�����ж���Ϊ��80�� �� sizeof(Word16) = 160
	// xxx dst���� = SERIAL_SIZE�����ж���Ϊ��80+2�� �� sizeof(Word16) = 164��32λ�£��� 328��64λ�£�
	// dst����������Ϊ 10 �ֽڣ���ԭ���ȵ� 1/16��
	int encode(char *src, char *dst);
// 	// src�ĳ��ȵ���80��Word16��2�ֽڣ������ܳ�����160
// 	int encode(Word16 *src, char *dst);

	// ����
	// ԭ���ȱ����� 160 ��������
	int encodeEx(char *src, unsigned int srcLen, char *dst);


private:

	Word16 prm[PRM_SIZE];          /* Analysis parameters.                  */
// 	Word16 serial[SERIAL_SIZE];    /* Output bitstream buffer               */
	unsigned char serial[SERIAL_SIZE];    /* Output bitstream buffer               */
	Word16 syn[L_FRAME];           /* Buffer for synthesis speech           */

	Word16 i, frame;               /* frame counter */

	Word16 srcLen;
	Word16 dstLen;
};
