#include "hyGameStart.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hySpriteRenderer.h"
#include "hyResources.h"
#include "hyAnimation.h"
#include "hyAnimator.h"
#include "hySceneManager.h"
#include "hySound.h"

namespace hy
{
	GameStart::GameStart()
		: GameTime(0.f)
		, Start(false)
		, Stop(false)
	{
	}
	GameStart::~GameStart()
	{
	}
	void GameStart::Initialize()
	{
		Resources::Load<Sound>(L"GameStart", L"..\\Resources\\Sound\\Sound\\game_start.wav");
		Resources::Find<Sound>(L"GameStart")->Play(false);

		Animator* spt = AddComponent<Animator>();
		spt->CreateAnimationFolder(L"Game", L"..\\Resources\\Image\\Game_Start\\Game", Vector2::Zero, 0.2f);
		spt->CreateAnimationFolder(L"Start", L"..\\Resources\\Image\\Game_Start\\Start", Vector2::Zero, 0.2f);
		spt->SetScale(Vector2(0.8f, 0.8f));

	}

	void GameStart::Update()
	{
		Animator* spt = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Vector2 Pos = tr->GetPosition();
		if (Pos.x <= 200.0f)
		{
			if (Start == false)
			{
				spt->PlayAnimation(L"Game", false);
				Start = true;
			}
			Pos.y += 650.0f * Time::DeltaTime();
		}
		else if (Pos.x >= 250.0f)
		{
			if (Start == false)
			{
				spt->SetScale(Vector2(0.65f, 0.65f));
				spt->PlayAnimation(L"Start", false);
				Start = true;
			}
			Pos.y -= 650.0f * Time::DeltaTime();
		}

		if (Stop == false)
		{
			tr->SetPosition(Pos);
		}

		if (Pos.y >= 300.0f && Pos.x <= 200.0f)
		{
			Stop = true;
		}
		else if (Pos.y <= 300.0f && Pos.x >= 250.0f)
		{
			Stop = true;
		}

		GameTime += Time::DeltaTime();

		if (GameTime >= 1.5f)
		{
			Destroy(this);
		}

		GameObject::Update();

	}

	void GameStart::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}