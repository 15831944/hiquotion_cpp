#pragma once

/*

ʹ�÷���
	����Windows API��FindWindow�ҵ��䴰��ָ�루�����������ַ����ʹ������ַ�������ָ���ģ���NULL��
	Ȼ�����ô���ָ���еĴ��ھ����Ϊ��һ������������findWindow���ڶ�����Ϊ��һ�������Ӵ������ڵġ�·����

	����·���Ķ����������ģ�
	class:text/class:text/class:text/ ...	���class��textû�У��뱣�ֿգ���ð�Ų���ʡ��

*/
class CWindowEx
{
public:
	CWindowEx(void);
	~CWindowEx(void);

	static HWND findWindow(HWND parent, CString windowPath);
	static HWND doOsApiFindWindow(CString wndClass, CString title);
	static HWND doOsApiFindWindowEx(HWND hWndParent, HWND hWndChildAfter, CString wndClass, CString title);

private:
	static HWND findWindow(HWND parent, CStringArray &windowFolder, int deepLevel);
};
