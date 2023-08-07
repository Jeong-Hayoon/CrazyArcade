#include "hyBazzi.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
//#include "hyForestMap1.h"
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

namespace hy
{
	Bazzi :: eItem Bazzi:: ActiveItem = Bazzi::eItem ::None;
	
	Bazzi::Bazzi()
		: mState(eState::Make)
		, mDirection(eDirection::Down)
		, BombLimit(5)
		, MoveSpeed(150.f)
		, Life(1)
		, BombFlow(0)
	{
	}
	Bazzi::~Bazzi()
	{
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
		at->CreateAnimation(L"BazziTrap", BazziTrap_, Vector2(0.0f, 0.0f), Vector2(88.0f, 144.0f), 13, Vector2(0.0f, 0.0f), 0.15f);
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
			// 이부분 수정 필요
			if(BombLimit != 0)
			{
				Bomb* Bomb_ = object::Instantiate<Bomb>(eLayerType::Effect);
				Bazzi* BazziLocation = object::Instantiate<Bazzi>(eLayerType::Player);
				Transform* Bazzitr = BazziLocation->GetComponent<Transform>();
				Vector2 BazziLocationtr = Bazzitr->GetPosition();
				Vector2 Bombpos;

				Bombpos.x = (BazziLocationtr.x) / (TILE_WIDTH);
				Bombpos.y = (BazziLocationtr.y ) / (TILE_HEIGHT);

				Bombpos.y += 20.f;
 				Bomb_->GetComponent<Transform>()->SetPosition(Bombpos);
				BombLimit--;
			}
		}

		// 아이템 사용
		if (Input::GetKeyDown(eKeyCode::Ctrl))
		{
			// 실드 아이템 사용
			if (GetActiveItem() == eItem::Shield)
			{


				eItem::None;
			}
			// 바늘 아이템 사용
			else if (GetActiveItem() == eItem::Needle)
			{
				Animator* at = GetComponent<Animator>();
				at->PlayAnimation(L"BazziLive", false);
				mState = eState::Live;
				eItem::None;
			}

		}



	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bazzi::OnCollisionEnter(Collider* other)	// 충돌 처리
	{
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

		else if (other->GetOwner()->GetLayerType() == eLayerType::Effect)
		{
			Animator* at = GetComponent<Animator>();
			at->SetScale(Vector2(1.0f, 1.0f));
			at->PlayAnimation(L"BazziBalloonDead", false);
			mState = eState::BalloonDead;
		}

		// 사용아이템 충돌시 
		else if (other->GetOwner()->GetLayerType() == eLayerType::UseItem)
		{
		}

		
	}
	void Bazzi::OnCollisionStay(Collider* other)
	{

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

		if (Input::GetKeyDown(eKeyCode::T) )	// Trap
		{
			animator->SetScale(Vector2(1.0f, 1.0f));
			animator->PlayAnimation(L"BazziTrap", false);
			mState = eState::Trap;
		}
		if (Input::GetKeyDown(eKeyCode::L))		// Live
		{
			animator->SetScale(Vector2(1.0f, 1.0f));
			animator->PlayAnimation(L"BazziLive", false);
			mState = eState::Live;
		}
		if (Input::GetKeyDown(eKeyCode::B))		// BalloonDead
		{
			animator->SetScale(Vector2(1.0f, 1.0f));
			animator->PlayAnimation(L"BazziBalloonDead", false);
			mState = eState::BalloonDead;
		}
		//if (Input::GetKeyDown(eKeyCode::D))		// Dead
		//{
		//	animator->SetScale(Vector2(1.0f, 1.0f));
		//	animator->PlayAnimation(L"BazziDead", false);
		//	mState = eState::Dead;
		//}
		if (Input::GetKeyDown(eKeyCode::V))		// Victory
		{
			animator->SetScale(Vector2(1.0f, 1.0f));
			animator->PlayAnimation(L"BazziVictory", true);
			mState = eState::Victory;
		}

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
			pos.y -= MoveSpeed * Time::DeltaTime();
		else if (mDirection == eDirection::Left)	// 방향이 왼쪽이면 왼쪽으로 이동
			pos.x -= MoveSpeed * Time::DeltaTime();
		else if (mDirection == eDirection::Right)	// 방향이 오른쪽이면 오른쪽으로 이동
			pos.x += MoveSpeed * Time::DeltaTime();
		else if (mDirection == eDirection::Down)	// 방향이 아래쪽이면 아래쪽으로 이동
			pos.y += MoveSpeed * Time::DeltaTime();

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
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
		}
	}

	void Bazzi::Live()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
		}
	}

	void Bazzi::Dead()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
		}
	}

	void Bazzi::BalloonDead()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
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

