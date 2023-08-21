#include "hyIceBoss.h"
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
	float IceBoss::BossTime = 0.f;
	float IceBoss::BubbleTime = 0.f;
	UINT IceBoss::ForestBossHP = 100;
	float IceBoss::Attacktime = 0.f;

	IceBoss::IceBoss()
		: mDeathTime(1.0f)
		, mState(eState::Right)
	{
	}
	IceBoss::~IceBoss()
	{
	}
	void IceBoss::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"IceBoss_Up", L"..\\Resources\\Image\\Monster\\IceBoss\\Up", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"IceBoss_Down", L"..\\Resources\\Image\\Monster\\IceBoss\\Down", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"IceBoss_Right", L"..\\Resources\\Image\\Monster\\IceBoss\\Right", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"IceBoss_Left", L"..\\Resources\\Image\\Monster\\IceBoss\\Left", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"IceBoss_Die", L"..\\Resources\\Image\\Monster\\IceBoss\\Die", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"IceBoss_Attack", L"..\\Resources\\Image\\Monster\\IceBoss\\Attack", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"IceBoss_Hit", L"..\\Resources\\Image\\Monster\\IceBoss\\Hit", Vector2::Zero, 0.2f);
		mt->CreateAnimationFolder(L"IceBoss_Bubble", L"..\\Resources\\Image\\Monster\\IceBoss\\Bubble", Vector2::Zero, 0.2f);

		mt->SetScale(Vector2(2.f, 2.f));
		mt->PlayAnimation(L"IceBoss_Right", true);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(100.0f, 100.0f));
		CollisionManager::CollisionLayerCheck(eLayerType::Boss, eLayerType::Bombflow, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BossBombflow, true);



		GameObject::Initialize();
	}
	void IceBoss::Update()
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
		case hy::IceBoss::eState::Idle:
			Idle();
			break;

		case hy::IceBoss::eState::Up:
			Up();
			break;

		case hy::IceBoss::eState::Down:
			Down();
			break;

		case hy::IceBoss::eState::Left:
			Left();
			break;

		case hy::IceBoss::eState::Right:
			Right();
			break;

		case hy::IceBoss::eState::Dead:
			Dead();
			break;

		case hy::IceBoss::eState::Attack:
			Attack();
			break;

		case hy::IceBoss::eState::End:
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
	void IceBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	// 충돌했을 때 처리 코드 여기에 작성
	// 물풍선과 충돌했을 때 Dead
	void IceBoss::OnCollisionEnter(Collider* other)
	{
		Animator* at = GetComponent<Animator>();

		if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			if (ForestBossHP == 0)
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

			else if (ForestBossHP != 0)
			{
				at->PlayAnimation(L"ForestBoss_Hit", false);
				mState = eState::Hit;
			}
		}

	}

	void IceBoss::OnCollisionStay(Collider* other)
	{
	}

	void IceBoss::OnCollisionExit(Collider* other)
	{
	}

	void IceBoss::Idle()
	{

	}

	void IceBoss::Up()
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

	void IceBoss::Down()
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

	void IceBoss::Left()
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

	void IceBoss::Right()
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

	void IceBoss::Hit()
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


	void IceBoss::Attack()
	{
		srand(time(NULL));

		int MultipleNum = (rand() % 6) + 1;

		for (int i = 6 - MultipleNum; i <= 6 + MultipleNum; i++)		// y
		{
			for (int j = 7 - MultipleNum; j <= 7 + MultipleNum; j++)		// x
			{
				float newX = j;
				float newY = i;

				if ((newY != 6 - MultipleNum)
					&& (newY != 6 + MultipleNum)
					&& (newX != 7 - MultipleNum)
					&& (newX != 7 + MultipleNum))
				{
					continue;
				}

				Vector2 Bossbombpos;
				Bossbombpos.x = newX;
				Bossbombpos.y = newY;

				Bossbombpos.x = ((Bossbombpos.x) * (TILE_WIDTH)) + (TILE_WIDTH / 2) + 20.f;
				Bossbombpos.y = ((Bossbombpos.y) * (TILE_HEIGHT)) + (TILE_HEIGHT / 2) + 40.f;

				BossBomb* bomb_ = object::Instantiate<BossBomb>(eLayerType::BossBombflow);
				bomb_->GetComponent<Transform>()->SetPosition(Bossbombpos);
			}

		}

		//// 해당 타일 인덱스를 구함
		//X_ = (BazziLocationtr.x - 20.f) / (TILE_WIDTH);
		//Y_ = (BazziLocationtr.y - 40.f) / (TILE_HEIGHT);

		//// 해당 타일 인덱스에 타일 사이즈를 곱하여 해당 타일의 LeftTop으로 이동
		//Bombpos.x = (X_ * TILE_WIDTH) + (TILE_WIDTH / 2) + 20.f;
		//Bombpos.y = (Y_ * TILE_HEIGHT) + (TILE_HEIGHT / 2) + 40.f;


		Attacktime = 0.f;

		mState = eState::Right;

	}

	void IceBoss::Dead()
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

