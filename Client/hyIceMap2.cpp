#include "hyIceMap2.h"
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
#include "hyIceMonster.h"
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

	IceMap2::IceMap2()
		:Initflag(false)

	{
	}
	IceMap2::~IceMap2()
	{
	}

	void IceMap2::Load()
	{
		
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = L"..\\Resources\\Tile\\IceMap_2.tm";

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
			if ((sourceX == 3 && sourceY == 2) ||
				(sourceX == 4 && sourceY == 2))
			{
				tile->SetType(Tile::eType::Crack);
			}
			// Uncrushable(�μ������� ������ �浹ü�� �ִ� Ÿ��)
			if ((sourceX == 2 && sourceY == 1) ||
				(sourceX == 1 && sourceY == 2) ||
				(sourceX == 2 && sourceY == 2))
			{
				tile->SetType(Tile::eType::Uncrushable);
			}
			// None(�浹ü�� ���� �ٴڰ��� Ÿ��)
			if ((sourceX == 1 && sourceY == 1))
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

	void IceMap2::Enter()
	{
		Resources::Find<Sound>(L"Play")->Play(true);

		SceneManager::SetMonsterQuantity(8);
		SceneManager::SetActiveStage(4);

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
			SceneManager::SetPlayerNum(1);

			IceBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = IceBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(350.0f, 200.0f));
			SceneManager::SetBazzi(IceBazzi);

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
			SceneManager::SetPlayerNum(1);

			IceDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = IceDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(350.0f, 200.0f));
			Initflag = true;
			SceneManager::SetDao(IceDao);

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
			SceneManager::SetPlayerNum(2);

			IceBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
			Transform* forestbazzitr = IceBazzi->GetComponent<Transform>();
			forestbazzitr->SetPosition(Vector2(380.0f, 250.0f));

			IceDao = object::Instantiate<Dao>(eLayerType::Player);
			Transform* forestdaotr = IceDao->GetComponent<Transform>();
			forestdaotr->SetPosition(Vector2(280.0f, 250.0f));

			SceneManager::SetBazzi(IceBazzi);
			SceneManager::SetDao(IceDao);

			Initflag = true;
		}

		// ���̽� ����
		IceMonster* IceMonster1 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster1->GetComponent<Transform>()->SetPosition(Vector2(40.0f, 70.0f));
		IceMonster* IceMonster2 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster2->GetComponent<Transform>()->SetPosition(Vector2(310.0f, 70.0f));
		IceMonster* IceMonster3 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster3->GetComponent<Transform>()->SetPosition(Vector2(560.0f, 70.0f));
		IceMonster* IceMonster4 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster4->GetComponent<Transform>()->SetPosition(Vector2(40.0f, 555.0f));

		/*IceMonster* IceMonster5 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster5->GetComponent<Transform>()->SetPosition(Vector2(350.0f, 565.0f));*/

		/*IceMonster* IceMonster6 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster6->GetComponent<Transform>()->SetPosition(Vector2(560.0f, 595.0f));*/

		IceMonster* IceMonster7 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster7->GetComponent<Transform>()->SetPosition(Vector2(125.0f, 175.0f));
		IceMonster* IceMonster8 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster8->GetComponent<Transform>()->SetPosition(Vector2(525.0f, 175.0f));
		IceMonster* IceMonster9 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster9->GetComponent<Transform>()->SetPosition(Vector2(125.0f, 495.0f));
		IceMonster* IceMonster10 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster10->GetComponent<Transform>()->SetPosition(Vector2(525.0f, 495.0f));
		/*IceMonster* IceMonster11 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster11->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 255.0f));
		IceMonster* IceMonster12 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster12->GetComponent<Transform>()->SetPosition(Vector2(445.0f, 255.0f));
		IceMonster* IceMonster13 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster13->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 420.0f));
		IceMonster* IceMonster14 = object::Instantiate<IceMonster>(eLayerType::Monster);
		IceMonster14->GetComponent<Transform>()->SetPosition(Vector2(445.0f, 420.0f));*/

	}

	void IceMap2::Exit()
	{
		Resources::Find<Sound>(L"Play")->Stop(true);

		IceBazzi->ResetBazzi();
		IceDao->ResetDao();
		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetBazziClick() == true)
		{
			Destroy(IceBazzi);
		}

		if (SceneManager::GetSelectSoloPlayer() == 1 && LobbyScene::GetDaoClick() == true )
		{
			Destroy(IceDao);
		}
		Initflag = false;
		SceneManager::SetItemOn(false);
		SceneManager::SetNeedleGet(false);
		SceneManager::SetShieldGet(false);
		SceneManager::SetItemUse(false);
	}

	void IceMap2::Initialize()
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

		IceMap2::Load();

		// �÷��̾�� ���Ͱ� �浹(�浹 ���� ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UseItem, true);

		mItemUI = object::Instantiate<ItemUI>(eLayerType::UI);

	}

	void IceMap2::Update()
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
			mItemUI->GetComponent<Animator>()->PlayAnimation(L"NeedleUI", true);
		}

		// ������ â�� �������� �������鼭 �������� ����� ���
		if (SceneManager::GetItemOn() == true && SceneManager::GetItemUse() == true)
		{
			if (SceneManager::GetNeedleGet() == false || SceneManager::GetShieldGet() == false)
			{
				mItemUI->GetComponent<Transform>()->SetPosition(Vector2(690.0f, 510.0f));
				mItemUI->GetComponent<Animator>()->PlayAnimation(L"NoneUI", true);
				SceneManager::SetItemOn(false);
			}
		}


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
			SceneManager::LoadScene(L"IceMap3");
			Initflag = false;

		}

		// �¸�
		if (SceneManager::GetMonsterQuantity() == 0)
		{
			Win();
			IceBazzi->Victory();
			SceneManager::SetMonsterQuantity(1);
		}


		// �й�
		if (SceneManager::GetMonsterQuantity() != 0 && SceneManager::GetPlayerDead() == true && SceneManager::GetPlayerNum() == 0)
		{
			Lose();
			SceneManager::SetPlayerDead(false);
		}


	}
	void IceMap2::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	Tile* IceMap2::GetTile(UINT x, UINT y)
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

	void IceMap2::Win()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* win = object::Instantiate< Win_Lose>(eLayerType::UI);
		win->Win();
		Transform* wintr = win->GetComponent<Transform>();
		wintr->SetPosition(Vector2(350.0f, 254.0f));

		if (Win_Lose::GetWin_Lose_flag() == true)
		{
			SceneManager::LoadScene(L"IceMap3");
			Win_Lose::SetWin_Lose_flag(false);
		}
	}

	void IceMap2::Lose()
	{
		Resources::Find<Sound>(L"Play")->Stop(1);

		Win_Lose* lose = object::Instantiate< Win_Lose>(eLayerType::UI);
		lose->Lose();
		Transform* losetr = lose->GetComponent<Transform>();
		losetr->SetPosition(Vector2(350.0f, 254.0f));
	}
}
