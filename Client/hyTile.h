#pragma once
#include "hyGameObject.h"

namespace hy
{
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

		void SetTile(int x, int y);

	private:
		class SpriteRenderer* mSpriteRenderer;


	};
}

