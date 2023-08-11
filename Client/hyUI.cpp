#include "hyUI.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hySpriteRenderer.h"

namespace hy
{
	UI::UI()
	{
	}
	UI::~UI()
	{
	}
	void UI::Initialize()
	{
		GameObject::Initialize();
	}

	void UI::Update()
	{
		GameObject::Update();
	}

	void UI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}