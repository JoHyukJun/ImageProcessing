//////////////////////////////////////////////////////////////////////////
//
// �� ȭ���� �Լ� ��Ͻ� �ڵ����� ������ ������Ʈ�Դϴ�.
//
// ����ڰ� ������ ���� ���, Project�� Setting...�� ������ �ʿ��ϹǷ�,
//
// �̴� ������ '�Լ� �ۼ���'�� ���� �ٶ��ϴ�.
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// KSClass ���̺귯���� ��ũ
//
//////////////////////////////////////////////////////////////////////////
//
// ��� ���ϰ� ���̺귯�� ���� �˻��� ���Ͽ�
// Visual Studio���� �޴� Tools - Options - Directories �ǿ���
// Show Directories for: �κ���
//     Include files���� KSClass�� Include�� ���丮��
//     Library files���� KSClass�� Lib       ���丮�� �����Ͽ��� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////////
//
// * ������
//
// Show Directories for: �κ���
//     Include files�� KSClass�� Include�� Lib ���丮�� ��� ������ ���,
//     ��ũ ���� �߻��Ѵ�.
//
//////////////////////////////////////////////////////////////////////////

#include "KSClass.h" // KSClass�鿡 ���� ���

#include <KScOpenCvUtils.h>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <iterator>


using namespace cv;
using namespace cv::dnn;
using namespace std;

// DLL �ܺο��� ȣ���ϱ� ���ؼ� �ʿ��� �κ� ...
extern "C" __declspec( dllexport )
int CDECL jFaceAnalysis(KScUserDefineArray* par0, KScUserDefineArray* par1, KScUserDefineArray* par2, KScUserDefineArray* par3, KScUserDefineArray* par4, int* par5, int* par6);

Scalar MODEL_MEAN_VALUES = Scalar(78.4263377603, 87.7689143744, 114.895847746);

vector<string> ageList = { "(0-2)", "(4-6)", "(8-12)", "(15-20)", "(25-32)", "(38-43)", "(48-53)", "(60-100)" };
vector<string> genderList = { "Male", "Female" };


int padding = 20;


void GenderParser(string inGender, int* outGender);


void AgeParser(string inAge, int* outAge);


int GenderAgeParser(int gender, int age);


