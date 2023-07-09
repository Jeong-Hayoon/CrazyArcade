#pragma once
#include "wzEntity.h"
#include "wzGameObject.h"


namespace wz
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);


		void AddGameObject(GameObject* gameObj)
		{
			mGameObjects.push_back(gameObj);
		}

	private:
		std::vector<GameObject*> mGameObjects;
	};
}


