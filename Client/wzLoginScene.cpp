#include "wzLoginScene.h"
#include "wzTitleScene.h"
#include "wzPlayer.h"
#include "wzSpriteRenderer.h"
#include "wzObject.h"
#include "wzTransform.h"
#include "wzGameObject.h"
#include "wzComponent.h"
#include "wzSceneManager.h"
#include "wzApplication.h"
#include "wzInput.h"


namespace wz
{
	LoginScene::LoginScene()
	{
	}
	LoginScene::~LoginScene()
	{
	}
	void LoginScene::Initialize()
	{
		/*Player* player = object::Instantiate <Player>(eLayerType::Player);
		player->AddComponent<SpriteRenderer>();*/

	}
	void LoginScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) // N을 누르면 다음 씬으로 넘어가기
		{
			SceneManager::LoadScene(L"LobbyScene");
		}

	}
	void LoginScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"LoginScene");
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 700, 350, szFloat, strLen);
	}
}
