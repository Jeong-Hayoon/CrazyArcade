#pragma once
#include "hyGameObject.h"

namespace hy
{
	class ForestBoss : public GameObject
	{
	public:
		ForestBoss();
		virtual ~ForestBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

	private:
		UINT MonsterQuantity;
	};
}

