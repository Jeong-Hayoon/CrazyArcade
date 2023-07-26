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

		// GetFocus : 윈도우가 활성될 때만 할 수 있게 해주는 함수
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && GetFocus())
		{
			Vector2 mousePos = Input::GetMousePosition();

			int idxX = mousePos.x / (TILE_WIDTH);
			int idxY = mousePos.y / (TILE_HEIGHT);

			Vector2 offset = Vector2((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f);
			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile
				, Vector2(idxX * (TILE_WIDTH) + offset.x
					, idxY * (TILE_HEIGHT) + offset.y));

			tile->SetTile(Tile::mSelectedX, Tile::mSelectedY);
		}
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		// 격자 만들기
		int maxRow = 800 / (TILE_HEIGHT) + 1;
		for (size_t y = 0; y < maxRow; y++)
		{	//시작 위치 0,0 부터 200, 200 까지 선을 그리겠다
			MoveToEx(hdc, 0, TILE_HEIGHT * y, NULL);	 //      라인(선) 시작
			LineTo(hdc, 1200, TILE_HEIGHT * y);			 //      라인(선) 끝
		}

		int maxColumn = 1200 / (TILE_WIDTH) + 1;
		for (size_t x = 0; x < maxColumn; x++)
		{
			MoveToEx(hdc, TILE_WIDTH * x , 0, NULL);		 //      라인(선) 시작
			LineTo(hdc, TILE_WIDTH * x , 800);			 //      라인(선) 끝
		}
	}
}
