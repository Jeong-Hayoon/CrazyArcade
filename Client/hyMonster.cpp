#include "hyMonster.h"

namespace hy
{
	hy::Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
	}

	void Monster::Update()
	{
		GameObject::Update();
	}

	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Monster::OnCollisionEnter(Collider* other)
	{
	}

	void Monster::OnCollisionStay(Collider* other)
	{
	}

	void Monster::OnCollisionExit(Collider* other)
	{
	}
}
