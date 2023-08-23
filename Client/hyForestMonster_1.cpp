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
	// static ������ �������� �ʱ�ȭ���ֱ�
	//float ForestMonster_1:: MonsterTime = 0.f;

	ForestMonster_1::ForestMonster_1()
		: mDeathTime(1.0f)
		, mState(eState::Right)
		, MonsterTime(0.f)
		, MoveSpeed(50.f)
		, mDirection(eDirection::Right)
		, Statetime(0.f)
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

		case hy::ForestMonster_1::eState::Move:
			Move();

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


	// �浹���� �� ó�� �ڵ� ���⿡ �ۼ�
	// ��ǳ���� �浹���� �� Dead
	void ForestMonster_1::OnCollisionEnter(Collider* other)
	{
		Animator* animator = GetComponent<Animator>();

		// �浹ü�� owner�� �����ͼ�
		GameObject* obj = other->GetOwner();
		// Tile�� ������ Tile�� �ּҸ� ��ȯ�ϰ� �ȵǸ� nullptr
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
			Vector2 monsterpos = this->GetComponent<Collider>()->GetPosition();
			Vector2 monstersize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((monstersize.x + tilesize.x) / 2.f) - fabs(monsterpos.x - tilepos.x);
			float ColSum_Y = ((monstersize.y + tilesize.y) / 2.f) - fabs(monsterpos.y - tilepos.y);

			// �¿�
			if (ColSum_X < ColSum_Y)
			{
				// ���� �浹
				if ((monsterpos.x < tilepos.x))
				{
					monsterpos.x -= ColSum_X;
					mState = eState::Move;
				}
				// ������ �浹
				else
				{
					monsterpos.x += ColSum_X;
					mState = eState::Move;
				}
			}
			// ����
			else
			{
				// ���� �浹
				if ((monsterpos.y < tilepos.y))
				{
					monsterpos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// �Ʒ��� �浹
				else
				{
					monsterpos.y += ColSum_Y;
					mState = eState::Move;
				}
			}

			monsterpos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(monsterpos);

			/*if (mDirection == eDirection::Right)
			{
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mState = eState::Left;
				mDirection = eDirection::Left;
			}
			else if (mDirection == eDirection::Left)
			{
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mState = eState::Right;
				mDirection = eDirection::Right;
			}
			else if (mDirection == eDirection::Down)
			{
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mState = eState::Up;
				mDirection = eDirection::Up;
			}
			else if (mDirection == eDirection::Up)
			{
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mState = eState::Down;
				mDirection = eDirection::Down;
			}*/

		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Uncrushable)
		{
			Vector2 monsterpos = this->GetComponent<Collider>()->GetPosition();
			Vector2 monstersize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((monstersize.x + tilesize.x) / 2.f) - fabs(monsterpos.x - tilepos.x);
			float ColSum_Y = ((monstersize.y + tilesize.y) / 2.f) - fabs(monsterpos.y - tilepos.y);

			// �¿�
			if (ColSum_X < ColSum_Y)
			{
				// ���� �浹
				if ((monsterpos.x < tilepos.x))
				{
					monsterpos.x -= ColSum_X;
					mState = eState::Move;
				}
				// ������ �浹
				else
				{
					monsterpos.x += ColSum_X;
					mState = eState::Move;
				}
			}
			// ����
			else
			{
				// ���� �浹
				if ((monsterpos.y < tilepos.y))
				{
					monsterpos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// �Ʒ��� �浹
				else
				{
					monsterpos.y += ColSum_Y;
					mState = eState::Move;
				}
			}

			monsterpos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(monsterpos);
		}

		//	// ���� �̵� ���� �ݴ��
		//	if (mDirection == eDirection::Right)
		//	{
		//		animator->PlayAnimation(L"ForestMonster_1Left", true);
		//		mState = eState::Left;
		//		mDirection = eDirection::Left;
		//	}
		//	else if (mDirection == eDirection::Left)
		//	{
		//		animator->PlayAnimation(L"ForestMonster_1Right", true);
		//		mState = eState::Right;
		//		mDirection = eDirection::Right;
		//	}
		//	else if (mDirection == eDirection::Down)
		//	{
		//		animator->PlayAnimation(L"ForestMonster_1Up", true);
		//		mState = eState::Up;
		//		mDirection = eDirection::Up;
		//	}
		//	else if (mDirection == eDirection::Up)
		//	{
		//		animator->PlayAnimation(L"ForestMonster_1Down", true);
		//		mState = eState::Down;
		//		mDirection = eDirection::Down;
		//	}
		//}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Bomb)
		{
			if (mDirection == eDirection::Right)
			{
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mDirection = eDirection::Left;
			}
			else if (mDirection == eDirection::Left)
			{
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mDirection = eDirection::Right;
			}
			else if (mDirection == eDirection::Down)
			{
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mDirection = eDirection::Up;
			}
			else if (mDirection == eDirection::Up)
			{
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mDirection = eDirection::Down;
			}

		}
	}

	void ForestMonster_1::OnCollisionStay(Collider* other)
	{

	}

	void ForestMonster_1::OnCollisionExit(Collider* other)
	{
	}

	void ForestMonster_1 ::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (MonsterTime > 1.f)
		{
			int StateSelect = rand() % 4;;

			mDirection = (eDirection)StateSelect;

			if (mDirection == eDirection::Up)			// ������ �����̸� �������� �̵�
			{
				animator->PlayAnimation(L"ForestMonster_1Up", true);
				mState = eState::Up;

			}
			else if (mDirection == eDirection::Down)	// ������ �Ʒ����̸� �Ʒ������� �̵�
			{
				animator->PlayAnimation(L"ForestMonster_1Down", true);
				mState = eState::Down;

			}
			else if (mDirection == eDirection::Left)	// ������ �����̸� �������� �̵�
			{
				animator->PlayAnimation(L"ForestMonster_1Left", true);
				mState = eState::Left;

			}
			else if (mDirection == eDirection::Right)	// ������ �������̸� ���������� �̵�
			{
				animator->PlayAnimation(L"ForestMonster_1Right", true);
				mState = eState::Right;
			}
			
			MonsterTime = 0.f;
			tr->SetPosition(pos);
		}
		
	}

	void ForestMonster_1::Up()
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

	void ForestMonster_1::Down()
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

	void ForestMonster_1::Left()
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

	void ForestMonster_1::Right()
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

