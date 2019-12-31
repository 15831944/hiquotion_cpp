#include "StdAfx.h"
#include "PEImporterTable.h"
#include <Dbghelp.h> //ImageRvaToVa
#pragma comment(lib, "dbghelp.lib")

CPEImporterTable::CPEImporterTable(void)
{
}


CPEImporterTable::~CPEImporterTable(void)
{
}

int CPEImporterTable::getImporterTable(string file, ImporterTable &dllTable)
{
	m_errMsg="";
	dllTable.clear();

	if(file.length()<=0 || file.size()<=0)
	{
		m_errMsg="�ļ���Ϊ�գ�";
		return -1;
	}

	HANDLE hFile = CreateFile(
//		"F:\\vs.exe", //PE�ļ���
//		"F:\\adhapi.dll", //PE�ļ���
		file.c_str(),
		GENERIC_READ, 
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		m_errMsg="���ļ�ʧ�ܣ�";
		return -2;
	}

	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY,    0, 0, NULL);
	if (hFileMapping == NULL || hFileMapping == INVALID_HANDLE_VALUE) 
	{ 
		m_errMsg="Could not create file mapping object.\n";
		return -3;
	}

	LPBYTE lpBaseAddress = (LPBYTE)MapViewOfFile(hFileMapping,   // handle to map object
		FILE_MAP_READ, 0, 0, 0);
	if (lpBaseAddress == NULL) 
	{ 
		m_errMsg="Could not map view of file."; 
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return -4;
	}

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		m_errMsg="NOT PE file!"; 
		UnmapViewOfFile(lpBaseAddress);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		return -5;
	}

	PIMAGE_NT_HEADERS32 pNtHeaders = (PIMAGE_NT_HEADERS32)(lpBaseAddress + pDosHeader->e_lfanew);
	if(pNtHeaders->FileHeader.Machine!=IMAGE_FILE_MACHINE_I386)
	{
		if (pNtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_IA64 || pNtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64)
		{
			int ret=getImporterTable64(pNtHeaders, lpBaseAddress, dllTable);
			if(ret==0)
				return 0;
			else if(ret<0)
			{
				//m_errMsg �ɺ���getImporterTable64����
				UnmapViewOfFile(lpBaseAddress);
				CloseHandle(hFileMapping);
				CloseHandle(hFile);
				return -100-ret;
			}
		}
		else
		{
			m_errMsg="NOT 32bit file, NOT 64bit file!";
			return -6;
		}
	}

	//������rva��0x2a000;
	DWORD Rva_import_table = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	if(Rva_import_table == 0)
	{
		m_errMsg="no import table!";
		//�ر��ļ����������
		UnmapViewOfFile(lpBaseAddress);
		CloseHandle(hFileMapping);
		CloseHandle(hFile);
		//getchar();
		return -7;
//				goto UNMAP_AND_EXIT;
	}

	//�����Ȼ���ڴ��ַ�����Ǽ�ȥ�ļ���ͷ�ĵ�ַ�������ļ���ַ��
	//�����ַ����ֱ�Ӵ������ȡ����Ҫ�Ķ�����
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)ImageRvaToVa(
		pNtHeaders, 
		lpBaseAddress, 
		Rva_import_table,
		NULL
		);

	//��ȥ�ڴ�ӳ����׵�ַ�������ļ���ַ�ˡ������ܼ򵥰ɣ�
	//printf("FileAddress Of ImportTable: %p\n", ((DWORD)pImportTable - (DWORD)lpBaseAddress));

	//���������˵�������ǰ��IMAGE_IMPORT_DESCRIPTOR ���飨��0Ԫ��Ϊ��ֹ��
	//�����ʾ�����β��nullԪ�أ�
	IMAGE_IMPORT_DESCRIPTOR null_iid;
	IMAGE_THUNK_DATA null_thunk;
	memset(&null_iid, 0, sizeof(null_iid));
	memset(&null_thunk, 0, sizeof(null_thunk));

	int i,j;
	//ÿ��Ԫ�ش�����һ�������DLL��
	for(i=0; memcmp(pImportTable + i, &null_iid, sizeof(null_iid))!=0; i++)
	{
		//LPCSTR: ���� const char*
		LPCSTR szDllName = (LPCSTR)ImageRvaToVa(
			pNtHeaders, lpBaseAddress, 
			pImportTable[i].Name, //DLL���Ƶ�RVA
			NULL);

		IMPORTED_Dll *dll=new IMPORTED_Dll;
		dll->dllName=szDllName;

		////�õ���DLL������
		//printf("-----------------------------------------\n");
		//printf("[%d]: %s\n", i, szDllName);
		//printf("-----------------------------------------\n");

		//����ȥ�����Ӹ�DLL����������Щ����
		//����������DLL�� IMAGE_TRUNK_DATA ���飨IAT�������ַ��ǰ��
		PIMAGE_THUNK_DATA32 pThunk = (PIMAGE_THUNK_DATA32)ImageRvaToVa(
			pNtHeaders, lpBaseAddress,
			pImportTable[i].OriginalFirstThunk, //��ע�⡿����ʹ�õ���OriginalFirstThunk
			NULL);

		for(j=0; memcmp(pThunk+j, &null_thunk, sizeof(null_thunk))!=0; j++)
		{
			IMPORTED_FUNCTION *func=new IMPORTED_FUNCTION;

			//����ͨ��RVA�����λ�жϺ����ĵ��뷽ʽ��
			//������λΪ1������ŵ��룬�������Ƶ���
			if(pThunk[j].u1.AddressOfData & IMAGE_ORDINAL_FLAG32)
			{
				func->no=pThunk[j].u1.AddressOfData & 0xffff;
				//printf("\t [%d] \t %ld \t ����ŵ���\n", j, pThunk[j].u1.AddressOfData & 0xffff);
			}
			else
			{
				//�����Ƶ��룬�����ٴζ��򵽺�����ź�����
				//ע�����ַ����ֱ���ã���Ϊ��Ȼ��RVA��
				PIMAGE_IMPORT_BY_NAME pFuncName = (PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(
					pNtHeaders,    lpBaseAddress,
					pThunk[j].u1.AddressOfData,
					NULL);
                
				func->no=pFuncName->Hint;
				func->funcName=(char *)pFuncName->Name;
				//printf("\t [%d] \t %ld \t %s\n", j, pFuncName->Hint, pFuncName->Name);
			}

			dll->funcNames.push_back(func);
		}

		dllTable.dllNames.push_back(dll);
	}

	return 0;
}

int CPEImporterTable::getImporterTable64(PIMAGE_NT_HEADERS pNtHeaders, LPBYTE lpBaseAddress, ImporterTable &dllTable)
{
	//������rva��0x2a000;
	PIMAGE_NT_HEADERS64 pNtHeaders64=(PIMAGE_NT_HEADERS64)pNtHeaders;
	DWORD Rva_import_table = pNtHeaders64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	if(Rva_import_table == 0)
	{
		m_errMsg="no import table(64 bit)!";
		//�ر��ļ����������
		//getchar();
		return -7;
//				goto UNMAP_AND_EXIT;
	}

	//�����Ȼ���ڴ��ַ�����Ǽ�ȥ�ļ���ͷ�ĵ�ַ�������ļ���ַ��
	//�����ַ����ֱ�Ӵ������ȡ����Ҫ�Ķ�����
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)ImageRvaToVa(
		pNtHeaders, 
		lpBaseAddress, 
		Rva_import_table,
		NULL
		);

	//��ȥ�ڴ�ӳ����׵�ַ�������ļ���ַ�ˡ������ܼ򵥰ɣ�
	//printf("FileAddress Of ImportTable: %p\n", ((DWORD)pImportTable - (DWORD)lpBaseAddress));

	//���������˵�������ǰ��IMAGE_IMPORT_DESCRIPTOR ���飨��0Ԫ��Ϊ��ֹ��
	//�����ʾ�����β��nullԪ�أ�
	IMAGE_IMPORT_DESCRIPTOR null_iid;
	IMAGE_THUNK_DATA64 null_thunk;
	memset(&null_iid, 0, sizeof(null_iid));
	memset(&null_thunk, 0, sizeof(null_thunk));

	int i,j;
	//ÿ��Ԫ�ش�����һ�������DLL��
	for(i=0; memcmp(pImportTable + i, &null_iid, sizeof(null_iid))!=0; i++)
	{
		//LPCSTR: ���� const char*
		LPCSTR szDllName = (LPCSTR)ImageRvaToVa(
			pNtHeaders, lpBaseAddress, 
			pImportTable[i].Name, //DLL���Ƶ�RVA
			NULL);

		IMPORTED_Dll *dll=new IMPORTED_Dll;
		dll->dllName=szDllName;

		////�õ���DLL������
		//printf("-----------------------------------------\n");
		//printf("[%d]: %s\n", i, szDllName);
		//printf("-----------------------------------------\n");

		//����ȥ�����Ӹ�DLL����������Щ����
		//����������DLL�� IMAGE_TRUNK_DATA ���飨IAT�������ַ��ǰ��
		PIMAGE_THUNK_DATA64 pThunk = (PIMAGE_THUNK_DATA64)ImageRvaToVa(
			pNtHeaders, lpBaseAddress,
			pImportTable[i].OriginalFirstThunk, //��ע�⡿����ʹ�õ���OriginalFirstThunk
			NULL);

		for(j=0; memcmp(pThunk+j, &null_thunk, sizeof(null_thunk))!=0; j++)
		{
			IMPORTED_FUNCTION *func=new IMPORTED_FUNCTION;

			//����ͨ��RVA�����λ�жϺ����ĵ��뷽ʽ��
			//������λΪ1������ŵ��룬�������Ƶ���
			if(pThunk[j].u1.AddressOfData & IMAGE_ORDINAL_FLAG64)
			{
				func->no=pThunk[j].u1.AddressOfData & 0xffff;
				//printf("\t [%d] \t %ld \t ����ŵ���\n", j, pThunk[j].u1.AddressOfData & 0xffff);
			}
			else
			{
				//�����Ƶ��룬�����ٴζ��򵽺�����ź�����
				//ע�����ַ����ֱ���ã���Ϊ��Ȼ��RVA��
				PIMAGE_IMPORT_BY_NAME pFuncName = (PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(
					pNtHeaders,    lpBaseAddress,
					pThunk[j].u1.AddressOfData,
					NULL);
                
				func->no=pFuncName->Hint;
				func->funcName=(char *)pFuncName->Name;
				//printf("\t [%d] \t %ld \t %s\n", j, pFuncName->Hint, pFuncName->Name);
			}

			dll->funcNames.push_back(func);
		}

		dllTable.dllNames.push_back(dll);
	}

	return 0;
}
