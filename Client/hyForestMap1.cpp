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


// Ÿ�� ��ġ 30,55�� �ֱ�

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

		//// rb : �������� ������ ����
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
		// ���� Ʋ
		Texture* image = Resources::Load<Texture>(L"PlayBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\play.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.f, 1.f));
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));	

		// �� �ʿ� ���� �� ȭ��
		/*Texture* ForestMap1 = Resources::Load<Texture>(L"ForestMapImage"
			, L"..\\Resources\\Image\\Bg\\ForestTile.bmp");
		BackGround* forestmap1 = object::Instantiate<BackGround>(eLayerType::Background);
		forestmap1->GetComponent<Transform>()->SetPosition(Vector2(480.0f, 402.0f));
		SpriteRenderer* forestmapsr= forestmap1->AddComponent<SpriteRenderer>();
		forestmapsr->SetImage(ForestMap1);
		forestmapsr->SetScale(Vector2(1.0f, 0.90f));*/

		// Load();

		// ���� ������
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::Background);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		// ���� �����¿� �ִϸ��̼�
		Bazzi* forestbazzi1 = object::Instantiate<Bazzi>(eLayerType::Player);
		Transform* forestbazzitr = forestbazzi1->GetComponent<Transform>();
		forestbazzitr->SetPosition(Vector2(60.0f, 70.0f));

		// ������Ʈ ����
		ForestMonster* forestmonster = object::Instantiate<ForestMonster>(eLayerType::Monster);
		forestmonster->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 70.0f));

		// �浹 ����
		Collider* col = forestbazzi1->AddComponent<Collider>();
		// ������ �浹 �簢�� ������ ����
		col->SetSize(Vector2(30.0f, 20.0f));
		col->SetOffset(Vector2(0.0f, 25.0f));

		col = forestmonster->AddComponent<Collider>();
		// ������Ʈ ������ �浹 �簢�� ������ ����
		col->SetSize(Vector2(30.0f, 40.0f));
		//col->SetOffset(Vector2(10.0f, 10.0f));
		forestbazzitr = forestmonster->GetComponent<Transform>();

		forestbazzitr->SetPosition(Vector2(100.0f, 100.0f));

		// �÷��̾�� ���Ͱ� �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// Balloon ������ setting
		Balloon* Balloon_1 = object::Instantiate<Balloon>(eLayerType::Item);
		Transform* Balloontr = Balloon_1->GetComponent<Transform>();
		Vector2 Balloonpos = Balloontr->GetPosition();

		Balloonpos.y = 150.f;
		Balloonpos.x = 150.f;

		Balloon_1->GetComponent<Transform>()->SetPosition(Balloonpos);

		// ��ǳ�� ������ �浹 ����
		Collider* Ballooncol = Balloon_1->AddComponent<Collider>();
		// ��ǳ�� ������ �浹 �簢�� ������ ����
		Ballooncol->SetSize(Vector2(10.0f, 10.0f));

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);

		// Devil ������ setting
		Devil* Devil_1 = object::Instantiate<Devil>(eLayerType::Item);
		Transform* Deviltr = Devil_1->GetComponent<Transform>();
		Vector2 Devilpos = Deviltr->GetPosition();

		Devilpos.y = 400.f;
		Devilpos.x = 400.f;

		Devil_1->GetComponent<Transform>()->SetPosition(Devilpos);

		// Devil ������ �浹 ����
		Collider* Devilcol = Devil_1->AddComponent<Collider>();
		// Devil ������ �浹 �簢�� ������ ����
		Devilcol->SetSize(Vector2(10.0f, 10.0f));
		Devilcol->SetOffset(Vector2(0.0f, 0.0f));
		Scene::Initialize();
	}

	void ForestMap1::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N�� ������ ���� ������ �Ѿ��
		{
			SceneManager::LoadScene(L"IceMap");
		}
	}
	void ForestMap1::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
}
