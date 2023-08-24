#include "hyForestMonster.h"
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
	//float ForestMonster:: MonsterTime = 0.f;

	ForestMonster::ForestMonster()
		: mDeathTime(1.0f)
		, mState(eState::Right)
		, MonsterTime(0.f)
		, MoveSpeed(50.f)
		, mDirection(eDirection::Right)
		, Statetime(0.f)
	{
	}
	ForestMonster::~ForestMonster()
	{
	}
	void ForestMonster::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"ForestMonsterUp", L"..\\Resources\\Image\\Monster\\Forest\\Up", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonsterDown", L"..\\Resources\\Image\\Monster\\Forest\\Down",Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonsterRight", L"..\\Resources\\Image\\Monster\\Forest\\Right", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonsterLeft", L"..\\Resources\\Image\\Monster\\Forest\\Left", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"ForestMonsterDie", L"..\\Resources\\Image\\Monster\\Forest\\Die", Vector2::Zero, 0.2f);
		mt->PlayAnimation(L"ForestMonsterRight", true);

		

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(30.0f, 30.0f));

		GameObject::Initialize();
	}
	void ForestMonster::Update()
	{
		GameObject::Update();

		MonsterTime += Time::DeltaTime();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (pos.x >= 580)
		{
			pos.x = 580;
		}
		else if (pos.x <= 40)
		{
			pos.x = 40;
		}
		else if (pos.y <= 50)
		{
			pos.y = 50;
		}
		else if (pos.y >= 520)
		{
			pos.y = 520;
		}

		tr->SetPosition(pos);


		switch (mState)
		{
		case hy::ForestMonster::eState::Up:
			Up();
			break;

		case hy::ForestMonster::eState::Down:
			Down();
			break;

		case hy::ForestMonster::eState::Left:
			Left();
			break;

		case hy::ForestMonster::eState::Right:
			Right();
			break;

		case hy::ForestMonster::eState::Move:
			Move();

		case hy::ForestMonster::eState::Dead:
			Dead();
			break;

		case hy::ForestMonster::eState::End:
			break;

		default:
			break;
		}
	}
	void ForestMonster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	// 충돌했을 때 처리 코드 여기에 작성
	// 물풍선과 충돌했을 때 Dead
	void ForestMonster::OnCollisionEnter(Collider* other)
	{
		Animator* animator = GetComponent<Animator>();

		// 충돌체의 owner를 가져와서
		GameObject* obj = other->GetOwner();
		// Tile과 같으면 Tile의 주소를 반환하고 안되면 nullptr
		Tile* tile = dynamic_cast<Tile*>(obj);

		if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"ForestMonsterDie", false);
			// 몬스터 개수 줄이는 코드
			mState = eState::Dead;
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Crack)
		{
			Vector2 monsterpos = this->GetComponent<Collider>()->GetPosition();
			Vector2 monstersize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((monstersize.x + tilesize.x) / 2.f) - fabs(monsterpos.x - tilepos.x);
			float ColSum_Y = ((monstersize.y + tilesize.y) / 2.f) - fabs(monsterpos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((monsterpos.x < tilepos.x))
				{
					monsterpos.x -= ColSum_X;
					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					monsterpos.x += ColSum_X;
					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((monsterpos.y < tilepos.y))
				{
					monsterpos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					monsterpos.y += ColSum_Y;
					mState = eState::Move;
				}
			}

			monsterpos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(monsterpos);

		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Uncrushable)
		{
			Vector2 monsterpos = this->GetComponent<Collider>()->GetPosition();
			Vector2 monstersize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((monstersize.x + tilesize.x) / 2.f) - fabs(monsterpos.x - tilepos.x);
			float ColSum_Y = ((monstersize.y + tilesize.y) / 2.f) - fabs(monsterpos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((monsterpos.x < tilepos.x))
				{
					monsterpos.x -= ColSum_X;
					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					monsterpos.x += ColSum_X;
					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((monsterpos.y < tilepos.y))
				{
					monsterpos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					monsterpos.y += ColSum_Y;
					mState = eState::Move;
				}
			}

			monsterpos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(monsterpos);
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::Bomb)
		{
			if (mDirection == eDirection::Right)
			{
				animator->PlayAnimation(L"ForestMonsterLeft", true);
				mDirection = eDirection::Left;
			}
			else if (mDirection == eDirection::Left)
			{
				animator->PlayAnimation(L"ForestMonsterRight", true);
				mDirection = eDirection::Right;
			}
			else if (mDirection == eDirection::Down)
			{
				animator->PlayAnimation(L"ForestMonsterUp", true);
				mDirection = eDirection::Up;
			}
			else if (mDirection == eDirection::Up)
			{
				animator->PlayAnimation(L"ForestMonsterDown", true);
				mDirection = eDirection::Down;
			}

		}
	}

	void ForestMonster::OnCollisionStay(Collider* other)
	{

	}

	void ForestMonster::OnCollisionExit(Collider* other)
	{
	}

	void ForestMonster ::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (MonsterTime > 1.f)
		{
			int StateSelect = rand() % 4;;

			mDirection = (eDirection)StateSelect;

			if (mDirection == eDirection::Up)			// 방향이 위쪽이면 위쪽으로 이동
			{
				animator->PlayAnimation(L"ForestMonsterUp", true);
				mState = eState::Up;

			}
			else if (mDirection == eDirection::Down)	// 방향이 아래쪽이면 아래쪽으로 이동
			{
				animator->PlayAnimation(L"ForestMonsterDown", true);
				mState = eState::Down;

			}
			else if (mDirection == eDirection::Left)	// 방향이 왼쪽이면 왼쪽으로 이동
			{
				animator->PlayAnimation(L"ForestMonsterLeft", true);
				mState = eState::Left;

			}
			else if (mDirection == eDirection::Right)	// 방향이 오른쪽이면 오른쪽으로 이동
			{
				animator->PlayAnimation(L"ForestMonsterRight", true);
				mState = eState::Right;
			}
			
			MonsterTime = 0.f;
			tr->SetPosition(pos);
		}
		
	}

	void ForestMonster::Up()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.y -= 50.f * Time::DeltaTime();

		if (pos.y <= 40)
		{
			pos.y = 40;
		}

		tr->SetPosition(pos);

		Statetime += Time::DeltaTime();

		if (Statetime > 2.f)
		{
			Statetime = 0.f;
			mState = eState::Move;

		}

	}

	void ForestMonster::Down()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.y += 50.f * Time::DeltaTime();

		if (pos.y >= 530)
		{
			pos.y = 530;
		}

		tr->SetPosition(pos);

		Statetime += Time::DeltaTime();

		if (Statetime > 2.f)
		{
			Statetime = 0.f;

			mState = eState::Move;
		}
	}

	void ForestMonster::Left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x -= 50.f * Time::DeltaTime();

		if (pos.x <= 30)
		{
			pos.x = 30;
		}

		tr->SetPosition(pos);

		Statetime += Time::DeltaTime();


		if (Statetime > 2.f)
		{
			Statetime = 0.f;

			mState = eState::Move;
		}
	}

	void ForestMonster::Right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x += 50.f * Time::DeltaTime();

		if (pos.x >= 610)
		{
			pos.x = 610;
		}

		tr->SetPosition(pos);

		Statetime += Time::DeltaTime();

		if (Statetime > 2.f)
		{
			Statetime = 0.f;

			mState = eState::Move;
		}
	}

	void ForestMonster::Dead()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			// 몬스터 개수 줄이는 코드
			//ForestMap1::SetFunCheck(1);

		}
	}
}

