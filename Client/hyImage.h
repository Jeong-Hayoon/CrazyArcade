#pragma once
#include "hyResource.h"

namespace hy
{
	class Image : public Resource			// bmp파일을 불러와서 저장을 해야함 
	{
	public:
		Image();
		virtual ~Image();

		virtual HRESULT Load(const std::wstring& path) override;	// Load가 순수가상함수이기 때문에 무조건 오버라이딩 해줘야 함

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }

	private:			
		HBITMAP mBitmap;						// 비트맵 이미지 파일
		HDC mHdc;								// 이미지 파일 하나당 DC 필요
		UINT mWidth;								// 이미지 길이
		UINT mHeight;							//// 이미지 높이
	};
}
