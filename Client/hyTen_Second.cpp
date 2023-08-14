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
	Ten_Second::Ten_Second()
	{
		Animator* timeranimator = AddComponent<Animator>();

		Texture* Ten_Second_ = Resources::Load<Texture>(L"Ten_SecoundTimer"
			, L"..\\Resources\\Image\\UI\\Timer\\Ten_Second.bmp");

		timeranimator->CreateAnimation(L"Ten_SecoundTimer", Ten_Second_, Vector2(0.0f, 0.0f), Vector2(22.0f, 26.0f), 6, Vector2(0.0f, 0.0f), 10.f);
		timeranimator->SetScale(Vector2(0.7f, 0.9f));

		timeranimator->PlayAnimation(L"Ten_SecoundTimer", true);
	}
	Ten_Second::~Ten_Second()
	{
	}
	void Ten_Second::Initialize()
	{

	}
	void Ten_Second::Update()
	{
		GameObject::Update();
	}
	void Ten_Second::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

}