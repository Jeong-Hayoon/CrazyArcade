#include "wzLobbyScene.h"
#include "wzTitleScene.h"
#include "wzPlayer.h"
#include "wzSpriteRenderer.h"
#include "wzObject.h"
#include "wzSceneManager.h"
#include "wzApplication.h"
#include "wzInput.h"

namespace wz
{
	LobbyScene::LobbyScene()
	{
	}
	LobbyScene::~LobbyScene()
	{
	}
	void LobbyScene::Initialize()
	{
	/*	Player* player = object::Instantiate <Player>(eLayerType::Player);
		player->AddComponent<SpriteRenderer>();*/

	}
	void LobbyScene::Update()
	{
		Scene::Update();

		if (Input::GetKey(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			SceneManager::LoadScene(L"PlayScene");
		}

	}
	void LobbyScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"LobbyScene");
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 700, 350, szFloat, strLen);

		Ellipse(hdc, 685, 400, 785, 500);
	}
}
