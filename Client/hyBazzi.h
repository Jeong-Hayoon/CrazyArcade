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

		enum class eItem
		{
			Shield,
			Needle,
			None
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

		// 물풍선 최대 개수 증가(Balloon)
		void BombLimitUp() { BombLimit++;}
		// 이동 속도 증가(VelocitySkate)
		void MoveSpeedUp() { MoveSpeed += 50; }
		// 이동 속도 최대로 증가(Devil)
		void MoveSpeedMax() { MoveSpeed = 300; }
		// 물풍선에 갇혀있을 때 소생(Needle)
		void Revive() { Life = 1; }
		// (Shield)
		// (Potion)
		// (PotionMax)

		eItem GetActiveItem() { return ActiveItem; }
		void SetActiveItem(eItem eatitem) { ActiveItem = eatitem; }

		static UINT GetBombFlow() { return BombFlow; }
		void AddBombFlow() { BombFlow++; }
		class Texture* mFloorTexture;

	private:
		eState mState;
		eDirection mDirection;
		UINT BombLimit;						// 물풍선 최대 사용 개수
		float MoveSpeed;					// 기본 속도
		bool Life;							// 0이면 물풍선에 갇혀있는 상태, 1이면 물풍선에 갇혀있지 않은 상태
		static eItem ActiveItem;			// 장착되어 있는 아이템(0이면 실드, 1이면 바늘로 지정)
		static UINT BombFlow;				// 물줄기
	};
}

// ctrl 사용해야만 사용할 수 있는 아이템 : Shield, Needle
// 습득만 해도 사용되는 아이템 : Potion, PotionMax, Balloon, VelocitySkate, Devil



