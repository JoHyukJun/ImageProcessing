//////////////////////////////////////////////////////////////////////////
//
// �� ȭ���� �Լ� ��Ͻ� �ڵ����� ������ ������Ʈ�Դϴ�.
//
// ����ڰ� ������ ���� ���, Project�� Setting...�� ������ �ʿ��ϹǷ�,
//
// �̴� ������ '�Լ� �ۼ���'�� ���� �ٶ��ϴ�.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "jSubtractAndThresholding.h"

// DLL�� ����� ���� �κ�
BOOL WINAPI DllMain (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH: break;
		case DLL_THREAD_ATTACH:  break;
		case DLL_THREAD_DETACH:  break;
		case DLL_PROCESS_DETACH: break;
	}

	return TRUE;
}

// �Լ��� ���� �κ�
int CDECL jSubtractAndThresholding(KScScalarImage2dUint8* inBackgroundImg, KScScalarImage2dUint8* inSequenceImg, KScScalarImage2dUint8* outputImg, int* thresholidngValue)
{
	int dx = inBackgroundImg->GetXSize();
	int dy = inBackgroundImg->GetYSize();

	outputImg->Free();
	outputImg->Alloc(dx, dy);

	cv::Mat imgBackground = KScScalarImage2dUint8ToMat(inBackgroundImg);
	cv::Mat imgSequence = KScScalarImage2dUint8ToMat(inSequenceImg);
	cv::Mat imgResult = KScScalarImage2dUint8ToMat(outputImg);

	// Substract and Threshold Image.
	// Pixel Value	:	{0, 255}
	int tempThresholdingValue = 15;

	for (int y = 0; y < dy; y++) {
		for (int x = 0; x < dx; x++) {
			if (fabs(imgBackground.at<uchar>(y, x) - imgSequence.at<uchar>(y, x) < tempThresholdingValue)) {
				imgResult.at<uchar>(y, x) = 0;
			}
			else {
				imgResult.at<uchar>(y, x) = 255;
			}
		}
	}

	*thresholidngValue = tempThresholdingValue;
	MatToKScScalarImage2dUint8(imgResult, outputImg);

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


