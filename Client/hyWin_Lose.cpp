#include "hyWin_Lose.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hySpriteRenderer.h"
#include "hyAnimator.h"
#include "hyObject.h"
#include "hyResources.h"
#include "hySound.h"


namespace hy
{
	bool Win_Lose::Win_Lose_flag = false;

	Win_Lose::Win_Lose()
	{
	}
	Win_Lose::~Win_Lose()
	{
	}
	void Win_Lose::Initialize()
	{
		Texture* Win_ = Resources::Load<Texture>(L"WinImage"
			, L"..\\Resources\\Image\\UI\\Win\\Win.bmp");

		Texture* Lose_ = Resources::Load<Texture>(L"LoseImage"
			, L"..\\Resources\\Image\\UI\\Lose\\Lose.bmp");

		Animator* at = AddComponent<Animator>();

		at->CreateAnimation(L"WinAnimation", Win_, Vector2(0.0f, 0.0f), Vector2(300.0f, 54.0f), 1, Vector2(0.0f, 0.0f), 3.f);
		at->CreateAnimation(L"LoseAnimation", Lose_, Vector2(0.0f, 0.0f), Vector2(300.0f, 54.0f), 1, Vector2(0.0f, 0.0f), 3.f);

		Resources::Load<Sound>(L"Win", L"..\\Resources\\Sound\\Sound\\win.wav");
		Resources::Load<Sound>(L"Lose", L"..\\Resources\\Sound\\Sound\\lose.wav");
	}

	void Win_Lose::Update()
	{
		GameObject::Update();
	}

	void Win_Lose::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Win_Lose::Win()
	{
		Resources::Find<Sound>(L"Win")->Play(false);

		Animator* at = GetComponent<Animator>();

		at->PlayAnimation(L"WinAnimation", false);

		if (at->IsActiveAnimationComplete())
		{
			Win_Lose_flag = true;
		}


		// 배찌 Victory 상태 호출
	}

	void Win_Lose::Lose()
	{
		Resources::Find<Sound>(L"Lose")->Play(false);

		Animator* at = GetComponent<Animator>();

		at->PlayAnimation(L"LoseAnimation", false);

	}
}