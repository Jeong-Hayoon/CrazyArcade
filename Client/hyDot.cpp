#include "hyDot.h"
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
	Timer_Dot::Timer_Dot()
	{
		Animator* timeranimator = AddComponent<Animator>();

		Texture* Dot = Resources::Load<Texture>(L"TimerDot"
			, L"..\\Resources\\Image\\UI\\Timer\\Dot\\Dot.bmp");

		timeranimator->CreateAnimation(L"TimerDot", Dot, Vector2(0.0f, 0.0f), Vector2(22.0f, 26.0f), 1, Vector2(0.0f, 0.0f), 1.f);
		timeranimator->SetScale(Vector2(0.7f, 0.9f));
		timeranimator->PlayAnimation(L"TimerDot", true);


	}
	Timer_Dot::~Timer_Dot()
	{
	}
	void Timer_Dot::Initialize()
	{
	}
	void Timer_Dot::Update()
	{
		GameObject::Update();
	}
	void Timer_Dot::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}