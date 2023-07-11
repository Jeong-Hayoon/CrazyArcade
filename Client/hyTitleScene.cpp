#include "hyTitleScene.h"
#include "hyPlayer.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hyInput.h"
#include "hyImage.h"
#include "hyResources.h"

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

		Image* image = Resources::Load<Image>(L"TitleBackGroundImgae"			// �̹��� ������������ ���ҽ��� ��ȯ����, �̹��� �ε�
			, L"..\\Resources\\Image\\Idle.bmp");											// Client �ۿ� ���ҽ� ����-�̹���-���� ���� ������ �ְ� ��� �Է�(�����)
																													// �Ӽ����� �������� ���� ���� ���
																													// �����θ� ����ϸ� ��ǻ�Ͱ� �ٲ�� ������ ������ �ε� �Ұ�
																													// ���� ����θ� ����ؾ� ��
																													// \\ : ���� ��ĭ, .. : �Ʒ��� ��ĭ
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetImage(image);

		std::wstring name = player->GetName();

		//mLayers[(int)eLayerType::Player].AddGameObject(player);

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

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"LoginScene");
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 700, 350, szFloat, strLen);
	}
}
