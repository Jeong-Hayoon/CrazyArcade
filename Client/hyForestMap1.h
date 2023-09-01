#pragma once
#include "hyScene.h"
#include "hyTile.h"
#include "hyBazzi.h"
#include "hyDao.h"
//#include "hyCharactorProfile.h"


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

		virtual void Enter();
		virtual void Exit();

		void Win();
		void Lose();

		void Reset();									// 게임이 끝나고 경기를 리셋하는 함수

		//static void SetFunCheck(bool check) { FunCheck = check; }

		Tile* GetTile(UINT x, UINT y);


	private:
		std::vector<Tile*> mTiles;
		// static bool FunCheck;
		Bazzi* ForestBazzi;
		Dao* ForestDao;
		bool Initflag;
		//CharactorProfile* Profile;
	};
}

