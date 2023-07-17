#pragma once
#include "hyGameObject.h"

namespace hy
{
	class PirateMonster : public GameObject
	{
	public:
		PirateMonster();
		virtual ~PirateMonster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

	private:
	};
}

