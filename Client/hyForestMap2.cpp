#include "hyForestMap2.h"
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
#include "hyWin_Lose.h"
#include "hyGameStart.h"
#include "hyLobbyScene.h"



// Ÿ�� ��ġ 30,55�� �ֱ�

extern hy::Application application;

namespace hy
{

	ForestMap2::ForestMap2()
	{
	}
	ForestMap2::~ForestMap2()
	{
	}

	void ForestMap2::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = L"..\\Resources\\Tile\\ForestMap_2.tm";

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

			tile->SetTile(sourceX, sourceY);
			// Crack(�μ����� �浹ü�� �ִ� Ÿ��)
			if ((sourceX == 0 && sourceY == 0) ||
				(sourceX == 1 && sourceY == 0) ||
				(sourceX == 2 && sourceY == 0))
			{
				tile->SetType(Tile::eType::Crack);
			}
			// Uncrushable(�μ������� ������ �浹ü�� �ִ� Ÿ��)
			if ((sourceX == 0 && sourceY == 3) ||
				(sourceX == 1 && sourceY == 3))
			{
				tile->SetType(Tile::eType::Uncrushable);
			}
			// None(�浹ü�� ���� �ٴڰ��� Ÿ��)
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

	void ForestMap2::Enter()
	{
		Resources::Find<Sound>(L"Play")->Play(true);

		SceneManager::SetMonsterQuantity(5);
		SceneManager::SetActiveStage(1);

		GameStart* gs1 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(185.0f, 60.0f));
		GameStart* gs2 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(450.0f, 640.0f));

	
		// ���� �����¿� �ִϸ��̼�
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetBazziClick() == true && Initflag == false)
		{
			ForestBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = ForestBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(60.0f, 70.0f));
			Initflag = true;

		}

		// �ٿ� �����¿� �ִϸ��̼�
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetDaoClick() == true && Initflag == false)
		{
			ForestDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = ForestDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(60.0f, 70.0f));
			Initflag = true;

		}

		// ��Ƽ �÷��̾� ����
		if (SceneManager::GetSelectMultiPlayer() == 1 && Initflag == false)
		{
			ForestBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = ForestBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(380.0f, 250.0f));

			ForestDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = ForestDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(480.0f, 250.0f));

			Initflag = true;
		}

	}

	void ForestMap2::Exit()
	{
		Resources::Find<Sound>(L"Play")->Stop(true);

		ForestBazzi->ResetBazzi();

	}

	void ForestMap2::Initialize()
	{
		Scene::Initialize();

		// ���� ����
		Resources::Load<Sound>(L"Play", L"..\\Resources\\Sound\\Sound\\Map\\bg_0.wav");
		Resources::Load<Sound>(L"Click", L"..\\Resources\\Sound\\Sound\\click.wav");


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

		ForestMap2::Load();

		// ���� ������
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::UI);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		

		// ������Ʈ ����
		ForestMonster* ForestMonster1 = object::Instantiate<ForestMonster>(eLayerType::Monster);
		ForestMonster1->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 70.0f));
		ForestMonster* ForestMonster2 = object::Instantiate<ForestMonster>(eLayerType::Monster);
		ForestMonster2->GetComponent<Transform>()->SetPosition(Vector2(325.0f, 310.0f));
		ForestMonster* ForestMonster3 = object::Instantiate<ForestMonster>(eLayerType::Monster);
		ForestMonster3->GetComponent<Transform>()->SetPosition(Vector2(425.0f, 530.0f));
		ForestMonster* ForestMonster4 = object::Instantiate<ForestMonster>(eLayerType::Monster);
		ForestMonster4->GetComponent<Transform>()->SetPosition(Vector2(470.0f, 280.0f));
		ForestMonster* ForestMonster5 = object::Instantiate<ForestMonster>(eLayerType::Monster);
		ForestMonster5->GetComponent<Transform>()->SetPosition(Vector2(590.0f, 240.0f));


		// �÷��̾�� ���Ͱ� �浹(�浹 ���� ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UseItem, true);

	}

	void ForestMap2::Update()
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
			Resources::Find<Sound>(L"Play")->Stop(true);
			Initflag = false;

			SceneManager::LoadScene(L"ForestMap3");
		}

		// �¸�
		if (SceneManager::GetMonsterQuantity() == 0)
		{
			Win();
			ForestBazzi->Victory();
			SceneManager::SetMonsterQuantity(1);
		}


		// �й�
		if (SceneManager::GetMonsterQuantity() != 0 && SceneManager::GetPlayerDead() == true)
		{
			Lose();
			SceneManager::SetPlayerDead(false);
		}


	}
	void ForestMap2::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	Tile* ForestMap2::GetTile(UINT x, UINT y)
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

	void ForestMap2::Win()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* win = object::Instantiate< Win_Lose>(eLayerType::UI);
		win->Win();
		Transform* wintr = win->GetComponent<Transform>();
		wintr->SetPosition(Vector2(350.0f, 254.0f));

		if (Win_Lose::GetWin_Lose_flag() == true)
		{
			SceneManager::LoadScene(L"ForestMap3");
			Win_Lose::SetWin_Lose_flag(false);
		}
	}

	void ForestMap2::Lose()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* lose = object::Instantiate< Win_Lose>(eLayerType::UI);
		lose->Lose();
		Transform* losetr = lose->GetComponent<Transform>();
		losetr->SetPosition(Vector2(350.0f, 254.0f));
	}
}
