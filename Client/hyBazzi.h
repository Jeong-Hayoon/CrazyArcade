#pragma once
#include "hyGameObject.h"

namespace hy
{
	// MoveSpeedUp 함수
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
			Trap,
			Live,
			Dead,
			BalloonDead,
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
		void Trap();
		void Live();
		void Dead ();
		void BalloonDead ();
		void Victory();

		// 물풍선 최대 개수 증가
		void BombLimitUp() { BombLimit++;}
		// 이동 속도 증가
		void MoveSpeedUp() { MoveSpeed += 100; }

		class Texture* mFloorTexture;

	private:
		eState mState;
		eDirection mDirection;
		UINT BombLimit;		// 물풍선 최대 사용 개수
		float MoveSpeed;	// 기본 속도
	};
}



