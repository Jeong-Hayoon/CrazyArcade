#include "hyPirateMap1.h"
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



// 타일 위치 30,55에 넣기

extern hy::Application application;

namespace hy
{
	UINT PirateMap1::MonsterQuantity = 1;

	PirateMap1::PirateMap1()
	{
	}
	PirateMap1::~PirateMap1()
	{
	}

	void PirateMap1::Load()
	{
		/*	Texture* forestFloor
				= Resources::Load<Texture>(L"ForestFloorTile", L"..\\resources\\image\\Bg\\ForestTile.bmp");*/

		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = L"..\\Resources\\Tile\\PirateMap_1.tm";

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
			tile->SetSourceTileIdx(sourceX, sourceY);
			tile->SetTileIdx(myX, myY);

			mTiles.push_back(tile);
		}
		fclose(pFile);
	}

	void PirateMap1::Enter()
	{
		Resources::Find<Sound>(L"Play")->Play(true);


	}

	void PirateMap1::Exit()
	{
	}

	void PirateMap1::Initialize()
	{
		Scene::Initialize();
		// 사운드 적용
		Resources::Load<Sound>(L"Play", L"..\\Resources\\Sound\\Sound\\Map\\bg_0.wav");

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

		PirateMap1::Load();

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::UI);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		// 배찌 상하좌우 애니메이션
		Bazzi* forestbazzi1 = object::Instantiate<Bazzi>(eLayerType::Player);
		Transform* forestbazzitr = forestbazzi1->GetComponent<Transform>();
		forestbazzitr->SetPosition(Vector2(60.0f, 70.0f));

		// 포레스트 몬스터
		ForestMonster_1* ForestMonster1 = object::Instantiate<ForestMonster_1>(eLayerType::Monster);
		ForestMonster1->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 70.0f));

		// 배찌 충돌 구현
		Collider* col = forestbazzi1->AddComponent<Collider>();
		// 배찌의 충돌 사각형 사이즈 수정
		col->SetSize(Vector2(30.0f, 25.0f));
		col->SetOffset(Vector2(0.0f, 10.0f));
		forestbazzitr->SetPosition(Vector2(100.0f, 100.0f));


		// 포레스트 몬스터의 충돌 사각형 사이즈 수정
		col = ForestMonster1->AddComponent<Collider>();
		col->SetSize(Vector2(30.0f, 40.0f));

		// 플레이어와 몬스터가 충돌(충돌 관계 지정)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// Balloon 아이템 setting
		Balloon* Balloon_1 = object::Instantiate<Balloon>(eLayerType::Item);
		Transform* Balloontr = Balloon_1->GetComponent<Transform>();
		Vector2 Balloonpos = Balloontr->GetPosition();

		Balloonpos.y = 250.f;
		Balloonpos.x = 150.f;

		Balloon_1->GetComponent<Transform>()->SetPosition(Balloonpos);

		// Balloon 아이템 충돌 구현
		Collider* Ballooncol = Balloon_1->AddComponent<Collider>();
		// Balloon 아이템 충돌 사각형 사이즈 수정
		Ballooncol->SetSize(Vector2(10.0f, 30.0f));

		// 플레이어와 물풍선 아이템 충돌(충돌 관계)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);

		// 플레이어와 물풍선 아이템 충돌(충돌 관계)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UseItem, true);

		// Devil 아이템 setting
		Devil* Devil_1 = object::Instantiate<Devil>(eLayerType::Item);
		Transform* Deviltr = Devil_1->GetComponent<Transform>();
		Vector2 Devilpos = Deviltr->GetPosition();

		Devilpos.y = 250.f;
		Devilpos.x = 250.f;

		Devil_1->GetComponent<Transform>()->SetPosition(Devilpos);

		// Devil 아이템 충돌 구현
		Collider* Devilcol = Devil_1->AddComponent<Collider>();
		// Devil 아이템 충돌 사각형 사이즈 수정
		Devilcol->SetSize(Vector2(10.0f, 30.0f));
		Devilcol->SetOffset(Vector2(0.0f, 0.0f));

		// Potion 아이템 setting
		Potion* Potion_1 = object::Instantiate<Potion>(eLayerType::Item);
		Transform* Potiontr = Potion_1->GetComponent<Transform>();
		Vector2 Potionpos = Potiontr->GetPosition();

		Potionpos.y = 250.f;
		Potionpos.x = 350.f;

		Potion_1->GetComponent<Transform>()->SetPosition(Potionpos);

		// Potion 아이템 충돌 구현
		Collider* Potioncol = Potion_1->AddComponent<Collider>();
		// Potion 아이템 충돌 사각형 사이즈 수정
		Potioncol->SetSize(Vector2(10.0f, 30.0f));
		Potioncol->SetOffset(Vector2(0.0f, 0.0f));

		// Shield 아이템 setting
		Shield* Shield_1 = object::Instantiate<Shield>(eLayerType::UseItem);
		Transform* Shieldtr = Shield_1->GetComponent<Transform>();
		Vector2 Shieldnpos = Shieldtr->GetPosition();

		Shieldnpos.y = 250.f;
		Shieldnpos.x = 450.f;

		Shield_1->GetComponent<Transform>()->SetPosition(Shieldnpos);

		// Shield 아이템 충돌 구현
		Collider* Shieldcol = Shield_1->AddComponent<Collider>();
		// Shield 아이템 충돌 사각형 사이즈 수정
		Shieldcol->SetSize(Vector2(10.0f, 30.0f));
		Shieldcol->SetOffset(Vector2(0.0f, 0.0f));


		// Needle 아이템 setting
		Needle* Needle_1 = object::Instantiate<Needle>(eLayerType::UseItem);
		Transform* Needletr = Needle_1->GetComponent<Transform>();
		Vector2 Needlepos = Needletr->GetPosition();

		Needlepos.y = 250.f;
		Needlepos.x = 550.f;

		Needle_1->GetComponent<Transform>()->SetPosition(Needlepos);

		// Needle 아이템 충돌 구현
		Collider* Needlecol = Needle_1->AddComponent<Collider>();
		// Needle 아이템 충돌 사각형 사이즈 수정
		Needlecol->SetSize(Vector2(10.0f, 30.0f));
		Needlecol->SetOffset(Vector2(0.0f, 0.0f));

	}

	void PirateMap1::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			Resources::Find<Sound>(L"LoginSound")->Stop(1);

			SceneManager::LoadScene(L"PirateMap2");
		}


	}
	void PirateMap1::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
}
