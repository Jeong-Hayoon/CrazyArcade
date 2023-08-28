#include "hyPirateMap2.h"
#include "hyPlayScene.h"
#include "hyTitleScene.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyBackGround.h"
#include "hyTransform.h"
#include "hyAnimator.h"
#include "hyBazzi.h"
#include "hyPirateMonster.h"
#include "hyCollisionManager.h"
#include "hyToolScene.h"
#include "hyBalloon.h"
#include "hyDevil.h"
#include "hyPotion.h"
#include "hyNeedle.h"
#include "hyShield.h"
#include "hySecond.h"
#include "hyTen_Second.h"
#include "hyMinutes.h"
#include "hyDot.h"
#include "hyWin_Lose.h"
#include "hyGameStart.h"




// 타일 위치 30,55에 넣기

extern hy::Application application;

namespace hy
{
	PirateMap2::PirateMap2()
	{
	}
	PirateMap2::~PirateMap2()
	{
	}

	void PirateMap2::Load()
	{

		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = L"..\\Resources\\Tile\\PirateMap_2.tm";

		// rb : 이진수로 파일을 읽음
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");

		if (pFile == nullptr)
			return;

		while (true)
		{
			int sourceX = -1;
			int sourceY = -1;

			int	myX = -1;
			int myY = -1;

			if (fread(&sourceX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&sourceY, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myY, sizeof(int), 1, pFile) == NULL)
				break;

			Vector2 offset = Vector2((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f);
			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile
				, Vector2(myX * (TILE_WIDTH)+offset.x + LEFT_TOP_X
					, myY * (TILE_HEIGHT)+offset.y + LEFT_TOP_Y));

			tile->SetTile(sourceX, sourceY);
			// Crack(부서지며 충돌체가 있는 타일)
			if ((sourceX == 3 && sourceY == 0) ||
				(sourceX == 4 && sourceY == 0))
			{
				tile->SetType(Tile::eType::Crack);
			}
			// Uncrushable(부서지지는 않지만 충돌체는 있는 타입)
			if ((sourceX == 2 && sourceY == 3) ||
				(sourceX == 3 && sourceY == 3) ||
				(sourceX == 4 && sourceY == 3) ||
				(sourceX == 0 && sourceY == 4) ||
				(sourceX == 1 && sourceY == 4) ||
				(sourceX == 2 && sourceY == 4))
			{
				tile->SetType(Tile::eType::Uncrushable);
			}
			// None(충돌체가 없는 바닥같은 타일)
			if ((sourceX == 3 && sourceY == 4) ||
				(sourceX == 4 && sourceY == 4))
			{
				tile->SetType(Tile::eType::None);
			}

			if (tile->GetType() == Tile::eType::Crack || tile->GetType() == Tile::eType::Uncrushable)
			{
				Collider* Col = tile->AddComponent<Collider>();;
				Col->SetSize(Vector2(40.0f, 40.0f));

				CollisionManager::CollisionLayerCheck(eLayerType::Tile, eLayerType::Bomb, true);
				CollisionManager::CollisionLayerCheck(eLayerType::Tile, eLayerType::Player, true);
				CollisionManager::CollisionLayerCheck(eLayerType::Tile, eLayerType::Monster, true);
				CollisionManager::CollisionLayerCheck(eLayerType::Tile, eLayerType::Bombflow, true);

			}

			tile->SetSourceTileIdx(sourceX, sourceY);
			tile->SetTileIdx(myX, myY);

			mTiles.push_back(tile);
		}
		fclose(pFile);
	}

	void PirateMap2::Enter()
	{
		Resources::Find<Sound>(L"Play")->Play(true);
		SceneManager::SetBossQuantity(8);
		SceneManager::SetActiveStage(7);

		GameStart* gs1 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(185.0f, 60.0f));
		GameStart* gs2 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(450.0f, 640.0f));


	}

	void PirateMap2::Exit()
	{
		Resources::Find<Sound>(L"Play")->Stop(true);

		PirateBazzi->ResetBazzi();

	}

	void PirateMap2::Initialize()
	{
		Scene::Initialize();
		// 사운드 적용
		Resources::Load<Sound>(L"Play", L"..\\Resources\\Sound\\Sound\\Map\\bg_0.wav");
		Resources::Load<Sound>(L"Click", L"..\\Resources\\Sound\\Sound\\click.wav");


		// 타이머
		Timer_Dot* TimerDot = object::Instantiate<Timer_Dot>(eLayerType::UI);
		Transform* TimerDottr = TimerDot->GetComponent<Transform>();
		TimerDottr->SetPosition(Vector2(735.f, 81.f));

		Second* ForestSecondTimer = object::Instantiate<Second>(eLayerType::UI);
		Transform* ForestSecondTimertr = ForestSecondTimer->GetComponent<Transform>();
		ForestSecondTimertr->SetPosition(Vector2(765.f, 81.f));

		Ten_Second* ForestTen_SecondTimer = object::Instantiate<Ten_Second>(eLayerType::UI);
		Transform* ForestTen_SecondTimertr = ForestTen_SecondTimer->GetComponent<Transform>();
		ForestTen_SecondTimertr->SetPosition(Vector2(750.f, 81.f));

		Minutes* ForestMinutesTimer = object::Instantiate<Minutes>(eLayerType::UI);
		Transform* ForestMinutesTimertr = ForestMinutesTimer->GetComponent<Transform>();
		ForestMinutesTimertr->SetPosition(Vector2(720.f, 81.f));

		// 게임 틀
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.f, 1.f));
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));

		Texture* Tile_
			= Resources::Load<Texture>(L"Tile", L"..\\Resources\\Image\\Map\\Tile.bmp");

		PirateMap2::Load();

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::UI);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		// 배찌 상하좌우 애니메이션
		PirateBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
		Transform* forestbazzitr = PirateBazzi->GetComponent<Transform>();
		forestbazzitr->SetPosition(Vector2(60.0f, 70.0f));

		// 포레스트 몬스터
		PirateMonster* PirateMonster1 = object::Instantiate<PirateMonster>(eLayerType::Monster);
		PirateMonster1->GetComponent<Transform>()->SetPosition(Vector2(255.0f, 15.0f));
		PirateMonster* PirateMonster2 = object::Instantiate<PirateMonster>(eLayerType::Monster);
		PirateMonster2->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 300.0f));
		PirateMonster* PirateMonster3 = object::Instantiate<PirateMonster>(eLayerType::Monster);
		PirateMonster3->GetComponent<Transform>()->SetPosition(Vector2(830.0f, 540.0f));
		PirateMonster* PirateMonster4 = object::Instantiate<PirateMonster>(eLayerType::Monster);
		PirateMonster4->GetComponent<Transform>()->SetPosition(Vector2(650.0f, 780.0f));

		// 플레이어와 몬스터가 충돌(충돌 관계 지정)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// 플레이어와 물풍선 아이템 충돌(충돌 관계)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);

		// 플레이어와 물풍선 아이템 충돌(충돌 관계)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UseItem, true);

	

	}

	void PirateMap2::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MouseLeft))
		{
			Resources::Find<Sound>(L"Click")->Play(false);
		}

		Vector2 temp = Input::GetMousePosition();

		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 560 && temp.y <= 590 && temp.x >= 645 && temp.x <= 785)
		{
			Resources::Find<Sound>(L"Play")->Stop(true);

			SceneManager::LoadScene(L"LobbyScene");
		}

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"PirateMap3");
		}


	}
	void PirateMap2::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	Tile* PirateMap2::GetTile(UINT x, UINT y)
	{
		Tile* temp = nullptr;

		for (Tile* iter : mTiles)
		{
			UINT iter_x = iter->GetTileIndexX();
			UINT iter_y = iter->GetTileIndexY();

			if (x == iter_x && y == iter_y)
			{
				return iter;
			}
		}

		return nullptr;
	}
}
