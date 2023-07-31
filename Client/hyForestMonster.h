#pragma once
#include "hyGameObject.h"

namespace hy
{
	class ForestMonster : public GameObject
	{
	public:
		enum class eState
		{
			Up,
			Down,
			Left,
			Right,
			Dead,
			End,
		};

		ForestMonster();
		virtual ~ForestMonster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Up();
		void Down();
		void Left();
		void Right();

		void Dead();

	private:
		eState mState;
		float mDeathTime;
		static float MonsterTime;
	};
}



