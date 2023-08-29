#include "hyPotionMax.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hySound.h"
#include "hyCollider.h"
#include "hyBazzi.h"

namespace hy
{
	PotionMax::PotionMax()
	{
		Animator* pmt = AddComponent<Animator>();

		Texture* PotionMax_ = Resources::Load<Texture>(L"PotionMax"
			, L"..\\Resources\\Image\\Items\\potionmax.bmp");

		pmt->CreateAnimation(L"PotionMax", PotionMax_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, -5.f), 0.3f);
		pmt->SetScale(Vector2(0.78f, 0.8f));
		pmt->PlayAnimation(L"PotionMax", true);
	}
	PotionMax::~PotionMax()
	{
	}
	void PotionMax::Initialize()
	{
		Item::Initialize();
		Resources::Load<Sound>(L"EatItem", L"..\\Resources\\Sound\\Sound\\eat_item.wav");

	}
	void PotionMax::Update()
	{
		Item::Update();
	}
	void PotionMax::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void PotionMax::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			Bazzi* bz = (Bazzi*)(other->GetOwner());
			if (bz != nullptr)
			{
				bz->MaxBombFlowCount();
				Resources::Find<Sound>(L"EatItem")->Play(false);

				Destroy(this);
			}
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Destroy(this);
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::BossBombflow)
		{
			Destroy(this);
		}

	}
	void PotionMax::OnCollisionStay(Collider* other)
	{
	}
	void PotionMax::OnCollisionExit(Collider* other)
	{
	}
	void PotionMax::Idle()
	{
	}
	void PotionMax::Use()
	{
	}
	void PotionMax::Extinct()
	{
	}
}
