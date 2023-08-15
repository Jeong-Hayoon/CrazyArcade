#include "hyTile.h"
#include "hySpriteRenderer.h"
#include "hyCollider.h"
#include "hyTexture.h"
#include "hyResources.h"
#include "hyCollisionManager.h"
#include "hySteam.h"
#include "hyObject.h"



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
		, mType(eType::None)

	{
	
	}

	Tile::~Tile()
	{
	}

	void Tile::Initialize()
	{
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		//AddComponent<Collider>();

		// Ÿ�� �ּ�
		hy::Texture* Tile_
			= hy::Resources::Find<hy::Texture>(L"Tile");

		mSpriteRenderer->SetImage(Tile_);
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

	void Tile::OnCollisionEnter(Collider* other)
	{
	
		if (other->GetOwner()->GetLayerType() == eLayerType::Bombflow)
		{
			if (this->GetType() == eType::Crack)
			{
				// ���� ������ ���� �ڵ� �߰�
				this->SetSourceTileIdx(0, 1);
				Steam* steam_ = object::Instantiate<Steam>(eLayerType::Effect);
				Transform* tiletr = this->GetComponent<Transform>();
				Vector2  Steampos = tiletr->GetPosition();

				steam_->GetComponent<Transform>()->SetPosition(Steampos);
			}
			else if (this->GetType() == eType::Uncrushable)
			{
				// Bomb Destroy..?
			}
		}
	}
	void Tile::OnCollisionStay(Collider* other)
	{

	}
	void Tile::OnCollisionExit(Collider* other)
	{
	}


}