#include "hyBossBomb.h"
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
#include "hyRigidbody.h"
#include "hyBazzi.h"
#include "hyCollider.h"
#include "hyCollisionManager.h"


namespace hy
{
	BossBomb::BossBomb()
		: mState(eState::Flow)
	{
		Collider* Col = AddComponent<Collider>();
		Col->SetSize(Vector2(40.0f, 40.0f));

		CollisionManager::CollisionLayerCheck(eLayerType::BossBombflow, eLayerType::Tile, true);


		Animator* bbt = AddComponent<Animator>();
		bbt->CreateAnimationFolder(L"BossBomb", L"..\\Resources\\Image\\Bomb\\Centerflow", Vector2(0.f, 0.f), 0.25f); // 0.25
		bbt->SetScale(Vector2(1.f, 1.f));
		bbt->PlayAnimation(L"BossBomb", false);

	}
	BossBomb::~BossBomb()
	{
	}
	void BossBomb::Initialize()
	{


		GameObject::Initialize();
	}
	void BossBomb::Update()
	{
		GameObject::Update();

		// tab + enter 하면 스위치 생성
		switch (mState)
		{
		case hy::BossBomb::eState::Flow:
			Flow();
			break;
		case hy::BossBomb::eState::Pop:
			Pop();
			break;
		case hy::BossBomb::eState::End:
			break;
		default:
			break;
		}

	}
	void BossBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BossBomb::OnCollisionEnter(Collider* other)
	{
	}
	void BossBomb::OnCollisionStay(Collider* other)
	{
	}
	void BossBomb::OnCollisionExit(Collider* other)
	{
	}


	void BossBomb::Flow()
	{
		static float BossBombtime = 0.f;
		BossBombtime += Time::DeltaTime();

		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Pop;
			BossBombtime = 0.f;
		}

	}
	void BossBomb::Pop()
	{
		Destroy(this);
	}


}

