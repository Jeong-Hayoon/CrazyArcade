#pragma once
#include "hyGameObject.h"
#include "hyTransform.h"


namespace hy
{
	class ForestBossBomb : public GameObject
	{
	public:
		enum class eState
		{
			Flow,
			Pop,
			End,
		};
		ForestBossBomb();
		virtual ~ForestBossBomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void Flow();
		void Pop();

	private:
		eState mState;
	};
}



