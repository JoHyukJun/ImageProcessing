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

#include "KScOpenCvUtils.h"


using namespace std;
using namespace cv;

// DLL �ܺο��� ȣ���ϱ� ���ؼ� �ʿ��� �κ� ...
extern "C" __declspec( dllexport )
int CDECL jAgeChecker(KScUserDefineArray* par0, int* par1, KScUserDefineArray* par2);

// 2 �� �̻��� �Լ��� export �� ���, �Ʒ��� �������� �����մϴ�.


const string underAge = "Age is limited in watching video.";
const string overAge = "It's a possible age for watching videos.";
const string ageInfo = "YOUR AGE IS ";

Point printLocation;
Point printAgeLocation;


string AgeParser(int inAge);