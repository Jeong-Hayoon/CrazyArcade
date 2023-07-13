#pragma once
#include "hyScene.h"

namespace hy
{
	class IceMap : public Scene
	{
	public:
		IceMap();
		virtual ~IceMap();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}

