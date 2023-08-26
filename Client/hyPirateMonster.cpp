#include "hyPirateMonster.h"
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
	//float PirateMonster:: MonsterTime = 0.f;

	PirateMonster::PirateMonster()
		: mDeathTime(1.0f)
		, mState(eState::Right)
		, MonsterTime(0.f)
		, MoveSpeed(50.f)
		, mDirection(eDirection::Right)
		, Statetime(0.f)
	{
	}
	PirateMonster::~PirateMonster()
	{
	}
	void PirateMonster::Initialize()
	{
		Animator* mt = AddComponent<Animator>();
		mt->CreateAnimationFolder(L"PirateMonsterUp", L"..\\Resources\\Image\\Monster\\Pirate\\Up", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"PirateMonsterDown", L"..\\Resources\\Image\\Monster\\Pirate\\Down", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"PirateMonsterRight", L"..\\Resources\\Image\\Monster\\Pirate\\Right", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"PirateMonsterLeft", L"..\\Resources\\Image\\Monster\\Pirate\\Left", Vector2::Zero, 0.15f);
		mt->CreateAnimationFolder(L"PirateMonsterDie", L"..\\Resources\\Image\\Monster\\Pirate\\Die", Vector2::Zero, 0.2f);
		mt->PlayAnimation(L"PirateMonsterRight", true);



		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(30.0f, 30.0f));

		GameObject::Initialize();
	}
	void PirateMonster::Update()
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
		case hy::PirateMonster::eState::Up:
			Up();
			break;

		case hy::PirateMonster::eState::Down:
			Down();
			break;

		case hy::PirateMonster::eState::Left:
			Left();
			break;

		case hy::PirateMonster::eState::Right:
			Right();
			break;

		case hy::PirateMonster::eState::Move:
			Move();

		case hy::PirateMonster::eState::Dead:
			Dead();
			break;

		case hy::PirateMonster::eState::End:
			break;

		default:
			break;
		}
	}
	void PirateMonster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	// �浹���� �� ó�� �ڵ� ���⿡ �ۼ�
	// ��ǳ���� �浹���� �� Dead
	void PirateMonster::OnCollisionEnter(Collider* other)
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
			// ���� ���� ���̴� �ڵ�
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

		else if (other->GetOwner()->GetLayerType() == eLayerType::Bomb)
		{
			if (mDirection == eDirection::Right)
			{
				animator->PlayAnimation(L"PirateMonsterLeft", true);
				mDirection = eDirection::Left;
			}
			else if (mDirection == eDirection::Left)
			{
				animator->PlayAnimation(L"PirateMonsterRight", true);
				mDirection = eDirection::Right;
			}
			else if (mDirection == eDirection::Down)
			{
				animator->PlayAnimation(L"PirateMonsterUp", true);
				mDirection = eDirection::Up;
			}
			else if (mDirection == eDirection::Up)
			{
				animator->PlayAnimation(L"PirateMonsterDown", true);
				mDirection = eDirection::Down;
			}

		}
	}

	void PirateMonster::OnCollisionStay(Collider* other)
	{

	}

	void PirateMonster::OnCollisionExit(Collider* other)
	{
	}

	void PirateMonster::Move()
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
				animator->PlayAnimation(L"PirateMonsterUp", true);
				mState = eState::Up;

			}
			else if (mDirection == eDirection::Down)	// ������ �Ʒ����̸� �Ʒ������� �̵�
			{
				animator->PlayAnimation(L"PirateMonsterDown", true);
				mState = eState::Down;

			}
			else if (mDirection == eDirection::Left)	// ������ �����̸� �������� �̵�
			{
				animator->PlayAnimation(L"PirateMonsterLeft", true);
				mState = eState::Left;

			}
			else if (mDirection == eDirection::Right)	// ������ �������̸� ���������� �̵�
			{
				animator->PlayAnimation(L"PirateMonsterRight", true);
				mState = eState::Right;
			}

			MonsterTime = 0.f;
			tr->SetPosition(pos);
		}

	}

	void PirateMonster::Up()
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

	void PirateMonster::Down()
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

	void PirateMonster::Left()
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

	void PirateMonster::Right()
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

	void PirateMonster::Dead()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			SceneManager::KillMonsterQuantity();

		}
	}
}

