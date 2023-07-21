#pragma once
#include "hyGameObject.h"
#include "hyTransform.h"

namespace hy
{
	class Bomb : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Pop,
			End,
		};
		Bomb();
		virtual ~Bomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Pop();

	private:
		eState mState;
	};
}



