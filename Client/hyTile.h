#pragma once
#include "hyGameObject.h"

namespace hy
{
	using namespace math;

	class Tile : public GameObject
	{
	public:
		static UINT mSelectedX;
		static UINT mSelectedY;

		Tile();
		~Tile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetSourceTileIdx(int x, int y) { mSourceIndexX = x;  mSourceIndexY = y; }
		void SetTileIdx(int x, int y) { mIndexX = x;  mIndexY = y; }
		Vector2 GetSourceTileIdx() { return Vector2(mSourceIndexX, mSourceIndexY); }
		Vector2 GetTileIdx() { return Vector2(mIndexX, mIndexY); }
		void SetTile(int x, int y);

	private:
		class SpriteRenderer* mSpriteRenderer;
		UINT mSourceIndexX;
		UINT mSourceIndexY;

		UINT mIndexX;
		UINT mIndexY;

	};
}

