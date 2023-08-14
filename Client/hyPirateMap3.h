#pragma once
#include "hyScene.h"
#include "hyTile.h"

namespace hy
{
#define LEFT_TOP_Y 40.f
#define LEFT_TOP_X 20.f

#define RIGHT_BOTTOM_Y 560.f
#define RIGHT_BOTTOM_X 620.f

	class PirateMap3 : public Scene
	{
	public:
		PirateMap3();
		virtual ~PirateMap3();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		void Load();

		static UINT GetMonsterQuantity() { return MonsterQuantity; }
		static void SetMonsterQuantity() { MonsterQuantity--; }

		virtual void Enter();
		virtual void Exit();

	private:
		std::vector<Tile*> mTiles;;
		static UINT MonsterQuantity;

	};
}

