#pragma once
#include "hyGameObject.h"

namespace hy
{
	class ForestMonster : public GameObject
	{
	public:
		ForestMonster();
		virtual ~ForestMonster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;
		int direction;

	private:
	};
}

