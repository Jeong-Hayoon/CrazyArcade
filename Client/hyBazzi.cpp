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
		at->CreateAnimation(L"BazziIdle", Bazzi_, Vector2(0.0f, 0.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziUp", Bazzi_, Vector2(0.0f, 60.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziDown", Bazzi_, Vector2(0.0f, 120.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziRight", Bazzi_, Vector2(0.0f, 240.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziLeft", Bazzi_, Vector2(0.0f, 180.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
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

		if (Input::GetKeyDown(eKeyCode::W))
		{
			anim->PlayAnimation(L"BazziUp", true);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			anim->PlayAnimation(L"BazziLeft", true);
		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			anim->PlayAnimation(L"BazziDown", true);
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 300.0f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			anim->PlayAnimation(L"BazziRight", true);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 300.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::K))
		{
			anim->PlayAnimation(L"BazziDie", true);
			pos.x += 300.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}

