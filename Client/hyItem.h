#pragma once
#include "hyGameObject.h"

namespace hy
{
	class Item : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Use,
			Extinct,
			End,
		};


		Item();
		virtual ~Item();

		virtual void Idle() = 0;
		virtual void Use() = 0;
		virtual void Extinct() = 0;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		eState mstate;
	};
}

