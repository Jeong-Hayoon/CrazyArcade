#pragma once
#include "hyGameObject.h"

namespace hy
{
	class TitleSceneBG : public GameObject
	{
	public:
		TitleSceneBG();
		virtual ~TitleSceneBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
