#include "hyBazzi.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
//#include "hyForestMap1.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
//#include "hyRigidbody.h"
#include "hyBomb.h"



namespace hy
{
	Bazzi::Bazzi()
		: mState(eState::Idle)
		,mDirection(eDirection::Down)
	{
	}
	Bazzi::~Bazzi()
	{
	}
	void Bazzi::Initialize()
	{

		Texture* Bazzi_ = Resources::Load<Texture>(L"Bazzi"
			, L"..\\Resources\\Image\\Bazzi\\Bazzi.bmp");

		Animator* at = AddComponent<Animator>();
		at->CreateAnimation(L"BazziIdle", Bazzi_, Vector2(0.0f, 0.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.6f);

		at->CreateAnimation(L"BazziUp", Bazzi_, Vector2(0.0f, 60.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziUpStop", Bazzi_, Vector2(50.0f, 60.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziDown", Bazzi_, Vector2(0.0f, 120.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziDownStop", Bazzi_, Vector2(50.0f, 120.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziRight", Bazzi_, Vector2(0.0f, 240.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziRightStop", Bazzi_, Vector2(50.0f, 240.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziLeft", Bazzi_, Vector2(0.0f, 180.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziLeftStop", Bazzi_, Vector2(50.0f, 180.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziDie", Bazzi_, Vector2(0.0f, 300.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);

		at->PlayAnimation(L"BazziIdle", true);
		at->SetScale(Vector2(1.3f, 1.3f));

		GameObject::Initialize();
	}
	void Bazzi::Update()	// 상태 변화만 업데이트에서 
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
		case hy::Bazzi::eState::MoveStop:
			MoveStop();
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


		if (Input::GetKeyDown(eKeyCode::Space))
		{
			Bomb* Bomb_ = object::Instantiate<Bomb>(eLayerType::Effect);
			Transform* Bazzitr = GetComponent<Transform>();
			if (mDirection == eDirection::Up)
			{
				Bomb_->GetComponent<Transform>()->SetPosition(Bazzitr->GetPosition());
			}
			else if (mDirection == eDirection::Down)
			{
				Bomb_->GetComponent<Transform>()->SetPosition(Bazzitr->GetPosition());
			}
			else if (mDirection == eDirection::Left)
			{
				Bomb_->GetComponent<Transform>()->SetPosition(Bazzitr->GetPosition());
			}
			else if (mDirection == eDirection::Right)
			{
				Bomb_->GetComponent<Transform>()->SetPosition(Bazzitr->GetPosition());
			}
		}

	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bazzi::OnCollisionEnter(Collider* other)
	{
	}
	void Bazzi::OnCollisionStay(Collider* other)
	{
	}
	void Bazzi::OnCollisionExit(Collider* other)
	{
	}
 
	void Bazzi::Idle()
	{
		Animator* animator = GetComponent<Animator>();	


		if (Input::GetKeyDown(eKeyCode::Left))		// 왼쪽 키를 누르면 왼쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziLeft", true);
			mState = eState::Move;
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::Right))		// 오른쪽 키를 누르면 오른쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziRight", true);
			mState = eState::Move;
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::Up))		// 위쪽 키를 누르면 위쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziUp", true);
			mState = eState::Move;
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::Down))		// 아레쪽 키를 누르면 아레쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziDown", true);
			mState = eState::Move;
			mDirection = eDirection::Down;
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
		Animator* animator = GetComponent<Animator>();

 		if (mDirection == eDirection::Up)			// 방향이 위쪽이면 위쪽으로 이동
			pos.y -= 150.f * Time::DeltaTime();
		else if (mDirection == eDirection::Left)	// 방향이 왼쪽이면 왼쪽으로 이동
			pos.x -= 150.f * Time::DeltaTime();
		else if (mDirection == eDirection::Right)	// 방향이 오른쪽이면 오른쪽으로 이동
			pos.x += 150.f * Time::DeltaTime();
		else if (mDirection == eDirection::Down)	// 방향이 아래쪽이면 아래쪽으로 이동
			pos.y += 150.f * Time::DeltaTime();

		tr->SetPosition(pos);

		if (Input::GetKeyDown(eKeyCode::Left))		// 어떤 키를 누르고 이따가 왼쪽 키를 눌렀을 때
		{
			animator->PlayAnimation(L"BazziLeft", true);
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			animator->PlayAnimation(L"BazziRight", true);
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			animator->PlayAnimation(L"BazziUp", true);
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			animator->PlayAnimation(L"BazziDown", true);
			mDirection = eDirection::Down;
		}

		if (!Input::GetKey(eKeyCode::Up) && !Input::GetKey(eKeyCode::Down)
			&& !Input::GetKey(eKeyCode::Left) && !Input::GetKey(eKeyCode::Right))
		{
			mState = eState::MoveStop;
		}

	}

	void Bazzi::MoveStop()
	{
		static float time = 0.f;
		time += Time::DeltaTime();
		Animator* animator = GetComponent<Animator>();

		if (mDirection == eDirection::Up)
		{
			animator->PlayAnimation(L"BazziUpStop", true);
		}
		if (mDirection == eDirection::Down)
		{
			animator->PlayAnimation(L"BazziDownStop", true);
		}
		if (mDirection == eDirection::Left)
		{
			animator->PlayAnimation(L"BazziLeftStop", true);
		}
		if (mDirection == eDirection::Right)
		{
			animator->PlayAnimation(L"BazziRightStop", true); 
		}
		if (time > 3.f)
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
			time = 0.f;
		}
	}

	void Bazzi::DropWater()
	{
		// 농작물에 물을 주는 로직이 추가가된다.
		/*Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"bazziidle", true);
			mState = eState::Idle;
		}*/
	}
	 
	void Bazzi::Dead()
	{
	}
}

