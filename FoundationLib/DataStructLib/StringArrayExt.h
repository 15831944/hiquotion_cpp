#pragma once
class CStringArrayExt
{
public:
	CStringArrayExt(void);
	~CStringArrayExt(void);

	// �ж����� CStringArray �������Ƿ�����ͬ��Ԫ��
	static BOOL intersect(CStringArray *array1, CStringArray *array2);
	// �ж�CS��ringArray�������Ƿ����ָ��CString�ַ���
	static BOOL isContain(CStringArray *array, CString str);
};

