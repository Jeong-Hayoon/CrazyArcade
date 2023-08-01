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

extern hy::Application application;

namespace hy
{
	LogoScene::LogoScene()
	{
	}
	LogoScene::~LogoScene()
	{
	}
	void LogoScene::Initialize()
	{
		// ���� ����
		Sound* sound = Resources::Load<Sound>(L"bgSound", L"..\\Resources\\Sound\\Sound\\lobby_scene.wav");
		sound->Play(true);

		// �ؽ� ȭ��
		Texture* Logo_ = Resources::Load<Texture>(L"Logo"	
			, L"..\\Resources\\Image\\Bg\\Logo.bmp");		

		BackGround* Logobg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* Logobgsr = Logobg->AddComponent<SpriteRenderer>();
		Logobgsr->SetImage(Logo_);
		Logobgsr->SetAlpha(0.5f);						// ��� ���� ����
		Logobgsr->SetScale(Vector2(1.45f, 1.45f));		// �̹��� ������ ����
		Logobg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));	// ����� �ػ��� �������� ����

		
	}
	void LogoScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N�� ������ ���� ������ �Ѿ��
		{
			SceneManager::LoadScene(L"TitleScene");
		}


	}
	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}
