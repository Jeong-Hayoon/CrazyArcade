#pragma once
#include "hyGameObject.h"


// ½Çµå 
namespace hy
{
	class Shield : public GameObject
	{
		Shield();
		virtual ~Shield();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	};
}

