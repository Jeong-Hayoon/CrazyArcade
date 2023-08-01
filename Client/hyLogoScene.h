#pragma once
class LogoScene
{
};

#pragma once
#include "hyScene.h"

namespace hy
{
	class LogoScene : public Scene
	{
	public:
		LogoScene();
		virtual ~LogoScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}

