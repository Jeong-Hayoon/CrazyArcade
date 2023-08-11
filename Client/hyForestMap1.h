#pragma once
#include "hyScene.h"
#include "hyTile.h"

namespace hy
{
	#define LEFT_TOP_Y 40.f
	#define LEFT_TOP_X 20.f

	#define RIGHT_BOTTOM_Y 560.f
	#define RIGHT_BOTTOM_X 620.f

	class ForestMap1 : public Scene
	{
	public:
		ForestMap1();
		virtual ~ForestMap1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		void Load();

	private:
		std::vector<Tile*> mTiles;;
	};
}

