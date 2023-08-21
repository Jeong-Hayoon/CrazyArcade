#include "hyNeedle.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyObject.h"
#include "hySound.h"


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
	}
	void Needle::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void Needle::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			Bazzi* bz = (Bazzi*)(other->GetOwner());
			if (bz != nullptr)
			{
				bz->SetActiveItem(Bazzi::eItem::Needle);
				Bazzi::SetUseItemNum(1);
				Resources::Find<Sound>(L"EatItem")->Play(false);

				Destroy(this);
			}
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
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