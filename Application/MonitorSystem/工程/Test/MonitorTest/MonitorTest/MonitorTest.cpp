// MonitorTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MonitorTest.h"
#include <FileSysLib\FolderOperation.h>
#include <PugiXmlLib\pugixml.hpp>
#include <sstream>
#include "imonitedobject.h"
#include "Alertor.h"
#include "monitor.h"
#include "monitedobjectcreator.h"

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
	 	CString file=CFolderOperation::addGang(CFolderOperation::GetModulePath())+"config.xml";
	 	pugi::xml_document doc;
	 	pugi::xml_parse_result result=doc.load_file((LPTSTR)(LPCSTR)file);
	 	if (result.status!=pugi::status_ok)
	 	{
	 		return -1;
	 	}
		
	 	pugi::xml_node node = doc.child("MonitorSystem").child("Monitor");
	 	std::string sinterval = node.attribute("interval").value();
		int interval=0;
		stringstream ss;
		ss<< sinterval;
		ss>> interval;
		
		if(interval<=0)
			interval=60;

		std::string stimes = node.attribute("times").value();
		int times=0;
		ss.clear();
		ss<< stimes;
		ss>> times;

		if(times<=0)
			times=1;

		pugi::xml_node nodeObj = node.child("MonitedObject");
		string stype = nodeObj.attribute("type").value();
		string status = nodeObj.attribute("status").value();

		IMonitedObject *obj=CMonitedObjectCreator::create(stype, status);
		if(obj==NULL)
			return -2;

		if(!obj->readConfig(nodeObj))
			return -3;

		pugi::xml_node nodeAlertor = node.child("Alertor");

		CAlertor alertor;
		if(!alertor.readConfig(node))
			return -4;

		CMonitor monitor(obj, &alertor, interval, times);
		if(!monitor.start())
			return -5;
	}

	return nRetCode;
}
