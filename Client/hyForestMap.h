#pragma once
#include "hyScene.h"

namespace hy
{
	class ForestMap : public Scene
	{
	public:
		ForestMap();
		virtual ~ForestMap();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}

