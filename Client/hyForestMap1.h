#pragma once
#include "hyScene.h"

namespace hy
{
	class ForestMap1 : public Scene
	{
	public:
		ForestMap1();
		virtual ~ForestMap1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}

