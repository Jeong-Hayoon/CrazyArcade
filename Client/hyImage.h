#pragma once
#include "hyResource.h"

namespace hy
{
	class Image : public Resource
	{
	public:
		Image();
		virtual ~Image();

		virtual HRESULT Load(const std::wstring& path) override;	// Load가 순수가상함수이기 때문에 무조건 오버라이딩 해줘야 함

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}
