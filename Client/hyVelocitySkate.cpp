#include "hyVelocitySkate.h"
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
	VelocitySkate::VelocitySkate()
	{
		Animator* vst = AddComponent<Animator>();

		Texture* VelocitySkate_ = Resources::Load<Texture>(L"VelocitySkate"
			, L"..\\Resources\\Image\\Items\\skate.bmp");

		vst->CreateAnimation(L"VelocitySkate", VelocitySkate_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, -5.f), 0.3f);
		vst->SetScale(Vector2(0.8f, 0.8f));
		vst->PlayAnimation(L"VelocitySkate", true);
	}
	VelocitySkate::~VelocitySkate()
	{
	}
	void VelocitySkate::Initialize()
	{
		Item::Initialize();
		Resources::Load<Sound>(L"EatItem", L"..\\Resources\\Sound\\Sound\\eat_item.wav");

	}
	void VelocitySkate::Update()
	{
		Item::Update();

		Bombtime += Time::DeltaTime();

	}
	void VelocitySkate::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void VelocitySkate::OnCollisionEnter(Collider* other)
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
				bazzi->MoveSpeedUp();
				Resources::Find<Sound>(L"EatItem")->Play(false);

				Destroy(this);
			}

			else if (bazzi == nullptr)
			{
				Dao* dao = dynamic_cast<Dao*>(player);

				if (player != nullptr)
				{
					dao->MoveSpeedUp();
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
	void VelocitySkate::OnCollisionStay(Collider* other)
	{
	}
	void VelocitySkate::OnCollisionExit(Collider* other)
	{
	}
	void VelocitySkate::Idle()
	{
	}
	void VelocitySkate::Use()
	{
	}
	void VelocitySkate::Extinct()
	{
	}
}
