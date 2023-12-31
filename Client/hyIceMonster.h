#pragma once
#include "hyGameObject.h"

namespace hy
{
	class IceMonster : public GameObject
	{
	public:
		enum class eState
		{
			Up,
			Down,
			Left,
			Right,
			Move,
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

		IceMonster();
		virtual ~IceMonster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Move();

		void Up();
		void Down();
		void Left();
		void Right();

		void Dead();

	private:
		eState mState;
		float mDeathTime;
		eDirection mDirection;
		float MonsterTime;
		float MoveSpeed;						// �⺻ �ӵ�
		float Statetime;


	};
}




