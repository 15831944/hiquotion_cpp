// XmlOperation.cpp: implementation of the CXmlOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXmlOperation::CXmlOperation(string path) : m_root(NULL)
{
	if(m_doc.LoadFile(path.c_str()))
	{
		m_isOpen=true;
		m_root=m_doc.RootElement();
	}	
	else
		m_isOpen=false;
}

CXmlOperation::~CXmlOperation()
{

}

// ��ȡ���ڵ�
TiXmlElement *CXmlOperation::getRoot()
{
	if(m_isOpen)
		return m_doc.RootElement();
	else
		return NULL;
}

// ��ȡָ���ڵ���ӽڵ���ָ���ڵ����е�ָ��������=����ֵ�Ľڵ㡣
// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
// ���ؿգ������ʧ��
TiXmlElement *CXmlOperation::getElement(TiXmlElement* element,std::string nodeName,std::string attributeName,std::string attributeValue)
{
	if(!m_isOpen)
		return NULL;
	
	if(!element)
		return NULL;

	TiXmlElement* pEle = NULL;
	for (pEle = element->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
    {
		if (pEle->Value()==nodeName)
		{
			// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
			if(attributeName=="")
				return pEle;
			else
			{
				string attribute="";
				attribute=pEle->Attribute(attributeName.c_str());
				// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
				if(attributeValue=="")
				{
					// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
					if(attribute!="")
						return pEle;
				}
				else
				{
					// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
					if(attribute==attributeValue)
						return pEle;
				}
			}
		}
	}
	return NULL;
}

// ��ȡ���ڵ���ӽڵ���ָ���ڵ����е�ָ��������=����ֵ�Ľڵ㡣
// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
// ���ؿգ������ʧ��
TiXmlElement *CXmlOperation::getElement(std::string nodeName,std::string attributeName,std::string attributeValue)
{
	if(!m_isOpen)
		return NULL;

	return getElement(m_root,nodeName,attributeName,attributeValue);
}

// �ȸ�������������ȡָ���ڵ����е�ָ��������=����ֵ�Ľڵ㡣
// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
// ���ؿգ������ʧ��
TiXmlElement *CXmlOperation::getElementInSubtree(TiXmlElement* subRoot,std::string nodeName,std::string attributeName,std::string attributeValue)
{
	if(!m_isOpen)
		return NULL;

	if(!subRoot)
		return NULL;

	// ������ڸ��ڵ��������˳�
	if (subRoot->Value()==nodeName)
	{
		// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
		if(attributeName=="")
			return subRoot;
		else
		{
			string attribute="";
			attribute=subRoot->Attribute(attributeName.c_str());
			// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
			if(attributeValue=="")
			{
				// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
				if(attribute!="")
					return subRoot;
			}
			else
			{
				// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
				if(attribute==attributeValue)
					return subRoot;
			}
		}
	}
	TiXmlElement* element = NULL;
	for (element = subRoot->FirstChildElement(); element; element = element->NextSiblingElement())
	{
		//�ݹ鴦���ӽڵ㣬��ȡ�ڵ�ָ��
		TiXmlElement *retElement=getElementInSubtree(element,nodeName,attributeName,attributeValue);
		if(retElement)
			return retElement;
	}

	return NULL;
}

// �ȸ���������������ȡָ���ڵ����е�ָ��������=����ֵ�Ľڵ㡣
// ���������Ϊ�գ��򲻿������Ե����أ����ص�ǰԪ��
// �������ֵΪ�գ�����Ҿ���ָ����������Ԫ��
// �����������������ֵ���գ����ҵ��ˣ�����������������ڵ�
// �������ֵ���գ�����������=����ֵ���򷵻أ�����������������ڵ�
// ���ؿգ������ʧ��
TiXmlElement *CXmlOperation::getElementInSubtree(std::string nodeName,std::string attributeName,std::string attributeValue)
{
	if(!m_isOpen)
		return NULL;

	return getElementInSubtree(m_root,nodeName,attributeName,attributeValue);
}

// ��ȡָ���ڵ���ı�
string CXmlOperation::getElementText(TiXmlElement *element)
{
	if(!m_isOpen)
		return "";

	if(!element)
		return "";

	TiXmlNode *text=element->FirstChild();
	if(!text)
		return "";

	return text->Value();
}

// ��ȡָ���ڵ��ָ���������Ƶ�����ֵ
string CXmlOperation::getElementAttribute(TiXmlElement *element,string propertyName)
{
	if(!m_isOpen)
		return "";
	
	if(!element)
		return "";
	
	const char *attribute=element->Attribute(propertyName.c_str());
	if(!attribute)
		return "";

	string propertyValue=attribute;
	return propertyValue;
}
