#include "hyBomb.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
// #include "hyForestMap1.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyRigidbody.h"


namespace hy
{
	Bomb::Bomb()
		: mState(eState::Idle)
	{
		Animator* bt = AddComponent<Animator>();
		bt->CreateAnimationFolder(L"Bombidle", L"..\\Resources\\Image\\Bomb\\Idle");

		bt->PlayAnimation(L"Bombidle", true);

	}
	Bomb::~Bomb()
	{
	}
	void Bomb::Initialize()
	{
		GameObject::Initialize();
	}
	void Bomb::Update()
	{
		GameObject::Update();

		// tab + enter 하면 스위치 생성
		switch (mState)
		{
		case hy::Bomb::eState::Idle:
			Idle();
			break;
		case hy::Bomb::eState::Pop:
			Pop();
			break;
		case hy::Bomb::eState::End:
			break;
		default:
			break;
		}

	}
	void Bomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bomb::OnCollisionEnter(Collider* other)
	{
	}
	void Bomb::OnCollisionStay(Collider* other)
	{
	}
	void Bomb::OnCollisionExit(Collider* other)
	{
	}

	void Bomb::Idle()
	{
		Animator* bt = GetComponent<Animator>();
		bt->PlayAnimation(L"Bombidle", true);

	}
	void Bomb::Pop()
	{
		
	}


}

