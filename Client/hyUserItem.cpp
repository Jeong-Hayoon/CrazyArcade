#include "hyUserItem.h"

namespace hy
{
	UserItem::UserItem()
		: mstate(eState::Idle)
	{
	}

	UserItem::~UserItem()
	{
	}

	void UserItem::Idle()
	{
	}

	void UserItem::Use()
	{
	}

	void UserItem::Extinct()
	{
	}

	void UserItem::Initialize()
	{
		GameObject::Initialize();
	}

	void UserItem::Update()
	{
		GameObject::Update();
	}

	void UserItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void UserItem::OnCollisionEnter(Collider* other)
	{
	}

	void UserItem::OnCollisionStay(Collider* other)
	{
	}

	void UserItem::OnCollisionExit(Collider* other)
	{
	}
}
