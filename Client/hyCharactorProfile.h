#pragma once
#include "hyGameObject.h"

namespace hy
{
	class CharactorProfile : public GameObject
	{
	public:
		CharactorProfile();
		virtual ~CharactorProfile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
