#include "StdAfx.h"
#include "RandNum.h"

CRandNum::CRandNum(void)
{
}

CRandNum::~CRandNum(void)
{
}

// ������� min �� max ֮���һ������
int CRandNum::generate(int min, int max)
{
	if(min==max)
		return min;

	if(min>max){
		int tmp=min;
		min=max;
		max=tmp;
	}

	srand(GetTickCount());
	return min+rand()%(max-min+1);

}
