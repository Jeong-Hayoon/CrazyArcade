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
	Texture::~Texture()
	{
		delete mImage;
		mImage = nullptr;

		DeleteObject(mBitmap);
		mBitmap = NULL;
	}
	HRESULT Texture::Load(const std::wstring& path)			// LoadImageW : 2����Ʈ ���ڸ� �ҷ����̴� �Լ�
	{
		std::wstring ext
			= path.substr(path.find_last_of(L".") + 1);
		if (ext == L"bmp")
		{
			mType = eTextureType::Bmp;
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
				, LR_LOADFROMFILE | LR_CREATEDIBSECTION);	//HBITMAP ��Ʈ�� ����, �ν��Ͻ��� nullptr ������ �˾Ƽ� ����, 
			//path.c_str() : ���� �Ҵ�� �޸��� �ּ� ��ȯ, ��ȯ���� �ڵ��̱� ������ ��Ʈ������ ���� ĳ����

			if (mBitmap == nullptr)		// �̹����� ������ nullptr ��ȯ	-> �̹��� �ε� ����
				return E_FAIL;

			BITMAP info = {};			// �̹����� ���� ����
			GetObject(mBitmap, sizeof(BITMAP), &info);	// �̹����� ���� ������ info�� �־��ִ� �Լ�

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();			// �̹����� ������ �� �ִ� DC �ʿ�(�� �̹����� DC 1��)
			mHdc = CreateCompatibleDC(mainDC);			// DC �ϳ��� �� ����ų� ���� DC�� �־���� ��(���� DC�� �־��ָ� DC�� �ϳ� �� �������)

			HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);		// �̹����� DC ����
			DeleteObject(deafultBitmap);				// deafultBitmap�� ������ �Ұ����ϴϱ� 
		}												// ������ �Ұ����Ѱ��� ������ ������ �ٲ��� ��
		else if (ext == L"png")
		{
			mType = eTextureType::Png;
			// image.png ������ �̿��Ͽ� Texture ��ü�� �����մϴ�.
			mImage = Gdiplus::Image::FromFile(path.c_str());

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}
}


