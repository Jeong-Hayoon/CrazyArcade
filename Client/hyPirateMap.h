#pragma once
#include "hyScene.h"

namespace hy
{
	class PirateMap : public Scene
	{
	public:
		PirateMap();
		virtual ~PirateMap();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}


