#pragma once
#include "hyItem.h"

//실드 사용

namespace hy
{
	class UseShield : public Item
	{
	public:

		UseShield();
		virtual ~UseShield();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		virtual void Idle() override;
		virtual void Use() override;

	private:
		eState mState;
	};
}



