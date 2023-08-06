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

// ToolScene���� �ϴ� �۾��� �� ������ �ҷ����ָ� ��
// ������ ���

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

		// Ÿ�� �ּ�
		Texture* Tile_
			= Resources::Load<Texture>(L"Tile", L"..\\Resources\\Image\\Map\\Tile.bmp");

	

		// Ÿ�� ��ġ..?
		/*Tile* tile_
			= object::Instantiate<Tile>(eLayerType::Tile, Vector2(600.0f, 400.0f));*/
	
	}

	void ToolScene::Update()
	{
		Scene::Update();

		// GetFocus : �����찡 Ȱ���� ���� �� �� �ְ� ���ִ� �Լ�
		if (Input::GetKeyDown(eKeyCode::MouseLeft) && GetFocus())
		{
			Vector2 mousePos = Input::GetMousePosition();

			// ���콺 Ŀ���� ��ġ�� Ÿ���� �ε����� �ٲ��ִ� �۾�
			int idxX = mousePos.x / (TILE_WIDTH);
			int idxY = mousePos.y / (TILE_HEIGHT);

			// Ÿ���� �߾��� �߽����� ������ ����
			Vector2 offset = Vector2((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f);

			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile
				, Vector2(idxX * (TILE_WIDTH) + offset.x
				, idxY * (TILE_HEIGHT) + offset.y));

			tile->SetTile(Tile::mSelectedX, Tile::mSelectedY);
			tile->SetSourceTileIdx(Tile::mSelectedX, Tile::mSelectedY);
			tile->SetTileIdx(idxX, idxY);

			mTiles.push_back(tile);
		}

		// Ÿ���� ��� ��򰡿� ������ �ؾ� �� 
		// ���� �����(���� �ִ� �����͸� SSD�� �ű�� �۾�)
		if (Input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}
		if (Input::GetKeyDown(eKeyCode::L))
		{
			Load();
		}

	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		// 20, 40
		// 620,560
		// ���� �����
		int maxRow = 560 / (TILE_HEIGHT) + 1;
		for (size_t y = 0; y < maxRow; y++)
		{
			MoveToEx(hdc, 20, TILE_HEIGHT * y, NULL);	 //      ����(��) ���ۺ���
			LineTo(hdc, 620, TILE_HEIGHT * y);			 //      ����(��) ������ ���� �׸�
		}

		int maxColumn = 620 / (TILE_WIDTH) + 1;
		for (size_t x = 0; x < maxColumn; x++)
		{
			MoveToEx(hdc, TILE_WIDTH * x , 40, NULL);	 //      ����(��) ����
			LineTo(hdc, TILE_WIDTH * x , 560);			 //      ����(��) ��
		}
	}
	// ���� �����
	void ToolScene::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		//szFilePath - ���
		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;

		// ������ ���� �Լ�
		// wb : ������ �������� ������ ������
		// wt : �ؽ�Ʈ�� ������ ������
		_wfopen_s(&pFile, szFilePath, L"wb");
		if (pFile == nullptr)
			return;

		for (Tile* tile : mTiles)
		{
			Vector2 sourIdx = tile->GetSourceTileIdx();
			Vector2 idx = tile->GetTileIdx();

			int sourceX = sourIdx.x;
			int sourceY = sourIdx.y;

			int	myX = idx.x;
			int myY = idx.y;

			// ������� ���Ͽ� ���ϴ� ũ�⸸ŭ ���Ͽ� ���
			// sourceX, sourceY - ������ Ÿ���� �ҽ� �ε���
			// myX, myY - ������ Ÿ�� �ҽ� �ε���
			fwrite(&sourceX, sizeof(int), 1, pFile);
			fwrite(&sourceY, sizeof(int), 1, pFile);
			fwrite(&myX, sizeof(int), 1, pFile);
			fwrite(&myY, sizeof(int), 1, pFile);
		}

		// �޸� �Ҵ�� ���� �������ִ� �Լ�
		fclose(pFile);
	}

	void ToolScene::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&ofn))
			return;

		// rb : �������� ������ ����
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");

		if (pFile == nullptr)
			return;

		while (true)
		{
			int sourceX = -1;
			int sourceY = -1;

			int	myX = -1;
			int myY = -1;

			if (fread(&sourceX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&sourceY, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myY, sizeof(int), 1, pFile) == NULL)
				break;

			Vector2 offset = Vector2((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f);
			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile
				, Vector2(myX * (TILE_WIDTH ) + offset.x
					, myY * (TILE_HEIGHT) + offset.y));

			tile->SetTile(sourceX, sourceY);
			tile->SetSourceTileIdx(sourceX, sourceY);
			tile->SetTileIdx(myX, myY);

			mTiles.push_back(tile);
		}
	}
}
