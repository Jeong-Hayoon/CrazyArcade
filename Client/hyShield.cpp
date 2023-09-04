#include "hyShield.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyObject.h"
#include "hyTime.h"
#include "hySound.h"
#include "hyTime.h"
#include "hyDao.h"


namespace hy
{
	Shield::Shield()
	{
		Animator* st = AddComponent<Animator>();

		Texture* Shield_ = Resources::Load<Texture>(L"Shield"
			, L"..\\Resources\\Image\\Items\\shield.bmp");

		Texture* ShieldEffect_ = Resources::Load<Texture>(L"ShieldEffect"
			, L"..\\Resources\\Image\\Items\\shieldeffect.bmp");


		st->CreateAnimation(L"Shield", Shield_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, -5.f), 0.3f);
		st->CreateAnimation(L"BazziShield", ShieldEffect_, Vector2(0.0f, 0.0f), Vector2(88.0f, 101.0f), 4, Vector2(0.0f, 0.0f), 0.05f);

		st->SetScale(Vector2(0.8f, 0.8f));
		st->PlayAnimation(L"Shield", true);
	}
	Shield::~Shield()
	{
	}
	void Shield::Initialize()
	{
		Item::Initialize();

		// Shield ������ �浹 ����
		Collider* Shieldcol = AddComponent<Collider>();
		// Shield ������ �浹 �簢�� ������ ����
		Shieldcol->SetSize(Vector2(10.0f, 30.0f));

		Resources::Load<Sound>(L"EatItem", L"..\\Resources\\Sound\\Sound\\eat_item.wav");

	}
	void Shield::Update()
	{
		Item::Update();

		Bombtime += Time::DeltaTime();

	} 
	void Shield::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void Shield::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			// �浹ü�� owner�� �����ͼ�
			GameObject* player = other->GetOwner();
			// Bazzi�� ������ Bazzi�� �ּҸ� ��ȯ�ϰ� �ȵǸ� nullptr
			Bazzi* bazzi = dynamic_cast<Bazzi*>(player);

			//Bazzi* player = (Bazzi*)(other->GetOwner());

			if (bazzi != nullptr)
			{
				bazzi->SetActiveItem(Bazzi::eItem::Shield);
				Bazzi::SetUseItemNum(1);
				Resources::Find<Sound>(L"EatItem")->Play(false);
				SceneManager::SetShieldGet(true);
				SceneManager::SetNeedleGet(false);


				Destroy(this);
			}

			else if (bazzi == nullptr)
			{
				Dao* dao = dynamic_cast<Dao*>(player);

				if (player != nullptr)
				{
					dao->SetActiveItem(Dao::eItem::Shield);
					Dao::SetUseItemNum(1);
					SceneManager::SetShieldGet(true);
					SceneManager::SetNeedleGet(false);

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
	void Shield::OnCollisionStay(Collider* other)
	{
	}
	void Shield::OnCollisionExit(Collider* other)
	{
	}
	void Shield::Idle()
	{
	}
	void Shield::Use()
	{
	
	}

}
