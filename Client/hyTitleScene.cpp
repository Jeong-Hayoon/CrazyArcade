#include "hyTitleScene.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyBackGround.h"
#include "hyTransform.h"
// #include "hyCamera.h"
#include "hyApplication.h"
#include "hySound.h"

extern hy::Application application;

namespace hy
{
	Sound* TitleScene::sound = nullptr;

	TitleScene::TitleScene()
		: Choicefinish(false)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Scene::Initialize();
		/*Player* player = object::Instantiate <Player>(eLayerType::Player);
		player->AddComponent<SpriteRenderer>();*/

		// 사운드 적용
		Resources::Load<Sound>(L"LoginSound", L"..\\Resources\\Sound\\Sound\\login_scene.wav");
		Resources::Load<Sound>(L"Click", L"..\\Resources\\Sound\\Sound\\click.wav");


		// 게임시작 화면
		Texture* image = Resources::Load<Texture>(L"TitleBackGroundImgae"	// 이미지 포인터형으로 리소스를 반환해줌, 이미지 로드
			, L"..\\Resources\\Image\\Bg\\login_scene_bg.bmp");		// Client 밖에 리소스 폴더-이미지-사운드 만들어서 파일을 넣고 경로 입력(상대경로)
		// 속성에서 가져오는 것은 절대 경로
		// 절대경로를 사용하면 컴퓨터가 바뀌고 파일이 없으면 로드 불가
		// 따라서 상대경로를 사용해야 함						
		// \\ : 위로 한칸, .. : 아래로 한칸 

	/*	Player* player = object::Instantiate<Player>(eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(image);*/

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(0.77f, 0.79f));		// 이미지 사이즈 조절
		
		// 회전
		//bg->GetComponent<Transform>()->SetRotation(45);
		
		// <카메라>
		//bgsr->SetAffectCamera(false);				// 배경은 카메라의 영향을 받으면 안되므로
		//bgsr->SetAlpha(0.2f);						// 배경 투명도 세팅
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));	// 배경을 해상도의 절반으로 세팅
		
		//Image = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Image\\BSmile.png");

	/*	Player* player = object::Instantiate<Player>(eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(0.2f, 0.2f));*/

		//std::wstring name = player->GetName();

		//mLayers[(int)eLayerType::Player].AddGameObject(player);

		//Camera::SetTarget(player);		// mLookPosition이 player을 가리키게 됨

		//1p Button
		Texture* OnePlayer = Resources::Load<Texture>(L"OnePlayerImage"
		, L"..\\Resources\\Image\\UI\\Signle.png");

		BackGround* oneplayer = object::Instantiate<BackGround>(eLayerType::Background);
		oneplayer->GetComponent<Transform>()->SetPosition(Vector2(290.0f,120.0f));
		SpriteRenderer* oneplayersr = oneplayer->AddComponent<SpriteRenderer>();
		oneplayersr->SetImage(OnePlayer);
		oneplayersr->SetScale(Vector2(1.0f, 1.0f));

		//2p Button
		Texture* TwoPlayer = Resources::Load<Texture>(L"TwoPlayerImage"
			, L"..\\Resources\\Image\\UI\\Duo.png");

		BackGround* twoplayer = object::Instantiate<BackGround>(eLayerType::Background);
		twoplayer->GetComponent<Transform>()->SetPosition(Vector2(497.0f, 120.0f));
		SpriteRenderer* twoplayersr = twoplayer->AddComponent<SpriteRenderer>();
		twoplayersr->SetImage(TwoPlayer);
		twoplayersr->SetScale(Vector2(1.0f, 1.0f));
	}
	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MouseLeft))
		{
			Resources::Find<Sound>(L"Click")->Play(false);
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			SceneManager::LoadScene(L"ToolScene");
		}

		

		//if (Input::GetKeyDown(eKeyCode::MouseLeft)) // N을 누르면 다음 씬으로 넘어가기
		//{
		//	SceneManager::LoadScene(L"LobbyScene");
		//}

		Vector2 temp = Input::GetMousePosition();

		// 1p
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 115 && temp.y <= 185 && temp.x >= 275 && temp.x <= 325)
		{
			SceneManager::SetSelectSoloPlayer(true);
			SceneManager::SetSelectMultiPlayer(false);

			SceneManager::SetPlayerNum(1);
			Choicefinish = true;
		}

		// 2p 
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 110 && temp.y <= 185 && temp.x >= 475 && temp.x <= 530)
		{
			SceneManager::SetSelectMultiPlayer(true);
			SceneManager::SetSelectSoloPlayer(false);

			SceneManager::SetPlayerNum(2);

			Choicefinish = true;
		}

		// Game Start
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && temp.y >= 90 && temp.y <= 185 && temp.x >= 350 && temp.x <= 455 && Choicefinish == true)
		{
			Resources::Find<Sound>(L"LoginSound")->Stop(true);
			SceneManager::LoadScene(L"LobbyScene");
		}

	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		//wchar_t szFloat[50] = {};
		//swprintf_s(szFloat, 50, L"LoginScene");
		//int strLen = wcsnlen_s(szFloat, 50);

		//TextOut(hdc, 700, 350, szFloat, strLen);
	}
	void TitleScene::Enter()
	{
		Resources::Find<Sound>(L"LoginSound")->Play(true);


	}
	void TitleScene::Exit()
	{
	}
}
