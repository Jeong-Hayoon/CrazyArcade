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

namespace hy
{
	Bazzi::Bazzi()
		: mState(eState::Make)
		,mDirection(eDirection::Down)
	{
	}
	Bazzi::~Bazzi()
	{
	}
	void Bazzi::Initialize()
	{

		Texture* Bazzi_ = Resources::Load<Texture>(L"Bazzi"
			, L"..\\Resources\\Image\\Bazzi\\Bazzi.bmp");

		Texture* BazziDie_ = Resources::Load<Texture>(L"BazziDie"
			, L"..\\Resources\\Image\\Bazzi\\BazziDie.bmp");

		Animator* at = AddComponent<Animator>();

		Texture* StartBazzi_ = Resources::Load<Texture>(L"StartBazzi"
			, L"..\\Resources\\Image\\Bazzi\\ready.bmp");

		at->CreateAnimation(L"StartBazzi", StartBazzi_, Vector2(0.0f, 0.0f), Vector2(64.0f, 86.0f), 18, Vector2(0.0f, 0.0f), 0.1f);
		at->CreateAnimation(L"BazziIdle", Bazzi_, Vector2(0.0f, 0.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.6f);

		at->CreateAnimation(L"BazziUp", Bazzi_, Vector2(0.0f, 60.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziUpStop", Bazzi_, Vector2(50.0f, 60.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziDown", Bazzi_, Vector2(0.0f, 120.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziDownStop", Bazzi_, Vector2(50.0f, 120.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziRight", Bazzi_, Vector2(0.0f, 240.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziRightStop", Bazzi_, Vector2(50.0f, 240.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziLeft", Bazzi_, Vector2(0.0f, 180.0f), Vector2(50.0f, 60.0f), 4, Vector2(0.0f, 0.0f), 0.15f);
		at->CreateAnimation(L"BazziLeftStop", Bazzi_, Vector2(50.0f, 180.0f), Vector2(50.0f, 60.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		at->CreateAnimation(L"BazziDie", BazziDie_, Vector2(0.0f, 0.0f), Vector2(91.0f, 144.0f), 10, Vector2(0.0f, 0.0f), 0.1f);

		at->PlayAnimation(L"StartBazzi", false);

		GameObject::Initialize();
	}

	// ���� ��ȭ�� ������Ʈ���� 
	void Bazzi::Update()	
	{
		GameObject::Update();

		//pixel �浹(���� �ϼ��� �ϰ� ���� ���̾ ��� �ڷ� ��ġ�ؼ� ���� ���� �� �� ���̰� ��ġ)
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

		// tab + enter �ϸ� ����ġ ����
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
		case hy::Bazzi::eState::Ready:
			Ready();
			break;
		case hy::Bazzi::eState::Trap:
			Trap();
			break;
		case hy::Bazzi::eState::Live:
			Live();
			break;

		case hy::Bazzi::eState::Victory:
			Victory();
			break;

		case hy::Bazzi::eState::End:
			break;
		default:
			break;
		}


		if (Input::GetKeyDown(eKeyCode::Space))		// ��ǳ�� ��ü ���� �� ��ġ ����
		{
			Bomb* Bomb_ = object::Instantiate<Bomb>(eLayerType::Effect);
			Transform* Bazzitr = GetComponent<Transform>();
			Vector2 Bazzipos = Bazzitr->GetPosition();

			if (mDirection == eDirection::Up)
			{
				Bazzipos.y -= 40.f;
				Bomb_->GetComponent<Transform>()->SetPosition(Bazzipos);
			}
			else if (mDirection == eDirection::Down)
			{
				Bazzipos.y += 70.f;
				Bomb_->GetComponent<Transform>()->SetPosition(Bazzipos);
			}
			else if (mDirection == eDirection::Left)
			{
				Bazzipos.x -= 60.f;
				Bazzipos.y += 25.f;
				Bomb_->GetComponent<Transform>()->SetPosition(Bazzipos);
			}
			else if (mDirection == eDirection::Right)
			{
				Bazzipos.x += 60.f;
				Bazzipos.y += 17.f;
				Bomb_->GetComponent<Transform>()->SetPosition(Bazzipos);
			}
		}

	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bazzi::OnCollisionEnter(Collider* other)
	{
		/*Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"BazziDie", false);

		if (at->IsActiveAnimationComplete())
		{
			SceneManager::LoadScene(L"IceMap");
		}*/
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
		if(animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"BazziIdle", true);
			mState = eState::Idle;
		}
	}

	void Bazzi::Idle()
	{
		Animator* animator = GetComponent<Animator>();	
		animator->SetScale(Vector2(1.3f, 1.3f));

		if (Input::GetKeyDown(eKeyCode::Left) || Input::GetKey(eKeyCode::Left))		// ���� Ű�� ������ ���� �ִϸ��̼� ����
		{
			animator->PlayAnimation(L"BazziLeft", true);
			mState = eState::Move;
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::Right) || Input::GetKey(eKeyCode::Right))		// ������ Ű�� ������ ������ �ִϸ��̼� ����
		{
			animator->PlayAnimation(L"BazziRight", true);
			mState = eState::Move;
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::Up) || Input::GetKey(eKeyCode::Up))		// ���� Ű�� ������ ���� �ִϸ��̼� ����
		{
			animator->PlayAnimation(L"BazziUp", true);
			mState = eState::Move;
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::Down) || Input::GetKey(eKeyCode::Down))		// �Ʒ��� Ű�� ������ �Ʒ��� �ִϸ��̼� ����
		{
			animator->PlayAnimation(L"BazziDown", true);
			mState = eState::Move;
			mDirection = eDirection::Down;
		}

		//if (Input::GetKeyDown(eKeyCode::K))		// �Ʒ��� Ű�� ������ �Ʒ��� �ִϸ��̼� ����
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

		// �߷�
	/*	if (Input::GetKeyDown(eKeyCode::W))
		{
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
		}*/
	
		// space�� ������ ��ü�� �����Ǵ� �ڵ� -> ��ǳ�� ��ü
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

 		if (mDirection == eDirection::Up)			// ������ �����̸� �������� �̵�
			pos.y -= 150.f * Time::DeltaTime();
		else if (mDirection == eDirection::Left)	// ������ �����̸� �������� �̵�
			pos.x -= 150.f * Time::DeltaTime();
		else if (mDirection == eDirection::Right)	// ������ �������̸� ���������� �̵�
			pos.x += 150.f * Time::DeltaTime();
		else if (mDirection == eDirection::Down)	// ������ �Ʒ����̸� �Ʒ������� �̵�
			pos.y += 150.f * Time::DeltaTime();

		tr->SetPosition(pos);

		if (Input::GetKeyDown(eKeyCode::Left))		// � Ű�� ������ �̵��� ���� Ű�� ������ ��(���� ��ȯ)
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


		if (!Input::GetKey(eKeyCode::Up) && !Input::GetKey(eKeyCode::Down)			// �ƹ� Ű�� �ȴ��� ������ ��
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

		if (Input::GetKeyDown(eKeyCode::Left) || Input::GetKey(eKeyCode::Left))		// ���� Ű�� ������ ���� �ִϸ��̼� ����
		{
			animator->PlayAnimation(L"BazziLeft", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Left;
		}
		if (Input::GetKeyDown(eKeyCode::Right) || Input::GetKey(eKeyCode::Right))		// ������ Ű�� ������ ������ �ִϸ��̼� ����
		{
			animator->PlayAnimation(L"BazziRight", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Right;
		}
		if (Input::GetKeyDown(eKeyCode::Up) || Input::GetKey(eKeyCode::Up))		// ���� Ű�� ������ ���� �ִϸ��̼� ����
		{
			animator->PlayAnimation(L"BazziUp", true);
			mState = eState::Move;
			time = 0.f;
			mDirection = eDirection::Up;
		}
		if (Input::GetKeyDown(eKeyCode::Down) || Input::GetKey(eKeyCode::Down))		// �Ʒ��� Ű�� ������ �Ʒ��� �ִϸ��̼� ����
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

	void Bazzi::DropWater()
	{
		// ���۹��� ���� �ִ� ������ �߰����ȴ�.
		/*Animator* animator = GetComponent<Animator>();

		if (animator->IsActiveAnimationComplete())
		{
			animator->PlayAnimation(L"bazziidle", true);
			mState = eState::Idle;
		}*/
	}

	void Bazzi::Ready()
	{
	}

	void Bazzi::Trap()
	{
	}

	void Bazzi::Live()
	{
	}
	 
	void Bazzi::Victory()
	{
	}
}

