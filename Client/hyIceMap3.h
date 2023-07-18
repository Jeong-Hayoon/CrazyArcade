#pragma once
class IceMap3
{
};

#pragma once
#include "hyScene.h"

namespace hy
{
	class IceMap3 : public Scene
	{
	public:
		IceMap3();
		virtual ~IceMap3();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}

