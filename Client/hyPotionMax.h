#pragma once
#include "hyGameObject.h"


// 물줄기 최대 아이템
namespace hy
{
	class PotionMax : public GameObject
	{
		PotionMax();
		virtual ~PotionMax();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	};
}

