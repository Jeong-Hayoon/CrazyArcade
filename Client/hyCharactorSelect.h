#pragma once
#include "hyGameObject.h"

namespace hy
{
	class CharactorSelect : public GameObject
	{
	public:
		CharactorSelect();
		virtual ~CharactorSelect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
