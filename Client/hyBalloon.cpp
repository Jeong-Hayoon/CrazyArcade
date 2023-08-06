#include "hyBalloon.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hyTexture.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyGameObject.h"



// ¹°Ç³¼±
namespace hy
{
	Balloon::Balloon()
		: mState(eState::Idle)
	{
		Animator* bt = AddComponent<Animator>();

		Texture* Balloon_ = Resources::Load<Texture>(L"Balloon"
			, L"..\\Resources\\Image\\Items\\balloon.bmp");

		bt->CreateAnimation(L"Balloon", Balloon_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, 0.0f), 0.3f);
		bt->SetScale(Vector2(0.9f, 0.9f));
		bt->PlayAnimation(L"Balloon", true);
	}

	Balloon::~Balloon()
	{
	}

	void Balloon::Initialize()
	{
		Item::Initialize();
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
	}

	void Balloon::OnCollisionStay(Collider* other)
	{
		Bazzi* bz = (Bazzi*)(other->GetOwner());
		bz->BombLimitUp();
		Destroy(this);
	}

	void Balloon::OnCollisionExit(Collider* other)
	{
	}

}
