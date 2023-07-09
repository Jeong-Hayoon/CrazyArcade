#pragma once
#include "wzScene.h"

namespace wz
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
			
	};
}

