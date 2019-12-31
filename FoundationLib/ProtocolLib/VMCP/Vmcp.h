#pragma once

#include <c++\FoudationLib\DataStructLib\PointerMap.h>

/*
	Request��ʽ
	VMCP
	1.0
	<command>
	<command data>��ÿ������һ�У��������Ͳ���ֵ֮����=�ָ

	Respond�ɹ�ʱ��ʽ
	VMCP
	1.0
	<command>_response
	OK
	<respond data>��ÿ������һ�У��������Ͳ���ֵ֮����=�ָ����ֵ����ʱ��;���滻�У�

	Respondʧ��ʱ��ʽ
	VMCP
	1.0
	<command>_response
	ERROR
	<error message shown>
	<error message kernel>

	command������
	heartbeat��������
	start��������
	stop��ֹͣ��

	1��heartbeat

	���ͣ�
	VMCP
	1.0
	heartbeat

	���գ�
	VMCP
	1.0
	heartbeat_response
	OK
	ffmpeg=running������Ϊstopped��unknown��unknown��ʾ��ȡffmpeg������Ϣʧ�ܣ�

	2��start

	���ͣ�
	VMCP
	1.0
	start
	ip=
	port=
	name=
	��˵���������ɹ��󣬷��ص�sdpΪ��sdp://<ip>:<port>/<name>.sdp������

	���գ������ɹ�ʱ����
	VMCP
	1.0
	start_response
	OK
	sdp=

	���գ�����ʧ��ʱ����
	VMCP
	1.0
	start_response
	ERROR
	<error message shown>
	<error message kernel>

	3��stop

	���ͣ�
	VMCP
	1.0
	stop

	���գ��رճɹ�ʱ����
	VMCP
	1.0
	stop_response
	OK

	���գ��ر�ʧ��ʱ����
	VMCP
	1.0
	stop_response
	ERROR
	<error message shown>
	<error message kernel>
*/

struct ParseResult
{
	CString head;
	CString version;
	CString command;
	BOOL result;
	CPointerMap<CString, CString> parameters;
	CString errMsgShown;
	CString errMsgKernel;
};

enum ParseMode
{
	serverParse,
	clientParse,
};


// VMC Application protocol class
class CVmcp
{
public:
	CVmcp() {}
	~CVmcp() {}

	CString parameters2Text(CPointerMap<CString, CString>& parameters);
	CString create(CString head, CString version, CString command, CPointerMap<CString, CString>& parameters);

	CString createHeartBeat();
	CString createStart(CString serverIp, int serverPort, CString name);
	CString createStop();

	CString createSuccessResponse(CString head, CString version, CString command, CPointerMap<CString, CString>& parameters);
	CString createFailureResponse(CString head, CString version, CString command, CString errMsgShown, CString errMsgKernel);
	BOOL parse(CString text, ParseResult& result, CString& parseErrMsg, ParseMode mode = serverParse);

	CString createHeartBeatResponse(CString status);
	CString createStartSuccessResponse(CString sdp);
	CString createStartFailureResponse(CString errMsgShown, CString errMsgKernel);
	CString createStopSuccessResponse();
	CString createStopFailureResponse(CString errMsgShown, CString errMsgKernel);

	BOOL checkResponsedCommand(CString commandSent, CString commandResponded);

protected:
	CPointerMap<CString, CString> m_parameters;
	CPointerMap<CString, CString> m_parametersResponded;
};

