#pragma once
#include "wzGameObject.h"

namespace wz
{
	class Player : GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

	private:

	};
}

