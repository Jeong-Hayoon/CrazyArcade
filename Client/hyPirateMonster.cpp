#include "hyPirateMonster.h"
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
	PirateMonster::PirateMonster()
	{
	}
	PirateMonster::~PirateMonster()
	{
	}
	void PirateMonster::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"PirateMonsterUp", L"..\\Resources\\Image\\Monster\\Pirate\\Up");
		mt->CreateAnimationFolder(L"PirateMonsterDown", L"..\\Resources\\Image\\Monster\\Pirate\\Down");
		mt->CreateAnimationFolder(L"PirateMonsterRight", L"..\\Resources\\Image\\Monster\\Pirate\\Right");
		mt->CreateAnimationFolder(L"PirateMonsterLeft", L"..\\Resources\\Image\\Monster\\Pirate\\Left");
		mt->CreateAnimationFolder(L"PirateMonsterDie", L"..\\Resources\\Image\\Monster\\Pirate\\Die");
		mt->PlayAnimation(L"PirateMonsterLeft", true);

		GameObject::Initialize();
	}
	void PirateMonster::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		tr->SetPosition(pos);
		static float MonsterTime = 0.f;
		MonsterTime += Time::DeltaTime();

		if (MonsterTime < 3)
		{
			anim->PlayAnimation(L"PirateMonsterRight", true);
			pos.x += 150.0f * Time::DeltaTime();
		}

		if (MonsterTime < 6 && MonsterTime > 3)
		{
			anim->PlayAnimation(L"PirateMonsterDown", true);
			pos.y += 150.0f * Time::DeltaTime();
		}

		if (MonsterTime < 9 && MonsterTime > 6)
		{
			anim->PlayAnimation(L"PirateMonsterLeft", true);
			pos.x -= 150.0f * Time::DeltaTime();
		}

		if (MonsterTime < 12 && MonsterTime > 9)
		{
			anim->PlayAnimation(L"PirateMonsterUp", true);
			pos.y -= 150.0f * Time::DeltaTime();
		}
	}
	void PirateMonster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}

