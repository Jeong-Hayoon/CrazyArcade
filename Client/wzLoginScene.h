#pragma once
#include "wzScene.h"

namespace wz
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

