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

	void Bomb::Flow()
	{
		// 2�� ������ Pop �ִϸ��̼��� ȣ���ϰ�, ���� ��ȯ

		static float Bombtime = 0.f;
		Bombtime += Time::DeltaTime();
		Animator* animator = GetComponent<Animator>();
		if (Bombtime > 3.f)
		{
			BombFlow* BombFlow_0 = object::Instantiate<BombFlow>(eLayerType::Effect);
			BombFlow* BombFlow_1 = object::Instantiate<BombFlow>(eLayerType::Effect);
			BombFlow* BombFlow_2 = object::Instantiate<BombFlow>(eLayerType::Effect);
			BombFlow* BombFlow_3 = object::Instantiate<BombFlow>(eLayerType::Effect);
			BombFlow* BombFlow_4 = object::Instantiate<BombFlow>(eLayerType::Effect);

			Transform* Bombtr = this->GetComponent<Transform>();
			Vector2 BombLocationtr = Bombtr->GetPosition();
			Vector2 bombflowpos;

			int offset[4][2] =
			{
				0,+1, // ������
				0,-1, // ����
				-1,0, // ����
				+1,0  // �Ʒ���
			};

			int X_ = 0;
			int Y_ = 0;

			// �ش� Ÿ�� �ε����� ����
			X_ = (BombLocationtr.x - 20.f) / (TILE_WIDTH);
			Y_ = (BombLocationtr.y - 40.f) / (TILE_HEIGHT);

			// �ش� Ÿ�� �ε����� Ÿ�� ����� ���Ͽ� �ش� Ÿ���� LeftTop���� �̵�
			bombflowpos.x = (X_ * TILE_WIDTH) + (TILE_WIDTH / 2) + 20.f;
			bombflowpos.y = (Y_ * TILE_HEIGHT) + (TILE_HEIGHT / 2) + 40.f;

			BombFlow_0->GetComponent<Transform>()->SetPosition(bombflowpos);

			for (int i = 0; i < 4; i++)
			{
				bombflowpos.y = BombLocationtr.y + (offset[i][0] * TILE_HEIGHT);
				bombflowpos.x = BombLocationtr.x + (offset[i][1] * TILE_WIDTH);

				if(i == 0)
				{
					BombFlow_1->Right();
					BombFlow_1->GetComponent<Transform>()->SetPosition(bombflowpos);
				}

				else if (i == 1)
				{
					BombFlow_2->Left();
					BombFlow_2->GetComponent<Transform>()->SetPosition(bombflowpos);
				}

				else if (i == 2)
				{
					BombFlow_3->Up();
					BombFlow_3->GetComponent<Transform>()->SetPosition(bombflowpos);
				}

				else if (i == 3)
				{
					BombFlow_4->Down();
					BombFlow_4->GetComponent<Transform>()->SetPosition(bombflowpos);
				}

			}

		/*	if (Bazzi::GetBombFlowCount() == 0)
			{
				
			}

			else
			{


			}*/

			mState = eState::Pop;
			Bombtime = 0.f;
		}
		
	}
	void Bomb::Pop()
	{
		Destroy(this);
	}


}

