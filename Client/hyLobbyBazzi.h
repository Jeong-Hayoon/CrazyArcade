#pragma once
#include "hyGameObject.h"

namespace hy
{
	class LobbyBazzi : public GameObject
	{
	public:
		LobbyBazzi();
		virtual ~LobbyBazzi();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
