#include "hyItem.h"

namespace hy
{
	Item::Item()
		: mstate(eState ::Idle)
	{
	}

	Item::~Item()
	{
	}

	void Item::Idle()
	{
	}

	void Item::Use()
	{
	}

	void Item::Extinct()
	{
	}

	void Item::Initialize()
	{
		GameObject::Initialize();
	}

	void Item::Update()
	{
		GameObject::Update();
	}

	void Item::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Item::OnCollisionEnter(Collider* other)
	{

	}

	void Item::OnCollisionStay(Collider* other)
	{
	}

	void Item::OnCollisionExit(Collider* other)
	{
	}
}
