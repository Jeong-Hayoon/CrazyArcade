//#include "hyPlayer.h"
//#include "hyTransform.h"
//#include "hyInput.h"
//#include "hyTime.h"
//#include "hyAnimator.h"
//
//namespace hy
//{
//	Player::Player()
//		: mState(eState::Idle)
//
//	{
//	}
//	Player::~Player()
//	{
//	}
//	void Player::Initialize()
//	{
//		GameObject::Initialize();
//	}
//	void Player::Update()
//	{
//		GameObject::Update();
//
//		switch (mState)
//		{
//		case hy::Player::eState::Idle:
//			Idle();
//			break;
//		case hy::Player::eState::Move:
//			Move();
//			break;
//		case hy::Player::eState::DropWater:
//			DropWater();
//			break;
//		case hy::Player::eState::Death:
//			DropWater();
//			break;
//		case hy::Player::eState::End:
//			break;
//		default:
//			break;
//		}
//	}
//	void Player::Render(HDC hdc)
//	{
//		GameObject::Render(hdc);
// 
// ---------------------------------------------------------- //
// void Player::OnCollisionEnter(Collider* other)
//{
//}
//void Player::OnCollisionStay(Collider* other)
//{
//}
//void Player::OnCollisionExit(Collider* other)
//{
//}

//	}
//
//	void Player::Idle()
//	{
//		Animator* animator = GetComponent<Animator>();
//
//		if (Input::GetKey(eKeyCode::W))
//		{
//			animator->PlayAnimation(L"PlayerUpMove", true);
//			mState = eState::Move;
//		}
//		if (Input::GetKey(eKeyCode::A))
//		{
//			animator->PlayAnimation(L"PlayerLeftMove", true);
//			mState = eState::Move;
//		}
//		if (Input::GetKey(eKeyCode::S))
//		{
//			animator->PlayAnimation(L"PlayerDownMove", true);
//			mState = eState::Move;
//		}
//		if (Input::GetKey(eKeyCode::D))
//		{
//			animator->PlayAnimation(L"PlayerRightMove", true);
//			mState = eState::Move;
//		}
//
//		if (Input::GetKey(eKeyCode::MouseLeft))
//		{
//			animator->PlayAnimation(L"PlayerDropWater", false);
//			mState = eState::DropWater;
//		}
//	}
//	void Player::Move()
//	{
//		Transform* tr = GetComponent<Transform>();
//		Vector2 pos = tr->GetPosition();
//		if (Input::GetKey(eKeyCode::W))
//		{
//			pos.y -= 100.0f * Time::DeltaTime();
//		}
//		if (Input::GetKey(eKeyCode::A))
//		{
//			pos.x -= 100.0f * Time::DeltaTime();
//		}
//		if (Input::GetKey(eKeyCode::S))
//		{
//			pos.y += 100.0f * Time::DeltaTime();
//		}
//		if (Input::GetKey(eKeyCode::D))
//		{
//			pos.x += 100.0f * Time::DeltaTime();
//		}
//		tr->SetPosition(pos);
//
//		if (Input::GetKeyUp(eKeyCode::W)
//			|| Input::GetKeyUp(eKeyCode::A)
//			|| Input::GetKeyUp(eKeyCode::S)
//			|| Input::GetKeyUp(eKeyCode::D))
//		{
//			Animator* animator = GetComponent<Animator>();
//			animator->PlayAnimation(L"PlayerIdle", true);
//			mState = eState::Idle;
//		}
//	}
//	void Player::DropWater()
//	{
//		// 농작물에 물을 주는 로직이 추가가된다.
//		Animator* animator = GetComponent<Animator>();
//
//		if (animator->IsActiveAnimationComplete())
//		{
//			animator->PlayAnimation(L"PlayerIdle", true);
//			mState = eState::Idle;
//		}
//	}
//
//	void Player::Dead()
//	{
//	}
//}
//
