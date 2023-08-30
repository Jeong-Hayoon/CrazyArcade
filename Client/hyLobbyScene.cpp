#include "hyLobbyScene.h"
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
#include "hyBazzi.h"
#include "hyStagePick.h"



extern hy::Application application;
namespace hy
{
	bool LobbyScene :: BazziClick = false;
	bool LobbyScene :: DaoClick = false;

	LobbyScene::LobbyScene()
		: MapSelect(nullptr)
		, AlreadySeat(false)
	{
	}
	LobbyScene::~LobbyScene()
	{
	}
	void LobbyScene::Initialize()
	{
		Scene::Initialize();
		// 사운드 적용
		Resources::Load<Sound>(L"Click", L"..\\Resources\\Sound\\Sound\\click.wav");
		Resources::Load<Sound>(L"LobbySound", L"..\\Resources\\Sound\\Sound\\lobby_scene.wav");

		// 로비
		Texture* image = Resources::Load<Texture>(L"LobbyBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\Lobby.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.f, 1.f));
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));	// 배경을 해상도의 절반으로 세팅

		// 맵 선택(포레스트 맵)
		/*Texture* ForestMapSelect = Resources::Load<Texture>(L"ForestMapSelectImage"
			//, L"..\\Resources\\Image\\UI\\ForestRandom.bmp");

		BackGround* fms = object::Instantiate<BackGround>(eLayerType::Background);
		fms->GetComponent<Transform>()->SetPosition(Vector2(560.0f, 415.0f));
		SpriteRenderer* fmssr = fms->AddComponent<SpriteRenderer>();
		fmssr->SetImage(ForestMapSelect);
		fmssr->SetScale(Vector2(0.7f, 0.7f));*/

		//Sound* sound = Resources::Load<Sound>(L"bgSound", L"..\\Resources\\Sounds\\smw_bonus_game_end.wav");

		//if (Input::GetKeyDown(eKeyCode::Q))
		//{
		//	mbStart = true;
		//}

		//if (mbStart == false)
		//{
		//	sound->Play(true);
		//	mbStart = false;
		//}

	}
	void LobbyScene::Update()
	{
		Scene::Update();

		Vector2 temp = Input::GetMousePosition();

		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 210 && temp.y <= 245 && temp.x >= 635 && temp.x <= 695)
		{
			BazziClick = true;
			DaoClick = false;
		}
		else if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 210 && temp.y <= 245 && temp.x >= 490 && temp.x <= 550)
		{
			BazziClick = false;
			DaoClick = true;
		}

		// 1P - 캐릭터 선택
		if (SceneManager :: GetSelectSoloPlayer() == 1 && BazziClick == true)
		{
			// 캐릭터 세팅
			Texture* Bazzi = Resources::Load<Texture>(L"BazziImage"
				, L"..\\Resources\\Image\\Bazzi\\Idle.bmp");

			BackGround* Charactor = object::Instantiate<BackGround>(eLayerType::Background);
			Charactor->GetComponent<Transform>()->SetPosition(Vector2(75.0f, 140.0f));
			SpriteRenderer* Charactorsr = Charactor->AddComponent<SpriteRenderer>();
			Charactorsr->SetScale(Vector2(0.7f, 0.7f));
			Charactorsr->SetImage(Bazzi);

			// 캐릭터 선택 창
			Texture* CharSelect = Resources::Load<Texture>(L"CharSelectImage"
				, L"..\\Resources\\Image\\UI\\bazzi_image.bmp");

			BackGround* cs = object::Instantiate<BackGround>(eLayerType::Background);
			cs->GetComponent<Transform>()->SetPosition(Vector2(630.0f, 50.0f));
			SpriteRenderer* cssr = cs->AddComponent<SpriteRenderer>();
			cssr->SetImage(CharSelect);
			cssr->SetScale(Vector2(1.f, 1.f));
		}
		if (SceneManager::GetSelectSoloPlayer() == 1 && DaoClick == true )
		{
			// 캐릭터 세팅
			Texture* Dao = Resources::Load<Texture>(L"DaoImage"
				, L"..\\Resources\\Image\\Dao\\Idle\\Idle.bmp");

			BackGround* Charactor = object::Instantiate<BackGround>(eLayerType::Background);
			Charactor->GetComponent<Transform>()->SetPosition(Vector2(75.0f, 140.0f));
			SpriteRenderer* Charactorsr = Charactor->AddComponent<SpriteRenderer>();
			Charactorsr->SetScale(Vector2(1.3f, 1.3f));
			Charactorsr->SetImage(Dao);

			// 캐릭터 선택 창
			Texture* DaoSelect = Resources::Load<Texture>(L"DaoSelectImage"
				, L"..\\Resources\\Image\\UI\\dao_image.bmp");

			BackGround* cs = object::Instantiate<BackGround>(eLayerType::Background);
			cs->GetComponent<Transform>()->SetPosition(Vector2(630.0f, 50.0f));
			SpriteRenderer* cssr = cs->AddComponent<SpriteRenderer>();
			cssr->SetImage(DaoSelect);
			cssr->SetScale(Vector2(1.f, 1.f));
		}

		// 2P - 캐릭터 선택
		if (SceneManager::GetSelectMultiPlayer() == 1 && BazziClick == true)
		{
			// 캐릭터 세팅
			Texture* Bazzi = Resources::Load<Texture>(L"BazziImage"
				, L"..\\Resources\\Image\\Bazzi\\Idle.bmp");

			BackGround* Charactor = object::Instantiate<BackGround>(eLayerType::Background);
			Charactor->GetComponent<Transform>()->SetPosition(Vector2(75.0f, 140.0f));
			SpriteRenderer* Charactorsr = Charactor->AddComponent<SpriteRenderer>();
			Charactorsr->SetScale(Vector2(0.7f, 0.7f));
			Charactorsr->SetImage(Bazzi);

			// 캐릭터 선택 창
			Texture* CharSelect = Resources::Load<Texture>(L"CharSelectImage"
				, L"..\\Resources\\Image\\UI\\bazzi_image.bmp");

			BackGround* cs = object::Instantiate<BackGround>(eLayerType::Background);
			cs->GetComponent<Transform>()->SetPosition(Vector2(630.0f, 50.0f));
			SpriteRenderer* cssr = cs->AddComponent<SpriteRenderer>();
			cssr->SetImage(CharSelect);
			cssr->SetScale(Vector2(1.f, 1.f));
		}

		if (SceneManager::GetSelectMultiPlayer() == 1 && DaoClick == true) 
		{
			// 캐릭터 세팅
			Texture* Dao = Resources::Load<Texture>(L"DaoImage"
				, L"..\\Resources\\Image\\Dao\\Idle\\Idle.bmp");

			BackGround* Charactor = object::Instantiate<BackGround>(eLayerType::Background);
			Charactor->GetComponent<Transform>()->SetPosition(Vector2(180.0f, 140.0f));
			SpriteRenderer* Charactorsr = Charactor->AddComponent<SpriteRenderer>();
			Charactorsr->SetScale(Vector2(1.3f, 1.3f));
			Charactorsr->SetImage(Dao);

			// 캐릭터 선택 창
			Texture* DaoSelect = Resources::Load<Texture>(L"DaoSelectImage"
				, L"..\\Resources\\Image\\UI\\dao_image.bmp");

			BackGround* cs = object::Instantiate<BackGround>(eLayerType::Background);
			cs->GetComponent<Transform>()->SetPosition(Vector2(630.0f, 50.0f));
			SpriteRenderer* cssr = cs->AddComponent<SpriteRenderer>();
			cssr->SetImage(DaoSelect);
			cssr->SetScale(Vector2(1.f, 1.f));
		}

		// 마우스 클릭마다 소리
		if (Input::GetKeyDown(eKeyCode::MouseLeft))
		{
			Resources::Find<Sound>(L"Click")->Play(false);
		}
	
		// 시작 버튼
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 530 && temp.y <= 575 && temp.x >= 515 && temp.x <= 695)
		{
			if (SceneManager::GetActiveMap() == 1)
			{
				Resources::Find<Sound>(L"LobbySound")->Stop(true);

				SceneManager::LoadScene(L"ForestMap1");
			}
			else if(SceneManager::GetActiveMap() == 2)
			{
				Resources::Find<Sound>(L"LobbySound")->Stop(true);

				SceneManager::LoadScene(L"IceMap1");
			}
			else if (SceneManager::GetActiveMap() == 3)
			{
				Resources::Find<Sound>(L"LobbySound")->Stop(true);

				SceneManager::LoadScene(L"PirateMap1");
			}
		}

		// Map 창 키기
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 440 && temp.y <= 480 && temp.x >= 650 && temp.x <= 770)
		{
			MapSelect = object::Instantiate<StagePick>(eLayerType::UI);
			Transform* MapSelecttr = MapSelect->GetComponent<Transform>();
			MapSelecttr->SetPosition(Vector2(400.f, 290.f));
		}

		// 확인
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 480 && temp.y <= 500 && temp.x >= 295 && temp.x <= 385)
		{
			Destroy(MapSelect);
		}

		// 취소
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 480 && temp.y <= 500 && temp.x >= 400 && temp.x <= 500)
		{
			Destroy(MapSelect);
		}

		if (Input::GetKeyDown(eKeyCode::N))
		{
			Resources::Find<Sound>(L"LobbySound")->Stop(true);

			SceneManager::LoadScene(L"ForestMap1");

		}
		

	}
	void LobbyScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		/*wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"LobbyScene");
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 700, 350, szFloat, strLen);

		Ellipse(hdc, 685, 400, 785, 500);*/
	}
	void LobbyScene::Enter()
	{
		Resources::Find<Sound>(L"LobbySound")->Play(true);

	}
	void LobbyScene::Exit()
	{
	}
}
