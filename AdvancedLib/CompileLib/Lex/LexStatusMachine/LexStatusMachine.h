// StatusMachine.h: interface for the CStatusMachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSMACHINE_H__BEB72CE6_E022_4C9C_987C_D3863DC27EE0__INCLUDED_)
#define AFX_STATUSMACHINE_H__BEB72CE6_E022_4C9C_987C_D3863DC27EE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../LexStatusGraph/LexStatusGraph.h"
#include <string>
// #include "StatusGraphLoader.h"
#include "../LexStatusGraph/StatusGraphNode.h"

// ״̬��
// һ��һ���ַ����룬�Ӷ��ж�״̬����״̬
// ����״̬����״̬����ȡ���е��ַ����ַ����ͣ����߻��һ��������Ϣ
// ע����״̬��һ��ֻ�ܻ�ȡһ���ַ�������Դ�롰int a=10;������һ��״̬�����int���ڶ��λ��a���Դ�����
class CLexStatusMachine  
{
public:
	CLexStatusMachine();
	CLexStatusMachine(CLexStatusGraph *graphic);
	virtual ~CLexStatusMachine();

	// �ָ���ʼ״̬����ָ��ʼ״̬
	void init();

	// �Ƿ���ܸ������ַ�
	// 1������
	// 0��������
	// -1����ǰ���ָ��Ϊ��
	int accept(char ch);

	// ��������ĳ�ַ�ʱ���ж��Ƿ��ڽ���״̬
	// 1����
	// 0������
	// -1����ǰ���ָ��Ϊ��
	int isFinalStatus();

	// ��ȡ״̬���е��ַ���
	std::string getString(){return m_string;};

	// ��ȡ״̬�����ַ��������ͣ����������Ե�ǰ��̬��㣩
	std::string getStringType();

	// ��ȡ״̬�����ַ����������ͣ����������Ե�ǰ��̬��㣩
	std::string getStringSubType();

	// ��ȡ״̬��������Ϣ������Ϣ���Է���̬��㣩
	std::string getErrMsg();

	CLexStatusGraph *getGraphic() const { return m_graphic; }
	void setGraphic(CLexStatusGraph *val) { m_graphic = val; }

	int getInitStatus() const { return m_initStatus; }

private:
	CLexStatusGraph *m_graphic;
// 	CStatusGraphLoader m_statusGraphLoader;
	CStatusGraphNode *m_currentNode;

	std::string m_string;

	// ��ʼ��״̬�����������ж��Ƿ��Ǹոճ�ʼ���������� init ֮��Ϊ1��accept�������ַ���֮��Ϊ0
	// ����δ����init����֮ǰ��Ϊ-1
	int m_initStatus;
};

#endif // !defined(AFX_STATUSMACHINE_H__BEB72CE6_E022_4C9C_987C_D3863DC27EE0__INCLUDED_)
