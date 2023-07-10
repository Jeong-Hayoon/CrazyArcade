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

		if (mBitmap == nullptr)		// 이미지가 없으면 nullptr 반환	-> 이미지 로드 실패
			return S_FALSE;

		BITMAP info = {};			// 이미지에 대한 정보
		GetObject(mBitmap, sizeof(BITMAP), &info);		// 이미지에 대한 정보를 info에 넣어주는 함수

		mWidth = info.bmWidth;
		mHeight = info.bmHeight;

		HDC mainDC = application.GetHdc();				// 로드에 접근할 수 있는 DC 필요
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(deafultBitmap);

		return S_OK;
	}
}


