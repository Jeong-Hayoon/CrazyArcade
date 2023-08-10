#include "hyBomb.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hyAnimator.h"
#include "hyResources.h"
// #include "hyForestMap1.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyRigidbody.h"
#include "hyBazzi.h"
#include "hyBombFlow.h"



namespace hy
{
	// 3�� ������ ���ٱ� ��
	Bomb::Bomb()
		: mState(eState::Flow)
	{
		Animator* bt = AddComponent<Animator>();
		bt->CreateAnimationFolder(L"Bombidle", L"..\\Resources\\Image\\Bomb\\Idle", Vector2(0.f, 0.f), 0.4f);
		
		// �����¿� ���ٱ�
		bt->CreateAnimationFolder(L"BombUpIdle", L"..\\Resources\\Image\\Bomb\\UpIdleflow", Vector2(0.f, 0.f), 0.4f);
		bt->CreateAnimationFolder(L"BombUp", L"..\\Resources\\Image\\Bomb\\Upflow", Vector2(0.f, 0.f), 0.4f);

		bt->CreateAnimationFolder(L"BombDownIdle", L"..\\Resources\\Image\\Bomb\\DownIdleflow", Vector2(0.f, 0.f), 0.4f);
		bt->CreateAnimationFolder(L"BombDown", L"..\\Resources\\Image\\Bomb\\Downflow", Vector2(0.f, 0.f), 0.4f);

		bt->CreateAnimationFolder(L"BombRightIdle", L"..\\Resources\\Image\\Bomb\\RightIdleflow", Vector2(0.f, 0.f), 0.4f);
		bt->CreateAnimationFolder(L"BombRight", L"..\\Resources\\Image\\Bomb\\Rightflow", Vector2(0.f, 0.f), 0.4f);

		bt->CreateAnimationFolder(L"BombLeftIdle", L"..\\Resources\\Image\\Bomb\\LeftIdleflow", Vector2(0.f, 0.f), 0.4f);
		bt->CreateAnimationFolder(L"BombLeft", L"..\\Resources\\Image\\Bomb\\Leftflow", Vector2(0.f, 0.f), 0.4f);

		bt->CreateAnimationFolder(L"BombCenter", L"..\\Resources\\Image\\Bomb\\Centerflow", Vector2(0.f, 0.f), 0.4f);

		bt->SetScale(Vector2(1.f, 1.f));
		bt->PlayAnimation(L"Bombidle", true);

	}
	Bomb::~Bomb()
	{
	}
	void Bomb::Initialize()
	{
		GameObject::Initialize();
	}
	void Bomb::Update()
	{
		GameObject::Update();

		// tab + enter �ϸ� ����ġ ����
		switch (mState)
		{
		/*case hy::Bomb::eState::FlowIdle:
			FlowIdle(1);
			break;*/

		case hy::Bomb::eState::Flow:
			Flow();
			break;
		case hy::Bomb::eState::Pop:
			Pop();
			break;
		case hy::Bomb::eState::End:
			break;
		default:
			break;
		}

	}
	void Bomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bomb::OnCollisionEnter(Collider* other)
	{
	}
	void Bomb::OnCollisionStay(Collider* other)
	{
	}
	void Bomb::OnCollisionExit(Collider* other)
	{
	}

	// �������� ����Լ� ��õ..
	// but ����Լ� �ʹ� �����..
	//void Bomb::FlowIdle(UINT num)
	//{
	//	Animator* animator = GetComponent<Animator>();

	//	for (int i = 0; i < num; i++)
	//	{
	//		// �̺κ� ����
	//		// �ִϸ��̼��� ��ġ�� Bomb�� �����¿�� ��ġ
	//		//
	//		animator->PlayAnimation(L"BombUpIdle", false);
	//		animator->PlayAnimation(L"BombDownIdle", false);
	//		animator->PlayAnimation(L"BombRightIdle", false);
	//		animator->PlayAnimation(L"BombLeftIdle", false);

	//		animator->PlayAnimation(L"BombUp", false);
	//		animator->PlayAnimation(L"BombDown", false);
	//		animator->PlayAnimation(L"BombRight", false);
	//		animator->PlayAnimation(L"BombLeft", false);

	//		/*Bazzi* flow = object::Instantiate<Bazzi>(eLayerType::Player);
	//		FlowIdle(flow->GetBombFlow());*/
	//	}

	//}

	void Bomb::BombRec(Vector2 dir, int x, int y)
	{
		// ����ó������ ������ BombFlow ������ŭ ��������
		// BombFlow-1�϶��� FlowIdle���� Flow �ִϸ��̼� ����ǵ���
		if (y < 0 || y >= 13 
			|| x < 0 || x >= 15)
			return;

		//if (power > MaxPower(3))
		//	return;

		//if (mapData[y][x] == �浹����)		// Ÿ�ϸ����� �迭 �����
		//	return;
	
		if (dir == Vector2::Right)
		{
			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Effect);
			bombflowpos.y = y * TILE_HEIGHT + 60.0f;
			bombflowpos.x = x * TILE_WIDTH + 40.0f;

			bombFlow->Right();
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			BombRec(dir, int(x + dir.x), int(y + dir.y));
		}
	
		if (dir == Vector2::Up)
		{
			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Effect);
			bombflowpos.y = y * TILE_HEIGHT + 60.0f;
			bombflowpos.x = x * TILE_WIDTH + 40.0f;

			bombFlow->Up();
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			BombRec(dir, int(x + dir.x), int(y + dir.y));
		}

		if (dir == Vector2::Left)
		{
			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Effect);
			bombflowpos.y = y * TILE_HEIGHT + 60.0f;
			bombflowpos.x = x * TILE_WIDTH + 40.0f;

			bombFlow->Left();
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			BombRec(dir, int(x + dir.x), int(y + dir.y));
		}

		if (dir == Vector2::Down)
		{
			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Effect);
			bombflowpos.y = y * TILE_HEIGHT + 60.0f;
			bombflowpos.x = x * TILE_WIDTH + 40.0f;

			bombFlow->Down();
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			BombRec(dir, int(x + dir.x), int(y + dir.y));
		}

	}

	void Bomb::Flow()
	{
		// 2�� ������ Pop �ִϸ��̼��� ȣ���ϰ�, ���� ��ȯ

		static float Bombtime = 0.f;
		Bombtime += Time::DeltaTime();
		Animator* animator = GetComponent<Animator>();
		if (Bombtime > 3.f)
		{
			int X_ = 0;
			int Y_ = 0;
	
			Transform* Bombtr = this->GetComponent<Transform>();
			Vector2 BombLocationtr = Bombtr->GetPosition();
			// �ش� Ÿ�� �ε����� ����
			X_ = (BombLocationtr.x - 20.f) / (TILE_WIDTH);
			Y_ = (BombLocationtr.y - 40.f) / (TILE_HEIGHT);

			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Effect);
			bombflowpos.x = X_ * TILE_HEIGHT + 40.0f;
			bombflowpos.y = Y_ * TILE_WIDTH + 60.0f;

			//bombFlow->Right();
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			BombRec(Vector2::Right,  X_ + 1, Y_);
			BombRec(Vector2::Up, X_, Y_ - 1);
			BombRec(Vector2::Left, X_ - 1, Y_);
			BombRec(Vector2::Down, X_, Y_ + 1);

			mState = eState::Pop;
			Bombtime = 0.f;
		}
		
	}
	void Bomb::Pop()
	{
		Destroy(this);
	}


}

