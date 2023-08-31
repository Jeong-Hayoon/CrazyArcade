#pragma once
#include "hyGameObject.h"

namespace hy
{
	class LobbyCharactor : public GameObject
	{
	public:
		LobbyCharactor();
		virtual ~LobbyCharactor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
