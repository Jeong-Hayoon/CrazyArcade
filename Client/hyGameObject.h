#pragma once
#include "hyEntity.h"
#include "hyComponent.h"

namespace hy
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Pause,
			Dead,
			End,
		};

		friend static __forceinline void Destroy(GameObject* gameObject);


		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		template <typename T>
		T* GetComponent()
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				// �ڽ�Ÿ�԰� TŸ���� ��ġ�Ѵٸ�
				// �ּҸ� ��ȯ �׷����ʴٸ� nullptr ��ȯ
				comp = dynamic_cast<T*>(c);
				if (comp != nullptr)
					return comp;
			}

			return comp;
 		}

		template <typename T>
		T* AddComponent() 
		{
			T* comp = new T();
			mComponents.push_back(comp);
			comp->SetOwner(this);

			return comp;
		}

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		eState GetState() { return mState; }
		void Pause() { mState = eState::Pause; }

	private:
		void death() { mState = eState::Dead; }

	private:
		std::vector<Component*> mComponents;		// Component(eComponentType, GameObject)
		eState mState;

	// ���� ���� ������Ʈ�� �޸� �������ִ� �Լ�
	static __forceinline void Destroy(GameObject* gameObject)
	{
		gameObject->death();
	}

	};
}


