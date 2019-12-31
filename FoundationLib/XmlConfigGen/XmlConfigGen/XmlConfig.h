#pragma once
#include <string>
#include <C++/FoundationLib/DataStructLib/PointerList.h>
#include <C++\3rdParty\PugiXmlLib\pugixml.hpp>
#include <C++\foundationLib\DataStructLib\ValueList.h>

struct XmlConfigNodeProperty
{
	std::string name;
	std::string type;
};

struct XmlConfigNode
{
	std::string gentype;	// ��������
							// valuable��ʾÿ��property�����ԣ������ɱ�����pusher_ip��pusher_port��
							// struct��ʾ���ɽṹ�壬ip��portΪpusher�ṹ���еı���
	std::string name;    // gentype �����ƣ�����gentype��struct��name��config��������� struct config�Ĵ���
	std::string location;
	CPointerList<XmlConfigNodeProperty*> properties;
	CPointerList<XmlConfigNode*> nodes;

	std::string generatedStructor;
	std::string generatedOperationLoad;
	std::string generatedOperationSave;
};

struct XmlConfig
{
	std::string gentype; // value="struct"/"class"
	std::string name;    // gentype �����ƣ�����gentype��struct��name��config��������� struct config�Ĵ���
	CPointerList<XmlConfigNode*> nodes;
};

class CXmlClassGenerator
{
public:
	CXmlClassGenerator();
	~CXmlClassGenerator();
	
	int parseNode(pugi::xml_node current, XmlConfigNode *configNode );
	int loadConfigXmlFile(std::string fileName);
	std::string genConfigOperation();

private:
	std::string genWholeStructor();
	std::string genWholeImpl();

	std::string genStructor(XmlConfigNode* node);
	std::string genLoadOperation(XmlConfigNode* node);
	std::string genSaveOperation(XmlConfigNode* node);

	std::string list2string(CValueList<std::string> lines, std::string saperator="\n");

private:
	XmlConfig m_config;

	std::string generatedWholeStructor;
	std::string generatedWholeImpl;
};
