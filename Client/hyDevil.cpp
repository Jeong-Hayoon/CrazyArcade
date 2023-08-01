#include "hyDevil.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hyTexture.h"


namespace hy
{
	Devil::Devil()
		: mState(eState::Idle)
	{
		Animator* dt = AddComponent<Animator>();

		Texture* Devil_ = Resources::Load<Texture>(L"Devil"
			, L"..\\Resources\\Image\\Items\\Devil.bmp");

		dt->CreateAnimation(L"Devil", Devil_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, 0.0f), 0.3f);
		dt->SetScale(Vector2(1.f, 1.f));
		dt->PlayAnimation(L"Devil", true);
	}

	Devil::~Devil()
	{
	}

	void Devil::Initialize()
	{
		GameObject::Initialize();
	}

	void Devil::Update()
	{
		GameObject::Update();
	}

	void Devil::Render(HDC hdc)
	{
		GameObject::Render(hdc);
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
	}

	void Devil::OnCollisionStay(Collider* other)
	{
	}

	void Devil::OnCollisionExit(Collider* other)
	{
	}

}
