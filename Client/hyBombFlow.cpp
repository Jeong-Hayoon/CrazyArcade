#include "hyBombFlow.h"
#include "hyBomb.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyRigidbody.h"
#include "hyBazzi.h"
#include "hyCollider.h"


namespace hy
{
	// 3초 지나면 물줄기 팡
	BombFlow::BombFlow()
		: mState(eState::Idle)
	{
		Collider* Col = AddComponent<Collider>();
		Col->SetSize(Vector2(40.0f, 40.0f));

		Animator* bft = AddComponent<Animator>();

		// 상하좌우 물줄기
		bft->CreateAnimationFolder(L"BombUpIdle", L"..\\Resources\\Image\\Bomb\\UpIdleflow", Vector2(0.f, 0.f), 0.3f);
		bft->CreateAnimationFolder(L"BombUp", L"..\\Resources\\Image\\Bomb\\Upflow", Vector2(0.f, 0.f), 0.15f);

		bft->CreateAnimationFolder(L"BombDownIdle", L"..\\Resources\\Image\\Bomb\\DownIdleflow", Vector2(0.f, 0.f), 0.3f);
		bft->CreateAnimationFolder(L"BombDown", L"..\\Resources\\Image\\Bomb\\Downflow", Vector2(0.f, 0.f), 0.15f);

		bft->CreateAnimationFolder(L"BombRightIdle", L"..\\Resources\\Image\\Bomb\\RightIdleflow", Vector2(0.f, 0.f), 0.3f);
		bft->CreateAnimationFolder(L"BombRight", L"..\\Resources\\Image\\Bomb\\Rightflow", Vector2(0.f, 0.f), 0.15f);

		bft->CreateAnimationFolder(L"BombLeftIdle", L"..\\Resources\\Image\\Bomb\\LeftIdleflow", Vector2(0.f, 0.f), 0.3f);
		bft->CreateAnimationFolder(L"BombLeft", L"..\\Resources\\Image\\Bomb\\Leftflow", Vector2(0.f, 0.f), 0.15f);

		bft->CreateAnimationFolder(L"BombCenter", L"..\\Resources\\Image\\Bomb\\Centerflow", Vector2(0.f, 0.f), 0.18f);

		bft->SetScale(Vector2(1.f, 1.f));
		bft->PlayAnimation(L"BombCenter", false);


	}
	BombFlow::~BombFlow()
	{
	}
	void BombFlow::Initialize()
	{
		GameObject::Initialize();
	}
	void BombFlow::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case hy::BombFlow::eState::Idle:
			Idle();
			break;
	
		case hy::BombFlow::eState::Extinct:
			Extinct();
			break;

		case hy::BombFlow::eState::End:
			break;
		default:
			break;
		}

	}
	void BombFlow::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BombFlow::OnCollisionEnter(Collider* other)
	{
	}
	void BombFlow::OnCollisionStay(Collider* other)
	{
	}
	void BombFlow::OnCollisionExit(Collider* other)
	{
	}

	void BombFlow::Idle()
	{
		Animator* animator = GetComponent<Animator>();

		if(animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}
	}

	void BombFlow::Left()
	{
		Animator* animator = GetComponent<Animator>();
		animator->PlayAnimation(L"BombLeft", false);
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}

	}

	void BombFlow::Right()
	{
		Animator* animator = GetComponent<Animator>();
		animator->PlayAnimation(L"BombRight", false);
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}
	}

	void BombFlow::Up()
	{
		Animator* animator = GetComponent<Animator>();
		animator->PlayAnimation(L"BombUp", false);
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}
	}

	void BombFlow::Down()
	{
		Animator* animator = GetComponent<Animator>();
		animator->PlayAnimation(L"BombDown", false);
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}
	}

	void BombFlow::LeftIdle()
	{
		Animator* animator = GetComponent<Animator>();
		animator->PlayAnimation(L"BombLeftIdle", false);
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}
	}

	void BombFlow::RightIdle()
	{
		Animator* animator = GetComponent<Animator>();
		animator->PlayAnimation(L"BombRightIdle", false);
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}
	}

	void BombFlow::UpIdle()
	{
		Animator* animator = GetComponent<Animator>();
		animator->PlayAnimation(L"BombUpIdle", false);
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}
	}

	void BombFlow::DownIdle()
	{
		Animator* animator = GetComponent<Animator>();
		animator->PlayAnimation(L"BombDownIdle", false);
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}
	}


	void BombFlow::Extinct()
	{
		Destroy(this);
	}
}


	