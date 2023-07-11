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
	HRESULT Image::Load(const std::wstring& path)			// LoadImageW : 2바이트 글자를 불러들이는 함수
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);	//HBITMAP 비트맵 파일, 인스턴스는 nullptr 넣으면 알아서 해줌, 
																					//path.c_str() : 실제 할당된 메모리의 주소 반환, 반환값이 핸들이기 때문에 비트맵으로 강제 캐스팅

		if (mBitmap == nullptr)		// 이미지가 없으면 nullptr 반환	-> 이미지 로드 실패
			return E_FAIL;

		BITMAP info = {};			// 이미지에 대한 정보
		GetObject(mBitmap, sizeof(BITMAP), &info);			// 이미지에 대한 정보를 info에 넣어주는 함수

		mWidth = info.bmWidth;
		mHeight = info.bmHeight;

		HDC mainDC = application.GetHdc();					// 이미지에 접근할 수 있는 DC 필요(한 이미지당 DC 1개)
		mHdc = CreateCompatibleDC(mainDC);				// DC 하나를 더 만드렴녀 원본 DC가 있었어야 함(메인 DC를 넣어주면 DC를 하나 더 만들어줌)

		HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);		// 이미지와 DC 연결
		DeleteObject(deafultBitmap);		// deafultBitmap은 수정이 불가능하니까 
														// 수정이 불가능한것을 가능한 것으로 바꿔준 것

		return S_OK;
	}
}


