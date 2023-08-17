#include "hyLogoScene.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyBackGround.h"
#include "hyTransform.h"
#include "hyApplication.h"
#include "hySound.h"
#include "hyTime.h"


extern hy::Application application;

namespace hy
{
	Sound* LogoScene::sound = nullptr;

	LogoScene::LogoScene()
	{
	}
	LogoScene::~LogoScene()
	{
	}
	void LogoScene::Initialize()
	{
		Scene::Initialize();

		// 사운드 적용
		Resources::Load<Sound>(L"LogoSound", L"..\\Resources\\Sound\\Sound\\logo.wav");

		//// 넥슨 화면
		//Texture* Logo_ = Resources::Load<Texture>(L"Logo"	
		//	, L"..\\Resources\\Image\\Bg\\Logo.bmp");		

		//BackGround* Logobg = object::Instantiate<BackGround>(eLayerType::Background);
		//SpriteRenderer* Logobgsr = Logobg->AddComponent<SpriteRenderer>();
		//Logobgsr->SetImage(Logo_);
		//Logobgsr->SetAlpha(0.5f);						// 배경 투명도 세팅
		//Logobgsr->SetScale(Vector2(1.f, 1.f));			// 이미지 사이즈 조절
		//Logobg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));	// 배경을 해상도의 절반으로 세팅

		object::Instantiate<Logo>(eLayerType::Background);


	}
	void LogoScene::Update()
	{
		Scene::Update();

		mSceneTime += Time::DeltaTime();

		if (mSceneTime >= 5.0f)
		{
			Resources::Find<Sound>(L"LogoSound")->Stop(1);
			SceneManager::LoadScene(L"TitleScene");
		}

		//if (Input::GetKeyDown(eKeyCode::MouseLeft)) // N을 누르면 다음 씬으로 넘어가기
		//{
		//	Resources::Find<Sound>(L"LogoSound")->Stop(1);
		//	SceneManager::LoadScene(L"TitleScene");
		//}


	}
	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
	void LogoScene::Enter()
	{
		Resources::Find<Sound>(L"LogoSound")->Play(false);

	}
	void LogoScene::Exit()
	{
	}
}
