#include "hyGameObject.h"
#include "hyTransform.h"
#include "hySpriteRenderer.h"

namespace hy
{
	GameObject::GameObject()
		: mState(eState::Active)

	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			comp->Initialize();
		}
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

	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}
}
