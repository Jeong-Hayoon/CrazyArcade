#pragma once
#include "hyGameObject.h"

namespace hy
{
	class Dao : public GameObject
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

		enum class eItem
		{
			Shield,
			Needle,
			None
		};

		Dao();
		virtual ~Dao();

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
		void Dead();
		void BalloonDead();
		void Victory();

		// ---- ������ ���� �Լ� ----
		// ��ǳ�� �ִ� ���� ����(Balloon)
		static void BombLimitUp() { BombLimit++; }
		// �̵� �ӵ� ����(VelocitySkate)
		void MoveSpeedUp() { MoveSpeed += 50; }
		// �̵� �ӵ� �ִ�� ����(Devil)
		void MoveSpeedMax() { MoveSpeed = 300; }


		static float GetMoveSpeed() { return MoveSpeed; }
		static void SetMoveSpeed(float speed) { MoveSpeed = speed; }

		eItem GetActiveItem() { return ActiveItem; }
		void SetActiveItem(eItem eatitem) { ActiveItem = eatitem; }

		class Texture* mFloorTexture;


		static UINT GetBombFlowCount() { return BombFlowCount; }
		static void SetBombFlowCount() { BombFlowCount++; }
		static void MaxBombFlowCount() { BombFlowCount = 9; }

		static bool GetUseItemNum() { return UseItemNum; }
		static void SetUseItemNum(bool n) { UseItemNum = n; }

		bool GetTrigger() { return Trigger; }

		static void ResetDao();

	private:
		eState mState;
		eDirection mDirection;
		static UINT BombLimit;					// ��ǳ�� �ִ� ��� ����
		static float MoveSpeed;						// �⺻ �ӵ�
		static eItem ActiveItem;				// �����Ǿ� �ִ� ������(0�̸� �ǵ�, 1�̸� �ٴ÷� ����)
		static UINT BombFlowCount;				// ���ٱ�, ��ǳ�� ���� �� ����

		static bool UseItemNum;
		static bool Trigger;
		static float SpeedTemp;

	};
}

// ctrl ����ؾ߸� ����� �� �ִ� ������ : Shield, Needle
// ���游 �ص� ���Ǵ� ������ : Potion, PotionMax, Balloon, VelocitySkate, Devil





