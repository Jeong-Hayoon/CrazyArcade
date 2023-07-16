#pragma once
#include "hyGameObject.h"

namespace hy
{
	class Dao : public GameObject
	{
	public:
		Dao();
		virtual ~Dao();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

	private:

	};
}

