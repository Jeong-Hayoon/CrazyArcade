#pragma once
#include "hyGameObject.h"

namespace hy
{
	class PlaySceneBG : public GameObject
	{
	public:
		PlaySceneBG();
		virtual ~PlaySceneBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
