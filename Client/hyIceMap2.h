#pragma once
#include "hyScene.h"

namespace hy
{
	class IceMap2 : public Scene
	{
	public:
		IceMap2();
		virtual ~IceMap2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}

