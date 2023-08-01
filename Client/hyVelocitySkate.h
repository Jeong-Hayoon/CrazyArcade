#pragma once
#include "hyItem.h"

//속도 증가 아이템

namespace hy
{
	class VelocitySkate : public Item
	{
	public:
		enum class eState
		{
			Idle,
			Use,
			Extinct,
			End,
		};

		VelocitySkate();
		virtual ~VelocitySkate();

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



