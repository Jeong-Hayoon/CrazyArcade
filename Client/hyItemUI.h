#pragma once
#include "hyGameObject.h"

namespace hy
{
	class ItemUI : public GameObject
	{
	public:
		ItemUI();
		virtual ~ItemUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
