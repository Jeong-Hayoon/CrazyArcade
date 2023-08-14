#pragma once
#include "hyScene.h"
#include "hySound.h"


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

		virtual void Enter();
		virtual void Exit();

	private:
		static Sound* sound;
	};
}

