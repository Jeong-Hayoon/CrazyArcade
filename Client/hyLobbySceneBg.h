#pragma once
#include "hyGameObject.h"

namespace hy
{
	class LobbySceneBG : public GameObject
	{
	public:
		LobbySceneBG();
		virtual ~LobbySceneBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}

