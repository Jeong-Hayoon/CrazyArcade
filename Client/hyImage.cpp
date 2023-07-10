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
	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)		// �̹����� ������ nullptr ��ȯ	-> �̹��� �ε� ����
			return S_FALSE;

		BITMAP info = {};			// �̹����� ���� ����
		GetObject(mBitmap, sizeof(BITMAP), &info);		// �̹����� ���� ������ info�� �־��ִ� �Լ�

		mWidth = info.bmWidth;
		mHeight = info.bmHeight;

		HDC mainDC = application.GetHdc();				// �ε忡 ������ �� �ִ� DC �ʿ�
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(deafultBitmap);

		return S_OK;
	}
}


