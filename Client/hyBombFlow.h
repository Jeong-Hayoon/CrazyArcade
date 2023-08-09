#pragma once
#include "hyGameObject.h"
#include "hyTransform.h"


namespace hy
{
	class BombFlow : public GameObject
	{
	public:
	
		enum class eState
		{
			Idle,
			Extinct,
			End,
		};

		BombFlow();
		virtual ~BombFlow();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Left();
		void Right();
		void Up();
		void Down();

		void LeftIdle();
		void RightIdle();
		void UpIdle();
		void DownIdle();

		void Extinct();

	private:
		eState mState;
	};
}




