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


extern hy::Application application;
namespace hy
{
	LobbyScene::LobbyScene()
	{
	}
	LobbyScene::~LobbyScene()
	{
	}
	void LobbyScene::Initialize()
	{
		Scene::Initialize();

		// 로비
		Texture* image = Resources::Load<Texture>(L"LobbyBackGroundImage"
			, L"..\\Resources\\Image\\Bg\\Lobby.bmp");

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(1.5f, 1.35f));
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));	// 배경을 해상도의 절반으로 세팅


		// 캐릭터 세팅
		Texture* Bazzi = Resources::Load<Texture>(L"BazziImage"
			, L"..\\Resources\\Image\\Bazzi\\Idle.bmp");

		BackGround* Charactor = object::Instantiate<BackGround>(eLayerType::Background);
		Charactor->GetComponent<Transform>()->SetPosition(Vector2(115.0f, 190.0f));
		SpriteRenderer* Charactorsr = Charactor->AddComponent<SpriteRenderer>();
		Charactorsr->SetScale(Vector2(0.9f, 0.9f));
		Charactorsr->SetImage(Bazzi);

		//Bazzi* Lobbytbazzi = object::Instantiate<Bazzi>(eLayerType::Player);
		//Transform* forestbazzitr = Lobbytbazzi->GetComponent<Transform>();
		//forestbazzitr->SetPosition(Vector2(115.0f, 160.0f));

		// 캐릭터 선택 창
		Texture* CharSelect = Resources::Load<Texture>(L"CharSelectImage"
			, L"..\\Resources\\Image\\UI\\bazzi_image.bmp");

		BackGround* cs = object::Instantiate<BackGround>(eLayerType::Background);
		cs->GetComponent<Transform>()->SetPosition(Vector2(947.0f, 68.0f));
		SpriteRenderer* cssr = cs->AddComponent<SpriteRenderer>();
		cssr->SetImage(CharSelect);
		cssr->SetScale(Vector2(1.470f, 1.35f));

		// 맵 선택(포레스트 맵)
		Texture* ForestMapSelect = Resources::Load<Texture>(L"ForestMapSelectImage"
			, L"..\\Resources\\Image\\UI\\ForestRandom.bmp");

		BackGround* fms = object::Instantiate<BackGround>(eLayerType::Background);
		fms->GetComponent<Transform>()->SetPosition(Vector2(840.0f, 555.0f));
		SpriteRenderer* fmssr = fms->AddComponent<SpriteRenderer>();
		fmssr->SetImage(ForestMapSelect);
		fmssr->SetScale(Vector2(1.0f, 0.9f));

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

		if (Input::GetKeyDown(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			SceneManager::LoadScene(L"ForestMap");
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
}
