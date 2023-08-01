#pragma once
#include "hyItem.h"

//물줄기 최대 아이템

namespace hy
{
	class PotionMax : public Item
	{
	public:
		enum class eState
		{
			Idle,
			Use,
			Extinct,
			End,
		};

		PotionMax();
		virtual ~PotionMax();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		virtual void Idle() override;
		virtual void Use() override;
		virtual void Extinct() override;

	private:
		eState mState;
	};
}



