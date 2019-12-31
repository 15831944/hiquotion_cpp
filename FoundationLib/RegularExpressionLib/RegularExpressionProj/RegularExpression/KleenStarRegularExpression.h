// KleenStarRegularExpression.h: interface for the CKleenStarRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KLEENSTARREGULAREXPRESSION_H__70EF4E1D_DE05_413E_AC8A_08D5528053D9__INCLUDED_)
#define AFX_KLEENSTARREGULAREXPRESSION_H__70EF4E1D_DE05_413E_AC8A_08D5528053D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\StatusGraphic.h"

class CKleenStarRegularExpression : public IRegularExpression  
{
public:
	CKleenStarRegularExpression();
	CKleenStarRegularExpression(IRegularExpression *regularExpression);
	virtual ~CKleenStarRegularExpression();

	IRegularExpression * getRegularExpression() const { return m_regularExpression; }
	void setRegularExpression(IRegularExpression * val) { m_regularExpression = val; }

// 	virtual CStatusGraphic *genStatusGraphic();
	
// 	// ��Ҫ�ⲿ�ͷ�ָ��
// 	virtual ICharChecker *getChecker();
	
	// ��������ʽ�Ƿ���� ch �ַ�
	virtual BOOL accept(char *ch);

private:
	IRegularExpression *m_regularExpression;
};

#endif // !defined(AFX_KLEENSTARREGULAREXPRESSION_H__70EF4E1D_DE05_413E_AC8A_08D5528053D9__INCLUDED_)
