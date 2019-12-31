// TLV.h: interface for the CTLV class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLV_H__3B11192D_74BF_48F4_ABC1_B56FAB2B88B1__INCLUDED_)
#define AFX_TLV_H__3B11192D_74BF_48F4_ABC1_B56FAB2B88B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Tag Length Value ��
// ������������ʽʹ���� Value
// һ���ǽ�ԭ���ݸ��Ƶ� m_valueNew ������
// ��һ����ֱ��ʹ��ԭ���ݵ���ʼ��ַ���� m_value
// ͨ�� m_isUseValueNew ���ж�ʹ�����ֵ�����
class CTLV  
{
public:
	CTLV(short tag, int length, char *value, BOOL isUseValueNew=FALSE);
	virtual ~CTLV();

	char getTag() const { return m_tag; }
	void setTag(char val) { m_tag = val; }

	int getLength() const { return m_length; }

	char * getValue();
	void setValue(char *val, int length, BOOL isUseValueNew);

protected:
	short m_tag;
	int m_length;
	char *m_value;
	char *m_valueNew;

	BOOL m_isUseValueNew;
};

#endif // !defined(AFX_TLV_H__3B11192D_74BF_48F4_ABC1_B56FAB2B88B1__INCLUDED_)
