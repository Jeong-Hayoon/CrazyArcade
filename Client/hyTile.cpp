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
		mSpriteRenderer->SetScale(Vector2(3.0f, 3.0f));
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