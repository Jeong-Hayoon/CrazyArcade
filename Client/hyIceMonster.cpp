#include "hyIceMonster.h"
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

// PirateMonster 그대로 사용하고 보스만 아이스 보스로
namespace hy
{
	IceMonster::IceMonster()
	{
	}
	IceMonster::~IceMonster()
	{
	}
	void IceMonster::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"IceMonsterUp", L"..\\Resources\\Image\\Monster\\Pirate\\Up");
		mt->CreateAnimationFolder(L"IceMonsterDown", L"..\\Resources\\Image\\Monster\\Pirate\\Down");
		mt->CreateAnimationFolder(L"IceMonsterRight", L"..\\Resources\\Image\\Monster\\Pirate\\Right");
		mt->CreateAnimationFolder(L"IceMonsterLeft", L"..\\Resources\\Image\\Monster\\Pirate\\Left");
		mt->CreateAnimationFolder(L"IceMonsterDie", L"..\\Resources\\Image\\Monster\\Pirate\\Die");
		mt->PlayAnimation(L"IceMonsterLeft", true);

		GameObject::Initialize();
	}
	void IceMonster::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case hy::IceMonster::eState::Move:
			Move();
			break;

		case hy::IceMonster::eState::Dead:
			Dead();
			break;

		case hy::IceMonster::eState::End:
			break;

		default:
			break;
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		tr->SetPosition(pos);
		static float MonsterTime = 0.f;
		MonsterTime += Time::DeltaTime();

		if (MonsterTime < 3)
		{
			anim->PlayAnimation(L"IceMonsterRight", true);
			pos.x += 150.0f * Time::DeltaTime();
		}

		if (MonsterTime < 6 && MonsterTime > 3)
		{
			anim->PlayAnimation(L"IceMonsterDown", true);
			pos.y += 150.0f * Time::DeltaTime();
		}

		if (MonsterTime < 9 && MonsterTime > 6)
		{
			anim->PlayAnimation(L"IceMonsterLeft", true);
			pos.x -= 150.0f * Time::DeltaTime();
		}

		if (MonsterTime < 12 && MonsterTime > 9)
		{
			anim->PlayAnimation(L"IceMonsterUp", true);
			pos.y -= 150.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);

	}
	void IceMonster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void IceMonster::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		tr->SetPosition(pos);
		static float MonsterTime = 0.f;
		MonsterTime += Time::DeltaTime();

		if (MonsterTime < 3)
		{
			anim->PlayAnimation(L"IceMonsterRight", true);
			pos.x += 100.0f * Time::DeltaTime();
		}

		if (MonsterTime < 6 && MonsterTime > 3)
		{
			anim->PlayAnimation(L"IceMosterDown", true);
			pos.y += 100.0f * Time::DeltaTime();
		}

		if (MonsterTime < 9 && MonsterTime > 6)
		{
			anim->PlayAnimation(L"IceMosterLeft", true);
			pos.x -= 100.0f * Time::DeltaTime();
		}

		if (MonsterTime < 12 && MonsterTime > 9)
		{
			anim->PlayAnimation(L"IceMosterUp", true);
			pos.y -= 100.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);

	}

	// 충돌했을 때 처리 코드 여기에 작성
	void IceMonster::OnCollisionEnter(Collider* other)
	{
	}

	void IceMonster::OnCollisionStay(Collider* other)
	{
	}

	void IceMonster::OnCollisionExit(Collider* other)
	{
	}

	void IceMonster::Dead()
	{
	}

}


