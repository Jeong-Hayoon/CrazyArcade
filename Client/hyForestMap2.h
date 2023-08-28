#pragma once
#include "hyScene.h"
#include "hyTile.h"
#include "hyBazzi.h"


namespace hy
{
#define LEFT_TOP_Y 40.f
#define LEFT_TOP_X 20.f

#define RIGHT_BOTTOM_Y 560.f
#define RIGHT_BOTTOM_X 620.f

	class ForestMap2 : public Scene
	{
	public:
		ForestMap2();
		virtual ~ForestMap2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		void Load();

		virtual void Enter();
		virtual void Exit();

		void Win();
		void Lose();

		void Reset();

		Tile* GetTile(UINT x, UINT y);

	private:
		std::vector<Tile*> mTiles;
		Bazzi* ForestBazzi;


	};
}

