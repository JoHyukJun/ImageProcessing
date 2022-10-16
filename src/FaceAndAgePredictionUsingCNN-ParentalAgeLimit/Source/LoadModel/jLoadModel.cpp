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
#include "jLoadModel.h"

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
int CDECL jLoadModel(KScUserDefineArray* outFaceModel, KScUserDefineArray* outGenderModel, KScUserDefineArray* outAgeModel)
{
	JoModelReader *facePtr = NULL;
	JoModelReader *genderPtr = NULL;
	JoModelReader *agePtr = NULL;


	// Model path.
	// Face model.
	string faceProto = "C:\\Program Files (x86)\\MTES2.0\\FMS\\JoHyukJun\\models\\opencv_face_detector.pbtxt";
	string faceModel = "C:\\Program Files (x86)\\MTES2.0\\FMS\\JoHyukJun\\models\\opencv_face_detector_uint8.pb";

	// Age model.
	string ageProto = "C:\\Program Files (x86)\\MTES2.0\\FMS\\JoHyukJun\\models\\age_deploy.prototxt";
	string ageModel = "C:\\Program Files (x86)\\MTES2.0\\FMS\\JoHyukJun\\models\\age_net.caffemodel";

	// Gender model.
	string genderProto = "C:\\Program Files (x86)\\MTES2.0\\FMS\\JoHyukJun\\models\\gender_deploy.prototxt";
	string genderModel = "C:\\Program Files (x86)\\MTES2.0\\FMS\\JoHyukJun\\models\\gender_net.caffemodel";

	facePtr = AttachNewObjToUDA(facePtr, outFaceModel);
	facePtr->face_Model = readNetFromTensorflow(faceModel, faceProto);

	genderPtr = AttachNewObjToUDA(genderPtr, outGenderModel);
	genderPtr->gender_Model = readNet(genderModel, genderProto);

	agePtr = AttachNewObjToUDA(agePtr, outAgeModel);
	agePtr->age_Model = readNet(ageModel, ageProto);

	return TRUE;
}