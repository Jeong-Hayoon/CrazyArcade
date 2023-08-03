#pragma once
#include "hyScene.h"
#include "hySound.h"

namespace hy
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();
	
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		static Sound* sound;

	};
}

