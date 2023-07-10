#pragma once
#include "hyScene.h"

namespace hy
{
	class LoginScene : public Scene
	{
	public:
		LoginScene();
		virtual ~LoginScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}

