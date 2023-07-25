#include "hyToolScene.h"
#include "hyTitleScene.h"
#include "hySpriteRenderer.h"
#include "hyObject.h"
#include "hyInput.h"
#include "hyTexture.h"
#include "hyTransform.h"
#include "hyResources.h"
#include "hyBackGround.h"
#include "hyCamera.h"
#include "hyTile.h"

namespace hy
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
		Texture* forestFloor
			= Resources::Load<Texture>(L"ForestFloorTile", L"..\\resources\\image\\Bg\\ForestTile.bmp");

		// 타일 위치..?
		Tile* tile
			= object::Instantiate<Tile>(eLayerType::Tile, Vector2(600.0f, 400.0f));
	}

	void ToolScene::Update()
	{
		Scene::Update();



	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}
