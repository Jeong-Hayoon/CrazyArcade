#pragma once
#include "hyGameObject.h"


// 속도 증가 아이템

namespace hy
{
	class VelocitySkate : public GameObject
	{
		VelocitySkate();
		virtual ~VelocitySkate();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	};
}

