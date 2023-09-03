#include "hyDevil.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hyTexture.h"
#include "hyBazzi.h"
#include "hyCollider.h"
#include "hySound.h"
#include "hyTime.h"
#include "hyDao.h"



//속도 최대 아이템
namespace hy
{
	Devil::Devil()
		: mState(eState::Idle)
	{
		Animator* dt = AddComponent<Animator>();

		Texture* Devil_ = Resources::Load<Texture>(L"Devil"
			, L"..\\Resources\\Image\\Items\\Devil.bmp");

		dt->CreateAnimation(L"Devil", Devil_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, -5.f), 0.3f);
		dt->SetScale(Vector2(0.8f, 0.8f));
		dt->PlayAnimation(L"Devil", true);
	}

	Devil::~Devil()
	{
	}

	void Devil::Initialize()
	{
		Item::Initialize();

		// Devil 아이템 충돌 구현
		Collider* Devilcol = AddComponent<Collider>();

		// Devil 아이템 충돌 사각형 사이즈 수정
		Devilcol->SetSize(Vector2(10.0f, 30.0f));

		Resources::Load<Sound>(L"EatItem", L"..\\Resources\\Sound\\Sound\\eat_item.wav");

	}

	void Devil::Update()
	{
		Item::Update();

		Bombtime += Time::DeltaTime();

	}

	void Devil::Render(HDC hdc)
	{
		Item::Render(hdc);
	}

	void Devil::Idle()
	{
	}

	void Devil::Use()
	{
	}
	void Devil::Extinct()
	{
	}

	void Devil::OnCollisionEnter(Collider* other)
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
				bazzi->MoveSpeedMax();
				Resources::Find<Sound>(L"EatItem")->Play(false);

				Destroy(this);
			}

			else if (bazzi == nullptr)
			{
				Dao* dao = dynamic_cast<Dao*>(player);

				if (player != nullptr)
				{
					dao->MoveSpeedMax();
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

	void Devil::OnCollisionStay(Collider* other)
	{
	/*	Bazzi* bz = (Bazzi*)(other->GetOwner());
		bz->MoveSpeedMax();
		Destroy(this);*/
	}

	void Devil::OnCollisionExit(Collider* other)
	{
	}

}
