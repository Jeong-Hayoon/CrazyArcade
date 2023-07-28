#pragma once
#include "hyGameObject.h"


// 물줄기 증가 아이템

namespace hy
{
	class Potion : public GameObject
	{
		Potion();
		virtual ~Potion();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	};
}

