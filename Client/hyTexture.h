#pragma once
#include "hyResource.h"

namespace hy
{
	using namespace math;

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

		static Texture* Create(const std::wstring& name, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring& path) override;	// Load가 순수가상함수이기 때문에 무조건 오버라이딩 해줘야 함

		void Render(HDC hdc
			, Vector2 pos
			, Vector2 size
			, Vector2 leftTop
			, Vector2 rightBottom
			, Vector2 offset = Vector2::Zero
			, Vector2 scale = Vector2::One
			, float alpha = 1.0f
			, float rotate = 0.0f);

		COLORREF GetTexturePixel(int x, int y);	

		UINT GetWidth() { return mWidth; }
		void SetWidth(UINT width) { mWidth = width; }
		UINT GetHeight() { return mHeight; }
		void SetHeight(UINT height) { mHeight = height; }

		HDC GetHdc() { return mHdc; }
		eTextureType GetType() { return mType; }
		void SetType(eTextureType type) { mType = type; }
		Gdiplus::Image* GetImage() { return mImage; }
		void SetHBitmap(HBITMAP bitmap) { mBitmap = bitmap; }
		void SetHdc(HDC hdc) { mHdc = hdc; }
		HBITMAP GetHBitmap() { return mBitmap; }

	private:			
		eTextureType mType;
		Gdiplus::Image* mImage;			// png 파일이 저장될 변수
		
		HBITMAP mBitmap;				// 비트맵 이미지 파일
		HDC mHdc;						// 이미지 파일 하나당 DC 필요
		UINT mWidth;					// 이미지 길이
		UINT mHeight;					// 이미지 높이
		// bool mbAffectCamera;
		//float mRotate;


	};
}
