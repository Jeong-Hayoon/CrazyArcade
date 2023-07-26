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

		if (Input::GetKeyDown(eKeyCode::MouseLeft) && GetFocus())
		{
			Vector2 mousePos = Input::GetMousePosition();

			int idxX = mousePos.x / (TILE_WIDTH * 3);
			int idxY = mousePos.y / (TILE_HEIGHT * 3);

			Vector2 offset = Vector2((TILE_WIDTH * 3) / 2.0f, (TILE_HEIGHT * 3) / 2.0f);
			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile
				, Vector2(idxX * (TILE_WIDTH * 3) + offset.x
					, idxY * (TILE_HEIGHT * 3) + offset.y));

			tile->SetTile(Tile::mSelectedX, Tile::mSelectedY);
		}
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		int maxRow = 720 / (TILE_HEIGHT * 3) + 1;
		for (size_t y = 0; y < maxRow; y++)
		{
			MoveToEx(hdc, 0, TILE_HEIGHT * y * 3, NULL);      //      라인(선) 시작
			LineTo(hdc, 1280, TILE_HEIGHT * y * 3);        //          라인(선) 끝
		}

		int maxColumn = 1280 / (TILE_WIDTH * 3) + 1;
		for (size_t x = 0; x < maxColumn; x++)
		{
			MoveToEx(hdc, TILE_WIDTH * x * 3, 0, NULL);      //      라인(선) 시작
			LineTo(hdc, TILE_WIDTH * x * 3, 720);        //          라인(선) 끝
		}
	}
}
