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
#include "jAgeChecker.h"

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
int CDECL jAgeChecker(KScUserDefineArray* src_uda, int* inAge, KScUserDefineArray* dst_uda)
{
	// Get the source image
	KScMatType_cv *matSrcPtr = NULL;
	matSrcPtr = GetNewObjFromUDA(matSrcPtr, src_uda); // Convert UserDefinedType to Mat Type
	if (matSrcPtr == NULL) {  // if NULL, pointer is empty or different data type
		::MessageBox(NULL, "ERROR: Type Mismatched or Memory not Initializated", "jFaceAnalysis", MB_OK);
		return FALSE;
	}
	// create the output image
	KScMatType_cv *matDstPtr = NULL;
	matDstPtr = AttachNewObjToUDA(matDstPtr, dst_uda);  // define Mat for User define Array

	Mat frame = matSrcPtr->image.clone();

	matDstPtr->image = cv::Mat::zeros(matSrcPtr->image.size(), matSrcPtr->image.type());

	printLocation.x = 10;
	printLocation.y = 40;
	printAgeLocation.x = frame.rows / 2;
	printAgeLocation.y = frame.cols / 2;

	int ageVal = *inAge;

	string ageStr = AgeParser(ageVal);

	if (ageVal < 3) {
		putText(matDstPtr->image, underAge, printLocation, cv::FONT_HERSHEY_SIMPLEX, 0.9, Scalar(255, 255, 255), 2, cv::LINE_AA);
		putText(matDstPtr->image, ageInfo + ageStr, printAgeLocation, cv::FONT_HERSHEY_SIMPLEX, 2.0, Scalar(255, 255, 255), 2, cv::LINE_AA);
	}
	else {
		matDstPtr->image = frame.clone();
	}

	return TRUE;
}


string AgeParser(int inAge) {
	string stringAge = "";

	switch (inAge)
	{
	case 0:
		stringAge = "(0-2)";
		break;
	case 1:
		stringAge = "(4-6)";
		break;
	case 2:
		stringAge = "(8-12)";
		break;
	case 3:
		stringAge = "(15-20)";
		break;
	case 4:
		stringAge = "(25-32)";
		break;
	case 5:
		stringAge = "(38-43)";
		break;
	case 6:
		stringAge = "(48-53)";
		break;
	case 7:
		stringAge = "(60-100)";
		break;

	default:
		break;
	}

	return stringAge;
}