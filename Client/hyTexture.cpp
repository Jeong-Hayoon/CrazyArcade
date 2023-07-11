#include "hyTexture.h"
#include "hyApplication.h"


extern hy::Application application;

namespace hy
{
	Texture::Texture()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
		, mType(eTextureType::None)
	{
	}
	Texture::~Texture()			// 메모리 릭을 방지하기 위해
	{
		delete mImage;
		mImage = nullptr;

		DeleteObject(mBitmap);
		mBitmap = NULL;
	}
	HRESULT Texture::Load(const std::wstring& path)			// LoadImageW : 2바이트 글자를 불러들이는 함수
	{
		std::wstring ext
			= path.substr(path.find_last_of(L".") + 1);				// 맨뒤 글자를 가져와주는 함수

		if (ext == L"bmp")		// 맨뒤에서 세글자가 bmp이면
		{
			mType = eTextureType::Bmp;

			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
				, LR_LOADFROMFILE | LR_CREATEDIBSECTION);	//HBITMAP 비트맵 파일, 인스턴스는 nullptr 넣으면 알아서 해줌, 
			//path.c_str() : 실제 할당된 메모리의 주소 반환, 반환값이 핸들이기 때문에 비트맵으로 강제 캐스팅

			if (mBitmap == nullptr)			// 이미지가 없으면 nullptr 반환	-> 이미지 로드 실패
				return E_FAIL;

			BITMAP info = {};			// 이미지에 대한 정보
			GetObject(mBitmap, sizeof(BITMAP), &info);	// 이미지에 대한 정보를 info에 넣어주는 함수

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();			// 이미지에 접근할 수 있는 DC 필요(한 이미지당 DC 1개)
			mHdc = CreateCompatibleDC(mainDC);		// DC 하나를 더 만드렴녀 원본 DC가 있었어야 함(메인 DC를 넣어주면 DC를 하나 더 만들어줌)

			HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);		// 이미지와 DC 연결
			DeleteObject(deafultBitmap);				// deafultBitmap은 수정이 불가능하니까 
		}															// 수정이 불가능한것을 가능한 것으로 바꿔준 것


		else if (ext == L"png")			// 맨뒤에서 세글자가 png이면(png의 경우 gdiplus 헤더 추가 해야함)
		{
			mType = eTextureType::Png;

			// image.png 파일을 이용하여 Texture 객체를 생성
			mImage = Gdiplus::Image::FromFile(path.c_str());		// 이미지 로드

			mWidth = mImage->GetWidth();								// 이미지 로드할 때 크기와 길이
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}
}


