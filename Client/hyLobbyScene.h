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
		// 멤버 변수로 포인터를 가지고 있기 때문에 MapSelect는 객체 생성 전까지는 nullptr
		StagePick* MapSelect;
	};
}


