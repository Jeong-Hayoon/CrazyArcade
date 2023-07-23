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
#include "hyBazzi.h"


namespace hy
{
	Bomb::Bomb()
		: mState(eState::Idle)
	{
		Animator* bt = AddComponent<Animator>();
		bt->CreateAnimationFolder(L"BombidleBottom", L"..\\Resources\\Image\\Bomb\\Idle", Vector2(0.f,70.f), 0.4f);
		bt->CreateAnimationFolder(L"BombidleTop", L"..\\Resources\\Image\\Bomb\\Idle", Vector2(0.f, -70.f), 0.4f);
		bt->CreateAnimationFolder(L"BombidleLeft", L"..\\Resources\\Image\\Bomb\\Idle", Vector2(-70.f, 0.f), 0.4f);
		bt->CreateAnimationFolder(L"BombidleRight", L"..\\Resources\\Image\\Bomb\\Idle", Vector2(+70.f, 0.f), 0.4f);

		bt->PlayAnimation(L"BombidleBottom", true);

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

		// tab + enter �ϸ� ����ġ ����
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
		/*if (Bazzi::GetDirection() == Up)
		{
			animator->PlayAnimation(L"BazziUpStop", true);
		}
		if (mDirection == eDirection::Down)
		{
			animator->PlayAnimation(L"BazziDownStop", true);
		}
		if (mDirection == eDirection::Left)
		{
			animator->PlayAnimation(L"BazziLeftStop", true);
		}
		if (mDirection == eDirection::Right)
		{
			animator->PlayAnimation(L"BazziRightStop", true);
		}*/
		
	}
	void Bomb::Pop()
	{
		
	}


}

