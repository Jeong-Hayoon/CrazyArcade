#include "hyBalloon.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hyTexture.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyGameObject.h"
#include "hySound.h"
#include "hyCollisionManager.h"


// 물풍선
namespace hy
{
	Balloon::Balloon()
		: mState(eState::Idle)
	{
		Animator* bt = AddComponent<Animator>();

		Texture* Balloon_ = Resources::Load<Texture>(L"Balloon"
			, L"..\\Resources\\Image\\Items\\balloon.bmp");

		bt->CreateAnimation(L"Balloon", Balloon_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, -5.f), 0.3f);
		bt->SetScale(Vector2(0.8f, 0.8f));
		bt->PlayAnimation(L"Balloon", true);
	}

	Balloon::~Balloon()
	{
	}

	void Balloon::Initialize()
	{
		Item::Initialize();

		// Balloon 아이템 충돌 구현
		Collider* Ballooncol = AddComponent<Collider>();
		// Balloon 아이템 충돌 사각형 사이즈 수정
		Ballooncol->SetSize(Vector2(10.0f, 30.0f));

		CollisionManager::CollisionLayerCheck(eLayerType::Item, eLayerType::Bombflow, true);
		CollisionManager::CollisionLayerCheck(eLayerType::UseItem, eLayerType::Bombflow, true);

		Resources::Load<Sound>(L"EatItem", L"..\\Resources\\Sound\\Sound\\eat_item.wav");


	}

	void Balloon::Update()
	{
		Item::Update();
	}

	void Balloon::Render(HDC hdc)
	{
		Item::Render(hdc);
	}

	void Balloon::Idle()
	{
	}

	void Balloon::Use()
	{
	}
	void Balloon::Extinct()
	{
	}
	
	void Balloon::OnCollisionEnter(Collider* other)
	{
		if(other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			Bazzi* bz = (Bazzi*)(other->GetOwner());
			if(bz != nullptr)
			{
				bz->BombLimitUp();
				Resources::Find<Sound>(L"EatItem")->Play(false);

				Destroy(this);
			}
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Destroy(this);
		}
	}

	void Balloon::OnCollisionStay(Collider* other)
	{
	}

	void Balloon::OnCollisionExit(Collider* other)
	{
	}

}
