#pragma once
#include "hyItem.h"
#include "hyBazzi.h"
#include "hyDao.h"


//�ǵ� ���

namespace hy
{
	class ShieldEffect : public Item
	{
	public:

		enum class eState
		{
			Idle,
			Use,
			End
		};

		ShieldEffect(/*class Bazzi* owner*/);
		virtual ~ShieldEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		virtual void Idle() override;
		virtual void Use() override;

	private:
		eState mState;
		Bazzi* mBazziOwner;
		Dao* mDaoOwner;

	};
}


