#pragma once
#include "hyScene.h"

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

	private:
	// bool mbStart;
	};
}


