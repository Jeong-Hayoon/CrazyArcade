#include "hySpriteRenderer.h"
#include "hyTransform.h"
#include "hyGameObject.h"

namespace hy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		/*Ellipse(hdc, 100 + pos.x, 100 + pos.y
			, 200 + pos.x, 200 + pos.y);*/

		// 로드해온 이미지 그리기
		TransparentBlt(hdc, (int)pos.x, (int)pos.y		// 그림을 그리는 위치
			, mImage->GetWidth(), mImage->GetHeight()		// *2 하면 사이즈 2배
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		// RGB(255, 0, 255) 색으로 칠해진 부분을 지우고 
	}
}
