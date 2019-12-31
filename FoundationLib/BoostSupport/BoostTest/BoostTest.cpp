// BoostTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BoostTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <boost/circular_buffer.hpp>   
#include <numeric>   
#include <assert.h>   

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;

		// ����һ�����λ��������������int���͵�����   
		boost::circular_buffer<int> cb(3);  

		//����Ԫ��   
		cb.push_back(1);  
		cb.push_back(2);  
		cb.push_back(3);  

		int a = cb[0];  // a == 1   
		int b = cb[1];  // b == 2   
		int c = cb[2];  // c == 3   

		//���λ����������Ѿ����ˣ���������Ԫ�ؽ��Ḳ�ǵ���ǰ���Ԫ��   

		cb.push_back(4);  // ��4������1   
		cb.push_back(5);  // ��5������2   

		//���λ��������ڰ���Ԫ�� 3, 4 �� 5.   

		a = cb[0];  // a == 3   
		b = cb[1];  // b == 4   
		c = cb[2];  // c == 5   

		//Ԫ���ܹ����Ӻ���ȡ��Ҳ�ɴ�ǰ��ȡ��   

		cb.pop_back();  // 5 ��ȡ��   
		cb.pop_front(); // 3 ��ȡ��   

		int d = cb[0];  // d == 4   

		return 0;  


// 		//����һ������Ϊ3�Ļ��λ�����   
// 		boost::circular_buffer<int> cb(3);  
// 		
// 		//����2��Ԫ�ؽ��뻷�λ�����   
// 		cb.push_back(1);  
// 		cb.push_back(2);  
// 		
// 		// assertions   
// 		assert(cb[0] == 1);  
// 		assert(cb[1] == 2);  
// 		assert(!cb.full());  
// 		assert(cb.size() == 2);  
// 		assert(cb.capacity() == 3);  
// 		
// 		//�ٲ���2��Ԫ��   
// 		cb.push_back(3);  
// 		cb.push_back(4);  
// 		
// 		//��������������Ԫ��֮��   
// 		int sum = std::accumulate(cb.begin(), cb.end(), 0);  
// 		
// 		//����   
// 		assert(cb[0] == 2);  
// 		assert(cb[1] == 3);  
// 		assert(cb[2] == 4);  
// 		assert(*cb.begin() == 2);  
// 		assert(cb.front() == 2);  
// 		assert(cb.back() == 4);  
// 		assert(sum == 9);  
// 		assert(cb.full());  
// 		assert(cb.size() == 3);  
// 		assert(cb.capacity() == 3);  
// 		
// 		return 0;  

	}

	return nRetCode;
}


