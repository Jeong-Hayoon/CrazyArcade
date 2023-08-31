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
		// ��� ������ �����͸� ������ �ֱ� ������ MapSelect�� ��ü ���� �������� nullptr
		StagePick* MapSelect;
		static bool BazziClick;
		static bool DaoClick;
		bool AlreadySeat;			// �̹� ������ Ŭ���� �Ǿ� �ִ���
		LobbyDao* DaoReady;
		LobbyBazzi* BazziReady;
	};
}


