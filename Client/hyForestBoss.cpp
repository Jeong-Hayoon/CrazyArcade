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
#include "hyCollisionManager.h"
#include "hyBossBomb.h"



namespace hy
{
	// static 변수는 전역에서 초기화해주기
	float ForestBoss::BossTime = 0.f;
	float ForestBoss::BubbleTime = 0.f;	
	UINT ForestBoss::ForestBossHP = 100;
	float ForestBoss::Attacktime = 0.f;

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

		mt->SetScale(Vector2(2.f, 2.f));
		mt->PlayAnimation(L"ForestBoss_Right", true);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(100.0f, 100.0f));
		CollisionManager::CollisionLayerCheck(eLayerType::Boss, eLayerType::Bombflow, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BossBombflow, true);

		
		GameObject::Initialize();
	}
	void ForestBoss::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();

		if (pos.x >= 590)
		{
			pos.x = 590;
		}
		else if (pos.x <= 40)
		{
			pos.x = 40;
		}
		else if (pos.y <= 50)
		{
			pos.y = 50;
		}
		else if (pos.y >= 530)
		{
			pos.y = 530;
		}

		tr->SetPosition(pos);


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

		case hy::ForestBoss::eState::Attack:
			Attack();
			break;

		case hy::ForestBoss::eState::End:
			break;

		default:
			break;
		}

		Attacktime += Time::DeltaTime();
		if (Attacktime > 5.f)
		{
			at->PlayAnimation(L"ForestBoss_Attack", false);
			mState = eState::Attack;
		}


	}
	void ForestBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	// 충돌했을 때 처리 코드 여기에 작성
	// 물풍선과 충돌했을 때 Dead
	void ForestBoss::OnCollisionEnter(Collider* other)
	{
		Animator* at = GetComponent<Animator>();

		if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			if(ForestBossHP == 0)
			{
				BubbleTime += Time::DeltaTime();

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
				at->PlayAnimation(L"ForestBoss_Hit", false);
				mState = eState::Hit;
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
		pos.y -= 50.f * Time::DeltaTime();
		tr->SetPosition(pos);

		BossTime += Time::DeltaTime();

		if (BossTime > 3.f)
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"ForestBoss_Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"ForestBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"ForestBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"ForestBoss_Down", true);
				mState = eState::Down;
			}

			BossTime = 0.f;
		}
	}

	void ForestBoss::Down()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		pos.y += 50.f * Time::DeltaTime();
		tr->SetPosition(pos);

		BossTime += Time::DeltaTime();

		if (BossTime > 3.f)
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"ForestBoss_Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"ForestBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"ForestBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"ForestBoss_Down", true);
				mState = eState::Down;
			}

			BossTime = 0.f;
		}
	}

	void ForestBoss::Left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		pos.x -= 50.f * Time::DeltaTime();
		tr->SetPosition(pos);

		BossTime += Time::DeltaTime();

		if (BossTime > 3.f)
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"ForestBoss_Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"ForestBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"ForestBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"ForestBoss_Down", true);
				mState = eState::Down;
			}

			BossTime = 0.f;
		}
	}

	void ForestBoss::Right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();			
		pos.x += 50.f * Time::DeltaTime();
		tr->SetPosition(pos);

		BossTime += Time::DeltaTime();

		if (BossTime > 3.f)
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"ForestBoss_Right", true);
				mState = eState::Right;

			}
			else if(StateSelect == 1)
			{
				animator->PlayAnimation(L"ForestBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"ForestBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"ForestBoss_Down", true);
				mState = eState::Down;
			}

			BossTime = 0.f;
		}
	}

	void ForestBoss::Hit()
	{
		ForestBossHP -= 10;
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"ForestBoss_Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"ForestBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"ForestBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"ForestBoss_Down", true);
				mState = eState::Down;
			}
		}
		
	}


	void ForestBoss::Attack()
	{
		int Target_X = rand() % 13;		// 0~12
		int Target_Y = rand() % 11;		// 0~ 10

		for (int i = Target_Y; i < Target_Y + 3; i++)		// y
		{
			for (int j = Target_X; j < Target_X + 3; j++)	// x
			{

				Vector2 Bossbombpos;
				Bossbombpos.x = j;
				Bossbombpos.y = i;

				Bossbombpos.x = ((Bossbombpos.x) * (TILE_WIDTH)) + (TILE_WIDTH / 2) + 20.f;
				Bossbombpos.y = ((Bossbombpos.y) * (TILE_HEIGHT)) + (TILE_HEIGHT / 2) + 40.f;

				BossBomb* bomb_ = object::Instantiate<BossBomb>(eLayerType::BossBombflow);
				bomb_->GetComponent<Transform>()->SetPosition(Bossbombpos);
			}
		}

		Attacktime = 0.f;

		mState = eState::Right;

	}

	void ForestBoss::Dead()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			// 보스 개수 줄이는 코드
			//ForestMap1::SetFunCheck(1);

		}
	}
}

