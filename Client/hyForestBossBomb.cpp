#include "hyForestBossBomb.h"
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
	ForestBossBomb::ForestBossBomb()
		: mState(eState::Flow)
	{
		Collider* Col = AddComponent<Collider>();
		Col->SetSize(Vector2(40.0f, 40.0f));

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Bomb, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bomb, eLayerType::Tile, true);


		Animator* bbt = AddComponent<Animator>();
		bbt->CreateAnimationFolder(L"ForestBossBomb", L"..\\Resources\\Image\\Bomb\\Centerflow", Vector2(0.f, 0.f), 0.25f); // 0.25
		bbt->SetScale(Vector2(1.f, 1.f));
		bbt->PlayAnimation(L"ForestBossBomb", false);

	}
	ForestBossBomb::~ForestBossBomb()
	{
	}
	void ForestBossBomb::Initialize()
	{


		GameObject::Initialize();
	}
	void ForestBossBomb::Update()
	{
		GameObject::Update();

		// tab + enter 하면 스위치 생성
		switch (mState)
		{
		case hy::ForestBossBomb::eState::Flow:
			Flow();
			break;
		case hy::ForestBossBomb::eState::Pop:
			Pop();
			break;
		case hy::ForestBossBomb::eState::End:
			break;
		default:
			break;
		}

	}
	void ForestBossBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ForestBossBomb::OnCollisionEnter(Collider* other)
	{
	}
	void ForestBossBomb::OnCollisionStay(Collider* other)
	{
	}
	void ForestBossBomb::OnCollisionExit(Collider* other)
	{
	}


	void ForestBossBomb::Flow()
	{
		static float ForestBossBombtime = 0.f;
		ForestBossBombtime += Time::DeltaTime();

		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			mState = eState::Pop;
			ForestBossBombtime = 0.f;
		}

	}
	void ForestBossBomb::Pop()
	{
		Destroy(this);
	}


}

