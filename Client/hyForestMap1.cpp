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


// 타일 위치 30,55에 넣기

extern hy::Application application;
namespace hy
{
	ForestMap1::ForestMap1()
	{
	}
	ForestMap1::~ForestMap1()
	{
	}

	void ForestMap1::Load()
	{
		Texture* forestFloor
			= Resources::Load<Texture>(L"ForestFloorTile", L"..\\resources\\image\\Bg\\ForestTile.bmp");

		//OPENFILENAME ofn = {};

		//wchar_t szFilePath[256] = {};

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

		//// rb : 이진수로 파일을 읽음
		//FILE* pFile = nullptr;
		//_wfopen_s(&pFile, szFilePath, L"rb");

		//if (pFile == nullptr)
		//	return;

		//while (true)
		//{
		//	int sourceX = -1;
		//	int sourceY = -1;

		//	int	myX = -1;
		//	int myY = -1;

		//	if (fread(&sourceX, sizeof(int), 1, pFile) == NULL)
		//		break;
		//	if (fread(&sourceY, sizeof(int), 1, pFile) == NULL)
		//		break;
		//	if (fread(&myX, sizeof(int), 1, pFile) == NULL)
		//		break;
		//	if (fread(&myY, sizeof(int), 1, pFile) == NULL)
		//		break;

		//	Vector2 offset = Vector2((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f);
		//	Tile* tile = object::Instantiate<Tile>(eLayerType::Tile
		//		, Vector2(myX * (TILE_WIDTH ) + offset.x
		//			, myY * (TILE_HEIGHT) + offset.y));
		//	
		//	tile->SetTile(sourceX, sourceY);
		//	tile->SetSourceTileIdx(sourceX, sourceY);
		//	tile->SetTileIdx(myX, myY);
		//}
	}

	void ForestMap1::Initialize()
	{
		// 게임 틀
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.f, 1.f));
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));	

		// 각 맵에 따른 맵 화면
		/*Texture* ForestMap1 = Resources::Load<Texture>(L"ForestMapImage"
			, L"..\\Resources\\Image\\Bg\\ForestTile.bmp");
		BackGround* forestmap1 = object::Instantiate<BackGround>(eLayerType::Background);
		forestmap1->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 402.0f));
		SpriteRenderer* forestmapsr= forestmap1->AddComponent<SpriteRenderer>();
		forestmapsr->SetImage(ForestMap1);
		forestmapsr->SetScale(Vector2(1.0f, 0.90f));*/

		// Load();

		// 배찌 프로필
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		// 배찌 상하좌우 애니메이션
		Bazzi* forestbazzi1 = object::Instantiate<Bazzi>(eLayerType::Player);
		Transform* forestbazzitr = forestbazzi1->GetComponent<Transform>();
		forestbazzitr->SetPosition(Vector2(60.0f, 70.0f));

		// 포레스트 몬스터
		ForestMonster* forestmonster = object::Instantiate<ForestMonster>(eLayerType::Monster);
		forestmonster->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 70.0f));

		// 충돌 구현
		Collider* col = forestbazzi1->AddComponent<Collider>();
		// 배찌의 충돌 사각형 사이즈 수정
		col->SetSize(Vector2(30.0f, 20.0f));
		col->SetOffset(Vector2(0.0f, 25.0f));

		col = forestmonster->AddComponent<Collider>();
		// 포레스트 몬스터의 충돌 사각형 사이즈 수정
		col->SetSize(Vector2(30.0f, 40.0f));
		//col->SetOffset(Vector2(10.0f, 10.0f));
		forestbazzitr = forestmonster->GetComponent<Transform>();

		forestbazzitr->SetPosition(Vector2(100.0f, 100.0f));

		// 플레이어와 몬스터가 충돌(충돌 관계)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// Balloon 아이템 setting
		Balloon* Balloon_1 = object::Instantiate<Balloon>(eLayerType::Item);
		Transform* Balloontr = Balloon_1->GetComponent<Transform>();
		Vector2 Balloonpos = Balloontr->GetPosition();

		Balloonpos.y = 150.f;
		Balloonpos.x = 150.f;

		Balloon_1->GetComponent<Transform>()->SetPosition(Balloonpos);

		// 물풍선 아이템 충돌 구현
		Collider* Ballooncol = Balloon_1->AddComponent<Collider>();
		// 물풍선 아이템 충돌 사각형 사이즈 수정
		Ballooncol->SetSize(Vector2(10.0f, 10.0f));

		// 플레이어와 물풍선 아이템 충돌(충돌 관계)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);

		// Devil 아이템 setting
		Devil* Devil_1 = object::Instantiate<Devil>(eLayerType::Item);
		Transform* Deviltr = Devil_1->GetComponent<Transform>();
		Vector2 Devilpos = Deviltr->GetPosition();

		Devilpos.y = 400.f;
		Devilpos.x = 400.f;

		Devil_1->GetComponent<Transform>()->SetPosition(Devilpos);

		// Devil 아이템 충돌 구현
		Collider* Devilcol = Devil_1->AddComponent<Collider>();
		// Devil 아이템 충돌 사각형 사이즈 수정
		Devilcol->SetSize(Vector2(10.0f, 10.0f));
		Devilcol->SetOffset(Vector2(0.0f, 0.0f));
		Scene::Initialize();
	}

	void ForestMap1::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			SceneManager::LoadScene(L"IceMap");
		}
	}
	void ForestMap1::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
}
