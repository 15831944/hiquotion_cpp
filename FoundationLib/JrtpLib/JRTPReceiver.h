#pragma once

#include <C++\3rdParty\jrtplib3\jrtplib3.h>
#include <C++/FoudationLib/eventlib/eventemu-��mfc���¼�����/ieventraisable.h>
#include <C++/FoudationLib/eventlib/eventemu-��mfc���¼�����/delegate.h>
#include <C++\3rdParty\jrtplib3\rtppacket.h>
#include <C++\3rdParty\jrtplib3\rtpsourcedata.h>
#include <c++/foudationlib/bufferlib/cycledbuffer.h>

#ifdef RTP_SUPPORT_THREAD
	#undef RTP_SUPPORT_THREAD
#endif

// JRTP ���ݽ�����
// ���յ������ݣ������ж� PayloadType ֵ�Ƿ���������ָ�� PayloadType ֵ��ͬ
// �����ͬ������뻺����
// ��������һ�������׳��յ����ݵ��¼����¼������Ǽ̳� IEvent �ӿڵ� CJRTPReceiverEvent ��
class CJRTPReceiver : public RTPSession, public IEventRaisable
{
public:
	CJRTPReceiver();
	~CJRTPReceiver(void);

	// ��ʼ��������
	void initBuffer();

	void setPayloadType(int payloadType);

	CDelegate DataGot;
	CDelegate ByePacket;
	CDelegate NewSource;

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

	CCycledBuffer m_buffer;
};


class CJRTPReceiverEvent :
	public IEvent
{
public:
	CJRTPReceiverEvent(IEventRaisable *sender, string eventId, char *buffer, int bufferLength);
	~CJRTPReceiverEvent(void);

	char *getBuffer() const { return m_buffer; }
	int getBufferLength() const { return m_bufferLength; }

private:
	char *m_buffer;
	int m_bufferLength;
};
