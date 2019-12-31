// BitmapProcess.h: interface for the CBitmapProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPPROCESS_H__F93A9E7C_8A0C_4A56_BE7C_1063B3206316__INCLUDED_)
#define AFX_BITMAPPROCESS_H__F93A9E7C_8A0C_4A56_BE7C_1063B3206316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBitmapProcess  
{
public:
	CBitmapProcess();
	virtual ~CBitmapProcess();

	// ��ɫͼ�����ɻҶ�ͼ
	// ������ͼ���ȡ�ͼ��߶ȡ���ɫRGBͼ�����ݣ�����Ϊ��x��x3�����Ҷ�ͼ�����ݣ�����Ϊ��x�ߣ�
	static int color2Gray(int width, int height, unsigned char *rgbData, unsigned char *greyData);
	static int color8bit2Gray(int width, int height, BITMAPINFO *info, unsigned char *rgbData, unsigned char *greyData);

	// ��ɫͼ���ֵ��
	// ������ͼ���ȡ�ͼ��߶ȡ���ɫRGBͼ�����ݣ�����Ϊ��x��x3������ֵͼ�����ݣ�����Ϊ��x��x3������ֵ����ֵ
	// ��ֵ��������rgb��ͣ�������ֵ�Ƚϣ�<=����0��������255
	static int colorBinaryzation(int width, int height, unsigned char *rgbData, unsigned char *binaryData, int threshold);
	
	// ��λ��ɫͼ���ֵ��
	// ��һ���ֽڴ���һ�����أ���ɫֵ�ɵ�ɫ�����
	// ������ͼ���ȡ�ͼ��߶ȡ���ɫRGBͼ�����ݣ�����Ϊ��x�ߣ�����ֵͼ�����ݣ�����Ϊ��x�ߣ�����ֵ����ֵ
	// ��ֵ��������rgb��ͣ�������ֵ�Ƚϣ�<=����0��������255
	static int color8Binaryzation(int width, int height, BITMAPINFO *info, unsigned char *rgbData, unsigned char *binaryData, int threshold);
	static int color8Binaryzation(int width, int height, RGBQUAD *quad, unsigned char *rgbData, unsigned char *binaryData, int threshold);
	
	// ��ɫͼ���ֵ��
	// ������ͼ���ȡ�ͼ��߶ȡ���ɫRGBͼ�����ݣ�����Ϊ��x��x3������ֵͼ�����ݣ�����Ϊ��x�ߣ�����ֵ����ֵ�� ��ֵӦ���ڣ�0-R��1-G��2-B������-B��
	// ��ֵ��������ָ��r��g��bֵ����Ӧ����ֵ�Ƚϣ�<=����0��������255
	static int colorBinaryzation(int width, int height, unsigned char *rgbData, unsigned char *binaryData, unsigned char threshold, char appto);
	
	// �Ҷ�ͼ���ֵ��
	// ������ͼ���ȡ�ͼ��߶ȡ��Ҷ�ͼ�����ݣ�����Ϊ��x�ߣ�����ֵ����ֵ����ֵͼ�����ݣ�����Ϊ��x�ߣ�
	// ��ֵ���������Ҷ�ֵ����ֵ�Ƚϣ�<=����0��������255
	static int greyBinaryzation(int width, int height, unsigned char *greyData, unsigned char threshold, unsigned char *binaryData);
};

#endif // !defined(AFX_BITMAPPROCESS_H__F93A9E7C_8A0C_4A56_BE7C_1063B3206316__INCLUDED_)
