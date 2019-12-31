// PugiXmlTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PugiXmlTest.h"
#include "pugixmllib\pugixml.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		std::string strFile = "F:\\����\\��Ŀ\\ʡ���籣������֤��ϵͳ\\������\\�Ǿӱ�\\Monitor\\����\\Test\\PugiXmlTest\\Debug\\config.xml";
		pugi::xml_document doc;
		pugi::xml_parse_result result=doc.load_file(strFile.c_str());
		if (result.status!=pugi::status_ok) 
			return -1;

		pugi::xml_node node = doc.child("MonitorSystem").child("Monitor");
		std::string prop = node.attribute("interval").value();

		string path=node.child("MonitedObject").child_value("Path");

		return 0;
	}

	return nRetCode;
}
