#pragma once
#include "hyGameObject.h"

namespace hy
{
	class ForestMonster : public GameObject
	{
	public:
		enum class eState
		{
			Move,
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

		void Move();
		void Dead();

	private:
		eState mState;

	};
}



