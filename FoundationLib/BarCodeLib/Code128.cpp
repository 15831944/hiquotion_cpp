// Code128.cpp: implementation of the CCode128 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Code128.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCode128::CCode128()
{

}

CCode128::~CCode128()
{

}

int CCode128::Code128BVerify(LPCSTR text)
{
   if (text[0] == '\0')
		return -1;

   while (*text && *text>=32 && !(*text&0x80))
		text++;

   if (*text)
		return -1; // ���ǺϷ����ַ�

   return 0; 
}

int CCode128::Code128BEncode(LPSTR text, LPSTR partial)
{
	unsigned i;
	int code,checksum=0;
	char *str=text;


	if(!partial)
	{
		return -1;
	}
	
	//���ַ�ΪSTART_B(HEAD)
	strcat(partial,code128set[START_B]);
	//���ַ�ҲҪ�ӵ�У�����ȥ
	checksum+=START_B;

	//����ַ���Ϊ�գ��򷵻�
	if(!str)
	{
		delete partial;
		return -1;
	}

	for(i=0;i<strlen(str);i++)
	{
		if ( str[i] < 32 || (str[i] & 0x80))
		{
			//��Ϊ�Ƿ��ַ����򷵻�
			free(partial);
			return -1;
		}
		
		code = str[i]-32;
		strcat(partial, code128set[code]);
		//У���Ϊ��first * 1 + second * 2 + third * 3... 
		checksum += code * (i+1); 
	}

	//����У���Ϊ����103���õ�����
	checksum%=103;
	//��У��ͼ���partial
	strcat(partial,code128set[checksum]);
	//����STOP��β�ַ�
	strcat(partial,code128set[STOP]);

	return 0;
}

int CCode128::Code128CVerify(LPCSTR text)
{
	if (text[0] == '\0')
		return -1;

	//�ַ���Ŀ����Ϊż����
	if (strlen(text)%2)
		return -1;

	//�����ַ����붼������
	for (; *text; text++)
		if (!isdigit(*text))
			return -1;

	return 0;
}

int CCode128::Code128CEncode(LPSTR text, LPSTR partial)
{
	int i,code,checksum=0;
	char *str=text;


	if(!partial)
	{
		return -1;
	}

	//���ַ�ΪSTART_C(HEAD)
	strcat(partial,code128set[START_C]);
	//���ַ�ҲҪ�ӵ�У�����ȥ
	checksum+=START_C;

	//����ַ���Ϊ�գ��򷵻�
	if(!str)
	{
		delete partial;
		return -1;
	}

	for(i=0;str[i];i+=2)
	{
		if(!isdigit(str[i])||!isdigit(str[i+1]))
		{
			free(partial);
			return -1;
		}
		code=(str[i]-'0')*10+str[i+1]-'0';
		strcat(partial,code128set[code]);
		//У���Ϊ��first * 1 + second * 2 + third * 3... 
		checksum+=code*(i/2+1);
	}

	//����У���Ϊ����103���õ�����
	checksum%=103;
	//��У��ͼ���partial
	strcat(partial,code128set[checksum]);
	//����STOP��β�ַ�
	strcat(partial,code128set[STOP]);

	return 0;
}

int CCode128::Code128AEncode(LPSTR text, LPSTR partial)
{
	unsigned i;
	int code,checksum=0;
	char *str=text;


	//����ռ�
	if(!partial)
	{
		return -1;
	}

	//���ַ�ΪSTART_A(HEAD)
	strcat(partial,code128set[START_A]);
	//���ַ�ҲҪ�ӵ�У�����ȥ
	checksum+=START_A;

	//����ַ���Ϊ�գ��򷵻�
	if(!str)
	{
		delete partial;
		return -1;
	}
	for(i=0;i<strlen(str);i++)
	{
		if ( str[i] > 95 && !(str[i] & 0x80))
		{
			//��Ϊ�Ƿ��ַ����򷵻�
			free(partial);
			return -1;
		}
		
		if (str[i]<32)
		{
			code=str[i]+64;
		}
		else if((str[i]>=32)&&(str[i]<=95))
		{
			code=str[i]-32;
		}
		else if(str[i]==0xc1)
		{
			code=FUNC_1;
		}
		else if(str[i]==0xc2)
		{
			code=FUNC_2;
		}
		else if(str[i]==0xc3)
		{
			code=FUNC_3;
		}
		else if(str[i]==0xc4)
		{
			code=CODE_A;
		}
		else if(str[i]==0x80)
		{
			code=64;
		}

		strcat(partial, code128set[code]);
		//У���Ϊ��first * 1 + second * 2 + third * 3... 
		checksum += code * (i+1); 
	}

	//����У���Ϊ����103���õ�����
	checksum%=103;
	//��У��ͼ���partial
	strcat(partial,code128set[checksum]);
	//����STOP��β�ַ�
	strcat(partial,code128set[STOP]);



	return 0;
}

int CCode128::Code128AVerify(LPCSTR text)
{
	while (*text&&(*text<=95 ||(*text&0x80)))
		text++;

	if (*text)
		return -1; // ���ǺϷ����ַ�

	return 0;
}