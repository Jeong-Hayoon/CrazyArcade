#pragma once
#include "hyGameObject.h"


// ¹°Ç³¼±

namespace hy
{
	class Balloon : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Use,
			End,
		};

		Balloon();
		virtual ~Balloon();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Use();


	private:
		eState mState;
	};
}


