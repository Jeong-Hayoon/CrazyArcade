#include "hyNeedle.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyObject.h"
#include "hySound.h"
#include "hyTime.h"
#include "hyDao.h"


// 바늘
namespace hy
{
	Needle::Needle()
	{
		Animator* nt = AddComponent<Animator>();

		Texture* Needle_ = Resources::Load<Texture>(L"Needle"
			, L"..\\Resources\\Image\\Items\\needle.bmp");

		nt->CreateAnimation(L"Needle", Needle_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, -5.f), 0.3f);
		nt->SetScale(Vector2(0.8f, 0.8f));
		nt->PlayAnimation(L"Needle", true);
	}
	Needle::~Needle()
	{
	}
	void Needle::Initialize()
	{
		Item::Initialize();

		// Needle 아이템 충돌 구현
		Collider* Needlecol = AddComponent<Collider>();
		// Needle 아이템 충돌 사각형 사이즈 수정
		Needlecol->SetSize(Vector2(10.0f, 30.0f));

		Resources::Load<Sound>(L"EatItem", L"..\\Resources\\Sound\\Sound\\eat_item.wav");

	}
	void Needle::Update()
	{
		Item::Update();

		Bombtime += Time::DeltaTime();

	}
	void Needle::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void Needle::OnCollisionEnter(Collider* other)
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
				bazzi->SetActiveItem(Bazzi::eItem::Needle);
				Bazzi::SetUseItemNum(1);
				Resources::Find<Sound>(L"EatItem")->Play(false);
				SceneManager::SetNeedleGet(true);
				SceneManager::SetShieldGet(false);


				Destroy(this);
			}

			else if (bazzi == nullptr)
			{
				Dao* dao = dynamic_cast<Dao*>(player);

				if (player != nullptr)
				{
					dao->SetActiveItem(Dao::eItem::Needle);
					Dao::SetUseItemNum(1);
					SceneManager::SetNeedleGet(true);
					SceneManager::SetShieldGet(false);

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
	void Needle::OnCollisionStay(Collider* other)
	{
	}
	void Needle::OnCollisionExit(Collider* other)
	{
	}

	void Needle::Use()
	{

	}

}