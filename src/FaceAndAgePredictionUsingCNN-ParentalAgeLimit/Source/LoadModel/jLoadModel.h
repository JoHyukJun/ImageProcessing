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
#include <opencv2/dnn.hpp>
#include <string>

using namespace cv;
using namespace cv::dnn;
using namespace std;

// DLL �ܺο��� ȣ���ϱ� ���ؼ� �ʿ��� �κ� ...
extern "C" __declspec( dllexport )
int CDECL jLoadModel(KScUserDefineArray* par0, KScUserDefineArray* par1, KScUserDefineArray* par2);

// 2 �� �̻��� �Լ��� export �� ���, �Ʒ��� �������� �����մϴ�.


