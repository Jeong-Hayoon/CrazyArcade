#include "hyTitleScene.h"
#include "hyPlayer.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyBackGround.h"
#include "hyTransform.h"
// #include "hyCamera.h"

namespace hy
{
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
		bgsr->SetScale(Vector2(1.16f, 1.07f));		// �̹��� ������ ����
		
		// <ī�޶�>
		//bgsr->SetAffectCamera(false);					// ����� ī�޶��� ������ ������ �ȵǹǷ�
		//bgsr->SetAlpha(0.2f);							// ��� ���� ����
		//bg->GetComponent<Transform>()->SetPosition(Vector2(640.0f, 360.0f));	// ����� �ػ��� �������� ����

		image = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Image\\Smile.png");

		Player* player = object::Instantiate<Player>(eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(0.2f, 0.2f));

		//std::wstring name = player->GetName();

		//mLayers[(int)eLayerType::Player].AddGameObject(player);

		// Camera::SetTarget(player);		// mLookPosition�� player�� ����Ű�� ��

	}
	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N�� ������ ���� ������ �Ѿ��
		{
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
