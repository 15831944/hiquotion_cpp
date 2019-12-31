#pragma once

#include <string>
#include <vector>
using namespace std;

class CStringExt
{
public:
	CStringExt(void);
	~CStringExt(void);

	static void Split(CString source, CStringArray& dest, CString division);
	static void Split(CStringArray *splitStrings, CHAR *buffer, DWORD size, CHAR find);
	static CString Capital(CString str);  // ����ĸ��д
	static CString camel(CString str);    // ����ĸСд
	// ȡ c ��ߵ��ַ���
	// ���û�� c���򷵻�ȫ���ַ���
	// mode>0������������ң�modeС��0�������������
	// modeֵ��ʾ�ҵ��ڼ���Ϊֹ��modeĬ��ֵΪ1�������������ҵ���1��Ϊֹ
	// ���modeΪ0������Ϊmode����1��
// 	static CString stringLeft(CString str, char c, int mode=1);
	// ȡ subStr �ұߵ��ַ���
	// ���û�� subStr���򷵻�ȫ���ַ���
	static BOOL stringRight(CString str, CString subStr, CString &dst, int mode=1);

	static void string_replace(string&s1,const string&s2,const string&s3);

#if _MSC_VER  >  1200   // greater than vc6
	static char* wideChartoMultiByte(const wchar_t* wp);
	static wchar_t* multiBytetoWideChar(const char* c);
	static std::wstring utf8toWideChar(const char* buf);
	static std::string wideChartoUTF8(const wchar_t* buf);

#endif

};
