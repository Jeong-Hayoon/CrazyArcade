#pragma once
#include "hyGameObject.h"

namespace hy
{
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

	private:

	};
}

