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


namespace hy
{
	ForestMonster::ForestMonster()
	{
	}
	ForestMonster::~ForestMonster()
	{
	}
	void ForestMonster::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"ForestMosterUp", L"..\\Resources\\Image\\Monster\\Forest\\Up", Vector2::Zero, 0.4f);
		mt->CreateAnimationFolder(L"ForestMosterDown", L"..\\Resources\\Image\\Monster\\Forest\\Down",Vector2::Zero, 0.4f);
		mt->CreateAnimationFolder(L"ForestMosterRight", L"..\\Resources\\Image\\Monster\\Forest\\Right", Vector2::Zero, 0.4f);
		mt->CreateAnimationFolder(L"ForestMosterLeft", L"..\\Resources\\Image\\Monster\\Forest\\Left", Vector2::Zero, 0.4f);
		mt->CreateAnimationFolder(L"ForestMonsterDie", L"..\\Resources\\Image\\Monster\\Forest\\Die", Vector2::Zero, 0.4f);
		mt->PlayAnimation(L"ForestMosterRight", true);

		GameObject::Initialize();
	}
	void ForestMonster::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case hy::ForestMonster::eState::Move:
			Move();
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

	void ForestMonster::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		tr->SetPosition(pos);
		static float MonsterTime = 0.f;
		MonsterTime += Time::DeltaTime();

		if (MonsterTime < 3)
		{
			anim->PlayAnimation(L"ForestMosterRight", true);
			pos.x += 150.0f * Time::DeltaTime();
		}

		if (MonsterTime < 6 && MonsterTime > 3)
		{
			anim->PlayAnimation(L"ForestMosterDown", true);
			pos.y += 150.0f * Time::DeltaTime();
		}

		if (MonsterTime < 9 && MonsterTime > 6)
		{
			anim->PlayAnimation(L"ForestMosterLeft", true);
			pos.x -= 150.0f * Time::DeltaTime();
		}

		if (MonsterTime < 12 && MonsterTime > 9)
		{
			anim->PlayAnimation(L"ForestMosterUp", true);
			pos.y -= 150.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
		
	}

	// 충돌했을 때 처리 코드 여기에 작성
	void ForestMonster::OnCollisionEnter(Collider* other)
	{
	}

	void ForestMonster::OnCollisionStay(Collider* other)
	{
	}

	void ForestMonster::OnCollisionExit(Collider* other)
	{
	}

	void ForestMonster::Dead()
	{
	}
}

