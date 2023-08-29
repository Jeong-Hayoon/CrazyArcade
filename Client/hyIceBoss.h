#pragma once
#include "hyGameObject.h"

namespace hy
{
	class IceBoss : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Up,
			Down,
			Left,
			Right,
			Hit,
			Attack,
			Dead,
			End,
		};

		enum class eDirection
		{
			Up,
			Down,
			Left,
			Right
		};

		IceBoss();
		virtual ~IceBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Idle();

		void Up();
		void Down();
		void Left();
		void Right();

		void Hit();

		void Attack();

		void Dead();

	private:
		eState mState;
		float mDeathTime;
		static float BossTime;			// ���ʸ��� �̵��Ұ���
		static float BubbleTime;		// ��ǳ���� �����ִ� �ð�
		static UINT IceBossHP;
		static float Attacktime;
		eDirection mDirection;


	};
}




