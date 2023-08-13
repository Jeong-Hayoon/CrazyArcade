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
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		/*Player* player = object::Instantiate <Player>(eLayerType::Player);
		player->AddComponent<SpriteRenderer>();*/

		// ���� ����
		Resources::Load<Sound>(L"LoginSound", L"..\\Resources\\Sound\\Sound\\login_scene.wav");
		Resources::Find<Sound>(L"LoginSound")->Play(true);

		// ���ӽ��� ȭ��
		Texture* image = Resources::Load<Texture>(L"TitleBackGroundImgae"	// �̹��� ������������ ���ҽ��� ��ȯ����, �̹��� �ε�
			, L"..\\Resources\\Image\\Bg\\login_scene_bg.bmp");		// Client �ۿ� ���ҽ� ����-�̹���-���� ���� ������ �ְ� ��� �Է�(�����)
		// �Ӽ����� �������� ���� ���� ���
		// �����θ� ����ϸ� ��ǻ�Ͱ� �ٲ�� ������ ������ �ε� �Ұ�
		// ���� ����θ� ����ؾ� ��						
		// \\ : ���� ��ĭ, .. : �Ʒ��� ��ĭ 

	/*	Player* player = object::Instantiate<Player>(eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(image);*/

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(0.77f, 0.79f));		// �̹��� ������ ����
		
		// ȸ��
		//bg->GetComponent<Transform>()->SetRotation(45);
		
		// <ī�޶�>
		//bgsr->SetAffectCamera(false);				// ����� ī�޶��� ������ ������ �ȵǹǷ�
		//bgsr->SetAlpha(0.2f);						// ��� ���� ����
		bg->GetComponent<Transform>()->SetPosition(Vector2((float)(application.GetWidth() / 2), (float)(application.GetHeight() / 2)));	// ����� �ػ��� �������� ����
		
		//Image = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Image\\BSmile.png");

	/*	Player* player = object::Instantiate<Player>(eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(0.2f, 0.2f));*/

		//std::wstring name = player->GetName();

		//mLayers[(int)eLayerType::Player].AddGameObject(player);

		//Camera::SetTarget(player);		// mLookPosition�� player�� ����Ű�� ��

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

		if (Input::GetKeyDown(eKeyCode::N)) // N�� ������ ���� ������ �Ѿ��
		{
			Resources::Find<Sound>(L"LoginSound")->Stop(1);
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
}
