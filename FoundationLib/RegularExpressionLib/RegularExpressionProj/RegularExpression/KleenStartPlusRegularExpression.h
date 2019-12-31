// KleenStartPlusRegularExpression.h: interface for the CKleenStartPlusRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KLEENSTARTPLUSREGULAREXPRESSION_H__BFA270FF_CB88_4EA6_9B7D_A443CFB7B569__INCLUDED_)
#define AFX_KLEENSTARTPLUSREGULAREXPRESSION_H__BFA270FF_CB88_4EA6_9B7D_A443CFB7B569__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRegularExpression.h"

class CKleenStartPlusRegularExpression : public IRegularExpression  
{
public:
	CKleenStartPlusRegularExpression();
	CKleenStartPlusRegularExpression(IRegularExpression *regularExpression);
	virtual ~CKleenStartPlusRegularExpression();

	IRegularExpression * getRegularExpression() const { return m_regularExpression; }
	void setRegularExpression(IRegularExpression * val) { m_regularExpression = val; }

	// ��������ʽ�Ƿ���� ch �ַ�
	virtual BOOL accept(char *ch);
	
private:
	IRegularExpression *m_regularExpression;
};

#endif // !defined(AFX_KLEENSTARTPLUSREGULAREXPRESSION_H__BFA270FF_CB88_4EA6_9B7D_A443CFB7B569__INCLUDED_)
