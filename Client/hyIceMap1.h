#pragma once
#include "hyScene.h"
#include "hyTile.h"
#include "hyBazzi.h"
#include "hyDao.h"
#include "hyItemUI.h"


namespace hy
{
#define LEFT_TOP_Y 40.f
#define LEFT_TOP_X 20.f

#define RIGHT_BOTTOM_Y 560.f
#define RIGHT_BOTTOM_X 620.f

	class IceMap1 : public Scene
	{
	public:
		IceMap1();
		virtual ~IceMap1();

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
		Bazzi* IceBazzi;
		Dao* IceDao;
		bool Initflag;
		ItemUI* mItemUI;



	};
}

