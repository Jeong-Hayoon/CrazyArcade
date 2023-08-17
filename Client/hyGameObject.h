#pragma once
#include "hyEntity.h"
#include "hyComponent.h"

namespace hy
{
	class GameObject : public Entity
	{
	public:
		//GameObject�� ����
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

		template <typename T>
		T* DeleteComponent()
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					return comp;

				GameObject* Obj = *iter;
				delete Obj;
				Obj = nullptr;
				iter = mGameObjects.erase(iter);

			}

			
		}

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		eState GetState() { return mState; }
		void Pause() { mState = eState::Pause; }

		void SetLayerType(eLayerType LayerType) { mLayerType = LayerType; }
		eLayerType GetLayerType() { return mLayerType; }



	private:
		std::vector<Component*> mComponents;		// Component(eComponentType, GameObject)
		eState mState;
		eLayerType mLayerType;
		void death() { mState = eState::Dead; }


	};
	// ���� ���� ������Ʈ�� �޸� �������ִ� �Լ�
	static __forceinline void Destroy(GameObject* gameObject)
	{
		gameObject->death();
	}

}


