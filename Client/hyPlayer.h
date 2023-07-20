#pragma once
#include "hyGameObject.h"

namespace hy
{
	class Player : public GameObject
	{
	public:

		enum class eState
		{
			Idle,
			Move,
			DropWater,
			Death,
			End,
		};

		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Move();
		void DropWater();
		void Dead();

	private:
		eState mState;

	};
}

