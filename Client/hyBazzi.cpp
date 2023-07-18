#include "hyBazzi.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hyForestMap.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"


namespace hy
{
	Bazzi::Bazzi()
	{
	}
	Bazzi::~Bazzi()
	{
	}
	void Bazzi::Initialize()
	{

		Texture* Bazzi_ = Resources::Load<Texture>(L"Bazzi"
			, L"..\\Resources\\Image\\Bazzi\\Bazzi.bmp");

		/*bazzi->GetComponent<Transform>()->SetPosition(Vector2(60.0f, 70.0f));*/

		Animator* at = AddComponent<Animator>();
		at->CreateAnimation(L"BazziIdle", Bazzi_, Vector2(0.0f, 0.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.6f);

		at->CreateAnimation(L"BazziUp", Bazzi_, Vector2(0.0f, 60.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziUpStop", Bazzi_, Vector2(0.0f, 60.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f),1.0f);

		at->CreateAnimation(L"BazziDown", Bazzi_, Vector2(0.0f, 120.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziDownStop", Bazzi_, Vector2(0.0f, 120.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziRight", Bazzi_, Vector2(0.0f, 240.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziRightStop", Bazzi_, Vector2(0.0f, 240.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziLeft", Bazzi_, Vector2(0.0f, 180.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziLeftStop", Bazzi_, Vector2(0.0f, 180.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.05f);

		at->CreateAnimation(L"BazziDie", Bazzi_, Vector2(0.0f, 300.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);

		at->PlayAnimation(L"BazziIdle", true);
		at->SetScale(Vector2(1.3f, 1.3f));

		GameObject::Initialize();
	}
	void Bazzi::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		// 위
		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 250.0f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			anim->PlayAnimation(L"BazziUp", true);
		}
		if (Input::GetKeyUp(eKeyCode::W))
		{
			anim->PlayAnimation(L"BazziUpStop", true);
		}


		// 왼쪽
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 250.0f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			anim->PlayAnimation(L"BazziLeft", true);
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			anim->PlayAnimation(L"BazziLeftStop", true);
		}

		// 아래
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 250.0f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			anim->PlayAnimation(L"BazziDown", true);
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			anim->PlayAnimation(L"BazziIdle", true);
		}

		// 오른쪽
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 250.0f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			anim->PlayAnimation(L"BazziRight", true);
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			anim->PlayAnimation(L"BazziRightStop", true);
		}

		if (Input::GetKey(eKeyCode::K))
		{
			anim->PlayAnimation(L"BazziDie", true);
		}


		tr->SetPosition(pos);
	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}

