#include "hySteam.h"
#include "hyTransform.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
// #include "hyForestMap1.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyBazzi.h"
#include "hyCollider.h"
#include "hyBalloon.h"
#include "hyDevil.h"
#include "hyNeedle.h"
#include "hyPotionMax.h"
#include "hyPotion.h"
#include "hyVelocitySkate.h"


// 박스가 소멸될때 효과
// 랜덤 확률로 소멸된 후에는 아이템이 그 위치에 생성됨(객체 생성)

namespace hy
{
	Steam::Steam()
		: mState(eState::Make)
	{
		Animator* st = AddComponent<Animator>();
		st->CreateAnimationFolder(L"Steam", L"..\\Resources\\Image\\Effect\\Crashed", Vector2(0.f, 0.f), 0.1f);
		st->SetScale(Vector2(1.f, 1.f));

		st->PlayAnimation(L"Steam", false);
	}
	Steam::~Steam()
	{
	}
	void Steam::Initialize()
	{
	}
	void Steam::Update()
	{
		GameObject::Update();

		// tab + enter 하면 스위치 생성
		switch (mState)
		{
		case hy::Steam::eState::Make:
			Make();
			break;
		case hy::Steam::eState::Extinct:
			Extinct();
			break;
		case hy::Steam::eState::End:
			break;
		default:
			break;
		}

	}
	void Steam::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Steam::Make()
	{
		Animator* st = GetComponent<Animator>();

		if (st->IsActiveAnimationComplete())
		{
			mState = eState::Extinct;
		}

	}

	void Steam::Extinct()
	{
		Transform* tr = GetComponent<Transform>();

		int ItemSelect = rand() % 6;

		if (ItemSelect == 0)
		{
			// Balloon 아이템 setting
			Balloon* Balloon_1 = object::Instantiate<Balloon>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// Balloon 아이템 충돌 구현
			Collider* Ballooncol = Balloon_1->AddComponent<Collider>();
			// Balloon 아이템 충돌 사각형 사이즈 수정
			Ballooncol->SetSize(Vector2(10.0f, 30.0f));
		}
		else if (ItemSelect == 1)
		{
			// Devil 아이템 setting
			Devil* Devil_1 = object::Instantiate<Devil>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));
	
			// Devil 아이템 충돌 구현
			Collider* Devilcol = Devil_1->AddComponent<Collider>();
			// Devil 아이템 충돌 사각형 사이즈 수정
			Devilcol->SetSize(Vector2(10.0f, 30.0f));
			Devilcol->SetOffset(Vector2(0.0f, 0.0f));

		}
		else if (ItemSelect == 2)
		{
			// Potion 아이템 setting
			Potion* Potion_1 = object::Instantiate<Potion>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// Potion 아이템 충돌 구현
			Collider* Potioncol = Potion_1->AddComponent<Collider>();
			// Potion 아이템 충돌 사각형 사이즈 수정
			Potioncol->SetSize(Vector2(10.0f, 30.0f));
			Potioncol->SetOffset(Vector2(0.0f, 0.0f));

		}
		else if (ItemSelect == 3)
		{
			// Needle 아이템 setting
			Needle* Needle_1 = object::Instantiate<Needle>(eLayerType::UseItem, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// Needle 아이템 충돌 구현
			Collider* Needlecol = Needle_1->AddComponent<Collider>();
			// Needle 아이템 충돌 사각형 사이즈 수정
			Needlecol->SetSize(Vector2(10.0f, 30.0f));
			Needlecol->SetOffset(Vector2(0.0f, 0.0f));

		}
		else if (ItemSelect == 4)
		{
			// PotionMax 아이템 setting
			PotionMax* PotionMax_1 = object::Instantiate<PotionMax>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// PotionMax 아이템 충돌 구현
			Collider* PotionMaxcol = PotionMax_1->AddComponent<Collider>();
			// PotionMax 아이템 충돌 사각형 사이즈 수정
			PotionMaxcol->SetSize(Vector2(10.0f, 30.0f));
			PotionMaxcol->SetOffset(Vector2(0.0f, 0.0f));

		}
		else if (ItemSelect == 5)
		{
			// VelocitySkate 아이템 setting
			VelocitySkate* VelocitySkate_1 = object::Instantiate<VelocitySkate>(eLayerType::Item, tr->GetPosition() + Vector2(0.0f, -2.0f));

			// VelocitySkate 아이템 충돌 구현
			Collider* VelocitySkatecol = VelocitySkate_1->AddComponent<Collider>();
			// VelocitySkate 아이템 충돌 사각형 사이즈 수정
			VelocitySkatecol->SetSize(Vector2(10.0f, 30.0f));
			VelocitySkatecol->SetOffset(Vector2(0.0f, 0.0f));
		}

		Destroy(this);
	}

}

//Balloon,
//Devil,
//Needle,
//Potion,
//PotionMax,
//VelocitySkate,