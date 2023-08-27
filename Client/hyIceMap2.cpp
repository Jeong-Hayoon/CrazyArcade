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


// Ÿ�� ��ġ 30,55�� �ֱ�

extern hy::Application application;

namespace hy
{

	IceMap2::IceMap2()
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

		SceneManager::SetBossQuantity(8);
		GameStart* gs1 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(185.0f, 60.0f));
		GameStart* gs2 = object::Instantiate<GameStart>(eLayerType::UI, Vector2(450.0f, 640.0f));

	}

	void IceMap2::Exit()
	{
		IceBazzi->ResetBazzi();
	}

	void IceMap2::Initialize()
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

		IceMap2::Load();

		// ���� ������
		Texture* BZProfile = Resources::Load<Texture>(L"BZProfileImage"
			, L"..\\Resources\\Image\\UI\\IngameBazzi.bmp");

		BackGround* bzprofile = object::Instantiate<BackGround>(eLayerType::UI);
		bzprofile->GetComponent<Transform>()->SetPosition(Vector2(682.0f, 118.0f));
		SpriteRenderer* bzprofilesr = bzprofile->AddComponent<SpriteRenderer>();
		bzprofilesr->SetImage(BZProfile);
		bzprofilesr->SetScale(Vector2(0.6f, 0.6f));

		// ���� �����¿� �ִϸ��̼�
		IceBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
		Transform* forestbazzitr = IceBazzi->GetComponent<Transform>();
		forestbazzitr->SetPosition(Vector2(350.0f, 200.0f));

		// ������Ʈ ����
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

		// �÷��̾�� ���Ͱ� �浹(�浹 ���� ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Item, true);

		// �÷��̾�� ��ǳ�� ������ �浹(�浹 ����)
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::UseItem, true);

	}

	void IceMap2::Update()
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
			SceneManager::LoadScene(L"IceMap3");
		}


	}
	void IceMap2::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
}
