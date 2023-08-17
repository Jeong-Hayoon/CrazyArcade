#include "hyAlphaBlending.h"
#include "hySceneManager.h"
#include "hyResources.h"
#include "hyTime.h"



namespace hy
{
	AlphaBlending::AlphaBlending()
	{
	}
	AlphaBlending::~AlphaBlending()
	{
	}
	void AlphaBlending::Initialize()
	{
		mAlpha = 255;
		mImage = Resources::Load<Texture>(L"AlphaBlend", L"..\\Resources\\Image\\AlphaBlend\\AlphaBlender.bmp");
	}
	void AlphaBlending::Update()
	{
		mTime += Time::DeltaTime();
		mAlpha = mAlpha - mTime * 40;
		
	}

	void AlphaBlending::Render(HDC hdc)
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
			, mImage->GetWidth() * 1.4f
			, mImage->GetHeight() * 1.4f
			, mImage->GetHdc()
			, 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, func);



	}
}