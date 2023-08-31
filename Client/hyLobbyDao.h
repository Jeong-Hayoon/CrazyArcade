#pragma once
#include "hyGameObject.h"

namespace hy
{
	class LobbyDao : public GameObject
	{
	public:
		LobbyDao();
		virtual ~LobbyDao();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
