#include "hyPotionMax.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hySound.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyTime.h"
#include "hyDao.h"

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

		Bombtime += Time::DeltaTime();

	}
	void PotionMax::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void PotionMax::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			// 충돌체의 owner를 가져와서
			GameObject* player = other->GetOwner();
			// Bazzi과 같으면 Bazzi의 주소를 반환하고 안되면 nullptr
			Bazzi* bazzi = dynamic_cast<Bazzi*>(player);

			//Bazzi* player = (Bazzi*)(other->GetOwner());

			if (bazzi != nullptr)
			{
				bazzi->MaxBombFlowCount();
				Resources::Find<Sound>(L"EatItem")->Play(false);

				Destroy(this);
			}

			else if (bazzi == nullptr)
			{
				Dao* dao = dynamic_cast<Dao*>(player);

				if (player != nullptr)
				{
					dao->MaxBombFlowCount();
					Resources::Find<Sound>(L"EatItem")->Play(false);

					Destroy(this);
				}
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
