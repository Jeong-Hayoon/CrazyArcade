#include "hyDaoBomb.h"
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
#include "hyDao.h"
#include "hyBombFlow.h"
#include "hyCollider.h"
#include "hyCollisionManager.h"
#include "hySound.h"
#include "hyForestMap1.h"
#include "hyForestMap2.h"
#include "hyForestMap3.h"
#include "hyIceMap1.h"
#include "hyIceMap2.h"
#include "hyIceMap3.h"
#include "hyPirateMap1.h"
#include "hyPirateMap2.h"
#include "hyPirateMap3.h"

namespace hy
{
	// 3초 지나면 물줄기 팡
	DaoBomb::DaoBomb()
		: mState(eState::Flow),
		Bombtime(0.f)
	{
		Collider* Col = AddComponent<Collider>();
		Col->SetSize(Vector2(40.0f, 40.0f));

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Bomb, true);

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
	DaoBomb::~DaoBomb()
	{
	}
	void DaoBomb::Initialize()
	{
		GameObject::Initialize();

		Resources::Load<Sound>(L"Wave", L"..\\Resources\\Sound\\Sound\\wave.wav");

	}
	void DaoBomb::Update()
	{
		GameObject::Update();

		Bombtime += Time::DeltaTime();

		// tab + enter 하면 스위치 생성
		switch (mState)
		{
			/*case hy::Bomb::eState::FlowIdle:
				FlowIdle(1);
				break;*/

		case hy::DaoBomb::eState::Flow:
			Flow();
			break;
		case hy::DaoBomb::eState::Pop:
			Pop();
			break;
		case hy::DaoBomb::eState::End:
			break;
		default:
			break;
		}

	}
	void DaoBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DaoBomb::OnCollisionEnter(Collider* other)
	{
	}
	void DaoBomb::OnCollisionStay(Collider* other)
	{
	}
	void DaoBomb::OnCollisionExit(Collider* other)
	{
	}

	void DaoBomb::BombRec(int level, Vector2 dir, int x, int y)
	{
		// 예외처리에서 배찌의 BombFlow 변수만큼 가져오기
		// BombFlow-1일때는 FlowIdle말고 Flow 애니메이션 재생되도록

		if (Dao::GetBombFlowCount() <= level)
		{
			if (dir == Vector2::Right)
			{
				Scene* scene = SceneManager::GetActiveScene();

				ForestMap1* forestScene1 = dynamic_cast<ForestMap1*>(scene);
				ForestMap2* forestScene2 = dynamic_cast<ForestMap2*>(scene);
				ForestMap3* forestScene3 = dynamic_cast<ForestMap3*>(scene);
				IceMap1* iceScene1 = dynamic_cast<IceMap1*>(scene);
				IceMap2* iceScene2 = dynamic_cast<IceMap2*>(scene);
				IceMap3* iceScene3 = dynamic_cast<IceMap3*>(scene);
				PirateMap1* pirateScene1 = dynamic_cast<PirateMap1*>(scene);
				PirateMap2* pirateScene2 = dynamic_cast<PirateMap2*>(scene);
				PirateMap3* pirateScene3 = dynamic_cast<PirateMap3*>(scene);

				Tile* tile = nullptr;

				if (forestScene1 != nullptr)
					tile = forestScene1->GetTile(x, y);

				if (forestScene2 != nullptr)
					tile = forestScene2->GetTile(x, y);

				if (forestScene3 != nullptr)
					tile = forestScene3->GetTile(x, y);

				if (iceScene1 != nullptr)
					tile = iceScene1->GetTile(x, y);

				if (iceScene2 != nullptr)
					tile = iceScene2->GetTile(x, y);

				if (iceScene3 != nullptr)
					tile = iceScene3->GetTile(x, y);

				if (pirateScene1 != nullptr)
					tile = pirateScene1->GetTile(x, y);

				if (pirateScene2 != nullptr)
					tile = pirateScene2->GetTile(x, y);

				if (pirateScene3 != nullptr)
					tile = pirateScene3->GetTile(x, y);

				if (tile != nullptr)
				{
					if (tile->GetType() == Tile::eType::Uncrushable)
					{
						return;
					}
					else
					{
						Vector2 bombflowpos;
						BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
						bombflowpos.y = y * TILE_HEIGHT + 60.0f;
						bombflowpos.x = x * TILE_WIDTH + 40.0f;

						bombFlow->Right();
						bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);
						return;
					}
				}
			}

			if (dir == Vector2::Up)
			{
				Scene* scene = SceneManager::GetActiveScene();

				ForestMap1* forestScene1 = dynamic_cast<ForestMap1*>(scene);
				ForestMap2* forestScene2 = dynamic_cast<ForestMap2*>(scene);
				ForestMap3* forestScene3 = dynamic_cast<ForestMap3*>(scene);
				IceMap1* iceScene1 = dynamic_cast<IceMap1*>(scene);
				IceMap2* iceScene2 = dynamic_cast<IceMap2*>(scene);
				IceMap3* iceScene3 = dynamic_cast<IceMap3*>(scene);
				PirateMap1* pirateScene1 = dynamic_cast<PirateMap1*>(scene);
				PirateMap2* pirateScene2 = dynamic_cast<PirateMap2*>(scene);
				PirateMap3* pirateScene3 = dynamic_cast<PirateMap3*>(scene);

				Tile* tile = nullptr;

				if (forestScene1 != nullptr)
					tile = forestScene1->GetTile(x, y);

				if (forestScene2 != nullptr)
					tile = forestScene2->GetTile(x, y);

				if (forestScene3 != nullptr)
					tile = forestScene3->GetTile(x, y);

				if (iceScene1 != nullptr)
					tile = iceScene1->GetTile(x, y);

				if (iceScene2 != nullptr)
					tile = iceScene2->GetTile(x, y);

				if (iceScene3 != nullptr)
					tile = iceScene3->GetTile(x, y);

				if (pirateScene1 != nullptr)
					tile = pirateScene1->GetTile(x, y);

				if (pirateScene2 != nullptr)
					tile = pirateScene2->GetTile(x, y);

				if (pirateScene3 != nullptr)
					tile = pirateScene3->GetTile(x, y);

				if (tile != nullptr)
				{
					if (tile->GetType() == Tile::eType::Uncrushable)
					{
						return;
					}
					else
					{
						Vector2 bombflowpos;
						BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
						bombflowpos.y = y * TILE_HEIGHT + 60.0f;
						bombflowpos.x = x * TILE_WIDTH + 40.0f;

						bombFlow->Up();
						bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);
						return;
					}
				}
			}

			if (dir == Vector2::Left)
			{
				Scene* scene = SceneManager::GetActiveScene();

				ForestMap1* forestScene1 = dynamic_cast<ForestMap1*>(scene);
				ForestMap2* forestScene2 = dynamic_cast<ForestMap2*>(scene);
				ForestMap3* forestScene3 = dynamic_cast<ForestMap3*>(scene);
				IceMap1* iceScene1 = dynamic_cast<IceMap1*>(scene);
				IceMap2* iceScene2 = dynamic_cast<IceMap2*>(scene);
				IceMap3* iceScene3 = dynamic_cast<IceMap3*>(scene);
				PirateMap1* pirateScene1 = dynamic_cast<PirateMap1*>(scene);
				PirateMap2* pirateScene2 = dynamic_cast<PirateMap2*>(scene);
				PirateMap3* pirateScene3 = dynamic_cast<PirateMap3*>(scene);

				Tile* tile = nullptr;

				if (forestScene1 != nullptr)
					tile = forestScene1->GetTile(x, y);

				if (forestScene2 != nullptr)
					tile = forestScene2->GetTile(x, y);

				if (forestScene3 != nullptr)
					tile = forestScene3->GetTile(x, y);

				if (iceScene1 != nullptr)
					tile = iceScene1->GetTile(x, y);

				if (iceScene2 != nullptr)
					tile = iceScene2->GetTile(x, y);

				if (iceScene3 != nullptr)
					tile = iceScene3->GetTile(x, y);

				if (pirateScene1 != nullptr)
					tile = pirateScene1->GetTile(x, y);

				if (pirateScene2 != nullptr)
					tile = pirateScene2->GetTile(x, y);

				if (pirateScene3 != nullptr)
					tile = pirateScene3->GetTile(x, y);

				if (tile != nullptr)
				{
					if (tile->GetType() == Tile::eType::Uncrushable)
					{
						return;
					}
					else
					{
						Vector2 bombflowpos;
						BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
						bombflowpos.y = y * TILE_HEIGHT + 60.0f;
						bombflowpos.x = x * TILE_WIDTH + 40.0f;

						bombFlow->Left();
						bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);
						return;
					}
				}
			}

			if (dir == Vector2::Down)
			{
				Scene* scene = SceneManager::GetActiveScene();

				ForestMap1* forestScene1 = dynamic_cast<ForestMap1*>(scene);
				ForestMap2* forestScene2 = dynamic_cast<ForestMap2*>(scene);
				ForestMap3* forestScene3 = dynamic_cast<ForestMap3*>(scene);
				IceMap1* iceScene1 = dynamic_cast<IceMap1*>(scene);
				IceMap2* iceScene2 = dynamic_cast<IceMap2*>(scene);
				IceMap3* iceScene3 = dynamic_cast<IceMap3*>(scene);
				PirateMap1* pirateScene1 = dynamic_cast<PirateMap1*>(scene);
				PirateMap2* pirateScene2 = dynamic_cast<PirateMap2*>(scene);
				PirateMap3* pirateScene3 = dynamic_cast<PirateMap3*>(scene);

				Tile* tile = nullptr;

				if (forestScene1 != nullptr)
					tile = forestScene1->GetTile(x, y);

				if (forestScene2 != nullptr)
					tile = forestScene2->GetTile(x, y);

				if (forestScene3 != nullptr)
					tile = forestScene3->GetTile(x, y);

				if (iceScene1 != nullptr)
					tile = iceScene1->GetTile(x, y);

				if (iceScene2 != nullptr)
					tile = iceScene2->GetTile(x, y);

				if (iceScene3 != nullptr)
					tile = iceScene3->GetTile(x, y);

				if (pirateScene1 != nullptr)
					tile = pirateScene1->GetTile(x, y);

				if (pirateScene2 != nullptr)
					tile = pirateScene2->GetTile(x, y);

				if (pirateScene3 != nullptr)
					tile = pirateScene3->GetTile(x, y);

				if (tile != nullptr)
				{
					if (tile->GetType() == Tile::eType::Uncrushable)
					{
						return;
					}
					else
					{
						Vector2 bombflowpos;
						BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
						bombflowpos.y = y * TILE_HEIGHT + 60.0f;
						bombflowpos.x = x * TILE_WIDTH + 40.0f;

						bombFlow->Down();
						bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);
						return;
					}
				}
			}

			return;
		}

		if (y < 0 || y >= 13
			|| x < 0 || x >= 15)
			return;

		// 만약 타일이 있다면 return
		/*if ()
			return;*/

			//if (mapData[y][x] == 충돌가능)		// 타일맵으로 배열 만들기
			//	return;

		if (dir == Vector2::Right)
		{
			Scene* scene = SceneManager::GetActiveScene();

			ForestMap1* forestScene1 = dynamic_cast<ForestMap1*>(scene);
			ForestMap2* forestScene2 = dynamic_cast<ForestMap2*>(scene);
			ForestMap3* forestScene3 = dynamic_cast<ForestMap3*>(scene);
			IceMap1* iceScene1 = dynamic_cast<IceMap1*>(scene);
			IceMap2* iceScene2 = dynamic_cast<IceMap2*>(scene);
			IceMap3* iceScene3 = dynamic_cast<IceMap3*>(scene);
			PirateMap1* pirateScene1 = dynamic_cast<PirateMap1*>(scene);
			PirateMap2* pirateScene2 = dynamic_cast<PirateMap2*>(scene);
			PirateMap3* pirateScene3 = dynamic_cast<PirateMap3*>(scene);

			Tile* tile = nullptr;

			if (forestScene1 != nullptr)
				tile = forestScene1->GetTile(x, y);

			if (forestScene2 != nullptr)
				tile = forestScene2->GetTile(x, y);

			if (forestScene3 != nullptr)
				tile = forestScene3->GetTile(x, y);

			if (iceScene1 != nullptr)
				tile = iceScene1->GetTile(x, y);

			if (iceScene2 != nullptr)
				tile = iceScene2->GetTile(x, y);

			if (iceScene3 != nullptr)
				tile = iceScene3->GetTile(x, y);

			if (pirateScene1 != nullptr)
				tile = pirateScene1->GetTile(x, y);

			if (pirateScene2 != nullptr)
				tile = pirateScene2->GetTile(x, y);

			if (pirateScene3 != nullptr)
				tile = pirateScene3->GetTile(x, y);

			if (tile != nullptr)
			{
				if (tile->GetType() == Tile::eType::Crack)
				{
					Vector2 bombflowpos;
					BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
					bombflowpos.y = y * TILE_HEIGHT + 60.0f;
					bombflowpos.x = x * TILE_WIDTH + 40.0f;

					bombFlow->Right();
					bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);
					return;
				}
				else if (tile != nullptr && tile->GetType() == Tile::eType::Uncrushable)
				{
					return;
				}
			}


			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
			bombflowpos.y = y * TILE_HEIGHT + 60.0f;
			bombflowpos.x = x * TILE_WIDTH + 40.0f;

			if (Dao::GetBombFlowCount() < (level - 2))
			{
				bombFlow->RightIdle();
			}
			else if (Dao::GetBombFlowCount() == (level - 2))
			{
				bombFlow->Right();
			}
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			BombRec(level + 1, dir, int(x + dir.x), int(y + dir.y));
		}

		if (dir == Vector2::Up)
		{
			Scene* scene = SceneManager::GetActiveScene();

			ForestMap1* forestScene1 = dynamic_cast<ForestMap1*>(scene);
			ForestMap2* forestScene2 = dynamic_cast<ForestMap2*>(scene);
			ForestMap3* forestScene3 = dynamic_cast<ForestMap3*>(scene);
			IceMap1* iceScene1 = dynamic_cast<IceMap1*>(scene);
			IceMap2* iceScene2 = dynamic_cast<IceMap2*>(scene);
			IceMap3* iceScene3 = dynamic_cast<IceMap3*>(scene);
			PirateMap1* pirateScene1 = dynamic_cast<PirateMap1*>(scene);
			PirateMap2* pirateScene2 = dynamic_cast<PirateMap2*>(scene);
			PirateMap3* pirateScene3 = dynamic_cast<PirateMap3*>(scene);

			Tile* tile = nullptr;

			if (forestScene1 != nullptr)
				tile = forestScene1->GetTile(x, y);

			if (forestScene2 != nullptr)
				tile = forestScene2->GetTile(x, y);

			if (forestScene3 != nullptr)
				tile = forestScene3->GetTile(x, y);

			if (iceScene1 != nullptr)
				tile = iceScene1->GetTile(x, y);

			if (iceScene2 != nullptr)
				tile = iceScene2->GetTile(x, y);

			if (iceScene3 != nullptr)
				tile = iceScene3->GetTile(x, y);

			if (pirateScene1 != nullptr)
				tile = pirateScene1->GetTile(x, y);

			if (pirateScene2 != nullptr)
				tile = pirateScene2->GetTile(x, y);

			if (pirateScene3 != nullptr)
				tile = pirateScene3->GetTile(x, y);

			if (tile != nullptr)
			{
				if (tile->GetType() == Tile::eType::Crack)
				{
					Vector2 bombflowpos;
					BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
					bombflowpos.y = y * TILE_HEIGHT + 60.0f;
					bombflowpos.x = x * TILE_WIDTH + 40.0f;

					bombFlow->Up();
					bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);
					return;
				}
				else if (tile != nullptr && tile->GetType() == Tile::eType::Uncrushable)
				{
					return;
				}
			}

			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
			bombflowpos.y = y * TILE_HEIGHT + 60.0f;
			bombflowpos.x = x * TILE_WIDTH + 40.0f;

			if (Dao::GetBombFlowCount() < (level - 2))
			{
				bombFlow->UpIdle();
			}
			else if (Dao::GetBombFlowCount() == (level - 2))
			{
				bombFlow->Up();
			}
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			BombRec(level + 1, dir, int(x + dir.x), int(y + dir.y));
		}

		if (dir == Vector2::Left)
		{
			Scene* scene = SceneManager::GetActiveScene();

			ForestMap1* forestScene1 = dynamic_cast<ForestMap1*>(scene);
			ForestMap2* forestScene2 = dynamic_cast<ForestMap2*>(scene);
			ForestMap3* forestScene3 = dynamic_cast<ForestMap3*>(scene);
			IceMap1* iceScene1 = dynamic_cast<IceMap1*>(scene);
			IceMap2* iceScene2 = dynamic_cast<IceMap2*>(scene);
			IceMap3* iceScene3 = dynamic_cast<IceMap3*>(scene);
			PirateMap1* pirateScene1 = dynamic_cast<PirateMap1*>(scene);
			PirateMap2* pirateScene2 = dynamic_cast<PirateMap2*>(scene);
			PirateMap3* pirateScene3 = dynamic_cast<PirateMap3*>(scene);

			Tile* tile = nullptr;

			if (forestScene1 != nullptr)
				tile = forestScene1->GetTile(x, y);

			if (forestScene2 != nullptr)
				tile = forestScene2->GetTile(x, y);

			if (forestScene3 != nullptr)
				tile = forestScene3->GetTile(x, y);

			if (iceScene1 != nullptr)
				tile = iceScene1->GetTile(x, y);

			if (iceScene2 != nullptr)
				tile = iceScene2->GetTile(x, y);

			if (iceScene3 != nullptr)
				tile = iceScene3->GetTile(x, y);

			if (pirateScene1 != nullptr)
				tile = pirateScene1->GetTile(x, y);

			if (pirateScene2 != nullptr)
				tile = pirateScene2->GetTile(x, y);

			if (pirateScene3 != nullptr)
				tile = pirateScene3->GetTile(x, y);

			if (tile != nullptr)
			{
				if (tile->GetType() == Tile::eType::Crack)
				{
					Vector2 bombflowpos;
					BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
					bombflowpos.y = y * TILE_HEIGHT + 60.0f;
					bombflowpos.x = x * TILE_WIDTH + 40.0f;

					bombFlow->Left();
					bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);
					return;
				}
				else if (tile != nullptr && tile->GetType() == Tile::eType::Uncrushable)
				{
					return;
				}
			}

			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
			bombflowpos.y = y * TILE_HEIGHT + 60.0f;
			bombflowpos.x = x * TILE_WIDTH + 40.0f;

			if (Bazzi::GetBombFlowCount() < (level - 2))
			{
				bombFlow->LeftIdle();
			}
			else if (Bazzi::GetBombFlowCount() == (level - 2))
			{
				bombFlow->Left();
			}
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			BombRec(level + 1, dir, int(x + dir.x), int(y + dir.y));
		}

		if (dir == Vector2::Down)
		{
			Scene* scene = SceneManager::GetActiveScene();

			ForestMap1* forestScene1 = dynamic_cast<ForestMap1*>(scene);
			ForestMap2* forestScene2 = dynamic_cast<ForestMap2*>(scene);
			ForestMap3* forestScene3 = dynamic_cast<ForestMap3*>(scene);
			IceMap1* iceScene1 = dynamic_cast<IceMap1*>(scene);
			IceMap2* iceScene2 = dynamic_cast<IceMap2*>(scene);
			IceMap3* iceScene3 = dynamic_cast<IceMap3*>(scene);
			PirateMap1* pirateScene1 = dynamic_cast<PirateMap1*>(scene);
			PirateMap2* pirateScene2 = dynamic_cast<PirateMap2*>(scene);
			PirateMap3* pirateScene3 = dynamic_cast<PirateMap3*>(scene);

			Tile* tile = nullptr;

			if (forestScene1 != nullptr)
				tile = forestScene1->GetTile(x, y);

			if (forestScene2 != nullptr)
				tile = forestScene2->GetTile(x, y);

			if (forestScene3 != nullptr)
				tile = forestScene3->GetTile(x, y);

			if (iceScene1 != nullptr)
				tile = iceScene1->GetTile(x, y);

			if (iceScene2 != nullptr)
				tile = iceScene2->GetTile(x, y);

			if (iceScene3 != nullptr)
				tile = iceScene3->GetTile(x, y);

			if (pirateScene1 != nullptr)
				tile = pirateScene1->GetTile(x, y);

			if (pirateScene2 != nullptr)
				tile = pirateScene2->GetTile(x, y);

			if (pirateScene3 != nullptr)
				tile = pirateScene3->GetTile(x, y);

			if (tile != nullptr)
			{
				if (tile->GetType() == Tile::eType::Crack)
				{
					Vector2 bombflowpos;
					BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
					bombflowpos.y = y * TILE_HEIGHT + 60.0f;
					bombflowpos.x = x * TILE_WIDTH + 40.0f;

					bombFlow->Down();
					bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);
					return;
				}
				else if (tile != nullptr && tile->GetType() == Tile::eType::Uncrushable)
				{
					return;
				}
			}

			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
			bombflowpos.y = y * TILE_HEIGHT + 60.0f;
			bombflowpos.x = x * TILE_WIDTH + 40.0f;

			if (Dao::GetBombFlowCount() < (level - 2))
			{
				bombFlow->DownIdle();
			}
			else if (Dao::GetBombFlowCount() == (level - 2))
			{
				bombFlow->Down();
			}
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			BombRec(level + 1, dir, int(x + dir.x), int(y + dir.y));
		}
	}

	void DaoBomb::Flow()
	{
		// 2초 지나면 Pop 애니메이션을 호출하고, 상태 전환

		Animator* animator = GetComponent<Animator>();
		if (Bombtime > 3.f)
		{
			int X_ = 0;
			int Y_ = 0;

			Transform* Bombtr = this->GetComponent<Transform>();
			Vector2 BombLocationtr = Bombtr->GetPosition();
			// 해당 타일 인덱스를 구함
			X_ = (BombLocationtr.x - 20.f) / (TILE_WIDTH);
			Y_ = (BombLocationtr.y - 40.f) / (TILE_HEIGHT);

			Vector2 bombflowpos;
			BombFlow* bombFlow = object::Instantiate<BombFlow>(eLayerType::Bombflow);
			bombflowpos.x = X_ * TILE_HEIGHT + 40.0f;
			bombflowpos.y = Y_ * TILE_WIDTH + 60.0f;

			//bombFlow->Right();
			bombFlow->GetComponent<Transform>()->SetPosition(bombflowpos);

			int level = 0;
			BombRec(level, Vector2::Right, X_ + 1, Y_);
			BombRec(level, Vector2::Up, X_, Y_ - 1);
			BombRec(level, Vector2::Left, X_ - 1, Y_);
			BombRec(level, Vector2::Down, X_, Y_ + 1);

			Resources::Find<Sound>(L"Wave")->Play(false);

			mState = eState::Pop;
			Bombtime = 0.f;
		}

	}
	void DaoBomb::Pop()
	{
		Destroy(this);
		Dao::BombLimitUp();

	}


}

