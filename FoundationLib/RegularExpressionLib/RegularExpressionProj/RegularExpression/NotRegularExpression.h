// NotRegularExpression.h: interface for the CNotRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTREGULAREXPRESSION_H__345819BF_BEDF_4B07_9278_4E90EE56D956__INCLUDED_)
#define AFX_NOTREGULAREXPRESSION_H__345819BF_BEDF_4B07_9278_4E90EE56D956__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\REGULAREXPRESSION\IRegularExpression.h"

class CNotRegularExpression : public IRegularExpression  
{
public:
	CNotRegularExpression(IRegularExpression *re);
	virtual ~CNotRegularExpression();

	// ch �ַ��Ƿ���ϸ�������ʽ
	virtual BOOL accept(char *ch);;

private:
	CNotRegularExpression();

private:
	IRegularExpression *m_re;
};

#endif // !defined(AFX_NOTREGULAREXPRESSION_H__345819BF_BEDF_4B07_9278_4E90EE56D956__INCLUDED_)
