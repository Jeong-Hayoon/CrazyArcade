#include "hySpriteRenderer.h"
#include "hyTransform.h"
#include "hyGameObject.h"

namespace hy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mScale(Vector2::One)
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

		if (mTexture == nullptr)									// 이부분 질문
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (mTexture->GetType() == eTextureType::Bmp)				// bmp 파일일 때
		{
			TransparentBlt(hdc, (int)pos.x, (int)pos.y
				, mTexture->GetWidth() * mScale.x, mTexture->GetHeight() * mScale.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
		}

		// TransparentBlt : 투명한 비트맵을 출력하는 데 사용
		// 출력할 비트맵의 시작 위치, 크기, 투명할 색상, 출력할 위치를 인자로 
		// 출력할 비트맵의 투명한 부분을 출력 X

		else if (mTexture->GetType() == eTextureType::Png)		// png 파일일 때
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->GetImage(), (int)pos.x, (int)pos.y
				, (int)(mTexture->GetWidth() * mScale.x)
				, (int)(mTexture->GetHeight() * mScale.y));
		}
	}
}
