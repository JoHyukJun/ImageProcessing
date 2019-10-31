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
#include "jFaceAnalysis.h"

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


tuple<Mat, vector<vector<int>>> getFaceBox(Net net, Mat &frame, double faceConfidenceThreshold) {
	Mat frameFull = frame.clone();
	int frameHeight = frameFull.rows;
	int frameWidth = frameFull.cols;
	double inScaleFactor = 1.0;
	Size size = Size(300, 300);

	// ���� ��� ��.
	Scalar meanVal = Scalar(104, 117, 123);

	cv::Mat inputBlob;
	// blob ��ü�� 1 * 3 * 300 * 300 ������ 4���� ���.
	// net ��ü�� �Է����� ���.
	inputBlob = cv::dnn::blobFromImage(frameFull, inScaleFactor, size, meanVal, true, false);

	net.setInput(inputBlob, "data");

	// detection �� 1 * 1 * N * 7 ũ���� 4���� ���.
	// ó�� �� ���� ���� ũ��� �׻� 1�̰�, �� ��° ���� ũ��� �׻� 7, N �� ����� �� �ĺ� ���� ����.
	// �ִ� 200�� ���� ���� ����.
	cv::Mat detection = net.forward("detection_out");

	// 1, 2 ���� ũ��� �׻� 1�̹Ƿ� detection �� 3, 4 ������ �̿��Ͽ� ���ο� 2���� ��� ����.
	// N * 7 ũ���� 2���� �࿭(TYPE : CV_32F).
	// ����� 0��, 1�� ������ �׻� 0�� 1 ���� -> 2��° ������ face confidence ����.
	// confidence �� 0���� 1 ������ float �� ����.
	// ���� ���ɼ��� ������ 1�� ����� ������ ����.
	// 3������ 6�� ������ �� ���� �簢�� ���� ��� ��ǥ (x1, y1) �� ���� �ϴ� ��ǥ (x2, y2) ����.
	// �簢�� ��ǥ�� ������ ���ο� ���� ũ�⸦ 1�� ����ȭ�Ͽ� ����� ��ǥ�̹Ƿ� ���� �ȼ� ��ǥ�� ������ ���� �� ���� ũ�⸦ ���ؼ� ���.
	// �� ���� face confidence �� ���� ������� ����.
	// ���� �����鼭 face confidence �� �Ӱ谪�� �������� ���.
	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

	// ���� ��� ��ǥ (x1, y1), ���� �ϴ� ��ǥ (x2, y2).
	vector<vector<int>> bboxes;


	// Draw Rectangle.
	for (int i = 0; i < detectionMat.rows; i++)
	{
		// face confidence 0���� 1������ float.
		float faceConfidence = detectionMat.at<float>(i, 2);

		if (faceConfidence > faceConfidenceThreshold)
		{
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);
			vector<int> box = { x1, y1, x2, y2 };
			bboxes.push_back(box);

			// �簢�� �׸���.
			cv::rectangle(frameFull, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 255), 2, 4);
		}
	}

	return make_tuple(frameFull, bboxes);
}


// �Լ��� ���� �κ�
int CDECL jFaceAnalysis(KScUserDefineArray* faceModel, KScUserDefineArray* genderModel, KScUserDefineArray* ageModel, KScUserDefineArray* src_uda, KScUserDefineArray* dst_uda, int* outGender, int* outAge)
{
	// Get the source image
	KScMatType_cv *matSrcPtr = NULL;
	matSrcPtr = GetNewObjFromUDA(matSrcPtr, src_uda); // Convert UserDefinedType to Mat Type
	if (matSrcPtr == NULL) {  // if NULL, pointer is empty or different data type
		::MessageBox(NULL, "ERROR: Type Mismatched or Memory not Initializated", "jFaceAnalytics", MB_OK);
		return FALSE;
	}

	// Create the output image.
	KScMatType_cv *matDstPtr = NULL;
	matDstPtr = AttachNewObjToUDA(matDstPtr, dst_uda);  // define Mat for User define Array


	// Get the face model.
	JoModelReader *faceNet = NULL;
	faceNet = GetNewObjFromUDA(faceNet, faceModel); // Convert UserDefinedType to Net Type
	if (faceNet == NULL) {  // if NULL, pointer is empty or different data type
		::MessageBox(NULL, "ERROR: Type Mismatched or Memory not Initializated", "jFaceAnalytics", MB_OK);
		return FALSE;
	}

	// Get the gender model.
	JoModelReader *genderNet = NULL;
	genderNet = GetNewObjFromUDA(genderNet, genderModel); // Convert UserDefinedType to Net Type
	if (genderNet == NULL) {  // if NULL, pointer is empty or different data type
		::MessageBox(NULL, "ERROR: Type Mismatched or Memory not Initializated", "jFaceAnalytics", MB_OK);
		return FALSE;
	}

	// Get the age model.
	JoModelReader *ageNet = NULL;
	ageNet = GetNewObjFromUDA(ageNet, ageModel); // Convert UserDefinedType to Net Type
	if (ageNet == NULL) {  // if NULL, pointer is empty or different data type
		::MessageBox(NULL, "ERROR: Type Mismatched or Memory not Initializated", "jFaceAnalytics", MB_OK);
		return FALSE;
	}

	Mat frame = matSrcPtr->image.clone();

	vector<vector<int>> bboxes;
	Mat frameFace;

	// Get face box.
	// face confiden threshold value �� 0.7 �� ����
	tie(frameFace, bboxes) = getFaceBox(faceNet->face_Model, frame, 0.7);

	// System error.
	if (bboxes.size() == 0) {
		::MessageBox(NULL, "ERROR: No face detected, checking next frame.", "jFaceAnalytics", MB_OK);
		return FALSE;
	}

	// Age, Gender prediction.
	for (auto it = begin(bboxes); it != end(bboxes); ++it) {
		Rect rec(it->at(0) - padding, it->at(1) - padding, it->at(2) - it->at(0) + 2 * padding, it->at(3) - it->at(1) + 2 * padding);

		// take the ROI of box on the frame.
		Mat face = frame(rec);

		Mat blob;
		// blob ��ü�� 1 * 3 * 277 * 277 ������ 4���� ��� -> net ��ü�� �Է����� ���.
		blob = blobFromImage(face, 1, Size(227, 227), MODEL_MEAN_VALUES, false);

		// Finding gender.
		genderNet->gender_Model.setInput(blob);
		vector<float> genderPreds = genderNet->gender_Model.forward();

		// Find max element index.
		int max_index_gender = std::distance(genderPreds.begin(), max_element(genderPreds.begin(), genderPreds.end()));
		string gender = genderList[max_index_gender];
		GenderParser(gender, outGender);

		// Finding age.
		ageNet->age_Model.setInput(blob);
		vector<float> agePreds = ageNet->age_Model.forward();

		// Finding maximum indicd in the age_preds vector.
		int max_indice_age = std::distance(agePreds.begin(), max_element(agePreds.begin(), agePreds.end()));
		string age = ageList[max_indice_age];
		AgeParser(age, outAge);

		// Label to put in the image.
		string label = "[ Gender : " + gender + ", Age : " + age + "]";
		cv::putText(frameFace, label, Point(it->at(0), it->at(1) - 15), cv::FONT_HERSHEY_PLAIN, 1.2, Scalar(0, 255, 0), 2, cv::LINE_AA);

	}


	// Full frame image.
	matDstPtr->image = frameFace.clone();

	return TRUE;
}


void GenderParser(string inGender, int* outGender) {
	if (inGender == "Male") {
		*outGender = 0;
	}
	else if (inGender == "Female") {
		*outGender = 1;
	}

	return;
}


void AgeParser(string inAge, int* outAge) {
	if (inAge == "(0-2)") {
		*outAge = 0;
	}
	else if (inAge == "(4-6)") {
		*outAge = 1;
	}
	else if (inAge == "(8-12)") {
		*outAge = 2;
	}
	else if (inAge == "(15-20)") {
		*outAge = 3;
	}
	else if (inAge == "(25-32)") {
		*outAge = 4;
	}
	else if (inAge == "(38-43)") {
		*outAge = 5;
	}
	else if (inAge == "(48-53)") {
		*outAge = 6;
	}
	else if (inAge == "(60-100)") {
		*outAge = 7;
	}

	return;
}


int GenderAgeParser(int gender, int age) {
	if (gender == 0) {
		switch (age) {
		case 0:
			return 1;
			break;
		case 1:
			return 2;
			break;
		case 2:
			return 3;
			break;
		case 3:
			return 4;
			break;
		case 4:
			return 5;
			break;
		case 5:
			return 6;
			break;
		case 6:
			return 7;
			break;
		case 7:
			return 8;
			break;
		default:
			return 0;
			break;
		}

	}
	else if (gender == 1) {
		switch (age) {
		case 0:
			return 9;
			break;
		case 1:
			return 10;
			break;
		case 2:
			return 11;
			break;
		case 3:
			return 12;
			break;
		case 4:
			return 13;
			break;
		case 5:
			return 14;
			break;
		case 6:
			return 15;
			break;
		case 7:
			return 16;
			break;
		default:
			return 0;
			break;
		}
	}
}


