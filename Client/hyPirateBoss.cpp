#include "hyPirateBoss.h"
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
	float PirateBoss::BossTime = 0.f;
	float PirateBoss::BubbleTime = 0.f;
	UINT PirateBoss::ForestBossHP = 100;
	float PirateBoss::Attacktime = 0.f;

	PirateBoss::PirateBoss()
		: mDeathTime(1.0f)
		, mState(eState::Right)
	{
	}
	PirateBoss::~PirateBoss()
	{
	}
	void PirateBoss::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"PirateBoss_Up", L"..\\Resources\\Image\\Monster\\PirateBoss\\Up", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"PirateBoss_Down", L"..\\Resources\\Image\\Monster\\PirateBoss\\Down", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"PirateBoss_Right", L"..\\Resources\\Image\\Monster\\PirateBoss\\Right", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"PirateBoss_Left", L"..\\Resources\\Image\\Monster\\PirateBoss\\Left", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"PirateBoss_Die", L"..\\Resources\\Image\\Monster\\PirateBoss\\Die", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"PirateBoss_Hit", L"..\\Resources\\Image\\Monster\\PirateBoss\\Hit", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"PirateBoss_Bubble", L"..\\Resources\\Image\\Monster\\PirateBoss\\Bubble", Vector2::Zero, 0.2f);

		mt->SetScale(Vector2(2.f, 2.f));
		mt->PlayAnimation(L"PirateBoss_Right", true);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(100.0f, 100.0f));
		CollisionManager::CollisionLayerCheck(eLayerType::Boss, eLayerType::Bombflow, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BossBombflow, true);



		GameObject::Initialize();
	}
	void PirateBoss::Update()
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
		else if (pos.y <= 80)
		{
			pos.y = 80;
		}
		else if (pos.y >= 520)
		{
			pos.y = 520;
		}

		tr->SetPosition(pos);


		switch (mState)
		{
		case hy::PirateBoss::eState::Idle:
			Idle();
			break;

		case hy::PirateBoss::eState::Up:
			Up();
			break;

		case hy::PirateBoss::eState::Down:
			Down();
			break;

		case hy::PirateBoss::eState::Left:
			Left();
			break;

		case hy::PirateBoss::eState::Right:
			Right();
			break;

		case hy::PirateBoss::eState::Dead:
			Dead();
			break;

		case hy::PirateBoss::eState::Attack:
			Attack();
			break;

		case hy::PirateBoss::eState::End:
			break;

		default:
			break;
		}

		Attacktime += Time::DeltaTime();
		if (Attacktime > 5.f)
		{
			mState = eState::Attack;
		}


	}
	void PirateBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	// 충돌했을 때 처리 코드 여기에 작성
	// 물풍선과 충돌했을 때 Dead
	void PirateBoss::OnCollisionEnter(Collider* other)
	{
		Animator* at = GetComponent<Animator>();

		if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			if (ForestBossHP == 0)
			{
				BubbleTime += Time::DeltaTime();

				if (BubbleTime < 3.f)
				{
					at->PlayAnimation(L"PirateBoss_Bubble", false);
				}
				else if (BubbleTime > 3.f)
				{
					at->PlayAnimation(L"PirateBoss_Die", false);

					mState = eState::Dead;
					BubbleTime = 0.f;
				}
			}

			else if (ForestBossHP != 0)
			{
				at->PlayAnimation(L"PirateBoss_Hit", false);
				mState = eState::Hit;
			}
		}

	}

	void PirateBoss::OnCollisionStay(Collider* other)
	{
	}

	void PirateBoss::OnCollisionExit(Collider* other)
	{
	}

	void PirateBoss::Idle()
	{

	}

	void PirateBoss::Up()
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
				animator->PlayAnimation(L"PirateBoss_Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"PirateBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"PirateBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"PirateBoss_Down", true);
				mState = eState::Down;
			}

			BossTime = 0.f;
		}
	}

	void PirateBoss::Down()
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
				animator->PlayAnimation(L"PirateBoss_Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"PirateBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"PirateBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"PirateBoss_Down", true);
				mState = eState::Down;
			}

			BossTime = 0.f;
		}
	}

	void PirateBoss::Left()
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
				animator->PlayAnimation(L"PirateBoss_Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"PirateBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"PirateBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"PirateBoss_Down", true);
				mState = eState::Down;
			}

			BossTime = 0.f;
		}
	}

	void PirateBoss::Right()
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
				animator->PlayAnimation(L"PirateBoss_Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"PirateBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"PirateBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"PirateBoss_Down", true);
				mState = eState::Down;
			}

			BossTime = 0.f;
		}
	}

	void PirateBoss::Hit()
	{
		ForestBossHP -= 10;
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"PirateBoss_Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"PirateBoss_Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"PirateBoss_Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"PirateBoss_Down", true);
				mState = eState::Down;
			}
		}

	}


	void PirateBoss::Attack()
	{
		int Target_X = rand() % 15;		// 0~14
		int Target_Y = rand() % 13;		// 0~12
		int Select_XY = rand() % 2;		// 세로 공격할건지 가로 공격할건지 랜덤

		int a = 0;

		// Y 고정(X값 증가) - 가로 공격
		if(Select_XY == 0)
		{
			for (int j = 0; j < 15; j++)	// x
			{
				Vector2 Bossbombpos;
				Bossbombpos.x = j;
				if (Target_Y == 0)
				{
					Target_Y = 1;
				}
				if (Target_Y == 12)
				{
					Target_Y = 11;
				}
				Bossbombpos.y = Target_Y;

				Bossbombpos.x = ((Bossbombpos.x) * (TILE_WIDTH)) + (TILE_WIDTH / 2) + 20.f;
				Bossbombpos.y = ((Bossbombpos.y) * (TILE_HEIGHT)) + (TILE_HEIGHT / 2) + 40.f;

				BossBomb* bomb_ = object::Instantiate<BossBomb>(eLayerType::BossBombflow);
				bomb_->GetComponent<Transform>()->SetPosition(Bossbombpos);
			}
		}

		// X 고정(Y값 증가) - 세로 공격
		if (Select_XY == 1)
		{
			for (int i = 0; i < 13; i++)	// x
			{
				if (i == 0 || i == 12)
				{
					continue;
				}

				Vector2 Bossbombpos;
				Bossbombpos.x = Target_X;
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

	void PirateBoss::Dead()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			SceneManager:: KillBossQuantity();

		}
	}
}

