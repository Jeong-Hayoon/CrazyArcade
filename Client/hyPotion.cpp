#include "hyPotion.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyBazzi.h"
#include "hyCollider.h"
#include "hySound.h"
#include "hyTime.h"




namespace hy
{
	Potion::Potion()
	{
		Animator* pt = AddComponent<Animator>();

		Texture* Potion_ = Resources::Load<Texture>(L"Potion"
			, L"..\\Resources\\Image\\Items\\potion.bmp");

		pt->CreateAnimation(L"Potion", Potion_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, -5.f), 0.3f);
		pt->SetScale(Vector2(0.8f, 0.8f));
		pt->PlayAnimation(L"Potion", true);
	}
	Potion::~Potion()
	{
	}
	void Potion::Initialize()
	{
		Item::Initialize();

		// Potion 아이템 충돌 구현
		Collider* Potioncol = AddComponent<Collider>();
		// Potion 아이템 충돌 사각형 사이즈 수정
		Potioncol->SetSize(Vector2(10.0f, 30.0f));

		Resources::Load<Sound>(L"EatItem", L"..\\Resources\\Sound\\Sound\\eat_item.wav");

	}
	void Potion::Update()
	{
		Item::Update();

		Bombtime += Time::DeltaTime();

	}
	void Potion::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void Potion::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			Bazzi* bz = (Bazzi*)(other->GetOwner());
			if (bz != nullptr)
			{
				bz->SetBombFlowCount();

				Resources::Find<Sound>(L"EatItem")->Play(false);

				Destroy(this);
			}
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Destroy(this);
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::BossBombflow && Bombtime > 2.f)
		{
			Destroy(this);
		}
	}
	void Potion::OnCollisionStay(Collider* other)
	{
		/*Bazzi* bz = (Bazzi*)(other->GetOwner());
		bz->AddBombFlow();
		Destroy(this);*/
	}
	void Potion::OnCollisionExit(Collider* other)
	{
	}
	void Potion::Idle()
	{
	}
	void Potion::Use()
	{
	}
	void Potion::Extinct()
	{
	}
}