#include "hyDao.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
#include "hyForestMap1.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
//#include "hyRigidbody.h"
#include "hyDaoBomb.h"
#include "hyCollider.h"
#include "hyShield.h"
#include "hyShieldEffect.h"
#include "hySound.h"
#include "hyCollisionManager.h"
#include "hyWin_Lose.h"
#include "hyBalloon.h"
#include "hyPotion.h"
#include "hyVelocitySkate.h"
#include "hyNeedle.h"

namespace hy
{
	UINT Dao::BombFlowCount = 0;
	bool Dao::Trigger = false;
	Dao::eItem Dao::ActiveItem = Dao::eItem::None;
	bool Dao::UseItemNum = 0;
	UINT Dao::BombLimit = 1;
	float Dao::MoveSpeed = 150.f;


	Dao::Dao()
		: mState(eState::Idle)
		, mDirection(eDirection::Down)
	{
	}
	Dao::~Dao()
	{
	}
	void Dao::Initialize()
	{
		Resources::Load<Sound>(L"BombSet", L"..\\Resources\\Sound\\Sound\\bomb_set.wav");
		Resources::Load<Sound>(L"PlayerDie", L"..\\Resources\\Sound\\Sound\\player_die.wav");


		// 다오 충돌 구현
		Collider* col = AddComponent<Collider>();

		// 다오의 충돌 사각형 사이즈 수정
		col->SetSize(Vector2(30.0f, 25.0f));
		col->SetOffset(Vector2(0.0f, 10.0f));

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UseItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Boss, true);


		Animator* at = AddComponent<Animator>();

		//at->CreateAnimationFolder(L"StartDao", L"..\\Resources\\Image\\Dao\\UpIdleflow", Vector2(0.f, 0.f), 0.4f);
		at->CreateAnimationFolder(L"DaoIdle", L"..\\Resources\\Image\\Dao\\Idle", Vector2(0.f, 0.f), 0.4f);

		at->CreateAnimationFolder(L"DaoUp", L"..\\Resources\\Image\\Dao\\Up", Vector2(0.f, 0.f), 0.4f);
		at->CreateAnimationFolder(L"DaoUpStop", L"..\\Resources\\Image\\Dao\\UpIdle", Vector2(0.f, 0.f), 0.4f);

		at->CreateAnimationFolder(L"DaoDown", L"..\\Resources\\Image\\Dao\\Down", Vector2(0.f, 0.f), 0.4f);
		at->CreateAnimationFolder(L"DaoDownStop", L"..\\Resources\\Image\\Dao\\DownIdle", Vector2(0.f, 0.f), 0.4f);

		at->CreateAnimationFolder(L"DaoRight", L"..\\Resources\\Image\\Dao\\Right", Vector2(0.f, 0.f), 0.4f);
		at->CreateAnimationFolder(L"DaoRightStop", L"..\\Resources\\Image\\Dao\\RightIdle", Vector2(0.f, 0.f), 0.4f);

		at->CreateAnimationFolder(L"DaoLeft", L"..\\Resources\\Image\\Dao\\Left", Vector2(0.f, 0.f), 0.4f);
		at->CreateAnimationFolder(L"DaoLeftStop", L"..\\Resources\\Image\\Dao\\LeftIdle", Vector2(0.f, 0.f), 0.4f);

		// 상태 애니메이션
		// Dead 상태가 두가지
		// 물풍선에 일정 시간 갇히는 경우
		// 몬스터와 충돌하는 경우
		at->CreateAnimationFolder(L"DaoDead", L"..\\Resources\\Image\\Dao\\Dead", Vector2(0.f, 0.f), 0.15f);
		at->CreateAnimationFolder(L"DaoTrap", L"..\\Resources\\Image\\Dao\\Bubble", Vector2(0.f, 0.f), 0.4f);
		at->CreateAnimationFolder(L"DaoLive", L"..\\Resources\\Image\\Dao\\Live", Vector2(0.f, 0.f), 0.4f);
		at->CreateAnimationFolder(L"DaoVictory", L"..\\Resources\\Image\\Dao\\Victory", Vector2(0.f, 0.f), 0.4f);
		at->CreateAnimationFolder(L"DaoBalloonDead", L"..\\Resources\\Image\\Dao\\Die", Vector2(0.f, 0.f), 0.15f);

		at->PlayAnimation(L"DaoIdle", false);

		GameObject::Initialize();
	}

	// 상태 변화만 업데이트에서 
	void Dao::Update()
	{
		GameObject::Update();

		// tab + enter 하면 스위치 생성
		switch (mState)
		{
		case hy::Dao::eState::Idle:
			Idle();
			break;
		case hy::Dao::eState::Move:
			Move();
			break;
		case hy::Dao::eState::MoveStop:
			MoveStop();
			break;
		case hy::Dao::eState::Trap:
			Trap();
			break;
		case hy::Dao::eState::Live:
			Live();
			break;
		case hy::Dao::eState::Dead:
			Dead();
			break;
		case hy::Dao::eState::BalloonDead:
			BalloonDead();
			break;
		case hy::Dao::eState::Victory:
			Victory();
			break;

		case hy::Dao::eState::End:
			break;
		default:
			break;
		}

		if (Input::GetKeyDown(eKeyCode::Q))
		{
			// Balloon 아이템 setting
			Balloon* Balloon_ = object::Instantiate<Balloon>(eLayerType::Item, this->GetComponent<Transform>()->GetPosition() + Vector2(-45.0f, 0.0f));
			// Balloon 아이템 충돌 구현
			Collider* Ballooncol = Balloon_->AddComponent<Collider>();
			// Balloon 아이템 충돌 사각형 사이즈 수정
			Ballooncol->SetSize(Vector2(10.0f, 30.0f));

			// Potion 아이템 setting
			Potion* Potion_ = object::Instantiate<Potion>(eLayerType::Item, this->GetComponent<Transform>()->GetPosition() + Vector2(45.0f, 0.0f));

			// Potion 아이템 충돌 구현
			Collider* Potioncol = Potion_->AddComponent<Collider>();
			// Potion 아이템 충돌 사각형 사이즈 수정
			Potioncol->SetSize(Vector2(10.0f, 30.0f));
			Potioncol->SetOffset(Vector2(0.0f, 0.0f));

			// VelocitySkate 아이템 setting
			VelocitySkate* VelocitySkate_ = object::Instantiate<VelocitySkate>(eLayerType::Item, this->GetComponent<Transform>()->GetPosition() + Vector2(0.0f, 50.0f));

			// VelocitySkate 아이템 충돌 구현
			Collider* VelocitySkatecol = VelocitySkate_->AddComponent<Collider>();
			// VelocitySkate 아이템 충돌 사각형 사이즈 수정
			VelocitySkatecol->SetSize(Vector2(10.0f, 30.0f));
			VelocitySkatecol->SetOffset(Vector2(0.0f, 0.0f));

			// Needle 아이템 setting
			Needle* Needle_ = object::Instantiate<Needle>(eLayerType::UseItem, this->GetComponent<Transform>()->GetPosition() + Vector2(0.0f, -50.0f));

			// Needle 아이템 충돌 구현
			Collider* Needlecol = Needle_->AddComponent<Collider>();
			// Needle 아이템 충돌 사각형 사이즈 수정
			Needlecol->SetSize(Vector2(10.0f, 30.0f));
			Needlecol->SetOffset(Vector2(0.0f, 0.0f));

		}

		// 물풍선 객체 생성 및 위치 조정
		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			if (BombLimit != 0)
			{
				Resources::Find<Sound>(L"BombSet")->Play(false);

				DaoBomb* Bomb_ = object::Instantiate<DaoBomb>(eLayerType::Bomb);
				Transform* Daotr = this->GetComponent<Transform>();
				Vector2 DaoLocationtr = Daotr->GetPosition();
				Vector2 Bombpos;

				int X_ = 0;
				int Y_ = 0;

				// 해당 타일 인덱스를 구함
				X_ = (DaoLocationtr.x - 20.f) / (TILE_WIDTH);
				Y_ = (DaoLocationtr.y - 40.f) / (TILE_HEIGHT);

				// 해당 타일 인덱스에 타일 사이즈를 곱하여 해당 타일의 LeftTop으로 이동
				Bombpos.x = (X_ * TILE_WIDTH) + (TILE_WIDTH / 2) + 20.f;
				Bombpos.y = (Y_ * TILE_HEIGHT) + (TILE_HEIGHT / 2) + 40.f;

				Bomb_->GetComponent<Transform>()->SetPosition(Bombpos);
				BombLimit--;
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z) && ActiveItem == eItem::Shield && UseItemNum == 1)
		{
			Trigger = true;

			ShieldEffect* ShieldEffect_ = object::Instantiate<ShieldEffect>(eLayerType::Effect);
			Transform* Daotr = this->GetComponent<Transform>();
			Vector2 DaoLocation = Daotr->GetPosition();
			Vector2 Shieldpos = DaoLocation;
			//ShieldEffect_->Use();
			//ShieldEffect_->SetPlayer(this);
			ShieldEffect_->GetComponent<Transform>()->SetPosition(Shieldpos);

		}

		if (Trigger == true)
		{
			static float Shieldtime = 0.f;
			Shieldtime += Time::DeltaTime();

			if (Shieldtime < 3.0f)
			{

			}
			else
			{
				eItem::None;
				UseItemNum = 0;
				Shieldtime = 0.f;
				Trigger = false;
			}
		}

	}

	void Dao::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Dao::OnCollisionEnter(Collider* other)	// 충돌 처리
	{
		// 충돌체의 owner를 가져와서
		GameObject* obj = other->GetOwner();
		// Dao과 같으면 Dao의 주소를 반환하고 안되면 nullptr
		Tile* tile = dynamic_cast<Tile*>(obj);

		if (other->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Resources::Find<Sound>(L"PlayerDie")->Play(false);

			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(1.f, 1.f));
			at->PlayAnimation(L"DaoDead", false);
			mState = eState::Dead;
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(1.f, 1.f));
			at->PlayAnimation(L"DaoTrap", false);
			mState = eState::Trap;
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::BossBombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(1.f, 1.f));
			at->PlayAnimation(L"DaoTrap", false);
			mState = eState::Trap;
		}

		// East / West / South0 / North 가 0이면 이동
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Crack)
		{
			Vector2 dopos = this->GetComponent<Collider>()->GetPosition();
			Vector2 dosize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((dosize.x + tilesize.x) / 2.f) - fabs(dopos.x - tilepos.x);
			float ColSum_Y = ((dosize.y + tilesize.y) / 2.f) - fabs(dopos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((dopos.x < tilepos.x))
				{
					dopos.x -= ColSum_X;

					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					dopos.x += ColSum_X;

					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((dopos.y < tilepos.y))
				{
					dopos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					dopos.y += ColSum_Y;
					mState = eState::Move;
				}

			}

			dopos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(dopos);

		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Uncrushable)
		{
			Vector2 dopos = this->GetComponent<Collider>()->GetPosition();
			Vector2 dosize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((dosize.x + tilesize.x) / 2.f) - fabs(dopos.x - tilepos.x);
			float ColSum_Y = ((dosize.y + tilesize.y) / 2.f) - fabs(dopos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((dopos.x < tilepos.x))
				{
					dopos.x -= ColSum_X;

					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					dopos.x += ColSum_X;

					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((dopos.y < tilepos.y))
				{
					dopos.y -= ColSum_Y;

					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					dopos.y += ColSum_Y;

					mState = eState::Move;
				}

			}

			dopos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(dopos);

		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Boss)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.9f, 0.9f));
			at->PlayAnimation(L"DaoDead", false);
			mState = eState::Dead;
		}


	}
	void Dao::OnCollisionStay(Collider* other)
	{
		// 충돌체의 owner를 가져와서
		GameObject* obj = other->GetOwner();
		// Dao과 같으면 Dao의 주소를 반환하고 안되면 nullptr
		Tile* tile = dynamic_cast<Tile*>(obj);

		if (other->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.9f, 0.9f));
			at->PlayAnimation(L"DaoDead", false);
			mState = eState::Dead;
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(1.f, 1.f));
			at->PlayAnimation(L"DaoTrap", false);
			mState = eState::Trap;
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::BossBombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(1.f, 1.f));
			at->PlayAnimation(L"DaoTrap", false);
			mState = eState::Trap;
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Crack)
		{
			Vector2 dopos = this->GetComponent<Collider>()->GetPosition();
			Vector2 dosize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((dosize.x + tilesize.x) / 2.f) - fabs(dopos.x - tilepos.x);
			float ColSum_Y = ((dosize.y + tilesize.y) / 2.f) - fabs(dopos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((dopos.x < tilepos.x))
				{
					dopos.x -= ColSum_X;
					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					dopos.x += ColSum_X;
					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((dopos.y < tilepos.y))
				{
					dopos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					dopos.y += ColSum_Y;
					mState = eState::Move;
				}
			}

			dopos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(dopos);
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Uncrushable)
		{
			Vector2 dopos = this->GetComponent<Collider>()->GetPosition();
			Vector2 dosize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((dosize.x + tilesize.x) / 2.f) - fabs(dopos.x - tilepos.x);
			float ColSum_Y = ((dosize.y + tilesize.y) / 2.f) - fabs(dopos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((dopos.x < tilepos.x))
				{
					dopos.x -= ColSum_X;
					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					dopos.x += ColSum_X;
					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((dopos.y < tilepos.y))
				{
					dopos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					dopos.y += ColSum_Y;
					mState = eState::Move;
				}
			}

			dopos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(dopos);
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Boss)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.9f, 0.9f));
			at->PlayAnimation(L"DaoDead", false);
			mState = eState::Dead;
		}

	}
	void Dao::OnCollisionExit(Collider* other)
	{

	}

	void Dao::Idle()
	{
		Animator* animator = GetComponent<Animator>();
		animator->SetScale(Vector2(1.f, 1.f));

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))		// 왼쪽 키를 누르면 왼쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"DaoLeft", true);
			mState = eState::Move;
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))		// 오른쪽 키를 누르면 오른쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"DaoRight", true);
			mState = eState::Move;
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W))		// 위쪽 키를 누르면 위쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"DaoUp", true);
			mState = eState::Move;
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))		// 아레쪽 키를 누르면 아레쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"DaoDown", true);
			mState = eState::Move;
			mDirection = eDirection::Down;
		}

	}

	void Dao::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (mDirection == eDirection::Up)			// 방향이 위쪽이면 위쪽으로 이동
		{
			if (pos.y <= 40)
			{
				pos.y = 40;
			}
			else
			{
				pos.y -= MoveSpeed * Time::DeltaTime();
			}
		}
		else if (mDirection == eDirection::Left)	// 방향이 왼쪽이면 왼쪽으로 이동
		{
			if (pos.x <= 30)
			{
				pos.x = 30;
			}
			else
			{
				pos.x -= MoveSpeed * Time::DeltaTime();
			}
		}
		else if (mDirection == eDirection::Right)	// 방향이 오른쪽이면 오른쪽으로 이동
		{
			if (pos.x >= 610)
			{
				pos.x = 610;
			}
			else
			{
				pos.x += MoveSpeed * Time::DeltaTime();
			}
		}
		else if (mDirection == eDirection::Down)	// 방향이 아래쪽이면 아래쪽으로 이동
		{
			if (pos.y >= 530)
			{
				pos.y = 530;
			}
			else
			{
				pos.y += MoveSpeed * Time::DeltaTime();
			}
		}

		tr->SetPosition(pos);

		if (Input::GetKeyDown(eKeyCode::A))		// 어떤 키를 누르고 이따가 왼쪽 키를 눌렀을 때(방향 전환)
		{
			animator->PlayAnimation(L"DaoLeft", true);
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			animator->PlayAnimation(L"DaoRight", true);
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			animator->PlayAnimation(L"DaoUp", true);
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			animator->PlayAnimation(L"DaoDown", true);
			mDirection = eDirection::Down;
		}


		if (!Input::GetKey(eKeyCode::W) && !Input::GetKey(eKeyCode::S)			// 아무 키도 안눌린 상태일 때
			&& !Input::GetKey(eKeyCode::A) && !Input::GetKey(eKeyCode::D))
		{
			if (mDirection == eDirection::Up)
			{
				animator->PlayAnimation(L"DaoUpStop", true);
			}
			if (mDirection == eDirection::Down)
			{
				animator->PlayAnimation(L"DaoDownStop", true);
			}
			if (mDirection == eDirection::Left)
			{
				animator->PlayAnimation(L"DaoLeftStop", true);
			}
			if (mDirection == eDirection::Right)
			{
				animator->PlayAnimation(L"DaoRightStop", true);
			}
			mState = eState::MoveStop;
		}

	}

	void Dao::MoveStop()
	{
		static float time = 0.f;
		time += Time::DeltaTime();
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))		// 왼쪽 키를 누르면 왼쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"DaoLeft", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))	// 오른쪽 키를 누르면 오른쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"DaoRight", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::W) || Input::GetKey(eKeyCode::W))			// 위쪽 키를 누르면 위쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"DaoUp", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))		// 아레쪽 키를 누르면 아레쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"DaoDown", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Down;
		}

		if (time > 3.f)
		{
			animator->PlayAnimation(L"DaoIdle", true);
			mState = eState::Idle;
			time = 0.f;

		}
	}

	void Dao::Trap()
	{
		static float Traptime = 0.f;
		Traptime += Time::DeltaTime();

		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyDown(eKeyCode::Z) && ActiveItem == eItem::Needle)	// Live
		{
			animator->SetScale(Vector2(0.8f, 0.8f));
			animator->PlayAnimation(L"DaoLive", false);
			mState = eState::Live;
			eItem::None;
		}
		else if (Traptime > 4.f)
		{
			if (SceneManager::GetMonsterQuantity != 0)
			{
				Resources::Find<Sound>(L"PlayerDie")->Play(false);

				animator->SetScale(Vector2(1.2f, 1.2f));
				animator->PlayAnimation(L"DaoBalloonDead", false);
				mState = eState::BalloonDead;
				Traptime = 0.f;
			}

		}
	}

	void Dao::Live()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"DaoIdle", true);
			ActiveItem = eItem::None;
			UseItemNum = 0;
			mState = eState::Idle;
		}
	}

	void Dao::Dead()
	{
		Animator* animator = GetComponent<Animator>();
		animator->SetScale(Vector2(1.f, 1.f));

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			//SceneManager::SetPlayerDead(true);
			SceneManager::SubPlayerNum();

		}
	}

	void Dao::BalloonDead()
	{
		Animator* animator = GetComponent<Animator>();
		animator->SetScale(Vector2(1.f, 1.f));

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			//SceneManager::SetPlayerDead(true);
			SceneManager::SubPlayerNum();
		}
	}

	void Dao::Victory()
	{
		Animator* animator = GetComponent<Animator>();
		animator->SetScale(Vector2(0.8f, 0.8f));
		animator->PlayAnimation(L"DaoVictory", true);

		/*if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"DaoIdle", true);
			mState = eState::Idle;
		}*/
	}
	void Dao::ResetDao()
	{
		BombFlowCount = 0;
		Trigger = false;
		ActiveItem = eItem::None;
		UseItemNum = 0;
		BombLimit = 1;
		SetMoveSpeed(150.f);
	}
}

