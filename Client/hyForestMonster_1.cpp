#include "hyForestMonster_1.h"
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
#include "hyCollider.h"
#include "hyForestMap1.h"



namespace hy
{
	// static 변수는 전역에서 초기화해주기
	float ForestMonster_1:: MonsterTime = 0.f;

	ForestMonster_1::ForestMonster_1()
		: mDeathTime(1.0f)
		, mState(eState::Right)
	{
	}
	ForestMonster_1::~ForestMonster_1()
	{
	}
	void ForestMonster_1::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"ForestMonster_1Up", L"..\\Resources\\Image\\Monster\\Forest\\Up", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonster_1Down", L"..\\Resources\\Image\\Monster\\Forest\\Down",Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonster_1Right", L"..\\Resources\\Image\\Monster\\Forest\\Right", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonster_1Left", L"..\\Resources\\Image\\Monster\\Forest\\Left", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonnsterDie", L"..\\Resources\\Image\\Monster\\Forest\\Die", Vector2::Zero, 0.2f);
		mt->PlayAnimation(L"ForestMonster_1Right", true);

		GameObject::Initialize();
	}
	void ForestMonster_1::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case hy::ForestMonster_1::eState::Up:
			Up();
			break;

		case hy::ForestMonster_1::eState::Down:
			Down();
			break;

		case hy::ForestMonster_1::eState::Left:
			Left();
			break;

		case hy::ForestMonster_1::eState::Right:
			Right();
			break;

		case hy::ForestMonster_1::eState::Dead:
			Dead();
			break;

		case hy::ForestMonster_1::eState::End:
			break;

		default:
			break;
		}
	}
	void ForestMonster_1::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	// 충돌했을 때 처리 코드 여기에 작성
	// 물풍선과 충돌했을 때 Dead
	void ForestMonster_1::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"ForestMonnsterDie", false);
			ForestMap1::SetMonsterQuantity;
			mState = eState::Dead;
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && other->GetOwner()->GetComponent<Tile>()->Tile::GetType() == Tile::eType::Crack)
		{
			// 몬스터 이동 방향 반대로
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && other->GetOwner()->GetComponent<Tile>()->Tile::GetType() == Tile::eType::Uncrushable)
		{
			// 몬스터 이동 방향 반대로
		}
	}

	void ForestMonster_1::OnCollisionStay(Collider* other)
	{
	}

	void ForestMonster_1::OnCollisionExit(Collider* other)
	{
	}

	void ForestMonster_1::Up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();		//
		pos.y -= 100.f * Time::DeltaTime();
		tr->SetPosition(pos);
		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 3)
		{
			animator->PlayAnimation(L"ForestMonster_1Right", true);
			mState = eState::Right;
			MonsterTime = 0.f;
		}
	}

	void ForestMonster_1::Down()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();		//
		pos.y += 100.f * Time::DeltaTime();
		tr->SetPosition(pos);
		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 3)
		{
			animator->PlayAnimation(L"ForestMonster_1Left", true);
			mState = eState::Left;
			MonsterTime = 0.f;
		}
	}

	void ForestMonster_1::Left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();		//
		pos.x -= 100.f * Time::DeltaTime();

		tr->SetPosition(pos);
		MonsterTime += Time::DeltaTime();
		if (MonsterTime > 3)
		{
			animator->PlayAnimation(L"ForestMonster_1Up", true);
			mState = eState::Up;
			MonsterTime = 0.f;
		}
	}

	void ForestMonster_1::Right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();			//
		pos.x += 100.f * Time::DeltaTime();
		tr->SetPosition(pos);
		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 3)
		{
			animator->PlayAnimation(L"ForestMonster_1Down", true);
			mState = eState::Down;
			MonsterTime = 0.f;
		}

	}

	void ForestMonster_1::Dead()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}

