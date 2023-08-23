#pragma once
#include "hyGameObject.h"

namespace hy
{
	class StagePick : public GameObject
	{
	public:
		StagePick();
		virtual ~StagePick();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
