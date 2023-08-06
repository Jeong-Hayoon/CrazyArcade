#include "hyForestMonster.h"
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



namespace hy
{
	// static 변수는 전역에서 초기화해주기
	float ForestMonster:: MonsterTime = 0.f;
	UINT ForestMonster :: MonsterQuantity(3);

	ForestMonster::ForestMonster()
		: mDeathTime(1.0f)
		, mState(eState::Right)
	{
	}
	ForestMonster::~ForestMonster()
	{
	}
	void ForestMonster::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"ForestMonsterUp", L"..\\Resources\\Image\\Monster\\Forest\\Up", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonsterDown", L"..\\Resources\\Image\\Monster\\Forest\\Down",Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonsterRight", L"..\\Resources\\Image\\Monster\\Forest\\Right", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonsterLeft", L"..\\Resources\\Image\\Monster\\Forest\\Left", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonnsterDie", L"..\\Resources\\Image\\Monster\\Forest\\Die", Vector2::Zero, 0.15f);
		mt->PlayAnimation(L"ForestMonsterRight", true);

		GameObject::Initialize();
	}
	void ForestMonster::Update()
	{
		GameObject::Update();

		//// 시간이 지남에 따라 객체 삭제 -> 물풍선 교체
		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPosition();
		//pos.x += 300.0f * Time::DeltaTime();
		//tr->SetPosition(pos);

		//mDeathTime -= Time::DeltaTime();
		//if (mDeathTime < 0.0f)
		//{
		//	Destroy(this);
		//}


		switch (mState)
		{
		case hy::ForestMonster::eState::Up:
			Up();
			break;

		case hy::ForestMonster::eState::Down:
			Down();
			break;

		case hy::ForestMonster::eState::Left:
			Left();
			break;

		case hy::ForestMonster::eState::Right:
			Right();
			break;

		case hy::ForestMonster::eState::Dead:
			Dead();
			break;

		case hy::ForestMonster::eState::End:
			break;

		default:
			break;
		}
	}
	void ForestMonster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	// 충돌했을 때 처리 코드 여기에 작성
	// 물풍선과 충돌했을 때 Dead
	void ForestMonster::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Effect)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(1.0f, 1.0f));
			at->PlayAnimation(L"ForestMonnsterDie", false);
			MonsterQuantity--;
			mState = eState::Dead;
		}

	}

	void ForestMonster::OnCollisionStay(Collider* other)
	{
	}

	void ForestMonster::OnCollisionExit(Collider* other)
	{
	}

	void ForestMonster::Up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();		//
		pos.y -= 100.f * Time::DeltaTime();
		tr->SetPosition(pos);
		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 3)
		{
			animator->PlayAnimation(L"ForestMonsterRight", true);
			mState = eState::Right;
			MonsterTime = 0.f;
		}
	}

	void ForestMonster::Down()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();		//
		pos.y += 100.f * Time::DeltaTime();
		tr->SetPosition(pos);
		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 3)
		{
			animator->PlayAnimation(L"ForestMonsterLeft", true);
			mState = eState::Left;
			MonsterTime = 0.f;
		}
	}

	void ForestMonster::Left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();		//
		pos.x -= 100.f * Time::DeltaTime();

		tr->SetPosition(pos);
		MonsterTime += Time::DeltaTime();
		if (MonsterTime > 3)
		{
			animator->PlayAnimation(L"ForestMonsterUp", true);
			mState = eState::Up;
			MonsterTime = 0.f;
		}
	}

	void ForestMonster::Right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();			//
		pos.x += 100.f * Time::DeltaTime();
		tr->SetPosition(pos);
		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 3)
		{
			animator->PlayAnimation(L"ForestMonsterDown", true);
			mState = eState::Down;
			MonsterTime = 0.f;
		}

	}

	void ForestMonster::Dead()
	{
	}
}

