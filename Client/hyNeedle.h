#pragma once
#include "hyGameObject.h"

// ¹Ù´Ã
namespace hy
{
	class Needle : public GameObject
	{
		Needle();
		virtual ~Needle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	};
}

