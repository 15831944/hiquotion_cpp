// ILexer.h: interface for the ILexer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILEXER_H__0EC3FDCA_BED5_41F4_82FF_E2656E043F46__INCLUDED_)
#define AFX_ILEXER_H__0EC3FDCA_BED5_41F4_82FF_E2656E043F46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sstream>
#include <string>
#include <C++\FoundationLib\DataStructLib\PointerList.h>

using namespace std;

/*
Token Type & Subtype
	id,                          // ��ʶ����ؼ��֣��ؼ������ⲿ���壩
	number(integer,hex,double),  // ���֣����ͣ�ʮ�����ƣ�˫���ȣ�
	comment(line,block),         // ע�ͣ���ע�ͣ���ע�ͣ�
	alt_meaning,                 // ת���ַ�
	var,                         // ����������%�м��token��
	�����ɴ�ӡ�ַ����������ַ�������ͬ
*/

enum
{
	CheckToken4Statute,
	CheckType4Statute,
};

struct MachineToken
{
	std::string token;
	std::string type;  // ״̬������������
	std::string subtype;  // ״̬��������������
	int startPosition;  // ״̬���еĿ�ʼλ�ã�״̬��ֻ�����ַ��������Ը�λ�ñ�ʾ�ַ���������
	int endPosition;    // ״̬���еĽ���λ��

	int check4Statute;  // ��Լʱ�Ǽ��token���Ǽ�����ͣ��������ͣ���Ĭ���Ǽ��token
	bool isCheckSubtype; // �ڼ�����͵�����£������Ƿ���������

	MachineToken()
	{
		startPosition=-1;
		endPosition=-1;
		check4Statute=CheckToken4Statute;
		isCheckSubtype=false;
	}
	
	std::string toString()
	{
		std::stringstream ss;
		ss << "token[" << token << "], type[" << type << "], startPos[" << startPosition << "], endPos[" << endPosition << "]";
		//		std::string msg=ss.str();
		return ss.str();
	}
};

// struct LexToken
// {
// 	MachineToken token;
// 	
// 	BOOL isKeyword;
// 	BOOL isNumeric;
// 	BOOL isInteger;
// 	BOOL isHex;
// 	
// 	std::string grammerType;  // ����״̬����id���ͣ����﷨������õ������ͣ���id�����⣬��ֵ�� machine_type ��ͬ
// 	int startRow;  // ����״̬���Ŀ�ʼλ�ã��õ��Ŀ�ʼ��
// 	int startCol;  // ����״̬���Ŀ�ʼλ�ã��õ��Ŀ�ʼ��
// 	int endRow;    // ����״̬���Ľ���λ�ã��õ��Ľ�����
// 	int endCol;    // ����״̬���Ľ���λ�ã��õ��Ľ�����
// };

class ILexer  
{
public:
	ILexer(){};
	virtual ~ILexer(){};

	virtual int analyze(string text, CPointerList<MachineToken *> &tokenList, CValueList<string> &errList){ return 0; };
};

#endif // !defined(AFX_ILEXER_H__0EC3FDCA_BED5_41F4_82FF_E2656E043F46__INCLUDED_)
