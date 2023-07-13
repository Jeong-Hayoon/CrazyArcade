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

		virtual HRESULT Load(const std::wstring& path) override;	// Load�� ���������Լ��̱� ������ ������ �������̵� ����� ��

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }
		eTextureType GetType() { return mType; }
		Gdiplus::Image* GetImage() { return mImage; }

	private:			
		eTextureType mType;
		Gdiplus::Image* mImage;			// png ������ ����� ����
		
		HBITMAP mBitmap;						// ��Ʈ�� �̹��� ����
		HDC mHdc;								// �̹��� ���� �ϳ��� DC �ʿ�
		UINT mWidth;								// �̹��� ����
		UINT mHeight;							// �̹��� ����
	};
}
