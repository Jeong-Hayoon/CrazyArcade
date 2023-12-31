#include "hyBazzi.h"
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
#include "hyBomb.h"
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
	UINT Bazzi ::BombFlowCount = 0;
	bool Bazzi::Trigger = false;
	Bazzi :: eItem Bazzi:: ActiveItem = Bazzi::eItem ::None;
	bool Bazzi::UseItemNum = 0;
	UINT Bazzi::BombLimit = 1;
	float Bazzi :: MoveSpeed = 150.f;


	Bazzi::Bazzi()
		: mState(eState::Make)
		, mDirection(eDirection::Down)
		, ShieldUse(false)
	{
	}
	Bazzi::~Bazzi()
	{
	}
	void Bazzi::Initialize()
	{
		Resources::Load<Sound>(L"BombSet", L"..\\Resources\\Sound\\Sound\\bomb_set.wav");
		Resources::Load<Sound>(L"PlayerDie", L"..\\Resources\\Sound\\Sound\\player_die.wav");


		// 배찌 충돌 구현
		Collider* col = AddComponent<Collider>();

		// 배찌의 충돌 사각형 사이즈 수정
		col->SetSize(Vector2(30.0f, 25.0f));
		col->SetOffset(Vector2(0.0f, 10.0f));

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UseItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Boss, true);


		Animator* at = AddComponent<Animator>();

		Texture* Bazzi_ = Resources::Load<Texture>(L"Bazzi"
			, L"..\\Resources\\Image\\Bazzi\\Bazzi.bmp");

		Texture* BazziDead_ = Resources::Load<Texture>(L"BazziDead"
			, L"..\\Resources\\Image\\Bazzi\\BazziDead.bmp");

		Texture* BazziBalloonDead_ = Resources::Load<Texture>(L"BazziBalloonDead"
			, L"..\\Resources\\Image\\Bazzi\\BazziDie.bmp");

		Texture* StartBazzi_ = Resources::Load<Texture>(L"StartBazzi"
			, L"..\\Resources\\Image\\Bazzi\\ready.bmp");

		Texture* BazziTrap_ = Resources::Load<Texture>(L"BazziTrap"
			, L"..\\Resources\\Image\\Bazzi\\trap.bmp");

		Texture* BazziLive_ = Resources::Load<Texture>(L"BazziLive"
			, L"..\\Resources\\Image\\Bazzi\\live.bmp");

		Texture* BazziVictory_ = Resources::Load<Texture>(L"BazziVictory"
			, L"..\\Resources\\Image\\Bazzi\\jump.bmp");

		Texture* BazziShield_ = Resources::Load<Texture>(L"Bazzi_Shield"
			, L"..\\Resources\\Image\\Items\\shieldeffect.bmp");
		

		at->CreateAnimation(L"StartBazzi", StartBazzi_, Vector2(0.0f, 0.0f), Vector2(64.0f, 86.0f), 18, Vector2(0.0f, 0.0f), 0.07f);
		at->CreateAnimation(L"BazziIdle", Bazzi_, Vector2(0.0f, 0.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.6f);

		at->CreateAnimation(L"BazziUp", Bazzi_, Vector2(0.0f, 60.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziUpStop", Bazzi_, Vector2(50.0f, 60.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziDown", Bazzi_, Vector2(0.0f, 120.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziDownStop", Bazzi_, Vector2(50.0f, 120.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziRight", Bazzi_, Vector2(0.0f, 240.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziRightStop", Bazzi_, Vector2(50.0f, 240.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziLeft", Bazzi_, Vector2(0.0f, 180.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziLeftStop", Bazzi_, Vector2(50.0f, 180.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		// 상태 애니메이션
		// Dead 상태가 두가지
		// 물풍선에 일정 시간 갇히는 경우
		// 몬스터와 충돌하는 경우
		at->CreateAnimation(L"BazziDead", BazziDead_, Vector2(0.0f, 0.0f), Vector2(81.0f, 144.0f), 6, Vector2(0.0f, -15.0f), 0.2f);
		at->CreateAnimation(L"BazziTrap", BazziTrap_, Vector2(0.0f, 0.0f), Vector2(88.0f, 144.0f), 13, Vector2(0.0f, 0.0f), 0.18f);
		at->CreateAnimation(L"BazziLive", BazziLive_, Vector2(0.0f, 0.0f), Vector2(88.0f, 144.0f), 5, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziVictory", BazziVictory_, Vector2(0.0f, 0.0f), Vector2(64.0f, 80.0f), 8, Vector2(0.0f, 0.0f), 0.25f);
		at->CreateAnimation(L"BazziBalloonDead", BazziBalloonDead_, Vector2(0.0f, 0.0f), Vector2(91.0f, 144.0f), 10, Vector2(0.0f, 0.0f), 0.15f);

		at->PlayAnimation(L"StartBazzi", false);

		GameObject::Initialize();
	}

	// 상태 변화만 업데이트에서 
	void Bazzi::Update()	
	{   
		GameObject::Update();

		//pixel 충돌(게임 완성을 하고 나면 레이어를 배경 뒤로 배치해서 게임 실행 시 안 보이게 배치)
		/*Transform* tr = GetComponent<Transform>();
		COLORREF rgb = mFloorTexture->GetTexturePixel(tr->GetPosition().x, tr->GetPosition().y + 48);

		Rigidbody* rb = GetComponent<Rigidbody>();

		if (rgb == RGB(0, 0, 255))
		{
			Transform* tr = GetComponent<Transform>();

			Vector2 pos = tr->GetPosition();
			pos.y -= 1;
			tr->SetPosition(pos);

			rb->SetGround(true);
		}
		else
		{
			rb->SetGround(false);
		}*/

		// tab + enter 하면 스위치 생성
		switch (mState)
		{
		case hy::Bazzi::eState::Make:
			Make();
			break;
		case hy::Bazzi::eState::Idle:
			Idle();
			break;
		case hy::Bazzi::eState::Move:
			Move();
			break;
		case hy::Bazzi::eState::MoveStop:
			MoveStop();
			break;
		case hy::Bazzi::eState::Trap:
			Trap();
			break;
		case hy::Bazzi::eState::Live:
			Live();
			break;
		case hy::Bazzi::eState::Dead:
			Dead();
			break;
		case hy::Bazzi::eState::BalloonDead:
			BalloonDead();
			break;
		case hy::Bazzi::eState::Victory:
			Victory();
			break;

		case hy::Bazzi::eState::End:
			break;
		default:
			break;
		}


		if (Input::GetKeyDown(eKeyCode::C))
		{
			SceneManager::SetColliderControl(true);
		}
		else if (Input::GetKeyDown(eKeyCode::V))
		{
			SceneManager::SetColliderControl(false);
		}


		// 치트키
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
		if (Input::GetKeyDown(eKeyCode::Space))	
		{
			if(BombLimit != 0 /*&& Tile::GetHaveBomb() == 0*/)
			{
				Resources::Find<Sound>(L"BombSet")->Play(false);

				Bomb* Bomb_ = object::Instantiate<Bomb>(eLayerType::Bomb);
				Transform* Bazzitr = this->GetComponent<Transform>();
				Vector2 BazziLocationtr = Bazzitr->GetPosition();
				Vector2 Bombpos;

				int X_ = 0;
				int Y_ = 0;

				// 해당 타일 인덱스를 구함
				X_ = (BazziLocationtr.x - 20.f) / (TILE_WIDTH);
				Y_ = (BazziLocationtr.y - 40.f) / (TILE_HEIGHT);

				// 해당 타일 인덱스에 타일 사이즈를 곱하여 해당 타일의 LeftTop으로 이동
				Bombpos.x = (X_ *  TILE_WIDTH) + (TILE_WIDTH / 2) + 20.f;
				Bombpos.y = (Y_ * TILE_HEIGHT) + (TILE_HEIGHT / 2) + 40.f; 

				/*Tile::SetHaveBomb(1);*/

 				Bomb_->GetComponent<Transform>()->SetPosition(Bombpos);
				BombLimit--;
			}
		}

		if (Input::GetKeyDown(eKeyCode::Ctrl) && ActiveItem == eItem::Shield && UseItemNum == 1)
		{
			Trigger = true;
			ShieldUse = true;
			SceneManager::SetShieldGet(false);
			SceneManager::SetItemUse(true);

			ShieldEffect* ShieldEffect_ = object::Instantiate<ShieldEffect>(eLayerType::Effect);
		}

		if (Trigger == true)
		{
			static float Shieldtime = 0.f;
			Shieldtime += Time::DeltaTime();

			CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, false);
			CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Boss, false);
			CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BossBombflow, false);
			CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Bombflow, false);

			if (Shieldtime >= 2.0f)
			{
				ShieldUse = false;
				ActiveItem = eItem::None;
				UseItemNum = 0;
				Shieldtime = 0.f;
				Trigger = false;
				CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
				CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Boss, true);
				CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::BossBombflow, true);
				CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Bombflow, true);
			}
			
		}

	}

	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bazzi::OnCollisionEnter(Collider* other)	// 충돌 처리
	{
		// 충돌체의 owner를 가져와서
		GameObject* obj = other->GetOwner();
		// Bazzi과 같으면 Bazzi의 주소를 반환하고 안되면 nullptr
		Tile* tile = dynamic_cast<Tile*>(obj);

		if (other->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Resources::Find<Sound>(L"PlayerDie")->Play(false);

			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.9f, 0.9f));
			at->PlayAnimation(L"BazziDead", false);
			mState = eState::Dead;
		}

		// Trap 상태일 때 다른 플레이어와 부딪히면 살아나게
		else if (other->GetOwner()->GetLayerType() == eLayerType::Player && this->mState == eState::Trap)
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"BazziLive", false);
			mState = eState::Live;
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.8f, 0.8f));
			at->PlayAnimation(L"BazziTrap", false);
			mState = eState::Trap;
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::BossBombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.8f, 0.8f));
			at->PlayAnimation(L"BazziTrap", false);
			mState = eState::Trap;
		}

		// East / West / South0 / North 가 0이면 이동
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Crack)
		{
			Vector2 bzpos = this->GetComponent<Collider>()->GetPosition();
			Vector2 bzsize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((bzsize.x + tilesize.x) / 2.f) - fabs(bzpos.x - tilepos.x);
			float ColSum_Y = ((bzsize.y + tilesize.y) / 2.f) - fabs(bzpos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((bzpos.x < tilepos.x))
				{
					bzpos.x -= ColSum_X;

					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					bzpos.x += ColSum_X;

					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((bzpos.y < tilepos.y))
				{
					bzpos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					bzpos.y += ColSum_Y;
					mState = eState::Move;
				}

			}

			bzpos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(bzpos);

			//float GetSpeed = GetMoveSpeed();
			// 이동은 없고, 애니메이션만
			// 오른쪽으로 이동했을때 
			// 이동을 할때 방향이 곱해져서 이동을 함
			/*if (mDirection == eDirection::Right)
			{
				East++;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Left)
			{
				West++;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Down)
			{
				South++;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Up)
			{
				North++;
				mState = eState::Move;
			}*/
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Uncrushable)
		{
			Vector2 bzpos = this->GetComponent<Collider>()->GetPosition();
			Vector2 bzsize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((bzsize.x + tilesize.x) / 2.f) - fabs(bzpos.x - tilepos.x);
			float ColSum_Y = ((bzsize.y + tilesize.y) / 2.f) - fabs(bzpos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((bzpos.x < tilepos.x))
				{
					bzpos.x -= ColSum_X;

					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					bzpos.x += ColSum_X;

					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((bzpos.y < tilepos.y))
				{
					bzpos.y -= ColSum_Y;

					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					bzpos.y += ColSum_Y;

					mState = eState::Move;
				}

			}

			bzpos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(bzpos);

			/*if (mDirection == eDirection::Right)
			{
				East++;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Left)
			{
				West++;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Down)
			{
				South++;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Up)
			{
				North++;
				mState = eState::Move;
			}*/
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Boss)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.9f, 0.9f));
			at->PlayAnimation(L"BazziDead", false);
			mState = eState::Dead;
		}

		
	}
	void Bazzi::OnCollisionStay(Collider* other)
	{
		// 충돌체의 owner를 가져와서
		GameObject* obj = other->GetOwner();
		// Bazzi과 같으면 Bazzi의 주소를 반환하고 안되면 nullptr
		Tile* tile = dynamic_cast<Tile*>(obj);

		if (other->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.9f, 0.9f));
			at->PlayAnimation(L"BazziDead", false);
			mState = eState::Dead;
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.8f, 0.8f));
			at->PlayAnimation(L"BazziTrap", false);
			mState = eState::Trap;
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::BossBombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.8f, 0.8f));
			at->PlayAnimation(L"BazziTrap", false);
			mState = eState::Trap;
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Crack)
		{
			Vector2 bzpos = this->GetComponent<Collider>()->GetPosition();
			Vector2 bzsize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((bzsize.x + tilesize.x) / 2.f) - fabs(bzpos.x - tilepos.x);
			float ColSum_Y = ((bzsize.y + tilesize.y) / 2.f) - fabs(bzpos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((bzpos.x < tilepos.x))
				{
					bzpos.x -= ColSum_X;
					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					bzpos.x += ColSum_X;
					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((bzpos.y < tilepos.y))
				{
					bzpos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					bzpos.y += ColSum_Y;
					mState = eState::Move;
				}
			}

			bzpos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(bzpos);
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Uncrushable)
		{
			Vector2 bzpos = this->GetComponent<Collider>()->GetPosition();
			Vector2 bzsize = this->GetComponent<Collider>()->GetSize();

			Vector2 tilepos = other->GetPosition();
			Vector2 tilesize = other->GetSize();

			float ColSum_X = ((bzsize.x + tilesize.x) / 2.f) - fabs(bzpos.x - tilepos.x);
			float ColSum_Y = ((bzsize.y + tilesize.y) / 2.f) - fabs(bzpos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((bzpos.x < tilepos.x))
				{
					bzpos.x -= ColSum_X;
					mState = eState::Move;
				}
				// 오른쪽 충돌
				else
				{
					bzpos.x += ColSum_X;
					mState = eState::Move;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if ((bzpos.y < tilepos.y))
				{
					bzpos.y -= ColSum_Y;
					mState = eState::Move;
				}
				// 아래쪽 충돌
				else
				{
					bzpos.y += ColSum_Y;
					mState = eState::Move;
				}
			}

			bzpos -= GetComponent<Collider>()->GetOffset();
			this->GetComponent<Transform>()->SetPosition(bzpos);
		}
		else if (other->GetOwner()->GetLayerType() == eLayerType::Boss)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.9f, 0.9f));
			at->PlayAnimation(L"BazziDead", false);
			mState = eState::Dead;
		}
		
	}
	void Bazzi::OnCollisionExit(Collider* other)
	{
	
	}
 
	void Bazzi::Make()
	{
		Animator* animator = GetComponent<Animator>();
		animator->SetScale(Vector2(0.8f, 0.8f));

		if(animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
		}
	}

	void Bazzi::Idle()
	{
		Animator* animator = GetComponent<Animator>();	
		animator->SetScale(Vector2(1.f, 1.f));

		if (Input::GetKeyDown(eKeyCode::Left) || Input::GetKey(eKeyCode::Left))		// 왼쪽 키를 누르면 왼쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziLeft", true);
			mState = eState::Move;
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::Right) || Input::GetKey(eKeyCode::Right))		// 오른쪽 키를 누르면 오른쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziRight", true);
			mState = eState::Move;
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::Up) || Input::GetKey(eKeyCode::Up))		// 위쪽 키를 누르면 위쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziUp", true);
			mState = eState::Move;
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::Down) || Input::GetKey(eKeyCode::Down))		// 아레쪽 키를 누르면 아레쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziDown", true);
			mState = eState::Move;
			mDirection = eDirection::Down;
		}

		if (Input::GetKeyDown(eKeyCode::Ctrl) && ActiveItem == eItem::Needle && UseItemNum == 1)	// Live
		{
			animator->SetScale(Vector2(0.8f, 0.8f));
			SceneManager::SetNeedleGet(false);
			animator->PlayAnimation(L"BazziLive", false);
			mState = eState::Live;
		}
		

		// 위치 업데이트가 안됨(배찌를 따라서 갈수있도록 수정)
		//if (Input::GetKeyDown(eKeyCode::Ctrl) && ActiveItem == eItem ::Shield)
		//{
		//	static float Shieldtime = 0.f;
		//	Shieldtime += Time::DeltaTime();
		//	
		//	if (Shieldtime < 3.0f)
		//	{
		//		ShieldEffect* ShieldEffect_ = object::Instantiate<ShieldEffect>(eLayerType::Effect);
		//		Transform* Bazzitr = this->GetComponent<Transform>();
		//		Vector2  Shieldpos = Bazzitr->GetPosition();
		//		
		//		ShieldEffect_->Use();
		//		ShieldEffect_->GetComponent<Transform>()->SetPosition(Shieldpos);
		//	}

		//	/*else if(Shieldtime > 3.0f)
		//	{
		//		animator->SetScale(Vector2(1.0f, 1.0f));
		//		animator->PlayAnimation(L"BazziIdle", true);
		//		mState = eState::Idle;
		//	}*/
		//}

		//if (Input::GetKeyDown(eKeyCode::K))		// 아레쪽 키를 누르면 아레쪽 애니메이션 실행
		//{
		//	animator->PlayAnimation(L"BazziDie", false);
		//	mState = eState::Move;
		//	mDirection = eDirection::Down;
		//}
		
		/*if (Input::GetKey(eKeyCode::MouseLeft))
		{
			animator->PlayAnimation(L"PlayerDropWater", false);
			mState = eState::DropWater;
		}*/

		// 중력
	/*	if (Input::GetKeyDown(eKeyCode::W))
		{
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
		}*/
	
		// space를 누르면 객체가 생성되는 코드 -> 물풍선 교체
		/*if (Input::GetKeyDown(eKeyCode::Space))
		{
			Transform* tr = GetComponent<Transform>();

			Texture* image = Resources::Load<Texture>(L"Chiken"
				, L"..\\Resources\\Image\\Animals\\Chiken.bmp");

			Monster* monster = object::Instantiate<Monster>(eLayerType::Monster, tr->GetPosition());
			Animator* at = monster->AddComponent<Animator>();
			at->CreateAnimation(L"ChickenIdle", image, Vector2(0.0f, 0.0f), Vector2(16.0f, 16.0f), 4);
			at->SetScale(Vector2(3.0f, 3.0f));
			at->PlayAnimation(L"ChickenIdle", true);
			Collider* col = monster->AddComponent<Collider>();
			col->SetSize(Vector2(100.0f, 100.0f));

			object::Instantiate<Monster>(eLayerType::Monster, tr->GetPosition());
		}*/

	}

	void Bazzi::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

 		if (mDirection == eDirection::Up)			// 방향이 위쪽이면 위쪽으로 이동
		{
			if(pos.y <= 40)
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

		if (Input::GetKeyDown(eKeyCode::Left))		// 어떤 키를 누르고 이따가 왼쪽 키를 눌렀을 때(방향 전환)
		{
			animator->PlayAnimation(L"BazziLeft", true);
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			animator->PlayAnimation(L"BazziRight", true);
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			animator->PlayAnimation(L"BazziUp", true);
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			animator->PlayAnimation(L"BazziDown", true);
			mDirection = eDirection::Down;
		}


		if (!Input::GetKey(eKeyCode::Up) && !Input::GetKey(eKeyCode::Down)			// 아무 키도 안눌린 상태일 때
			&& !Input::GetKey(eKeyCode::Left) && !Input::GetKey(eKeyCode::Right))
		{
			if (mDirection == eDirection::Up)
			{
				animator->PlayAnimation(L"BazziUpStop", true);
			}
			if (mDirection == eDirection::Down)
			{
				animator->PlayAnimation(L"BazziDownStop", true);
			}
			if (mDirection == eDirection::Left)
			{
				animator->PlayAnimation(L"BazziLeftStop", true);
			}
			if (mDirection == eDirection::Right)
			{
				animator->PlayAnimation(L"BazziRightStop", true);
			}
			mState = eState::MoveStop;
		}

	}

	void Bazzi::MoveStop()
	{
		static float time = 0.f;
		time += Time::DeltaTime();
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyDown(eKeyCode::Left) || Input::GetKey(eKeyCode::Left))		// 왼쪽 키를 누르면 왼쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziLeft", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::Right) || Input::GetKey(eKeyCode::Right))	// 오른쪽 키를 누르면 오른쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziRight", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::Up) || Input::GetKey(eKeyCode::Up))			// 위쪽 키를 누르면 위쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziUp", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::Down) || Input::GetKey(eKeyCode::Down))		// 아레쪽 키를 누르면 아레쪽 애니메이션 실행
		{
			animator->PlayAnimation(L"BazziDown", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Down;
		}

		if (time > 3.f)
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
			time = 0.f;

		}
	}

	void Bazzi::Trap()
	{
		static float Traptime = 0.f;
		Traptime += Time::DeltaTime();

		Animator* animator = GetComponent<Animator>();

		// 바늘 아이템 사용
		if (Input::GetKeyDown(eKeyCode::Ctrl) && ActiveItem == eItem::Needle)	// Live
		{
			SceneManager::SetNeedleGet(false);
			SceneManager::SetItemUse(true);

			animator->SetScale(Vector2(0.8f, 0.8f));
			animator->PlayAnimation(L"BazziLive", false);
			mState = eState::Live;
			ActiveItem = eItem::None;

		}
		else if(Traptime > 4.f)
		{
			if(SceneManager::GetMonsterQuantity != 0)
			{
				animator->SetScale(Vector2(0.8f, 0.8f));
				Resources::Find<Sound>(L"PlayerDie")->Play(false);

				animator->PlayAnimation(L"BazziBalloonDead", false);
				mState = eState::BalloonDead;
				Traptime = 0.f;
			}
			
		}
	}

	void Bazzi::Live()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			eItem::None;
			UseItemNum = 0;
			mState = eState::Idle;
		}
	}

	void Bazzi::Dead()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			SceneManager::SetPlayerDead(true);
			SceneManager::SubPlayerNum();
		}
	}

	void Bazzi::BalloonDead()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			SceneManager::SetPlayerDead(true);
			SceneManager::SubPlayerNum();
		}
	}
	 
	void Bazzi::Victory()
	{
		Animator* animator = GetComponent<Animator>();
		animator->SetScale(Vector2(0.9f, 0.9f));
		animator->PlayAnimation(L"BazziVictory", true);

		/*if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
		}*/
	}
	void Bazzi::ResetBazzi()
	{
		BombFlowCount = 0;
		Trigger = false;
		ActiveItem = eItem::None;
		UseItemNum = 0;
		BombLimit = 1;
		SetMoveSpeed(150.f);
		//ShieldUse = false;

	}
}

