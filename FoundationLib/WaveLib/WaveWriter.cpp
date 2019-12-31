#include "stdafx.h"
#include "WaveWriter.h"

CWaveWriter::CWaveWriter(void)
{
	m_isOpen=FALSE;
	m_dataLen=0;
}

CWaveWriter::~CWaveWriter(void)
{
	if(m_isOpen)
		closeFile();
}

BOOL CWaveWriter::createFile(CString path, PWAVEFORMATEX pWaveInfo)
{
	if(!m_file.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
		return FALSE;

	m_isOpen=TRUE;

	char RIFF[4]={'R', 'I', 'F', 'F'};
	char WAVE[4]={'W', 'A', 'V', 'E'};
	char fmt[4]={'f', 'm', 't', ' '};
	char data[4]={'d', 'a', 't', 'a'};
	int len=0;
	m_file.Write(RIFF, 4);   // ��ý���ļ���ʶ
	len=CONTENT_LEN;
	m_file.Write(&len, 4);      // �������ݳ��ȣ�������RIFF��ʾ�͸�4�ֽڵĳ��ȱ������ٰ��� 36 �ֽڵ�WAVE��ʽ��Ϣ����
	m_file.Write(WAVE, 4);   // WAVE �ļ���ʶ
	m_file.Write(fmt, 4);    // �ӿ�1��id
	len=TRUNK1_LEN;
	m_file.Write(&len, 4);     // ���ӿ�Ĵ�С
	m_file.Write(&pWaveInfo->wFormatTag, 2);   // ��Ƶ��ʽ
	m_file.Write(&pWaveInfo->nChannels, 2);    // ������
	m_file.Write(&pWaveInfo->nSamplesPerSec, 4); // ������   22050
	m_file.Write(&pWaveInfo->nAvgBytesPerSec, 4); // �����ʣ���ÿ���ֽ��������� SampleRate * numChannels * BitsPerSample / 8     44100
	m_file.Write(&pWaveInfo->nBlockAlign, 2);     // ���룬 ���� NumChannels * BitsPerSample / 8 
	m_file.Write(&pWaveInfo->wBitsPerSample, 2);  // ����λ��
	len=0;
	m_file.Write(&len, 2);          // cbSizeֵ(�˴�Ϊ0)
	m_file.Write(data, 4);   // ���ݿ��ʶ
	len=0;
	m_file.Write(&len, 4);      // ���ݳ��ȣ���ǰΪ0

	return TRUE;
}

void CWaveWriter::writeData(char *data, int dataLen)
{
	// д������
	m_file.Write(data, dataLen);
	m_dataLen+=dataLen;

	// д������������
	m_file.Seek(4, CFile::begin);
	int len=CONTENT_LEN+m_dataLen;
	m_file.Write(&len, 4); // д���ܳ��ȣ�38 + ���ݳ��ȣ�
	m_file.Seek(DATA_LEN_POSITION, CFile::begin);
	m_file.Write(&m_dataLen, 4);    // д�����ݳ���
	m_file.SeekToEnd();
}

void CWaveWriter::closeFile()
{
	if(m_isOpen)
		m_file.Close();
	m_isOpen=FALSE;
}
