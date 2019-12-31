// KernelLexer.cpp: implementation of the CKernelLexer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KernelLexer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKernelLexer::CKernelLexer()
{
	m_builder.build();
	m_lexer.setLexStatusGraph(m_builder.getGraph());
}

CKernelLexer::~CKernelLexer()
{

}

// ����ֵ��
// -1������Ϊ��
// -2��״̬���ڲ����󣨵�ǰ���Ϊ�գ�
// -3������ preProcessTokens ʧ��
int CKernelLexer::analyze(string text, CPointerList<MachineToken *> &tokenList, CValueList<string> &errList)
{
	int ret=m_lexer.analyze(text, tokenList, errList);
	if(ret<0)
		return ret;
	
 	ret=preProcessTokens(tokenList);
	if(ret<0)
		return -3;

	return 0;
}

// ��token�б���Ԥ����
// 1. ��˫�����е����ݣ����һ��token
// 2. ���� \" �Ĵ��������һ�������ڣ��������ַ������������һ�������⣬������token����
// 3. ȥ���س����ո���ע�͡���ע�͵ȵȵ�token��
// 4. ��ȡ��������������%֮����Ǳ���������ȡ˫����֮����ַ���֮������
// ������
// tokenList����Լʽ��token�б�
// ����ֵ��
// 0���ɹ�
// -1��tokenList���д���
// -2��preProcessExtractStringToken����ʧ��
// -3����һ��token�����ţ�����������κ�token�������Ŷ�
int CKernelLexer::preProcessTokens(CPointerList<MachineToken *> &tokenList)
{
	if(tokenList.size()<=0)
		return -1;

	BOOL isinQuota=FALSE;
	int quotaStartIndex=-1;
	int quotaEndIndex=-1;
//	MachineToken *startToken;
	MachineToken *endToken;

	int i=0;
	// 1. ��˫�����е����ݣ����һ��token
	// 2. ���� \" �Ĵ��������һ�������ڣ��������ַ������������һ�������⣬������token����

	// �����һ��token��ʼ�������ڲ����б��ʱ�򣬲���Ӱ���б�ǰ���Ԫ�ء���ͬ��
	for(i=tokenList.size()-1;i>=0;i--)
	{
		MachineToken *token=tokenList.at(i);
		// �������������
		if(token->token=="\"")
		{
			if(i>0 && i-1>=0)
			{
				// �������ǰ��û��\��˵���ǽ���������
				if(tokenList.at(i-1)->token!="\\")
				{
					// �����ǰ����������
					if(!isinQuota)
					{
						quotaEndIndex=i;
						endToken=token;
						isinQuota=TRUE;
					}
					// ����Ѿ����������ˣ���ȡ���������ڵ����ݣ����һ���ַ���������������token�����ڵ�token��ɾ��������Ӹ��ַ�������������Ϊstring
					else
					{
						quotaStartIndex=i;
						int ret=preProcessExtractStringToken(tokenList, i, quotaEndIndex);
						if(ret<0)
							return -2;

						// �ָ������ĳ�ֵΪ-1
						quotaStartIndex=-1;
						quotaEndIndex=-1;
						
						// ����״̬Ϊ����������
						isinQuota=FALSE;
					}
				}
				else  // ��ʾʵ�ʵ�����
				{
					tokenList.destroyByIndex(i-1);

					i--;
				}
			}
			else // i=0 �����
			{
				// �����ǰ���������ڣ�˵��������
				if(!isinQuota)
				{
					std::stringstream ss;
					ss << "��һ��token�����ţ�����������κ�token�������Ŷ�";
					m_errMsg=ss.str();
					return -3;
				}
				else
				{
					quotaStartIndex=i;
					int ret=preProcessExtractStringToken(tokenList, i, quotaEndIndex);
					if(ret<0)
						return ret;

					// �ָ������ĳ�ֵΪ-1
					quotaStartIndex=-1;
					quotaEndIndex=-1;
					
					// ����״̬Ϊ����������
					isinQuota=FALSE;
				}
			}
		}
	}

	// 3. ȥ���س����ո���ע�͡���ע�͵ȵȵ�token��
	for(i=tokenList.size()-1;i>=0;i--)
	{
		MachineToken *token=tokenList.at(i);
		if(!token)
			continue;
		
		std::string name=token->token;
		std::string tp=token->type;
		// ȥ���س����ո���ע�͡���ע��
		if(name=="\r" || name=="\n" || name=="\r\n" || name==" " || tp=="lineComment" || tp=="blockComment")
			tokenList.destroyByIndex(i);
	}

	// 4. ��ȡ��������������%֮����Ǳ���������ȡ˫����֮����ַ���֮������
	int percentStartIndex=-1;
	int percentEndIndex=-1;
	int percentMetTimes=0;

	for(i=tokenList.size()-1;i>=0;i--)
	{
		MachineToken *token=tokenList.at(i);
		if(!token)
			continue;

		if(token->type!="%")    // Ҫ��type���жϣ���Ϊǰ�������е�tokenName(name)�Ѿ������%�ˣ���type��string��
			continue;			// �����name�жϵĻ��������������type�жϾͲ��������
		
		percentMetTimes=(percentMetTimes+1)%2;

		if(percentMetTimes==1)
		{
			percentEndIndex=i;
			continue;
		}
		else if(percentMetTimes==0)
		{
			percentStartIndex=i;
			if(percentEndIndex==-1)
			{
				percentStartIndex=-1;
				percentEndIndex=-1;
				percentMetTimes=0;
				continue;

			}

			if(percentEndIndex-percentStartIndex!=2)
			{
				percentStartIndex=-1;
				percentEndIndex=-1;
				percentMetTimes=0;
				continue;
			}

			MachineToken *varToken=tokenList.at(i+1);
			if(!varToken)
			{
				percentStartIndex=-1;
				percentEndIndex=-1;
				percentMetTimes=0;
				continue;
			}
// 			if(varToken->type!="id")
// 			{
// 				percentStartIndex=-1;
// 				percentEndIndex=-1;
// 				percentMetTimes=0;
// 				continue;
// 			}
// 
// 			varToken->type="var";

			varToken->check4Statute=CheckType4Statute;

			tokenList.destroyByIndex(percentEndIndex);
			tokenList.destroyByIndex(percentStartIndex);

			percentStartIndex=-1;
			percentEndIndex=-1;
			percentMetTimes=0;
		}
	}

	return 0;
}

// ������ʼ����ֹ����������ȡ�÷�Χ��tokensΪ�ַ���token
int CKernelLexer::preProcessExtractStringToken(CPointerList<MachineToken *> &tokenList, int startIndex, int endIndex)
{
	int quotaStartIndex=startIndex;
	int quotaEndIndex=endIndex;
	
	// ���������������token��λ�������Ƿ�Ϸ�
	if(quotaStartIndex>=0 && quotaEndIndex>=0 && quotaStartIndex<quotaEndIndex && quotaEndIndex<tokenList.size())
	{
		MachineToken *startToken=tokenList.at(startIndex);
		MachineToken *endToken=tokenList.at(endIndex);
		
		int j=0;
		std::string content="";
		if(quotaEndIndex-quotaStartIndex>1)  // ����1��ʾ���ַ������Ͳ���Ҫ�������Ĵ����ˣ�С��1������
		{
			for(j=quotaStartIndex+1;j<quotaEndIndex;j++)  // ����������˫����
			{
				MachineToken *tmpToken=tokenList.at(j);
				if(!tmpToken)
					continue;
				
				content+=tmpToken->token;
			}
		}
		
		// ����һ���µ�token
		MachineToken *newToken=new MachineToken;
		newToken->startPosition=startToken->startPosition; // �費��Ҫ��1�أ���Ϊ��ֵΪ����λ��
		newToken->endPosition=endToken->endPosition;  // �費��Ҫ��1�أ���Ϊ��ֵΪ����λ��
		newToken->token=content;
		newToken->type="string";
		
		// ɾ��tokenList�е���Щ����������token
		for(j=quotaEndIndex;j>=quotaStartIndex;j--)
			tokenList.destroyByIndex(j);
		
		// ���½������ַ������͵�token����ӵ�quotaStartIndexλ��
		if(tokenList.size()<=0)
			tokenList.push_back(newToken);
		else
			tokenList.insert(tokenList.begin()+quotaStartIndex, newToken);
	}
	else
	{
		std::stringstream ss;
		ss<<"token�б������ŵ�ʹ�����󣡣��ڵ�" << quotaStartIndex << "�͵�" << quotaEndIndex << "��������";
		m_errMsg=ss.str();
		return -1;
	}
	
	return 0;
}
