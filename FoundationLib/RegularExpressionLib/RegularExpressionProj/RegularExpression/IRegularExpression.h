// IRegularExpression.h: interface for the INormalExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IREGULAREXPRESSION_H__0C300E2A_827D_49C5_8E76_7A01390DB7DE__INCLUDED_)
#define AFX_IREGULAREXPRESSION_H__0C300E2A_827D_49C5_8E76_7A01390DB7DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include "..\..\..\DataStructLib\Graph\DiGraphProj\StatusGraphic.h"
// #include "..\CharChecker\ICharChecker.h"

// ������ʽ�ӿ�
class IRegularExpression  
{
public:
	IRegularExpression(){};
	virtual ~IRegularExpression(){};

// 	virtual CStatusGraphic *genStatusGraphic(){return NULL;}

// 	virtual ICharChecker *getChecker(){return NULL;}

	// ch �ַ��Ƿ���ϸ�������ʽ
	virtual BOOL accept(char *ch){ return FALSE;};
};

#endif // !defined(AFX_IREGULAREXPRESSION_H__0C300E2A_827D_49C5_8E76_7A01390DB7DE__INCLUDED_)
