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
#include "jHistogramSpecifiacation.h"
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
int CDECL jHistogramSpecifiacation(KScScalarImage2dUint8* inBackgroundImg, KScScalarImage2dUint8* inSequenceImg, KScScalarImage2dUint8* outputImg)
{
	int dx = inBackgroundImg->GetXSize();
	int dy = inBackgroundImg->GetYSize();

	outputImg->Free();
	outputImg->Alloc(dx, dy);

	Mat imgBackground = KScScalarImage2dUint8ToMat(inBackgroundImg);
	Mat imgSequence = KScScalarImage2dUint8ToMat(inSequenceImg);
	//Mat imgResult = KScScalarImage2dUint8ToMat(outputImg);


	// Threshold of histogram difference.
	const float HISTMATCH = 0.000001;
	double minVal, maxVal;

	int histSize = 255;
	float range[] = { 0, 255 };
	const float* histRange = { range };
	bool uniform = true;
	bool accumulate = false;
	const int* channelNumber = { 0 };

	Mat refHist, tgtHist;
	Mat refCDF, tgtCDF;

	calcHist(&imgBackground, 1, channelNumber, Mat(), refHist, 1, &histSize, &histRange);
	calcHist(&imgSequence, 1, channelNumber, Mat(), tgtHist, 1, &histSize, &histRange);

	minMaxLoc(refHist, &minVal, &maxVal);

	if (maxVal == 0) {
		std::cerr << "ERROR: maxVal is 0 in refHist" << std::endl;
	}

	normalize(refHist, refHist, minVal / maxVal, 1.0, NORM_MINMAX);

	refHist.copyTo(refCDF);
	tgtHist.copyTo(tgtCDF);

	float *srcCDFData = refCDF.ptr<float>();
	float *dstCDFData = tgtCDF.ptr<float>();

	for (int j = 1; j < 256; j++) {
		srcCDFData[j] += srcCDFData[j - 1];
		dstCDFData[j] += dstCDFData[j - 1];
	}

	minMaxLoc(refCDF, &minVal, &maxVal);
	normalize(refCDF, refCDF, minVal / maxVal, 1.0, NORM_MINMAX);
	minMaxLoc(tgtCDF, &minVal, &maxVal);
	normalize(tgtCDF, tgtCDF, minVal / maxVal, 1.0, NORM_MINMAX);

	// Lookup table.
	Mat lut(1, 256, CV_8UC1);
	uchar *M = lut.ptr<uchar>();
	uchar last = 0;

	for (int i = 0; i < tgtCDF.rows; i++) {
		float F1 = dstCDFData[i];

		// Benchmarking.
		for (uchar j = last; j < refCDF.rows; j++) {
			float F2 = srcCDFData[j];

			if (abs(F2 - F1) < HISTMATCH || F2 > F1) {
				M[i] = j;
				last = j;

				break;
			}
		}
	}

	LUT(imgSequence, lut, imgSequence);

	MatToKScScalarImage2dUint8(imgSequence, outputImg);

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


