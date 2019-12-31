// IInterfaceManager.h: interface for the IInterfaceManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IUNKOWN_H__EF8D39E7_DAA3_4FB6_9963_5E254EA6159E__INCLUDED_)
#define AFX_IUNKOWN_H__EF8D39E7_DAA3_4FB6_9963_5E254EA6159E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "IInterface.h"

/*
  ���ÿ��dll������getInterfce��ȡIInterfaceManager*�ӿ���
  ����IInterfaceManager*�ӿ����queryInterface��ȡԤ����Ľӿ���IInterface*

  queryInterface����IInterface���࣬���巵���ĸ�IInterface���࣬��IInterfaceManager���������

*/

class IInterfaceManager  
{
public:
	IInterfaceManager(){};
	virtual ~IInterfaceManager(){};

	virtual IInterface* queryInterfaceObj(std::string name){ return NULL; };

};


#define GET_INTERFACE_MANAGER_STRING "getInterfaceManager"
typedef IInterfaceManager* (*getInterfceManagerFunc)();

#endif // !defined(AFX_IUNKOWN_H__EF8D39E7_DAA3_4FB6_9963_5E254EA6159E__INCLUDED_)
