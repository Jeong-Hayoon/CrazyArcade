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

	class Texture : public Resource									// bmp������ �ҷ��ͼ� ������ �ؾ��� 
	{
	public:
		Texture();
		virtual ~Texture();

		static Texture* Create(const std::wstring& name, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring& path) override;	// Load�� ���������Լ��̱� ������ ������ �������̵� ����� ��

		UINT GetWidth() { return mWidth; }
		void SetWidth(UINT width) { mWidth = width; }
		UINT GetHeight() { return mHeight; }
		void SetHeight(UINT height) { mHeight = height; }

		HDC GetHdc() { return mHdc; }
		eTextureType GetType() { return mType; }
		Gdiplus::Image* GetImage() { return mImage; }
		void SetHBitmap(HBITMAP bitmap) { mBitmap = bitmap; }
		void SetHdc(HDC hdc) { mHdc = hdc; }

	private:			
		eTextureType mType;
		Gdiplus::Image* mImage;			// png ������ ����� ����
		
		HBITMAP mBitmap;						// ��Ʈ�� �̹��� ����
		HDC mHdc;								// �̹��� ���� �ϳ��� DC �ʿ�
		UINT mWidth;								// �̹��� ����
		UINT mHeight;							// �̹��� ����
	};
}
