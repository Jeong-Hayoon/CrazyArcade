#pragma once
#include "hyScene.h"

namespace hy
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		virtual ~ToolScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
