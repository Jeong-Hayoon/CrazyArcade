#include "hyForestBoss.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollider.h"
#include "hyForestMap3.h"
#include "hySound.h"



namespace hy
{
	// static 변수는 전역에서 초기화해주기
	float ForestBoss::BossTime = 0.f;
	float ForestBoss::BubbleTime = 0.f;	
	UINT ForestBoss::ForestBossHP = 100;

	ForestBoss::ForestBoss()
		: mDeathTime(1.0f)
		, mState(eState::Right)
	{
	}
	ForestBoss::~ForestBoss()
	{
	}
	void ForestBoss::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"ForestBoss_Up", L"..\\Resources\\Image\\Monster\\ForestBoss\\Up", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestBoss_Down", L"..\\Resources\\Image\\Monster\\ForestBoss\\Down", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestBoss_Right", L"..\\Resources\\Image\\Monster\\ForestBoss\\Right", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestBoss_Left", L"..\\Resources\\Image\\Monster\\ForestBoss\\Left", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestBoss_Die", L"..\\Resources\\Image\\Monster\\ForestBoss\\Die", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"ForestBoss_Attack", L"..\\Resources\\Image\\Monster\\ForestBoss\\Attack", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"ForestBoss_Hit", L"..\\Resources\\Image\\Monster\\ForestBoss\\Hit", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"ForestBoss_Bubble", L"..\\Resources\\Image\\Monster\\ForestBoss\\Bubble", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"ForestBoss_LeftRoll", L"..\\Resources\\Image\\Monster\\ForestBoss\\LeftRoll", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"ForestBoss_RightRoll", L"..\\Resources\\Image\\Monster\\ForestBoss\\RightRoll", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"ForestBoss_Idle", L"..\\Resources\\Image\\Monster\\ForestBoss\\Idle", Vector2::Zero, 0.2f);


		mt->PlayAnimation(L"ForestBoss_Idle", true);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(65.0f, 80.0f));

		GameObject::Initialize();
	}
	void ForestBoss::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (pos.x >= 610)
		{
			pos.x = 610;
		}
		else if (pos.x <= 30)
		{
			pos.x = 30;
		}
		else if (pos.y <= 40)
		{
			pos.y = 30;
		}
		else if (pos.y >= 530)
		{
			pos.y = 30;
		}

		switch (mState)
		{
		case hy::ForestBoss::eState::Idle:
			Idle();
			break;

		case hy::ForestBoss::eState::Up:
			Up();
			break;

		case hy::ForestBoss::eState::Down:
			Down();
			break;

		case hy::ForestBoss::eState::Left:
			Left();
			break;

		case hy::ForestBoss::eState::Right:
			Right();
			break;

		case hy::ForestBoss::eState::Dead:
			Dead();
			break;

		case hy::ForestBoss::eState::End:
			break;

		default:
			break;
		}

		tr->SetPosition(pos);

	}
	void ForestBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	// 충돌했을 때 처리 코드 여기에 작성
	// 물풍선과 충돌했을 때 Dead
	void ForestBoss::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			if(ForestBossHP == 0)
			{
				BubbleTime += Time::DeltaTime();
				Animator* at = GetComponent<Animator>();
				if (BubbleTime < 3.f)
				{
					at->PlayAnimation(L"ForestBoss_Bubble", false);
				}
				else if (BubbleTime > 3.f)
				{
					at->PlayAnimation(L"ForestBoss_Die", false);

					mState = eState::Dead;
					BubbleTime = 0.f;
				}
			}

			else if(ForestBossHP != 0)
			{
				ForestBossHP -= 10;
			}
		}
		
	}

	void ForestBoss::OnCollisionStay(Collider* other)
	{
	}

	void ForestBoss::OnCollisionExit(Collider* other)
	{
	}

	void ForestBoss::Idle()
	{
		
	}

	void ForestBoss::Up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		BossTime += Time::DeltaTime();

		animator->PlayAnimation(L"ForestBoss_Down", true);

		if (BossTime > 7.f)
		{
			pos.y -= 50.f * Time::DeltaTime();
			tr->SetPosition(pos);

			if (BossTime > 10.f)
			{
				animator->PlayAnimation(L"ForestBoss_Right", true);
				mState = eState::Right;
				BossTime = 0.f;
			}
		}
	}

	void ForestBoss::Down()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();		
		
		BossTime += Time::DeltaTime();

		if(BossTime > 7.f)
		{
			pos.y += 50.f * Time::DeltaTime();
			tr->SetPosition(pos);
			if(BossTime > 10.f)
			{
				animator->PlayAnimation(L"ForestBoss_Down", true);
				mState = eState::Left;
				BossTime = 0.f;
			}
		}
	}

	void ForestBoss::Left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();		//
		BossTime += Time::DeltaTime();

		if (BossTime > 7.f)
		{
			pos.x -= 50.f * Time::DeltaTime();
			tr->SetPosition(pos);

			animator->PlayAnimation(L"ForestBoss_Left", true);


			if (BossTime > 10.f)
			{
				animator->PlayAnimation(L"ForestBoss_Up", true);
				mState = eState::Up;
				BossTime = 0.f;
			}
		}
	}

	void ForestBoss::Right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();			//
		
		BossTime += Time::DeltaTime();

		if (BossTime > 7.f)
		{
			animator->PlayAnimation(L"ForestBoss_Right", true);

			pos.x += 50.f * Time::DeltaTime();
			tr->SetPosition(pos);

			if(BossTime > 10.f)
			{
				animator->PlayAnimation(L"ForestBoss_Down", true);
				mState = eState::Down;
				BossTime = 0.f;
			}
		}

	}

	void ForestBoss::Dead()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			ForestMap3::SetBossLife();
			//ForestMap1::SetFunCheck(1);

		}
	}
}

