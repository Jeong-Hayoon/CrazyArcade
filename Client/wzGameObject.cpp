#include "wzGameObject.h"
#include "wzTransform.h"
#include "wzSpriteRenderer.h"

namespace wz
{
	GameObject::GameObject()
	{
		mComponents.push_back(new Transform());
		mComponents[0]->SetOwner(this);	//GameObject(this)가 부모라는 것을 SetOwner로 알려줌

		mComponents.push_back(new SpriteRenderer());
		mComponents[1]->SetOwner(this);
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			comp->Render(hdc);
		}
	}
}
