#include "hyForestMonster_1.h"
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
#include "hyForestMap1.h"
#include "hySound.h"



namespace hy
{
	// static 변수는 전역에서 초기화해주기
	float ForestMonster_1:: MonsterTime = 0.f;

	ForestMonster_1::ForestMonster_1()
		: mDeathTime(1.0f)
		, mState(eState::Right)
		, North(1)
		, South(1)
		, East(1)
		, West(1)
	{
	}
	ForestMonster_1::~ForestMonster_1()
	{
	}
	void ForestMonster_1::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"ForestMonster_1Up", L"..\\Resources\\Image\\Monster\\Forest\\Up", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonster_1Down", L"..\\Resources\\Image\\Monster\\Forest\\Down",Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonster_1Right", L"..\\Resources\\Image\\Monster\\Forest\\Right", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonster_1Left", L"..\\Resources\\Image\\Monster\\Forest\\Left", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonnsterDie", L"..\\Resources\\Image\\Monster\\Forest\\Die", Vector2::Zero, 0.2f);
		mt->PlayAnimation(L"ForestMonster_1Right", true);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(30.0f, 30.0f));

		GameObject::Initialize();
	}
	void ForestMonster_1::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
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
		case hy::ForestMonster_1::eState::Up:
			Up();
			break;

		case hy::ForestMonster_1::eState::Down:
			Down();
			break;

		case hy::ForestMonster_1::eState::Left:
			Left();
			break;

		case hy::ForestMonster_1::eState::Right:
			Right();
			break;

		case hy::ForestMonster_1::eState::Dead:
			Dead();
			break;

		case hy::ForestMonster_1::eState::End:
			break;

		default:
			break;
		}
	}
	void ForestMonster_1::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	// 충돌했을 때 처리 코드 여기에 작성
	// 물풍선과 충돌했을 때 Dead
	void ForestMonster_1::OnCollisionEnter(Collider* other)
	{
		Animator* animator = GetComponent<Animator>();

		// 충돌체의 owner를 가져와서
		GameObject* obj = other->GetOwner();
		// Tile과 같으면 Tile의 주소를 반환하고 안되면 nullptr
		Tile* tile = dynamic_cast<Tile*>(obj);

		if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"ForestMonnsterDie", false);
			ForestMap1::SetMonsterQuantity;
			mState = eState::Dead;
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Crack)
		{
			if (mDirection == eDirection::Right)
			{
				East = 0;
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mState = eState::Left;
				mDirection = eDirection::Left;
			}
			else if (mDirection == eDirection::Left)
			{
				West = 0;
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mState = eState::Right;
				mDirection = eDirection::Right;
			}
			else if (mDirection == eDirection::Down)
			{
				South = 0;
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mState = eState::Up;
				mDirection = eDirection::Up;
			}
			else if (mDirection == eDirection::Up)
			{
				North = 0;
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mState = eState::Down;
				mDirection = eDirection::Down;
			}

		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Uncrushable)
		{
			// 몬스터 이동 방향 반대로
			if (mDirection == eDirection::Right)
			{
				East = 0;
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mState = eState::Left;
				mDirection = eDirection::Left;
			}
			else if (mDirection == eDirection::Left)
			{
				West = 0;
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mState = eState::Right;
				mDirection = eDirection::Right;
			}
			else if (mDirection == eDirection::Down)
			{
				South = 0;
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mState = eState::Up;
				mDirection = eDirection::Up;
			}
			else if (mDirection == eDirection::Up)
			{
				North = 0;
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mState = eState::Down;
				mDirection = eDirection::Down;
			}
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Bomb)
		{
			if (mDirection == eDirection::Right)
			{
				East = 0;
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mState = eState::Left;
				mDirection = eDirection::Left;
			}
			else if (mDirection == eDirection::Left)
			{
				West = 0;
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mState = eState::Right;
				mDirection = eDirection::Right;
			}
			else if (mDirection == eDirection::Down)
			{
				South = 0;
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mState = eState::Up;
				mDirection = eDirection::Up;
			}
			else if (mDirection == eDirection::Up)
			{
				North = 0;
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mState = eState::Down;
				mDirection = eDirection::Down;
			}

		}
	}

	void ForestMonster_1::OnCollisionStay(Collider* other)
	{

	}

	void ForestMonster_1::OnCollisionExit(Collider* other)
	{
		North = 1;
		South = 1;
		East = 1;
		West = 1;
	}

	void ForestMonster_1::Up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		pos.y -= North * 50.f * Time::DeltaTime();
		tr->SetPosition(pos);

		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 2.f)
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mState = eState::Right;
				mDirection = eDirection::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mState = eState::Left;
				mDirection = eDirection::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mState = eState::Up;
				mDirection = eDirection::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mState = eState::Down;
				mDirection = eDirection::Down;

			}

			MonsterTime = 0.f;
		}

	}

	void ForestMonster_1::Down()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		pos.y += South * 50.f * Time::DeltaTime();
		tr->SetPosition(pos);

		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 2.f)
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mState = eState::Down;
			}

			MonsterTime = 0.f;
		}
	}

	void ForestMonster_1::Left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		pos.x -= West * 50.f * Time::DeltaTime();
		tr->SetPosition(pos);

		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 2.f)
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mState = eState::Down;
			}

			MonsterTime = 0.f;
		}
	}

	void ForestMonster_1::Right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		pos.x += East * 50.f * Time::DeltaTime();
		tr->SetPosition(pos);

		MonsterTime += Time::DeltaTime();

		if (MonsterTime > 2.f)
		{
			srand(time(NULL));

			int StateSelect = rand() % 4;;

			if (StateSelect == 0)
			{
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mState = eState::Right;

			}
			else if (StateSelect == 1)
			{
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mState = eState::Left;

			}
			else if (StateSelect == 2)
			{
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mState = eState::Up;

			}
			else if (StateSelect == 3)
			{
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mState = eState::Down;
			}

			MonsterTime = 0.f;
		}
	}

	void ForestMonster_1::Dead()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			ForestMap1::SetMonsterQuantity();
			//ForestMap1::SetFunCheck(1);

		}
	}
}

