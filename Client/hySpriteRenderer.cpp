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

		TransparentBlt(hdc, (int)pos.x, (int)pos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
}
