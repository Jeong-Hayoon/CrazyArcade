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
	// 3초 지나면 물줄기 팡
	Bomb::Bomb()
		: mState(eState::Flow)
	{
		Animator* bt = AddComponent<Animator>();
		bt->CreateAnimationFolder(L"Bombidle", L"..\\Resources\\Image\\Bomb\\Idle", Vector2(0.f, 0.f), 0.4f);
		
		// 상하좌우 물줄기
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

		// tab + enter 하면 스위치 생성
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

	// 선생님은 재귀함수 추천..
	// but 재귀함수 너무 어려워..
	//void Bomb::FlowIdle(UINT num)
	//{
	//	Animator* animator = GetComponent<Animator>();

	//	for (int i = 0; i < num; i++)
	//	{
	//		// 이부분 수정
	//		// 애니메이션의 위치는 Bomb의 상하좌우로 배치
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
		// 2초 지나면 Pop 애니메이션을 호출하고, 상태 전환

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
				0,+1, // 오른쪽
				0,-1, // 왼쪽
				-1,0, // 위쪽
				+1,0  // 아랫쪽
			};

			int X_ = 0;
			int Y_ = 0;

			// 해당 타일 인덱스를 구함
			X_ = (BombLocationtr.x - 20.f) / (TILE_WIDTH);
			Y_ = (BombLocationtr.y - 40.f) / (TILE_HEIGHT);

			// 해당 타일 인덱스에 타일 사이즈를 곱하여 해당 타일의 LeftTop으로 이동
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

