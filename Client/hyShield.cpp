#include "hyShield.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyObject.h"
#include "hyTime.h"
#include "hySound.h"


namespace hy
{
	Shield::Shield()
	{



		Animator* st = AddComponent<Animator>();

		Texture* Shield_ = Resources::Load<Texture>(L"Shield"
			, L"..\\Resources\\Image\\Items\\shield.bmp");

		Texture* ShieldEffect_ = Resources::Load<Texture>(L"ShieldEffect"
			, L"..\\Resources\\Image\\Items\\shieldeffect.bmp");


		st->CreateAnimation(L"Shield", Shield_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, 0.0f), 0.3f);
		st->CreateAnimation(L"BazziShield", ShieldEffect_, Vector2(0.0f, 0.0f), Vector2(88.0f, 101.0f), 4, Vector2(0.0f, 0.0f), 0.05f);

		st->SetScale(Vector2(0.9f, 0.9f));
		st->PlayAnimation(L"Shield", true);
	}
	Shield::~Shield()
	{
	}
	void Shield::Initialize()
	{
		Item::Initialize();

		// Shield 아이템 충돌 구현
		Collider* Shieldcol = AddComponent<Collider>();
		// Shield 아이템 충돌 사각형 사이즈 수정
		Shieldcol->SetSize(Vector2(10.0f, 30.0f));

		Resources::Load<Sound>(L"EatItem", L"..\\Resources\\Sound\\Sound\\eat_item.wav");

	}
	void Shield::Update()
	{
		Item::Update();
	} 
	void Shield::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void Shield::OnCollisionEnter(Collider* other)
	{
		// 충돌체의 owner를 가져와서
		GameObject* obj = other->GetOwner();
		// Bazzi과 같으면 Bazzi의 주소를 반환하고 안되면 nullptr
		Bazzi* player = dynamic_cast<Bazzi*>(obj);	
		if (player != nullptr)
		{
			player->SetActiveItem(Bazzi::eItem::Shield);
			Bazzi::SetUseItemNum(1);
			Resources::Find<Sound>(L"EatItem")->Play(false);

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
