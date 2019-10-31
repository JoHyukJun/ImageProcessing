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
#include "func02.h"

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
int CDECL func02(KScRgbImage2d* inputImg,KScRgbImage2d* outputImg)
{
	int dx = inputImg->GetXSize();
	int dy = inputImg->GetYSize();

	outputImg->Free();
	outputImg->Alloc(dx, dy);

	KScHsiImage2d *srcHsiImg = new KScHsiImage2d;
	KScHsiImage2d *dstHsiImg = new KScHsiImage2d;
	srcHsiImg->Alloc(dx, dy);
	dstHsiImg->Alloc(dx, dy);

	KScScalarImage2dFloat *Hue = new KScScalarImage2dFloat;
	KScScalarImage2dFloat *Saturation = new KScScalarImage2dFloat;
	KScScalarImage2dFloat *Intensity = new KScScalarImage2dFloat;
	Hue->Alloc(dx, dy);
	Saturation->Alloc(dx, dy);
	Intensity->Alloc(dx, dy);

	inputImg->ConvertToHsiImage(srcHsiImg);

	srcHsiImg->SplitAllPlane(Hue, Saturation, Intensity);

	KSdFloat **pArrayHue = Hue->Get2dArray();
	KSdFloat **pArraySaturation = Saturation->Get2dArray();
	KSdFloat **pArrayIntensity = Intensity->Get2dArray();

	for (int y = 0; y < dy; y++) {
		for (int x = 0; x < dx; x++) {
			if (pArrayHue[y][x] < 18 || pArrayHue[y][x] > 32) {
				if (pArraySaturation[y][x] < 0.7 || pArraySaturation[y][x] > 0.8) {
					if (pArrayIntensity[y][x] < 180 || pArrayIntensity[y][x] > 200) {
						pArrayHue[y][x] = 0;
						pArraySaturation[y][x] = 0;
						pArrayIntensity[y][x] = 0;
					}
				}
			}


			if (pArrayHue[y][x] < 0) {
				pArrayHue[y][x] == 0;
			}
			else if (pArrayHue[y][x] > 360) {
				pArrayHue[y][x] == 360;
			}

			if (pArraySaturation[y][x] < 0) {
				pArraySaturation[y][x] == 0;
			}
			else if (pArraySaturation[y][x] > 1) {
				pArraySaturation[y][x] == 1;
			}

			if (pArrayIntensity[y][x] < 0) {
				pArrayIntensity[y][x] == 0;
			}
			else if (pArrayIntensity[y][x] > 255) {
				pArrayIntensity[y][x] == 255;
			}
		}
	}

	dstHsiImg->MergeAllPlane(Hue, Saturation, Intensity);

	dstHsiImg->ConvertToRgbImage(outputImg);

	delete srcHsiImg;
	delete dstHsiImg;
	delete Hue;
	delete Saturation;
	delete Intensity;

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


