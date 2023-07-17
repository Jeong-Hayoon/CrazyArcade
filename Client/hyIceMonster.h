#pragma once
#include "hyGameObject.h"

namespace hy
{
	class IceMonster : public GameObject
	{
	public:
		IceMonster();
		virtual ~IceMonster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

	private:
	};
}

