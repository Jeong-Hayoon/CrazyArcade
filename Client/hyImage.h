#pragma once
#include "hyResource.h"

namespace hy
{
	class Image : public Resource
	{
	public:
		Image();
		virtual ~Image();

		virtual HRESULT Load(const std::wstring& path) override;	// Load�� ���������Լ��̱� ������ ������ �������̵� ����� ��

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
