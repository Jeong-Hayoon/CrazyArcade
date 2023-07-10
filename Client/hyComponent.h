#pragma once
#include "hyEntity.h"

namespace hy
{
	using namespace enums;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc); 

		void SetOwner(class GameObject* owner) { mOwner = owner; }
		class GameObject* GetOwner() { return mOwner; }

	private:
		const eComponentType mType;	// ComponentType 자신의 타입을 가지고 이음
		class GameObject* mOwner;
	};
}


