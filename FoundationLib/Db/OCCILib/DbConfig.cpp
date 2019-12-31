// DbConfig.cpp: implementation of the CDbConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DbConfig.h"
#include <C++\FoudationLib\FileSysLib\FolderOperation.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbConfig::CDbConfig(string configFileOrWithFullPath)
{
	section="DB";
	user="name";
	pwd="pwd";
	oraName="oraName";

	m_configFile=configFileOrWithFullPath;

	appPath=CFolderOperation::GetModulePath();
// 	config.setFileName((LPTSTR)(LPCTSTR)(appPath + "\\appconfig.ini"));
	config.setFileName((LPTSTR)(LPCTSTR)(appPath + "\\appconfig.ini"));
}

CDbConfig::~CDbConfig()
{

}

// ��ȡ�û���
char *CDbConfig::getUserName()
{
	return config.getSectionValueString(section,user);
}

// ��ȡ����
char *CDbConfig::getPwd()
{
	return config.getSectionValueString(section,pwd);
}

// ��ȡ���ݿ���
char *CDbConfig::getOraName()
{
	return config.getSectionValueString(section,oraName);
}
