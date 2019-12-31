// CycledBufferTest2.h: interface for the CCycledBufferTest2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYCLEDBUFFERTEST2_H__20F7A6F1_828A_4981_BD17_C40F789ED77D__INCLUDED_)
#define AFX_CYCLEDBUFFERTEST2_H__20F7A6F1_828A_4981_BD17_C40F789ED77D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISimpleTest.h"
#include "CycledBuffer.h"

class CCycledBufferTest2 : ISimpleTest<CCycledBuffer>
{
public:
	CCycledBufferTest2();
	virtual ~CCycledBufferTest2();

	// ��ʼ����
	void startTest()
	{
		testcase3();
		testcase4();
		testcase5();
		testcase6();
		testcase7();
		testcase8();
		testcase9();
		testcase10();
		testcase11();
	}

// 	3	��ʼ״̬		0	-1	0	��	���д����ȡ��
// 		д��10��Ԫ��	0	9	10	��	1,2,3,4,5,6,7,8,9,10
// 		��ȡ10��Ԫ��	0	9	0	��	(1,2,3,4,5,6,7,8,9,10)
	void testcase3()
	{
		printf("testcase3\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

// 		д��10��Ԫ��
		char data[10]={1,2,3,4,5,6,7,8,9,10};
		printBufferData("data to write is:", data, 10);

		buffer->write(data, 10);

		char dataContent[10];
		int dataLength=0;
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=10)
		{
			printFailed("buffer content data length is not equals to 10!");
			return;
		}

		printBufferData("data written is:", dataContent, dataLength);
		if(!compareBufferData(data, dataContent, 10))
		{
			printFailed("data content is not same with written!");
			return;
		}

// 		��ȡ10��Ԫ��
		char dataRead[10];
		buffer->read(dataRead, 10);

		printBufferData("data read is:", dataRead, 10);

		char dataReadExpected[10]={1,2,3,4,5,6,7,8,9,10};
		if(compareBufferData(dataRead, dataReadExpected, 10))
			printOK();
		else
			printFailed("data read is not same with data expected!");

		testCaseCleanup(buffer);
	}

// 	4	��ʼ״̬	0	-1	0	��	����ͷд�룬���м�д�룬���м�д��������ѭ����
// 		д��3��Ԫ��	0	2	3	��	1,2,3
// 		д��4��Ԫ��	0	6	7	��	1,2,3,4,5,6,7
// 		д��3��Ԫ��	0	9	10	��	1,2,3,4,5,6,7,8,9,10
	void testcase4()
	{
		printf("testcase4\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		
// 		д��3��Ԫ��
		char data[3]={1,2,3};
		char data2[4]={4,5,6,7};
		char data3[3]={8,9,10};

		buffer->write(data, 3);
		buffer->write(data2, 4);
		buffer->write(data3, 3);

		char dataContent[10];
		int dataLength=0;
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=10)
		{
			printFailed("buffer content data length is not equals to 10!");
			return;
		}

		printBufferData("data written is:", dataContent, dataLength);

		char dataExpected[10]={1,2,3,4,5,6,7,8,9,10};
		if(compareBufferData(dataContent, dataExpected, 10))
			printOK();
		else
			printFailed("data read is not same with data expected!");

		testCaseCleanup(buffer);
}
	
// 	5	��ʼ״̬	0	-1	0	��	����ͷ��ȡ�����м��ȡ�����м�ȡ�գ�����ѭ������ȡ�պ���д�루����ѭ����
// 		д��7��Ԫ��	0	6	7	��	1,2,3,4,5,6,7
// 		��ȡ2��Ԫ��	2	6	5	��	3,4,5,6,7(1,2)
// 		��ȡ4��Ԫ��	6	6	1	��	7(3,4,5,6)
// 		��ȡ1��Ԫ��	7	6	0	��	(7)
// 		д��2��Ԫ��	7	8	2	��	8,9
// 		д��1��Ԫ��	7	9	3	��	8,9,10
	void testcase5()
	{
		printf("testcase5\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		
// 		д��7��Ԫ��
		char a[7]={1,2,3,4,5,6,7};
		buffer->write(a, 7);
// 		��ȡ2��Ԫ��
		char read1[2];
		buffer->read(read1, 2);
		char read1Expected[2]={1,2};
		if(!compareBufferData(read1, read1Expected, 2))
		{
			printFailed("data read 2 bytes is not same with expected!");
			return;
		}

// 		��ȡ4��Ԫ��
		char read2[4];
		buffer->read(read2, 4);
		char read2Expected[4]={3,4,5,6};
		if(!compareBufferData(read2, read2Expected, 4))
		{
			printFailed("data read 4 bytes is not same with expected!");
			return;
		}

// 		��ȡ1��Ԫ��
		char read3[1];
		buffer->read(read3, 1);
		char read3Expected[1]={7};
		if(!compareBufferData(read3, read3Expected, 1))
		{
			printFailed("data read 1 bytes is not same with expected!");
			return;
		}

		char write1[2]={8,9};
		buffer->write(write1, 2);
		char content1[10];
		int dataLength=0;
		
		getCycledBufferContent(buffer, content1, &dataLength);
		if(dataLength!=2)
		{
			printFailed("data content length is not equals to 2!");
			return;
		}

		if(!compareBufferData(content1, write1, 2))
		{
			printFailed("data content is not same with data expected!");
			return;
		}

		char write2[1]={10};
		buffer->write(write2, 1);
		char content2[10];

		getCycledBufferContent(buffer, content2, &dataLength);
		if(dataLength!=3)
		{
			printFailed("data content length is not equals to 3!");
			return;
		}
		
		char dataExpected[3]={8,9,10};
		if(compareBufferData(content2, dataExpected, 3))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	6	��ʼ״̬	7	6	0	��	�����м�д�뵽������β����д�루��ѭ����
// 		д��3��Ԫ��	7	9	3	��	1,2,3
// 		д��5��Ԫ��	7	4	8	��	1,2,3,4,5,6,7,8
	void testcase6()
	{
		printf("testcase6\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		buffer->setStartIndex(7);
		buffer->setEndIndex(6);
		buffer->setEmpty(TRUE);

		char data[3]={1,2,3};
		buffer->write(data, 3);

		char data2[5]={4,5,6,7,8};
		buffer->write(data2, 5);

		char dataContent[10];
		int dataLength=0;

		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=8)
		{
			printFailed("data content length is not equals to 8!");
			return;
		}

		char dataExpected[8]={1,2,3,4,5,6,7,8};
		if(compareBufferData(dataContent, dataExpected, 8))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	7	��ʼ״̬	7	4	8	��	�����м��ȡ�����м��ȡ��������β���ٶ�ȡ����ѭ����
// 									1,2,3,4,5,6,7,8
// 		��ȡ1��Ԫ��	8	4	7	��	2,3,4,5,6,7,8(1)
// 		��ȡ2��Ԫ��	0	4	5	��	4,5,6,7,8(2,3)
// 		��ȡ3��Ԫ��	3	4	2	��	7,8(4,5,6)
	void testcase7()
	{
		printf("testcase7\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		char initData[8]={1,2,3,4,5,6,7,8};
		initCycledBuffer(buffer, 7, 4, initData);

		char read1[1];
		buffer->read(read1, 1);

		char read1Expected[1]={1};
		if(!compareBufferData(read1, read1Expected, 1))
		{
			printFailed("data read is not same with expected!");
			return;
		}

		char read2[2];
		buffer->read(read2, 2);

		char read2Expected[2]={2,3};
		if(!compareBufferData(read2, read2Expected, 2))
		{
			printFailed("data read is not same with expected!");
			return;
		}
		
		char read3[3];
		buffer->read(read3, 3);
		
		char read3Expected[3]={4,5,6};
		if(!compareBufferData(read3, read3Expected, 3))
		{
			printFailed("data read is not same with expected!");
			return;
		}
		
		char dataContent[10];
		int dataLength=0;
		
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=2)
		{
			printFailed("data content length is not equals to 2!");
			return;
		}
		
		char dataExpected[2]={7,8};
		if(compareBufferData(dataContent, dataExpected, 2))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	8	��ʼ״̬	7	6	0	��	�����м�д�루��ѭ������ѭ������д��
// 		д��6��Ԫ��	7	2	6	��	1,2,3,4,5,6
// 		д��2��Ԫ��	7	4	8	��	1,2,3,4,5,6,7,8
	void testcase8()
	{
		printf("testcase8\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		buffer->setStartIndex(7);
		buffer->setEndIndex(6);
		buffer->setEmpty(TRUE);

		char data1[6]={1,2,3,4,5,6};
		buffer->write(data1, 6);

		char dataContent[10];
		int dataLength=0;

		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=6)
		{
			printFailed("data content length is not equals to 6!");
			return;
		}
		
		if(!compareBufferData(data1, dataContent, 6))
		{
			printFailed("data content is not same with expected!");
			return;
		}

		char data2[2]={7,8};
		buffer->write(data2, 2);
		
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=8)
		{
			printFailed("data content length is not equals to 8!");
			return;
		}

		char dataExpected[8]={1,2,3,4,5,6,7,8};
		if(compareBufferData(dataContent, dataExpected, 8))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	9	��ʼ״̬	7	4	8	��	�����м��ȡ����ѭ������ѭ�����ٶ�ȡ
// 									1,2,3,4,5,6,7,8
// 		��ȡ6��Ԫ��	3	4	2	��	7,8(1,2,3,4,5,6)
// 		��ȡ1��Ԫ��	4	4	1	��	8(7)
	void testcase9()
	{
		printf("testcase9\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		buffer->setStartIndex(7);
		buffer->setEndIndex(4);
		buffer->setEmpty(FALSE);

		char data[8]={1,2,3,4,5,6,7,8};
		initCycledBuffer(buffer, 7, 4, data);

		char read1[6];
		buffer->read(read1, 6);

		char read1Expected[6]={1,2,3,4,5,6};
		if(!compareBufferData(read1, read1Expected, 6))
		{
			printFailed("data read is not same with expected!");
			return;
		}

		char read2[1];
		buffer->read(read2, 1);
		
		char read2Expected[1]={7};
		if(!compareBufferData(read2, read2Expected, 1))
		{
			printFailed("data read is not same with expected!");
			return;
		}

		char dataContent[10];
		int dataLength=0;
		
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=1)
		{
			printFailed("data content length is not equals to 1!");
			return;
		}
		
		char dataExpected[1]={8};
		if(compareBufferData(dataContent, dataExpected, 1))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	10	��ʼ״̬		7	6	0	��	�����м�д������ѭ���������м�ȡ�գ���ѭ����
// 		д��10��Ԫ��	7	6	10	��	1,2,3,4,5,6,7,8,9,10
// 		��ȡ10��Ԫ��	7	6	0	��	(1,2,3,4,5,6,7,8,9,10)
	void testcase10()
	{
		printf("testcase10\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		char data[10]={1,2,3,4,5,6,7,8,9,10};
		initCycledBuffer(buffer, 7, 6, data);

		char read[10];
		buffer->read(read, 10);

		if(compareBufferData(read, data, 1))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	11	��ʼ״̬	7	2	6	��	�����м�д������ѭ����֮ǰ�����ݣ������м�ȡ�գ���ѭ����
// 									1,2,3,4,5,6
// 		д��4��Ԫ��	7	6	10	��	1,2,3,4,5,6,7,8,9,10
// 		��ȡ10��Ԫ��	7	6	0	��	(1,2,3,4,5,6,7,8,9,10)
	void testcase11()
	{
		printf("testcase11\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		
		char data[6]={1,2,3,4,5,6};
		initCycledBuffer(buffer, 7, 2, data);

		char data2[4]={7,8,9,10};
		buffer->write(data2, 4);

		char read[10];
		buffer->read(read, 10);

		char readExpected[10]={1,2,3,4,5,6,7,8,9,10};

		if(compareBufferData(read, readExpected, 10))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}

	void printOK()
	{
		printf("--------------------------------------  OK!\n");
	}

	void printFailed(char *msg)
	{
		printf("%s \t -------- \t  Oh!No!\n", msg);
	}
	
	// ��ʼ��CycledBuffer�����ݡ���ʼλ�úͽ���λ��
	void initCycledBuffer(CCycledBuffer *buffer, int startIndex, int endIndex, char *data)
	{
		int i=startIndex;
		int dataIndex=0;
		while(i!=endIndex)
		{
			buffer->setBufferData(i, data[dataIndex]);
			i=(i+1)%buffer->getBufferLength();
			dataIndex++;
		}
		buffer->setBufferData(endIndex, data[dataIndex]);

		buffer->setStartIndex(startIndex);
		buffer->setEndIndex(endIndex);
		buffer->setEmpty(FALSE);
	}

	void getCycledBufferContent(CCycledBuffer *buffer, char *data, int *dataLength)
	{
		int i=buffer->getStartIndex();
		int dataIndex=0;
		while(i!=buffer->getEndIndex())
		{
			data[dataIndex]=buffer->getBufferData(i);
			i=(i+1)%buffer->getBufferLength();
			dataIndex++;
		}
		data[dataIndex]=buffer->getBufferData(buffer->getEndIndex());

		*dataLength=dataIndex+1;
	}

	BOOL compareBufferData(char *arr1, char *arr2, int len)
	{
		if(len<=0)
			return FALSE;
		
		for(int i=0;i<len;i++)
		{
			if(arr1[i]!=arr2[i])
				return FALSE;
		}
		
		return TRUE;
	}
	
	void printBufferData(char *msg, char *arr, int len)
	{
		if(len<=0)
		{
			printf("No data.");
			return;
		}

		if(msg)
			printf("%s", msg);
		
		CString display="",tmp="";
		display.Format("%d",arr[0]);
		
		for(int i=1;i<len;i++)
		{
			tmp.Format("%d", arr[i]);
			display+=","+tmp;
		}
		printf("%s\n", (LPTSTR)(LPCSTR)display);
		
	}
};

#endif // !defined(AFX_CYCLEDBUFFERTEST2_H__20F7A6F1_828A_4981_BD17_C40F789ED77D__INCLUDED_)
