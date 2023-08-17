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



namespace hy
{
	UINT Bazzi ::BombFlowCount = 0;
	bool Bazzi::Trigger = false;
	Bazzi :: eItem Bazzi:: ActiveItem = Bazzi::eItem ::None;
	bool Bazzi::UseItemNum = 0;
	UINT Bazzi::BombLimit = 1;
	
	Bazzi::Bazzi()
		: mState(eState::Make)
		, mDirection(eDirection::Down)
		, MoveSpeed(150.f)
		, Life(1)
		, North(1)
		, South(1)
		, East(1)
		, West(1)
	{
	}
	Bazzi::~Bazzi()
	{
		int a = 0;
	}
	void Bazzi::Initialize()
	{
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
		at->CreateAnimation(L"BazziDead", BazziDead_, Vector2(0.0f, 0.0f), Vector2(81.0f, 144.0f), 6, Vector2(0.0f, -15.0f), 0.15f);
		at->CreateAnimation(L"BazziTrap", BazziTrap_, Vector2(0.0f, 0.0f), Vector2(88.0f, 144.0f), 13, Vector2(0.0f, 0.0f), 0.18f);
		at->CreateAnimation(L"BazziLive", BazziLive_, Vector2(0.0f, 0.0f), Vector2(88.0f, 144.0f), 5, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziVictory", BazziVictory_, Vector2(0.0f, 0.0f), Vector2(64.0f, 80.0f), 8, Vector2(0.0f, 0.0f), 0.15f);
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

		// 물풍선 객체 생성 및 위치 조정
		if (Input::GetKeyDown(eKeyCode::Space))	
		{
			if(BombLimit != 0)
			{
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

 				Bomb_->GetComponent<Transform>()->SetPosition(Bombpos);
				BombLimit--;
			}
		}

		if (Input::GetKeyDown(eKeyCode::Ctrl) && ActiveItem == eItem::Shield && UseItemNum == 1)
		{
			Trigger = true;

			ShieldEffect* ShieldEffect_ = object::Instantiate<ShieldEffect>(eLayerType::Effect);
			Transform* Bazzitr = this->GetComponent<Transform>();
			Vector2 BazziLocation = Bazzitr->GetPosition();
			Vector2 Shieldpos = BazziLocation;
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
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.9f, 0.9f));
			at->PlayAnimation(L"BazziDead", false);
			mState = eState::Dead;
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::Item)
		{
			/*Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(1.0f, 1.0f));
			at->PlayAnimation(L"BazziDead", false);
			mState = eState::Dead;*/
		}

		else if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(0.8f, 0.8f));
			at->PlayAnimation(L"BazziTrap", false);
			mState = eState::Trap;

			/*at->PlayAnimation(L"BazziBalloonDead", false);
			mState = eState::BalloonDead;*/
		}

		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Crack)
		{
			//float GetSpeed = GetMoveSpeed();
			// 이동은 없고, 애니메이션만
			// 오른쪽으로 이동했을때 
			// 이동을 할때 방향이 곱해져서 이동을 함
			if (mDirection == eDirection::Right)
			{
				East = 0;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Left)
			{
				West = 0;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Down)
			{
				South = 0;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Up)
			{
				North = 0;
				mState = eState::Move;
			}
		}
		else if ((other->GetOwner()->GetLayerType() == eLayerType::Tile) && (tile != nullptr) && tile->GetType() == Tile::eType::Uncrushable)
		{
			if (mDirection == eDirection::Right)
			{
				East = 0;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Left)
			{
				West = 0;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Down)
			{
				South = 0;
				mState = eState::Move;
			}
			else if (mDirection == eDirection::Up)
			{
				North = 0;
				mState = eState::Move;
			}
		}

		
	}
	void Bazzi::OnCollisionStay(Collider* other)
	{

	}
	void Bazzi::OnCollisionExit(Collider* other)
	{
		North = 1;
		South = 1;
		East = 1;
		West = 1;
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

		//if (Input::GetKeyDown(eKeyCode::T) )	// Trap
		//{
		//	animator->SetScale(Vector2(1.0f, 1.0f));
		//	animator->PlayAnimation(L"BazziTrap", false);
		//	mState = eState::Trap;
		//}
		if (Input::GetKeyDown(eKeyCode::Ctrl) && ActiveItem == eItem::Needle && UseItemNum == 1)	// Live
		{
			animator->SetScale(Vector2(0.8f, 0.8f));
			animator->PlayAnimation(L"BazziLive", false);
			mState = eState::Live;
		}
		if (Input::GetKeyDown(eKeyCode::B))		// BalloonDead
		{
			animator->SetScale(Vector2(1.0f, 1.0f));
			animator->PlayAnimation(L"BazziBalloonDead", false);
			mState = eState::BalloonDead;
		}
	
		if (Input::GetKeyDown(eKeyCode::V))		// Victory
		{
			animator->SetScale(Vector2(0.8f, 0.8f));
			animator->PlayAnimation(L"BazziVictory", true);
			mState = eState::Victory;
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
				pos.y -=  North * MoveSpeed * Time::DeltaTime();

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
				pos.x -= West * MoveSpeed * Time::DeltaTime();

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
				pos.x += East * MoveSpeed * Time::DeltaTime();
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
				pos.y += South* MoveSpeed * Time::DeltaTime();
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

		if (Input::GetKeyDown(eKeyCode::Ctrl) && ActiveItem == eItem::Needle)	// Live
		{
			animator->SetScale(Vector2(0.8f, 0.8f));
			animator->PlayAnimation(L"BazziLive", false);
			mState = eState::Live;
			eItem::None;
		}
		else if(Traptime > 4.f)
		{
			if(ForestMap1::GetMonsterQuantity != 0)
			{
				animator->SetScale(Vector2(0.8f, 0.8f));
				animator->PlayAnimation(L"BazziBalloonDead", false);
				mState = eState::BalloonDead;
				Traptime = 0.f;
			}
			else
			{
				// Win
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
		ForestMap1::SetLoseLife(true);
		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void Bazzi::BalloonDead()
	{
		Animator* animator = GetComponent<Animator>();
		ForestMap1::SetLoseLife(true);

		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
			// Lose 
		}
	}
	 
	void Bazzi::Victory()
	{

		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
		}
	}
}

