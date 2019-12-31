// SIDCardOperation.cpp: implementation of the CSIDCardOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SIDCardOperation.h"
#include "dcic32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSIDCardOperation::CSIDCardOperation()
: icdev((HANDLE)-1), m_isOpen(FALSE)
{

}

CSIDCardOperation::~CSIDCardOperation()
{
	closeReader();
}

// ����ֵ��
// 0���ɹ�
// С��0��ʧ��
int CSIDCardOperation::initReader()
{
	//��ʼ������    wfl 2003.12.10
	icdev = IC_InitComm_Baud(100,119200);
	if(icdev<0)
		return (int)icdev;

	IC_InitType(icdev,12);  // 12 ��������
	m_isOpen=TRUE;

	return 0;
}

void CSIDCardOperation::closeReader()
{
	if (m_isOpen)
	{
		IC_ExitComm(icdev);
		icdev=0;
		m_isOpen=FALSE;
	}
}

BOOL CSIDCardOperation::isCardExist()
{
	if(!m_isOpen)
		return FALSE;

	int relen = -1;
	unsigned char redata[64] = "\0";
	
	int st=IC_CpuReset_Hex(icdev,(unsigned char *)&relen,redata);
	if (st!=0)
	{
// 		if(st==-134)  // �޿�
// 			return FALSE;

		return FALSE;
	}

	return TRUE;
}

int CSIDCardOperation::read()
{
	initString();

	int st=doSSSECmd_Hex();
	if(st!=0)
		return st;

	// ��ȡ����Ϣ

	st=doSelectCardInfoFileCmd_Hex();
	if(st!=0)
		return st;

// 	// ����                                     �ļ� flag ����
// 	CString m_cardId;      // ��ʶ����          EF05  01   10
// 	CString m_cardPubDate; // ��������          EF05  05   04
// 	CString m_cardValidateTo;  // ��Ч��        EF05  06   04
// 	CString m_sidNo;      // ���ţ������籣�ţ� EF05  07   09

	st=doGetRecordCmd_Hex("01", "12", m_cardId);
	if(st!=0)
		return st;

	st=doGetRecordCmd_Hex("05", "06", m_cardPubDate);
	if(st!=0)
		return st;
	
	st=doGetRecordCmd_Hex("06", "06", m_cardValidateTo);
	if(st!=0)
		return st;
	
	st=doGetRecordCmd(7, 11, m_sidNo);
	if(st!=0)
		return st;

	// ��ȡ���˻�����Ϣ

	st=doSelectPersonInfoFileCmd_Hex();
	if(st!=0)
		return st;
	
// 	                       // ����     �ļ� flag ����
// 	CString m_idNo;        // ���֤�� EF06  08   12
// 	CString m_name;        // ����     EF06  09   1E
// 	CString m_sex;         // �Ա�     EF06  0A   01
// 	CString m_folk;        // ����     EF06  0B   01
// 	CString m_birthPlace;  // ������   Ef06  0C   03
// 	CString m_birthday;    // ����     EF06  0D   04
	st=doGetRecordCmd(8, 20, m_idNo);
	if(st!=0)
		return st;

	st=doGetRecordCmd(9, 32, m_name);
	if(st!=0)
		return st;
	
	st=doGetRecordCmd(10, 3, m_sex);
	if(st!=0)
		return st;
	
	st=doGetRecordCmd_Hex("0B", "03", m_folk);
	if(st!=0)
		return st;
	
	st=doGetRecordCmd_Hex("0C", "05", m_birthPlace);
	if(st!=0)
		return st;

	while(m_birthPlace.GetLength()>0 && m_birthPlace.Right(2)=="FF")
		m_birthPlace=m_birthPlace.Left(m_birthPlace.GetLength()-2);
	
	st=doGetRecordCmd_Hex("0D", "06", m_birthday);
	if(st!=0)
		return st;
	
	return 0;
}

int CSIDCardOperation::doSSSECmd_Hex()
{
	unsigned char sedata[64]={"00A404000F7378312E73682EC9E7BBE1B1A3D5CF"};
	int relen = -1;
	unsigned char redata[64] = "\0";
	memset(redata,0,sizeof(redata));
	int st=IC_CpuApduEXT_Hex(icdev,20,sedata,(__int16 *)&relen,redata);
	return st;
}

int CSIDCardOperation::doPublicAppCmd_Hex()
{
	unsigned char sedata[64]={"00A404000F7378312E73682EC9E7BBE1B1A3D5CF"};
	int relen = -1;
	unsigned char redata[64] = "\0";
	memset(redata,0,sizeof(redata));
	int st=IC_CpuApduEXT_Hex(icdev,20,sedata,(__int16 *)&relen,redata);
	return st;
}

int CSIDCardOperation::doSelectCardInfoFileCmd_Hex()
{
	unsigned char sedata[64]={"00A4020002EF05"};
	int relen = -1;
	unsigned char redata[64] = "\0";
	memset(redata,0,sizeof(redata));
	int st=IC_CpuApduEXT_Hex(icdev,7,sedata,(__int16 *)&relen,redata);
	return st;
}

int CSIDCardOperation::doSelectPersonInfoFileCmd_Hex()
{
	unsigned char sedata[64]={"00A4020002EF06"};
	int relen = -1;
	unsigned char redata[64] = "\0";
	memset(redata,0,sizeof(redata));
	int st=IC_CpuApduEXT_Hex(icdev,7,sedata,(__int16 *)&relen,redata);
	return st;
}

int CSIDCardOperation::doGetRecordCmd_Hex(CString flag, CString len, CString &result)
{
	if(flag.GetLength()!=2)
		return -1001;

	if(len.GetLength()!=2)
		return -1002;

	CString pre="00B2";
	CString mid="00";
	CString sedata="00B2"+flag+"00"+len;
// 	CString sedata=pre+flag+mid+len;
//	unsigned char sedata[64]={"00B2010012"};
	int relen = -1;
	unsigned char redata[64] = "\0";
	memset(redata,0,sizeof(redata));
	int st=IC_CpuApduEXT_Hex(icdev,sedata.GetLength()/2,(unsigned char *)sedata.GetBuffer(sedata.GetLength()),(__int16 *)&relen,redata);
	if (st!=0)
		return st;

	CString sresult=redata;
	sresult=sresult.Right(sresult.GetLength()-4);
	if(sresult.GetLength()<4)
		return -1003;

	if(sresult.GetLength()==4 && sresult!="9000" && sresult.Left(2)!="61")
		return -1004;

	result=getResult(sresult);
	
	return st;
}

int CSIDCardOperation::doGetRecordCmd(char flag, char len, CString &result)
{
	// {"00B2010012"};
	unsigned char sedata[64]={ 0, 178, flag, 0, len};
	int relen = -1;
	unsigned char redata[64] = "\0";
	memset(redata,0,sizeof(redata));
	int st=IC_CpuApduEXT(icdev,5,sedata,(__int16 *)&relen,redata);
	if (st!=0)
		return st;

	memcpy(redata, redata+2, len);
	redata[len-2]='\0';
	
	result=redata;
	
	return st;
}

// ����Э�飬���������������������ֽ�ȥ������16�����ַ������ã�2�ֽ�����16���Ƶ�4�ֽڣ�����ȥ���ַ�������4���ֽ�
CString CSIDCardOperation::getResult(CString result)
{
	if(result.GetLength()<4)
		return "data error!";
	else if(result.GetLength()==4)
	{
		if(result=="9000" || result.Left(2)=="61")
			return "";
		else
			return result;
	}

	return result.Left(result.GetLength()-4);
}

void CSIDCardOperation::initString()
{
	m_cardId="";
	m_cardPubDate="";
	m_cardValidateTo="";
	m_sidNo="";
	m_idNo="";
	m_name="";
	m_sex="";
	m_folk="";
	m_birthPlace="";
	m_birthday="";
}
