// IniOperation.cpp: implementation of the CIniOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniOperation.h"
#include <sstream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// char m_fileName[MAX_LEN];

// CIniOperation::CIniOperation(char* iniFileName)
// {
// 	memset(m_fileName, 0x00, MAX_PATH);
// 	memcpy(m_fileName, iniFileName, strlen(iniFileName));
// }

CIniOperation::CIniOperation()
{
	memset(m_fileName, 0x00, MAX_PATH);
	result = new char[MAX_PATH];
// 	className="CIniOperation";
// 	classCode="01";
}

CIniOperation::CIniOperation(string path)
{
	memset(m_fileName, 0x00, MAX_PATH);
	memcpy(m_fileName, (char *)path.c_str(), path.size());
	result = new char[MAX_PATH];
}

CIniOperation::~CIniOperation()
{
	if(result) delete(result);
}

// ��ȡָ����ָ�������ַ���ֵ
char *CIniOperation::getSectionValueString(char *sectionName,char *sectionKey,char *defaultValue)
{
	memset(result, 0x00, MAX_PATH);
	GetPrivateProfileString(sectionName, sectionKey, defaultValue, result, MAX_PATH, m_fileName); 
	return result;

}
// ��ȡָ����ָ��������ֵ
int CIniOperation::getSectionValueInt(char *sectionName,char *sectionKey,int defaultValue)
{
	int iResult = ::GetPrivateProfileInt(sectionName,  sectionKey, defaultValue, m_fileName); 
	return iResult;
}

// ����ָ����ָ������ָ���ַ���ֵ
void CIniOperation::setSectionValueString(char *sectionName,char *sectionKey,char *keyValue)
{
	::WritePrivateProfileString(sectionName,  sectionKey, keyValue, m_fileName);
}
// ����ָ����ָ������ָ����ֵ
void CIniOperation::setSectionValueInt(char *sectionName,char *sectionKey,int keyValue)
{
	stringstream ss;
	ss<<keyValue;
	string svalue=ss.str();
	::WritePrivateProfileString(sectionName,  sectionKey, svalue.c_str(), m_fileName);
}
