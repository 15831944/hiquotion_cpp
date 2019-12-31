// GCardReaderCtl.cpp : Implementation of the CIDCardOperation ActiveX Control class.

#include "stdafx.h"
#include "IDCardOperation.h"
#include "UCmd.h"
#include <C++\FoudationLib\social.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nOpen=1;
bool	bConnect;
int		nCom;
BYTE buff[2048];
int nReset=0;
BOOL bRun;

CIDCardOperation::CIDCardOperation()
{
	
}

CIDCardOperation::~CIDCardOperation()
{
	
}

int CIDCardOperation::initReader()
{
	if(!LoadDll())
		return -2;

	int para0,para1,para2;
	BYTE CMD=0x41;       //��ʼ���˿�
	para0=0;
	para1=8811;
	para2=9986;
	int nRet;
	nRet=mycmd(&CMD,&para0,&para1,&para2);
	if((nRet!=62171)||(nRet==-5)||(nRet==-7))
		//if(nRet!=62171)
	{
		bConnect=FALSE;
		//ShowMessage("��˼SS628--�ڶ����������֤��֤�ն�����ʧ�ܣ�"+0x0a+0x0d+"����ԭ����ֶ����ӣ�");
// 		ss.Format("����ʧ��");
// 		m_ctMsg.SetWindowText(ss);
		return -1;
	}
	else
	{
		//
		bConnect=TRUE;
// 		SetTimer(1,300,NULL);
// 		pBtn->SetWindowText("ֹͣ����");
// 		m_ctMsg.SetWindowText("���ӳɹ�����ʼ����");
		return 0;
	}

}

// ����ֵ��
// 0���ɹ�����
// 2��δ�ҵ���
// 1������ʧ��
// <0��
int CIDCardOperation::read()
{
	BYTE CMD;
	int para0,para1,para2;
	int nRet,nRet1;

		bRun=TRUE;
// 	m_ctMsg.SetWindowText("Ѱ�ҿ�..");
	//------------------------------------------------------------
	CMD=0x43;       //��֤��
	//para0=1001;
	para1=8811;
	para2=9986;
	nRet=mycmd(&CMD,&para0,&para1,&para2);
	if(nRet==62171)
	{
		//m_strMsg="���ڶ���...";
// 		m_ctMsg.SetWindowText("���ڶ���...");
		//--------------------------------------------------------

		CMD=0x44;       //��������Ϣ
		//para0=0;
		para1=8811;
		para2=9986;
		int nRet;
		nRet=mycmd(&CMD,&para0,&para1,&para2);
		if ((nRet==62171) || (nRet==62172))
		{
			m_strNewAddr="";
			
			CMD=0x45;       //������סַ��Ϣ
			//para0=0;
			para1=8811;
			para2=9986;
			nRet1=mycmd(&CMD,&para0,&para1,&para2);
			if(nRet1==62171)
			{
				CFile f_name;
				
				char byNewAddr[72];
				if(f_name.Open("NewAdd.txt",CFile::modeRead))
				{
					f_name.SeekToBegin();
					f_name.Read(&byNewAddr,70);			
					byNewAddr[70]=0x0;byNewAddr[71]=0x0;
					m_strNewAddr=byNewAddr;

					f_name.Close();
				}
			}
			else
			{
				m_strNewAddr="";
			}

			if ((nRet==62171) || (nRet==62172))
			{
// 				SendMessage(CARD_READ_MSG, 0, 0);  !!!!!!!!!!!!!!!!!!!! �����ɹ� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// 				Beep(1500,300);
				return 0;

			}
			else
				return nRet;
// 				else if (nRet==0)
// 				{
// 					::MessageBox(NULL,"����sdtapi.dll����",MB_OK,0);
// 				}else if( nRet==-1)
// 				{
// 					::MessageBox(NULL,"��Ƭ�������",MB_OK,0);
// 				}
// 				else if (nRet==-2)
// 				{
// 					::MessageBox(NULL,"wlt�ļ���׺����",MB_OK,0);
// 				}
// 				else if (nRet==-3)
// 				{
// 					::MessageBox(NULL,"wlt�ļ��򿪴���",MB_OK,0);
// 				}
// 				else if (nRet==-4)
// 				{
// 					::MessageBox(NULL,"wlt�ļ���ʽ����",MB_OK,0);
// 				}
// 				else if (nRet==-5)
// 				{
// 					::MessageBox(NULL,"���δ��Ȩ",MB_OK,0);
// 				}
// 				else if (nRet==-6)
// 				{
// 					::MessageBox(NULL,"�豸���Ӵ���",MB_OK,0);
// 				}


		}
		else
		{
			//��������Ϣ����

// 			m_ctMsg.SetWindowText("����ʧ��!");
//			::MessageBox(NULL,"����ʧ�ܣ������������Ҫ�Թ���Ա������С�",MB_OK,0);
			return 1;
		}
		//--------------------------------------------------------
	}
	else
	{
		//Ѱ��/֤����    ѡ��/֤����
		//m_ctMsg.SetWindowText("ѡ������...");
// 		m_ctMsg.SetWindowText("Ѱ�ҿ�...");
		return 2;
	}
}

CString CIDCardOperation::GetName() 
{
	memset(buff, 0x00, 2048);
	myGetName(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetSex() 
{
	memset(buff, 0x00, 2048);
	myGetSex(buff);
	CString strResult(buff);
	strResult.TrimRight();
	if(strResult=="1")
		strResult="��";
	else
		strResult="Ů";
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetFolk() 
{
	memset(buff, 0x00, 2048);
	myGetFolk(buff);
	CString strResult(buff);
	strResult.TrimRight();
	strResult=FOLK[atoi((LPTSTR)(LPCSTR)strResult)].c_str();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetBirth() 
{
	memset(buff, 0x00, 2048);
	myGetBirth(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetAddr() 
{
	memset(buff, 0x00, 2048);
	myGetAddr(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetIDNum() 
{
	memset(buff, 0x00, 2048);
	myGetIDNum(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetDepartment() 
{
	memset(buff, 0x00, 2048);
	myGetDep(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetValidDateFrom() 
{
	memset(buff, 0x00, 2048);
	myGetBegin(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetValidDateTo() 
{
	memset(buff, 0x00, 2048);
	myGetEnd(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetPicPath() 
{
	memset(buff, 0x00, 2048);
	myGetPicPath(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

