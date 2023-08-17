#pragma once
#include "hyItem.h"
#include "hyBazzi.h"
#include "hyDao.h"


//실드 사용

namespace hy
{
	class ShieldEffect : public GameObject
	{
	public:

		enum class eState
		{
			Idle,
			Use,
			End
		};

		ShieldEffect();
		virtual ~ShieldEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Use();

		void SetBazzi(Bazzi* player) { mBazziOwner = player; }

	private:
		eState mState;
		Bazzi* mBazziOwner;
		Dao* mDaoOwner;

	};
}



