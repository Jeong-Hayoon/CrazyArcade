#include "hyShield.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"


namespace hy
{
	Shield::Shield()
	{
		Animator* st = AddComponent<Animator>();

		Texture* Shield_ = Resources::Load<Texture>(L"Shield"
			, L"..\\Resources\\Image\\Items\\shield.bmp");

		st->CreateAnimation(L"Shield", Shield_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, 0.0f), 0.3f);
		st->SetScale(Vector2(0.9f, 0.9f));
		st->PlayAnimation(L"Shield", true);
	}
	Shield::~Shield()
	{
	}
	void Shield::Initialize()
	{
		Item::Initialize();
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
	void Shield::Extinct()
	{
	}
}
