#include "hySpriteRenderer.h"
#include "hyTransform.h"
#include "hyGameObject.h"
#include "hyCamera.h"

namespace hy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mScale(Vector2::One)
		, mbAffectCamera(true)
		, mTexture(nullptr)
		, mAlpha(1.0f)	
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::Render(HDC hdc)
	{
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector2 pos = tr->GetPosition();

		///*Ellipse(hdc, 100 + pos.x, 100 + pos.y
		//	, 200 + pos.x, 200 + pos.y);*/

		//// 로드해온 이미지 그리기
		//TransparentBlt(hdc, (int)pos.x, (int)pos.y					// 그림을 그리는 위치
		//	, mImage->GetWidth(), mImage->GetHeight()		// *2 하면 사이즈 2배
		//	, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		//// RGB(255, 0, 255) 색으로 칠해진 부분을 지우고 

		if (mTexture == nullptr)									// mTexturer가 nullptr이면 프로그램이 고장남
			return;													// 그래서 만약 nullptr이면 리턴해서 함수 자체를 나가버림

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (mbAffectCamera)
			pos = Camera::CalculatePosition(pos);

		if (mTexture->GetType() == eTextureType::Bmp)				// bmp 파일일 때
		{
			if (mAlpha < 1.0f)
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				// 0.0f ~ 1.0f -> 0 ~ 255
				int alpha = (int)(mAlpha * 255.0f);
				if (alpha <= 0)
					alpha = 0;
				func.SourceConstantAlpha = alpha; // 0 ~ 255

				AlphaBlend(hdc, (int)pos.x - (mTexture->GetWidth() * mScale.x / 2.0f)
					, (int)pos.y - (mTexture->GetHeight() * mScale.y / 2.0f)
					, mTexture->GetWidth() * mScale.x
					, mTexture->GetHeight() * mScale.y
					, mTexture->GetHdc()
					, 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
					, func);
			}
			else
			{
				TransparentBlt(hdc, (int)pos.x - (mTexture->GetWidth() * mScale.x / 2.0f)
					, (int)pos.y - (mTexture->GetHeight() * mScale.y / 2.0f)
					, mTexture->GetWidth() * mScale.x
					, mTexture->GetHeight() * mScale.y
					, mTexture->GetHdc()
					, 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
					, RGB(255, 0, 255));
			}
		}

		// TransparentBlt : 투명한 비트맵을 출력하는 데 사용
		// 출력할 비트맵의 시작 위치, 크기, 투명할 색상, 출력할 위치를 인자로 
		// 출력할 비트맵의 투명한 부분을 출력 X

		else if (mTexture->GetType() == eTextureType::Png)		// png 파일일 때
		{
			//// 내가 원하는 픽셀을 투명화 시킬떄
			//Gdiplus::ImageAttributes imageAtt = {};

			//// 투명화 시킬 픽셀 색 범위
			//imageAtt.SetColorKey(Gdiplus::Color(100,100,100)
			//	, Gdiplus::Color(255,255,255));

			//Gdiplus::Graphics graphics(hdc);
			//graphics.DrawImage(mTexture->GetImage()
			//	, Gdiplus::Rect
			//	(
			//		(int)(pos.x - (mTexture->GetWidth() * mScale.x / 2.0f))
			//		, (int)(pos.y - (mTexture->GetHeight() * mScale.y / 2.0f))
			//		, (int)(mTexture->GetWidth() * mScale.x)
			//		, (int)(mTexture->GetHeight() * mScale.y)
			//	)
			//	, 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
			//	, Gdiplus::UnitPixel
			//	, &imageAtt);
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->GetImage()
				, (int)(pos.x - (mTexture->GetWidth() * mScale.x / 2.0f))
				, (int)(pos.y - (mTexture->GetHeight() * mScale.y / 2.0f))
				, (int)(mTexture->GetWidth() * mScale.x)
				, (int)(mTexture->GetHeight() * mScale.y));
		}
	}
}
