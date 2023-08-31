#include "hyForestMap1.h"
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
#include "hyForestMonster.h"
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
#include "hyUI.h"
#include "hyTime.h"
#include "hyWin_Lose.h"
#include "hyGameStart.h"
#include "hyDao.h"
#include "hyLobbyScene.h"




// 타일 위치 30,55에 넣기

extern hy::Application application;

namespace hy
{
	//bool ForestMap1::FunCheck = 0;

	ForestMap1::ForestMap1()
		:Initflag(false)
	{
	}
	ForestMap1::~ForestMap1()
	{
	}

	void ForestMap1::Enter()
	{
		Resources::Find<Sound>(L"Play")->Play(true);
		SceneManager::SetMonsterQuantity(4);
		GameStart* gs1 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(185.0f, 60.0f));
		GameStart* gs2= object::Instantiate<GameStart>(eLayerType::UI, Vector2(450.0f, 640.0f));
		SceneManager::SetActiveStage(0);

		// 배찌 상하좌우 애니메이션
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetBazziClick() == true && Initflag == false)
		{
			ForestBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = ForestBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(380.0f, 250.0f));
			Initflag = true;
			SceneManager::SetBazzi(ForestBazzi);


		}

		// 다오 상하좌우 애니메이션
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetDaoClick() == true && Initflag == false)
		{
			ForestDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = ForestDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(380.0f, 250.0f));
			Initflag = true;
			SceneManager::SetDao(ForestDao);


		}

		// 멀티 플레이어 세팅
		if (SceneManager::GetSelectMultiPlayer() == 1 && Initflag == false)
		{
			ForestBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = ForestBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(280.0f, 250.0f));

			ForestDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = ForestDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(360.0f, 250.0f));

			SceneManager::SetBazzi(ForestBazzi);
			SceneManager::SetDao(ForestDao);
			Initflag = true;
		}

		// 몬스터 수 세팅
		SceneManager::SetMonsterQuantity(4);

		// 포레스트 몬스터
		ForestMonster* ForestMonster1 = object::Instantiate<ForestMonster>(eLayerType::Monster);
		ForestMonster1->GetComponent<Transform>()->SetPosition(Vector2(40.0f, 60.0f));
		ForestMonster* ForestMonster2 = object::Instantiate<ForestMonster>(eLayerType::Monster);
		ForestMonster2->GetComponent<Transform>()->SetPosition(Vector2(40.0f, 450.0f));
		ForestMonster* ForestMonster3 = object::Instantiate<ForestMonster>(eLayerType::Monster);
		ForestMonster3->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 450.0f));
		ForestMonster* ForestMonster4 = object::Instantiate<ForestMonster>(eLayerType::Monster);
		ForestMonster4->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 60.0f));
	}

	void ForestMap1::Exit()
	{
		ForestBazzi->ResetBazzi();
		Resources::Find<Sound>(L"Play")->Stop(true);

	}


	void ForestMap1::Initialize()
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

		ForestMap1::Load();

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::UI);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		

		// 플레이어와 몬스터가 충돌(충돌 관계 지정)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		// 플레이어와 물풍선 아이템 충돌(충돌 관계)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);
		// 플레이어와 물풍선 아이템 충돌(충돌 관계)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UseItem, true);
		// 몬스터 물풍선 충돌(충돌 관계)
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Bomb, true);


		//// Shield 아이템 setting
		//Shield* Shield_1 = object::Instantiate<Shield>(eLayerType::UseItem, Vector2(410.0f, 250.0f));

		//// Shield 아이템 충돌 구현
		//Collider* Shiledcol = Shield_1->AddComponent<Collider>();
		//// Shield 아이템 충돌 사각형 사이즈 수정
		//Shiledcol->SetSize(Vector2(10.0f, 30.0f));
		
	}

	void ForestMap1::Update()
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
			Initflag = false;

		}

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"ForestMap2");
			Initflag = false;

		}

		// 승리
		if (SceneManager::GetMonsterQuantity() == 0)
		{
			Win();
			// 이부분 체크(중단점애는 들어오는데 애니메이션 실행이 안됨)
			ForestBazzi->Victory();
			SceneManager::SetMonsterQuantity(1);
		}

	
		// 패배
		if (SceneManager::GetMonsterQuantity() != 0/* && SceneManager::GetPlayerDead() == true*/ && SceneManager::GetPlayerNum() == 0)
		{
			Lose();
			//SceneManager::SetPlayerDead(false);
		}


	}
	void ForestMap1::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	void ForestMap1::Win()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* win = object::Instantiate< Win_Lose>(eLayerType::UI);
		win->Win();
		Transform* wintr = win->GetComponent<Transform>();
		wintr->SetPosition(Vector2(350.0f, 254.0f));

		if (Win_Lose::GetWin_Lose_flag() == true)
		{
			SceneManager::LoadScene(L"ForestMap2");
			Win_Lose::SetWin_Lose_flag(false);
		}
	}

	void ForestMap1::Lose()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* lose = object::Instantiate< Win_Lose>(eLayerType::UI);
		lose->Lose();
		Transform* losetr = lose->GetComponent<Transform>();
		losetr->SetPosition(Vector2(350.0f, 254.0f));
	}

	void ForestMap1::Reset()
	{

	}

	Tile* ForestMap1::GetTile(UINT x, UINT y)
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

	void ForestMap1::Load()
	{
		/*	Texture* forestFloor
				= Resources::Load<Texture>(L"ForestFloorTile", L"..\\resources\\image\\Bg\\ForestTile.bmp");*/

		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = L"..\\Resources\\Tile\\ForestMap_1.tm";

		//ZeroMemory(&ofn, sizeof(ofn));
		//ofn.lStructSize = sizeof(ofn);
		//ofn.hwndOwner = NULL;
		//ofn.lpstrFile = szFilePath;
		//ofn.lpstrFile[0] = '\0';
		//ofn.nMaxFile = 256;
		//ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		//ofn.nFilterIndex = 1;
		//ofn.lpstrFileTitle = NULL;
		//ofn.nMaxFileTitle = 0;
		//ofn.lpstrInitialDir = NULL;
		//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		//if (false == GetOpenFileName(&ofn))
		//	return;

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
			if ((sourceX == 0 && sourceY == 0) ||
				(sourceX == 1 && sourceY == 0) ||
				(sourceX == 2 && sourceY == 0))
			{
				tile->SetType(Tile::eType::Crack);
			}
			// Uncrushable(부서지지는 않지만 충돌체는 있는 타입)
			if ((sourceX == 0 && sourceY == 3) ||
				(sourceX == 1 && sourceY == 3))
			{
				tile->SetType(Tile::eType::Uncrushable);
			}
			// None(충돌체가 없는 바닥같은 타일)
			if ((sourceX == 0 && sourceY == 1))
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
}
