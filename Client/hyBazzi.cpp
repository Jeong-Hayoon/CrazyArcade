#include "hyBazzi.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
// #include "hyForestMap1.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"

namespace hy
{
	Bazzi::Bazzi()
	{
	}
	Bazzi::~Bazzi()
	{
	}
	void Bazzi::Initialize()
	{

		Texture* Bazzi_ = Resources::Load<Texture>(L"Bazzi"
			, L"..\\Resources\\Image\\Bazzi\\Bazzi.bmp");

		/*bazzi->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));*/

		Animator* at = AddComponent<Animator>();
		at->CreateAnimation(L"BazziIdle", Bazzi_, Vector2(0.0f, 0.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.6f);
		at->CreateAnimation(L"BazziUp", Bazzi_, Vector2(0.0f, 60.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziDown", Bazzi_, Vector2(0.0f, 120.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziRight", Bazzi_, Vector2(0.0f, 240.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziLeft", Bazzi_, Vector2(0.0f, 180.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziDie", Bazzi_, Vector2(0.0f, 300.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);

		at->PlayAnimation(L"BazziIdle", true);
		at->SetScale(Vector2(1.3f, 1.3f));

		GameObject::Initialize();
	}
	void Bazzi::Update()
	{
		GameObject::Update();

		// tab + enter 하면 스위치 생성
		switch (mState)
		{
		case hy::Bazzi::eState::Idle:
			Idle();
			break;
		case hy::Bazzi::eState::Move:
			Move();
			break;
		case hy::Bazzi::eState::DropWater:
			DropWater();
			break;
		case hy::Bazzi::eState::Death:
			DropWater();
			break;
		case hy::Bazzi::eState::End:
			break;
		default:
			break;
		}

	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bazzi::Idle()
	{
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::Up))
		{
			if (Input::GetKey(eKeyCode::Left))
			{
				animator->PlayAnimation(L"BazziLeft", true);
				mState = eState::Move;
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				animator->PlayAnimation(L"BazziRight", true);
				mState = eState::Move;
			}
			else if (Input::GetKey(eKeyCode::Down))
			{
				animator->PlayAnimation(L"BazziDown", true);
				mState = eState::Move;
			}
			else
			{
				animator->PlayAnimation(L"BazziUp", true);
				mState = eState::Move;
			}
		}
		else if (Input::GetKey(eKeyCode::Left))
		{

			if (Input::GetKey(eKeyCode::Up))
			{
				animator->PlayAnimation(L"BazziUp", true);
				mState = eState::Move;
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				animator->PlayAnimation(L"BazziRight", true);
				mState = eState::Move;
			}
			else if (Input::GetKey(eKeyCode::Down))
			{
				animator->PlayAnimation(L"BazziDown", true);
				mState = eState::Move;
			}
			else
			{
				animator->PlayAnimation(L"BazziLeft", true);
				mState = eState::Move;
			}
		}
		else if (Input::GetKey(eKeyCode::Down))
		{

			if (Input::GetKey(eKeyCode::Left))
			{
				animator->PlayAnimation(L"BazziLeft", true);
				mState = eState::Move;
			}
			else if (Input::GetKey(eKeyCode::Right))
			{
				animator->PlayAnimation(L"BazziRight", true);
				mState = eState::Move;
			}
			else if (Input::GetKey(eKeyCode::Up))
			{
				animator->PlayAnimation(L"BazziUp", true);
				mState = eState::Move;
			}
			else
			{
				animator->PlayAnimation(L"BazziDown", true);
				mState = eState::Move;
			}
		}
		else if (Input::GetKey(eKeyCode::Right))
		{
			if (Input::GetKey(eKeyCode::Left))
			{
				animator->PlayAnimation(L"BazziLeft", true);
				mState = eState::Move;
			}
			else if (Input::GetKey(eKeyCode::Up))
			{
				animator->PlayAnimation(L"BazziUp", true);
				mState = eState::Move;
			}
			else if (Input::GetKey(eKeyCode::Down))
			{
				animator->PlayAnimation(L"BazziDown", true);
				mState = eState::Move;
			}
			else
			{
				animator->PlayAnimation(L"BazziRight", true);
				mState = eState::Move;
			}
		}


		/*if (Input::GetKey(eKeyCode::MouseLeft))
		{
			animator->PlayAnimation(L"PlayerDropWater", false);
			mState = eState::DropWater;
		}*/
	}
	void Bazzi::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::Up))
		{
			pos.y -= 250.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::Left))
		{
			pos.x -= 250.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::Down))
		{
			pos.y += 250.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::Right))
		{
			pos.x += 250.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::Up)
			|| Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Down)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			Animator* animator = GetComponent<Animator>();
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
		}
	}
	void Bazzi::DropWater()
	{
		// 농작물에 물을 주는 로직이 추가가된다.
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
		}
	}

	void Bazzi::Dead()
	{
	}
}

