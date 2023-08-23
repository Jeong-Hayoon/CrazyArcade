#include "hyStagePick.h"
#include "hyTransform.h"
#include "hyInput.h"
#include "hyTime.h"
#include "hySpriteRenderer.h"

namespace hy
{
	StagePick::StagePick()
	{
	}
	StagePick::~StagePick()
	{
	}
	void StagePick::Initialize()
	{
	}

	void StagePick::Update()
	{
		GameObject::Update();
	}

	void StagePick::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}