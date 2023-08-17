#include "hyLogo.h"
#include "hySceneManager.h"
#include "hyResources.h"
#include "hyTexture.h"
#include "hyTime.h"

namespace hy
{
	Logo::Logo()
	{
	}
	Logo::~Logo()
	{
	}
	void Logo::Initialize()
	{
		mImage = Resources::Load<Texture>(L"Logo_BG", L"..\\Resources\\Image\\Bg\\Logo.bmp");

	}
	void Logo::Update()
	{
		mTime += Time::DeltaTime();

		if (mAlpha > 255 && IsTransparent == false)
		{
			IsTransparent = true;
			mTime = 0;
		}

		if (mAlpha <= 255 && IsTransparent == false)
		{
			mAlpha = mTime * 90;
		}
		else if (IsTransparent == true)
		{
			mAlpha = 255 - mTime * 90;
		}
	}
	void Logo::Render(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;

		if (mAlpha >= 255)
		{
			func.SourceConstantAlpha = 255;
		}
		else if (mAlpha < 255 && mAlpha >= 0)
		{
			func.SourceConstantAlpha = mAlpha;
		}
		else if (mAlpha <= 0)
		{
			func.SourceConstantAlpha = 0;
		}

		AlphaBlend(hdc, 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, func);


	}

}