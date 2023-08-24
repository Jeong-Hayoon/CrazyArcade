#pragma once
#include "hyScene.h"
#include "hyStagePick.h"

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

	private:
		// ��� ������ �����͸� ������ �ֱ� ������ MapSelect�� ��ü ���� �������� nullptr
		StagePick* MapSelect;
	};
}


