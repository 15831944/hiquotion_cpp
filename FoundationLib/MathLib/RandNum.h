#pragma once

class CRandNum
{
public:
	CRandNum(void);
	~CRandNum(void);

	// ������� min �� max ֮���һ������
	static int generate(int min, int max);
};
