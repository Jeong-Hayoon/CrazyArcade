#include "hyShield.h"
#include "hyAnimator.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollider.h"
#include "hyBazzi.h"
#include "hyObject.h"

namespace hy
{
	Shield::Shield()
	{
		Animator* st = AddComponent<Animator>();

		Texture* Shield_ = Resources::Load<Texture>(L"Shield"
			, L"..\\Resources\\Image\\Items\\shield.bmp");

		Texture* ShieldEffect_ = Resources::Load<Texture>(L"ShieldEffect"
			, L"..\\Resources\\Image\\Items\\shieldeffect.bmp");


		st->CreateAnimation(L"Shield", Shield_, Vector2(0.0f, 0.0f), Vector2(56.0f, 70.0f), 2, Vector2(0.0f, 0.0f), 0.3f);
		st->CreateAnimation(L"BazziShield", ShieldEffect_, Vector2(0.0f, 0.0f), Vector2(88.0f, 101.0f), 4, Vector2(0.0f, 0.0f), 0.05f);

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
		// �浹ü�� owner�� �����ͼ�
		GameObject* obj = other->GetOwner();
		// Bazzi�� ������ Bazzi�� �ּҸ� ��ȯ�ϰ� �ȵǸ� nullptr
		Bazzi* player = dynamic_cast<Bazzi*>(obj);	
		if (player != nullptr)
		{
			player->SetActiveItem(Bazzi::eItem::Shield);
			Destroy(this);
		}

	
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
		//if (Input::GetKeyDown(eKeyCode::Ctrl) && ActiveItem == eItem::Shield)
		//{
		//	static float Shieldtime = 0.f;
		//	Shieldtime += Time::DeltaTime();

		//	if (Shieldtime < 3.0f)
		//	{
		//		animator->SetScale(Vector2(0.9f, 0.9f));
		//		animator->PlayAnimation(L"BazziShield", true);
		//		// ��� �浹ü �浹 ���� �ڵ� ����
		//	}

		//	else if (Shieldtime > 3.0f)
		//	{
		//		animator->SetScale(Vector2(1.0f, 1.0f));
		//		animator->PlayAnimation(L"BazziIdle", true);
		//		mState = eState::Idle;
		//	}
		//}

	}
	void Shield::Extinct()
	{
	}
}
