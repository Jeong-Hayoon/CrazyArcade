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

// ToolScene에서 하던 작업을 각 씬에서 불러와주면 됨
// 절대경로 사용

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
		Texture* Forestfloor
			= Resources::Load<Texture>(L"ForestFloorTile", L"..\\Resources\\Image\\Bg\\ForestTile.bmp");

		// 타일 위치..?
		/*Tile* tile
			= object::Instantiate<Tile>(eLayerType::Tile, Vector2(600.0f, 400.0f));*/
	
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
			tile->SetSourceTileIdx(Tile::mSelectedX, Tile::mSelectedY);
			tile->SetTileIdx(idxX, idxY);

			mTiles.push_back(tile);
		}

		// 타일을 깔고 어딘가에 저장을 해야 함 
		// 파일 입출력(램에 있는 데이터를 SSD에 옮기는 작업)
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
	// 파일 입출력
	void ToolScene::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		//szFilePath - 경로
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

		// 파일을 여는 함수
		// wb : 파일을 이진수로 저장할 것인지
		// wt : 텍스트로 저장할 것인지
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

			// 열어놓은 파일에 원하는 크기만큼 파일에 기록
			// sourceX, sourceY - 우측의 타일의 소스 인덱스
			// myX, myY - 좌측의 타일 소스 인덱스
			fwrite(&sourceX, sizeof(int), 1, pFile);
			fwrite(&sourceY, sizeof(int), 1, pFile);
			fwrite(&myX, sizeof(int), 1, pFile);
			fwrite(&myY, sizeof(int), 1, pFile);
		}

		// 메모리 할당된 것을 삭제해주는 함수
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

		// rb : 이진수로 파일을 읽음
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
