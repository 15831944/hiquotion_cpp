// Shortcut.h: interface for the CShortcut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHORTCUT_H__0C471C15_2FB6_456E_8AA7_2428A610B6CB__INCLUDED_)
#define AFX_SHORTCUT_H__0C471C15_2FB6_456E_8AA7_2428A610B6CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShortcut  
{
public:
	CShortcut();
	virtual ~CShortcut();

	/*

	�ر�˵��������ǰ��Ҫ����
	
	CoInitialize(NULL);
	
	����֮����Ҫ����

	CoUninitialize();

	�������������ڳ�����غͳ����˳�ʱ�ֱ���á�

	**************

	�������ܣ���ָ���ļ���ָ����Ŀ¼�´������ݷ�ʽ

	����������
	lpszFileFullPath    ָ���ļ���ΪNULL��ʾ��ǰ���̵�EXE�ļ���
	lpszLnkFileDir  ָ��Ŀ¼������ΪNULL��
	lpszLnkFileName ��ݷ�ʽ���ƣ�ΪNULL��ʾEXE�ļ�����.EXE����.LNK�滻����
	wHotkey         Ϊ0��ʾ�����ÿ�ݼ�
	pszDescription  ��ע
	iShowCmd        ���з�ʽ��Ĭ��Ϊ���洰��

    ��ݼ�˵����
  ��λ����virtual key code����λ�Ͽ�����ALT,CTRL����ϼ���������MAKEWORD(low, high)������һ��WORD����Ctrl+F12������MAKEWORD(VK_F12, HOTKEYF_CONTROL)��ʾ��
  
	ALT,CTRL����ϼ���
  HOTKEYF_ALT       ALT key 
  HOTKEYF_CONTROL   CTRL key 
  HOTKEYF_EXT       Extended key 
  HOTKEYF_SHIFT     SHIFT key 

	*/
	static BOOL createFileShortcut(LPCSTR lpszFileFullPath, LPCSTR lpszLnkFileDir, LPCSTR lpszLnkFileName="", LPCSTR lpszArguments="", LPCSTR lpszWorkDir="", WORD wHotkey=0, LPCTSTR lpszDescription="", int iShowCmd = SW_SHOWNORMAL);
};

#endif // !defined(AFX_SHORTCUT_H__0C471C15_2FB6_456E_8AA7_2428A610B6CB__INCLUDED_)
