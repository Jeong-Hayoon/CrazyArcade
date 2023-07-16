#include "hyPlayer.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"

namespace hy
{
	Player::Player()
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
	}
	void Player::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		//Animator* anim = GetComponent<Animator>();
		Animator* Monsteranim = GetComponent<Animator>();


		if (Input::GetKey(eKeyCode::W))
		{
			//anim->PlayAnimation(L"BazziUp", true);
			Monsteranim->PlayAnimation(L"ForestMosterUp", true);
			pos.y -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			//anim->PlayAnimation(L"BazziLeft", true);
			Monsteranim->PlayAnimation(L"ForestMosterLeft", true);
			pos.x -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			//anim->PlayAnimation(L"BazziDown", true);
			Monsteranim->PlayAnimation(L"ForestMosterDown", true);
			pos.y += 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			//anim->PlayAnimation(L"BazziRight", true);
			Monsteranim->PlayAnimation(L"ForestMosterRight", true);
			pos.x += 300.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::K))
		{
			//anim->PlayAnimation(L"BazziDie", true);
			Monsteranim->PlayAnimation(L"ForestMonsterDie", true);
			pos.x += 300.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}

