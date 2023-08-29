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

		// ---- 아이템 관련 함수 ----
		// 물풍선 최대 개수 증가(Balloon)
		static void BombLimitUp() { BombLimit++; }
		// 이동 속도 증가(VelocitySkate)
		void MoveSpeedUp() { MoveSpeed += 50; }
		// 이동 속도 최대로 증가(Devil)
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
		static UINT BombLimit;					// 물풍선 최대 사용 개수
		static float MoveSpeed;						// 기본 속도
		static eItem ActiveItem;				// 장착되어 있는 아이템(0이면 실드, 1이면 바늘로 지정)
		static UINT BombFlowCount;				// 물줄기, 물풍선 생성 시 증가

		static bool UseItemNum;
		static bool Trigger;
		static float SpeedTemp;

	};
}

// ctrl 사용해야만 사용할 수 있는 아이템 : Shield, Needle
// 습득만 해도 사용되는 아이템 : Potion, PotionMax, Balloon, VelocitySkate, Devil





