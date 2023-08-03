#pragma once
#include "hyGameObject.h"

namespace hy
{
	// MoveSpeedUp �Լ�
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

		// ��ǳ�� �ִ� ���� ����(Balloon)
		void BombLimitUp() { BombLimit++;}
		// �̵� �ӵ� ����(VelocitySkate)
		void MoveSpeedUp() { MoveSpeed += 50; }
		// �̵� �ӵ� �ִ�� ����(Devil)
		void MoveSpeedMax() { MoveSpeed = 300; }
		// ��ǳ���� �������� �� �һ�(Needle)
		void Revive() { Life = 1; }
		// (Shield)
		// (Potion)
		// (PotionMax)

		class Texture* mFloorTexture;

	private:
		eState mState;
		eDirection mDirection;
		UINT BombLimit;		// ��ǳ�� �ִ� ��� ����
		float MoveSpeed;	// �⺻ �ӵ�
		bool Life;			// 0�̸� ��ǳ���� �����ִ� ����, 1�̸� ��ǳ���� �������� ���� ����
	};
}

// ctrl ����ؾ߸� ����� �� �ִ� ������ : Shield, Needle
// ���游 �ص� ���Ǵ� ������ : Potion, PotionMax, Balloon, VelocitySkate, Devil



