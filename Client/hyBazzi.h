#pragma once
#include "hyGameObject.h"

namespace hy
{
	class Bazzi : public GameObject
	{
	public:
		enum class eDirection
		{
			Up,
			Down,
			Left,
			Right
		};

		enum class eState
		{
			Make,
			Idle,
			Move,
			MoveStop,
			Ready,
			Trap,
			Live,
			Dead,
			Victory,
			End,
		};
		Bazzi();
		virtual ~Bazzi();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eDirection GetDirection() { return mDirection; }

		void Make();
		void Idle();
		void Move();
		void MoveStop();
		void DropWater();	
		void Ready();
		void Trap();
		void Live();
		void Dead();
		void Victory();

	private:
		eState mState;
		eDirection mDirection;
	};
}



