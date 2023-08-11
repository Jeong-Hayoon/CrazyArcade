#pragma once
#include "hyGameObject.h"

namespace hy
{
	class UI : public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
