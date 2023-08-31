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
#include "hyLobbyScene.h"




// Ÿ�� ��ġ 30,55�� �ֱ�

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

		// rb : �������� ������ ����
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
			// Crack(�μ����� �浹ü�� �ִ� Ÿ��)
			if ((sourceX == 3 && sourceY == 0) ||
				(sourceX == 4 && sourceY == 0))
			{
				tile->SetType(Tile::eType::Crack);
			}
			// Uncrushable(�μ������� ������ �浹ü�� �ִ� Ÿ��)
			if ((sourceX == 2 && sourceY == 3) ||
				(sourceX == 3 && sourceY == 3) ||
				(sourceX == 4 && sourceY == 3) ||
				(sourceX == 0 && sourceY == 4) ||
				(sourceX == 1 && sourceY == 4) ||
				(sourceX == 2 && sourceY == 4))
			{
				tile->SetType(Tile::eType::Uncrushable);
			}
			// None(�浹ü�� ���� �ٴڰ��� Ÿ��)
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
		SceneManager::SetMonsterQuantity(4);
		SceneManager::SetActiveStage(7);

		GameStart* gs1 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(185.0f, 60.0f));
		GameStart* gs2 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(450.0f, 640.0f));

		// Ÿ�̸�
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

		// ���� �����¿� �ִϸ��̼�
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetBazziClick() == true && Initflag == false)
		{
			PirateBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = PirateBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(60.0f, 70.0f));
			SceneManager::SetBazzi(PirateBazzi);

			Initflag = true;

			// ���� ������
			Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
				, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

			BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::UI);
			bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
			SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
			bzprofilesr->SetImage(BZProfile);
			bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		}

		// �ٿ� �����¿� �ִϸ��̼�
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetDaoClick() == true && Initflag == false)
		{
			PirateDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = PirateDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(60.0f, 70.0f));
			Initflag = true;
			SceneManager::SetDao(PirateDao);

			// �ٿ� ������
			Texture* DAProfile = Resources::Load<Texture>(L"DAProfileImage"
				, L"..\\Resources\\Image\\UI\\IngameDao.bmp");

			BackGround* daprofile = object::Instantiate<BackGround>(eLayerType::UI);
			daprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
			SpriteRenderer* daprofilesr = daprofile->AddComponent<SpriteRenderer>();
			daprofilesr->SetImage(DAProfile);
			daprofilesr->SetScale(Vector2(0.6f, 0.6f));
		}

		// ��Ƽ �÷��̾� ����
		if (SceneManager::GetSelectMultiPlayer() == 1 && Initflag == false)
		{
			PirateBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = PirateBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(380.0f, 250.0f));

			PirateDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = PirateDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(280.0f, 250.0f));

			SceneManager::SetBazzi(PirateBazzi);
			SceneManager::SetDao(PirateDao);

			Initflag = true;
		}

		// �Ƕ��� ����
		PirateMonster* PirateMonster1 = object::Instantiate<PirateMonster>(eLayerType::Monster);
		PirateMonster1->GetComponent<Transform>()->SetPosition(Vector2(255.0f, 15.0f));
		PirateMonster* PirateMonster2 = object::Instantiate<PirateMonster>(eLayerType::Monster);
		PirateMonster2->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 300.0f));
		PirateMonster* PirateMonster3 = object::Instantiate<PirateMonster>(eLayerType::Monster);
		PirateMonster3->GetComponent<Transform>()->SetPosition(Vector2(280.0f, 400.0f));
		PirateMonster* PirateMonster4 = object::Instantiate<PirateMonster>(eLayerType::Monster);
		PirateMonster4->GetComponent<Transform>()->SetPosition(Vector2(180.0f, 300.0f));

		// ��ġ ���� �ʿ�
		/*PirateMonster* PirateMonster5 = object::Instantiate<PirateMonster>(eLayerType::Monster);
		PirateMonster5->GetComponent<Transform>()->SetPosition(Vector2(600.f, 550.0f));*/

	}

	void PirateMap2::Exit()
	{
		Resources::Find<Sound>(L"Play")->Stop(true);

		PirateBazzi->ResetBazzi();
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetBazziClick() == true)
		{
			Destroy(PirateBazzi);
		}

		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetDaoClick() == true && Initflag == false)
		{
			Destroy(PirateDao);
		}


	}

	void PirateMap2::Initialize()
	{
		Scene::Initialize();
		// ���� ����
		Resources::Load<Sound>(L"Play", L"..\\Resources\\Sound\\Sound\\Map\\bg_0.wav");
		Resources::Load<Sound>(L"Click", L"..\\Resources\\Sound\\Sound\\click.wav");

		// ���� Ʋ
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


		// �÷��̾�� ���Ͱ� �浹(�浹 ���� ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
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
			Initflag = false;

			SceneManager::LoadScene(L"LobbyScene");
		}

		if (Input::GetKeyDown(eKeyCode::N))
		{
			Initflag = false;

			SceneManager::LoadScene(L"PirateMap3");
		}

		// �¸�
		if (SceneManager::GetMonsterQuantity() == 0)
		{
			Win();
			PirateBazzi->Victory();
			SceneManager::SetMonsterQuantity(1);
		}


		// �й�
		if (SceneManager::GetMonsterQuantity() != 0 && SceneManager::GetPlayerDead() == true)
		{
			Lose();
			SceneManager::SetPlayerDead(false);
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

	void PirateMap2::Win()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* win = object::Instantiate< Win_Lose>(eLayerType::UI);
		win->Win();
		Transform* wintr = win->GetComponent<Transform>();
		wintr->SetPosition(Vector2(350.0f, 254.0f));

		if (Win_Lose::GetWin_Lose_flag() == true)
		{
			SceneManager::LoadScene(L"PirateMap3");
			Win_Lose::SetWin_Lose_flag(false);
		}
	}

	void PirateMap2::Lose()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* lose = object::Instantiate< Win_Lose>(eLayerType::UI);
		lose->Lose();
		Transform* losetr = lose->GetComponent<Transform>();
		losetr->SetPosition(Vector2(350.0f, 254.0f));
	}
}
