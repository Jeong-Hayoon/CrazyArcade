#include "hyLoginScene.h"
#include "hyTitleScene.h"
#include "hyPlayer.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hyTransform.h"
#include "hyGameObject.h"
#include "hyComponent.h"
#include "hySceneManager.h"
#include "hyApplication.h"
#include "hyInput.h"


namespace hy
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
