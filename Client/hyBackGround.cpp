#include "hyBackGround.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hySpriteRenderer.h"

namespace hy
{
	BackGround::BackGround()
	{
	}
	BackGround::~BackGround()
	{
	}
	void BackGround::Initialize()
	{
	}

	void BackGround::Update()
	{
		GameObject::Update();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();

		float alpha = sr->GetAlpha();
		alpha -= 0.2f * Time::DeltaTime();
		sr->SetAlpha(alpha);
	}

	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}