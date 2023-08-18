#include "hyDevil.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hyTexture.h"
#include "hyBazzi.h"
#include "hyCollider.h"
#include "hySound.h"



//속도 최대 아이템
namespace hy
{
	Devil::Devil()
		: mState(eState::Idle)
	{
		


		Animator* dt = AddComponent<Animator>();

		Texture* Devil_ = Resources::Load<Texture>(L"Devil"
			, L"..\\Resources\\Image\\Items\\Devil.bmp");

		dt->CreateAnimation(L"Devil", Devil_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, 0.0f), 0.3f);
		dt->SetScale(Vector2(0.9f, 0.9f));
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
		Bazzi* bz = (Bazzi*)(other->GetOwner());
		bz->MoveSpeedMax();
		Resources::Find<Sound>(L"EatItem")->Play(false);

		Destroy(this);
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
