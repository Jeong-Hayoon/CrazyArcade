#include "wzTitleScene.h"
#include "wzPlayer.h"
#include "wzSpriteRenderer.h"
#include "wzObject.h"

namespace wz 
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Player* player = object::Instantiate <Player>(eLayerType::Player);
		player->AddComponent<SpriteRenderer>();

	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}
