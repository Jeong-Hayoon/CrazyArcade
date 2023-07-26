#include "hyLayer.h"

namespace hy
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Initialize()
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetState() == GameObject::eState::Pause)
				continue;

			obj->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetState() == GameObject::eState::Pause)
				continue;

			obj->Render(hdc);
		}

		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->GetState() == GameObject::eState::Dead)
			{
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}


}
