#include "hyUseShield.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyObject.h"
#include "hyTime.h"

namespace hy
{
	UseShield::UseShield()
	{
		Animator* st = AddComponent<Animator>();

		Texture* ShieldEffect_ = Resources::Load<Texture>(L"ShieldEffect"
			, L"..\\Resources\\Image\\Items\\shieldeffect.bmp");


		st->CreateAnimation(L"BazziShield", ShieldEffect_, Vector2(0.0f, 0.0f), Vector2(88.0f, 101.0f), 4, Vector2(0.0f, 0.0f), 0.05f);

		st->SetScale(Vector2(0.9f, 0.9f));
	}
	UseShield::~UseShield()
	{
	}
	void UseShield::Initialize()
	{
		Item::Initialize();
	}
	void UseShield::Update()
	{



		Item::Update();
	}
	void UseShield::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void UseShield::OnCollisionEnter(Collider* other)
	{
	}
	void UseShield::OnCollisionStay(Collider* other)
	{
	}
	void UseShield::OnCollisionExit(Collider* other)
	{
	}
	void UseShield::Idle()
	{
	}
	void UseShield::Use()
	{
		Animator* st = GetComponent<Animator>();

		static float Shieldtime = 0.f;
		Shieldtime += Time::DeltaTime();

		if (Shieldtime < 3.0f)
		{
			st->SetScale(Vector2(0.9f, 0.9f));
			st->PlayAnimation(L"BazziShield", true);
			// 모든 충돌체 충돌 끄는 코드 삽입
		}
		else
		{
			Destroy(this);
		}
	}

}
