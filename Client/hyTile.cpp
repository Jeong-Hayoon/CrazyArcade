#include "hyTile.h"
#include "hySpriteRenderer.h"
#include "hyCollider.h"
#include "hyTexture.h"
#include "hyResources.h"

namespace hy
{
	Tile::Tile()
	{
	}

	Tile::~Tile()
	{
	}

	void Tile::Initialize()
	{
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		//AddComponent<Collider>();

		hy::Texture* forestFloor
			= hy::Resources::Find<hy::Texture>(L"ForestFloorTile");

		sr->SetImage(forestFloor);
		sr->SetTile(1, 0);
		sr->SetScale(Vector2(3.0f, 3.0f));
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}