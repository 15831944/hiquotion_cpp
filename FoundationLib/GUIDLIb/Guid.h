#pragma once

class CGuid
{
public:
	static CString genGUID();
	static BOOL isGUIDEqual(GUID guid1, GUID guid2);
	// GUID ת�ַ���
	// ��������ʽ
	// ��ʽ˵����ʾ����
	// d/D, 10244798-9a34-4245-b1ef-9143f9b1e68a
	// n/N, 102447989a344245b1ef9143f9b1e68a
	// b/B, {10244798-9a34-4245-b1ef-9143f9b1e68a}
	// p/P, (10244798-9a34-4245-b1ef-9143f9b1e68a)
	static CString toString(GUID &guid, char c='d');
};

