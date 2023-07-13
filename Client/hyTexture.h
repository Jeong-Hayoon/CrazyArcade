#pragma once
#include "hyResource.h"

namespace hy
{
	enum class eTextureType
	{
		Bmp,
		AlphaBmp,
		Png,
		None,
	};

	class Texture : public Resource									// bmp파일을 불러와서 저장을 해야함 
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path) override;	// Load가 순수가상함수이기 때문에 무조건 오버라이딩 해줘야 함

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }
		eTextureType GetType() { return mType; }
		Gdiplus::Image* GetImage() { return mImage; }

	private:			
		eTextureType mType;
		Gdiplus::Image* mImage;			// png 파일이 저장될 변수
		
		HBITMAP mBitmap;						// 비트맵 이미지 파일
		HDC mHdc;								// 이미지 파일 하나당 DC 필요
		UINT mWidth;								// 이미지 길이
		UINT mHeight;							// 이미지 높이
	};
}
