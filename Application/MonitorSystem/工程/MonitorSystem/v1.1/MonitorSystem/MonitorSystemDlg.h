// MonitorSystemDlg.h : ͷ�ļ�
//

#pragma once

#include "monitorlib\monitormanager.h"
#include "afxcmn.h"
#include "afxwin.h"

// CMonitorSystemDlg �Ի���
class CMonitorSystemDlg : public CDialog
{
// ����
public:
	CMonitorSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MONITORSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void initListCtrl();

private:
	CMonitorManager m_monitorManager;
	CString m_appPath;
public:
	afx_msg void OnBnClickedButtonStartAll();
	afx_msg void OnBnClickedButtonStopAll();
	CListCtrl m_monitorList;
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnClose();
//	afx_msg void OnLvnItemchangedListMonitorInfo(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_monitorDetails;
	afx_msg void OnNMClickListMonitorInfo(NMHDR *pNMHDR, LRESULT *pResult);
// 	CString m_eventLogString;
	CEdit m_txtLog;
	afx_msg void OnBnClickedButton1();
};
