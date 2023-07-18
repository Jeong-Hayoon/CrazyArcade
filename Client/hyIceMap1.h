#pragma once
#include "hyScene.h"

namespace hy
{
	class IceMap1 : public Scene
	{
	public:
		IceMap1();
		virtual ~IceMap1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}

