#pragma once

#include <string>
#include <vector>

using namespace std;


/******************************************************************************
* 
* PE �ļ����뺯����Ϣ�Ļ�ȡ
* 
* ��ȡ���ݣ�
* 
* PE�ļ������DLL�ļ����б�
* ÿ������DLL�ļ��ĵ��뺯���б�
* ÿ�����뺯�����������źͺ����������������Ϊ�գ���ֻ���Ժ����ŵ��룩
* 
******************************************************************************/

struct IMPORTED_FUNCTION
{
	DWORD no;           // ���
	string funcName;  // �����������������Ϊ�գ���Ϊ����ŵ��룩
};

struct IMPORTED_Dll
{
	string dllName;
	vector<IMPORTED_FUNCTION *> funcNames;

	~IMPORTED_Dll()
	{ for each(IMPORTED_FUNCTION *func in funcNames){ delete func; } }
};

struct ImporterTable
{
	vector<IMPORTED_Dll *> dllNames;

	void clear()
	{
		for each(IMPORTED_Dll *dll in dllNames){ delete dll; }
	}

	~ImporterTable()
	{ clear(); }
};

class CPEImporterTable
{
public:
	CPEImporterTable(void);
	~CPEImporterTable(void);

//	int getImporterTable(string file, vector<vector<string > *> &dllNames);
	int getImporterTable(string file, ImporterTable &dllTable);

	string getErrMsg(){ return m_errMsg; };

protected:
	int getImporterTable64(PIMAGE_NT_HEADERS pNtHeaders, LPBYTE lpBaseAddress, ImporterTable &dllTable);

	string m_errMsg;
};

