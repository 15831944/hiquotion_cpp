#pragma once

// for sending

#include <C++\3rdParty\jrtplib3\jrtplib3.h>
#include <c++\foudationlib\bufferlib\cycledbuffer.h>

#define JRTP_MAX_PACKAGE_LENGTH 1200

#define TIME_STAMP 16


// for receiving

#include <C++/FoudationLib/eventlib/eventemu-��mfc���¼�����/ieventraisable.h>
#include <C++/FoudationLib/eventlib/eventemu-��mfc���¼�����/delegate.h>
#include <C++\3rdParty\jrtplib3\rtppacket.h>
#include <C++\3rdParty\jrtplib3\rtpsourcedata.h>
#include <c++/foudationlib/bufferlib/cycledbuffer.h>


class CJRTPExt :
	public RTPSession, public IEventRaisable
{
public:
	CJRTPExt(void);
	~CJRTPExt(void);

	// for sending

	int SendPacket(const void *data,size_t len, uint8_t pt,uint32_t timestampinc);

	// for receiving

	// ���յ������ݣ������ж� PayloadType ֵ�Ƿ���������ָ�� PayloadType ֵ��ͬ
	// �����ͬ������뻺����
	// ��������һ�������׳��յ����ݵ��¼����¼������Ǽ̳� IEvent �ӿڵ� 
	// ��ʼ��������
	void initBuffer();

	void setPayloadType(int payloadType);

	BOOL isWaitMark() const { return m_isWaitMark; }
	void setWaitMark(BOOL val) { m_isWaitMark = val; }

	CDelegate DataGot;
	CDelegate ByePacket;
	CDelegate NewSource;

private:
	char *m_multiSendBuffer;
	CCycledBuffer m_buffer4Sending;

protected:
	void OnPollThreadStep();
	// �����ﴦ���յ��İ����ж������Ƿ���ȷ�������Ƿ��㹻������һ��������˵�����Լ��Ƿ���Ҫ�׳����ݵ�����¼��ȵ�
	void ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack);
	// �̳и÷�����ʵ�ִ���Ҫ��ִ�� CJrtpSession::OnNewSource(data); Ȼ����ִ���Լ��Ĵ���
	void OnNewSource(RTPSourceData *dat);
	// �̳и÷�����ʵ�ִ���Ҫ��ִ�� CJrtpSession::OnBYEPacket(data); Ȼ����ִ���Լ��Ĵ���
	void OnBYEPacket(RTPSourceData *dat);

private:

#define H264  96
#define G729A 18

	int m_payloadType;

	CCycledBuffer m_buffer4Receiving;

	BOOL m_isWaitMark;
};

class CJRTPReceiverEvent :
	public IEvent
{
public:
	CJRTPReceiverEvent(IEventRaisable *sender, string eventId, string ip, char *buffer, int bufferLength, unsigned int timestamp);
	~CJRTPReceiverEvent(void);

	char *getBuffer() const { return m_buffer; }
	int getBufferLength() const { return m_bufferLength; }
	string getIp() const { return m_ip; }
	unsigned int getTimestamp() const { return m_timestamp; }

private:
	string m_ip;
	char *m_buffer;
	int m_bufferLength;
	unsigned int m_timestamp;
};
