#include "wzPlayScene.h"
#include "wzTitleScene.h"
#include "wzPlayer.h"
#include "wzSpriteRenderer.h"
#include "wzObject.h"
#include "wzSceneManager.h"
#include "wzApplication.h"
#include "wzInput.h"

namespace wz
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		/*Player* player = object::Instantiate <Player>(eLayerType::Player);
		player->AddComponent<SpriteRenderer>();*/

	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"PlayScene");
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 700, 350, szFloat, strLen);

		Rectangle(hdc, 685, 400, 785, 500);
	}
}
