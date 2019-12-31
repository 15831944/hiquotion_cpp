
// MonitorSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MonitorSystem.h"
#include "MonitorSystemDlg.h"
#include <FileSysLib\FolderOperation.h>
#include "monitorlib\monitorbuilder.h"
#include <sstream>
#include <FileSysLib\FileOperation.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMonitorSystemDlg �Ի���




CMonitorSystemDlg::CMonitorSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonitorSystemDlg::IDD, pParent)
	, m_monitorDetails(_T(""))
// 	, m_eventLogString(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitorSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MONITOR_INFO, m_monitorList);
	DDX_Text(pDX, IDC_EDIT_MONITOR_INFO, m_monitorDetails);
	// 	DDX_Text(pDX, IDC_EDIT_EVENT_LOG, m_eventLogString);
	DDX_Control(pDX, IDC_EDIT_EVENT_LOG, m_txtLog);
}

BEGIN_MESSAGE_MAP(CMonitorSystemDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_START_ALL, &CMonitorSystemDlg::OnBnClickedButtonStartAll)
	ON_BN_CLICKED(IDC_BUTTON_STOP_ALL, &CMonitorSystemDlg::OnBnClickedButtonStopAll)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMonitorSystemDlg::OnBnClickedButtonClose)
	ON_WM_CLOSE()
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MONITOR_INFO, &CMonitorSystemDlg::OnLvnItemchangedListMonitorInfo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MONITOR_INFO, &CMonitorSystemDlg::OnNMClickListMonitorInfo)
	ON_BN_CLICKED(IDC_BUTTON1, &CMonitorSystemDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMonitorSystemDlg ��Ϣ�������

BOOL CMonitorSystemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_appPath=CFolderOperation::addGang(CFolderOperation::GetModulePath());

	// ������־Ŀ¼
	CString eventFolder=m_appPath + "EventLogs";
	if(!CFolderOperation::isFolderExist(eventFolder))
	{
		if(!CFolderOperation::createDir(eventFolder))
			MessageBox("��־Ŀ¼ EventLogs ����ʧ�ܣ�\n\n���ȹرճ����ڳ���Ŀ¼���ֶ�������־Ŀ¼���ٴ����С�");
	}

	CString file=m_appPath+"config.xml";
	if(!CFileOperation::isFileExist(file))
	{
		MessageBox("config.xml �ļ������ڣ�");

		((CButton *)GetDlgItem(IDC_BUTTON_START_ALL))->EnableWindow(FALSE);
	}
	else
	{
		CMonitorBuilder monitorBuilder((LPTSTR)(LPCSTR)file, &m_monitorManager);
		int ret=monitorBuilder.build();

		if(ret==0)
			m_monitorManager.setEventLogPath(eventFolder+"\\");
		else
		{
			switch(ret)
			{
			case -1:
				MessageBox("config �ļ�·��Ϊ�գ�");
				break;
			case -2:
				MessageBox("config �ļ������ڣ�");
				break;
			case -3:
				MessageBox("pugixml ���� config.xml �ļ�ʧ�ܣ�");
				break;
			}

			((CButton *)GetDlgItem(IDC_BUTTON_START_ALL))->EnableWindow(FALSE);
		}

	}

	initListCtrl();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMonitorSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMonitorSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMonitorSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMonitorSystemDlg::OnBnClickedButtonStartAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_monitorManager.startAll();

	int nCount = m_monitorList.GetItemCount();//��ȡ��ǰ�Ѳ��������
	for(int i=0;i<nCount;i++)
		m_monitorList.SetItemText(i, 1, "������");
}

void CMonitorSystemDlg::OnBnClickedButtonStopAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_monitorManager.stopAll();

	int nCount = m_monitorList.GetItemCount();//��ȡ��ǰ�Ѳ��������
	for(int i=0;i<nCount;i++)
		m_monitorList.SetItemText(i, 1, "��ֹͣ");
}

void CMonitorSystemDlg::initListCtrl()
{
	////��ʼ������
	LONG lStyle;
	lStyle = GetWindowLong(m_monitorList.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_monitorList.m_hWnd, GWL_STYLE, lStyle);//����style
	DWORD styles=m_monitorList.GetExtendedStyle();  
	m_monitorList.SetExtendedStyle(styles|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	//�����
	m_monitorList.InsertColumn(0, _T("��������"),LVCFMT_CENTER, 80);//������
	m_monitorList.InsertColumn(1,_T("�����״̬"),LVCFMT_CENTER,90);        
	m_monitorList.InsertColumn(2,_T("��ѯ���(��)"),LVCFMT_CENTER,90);        
	m_monitorList.InsertColumn(3,_T("���κ󱨾�"),LVCFMT_CENTER,90);    
	m_monitorList.InsertColumn(4,_T("��ض�������"),LVCFMT_CENTER, 90);
	m_monitorList.InsertColumn(5,_T("��ض���״̬"),LVCFMT_CENTER, 90);

	for(int i=0;i<(int)m_monitorManager.size();i++)
	{
		CMonitor *monitor=m_monitorManager.at(i);
		if(!monitor)
			continue;

		stringstream ss;
		int nCount = m_monitorList.GetItemCount();//��ȡ��ǰ�Ѳ��������
		ss << i;
		m_monitorList.InsertItem(nCount, _T(""));//����һ��
		m_monitorList.SetItemText(nCount, 0, ss.str().c_str());//��һ��
		ss.clear();
		ss.str("");
		m_monitorList.SetItemText(nCount, 1, "δ����");//�ڶ���
		ss << monitor->Interval;
		m_monitorList.SetItemText(nCount, 2, ss.str().c_str());//������
		ss.clear();
		ss.str("");
		ss << monitor->Times;
		m_monitorList.SetItemText(nCount, 3, ss.str().c_str());//������
		ss.clear();
		ss.str("");
		m_monitorList.SetItemText(nCount, 4, monitor->MonitedObject->Type.c_str());//������
		m_monitorList.SetItemText(nCount, 5, monitor->MonitedObject->Status.c_str());//������

	}
}

void CMonitorSystemDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_CLOSE);
}

void CMonitorSystemDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int ret=MessageBox("ȷʵҪ�˳���", "ѯ��", MB_OKCANCEL);
	if(ret==1)
		CDialog::OnClose();
}

void CMonitorSystemDlg::OnNMClickListMonitorInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex=m_monitorList.GetSelectionMark();//��ȡѡ�е���
	if(nIndex>=0 && nIndex<(int)m_monitorManager.size())
	{
		CMonitor *monitor=m_monitorManager.at(nIndex);
		if(monitor)
		{
			m_monitorDetails=monitor->toString().c_str();

			CString log="";
			CStdioFile file;
			if(file.Open(monitor->getEventLogFile().c_str(), CFile::modeRead | CFile::shareDenyNone))
			{
				CString tmp="";
				while(file.ReadString(tmp)!=NULL)
				{
					log+=tmp+"\r\n";
				}
			}
			m_txtLog.SetWindowText(log);
			m_txtLog.SetSel(log.GetLength(),log.GetLength());

			file.Close();

			UpdateData(FALSE);
		}
	}

	*pResult = 0;
}

void CMonitorSystemDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlg;
	dlg.DoModal();
}
