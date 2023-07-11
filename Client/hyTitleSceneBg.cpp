#include "hyTitleSceneBG.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"

namespace hy
{
	TitleSceneBG::TitleSceneBG()
	{
	}
	TitleSceneBG::~TitleSceneBG()
	{
	}
	void TitleSceneBG::Initialize()
	{
	}

	void TitleSceneBG::Update()
	{
		GameObject::Update();
	}

	void TitleSceneBG::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
