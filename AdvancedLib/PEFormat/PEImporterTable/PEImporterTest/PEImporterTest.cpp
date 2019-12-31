// PEImporterTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PEImporterTest.h"
#include <Dbghelp.h> //ImageRvaToVa
#include "PEImporterTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			CPEImporterTable table;
			ImporterTable names;
			int ret=table.getImporterTable(
				"F:\\vs.exe",
//				"F:\\adhapi.dll", //PE�ļ���
				names);
			printf("ret=%d\n", ret);

			for(int i=0;i<names.dllNames.size();i++)
			{
				printf("DLL name: %s\n", names.dllNames[i]->dllName.c_str());

				for(int j=0;j<names.dllNames[i]->funcNames.size();j++)
				{
					if(names.dllNames[i]->funcNames[j]->funcName.size()<=0)
						printf("\tFUNC no:%d (��ͨ�������ŵ���)\n", names.dllNames[i]->funcNames[j]->no, names.dllNames[i]->funcNames[j]->funcName.c_str());
					else
						printf("\tFUNC no:%d\t name: %s\n", names.dllNames[i]->funcNames[j]->no, names.dllNames[i]->funcNames[j]->funcName.c_str());
				}
			}
//			int i, j;
//			HANDLE hFile = CreateFile(
////				"F:\\vs.exe", //PE�ļ���
//				"F:\\adhapi.dll", //PE�ļ���
//				GENERIC_READ, 
//				FILE_SHARE_READ,
//				NULL,
//				OPEN_EXISTING,
//				FILE_ATTRIBUTE_NORMAL,
//				NULL);
//
//			if(hFile == INVALID_HANDLE_VALUE)
//			{
//				printf("Create File Failed.\n");
//				return 0;
//			}
//
//			HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY,    0, 0, NULL);
//
//			if (hFileMapping == NULL || hFileMapping == INVALID_HANDLE_VALUE) 
//			{ 
//				printf("Could not create file mapping object (%d).\n", GetLastError());
//				return 0;
//			}
//
//			LPBYTE lpBaseAddress = (LPBYTE)MapViewOfFile(hFileMapping,   // handle to map object
//				FILE_MAP_READ, 0, 0, 0);
// 
//			if (lpBaseAddress == NULL) 
//			{ 
//				printf("Could not map view of file (%d).\n", GetLastError()); 
//				return 0;
//			}
//
//			PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
//			PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)(lpBaseAddress + pDosHeader->e_lfanew);
//  			PIMAGE_NT_HEADERS64 pNtHeaders64 = (PIMAGE_NT_HEADERS64)(lpBaseAddress + pDosHeader->e_lfanew);
//  
//			//if(pNtHeaders->FileHeader.Machine!=IMAGE_FILE_MACHINE_I386)
//			//{
//			//	printf("NOT 32bit file!\n");
//			//	system("pause");
//			//	return 0;
//			//}
//
//			//������rva��0x2a000;
//			DWORD Rva_import_table = pNtHeaders64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
//
//			if(Rva_import_table == 0)
//			{
//				printf("no import table!");
//				//�ر��ļ����������
//				UnmapViewOfFile(lpBaseAddress);
//				CloseHandle(hFileMapping);
//				CloseHandle(hFile);
//				getchar();
//				return 0;
////				goto UNMAP_AND_EXIT;
//			}
//
//			//�����Ȼ���ڴ��ַ�����Ǽ�ȥ�ļ���ͷ�ĵ�ַ�������ļ���ַ��
//			//�����ַ����ֱ�Ӵ������ȡ����Ҫ�Ķ�����
//			PIMAGE_IMPORT_DESCRIPTOR pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)ImageRvaToVa(
//				pNtHeaders, 
//				lpBaseAddress, 
//				Rva_import_table,
//				NULL
//				);
//
//			//��ȥ�ڴ�ӳ����׵�ַ�������ļ���ַ�ˡ������ܼ򵥰ɣ�
//			printf("FileAddress Of ImportTable: %p\n", ((DWORD)pImportTable - (DWORD)lpBaseAddress));
//
//			//���������˵�������ǰ��IMAGE_IMPORT_DESCRIPTOR ���飨��0Ԫ��Ϊ��ֹ��
//			//�����ʾ�����β��nullԪ�أ�
//			IMAGE_IMPORT_DESCRIPTOR null_iid;
//			IMAGE_THUNK_DATA64 null_thunk;
//			memset(&null_iid, 0, sizeof(null_iid));
//			memset(&null_thunk, 0, sizeof(null_thunk));
//
//			//ÿ��Ԫ�ش�����һ�������DLL��
//			for(i=0; memcmp(pImportTable + i, &null_iid, sizeof(null_iid))!=0; i++)
//			{
//				//LPCSTR: ���� const char*
//				LPCSTR szDllName = (LPCSTR)ImageRvaToVa(
//					pNtHeaders, lpBaseAddress, 
//					pImportTable[i].Name, //DLL���Ƶ�RVA
//					NULL);
//
//				//�õ���DLL������
//				printf("-----------------------------------------\n");
//				printf("[%d]: %s\n", i, szDllName);
//				printf("-----------------------------------------\n");
//
//				//����ȥ�����Ӹ�DLL����������Щ����
//				//����������DLL�� IMAGE_TRUNK_DATA ���飨IAT�������ַ��ǰ��
//				PIMAGE_THUNK_DATA64 pThunk = (PIMAGE_THUNK_DATA64)ImageRvaToVa(
//					pNtHeaders, lpBaseAddress,
//					pImportTable[i].OriginalFirstThunk, //��ע�⡿����ʹ�õ���OriginalFirstThunk
//					NULL);
//
//				for(j=0; memcmp(pThunk+j, &null_thunk, sizeof(null_thunk))!=0; j++)
//				{
//					//����ͨ��RVA�����λ�жϺ����ĵ��뷽ʽ��
//					//������λΪ1������ŵ��룬�������Ƶ���
//					if(pThunk[j].u1.AddressOfData & IMAGE_ORDINAL_FLAG64)
//					{
//						printf("\t [%d] \t %ld \t ����ŵ���\n", j, pThunk[j].u1.AddressOfData & 0xffff);
//					}
//					else
//					{
//						//�����Ƶ��룬�����ٴζ��򵽺�����ź�����
//						//ע�����ַ����ֱ���ã���Ϊ��Ȼ��RVA��
//						PIMAGE_IMPORT_BY_NAME pFuncName = (PIMAGE_IMPORT_BY_NAME)ImageRvaToVa(
//							pNtHeaders,    lpBaseAddress,
//							pThunk[j].u1.AddressOfData,
//							NULL);
//                
//						printf("\t [%d] \t %ld \t %s\n", j, pFuncName->Hint, pFuncName->Name);
//					}
//				}
//			}
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	system("pause");

	return nRetCode;
};

