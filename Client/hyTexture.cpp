#include "hyTexture.h"
#include "hyApplication.h"
#include "hyResources.h"
#include "hyGameObject.h"
#include "hyTransform.h"
//#include "hyCamera.h"

extern hy::Application application;

namespace hy
{
	Texture::Texture()
		: mImage(nullptr)
		, mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
		, mType(eTextureType::None)
		//, mbAffectCamera(true)

	{
	}
	Texture::~Texture()			// 메모리 릭을 방지하기 위해
	{
		delete mImage;
		mImage = nullptr;

		DeleteObject(mBitmap);
		mBitmap = NULL;
	}

	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
	{
		Texture* image = Resources::Find<Texture>(name);
		if (image != nullptr)
			return image;

		image = new Texture();
		image->SetWidth(width);
		image->SetHeight(height);
		HDC hdc = application.GetHdc();
		HBITMAP bitmap = CreateCompatibleBitmap(hdc, width, height);
		image->SetHBitmap(bitmap);

		HDC bitmapHdc = CreateCompatibleDC(hdc);
		image->SetHdc(bitmapHdc);

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(bitmapHdc, bitmap);
		DeleteObject(defaultBitmap);

		image->SetName(name);
		image->SetType(eTextureType::AlphaBmp);	
		Resources::Insert<Texture>(name, image);

		return image;
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

			if (info.bmBitsPixel == 32)
				mType = eTextureType::AlphaBmp;

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

	void Texture::Render(HDC hdc
		, Vector2 pos
		, Vector2 size
		, Vector2 leftTop
		, Vector2 rightBottom
		, Vector2 offset
		, Vector2 scale
		, float alpha
		, float rotate)
		
	{
		if (mBitmap == nullptr && mImage == nullptr)
			return;

		//if (mbAffectCamera)
		//	pos = Camera::CalculatePosition(pos);

		if (mType == eTextureType::Bmp)
		{
			TransparentBlt(hdc, (int)pos.x - (size.x * scale.x / 2.0f) + offset.x
				, (int)pos.y - (size.y * scale.y / 2.0f) + offset.y
				, size.x * scale.x
				, size.y * scale.y
				, mHdc
				, leftTop.x, leftTop.y, rightBottom.x, rightBottom.y
				, RGB(255, 0, 255));
		}
		else if (mType == eTextureType::AlphaBmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			// 0.0f ~ 1.0f -> 0 ~ 255
			// int alpha = 1.0f;
			alpha = (int)(alpha * 255.0f);

			if (alpha <= 0)
				alpha = 0;
			func.SourceConstantAlpha = alpha; // 0 ~ 255

			AlphaBlend(hdc, (int)pos.x - (size.x * scale.x / 2.0f) + offset.x
				, (int)pos.y - (size.y * scale.y / 2.0f) + offset.y
				, size.x * scale.x
				, size.y * scale.y
				, mHdc
				, leftTop.x, leftTop.y
				, rightBottom.x, rightBottom.y
				, func);
		}
		else if (mType == eTextureType::Png)
		{
			//// 내가 원하는 픽셀을 투명화 시킬떄
			Gdiplus::ImageAttributes imageAtt = {};
			//// 투명화 시킬 픽셀 색 범위
			imageAtt.SetColorKey(Gdiplus::Color(100, 100, 100)
				, Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);
			// 회전시키는 코드
			graphics.TranslateTransform((float)pos.x, (float)pos.y);
			graphics.RotateTransform(rotate);
			graphics.TranslateTransform(-(float)pos.x, -(float)pos.y);

			graphics.DrawImage(mImage
				, Gdiplus::Rect
				(
					(int)(pos.x - (size.x * scale.x / 2.0f) + offset.x)
					, (int)(pos.y - (size.y * scale.y / 2.0f) + offset.y)
					, (int)(size.x * scale.x)
					, (int)(size.y * scale.y)
				)
				, leftTop.x, leftTop.y
				, rightBottom.x, rightBottom.y
				, Gdiplus::UnitPixel
				, nullptr);
		}

		/*Rectangle(hdc
			, pos.x, pos.y
			, pos.x + 10, pos.y + 10);*/
	}
}


