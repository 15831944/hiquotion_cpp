// XmlOperation.h: interface for the CXmlOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLOPERATION_H__EB0258EF_638E_46E2_8551_6DFF4BB1D6EF__INCLUDED_)
#define AFX_XMLOPERATION_H__EB0258EF_638E_46E2_8551_6DFF4BB1D6EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tinyxml.h"
#include <string>

class CXmlOperation  
{
public:
	CXmlOperation(std::string path);
	virtual ~CXmlOperation();

	// ��ȡ���ڵ�
	TiXmlElement *getRoot();

	bool isOpenSuccess() const { return m_isOpen; }

	// ��ȡָ���ڵ���ӽڵ���ָ���ڵ����е�ָ��������=����ֵ�Ľڵ㡣
	// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
	// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
	// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
	// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
	// ���ؿգ������ʧ��
	TiXmlElement *getElement(TiXmlElement* element,std::string nodeName,std::string attributeName="",std::string attributeValue="");

	// ��ȡ���ڵ���ӽڵ���ָ���ڵ����е�ָ��������=����ֵ�Ľڵ㡣
	// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
	// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
	// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
	// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
	// ���ؿգ������ʧ��
	TiXmlElement *getElement(std::string nodeName,std::string attributeName="",std::string attributeValue="");

	// �ȸ�������������ȡָ���ڵ����е�ָ��������=����ֵ�Ľڵ㡣
	// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
	// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
	// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
	// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
	// ���ؿգ������ʧ��
	TiXmlElement *getElementInSubtree(TiXmlElement* subRoot,std::string nodeName,std::string attributeName="",std::string attributeValue="");

	// �ȸ���������������ȡָ���ڵ����е�ָ��������=����ֵ�Ľڵ㡣
	// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
	// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
	// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
	// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
	// ���ؿգ������ʧ��
	TiXmlElement *getElementInSubtree(std::string nodeName,std::string attributeName="",std::string attributeValue="");

	// ��ȡָ���ڵ���ı�
	std::string getElementText(TiXmlElement *element);
	// ��ȡָ���ڵ��ָ���������Ƶ�����ֵ
	std::string getElementAttribute(TiXmlElement *element, std::string propertyName);

	// ����Ԫ�ص����Կ���ʹ��Ԫ�ر����SetAttribute������

private:
	TiXmlDocument m_doc;
	TiXmlElement *m_root;
	bool m_isOpen;
};

#endif // !defined(AFX_XMLOPERATION_H__EB0258EF_638E_46E2_8551_6DFF4BB1D6EF__INCLUDED_)
