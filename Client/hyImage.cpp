#include "hyImage.h"
#include "hyApplication.h"


extern hy::Application application;

namespace hy
{
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}
	Image::~Image()
	{
	}
	HRESULT Image::Load(const std::wstring& path)			// LoadImageW : 2����Ʈ ���ڸ� �ҷ����̴� �Լ�
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);	//HBITMAP ��Ʈ�� ����, �ν��Ͻ��� nullptr ������ �˾Ƽ� ����, 
																					//path.c_str() : ���� �Ҵ�� �޸��� �ּ� ��ȯ, ��ȯ���� �ڵ��̱� ������ ��Ʈ������ ���� ĳ����

		if (mBitmap == nullptr)		// �̹����� ������ nullptr ��ȯ	-> �̹��� �ε� ����
			return E_FAIL;

		BITMAP info = {};			// �̹����� ���� ����
		GetObject(mBitmap, sizeof(BITMAP), &info);			// �̹����� ���� ������ info�� �־��ִ� �Լ�

		mWidth = info.bmWidth;
		mHeight = info.bmHeight;

		HDC mainDC = application.GetHdc();					// �̹����� ������ �� �ִ� DC �ʿ�(�� �̹����� DC 1��)
		mHdc = CreateCompatibleDC(mainDC);				// DC �ϳ��� �� ����ų� ���� DC�� �־���� ��(���� DC�� �־��ָ� DC�� �ϳ� �� �������)

		HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);		// �̹����� DC ����
		DeleteObject(deafultBitmap);		// deafultBitmap�� ������ �Ұ����ϴϱ� 
														// ������ �Ұ����Ѱ��� ������ ������ �ٲ��� ��

		return S_OK;
	}
}


