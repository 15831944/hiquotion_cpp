// SDTP.h: interface for the CSDTP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDTP_H__C4AC6824_B31B_48A1_9318_B8BF78A0C93F__INCLUDED_)
#define AFX_SDTP_H__C4AC6824_B31B_48A1_9318_B8BF78A0C93F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\BufferLib\HeaderBuffer.h>

// SDTP���������ݴ���Э��
// Э���ʽ��Э��ͷ + ����
// Э��ͷ��16�ֽڣ�
// Э���־��sdtp�������ݴ���Э�飩 ���� 4 �ֽ�
// �汾�ţ�1.0.0.0                    ���� 4 �ֽ�
// ���ݳ��ȣ�                         ���� 4 �ֽ�
// ����У�飺                         ���� 4 �ֽ�
// ���ݣ�ʵ�ʴ��������

// У�鷽����
// ������ͣ���ģ256

// �����ÿ����Ҫ��������ݶ���װ�������Ĵ���Э������ݣ�Ȼ���ٷ���
// �������ݺ��ȸ���Э��ͷ�ж����ݳ��ȣ����ж������Ƿ�����㹻�������㹻���׳��¼����¼��а���ʵ�ʴ�������ݺͳ������ԣ�

#define SDTP_FLAG_LENGTH      4
#define SDTP_VERTION_LENGTH   4
#define SDTP_DATA_LENGTH      4
#define SDTP_DATA_CODE_LENGTH 4
#define SDTP_HEAD_LENGTH      SDTP_FLAG_LENGTH + SDTP_VERTION_LENGTH + SDTP_DATA_LENGTH + SDTP_DATA_CODE_LENGTH

class CSDTP  
{
public:
	CSDTP();
	virtual ~CSDTP();

	// ��ʼ��
	void init();

	// ����Э���־��Э��汾
	void genHead(char flag[SDTP_FLAG_LENGTH], char ver[SDTP_VERTION_LENGTH]);
	void genHead(char flag1, char flag2, char flag3, char flag4, char ver1, char ver2, char ver3, char ver4);

	// ����Э��ͷ�е�Э���־
	void setProtocolFlagInHead(char c[SDTP_FLAG_LENGTH]);
	void setProtocolFlagInHead(char c1, char c2, char c3, char c4);

	// ��ȡЭ��ͷ�е�Э���־
	void getProtocolFlagInHead(char c[SDTP_FLAG_LENGTH]);
	void getProtocolFlagInHead(char *c1, char *c2, char *c3, char *c4);
	

	// ����Э��ͷ�еİ汾��
	void setVersionInHead(char v[SDTP_VERTION_LENGTH]);
	void setVersionInHead(char v1, char v2, char v3, char v4);

	// ��ȡЭ��ͷ�еİ汾��
	void getVersionInHead(char v[SDTP_VERTION_LENGTH]);
	void getVersionInHead(char *v1, char *v2, char *v3, char *v4);
	

	// ����Э��ͷ�е����ݳ���
	void setDataLengthInHead(int len);

	// ��ȡЭ��ͷ�е����ݳ���
	void getDataLengthInHead(int *len);
	

	// ����Э��ͷ�е�����У��
	void setCheckCodeInHead(int checkCode);

	// ��ȡЭ��ͷ�е�����У��
	void getCheckCodeInHead(int *checkCode);
	

	// ������������
	BOOL appendData(char *data, int dataLength);

	// ��ȡ��������
	BOOL getData(char *data);


	// ��ȡ���ݳ���
	int getDataLength();


	// �����������ݣ���Э��ͷ��ʼ����ʼд�룩
	BOOL setTotalData(char *data, int dataLength);

	// ��ȡ�������ݣ���Э��ͷ��ʼ����ʼ��ȡ��
	BOOL getTotalData(char *data);


	// ��ȡ�������ݳ��ȣ�����Э��ͷ��
	int getTotalDataLength();
	

	// ����У����
	virtual int genCheckCode();
	// ��֤У����
	virtual BOOL verifyCheckCode(int checkCode);
	

	// ���û�������С
	BOOL setBufferLength(int bufferLength);

protected:
	CHeaderBuffer m_buffer;
};

#endif // !defined(AFX_SDTP_H__C4AC6824_B31B_48A1_9318_B8BF78A0C93F__INCLUDED_)
