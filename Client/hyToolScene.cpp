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

		// Ÿ�� ��ġ..?
		Tile* tile
			= object::Instantiate<Tile>(eLayerType::Tile, Vector2(600.0f, 400.0f));
	}

	void ToolScene::Update()
	{
		Scene::Update();

		// GetFocus : �����찡 Ȱ���� ���� �� �� �ְ� ���ִ� �Լ�
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

		// ���� �����
		int maxRow = 800 / (TILE_HEIGHT) + 1;
		for (size_t y = 0; y < maxRow; y++)
		{	//���� ��ġ 0,0 ���� 200, 200 ���� ���� �׸��ڴ�
			MoveToEx(hdc, 0, TILE_HEIGHT * y, NULL);	 //      ����(��) ����
			LineTo(hdc, 1200, TILE_HEIGHT * y);			 //      ����(��) ��
		}

		int maxColumn = 1200 / (TILE_WIDTH) + 1;
		for (size_t x = 0; x < maxColumn; x++)
		{
			MoveToEx(hdc, TILE_WIDTH * x , 0, NULL);		 //      ����(��) ����
			LineTo(hdc, TILE_WIDTH * x , 800);			 //      ����(��) ��
		}
	}
}
