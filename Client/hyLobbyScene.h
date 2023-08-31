#pragma once
#include "hyScene.h"
#include "hyStagePick.h"
#include "hyLobbyDao.h"
#include "hyLobbyBazzi.h"


namespace hy
{
	class LobbyScene : public Scene
	{
	public:
		LobbyScene();
		virtual ~LobbyScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

		static bool GetBazziClick() { return BazziClick; }
		static void SetBazziClick(bool click) { BazziClick = click; }

		static bool GetDaoClick() { return DaoClick; }
		static bool SetDaoClick(bool click) { DaoClick = click; }


	private:
		// 멤버 변수로 포인터를 가지고 있기 때문에 MapSelect는 객체 생성 전까지는 nullptr
		StagePick* MapSelect;
		static bool BazziClick;
		static bool DaoClick;
		bool AlreadySeat;			// 이미 좌측에 클릭이 되어 있는지
		LobbyDao* DaoReady;
		LobbyBazzi* BazziReady;
	};
}


