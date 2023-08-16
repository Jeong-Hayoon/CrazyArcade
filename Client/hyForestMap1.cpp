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
#include "hyForestMonster_1.h"
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


// Ÿ�� ��ġ 30,55�� �ֱ�

extern hy::Application application;

namespace hy
{
	UINT ForestMap1::MonsterQuantity = 1;
	bool ForestMap1::FunCheck = 0;

	ForestMap1::ForestMap1()
	{
	}
	ForestMap1::~ForestMap1()
	{
	}

	void ForestMap1::Enter()
	{
		Resources::Find<Sound>(L"Play")->Play(true);

	}

	void ForestMap1::Exit()
	{
	}

	void ForestMap1::Initialize()
	{
		Scene::Initialize();
		// ���� ����
		Resources::Load<Sound>(L"Play", L"..\\Resources\\Sound\\Sound\\Map\\bg_0.wav");

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

		// ���� Ʋ Collider ����
		Texture* GameFrameColObject = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\GameFrameObject.bmp");

		BackGround* gfco = object::Instantiate<BackGround>(eLayerType::Collider);
		SpriteRenderer* gfcosr = gfco->AddComponent<SpriteRenderer>();
		gfcosr->SetImage(image);
		gfcosr->SetScale(Vector2(1.f, 1.f));
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));

		// GameFrameColObject �浹 ����
		Collider* gfcocol = gfco->AddComponent<Collider>();
		// GameFrameColObject �浹 �簢�� ������ ����
		gfcocol->SetSize(Vector2(10.0f, 10.0f));

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Collider, true);

		Texture* Tile_
			= Resources::Load<Texture>(L"Tile", L"..\\Resources\\Image\\Map\\Tile.bmp");

		ForestMap1::Load();

		// ���� ������
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::UI);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		// ���� �����¿� �ִϸ��̼�
		Bazzi* forestbazzi1 = object::Instantiate<Bazzi>(eLayerType::Player);
		Transform* forestbazzitr = forestbazzi1->GetComponent<Transform>();
		forestbazzitr->SetPosition(Vector2(50.0f, 70.0f));

		// ������Ʈ ����
		ForestMonster_1* ForestMonster1 = object::Instantiate<ForestMonster_1>(eLayerType::Monster);
		ForestMonster1->GetComponent<Transform>()->SetPosition(Vector2(150.0f, 70.0f));

		// ���� �浹 ����
		Collider* col = forestbazzi1->AddComponent<Collider>();
		// ������ �浹 �簢�� ������ ����
		col->SetSize(Vector2(30.0f, 25.0f));
		col->SetOffset(Vector2(0.0f, 10.0f));
		forestbazzitr->SetPosition(Vector2(100.0f, 100.0f));

		// ������Ʈ ������ �浹 �簢�� ������ ����
		col = ForestMonster1->AddComponent<Collider>();
		col->SetSize(Vector2(30.0f, 40.0f));

		// �÷��̾�� ���Ͱ� �浹(�浹 ���� ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// Balloon ������ setting
		Balloon* Balloon_1 = object::Instantiate<Balloon>(eLayerType::Item);
		Transform* Balloontr = Balloon_1->GetComponent<Transform>();
		Vector2 Balloonpos = Balloontr->GetPosition();

		Balloonpos.y = 250.f;
		Balloonpos.x = 150.f;

		Balloon_1->GetComponent<Transform>()->SetPosition(Balloonpos);

		// Balloon ������ �浹 ����
		Collider* Ballooncol = Balloon_1->AddComponent<Collider>();
		// Balloon ������ �浹 �簢�� ������ ����
		Ballooncol->SetSize(Vector2(10.0f, 30.0f));

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UseItem, true);

		// Devil ������ setting
		Devil* Devil_1 = object::Instantiate<Devil>(eLayerType::Item);
		Transform* Deviltr = Devil_1->GetComponent<Transform>();
		Vector2 Devilpos = Deviltr->GetPosition();

		Devilpos.y = 250.f;
		Devilpos.x = 250.f;

		Devil_1->GetComponent<Transform>()->SetPosition(Devilpos);

		// Devil ������ �浹 ����
		Collider* Devilcol = Devil_1->AddComponent<Collider>();
		// Devil ������ �浹 �簢�� ������ ����
		Devilcol->SetSize(Vector2(10.0f, 30.0f));
		Devilcol->SetOffset(Vector2(0.0f, 0.0f));

		// Potion ������ setting
		Potion* Potion_1 = object::Instantiate<Potion>(eLayerType::Item);
		Transform* Potiontr = Potion_1->GetComponent<Transform>();
		Vector2 Potionpos = Potiontr->GetPosition();

		Potionpos.y = 250.f;
		Potionpos.x = 350.f;

		Potion_1->GetComponent<Transform>()->SetPosition(Potionpos);

		// Potion ������ �浹 ����
		Collider* Potioncol = Potion_1->AddComponent<Collider>();
		// Potion ������ �浹 �簢�� ������ ����
		Potioncol->SetSize(Vector2(10.0f, 30.0f));
		Potioncol->SetOffset(Vector2(0.0f, 0.0f));

		// Shield ������ setting
		Shield* Shield_1 = object::Instantiate<Shield>(eLayerType::UseItem);
		Transform* Shieldtr = Shield_1->GetComponent<Transform>();
		Vector2 Shieldnpos = Shieldtr->GetPosition();

		Shieldnpos.y = 250.f;
		Shieldnpos.x = 500.f;

		Shield_1->GetComponent<Transform>()->SetPosition(Shieldnpos);

		// Shield ������ �浹 ����
		Collider* Shieldcol = Shield_1->AddComponent<Collider>();
		// Shield ������ �浹 �簢�� ������ ����
		Shieldcol->SetSize(Vector2(10.0f, 30.0f));
		Shieldcol->SetOffset(Vector2(0.0f, 0.0f));


		// Needle ������ setting
		Needle* Needle_1 = object::Instantiate<Needle>(eLayerType::UseItem);
		Transform* Needletr = Needle_1->GetComponent<Transform>();
		Vector2 Needlepos = Needletr->GetPosition();

		Needlepos.y = 250.f;
		Needlepos.x = 575.f;

		Needle_1->GetComponent<Transform>()->SetPosition(Needlepos);

		// Needle ������ �浹 ����
		Collider* Needlecol = Needle_1->AddComponent<Collider>();
		// Needle ������ �浹 �簢�� ������ ����
		Needlecol->SetSize(Vector2(10.0f, 30.0f));
		Needlecol->SetOffset(Vector2(0.0f, 0.0f));

		//Scene::Initialize();
	}

	//void ForestMap1::Win()
	//{
	//	Resources::Find<Sound>(L"Win")->Play(false);

	//	Resources::Find<Sound>(L"Play")->Stop(1);


	//	// ���� Victory ���� ȣ��
	//}

	void ForestMap1::Update()
	{
		Scene::Update();

		//if (Input::GetKeyDown(eKeyCode::N)) // N�� ������ ���� ������ �Ѿ��
		//{
		//	Resources::Find<Sound>(L"Play")->Stop(1);

		//}

		if (MonsterQuantity == 0 && FunCheck == 1)
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
			FunCheck = 0;
		}

		//if (MonsterQuantity != 0 // && ���� ���°� Dead or BalloonDead ��� && FunCheck == 1)
		//{
		//	Lose();
		//	FunCheck = 0;
		//}


	}
	void ForestMap1::Render(HDC hdc)
	{
		Scene::Render(hdc);

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
				Col->SetSize(Vector2(30.0f, 30.0f));

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
