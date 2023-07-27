#include "hyTile.h"
#include "hySpriteRenderer.h"
#include "hyCollider.h"
#include "hyTexture.h"
#include "hyResources.h"

namespace hy
{
	UINT Tile::mSelectedX = 0;
	UINT Tile::mSelectedY = 0;

	Tile::Tile()
		: mSpriteRenderer(nullptr)
		, mSourceIndexX(0)
		, mSourceIndexY(0)
		, mIndexX(0)
		, mIndexY(0)

	{
	}

	Tile::~Tile()
	{
	}

	void Tile::Initialize()
	{
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		//AddComponent<Collider>();

		hy::Texture* forestFloor
			= hy::Resources::Find<hy::Texture>(L"ForestFloorTile");

		mSpriteRenderer->SetImage(forestFloor);
		mSpriteRenderer->SetScale(Vector2(1.0f, 1.0f));
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Tile::SetTile(int x, int y)
	{
		mSpriteRenderer->SetTile(x, y);
	}

}