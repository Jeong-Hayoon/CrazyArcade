#include "hyForestMap3.h"
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
#include "hyForestBoss.h"
#include "hyWin_Lose.h"
#include "hyGameStart.h"
#include "hyLobbyScene.h"



// 타일 위치 30,55에 넣기

extern hy::Application application;

namespace hy
{

	ForestMap3::ForestMap3()
		:Initflag(false)

	{
	}
	ForestMap3::~ForestMap3()
	{
	}

	void ForestMap3::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = L"..\\Resources\\Tile\\ForestMap_3.tm";

	
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

	void ForestMap3::Enter()
	{
		Resources::Find<Sound>(L"BossStage")->Play(true);
		SceneManager::SetBossQuantity(1);
		SceneManager::SetActiveStage(2);

		GameStart* gs1 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(185.0f, 60.0f));
		GameStart* gs2 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(450.0f, 640.0f));

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


		// 배찌 상하좌우 애니메이션
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetBazziClick() == true && Initflag == false)
		{
			SceneManager::SetPlayerNum(1);

			ForestBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = ForestBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(60.0f, 70.0f));
			SceneManager::SetBazzi(ForestBazzi);

			Initflag = true;

			// 배찌 프로필
			Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
				, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

			BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::UI);
			bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
			SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
			bzprofilesr->SetImage(BZProfile);
			bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		}
	
		// 다오 상하좌우 애니메이션
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetDaoClick() == true && Initflag == false)
		{
			SceneManager::SetPlayerNum(1);

			ForestDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = ForestDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(60.0f, 70.0f));
			Initflag = true;
			SceneManager::SetDao(ForestDao);

			// 다오 프로필
			Texture* DAProfile = Resources::Load<Texture>(L"DAProfileImage"
				, L"..\\Resources\\Image\\UI\\IngameDao.bmp");

			BackGround* daprofile = object::Instantiate<BackGround>(eLayerType::UI);
			daprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
			SpriteRenderer* daprofilesr = daprofile->AddComponent<SpriteRenderer>();
			daprofilesr->SetImage(DAProfile);
			daprofilesr->SetScale(Vector2(0.6f, 0.6f));
		}

		// 멀티 플레이어 세팅
		if (SceneManager::GetSelectMultiPlayer() == 1 && Initflag == false)
		{
			SceneManager::SetPlayerNum(2);

			ForestBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = ForestBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(35.0f, 70.0f));

			ForestDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = ForestDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(580.0f, 70.0f));

			SceneManager::SetBazzi(ForestBazzi);
			SceneManager::SetDao(ForestDao);

			Initflag = true;
		}


		// 포레스트 보스
		ForestBoss* ForestBoss_ = object::Instantiate<ForestBoss>(eLayerType::Boss);
		ForestBoss_->GetComponent<Transform>()->SetPosition(Vector2(250.0f, 300.0f));
	}

	void ForestMap3::Exit()
	{
		Resources::Find<Sound>(L"BossStage")->Stop(true);

		ForestBazzi->ResetBazzi();
		ForestDao->ResetDao();

		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetBazziClick() == true)
		{
			Destroy(ForestBazzi);
		}

		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetDaoClick() == true)
		{
			Destroy(ForestDao);
		}
		Initflag = false;
		SceneManager::SetItemOn(false);
		SceneManager::SetNeedleGet(false);
		SceneManager::SetShieldGet(false);
		SceneManager::SetItemUse(false);
	}

	void ForestMap3::Initialize()
	{
		Scene::Initialize();
		// 사운드 적용
		Resources::Load<Sound>(L"BossStage", L"..\\Resources\\Sound\\Sound\\Map\\Boss.wav");
		Resources::Load<Sound>(L"Click", L"..\\Resources\\Sound\\Sound\\click.wav");

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

		ForestMap3::Load();

		mItemUI = object::Instantiate<ItemUI>(eLayerType::UI);


	}

	void ForestMap3::Update()
	{
		Scene::Update();

		if (SceneManager::GetNeedleGet() == true)
		{
			SceneManager::SetItemOn(true);
			mItemUI->GetComponent<Transform>()->SetPosition(Vector2(690.0f, 510.0f));
			mItemUI->GetComponent<Animator>()->PlayAnimation(L"NeedleUI", true);
		}

		if (SceneManager::GetShieldGet() == true)
		{
			SceneManager::SetItemOn(true);
			mItemUI->GetComponent<Transform>()->SetPosition(Vector2(690.0f, 510.0f));
			mItemUI->GetComponent<Animator>()->PlayAnimation(L"ShieldUI", true);
		}

		// 아이템 창고에 아이템이 있으면서 아이템을 사용한 경우
		if (SceneManager::GetItemOn() == true && SceneManager::GetItemUse() == true)
		{
			if (SceneManager::GetNeedleGet() == false || SceneManager::GetShieldGet() == false)
			{
				mItemUI->GetComponent<Transform>()->SetPosition(Vector2(690.0f, 510.0f));
				mItemUI->GetComponent<Animator>()->PlayAnimation(L"NoneUI", true);
				SceneManager::SetItemOn(false);
				SceneManager::SetItemUse(false);
			}
		}


		if (Input::GetKeyDown(eKeyCode::MouseLeft))
		{
			Resources::Find<Sound>(L"Click")->Play(false);
		}

		Vector2 temp = Input::GetMousePosition();

		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 560 && temp.y <= 590 && temp.x >= 645 && temp.x <= 785)
		{
			Resources::Find<Sound>(L"BossStage")->Stop(true);
			SceneManager::LoadScene(L"LobbyScene");
			Initflag = false;

		}

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"IceMap1");
			Initflag = false;

		}

		// 승리
		if (SceneManager::GetBossQuantity() == 0)
		{
			Win();
			if (SceneManager::GetDao() != nullptr)
			{
				ForestDao->Victory();

			}
			if (SceneManager::GetBazzi() != nullptr)
			{
				ForestBazzi->Victory();
			}
			SceneManager::SetBossQuantity(1);
		}


		// 패배
		if (SceneManager::GetBossQuantity() != 0 && SceneManager::GetPlayerDead() == true && SceneManager::GetPlayerNum() == 0)
		{
			Lose();
			SceneManager::SetPlayerDead(false);
		}

	}
	void ForestMap3::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	Tile* ForestMap3::GetTile(UINT x, UINT y)
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

	void ForestMap3::Win()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* win = object::Instantiate< Win_Lose>(eLayerType::UI);
		win->Win();
		Transform* wintr = win->GetComponent<Transform>();
		wintr->SetPosition(Vector2(350.0f, 254.0f));

		if (Win_Lose::GetWin_Lose_flag() == true)
		{
			SceneManager::LoadScene(L"LobbyScene");
			Win_Lose::SetWin_Lose_flag(false);
		}
	}

	void ForestMap3::Lose()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* lose = object::Instantiate< Win_Lose>(eLayerType::UI);
		lose->Lose();
		Transform* losetr = lose->GetComponent<Transform>();
		losetr->SetPosition(Vector2(350.0f, 254.0f));
	}
}
