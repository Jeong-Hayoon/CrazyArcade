#include "hyMinutes.h"
#include "hyTen_Second.h"
#include "hySecond.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyUI.h"
#include "hyObject.h"
#include "hyTime.h"
#include "hySpriteRenderer.h"
#include "hyTransform.h"
#include "hyAnimator.h"


namespace hy
{
	Minutes::Minutes()
	{
		Animator* timeranimator = AddComponent<Animator>();

		Texture* Minutes = Resources::Load<Texture>(L"MinutesTimer"
			, L"..\\Resources\\Image\\UI\\Timer\\Minutes.bmp");

		timeranimator->CreateAnimation(L"MinutesTimer", Minutes, Vector2(0.0f, 0.0f), Vector2(22.0f, 26.0f), 4, Vector2(0.0f, 0.0f), 60.f);
		timeranimator->SetScale(Vector2(0.7f, 0.9f));

		timeranimator->PlayAnimation(L"MinutesTimer", false);
	}
	Minutes::~Minutes()
	{
	}
	void Minutes::Initialize()
	{
	}
	void Minutes::Update()
	{
		GameObject::Update();
	}
	void Minutes::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}