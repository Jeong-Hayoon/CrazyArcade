#include "hyShieldEffect.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyObject.h"
#include "hyTime.h"


namespace hy
{
	ShieldEffect::ShieldEffect()/*(Bazzi * owner)*/
		: mState(eState::Idle)

	{
		Animator* st = AddComponent<Animator>();

		Texture* ShieldEffect_ = Resources::Load<Texture>(L"ShieldEffect"
			, L"..\\Resources\\Image\\Items\\shieldeffect.bmp");

		st->CreateAnimation(L"UseShieldEffect", ShieldEffect_, Vector2(0.0f, 0.0f), Vector2(88.0f, 101.0f), 4, Vector2(0.0f, 0.0f), 0.05f);
		st->SetScale(Vector2(0.9f, 0.9f));
	}
	ShieldEffect::~ShieldEffect()
	{
	}
	void ShieldEffect::Initialize()
	{
		Item::Initialize();
	}
	void ShieldEffect::Update()
	{
		Item::Update();

		//Animator* st = GetComponent<Animator>();

		//static float Shieldtime = 0.f;
		//Shieldtime += Time::DeltaTime();

		//if (Shieldtime < 3.0f)
		//{
		//	st->SetScale(Vector2(0.9f, 0.9f));
		//	st->PlayAnimation(L"UseShieldEffect", true);

		//	Transform* Bazzitr = mBazziOwner->GetComponent<Transform>();
		//	Vector2 BazziLocationtr = Bazzitr->GetPosition();
		//	Vector2 Shieldpos = BazziLocationtr->GetComponent<Transform>()->GetPosition();

		//	this->GetComponent<Transform>()->SetPosition(Shieldpos);



		//	// 모든 충돌체 충돌 끄는 코드 삽입
		//}
		//else
		//{
		//	Destroy(this);
		//}

	}
	void ShieldEffect::Render(HDC hdc)
	{
		Item::Render(hdc);
	}
	void ShieldEffect::OnCollisionEnter(Collider* other)
	{
	}
	void ShieldEffect::OnCollisionStay(Collider* other)
	{
	}
	void ShieldEffect::OnCollisionExit(Collider* other)
	{
	}
	void ShieldEffect::Idle()
	{
	}
	void ShieldEffect::Use()
	{
		Animator* st = GetComponent<Animator>();

		//static float Shieldtime = 0.f;
		//Shieldtime += Time::DeltaTime();

		//if (Shieldtime < 3.0f)
		//{
		st->SetScale(Vector2(0.9f, 0.9f));
		st->PlayAnimation(L"UseShieldEffect", true);

		//	Transform* Bazzitr = mBazziOwner->GetComponent<Transform>();
		//	Vector2 BazziLocationtr = Bazzitr->GetPosition();
		//	Vector2 Shieldpos = BazziLocationtr->GetComponent<Transform>()->GetPosition();

		//	Bomb_->GetComponent<Transform>()->SetPosition(Bombpos);



		//	// 모든 충돌체 충돌 끄는 코드 삽입
		//}
		//else
		//{
		//	Destroy(this);
		//}
	}

}
