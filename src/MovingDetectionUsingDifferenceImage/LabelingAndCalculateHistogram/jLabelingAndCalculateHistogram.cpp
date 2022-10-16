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
#include "jLabelingAndCalculateHistogram.h"
#include "KScOpenCvUtils.h"

using namespace cv;

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
int CDECL jLabelingAndCalculateHistogram(KScScalarImage2dUint8* inputImg,KScScalarImage2dUint8* outputImg,KScScalarImage2dInt32* par2)
{
	int dx = inputImg->GetXSize();
	int dy = inputImg->GetYSize();

	outputImg->Alloc(dx, dy);

	Mat inputMat = KScScalarImage2dUint8ToMat(inputImg);


	// Labeling Image and Make Histogram. 
	Mat labelMat, stats, centrodis;
	int numOfLables = connectedComponentsWithStats(inputMat, labelMat, stats, centrodis, 8, CV_32S);

	int histogram[1000] = { 0, };

	for (int y = 0; y < labelMat.rows; y++) {
		int *label = labelMat.ptr<int>(y);

		for (int x = 0; x < labelMat.cols; x++) {
			if (label[x] == 0) {
				histogram[label[x]] = 0;
			}
			else {
				histogram[label[x]] += 1;
			}
		}
	}


	// Thresholding point that over histogram value.
	for (int i = 0; i < numOfLables; i++) {
		if (histogram[i] < 25) {
			for (int y = 0; y < labelMat.rows; y++) {
				int *tempLabel = labelMat.ptr<int>(y);
				uchar *pixel = inputMat.ptr<uchar>(y);

				for (int x = 0; x < labelMat.cols; x++) {
					if (tempLabel[x] == i) {
						pixel[x] = 0;

					}
				}
			}
		}
	}


	MatToKScScalarImage2dUint8(inputMat, outputImg);

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


