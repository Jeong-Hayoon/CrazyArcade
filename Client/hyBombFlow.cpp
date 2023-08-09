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


namespace hy
{
	// 3초 지나면 물줄기 팡
	BombFlow::BombFlow()
		: mState(eState::Idle)
	{
		Animator* bft = AddComponent<Animator>();
		bft->CreateAnimationFolder(L"BombidleBottom", L"..\\Resources\\Image\\Bomb\\Idle", Vector2(0.f, 0.f), 0.4f);

		// 상하좌우 물줄기
		bft->CreateAnimationFolder(L"BombUpIdle", L"..\\Resources\\Image\\Bomb\\UpIdleflow", Vector2(0.f, 0.f), 0.4f);
		bft->CreateAnimationFolder(L"BombUp", L"..\\Resources\\Image\\Bomb\\Upflow", Vector2(0.f, 0.f), 0.4f);

		bft->CreateAnimationFolder(L"BombDownIdle", L"..\\Resources\\Image\\Bomb\\DownIdleflow", Vector2(0.f, 0.f), 0.4f);
		bft->CreateAnimationFolder(L"BombDown", L"..\\Resources\\Image\\Bomb\\Downflow", Vector2(0.f, 0.f), 0.4f);

		bft->CreateAnimationFolder(L"BombRightIdle", L"..\\Resources\\Image\\Bomb\\RightIdleflow", Vector2(0.f, 0.f), 0.4f);
		bft->CreateAnimationFolder(L"BombRight", L"..\\Resources\\Image\\Bomb\\Rightflow", Vector2(0.f, 0.f), 0.4f);

		bft->CreateAnimationFolder(L"BombLeftIdle", L"..\\Resources\\Image\\Bomb\\LeftIdleflow", Vector2(0.f, 0.f), 0.4f);
		bft->CreateAnimationFolder(L"BombLeft", L"..\\Resources\\Image\\Bomb\\Leftflow", Vector2(0.f, 0.f), 0.4f);

		bft->CreateAnimationFolder(L"BombCenter", L"..\\Resources\\Image\\Bomb\\Centerflow", Vector2(0.f, 0.f), 1000.f);

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
		Animator* animator = AddComponent<Animator>();

		if(animator->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}
	}


	void BombFlow::Extinct()
	{
		Destroy(this);
	}
}


	