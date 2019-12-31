#pragma once

#include <string>
using namespace std;

enum ThreadStatus
{
	Created,
	Running,
	Paused,
	Stopped,
	ToStop,
	Closed,
	Terminated,
// 	Destroyed,
	Error,
};

class CThreadStatus
{
public:
	static std::string toString(ThreadStatus status)
	{
		std::string s="";
		switch(status)
		{
		case Created:
			s="�Ѿ�����";
			break;
		case Running:
			s="��������";
			break;
		case Paused:
			s="��ͣ����";
			break;
		case Stopped:
			s="�Ѿ�ֹͣ";
			break;
		case ToStop:
			s="׼��ֹͣ";
			break;
		case Terminated:
			s="��ǿ����ֹ";
			break;
		case Error:
			s="���ִ���";
			break;
		}

		return s;
	}
};